#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>
#include <map>
#include <Windows.h>
#include "Entity.hpp"
#include "Configs.hpp"
#include "Utils/Format.hpp"
#include "Utils/imgui/imgui.h"
#include "Utils/imgui/imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

namespace Render
{	
	void DrawHeadbox(const CEntity& Entity, ImColor Color)
	{
		if (!ESPConfig::ShowHeadBox)
			return;

		Vec2 CenterPos;
		Vec3 Temp;
		BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];
		BoneJointPos Neck = Entity.GetBone().BonePosList[BONEINDEX::neck_0];

		CenterPos = Head.ScreenPos;
		float Radius = abs(Head.ScreenPos.y - Neck.ScreenPos.y) + 2;

		switch (ESPConfig::HeadBoxStyle)
		{
		case 1:
			Gui.CircleFilled(CenterPos, Radius + 1, Color & IM_COL32_A_MASK);
			Gui.CircleFilled(CenterPos, Radius, Color);
			break;
		default:
			//Gui.Circle(CenterPos, Radius, Color, 1.2);
			Gui.Rectangle(ImVec2(CenterPos.x - Radius, CenterPos.y - Radius * 1.5), ImVec2(Radius * 2, Radius * 2.5), Color, 1.2);
		}
	}

	void DrawHealth(int Health, ImVec2 Pos)
	{
		if (!ESPConfig::ShowHealthNum)
			return;

		std::string health_str = Format("%i", Health);
		Gui.StrokeText(health_str, Pos, ImColor(0, 220, 0, 255), 12, false);
	}

	void DrawDistance(const CEntity& LocalEntity, CEntity& Entity, ImVec4 Rect)
	{
		if (!ESPConfig::ShowDistance)
			return;

		int distance = static_cast<int>(Entity.Pawn.Pos.DistanceTo(LocalEntity.Pawn.Pos) / 100);
		std::string dis_str = Format("%im", distance);
		Gui.StrokeText(dis_str, { Rect.x + Rect.z + 4, Rect.y }, ImColor(255, 204, 0, 255), 14, false);
	}

	void LineToEnemy(ImVec4 Rect, ImColor Color, float Thickness, bool IsItem = false)
	{
		if (!ESPConfig::ShowLineToEnemy)
			return;

		switch (ESPConfig::LinePos)
		{
		case 0:
			Gui.Line({ Rect.x + Rect.z / 2,Rect.y }, { Gui.Window.Size.x / 2,0 }, Color, Thickness, IsItem);
			break;
		case 1:
			Gui.Line({ Rect.x + Rect.z / 2,Rect.y }, { Gui.Window.Size.x / 2, Gui.Window.Size.y / 2 }, Color, Thickness, IsItem);
			break;
		case 2:
			Gui.Line({ Rect.x + Rect.z / 2,Rect.y + Rect.w }, { Gui.Window.Size.x / 2, Gui.Window.Size.y }, Color, Thickness, IsItem);
			break;
		default:
			break;
		}

	}

	ImVec4 Get2DBox(const CEntity& Entity)
	{
		BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];

		Vec2 Size, Pos;
		Size.y = (Entity.Pawn.ScreenPos.y - Head.ScreenPos.y) * 1.09;
		Size.x = Size.y * 0.6;

		Pos = ImVec2(Entity.Pawn.ScreenPos.x - Size.x / 2, Head.ScreenPos.y - Size.y * 0.08);

		return ImVec4{ Pos.x,Pos.y,Size.x,Size.y };
	}

	void DrawBone(const CEntity& Entity, ImColor Color, float Thickness)
	{
		if (!ESPConfig::ShowBoneESP)
			return;

		BoneJointPos Previous, Current;
		for (auto i : BoneJointList::List)
		{
			Previous.Pos = Vec3(0, 0, 0);
			for (auto Index : i)
			{
				Current = Entity.GetBone().BonePosList[Index];
				if (Previous.Pos == Vec3(0, 0, 0))
				{
					Previous = Current;
					//pGame->View->Gui->Text(Current.Name.c_str(), Current.ScreenPos, ImColor(255, 255, 0, 255));
					continue;
				}
				if (Previous.IsVisible && Current.IsVisible)
				{
					Gui.Line(Previous.ScreenPos, Current.ScreenPos, Color, Thickness, false);
					//pGame->View->Gui->Text(Current.Name.c_str(), Current.ScreenPos, ImColor(255, 255, 0, 255));
				}
				Previous = Current;
			}
		}
	}

	void ShowPenis(const CEntity& Entity, const float Length, ImColor Color, float Thickness)
	{
		if (!ESPConfig::ShowPenis)
			return;

		Vec2 StartPoint, EndPoint;
		Vec3 Temp;
		BoneJointPos Dick = Entity.GetBone().BonePosList[BONEINDEX::pelvis];

		StartPoint = Dick.ScreenPos;

		float LineLength = cos(Entity.Pawn.ViewAngle.x * M_PI / 180) * Length;

		Temp.x = Dick.Pos.x + cos(Entity.Pawn.ViewAngle.y * M_PI / 180) * LineLength;
		Temp.y = Dick.Pos.y + sin(Entity.Pawn.ViewAngle.y * M_PI / 180) * LineLength;
		Temp.z = Dick.Pos.z - sin(Entity.Pawn.ViewAngle.x * M_PI / 180) * Length;

		if (!gGame.View.WorldToScreen(Temp, EndPoint))
			return;

		Gui.Line(StartPoint, EndPoint, Color, Thickness, false);
	}

	ImVec4 Get2DBoneRect(const CEntity& Entity)
	{
		Vec2 Min, Max, Size;
		Min = Max = Entity.GetBone().BonePosList[0].ScreenPos;

		for (auto& BoneJoint : Entity.GetBone().BonePosList)
		{
			if (!BoneJoint.IsVisible)
				continue;
			Min.x = min(BoneJoint.ScreenPos.x, Min.x);
			Min.y = min(BoneJoint.ScreenPos.y, Min.y);
			Max.x = max(BoneJoint.ScreenPos.x, Max.x);
			Max.y = max(BoneJoint.ScreenPos.y, Max.y);
		}
		Size.x = Max.x - Min.x;
		Size.y = Max.y - Min.y;

		return ImVec4(Min.x, Min.y, Size.x, Size.y);
	}

	class HealthBar
	{
	private:
		using TimePoint_ = std::chrono::steady_clock::time_point;
	private:
		const int ShowBackUpHealthDuration = 500;
		float MaxHealth = 0.f;
		float CurrentHealth = 0.f;
		float LastestBackupHealth = 0.f;
		ImVec2 RectPos{};
		ImVec2 RectSize{};
		bool InShowBackupHealth = false;
		TimePoint_ BackupHealthTimePoint{};
		int MaxAmmo = 0;
		int CurrentAmmo = 0;
		int MaxArmor = 0;
		int CurrentArmor = 0;

	public:
		HealthBar() {}

		void HealthBarV(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool ShowNum);

		void ArmorBarV(bool HasHelmet, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool ShowNum);

		void AmmoBarH(float MaxAmmo, float CurrentAmmo, ImVec2 Pos, ImVec2 Size);
	private:

		ImColor Mix(ImColor Col_1, ImColor Col_2, float t);

		ImColor FirstStageColor = ImColor(0, 255, 0, 255);

		ImColor SecondStageColor = ImColor(255, 232, 0, 255);

		ImColor ThirdStageColor = ImColor(255, 39, 0, 255);

		ImColor BackupHealthColor = ImColor(255, 255, 255, 220);

		ImColor FrameColor = ImColor(45, 45, 45, 220);

		ImColor BackGroundColor = ImColor(0, 0, 0, 255);

		ImColor AmmoColor = ImColor(255, 255, 0, 255);

		ImColor ArmorColor = ImColor(0, 128, 255, 255);
		ImColor ArmorWithHelmetColor = ImColor(255, 0, 255, 255);
	};

	void HealthBar::HealthBarV(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool ShowNum)
	{
		auto InRange = [&](float value, float min, float max) -> bool
			{
				return value > min && value <= max;
			};

		ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

		this->MaxHealth = MaxHealth;
		this->CurrentHealth = CurrentHealth;
		this->RectPos = Pos;
		this->RectSize = Size;

		float Proportion = CurrentHealth / MaxHealth;

		float Height = RectSize.y * Proportion;

		ImColor Color;

		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			BackGroundColor, 5, 15);

		float Color_Lerp_t = pow(Proportion, 2.5);
		if (InRange(Proportion, 0.5, 1))
			Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
		else
			Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);

		DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - Height },
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			Color, 0);

		DrawList->AddRect(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			FrameColor, 0, 15, 1);

		if (ShowNum)
		{
			if (CurrentHealth < MaxHealth)
			{
				std::string health_str = Format("%.f", CurrentHealth);
				Vec2 Pos = { RectPos.x,RectPos.y + RectSize.y - Height };
				Gui.StrokeText(health_str, Pos, ImColor(255, 255, 255), 13.f, true);
			}
		}
	}

	void HealthBar::ArmorBarV(bool HasHelmet, float MaxArmor, float CurrentArmor, ImVec2 Pos, ImVec2 Size, bool ShowNum)
	{
		auto InRange = [&](float value, float min, float max) -> bool
			{
				return value > min && value <= max;
			};

		ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

		this->MaxArmor = MaxArmor;
		this->CurrentArmor = CurrentArmor;
		this->RectPos = Pos;
		this->RectSize = Size;

		float Proportion = CurrentArmor / MaxArmor;

		float Height = RectSize.y * Proportion;

		ImColor Color;

		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			BackGroundColor, 5, 15);

		if (HasHelmet)
			Color = ArmorWithHelmetColor;
		else
			Color = ArmorColor;

		DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - Height },
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			Color, 0);

		DrawList->AddRect(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			FrameColor, 0, 15, 1);

		if (ShowNum)
		{
			if (CurrentArmor < MaxArmor)
			{
				std::string armor_str = Format("%.f", CurrentArmor);
				Vec2 Pos = { RectPos.x,RectPos.y + RectSize.y - Height };
				Gui.StrokeText(armor_str, Pos, ImColor(255, 255, 255), 13.f, true);
			}
		}
	}

	void HealthBar::AmmoBarH(float MaxAmmo, float CurrentAmmo, ImVec2 Pos, ImVec2 Size)
	{
		ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

		this->MaxAmmo = MaxAmmo;
		this->CurrentAmmo = CurrentAmmo;
		this->RectPos = Pos;
		this->RectSize = Size;

		float Proportion = CurrentAmmo / MaxAmmo;

		float Width = RectSize.x * Proportion;

		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			BackGroundColor, 5, 15);

		DrawList->AddRectFilled(RectPos,
			{ RectPos.x + Width,RectPos.y + RectSize.y },
			AmmoColor, 0);

		DrawList->AddRect(RectPos,
			{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
			FrameColor, 0, 15, 1);
	}

	ImColor HealthBar::Mix(ImColor Col_1, ImColor Col_2, float t)
	{
		ImColor Col;
		Col.Value.x = t * Col_1.Value.x + (1 - t) * Col_2.Value.x;
		Col.Value.y = t * Col_1.Value.y + (1 - t) * Col_2.Value.y;
		Col.Value.z = t * Col_1.Value.z + (1 - t) * Col_2.Value.z;
		Col.Value.w = Col_1.Value.w;
		return Col;
	}

	void DrawHealthBar(DWORD Sign, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
			HealthBarMap.insert({ Sign,HealthBar() });

		if (HealthBarMap.count(Sign))
			HealthBarMap[Sign].HealthBarV(MaxHealth, CurrentHealth, Pos, Size, ESPConfig::ShowHealthNum);
	}

	void DrawAmmoBar(DWORD Sign, float MaxAmmo, float CurrentAmmo, ImVec2 Pos, ImVec2 Size)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
			HealthBarMap.insert({ Sign,HealthBar() });

		if (HealthBarMap.count(Sign))
			HealthBarMap[Sign].AmmoBarH(MaxAmmo, CurrentAmmo, Pos, Size);
	}

	void DrawArmorBar(DWORD Sign, float MaxArmor, float CurrentArmor, bool HasHelmet, ImVec2 Pos, ImVec2 Size)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
			HealthBarMap.insert({ Sign,HealthBar() });

		if (HealthBarMap.count(Sign))
			HealthBarMap[Sign].ArmorBarV(HasHelmet, MaxArmor, CurrentArmor, Pos, Size, ESPConfig::ShowArmorNum);
	}

	ImVec4 GetBoxRect(const CEntity& Entity, int BoxType)
	{
		ImVec4 Rect;
		switch (BoxType)
		{
		case 0:
			Rect = Get2DBox(Entity);
			break;
		case 1:
			Rect = Get2DBoneRect(Entity);
			break;
		case 2:
			Rect = Get2DBox(Entity);
			break;
		case 3:
			Rect = Get2DBox(Entity);
			break;
		case 4:
			Rect = Get2DBoneRect(Entity);
			break;
		default:
			break;
		}

		return Rect;
	}
}