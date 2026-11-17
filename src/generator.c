/*
 * Project: SIGNAL LAB
 * File: generator.c
 * Description: Implementation of mathematical waveform generators (Sine, Square, Triangle)
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/generator.h"
#include <math.h>

/* Ensure PI is defined under strict C11 standard */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Generates a sinusoidal waveform into an existing Signal structure.
 */
int generate_sine(Signal *sig, double amplitude, double frequency, double phase) {
    /* Defensive check: validate pointers and physical parameters */
    if (sig == NULL || sig->samples == NULL || frequency < 0.0) {
        return -1;
    }

    /* Precompute angular frequency omega = 2 * pi * f for speed */
    double omega = 2.0 * M_PI * frequency;

    for (size_t i = 0; i < sig->length; i++) {
        /* Convert discrete sample index to continuous time t = i / fs */
        double t = (double)i / sig->sample_rate;
        sig->samples[i] = amplitude * sin(omega * t + phase);
    }

    return 0;
}

/**
 * @brief Generates a periodic square waveform switching between +A and -A.
 */
int generate_square(Signal *sig, double amplitude, double frequency) {
    if (sig == NULL || sig->samples == NULL || frequency <= 0.0) {
        return -1;
    }

    double omega = 2.0 * M_PI * frequency;

    for (size_t i = 0; i < sig->length; i++) {
        double t = (double)i / sig->sample_rate;
        /* Use the sign of the sine wave to switch cleanly at every half-period */
        if (sin(omega * t) >= 0.0) {
            sig->samples[i] = amplitude;
        } else {
            sig->samples[i] = -amplitude;
        }
    }

    return 0;
}

/**
 * @brief Generates a piecewise linear triangular waveform between -A and +A.
 */
int generate_triangle(Signal *sig, double amplitude, double frequency) {
    if (sig == NULL || sig->samples == NULL || frequency <= 0.0) {
        return -1;
    }

    double omega = 2.0 * M_PI * frequency;

    for (size_t i = 0; i < sig->length; i++) {
        double t = (double)i / sig->sample_rate;
        /* Exact trigonometric formula for a triangle wave: (2*A/pi) * asin(sin(omega * t)) */
        sig->samples[i] = (2.0 * amplitude / M_PI) * asin(sin(omega * t));
    }

    return 0;
}
