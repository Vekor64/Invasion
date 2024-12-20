#pragma once
#include "Bone.hpp"
#include "Game.hpp"
#include "Entity.hpp"

namespace MenuConfig
{
	inline bool ShowMenu = true;
	inline int Ping = 0;
	inline bool TeamCheck = true;
}

namespace ESPConfig
{
	inline bool enabled = false;
	inline bool AlwaysActive = false;
	inline bool ShowScoping = false;
	inline bool ShowBoneESP = true;
	inline bool ShowBoxESP = true;
	inline bool ShowHealthBar = true;
	inline bool ShowEyeRay = false;
	inline bool ShowPlayerName = true;
	inline bool ShowDistance = false;
	inline bool ShowHealthNum = false;
	inline bool ArmorBar = false;
	inline bool ShowArmorNum = false;
	inline bool ShowHeadBox = false;
	inline bool ShowPreview = true;
	inline bool VisibleCheck = false;
	inline bool FilledBox = false;
	inline bool FilledVisBox = false;
	inline bool MultiColor = false;
	inline bool OutLine = true;
	inline bool ShowIsScoped = false;
	// 0: normal 1: Flat
	inline int HeadBoxStyle = 0;
	inline float BoxRounding = 0.0f;
	inline float BoxAlpha = 0.35f;
	inline bool ShowLineToEnemy = false;
	inline int RenderDistance = 0;
	inline float LineToEnemyColor[4] = {1.f, 1.f, 1.f, 1.f};
	// 0: Top 1: Center 2: Bottom
	inline int LinePos = 0;

	inline float BoneColor[4] = { 0.f, 1.f, 1.f, 1.f };
	inline float BoxColor[4] = { 1.f, 0.8f, 0.f, 1.f };
	inline float EyeRayColor[4] = { 1.f, 0.f, 0.f, 1.f };
	inline float HeadBoxColor[4] = { 1.f, 1.f, 1.f, 1.f };
	inline float VisibleColor[4] = { 1.f, 0.f, 0.f, 1.f };
	inline float FilledColor[4] = { 1.f, 1.f, 1.f, 0.5f };
	inline float BoxFilledVisColor[4] = { 0.f, 0.f, 1.f, 1.f };
	inline float FilledColor2[4] = { 0.f, 1.f, 0.f, 1.f };

	// Penis Config
	inline bool ShowPenis = false;
	inline ImColor PenisColor = ImColor(255, 0, 0, 200);
}