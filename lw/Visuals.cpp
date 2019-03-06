#include "Visuals.h"

CVisuals Visuals;

//Don't change
bool forceSpotted = false;

void CVisuals::Run(int i)
{
	int entityIndex, glowManager;

	CEntityBase* Entity;

	//Get entity from entitylist using our loop index
	ReadProcessMemory(Offsets.handle, (LPVOID)(Offsets.Client + Offsets.EntityList + (i - 1) * 0x10), &Entity, sizeof(DWORD), NULL);

	//Checking if we got some kind of entity atleast if not then return
	if (!Entity)
		return;

	//Read info from entity once here so we don't have to read all two times on the same function
	bool entityAlive = Entity->IsAlive();
	bool isEnemy = Entity->IsEnemy();
	bool isDormant = Entity->IsDormant();
	bool isSpotted = Entity->IsSpotted();

	//Checking if glow is enabled, entity is alive, updated by server and entity is enemy or teammate, but then we must have glowTeam variable set to true
	if (Settings.Visuals.Glow.enabled && entityAlive && !isDormant && (isEnemy || !isEnemy && Settings.Visuals.Glow.glowTeam))
	{
		ReadProcessMemory(Offsets.handle, (LPVOID)(Offsets.Client + Offsets.GlowObject), &glowManager, sizeof(glowManager), NULL);
		ReadProcessMemory(Offsets.handle, (LPVOID)((DWORD)Entity + Offsets.GlowIndex), &entityIndex, sizeof(entityIndex), NULL);

		//Read enemy player into our glow struct
		ReadProcessMemory(Offsets.handle, (LPVOID)(glowManager + (entityIndex * 0x38) + 0x4), &sGlow, sizeof(sGlow), NULL);

		//Modify glow struct
		sGlow.r = 255.f;
		//Check if player is not enemy and we have glowTeam variable set to true. If so set green to 255 else 0.
		sGlow.g = !isEnemy && Settings.Visuals.Glow.glowTeam ? 255.f : 0.f;
		sGlow.b = 0.f;
		sGlow.a = 0.5f;
		sGlow.m_bRenderWhenOccluded = true;
		sGlow.m_bRenderWhenUnoccluded = false;

		//Write the modified struct into the player
		WriteProcessMemory(Offsets.handle, (LPVOID)(glowManager + (entityIndex * 0x38) + 0x4), &sGlow, sizeof(sGlow), NULL);
	}

	//Same checks as the glow, but we also check if entity is not spotted
	if (Settings.Visuals.Radar.enabled && entityAlive && isEnemy && !isSpotted)
	{
		//Force player to be spotted ( will show up on radar )
		WriteProcessMemory(Offsets.handle, (LPVOID)((DWORD)Entity + Offsets.bSpotted), &forceSpotted, sizeof(forceSpotted), NULL);
	}
}