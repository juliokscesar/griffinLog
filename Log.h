#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

int LogInit();

// TODO: int LogInit(const char* fileName); -- implement

void LogWrite(const char* logInfo);
void LogWriteLine(const char* logInfo);
void LogWriteF(const char* formatLog, ...);
int LogFinish();

char* GetCurrentDateTime();

#endif // LOG_H
