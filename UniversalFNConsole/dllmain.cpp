#define _CRT_SECURE_NO_WARNINGS

#include "console.h"

DWORD WINAPI Main(LPVOID param)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    uintptr_t GetEngineVersionAddress = Util::FindPattern("\x40\x53\x48\x83\xEC\x20\x48\x8B\xD9\xE8\x00\x00\x00\x00\x48\x8B\xC8\x41\xB8\x04\x00\x00\x00\x48\x8B\xD3", "xxxxxxxxxx????xxxxxxxxxxxx");
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