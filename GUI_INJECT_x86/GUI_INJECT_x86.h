#pragma once
#include "resource.h"
#include <TlHelp32.h>
#include <io.h>
#include <iostream>
using namespace std;

DWORD GetProcessByName(char* process_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	DWORD proc_id = 0;
	if (Process32First(snapshot, &process))
	{
		while (Process32Next(snapshot, &process))
		{
			if (_stricmp(process.szExeFile, process_name) == 0)/////<---------------------
			{
				proc_id = process.th32ProcessID;
				break;
			}
		}
	}
	CloseHandle(snapshot);
	return proc_id;
}

bool FileExist(char* name)
{
	return _access(name, 0) != -1;
}

bool Inject(DWORD pID, char*path)
{
	HANDLE proc_handle;
	LPVOID RemoteString;
	LPCVOID LoadLibAddy;
	if (pID == 0)
		return false;
	proc_handle = OpenProcess(PROCESS_ALL_ACCESS, false, pID);
	if (proc_handle == 0)
		return false;
	LoadLibAddy = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	RemoteString = VirtualAllocEx(proc_handle, NULL, strlen(path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(proc_handle, RemoteString, path, strlen(path), NULL);
	CreateRemoteThread(proc_handle, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, RemoteString, NULL, NULL);
	CloseHandle(proc_handle);
	return true;
}