# Signals-Systems
This C++ project emulates fundamental Signals and Systems operations — enabling students to play around with discrete signals from the terminal.
It assists in learning basic signal transformations and LTI system behavior. 

It is a menu-driven terminal program with the look and feel of a digital signal laboratory — complete with reversible transformations, convolution, and LTI system checking.
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
