#define _CRT_SECURE_NO_WARNINGS

#include "console.h"

DWORD WINAPI Main(LPVOID param)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    uintptr_t GetEngineVersionAddress = Util::FindPattern("x40\x53\x48\x83\xEC\x30\x41\xB9\x00\x00\x00\x00\x0F\xB6\xD9\x44\x38\x0D\x00\x00\x00\x00\x72\x20\x48\x8D\x05\x00\x00\x00\x00\x89\x5C\x24\x28\x4C\x8D\x05\x00\x00\x00\x00\x48\x89\x44\x24\x00\x33\xD2\x33\xC9\xE8\x00\x00\x00\x00", "xxxxxxxx????xxxxxx????xxxxx????xxxxxxx????xxxx?xxxxx????");
    GetEngineVersion = reinterpret_cast<fGetEngineVersion>(GetEngineVersionAddress);
    text = GetEngineVersion(&Result)->ToString().c_str();

    double EngineVersion = Util::EngineVersion();
    double FortniteVersion = Util::FortniteVersion();
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
