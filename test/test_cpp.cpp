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

#include "../cpp/Log.hpp"

/* 
Compile with:
g++ test_cpp.cpp ../cpp/Log.cpp
*/

int main()
{
    // Initiate the log with default name ("logfile.log")
    // jkscLog::Init();

    // Initiate the log with custom name
    if (!jkscLog::Init("log_cpp.log"))
        return -1;

    // Write log info
    jkscLog::Info("This is a info log with %s", "formatted strings");

    // Write log warning
    jkscLog::Warn("This is a warning log in %d", 2020 + 1);
    
    // Write log critical
    jkscLog::Critical("Critical logging hello %s", "user");

    // Finish the log
    jkscLog::Finish();

    return 0;
}