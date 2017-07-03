//
//  nco.c
//  cw
//
//  Created by Albin Stigö on 29/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "nco.h"

#include <math.h>

void nco_init(nco_t *nco, float samplerate, float freq) {
    for (uint16_t i = 0; i < NUM_SAMPLES; i++) {
        nco->samples[i] = sinf(2. * M_PI * i / NUM_SAMPLES);
    }
    nco_set(nco, samplerate, freq);
}

void nco_set(nco_t *nco, float samplerate, float freq) {
    nco->step = (uint8_t) (freq * NUM_SAMPLES / samplerate);
}
