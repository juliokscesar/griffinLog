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
    jkscLog::Write("Hello, ");

    // Write with \n at the end
    jkscLog::WriteLine(name);

    jkscLog::Finish();
    return 0;
}