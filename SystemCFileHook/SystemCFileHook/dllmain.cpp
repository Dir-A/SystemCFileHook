#include <Windows.h>
#include <iostream>
#include "Tools.h"

VOID __declspec(naked) ScriptHook()
{
	__asm
	{
		pushfd
		pushad
		mov eax,dword ptr[ebp+0x8]
		mov g_pFileName,eax
	}

	if (FileExist())
	{
		__asm mov dword ptr[ebp + 0x8], offset repPath
		__asm mov dword ptr[ebp + 0xC],0 //Set Pack Path To NULL
	}
	__asm
	{
		popad
		popfd
		ret
	}
}

VOID __declspec(naked) KGHook()
{
	__asm
	{
		pushfd
		pushad
		mov eax, dword ptr[ebp + 0x8]
		mov g_pFileName, eax
	}

	if (FileExist())
	{
		__asm mov dword ptr[ebp + 0x8], offset repPath
		__asm mov dword ptr[ebp + 0xC], 0
	}
	__asm
	{
		popad
		popfd
		ret
	}
}

VOID __declspec(naked) BMPHook()
{
	__asm
	{
		pushfd
		pushad
		mov eax, dword ptr[ebp + 0x10]
		mov g_pFileName, eax
	}

	if (FileExist())
	{
		__asm mov dword ptr[ebp + 0x10], offset repPath
		__asm mov dword ptr[ebp + 0x14], 0
	}
	__asm
	{
		popad
		popfd
		ret
	}
}

VOID StartHook()
{
	SetConsole();

	//ノットフィクション！
	//0045F4B0 -> GetPackInfo
	//0045F670 -> GetFileInfo
	//0045FF80 -> GetFileSize
	//Make the pack path empty to enable reading files from the directory
	SetHook(0x0045E0F0, (DWORD)ScriptHook, 0x5);
	SetHook(0x00462960, (DWORD)KGHook, 0x5);
	SetHook(0x00450330, (DWORD)BMPHook, 0x5);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		StartHook();
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

VOID __declspec(dllexport) DirA() {}