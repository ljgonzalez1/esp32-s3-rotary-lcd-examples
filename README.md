## esp32-s3-rotary-lcd-examples

### 📚 Table of Contents

* [Overview](#-overview)
* [Examples](#-examples)
* [Getting Started](#-getting-started)
* [File Tree](#-file-tree)
* [Hardware Specs (This Device)](#-hardware-specs-this-device)
* [Licence](#-licence)

### 🧭 Overview

This repository contains simple, beginner-friendly examples for the ESP32‑S3 with a round touchscreen LCD and a rotary encoder. Each example is independent so you can build and upload it on its own. Start with the basics, confirm the hardware works, and then add features step by step.

### 🧪 Examples

* `example-01-red-screen`: minimal project that initializes the board and sets the screen background to solid red. Also prints basic status over the serial monitor.

---

### 🚀 Getting Started

1. Clone this repository.
2. Open the `example-01-red-screen` folder in your preferred development setup.
3. Build and upload to your ESP32‑S3.
4. Open a serial monitor at **115200 baud** to view logs.

---

### 📂 File Tree

```
esp32-s3-rotary-lcd-examples/
├─ example-01-red-screen/
│  ├─ platformio.ini
│  └─ src/main.cpp
└─ LICENSE
```

---

### 🧩 Hardware Specs (This Device)

* **SoC:** ESP32‑S3 (QFN56), **revision v0.2**
* **CPU:** Dual‑core + LP core, **up to 240 MHz**
* **Crystal:** **40 MHz**
* **Connectivity:** **Wi‑Fi** and **Bluetooth 5 (LE)**
* **USB:** **USB‑Serial/JTAG (native)** — typical Linux port: `/dev/ttyACM0`
* **Flash:** **16 MB** SPI flash (JEDEC **0x46:0x4018**), **quad** mode, **3.3 V**
* **PSRAM:** **8 MB embedded** (vendor: **AP\_3v3**)
* **Boot/eFuse notes:** `VDD_SPI=3.3V`, USB features enabled, UART boot message output enabled
* **MAC:** `30:ED:A0:1D:0C:00` (unique identifier)

*(All values measured via `esptool`/`espefuse` on this board.)*

---

### 📄 Licence

[MIT License](LICENSE)

Copyright (c) 2025 [Luis González](https://github.com/ljgonzalez1)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
