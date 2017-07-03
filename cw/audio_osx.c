//
//  audio_osx.c
//  dtmf
//
//  Created by Albin Stigö on 26/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "audio_osx.h"
#include "audiodevice.h"

#include <AudioToolbox/AudioToolbox.h>
#include <assert.h>
#include <dispatch/dispatch.h>
#include <string.h>

#include "TPCircularBuffer.h"

const int kOutputBus            = 0;
const int kInputBus             = 1;
const int kSlicesInRingbuffer   = 3;
const int kFramesPerSlice       = 1024;

TPCircularBuffer cb;

dispatch_semaphore_t audio_semaphore;

OSStatus outputProc(void *inRefCon,
                   AudioUnitRenderActionFlags *ioActionFlags,
                   const AudioTimeStamp *inTimeStamp,
                   UInt32 inBusNumber,
                   UInt32 inNumberFrames,
                   AudioBufferList * ioData) {
    
    //AudioComponentInstance outputUnit = (AudioComponentInstance) inRefCon;
    OSStatus status = noErr;
    
    int32_t available;
    float *tail = (float*) TPCircularBufferTail(&cb, &available);
    
    if (available/sizeof(float) >= inNumberFrames) {
        memcpy(ioData->mBuffers[0].mData, tail, inNumberFrames * sizeof(float));
        memcpy(ioData->mBuffers[1].mData, tail, inNumberFrames * sizeof(float));
        TPCircularBufferConsume(&cb, inNumberFrames * sizeof(float));
        
        //puts("a");
        
        // signal that we have space in circularbuffer.
        dispatch_semaphore_signal(audio_semaphore);
    } else {
        //puts("s");
        for(UInt32 i=0; i<ioData->mNumberBuffers;i++) {
            memset(ioData->mBuffers[i].mData, 0, ioData->mBuffers[i].mDataByteSize);
        }
    }
    
    return status;
}

uint32_t writeAudio(float *samples, uint32_t length) {
    
    dispatch_semaphore_wait(audio_semaphore, DISPATCH_TIME_FOREVER);
    
    // Get pointer to head of ringbuffer
    int32_t available;
    TPCircularBufferHead(&cb, &available);
    assert((available/sizeof(float)) >= length);
    
    TPCircularBufferProduceBytes(&cb, (const void*) samples, sizeof(float) * length);

    return length;
}


OSStatus openAudio() {
    
    OSStatus        status;
    UInt32          size;
    AudioUnit       outputUnit;
    AUGraph         graph;
    
    status = NewAUGraph(&graph);
    checkError(status);
    //Open the Graph, AudioUnits are opened but not initialized
    status = AUGraphOpen(graph);
    checkError(status);
    
    AudioComponentDescription   desc;
    desc.componentType          = kAudioUnitType_Output;
    desc.componentSubType       = kAudioUnitSubType_HALOutput;
    
    desc.componentManufacturer  = kAudioUnitManufacturer_Apple;
    desc.componentFlags         = 0;
    desc.componentFlagsMask     = 0;
    
    AUNode outputNode;
    status = AUGraphAddNode(graph, &desc, &outputNode);
    checkError(status);
    
    status = AUGraphNodeInfo(graph, outputNode, &desc, &outputUnit);
    
    UInt32 enableIO = 1; // Enable output
    status = AudioUnitSetProperty(outputUnit,
                                  kAudioOutputUnitProperty_EnableIO,
                                  kAudioUnitScope_Output,
                                  kOutputBus,   //output element
                                  &enableIO,
                                  sizeof(enableIO));
    checkError(status);
    
    AudioDeviceID outputDevice = defaultOutputDevice();
    
    // Set current device
    status = AudioUnitSetProperty(outputUnit,
                                  kAudioOutputUnitProperty_CurrentDevice,
                                  kAudioUnitScope_Global,
                                  0,
                                  &outputDevice,
                                  sizeof(outputDevice));
    checkError(status);
    
    // Get format
    // Stream format
    AudioStreamBasicDescription streamFormat = { 0 };
    size = sizeof(streamFormat);
    status = AudioUnitGetProperty (outputUnit,
                                   kAudioUnitProperty_StreamFormat,
                                   kAudioUnitScope_Input,
                                   1,
                                   &streamFormat,
                                   &size);

    checkError(status);
    
    /*printf("%f\n"
           "%d\n",
           streamFormat.mSampleRate,
           streamFormat.mChannelsPerFrame);*/
    
    AudioObjectPropertyAddress propertyAddress1 = { kAudioDevicePropertyBufferFrameSize,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMaster };
    
    // Set buffer length.
    status = AudioObjectSetPropertyData(outputDevice,
                                        &propertyAddress1,
                                        0,
                                        NULL,
                                        sizeof(kFramesPerSlice),
                                        &kFramesPerSlice);
    checkError(status);
    // Also need to set this; maximum frames per slice.
    status = AudioUnitSetProperty(outputUnit,
                                  kAudioUnitProperty_MaximumFramesPerSlice,
                                  kAudioUnitScope_Global,
                                  0,
                                  &kFramesPerSlice,
                                  sizeof(kFramesPerSlice));
    checkError(status);
    
    AURenderCallbackStruct output;
    output.inputProc = outputProc;
    output.inputProcRefCon = outputUnit;
    
    status = AudioUnitSetProperty(outputUnit,
                                  kAudioUnitProperty_SetRenderCallback,
                                  kAudioUnitScope_Input,
                                  0,
                                  &output,
                                  sizeof(output));
    checkError(status);
    
    // Store periods in ringbuffer.
    TPCircularBufferInit(&cb, kSlicesInRingbuffer * kFramesPerSlice * (streamFormat.mBytesPerFrame >> 1));
    
    // Semaphore we use for waiting for audio to arrive
    audio_semaphore = dispatch_semaphore_create(kSlicesInRingbuffer - 1);
    
    status = AUGraphInitialize(graph);
    checkError(status);
    
    status = AUGraphStart(graph);
    checkError(status);
    
    return status;
}
