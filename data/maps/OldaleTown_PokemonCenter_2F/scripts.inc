.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

OldaleTown_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_PokemonCenter_2F_OnTransition
	.byte 0

OldaleTown_PokemonCenter_2F_OnTransition:
	setrespawn HEAL_LOCATION_LITTLEROOT_NEW
	call_if_lt VAR_BALL_QUEST_STATE, 13, OldaleTown_PokemonCenter_2F_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 13, OldaleTown_PokemonCenter_2F_EventScript_RemovePhillipe
	end

OldaleTown_PokemonCenter_2F_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

OldaleTown_PokemonCenter_2F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

OldaleTown_PokemonCenter_2F_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername OldaleTown_PokemonCenter_2F_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 13, OldaleTown_PokemonCenter_2F_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, OldaleTown_PokemonCenter_2F_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox OldaleTown_PokemonCenter_2F_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_SHISHIMA
	goto_if_eq VAR_RESULT, TRUE, OldaleTown_PokemonCenter_2F_EventScript_Check2
	msgbox OldaleTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

OldaleTown_PokemonCenter_2F_EventScript_BallQuestGuyTruncated::
	speakername OldaleTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox OldaleTown_PokemonCenter_2F_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_SHISHIMA
	goto_if_eq VAR_RESULT, TRUE, OldaleTown_PokemonCenter_2F_EventScript_Check2
	msgbox OldaleTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

OldaleTown_PokemonCenter_2F_EventScript_Check2::
	getcaughtmon SPECIES_OLFLOOKIE
	goto_if_eq VAR_RESULT, TRUE, OldaleTown_PokemonCenter_2F_EventScript_Check3
	speakername OldaleTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox OldaleTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

OldaleTown_PokemonCenter_2F_EventScript_Check3::
	getcaughtmon SPECIES_JUSTRICHA
	goto_if_eq VAR_RESULT, TRUE, OldaleTown_PokemonCenter_2F_EventScript_GiveNewBall
	speakername OldaleTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox OldaleTown_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

OldaleTown_PokemonCenter_2F_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	speakername OldaleTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox OldaleTown_PokemonCenter_2F_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	release
	end

OldaleTown_PokemonCenter_2F_EventScript_NoMoreQuest::
	speakername OldaleTown_PokemonCenter_2F_Text_NamePhillipe
	msgbox OldaleTown_PokemonCenter_2F_Text_NoMoreQuest, MSGBOX_NPC
	release
	end

OldaleTown_PokemonCenter_2F_Text_NamePhillipe:
	.string "Phillipe$"

OldaleTown_PokemonCenter_2F_Text_HaveYouCaughtThisMon:
	.string "SHISHIMA JUSTRICHA OLFLOOKIE$"

OldaleTown_PokemonCenter_2F_Text_CaughtMonReminder:
	.string "SHISHIMA, JUSTRICHA, and OLFLOOKIE...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

OldaleTown_PokemonCenter_2F_Text_GoCatchIt:
	.string "go GET em shithead$"

OldaleTown_PokemonCenter_2F_Text_YouveUnlockedNewBall:
	.string "you have unlocked new ball$"

OldaleTown_PokemonCenter_2F_Text_NoMoreQuest:
	.string "no more quest dood$"
