//
//  morse.c
//  cw
//
//  Created by Albin Stigö on 29/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "morse.h"
#include "morse_code.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "ringbuffer.h"

static const char *test = "sm6wjm ";

// TODO: implement lookahead.
void morse_encode_char(morse_t *morse, char c) {
    
    printf("encode: %c\n", c);
    
    if (isspace(c)) {
        rb_push(&morse->el_buffer, MORSE_WORD_SPACE);
        return;
    }
    
    assert(isprint(c));

    // Get code
    const char *code = unicode_morse[c];
    assert(code != NULL);
    int codelen = (int) strlen(code);
    
    for (uint8_t i = 0; i<codelen; i++) {
        switch (code[i]) {
            case '.':
                rb_push(&morse->el_buffer, MORSE_DOT);
                break;
            case '-':
                rb_push(&morse->el_buffer, MORSE_DASH);
                break;
            default:
                break;
        }
        
        if (i < (codelen-1)) {
            rb_push(&morse->el_buffer, MORSE_DOT_SPACE);
        } else {
            rb_push(&morse->el_buffer, MORSE_DASH_SPACE);
        }
            
    }
}

void morse_encode_next(morse_t *morse) {
    static uint8_t i = 0;
    morse_encode_char(morse, test[i++ % 7]);
}


uint32_t m_samples_per_dots(morse_t *morse, float dots) {
    float dot_duration_s = 1.2 / morse->wpm;
    return (uint32_t) ceilf(dots * dot_duration_s * morse->samplerate);
}

void morse_update_state(morse_t *morse) {

    if(rb_empty(&morse->el_buffer)) {
        morse_encode_next(morse);
    }
    
    switch (rb_shift(&morse->el_buffer)) {
        case MORSE_DOT:
            morse->state.rem = m_samples_per_dots(morse, 1);
            morse->state.val = 1.;
            break;
        case MORSE_DASH:
            morse->state.rem = m_samples_per_dots(morse, 3);
            morse->state.val = 1.;
            break;
        case MORSE_DOT_SPACE:
            morse->state.rem = m_samples_per_dots(morse, 1);
            morse->state.val = 0.;
            break;
        case MORSE_DASH_SPACE:
            morse->state.rem = m_samples_per_dots(morse, 3);
            morse->state.val = 0.;
            break;
        case MORSE_WORD_SPACE:
            morse->state.rem = m_samples_per_dots(morse, 7);
            morse->state.val = 0.;
            break;
        case MORSE_STOP:
            exit(EXIT_SUCCESS);
            break;
    }
}

void morse_init(morse_t *morse, float wpm, float samplerate) {
    rb_init(&morse->el_buffer, MAX_CAPACITY);
    morse->wpm = wpm;
    morse->samplerate = samplerate;
}

inline float morse_next(morse_t *morse) {
    if (!morse->state.rem) {
        morse_update_state(morse);
    }
    morse->state.rem--;
    return morse->state.val;
}
