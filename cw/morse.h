//
//  morse.h
//  cw
//
//  Created by Albin Stigö on 29/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef morse_h
#define morse_h

#include <stdio.h>
#include "ringbuffer.h"

typedef char (*morse_callback_t)();

typedef struct {
    float       val;
    uint32_t    rem;
} morse_state_t;

typedef struct {
    float wpm;
    //float pitch;
    float samplerate;
    float t;
    rb_t el_buffer;
    morse_state_t state;
    morse_callback_t char_source;
} morse_t;

void morse_init(morse_t *morse, float wpm, float samplerate);
float morse_next(morse_t *morse);

#endif /* morse_h */
