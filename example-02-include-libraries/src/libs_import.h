#pragma once
#include <Arduino.h>

/* Helper macros to stringify */
#ifndef V_STR
#define V_XSTR(x) #x
#define V_STR(x)  V_XSTR(x)
#endif

/* ========= ESP32_IO_Expander =========
   - Nombre “nuevo” (>= v1.x):  esp_io_expander.hpp
   - Nombre “antiguo” (algunas libs lo piden): ESP_IOExpander.h
   Nota: cuando Display Panel antiguo pide "ESP_IOExpander.h" pero instalas la v1.x,
         falla el include. Aquí soportamos ambos para evitar el choque.
*/
#if __has_include(<esp_io_expander.hpp>)
#include <esp_io_expander.hpp>
  #define V_HAVE_IOEXP 1
  #define V_IOEXP_HDR  "esp_io_expander.hpp"
#elif __has_include(<ESP_IOExpander.h>)
#include <ESP_IOExpander.h>
  #define V_HAVE_IOEXP 1
  #define V_IOEXP_HDR  "ESP_IOExpander.h"
#else
#define V_HAVE_IOEXP 0
#endif

/* ========= esp-lib-utils (dependencia de IO_Expander) =========
   Si la tienes vendorizada, no hace falta usarla explícitamente,
   pero dejamos la detección por si quieres validar presencia.
*/
#if __has_include(<esp_utils.hpp>)
#include <esp_utils.hpp>
  #define V_HAVE_UTILS 1
  #define V_UTILS_HDR "esp_utils.hpp"
#else
#define V_HAVE_UTILS 0
#endif

/* ========= Configuración por macros (editables vía build_flags) =========
   - Habilita uso real del expansor:       -DIOEXP_ENABLE=1
   - Selecciona chip (uno):                -DIOEXP_CHIP_TCA95XX_8BIT   (por defecto)
                                           -DIOEXP_CHIP_TCA95XX_16BIT
                                           -DIOEXP_CHIP_HT8574
                                           -DIOEXP_CHIP_CH422G
   - Pines I2C (SCL/SDA):                  -DIOEXP_I2C_SCL=19 -DIOEXP_I2C_SDA=20  (ejemplo)
   - Dirección I2C (TCA9554):              -DIOEXP_TCA9554_ADDR=ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000
*/
#ifndef IOEXP_ENABLE
#define IOEXP_ENABLE 0
#endif

#ifndef IOEXP_I2C_SCL
#define IOEXP_I2C_SCL 19  // cámbialo si tu placa usa otros pines para I2C
#endif
#ifndef IOEXP_I2C_SDA
#define IOEXP_I2C_SDA 20
#endif

/* Predeterminar chip a TCA95XX de 8 bits */
#if !defined(IOEXP_CHIP_TCA95XX_8BIT) && !defined(IOEXP_CHIP_TCA95XX_16BIT) && !defined(IOEXP_CHIP_HT8574) && !defined(IOEXP_CHIP_CH422G)
#define IOEXP_CHIP_TCA95XX_8BIT 1
#endif

/* Dirección por defecto para TCA9554 cuando usamos 8 bits */
#ifndef IOEXP_TCA9554_ADDR
#ifdef ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000
#define IOEXP_TCA9554_ADDR ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000
#else
#define IOEXP_TCA9554_ADDR 0x20  // fallback si no está la macro del header
#endif
#endif

/* ========= Factoría opcional del expansor =========
   Solo se compila si:
     - V_HAVE_IOEXP = 1 (se encontró la librería)
     - IOEXP_ENABLE = 1 (tú lo habilitas por build_flags)
*/
#if V_HAVE_IOEXP && IOEXP_ENABLE
#include <Wire.h>

  namespace ioexpander_factory {
    inline esp_expander::Base* create() {
      /* Selección de clase segun el chip indicado */
      #if defined(IOEXP_CHIP_TCA95XX_8BIT)
        using Expander = esp_expander::TCA95XX_8BIT;
        const uint8_t addr = IOEXP_TCA9554_ADDR;
      #elif defined(IOEXP_CHIP_TCA95XX_16BIT)
        using Expander = esp_expander::TCA95XX_16BIT;
        const uint8_t addr = 0x20; // ajusta según tu cableado (TCA9555 etc.)
      #elif defined(IOEXP_CHIP_HT8574)
        using Expander = esp_expander::HT8574;
        const uint8_t addr = 0x20; // típico 0x20..0x27
      #elif defined(IOEXP_CHIP_CH422G)
        using Expander = esp_expander::CH422G;
        const uint8_t addr = 0x00; // CH422G no es I2C puro, el ctor puede variar
      #else
        #error "Define one IOEXP_CHIP_* macro"
      #endif

      /* Iniciar bus I2C (si ya lo inicias en otro lado, no hace daño) */
      Wire.begin(IOEXP_I2C_SDA, IOEXP_I2C_SCL);

      /* Crear e inicializar */
      auto* exp = new Expander(IOEXP_I2C_SCL, IOEXP_I2C_SDA, addr);
      exp->init();
      exp->begin();
      return exp;
    }
  } // namespace
#endif /* V_HAVE_IOEXP && IOEXP_ENABLE */
