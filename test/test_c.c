#include "../Log.h"

/* 
Compile with:
gcc test_c.c ../Log.h
*/

int main()
{
    if (!LogInit())
        return 1;

    LogWriteLine("testing c log line");
    LogWrite("testing c log");

    LogFinish();

    return 0;
}