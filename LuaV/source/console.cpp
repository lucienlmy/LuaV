#include "console.h"

FILE* consoleOutput;

void consoleInitialize()
{
    if (!AllocConsole())
    {
        return;
    }

    SetConsoleTitle(L"LuaV Development Console");
    
    freopen_s(&consoleOutput, "CONOUT$", "w", stdout);
    std::cout.clear();

    std::cout << "[PLUGIN] Console initialized." << std::endl << std::endl;
}

void consoleTerminate()
{
    if (consoleOutput)
    {
        fclose(consoleOutput);
        consoleOutput = nullptr;
    }

    FreeConsole();
}

void toggleConsole()
{
    if (consoleOutput)
    {
        consoleTerminate();
    }
    else
    {
        consoleInitialize();
    }
}