/*
 * Project: SIGNAL LAB
 * File: main.c
 * Description: Entry point and initial waveform generation test
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/signal.h"
#include "../include/generator.h"
#include <stdio.h>

int main(void) {
    /* Create a 1-second signal sampled at 1000 Hz (1000 samples) */
    Signal *sig = create_signal(1000, 1000.0);
    if (sig == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    /* Generate a 5 Hz sine wave with amplitude 2.5 and 0 phase */
    if (generate_sine(sig, 2.5, 5.0, 0.0) != 0) {
        fprintf(stderr, "Error: Sine wave generation failed.\n");
        free_signal(sig);
        return 1;
    }

    /* Export generated samples to CSV */
    if (export_signal_csv(sig, "data/signal.csv") != 0) {
        fprintf(stderr, "Error: CSV export failed.\n");
        free_signal(sig);
        return 1;
    }

    printf("Success: Generated and exported 5 Hz sine wave to data/signal.csv\n");

    /* Clean up allocated memory */
    free_signal(sig);
    return 0;
}
