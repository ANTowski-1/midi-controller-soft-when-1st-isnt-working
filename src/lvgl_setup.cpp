#include <lvgl.h>
#include <bb_spi_lcd.h>
#include <ui.h>
#include "display_headers.hpp"

uint32_t my_tick(void)
{
    return millis();
}
uint16_t w = 320;
uint16_t h = 240;
uint16_t iSize = (w * h / 4) * sizeof(uint16_t);
uint16_t *dma_buf = new uint16_t[iSize];
BB_SPI_LCD lcd;
#define DRAW_BUF_SIZE(w, h) ((w * h) / 10 * sizeof(uint16_t))
uint16_t *draw_buf;

void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map){
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);
    uint16_t *px_map_16 = (uint16_t *)px_map;

    static uint16_t *dma_buf = nullptr;
    if (!dma_buf) {
        dma_buf = (uint16_t *)heap_caps_malloc(w * h * sizeof(uint16_t), MALLOC_CAP_DMA);
    }

    memcpy(dma_buf, px_map_16, w * h * sizeof(uint16_t));

    lcd.setAddrWindow(area->x1,  area->y1, w, h);
    lcd.pushPixels(dma_buf, w, DRAW_TO_LCD | DRAW_WITH_DMA);

    lv_display_flush_ready(disp);
}

void lvgl_init(void) {
    lcd.begin(LCD_ST7789, FLAGS_INVERT, 40000000, 14, 17, 18, -1, 13, 11, 12);
    delay(100);
    lcd.setRotation(0);
    /*lcd.fillScreen(TFT_BLACK);
    lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    lcd.setFont(FONT_12x16);
    lcd.println("Copyright 2026 Antoni Kolaczek");
    lcd.println("This software comes with");
    lcd.println("absolutly no warranty!");
    lcd.println("Software Licenced Under");
    lcd.println("GNU-GPL 3.0");
    lcd.println("Hardware Is Licenced Under");
    lcd.println("Open Hardware Licence V2");
    lcd.println("For More Info Visit");
    lcd.println("github.com/ANTowski-1/MIDI-Controller");
    */
    lv_init();
    lv_tick_set_cb(my_tick);
    lv_display_t *disp;
    iSize = LV_DRAW_BUF_SIZE(w, h, LV_COLOR_FORMAT_RGB565);
    disp = lv_display_create(w,h);
    draw_buf = (uint16_t *)heap_caps_malloc(iSize, MALLOC_CAP_DMA);
    lv_display_set_flush_cb(disp, disp_flush);
    lv_display_set_buffers(disp, draw_buf, NULL, iSize, LV_DISPLAY_RENDER_MODE_FULL);
    ui_init();
    Serial.println("LVGL library has been initialised");
}
