#include "Trigger.h"

CTrigger Trigger;

//Don't change
int forceAttack = 6;

void CTrigger::Run()
{
	int crosshairID;

	//Read our crosshairID into crosshairID variable
	ReadProcessMemory(Offsets.handle, (LPVOID)((DWORD)LocalPlayer + Offsets.Crosshair), &crosshairID, sizeof(crosshairID), NULL);

	CEntityBase* Entity;

	//Getting entity from our crosshair with the crosshairID we stored above
	ReadProcessMemory(Offsets.handle, (LPVOID)(Offsets.Client + Offsets.EntityList + (crosshairID - 1) * 0x10), &Entity, sizeof(DWORD), NULL);
	if (!Entity)
		return;

	//If entity is on same team with us and we have team check enabled return from this function
	if (!Entity->IsEnemy() && Settings.Trigger.teamCheck)
		return;

	//Checking if entity health is more than 0. You can check for more if you like, but this has been enough for me always.
	if (Entity->GetHealth() > 0)
	{
		//Force our player to shoot
		WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.Client + Offsets.Attack), &forceAttack, sizeof(forceAttack), NULL);
	}
}