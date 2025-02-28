.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

DewfordTown_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_PokemonCenter_2F_OnTransition
	.byte 0

DewfordTown_PokemonCenter_2F_OnTransition:
	setrespawn HEAL_LOCATION_DEWFORD_NEW
	call_if_lt VAR_BALL_QUEST_STATE, 12, DewfordTown_PokemonCenter_2F_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 12, DewfordTown_PokemonCenter_2F_EventScript_RemovePhillipe
	end

DewfordTown_PokemonCenter_2F_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

DewfordTown_PokemonCenter_2F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

DewfordTown_PokemonCenter_2F_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername DewfordTown_PokemonCenter_2F_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 12, DewfordTown_PokemonCenter_2F_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, DewfordTown_PokemonCenter_2F_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox DewfordTown_PokemonCenter_2F_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_SKELLYWARG
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_PokemonCenter_2F_EventScript_Check2
	msgbox DewfordTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

DewfordTown_PokemonCenter_2F_EventScript_BallQuestGuyTruncated::
	speakername DewfordTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox DewfordTown_PokemonCenter_2F_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_SKELLYWARG
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_PokemonCenter_2F_EventScript_Check2
	msgbox DewfordTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

DewfordTown_PokemonCenter_2F_EventScript_Check2::
	getcaughtmon SPECIES_MARSOYART
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_PokemonCenter_2F_EventScript_Check3
	speakername DewfordTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox DewfordTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

DewfordTown_PokemonCenter_2F_EventScript_Check3::
	getcaughtmon SPECIES_ARMAGATTON
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_PokemonCenter_2F_EventScript_GiveNewBall
	speakername DewfordTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox DewfordTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

DewfordTown_PokemonCenter_2F_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	speakername DewfordTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox DewfordTown_PokemonCenter_2F_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	release
	end

DewfordTown_PokemonCenter_2F_EventScript_NoMoreQuest::
	speakername DewfordTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox DewfordTown_PokemonCenter_2F_Text_NoMoreQuest, MSGBOX_NPC
	release
	end

DewfordTown_PokemonCenter_2F_Text_NamePhillipe:
	.string "Phillipe$"

DewfordTown_PokemonCenter_2F_Text_HaveYouCaughtThisMon:
	.string "SKELLYWARG ARMAGATTON MARSOYART$"

DewfordTown_PokemonCenter_2F_Text_CaughtMonReminder:
	.string "SKELLYWARG, ARMAGATTON, and MARSOYART...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

DewfordTown_PokemonCenter_2F_Text_GoCatchIt:
	.string "go GET em shithead$"

DewfordTown_PokemonCenter_2F_Text_YouveUnlockedNewBall:
	.string "you have unlocked new ball$"

DewfordTown_PokemonCenter_2F_Text_NoMoreQuest:
	.string "no more quest dood$"
