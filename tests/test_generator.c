/*
 * Project: SIGNAL LAB
 * File: test_generator.c
 * Description: Unit tests for waveform generators (Sine, Square, Triangle)
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/signal.h"
#include "../include/generator.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPSILON 1e-6

int main(void) {
    printf("[TEST] Running generator unit tests...\n");

    /* Test 1: Defensive check against NULL pointers and negative frequency */
    assert(generate_sine(NULL, 1.0, 5.0, 0.0) == -1);

    Signal *sig = create_signal(100, 100.0);
    assert(sig != NULL);
    assert(generate_sine(sig, 1.0, -5.0, 0.0) == -1);

    /* Test 2: Sine wave at t = 0 with phase = 0 must equal 0.0 */
    assert(generate_sine(sig, 3.0, 5.0, 0.0) == 0);
    assert(fabs(sig->samples[0] - 0.0) < EPSILON);

    /* Test 3: Square wave must strictly output +A or -A */
    assert(generate_square(sig, 4.0, 5.0) == 0);
    for (size_t i = 0; i < sig->length; i++) {
        assert(fabs(fabs(sig->samples[i]) - 4.0) < EPSILON);
    }

    /* Test 4: Triangle wave at t = 0 must equal 0.0 */
    assert(generate_triangle(sig, 2.0, 5.0) == 0);
    assert(fabs(sig->samples[0] - 0.0) < EPSILON);

    free_signal(sig);
    printf("[PASS] All generator unit tests passed!\n");
    return 0;
}
