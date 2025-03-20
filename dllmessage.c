#include <Windows.h>
#include <stdio.h>

void Payload() {
    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi;
    
    si.cb = sizeof(si);
    CreateProcessA("C:\\windows\\system32\\calc.exe", NULL, NULL, NULL, 0, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  dwReason,
                       LPVOID lpReserved
                     )
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH: {
        Payload();
        break;
    };
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

