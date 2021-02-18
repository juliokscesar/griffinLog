/*
Compile With:
g++ -o benchmark benchmark.cpp ../cpp/Log.cpp
*/

#include <iostream>

#ifdef _WIN32

#include <windows.h>

#else

#include <sys/time.h>
#include <sys/resource.h>

#endif // _WIN32

#include "../cpp/Log.hpp"


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
    #ifdef _WIN32
    double start = get_time();
    #endif // _WIN32

    jkscLog::Init("benchmark_log.log");

    jkscLog::Write("First message\n");
    jkscLog::WriteLine("Seconds Message");
    jkscLog::WriteFormatted("%s message (%d)", "Third", 3);

    jkscLog::Finish();

    #ifdef _WIN32
    double end = get_time();
    #endif // _WIN32

    std::cout << "Duration = " << (end - start) * 1000 << " milliseconds \n";
    return 0;
}