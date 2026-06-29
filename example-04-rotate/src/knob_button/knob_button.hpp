#pragma once

#include "hal/gpio_types.h"

// Inicializa el botón (pulsación del encoder) y loggea eventos por serial.
void knob_button_start(gpio_num_t pin);
