/*
 * Project: SIGNAL LAB
 * File: display.c
 * Description: Implementation of interactive terminal oscilloscope and DSP pipeline menu
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/display.h"
#include "../include/signal.h"
#include "../include/generator.h"
#include "../include/sampling.h"
#include "../include/noise.h"
#include "../include/filter.h"
#include "../include/analysis.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Flushes remaining characters from stdin to prevent infinite scanf loops.
 */
static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Discard residual characters */
    }
}

/**
 * @brief Prints the SIGNAL LAB banner and interactive menu options.
 */
void print_cli_menu(void) {
    printf("\n====================================================\n");
    printf("   SIGNAL LAB - C11 Digital Signal Processing CLI   \n");
    printf("====================================================\n");
    printf(" [1] Generate Waveform (Sine / Square / Triangle)\n");
    printf(" [2] Downsample Signal (Decimation)\n");
    printf(" [3] Quantize Signal (N-Bit ADC Simulation)\n");
    printf(" [4] Inject White Noise (Zero-Mean Perturbation)\n");
    printf(" [5] Apply Low-Pass Filter (Moving Average FIR)\n");
    printf(" [6] Run Spectral Analysis (DFT + Latency Benchmark)\n");
    printf(" [7] Export Time Signal to CSV (data/signal.csv)\n");
    printf(" [0] Exit SIGNAL LAB\n");
    printf("----------------------------------------------------\n");
    printf("Select an option: ");
}

/**
 * @brief Launches the main interactive CLI loop managing the full DSP pipeline.
 */
