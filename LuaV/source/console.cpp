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

	// Force a bad state on std::cout to prevent any further output after the console has been terminated
	std::cout.setstate(std::ios_base::badbit);

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