#pragma once

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "Offsets.h"

class CMemory
{
public:
	void getHandle();
	int getModule(const char* moduleName);
};

extern CMemory Memory;