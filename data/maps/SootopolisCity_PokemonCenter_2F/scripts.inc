.set LOCALID_NURSE, 1

SootopolisCity_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_PokemonCenter_2F_OnTransition
	.byte 0

SootopolisCity_PokemonCenter_2F_OnTransition:
	setrespawn HEAL_LOCATION_COSMOSS
	call_if_lt VAR_BALL_QUEST_STATE, 1, SootopolisCity_PokemonCenter_2F_EventScript_RemovePhillipe
	call_if_gt VAR_BALL_QUEST_STATE, 1, SootopolisCity_PokemonCenter_2F_EventScript_RemovePhillipe
	end

SootopolisCity_PokemonCenter_2F_EventScript_RemovePhillipe::
	removeobject LOCALID_PHILLIPE
	setflag FLAG_TEMP_11
	return

SootopolisCity_PokemonCenter_2F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SootopolisCity_PokemonCenter_2F_EventScript_BallQuestGuy::
	lock
	faceplayer
	speakername SootopolisCity_PokemonCenter_2F_Text_NamePhillipe
	goto_if_gt VAR_BALL_QUEST_STATE, 1, SootopolisCity_PokemonCenter_2F_EventScript_NoMoreQuest
	goto_if_set FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR, SootopolisCity_PokemonCenter_2F_EventScript_BallQuestGuyTruncated
	setflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox SootopolisCity_PokemonCenter_2F_Text_HaveYouCaughtThisMon, MSGBOX_DEFAULT
	getcaughtmon SPECIES_SNOTLOUD
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_PokemonCenter_2F_EventScript_Check2
	msgbox SootopolisCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

SootopolisCity_PokemonCenter_2F_EventScript_BallQuestGuyTruncated::
	msgbox SootopolisCity_PokemonCenter_2F_Text_CaughtMonReminder, MSGBOX_DEFAULT
	getcaughtmon SPECIES_SNOTLOUD
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_PokemonCenter_2F_EventScript_Check2
	msgbox SootopolisCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

SootopolisCity_PokemonCenter_2F_EventScript_Check2::
	getcaughtmon SPECIES_SPRYTE
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_PokemonCenter_2F_EventScript_Check3
	msgbox SootopolisCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

SootopolisCity_PokemonCenter_2F_EventScript_Check3::
	getcaughtmon SPECIES_LUMELMO
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_PokemonCenter_2F_EventScript_GiveNewBall
	msgbox SootopolisCity_PokemonCenter_2F_Text_GoCatchIt, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

SootopolisCity_PokemonCenter_2F_EventScript_GiveNewBall::
	addvar VAR_BALL_QUEST_STATE, 1
	clearflag FLAG_BALL_QUEST_DIALOGUE_TRUNCATOR
	msgbox SootopolisCity_PokemonCenter_2F_Text_YouveUnlockedNewBall, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

SootopolisCity_PokemonCenter_2F_EventScript_GoDoPreviousQuest::
	msgbox SootopolisCity_PokemonCenter_2F_Text_GoDoPreviousQuest, MSGBOX_NPC
	speakername NULL
	release
	end

SootopolisCity_PokemonCenter_2F_EventScript_NoMoreQuest::
	msgbox SootopolisCity_PokemonCenter_2F_Text_NoMoreQuest, MSGBOX_NPC
	speakername NULL
	release
	end

SootopolisCity_PokemonCenter_2F_EventScript_ConfusionTut::
    msgbox SootopolisCity_PokemonCenter_2F_Text_ConfusionTut, MSGBOX_NPC
    end

SootopolisCity_PokemonCenter_2F_EventScript_SleepRestTut::
    msgbox SootopolisCity_PokemonCenter_2F_Text_SleepRestTut, MSGBOX_NPC
    end

SootopolisCity_PokemonCenter_2F_EventScript_EXPCatchUpTut::
    msgbox SootopolisCity_PokemonCenter_2F_Text_EXPCatchUpTut, MSGBOX_NPC
    end

