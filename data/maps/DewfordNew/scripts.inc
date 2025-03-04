.set LOCALID_GYMBLOCKER, 1

DewfordNew_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, DewfordNew_OnLoad
	.byte 0

DewfordNew_OnLoad:
	call DewfordNew_EventScript_SetTempFlag
	call_if_set FLAG_TEMP_12, DewfordNew_EventScript_RemoveGymBlock
	end

DewfordNew_EventScript_SetTempFlag::
	goto_if_set FLAG_FOUND_SHELLY, DewfordNew_EventScript_CheckBrawly
	return

DewfordNew_EventScript_CheckBrawly::
	goto_if_set FLAG_FOUND_BRAWLY, DewfordNew_EventScript_TempFlagSet
	return

DewfordNew_EventScript_TempFlagSet::
	setflag FLAG_TEMP_12
	return

DewfordNew_EventScript_RemoveGymBlock::
	removeobject LOCALID_GYMBLOCKER
	setflag FLAG_TEMP_11
	return

DewfordNew_EventScript_GymBlock::
	lock
	faceplayer
	goto_if_set FLAG_FOUND_SHELLY, DewfordNew_EventScript_GoFindBrawly
	goto_if_set FLAG_FOUND_BRAWLY, DewfordNew_EventScript_GoFindShelly
	msgbox DewfordNew_Text_GoFindTheLeaders, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_GoFindShelly::
	msgbox DewfordNew_Text_GoFindShelly, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_GoFindBrawly::
	msgbox DewfordNew_Text_GoFindBrawly, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_BrineyFastTravel::
	lock
	faceplayer
	clearflag FLAG_BRINEY_MIDGAME_VISIT
	setflag FLAG_BRINEY_DEWFORD_VISIT
	speakername DewfordNew_Text_NameBriney
	msgbox DewfordNew_Text_WantToVoyage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordNew_EventScript_WarpToTidal
	msgbox DewfordNew_Text_IllBeHere, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

DewfordNew_EventScript_WarpToTidal::
	msgbox DewfordNew_Text_BonVoyage, MSGBOX_DEFAULT
	speakername NULL
	warp MAP_SS_TIDAL_MID_TERIORS, 33, 4
	release
	end

DewfordNew_Text_NameBriney:
	.string "Cpt. Briney$"

DewfordNew_Text_GoFindTheLeaders:
	.string "Dewford Gym is currently closed!\n"
	.string "Sorry, but both Gym Leaders\l"
	.string "got called away to investigate\l"
	.string "suspicious activity at sea.\l"
	.string "I pray nothing is\l"
	.string "seriously wrong...\p"
	.string "They both went eastward to the\n"
	.string "oceanic routes around the\l"
	.string "Pacifidlog, Sootopolis, and\l"
	.string "Mossdeep areas. I sure\l"
	.string "hope they make it back safely...$"

DewfordNew_Text_GoFindShelly:
	.string "Dewford Gym is currently closed!\n"
	.string "Sorry, but Shelly is still\l"
	.string "somewhere out at sea.\l"
	.string "Can't open the gym without\l"
	.string "one of its leaders!\p"
	.string "I had heard from Brawly that\n"
	.string "she went to Sailor's Pause\l"
	.string "to investigate suspicious\l"
	.string "activity... hmm.$"

DewfordNew_Text_GoFindBrawly:
	.string "Dewford Gym is currently closed!\n"
	.string "Sorry, but Brawly is still\l"
	.string "somewhere out at sea.\l"
	.string "Can't open the gym without\l"
	.string "one of its leaders!\p"
	.string "I had heard from Shelly that\n"
	.string "he went to Precipike Bluff\l"
	.string "to investigate suspicious\l"
	.string "activity... hmm.$"

DewfordNew_Text_WantToVoyage:
	.string "Ahoy there {PLAYER}!\p"
	.string "The Tidal is docked and\n"
	.string "itching for another voyage.\p"
	.string "Will you be joining us?$"

DewfordNew_Text_IllBeHere:
	.string "You're always welcome aboard!\n"
	.string "Have a good one.$"

DewfordNew_Text_BonVoyage:
	.string "About time to haul anchor, then!$"
