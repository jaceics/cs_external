#pragma once

#include <iostream>
#include <Windows.h>

//Our settings for the cheat
class CSettings
{
public:
	struct
	{
		struct
		{
			bool enabled = false;
			bool glowTeam = false;
		} Glow;


		struct
		{
			bool enabled = false;
		} Radar;
	} Visuals;

	struct
	{
		bool enabled = false;
		bool teamCheck = true;
		bool autoShoot = false;
	} Trigger;

	struct
	{
		bool enabled = false;
		bool legitMode = false;
	} Bhop;
};

extern CSettings Settings;