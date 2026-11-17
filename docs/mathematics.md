# Mathematical Foundations of SIGNAL LAB

This document details the continuous-to-discrete signal processing equations implemented in **SIGNAL LAB**.

---

## 1. Discrete-Time Waveform Synthesis (`generator.c`)

Given a sampling frequency $f_s$ (in Hz), discrete sample indices $n \in \{0, 1, \dots, N-1\}$ map to continuous timestamps via:

$$t_n = \frac{n}{f_s}$$

Defining angular frequency $\omega = 2\pi f$:

* **Sinusoidal Wave**:
  $$x[n] = A \sin(\omega t_n + \varphi)$$

* **Square Wave**:
  $$x[n] = \begin{cases} +A & \text{if } \sin(\omega t_n) \ge 0 \\ -A & \text{if } \sin(\omega t_n) < 0 \end{cases}$$

* **Triangular Wave**:
  $$x[n] = \frac{2A}{\pi} \arcsin\big(\sin(\omega t_n)\big)$$

---

## 2. Sampling & N-Bit Uniform Quantization (`sampling.c`)

### Nyquist-Shannon Sampling Theorem
To reconstruct a band-limited signal without spectral folding (**aliasing**), the sampling rate $f_s$ must strictly exceed twice the maximum signal frequency component $f_{\max}$:

$$f_s > 2 f_{\max}$$

### Uniform Mid-Tread ADC Quantization
For an $N$-bit Analog-to-Digital Converter operating between voltage rails $[V_{\min}, V_{\max}]$, the total number of discrete levels is $L = 2^N$, yielding a quantization step size (LSB):

$$\Delta = \frac{V_{\max} - V_{\min}}{2^N - 1}$$

Each clamped sample $x_{\text{clamped}}[n] \in [V_{\min}, V_{\max}]$ is mapped to its nearest discrete voltage level:

$$x_q[n] = V_{\min} + \text{round}\left(\frac{x_{\text{clamped}}[n] - V_{\min}}{\Delta}\right) \cdot \Delta$$

---

## 3. Zero-Mean White Noise Perturbation (`noise.c`)

Using a uniform pseudo-random variable $u[n] \sim \mathcal{U}(0, 1)$, zero-mean additive white noise bounded within $[-A_{\text{noise}}, +A_{\text{noise}}]$ is generated and superposed in-place:

$$\eta[n] = A_{\text{noise}} \cdot (2 u[n] - 1), \qquad x_{\text{noisy}}[n] = x[n] + \eta[n]$$

---

## 4. Causal Moving Average Low-Pass FIR Filter (`filter.c`)

To attenuate high-frequency noise while maintaining real-time causality ($y[n]$ depends strictly on current and past inputs), an $M$-point moving average filter is applied. At the left boundary ($n < M - 1$), the effective window length adapts dynamically to prevent unsigned index underflow:

$$M_{\text{eff}}(n) = \min(M, n + 1)$$

$$y[n] = \frac{1}{M_{\text{eff}}(n)} \sum_{k=0}^{M_{\text{eff}}(n) - 1} x[n - k]$$

---

## 5. Discrete Fourier Transform (DFT) Spectral Analysis (`analysis.c`)

The time-domain sequence $x[n]$ of length $N$ is transformed into the frequency domain via Euler's formula in $\mathcal{O}(N^2)$ time complexity for single-sided frequency bins $k \in \{0, 1, \dots, \lfloor N/2 \rfloor - 1\}$:

$$\text{Re}(X[k]) = \sum_{n=0}^{N-1} x[n] \cos\left(\frac{2\pi k n}{N}\right), \qquad \text{Im}(X[k]) = -\sum_{n=0}^{N-1} x[n] \sin\left(\frac{2\pi k n}{N}\right)$$

The physical frequency $f_k$ (in Hz) and single-sided normalized amplitude $|X[k]|_{\text{norm}}$ (in Volts) are given by:

$$f_k = k \cdot \frac{f_s}{N}, \qquad |X[k]|_{\text{norm}} = \begin{cases} \dfrac{\sqrt{\text{Re}(X[k])^2 + \text{Im}(X[k])^2}}{N} & \text{if } k = 0 \\[10pt] \dfrac{2\sqrt{\text{Re}(X[k])^2 + \text{Im}(X[k])^2}}{N} & \text{if } k > 0 \end{cases}$$
