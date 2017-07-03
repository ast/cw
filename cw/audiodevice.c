//
//  audiodevice.c
//  fcdfm
//
//  Created by Albin Stigö on 02/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "audiodevice.h"

void checkError(OSStatus status) {
    
    switch (status) {
        case noErr: return;
        case kAudio_ParamError:
            printf("Error: kAudio_ParamError \n");
            break;
            
        case kAUGraphErr_NodeNotFound:
            printf("Error: kAUGraphErr_NodeNotFound \n");
            break;
            
        case kAUGraphErr_OutputNodeErr:
            printf( "Error: kAUGraphErr_OutputNodeErr \n");
            break;
            
        case kAUGraphErr_InvalidConnection:
            printf("Error: kAUGraphErr_InvalidConnection \n");
            break;
            
        case kAUGraphErr_CannotDoInCurrentContext:
            printf( "Error: kAUGraphErr_CannotDoInCurrentContext \n");
            break;
            
        case kAUGraphErr_InvalidAudioUnit:
            printf( "Error: kAUGraphErr_InvalidAudioUnit \n");
            break;
            
        case kMIDIInvalidClient :
            printf( "kMIDIInvalidClient ");
            break;
            
        case kMIDIInvalidPort :
            printf( "Error: kMIDIInvalidPort ");
            break;
            
        case kMIDIWrongEndpointType :
            printf( "Error: kMIDIWrongEndpointType");
            break;
            
        case kMIDINoConnection :
            printf( "Error: kMIDINoConnection ");
            break;
            
        case kMIDIUnknownEndpoint :
            printf( "Error: kMIDIUnknownEndpoint ");
            break;
            
        case kMIDIUnknownProperty :
            printf( "Error: kMIDIUnknownProperty ");
            break;
            
        case kMIDIWrongPropertyType :
            printf( "Error: kMIDIWrongPropertyType ");
            
            
        case kMIDINoCurrentSetup :
            printf( "Error: kMIDINoCurrentSetup ");
            break;
            
        case kMIDIMessageSendErr :
            printf( "kError: MIDIMessageSendErr ");
            break;
            
        case kMIDIServerStartErr :
            printf( "kError: MIDIServerStartErr ");
            break;
            
        case kMIDISetupFormatErr :
            printf( "Error: kMIDISetupFormatErr ");
            break;
            
        case kMIDIWrongThread :
            printf( "Error: kMIDIWrongThread ");
            break;
            
        case kMIDIObjectNotFound :
            printf( "Error: kMIDIObjectNotFound ");
            break;
            
        case kMIDIIDNotUnique :
            printf( "Error: kMIDIIDNotUnique ");
            break;
            
        case kMIDINotPermitted:
            printf( "Error: kMIDINotPermitted: Have you enabled the audio background mode in your ios app?");
            break;
            
        case kAudioToolboxErr_InvalidSequenceType :
            printf( "Error: kAudioToolboxErr_InvalidSequenceType ");
            break;
            
        case kAudioToolboxErr_TrackIndexError :
            printf( "Error: kAudioToolboxErr_TrackIndexError ");
            break;
            
        case kAudioToolboxErr_TrackNotFound :
            printf( "Error: kAudioToolboxErr_TrackNotFound ");
            break;
            
        case kAudioToolboxErr_EndOfTrack :
            printf( "Error: kAudioToolboxErr_EndOfTrack ");
            break;
            
        case kAudioToolboxErr_StartOfTrack :
            printf( "Error: kAudioToolboxErr_StartOfTrack ");
            break;
            
        case kAudioToolboxErr_IllegalTrackDestination :
            printf( "Error: kAudioToolboxErr_IllegalTrackDestination");
            break;
            
        case kAudioToolboxErr_NoSequence :
            printf( "Error: kAudioToolboxErr_NoSequence ");
            break;
            
        case kAudioToolboxErr_InvalidEventType :
            printf( "Error: kAudioToolboxErr_InvalidEventType");
            break;
            
        case kAudioToolboxErr_InvalidPlayerState :
            printf( "Error: kAudioToolboxErr_InvalidPlayerState");
            break;
            
        case kAudioUnitErr_InvalidProperty :
            printf( "Error: kAudioUnitErr_InvalidProperty");
            break;
            
        case kAudioUnitErr_InvalidParameter :
            printf( "Error: kAudioUnitErr_InvalidParameter");
            break;
            
        case kAudioUnitErr_InvalidElement :
            printf( "Error: kAudioUnitErr_InvalidElement");
            break;
            
        case kAudioUnitErr_NoConnection :
            printf( "Error: kAudioUnitErr_NoConnection");
            break;
            
        case kAudioUnitErr_FailedInitialization :
            printf( "Error: kAudioUnitErr_FailedInitialization");
            break;
            
        case kAudioUnitErr_TooManyFramesToProcess :
            printf( "Error: kAudioUnitErr_TooManyFramesToProcess");
            break;
            
        case kAudioUnitErr_InvalidFile :
            printf( "Error: kAudioUnitErr_InvalidFile");
            break;
            
        case kAudioUnitErr_FormatNotSupported :
            printf( "Error: kAudioUnitErr_FormatNotSupported");
            break;
            
        case kAudioUnitErr_Uninitialized :
            printf( "Error: kAudioUnitErr_Uninitialized");
            break;
            
        case kAudioUnitErr_InvalidScope :
            printf( "Error: kAudioUnitErr_InvalidScope");
            break;
            
        case kAudioUnitErr_PropertyNotWritable :
            printf( "Error: kAudioUnitErr_PropertyNotWritable");
            break;
            
        case kAudioUnitErr_InvalidPropertyValue :
            printf( "Error: kAudioUnitErr_InvalidPropertyValue");
            break;
            
        case kAudioUnitErr_PropertyNotInUse :
            printf( "Error: kAudioUnitErr_PropertyNotInUse");
            break;
            
        case kAudioUnitErr_Initialized :
            printf( "Error: kAudioUnitErr_Initialized");
            break;
            
        case kAudioUnitErr_InvalidOfflineRender :
            printf( "Error: kAudioUnitErr_InvalidOfflineRender");
            break;
            
        case kAudioUnitErr_Unauthorized :
            printf( "Error: kAudioUnitErr_Unauthorized");
            break;
            
        default:
            printf("Error: \(error)");
            break;
    }
    
    
    abort();
}

