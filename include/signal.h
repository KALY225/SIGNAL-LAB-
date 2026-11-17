/*
 * Project: SIGNAL LAB
 * File: signal.h
 * Description: Core data structure and lifecycle prototypes for discrete signals
 * Author: Ibrahim
 * Date: November 2026
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#include <stddef.h>

/**
 * @brief Represents a discrete-time digital signal in memory.
 */
typedef struct {
    double *samples;     /**< Pointer to dynamic array of signal amplitudes */
    size_t length;       /**< Total number of samples (N) */
    double sample_rate;  /**< Sampling frequency in Hertz (fs) */
} Signal;

/**
 * @brief Allocates memory for a new Signal structure and its sample array.
 * 
 * @param length Number of samples to allocate.
 * @param sample_rate Sampling frequency in Hz.
 * @return Pointer to the allocated Signal, or NULL if allocation fails.
 */
Signal *create_signal(size_t length, double sample_rate);

/**
 * @brief Frees all heap memory associated with a Signal structure.
 * 
 * @param sig Pointer to the Signal structure to deallocate.
 */
void free_signal(Signal *sig);

/**
 * @brief Exports signal time and amplitude data to a CSV file.
 * 
 * @param sig Constant pointer to the Signal to export.
 * @param filepath Destination path for the output CSV file.
 * @return 0 on success, -1 if file creation or writing fails.
 */
int export_signal_csv(const Signal *sig, const char *filepath);

#endif /* SIGNAL_H */
