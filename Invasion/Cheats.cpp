#include <string>
#include <thread>
#include <future>
#include <iostream>

#include "Cheats.hpp"
#include "Render.hpp"
#include "Configs.hpp"
#include "GUI.h"
#include "Utils/NewColor.hpp"

void Cheats::RenderESP(DWORD64 EntityAddress, const CEntity& LocalEntity, CEntity& Entity, int LocalPlayerControllerIndex, int Index)
{
	ImVec4 Rect = Render::GetBoxRect(Entity, 0);
	Render::DrawBone(Entity, NColor2ImColor(ESPConfig::BoneColor), 1.3f);
	Render::ShowPenis(Entity, 5.f, ESPConfig::PenisColor, 1.3f);
	Render::DrawHeadbox(Entity, NColor2ImColor(ESPConfig::HeadBoxColor));

	if (ESPConfig::ShowBoxESP)
	{
		if (ESPConfig::OutLine)
			Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, NColor2ImColor(ESPConfig::BoxColor) &IM_COL32_A_MASK, 3, ESPConfig::BoxRounding);

		if (((Entity.Pawn.bSpottedByMask & (DWORD64(1) << LocalPlayerControllerIndex)) || (LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << Index))))
		{
			Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, NColor2ImColor(ESPConfig::VisibleColor), 1.3, ESPConfig::BoxRounding);
		}
		else {
			Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, NColor2ImColor(ESPConfig::BoxColor), 1.3, ESPConfig::BoxRounding);
		}
	}

	Render::LineToEnemy(Rect, NColor2ImColor(ESPConfig::LineToEnemyColor), 1.2);

	if (ESPConfig::ShowPlayerName)
	{
		Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
	}

	Render::DrawDistance(LocalEntity, Entity, Rect);

	if (ESPConfig::ShowHealthBar)
	{
		ImVec2 HealthBarPos = { Rect.x - 6.f,Rect.y };
		ImVec2 HealthBarSize = { 4 ,Rect.w };
		Render::DrawHealthBar(EntityAddress, 100, Entity.Pawn.Health, HealthBarPos, HealthBarSize);
	}

	if (ESPConfig::ArmorBar && Entity.Pawn.Armor > 0)
	{
		ImVec2 ArmorBarPos;
		ArmorBarPos = { Rect.x + Rect.z + 2.f,Rect.y };
		ImVec2 ArmorBarSize = { 4.f,Rect.w };
		Render::DrawArmorBar(EntityAddress, 100, Entity.Pawn.Armor, Entity.Controller.HasHelmet, ArmorBarPos, ArmorBarSize);
	}

}

bool GameKeepOn, UserBruted;
int BruteC, BruteD = 0;
void Cheats::Run() noexcept
{
	// Show menu
	static DWORD lastTick = 0;
	DWORD currentTick = GetTickCount();
	if (((GetAsyncKeyState(VK_INSERT) & 0x8000) || (GetAsyncKeyState(VK_DELETE) & 0x8000)) && currentTick - lastTick >= 250) {
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		lastTick = currentTick;
	}

	if (MenuConfig::ShowMenu)
		GUI::DrawCallBack();

	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	CEntity LocalEntity, ServerEntity;
	static int LocalPlayerControllerIndex = 1;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;

	ProcessMgr.ReadMemory(LocalControllerAddress + Offset::CCSPlayerController.m_iPing, MenuConfig::Ping);

	/*if (!LocalEntity.UpdatePawn(LocalPawnAddress))
		return;*/

	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;

		if (EntityAddress == LocalEntity.Controller.Address)
		{
			LocalPlayerControllerIndex = i;
			continue;
		}

		if (!Entity.UpdateController(EntityAddress))
			continue;

		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;

		if (!Entity.IsAlive())
			continue;

		if (!Entity.IsInScreen())
			continue;

		RenderESP(EntityAddress, LocalEntity, Entity, LocalPlayerControllerIndex, i);
	}


}