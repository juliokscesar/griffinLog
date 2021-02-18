#include "Log.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>

namespace jkscLog
{
    std::ofstream logFile;

    bool Init()
    {
        if (!logFile.is_open())
            logFile.open("logfile.log");
        
        return logFile.is_open();
    }

    bool Init(const std::string& fileName)
    {
        if (!logFile.is_open())
            logFile.open(fileName);
        
        return logFile.is_open();
    }

    void WriteLine(const std::string& logInfo)
    {
        logFile << "[" << GetDateTimeNow() << "] " << logInfo << "\n";
    }

    void Write(const std::string& logInfo)
    {
        logFile << "[" << GetDateTimeNow() << "] " << logInfo;
    }

    void WriteFormatted(const std::string& formatLog, ...)
    {
        va_list args;
        va_start(args, formatLog);

        const int logSize = (int)formatLog.length() + 256;
        char* log = new char[logSize];

        vsprintf(log, formatLog.c_str(), args);

        Write(log);

        delete[] log;
        va_end(args);
    }

    bool Finish()
    {
        if (logFile.is_open())
            logFile.close();

        return !logFile.is_open();
    }

    const std::string GetDateTimeNow()
    {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        std::stringstream stream;
        stream << std::put_time(now, "%Y-%m-%d;%H:%M:%S%p");

        std::string timeNow;
        stream >> timeNow;

        return timeNow;
    }
}