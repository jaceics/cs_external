#pragma once

#include <iostream>
#include <Windows.h>
#include "Offsets.h"

//This doesn't belong here, but as of now it can stay
struct Vector3 {
	float x, y, z;
};

class CEntityBase
{
public:
	int GetHealth();
	int GetTeam();
	bool IsInGame();
	Vector3 GetVelocity();
	Vector3 GetAimPunch();
	bool IsAlive();
	bool IsDormant();
	bool IsSpotted();
	bool IsEnemy();
};

extern CEntityBase* LocalPlayer;