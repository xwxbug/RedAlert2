#include "Ra2Game.h"

LPCSTR g_WindowName = "Red Alert 2";

WNDPROC sub_7375A0 = (WNDPROC)0x7375A0;
LPBYTE  g_c_force_in_window_mode = (LPBYTE)0x851CB0;
HWND*   g_lp_hmain_Wnd =(HWND*)0xb263d8;
HWND    g_hmain_Wnd = NULL;
HIMC*   g_lp_imm_Context = (HIMC*)0xB263E4;
int*    g_lp_winmain_ncmdshow = (int*)0xB263CC;

#pragma comment(lib,"Imm32.lib")
#pragma comment(lib,"Comctl32.lib")


HCURSOR __fastcall sub_00737BD0_create_main_windows(HINSTANCE hInstance, int n_show, int n_width, int n_height)
{
	DWORD v6; // ST2C_4
	BOOL v7; // ST28_4
	DWORD v8; // eax
	int n_screen_height;
	int n_screen_width;
	HCURSOR v11; // eax
	struct tagRECT rc; // [esp+18h] [ebp-38h]
	WNDCLASSA WndClass; // [esp+28h] [ebp-28h]


	InitCommonControls();
	HICON dword_B263D4 = LoadIconA(hInstance, (LPCSTR)0x5D);
	HCURSOR dword_B263D0 = LoadCursorA(hInstance, (LPCSTR)0x68);
	WndClass.style = 3;
	WndClass.lpfnWndProc = (WNDPROC)sub_7375A0;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = dword_B263D4;
	WndClass.hCursor = dword_B263D0;
	WndClass.hbrBackground = 0;
	WndClass.lpszMenuName = 0;
	WndClass.lpszClassName = g_WindowName;
	RegisterClassA(&WndClass);
//	*g_c_force_in_window_mode = 1;
	if (*g_c_force_in_window_mode)
	{
		g_hmain_Wnd = CreateWindowExA(0, g_WindowName, g_WindowName, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_SYSMENU | WS_CAPTION, 0, 0, 0, 0, 0, 0, hInstance, 0);
		*g_lp_hmain_Wnd = g_hmain_Wnd;
		SetRect(&rc, 0, 0, n_width, n_height);
		v6 = GetWindowLongA(g_hmain_Wnd, -20);
		v7 = GetMenu(g_hmain_Wnd) != 0;
		v8 = GetWindowLongA(g_hmain_Wnd, -16);
		AdjustWindowRectEx(&rc, v8, v7, v6);
		MoveWindow(g_hmain_Wnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, 1);
	}
	else
	{
		n_screen_height = GetSystemMetrics(1);
		n_screen_width = GetSystemMetrics(0);
		//1080P?
//		n_screen_height = 1080;
//		n_screen_width = 1920;
		g_hmain_Wnd = CreateWindowExA(WS_EX_TOPMOST, g_WindowName, g_WindowName, WS_POPUP | WS_CLIPCHILDREN, 0, 0, n_screen_width, n_screen_height, 0, 0, hInstance, 0);
//		g_hmain_Wnd = CreateWindowExA(WS_EX_TOPMOST, g_WindowName, g_WindowName, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_SYSMENU | WS_CAPTION, 0, 0, n_screen_width, n_screen_height, 0, 0, h_module_Instance, 0);

		*g_lp_hmain_Wnd = g_hmain_Wnd;
	}
	*g_lp_imm_Context = ImmGetContext(g_hmain_Wnd);
	ShowWindow(g_hmain_Wnd, SW_SHOWNORMAL);
	*g_lp_winmain_ncmdshow = n_show;
	UpdateWindow(g_hmain_Wnd);
	SetFocus(g_hmain_Wnd);
	// ALT+CONTROL+SHIFT+M key
	RegisterHotKey(g_hmain_Wnd, 1, MOD_ALT | MOD_CONTROL | MOD_SHIFT, 77u);
	v11 = LoadCursorA(hInstance, (LPCSTR)0x68);
	return SetCursor(v11);
}