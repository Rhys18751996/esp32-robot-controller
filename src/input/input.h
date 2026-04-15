// src/input/input.h

#pragma once

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
};

void initInput();
RawInput readInput();