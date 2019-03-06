#pragma once

#include <iostream>
#include <Windows.h>

//Our offsets are stored here. Incase csgo has an update change these to current offsets and cheat should be working again.
//Depends on the update though. You might need to change something from code also at some point.
class COffsets
{
public:
	DWORD LocalPlayer = 0xCC96B4;
	DWORD EntityList = 0x4CD9FFC;
	DWORD ClientState_State = 0x108;
	DWORD Crosshair = 0xB394;
	DWORD Health = 0x100;
	DWORD Team = 0xF4;
	DWORD Dormant = 0xED;
	DWORD Attack = 0x310B6A0;
	DWORD Jump = 0x517D1B4;
	DWORD Flags = 0x104;
	DWORD Velocity = 0x114;
	DWORD bSpotted = 0x93D;
	DWORD ClientState = 0x58BCFC;
	DWORD LifeState = 0x25F;
	DWORD GlowObject = 0x5219F38;
	DWORD GlowIndex = 0xA3F8;
	DWORD AimPunch = 0x302C;

	DWORD PID;
	HANDLE handle;
	DWORD CS;
	DWORD Client;
	DWORD Engine;
};

extern COffsets Offsets;