/*
 * Project: SIGNAL LAB
 * File: sampling.c
 * Description: Implementation of downsampling (decimation) and uniform N-bit ADC quantization
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/sampling.h"
#include <math.h>

/**
 * @brief Downsamples an input signal to a lower target sampling frequency (fs).
 */
Signal *downsample_signal(const Signal *input, double target_sample_rate) {
    /* Validate input pointer and ensure target rate is strictly positive and <= source rate */
    if (input == NULL || input->samples == NULL ||
        target_sample_rate <= 0.0 || target_sample_rate > input->sample_rate) {
        return NULL;
    }

    /* Compute decimation factor (take 1 sample every 'step' samples) */
    size_t step = (size_t)round(input->sample_rate / target_sample_rate);
    if (step == 0) {
        step = 1;
    }

    /* Compute resulting number of samples */
    size_t new_length = input->length / step;
    if (new_length == 0) {
        return NULL;
    }

    /* Allocate new downsampled Signal structure */
    Signal *output = create_signal(new_length, input->sample_rate / (double)step);
    if (output == NULL) {
        return NULL;
    }

    /* Copy decimated samples */
    for (size_t i = 0; i < new_length; i++) {
        output->samples[i] = input->samples[i * step];
    }

    return output;
}

/**
 * @brief Quantizes signal amplitudes into 2^bits discrete levels (uniform ADC).
 */
int quantize_signal(Signal *sig, uint8_t bits, double v_min, double v_max) {
    /* Defensive check: ADC bit depth must be between 1 and 16 bits, and v_max > v_min */
    if (sig == NULL || sig->samples == NULL || bits == 0 || bits > 16 || v_max <= v_min) {
        return -1;
    }

    /* Compute 2^bits discrete levels using fast bitwise shift */
    uint32_t levels = (1U << bits);
    double step_size = (v_max - v_min) / (double)(levels - 1);

    for (size_t i = 0; i < sig->length; i++) {
        double val = sig->samples[i];

        /* Step 1: Clamp input voltage within [v_min, v_max] */
        if (val < v_min) {
            val = v_min;
        } else if (val > v_max) {
            val = v_max;
        }

        /* Step 2: Map voltage to nearest discrete quantization level index */
        double level_index = round((val - v_min) / step_size);

        /* Step 3: Reconstruct quantized voltage */
        sig->samples[i] = v_min + level_index * step_size;
    }

    return 0;
}
