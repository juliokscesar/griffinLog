#include "../Log.h"

/* 
Compile with:
gcc test_c.c ../Log.h
*/

int main()
{
    // Initiate log
    if (!LogInit())
        return 1;

    // Write line with \n at the end
    LogWriteLine("testing c log line");

    // Write line with no \n at the end
    LogWrite("testing c log");

    LogFinish();
    return 0;
}