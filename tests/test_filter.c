/*
 * Project: SIGNAL LAB
 * File: test_filter.c
 * Description: Unit tests for causal moving average low-pass FIR filter
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/signal.h"
#include "../include/filter.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    printf("[TEST] Running moving average filter unit tests...\n");

    Signal *sig = create_signal(5, 100.0);
    assert(sig != NULL);

    /* Populate constant DC signal = 4.0 V */
    for (size_t i = 0; i < sig->length; i++) {
        sig->samples[i] = 4.0;
    }

    /* Moving average of a constant 4.0 V signal must remain 4.0 V everywhere (including left boundary) */
    Signal *filtered = moving_average_filter(sig, 3);
    assert(filtered != NULL);
    for (size_t i = 0; i < filtered->length; i++) {
        assert(fabs(filtered->samples[i] - 4.0) < 1e-6);
    }

    /* Defensive check: zero window size must return NULL */
    assert(moving_average_filter(sig, 0) == NULL);

    free_signal(filtered);
    free_signal(sig);
    printf("[PASS] All moving average filter unit tests passed!\n");
    return 0;
}
