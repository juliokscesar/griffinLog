# griffinLog - A Simple Logging Library for C
griffinLog is a simple logging library just to include the basics of logging info to a file, what you could simply do with no library, but helps by having no need to write every single time.

## Attention
griffinLog literally only includes the basics - Initiating, Writing (Info, Debug, Warning, Critical, Fatal) and Finishing (and a function to get the datetime).

## Getting Started
To use griffin, you only need to clone the repository or download the needed files for your programming language. **THIS IS NOT AN ADVANCED LIBRARY, ONLY SOMETHING I WROTE TO USE ON PERSONAL PROJECTS**.
Clone the repository with `git clone https://github.com/juliokscesar/griffinLog.git`

### Requirements
- griffinLog.h
- griffinLog.c
- CMake (if you are going to use the static library)

**This library can be used with C++ as well.**

## Building
### Windows
- Using the source code 
    - Just `#include "griffinLog.h"` in your code and add griffinLog.c to compile with your project. This library can be used with C++ as well.
- Using Static Library
    - Requirements: CMake >= 3.9 and MinGW or Visual Studio.
    - Open PowerShell on the repository root folder and execute `mkdir build; cd build`
        - Visual Studio: `cmake -G "Viual Studio [version]" -A [arch] ..` 
        - MinGW: `cmake -G "MinGW Makefiles" ..`
    - Execute `cmake --build .`
    - Add the library path to your project and link the library.

### Linux
- Using the source code
    - Just `#include "griffinLog.h"` in your code and add griffinLog.c to compile with your project. This library can be used with C++ as well.
- Using Static Library
    - Requirements: CMake >= 3.9, GCC and G++.
    - Open a terminal on the repository root folder and execute `mkdir build && cd build`
    - Run: `cmake .. && cmake --build .`
    - Add the library path to your project and link the library.

## Example Code
```
#include "griffinLog.h"

int main(void)
{
    // Info logging
    grflog_info("hello my name is %s how are you today?", "Julio");

    // Debug logging
    grflog_debug("hello this is a %s debug message in %d", "formatted", 2021);

    // Warn Logging
    grflog_warn("Warning! This is a log warning to you %s", "user");

    // Initialize file logging
    if (!grflog_init_file("logfilename.log"))
        return -1;
    grflog_info("From now, it will log to a file as well!");

    // Critical logging
    grflog_critical("Critical error! Find out today in %d", 2021);

    // Fatal logging
    grflog_fatal("Fatal error! Your pc will die, but it is %s", "just a joke");

    // Finish file logging (needs to be called if you initialized it)
    grflog_finish_file();
    return 0;
}
```
