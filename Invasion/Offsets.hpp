#pragma once
#include <Windows.h>
#include "Memory/ProcessManager.hpp"

class CGlobalVarsBase
{
public:
	float m_realtime; //0x0000
	int32_t m_framecount; //0x0004
	float m_frametime; //0x0008
	float m_abs_frametime; //0x000C
	int32_t m_maxclients; //0x0010
	char pad_0014[28]; //0x0014
	float m_frametime2; //0x0030
	float m_curtime; //0x0034
	float m_curtime2; //0x0038
	char pad_003C[20]; //0x003C
	int32_t m_tickcount; //0x0050
	char pad_0054[292]; //0x0054
	uint64_t m_current_map; //0x0178
	uint64_t m_current_mapname; //0x0180
};

namespace Offset
{
	inline DWORD EntityList = 0x0;
	inline DWORD Matrix = 0x0;
	inline DWORD ViewAngle = 0x0;
	inline DWORD LocalPlayerController = 0x0;
	inline DWORD LocalPlayerPawn = 0x0;
	inline DWORD PlantedC4 = 0x0;

	struct
	{
		DWORD m_flGravityScale = 0x0;
		DWORD m_iMaxHealth = 0x0;				// C_BaseEntity::m_iMaxHealth
		DWORD m_iHealth = 0x0;						// C_BaseEntity::m_iHealth
		DWORD m_pGameSceneNode = 0x0;		// C_BaseEntity::m_pGameSceneNode
		DWORD m_vecAbsVelocity = 0x0;
		DWORD m_fFlags = 0x0;
		DWORD m_iTeamNum = 0x0;
	} C_BaseEntity;

	struct
	{
		DWORD m_vecOrigin = 0x0;
	} CGameSceneNode;

	struct
	{
		DWORD m_hPawn = 0x0;
		DWORD m_iszPlayerName = 0x0;
		DWORD m_iDesiredFOV = 0x0;
		DWORD m_steamID = 0x0;
	} CBasePlayerController;

	struct
	{
		DWORD m_bPawnIsAlive = 0x0;
		DWORD m_bControllingBot = 0x0;
		DWORD m_bEverPlayedOnTeam = 0x0;
		DWORD m_hPlayerPawn = 0x0;
		DWORD m_sSanitizedPlayerName = 0x0;
		DWORD m_iPawnArmor = 0x0;
		DWORD m_bPawnHasDefuser = 0x0;
		DWORD m_bPawnHasHelmet = 0x0;
		DWORD m_iPing = 0x0;
	} CCSPlayerController;

	struct
	{
		DWORD m_pMovementServices = 0x0;		// CPlayer_MovementServices*
		DWORD m_pWeaponServices = 0x0;			// CPlayer_WeaponServices*
		DWORD m_pCameraServices = 0x0;			// CPlayer_CameraServices*
		DWORD m_pObserverServices = 0x0;
		DWORD m_vOldOrigin = 0x0;							// C_BasePlayerPawn::m_vOldOrigin
		DWORD m_hController = 0x0;
	} C_BasePlayerPawn;

	struct
	{
		DWORD m_pViewModelServices = 0x0;		// CPlayer_ViewModelServices*
		DWORD m_pClippingWeapon = 0x0;			// C_CSWeaponBase*
		DWORD m_angEyeAngles = 0x0;
		DWORD m_vecLastClipCameraPos = 0x0;
		DWORD m_flFlashMaxAlpha = 0x0;
		DWORD m_flFlashDuration = 0x0;
		DWORD m_iIDEntIndex = 0x0;
	} C_CSPlayerPawnBase;

	struct
	{

		DWORD m_pBulletServices = 0x0;			// CCSPlayer_BulletServices*
		DWORD m_bIsScoped = 0x0;
		DWORD m_bIsDefusing = 0x0;
		DWORD m_ArmorValue = 0x0;// C_CSPlayerPawn::m_ArmorValue
		DWORD m_iShotsFired = 0x0;
		DWORD m_aimPunchAngle = 0x0;			// C_CSPlayerPawn::m_aimPunchAngle
		DWORD m_aimPunchCache = 0x0;
		DWORD m_bIsBuyMenuOpen = 0x0;
		DWORD m_bWaitForNoAttack = 0x0;
		DWORD m_bSpottedByMask = 0x0; //C_CSPlayerPawn::m_entitySpottedState + EntitySpottedState_t::m_bSpottedByMask
	} C_CSPlayerPawn;

	struct
	{
		DWORD BoneArray = 0x1F0; // CSkeletonInstance_::m_modelState + CGameSceneNode_::m_vecOrigin
	} Pawn;

	bool UpdateOffsets();
}