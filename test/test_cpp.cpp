#include "../cpp/Log.hpp"

/* 
Compile with:
g++ test_cpp.cpp ../cpp/Log.cpp
*/

int main()
{
    // Initiate with default name
    // Log::Init();

    // Initiate with custom name
    Log::Init("test_log.log");

    std::string name;
    std::cout << "What is your name?\n";
    std::cin >> name;

    // Write with no \n at the end
    Log::Write("Hello, ");

    // Write with \n at the end
    Log::WriteLine(name);

    Log::Finish();
    return 0;
}