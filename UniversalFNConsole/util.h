#include <fstream>
#include <inttypes.h>
#include <Windows.h>
#include <psapi.h>
#include <stdio.h>
#include <iostream>
#include <string>

template<class T>
struct TArray
{
    T* Data;
    int Count;
    int Max;
};

struct FString : public TArray<wchar_t>
{
    inline const wchar_t* c_str() const
    {
        return Data;
    }

    std::string ToString() const
    {
        const auto length = std::wcslen(Data);

        std::string str(length, '\0');

        std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

        return str;
    }
};

void* Result;

typedef FString* (__fastcall* fGetEngineVersion)
(
    void* Result
);

static fGetEngineVersion GetEngineVersion;

std::string text;

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
    static double EngineVersion()
    {
        std::string EngineVersion = text.substr(0, 4);

        return std::stod(EngineVersion);
    }

    static double FortniteVersion()
    {
        std::string FortniteVersion = text.substr(34, 4);

        return std::stod(FortniteVersion);
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