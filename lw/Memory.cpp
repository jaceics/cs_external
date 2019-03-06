#include "Memory.h"

CMemory Memory;

void CMemory::getHandle()
{
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(ProcEntry);
	do
	{
		if (!strcmp(ProcEntry.szExeFile, "csgo.exe"))
		{
			if (!ProcEntry.th32ProcessID)
				continue;

			Offsets.PID = ProcEntry.th32ProcessID;
			CloseHandle(hPID);
			Offsets.handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Offsets.PID);
			std::cout << "Process found!\n";
			Sleep(1000);
			system("cls");
			return;
		}
	} while (Process32Next(hPID, &ProcEntry));
	CloseHandle(hPID);
	std::cout << "Process not found.." << std::endl;
	Sleep(1000);
	exit(0);
}

int CMemory::getModule(const char* moduleName)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Offsets.PID);
	MODULEENTRY32 mEntry;

	mEntry.dwSize = sizeof(mEntry);

	while (Module32Next(hModule, &mEntry)) {
		if (!strcmp(mEntry.szModule, moduleName))
		{
			std::cout << moduleName << " found!\n";
			Sleep(1000);
			system("cls");
			CloseHandle(hModule);
			return (DWORD)mEntry.modBaseAddr;
		}
	}
	return 0;
}