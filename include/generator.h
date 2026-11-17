/*
 * Project: SIGNAL LAB
 * File: generator.h
 * Description: Mathematical waveform generator prototypes (Sine, Square, Triangle)
 * Author: Ibrahim
 * Date: November 2026
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include "signal.h"

/**
 * @brief Supported mathematical waveform types.
 */
typedef enum {
    WAVE_SINE,      /**< Pure sinusoidal wave: A * sin(2 * pi * f * t + phi) */
    WAVE_SQUARE,    /**< Periodic square wave switching between +A and -A */
    WAVE_TRIANGLE   /**< Piecewise linear triangular wave between -A and +A */
} WaveType;

/**
 * @brief Generates a sinusoidal waveform into an existing Signal structure.
 * 
 * @param sig Pointer to an allocated Signal structure.
 * @param amplitude Peak amplitude of the wave (A).
 * @param frequency Signal frequency in Hertz (f).
 * @param phase Initial phase shift in radians (phi).
 * @return 0 on success, -1 if the signal pointer is NULL or parameters are invalid.
 */
int generate_sine(Signal *sig, double amplitude, double frequency, double phase);

/**
 * @brief Generates a square waveform into an existing Signal structure.
 * 
 * @param sig Pointer to an allocated Signal structure.
 * @param amplitude Peak amplitude of the wave (+A / -A).
 * @param frequency Signal frequency in Hertz (f).
 * @return 0 on success, -1 if the signal pointer is NULL or parameters are invalid.
 */
int generate_square(Signal *sig, double amplitude, double frequency);

/**
 * @brief Generates a triangular waveform into an existing Signal structure.
 * 
 * @param sig Pointer to an allocated Signal structure.
 * @param amplitude Peak amplitude of the wave (+A / -A).
 * @param frequency Signal frequency in Hertz (f).
 * @return 0 on success, -1 if the signal pointer is NULL or parameters are invalid.
 */
int generate_triangle(Signal *sig, double amplitude, double frequency);

#endif /* GENERATOR_H */
