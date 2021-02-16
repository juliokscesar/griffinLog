#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>

namespace Log
{
    bool Init();
    bool Init(const std::string& fileName);
    const std::string GetDateTimeNow();
    void WriteLine(const std::string& message);
    void Write(const std::string& message);
    bool Finish();
}

#endif // LOG_H