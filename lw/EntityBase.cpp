#include "EntityBase.h"

CEntityBase* LocalPlayer;

int CEntityBase::GetHealth()
{
	int health = 0;
	ReadProcessMemory(Offsets.handle, (LPCVOID)((DWORD)this + Offsets.Health), &health, sizeof(health), NULL);
	return health;
}

int CEntityBase::GetTeam()
{
	int team = 0;
	ReadProcessMemory(Offsets.handle, (LPCVOID)((DWORD)this + Offsets.Team), &team, sizeof(team), NULL);
	return team;
}

bool CEntityBase::IsInGame()
{
	int ClientState_State;
	ReadProcessMemory(Offsets.handle, (LPCVOID)(Offsets.CS + Offsets.ClientState_State), &ClientState_State, sizeof(ClientState_State), NULL);
	return (ClientState_State == 6 ? true : false);
}

Vector3 CEntityBase::GetVelocity()
{
	Vector3 velocity;
	ReadProcessMemory(Offsets.handle, (LPCVOID)((DWORD)this + Offsets.Velocity), &velocity, sizeof(velocity), NULL);
	return velocity;
}

Vector3 CEntityBase::GetAimPunch()
{
	Vector3 aimPunch;
	ReadProcessMemory(Offsets.handle, (LPCVOID)((DWORD)this + Offsets.AimPunch), &aimPunch, sizeof(aimPunch), NULL);
	return aimPunch;
}

bool CEntityBase::IsAlive()
{
	int health = 0;
	ReadProcessMemory(Offsets.handle, (LPCVOID)((DWORD)this + Offsets.Health), &health, sizeof(health), NULL);
	if (health <= 0)
		return false;

	int8_t lifestate = -1;
	ReadProcessMemory(Offsets.handle, (LPCVOID)((DWORD)this + Offsets.LifeState), &lifestate, sizeof(lifestate), NULL);
	if (lifestate != 0)
		return false;

	return true;
}

bool CEntityBase::IsDormant()
{
	bool dormant;
	ReadProcessMemory(Offsets.handle, (LPCVOID)((DWORD)this + Offsets.Dormant), &dormant, sizeof(dormant), NULL);
	return dormant;
}

bool CEntityBase::IsSpotted()
{
	bool spotted;
	ReadProcessMemory(Offsets.handle, (LPCVOID)((DWORD)this + Offsets.bSpotted), &spotted, sizeof(spotted), NULL);
	return spotted;
}

bool CEntityBase::IsEnemy()
{
	int myTeam = LocalPlayer->GetTeam();
	int team = GetTeam();

	return (team != myTeam ? true : false);
}