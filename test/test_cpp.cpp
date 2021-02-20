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
    // Initiate with default name
    // Log::Init();

    // Initiate with custom name
    jkscLog::Init("test_log.log");

    std::string name;
    std::cout << "What is your name?\n";
    std::cin >> name;

    // Write with no \n at the end
    jkscLog::Write("Hello\n");

    // Write with \n at the end
    jkscLog::WriteLine("Hello " + name);
    
    // Write a formatted string
    jkscLog::WriteF("Hello %s this is a formatted string from %d\n", "you", 2021);

    jkscLog::Finish();
    return 0;
}