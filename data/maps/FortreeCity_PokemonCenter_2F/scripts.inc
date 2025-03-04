.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

FortreeCity_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_2F_OnTransition
	.byte 0

FortreeCity_PokemonCenter_2F_OnTransition:
	setrespawn HEAL_LOCATION_OZONE_INSTITUTE
	call_if_lt VAR_BALL_QUEST_STATE, 6, FortreeCity_PokemonCenter_2F_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 6, FortreeCity_PokemonCenter_2F_EventScript_RemovePhillipe
	end

FortreeCity_PokemonCenter_2F_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

FortreeCity_PokemonCenter_2F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_2F_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername FortreeCity_PokemonCenter_2F_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 6, FortreeCity_PokemonCenter_2F_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, FortreeCity_PokemonCenter_2F_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox FortreeCity_PokemonCenter_2F_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_HAIBUN
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_PokemonCenter_2F_EventScript_Check2
	msgbox FortreeCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_PokemonCenter_2F_EventScript_BallQuestGuyTruncated::
	speakername FortreeCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox FortreeCity_PokemonCenter_2F_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_HAIBUN
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_PokemonCenter_2F_EventScript_Check2
	msgbox FortreeCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_PokemonCenter_2F_EventScript_Check2::
	getcaughtmon SPECIES_BURBUN
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_PokemonCenter_2F_EventScript_Check3
	speakername FortreeCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox FortreeCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_PokemonCenter_2F_EventScript_Check3::
	getcaughtmon SPECIES_INGBUN
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_PokemonCenter_2F_EventScript_GiveNewBall
	speakername FortreeCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox FortreeCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_PokemonCenter_2F_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	speakername FortreeCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox FortreeCity_PokemonCenter_2F_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_PokemonCenter_2F_EventScript_NoMoreQuest::
	speakername FortreeCity_PokemonCenter_2F_Text_NamePhillipe
	msgbox FortreeCity_PokemonCenter_2F_Text_NoMoreQuest, MSGBOX_NPC
	release
	end

FortreeCity_PokemonCenter_2F_Text_NamePhillipe:
	.string "Phillipe$"

FortreeCity_PokemonCenter_2F_Text_HaveYouCaughtThisMon:
	.string "HAIBUN INGBUN BURBUN$"

FortreeCity_PokemonCenter_2F_Text_CaughtMonReminder:
	.string "HAIBUN, INGBUN, and BURBUN...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

FortreeCity_PokemonCenter_2F_Text_GoCatchIt:
	.string "go GET em shithead$"

FortreeCity_PokemonCenter_2F_Text_YouveUnlockedNewBall:
	.string "you have unlocked new ball$"

FortreeCity_PokemonCenter_2F_Text_NoMoreQuest:
	.string "no more quest dood$"
