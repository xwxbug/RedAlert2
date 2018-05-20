#include "Ra2Game.h"

HRSRC __fastcall sub_4954E0_load_game_resource(LPCSTR lpname, LPCSTR lpType)
{
	HRSRC   result;
	HMODULE h_resource_module = NULL;
//  目前RES还不正确???
//	h_resource_module = hDLLModule;
	result = FindResourceA(h_resource_module, (LPCSTR)lpname, lpType);
	if (result)
	{
		result = (HRSRC)LoadResource(h_resource_module, result);
		if (result)
			result = (HRSRC)LockResource(result);
	}
	return result;
}