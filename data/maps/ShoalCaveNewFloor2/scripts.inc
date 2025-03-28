.set LOCALID_BRAWLY, 6
.set LOCALID_ROCK_1_PRE, 5
.set LOCALID_ROCK_1_POST, 7
.set LOCALID_ROCK_2_PRE, 4
.set LOCALID_ROCK_2_POST, 8
.set LOCALID_DELINQUENT_1, 9
.set LOCALID_DELINQUENT_2, 10

ShoalCaveNewFloor2_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, ShoalCaveNewFloor2_OnLoad
	.byte 0

ShoalCaveNewFloor2_OnLoad:
	call ShoalCaveNewFloor2_EventScript_RemovePostBoulders
	call_if_set FLAG_FOUND_BRAWLY, ShoalCaveNewFloor2_EventScript_RemoveBrawly
	end

ShoalCaveNewFloor2_EventScript_RemovePostBoulders::
	removeobject LOCALID_ROCK_1_POST
	setflag FLAG_TEMP_14
	removeobject LOCALID_ROCK_2_POST
	setflag FLAG_TEMP_16
	removeobject LOCALID_DELINQUENT_2
	setflag FLAG_TEMP_18
	return

ShoalCaveNewFloor2_EventScript_RemoveBrawly::
	removeobject LOCALID_BRAWLY
	setflag FLAG_TEMP_11
	return

ShoalCaveNewFloor2_EventScript_Brawly::
	lockall
	faceplayer
	goto_if_set FLAG_FOUND_BRAWLY, ShoalCaveNewFloor2_EventScript_BrawlyGone
	msgbox ShoalCaveNewFloor2_Text_BrawlyGreeting, MSGBOX_DEFAULT
	setflag FLAG_FOUND_BRAWLY
	delay 32
	closemessage
	fadescreen FADE_TO_BLACK
	delay 8
	playse SE_EXIT
	removeobject LOCALID_BRAWLY
	setflag FLAG_TEMP_11
	delay 8
	fadescreen FADE_FROM_BLACK
	releaseall
	end

ShoalCaveNewFloor2_EventScript_BrawlyGone::
	msgbox ShoalCaveNewFloor2_Text_BrawlyGone, MSGBOX_AUTOCLOSE
	releaseall
	end

ShoalCaveNewFloor2_EventScript_StrengthBoulder1::
	lockall
	goto_if_unset FLAG_BADGE05_GET, ShoalCaveNewFloor2_EventScript_CantStrength
	checkpartymove MOVE_STRENGTH
	goto_if_eq VAR_RESULT, PARTY_SIZE, ShoalCaveNewFloor2_EventScript_CantStrength
	msgbox ShoalCaveNewFloor2_Text_WantToStrength, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ShoalCaveNewFloor2_EventScript_CancelStrength
	closemessage
	playse SE_M_VITAL_THROW2
	delay 4
	applymovement LOCALID_ROCK_1_PRE, ShoalCaveNewFloor2_Movement_PushRock1
	waitmovement 0
	removeobject LOCALID_ROCK_1_PRE
	setflag FLAG_TEMP_13
	clearflag FLAG_TEMP_14
	addobject LOCALID_ROCK_1_POST
	playse SE_ICE_STAIRS
	releaseall
	end

ShoalCaveNewFloor2_Movement_PushRock1:
	slide_up
	slide_up
	step_end

ShoalCaveNewFloor2_EventScript_StrengthBoulder1Post::
	lock
	msgbox ShoalCaveNewFloor2_Text_Dangerous, MSGBOX_AUTOCLOSE
	release
	end

ShoalCaveNewFloor2_EventScript_StrengthBoulder2::
	lockall
	goto_if_unset FLAG_BADGE05_GET, ShoalCaveNewFloor2_EventScript_CantStrength
	checkpartymove MOVE_STRENGTH
	goto_if_eq VAR_RESULT, PARTY_SIZE, ShoalCaveNewFloor2_EventScript_CantStrength
	msgbox ShoalCaveNewFloor2_Text_WantToStrength, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ShoalCaveNewFloor2_EventScript_CancelStrength
	closemessage
	playse SE_M_VITAL_THROW2
	delay 4
	applymovement LOCALID_ROCK_2_PRE, ShoalCaveNewFloor2_Movement_PushRock2
	waitmovement 0
	removeobject LOCALID_ROCK_2_PRE
	setflag FLAG_TEMP_15
	clearflag FLAG_TEMP_16
	addobject LOCALID_ROCK_2_POST
	playse SE_ICE_STAIRS
	releaseall
	end

ShoalCaveNewFloor2_Movement_PushRock2:
	slide_down
	slide_down
	step_end

ShoalCaveNewFloor2_EventScript_StrengthBoulder2Post::
	lock
	msgbox ShoalCaveNewFloor2_Text_Dangerous, MSGBOX_AUTOCLOSE
	release
	end

ShoalCaveNewFloor2_EventScript_StrengthLady::
	lockall
	goto_if_unset FLAG_BADGE05_GET, ShoalCaveNewFloor2_EventScript_CantStrength2
	checkpartymove MOVE_STRENGTH
	goto_if_eq VAR_RESULT, PARTY_SIZE, ShoalCaveNewFloor2_EventScript_CantStrength2
	msgbox ShoalCaveNewFloor2_Text_WantToStrength2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ShoalCaveNewFloor2_EventScript_CancelStrength
	closemessage
	playse SE_M_VITAL_THROW2
	delay 4
	applymovement LOCALID_DELINQUENT_1, ShoalCaveNewFloor2_Movement_PushLady
	waitmovement 0
	removeobject LOCALID_DELINQUENT_1
	setflag FLAG_TEMP_17
	clearflag FLAG_TEMP_18
	addobject LOCALID_DELINQUENT_2
	playse SE_ICE_STAIRS
	releaseall
	end

