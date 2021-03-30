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

#include "../griffinLog.h"

/* 
Compile with:
gcc test_c.c ../griffinLog.c
*/

int main()
{
    // Initiate log with given file name
    if (!grf_log_init("testc_log.log"))
        return 1;

    // Info logging
    grf_log_info("hello my name is %s how are you today?", "Julio");

    // Debug logging
    grf_log_debug("hello this is a %s debug message in %d", "formatted", 2021);

    // Warn Logging
    grf_log_warn("Warning! This is a log warning to you %s", "user");

    // Critical logging
    grf_log_critical("Critical error! Find out today in %d", 2021);

    // Fatal logging
    grf_log_fatal("Fatal error! Your pc will die, but it is %s", "just a joke");

    grf_log_finish();
    return 0;
}
