#pragma once
#include "Game.hpp"
#include "Entity.hpp"

namespace Cheats
{
	void RenderESP(DWORD64 EntityAddress, const CEntity& LocalEntity, CEntity& Entity, int LocalPlayerControllerIndex, int Index);
	void Run() noexcept;
};

struct {
	ImFont* normal15px = nullptr;
} fonts;
