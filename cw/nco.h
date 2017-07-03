//
//  nco.h
//  cw
//
//  Created by Albin Stigö on 29/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef nco_h
#define nco_h

#include <stdio.h>
#include <assert.h>

static const int NUM_SAMPLES = 1024;

typedef struct {
    float       samples[NUM_SAMPLES];
    uint32_t    i;
    uint8_t     step;
} nco_t;

void nco_init(nco_t *nco, float samplerate, float freq);
void nco_set(nco_t *nco, float samplerate, float freq);

// Mask indicies to max capacity.
static inline uint16_t nco_mask(uint32_t val) {
    return val & (NUM_SAMPLES - 1);
}

static inline float nco_next(nco_t* nco) {
    return nco->samples[nco_mask(nco->i += nco->step)];
}

#endif /* nco_h */
