#include "Ra2Game.h"


LPDIRECTDRAW4* g_lpdd = (LPDIRECTDRAW4*)0x8523CC;
#pragma comment(lib,"ddraw.lib")

HRESULT sub_00495970_DirectDrawPrep_00()
{
	HRESULT result;
	HRESULT result_ddraw_create;
	wchar_t sz_message_text[MAX_PATH];
	LPDIRECTDRAW4 lpDD = *g_lpdd;
	result = (HRESULT)lpDD;
	if (!lpDD)
	{
		result_ddraw_create = DirectDrawCreate(0, (LPDIRECTDRAW*)&lpDD, 0);
		if (result_ddraw_create)
		{
			swprintf(sz_message_text, L"DDRAW.DLL Error code = %08X", result_ddraw_create);
			MessageBoxW(g_hmain_Wnd, sz_message_text, L"Direct X", 0x30u);
		}
		else
		{
			*g_lpdd = lpDD;
			if (*g_c_force_in_window_mode)
				result = lpDD->SetCooperativeLevel(g_hmain_Wnd, DDSCL_NORMAL);
			else
				result = lpDD->SetCooperativeLevel(g_hmain_Wnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
			if (result)
			{
				swprintf(sz_message_text, L"DDRAW.DLL Error code = %08X", result);
				result = MessageBoxW(g_hmain_Wnd, sz_message_text, L"Direct X", 0x30u);
			}
		}
	}
	return result;
}



