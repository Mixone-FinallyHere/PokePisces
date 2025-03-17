.set LOCALID_MAY, 1
.set LOCALID_BRENDAN, 2

ShunyongBattleArena_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ShunyongBattleArena_OnFrame
	.byte 0

ShunyongBattleArena_OnFrame:
	map_script_2 VAR_TEMP_4, 0, ShunyongBattleArena_EventScript_FacingShunyong
	.2byte 0

ShunyongBattleArena_EventScript_FacingShunyong::
	lock
	setvar VAR_TEMP_4, 1
	msgbox ShunyongBattleArena_Text_LoreDump, MSGBOX_DEFAULT
	closemessage
	delay 4
	fadenewbgm MUS_PISCES_TITLE
	delay 16
	msgbox ShunyongBattleArena_Text_ThisIsYourFinalTest, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_SHUNYONG, CRY_MODE_NORMAL
	waitmoncry
	doshunyongbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShunyongBattleArena_EventScript_CantEscape
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShunyongBattleArena_EventScript_CantEscape
	goto ShunyongBattleArena_EventScript_ShunyongVictory
	release
	end

ShunyongBattleArena_EventScript_CantEscape::
	lock
	msgbox ShunyongBattleArena_Text_CantEscapeShunyong, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_SHUNYONG, CRY_MODE_NORMAL
	waitmoncry
	doshunyongbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShunyongBattleArena_EventScript_CantEscape
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShunyongBattleArena_EventScript_CantEscape
	goto ShunyongBattleArena_EventScript_ShunyongVictory
	release
	end

ShunyongBattleArena_EventScript_ShunyongVictory::
	lock
	delay 8
	msgbox ShunyongBattleArena_Text_YouBeatShunyong, MSGBOX_DEFAULT
	turnobject LOCALID_MAY, DIR_EAST
	turnobject LOCALID_BRENDAN, DIR_WEST
	msgbox ShunyongBattleArena_Text_TimeToGetOutOfHere, MSGBOX_DEFAULT
	setvar VAR_PISCES_STORY_PROGRESS, 12
	closemessage
	delay 16
	warp MAP_EVER_GRANDE_PEAK, 39, 47
	waitstate
	release
	end

ShunyongBattleArena_EventScripts_ShunyongTest::
	lock
	doshunyongbattle
	release
	end

ShunyongBattleArena_Text_LoreDump:
	.string "$"

ShunyongBattleArena_Text_ThisIsYourFinalTest:
	.string "$"

ShunyongBattleArena_Text_CantEscapeShunyong:
	.string "$"

ShunyongBattleArena_Text_YouBeatShunyong:
	.string "$"

ShunyongBattleArena_Text_TimeToGetOutOfHere:
	.string "$"
