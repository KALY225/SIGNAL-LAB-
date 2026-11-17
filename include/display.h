/*
 * Project: SIGNAL LAB
 * File: display.h
 * Description: Interactive Command-Line Interface (CLI) dashboard prototypes
 * Author: Ibrahim
 * Date: November 2026
 */

#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @brief Prints the ASCII banner and interactive menu options to stdout.
 */
void print_cli_menu(void);

/**
 * @brief Launches the main interactive CLI loop managing the full DSP pipeline.
 */
void run_interactive_cli(void);

#endif /* DISPLAY_H */
