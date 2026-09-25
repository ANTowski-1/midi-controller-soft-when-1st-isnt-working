#include <Control_Surface.h>
#include <Preferences.h>


Preferences config;

// Lib setup
extern USBMIDI_Interface USB_MIDI;
extern HardwareSerialMIDI_Interface SERIAL_MIDI;
// ?HardwareSerialDebugMIDI_Interface DEBUG_MIDI(Serial, 9600);
extern USBDebugMIDI_Interface DEBUG_MIDI;
extern BluetoothMIDI_Interface BLE_MIDI;

extern BidirectionalMIDI_PipeFactory<2> pipes;

struct transportCfg {
    uint8_t source1;
    uint8_t source2;
    uint8_t sink1;
    uint8_t sink2;
};

TrueMIDI_SinkSource* transportInterfaces[] = {
    &Control_Surface,
    &USB_MIDI,
    &BLE_MIDI,
    &SERIAL_MIDI,
    &DEBUG_MIDI,
};

void loadCfg() {
    config.begin("midiTransport", true);
    transportCfg cfg;
    cfg.source1 = config.getUInt("source1", 0); // 1st source, default to Control Surface
    cfg.source2 = config.getUInt("source2", 0); // 2nd source, default to Control Surface
    cfg.sink1 = config.getUInt("sink1", 1); // 1st sink, default to USB
    cfg.sink2 = config.getUInt("sink2", 3); // 2nd sink, default to BLE
    config.end();
}

void saveCfg() {
    transportCfg cfg;
    config.begin("midiTransport", false);
    config.putUInt("source1", cfg.source1);
    config.putUInt("source2", cfg.source2);
    config.putUInt("sink1", cfg.sink1);
    config.putUInt("sink2", cfg.sink2);
    config.end(); 
}

void applyCfg() {
    transportCfg cfg;
    *transportInterfaces[cfg.source1] | pipes | *transportInterfaces[cfg.sink1];
    *transportInterfaces[cfg.source2] | pipes | *transportInterfaces[cfg.sink2];
}

void saveConfByTab(int tabNum, int chosenOption) {
    transportCfg cfg;
    if (tabNum == 0) {
	cfg.source1 = chosenOption;
    } else if (tabNum == 1) {
	cfg.sink1 = chosenOption;
    } else if (tabNum == 2) {
	cfg.source2 = chosenOption;
    } else if (tabNum == 3) {
	cfg.sink1 = chosenOption;
    }
    saveCfg();
}
