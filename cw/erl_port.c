//
//  erl_port.c
//  dtmf
//
//  Created by Albin Stigö on 27/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "erl_port.h"

#include <unistd.h>
#include <arpa/inet.h>

static const uint8_t PACKET = 2;

uint16_t read_exact(uint8_t *bytes, uint16_t length) {
    uint16_t i, got = 0;
    
    do {
        if ((i = read(0, bytes+got, length-got)) <= 0) return i;
        got += i;
    } while (got<length);
    
    return length;
}

uint16_t write_exact(uint8_t *bytes, uint16_t length) {
    uint16_t i, wrote = 0;
    do {
        if ((i = write(1, bytes+wrote, length-wrote)) <= 0) return i;
        wrote += i;
    } while(wrote<length);
    
    return length;
}

void erl_write_packet(uint8_t *bytes, uint16_t length) {
    // Erlang needs this byte order
    erl_packet_len_t len;
    len.nlen = htons(length);
    write_exact(len.bytes, PACKET);
    write_exact(bytes, length);
}

uint16_t erl_read_packet(uint8_t *bytes, uint32_t max_length, float timeout) {

    uint16_t len;
    
    if (read_exact((uint8_t*) &len, PACKET) != PACKET) {
        fprintf(stderr, "error reading packet length.\n");
        return -1;
    }
    // Change byte order. Erlang needs this byte order.
    len = ntohs(len);
    
    if (len > max_length) {
        return -1;
    }
    
    return read_exact(bytes, len);
}
