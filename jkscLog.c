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

#include "jkscLog.h"

#define ASSERT_LOG_INIT() if (!logFile) return

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>

void SetConsoleColor(WORD* Attributes, DWORD Color)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Color);
}

void ResetConsoleColor(WORD Attributes)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

#endif // WIN32 || _WIN32

static FILE *logFile;

void createLogDir()
{
    #if defined(WIN32) || defined(_WIN32)
    CreateDirectoryA("logs", NULL);
    #else
    system("mkdir -p ./logs");
    #endif // WIN32 || _WIN32
}

int JKSCLOG_API_C jkscLogInit(const char *logFileName)
{
    if (!logFile)
    {
        createLogDir();

        char logFilePath[256] = "logs/";
        strncat(logFilePath, logFileName, sizeof(logFilePath) - strlen(logFileName));

        logFile = fopen(logFilePath, "w");
    }

    jkscLogInfo("Log Intiated");
    return !(logFile == NULL);
}

void JKSCLOG_API_C jkscLogWriteMode(int logMode, char *log)
{
    ASSERT_LOG_INIT();

    char *dateTime = GetCurrentDateTime();
    const char *modes[] = { "INFO", "DEBUG", "WARN", "CRITICAL", "FATAL" };

    jkscLogWriteModeConsole(logMode, modes, log, dateTime);
    jkscLogWriteModeFile(logMode, modes, log, dateTime);

    free(dateTime);
    free(log);
}

void JKSCLOG_API_C jkscLogWriteModeConsole(int logMode, const char *modes[], const char *log, const char *dateTime)
{
    #if defined(WIN32) || defined(_WIN32)

    const DWORD colors[] = { COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW, COLOR_RED, COLOR_BLACK_RED };

    printf("[%s] [", dateTime);

    WORD attributes;
    SetConsoleColor(&attributes, colors[logMode]);
    printf("%s", modes[logMode]);
    ResetConsoleColor(attributes);

    printf("] %s\n", log);

    #else

    const char *colors[] = { COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW, COLOR_RED, COLOR_BLACK_RED };

    printf("[%s] [%s%s%s] %s\n", dateTime, colors[logMode], modes[logMode], COLOR_RESET, log);

    #endif // WIN32 || _WIN32
}

void JKSCLOG_API_C jkscLogWriteModeFile(int logMode, const char *modes[], const char *log, const char *dateTime)
{
    fprintf(logFile, "[%s] [%s] %s\n", dateTime, modes[logMode], log);
}

void JKSCLOG_API_C jkscLogInfo(const char *logInfo, ...)
{
    va_list args;
    va_start(args, logInfo);

    const int logSize = (int)strlen(logInfo) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logInfo, args);

    jkscLogWriteMode(INFO, log);

    va_end(args);
}

void JKSCLOG_API_C jkscLogDebug(const char *logDebug, ...)
{
	va_list args;
	va_start(args, logDebug);

	const int logSize = (int)strlen(logDebug) + 256;
	char *log = malloc(sizeof(char) * logSize);
	
	vsnprintf(log, logSize - 1, logDebug, args);

	jkscLogWriteMode(DEBUG, log);

	va_end(args);
}

void JKSCLOG_API_C jkscLogWarn(const char *logWarn, ...)
{
    va_list args;
    va_start(args, logWarn);

    const int logSize = (int)strlen(logWarn) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logWarn, args);

    jkscLogWriteMode(WARN, log);

    va_end(args);
}

void JKSCLOG_API_C jkscLogCritical(const char *logCritical, ...)
{
    va_list args;
    va_start(args, logCritical);

    const int logSize = (int)strlen(logCritical) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logCritical, args);

    jkscLogWriteMode(CRITICAL, log);

    va_end(args);
}

void JKSCLOG_API_C jkscLogFatal(const char *logFatal, ...)
{
    va_list args;
    va_start(args, logFatal);

    const int logSize = (int)strlen(logFatal) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logFatal, args);

    jkscLogWriteMode(FATAL, log);

    va_end(args);
}

int JKSCLOG_API_C jkscLogFinish()
{
    jkscLogInfo("Log Finished");
    
    if (logFile)
        fclose(logFile);

    return (logFile == NULL);
}

char* JKSCLOG_API_C GetCurrentDateTime()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    char *dateTime = calloc(20, sizeof(char));
    strftime(dateTime, 20, "%Y-%m-%d %H:%M:%S", now);

    return dateTime;
}
