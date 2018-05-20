#include "Ra2Game.h"

HMODULE hDLLModule;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hDLLModule = hModule;
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}