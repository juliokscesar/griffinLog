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

#include "Log.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include <stdexcept>

#define ASSERT_LOG_INIT() if (!m_logFile.is_open()) throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + " LOG WAS NOT INITIATED")

jkscLog::jkscLog()
{
    std::cout << "Default constructor of jkscLog called\n";
}

jkscLog::jkscLog(const std::string& fileName)
{
    Init(fileName);
}

bool jkscLog::Init()
{
    if (!m_logFile.is_open())
        m_logFile.open("jkscLogFile.log");
    
    WriteLine("Log Initiated");

    return m_logFile.is_open();
}

bool jkscLog::Init(const std::string& fileName)
{
    if (!m_logFile.is_open())
        m_logFile.open(fileName);

    WriteLine("Log Initiated");

    return m_logFile.is_open();
}

void jkscLog::Write(const std::string& logInfo)
{
    ASSERT_LOG_INIT();
    m_logFile << "[" << GetDateTimeNow() << "] " << logInfo;
}

void jkscLog::WriteLine(const std::string& logInfo)
{
    ASSERT_LOG_INIT();
    Write(logInfo + "\n");
}

void jkscLog::WriteF(const std::string& formatLogInfo, ...)
{
    ASSERT_LOG_INIT();

    va_list args;
    va_start(args, formatLogInfo);

    const int logSize = (int)formatLogInfo.length() + 256;
    char *log = new char[logSize];

    vsprintf(log, formatLogInfo.c_str(), args);

    Write(log);

    delete[] log;
    va_end(args);
}

bool jkscLog::Finish()
{
    if (m_logFile.is_open())
    {
        WriteLine("Log Finished");
        m_logFile.close();
    }

    return !m_logFile.is_open();
}

const std::string jkscLog::GetDateTimeNow()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::stringstream stream;
    stream << std::put_time(now, "%Y-%m-%d;%H:%M:%S%p");

    std::string timeNow;
    stream >> timeNow;

    return timeNow;
}
