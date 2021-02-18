#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
#include <cstdio>

namespace jkscLog
{
    bool Init();
    bool Init(const std::string& fileName);
    void WriteLine(const std::string& message);
    void Write(const std::string& message);
    void WriteFormatted(const std::string& formatLog, ...);
    bool Finish();

    const std::string GetDateTimeNow();
}

#endif // LOG_H