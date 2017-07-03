//
//  erl_port.h
//  dtmf
//
//  Created by Albin Stigö on 27/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#ifndef erl_port_h
#define erl_port_h

#include <stdio.h>

typedef union {
    uint16_t nlen;
    uint8_t  bytes[2];
} erl_packet_len_t;

uint16_t    read_exact(uint8_t *bytes, uint16_t length);
uint16_t    write_exact(uint8_t *bytes, uint16_t length);
void        erl_write_packet(uint8_t *bytes, uint16_t length);
uint16_t    erl_read_packet(uint8_t *bytes, uint32_t max_length, float timeout);

#endif /* erl_port_h */
