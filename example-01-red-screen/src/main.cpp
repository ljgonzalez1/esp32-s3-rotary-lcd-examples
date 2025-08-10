#include <Arduino.h>
#include <esp_display_panel.hpp>
#include <lvgl.h>
#include <esp_timer.h>
#include <esp_heap_caps.h>

// Panel global
static ESP_Panel* panel = nullptr;

// LVGL buffers/driver
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf1 = nullptr, *buf2 = nullptr;
static lv_disp_drv_t disp_drv;

static void lvgl_tick_cb(void*) {
  lv_tick_inc(5); // 5 ms
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
  // Dibuja el área usando el LCD del panel (RGB)
  panel->getLcd()->drawBitmap(area->x1, area->y1, area->x2 + 1, area->y2 + 1,
                              (const uint16_t*)color_p);
  lv_disp_flush_ready(drv);
}

void setup() {
  Serial.begin(115200);
  delay(50);

  // 1) Panel
  panel = new ESP_Panel();
  panel->init();     // usa la config interna del vendor (via nuestro shim)
  panel->begin();

  if (panel->getBacklight()) panel->getBacklight()->on(); // 100%

  // 2) LVGL básico
  lv_init();

  // Buffers en PSRAM: ~40 líneas
  const uint32_t w = panel->getLcd()->getWidth();
  const uint32_t h = panel->getLcd()->getHeight();
  const uint32_t lines = 40;
  const uint32_t buf_px = w * lines;

  buf1 = (lv_color_t*) heap_caps_malloc(buf_px * sizeof(lv_color_t),
                                        MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
  buf2 = (lv_color_t*) heap_caps_malloc(buf_px * sizeof(lv_color_t),
                                        MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
  lv_disp_draw_buf_init(&draw_buf, buf1, buf2, buf_px);

  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = w;
  disp_drv.ver_res = h;
  disp_drv.flush_cb = lvgl_flush_cb;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Tick de LVGL cada 5 ms
  static esp_timer_handle_t lvgl_tick_timer;
  const esp_timer_create_args_t targs = {.callback = lvgl_tick_cb, .arg = nullptr, .name = "lv_tick"};
  esp_timer_create(&targs, &lvgl_tick_timer);
  esp_timer_start_periodic(lvgl_tick_timer, 5000); // 5000 us = 5 ms

  // 3) Fondo rojo
  lv_obj_t *scr = lv_scr_act();
  lv_obj_set_style_bg_color(scr, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

  Serial.println("Red screen ready.");
}

void loop() {
  lv_timer_handler();
  delay(5);
}
