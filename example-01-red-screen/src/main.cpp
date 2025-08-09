#include <Arduino.h>
#include <ESP_Panel_Library.h>     // de ESP32_Display_Panel
#include <lvgl.h>                  // usa lv_conf.h del submódulo

// Fuerza el uso de nuestra config custom
#ifndef ESP_PANEL_USE_CUSTOM_BOARD
#define ESP_PANEL_USE_CUSTOM_BOARD 1
#endif
#include "ESP_Panel_Board_Custom.h"

static ESP_Panel *panel = nullptr;

void setup() {
  Serial.begin(115200);
  delay(50);

  // 1) Inicializa el panel según nuestro header custom
  panel = new ESP_Panel();
  panel->init();      // crea bus RGB + SPI cmd y resetea el GC9503
  panel->begin();

  // 2) Enciende backlight (PWM fijo a 100%)
  if (panel->getBacklight()) {
    panel->getBacklight()->on();
  }

  // 3) LVGL mínimo para pintar rojo toda la pantalla
  lv_init();

  // Crea el driver LVGL usando el LCD del panel (helper de la librería)
  esp_lcd_panel_handle_t lcd_handle = panel->getLcd()->getLcdHandle();
  lv_disp_t *disp = esp_lcd_attach_lvgl(lcd_handle, ESP_PANEL_LCD_H_RES, ESP_PANEL_LCD_V_RES);
  // Nota: esp_lcd_attach_lvgl() es un helper de ESP32_Display_Panel para Arduino.
  // Si tu versión no lo trae, usa esp_lvgl_port (ejemplos en la lib) para registrar el display.

  // Pinta fondo rojo
  lv_obj_t *scr = lv_scr_act();
  lv_obj_set_style_bg_color(scr, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

  Serial.println("Red screen ready.");
}

void loop() {
  lv_timer_handler();
  delay(5);
}
