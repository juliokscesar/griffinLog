#include "Log.h"

FILE* logFile;

int LogInit()
{
    if (!logFile)
        logFile = fopen("logfile.log", "w");

    LogWriteLine("Log Initiated");
    return !(logFile == NULL);
}

void LogWrite(const char* logInfo)
{
    char* dateTime = GetCurrentDateTime();

    fprintf(logFile, "[%s] %s", dateTime, logInfo);

    free(dateTime);
}

void LogWriteLine(const char* logInfo)
{
    char* dateTime = GetCurrentDateTime();

    fprintf(logFile, "[%s] %s\n", dateTime, logInfo);

    free(dateTime);
}

void LogWriteF(const char* formatLog, ...)
{
    va_list args;
    va_start(args, formatLog);

    const int logSize = (int)strlen(formatLog) + 256;
    char* log = malloc(logSize);

    vsprintf(log, formatLog, args);

    LogWrite(log);

    free(log);
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

    sprintf(timeNow, "%d-%d-%d;%dh%dm%ds", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);

    return timeNow;
}
