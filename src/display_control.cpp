#include <lvgl.h>
#include <ui.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_LvGL_Glue.h>
#include "display_headers.hpp"

void lvgl_init(void) {
    tft.init(320, 240);
    LvGLStatus status = glue.begin(&tft);
    if (status != LVGL_OK) {
        //Serial.println("Adafruit LVGL Glue error %d\r\n", (int)status);
        for (;;)
            ;
    }

    ui_init();
}
