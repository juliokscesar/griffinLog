# jksc Logging Lib - A Simple Logging Library for C/C++
jksc Logging Lib is a simple logging library just to include the basics of logging info to a file, what you could simply do with no library, but jksc helps by having no need to write every single time.

## Attention
jsksc Logging Lib literally only includes the basics - Initiating, Writing and Finishing (and a function to get the datetime).

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
Just `#include "Log.h"` (C) or `#include "Log.hpp"` (C++) in your code and add Log.c (C) or Log.cpp (C++) to compile with your project. C++ files includes the log as a class, with automatic optional init on jkscLog constructor and automatic finish on its destructor.

## Example Code
### C
```c
#include "Log.h"

int main()
{
    // Initiate log with custom name
    // if (!LogInitCustom("test_log.log"))
        // return 1;

    // Initiate log with default name (logfile.log)
    if (!LogInit())
        return 1;

    // Write line with \n at the end
    LogWriteLine("testing c log line");

    // Write line with no \n at the end
    LogWrite("testing c log\n");

    // Write a formatted string to the file (like fprintf)
    LogWriteF("testing c log %s", "with formatted strings\n");

    LogFinish();
    return 0;
}
```

### C++
```cpp
#include "Log.hpp"

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
```
