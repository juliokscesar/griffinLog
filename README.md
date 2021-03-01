# jksc Logging Lib - A Simple Logging Library for C/C++
jksc Logging Lib is a simple logging library just to include the basics of logging info to a file, what you could simply do with no library, but jksc helps by having no need to write every single time.

## Attention
jsksc Logging Lib literally only includes the basics - Initiating, Writing (Info, Warning, Critical) and Finishing (and a function to get the datetime).

## Getting Started
To use the jksc Logging Lib, you only need to clone the repository or download the needed files for your programming language. **THIS IS NOT AN ADVANCED LIBRARY, ONLY SOMETHING I WROTE TO USE ON PERSONAL PROJECTS**.
Clone the repository with `git clone https://github.com/juliokscesar/jkscLogLib.git`

### Requirements
#### C
- Log.h
- Log.c

#### C++ (files are in cpp folder)
- Log.hpp
- Log.cpp

## Building
Just `#include "Log.h"` (C) or `#include "Log.hpp"` (C++) in your code and add Log.c (C) or Log.cpp (C++) to compile with your project. C++ files includes the log in a namespace.

## Example Code
### C
```c
#include "Log.h"

int main()
{
    // Initiate log with custom name
    // if (!LogInitCustom("testlog.log"))
        // return 1;

    // Initiate log with default name (logfile.log)
    if (!LogInit())
        return 1;

    // Info logging
    LogInfo("hello my name is %s how are you today?", "Julio");

    // Warn Logging
    LogWarn("Warning! This is a log warning to you %s", "user");

    // Critical logging
    LogCritical("Critical error! Find out today in %d", 2021);

    LogFinish();
    return 0;
}
```

### C++
```cpp
#include "Log.hpp"

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
```
