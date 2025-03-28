.set LOCALID_BREAD, 1
.set LOCALID_KITIKITI1, 5
.set LOCALID_KITIKITI2, 6
.set LOCALID_KITIKITI3, 7
.set LOCALID_KITIKITI4, 8
.set LOCALID_KITIKITI5, 9
.set LOCALID_KITIKITI6, 10
.set LOCALID_KITIKITI7, 11
.set LOCALID_KITIKITI8, 12

PerplumeMaze_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PerplumeMaze_OnLoad
	.byte 0

PerplumeMaze_OnLoad:
	call_if_lt VAR_KITIKITI_QUEST_STATE, 1, PerplumeMaze_EventScript_RemoveKitikiti
	call_if_gt VAR_KITIKITI_QUEST_STATE, 1, PerplumeMaze_EventScript_ResetKitikiti
	call_if_gt VAR_BREADWINNER_STATE, 2, PerplumeMaze_EventScript_RemoveBreadwinner
	end

PerplumeMaze_EventScript_RemoveBreadwinner::
	removeobject LOCALID_BREAD
	setflag FLAG_TEMP_19
	return

PerplumeMaze_EventScript_ResetKitikiti::
	goto_if_ge VAR_KITIKITI_QUEST_STATE, 9, PerplumeMaze_EventScript_RemoveKitikiti
	setvar VAR_KITIKITI_QUEST_STATE, 1
	return

PerplumeMaze_EventScript_RemoveKitikiti::
	removeobject LOCALID_KITIKITI1
	removeobject LOCALID_KITIKITI2
	removeobject LOCALID_KITIKITI3
	removeobject LOCALID_KITIKITI4
	removeobject LOCALID_KITIKITI5
	removeobject LOCALID_KITIKITI6
	removeobject LOCALID_KITIKITI7
	removeobject LOCALID_KITIKITI8
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	setflag FLAG_TEMP_17
	setflag FLAG_TEMP_18
	return

PerplumeMaze_EventScript_BreadwinnerEncounter::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, PerplumeMaze_Movement_PlayerWalkUpLadder
	applymovement LOCALID_BREAD, PerplumeMaze_Movement_BreadEnc
	waitmovement 0
	pike_flashscreen
	playse SE_M_SWORDS_DANCE
	applymovement OBJ_EVENT_ID_PLAYER, PerplumeMaze_Movement_PlayerBlockBread
	waitmovement 0
	turnobject LOCALID_BREAD, DIR_SOUTH
	speakername PerplumeMaze_Text_NamePandou
	msgbox PerplumeMaze_Text_BreadwinnerIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_PANDOU_3, PerplumeMaze_Text_BreadwinnerDefeat
	goto PerplumeMaze_EventScript_BreadRun
	release
	end

PerplumeMaze_Movement_PlayerWalkUpLadder:
	walk_up
	walk_up
	walk_left
	delay_8
	emote_exclamation_mark
	step_end

PerplumeMaze_Movement_BreadEnc:
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_right
	walk_slow_right
	step_end

PerplumeMaze_Movement_PlayerBlockBread:
	walk_faster_right
	face_up
	step_end

PerplumeMaze_EventScript_BreadRun::
	setvar VAR_BREADWINNER_STATE, 3
	speakername PerplumeMaze_Text_NamePandou
	msgbox PerplumeMaze_Text_BreadwinnerRunAway, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BREAD, PerplumeMaze_Movement_BreadLookAround
	waitmovement 0
	playse SE_FLEE
	applymovement LOCALID_BREAD, PerplumeMaze_Movement_BreadEscape
	waitmovement 0
	removeobject LOCALID_BREAD
	setflag FLAG_TEMP_19
	release
	end

PerplumeMaze_Movement_BreadLookAround:
	face_right
	delay_16
	face_left
	delay_16
	face_up
	delay_16
	face_down
	delay_16
	step_end

PerplumeMaze_Movement_BreadEscape:
	jump_2_up
	step_end

