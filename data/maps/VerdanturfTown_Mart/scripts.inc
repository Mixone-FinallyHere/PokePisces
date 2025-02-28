.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

VerdanturfTown_Mart_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_Mart_OnTransition
	.byte 0

VerdanturfTown_Mart_OnTransition:
	setrespawn HEAL_LOCATION_LILYCOVE_CITY
	call_if_lt VAR_BALL_QUEST_STATE, 5, VerdanturfTown_Mart_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 5, VerdanturfTown_Mart_EventScript_RemovePhillipe
	end

VerdanturfTown_Mart_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

VerdanturfTown_Mart_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_Mart_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername VerdanturfTown_Mart_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 5, VerdanturfTown_Mart_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, VerdanturfTown_Mart_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox VerdanturfTown_Mart_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_GOLTIGATOR
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_Mart_EventScript_Check2
	msgbox VerdanturfTown_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_Mart_EventScript_BallQuestGuyTruncated::
	speakername VerdanturfTown_Mart_Text_NamePhillipe
	msgbox VerdanturfTown_Mart_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_GOLTIGATOR
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_Mart_EventScript_Check2
	msgbox VerdanturfTown_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_Mart_EventScript_Check2::
	getcaughtmon SPECIES_PAWNIARD
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_Mart_EventScript_Check3
	speakername VerdanturfTown_Mart_Text_NamePhillipe
	msgbox VerdanturfTown_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_Mart_EventScript_Check3::
	getcaughtmon SPECIES_BLOTTA
	goto_if_eq VAR_RESULT, TRUE, VerdanturfTown_Mart_EventScript_GiveNewBall
	speakername VerdanturfTown_Mart_Text_NamePhillipe
	msgbox VerdanturfTown_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_Mart_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	speakername VerdanturfTown_Mart_Text_NamePhillipe
	msgbox VerdanturfTown_Mart_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTown_Mart_EventScript_NoMoreQuest::
	speakername VerdanturfTown_Mart_Text_NamePhillipe
	msgbox VerdanturfTown_Mart_Text_NoMoreQuest, MSGBOX_NPC
	release
	end

VerdanturfTown_Mart_Text_NamePhillipe:
	.string "Phillipe$"

VerdanturfTown_Mart_Text_HaveYouCaughtThisMon:
	.string "GOLTIGATOR BLOTTA PAWNIARD$"

VerdanturfTown_Mart_Text_CaughtMonReminder:
	.string "GOLTIGATOR, BLOTTA, and PAWNIARD...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

VerdanturfTown_Mart_Text_GoCatchIt:
	.string "go GET em shithead$"

VerdanturfTown_Mart_Text_YouveUnlockedNewBall:
	.string "you have unlocked new ball$"

VerdanturfTown_Mart_Text_NoMoreQuest:
	.string "no more quest dood$"
