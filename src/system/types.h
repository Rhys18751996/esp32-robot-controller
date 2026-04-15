// src/system/types.h

#pragma once

struct Intent {
    float linear;    // -1.0 → 1.0
    float angular;   // -1.0 → 1.0
    bool boost;
    bool stop;
};

enum Mode {
    CONFIG,
    RUN
};

enum ControllerState {
    DISCONNECTED,
    CONNECTING,
    CONNECTED
};