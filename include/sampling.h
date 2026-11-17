/*
 * Project: SIGNAL LAB
 * File: sampling.h
 * Description: Analog-to-Digital Conversion (ADC) simulation: downsampling and N-bit quantization
 * Author: Ibrahim
 * Date: November 2026
 */

#ifndef SAMPLING_H
#define SAMPLING_H

#include "signal.h"
#include <stdint.h>

/**
 * @brief Downsamples an input signal to a lower target sampling frequency (fs).
 * 
 * @param input Constant pointer to the high-resolution source Signal.
 * @param target_sample_rate Desired new sampling frequency in Hz (must be <= input->sample_rate).
 * @return Pointer to a newly allocated downsampled Signal, or NULL on invalid parameters.
 */
Signal *downsample_signal(const Signal *input, double target_sample_rate);

/**
 * @brief Quantizes signal amplitudes into 2^bits discrete levels (uniform mid-tread ADC).
 * 
 * @param sig Pointer to the Signal structure to quantize in-place.
 * @param bits ADC bit depth resolution (e.g., 3, 8, 12, 16 bits; valid range: 1 to 16).
 * @param v_min Minimum voltage rail of the ADC (e.g., -5.0 V).
 * @param v_max Maximum voltage rail of the ADC (e.g., +5.0 V).
 * @return 0 on success, -1 if parameters are invalid.
 */
int quantize_signal(Signal *sig, uint8_t bits, double v_min, double v_max);

#endif /* SAMPLING_H */
