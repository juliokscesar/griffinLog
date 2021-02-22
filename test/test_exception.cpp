#include <iostream>
#include <stdexcept>

#include "../cpp/Log.hpp"

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