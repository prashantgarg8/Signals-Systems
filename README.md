# Signals-Systems
This C++ project simulates core Signals and Systems operations which allows students to experiment with discrete signals directly from the terminal.
It helps in understanding fundamental signal transformations and the behavior of Linear Time-Invariant (LTI) systems.

This is a menu-driven terminal application designed to feel like a digital signal lab — complete with reversible transformations, convolution, and LTI system verification.
## Features

| Operation            | Description                                               |
| -------------------- | --------------------------------------------------------- |
| **Scaling**          | Multiplies amplitude by a constant factor.                |
| **Addition**         | Combines two discrete-time signals.                       |
| **Reversal**         | Reflects a signal about n = 0.                            |
| **Time Shifting**    | Delays or advances a signal by a given number of samples. |
| **Convolution**      | Computes the discrete-time convolution of two signals.    |
| **LTI System Check** | Tests linearity and time invariance properties.           |
| **Impulse Response** | Displays δ[n] behavior of an LTI system.                  |
| **Step Response**    | Calculates step output for the given system.              |

## Run Instructions
For Windows (MinGW / Code::Blocks)
``g++ main.cpp -o main.exe
``
