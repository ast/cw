//
//  ringbuffer_h
//  afsk
//
//  Created by Albin Stigö on 09/06/2017.
//  Copyright © 2017 Albin Stigo. All rights reserved.
//

// Inspired by:
// https://www.snellman.net/blog/archive/2016-12-13-ring-buffers/

#ifndef ringbuffer_h
#define ringbuffer_h

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "morse_code.h"

typedef enum {
    MORSE_DOT,
    MORSE_DASH,
    MORSE_DOT_SPACE,
    MORSE_DASH_SPACE,
    MORSE_WORD_SPACE,
    MORSE_STOP
} morse_el_t ;

static const int MAX_CAPACITY = 64;

typedef struct {
    morse_el_t buffer[MAX_CAPACITY];
    uint32_t capacity;
    uint32_t read;
    uint32_t write;
} rb_t;

// Mask indicies to max capacity.
static inline uint32_t rb_mask(uint32_t val) {
    return val & (MAX_CAPACITY - 1);
}

static inline bool rb_empty(rb_t* rb) { return rb->read == rb->write; }
static inline void rb_flush(rb_t* rb) { rb->read = rb->write; }
static inline uint32_t rb_size(rb_t* rb) { return rb->write - rb->read; }
static inline bool rb_full(rb_t* rb) { return rb_size(rb) == rb->capacity; }

static inline void rb_push(rb_t *rb, morse_el_t val) {
    assert(!rb_full(rb));
    rb->buffer[rb_mask(rb->write++)] = val;
}

static inline morse_el_t rb_shift(rb_t* rb) {
    assert(!rb_empty(rb));
    return rb->buffer[rb_mask(rb->read++)];
}

void rb_init(rb_t* rb, uint32_t capacity);

#endif /* ringbuffer_h */
