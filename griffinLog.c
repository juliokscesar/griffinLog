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

#include "griffinLog.h"

#define ASSERT_LOG_INIT_WRITING() if(!log_file) grfLogErrorCallback(1)
#define ASSERT_LOG_INIT_FINISHING() if (!log_file) grfLogErrorCallback(-1)

void GRIFFIN_LOG_API_C grfLogErrorCallback(int err)
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

void GRIFFIN_LOG_API_C SetConsoleColor(WORD* Attributes, DWORD Color)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Color);
}

void GRIFFIN_LOG_API_C ResetConsoleColor(WORD Attributes)
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

static FILE *log_file;

static const char *modes[] = { "INFO", "DEBUG", "WARN", "CRITICAL", "FATAL" };
static const COLOR_ARRAY colors[] = { COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW, COLOR_RED, COLOR_BLACK_RED };

void GRIFFIN_LOG_API_C create_log_dir(void)
{
    #if defined(WIN32) || defined(_WIN32)
    CreateDirectoryA("logs", NULL);
    #else
    mkdir("./logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif // WIN32 || _WIN32
}

char* GRIFFIN_LOG_API_C get_current_datetime(void)
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    char *datetime = calloc(20, sizeof(char));
    strftime(datetime, 20, "%Y-%m-%d %H:%M:%S", now);

    return datetime;
}

int GRIFFIN_LOG_API_C grf_log_init(const char *log_file_name)
{
    if (!log_file)
    {
        create_log_dir();

        char log_file_path[256] = "logs/";
        strncat(log_file_path, log_file_name, sizeof(log_file_path) - strlen(log_file_name));

        log_file = fopen(log_file_path, "w");
    }

    grf_log_info("Log Intiated");
    return !(log_file == NULL);
}

void GRIFFIN_LOG_API_C grf_log_write_mode_console(int log_mode, const char *log, const char *datetime)
{
    #if defined(WIN32) || defined(_WIN32)

    printf("[%s] [", datetime);

    WORD attributes;
    SetConsoleColor(&attributes, colors[log_mode]);
    printf("%s", modes[log_mode]);
    ResetConsoleColor(attributes);

    printf("] %s\n", log);

    #else

    printf("[%s] [%s%s%s] %s\n", datetime, colors[log_mode], modes[log_mode], COLOR_RESET, log);

    #endif // WIN32 || _WIN32
}

void GRIFFIN_LOG_API_C grf_log_write_mode_file(int log_mode, const char *log, const char *datetime)
{
    fprintf(log_file, "[%s] [%s] %s\n", datetime, modes[log_mode], log);
}

void GRIFFIN_LOG_API_C grf_log_write_mode(int log_mode, const char *log_fmt, ...)
{
    ASSERT_LOG_INIT_WRITING();

    const size_t log_size = strlen(log_fmt) + 256;
    char *log = malloc(sizeof(char) * log_size);

    va_list vaArgs;
    va_start(vaArgs, log_fmt);
    vsnprintf(log, log_size - 1, log_fmt, vaArgs);
    va_end(vaArgs);

    char *datetime = get_current_datetime();

    grf_log_write_mode_console(log_mode, log, datetime);
    grf_log_write_mode_file(log_mode, log, datetime);

    free(datetime);
    free(log);
}

int GRIFFIN_LOG_API_C grf_log_finish(void)
{
    ASSERT_LOG_INIT_FINISHING();

    grf_log_info("Log Finished");
    fclose(log_file);
    return (log_file == NULL);
}

