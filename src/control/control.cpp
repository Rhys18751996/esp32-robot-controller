// src/control/control.cpp
#include "../system/types.h"
#include "../input/input.h"
#include "../utils/log.h"
#include <math.h>

RawInput input;
Intent currentIntent;
static float lastLinear = 0;
static float lastAngular = 0;
static ControllerState lastState = ControllerState::Disconnected;

float applyDeadzone(float value, float deadzone = 0.05f) {
    if (fabs(value) < deadzone) return 0.0f;
    return value;
}

float smooth(float current, float previous, float alpha = 0.2f) {
    return alpha * current + (1 - alpha) * previous;
}

const char* controllerStateToString(ControllerState state) {
    switch (state) {
        case ControllerState::Disconnected: return "Disconnected";
        case ControllerState::Connecting: return "Connecting";
        case ControllerState::Connected: return "Connected";
        default: return "Unknown";
    }
}

void initControl() {
    initInput();
}

void readInputs() {
    input = readInput();

    if (input.state != lastState) {
        logf(INFO, "Controller state: %s", controllerStateToString(input.state));
        lastState = input.state;
    }
}

void mapToIntent() {
    // deadzone
    float linear = applyDeadzone(input.leftStickY);
    float angular = applyDeadzone(input.leftStickX);

    // smoothing
    currentIntent.linear = smooth(linear, lastLinear);
    currentIntent.angular = smooth(angular, lastAngular);

    lastLinear = currentIntent.linear;
    lastAngular = currentIntent.angular;

    //currentIntent.boost = ?;
    //currentIntent.stop = ?;
}

void applySafety() {
    if (!input.connected) {
        // reset intent when disconnected
        currentIntent.linear = 0;
        currentIntent.angular = 0;
        currentIntent.boost = false;
        currentIntent.stop = true; 

        // reset smoothing carry over when disconnected
        lastLinear = 0;
        lastAngular = 0;
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

    static int debugCounter = 0;
    debugCounter++;

    if (debugCounter % 50 == 0) {
        logf(INFO, "Intent L: %.2f A: %.2f Conn: %d",
            currentIntent.linear,
            currentIntent.angular,
            input.connected);
    }

    outputControl();
}