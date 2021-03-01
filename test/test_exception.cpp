#include <iostream>
#include <stdexcept>

#include "../cpp/Log.hpp"

/* 
Compile with:
g++ test_exception.cpp ../cpp/Log.cpp
*/

int main()
{
    try
    {
        jkscLog::Critical("Trying to log without initiating");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}