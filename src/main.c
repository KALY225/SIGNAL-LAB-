/*
 * Project: SIGNAL LAB
 * File: main.c
 * Description: Complete signal processing pipeline test (Generate -> Noise -> Filter -> Export)
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/signal.h"
#include "../include/generator.h"
#include "../include/sampling.h"
#include "../include/noise.h"
#include "../include/filter.h"
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

    /* Step 5: Export the cleaned (filtered) signal to CSV */
    if (export_signal_csv(filtered, "data/signal.csv") != 0) {
        fprintf(stderr, "Error: CSV export failed.\n");
        free_signal(filtered);
        free_signal(sig);
        return 1;
    }

    printf("Success: Generated, noisy, and filtered 5 Hz signal exported to data/signal.csv\n");

    /* Step 6: Free BOTH allocated signals to guarantee zero memory leaks */
    free_signal(filtered);
    free_signal(sig);
    return 0;
}
