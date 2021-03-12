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

/*
Compile With:
g++ -o benchmark benchmark.cpp ../cpp/Log.cpp
*/

#include <stdio.h>

#ifdef _WIN32

#include <windows.h>

#else

#include <sys/time.h>
#include <sys/resource.h>

#endif // _WIN32

#include "../Log.h"


double get_time()
{
    #ifdef _WIN32
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart/(double)f.QuadPart;
    #else
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
    #endif // _WIN32
}

int main()
{
    double start = get_time();

    LogInitCustom("benchmarking_log_C.log");

    LogInfo("Writing INFO to log");
    LogWarn("Warning! Log warn benchmarking test");
    LogCritical("Testing critical log %s", "on benchmark.c");

    LogFinish();

    double end = get_time();

    printf("Duration = %fms\n", (end - start) * 1000);
    return 0;
}