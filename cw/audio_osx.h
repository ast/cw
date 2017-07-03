//
//  audio_osx.h
//  dtmf
//
//  Created by Albin Stigö on 26/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef audio_osx_h
#define audio_osx_h

#include <stdio.h>
#include <AudioToolbox/AudioToolbox.h>

OSStatus openAudio();
uint32_t writeAudio(float *samples, uint32_t length);

#endif /* audio_osx_h */
