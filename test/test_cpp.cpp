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
    // Create new logger
    jkscLog logger;

    // Create new logger already initializing it with custom name
    // jkscLog logger("log_name.log");

    // Initiate with default name (jkscLogFile.log)
    // logger.Init();

    // Initiate with custom name
    if (!logger.Init("logfile_name.log"))
        return 1;

    // Write with no \n at the end
    logger.Write("Hello testing write\n");

    // Write with \n at the end
    logger.WriteLine("Now testing with breakline at the end");
    
    // Write a formatted string
    logger.WriteF("Hello %s this is a formatted string from %d\n", "you", 2021);

    // Call logger.Finish() method to close it
    logger.Finish();
    // It is called on the object destructor, so it is optional

    return 0;
}