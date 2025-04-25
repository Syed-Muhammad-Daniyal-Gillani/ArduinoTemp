# Arduino Robot Motion Controller

This project allows you to control a 4-wheeled robot (using IBT-2 motor drivers) from a Python script via serial communication with an Arduino.

The robot can move in multiple directions with different motion types such as straight, diagonal, horizontal, and rotate.

---

## 📦 Project Contents

- `arduino.ino`: Arduino sketch to receive and process motion commands.
- `main.py`: Python script that automatically connects to the Arduino and sends hardcoded movement commands.
- `README.md`: Project documentation (this file).

---

## 🎮 Supported Commands

The motion commands sent from the Python script follow this format:


### 🧭 Motion Types & Directions

| Motion Type | Direction         | Description                                 |
|-------------|-------------------|---------------------------------------------|
| `straight`  | `forward`         | Move straight forward                       |
|             | `backward`        | Move straight backward                      |
| `horizontal`| `left`            | Strafe left (sideways)                      |
|             | `right`           | Strafe right (sideways)                     |
| `diagonal`  | `forward_left`    | Move diagonally forward to the left         |
|             | `forward_right`   | Move diagonally forward to the right        |
|             | `backward_left`   | Move diagonally backward to the left        |
|             | `backward_right`  | Move diagonally backward to the right       |
| `rotate`    | `left`            | Rotate counter-clockwise (turn left)        |
|             | `right`           | Rotate clockwise (turn right)               |

> **Speed**: Integer from `0` to `255`. Speed is auto-normalized based on motor calibration.
> 
> **Example command**: `straight forward 100`.
