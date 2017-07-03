//
//  audiodevice.h
//  fcdfm
//
//  Created by Albin Stigö on 02/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef audiodevice_h
#define audiodevice_h

#include <stdio.h>

#include <AudioToolbox/AudioToolbox.h>

void checkError(OSStatus status);

AudioDeviceID defaultOutputDevice();
AudioDeviceID defaultInputDevice();
AudioDeviceID findDeviceByName(char *name);

#endif /* audiodevice_h */
