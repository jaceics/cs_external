#pragma once

#include "Offsets.h"
#include "Settings.h"

#include "EntityBase.h"
class CVisuals
{
public:
	void Run(int i);
private:
	struct csGlow
	{
		float r;
		float g;
		float b;
		float a;
		uint8_t unk1[16];
		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloom;
		int GlowStyle;
		uint8_t unk2[10];
	}; csGlow sGlow;
};

extern CVisuals Visuals;