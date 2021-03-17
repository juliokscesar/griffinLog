# jkscLog - A Simple Logging Library for C/C++
jkscLog is a simple logging library just to include the basics of logging info to a file, what you could simply do with no library, but jksc helps by having no need to write every single time.

## Attention
jkscLog literally only includes the basics - Initiating, Writing (Info, Debug, Warning, Critical, Fatal) and Finishing (and a function to get the datetime).

## Getting Started
To use jkscLib, you only need to clone the repository or download the needed files for your programming language. **THIS IS NOT AN ADVANCED LIBRARY, ONLY SOMETHING I WROTE TO USE ON PERSONAL PROJECTS**.
Clone the repository with `git clone https://github.com/juliokscesar/jkscLog.git`

### Requirements
#### C
- jkscLog.h
- jkscLog.c

#### C++ (files are in cpp folder)
- jkscLog.hpp
- jkscLog.cpp \n
**IT IS STRONGLY ADVISED TO NOT USE C++ FILES CURRENTLY AS IT NEEDS TO BE ENTIRELY REFACTORED. IF YOU ARE GOING TO USE C++, USE C FILES**

## Building
### Windows
- Using the source code 
    - Just `#include "jkscLog.h"` (C) or `#include "jkscLog.hpp"` (C++) in your code and add jkscLog.c (C) or jkscLog.cpp (C++) to compile with your project. C++ files includes the log in a namespace.
- Using Static Library
    - Requirements: CMake >= 3.9 and MinGW or Visual Studio.
    - Open PowerShell on the repository root folder and type `mkdir build`, `cd build`
        - Visual Studio: `cmake -G "Viual Studio [version] -A [arch] ..` and define `_CRT_SECURE_NO_WARNINGS` on your project.
        - MinGW: `cmake -G "MinGW Makefiles" ..`
    - Add the library path to your project and link the library.

### Linux
- Using the source code
    - Just `#include "jkscLog.h"` (C) or `#include "jkscLog.hpp"` (C++) in your code and add jkscLog.c (C) or jkscLog.cpp (C++) to compile with your project. C++ files includes the log in a namespace.
- Using Static Library
    - Requirements: CMake >= 3.9, GCC and G++.
    - Open a terminal on the repository root folder and execute `mkdir build && cd build && cmake --build .`
    - Add the library path to your project and link the library.

## Example Code
### C
```c
#include "jkscLog.h"

int main()
{
    // Initiate log with name passed as argument
    if (!jkscLogInit("your_log_file.log"))
        return 1;

    // Info logging
    jkscLogInfo("hello my name is %s how are you today?", "Julio");

    // Debug logging
    jkscLogDebug("hello this is a %s debug message in %d", "formatted", 2021);

    // Warn Logging
    jkscLogWarn("Warning! This is a log warning to you %s", "user");

    // Critical logging
    jkscLogCritical("Critical error! Find out today in %d", 2021);

    // Fatal logging
    jkscLogFatal("Fatal error! Your pc will die, %s", "joking");

    jkscLogFinish();
    return 0;
}
```

### C++
```cpp
#include "jkscLog.hpp"

int main()
{
    // Initiate the log with default name ("logfile.log")
    // jkscLog::Init();

    // Initiate the log with custom name
    if (!jkscLog::Init("log_cpp.log"))
        return -1;

    // Write log info
    jkscLog::Info("This is an info log with %s", "formatted strings");
    
    // Write log debug
    jkscLog::Debug("This is a debug log with %s with color %s written in %d", "formatted strings", "green", 2021);

    // Write log warning
    jkscLog::Warn("This is a warning log in %d", 2020 + 1);
    
    // Write log critical
    jkscLog::Critical("Critical logging hello %s", "user");

    // Finish the log
    jkscLog::Finish();

    return 0;
}
```
