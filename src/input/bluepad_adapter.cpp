// /src/input/bluepad_adapter.cpp
#include "bluepad_adapter.h"
#include <Bluepad32.h>

// --- Internal state ---
static GamepadPtr gamepad = nullptr;

// --- Normalization ---
static float normalizeAxis(int value) {
    return value / 511.0f; // -511 → 512
}

static float normalizeTrigger(int value) {
    return value / 1023.0f; // 0 → 1023
}

// --- Callbacks ---
static void onConnectedGamepad(GamepadPtr gp) {
    Serial.println("[Adapter] Gamepad connected");
    gamepad = gp;
}

static void onDisconnectedGamepad(GamepadPtr gp) {
    Serial.println("[Adapter] Gamepad disconnected");
    if (gamepad == gp) {
        gamepad = nullptr;
    }
}

// --- Init ---
void initBluepadAdapter() {
    BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);

    // Optional but useful during dev
    BP32.forgetBluetoothKeys();

    Serial.println("[Adapter] Bluepad32 initialized");
}

// --- Read ---
RawInput readBluepadInput() {
    RawInput input = {};

    BP32.update();

    input.connected = (gamepad && gamepad->isConnected());
    input.state = input.connected
        ? ControllerState::Connected
        : ControllerState::Disconnected;

    if (!input.connected) {
        return input;
    }

    // --- Sticks ---
    input.leftStickX  = normalizeAxis(gamepad->axisX());
    input.leftStickY  = -normalizeAxis(gamepad->axisY());
    input.rightStickX = normalizeAxis(gamepad->axisRX());
    input.rightStickY = -normalizeAxis(gamepad->axisRY());

    // --- Triggers ---
    input.L2 = normalizeTrigger(gamepad->brake());
    input.R2 = normalizeTrigger(gamepad->throttle());

    // --- Face Buttons ---
    input.cross    = gamepad->a();
    input.circle   = gamepad->b();
    input.square   = gamepad->x();
    input.triangle = gamepad->y();

    // --- Shoulder ---
    input.L1 = gamepad->l1();
    input.R1 = gamepad->r1();

    // --- Stick Click ---
    input.L3 = gamepad->thumbL();
    input.R3 = gamepad->thumbR();

    // --- D-pad ---
    uint8_t dpad = gamepad->dpad();
    input.dpadUp    = dpad & DPAD_UP;
    input.dpadDown  = dpad & DPAD_DOWN;
    input.dpadLeft  = dpad & DPAD_LEFT;
    input.dpadRight = dpad & DPAD_RIGHT;

    // --- System ---
    input.options  = gamepad->miscButton();
    input.ps       = gamepad->miscSystem();

    // Not consistently supported across controllers
    input.share    = false;
    input.touchpad = false;

    return input;
}