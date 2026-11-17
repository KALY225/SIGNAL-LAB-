/*
 * Project: SIGNAL LAB
 * File: noise.h
 * Description: White noise generator and signal perturbation prototypes
 * Author: Ibrahim
 * Date: November 2026
 */

#ifndef NOISE_H
#define NOISE_H

#include "signal.h"

/**
 * @brief Initializes the pseudo-random number generator seed.
 * 
 * @param seed Seed value (pass 0 to automatically seed with current system time).
 */
void init_noise_seed(unsigned int seed);

/**
 * @brief Adds uniform zero-mean white noise to an existing Signal in-place.
 * 
 * @param sig Pointer to the Signal structure to perturb.
 * @param noise_amplitude Peak amplitude of the noise in Volts ([-A, +A]).
 * @return 0 on success, -1 if the signal pointer is NULL or amplitude is negative.
 */
int add_white_noise(Signal *sig, double noise_amplitude);

#endif /* NOISE_H */
