/*
 * Project: SIGNAL LAB
 * File: main.c
 * Description: Complete signal processing pipeline test (Generate -> Noise -> Filter -> DFT -> Export)
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/signal.h"
#include "../include/generator.h"
#include "../include/sampling.h"
#include "../include/noise.h"
#include "../include/filter.h"
#include "../include/analysis.h"
#include <stdio.h>

int main(void) {
    /* Step 1: Create a 1-second signal sampled at 1000 Hz (1000 samples) */
    Signal *sig = create_signal(1000, 1000.0);
    if (sig == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    /* Step 2: Generate a clean 5 Hz sine wave with amplitude 2.5 V */
    if (generate_sine(sig, 2.5, 5.0, 0.0) != 0) {
        fprintf(stderr, "Error: Sine wave generation failed.\n");
        free_signal(sig);
        return 1;
    }

    /* Step 3: Inject zero-mean white noise (+/- 0.6 V) */
    init_noise_seed(0);
    if (add_white_noise(sig, 0.6) != 0) {
        fprintf(stderr, "Error: White noise injection failed.\n");
        free_signal(sig);
        return 1;
    }

    /* Step 4: Apply causal moving average low-pass filter (window = 15 samples) */
    Signal *filtered = moving_average_filter(sig, 15);
    if (filtered == NULL) {
        fprintf(stderr, "Error: Moving average filtering failed.\n");
        free_signal(sig);
        return 1;
    }

    /* Step 5: Export the cleaned (filtered) time-domain signal to CSV */
    if (export_signal_csv(filtered, "data/signal.csv") != 0) {
        fprintf(stderr, "Error: Time-domain CSV export failed.\n");
        free_signal(filtered);
        free_signal(sig);
        return 1;
    }

    /* Step 6: Compute single-sided DFT spectrum and measure latency (Requirement F2) */
    Spectrum *spec = compute_dft(filtered);
    if (spec == NULL) {
        fprintf(stderr, "Error: DFT computation failed.\n");
        free_signal(filtered);
        free_signal(sig);
        return 1;
    }

    printf("[Benchmark F2] DFT computed in %.2f us for N=%zu samples\n",
           spec->compute_time_us, filtered->length);

    /* Step 7: Export the frequency-domain magnitude spectrum to CSV */
    if (export_spectrum_csv(spec, "data/spectrum.csv") != 0) {
        fprintf(stderr, "Error: Spectrum CSV export failed.\n");
        free_spectrum(spec);
        free_signal(filtered);
        free_signal(sig);
        return 1;
    }

    printf("Success: Time signal and frequency spectrum exported to data/\n");

    /* Step 8: Free all allocated heap structures to guarantee zero memory leaks */
    free_spectrum(spec);
    free_signal(filtered);
    free_signal(sig);
    return 0;
}
