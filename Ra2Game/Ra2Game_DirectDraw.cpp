#include "Ra2Game.h"


LPDIRECTDRAW2* g_lpdd = (LPDIRECTDRAW2*)0x8523CC;
LPDWORD g_n_display_width = (LPDWORD)0x8523E0;
LPDWORD g_n_display_height = (LPDWORD)0x8523E4;
LPDWORD g_n_display_bpp = (LPDWORD)0x8523E8;


#pragma comment(lib,"ddraw.lib")

HRESULT sub_00495970_DirectDrawPrep_00()
{
	HRESULT result;
	HRESULT result_ddraw_create;
	wchar_t sz_message_text[MAX_PATH];
	LPDIRECTDRAW2 lpDD = *g_lpdd;
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



unsigned int sub_00495AD0_DirectDrawCheckVRAM()
{
	bool b_ddraw_created; // bl
	HRESULT result_ddraw_create; // eax
	unsigned int result; // esi
	unsigned int v4; // esi
	int result_release; // eax
	_DDSURFACEDESC v7 = { 0 };


	wchar_t sz_message_text[MAX_PATH]; // [esp+78h] [ebp-18Ch]
	DDCAPS_DX3 dx3_caps; // [esp+C8h] [ebp-13Ch]

	LPDIRECTDRAW2 lpDD = *g_lpdd;
	b_ddraw_created = 0;
	if (!lpDD)
	{
		result_ddraw_create = DirectDrawCreate(0, (LPDIRECTDRAW*)&lpDD, 0);
		if (result_ddraw_create)
		{
			swprintf(sz_message_text, L"DDRAW.DLL Error code = %08X", result_ddraw_create);
			MessageBoxW(g_hmain_Wnd, sz_message_text, L"Direct X", 0x30u);
			lpDD = 0;
		}
		else
		{
			b_ddraw_created = 1;
		}
	}
	result = 0;
	if (lpDD)
	{
		dx3_caps.dwSize = 316;
		if (!lpDD->GetCaps((LPDDCAPS)&dx3_caps, 0))
		{
			v4 = dx3_caps.dwVidMemTotal;
			v7.dwSize = 108;
			if (!lpDD->GetDisplayMode((LPDDSURFACEDESC)&v7))
			{
				v4 += v7.dwHeight * v7.dwWidth * (v7.ddpfPixelFormat.dwRGBBitCount >> 3);
			}
			result = (v4 + 0x20000) & 0xFFF00000;
		}
	}
	if (b_ddraw_created && lpDD)
	{
		result_release = lpDD->Release();
		if (result_release)
		{
			swprintf(sz_message_text, L"DDRAW.DLL Error code = %08X", result_release);
			MessageBoxW(g_hmain_Wnd, sz_message_text, L"Direct X", 0x30u);
		}
		lpDD = 0;
	}
	return result;
}


typedef int(*psub_4957E0)();
psub_4957E0 sub_4957E0 = (psub_4957E0)0x4957E0;

bool __fastcall sub_00495C90_DirectDrawPrep_01(int a1, DWORD n_display_width, DWORD n_display_height, DWORD n_display_bpp)
{
	HRESULT result_ddraw_create; // eax
	bool result; // al
	int result_SetCooperativeLevel; // eax
	HRESULT result_create_palette; // eax
	wchar_t sz_message_text[MAX_PATH]; // [esp+24h] [ebp-50h]

	LPDIRECTDRAW2 lpDD = *g_lpdd;

	if (!lpDD)
	{
		result_ddraw_create = DirectDrawCreate(0, (LPDIRECTDRAW*)&lpDD, 0);
		if (result_ddraw_create)
		{
			swprintf(sz_message_text, L"DDRAW.DLL Error code = %08X", result_ddraw_create);
			MessageBoxW(g_hmain_Wnd, sz_message_text, L"Direct X", MB_ICONEXCLAMATION);
		}
		else
		{
			*g_lpdd = lpDD;
			if (*g_c_force_in_window_mode)
				result_SetCooperativeLevel = lpDD->SetCooperativeLevel(g_hmain_Wnd, 8);
			else
				result_SetCooperativeLevel = lpDD->SetCooperativeLevel(g_hmain_Wnd, 17);
			if (result_SetCooperativeLevel)
			{
				swprintf(sz_message_text, L"DDRAW.DLL Error code = %08X", result_SetCooperativeLevel);
				MessageBoxW(g_hmain_Wnd, sz_message_text, L"Direct X", MB_ICONEXCLAMATION);
			}
		}
	}
//	if (*g_c_force_in_window_mode)
//	a4 = 32;

	if (lpDD->SetDisplayMode(n_display_width, n_display_height, n_display_bpp, 0, 0))
	{
		MessageBoxW(g_hmain_Wnd, L"Error In Change Display Mode", 0, MB_ICONEXCLAMATION);
		result = 0;
	}
	else
	{
		*g_n_display_width = n_display_width;
		*g_n_display_height = n_display_height;
		*g_n_display_bpp = n_display_bpp;
		LPPALETTEENTRY      lpDDColorArray = (LPPALETTEENTRY)0x851FCC;
		LPDIRECTDRAWPALETTE* lplpDDPalette = (LPDIRECTDRAWPALETTE*)0x851FC8;
		if (n_display_bpp == 8
			&& (
			(result_create_palette = lpDD->CreatePalette(68,
				(LPPALETTEENTRY)lpDDColorArray,
				(LPDIRECTDRAWPALETTE *)lplpDDPalette,
				0)) != 0))
		{
			swprintf(sz_message_text, L"DDRAW.DLL Error code = %08X", result_create_palette);
			MessageBoxW(g_hmain_Wnd, sz_message_text, L"Direct X", MB_ICONEXCLAMATION);
			result = 0;
		}
		else
		{
			sub_4957E0();
			result = 1;
		}
	}
	return result;
}