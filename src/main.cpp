#include <Arduino.h>
#include <bb_spi_lcd.h>
#include <Control_Surface.h>
#include <main.cpp_includes.h>
#define configBtn 19


bool inConfigMode = false;
int menuSelection = 0;
int lastDispUpdate{5};

// OutputBank configBank(1);

void setup() {
    Control_Surface.begin();
    Wire.begin(47, 48);
    delay(100);
    pinMode(configBtn, INPUT);
    Serial.begin(9600);
    lvgl_init();
    //configBank.select(0);
}

void loop() {
    Control_Surface.loop();

    if (lastDispUpdate - millis() >= 5) {
        lv_timer_handler();
        lastDispUpdate = millis();
    }

    // if (digitalRead(configBtn) == LOW) {
    //     inConfigMode = !inConfigMode;

    //     if (inConfigMode = true) {
    //         configBank.select(1);
    //     } else {
    //         configBank.select(0); 
    //     }
    //     while(digitalRead(configBtn) == LOW);
    // }
}