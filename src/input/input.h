// src/input/input.h

#pragma once

#include "../system/types.h"

struct RawInput {
    float leftStickX;
    float leftStickY;
    float rightStickX;
    float rightStickY;

    bool cross;
    bool circle;
    bool square;
    bool triangle;

    bool connected;
    ControllerState state; 
};

void initInput();
RawInput readInput();