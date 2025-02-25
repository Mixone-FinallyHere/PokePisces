MangrottoRockSmashRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MangrottoRockSmashRoom_OnFrame
	.byte 0

MangrottoRockSmashRoom_OnFrame:
	map_script_2 VAR_TEMP_4, 0, MangrottoRockSmashRoom_EventScript_LockPlayerIntoChoice
	map_script_2 VAR_TEMP_4, 12, MangrottoRockSmashRoom_EventScript_YouWin
	.2byte 0

MangrottoRockSmashRoom_EventScript_LockPlayerIntoChoice::
	lock
	delay 8
	applymovement OBJ_EVENT_ID_PLAYER, MangrottoRockSmashRoom_Movement_PlayerWalkUp
	goto MangrottoRockSmashRoom_EventScript_RockSmashChallenge
	release
	end

MangrottoRockSmashRoom_Movement_PlayerWalkUp:
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

MangrottoRockSmashRoom_EventScript_YouWin::
	lock
	setvar VAR_TEMP_4, 69
	special ResetSSTidalFlag
	setvar VAR_SS_TIDAL_STATE, SS_TIDAL_LAND_LILYCOVE
	msgbox MangrottoRockSmashRoom_Text_ChallengeWon, MSGBOX_AUTOCLOSE
	giveitem ITEM_TM_BREAKING_SWIPE
	warp MAP_MANGROTTO_TUNNEL, 66, 31
	waitstate
	release
	end

MangrottoRockSmashRoom_EventScript_RockSmashChallenge::
	lock
	faceplayer
	checkitem ITEM_TM_BREAKING_SWIPE
	goto_if_eq VAR_RESULT, TRUE, MangrottoRockSmashRoom_EventScript_NoMoreChallenge
	goto_if_gt VAR_TEMP_4, 0, MangrottoRockSmashRoom_EventScript_MiddleOfChallenge
	msgbox MangrottoRockSmashRoom_Text_WantToTakeOnChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MangrottoRockSmashRoom_EventScript_StartRSChallenge
	msgbox MangrottoRockSmashRoom_Text_MaybeNextTime, MSGBOX_AUTOCLOSE
	special ResetSSTidalFlag
	warp MAP_MANGROTTO_TUNNEL, 66, 31
	waitstate
	release
	end

MangrottoRockSmashRoom_EventScript_NoMoreChallenge::
	msgbox MangrottoRockSmashRoom_Text_NoMoreChallenge, MSGBOX_AUTOCLOSE
	special ResetSSTidalFlag
	warp MAP_MANGROTTO_TUNNEL, 66, 31
	waitstate
	release
	end

MangrottoRockSmashRoom_EventScript_MiddleOfChallenge::
	msgbox MangrottoRockSmashRoom_Text_MiddleOfChallenge, MSGBOX_AUTOCLOSE
	release
	end

MangrottoRockSmashRoom_EventScript_StartRSChallenge::
	setvar VAR_TEMP_4, 1
	special SetSSTidalFlag
	setvar VAR_SS_TIDAL_STATE, SS_TIDAL_DEPART_SLATEPORT
	msgbox MangrottoRockSmashRoom_Text_StartChallenge, MSGBOX_AUTOCLOSE
	release
	end

MangrottoRockSmashRoom_EventScript_FailedChallenge::
	lock
	special ResetSSTidalFlag
	setvar VAR_SS_TIDAL_STATE, SS_TIDAL_LAND_LILYCOVE
	msgbox MangrottoRockSmashRoom_Text_FailedChallenge, MSGBOX_AUTOCLOSE
	warp MAP_MANGROTTO_TUNNEL, 66, 31
	waitstate
	release
	end

MangrottoRockSmashRoom_EventScript_SmashChallengeRock::
	lockall
	goto_if_unset FLAG_BADGE01_GET, EventScript_CantSmashRock
	checkpartymove MOVE_ROCK_SMASH
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantSmashRock
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH
	msgbox Text_WantToSmash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CancelSmash
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
	addvar VAR_TEMP_4, 1
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_SmashRock
	end

MangrottoRockSmashRoom_Text_WantToTakeOnChallenge:
	.string "I see you've found my special cave!\p"
	.string "I run a bit of a game here, you see.\n"
	.string "If you can break all 11 rocks\l"
	.string "in this room within a strict\l"
	.string "step limit, I will gift you a TM!\p"
	.string "Do you think you have\n"
	.string "what it takes?$"

MangrottoRockSmashRoom_Text_MaybeNextTime:
	.string "Guess not! Please leave\n"
	.string "the cave for the next\l"
	.string "potential challenger.$"

MangrottoRockSmashRoom_Text_NoMoreChallenge:
	.string "You've already cleared\n"
	.string "my challenge! Please don't hog\l"
	.string "the cave if you've already done it.$"

MangrottoRockSmashRoom_Text_StartChallenge:
	.string "Let the challenge... begin!$"

MangrottoRockSmashRoom_Text_FailedChallenge:
	.string "Challenge... failed!\n"
	.string "You have maxed out your\l"
	.string "available steps.$"

MangrottoRockSmashRoom_Text_ChallengeWon:
	.string "Challenge... SUCCESS!\n"
	.string "Please take your reward.$"

MangrottoRockSmashRoom_Text_MiddleOfChallenge:
	.string "What are you doing talking to me?\n"
	.string "Get to smashin'!$"