ShoalCaveNewFloor2_Movement_PushLady:
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	slide_right
	step_end

ShoalCaveNewFloor2_EventScript_StrengthLadyPost::
	lock
	faceplayer
	msgbox ShoalCaveNewFloor2_Text_WhyDidYouDoThat, MSGBOX_AUTOCLOSE
	release
	end

ShoalCaveNewFloor2_EventScript_CantStrength::
	msgbox ShoalCaveNewFloor2_Text_CantStrength, MSGBOX_DEFAULT
	releaseall
	end

ShoalCaveNewFloor2_EventScript_CantStrength2::
	msgbox ShoalCaveNewFloor2_Text_CantStrength2, MSGBOX_DEFAULT
	releaseall
	end

ShoalCaveNewFloor2_EventScript_CancelStrength::
	closemessage
	releaseall
	end

ShoalCaveNewFloor2_EventScript_Magnus::
    trainerbattle_single TRAINER_P_MAGNUS, ShoalCaveNewFloor2_Text_MagnusIntro, ShoalCaveNewFloor2_Text_MagnusDefeated
    msgbox ShoalCaveNewFloor2_Text_MagnusPostBattle, MSGBOX_AUTOCLOSE
    end

ShoalCaveNewFloor2_EventScript_Juneau::
    trainerbattle_single TRAINER_P_JUNEAU, ShoalCaveNewFloor2_Text_JuneauIntro, ShoalCaveNewFloor2_Text_JuneauDefeated
    msgbox ShoalCaveNewFloor2_Text_JuneauPostBattle, MSGBOX_AUTOCLOSE
    end

ShoalCaveNewFloor2_EventScript_Alaska::
    trainerbattle_single TRAINER_P_ALASKA, ShoalCaveNewFloor2_Text_AlaskaIntro, ShoalCaveNewFloor2_Text_AlaskaDefeated
    msgbox ShoalCaveNewFloor2_Text_AlaskaPostBattle, MSGBOX_AUTOCLOSE
    end

ShoalCaveNewFloor2_Text_MagnusIntro:
	.string "You must weild a titanic sword\n"
	.string "to slay a titanic beast!\p"
	.string "My Pokemon are my sword...\n"
	.string "and you are the beast!$"

ShoalCaveNewFloor2_Text_MagnusDefeated:
	.string "I can hear the angels\n"
	.string "calling my name...!$"

ShoalCaveNewFloor2_Text_MagnusPostBattle:
	.string "Try all you want, but Dragon\n"
	.string "type Pokemon cannot be intimidated!$"

ShoalCaveNewFloor2_Text_JuneauIntro:
	.string "Lottabats... assemble...$"

ShoalCaveNewFloor2_Text_JuneauDefeated:
	.string "I needed more bats...!$"

ShoalCaveNewFloor2_Text_JuneauPostBattle:
	.string "I must go further into the cave...\n"
	.string "to find more Lottabats...$"

ShoalCaveNewFloor2_Text_AlaskaIntro:
	.string "Hey, it's extra slippery in here!\n"
	.string "Outta my way!$"

ShoalCaveNewFloor2_Text_AlaskaDefeated:
	.string "Couldn't stay balanced!$"

ShoalCaveNewFloor2_Text_AlaskaPostBattle:
	.string "Maybe if I go fast enough, I can\n"
	.string "skate on the ceiling!$"

ShoalCaveNewFloor2_Text_BrawlyGreeting:
	.string "Hey there, trainer! Man, am I glad\n"
	.string "that I worked up quite a sweat\l"
	.string "swimming here, 'cuz it is\l"
	.string "FREEZING in here!\p"
	.string "I was tipped off from someone\n"
	.string "anonymous that there were folks\l"
	.string "illegally drilling into the cave\l"
	.string "depths for oil. Seems like\l"
	.string "it was some kind of prank,\l"
	.string "'cuz I see no signs of any\l"
	.string "of that kind of stuff.\p"
	.string "The things people will do\n"
	.string "for attention! Anyways, I gotta\l"
	.string "be getting back to Dewford.\l"
	.string "Hope to catch you there...\l"
	.string "you look pretty tough!$"

ShoalCaveNewFloor2_Text_BrawlyGone:
	.string "hey dunko$"

ShoalCaveNewFloor2_Text_WantToStrength:
	.string "It's a big boulder, but a Pokémon\n"
	.string "may be able to push it aside.\p"
	.string "Would you like to use Strength?$"

ShoalCaveNewFloor2_Text_MonUsedStrength:
	.string "{STR_VAR_1} used Strength!\p"
	.string "{STR_VAR_1}'s Strength made it\n"
	.string "possible to move boulders around!$"

ShoalCaveNewFloor2_Text_CantStrength:
	.string "It's a big boulder, but a Pokémon\n"
	.string "may be able to push it aside.$"

ShoalCaveNewFloor2_Text_StrengthActivated:
	.string "Strength made it possible to move\n"
	.string "boulders around.$"

ShoalCaveNewFloor2_Text_Dangerous:
	.string "It may be too dangerous\n"
	.string "to push this rock again.$"

ShoalCaveNewFloor2_Text_WantToStrength2:
	.string "It's a lady. A Pokémon\n"
	.string "may be able to push her aside.\p"
	.string "Would you like to use Strength?$"

ShoalCaveNewFloor2_Text_CantStrength2:
	.string "It's a lady. A Pokémon\n"
	.string "may be able to push her aside.$"

ShoalCaveNewFloor2_Text_WhyDidYouDoThat:
	.string "RUDE$"
