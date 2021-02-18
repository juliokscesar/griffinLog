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
    jkscLog::Init("test_log.log");

    std::string name;
    std::cout << "What is your name?\n";
    std::cin >> name;

    // Write with no \n at the end
    jkscLog::Write("Hello\n");

    // Write with \n at the end
    jkscLog::WriteLine("Hello " + name);
    
    // Write a formatted string
    jkscLog::WriteFormatted("Hello %s this is a formatted string from %d\n", "you", 2021);

    jkscLog::Finish();
    return 0;
}