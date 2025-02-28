.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

FortreeCity_Mart_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Mart_OnTransition
	.byte 0

FortreeCity_Mart_OnTransition:
	setrespawn HEAL_LOCATION_OZONE_INSTITUTE
	call_if_lt VAR_BALL_QUEST_STATE, 7, FortreeCity_Mart_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 7, FortreeCity_Mart_EventScript_RemovePhillipe
	end

FortreeCity_Mart_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

FortreeCity_Mart_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_Mart_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername FortreeCity_Mart_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 7, FortreeCity_Mart_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, FortreeCity_Mart_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox FortreeCity_Mart_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_MEGALITO
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Mart_EventScript_Check2
	msgbox FortreeCity_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_Mart_EventScript_BallQuestGuyTruncated::
	speakername FortreeCity_Mart_Text_NamePhillipe
	msgbox FortreeCity_Mart_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_MEGALITO
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Mart_EventScript_Check2
	msgbox FortreeCity_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_Mart_EventScript_Check2::
	getcaughtmon SPECIES_SOLROCK
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Mart_EventScript_Check3
	speakername FortreeCity_Mart_Text_NamePhillipe
	msgbox FortreeCity_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_Mart_EventScript_Check3::
	getcaughtmon SPECIES_KOMBAKYU
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Mart_EventScript_GiveNewBall
	speakername FortreeCity_Mart_Text_NamePhillipe
	msgbox FortreeCity_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_Mart_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	speakername FortreeCity_Mart_Text_NamePhillipe
	msgbox FortreeCity_Mart_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	release
	end

FortreeCity_Mart_EventScript_NoMoreQuest::
	speakername FortreeCity_Mart_Text_NamePhillipe
	msgbox FortreeCity_Mart_Text_NoMoreQuest, MSGBOX_NPC
	release
	end

FortreeCity_Mart_Text_NamePhillipe:
	.string "Phillipe$"

FortreeCity_Mart_Text_HaveYouCaughtThisMon:
	.string "MEGALITO KOMBAKYU SOLROCK$"

FortreeCity_Mart_Text_CaughtMonReminder:
	.string "MEGALITO, KOMBAKYU, and SOLROCK...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

FortreeCity_Mart_Text_GoCatchIt:
	.string "go GET em shithead$"

FortreeCity_Mart_Text_YouveUnlockedNewBall:
	.string "you have unlocked new ball$"

FortreeCity_Mart_Text_NoMoreQuest:
	.string "no more quest dood$"
