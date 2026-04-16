// src/input/input.cpp

#include "input.h"
#include <PS4Controller.h>

float normalize(int value) {
    // PS4 stick range is typically -128 → 127
    return value / 127.0f;
}

float normalizeTrigger(int value) {
    // Trigger range is 0 → 255
    return value / 255.0f;
}

void initInput() {
    PS4.begin();

    PS4.attachOnConnect([]() {
        Serial.println("PS4 Connected!");
    });

    PS4.attachOnDisconnect([]() {
        Serial.println("PS4 Disconnected!");
    });

    Serial.println("PS4 Bluetooth ready. Hold PS + Share to pair.");
}


RawInput readInput() {
    RawInput input = {};

    input.connected = PS4.isConnected();
    input.state = input.connected
        ? ControllerState::Connected
        : ControllerState::Disconnected;

    if (!input.connected) {
        return input; // everything stays zero/false
    }

    // --- Analog Sticks (-1.0 → 1.0) ---
    input.leftStickX  = normalize(PS4.LStickX());
    input.leftStickY  = -normalize(PS4.LStickY());
    input.rightStickX = normalize(PS4.RStickX());
    input.rightStickY = -normalize(PS4.RStickY());

    // --- Triggers (0.0 → 1.0) ---
    input.L2 = normalizeTrigger(PS4.L2Value());
    input.R2 = normalizeTrigger(PS4.R2Value());

    // --- Face Buttons ---
    input.cross    = PS4.Cross();
    input.circle   = PS4.Circle();
    input.square   = PS4.Square();
    input.triangle = PS4.Triangle();

    // --- Shoulder Buttons ---
    input.L1 = PS4.L1();
    input.R1 = PS4.R1();

    // --- Stick Clicks ---
    input.L3 = PS4.L3();
    input.R3 = PS4.R3();

    // --- D-Pad ---
    input.dpadUp    = PS4.Up();
    input.dpadDown  = PS4.Down();
    input.dpadLeft  = PS4.Left();
    input.dpadRight = PS4.Right();

    // --- System Buttons ---
    input.options  = PS4.Options();
    input.share    = PS4.Share();
    input.ps       = PS4.PSButton();
    input.touchpad = PS4.Touchpad();

    return input;
}

