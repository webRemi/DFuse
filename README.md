# preload
Preload for nativity - Performs clean DLL injection into a process.

## Commands
Usage
```powershell
./dfuse.exe <processName> <Dll>
```
Example
```powershell
./dfuse.exe notepad dllmessage.dll
```

> [!NOTE]
> Injecting in already injected process will fail.

## Demo
![DFuse demo](/assets/images/dfuse.png)
