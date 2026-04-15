// src/system/loop.cpp

#include <Arduino.h>
#include "loop.h"
#include "../utils/log.h"

const int LOOP_INTERVAL_MS = 20; // 50Hz

static unsigned long lastUpdate = 0;

void update(); // forward declaration

void initLoop() {
    log(INFO, "Loop initialized");
}

void updateLoop() {
    unsigned long now = millis();

    if (now - lastUpdate >= LOOP_INTERVAL_MS) {
        lastUpdate = now;
        Serial.printf("Tick: %lu\n", lastUpdate);
        update();
    }
}