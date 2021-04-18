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

#define ASSERT_LOG_INIT_WRITING() if(!log_file) grflog_error_callback(1)
#define ASSERT_LOG_INIT_FINISHING() if (!log_file) grflog_error_callback(-1)

void GRIFFIN_LOG_API_C grflog_error_callback(int err)
{
    switch (err)
    {
        case -1:
            fprintf(stderr, "griffinLog Error Callback code -1: Trying to finish not initiated log\n");
            break;

        case 1:
            fprintf(stderr, "griffinLog Error Callback code 1: Trying to write to not initiated log\n");
            break;
    }

    exit(EXIT_FAILURE);
}

#if defined(GRIFFIN_LOG_WIN32)
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

#endif // GRIFFIN_LOG_WIN32

void GRIFFIN_LOG_API_C create_log_dir(void)
{
    #if defined(GRIFFIN_LOG_WIN32)
    CreateDirectoryA("logs", NULL);
    #else
    mkdir("./logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif // GRIFFIN_LOG_WIN32
}

char* GRIFFIN_LOG_API_C get_current_datetime(void)
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    char* datetime = calloc(20, sizeof(char));
    strftime(datetime, 20, "%Y-%m-%d %H:%M:%S", now);

    return datetime;
}

const char* get_loglvl_str(uint32_t lvl)
{
    static const char* levels[] = { "INFO", "DEBUG", "WARN", "CRITICAL", "FATAL" };
    return levels[lvl];
}

const GRIFFIN_COLOR get_loglvl_color(uint32_t lvl)
{
    static const GRIFFIN_COLOR level_colors[] = { GRIFFIN_COLOR_BLUE, GRIFFIN_COLOR_GREEN, GRIFFIN_COLOR_YELLOW, GRIFFIN_COLOR_RED, GRIFFIN_COLOR_BLACK_RED };
    return level_colors[lvl];
}

static FILE* log_file;
int GRIFFIN_LOG_API_C grflog_init(const char* log_file_name)
{
    if (!log_file)
    {
        create_log_dir();

        char log_file_path[256] = "logs/";
        strncat(log_file_path, log_file_name, sizeof(log_file_path) - strlen(log_file_name));

        log_file = fopen(log_file_path, "w");
    }

    grflog_info("Log Intiated");
    return !(log_file == NULL);
}

void GRIFFIN_LOG_API_C grflog_write_level_console(uint32_t log_lvl, const char* log, const char* datetime)
{
    const char* lvl_str = get_loglvl_str(log_lvl);
    const GRIFFIN_COLOR lvl_color = get_loglvl_color(log_lvl);

    #if defined(GRIFFIN_LOG_WIN32)

    printf("[%s] [", datetime);

    WORD attributes;
    SetConsoleColor(&attributes, lvl_color);
    printf("%s", lvl_str);
    ResetConsoleColor(attributes);

    printf("] %s\n", log);

    #elif defined(GRIFFIN_LOG_LINUX)

    printf("[%s] [%s%s%s] %s\n", datetime, lvl_color, lvl_str, GRIFFIN_COLOR_RESET, log);

    #endif // GRIFFIN_LOG_WIN32
}

void GRIFFIN_LOG_API_C grflog_write_level_file(uint32_t log_lvl, const char* log, const char* datetime)
{
    fprintf(log_file, "[%s] [%s] %s\n", datetime, get_loglvl_str(log_lvl), log);
}

void GRIFFIN_LOG_API_C grflog_write_level(uint32_t log_lvl, const char* log_fmt, ...)
{
    ASSERT_LOG_INIT_WRITING();

    const size_t log_size = strlen(log_fmt) + 256;
    char* log = malloc(sizeof(char) * log_size);

    va_list vaArgs;
    va_start(vaArgs, log_fmt);
    vsnprintf(log, log_size - 1, log_fmt, vaArgs);
    va_end(vaArgs);

    char* datetime = get_current_datetime();

    grflog_write_level_console(log_lvl, log, datetime);
    grflog_write_level_file(log_lvl, log, datetime);

    free(datetime);
    free(log);
}

int GRIFFIN_LOG_API_C grflog_finish(void)
{
    ASSERT_LOG_INIT_FINISHING();

    grflog_info("Log Finished");
    fclose(log_file);
    return (log_file == NULL);
}
