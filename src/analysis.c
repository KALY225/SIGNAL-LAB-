/*
 * Project: SIGNAL LAB
 * File: analysis.c
 * Description: Implementation of O(N^2) Discrete Fourier Transform (DFT) and latency benchmarking
 * Author: Ibrahim
 * Date: November 2026
 */

#define _POSIX_C_SOURCE 199309L

#include "../include/analysis.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Computes the single-sided Discrete Fourier Transform (DFT) in O(N^2).
 */
Spectrum *compute_dft(const Signal *sig) {
    /* Defensive check: need at least 2 samples to form a spectrum */
    if (sig == NULL || sig->samples == NULL || sig->length < 2) {
        return NULL;
    }

    size_t N = sig->length;
    size_t num_bins = N / 2;

    /* Step 1: Allocate Spectrum structure and its two dynamic arrays */
    Spectrum *spec = (Spectrum *)malloc(sizeof(Spectrum));
    if (spec == NULL) {
        return NULL;
    }

    spec->frequencies = (double *)malloc(num_bins * sizeof(double));
    spec->magnitudes = (double *)malloc(num_bins * sizeof(double));
    if (spec->frequencies == NULL || spec->magnitudes == NULL) {
        free(spec->frequencies);
        free(spec->magnitudes);
        free(spec);
        return NULL;
    }

    spec->num_bins = num_bins;

    /* Step 2: Start high-precision monotonic timer (Requirement F2) */
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    /* Step 3: Compute DFT via Euler's formula in O(N^2) */
    double two_pi_over_N = (2.0 * M_PI) / (double)N;
    double freq_resolution = sig->sample_rate / (double)N;

    for (size_t k = 0; k < num_bins; k++) {
        double real_part = 0.0;
        double imag_part = 0.0;

        for (size_t n = 0; n < N; n++) {
            double angle = two_pi_over_N * (double)k * (double)n;
            real_part += sig->samples[n] * cos(angle);
            imag_part -= sig->samples[n] * sin(angle);
        }

        /* Compute raw magnitude |X[k]| = sqrt(Re^2 + Im^2) */
        double raw_mag = sqrt(real_part * real_part + imag_part * imag_part);

        /* Normalize amplitude to match physical Volts (DC vs AC bins) */
        if (k == 0) {
            spec->magnitudes[k] = raw_mag / (double)N;
        } else {
            spec->magnitudes[k] = (2.0 * raw_mag) / (double)N;
        }

        /* Map bin index k to physical frequency in Hz */
        spec->frequencies[k] = (double)k * freq_resolution;
    }

    /* Step 4: Stop timer and compute elapsed latency in microseconds */
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_sec = (double)(end.tv_sec - start.tv_sec);
    double elapsed_nsec = (double)(end.tv_nsec - start.tv_nsec);
    spec->compute_time_us = (elapsed_sec * 1e6) + (elapsed_nsec / 1e3);

    return spec;
}

/**
 * @brief Frees all heap memory associated with a Spectrum structure.
 */
void free_spectrum(Spectrum *spec) {
    if (spec == NULL) {
        return;
    }
    free(spec->frequencies);
    free(spec->magnitudes);
    free(spec);
}

/**
 * @brief Exports frequency and magnitude spectrum data to a CSV file.
 */
int export_spectrum_csv(const Spectrum *spec, const char *filepath) {
    if (spec == NULL || spec->frequencies == NULL || spec->magnitudes == NULL || filepath == NULL) {
        return -1;
    }

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        return -1;
    }

    fprintf(file, "frequency,magnitude\n");

    for (size_t k = 0; k < spec->num_bins; k++) {
        fprintf(file, "%.6f,%.6f\n", spec->frequencies[k], spec->magnitudes[k]);
    }

    fclose(file);
    return 0;
}
