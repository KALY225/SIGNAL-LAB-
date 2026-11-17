/*
 * Project: SIGNAL LAB
 * File: test_sampling.c
 * Description: Unit tests for downsampling and N-bit ADC quantization
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/signal.h"
#include "../include/generator.h"
#include "../include/sampling.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    printf("[TEST] Running sampling & quantization unit tests...\n");

    Signal *sig = create_signal(1000, 1000.0);
    assert(sig != NULL);
    assert(generate_sine(sig, 5.0, 10.0, 0.0) == 0);

    /* Test 1: Downsampling from 1000 Hz to 250 Hz must yield 250 samples */
    Signal *down = downsample_signal(sig, 250.0);
    assert(down != NULL);
    assert(down->length == 250);
    assert(fabs(down->sample_rate - 250.0) < 1e-6);

    /* Test 2: Quantization clamping within [-2.0, +2.0] on 3 bits */
    assert(quantize_signal(sig, 3, -2.0, 2.0) == 0);
    for (size_t i = 0; i < sig->length; i++) {
        assert(sig->samples[i] >= -2.0 && sig->samples[i] <= 2.0);
    }

    /* Test 3: Invalid bit depth rejection (0 bits or > 16 bits) */
    assert(quantize_signal(sig, 0, -2.0, 2.0) == -1);
    assert(quantize_signal(sig, 20, -2.0, 2.0) == -1);

    free_signal(down);
    free_signal(sig);
    printf("[PASS] All sampling & quantization unit tests passed!\n");
    return 0;
}
