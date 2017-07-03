//
//  main.c
//  cw
//
//  Created by Albin Stigö on 29/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include <stdio.h>

#include "audio_osx.h"

#include "morse.h"
#include "nco.h"
#include "filter_lowpass.h"

const char* sendme = "send me de sm6wjm/r";

int main(int argc, const char * argv[]) {
    
    nco_t nco;
    nco_init(&nco, 44100, 800);
    
    morse_t morse;
    morse_init(&morse, 20, 44100.);
    
    filter_t f;
    filter_init(&f, 44100, 0.005);
    
    openAudio();
    
    float samples[1024] = {0.};
    
    do {
        for(int i=0; i<1024;i++) {
            samples[i] = nco_next(&nco) * filter_filter(&f, morse_next(&morse));
        }
    } while(writeAudio(samples, 1024));
    
    
    getchar();
    
    return 0;
}
