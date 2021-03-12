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

static FILE *logFile;

int LogInit()
{
    if (!logFile)
        logFile = fopen("logfile.log", "w");

    LogInfo("Log Intiated");
    return !(logFile == NULL);
}

int LogInitCustom(const char* fileName)
{
    if (!logFile)
        logFile = fopen(fileName, "w");

    LogInfo("Log Initiated");
    return !(logFile == NULL);
}

void LogWriteMode(int logMode, char *log)
{
    if (!logFile)
        return;

    char *dateTime = GetCurrentDateTime();
    char mode[9];
    char modeColor[23];

    switch (logMode)
    {
        case INFO:
            strcpy(mode, "INFO");
            strcpy(modeColor, ANSI_COLOR_BLUE);
            break;
	
    	case DEBUG:
	    strcpy(mode, "DEBUG");
	    strcpy(modeColor, ANSI_COLOR_GREEN);
	    break;	    

        case WARN:
            strcpy(mode, "WARN");
            strcpy(modeColor, ANSI_COLOR_YELLOW);
            break;
        
        case CRITICAL:
            strcpy(mode, "CRITICAL");
            strcpy(modeColor, ANSI_COLOR_RED);
            break;

        default:
            fprintf(stderr, "Invalid log mode\n");
            return;
    }

    fprintf(logFile, "[%s] [%s] %s\n", dateTime, mode, log);

    printf("[%s] [%s%s%s] %s\n", dateTime, modeColor, mode, ANSI_COLOR_RESET, log);

    free(dateTime);
    free(log);
}

void LogInfo(const char *logInfo, ...)
{
    va_list args;
    va_start(args, logInfo);

    const int logSize = (int)strlen(logInfo) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logInfo, args);

    LogWriteMode(INFO, log);

    va_end(args);
}

void LogDebug(const char *logDebug, ...)
{
	va_list args;
	va_start(args, logDebug);

	const int logSize = (int)strlen(logDebug) + 256;
	char *log = malloc(sizeof(char) * logSize);
	
	vsnprintf(log, logSize - 1, logDebug, args);

	LogWriteMode(DEBUG, log);

	va_end(args);
}

void LogWarn(const char *logWarn, ...)
{
    va_list args;
    va_start(args, logWarn);

    const int logSize = (int)strlen(logWarn) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logWarn, args);

    LogWriteMode(WARN, log);

    va_end(args);
}

void LogCritical(const char *logCritical, ...)
{
    va_list args;
    va_start(args, logCritical);

    const int logSize = (int)strlen(logCritical) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logCritical, args);

    LogWriteMode(CRITICAL, log);

    va_end(args);
}

int LogFinish()
{
    LogInfo("Log Finished");
    
    if (logFile)
        fclose(logFile);

    return (logFile == NULL);
}

char *GetCurrentDateTime()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    char *dateTime = malloc(sizeof(char) * 20);
    strftime(dateTime, 20, "%Y-%m-%d %H:%M:%S", now);

    return dateTime;
}
