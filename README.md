# SIGNAL LAB — C11 Digital Signal Processing Engine & Virtual Oscilloscope

![C11](https://shields.io)
![Platform](https://shields.io)
![Valgrind](https://shields.io)
![License](https://shields.io)

**SIGNAL LAB** is a modular, zero-dependency Digital Signal Processing (DSP) engine and virtual oscilloscope written in strict **ISO C11** on **Debian 13**, paired with a decoupled **Python/Matplotlib** visualization layer.

Designed with embedded systems, FPGA hardware architecture, and low-latency computing principles in mind, it simulates a complete end-to-end signal acquisition and spectral analysis pipeline.

---

## Key Engineering Features

* **Mathematical Waveform Synthesis (`generator.c`)**: Generates continuous-to-discrete Sinusoidal, Square, and Triangular waveforms with phase control.
* **ADC Sampling & Quantization (`sampling.c`)**: Simulates decimation (downsampling) and N-bit uniform quantization (1 to 16 bits) using fast hardware-friendly bitwise shifts (`1U << bits`) and voltage rail clamping.
* **Zero-Mean White Noise Injection (`noise.c`)**: In-place uniform stochastic perturbation with configurable seeds for deterministic unit testing or randomized runs.
* **Causal Low-Pass FIR Filtering (`filter.c`)**: Moving average filter with strict unsigned `size_t` boundary protection against left-edge buffer underflows.
* **\(\mathcal{O}(N^2)\) Discrete Fourier Transform (`analysis.c`)**: Single-sided spectral analyzer computing exact physical frequencies (\(f_k = k \cdot f_s / N\)) and normalized amplitudes.
* **High-Precision Latency Benchmarking**: Instruments DFT execution time in microseconds (μs) via POSIX `CLOCK_MONOTONIC`.
* **100% Memory Safety**: Audited under **Valgrind Memcheck** (`0 bytes lost`, `0 invalid reads/writes`) and verified via automated `<assert.h>` unit tests.

---

## Project Architecture

```text
SIGNAL-LAB/
├── include/           # Public module interfaces & Doxygen headers (.h)
├── src/               # Core C11 DSP implementations & interactive CLI (.c)
├── tests/             # Isolated unit test suites using <assert.h>
├── scripts/           # Python/Matplotlib digital oscilloscope visualizer
├── docs/              # Mathematical derivations & waveform previews
├── data/              # Exported time-domain and spectral CSV datasets
├── .github/workflows/ # Automated CI/CD build & Valgrind pipeline
├── Makefile           # Incremental build, unit test & Valgrind automation
├── LICENSE            # MIT License
└── README.md          # Project documentation
```

---

## Build, Run & Verification (Debian / Ubuntu)

### Prerequisites
* `gcc` (with C11 support), `make`, `valgrind`
* `python3` with `matplotlib` (`sudo apt install python3-matplotlib`)

### Quick Start
```bash
# 1. Compile the optimized C11 binary (-O3 -Wall -Wextra -std=c11)
make all

# 2. Run the automated unit test suite
make test

# 3. Launch the interactive DSP CLI under Valgrind memory profiler
make valgrind

# 4. Visualize exported time-domain waveform in Python
python3 scripts/visualize.py
```

---

## Mathematical Documentation

Full equations, Nyquist-Shannon sampling proofs, quantization step derivations, and DFT normalization formulas are documented in [`docs/mathematics.md`](docs/mathematics.md).

---

## Author

**Ibrahim** — Computer Engineering & Low-Latency Systems Enthusiast.

