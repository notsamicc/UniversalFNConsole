#include <fstream>
#include <inttypes.h>
#include <Windows.h>
#include <psapi.h>
#include <stdio.h>
#include <iostream>
#include <string>

class Util
{
private:
    static bool MaskCompare(PVOID pBuffer, LPCSTR lpPattern, LPCSTR lpMask)
    {
        for (PBYTE value = reinterpret_cast<PBYTE>(pBuffer); *lpMask; ++lpPattern, ++lpMask, ++value)
        {
            if (*lpMask == 'x' && *reinterpret_cast<LPCBYTE>(lpPattern) != *value)
                return false;
        }
        return true;
    }
public:
    static double GetEngineVersion()
    {
        int line = 1;
        std::string path = getenv("localappdata");
        std::ifstream file;
        std::string text;
        std::string engineVersion = "Engine Version: ";

        path += "\\FortniteGame\\Saved\\Logs\\FortniteGame.log";

        file.open(path.c_str());

        while (std::getline(file, text))
        {
            if (text.find(engineVersion, 0) != std::string::npos)
            {
                engineVersion = text.substr(25, 4);
                break;
            }
            else
                line++;
        };
        file.close();

        return std::stod(engineVersion);
    }

    static double GetFortniteVersion()
    {
        int line = 1;
        std::string path = getenv("localappdata");
        std::ifstream file;
        std::string text;
        std::string fortniteVersion = "Fortnite+Release";

        path += "\\FortniteGame\\Saved\\Logs\\FortniteGame.log";

        file.open(path.c_str());

        while (std::getline(file, text))
        {
            if (text.find(fortniteVersion, 0) != std::string::npos)
            {
                fortniteVersion = text.substr(35, 5);
                break;
            }
            else
                line++;
        };
        file.close();
        return std::stod(fortniteVersion);
    }

    static uintptr_t FindPattern(PVOID pBase, DWORD dwSize, LPCSTR lpPattern, LPCSTR lpMask)
    {
        dwSize -= static_cast<DWORD>(strlen(lpMask));
        for (unsigned long index = 0; index < dwSize; ++index)
        {
            PBYTE pAddress = reinterpret_cast<PBYTE>(pBase) + index;
            if (MaskCompare(pAddress, lpPattern, lpMask))
                return reinterpret_cast<uintptr_t>(pAddress);
        }
        return NULL;
    }

    static uintptr_t FindPattern(LPCSTR lpPattern, LPCSTR lpMask)
    {
        MODULEINFO info = { 0 };
        GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));
        return FindPattern(info.lpBaseOfDll, info.SizeOfImage, lpPattern, lpMask);
    }

    static uintptr_t BaseAddress()
    {
        return reinterpret_cast<uintptr_t>(GetModuleHandle(0));
    }
};