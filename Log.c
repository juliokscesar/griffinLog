#include "Log.h"

FILE* logFile;

int LogInit()
{
    if (!logFile)
        logFile = fopen("logfile.log", "w");

    return !(logFile == NULL);
}

void LogWrite(const char* logInfo)
{
    fprintf(logFile, "[%s] %s", GetCurrentDateTime(), logInfo);
}

void LogWriteLine(const char* logInfo)
{
    fprintf(logFile, "[%s] %s\n", GetCurrentDateTime(), logInfo);
}

char* GetCurrentDateTime()
{
    time_t t = time(0);
    struct tm* now = localtime(&t);

    char* timeNow = malloc(sizeof(char) * 255);

    sprintf(timeNow, "%d-%d-%d;%dh%dm%ds", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);

    return timeNow;
}

int LogFinish()
{
    if (logFile)
        fclose(logFile);

    return (logFile == NULL);
}