// Default input device
AudioDeviceID defaultInputDevice()
{
    AudioDeviceID deviceID = 0;
    UInt32 size = sizeof(AudioDeviceID);
    AudioObjectPropertyAddress propertyAddress = { kAudioHardwarePropertyDefaultInputDevice,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMaster };
    
    OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject,
                                              &propertyAddress,
                                              0,
                                              NULL,
                                              &size,
                                              &deviceID);
    
    checkError(status);
    
    //printf("Default input device: %d\n", deviceID);
    
    return deviceID;
}


// Default output device
AudioDeviceID defaultOutputDevice()
{
    AudioDeviceID deviceID = 0;
    UInt32 size = sizeof(AudioDeviceID);
    AudioObjectPropertyAddress propertyAddress = { kAudioHardwarePropertyDefaultOutputDevice,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMaster };
    
    OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject,
                                              &propertyAddress,
                                              0,
                                              NULL,
                                              &size,
                                              &deviceID);
    
    checkError(status);
    
    //printf("Default output device: %d\n", deviceID);
    
    return deviceID;
}

AudioDeviceID findDeviceByName(char *name) {
    AudioObjectPropertyAddress  propertyAddress;
    AudioObjectID               *deviceIDs;
    UInt32                      propertySize;
    UInt32                      numDevices;
    
    propertyAddress.mSelector = kAudioHardwarePropertyDevices;
    propertyAddress.mScope = kAudioObjectPropertyScopeWildcard;
    propertyAddress.mElement = kAudioObjectPropertyElementWildcard;
    
    // enumerate all current/valid devices
    if (AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &propertySize) == noErr) {
        numDevices = propertySize / sizeof(AudioDeviceID);
        deviceIDs = (AudioDeviceID *)calloc(numDevices, sizeof(AudioDeviceID));
        
        if (AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &propertySize, deviceIDs) == noErr) {
            AudioObjectPropertyAddress      deviceAddress;
            char                            deviceName[64];
            //char                            manufacturerName[64];
            
            for (UInt32 idx=0; idx<numDevices; idx++) {
                propertySize = sizeof(deviceName);
                deviceAddress.mSelector = kAudioDevicePropertyDeviceName;
                deviceAddress.mScope = kAudioObjectPropertyScopeGlobal;
                deviceAddress.mElement = kAudioObjectPropertyElementMaster;
                
                // Get deviceName, manufacturerName and uidString.
                if (AudioObjectGetPropertyData(deviceIDs[idx], &deviceAddress, 0, NULL, &propertySize, deviceName) == noErr) {
                    
                    if (strncmp(name, deviceName, 64) == 0) {
                        printf("Found: %d %s\n", deviceIDs[idx], deviceName);
                        
                        // TODO: better error handling
                        //free(deviceIDs);
                        return deviceIDs[idx];
                    }
                }
            }
        }
        free(deviceIDs);
    }
    // TODO
    return -1;
}
