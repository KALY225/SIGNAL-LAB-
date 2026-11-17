/*
 * Project: SIGNAL LAB
 * File: filter.c
 * Description: Implementation of causal moving average low-pass FIR filter
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/filter.h"

/**
 * @brief Applies a causal moving average low-pass filter of window size M.
 */
Signal *moving_average_filter(const Signal *input, size_t window_size) {
    /* Defensive check: validate input pointer and ensure window_size >= 1 */
    if (input == NULL || input->samples == NULL || window_size == 0) {
        return NULL;
    }

    /* Allocate a new Signal structure for the filtered output (out-of-place) */
    Signal *output = create_signal(input->length, input->sample_rate);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < input->length; i++) {
        double sum = 0.0;
        size_t count = 0;

        /* Accumulate up to window_size past samples without underflowing index i */
        for (size_t k = 0; k < window_size && k <= i; k++) {
            sum += input->samples[i - k];
            count++;
        }

        /* Compute arithmetic mean over available window samples */
        output->samples[i] = sum / (double)count;
    }

    return output;
}
