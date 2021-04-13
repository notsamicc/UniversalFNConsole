#define _CRT_SECURE_NO_WARNINGS

#include "console.h"

DWORD WINAPI Main(LPVOID param)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    printf("Universal Fortnite console unlocker\n");
    double EngineVersion = Util::GetEngineVersion();
    double FortniteVersion = Util::GetFortniteVersion();
    std::cout << "Engine version: " << EngineVersion << std::endl;
    std::cout << "Fortnite version: " << FortniteVersion << std::endl;

    EnableConsole(EngineVersion, FortniteVersion);
    printf("Console enabled\n\n");

    return NULL;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, hModule, 0, 0);
        break;
    }
    return TRUE;
}