PerplumeMaze_EventScript_KitikitiFound::
	lock
	faceplayer
	playmoncry SPECIES_KITIKITI, CRY_MODE_NORMAL
	waitmoncry
	msgbox PerplumeMaze_Text_KitikitiFound, MSGBOX_DEFAULT
	addvar VAR_KITIKITI_QUEST_STATE, 1
	removeobject VAR_LAST_TALKED
	closemessage
	goto_if_eq VAR_KITIKITI_QUEST_STATE, 9, PerplumeMaze_EventScript_FoundAllKitikiti
	release
	end

PerplumeMaze_EventScript_FoundAllKitikiti::
	msgbox PerplumeMaze_Text_FoundAllKitikiti, MSGBOX_AUTOCLOSE
	release
	end

PerplumeMaze_EventScript_Kris::
    trainerbattle_single TRAINER_P_KRIS, PerplumeMaze_Text_KrisIntro, PerplumeMaze_Text_KrisDefeated
    msgbox PerplumeMaze_Text_KrisPostBattle, MSGBOX_AUTOCLOSE
    end

PerplumeMaze_EventScript_Susie::
    trainerbattle_single TRAINER_P_SUSIE, PerplumeMaze_Text_SusieIntro, PerplumeMaze_Text_SusieDefeated
    msgbox PerplumeMaze_Text_SusiePostBattle, MSGBOX_AUTOCLOSE
    end

PerplumeMaze_EventScript_Ralsei::
    trainerbattle_single TRAINER_P_RALSEI, PerplumeMaze_Text_RalseiIntro, PerplumeMaze_Text_RalseiDefeated
    msgbox PerplumeMaze_Text_RalseiPostBattle, MSGBOX_AUTOCLOSE
    end

PerplumeMaze_Text_KrisIntro:
	.string "...$"

PerplumeMaze_Text_KrisDefeated:
	.string "...!?$"

PerplumeMaze_Text_KrisPostBattle:
	.string "<3$"

PerplumeMaze_Text_SusieIntro:
	.string "Heh. You seem like a morose,\n"
	.string "quiet person. Just like Kris.\p"
	.string "You know...? Quiet people\n"
	.string "PISS me off.$"

PerplumeMaze_Text_SusieDefeated:
	.string "I could've had my Pawniard use\n"
	.string "Rude Buster on you, but\l"
	.string "I was holdin' back.\p"
	.string "If I weren't, you'd be dead meat!$"

PerplumeMaze_Text_SusiePostBattle:
	.string "Guess I should find Kris\n"
	.string "and get the hell outta here.$"

PerplumeMaze_Text_RalseiIntro:
	.string "Oh, hello! It's a struggle\n"
	.string "trying to keep my pals together\l"
	.string "in this maze...\p"
	.string "You... want to battle?\n"
	.string "O-Okay...$"

PerplumeMaze_Text_RalseiDefeated:
	.string "I didn't really expect to win\n"
	.string "that one without Kris and Susie...$"

PerplumeMaze_Text_RalseiPostBattle:
	.string "Maybe try practicing some Act\n"
	.string "commands when you fight? Not\l"
	.string "every encounter has to be dealt\l"
	.string "with with violence.$"

PerplumeMaze_Text_NamePandou:
	.string "Pandou$"

PerplumeMaze_Text_BreadwinnerIntro:
	.string "...Sigh...\p"
	.string "I-I surmise I can't b-bargain\n"
	.string "with you to not b-battle me again?\p"
	.string "We both know you're s-stronger...!\n"
	.string "You'd just be w-wasting both\l"
	.string "of our valuable time!\p"
	.string "And I h-have to get to wo-$"

PerplumeMaze_Text_BreadwinnerDefeat:
	.string "(He's frantically looking\n"
	.string "at his watch.)\p"
	.string "This won't d-do...!$"

PerplumeMaze_Text_BreadwinnerRunAway:
	.string "S-So that's how it's going\n"
	.string "to be, huh...\p"
	.string "Oy, vey...$"

PerplumeMaze_Text_KitikitiFound:
	.string "(You've found one of\n"
	.string "the lost Kitikiti!)$"

PerplumeMaze_Text_FoundAllKitikiti:
	.string "(You've found all eight Kitikiti!\n"
	.string "Time to tell Olimar.)$"
