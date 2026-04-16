#include "input.h"
#include <Bluepad32.h>

GamepadPtr myGamepad = nullptr;

float normalizeAxis(int value) {
    // Bluepad32 uses -511 → 512
    return value / 511.0f;
}

float normalizeTrigger(int value) {
    // 0 → 1023
    return value / 1023.0f;
}

// --- Callbacks ---
void onConnectedGamepad(GamepadPtr gp) {
    Serial.println("Gamepad connected!");
    myGamepad = gp;
}

void onDisconnectedGamepad(GamepadPtr gp) {
    Serial.println("Gamepad disconnected!");
    if (myGamepad == gp) {
        myGamepad = nullptr;
    }
}

void initInput() {
    BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);
    BP32.forgetBluetoothKeys(); // optional: forces re-pairing

    Serial.println("Bluepad32 ready. Pair your controller.");
}

RawInput readInput() {
    RawInput input = {};

    BP32.update();

    input.connected = (myGamepad && myGamepad->isConnected());
    input.state = input.connected
        ? ControllerState::Connected
        : ControllerState::Disconnected;

    if (!input.connected) {
        return input;
    }

    // --- Sticks ---
    input.leftStickX  = normalizeAxis(myGamepad->axisX());
    input.leftStickY  = -normalizeAxis(myGamepad->axisY());
    input.rightStickX = normalizeAxis(myGamepad->axisRX());
    input.rightStickY = -normalizeAxis(myGamepad->axisRY());

    // --- Triggers ---
    input.L2 = normalizeTrigger(myGamepad->brake());
    input.R2 = normalizeTrigger(myGamepad->throttle());

    // --- Face Buttons ---
    input.cross    = myGamepad->a();
    input.circle   = myGamepad->b();
    input.square   = myGamepad->x();
    input.triangle = myGamepad->y();

    // --- Shoulder ---
    input.L1 = myGamepad->l1();
    input.R1 = myGamepad->r1();

    // --- Stick Click ---
    input.L3 = myGamepad->thumbL();
    input.R3 = myGamepad->thumbR();

    // --- D-pad ---
    input.dpadUp    = myGamepad->dpad() & DPAD_UP;
    input.dpadDown  = myGamepad->dpad() & DPAD_DOWN;
    input.dpadLeft  = myGamepad->dpad() & DPAD_LEFT;
    input.dpadRight = myGamepad->dpad() & DPAD_RIGHT;

    // --- System ---
    input.options  = myGamepad->miscButton();
    input.share    = false; // not always mapped
    input.ps       = myGamepad->miscSystem();
    input.touchpad = false;

    return input;
}