SootopolisCity_PokemonCenter_2F_Text_ConfusionTut:
	.string "Are you maybe confused about\n"
	.string "the confusion status? Let me\l"
	.string "clear that up!\p"
	.string "When a Pokemon is confused by\n"
	.string "a move like Confuse Ray, that\l"
	.string "Pokemon has a chance to hit itself.\p"
	.string "The damage is physical or special,\n"
	.string "depending on which related stat is\l"
	.string "higher for the afflicted.\p"
	.string "Try confusing foes' Pokemon, and\n"
	.string "they'll find themselves, well,\l"
	.string "confused about why they can't\l"
	.string "stop receiving damage!$"

SootopolisCity_PokemonCenter_2F_Text_SleepRestTut:
	.string "Yawn...\p"
	.string "...Oh, huh. Sorry I seem so tired...\n"
	.string "It's from battling a lot.\p"
	.string "My favorite strategy... is sleeping\n"
	.string "moves... like Minote's Sing...\p"
	.string "It puts the enemy to sleep for\n"
	.string "a couple turns... then, when I hit\l"
	.string "'em... boom... automatic\l"
	.string "critical hit...\p"
	.string "...But that makes the sleeper\n"
	.string "wake right up...\p"
	.string "Now, with TM01...\n"
	.string "some Pokémon can use Rest...\p"
	.string "A Resting Pokémon is different\n"
	.string "than a Sleeping Pokémon...\l"
	.string "...They stay asleep longer...\l"
	.string "and can't be woken up\l"
	.string "by attacks...\p"
	.string "...Yawn. I'm boring myself...$"

SootopolisCity_PokemonCenter_2F_Text_EXPCatchUpTut:
	.string "My Snelfrend that I had caught\n"
	.string "way back in Flotshore Trail\l"
	.string "is gaining an awful lot of\l"
	.string "experience points now that I've\l"
	.string "brought it out of the box.\p"
	.string "I believe studies have shown that\n"
	.string "Pokemon will gain more experience\l"
	.string "points the further behind they are\l"
	.string "to the levels of the upcoming gym.\p"
	.string "They must really want to catch up!$"

SootopolisCity_PokemonCenter_2F_Text_NamePhillipe:
	.string "Phillipe$"

SootopolisCity_PokemonCenter_2F_Text_HaveYouCaughtThisMon:
	.string "Salut! It is you again, mon\n"
	.string "super étoile! Honh honh,\l"
	.string "you have un parfaite timing,\l"
	.string "for I am in need of artistic\l"
	.string "inspiration again!\l"
	.string "Could you assister your\l"
	.string "amie, Phillipe, again?\p"
	.string "I would like to lay an eye on\n"
	.string "3 particular Pokémon.\p"
	.string "Spryte, Lumelmo, and Snotloud.\p"
	.string "Catch those trés and show me your\n"
	.string "Pokédex, and I will make it\l"
	.string "worth your troubles.$"

SootopolisCity_PokemonCenter_2F_Text_CaughtMonReminder:
	.string "Spryte, Lumelmo, and Snotloud...\n"
	.string "I very much would like to see them!\p"
	.string "Do you have them registered\l"
	.string "in your Pokédex?$"

SootopolisCity_PokemonCenter_2F_Text_GoCatchIt:
	.string "I see you have not the required\n"
	.string "Pokémon, amie. You should check\l"
	.string "their locations in your Pokédex.\p"
	.string "Bonne chance!$"

SootopolisCity_PokemonCenter_2F_Text_YouveUnlockedNewBall:
	.string "...\p"
	.string "Ah! There they are! Lovely catches!\p"
	.string "Lumelmo's brilliant colour...\n"
	.string "Snotloud's lovely music...\l"
	.string "Spryte's segmented body...\p"
	.string "Inspiration strikes! Incroyable!\n"
	.string "I must get to painting.\p"
	.string "Merci, trainer. I will put in a good\n"
	.string "word for you with Purplina;\l"
	.string "you should soon be able to\l"
	.string "purchase Orbit Balls from her.\p"
	.string "Au revoir!$"

SootopolisCity_PokemonCenter_2F_Text_GoDoPreviousQuest:
	.string "go do the last one(s)$"

SootopolisCity_PokemonCenter_2F_Text_NoMoreQuest:
	.string "Bon aprés-midi, trainer.\n"
	.string "I have naught in the way of new\l"
	.string "jobs for you this very moment.\p"
	.string "Perhaps when we next meet,\n"
	.string "we shall work together again.$"
