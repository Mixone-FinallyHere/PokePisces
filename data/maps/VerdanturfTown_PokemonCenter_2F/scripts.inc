.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

VerdanturfTown_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_2F_OnTransition
	.byte 0

VerdanturfTown_PokemonCenter_2F_OnTransition:
	setrespawn HEAL_LOCATION_LILYCOVE_CITY
	call_if_lt VAR_BALL_QUEST_STATE, 4, VerdanturfTown_PokemonCenter_2F_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 4, VerdanturfTown_PokemonCenter_2F_EventScript_RemovePhillipe
	end

VerdanturfTown_PokemonCenter_2F_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

VerdanturfTown_PokemonCenter_2F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_PokemonCenter_2F_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername VerdanturfTown_PokemonCenter_2F_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 4, VerdanturfTown_PokemonCenter_2F_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, VerdanturfTown_PokemonCenter_2F_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox VerdanturfTown_PokemonCenter_2F_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_HAPPEA
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_PokemonCenter_2F_EventScript_Check2
	msgbox VerdanturfTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_PokemonCenter_2F_EventScript_BallQuestGuyTruncated::
	speakername VerdanturfTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox VerdanturfTown_PokemonCenter_2F_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_HAPPEA
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_PokemonCenter_2F_EventScript_Check2
	msgbox VerdanturfTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_PokemonCenter_2F_EventScript_Check2::
	getcaughtmon SPECIES_SHEDINJA
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_PokemonCenter_2F_EventScript_Check3
	speakername VerdanturfTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox VerdanturfTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_PokemonCenter_2F_EventScript_Check3::
	getcaughtmon SPECIES_BRAMBOOZLE
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_PokemonCenter_2F_EventScript_GiveNewBall
	speakername VerdanturfTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox VerdanturfTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_PokemonCenter_2F_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	speakername VerdanturfTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox VerdanturfTown_PokemonCenter_2F_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_PokemonCenter_2F_EventScript_NoMoreQuest::
	speakername VerdanturfTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox VerdanturfTown_PokemonCenter_2F_Text_NoMoreQuest, MSGBOX_NPC
	release
	end

VerdanturfTown_PokemonCenter_2F_Text_NamePhillipe:
	.string "Phillipe$"

VerdanturfTown_PokemonCenter_2F_Text_HaveYouCaughtThisMon:
	.string "HAPPEA BRAMBOOZLE SHEDINJA$"

VerdanturfTown_PokemonCenter_2F_Text_CaughtMonReminder:
	.string "HAPPEA, BRAMBOOZLE, and SHEDINJA...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

VerdanturfTown_PokemonCenter_2F_Text_GoCatchIt:
	.string "go GET em shithead$"

VerdanturfTown_PokemonCenter_2F_Text_YouveUnlockedNewBall:
	.string "you have unlocked new ball$"

VerdanturfTown_PokemonCenter_2F_Text_NoMoreQuest:
	.string "no more quest dood$"
