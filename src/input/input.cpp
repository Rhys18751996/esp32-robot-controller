#include "input.h"
#include "bluepad_adapter.h"

void initInput() {
    initBluepadAdapter();
}

RawInput readInput() {
    return readBluepadInput();
}