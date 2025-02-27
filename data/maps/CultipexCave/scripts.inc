CultipexCave_MapScripts::
	.byte 0

CultipexCave_EventScript_CultipexTrigger::
	lock
	delay 4
	goto_if_set FLAG_DEFEATED_CAVE_CULTIPEX, CultipexCave_EventScript_CultipexWantsYouToLeave
	applymovement OBJ_EVENT_ID_PLAYER, CultipexCave_Movement_GoToCultipex
	waitmovement 0
	goto CultipexCave_EventScript_CultipexBattle
	release
	end

CultipexCave_Movement_GoToCultipex:
	walk_up
	face_up
	step_end

CultipexCave_EventScript_CultipexWantsYouToLeave::
	msgbox CultipexCave_Text_CultipexWantsYouToLeave, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, CultipexCave_Movement_CultipexLeave
	waitmovement 0
	release
	end

CultipexCave_Movement_CultipexLeave:
	walk_down
	step_end

CultipexCave_EventScript_CultipexBattle::
	setwildbattle SPECIES_CULTIPEX, 33
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 3, 0, 2, 0, 1
	playmoncry SPECIES_CULTIPEX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox CultipexCave_Text_BigBug, MSGBOX_DEFAULT
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	msgbox CultipexCave_Text_GivesYouFromItsHoard, MSGBOX_DEFAULT
	giveitem ITEM_SILVER_CROWN
	delay 4
	msgbox CultipexCave_Text_Begone, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_CAVE_CULTIPEX
	applymovement OBJ_EVENT_ID_PLAYER, CultipexCave_Movement_CultipexLeave2
	waitmovement 0
	release
	end

CultipexCave_Movement_CultipexLeave2:
	walk_down
	walk_down
	step_end

CultipexCave_Text_BigBug:
	.string "(It's a massive Bug Pokemon.\n"
	.string "It appears to be commanding the\l"
	.string "Pokemon in its cave through\l"
	.string "multiple different tongues...)\p"
	.string "(It begins to speak English to you.)\p"
	.string "YOU DO NOT BELONG HERE.\n"
	.string "I WILL ABOLISH YOU MYSELF.\l"
	.string "BEGONE!$"

CultipexCave_Text_GivesYouFromItsHoard:
	.string "FUFUFU...\n"
	.string "YOU POSSESS SOME STRENGTH.\p"
	.string "I WILL BEQUEETH ONTO YOU...\n"
	.string "A PRINCE'S CROWN.$"

CultipexCave_Text_Begone:
	.string "SEEK OUT ONE OF MY MANY CHILDREN...\n"
	.string "AND CROWNETH THEM PRINCE.\p"
	.string "MY KINGDOM SHALT SPREAD.$"

CultipexCave_Text_CultipexWantsYouToLeave:
	.string "BEGONE, HOMO SAPIEN.\n"
	.string "YOUR PRESENCE IN THIS CAVERN\l"
	.string "IS UNFOUNDED.$"
