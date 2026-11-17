"""
Project: SIGNAL LAB
File: visualize.py
Description: Digital oscilloscope visualization layer for exported C signal data
Author: Ibrahim
Date: November 2026
"""

import csv
import os
import sys
import matplotlib.pyplot as plt


def load_signal_csv(filepath):
    """
    Reads time and amplitude columns from a SIGNAL LAB CSV file.

    Args:
        filepath (str): Path to the input CSV file.

    Returns:
        tuple: Two lists of floats (times, amplitudes).
    """
    if not os.path.exists(filepath):
        print(f"Error: File '{filepath}' not found. Run ./bin/signal_lab first.")
        sys.exit(1)

    times = []
    amplitudes = []

    with open(filepath, mode="r", encoding="utf-8") as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            times.append(float(row["time"]))
            amplitudes.append(float(row["amplitude"]))

    return times, amplitudes


def plot_waveform(times, amplitudes, title="SIGNAL LAB - Digital Oscilloscope", output_img=None):
    """
    Plots the discrete-time waveform and optionally saves a high-resolution PNG.

    Args:
        times (list): Time values in seconds.
        amplitudes (list): Signal amplitude values.
        title (str): Plot title.
        output_img (str, optional): Path to save the plot image.
    """
    plt.figure(figsize=(10, 5))
    plt.plot(times, amplitudes, color="#007acc", linewidth=1.8, label="Signal x(t)")
    plt.axhline(0, color="black", linewidth=0.8, linestyle="--")

    plt.title(title, fontsize=14, fontweight="bold")
    plt.xlabel("Time [s]", fontsize=12)
    plt.ylabel("Amplitude [V]", fontsize=12)
    plt.grid(True, which="both", linestyle=":", alpha=0.7)
    plt.legend(loc="upper right")
    plt.tight_layout()

    if output_img:
        plt.savefig(output_img, dpi=300)
        print(f"Saved high-resolution plot to {output_img}")

    plt.show()


if __name__ == "__main__":
    CSV_PATH = "data/signal.csv"
    PREVIEW_PATH = "docs/waveform_preview.png"

    t_data, amp_data = load_signal_csv(CSV_PATH)
    plot_waveform(
        t_data,
        amp_data,
        title="SIGNAL LAB - Generated Waveform (5 Hz Sine Wave)",
        output_img=PREVIEW_PATH,
    )
