// src/control/control.cpp
#include "../system/types.h"
#include "../input/input.h"

RawInput input;
Intent currentIntent;

void initControl() {
    initInput();
}

void readInputs() {
    input = readInput();
}

void mapToIntent() {
    currentIntent.linear = input.leftStickY;
    currentIntent.angular = input.leftStickX;

    currentIntent.boost = input.cross;
    currentIntent.stop = input.circle;
}

void applySafety() {
    if (!input.connected) {
        currentIntent.linear = 0;
        currentIntent.angular = 0;
    }

    if (currentIntent.stop) {
        currentIntent.linear = 0;
        currentIntent.angular = 0;
    }
}

void outputControl() {
    // TODO: motors (later phase)
}

void update() {
    readInputs();
    mapToIntent();
    applySafety();
    outputControl();
}