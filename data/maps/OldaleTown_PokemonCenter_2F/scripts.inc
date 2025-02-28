.set LOCALID_NURSE, 1

OldaleTown_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_2F_OnTransition
	.byte 0

OldaleTown_PokemonCenter_2F_OnTransition:
	setrespawn HEAL_LOCATION_LITTLEROOT_NEW
	end

OldaleTown_PokemonCenter_2F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
