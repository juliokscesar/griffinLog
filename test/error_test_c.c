#include <stdio.h>

#include "../jkscLog.h"

int main()
{
    printf("Error testing jkscLog\n");

    // jkscLogInfo("Writing to not initiated log"); // -> Error writing to not initiated log
    jkscLogFinish(); // -> Error finishing not initiated log

    return 0;
}