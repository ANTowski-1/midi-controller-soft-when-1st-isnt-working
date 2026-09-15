#define TFT_CS 14
#define TFT_DC 17
#define TFT_RST 18
#define TFT_MISO 13
#define TFT_MOSI 11
#define TFT_SCK 12

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);
Adafruit_LvGL_Glue glue;

extern void lvgl_init(){};