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

#ifndef GRIFFIN_LOG_H
#define GRIFFIN_LOG_H

/* GRIFFIN LOG PLATFORM DEFINITIONS */
#if defined(WIN32) || defined(_WIN32)
    #define GRIFFIN_LOG_WIN32
#else
    #if defined(__linux__) && !defined(__ANDROID__)
        #define GRIFFIN_LOG_LINUX
    #else
        #error GRIFFIN LOG ONLY SUPPORTS WINDOWS AND LINUX
    #endif // __linux__ && !__ANDROID__
#endif // WIN32 || _WIN32


/* GRIFFIN_LOG_API_C DEFINITION */
#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
    #ifdef __cplusplus
        #define GRIFFIN_LOG_API_C __attribute__ ((__cdecl__))
    #else
        #define GRIFFIN_LOG_API_C
    #endif // __cplusplus
#elif defined(_MSC_VER) || (defined(__MINGW32__) || defined(__MINGW64__))
    #define GRIFFIN_LOG_API_C __cdecl
#endif // __GNUC__ || __GNUG__ || __clang__

/* MUST DEFINE _CRT_SECURE_NO_WARNINGS ON MSVC (VISUAL STUDIO) */
#ifdef _MSC_VER
    #ifndef _CRT_SECURE_NO_WARNINGS
        #error _CRT_SECURE_NO_WARNINGS not defined
    #endif // !_CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

/* PLATFORM SPECIFIC CONSOLE COLOR DEFINITION */
#if defined(GRIFFIN_LOG_WIN32)
    typedef DWORD GRIFFIN_COLOR;

    #define GRIFFIN_COLOR_RED       0x0c
    #define GRIFFIN_COLOR_GREEN     0x0a
    #define GRIFFIN_COLOR_BLUE      0x09
    #define GRIFFIN_COLOR_YELLOW    0x0e
    #define GRIFFIN_COLOR_BLACK_RED 0xc0
#elif defined(GRIFFIN_LOG_LINUX)
    typedef char* GRIFFIN_COLOR;

    // ANSI escape sequences for UNIX systems
    #define GRIFFIN_COLOR_RED       "\x1b[31;1;1m"
    #define GRIFFIN_COLOR_GREEN     "\x1b[32;1;1m"
    #define GRIFFIN_COLOR_BLUE      "\x1b[34;1;1m"
    #define GRIFFIN_COLOR_YELLOW    "\x1b[38;2;255;255;1;1m"
    #define GRIFFIN_COLOR_BLACK_RED "\x1b[38;2;0;0;0;48;2;255;0;0;1;1m"
    #define GRIFFIN_COLOR_RESET     "\x1b[0m"
#endif // WIN32 || _WIN32

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define grflog_info(...) grflog_write_level(INFO, __VA_ARGS__)
#define grflog_debug(...) grflog_write_level(DEBUG, __VA_ARGS__)
#define grflog_warn(...) grflog_write_level(WARN, __VA_ARGS__)
#define grflog_critical(...) grflog_write_level(CRITICAL, __VA_ARGS__)
#define grflog_fatal(...) grflog_write_level(FATAL, __VA_ARGS__)

enum LogLevel
{
    INFO     = 0,
    DEBUG    = 1,
    WARN     = 2,
    CRITICAL = 3,
    FATAL    = 4
};

int GRIFFIN_LOG_API_C grflog_init(const char* log_file_name);

void GRIFFIN_LOG_API_C grflog_write_level(uint32_t log_level, const char* log_fmt, ...);

int GRIFFIN_LOG_API_C grflog_finish(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // JKSCLOG_H
