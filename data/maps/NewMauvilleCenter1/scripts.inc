.set LOCALID_NURSE, 1

NewMauvilleCenter1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewMauvilleCenter1_OnTransition
	.byte 0

NewMauvilleCenter1_OnTransition:
	setrespawn HEAL_LOCATION_MAUVILLE_NEW
	end

NewMauvilleCenter1_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
