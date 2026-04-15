// log.cpp

#include <Arduino.h>
#include "log.h"

void log(LogLevel level, const char* message) {
    const char* prefix;

    switch (level) {
        case INFO: prefix = "[INFO]"; break;
        case WARN: prefix = "[WARN]"; break;
        case ERROR: prefix = "[ERROR]"; break;
        default: prefix = "[LOG]"; break;
    }

    Serial.print(prefix);
    Serial.print(" ");
    Serial.println(message);
}