# jkscLog - A Simple Logging Library for C
jkscLog is a simple logging library just to include the basics of logging info to a file, what you could simply do with no library, but jksc helps by having no need to write every single time.

## Attention
jkscLog literally only includes the basics - Initiating, Writing (Info, Debug, Warning, Critical, Fatal) and Finishing (and a function to get the datetime).

## Getting Started
To use jkscLib, you only need to clone the repository or download the needed files for your programming language. **THIS IS NOT AN ADVANCED LIBRARY, ONLY SOMETHING I WROTE TO USE ON PERSONAL PROJECTS**.
Clone the repository with `git clone https://github.com/juliokscesar/jkscLog.git`

### Requirements
- jkscLog.h
- jkscLog.c
- CMake (if you are going to use the static library)

**This library can be used with C++ as well.**

## Building
### Windows
- Using the source code 
    - Just `#include "jkscLog.h"` in your code and add jkscLog.c to compile with your project. This library can be used with C++ as well.
- Using Static Library
    - Requirements: CMake >= 3.9 and MinGW or Visual Studio.
    - Open PowerShell on the repository root folder and execute `mkdir build; cd build`
        - Visual Studio: `cmake -G "Viual Studio [version]" -A [arch] ..` 
        - MinGW: `cmake -G "MinGW Makefiles" ..`
    - Execute `cmake --build .`
    - Add the library path to your project and link the library.

### Linux
- Using the source code
    - Just `#include "jkscLog.h"` in your code and add jkscLog.c to compile with your project. This library can be used with C++ as well.
- Using Static Library
    - Requirements: CMake >= 3.9, GCC and G++.
    - Open a terminal on the repository root folder and execute `mkdir build && cd build`
    - Run: `cmake .. && cmake --build .`
    - Add the library path to your project and link the library.

## Example Code
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
