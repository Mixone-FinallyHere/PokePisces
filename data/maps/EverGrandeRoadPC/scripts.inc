.set LOCALID_NURSE, 1

EverGrandeRoadPC_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeRoadPC_OnTransition
	.byte 0

EverGrandeRoadPC_OnTransition:
	setrespawn HEAL_LOCATION_EVER_GRANDE_ROAD
	end

EverGrandeRoadPC_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EverGrandeRoadPC_EventScript_Breadwinner::
	lock
	faceplayer
	speakername EverGrandeRoadPC_Text_NamePandou
    msgbox EverGrandeRoadPC_Text_Breadwinner, MSGBOX_NPC
    release
	end

EverGrandeRoadPC_Text_NamePandou:
	.string "Pandou$"

EverGrandeRoadPC_Text_Breadwinner:
	.string "I've been told by a few of\n"
	.string "my girls that you've been challenging\l"
	.string "them to battles.\l"
	.string "They're all much more into\l"
	.string "that kind of stuff than I am...\p"
	.string "I just ask that you treat\n"
	.string "them with a bevy of respect!$"
