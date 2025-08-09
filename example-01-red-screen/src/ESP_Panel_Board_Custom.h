/**
 * Custom board config for VIEWESMART 2.1" knob (UEDX48480021-MD80E)
 * LCD: GC9503CV (480x480) over RGB 16-bit + 3-wire SPI (SCL/SDA/CS)
 * Touch: GT1151 (I2C)
 */

#pragma once

// ---- BASIC LCD INFO ----
#define ESP_PANEL_LCD_NAME             GC9503
#define ESP_PANEL_LCD_H_RES            480
#define ESP_PANEL_LCD_V_RES            480
#define ESP_PANEL_LCD_RGB_DATA_WIDTH   16   // RGB565 (16 data lines)
#define ESP_PANEL_LCD_RGB_BPP          16   // bits per pixel

// ---- SPI (3-wire) for panel commands ----
#define ESP_PANEL_LCD_SPI_SCL_GPIO     13
#define ESP_PANEL_LCD_SPI_SDA_GPIO     12
#define ESP_PANEL_LCD_SPI_CS_GPIO      18

// ---- Control / backlight / reset ----
#define ESP_PANEL_LCD_RST_GPIO         8
#define ESP_PANEL_BACKLIGHT_GPIO       7

// ---- RGB timing pins ----
#define ESP_PANEL_RGB_DE_GPIO          17
#define ESP_PANEL_RGB_VSYNC_GPIO       3
#define ESP_PANEL_RGB_HSYNC_GPIO       46
#define ESP_PANEL_RGB_PCLK_GPIO        9

// ---- RGB data pins D0..D15 ----
#define ESP_PANEL_RGB_DATA0_GPIO       10
#define ESP_PANEL_RGB_DATA1_GPIO       11
#define ESP_PANEL_RGB_DATA2_GPIO       14
#define ESP_PANEL_RGB_DATA3_GPIO       21
#define ESP_PANEL_RGB_DATA4_GPIO       47
#define ESP_PANEL_RGB_DATA5_GPIO       45
#define ESP_PANEL_RGB_DATA6_GPIO       38
#define ESP_PANEL_RGB_DATA7_GPIO       39
#define ESP_PANEL_RGB_DATA8_GPIO       40
#define ESP_PANEL_RGB_DATA9_GPIO       41
#define ESP_PANEL_RGB_DATA10_GPIO      42
#define ESP_PANEL_RGB_DATA11_GPIO      2
#define ESP_PANEL_RGB_DATA12_GPIO      1
#define ESP_PANEL_RGB_DATA13_GPIO      -1   // (no cable en esta placa)
#define ESP_PANEL_RGB_DATA14_GPIO      -1
#define ESP_PANEL_RGB_DATA15_GPIO      -1

// ---- Polaridades/timings típicos GC9503 (60 Hz) ----
// Si ves imagen lavada o fuera de sync, ajusta estos 4:
#define ESP_PANEL_RGB_DE_IDLE_LEVEL            0
#define ESP_PANEL_RGB_HSYNC_IDLE_POLARITY      0
#define ESP_PANEL_RGB_VSYNC_IDLE_POLARITY      0
#define ESP_PANEL_RGB_PCLK_ACTIVE_NEG          0   // latch on rising edge

// Frecuencia de PCLK (empieza bajo y sube si todo ok)
#define ESP_PANEL_RGB_PCLK_HZ           (16 * 1000 * 1000)
