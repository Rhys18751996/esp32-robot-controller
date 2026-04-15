// control.cpp
#include "../system/types.h"

Intent currentIntent;

void readInputs() {
    // TODO: controller input later
}

void mapToIntent() {
    // TODO: convert raw input → intent
}

void applySafety() {
    // TODO: emergency stop, limits
}

void outputControl() {
    // TODO: motors (later phase)
}

void update() {
    readInputs();
    mapToIntent();
    applySafety();
    outputControl();
}