.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

MauvilleCity_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_PokemonCenter_2F_OnTransition
	.byte 0

MauvilleCity_PokemonCenter_2F_OnTransition:
	setrespawn HEAL_LOCATION_SEA_MAUVILLE
	call_if_lt VAR_BALL_QUEST_STATE, 10, MauvilleCity_PokemonCenter_2F_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 10, MauvilleCity_PokemonCenter_2F_EventScript_RemovePhillipe
	end

MauvilleCity_PokemonCenter_2F_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

MauvilleCity_PokemonCenter_2F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MauvilleCity_PokemonCenter_2F_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername MauvilleCity_PokemonCenter_2F_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 10, MauvilleCity_PokemonCenter_2F_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, MauvilleCity_PokemonCenter_2F_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox MauvilleCity_PokemonCenter_2F_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_EGGNEGGMA
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_2F_EventScript_Check2
	msgbox MauvilleCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

MauvilleCity_PokemonCenter_2F_EventScript_BallQuestGuyTruncated::
	speakername MauvilleCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox MauvilleCity_PokemonCenter_2F_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_EGGNEGGMA
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_2F_EventScript_Check2
	msgbox MauvilleCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

MauvilleCity_PokemonCenter_2F_EventScript_Check2::
	getcaughtmon SPECIES_PROMISCBUS
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_2F_EventScript_Check3
	speakername MauvilleCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox MauvilleCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

MauvilleCity_PokemonCenter_2F_EventScript_Check3::
	getcaughtmon SPECIES_SWORDUC
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_2F_EventScript_GiveNewBall
	speakername MauvilleCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox MauvilleCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

MauvilleCity_PokemonCenter_2F_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	speakername MauvilleCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox MauvilleCity_PokemonCenter_2F_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	release
	end

MauvilleCity_PokemonCenter_2F_EventScript_NoMoreQuest::
	speakername MauvilleCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox MauvilleCity_PokemonCenter_2F_Text_NoMoreQuest, MSGBOX_NPC
	release
	end

MauvilleCity_PokemonCenter_2F_Text_NamePhillipe:
	.string "Phillipe$"

MauvilleCity_PokemonCenter_2F_Text_HaveYouCaughtThisMon:
	.string "EGGNEGGMA SWORDUC PROMISCBUS$"

MauvilleCity_PokemonCenter_2F_Text_CaughtMonReminder:
	.string "EGGNEGGMA, SWORDUC, and PROMISCBUS...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

MauvilleCity_PokemonCenter_2F_Text_GoCatchIt:
	.string "go GET em shithead$"

MauvilleCity_PokemonCenter_2F_Text_YouveUnlockedNewBall:
	.string "you have unlocked new ball$"

MauvilleCity_PokemonCenter_2F_Text_NoMoreQuest:
	.string "no more quest dood$"