void run_interactive_cli(void) {
    Signal *current_sig = NULL;
    int choice = -1;

    init_noise_seed(0);

    while (choice != 0) {
        print_cli_menu();

        if (scanf("%d", &choice) != 1) {
            printf("[Warning] Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                int wave_choice = 1;
                size_t length = 1000;
                double fs = 1000.0, amp = 2.5, freq = 5.0;

                printf("Waveform type (1=Sine, 2=Square, 3=Triangle): ");
                if (scanf("%d", &wave_choice) != 1) { clear_input_buffer(); break; }
                printf("Number of samples (e.g., 1000): ");
                if (scanf("%zu", &length) != 1) { clear_input_buffer(); break; }
                printf("Sampling rate fs in Hz (e.g., 1000.0): ");
                if (scanf("%lf", &fs) != 1) { clear_input_buffer(); break; }
                printf("Amplitude in V (e.g., 2.5): ");
                if (scanf("%lf", &amp) != 1) { clear_input_buffer(); break; }
                printf("Frequency in Hz (e.g., 5.0): ");
                if (scanf("%lf", &freq) != 1) { clear_input_buffer(); break; }
                clear_input_buffer();

                Signal *new_sig = create_signal(length, fs);
                if (new_sig == NULL) {
                    printf("[Error] Memory allocation failed.\n");
                    break;
                }

                int status = -1;
                if (wave_choice == 1) status = generate_sine(new_sig, amp, freq, 0.0);
                else if (wave_choice == 2) status = generate_square(new_sig, amp, freq);
                else if (wave_choice == 3) status = generate_triangle(new_sig, amp, freq);

                if (status != 0) {
                    printf("[Error] Invalid waveform parameters.\n");
                    free_signal(new_sig);
                } else {
                    free_signal(current_sig);
                    current_sig = new_sig;
                    printf("[OK] Generated %zu samples at %.1f Hz.\n", length, fs);
                }
                break;
            }

            case 2: {
                if (current_sig == NULL) {
                    printf("[Warning] Generate a signal first (Option 1).\n");
                    break;
                }
                double target_fs = 0.0;
                printf("Current fs = %.1f Hz. Enter target fs (Hz): ", current_sig->sample_rate);
                if (scanf("%lf", &target_fs) != 1) { clear_input_buffer(); break; }
                clear_input_buffer();

                Signal *down = downsample_signal(current_sig, target_fs);
                if (down == NULL) {
                    printf("[Error] Downsampling failed (check target fs <= current fs).\n");
                } else {
                    free_signal(current_sig);
                    current_sig = down;
                    printf("[OK] Downsampled to %zu samples at %.1f Hz.\n",
                           current_sig->length, current_sig->sample_rate);
                }
                break;
            }

            case 3: {
                if (current_sig == NULL) {
                    printf("[Warning] Generate a signal first (Option 1).\n");
                    break;
                }
                unsigned int bits = 8;
                double vmin = -5.0, vmax = 5.0;
                printf("ADC bit depth (1 to 16, e.g., 3): ");
                if (scanf("%u", &bits) != 1) { clear_input_buffer(); break; }
                printf("Min voltage rail (e.g., -2.5): ");
                if (scanf("%lf", &vmin) != 1) { clear_input_buffer(); break; }
                printf("Max voltage rail (e.g., 2.5): ");
                if (scanf("%lf", &vmax) != 1) { clear_input_buffer(); break; }
                clear_input_buffer();

                if (quantize_signal(current_sig, (uint8_t)bits, vmin, vmax) == 0) {
                    printf("[OK] Signal quantized to %u bits (%u levels).\n", bits, (1U << bits));
                } else {
                    printf("[Error] Quantization parameters invalid.\n");
                }
                break;
            }

            case 4: {
                if (current_sig == NULL) {
                    printf("[Warning] Generate a signal first (Option 1).\n");
                    break;
                }
                double noise_amp = 0.5;
                printf("Noise peak amplitude in V (e.g., 0.6): ");
                if (scanf("%lf", &noise_amp) != 1) { clear_input_buffer(); break; }
                clear_input_buffer();

                if (add_white_noise(current_sig, noise_amp) == 0) {
                    printf("[OK] Added zero-mean white noise (+/- %.2f V).\n", noise_amp);
                } else {
                    printf("[Error] Invalid noise amplitude.\n");
                }
                break;
            }

            case 5: {
                if (current_sig == NULL) {
                    printf("[Warning] Generate a signal first (Option 1).\n");
                    break;
                }
                size_t win = 15;
                printf("Moving average window size M (e.g., 15): ");
                if (scanf("%zu", &win) != 1) { clear_input_buffer(); break; }
                clear_input_buffer();

                Signal *filt = moving_average_filter(current_sig, win);
                if (filt == NULL) {
                    printf("[Error] Filtering failed.\n");
                } else {
                    free_signal(current_sig);
                    current_sig = filt;
                    printf("[OK] Applied moving average filter (M = %zu).\n", win);
                }
                break;
            }

            case 6: {
                if (current_sig == NULL) {
                    printf("[Warning] Generate a signal first (Option 1).\n");
                    break;
                }
                Spectrum *spec = compute_dft(current_sig);
                if (spec == NULL) {
                    printf("[Error] DFT computation failed.\n");
                } else {
                    printf("[Benchmark F2] DFT computed in %.2f us for N=%zu samples.\n",
                           spec->compute_time_us, current_sig->length);
                    if (export_spectrum_csv(spec, "data/spectrum.csv") == 0) {
                        printf("[OK] Spectrum exported to data/spectrum.csv\n");
                    }
                    free_spectrum(spec);
                }
                break;
            }

            case 7: {
                if (current_sig == NULL) {
                    printf("[Warning] Generate a signal first (Option 1).\n");
                    break;
                }
                if (export_signal_csv(current_sig, "data/signal.csv") == 0) {
                    printf("[OK] Signal exported to data/signal.csv\n");
                } else {
                    printf("[Error] Failed to write CSV.\n");
                }
                break;
            }

            case 0:
                printf("Exiting SIGNAL LAB. Freeing memory...\n");
                break;

            default:
                printf("[Warning] Unknown option '%d'.\n", choice);
                break;
        }
    }

    free_signal(current_sig);
}
