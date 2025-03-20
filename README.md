# preload
Preload for nativity - Performs clean DLL injection into a process.

## Commands
Usage
```powershell
./preload.exe <processName> <Dll>
```
Example
```powershell
./preload.exe notepad dllmessage.dll
```

> [!NOTE]
> Injecting in already injected process will fail.
