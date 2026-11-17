/*
 * Project: SIGNAL LAB
 * File: main.c
 * Description: Application entry point launching the interactive DSP CLI
 * Author: Ibrahim
 * Date: November 2026
 */

#include "../include/display.h"

/**
 * @brief Main entry point of the SIGNAL LAB digital oscilloscope application.
 * 
 * @return 0 upon clean exit from the interactive CLI loop.
 */
int main(void) {
    /* Launch the interactive command-line signal processing pipeline */
    run_interactive_cli();

    return 0;
}
