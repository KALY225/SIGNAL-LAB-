/*
 * Project: SIGNAL LAB
 * File: filter.h
 * Description: Digital low-pass filtering prototypes (Moving Average FIR filter)
 * Author: Ibrahim
 * Date: November 2026
 */

#ifndef FILTER_H
#define FILTER_H

#include "signal.h"

/**
 * @brief Applies a causal moving average low-pass filter of window size M.
 * 
 * @param input Constant pointer to the noisy input Signal.
 * @param window_size Number of samples averaged per window (M >= 1).
 * @return Pointer to a newly allocated filtered Signal, or NULL on invalid parameters.
 */
Signal *moving_average_filter(const Signal *input, size_t window_size);

#endif /* FILTER_H */
