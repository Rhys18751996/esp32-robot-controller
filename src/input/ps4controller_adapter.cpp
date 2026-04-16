// src/input/ps4controller_adapter.cpp
#include "ps4_adapter.h"
#include <PS4Controller.h>

/*
to use this adapter would need to update input.cpp to
#include "ps4_adapter.h"

void initInput() {
    initPS4Adapter();
}

RawInput readInput() {
    return readPS4Input();
}
*/



// --- Normalization ---
static float normalizeAxis(int value) {
    // -128 → 127
    return value / 127.0f;
}

static float normalizeTrigger(int value) {
    // 0 → 255
    return value / 255.0f;
}

// --- Callbacks ---
void onPS4Connect() {
    Serial.println("[Adapter] PS4 Connected");
}

void onPS4Disconnect() {
    Serial.println("[Adapter] PS4 Disconnected");
}

// --- Init ---
void initPS4Adapter() {
    PS4.begin();

    PS4.attachOnConnect(onPS4Connect);
    PS4.attachOnDisconnect(onPS4Disconnect);

    Serial.println("[Adapter] PS4Controller initialized");
}

// --- Read ---
RawInput readPS4Input() {
    RawInput input = {};

    input.connected = PS4.isConnected();
    input.state = input.connected
        ? ControllerState::Connected
        : ControllerState::Disconnected;

    if (!input.connected) {
        return input;
    }

    // --- Sticks ---
    input.leftStickX  = normalizeAxis(PS4.LStickX());
    input.leftStickY  = -normalizeAxis(PS4.LStickY());
    input.rightStickX = normalizeAxis(PS4.RStickX());
    input.rightStickY = -normalizeAxis(PS4.RStickY());

    // --- Triggers ---
    input.L2 = normalizeTrigger(PS4.L2Value());
    input.R2 = normalizeTrigger(PS4.R2Value());

    // --- Face Buttons ---
    input.cross    = PS4.Cross();
    input.circle   = PS4.Circle();
    input.square   = PS4.Square();
    input.triangle = PS4.Triangle();

    // --- Shoulder ---
    input.L1 = PS4.L1();
    input.R1 = PS4.R1();

    // --- Stick Click ---
    input.L3 = PS4.L3();
    input.R3 = PS4.R3();

    // --- D-pad ---
    input.dpadUp    = PS4.Up();
    input.dpadDown  = PS4.Down();
    input.dpadLeft  = PS4.Left();
    input.dpadRight = PS4.Right();

    // --- System ---
    input.options  = PS4.Options();
    input.share    = PS4.Share();
    input.ps       = PS4.PSButton();
    input.touchpad = PS4.Touchpad();

    return input;
}
