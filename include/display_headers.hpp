#ifndef DISPLAY_HEADERS_HPP
#define DISPLAY_HEADERS_HPP
#include <stdint.h>

extern uint16_t w;
extern uint16_t h;
extern uint16_t iSize;
extern uint16_t *dma_buf;
extern uint16_t *draw_buf;
extern BB_SPI_LCD lcd;
extern void disp_flush(lv_display_t*, const lv_area_t*, uint8_t*);
extern void lvgl_init(void);
#endif
