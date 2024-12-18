#pragma once
#include "Game.hpp"
#include "View.hpp"
#include "Bone.hpp"
#include "Memory/Globals.hpp"
#include <map>

struct C_UTL_VECTOR
{
	DWORD64 Count = 0;
	DWORD64 Data = 0;
};

class PlayerController
{
public:
	DWORD64 Address = 0;
	int Money = 0;
	int CashSpent = 0;
	int CashSpentTotal = 0;
	int TeamID = 0;
	int Health = 0;
	int AliveStatus = 0;
	int CtrlBot = 0;
	bool Connected = false;
	bool HasHelmet = false;
	INT64 SteamID = 0;
	std::string PlayerName;
	DWORD Pawn = 0;
public:
	bool GetTeamID();
	bool GetHealth();
	bool GetIsAlive();
	bool GetIsCtrlBot();
	bool GetConnected();
	bool GetHasHelmet();
	bool GetPlayerSteamID();
	bool GetPlayerName();
	DWORD64 GetPlayerPawnAddress();
	DWORD64 GetPlayerhPawnAddress();
};

class PlayerPawn
{
public:
	enum class Flags
	{
		NONE,
		IN_AIR = 1 << 0,
		IN_CROUCH = 1 << 1
	};

	DWORD64 Address = 0;
	CBone BoneData;
	Vec2 ViewAngle;
	Vec3 Pos;
	Vec2 ScreenPos;
	Vec3 CameraPos;
	Vec3 Velocity;
	float Speed;
	std::string WeaponName;
	DWORD ShotsFired;
	Vec2 AimPunchAngle;
	C_UTL_VECTOR AimPunchCache;
	int Health;
	int Armor;
	int TeamID;
	DWORD64 bSpottedByMask;
	int fFlags;
	float FlashDuration;
	bool isDefusing;


public:
	bool GetPos();
	bool GetViewAngle();
	bool GetCameraPos();
	bool GetShotsFired();
	bool GetAimPunchAngle();
	bool GetHealth();
	bool GetTeamID();
	bool GetSpotted();
	bool GetFFlags();
	bool GetAimPunchCache();
	bool GetArmor();
	bool GetFlashDuration();
	bool GetVelocity();

	constexpr bool HasFlag(const Flags Flag) const noexcept {
		return fFlags & (int)Flag;
	}
};

class CEntity
{
public:
	PlayerController Controller;
	PlayerPawn Pawn;
public:
	// ��������
	bool UpdateController(const DWORD64& PlayerControllerAddress);
	bool UpdatePawn(const DWORD64& PlayerPawnAddress);
	// �Ƿ���
	bool IsAlive();
	bool ESPAlive();
	// �Ƿ�����Ļ��
	bool IsInScreen();
	// ��ȡ��������
	CBone GetBone() const;
};