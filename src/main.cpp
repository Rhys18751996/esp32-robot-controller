// src/main.cpp

#include <Arduino.h>
#include "system/loop.h"
#include "utils/log.h"
#include "control/control.h"

void setup() {
    Serial.begin(115200);
    delay(1000);

    log(INFO, "System starting");

    initControl();
    initLoop();
}

void loop() {
    updateLoop();
}