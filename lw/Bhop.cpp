#include "Bhop.h"

CBhop Bhop;

//Don't change
int forceJump = 6;

void CBhop::Run()
{
	//Get our localplayer velocity info
	Vector3 velocity = LocalPlayer->GetVelocity();

	//Checking if we are moving and on the group ( Why check if we are moving? It prevents you from jumping when typing etc.. )
	if (velocity.x != 0 && velocity.y != 0 && velocity.z == 0)
	{
		//Force our player to jump
		WriteProcessMemory(Offsets.handle, (LPVOID)(Offsets.Client + Offsets.Jump), &forceJump, sizeof(forceJump), NULL);
	}
}