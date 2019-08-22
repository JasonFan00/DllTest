// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>

void openWindow()
{
	if (!AllocConsole())  //  Each process can only have one console, so will fail if process already has one, so free console then make a new one
	{
		FreeConsole();
		AllocConsole();
	}
	freopen_s((FILE * *)stdout, "CONOUT$", "w", stdout);	//  stdout is already a file pointer (FILE*), but arg1 needs a pointer to a file pointer.  so cast (FILE**) is like saying FILE* fPtr = stdout.
	std::cout << "Console out!";
	std::getchar();
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)openWindow, NULL, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

