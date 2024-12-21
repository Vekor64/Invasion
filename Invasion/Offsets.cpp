#include "Offsets.hpp"
#include "Configs.hpp"
#include "Utils/YAML.h"
#include <filesystem>

namespace fs = std::filesystem;

bool Offset::UpdateOffsets()
{
	std::string offsetPath = MenuConfig::path + "\\offsets.yaml";
	if (!fs::exists(offsetPath))
	{
		std::cerr << "Failed to locate offsets file: " << offsetPath << std::endl;
		return false;
	}

	YAML::Node offset = YAML::LoadFile(offsetPath);

	Offset::EntityList = ReadData(offset["client_dll"]["dwEntityList"], 0);
	Offset::LocalPlayerController = ReadData(offset["client_dll"]["dwLocalPlayerController"], 0);
	Offset::Matrix = ReadData(offset["client_dll"]["dwViewMatrix"], 0);
	Offset::ViewAngle = ReadData(offset["client_dll"]["dwViewAngles"], 0);
	Offset::LocalPlayerPawn = ReadData(offset["client_dll"]["dwLocalPlayerPawn"], 0);
	Offset::PlantedC4 = ReadData(offset["client_dll"]["dwPlantedC4"], 0);

	Offset::C_BaseEntity.m_flGravityScale = ReadData(offset["client_dll"]["C_BaseEntity"]["m_flGravityScale"], 0);
	Offset::C_BaseEntity.m_iMaxHealth = ReadData(offset["client_dll"]["C_BaseEntity"]["m_iMaxHealth"], 0);
	Offset::C_BaseEntity.m_iHealth = ReadData(offset["client_dll"]["C_BaseEntity"]["m_iHealth"], 0);
	Offset::C_BaseEntity.m_pGameSceneNode = ReadData(offset["client_dll"]["C_BaseEntity"]["m_pGameSceneNode"], 0);
	Offset::C_BaseEntity.m_vecAbsVelocity = ReadData(offset["client_dll"]["C_BaseEntity"]["m_vecAbsVelocity"], 0);
	Offset::C_BaseEntity.m_iTeamNum = ReadData(offset["client_dll"]["C_BaseEntity"]["m_iTeamNum"], 0);
	Offset::C_BaseEntity.m_fFlags = ReadData(offset["client_dll"]["C_BaseEntity"]["m_fFlags"], 0);

	Offset::CGameSceneNode.m_vecOrigin = ReadData(offset["client_dll"]["CGameSceneNode"]["m_vecOrigin"], 0);

	Offset::CBasePlayerController.m_hPawn = ReadData(offset["client_dll"]["CBasePlayerController"]["m_hPawn"], 0);
	Offset::CBasePlayerController.m_iszPlayerName = ReadData(offset["client_dll"]["CBasePlayerController"]["m_iszPlayerName"], 0);
	Offset::CBasePlayerController.m_iDesiredFOV = ReadData(offset["client_dll"]["CBasePlayerController"]["m_iDesiredFOV"], 0);
	Offset::CBasePlayerController.m_steamID = ReadData(offset["client_dll"]["CBasePlayerController"]["m_steamID"], 0);

	Offset::CCSPlayerController.m_bPawnIsAlive = ReadData(offset["client_dll"]["CCSPlayerController"]["m_bPawnIsAlive"], 0);
	Offset::CCSPlayerController.m_bControllingBot = ReadData(offset["client_dll"]["CCSPlayerController"]["m_bControllingBot"], 0);
	Offset::CCSPlayerController.m_bEverPlayedOnTeam = ReadData(offset["client_dll"]["CCSPlayerController"]["m_bEverPlayedOnTeam"], 0);
	Offset::CCSPlayerController.m_hPlayerPawn = ReadData(offset["client_dll"]["CCSPlayerController"]["m_hPlayerPawn"], 0);
	Offset::CCSPlayerController.m_sSanitizedPlayerName = ReadData(offset["client_dll"]["CCSPlayerController"]["m_sSanitizedPlayerName"], 0);
	Offset::CCSPlayerController.m_iPawnArmor = ReadData(offset["client_dll"]["CCSPlayerController"]["m_iPawnArmor"], 0);
	Offset::CCSPlayerController.m_bPawnHasDefuser = ReadData(offset["client_dll"]["CCSPlayerController"]["m_bPawnHasDefuser"], 0);
	Offset::CCSPlayerController.m_bPawnHasHelmet = ReadData(offset["client_dll"]["CCSPlayerController"]["m_bPawnHasHelmet"], 0);
	Offset::CCSPlayerController.m_iPing = ReadData(offset["client_dll"]["CCSPlayerController"]["m_iPing"], 0);

	Offset::C_BasePlayerPawn.m_pMovementServices = ReadData(offset["client_dll"]["C_BasePlayerPawn"]["m_pMovementServices"], 0);
	Offset::C_BasePlayerPawn.m_pWeaponServices = ReadData(offset["client_dll"]["C_BasePlayerPawn"]["m_pWeaponServices"], 0);
	Offset::C_BasePlayerPawn.m_pCameraServices = ReadData(offset["client_dll"]["C_BasePlayerPawn"]["m_pCameraServices"], 0);
	Offset::C_BasePlayerPawn.m_pObserverServices = ReadData(offset["client_dll"]["C_BasePlayerPawn"]["m_pObserverServices"], 0);
	Offset::C_BasePlayerPawn.m_vOldOrigin = ReadData(offset["client_dll"]["C_BasePlayerPawn"]["m_vOldOrigin"], 0);
	Offset::C_BasePlayerPawn.m_hController = ReadData(offset["client_dll"]["C_BasePlayerPawn"]["m_hController"], 0);

	Offset::C_CSPlayerPawnBase.m_pViewModelServices = ReadData(offset["client_dll"]["C_CSPlayerPawnBase"]["m_pViewModelServices"], 0);
	Offset::C_CSPlayerPawnBase.m_pClippingWeapon = ReadData(offset["client_dll"]["C_CSPlayerPawnBase"]["m_pClippingWeapon"], 0);
	Offset::C_CSPlayerPawnBase.m_angEyeAngles = ReadData(offset["client_dll"]["C_CSPlayerPawnBase"]["m_angEyeAngles"], 0);
	Offset::C_CSPlayerPawnBase.m_vecLastClipCameraPos = ReadData(offset["client_dll"]["C_CSPlayerPawnBase"]["m_vecLastClipCameraPos"], 0);
	Offset::C_CSPlayerPawnBase.m_flFlashMaxAlpha = ReadData(offset["client_dll"]["C_CSPlayerPawnBase"]["m_flFlashMaxAlpha"], 0);
	Offset::C_CSPlayerPawnBase.m_flFlashDuration = ReadData(offset["client_dll"]["C_CSPlayerPawnBase"]["m_flFlashDuration"], 0);
	Offset::C_CSPlayerPawnBase.m_iIDEntIndex = ReadData(offset["client_dll"]["C_CSPlayerPawnBase"]["m_iIDEntIndex"], 0);

	Offset::C_CSPlayerPawn.m_pBulletServices = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_pBulletServices"], 0);
	Offset::C_CSPlayerPawn.m_bIsScoped = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_bIsScoped"], 0);
	Offset::C_CSPlayerPawn.m_bIsDefusing = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_bIsDefusing"], 0);
	Offset::C_CSPlayerPawn.m_ArmorValue = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_ArmorValue"], 0);
	Offset::C_CSPlayerPawn.m_iShotsFired = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_iShotsFired"], 0);
	Offset::C_CSPlayerPawn.m_aimPunchAngle = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_aimPunchAngle"], 0);
	Offset::C_CSPlayerPawn.m_aimPunchCache = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_aimPunchCache"], 0);
	Offset::C_CSPlayerPawn.m_bIsBuyMenuOpen = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_bIsBuyMenuOpen"], 0);
	Offset::C_CSPlayerPawn.m_bWaitForNoAttack = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_bWaitForNoAttack"], 0);
	Offset::C_CSPlayerPawn.m_bSpottedByMask = ReadData(offset["client_dll"]["C_CSPlayerPawn"]["m_entitySpottedState"], 0) + ReadData(offset["client_dll"]["EntitySpottedState_t"]["m_bSpottedByMask"], 0);

	Offset::WeaponBaseData.WeaponDataPTR = ReadData(offset["client_dll"]["C_BaseEntity"]["m_nSubclassID"], 0) + 0x08;
	Offset::WeaponBaseData.szName = ReadData(offset["client_dll"]["CCSWeaponBaseVData"]["m_szName"], 0);
	Offset::WeaponBaseData.Clip1 = ReadData(offset["client_dll"]["C_BasePlayerWeapon"]["m_iClip1"], 0);
	Offset::WeaponBaseData.MaxClip = ReadData(offset["client_dll"]["CBasePlayerWeaponVData"]["m_iMaxClip1"], 0);
	Offset::WeaponBaseData.CycleTime = ReadData(offset["client_dll"]["CCSWeaponBaseVData"]["m_flCycleTime"], 0);
	Offset::WeaponBaseData.Penetration = ReadData(offset["client_dll"]["CCSWeaponBaseVData"]["m_flPenetration"], 0);
	Offset::WeaponBaseData.WeaponType = ReadData(offset["client_dll"]["CCSWeaponBaseVData"]["m_WeaponType"], 0);
	Offset::WeaponBaseData.Inaccuracy = ReadData(offset["client_dll"]["CCSWeaponBaseVData"]["m_flInaccuracyMove"], 0);
	Offset::WeaponBaseData.inReload = ReadData(offset["client_dll"]["C_CSWeaponBase"]["m_bInReload"], 0);
	Offset::WeaponBaseData.m_nNumBullets = ReadData(offset["client_dll"]["CCSWeaponBaseVData"]["m_nNumBullets"], 0);
	Offset::WeaponBaseData.ActiveWeapon = ReadData(offset["client_dll"]["CPlayer_WeaponServices"]["m_hActiveWeapon"], 0);
	Offset::WeaponBaseData.Item = ReadData(offset["client_dll"]["C_AttributeContainer"]["m_Item"], 0);
	Offset::WeaponBaseData.ItemDefinitionIndex = ReadData(offset["client_dll"]["C_EconItemView"]["m_iItemDefinitionIndex"], 0);
	Offset::WeaponBaseData.m_MeshGroupMask = ReadData(offset["client_dll"]["CModelState"]["m_MeshGroupMask"], 0);
	Offset::WeaponBaseData.m_bIsFullAuto = ReadData(offset["client_dll"]["CCSWeaponBaseVData"]["m_bIsFullAuto"], 0);

	return true;
}