#pragma once
#include <Windows.h>
#include <iostream>

extern PCHAR g_pFileName;
extern CHAR g_sReadFolder[];
extern CHAR repPath[MAX_PATH];

VOID WINAPI SetConsole();
BOOL SetHook(DWORD dwRawAddr, DWORD dwTarAddr, SIZE_T szRawSize);
BOOL FileExist();