#pragma once
#include "imgui/imgui.h"

typedef float NColor[4];
void ImColor2NColot(const ImColor& ImColor, NColor& NColor)
{
	NColor[0] = ImColor.Value.x;
	NColor[1] = ImColor.Value.y;
	NColor[2] = ImColor.Value.z;
	NColor[3] = ImColor.Value.w;
}
ImColor NColor2ImColor(const NColor& NColor)
{
	return(ImColor(NColor[0], NColor[1], NColor[2], NColor[3]));
}