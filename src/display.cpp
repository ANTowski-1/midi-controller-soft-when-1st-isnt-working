#include <SPI.h>
#include <display.h>
#include <SPI.h>
#include <bb_spi_lcd.h>
#include <string.h>
BB_SPI_LCD lcd;

int lastFadVal[6];
std::string configOptIn[4] = {Control Surfuce, USB, BLE, Serial}
std::string configOptOut[4] = {Control Surfuce, USB, BLE, Serial}


void tft_init(){
    SPI.begin(12,13,11);
    lcd.begin(LCD_ST7789, FLAGS_INVERT, 40000000, 14, 17, 18, -1, 13, 11, 12);
    delay(100);
    lcd.setRotation(270);
    lcd.fillScreen(TFT_BLACK);
    lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    lcd.setFont(FONT_12x16);
    Serial.println("Display Have been succesfully initialised!");
}

void tft_draw_circle() {
    lcd.fillCircle(160, 120, 25, TFT_RED);
}

void tft_write_txt(int num) {
    lcd.println(int(num));
}

void muteDisplay(int btnNum, bool muted) {
    int muteBtnPosition = 15 + 50 * btnNum;
    if (muted == true){
        lcd.setTextColor(TFT_GREEN, TFT_RED);
	lcd.fillRect(int(muteBtnPosition), 190, 40, 40, TFT_RED);
        lcd.drawString("Mute", position, 210, FONT_6x8);
    } else if (muted == false) {
	lcd.setTextColor(TFT_GREEN, TFT_GREY);
        lcd.fillRect(int(muteBtnPosition), 190, 40, 40, TFT_GREY);
        lcd.drawString("Mute", position, 210, FONT_6x8);
    }
}

void fadersDisplay(int fadNum, int fadPos) {
    if (lastFadVal[fadNum] == fadPos) {
        return;
    }
    int fadPosition = 30 + 50 * fadNum;
    int fadBarPosition = 15 + 50 * fadNum;
    int fadBarVerticalPosition = 70 + (127 - fadPos) * 90/127;
    lcd.fillRect(int(fadBarPosition), 70, 40, 120);
    lcd.fillRect(int(fadPosition), 70, 10, 100, TFT_GREY);
    lcd.fillRect(int(fadBarPosition), fadBarVerticalPosition, 40, 10, TFT_GREY);
    lcd.setFont(FONT_8x8);
    lcd.setCursor(fadPosition, 175);
    lcd.print(int(fadPos));
    lastFadVal[fadNum] = fadPos;
}

void settings(){
	lcdClear();
	lcd.
}

void lcdClear(){
    lcd.fillScreen(TFT_BLACK);
}

/*
Settings — How to idea:
Make cards, seperate for each setting, beetwen which you switch using button, 
and choose options using encoder. Swiching cards also saves the settings changes.
*/
