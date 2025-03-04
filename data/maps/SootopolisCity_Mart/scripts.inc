.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

SootopolisCity_Mart_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Mart_OnTransition
	.byte 0

SootopolisCity_Mart_OnTransition:
	setrespawn HEAL_LOCATION_FALLARBOR_TOWN
	call_if_lt VAR_BALL_QUEST_STATE, 8, SootopolisCity_Mart_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 8, SootopolisCity_Mart_EventScript_RemovePhillipe
	end

SootopolisCity_Mart_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

SootopolisCity_Mart_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SootopolisCity_Mart_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername SootopolisCity_Mart_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 8, SootopolisCity_Mart_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, SootopolisCity_Mart_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox SootopolisCity_Mart_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_INFAIRNO
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Mart_EventScript_Check2
	msgbox SootopolisCity_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

SootopolisCity_Mart_EventScript_BallQuestGuyTruncated::
	speakername SootopolisCity_Mart_Text_NamePhillipe
	msgbox SootopolisCity_Mart_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_INFAIRNO
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Mart_EventScript_Check2
	msgbox SootopolisCity_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

SootopolisCity_Mart_EventScript_Check2::
	getcaughtmon SPECIES_CORISP
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Mart_EventScript_Check3
	speakername SootopolisCity_Mart_Text_NamePhillipe
	msgbox SootopolisCity_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

SootopolisCity_Mart_EventScript_Check3::
	getcaughtmon SPECIES_FERROR
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Mart_EventScript_GiveNewBall
	speakername SootopolisCity_Mart_Text_NamePhillipe
	msgbox SootopolisCity_Mart_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	release
	end

SootopolisCity_Mart_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	speakername SootopolisCity_Mart_Text_NamePhillipe
	msgbox SootopolisCity_Mart_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	release
	end

SootopolisCity_Mart_EventScript_NoMoreQuest::
	speakername SootopolisCity_Mart_Text_NamePhillipe
	msgbox SootopolisCity_Mart_Text_NoMoreQuest, MSGBOX_NPC
	release
	end

SootopolisCity_Mart_Text_NamePhillipe:
	.string "Phillipe$"

SootopolisCity_Mart_Text_HaveYouCaughtThisMon:
	.string "INFAIRNO FERROR CORISP$"

SootopolisCity_Mart_Text_CaughtMonReminder:
	.string "INFAIRNO, FERROR, and CORISP...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

SootopolisCity_Mart_Text_GoCatchIt:
	.string "go GET em shithead$"

SootopolisCity_Mart_Text_YouveUnlockedNewBall:
	.string "you have unlocked new ball$"

SootopolisCity_Mart_Text_NoMoreQuest:
	.string "no more quest dood$"
