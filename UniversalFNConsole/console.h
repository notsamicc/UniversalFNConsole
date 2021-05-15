#include "util.h"
#include "structs.h"

typedef UObject* (__fastcall* fStaticConstructObject_Internal)(
	UClass* Class,
	UObject* InOuter,
	void* Name,
	int SetFlags,
	unsigned int InternalSetFlags,
	UObject* Template,
	bool  bCopyTransientsFromClassDefaults,
	void* InstanceGraph,
	bool  bAssumeTemplateIsArchetype
);
static fStaticConstructObject_Internal StaticConstructObject_Internal;

static UConsole* ConstructConsole(UClass* ConsoleClass, UObject* outer)
{
	return reinterpret_cast<UConsole*>(StaticConstructObject_Internal(ConsoleClass, outer, nullptr, 0, 0, nullptr, false, nullptr, false));
}

static void EnableConsole(double EngineVersion, double FortniteVersion)
{
	static uintptr_t SCOIOffset = 0;
	unsigned long long SCOIAddress = 0;

	static uintptr_t GEngineOffset = 0;
	unsigned long long GEngineAddress = 0;

	switch ((int)(EngineVersion*100))
	{
	default:
		printf("Unsupported engine version\n");
		break;

		case 420:
			SCOIOffset = Util::FindPattern("\xE8\x00\x00\x00\x00\x41\x8D\x4D\x60", "x????xxxx");
			SCOIAddress = SCOIOffset + 5 + *reinterpret_cast<int32_t*>(SCOIOffset + 1);
			StaticConstructObject_Internal = reinterpret_cast<fStaticConstructObject_Internal>(SCOIAddress);

			if (FortniteVersion < 3.5)
			{
				UEngine420* GEngine;
				GEngineOffset = Util::FindPattern("\x48\x8B\xD3\xE8\x00\x00\x00\x00\x48\x8B\xC8\x48\x89\x05\x00\x00\x00\x00\xE8", "xxxx????xxxxxx????x");
				GEngineAddress = GEngineOffset + 18 + *reinterpret_cast<int32_t*>(GEngineOffset + 14);
				GEngine = *reinterpret_cast<UEngine420**>(GEngineAddress);

				GEngine->GameViewportClient->ViewportConsole = ConstructConsole(GEngine->ConsoleClass, reinterpret_cast<UObject*>(GEngine->GameViewportClient));
			}
			else
			{
				UEngine421* GEngine;
				GEngineOffset = Util::FindPattern("\x48\x8B\xD9\x48\x8B\xF2\x48\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\xF8\x48\x85\xC0", "xxxxxxxxx????x????xxxxxx");
				GEngineAddress = GEngineOffset + 13 + *reinterpret_cast<int32_t*>(GEngineOffset + 9);
				GEngine = *reinterpret_cast<UEngine421**>(GEngineAddress);

				GEngine->GameViewportClient->ViewportConsole = ConstructConsole(GEngine->ConsoleClass, reinterpret_cast<UObject*>(GEngine->GameViewportClient));
			}
			break;

		case 421:
			SCOIOffset = Util::FindPattern("\xE8\x00\x00\x00\x00\x41\x8D\x4D\x60", "x????xxxx");
			SCOIAddress = SCOIOffset + 5 + *reinterpret_cast<int32_t*>(SCOIOffset + 1);
			StaticConstructObject_Internal = reinterpret_cast<fStaticConstructObject_Internal>(SCOIAddress);

			if (FortniteVersion < 5.3)
			{
				UEngine421* GEngine;
				GEngineOffset = Util::FindPattern("\x48\x8B\xD1\x49\x89\x00\x00\x48\x8B\x0D\x00\x00\x00\x00\x00\x00\x00\x49\x89", "xxxxx??xxx???????xx");
				GEngineAddress = GEngineOffset + 14 + *reinterpret_cast<int32_t*>(GEngineOffset + 10);
				GEngine = *reinterpret_cast<UEngine421**>(GEngineAddress);

				GEngine->GameViewportClient->ViewportConsole = ConstructConsole(GEngine->ConsoleClass, reinterpret_cast<UObject*>(GEngine->GameViewportClient));
			}
			else if (FortniteVersion == 5.3)
			{
				UEngine530* GEngine = *reinterpret_cast<UEngine530**>(Util::BaseAddress() + 0x5485C28);
				GEngine->GameViewportClient->ViewportConsole = ConstructConsole(GEngine->ConsoleClass, reinterpret_cast<UObject*>(GEngine->GameViewportClient));
			}
			else
			{
				UEngine4212* GEngine;
				auto GEngineOffset = Util::FindPattern("\x49\x8B\xCC\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x85\xC9", "xxx????x????xx???xxx????xxx");
				auto GEngineAddress = GEngineOffset + 24 + *reinterpret_cast<int32_t*>(GEngineOffset + 20);
				GEngine = *reinterpret_cast<UEngine4212**>(GEngineAddress);

				GEngine->GameViewportClient->ViewportConsole = ConstructConsole(GEngine->ConsoleClass, reinterpret_cast<UObject*>(GEngine->GameViewportClient));
			}
			break;

		case 422:
			UEngine422* GEngine;
			GEngineOffset = Util::FindPattern("\x48\x8B\xD3\x00\x00\x00\x00\x00\x48\x8B\x4C\x24\x40\x48\x89\x05\x00\x00\x00\x00\x48\x85\xC9", "xxx?????xxxxxxxx????xxx");
			GEngineAddress = GEngineOffset + 20 + *reinterpret_cast<int32_t*>(GEngineOffset + 16);
			GEngine = *reinterpret_cast<UEngine422**>(GEngineAddress);

			SCOIOffset = Util::FindPattern("\xE8\x00\x00\x00\x00\x44\x8D\x4D\x01", "x????xxxx");
			SCOIAddress = SCOIOffset + 5 + *reinterpret_cast<int32_t*>(SCOIOffset + 1);
			StaticConstructObject_Internal = reinterpret_cast<fStaticConstructObject_Internal>(SCOIAddress);

			GEngine->GameViewportClient->ViewportConsole = ConstructConsole(GEngine->ConsoleClass, reinterpret_cast<UObject*>(GEngine->GameViewportClient));
			break;

		case 423:
			UEngine423* GEngine423;
			GEngineOffset = Util::FindPattern("\x48\x8B\xD3\x00\x00\x00\x00\x00\x48\x8B\x4C\x24\x40\x48\x89\x05\x00\x00\x00\x00\x48\x85\xC9", "xxx?????xxxxxxxx????xxx");
			GEngineAddress = GEngineOffset + 20 + *reinterpret_cast<int32_t*>(GEngineOffset + 16);
			GEngine423 = *reinterpret_cast<UEngine423**>(GEngineAddress);

			SCOIOffset = Util::FindPattern("\xE8\x00\x00\x00\x00\x44\x8D\x4D\x01", "x????xxxx");
			SCOIAddress = SCOIOffset + 5 + *reinterpret_cast<int32_t*>(SCOIOffset + 1);
			StaticConstructObject_Internal = reinterpret_cast<fStaticConstructObject_Internal>(SCOIAddress);

			GEngine423->GameViewportClient->ViewportConsole = ConstructConsole(GEngine423->ConsoleClass, reinterpret_cast<UObject*>(GEngine423->GameViewportClient));
			break;

		case 424:
			UEngine424* GEngine424;
			GEngineOffset = Util::FindPattern("\x40\x57\x48\x81\x00\x00\x00\x00\x00\x48\x8B\x00\x41\xB8\x00\x00\x00\x00\x48\x8B\xD1\x48\x8B\x0D\x00\x00\x00\x00\x00\x00\x00\x00\x00\x48\x85\xC0\x0F\x00\x00\x00\x00\x00\x48\x8B\xC8", "xxxx?????xx?xx????xxxxxx?????????xxxx?????xxx");
			GEngineAddress = GEngineOffset + 28 + *reinterpret_cast<int32_t*>(GEngineOffset + 24);
			GEngine424 = *reinterpret_cast<UEngine424**>(GEngineAddress);

			SCOIAddress = Util::FindPattern("\x4C\x89\x44\x24\x18\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x44\x8B\xA5\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxx????xxx????xxx????xxxxxx????xxx????");
			StaticConstructObject_Internal = reinterpret_cast<fStaticConstructObject_Internal>(SCOIAddress);

			GEngine424->GameViewportClient->ViewportConsole = ConstructConsole(GEngine424->ConsoleClass, reinterpret_cast<UObject*>(GEngine424->GameViewportClient));
			break;

		case 425:
			UEngine425* GEngine425;
			GEngineOffset = Util::FindPattern("\x48\x8B\xD3\x00\x00\x00\x00\x00\x48\x8B\x4C\x24\x40\x48\x89\x05\x00\x00\x00\x00\x48\x85\xC9", "xxx?????xxxxxxxx????xxx");
			GEngineAddress = GEngineOffset + 20 + *reinterpret_cast<int32_t*>(GEngineOffset + 16);
			GEngine425 = *reinterpret_cast<UEngine425**>(GEngineAddress);

			SCOIOffset = Util::FindPattern("\xE8\x00\x00\x00\x00\x8D\x57\x17\x48", "x????xxxx");
			SCOIAddress = SCOIOffset + 5 + *reinterpret_cast<int32_t*>(SCOIOffset + 1);
			StaticConstructObject_Internal = reinterpret_cast<fStaticConstructObject_Internal>(SCOIAddress);

			GEngine425->GameViewportClient->ViewportConsole = ConstructConsole(GEngine425->ConsoleClass, reinterpret_cast<UObject*>(GEngine425->GameViewportClient));
			break;

		case 426:
			SCOIAddress = Util::FindPattern("\x4C\x89\x44\x24\x18\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4", "xxxxxxxxxxxxxxxxxxxxx????xxx????xxx????xxx");
			StaticConstructObject_Internal = reinterpret_cast<fStaticConstructObject_Internal>(SCOIAddress);

			if (FortniteVersion < 14)
			{
				UEngine426* GEngine;
				GEngineOffset = Util::FindPattern("\x48\x8B\xD3\x00\x00\x00\x00\x00\x48\x8B\x4C\x24\x40\x48\x89\x05\x00\x00\x00\x00\x48\x85\xC9", "xxx?????xxxxxxxx????xxx");
				GEngineAddress = GEngineOffset + 20 + *reinterpret_cast<int32_t*>(GEngineOffset + 16);
				GEngine = *reinterpret_cast<UEngine426**>(GEngineAddress);

				GEngine->GameViewportClient->ViewportConsole = ConstructConsole(GEngine->ConsoleClass, reinterpret_cast<UObject*>(GEngine->GameViewportClient));
			}
			else
			{
				UEngine426* GEngine;
				auto GEngineOffset = Util::FindPattern("\x48\x89\x74\x24\x20\xE8\x00\x00\x00\x00\x48\x8B\x4C\x24\x40\x48\x89\x05", "xxxxxx????xxxxxxxx");
				auto GEngineAddress = GEngineOffset + 22 + *reinterpret_cast<int32_t*>(GEngineOffset + 18);
				GEngine = *reinterpret_cast<UEngine426**>(GEngineAddress);

				GEngine->GameViewportClient->ViewportConsole = ConstructConsole(GEngine->ConsoleClass, reinterpret_cast<UObject*>(GEngine->GameViewportClient));
			}
			break;
	}
}