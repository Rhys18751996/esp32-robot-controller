// src/input/input.cpp

#include "input.h"

void initInput() {
    // Later: Bluetooth init
}

RawInput readInput() {
    RawInput input = {};

    // Stub values for now
    input.leftStickX = 0;
    input.leftStickY = 0;
    input.connected = false;

    return input;
}