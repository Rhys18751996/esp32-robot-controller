// src/input/input.cpp

#include "input.h"

float normalize(int value) {
    return value / 127.0f;
}

void initInput() {
    // Later: Bluetooth init
}

RawInput readInput() {
    RawInput input = {};

    // stubbed values for now
    input.connected = false;
    input.state = ControllerState::Disconnected;

    return input;
}

// #include <PS4Controller.h>// depends on library
// RawInput readInput() {
//     RawInput input = {};

//     input.connected = PS4.isConnected();
//     input.state = input.connected
//         ? ControllerState::Connected
//         : ControllerState::Disconnected;

//     if (input.connected) {
//         input.leftStickX = normalize(PS4.LStickX());
//         input.leftStickY = normalize(PS4.LStickY());

//         input.cross = PS4.Cross();
//         input.circle = PS4.Circle();
//     }

//     return input;
// }

