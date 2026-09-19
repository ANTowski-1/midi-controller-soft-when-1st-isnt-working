#include <Arduino.h>
#include <Control_Surface.h>
#include <main.cpp_includes.h>

bool inConfigMode = false;
int menuSelection = 0;

// Screen update variables
int lastDispUpdate = 0;

int lastBtnPotUpdate = 0;
int currentBtnPotUpdate = 0;
bool currentMBtnState = false;
bool lastMBtnState[6] = {0,0,0,0,0,0};
int currentFaderPosition = 0;
int lastFadVal[6] = {0,0,0,0,0,0};
bool ScreenUpdated = false;
int i{0};

OutputBank configBank(1);


void setup() {
    Control_Surface.begin();
    Wire.begin(47, 48);
    delay(200);
    pinMode(BTN_ENC1, INPUT);

    Serial.begin(9600);
    configBank.select(0);

    tft_init();
    // while (i < 6){
    //     muteDisplay(i, false);
    //     fadersDisplay(i, 0);
    //     lastFadVal[i] = 0;
    //     lastMBtnState[i] = false;
    // }
    lastDispUpdate = millis();
    Serial.println("Setup complete");
}

void loop() {
    Control_Surface.loop();
    if (millis() - lastDispUpdate >= 100) {
        ScreenUpdated = false;
        while (ScreenUpdated == false) {
            if (lastBtnPotUpdate <= 6) {
                currentBtnPotUpdate++;
                currentMBtnState = muteButtons[currentBtnPotUpdate - 1].getState();
                currentFaderPosition = pots[currentBtnPotUpdate - 1].getValue();
                if (lastFadVal[currentBtnPotUpdate -1] != currentFaderPosition 
                    || lastMBtnState[currentBtnPotUpdate -1] != currentMBtnState) {
                    fadBtnClear(currentBtnPotUpdate -1);
                    muteDisplay((currentBtnPotUpdate -1), currentMBtnState);
                    fadersDisplay((currentBtnPotUpdate -1), currentFaderPosition);
                    lastFadVal[currentBtnPotUpdate -1] = currentFaderPosition;
                    lastMBtnState[currentBtnPotUpdate -1] = currentMBtnState;
                }
                lastBtnPotUpdate = currentBtnPotUpdate;
            } else if (lastBtnPotUpdate > 6) {
                lastBtnPotUpdate = 0;
                currentBtnPotUpdate = 0;
                ScreenUpdated = true;
                lastDispUpdate = millis();
            }
        }
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
