// log.h

#pragma once

enum LogLevel {
    INFO,
    WARN,
    ERROR
};

void log(LogLevel level, const char* message);