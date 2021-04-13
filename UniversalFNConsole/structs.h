#pragma once

struct UObject;

struct UClass;

struct UConsole;

struct UGameViewportClient
{
    char unknown1[0x40];
    UConsole* ViewportConsole;
};

struct UEngine420
{
	char unknown1[0xF8];
	UClass* ConsoleClass;
	char unknown2[0x620];
	UGameViewportClient* GameViewportClient;
};

struct UEngine421
{
	char unknown1[0xF8];
	UClass* ConsoleClass;
	char unknown2[0x621];
	UGameViewportClient* GameViewportClient;
};

struct UEngine4212
{
	char unknown1[0xF8];
	UClass* ConsoleClass;
	char unknown2[0x641];
	UGameViewportClient* GameViewportClient;
};

struct UEngine422
{
	char unknown1[0xF8];
	UClass* ConsoleClass;
	char unknown2[0x648];
	UGameViewportClient* GameViewportClient;
};

struct UEngine423
{
	char unknown1[0xF8];
	UClass* ConsoleClass;
	char unknown2[0x650];
	UGameViewportClient* GameViewportClient;
};

struct UEngine424
{
	char unknown1[0xF8];
	UClass* ConsoleClass;
	char unknown2[0x689];
	UGameViewportClient* GameViewportClient;
};

struct UEngine425
{
	char unknown1[0xF8];
	UClass* ConsoleClass;
	char unknown2[0x6C0];
	UGameViewportClient* GameViewportClient;
};

struct UEngine426
{
	char unknown1[0xF8];
	UClass* ConsoleClass;
	char unknown2[0x688];
	UGameViewportClient* GameViewportClient;
};