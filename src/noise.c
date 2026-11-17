/*
 * Project: SIGNAL LAB
 * File: noise.c
 * Description: Implementation of zero-mean uniform white noise generator
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/noise.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief Initializes the pseudo-random number generator seed.
 */
void init_noise_seed(unsigned int seed) {
    if (seed == 0) {
        srand((unsigned int)time(NULL));
    } else {
        srand(seed);
    }
}

/**
 * @brief Adds uniform zero-mean white noise to an existing Signal in-place.
 */
int add_white_noise(Signal *sig, double noise_amplitude) {
    /* Defensive check: validate pointer and non-negative noise amplitude */
    if (sig == NULL || sig->samples == NULL || noise_amplitude < 0.0) {
        return -1;
    }

    for (size_t i = 0; i < sig->length; i++) {
        /* Generate uniform random double in [0.0, 1.0] */
        double unit_rand = (double)rand() / (double)RAND_MAX;

        /* Map to zero-mean interval [-noise_amplitude, +noise_amplitude] */
        double noise = noise_amplitude * (2.0 * unit_rand - 1.0);

        /* Superpose noise onto the clean signal in-place */
        sig->samples[i] += noise;
    }

    return 0;
}
