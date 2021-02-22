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

#include "Log.h"

static FILE* logFile;

int LogInit()
{
    if (!logFile)
        logFile = fopen("logfile.log", "w");

    LogWriteLine("Log Initiated");
    return !(logFile == NULL);
}

int LogInitCustom(const char* fileName)
{
    if (!logFile)
        logFile = fopen(fileName, "w");

    LogWriteLine("Log Initiated");
    return !(logFile == NULL);
}

void LogWrite(const char* logInfo)
{
    char* dateTime = GetCurrentDateTime();

    fprintf(logFile, "%s %s", dateTime, logInfo);

    free(dateTime);
}

void LogWriteLine(const char* logInfo)
{
    char* dateTime = GetCurrentDateTime();

    fprintf(logFile, "%s %s\n", dateTime, logInfo);

    free(dateTime);
}

void LogWriteF(const char* formatLog, ...)
{
    va_list args;
    va_start(args, formatLog);

    // const int logSize = (int)strlen(formatLog) + 256;
    // char* log = malloc(logSize);

    // vsprintf(log, formatLog, args);

    // LogWrite(log);

    // free(log);

    fprintf(logFile, GetCurrentDateTime());
    vfprintf(logFile, formatLog, args);

    va_end(args);
}

int LogFinish()
{
    LogWriteLine("Log Finished");
    
    if (logFile)
        fclose(logFile);

    return (logFile == NULL);
}

char* GetCurrentDateTime()
{
    time_t t = time(0);
    struct tm* now = localtime(&t);

    char* timeNow = malloc(sizeof(char) * 21);

    sprintf(timeNow, "[%d-%d-%d;%dh%dm%ds]", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);

    return timeNow;
}
