/*
MIT License

Copyright (c) 2021 juliokscesar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "jkscLog.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include <stdexcept>

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif

#define ASSERT_LOG_INIT() if (!logFile.is_open()) throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " LOG WAS NOT INITIATED")

namespace jkscLog
{
    static std::ofstream logFile;

    void createLogDir()
    {
        #if defined(WIN32) || defined(_WIN32)
        CreateDirectoryA("logs", NULL);
        #else
        system("mkdir -p ./logs");
        #endif
    }

    bool Init()
    {
        if (!logFile.is_open())
        {
            createLogDir();
            logFile.open("logs/logfile.log", std::ofstream::out);
        }

        Info("Log Initiated");

        return logFile.is_open();
    }

    bool Init(const std::string &logFileName)
    {
        if (!logFile.is_open())
        {
            createLogDir();
            logFile.open(std::string("logs/") + logFileName, std::ofstream::out);
        }

        Info("Log Initiated");

        return logFile.is_open();
    }

    void LogWriteMode(LogMode logMode, const std::string &log)
    {
        ASSERT_LOG_INIT();

        std::string mode;
        std::string colorMode;

        switch (logMode)
        {
            case LogMode::INFO:
                mode = "INFO";
                colorMode = ANSI_COLOR_BLUE;
                break;
	   
	        case LogMode::DEBUG:
		        mode = "DEBUG";
		        colorMode = ANSI_COLOR_GREEN;
		        break;

            case LogMode::WARN:
                mode = "WARN";
                colorMode = ANSI_COLOR_YELLOW;
                break;

            case LogMode::CRITICAL:
                mode = "CRITICAL";
                colorMode = ANSI_COLOR_RED;
                break;

            default:
                throw std::runtime_error("Invalid log mode\n");
                break;
        }

        logFile << "[" << GetDateTimeNow() << "] [" << mode << "] " << log << "\n";
        std::cout << "[" << GetDateTimeNow() << "] " << colorMode << "[" << mode << "] " << ANSI_COLOR_RESET  << log << "\n";
    }

    void Info(const std::string &logInfo, ...)
    {
        va_list args;
        va_start(args, logInfo);

        char *log = new char[logInfo.size() + 256];
        vsnprintf(log, logInfo.size() + 255, logInfo.c_str(), args);

        LogWriteMode(LogMode::INFO, log);

        delete[] log;
        va_end(args);
    }

    void Debug(const std::string &logDebug, ...)
    {
	va_list args;
	va_start(args, logDebug);

	char *log = new char[logDebug.size() + 256];
	vsnprintf(log, logDebug.size() + 255, logDebug.c_str(), args);

	LogWriteMode(LogMode::DEBUG, log);

	delete[] log;
	va_end(args);
    }    

    void Warn(const std::string &logWarn, ...)
    {
        va_list args;
        va_start(args, logWarn);

        char *log = new char[logWarn.size() + 256];
        vsnprintf(log, logWarn.size() + 255, logWarn.c_str(), args);

        LogWriteMode(LogMode::WARN, log);

        delete[] log;
        va_end(args);
    }

    void Critical(const std::string &logCritical, ...)
    {
        va_list args;
        va_start(args, logCritical);

        char *log = new char[logCritical.size() + 256];
        vsnprintf(log, logCritical.size() + 255, logCritical.c_str(), args);

        LogWriteMode(LogMode::CRITICAL, log);

        delete[] log;
        va_end(args);
    }

    bool Finish()
    {
        Info("Log Finished");

        if (logFile.is_open())
            logFile.close();

        return !logFile.is_open();
    }

    const std::string GetDateTimeNow()
    {
        std::time_t t = std::time(0);
        std::tm *now = std::localtime(&t);
        
        char timeNow[20];
        std::strftime(timeNow, sizeof(timeNow), "%Y-%m-%d %H:%M:%S", now);
        const std::string dateTime(timeNow);

        return dateTime;
    }

}
