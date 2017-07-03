//
//  filter_lowpass.h
//  cw
//
//  Created by Albin Stigö on 30/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef filter_lowpass_h
#define filter_lowpass_h

#include <stdio.h>
#include <math.h>

typedef struct {
    float a0, b1, z1;
} filter_t;

void filter_init(filter_t *f, float samplerate, float t) {
    float x = expf(-1./(samplerate * t));
    f->a0 = 1 - x;
    f->b1 = x;
    f->z1 = 0;
}

static inline float filter_filter(filter_t *f, float x) {
    float y = f->a0 * x + f->b1 * f->z1;
    f->z1 = y;
    return y;
}

#endif /* filter_lowpass_h */
