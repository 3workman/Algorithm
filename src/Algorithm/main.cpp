#include "stdafx.h"

int main(int argc, char* argv[])
{
    LogFile log("log/algorithm", LogFile::DEBUG);
    _LOG_MAIN_(log);

    system("pause");
    return 0;
}