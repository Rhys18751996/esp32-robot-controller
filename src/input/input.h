// src/input/input.h

#pragma once

#include "../system/types.h"

struct RawInput {
    // --- Analog Sticks (-1.0 → 1.0) ---
    float leftStickX;
    float leftStickY;
    float rightStickX;
    float rightStickY;

    // --- Triggers (0.0 → 1.0) ---
    float L2;
    float R2;

    // --- Face Buttons ---
    bool cross;
    bool circle;
    bool square;
    bool triangle;

    // --- Shoulder Buttons ---
    bool L1;
    bool R1;

    // --- Stick Clicks ---
    bool L3;
    bool R3;

    // --- D-Pad ---
    bool dpadUp;
    bool dpadDown;
    bool dpadLeft;
    bool dpadRight;

    // --- System Buttons ---
    bool options;
    bool share;
    bool ps;
    bool touchpad;

    // --- Meta ---
    bool connected;
    ControllerState state;
};

void initInput();
RawInput readInput();