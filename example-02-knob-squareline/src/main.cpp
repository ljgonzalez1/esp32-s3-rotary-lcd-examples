#include <Arduino.h>

// IDF display driver (disponible dentro de Arduino-ESP32 3.x)
extern "C" {
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "driver/gpio.h"
}

static esp_lcd_panel_handle_t panel = nullptr;

// === Ajusta resolución del módulo ===
constexpr int LCD_HRES = 480;
constexpr int LCD_VRES = 480;

// === TODO: Rellena con tu mapeo de pines RGB ===
// Señales de sincronismo / control
#define PIN_LCD_DE      GPIO_NUM_XX   // TODO
#define PIN_LCD_PCLK    GPIO_NUM_XX   // TODO
#define PIN_LCD_VSYNC   GPIO_NUM_XX   // TODO
#define PIN_LCD_HSYNC   GPIO_NUM_XX   // TODO
#define PIN_LCD_DISP_EN GPIO_NUM_XX   // (si tu placa lo tiene) o quita este control

// Bus de datos RGB565 (16 bits: R5..R0, G5..G0, B5..B0)
#define PIN_LCD_DATA0   GPIO_NUM_XX   // B0
#define PIN_LCD_DATA1   GPIO_NUM_XX   // B1
#define PIN_LCD_DATA2   GPIO_NUM_XX   // B2
#define PIN_LCD_DATA3   GPIO_NUM_XX   // B3
#define PIN_LCD_DATA4   GPIO_NUM_XX   // B4
#define PIN_LCD_DATA5   GPIO_NUM_XX   // B5
#define PIN_LCD_DATA6   GPIO_NUM_XX   // G0
#define PIN_LCD_DATA7   GPIO_NUM_XX   // G1
#define PIN_LCD_DATA8   GPIO_NUM_XX   // G2
#define PIN_LCD_DATA9   GPIO_NUM_XX   // G3
#define PIN_LCD_DATA10  GPIO_NUM_XX   // G4
#define PIN_LCD_DATA11  GPIO_NUM_XX   // G5
#define PIN_LCD_DATA12  GPIO_NUM_XX   // R0
#define PIN_LCD_DATA13  GPIO_NUM_XX   // R1
#define PIN_LCD_DATA14  GPIO_NUM_XX   // R2
#define PIN_LCD_DATA15  GPIO_NUM_XX   // R3
// Si tu panel usa 18 bits, añade dos R bits más; si usa 16, así está bien.

// Brillo (opcional)
#define PIN_LCD_BKLT    GPIO_NUM_XX   // TODO o -1 si no aplica

void fill_screen_red(esp_lcd_panel_handle_t h) {
  static uint16_t line[LCD_HRES];
  for (int x = 0; x < LCD_HRES; ++x) line[x] = 0xF800; // rojo RGB565
  for (int y = 0; y < LCD_VRES; ++y) {
    esp_lcd_panel_draw_bitmap(h, 0, y, LCD_HRES, y + 1, line);
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);

  // Config del bus RGB
  esp_lcd_rgb_panel_config_t rgb_cfg = {
      .data_width = 16, // RGB565
      .psram_trans_align = 64,
      .num_fbs = 1,
      .clk_src = LCD_CLK_SRC_PLL240M, // típico en S3
      .disp_gpio_num = (int)PIN_LCD_DISP_EN, // o -1 si no existe
      .pclk_gpio_num = (int)PIN_LCD_PCLK,
      .vsync_gpio_num = (int)PIN_LCD_VSYNC,
      .hsync_gpio_num = (int)PIN_LCD_HSYNC,
      .de_gpio_num = (int)PIN_LCD_DE,
      .data_gpio_nums = {
          (int)PIN_LCD_DATA0,  (int)PIN_LCD_DATA1,  (int)PIN_LCD_DATA2,  (int)PIN_LCD_DATA3,
          (int)PIN_LCD_DATA4,  (int)PIN_LCD_DATA5,  (int)PIN_LCD_DATA6,  (int)PIN_LCD_DATA7,
          (int)PIN_LCD_DATA8,  (int)PIN_LCD_DATA9,  (int)PIN_LCD_DATA10, (int)PIN_LCD_DATA11,
          (int)PIN_LCD_DATA12, (int)PIN_LCD_DATA13, (int)PIN_LCD_DATA14, (int)PIN_LCD_DATA15,
      },
      .timings = {
          .pclk_hz = 12 * 1000 * 1000, // 12MHz para empezar (sube luego si todo va bien)
          .h_res = LCD_HRES,
          .v_res = LCD_VRES,
          // Estos márgenes dependen del controlador (p.ej. ST7701*). Valores conservadores:
          .hsync_back_porch = 40,
          .hsync_front_porch = 20,
          .hsync_pulse_width = 10,
          .vsync_back_porch = 8,
          .vsync_front_porch = 8,
          .vsync_pulse_width = 4,
          .flags = {
              .hsync_idle_low = 0,
              .vsync_idle_low = 0,
              .de_idle_high   = 0,
              .pclk_active_neg = 1, // muchos paneles RGB usan flanco descendente
              .pclk_idle_high  = 0,
          },
      },
      .flags = {
          .fb_in_psram = 1,
          .refresh_on_demand = 0,
      },
  };

  ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(&rgb_cfg, &panel));
  ESP_ERROR_CHECK(esp_lcd_panel_reset(panel));
  ESP_ERROR_CHECK(esp_lcd_panel_init(panel));
  ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel, true));

  // Backlight opcional
  if ((int)PIN_LCD_BKLT >= 0) {
    pinMode((int)PIN_LCD_BKLT, OUTPUT);
    digitalWrite((int)PIN_LCD_BKLT, HIGH);
  }

  fill_screen_red(panel);
}

void loop() {
  // nada
}
