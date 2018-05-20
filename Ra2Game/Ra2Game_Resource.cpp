#include "Ra2Game.h"

HRSRC __fastcall sub_4954E0_load_game_resource(LPCSTR lpname, LPCSTR lpType)
{
	HRSRC   result;
	HMODULE h_resource_module = NULL;
//  ĿǰRES������ȷ???
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