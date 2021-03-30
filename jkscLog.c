/*
* MIT License
* 
* Copyright (c) 2021 juliokscesar
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "jkscLog.h"

#define ASSERT_LOG_INIT_WRITING() if(!logFile) jkscLogErrorCallback(1)
#define ASSERT_LOG_INIT_FINISHING() if (!logFile) jkscLogErrorCallback(-1)

void JKSCLOG_API_C jkscLogErrorCallback(int err)
{
    switch (err)
    {
        case -1:
            fprintf(stderr, "Log Error Callback code -1: Trying to finish not initiated log\n");
            break;

        case 1:
            fprintf(stderr, "Log Error Callback code 1: Trying to write to not initiated log\n");
            break;
    }

    exit(EXIT_FAILURE);
}

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>

void JKSCLOG_API_C SetConsoleColor(WORD* Attributes, DWORD Color)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Color);
}

void JKSCLOG_API_C ResetConsoleColor(WORD Attributes)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}

#else

#include <sys/stat.h>

#endif // WIN32 || _WIN32

#if defined(WIN32) || defined(_WIN32)
    typedef DWORD COLOR_ARRAY;
#else
    typedef char* COLOR_ARRAY;
#endif // WIN32 || _WIN32

static FILE *logFile;

static const char *modes[] = { "INFO", "DEBUG", "WARN", "CRITICAL", "FATAL" };
static const COLOR_ARRAY colors[] = { COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW, COLOR_RED, COLOR_BLACK_RED };

void JKSCLOG_API_C createLogDir(void)
{
    #if defined(WIN32) || defined(_WIN32)
    CreateDirectoryA("logs", NULL);
    #else
    mkdir("./logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif // WIN32 || _WIN32
}

char* JKSCLOG_API_C GetCurrentDateTime(void)
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    char *dateTime = calloc(20, sizeof(char));
    strftime(dateTime, 20, "%Y-%m-%d %H:%M:%S", now);

    return dateTime;
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

void JKSCLOG_API_C jkscLogWriteModeConsole(int logMode, const char *log, const char *dateTime)
{
    #if defined(WIN32) || defined(_WIN32)

    printf("[%s] [", dateTime);

    WORD attributes;
    SetConsoleColor(&attributes, colors[logMode]);
    printf("%s", modes[logMode]);
    ResetConsoleColor(attributes);

    printf("] %s\n", log);

    #else

    printf("[%s] [%s%s%s] %s\n", dateTime, colors[logMode], modes[logMode], COLOR_RESET, log);

    #endif // WIN32 || _WIN32
}

void JKSCLOG_API_C jkscLogWriteModeFile(int logMode, const char *log, const char *dateTime)
{
    fprintf(logFile, "[%s] [%s] %s\n", dateTime, modes[logMode], log);
}

void JKSCLOG_API_C jkscLogWriteMode(int logMode, const char *logFmt, ...)
{
    ASSERT_LOG_INIT_WRITING();

    const size_t logSize = strlen(logFmt) + 256;
    char *log = malloc(sizeof(char) * logSize);

    va_list vaArgs;
    va_start(vaArgs, logFmt);
    vsnprintf(log, logSize - 1, logFmt, vaArgs);
    va_end(vaArgs);

    char *dateTime = GetCurrentDateTime();

    jkscLogWriteModeConsole(logMode, log, dateTime);
    jkscLogWriteModeFile(logMode, log, dateTime);

    free(dateTime);
    free(log);
}

int JKSCLOG_API_C jkscLogFinish(void)
{
    ASSERT_LOG_INIT_FINISHING();

    jkscLogInfo("Log Finished");
    fclose(logFile);
    return (logFile == NULL);
}

