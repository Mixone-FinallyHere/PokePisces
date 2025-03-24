.set LOCALID_NURSE, 1
.set LOCALID_PHILLIPE, 3

SootopolisCity_Mart_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Mart_OnTransition
	.byte 0

SootopolisCity_Mart_OnTransition:
	setrespawn HEAL_LOCATION_JAGGRO_PASS
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
	.string "Salut! It is you again, mon\n"
	.string "super étoile! Honh honh,\l"
	.string "you have un parfaite timing,\l"
	.string "for I am in need of artistic\l"
	.string "inspiration again!\l"
	.string "Could you assister your\l"
	.string "amie, Phillipe, again?\p"
	.string "I would like to lay an eye on\n"
	.string "3 particular Pokémon.\p"
	.string "Infairno, Ferror, and Corisp.\p"
	.string "Catch those trés and show me your\n"
	.string "Pokédex, and I will make it\l"
	.string "worth your troubles.$"

SootopolisCity_Mart_Text_CaughtMonReminder:
	.string "Infairno, Ferror, and Corisp...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

SootopolisCity_Mart_Text_GoCatchIt:
	.string "I see you have not the required\n"
	.string "Pokémon, amie. You should check\l"
	.string "their locations in your Pokédex.\p"
	.string "Bonne chance!$"

SootopolisCity_Mart_Text_YouveUnlockedNewBall:
	.string "...\p"
	.string "Ah! There they are! Lovely catches!\p"
	.string "The ever-ticking clock of Infairno...\n"
	.string "Corisp's crimson crust...\l"
	.string "And Ferror, king of the mammals...\p"
	.string "Inspiration strikes! Incroyable!\n"
	.string "I must get to painting.\p"
	.string "Merci, trainer. I will put in a good\n"
	.string "word for you with Purplina;\l"
	.string "you should soon be able to\l"
	.string "purchase Fast Balls from her.\p"
	.string "Au revoir!$"

SootopolisCity_Mart_Text_GoDoPreviousQuest:
	.string "go do the last one(s)$"

SootopolisCity_Mart_Text_NoMoreQuest:
	.string "Bon aprés-midi, trainer.\n"
	.string "I have naught in the way of new\l"
	.string "jobs for you this very moment.\p"
	.string "Perhaps when we next meet,\n"
	.string "we shall work together again.$"
