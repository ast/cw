//
//  ringbuffer.c
//  afsk
//
//  Created by Albin Stigö on 09/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

#include "ringbuffer.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

void rb_init(rb_t* rb, uint32_t capacity) {
    assert(capacity <= MAX_CAPACITY);
    rb->capacity = capacity;
    rb->read = rb->write = 0;
    memset(rb->buffer, 0, sizeof rb->buffer);
}
