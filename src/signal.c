/*
 * Project: SIGNAL LAB
 * File: signal.c
 * Description: Implementation of dynamic memory management for Signal structures
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/signal.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * @brief Allocates memory for a new Signal structure and its sample array.
 */
Signal *create_signal(size_t length, double sample_rate) {
    /* Prevent invalid zero-length or negative sampling rate allocations */
    if (length == 0 || sample_rate <= 0.0) {
        return NULL;
    }

    /* Step 1: Allocate memory for the Signal structure itself */
    Signal *sig = (Signal *)malloc(sizeof(Signal));
    if (sig == NULL) {
        return NULL;
    }

    /* Step 2: Allocate memory for the dynamic array of samples */
    sig->samples = (double *)malloc(length * sizeof(double));
    if (sig->samples == NULL) {
        free(sig); /* Clean up the structure if sample allocation fails */
        return NULL;
    }

    /* Step 3: Initialize metadata fields and zero-fill the sample array */
    sig->length = length;
    sig->sample_rate = sample_rate;
    for (size_t i = 0; i < length; i++) {
        sig->samples[i] = 0.0;
    }

    return sig;
}

/**
 * @brief Frees all heap memory associated with a Signal structure.
 */
void free_signal(Signal *sig) {
    /* Safety check: do nothing if the pointer is already NULL */
    if (sig == NULL) {
        return;
    }

    /* Step 1: Free the inner sample array first */
    free(sig->samples);

    /* Step 2: Free the outer Signal structure */
    free(sig);
}/**
 * @brief Exports signal time and amplitude data to a CSV file.
 */
int export_signal_csv(const Signal *sig, const char *filepath) {
    /* Defensive check: validate pointers */
    if (sig == NULL || sig->samples == NULL || filepath == NULL) {
        return -1;
    }

    /* Open target file in write mode ("w") */
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        return -1;
    }

    /* Write CSV header */
    fprintf(file, "time,amplitude\n");

    /* Write each sample row (time in seconds, amplitude) */
    for (size_t i = 0; i < sig->length; i++) {
        double t = (double)i / sig->sample_rate;
        fprintf(file, "%.6f,%.6f\n", t, sig->samples[i]);
    }

    /* Flush buffer and close file stream */
    fclose(file);
    return 0;
}

