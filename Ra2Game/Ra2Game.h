#pragma once
#include <windows.h>
#include <CommCtrl.h>
#include <ddraw.h>
#include <stdio.h>

extern HMODULE hDLLModule;










extern LPDIRECTDRAW2* g_lpdd;
extern LPBYTE  g_c_force_in_window_mode;
extern HWND*   g_lp_hmain_Wnd;
extern HWND    g_hmain_Wnd;
extern HIMC*   g_lp_imm_Context;
extern int*    g_lp_winmain_ncmdshow;

extern LPDWORD g_n_display_width;
extern LPDWORD g_n_display_height;
extern LPDWORD g_n_display_bpp;