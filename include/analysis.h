/*
 * Project: SIGNAL LAB
 * File: analysis.h
 * Description: Discrete Fourier Transform (DFT) spectral analyzer and high-precision benchmarking
 * Author: Ibrahim
 * Date: November 2026
 */

#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "signal.h"

/**
 * @brief Represents the frequency-domain magnitude spectrum of a signal.
 */
typedef struct {
    double *frequencies;   /**< Array of frequency bins in Hertz (Hz) */
    double *magnitudes;    /**< Array of normalized spectral amplitudes |X[k]| */
    size_t num_bins;       /**< Number of single-sided frequency bins (N / 2) */
    double compute_time_us;/**< Execution latency of the DFT in microseconds (Module F2) */
} Spectrum;

/**
 * @brief Computes the single-sided Discrete Fourier Transform (DFT) in O(N^2).
 * 
 * @param sig Constant pointer to the time-domain input Signal.
 * @return Pointer to a newly allocated Spectrum structure, or NULL on failure.
 */
Spectrum *compute_dft(const Signal *sig);

/**
 * @brief Frees all heap memory associated with a Spectrum structure.
 * 
 * @param spec Pointer to the Spectrum structure to deallocate.
 */
void free_spectrum(Spectrum *spec);

/**
 * @brief Exports frequency and magnitude spectrum data to a CSV file.
 * 
 * @param spec Constant pointer to the Spectrum to export.
 * @param filepath Destination path for the output CSV file (e.g., data/spectrum.csv).
 * @return 0 on success, -1 on failure.
 */
int export_spectrum_csv(const Spectrum *spec, const char *filepath);

#endif /* ANALYSIS_H */
