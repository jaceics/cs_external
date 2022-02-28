#include <iostream>
#include <Windows.h>
#include "Memory.h"
#include "Visuals.h"
#include "Trigger.h"
#include "Bhop.h"
#include "Settings.h"
#include "EntityBase.h"

//labeled<3

int main()
{
	//Get the handle to csgo.exe and modules ( client_panorama.dll & engine.dll )
	Memory.getHandle();
	Offsets.Client = Memory.getModule("client.dll");
	Offsets.Client = Memory.getModule("client_panorama.dll");
	Offsets.Engine = Memory.getModule("engine.dll");

	//Read engine.dll + clientStateOffset to get pointer for ClientState. We can use it to read ClientState_State ( for in-game check )
	ReadProcessMemory(Offsets.handle, (LPCVOID)(Offsets.Engine + Offsets.ClientState), &Offsets.CS, sizeof(Offsets.CS), NULL);

	std::cout << "twitter.com/laz0rware\n\n";
	std::cout << "by dust\n\n";

	//Tell user what the hotkeys are ( F1, F2 etc.. almost always used for hotkeys, but whatever it works the best atleast for me )
	std::cout << "F1: Glow ESP\n";
	std::cout << "F2: Radar\n";
	std::cout << "F3: Triggerbot\n";
	std::cout << "F4: Bunnyhop\n";
	std::cout << "INSERT: PANIC KEY\n\n";

	std::cout << "LOGS:\n";

	//Here is our infinite loop unless panic key is pressed
	while (!GetAsyncKeyState(VK_INSERT))
	{
		//If user presses F1, F2 or F3 we will toggle features ON / OFF. Also print if it's enabled or disabled.
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			Settings.Visuals.Glow.enabled = !Settings.Visuals.Glow.enabled;
			std::cout << "Glow has been " << (Settings.Visuals.Glow.enabled ? "enabled\n" : "disabled\n");
		}
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			Settings.Visuals.Radar.enabled = !Settings.Visuals.Radar.enabled;
			std::cout << "Radar has been " << (Settings.Visuals.Radar.enabled ? "enabled\n" : "disabled\n");
		}
		if (GetAsyncKeyState(VK_F3) & 1)
		{
			Settings.Trigger.enabled = !Settings.Trigger.enabled;
			std::cout << "Triggerbot has been " << (Settings.Trigger.enabled ? "enabled\n" : "disabled\n");
		}
		if (GetAsyncKeyState(VK_F4) & 1)
		{
			Settings.Bhop.enabled = !Settings.Bhop.enabled;
			std::cout << "Bunnyhop has been " << (Settings.Bhop.enabled ? "enabled\n" : "disabled\n");
		}

		//Read our localplayer
		ReadProcessMemory(Offsets.handle, (LPCVOID)(Offsets.Client + Offsets.LocalPlayer), &LocalPlayer, sizeof(DWORD), NULL);

		//Checking if localplayer is valid and that we are on game
		if (!LocalPlayer || !LocalPlayer->IsInGame()) {
			Sleep(2);
			continue;
		}

		//Run if glow or radar is enabled
		if (Settings.Visuals.Glow.enabled || Settings.Visuals.Radar.enabled)
		{
			//Here we have a small loop to iterate through entitylist
			for (int i = 0; i <= 64; i++)
			{
				Visuals.Run(i);
			}
		}

		//Checking if localplayer is alive if not then sleeping for 2ms and returning back to the top of the loop
		if (!LocalPlayer->IsAlive()) {
			Sleep(2);
			continue;
		}

		//Run triggerbot if it's enabled. Also checking if ALT is pressed or autoShoot is enabled
		if (Settings.Trigger.enabled && ((GetAsyncKeyState(VK_MENU)) || Settings.Trigger.autoShoot))
		{
			Trigger.Run();
		}

		//Run bunnyhop right away if legitMode is false else it runs less times ( slower )
		static size_t lT = 0;
		if (Settings.Bhop.enabled && (!Settings.Bhop.legitMode || GetTickCount() > lT))
		{
			//Check if user is holding space
			if (GetAsyncKeyState(VK_SPACE))
			{
				Bhop.Run();
			}

			//Get current tickcount and add random value between 0-15 to it so we have little timer when to run this code again
			//Not best, but works for now
			lT = GetTickCount() + (rand() % 16);
		}
		//Sleep for 1ms to save fps. You can increase if you want, but remember features will become slower too
		Sleep(1);
	}
}
