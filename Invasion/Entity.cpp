#include "Entity.hpp"

bool CEntity::UpdateController(const DWORD64& PlayerControllerAddress)
{
	if (PlayerControllerAddress == 0)
		return false;
	this->Controller.Address = PlayerControllerAddress;
	if (!this->Controller.GetHealth())
		return false;
	if (!this->Controller.GetIsAlive())
		return false;
	if (!this->Controller.GetIsCtrlBot())
		return false;
	if (!this->Controller.GetConnected())
		return false;
	if (!this->Controller.GetHasHelmet())
		return false;
	if (!this->Controller.GetTeamID())
		return false;
	if (!this->Controller.GetPlayerSteamID())
		return false;
	if (!this->Controller.GetPlayerName())
		return false;

	this->Pawn.Address = this->Controller.GetPlayerhPawnAddress();//this->Controller.GetPlayerPawnAddress();
	return true;
}

bool CEntity::UpdatePawn(const DWORD64& PlayerPawnAddress)
{
	if (PlayerPawnAddress == 0)
		return false;
	this->Pawn.Address = PlayerPawnAddress;

	if (!this->Pawn.GetCameraPos())
		return false;
	if (!this->Pawn.GetPos())
		return false;
	if (!this->Pawn.GetViewAngle())
		return false;
	if (!this->Pawn.GetAimPunchAngle())
		return false;
	if (!this->Pawn.GetShotsFired())
		return false;
	if (!this->Pawn.GetHealth())
		return false;
	if (!this->Pawn.GetArmor())
		return false;
	if (!this->Pawn.GetTeamID())
		return false;
	if (!this->Pawn.GetSpotted())
		return false;
	if (!this->Pawn.GetFFlags())
		return false;
	if (!this->Pawn.GetFlashDuration())
		return false;
	if (!this->Pawn.GetVelocity())
		return false;
	if (!this->Pawn.GetAimPunchCache())
		return false;
	if (!this->Pawn.BoneData.UpdateAllBoneData(PlayerPawnAddress))
		return false;

	return true;
}

bool PlayerController::GetTeamID()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_iTeamNum, this->TeamID);
}

bool PlayerController::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_iHealth, this->Health);
}

bool PlayerController::GetIsAlive()
{
	return GetDataAddressWithOffset<int>(Address, Offset::CCSPlayerController.m_bPawnIsAlive, this->AliveStatus);
}

bool PlayerController::GetIsCtrlBot()
{
	return GetDataAddressWithOffset<int>(Address, Offset::CCSPlayerController.m_bControllingBot, this->CtrlBot);
}

bool PlayerController::GetConnected()
{
	return GetDataAddressWithOffset<bool>(Address, Offset::CCSPlayerController.m_bEverPlayedOnTeam, this->Connected);
}

bool PlayerController::GetHasHelmet()
{
	return GetDataAddressWithOffset<bool>(Address, Offset::CCSPlayerController.m_bPawnHasHelmet, this->HasHelmet);
}

bool PlayerController::GetPlayerName()
{
	char Buffer[MAX_PATH]{};

	if (!ProcessMgr.ReadMemory(Address + Offset::CBasePlayerController.m_iszPlayerName, Buffer, MAX_PATH))
		return false;
	if (!this->SteamID)
		this->PlayerName = "BOT " + std::string(Buffer);
	else
		this->PlayerName = Buffer;
	if (this->PlayerName.empty())
		this->PlayerName = "Name_None";

	return true;
}

bool PlayerController::GetPlayerSteamID()
{
	return GetDataAddressWithOffset<INT64>(Address, Offset::CBasePlayerController.m_steamID, this->SteamID);
}

bool PlayerPawn::GetViewAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset::C_CSPlayerPawnBase.m_angEyeAngles, this->ViewAngle);
}

bool PlayerPawn::GetCameraPos()
{
	return GetDataAddressWithOffset<Vec3>(Address, Offset::C_CSPlayerPawnBase.m_vecLastClipCameraPos, this->CameraPos);
}

bool PlayerPawn::GetSpotted()
{
	return GetDataAddressWithOffset<DWORD64>(Address, Offset::C_CSPlayerPawn.m_bSpottedByMask, this->bSpottedByMask);
}

bool PlayerPawn::GetShotsFired()
{
	return GetDataAddressWithOffset<DWORD>(Address, Offset::C_CSPlayerPawn.m_iShotsFired, this->ShotsFired);
}

bool PlayerPawn::GetAimPunchAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset::C_CSPlayerPawn.m_aimPunchAngle, this->AimPunchAngle);
}

bool PlayerPawn::GetTeamID()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_iTeamNum, this->TeamID);
}

bool PlayerPawn::GetAimPunchCache()
{
	return GetDataAddressWithOffset<C_UTL_VECTOR>(Address, Offset::C_CSPlayerPawn.m_aimPunchCache, this->AimPunchCache);
}

DWORD64 PlayerController::GetPlayerPawnAddress()
{
	DWORD64 EntityPawnListEntry = 0;
	DWORD64 EntityPawnAddress = 0;

	if (!GetDataAddressWithOffset<DWORD>(Address, Offset::CCSPlayerController.m_hPlayerPawn, this->Pawn))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF), EntityPawnAddress))
		return 0;

	return EntityPawnAddress;
}

DWORD64 PlayerController::GetPlayerhPawnAddress()
{
	DWORD64 EntityPawnListEntry = 0;
	DWORD64 EntityPawnAddress = 0;

	if (!GetDataAddressWithOffset<DWORD>(Address, Offset::CBasePlayerController.m_hPawn, this->Pawn))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF), EntityPawnAddress))
		return 0;

	return EntityPawnAddress;
}

bool PlayerPawn::GetPos()
{
	DWORD64 GameSceneNode;
	if (!ProcessMgr.ReadMemory<uintptr_t>(Address + Offset::C_BaseEntity.m_pGameSceneNode, GameSceneNode))
		return false;

	return ProcessMgr.ReadMemory<Vec3>(GameSceneNode + Offset::CGameSceneNode.m_vecOrigin, this->Pos);
}

bool PlayerPawn::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_iHealth, this->Health);
}

bool PlayerPawn::GetArmor()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_CSPlayerPawn.m_ArmorValue, this->Armor);
}

bool PlayerPawn::GetFFlags()
{
	return GetDataAddressWithOffset<int>(Address, Offset::C_BaseEntity.m_fFlags, this->fFlags);
}

bool PlayerPawn::GetFlashDuration()
{
	return ProcessMgr.ReadMemory(Address + Offset::C_CSPlayerPawnBase.m_flFlashDuration, this->FlashDuration);
}

bool PlayerPawn::GetVelocity()
{
	if (!ProcessMgr.ReadMemory(Address + Offset::C_BaseEntity.m_vecAbsVelocity, this->Velocity))
		return false;
	this->Speed = sqrt(this->Velocity.x * this->Velocity.x + this->Velocity.y * this->Velocity.y);
	return true;
}

bool CEntity::IsAlive()
{
	return (this->Controller.AliveStatus == 1 || this->Controller.CtrlBot == 1) && this->Pawn.Health > 0;
}

bool CEntity::ESPAlive()
{
	return this->Pawn.Health > 0;
}

bool CEntity::IsInScreen()
{
	return gGame.View.WorldToScreen(this->Pawn.Pos, this->Pawn.ScreenPos);
}

CBone CEntity::GetBone() const
{
	if (this->Pawn.Address == 0)
		return CBone{};
	return this->Pawn.BoneData;
}