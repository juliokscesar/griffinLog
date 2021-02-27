#include <iostream>
#include <stdexcept>

#include "../cpp/Log.hpp"

/* 
Compile with:
g++ test_exception.cpp ../cpp/Log.cpp
*/

int main()
{
    jkscLog logger;
    try
    {
        logger.Write("Hello\n");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}