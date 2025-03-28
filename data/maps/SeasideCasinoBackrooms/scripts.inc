.set LOCALID_STEVEN, 4

SeasideCasinoBackrooms_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SeasideCasinoBackrooms_OnLoad
	.byte 0

SeasideCasinoBackrooms_OnLoad:
	call SeasideCasinoBackrooms_EventScript_RemoveSteven
	end

SeasideCasinoBackrooms_EventScript_RemoveSteven::
	removeobject LOCALID_STEVEN
	setflag FLAG_TEMP_11
	return

SeasideCasinoBackrooms_EventScript_StevenMeetingNorth::
	lock
	clearflag FLAG_TEMP_11
	addobject LOCALID_STEVEN
	applymovement LOCALID_STEVEN, SeasideCasinoBackrooms_Movement_StevenMeetingNorth
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	speakername SeasideCasinoBackrooms_Text_NameSteven
	msgbox SeasideCasinoBackrooms_Text_PointOfNoReturn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, SeasideCasinoBackrooms_Movement_StevenLeavesNorth
	waitmovement 0
	setvar VAR_WALLY_QUEST_STATE, 6
	removeobject LOCALID_STEVEN
	setflag FLAG_TEMP_11
	release
	end

SeasideCasinoBackrooms_Movement_StevenMeetingNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

SeasideCasinoBackrooms_Movement_StevenLeavesNorth:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	jump_2_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SeasideCasinoBackrooms_EventScript_StevenMeetingSouth::
	lock
	clearflag FLAG_TEMP_11
	addobject LOCALID_STEVEN
	applymovement LOCALID_STEVEN, SeasideCasinoBackrooms_Movement_StevenMeetingSouth
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	speakername SeasideCasinoBackrooms_Text_NameSteven
	msgbox SeasideCasinoBackrooms_Text_PointOfNoReturn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, SeasideCasinoBackrooms_Movement_StevenLeavesSouth
	waitmovement 0
	setvar VAR_WALLY_QUEST_STATE, 6
	removeobject LOCALID_STEVEN
	setflag FLAG_TEMP_11
	release
	end

SeasideCasinoBackrooms_Movement_StevenMeetingSouth:
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

SeasideCasinoBackrooms_Movement_StevenLeavesSouth:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	jump_2_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SeasideCasinoBackrooms_EventScript_Lincoln::
    trainerbattle_single TRAINER_P_LINCOLN, SeasideCasinoBackrooms_Text_LincolnIntro, SeasideCasinoBackrooms_Text_LincolnDefeated
    msgbox SeasideCasinoBackrooms_Text_LincolnPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoBackrooms_EventScript_Penn::
    trainerbattle_single TRAINER_P_PENN, SeasideCasinoBackrooms_Text_PennIntro, SeasideCasinoBackrooms_Text_PennDefeated
    msgbox SeasideCasinoBackrooms_Text_PennPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoBackrooms_EventScript_Ari::
    trainerbattle_single TRAINER_P_ARI, SeasideCasinoBackrooms_Text_AriIntro, SeasideCasinoBackrooms_Text_AriDefeated
    msgbox SeasideCasinoBackrooms_Text_AriPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoBackrooms_Text_LincolnIntro:
	.string "I've never told a lie, and I\n"
	.string "won't start now!\l"
	.string "You're a horse with a limp,\l"
	.string "I'll put you down!$"

SeasideCasinoBackrooms_Text_LincolnDefeated:
	.string "Let it be known that I fought\n"
	.string "for what was on my brain...$"

SeasideCasinoBackrooms_Text_LincolnPostBattle:
	.string "That match was worth but a penny.$"

SeasideCasinoBackrooms_Text_PennIntro:
	.string "More battles means more prize money!\n"
	.string "Let's take a shot...!$"

SeasideCasinoBackrooms_Text_PennDefeated:
	.string "...Best 2 out of 3?$"

SeasideCasinoBackrooms_Text_PennPostBattle:
	.string "...Eh. Alright. You beat me\n"
	.string "fair and square.$"

SeasideCasinoBackrooms_Text_AriIntro:
	.string "Two, four, six, eight!\n"
	.string "Who do we appreciate?\l"
	.string "This guy! It's this guy!\l"
	.string "Goooo... this... guy!$"

SeasideCasinoBackrooms_Text_AriDefeated:
	.string "I didn't cheer hard enough...$"

SeasideCasinoBackrooms_Text_AriPostBattle:
	.string "It's hard playing support when\n"
	.string "all your partner wants to do\l"
	.string "is gamble!$"

SeasideCasinoBackrooms_Text_NameSteven:
	.string "Steven$"

SeasideCasinoBackrooms_Text_PointOfNoReturn:
	.string "Hmph. That man was easy enough\n"
	.string "to trick. He's sleeping like\l"
	.string "a newborn in the casino's\l"
	.string "broom closet as we speak.\p"
	.string "This is a point of no return,\n"
	.string "{PLAYER}. Jumping the ropes\l"
	.string "will lock us in here until we\l"
	.string "find what we're looking for.\p"
	.string "Let the hesitation leave\n"
	.string "your body...$"
