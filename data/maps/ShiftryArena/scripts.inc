ShiftryArena_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, ShiftryArena_OnLoad
	.byte 0

ShiftryArena_OnLoad:
	call_if_set FLAG_DEFEATED_FOREST_SHIFTRY, ShiftryArena_EventScript_RemoveShiftry
	end

ShiftryArena_EventScript_RemoveShiftry::
	setvar VAR_TEMP_4, 1
	setmetatile 9, 3, METATILE_General_Grass, FALSE
	setmetatile 8, 4, METATILE_General_Grass, FALSE
	setmetatile 9, 4, METATILE_General_Grass, FALSE
	setmetatile 10, 4, METATILE_General_Grass, FALSE
	special DrawWholeMapView
	return

ShiftryArena_EventScript_ShiftryTrigger::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, ShiftryArena_Movement_GotoShiftry
	waitmovement 0
	goto ShiftryArena_EventScript_ShiftryBattle
	release
	end

ShiftryArena_Movement_GotoShiftry:
	walk_up
	walk_right
	walk_up
	walk_right
	face_up
	step_end

ShiftryArena_EventScript_ShiftryBattle::
	setwildbattle SPECIES_SHIFTRY, 32
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 3, 1
	playmoncry SPECIES_SHIFTRY, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox ShiftryArena_Text_ShiftryIsAngry, MSGBOX_DEFAULT
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	setflag FLAG_DEFEATED_FOREST_SHIFTRY
	setvar VAR_TEMP_4, 1
	setmetatile 9, 3, METATILE_General_Grass, FALSE
	setmetatile 8, 4, METATILE_General_Grass, FALSE
	setmetatile 9, 4, METATILE_General_Grass, FALSE
	setmetatile 10, 4, METATILE_General_Grass, FALSE
	special DrawWholeMapView
	msgbox ShiftryArena_Text_ItLeftBehindSomething, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_EERIE_MASK
	closemessage
	delay 4
	release
	end

ShiftryArena_Text_ShiftryIsAngry:
	.string "(It seems to be a Shiftry.\n"
	.string "It's twitching like it's agitated...)\p"
	.string "(It glares at you,\n"
	.string "and lunges into a strike!)$"

ShiftryArena_Text_ItLeftBehindSomething:
	.string "(The Shiftry, defeated,\n"
	.string "caught a strong wind and\l"
	.string "flew off to places unknown.)\p"
	.string "(It left behind something.)$"
