/*
 * Project: SIGNAL LAB
 * File: test_analysis.c
 * Description: Unit tests for O(N^2) DFT spectral peak detection accuracy
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/signal.h"
#include "../include/generator.h"
#include "../include/analysis.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    printf("[TEST] Running DFT spectral analysis unit tests...\n");

    /* Generate pure 10 Hz sine wave of amplitude 3.0 V sampled at 100 Hz for 1 s */
    Signal *sig = create_signal(100, 100.0);
    assert(sig != NULL);
    assert(generate_sine(sig, 3.0, 10.0, 0.0) == 0);

    Spectrum *spec = compute_dft(sig);
    assert(spec != NULL);
    assert(spec->num_bins == 50);

    /* Locate dominant frequency bin */
    size_t peak_idx = 0;
    for (size_t k = 1; k < spec->num_bins; k++) {
        if (spec->magnitudes[k] > spec->magnitudes[peak_idx]) {
            peak_idx = k;
        }
    }

    /* Peak frequency must be exactly 10.0 Hz and amplitude ~3.0 V */
    assert(fabs(spec->frequencies[peak_idx] - 10.0) < 1e-6);
    assert(fabs(spec->magnitudes[peak_idx] - 3.0) < 1e-3);

    free_spectrum(spec);
    free_signal(sig);
    printf("[PASS] All DFT spectral analysis unit tests passed!\n");
    return 0;
}
