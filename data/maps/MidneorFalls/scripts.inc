.set LOCALID_TAII, 3
.set LOCALID_CATT, 4
.set LOCALID_ZEPHYR, 6
.set LOCALID_MORGANA, 7
.set LOCALID_ANTHREENY, 8
.set LOCALID_SCHULI, 9
.set LOCALID_GERIER, 10
.set LOCALID_GONZEROS, 11
.set LOCALID_WALLACE, 13
.set LOCALID_OZONE_BLOCKER1, 12

MidneorFalls_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MidneorFalls_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MidneorFalls_OnFrame
	.byte 0

MidneorFalls_OnLoad:
	call_if_ge VAR_NEW_COO_STATE, 6, MidneorFalls_EventScript_RemoveOzoneBlocker
	end

MidneorFalls_OnFrame:
	map_script_2 VAR_NEW_COO_STATE, 8, MidneorFalls_EventScript_WallaceOrbEvent
	.2byte 0

MidneorFalls_EventScript_RemoveOzoneBlocker::
	removeobject LOCALID_OZONE_BLOCKER1
	setflag FLAG_TEMP_12
	return

MidneorFalls_EventScript_Roadblock::
	lock
	goto_if_gt VAR_NEW_COO_STATE, 5, MidneorFalls_EventScript_ReleaseTrigger
	msgbox MidneorFalls_Text_OzoneDoingResearch, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MidneorFalls_Movement_MoveRight
	waitmovement 0
	release
	end

MidneorFalls_EventScript_RoadblockNPC::
	msgbox MidneorFalls_Text_OzoneDoingResearch, MSGBOX_NPC
    end

MidneorFalls_Movement_MoveRight:
	walk_right
	step_end

MidneorFalls_EventScript_CattTaiiTrigger::
	lock
	goto_if_defeated TRAINER_P_CATT, MidneorFalls_EventScript_ReleaseTrigger
	goto_if_defeated TRAINER_P_TAII, MidneorFalls_EventScript_ReleaseTrigger
	playse SE_PIN
	applymovement LOCALID_CATT, MidneorFalls_Movement_Exclamation
	waitmovement 0
	msgbox MidneorFalls_Text_CattIntro, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_TAII, MidneorFalls_Movement_Exclamation
	waitmovement 0
	msgbox MidneorFalls_Text_TaiiIntro, MSGBOX_DEFAULT
	trainerbattle_two_trainers TRAINER_P_CATT, MidneorFalls_Text_CattDefeated, TRAINER_P_TAII, MidneorFalls_Text_TaiiDefeated, MidneorFalls_EventScript_ReleaseTrigger, NO_MUSIC
	release
	end

MidneorFalls_Movement_Exclamation:
	emote_exclamation_mark
	step_end

MidneorFalls_EventScript_ReleaseTrigger::
	release
	end

MidneorFalls_EventScript_Catt::
    trainerbattle_single TRAINER_P_CATT, MidneorFalls_Text_CattIntro, MidneorFalls_Text_CattDefeated
    msgbox MidneorFalls_Text_CattPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_Taii::
    trainerbattle_single TRAINER_P_TAII, MidneorFalls_Text_TaiiIntro, MidneorFalls_Text_TaiiDefeated
    msgbox MidneorFalls_Text_TaiiPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_ErkinAndKaya::
    trainerbattle_double TRAINER_P_ERKIN_AND_KAYA, MidneorFalls_Text_ErkinAndKayaIntro, MidneorFalls_Text_ErkinAndKayaDefeated, MidneorFalls_Text_ErkinAndKayaNeedTwoMons
    msgbox MidneorFalls_Text_ErkinAndKayaPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_Griselda::
    trainerbattle_single TRAINER_P_GRISELDA, MidneorFalls_Text_GriseldaIntro, MidneorFalls_Text_GriseldaDefeated
    msgbox MidneorFalls_Text_GriseldaPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_MorganaTrigger::
	lock
	goto_if_defeated TRAINER_P_MORGANA, MidneorFalls_EventScript_ReleaseTrigger
	playse SE_PIN
	applymovement LOCALID_MORGANA, MidneorFalls_Movement_Exclamation
	waitmovement 0
	msgbox MidneorFalls_Text_MorganaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_MORGANA, MidneorFalls_Text_MorganaDefeated
	release
	end

MidneorFalls_EventScript_Morgana::
    trainerbattle_single TRAINER_P_MORGANA, MidneorFalls_Text_MorganaIntro, MidneorFalls_Text_MorganaDefeated
    msgbox MidneorFalls_Text_MorganaPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_ZephyrTrigger::
	lock
	goto_if_defeated TRAINER_P_ZEPHYR, MidneorFalls_EventScript_ReleaseTrigger
	playse SE_PIN
	applymovement LOCALID_ZEPHYR, MidneorFalls_Movement_Exclamation
	waitmovement 0
	msgbox MidneorFalls_Text_ZephyrIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_ZEPHYR, MidneorFalls_Text_ZephyrDefeated
	release
	end

MidneorFalls_EventScript_Zephyr::
    trainerbattle_single TRAINER_P_ZEPHYR, MidneorFalls_Text_ZephyrIntro, MidneorFalls_Text_ZephyrDefeated
    msgbox MidneorFalls_Text_ZephyrPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_AnthreenyTrigger::
	lock
	goto_if_defeated TRAINER_P_ANTHREENY, MidneorFalls_EventScript_ReleaseTrigger
	playse SE_PIN
	applymovement LOCALID_ANTHREENY, MidneorFalls_Movement_Exclamation
	waitmovement 0
	msgbox MidneorFalls_Text_AnthreenyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_ANTHREENY, MidneorFalls_Text_AnthreenyDefeated
	release
	end

MidneorFalls_EventScript_Anthreeny::
    trainerbattle_single TRAINER_P_ANTHREENY, MidneorFalls_Text_AnthreenyIntro, MidneorFalls_Text_AnthreenyDefeated
    msgbox MidneorFalls_Text_AnthreenyPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_SchuliTrigger::
	lock
	goto_if_defeated TRAINER_P_SCHULI, MidneorFalls_EventScript_ReleaseTrigger
	playse SE_PIN
	applymovement LOCALID_SCHULI, MidneorFalls_Movement_Exclamation
	waitmovement 0
	msgbox MidneorFalls_Text_SchuliIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_SCHULI, MidneorFalls_Text_SchuliDefeated
	release
	end

MidneorFalls_EventScript_Schuli::
    trainerbattle_single TRAINER_P_SCHULI, MidneorFalls_Text_SchuliIntro, MidneorFalls_Text_SchuliDefeated
    msgbox MidneorFalls_Text_SchuliPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_GerierGonzerosTrigger::
	lock
	goto_if_defeated TRAINER_P_GERIER, MidneorFalls_EventScript_ReleaseTrigger
	goto_if_defeated TRAINER_P_GONZEROS, MidneorFalls_EventScript_ReleaseTrigger
	playse SE_PIN
	applymovement LOCALID_GERIER, MidneorFalls_Movement_Exclamation
	waitmovement 0
	msgbox MidneorFalls_Text_GerierIntro, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_GONZEROS, MidneorFalls_Movement_Exclamation
	waitmovement 0
	msgbox MidneorFalls_Text_GonzerosIntro, MSGBOX_DEFAULT
	trainerbattle_two_trainers TRAINER_P_GERIER, MidneorFalls_Text_GerierDefeated, TRAINER_P_GONZEROS, MidneorFalls_Text_GonzerosDefeated, MidneorFalls_EventScript_ReleaseTrigger, NO_MUSIC
	release
	end

MidneorFalls_EventScript_Gerier::
    trainerbattle_single TRAINER_P_GERIER, MidneorFalls_Text_GerierIntro, MidneorFalls_Text_GerierDefeated
    msgbox MidneorFalls_Text_GerierPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_Gonzeros::
    trainerbattle_single TRAINER_P_GONZEROS, MidneorFalls_Text_GonzerosIntro, MidneorFalls_Text_GonzerosDefeated
    msgbox MidneorFalls_Text_GonzerosPostBattle, MSGBOX_AUTOCLOSE
    end

MidneorFalls_EventScript_WallaceIdle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LUO_KYO, MidneorFalls_EventScript_WallaceIdleBeatLuo
	speakername MidneorFalls_Text_NameWallace
	msgbox MidneorFalls_Text_ISenseOneNearby, MSGBOX_AUTOCLOSE
	release
	end

MidneorFalls_EventScript_WallaceIdleBeatLuo::
	goto_if_set FLAG_DEFEATED_SHA_GROU, MidneorFalls_EventScript_WallaceIdleBeatBoth
	speakername MidneorFalls_Text_NameWallace
	msgbox MidneorFalls_Text_GoToShayon, MSGBOX_AUTOCLOSE
	release
	end

MidneorFalls_EventScript_WallaceIdleBeatBoth::
	speakername MidneorFalls_Text_NameWallace
	msgbox MidneorFalls_Text_TheFishWentToEGR, MSGBOX_AUTOCLOSE
	release
	end

MidneorFalls_EventScript_WallaceOrbEvent::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 4
	goto_if_set FLAG_DEFEATED_SHA_GROU, MidneorFalls_EventScript_BeatBothLegends
	setvar VAR_NEW_COO_STATE, 6
	speakername MidneorFalls_Text_NameWallace
	msgbox MidneorFalls_Text_GoToShayon, MSGBOX_DEFAULT
	setflag FLAG_TEMP_11
	release
	end

MidneorFalls_Movement_WalkToWallace:
	face_left
	step_end

MidneorFalls_Movement_WallaceWalkOver:
	walk_down
	face_right
	step_end

MidneorFalls_EventScript_BeatBothLegends::
	speakername MidneorFalls_Text_NameWallace
	msgbox MidneorFalls_Text_TheFishWentToEGR, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEW_COO_STATE, 9
	setflag FLAG_TEMP_11
	setflag FLAG_DEFEATED_TWO_PISCES_LEGENDS
	clearflag FLAG_HIDE_MAXIE_OZONE
	release
	end

MidneorFalls_Text_CattIntro:
	.string "intro$"

MidneorFalls_Text_CattDefeated:
	.string "defeat$"

MidneorFalls_Text_CattPostBattle:
	.string "post$"

MidneorFalls_Text_TaiiIntro:
	.string "intro$"

MidneorFalls_Text_TaiiDefeated:
	.string "defeat$"

MidneorFalls_Text_TaiiPostBattle:
	.string "post$"

MidneorFalls_Text_ErkinAndKayaIntro:
	.string "intro$"

MidneorFalls_Text_ErkinAndKayaDefeated:
	.string "defeat$"

MidneorFalls_Text_ErkinAndKayaPostBattle:
	.string "post$"

MidneorFalls_Text_ErkinAndKayaNeedTwoMons:
	.string "need 2 dood$"

MidneorFalls_Text_GriseldaIntro:
	.string "intro$"

MidneorFalls_Text_GriseldaDefeated:
	.string "defeat$"

MidneorFalls_Text_GriseldaPostBattle:
	.string "post$"

MidneorFalls_Text_MorganaIntro:
	.string "intro$"

MidneorFalls_Text_MorganaDefeated:
	.string "defeat$"

MidneorFalls_Text_MorganaPostBattle:
	.string "post$"

MidneorFalls_Text_ZephyrIntro:
	.string "intro$"

MidneorFalls_Text_ZephyrDefeated:
	.string "defeat$"

MidneorFalls_Text_ZephyrPostBattle:
	.string "post$"

MidneorFalls_Text_AnthreenyIntro:
	.string "intro$"

MidneorFalls_Text_AnthreenyDefeated:
	.string "defeat$"

MidneorFalls_Text_AnthreenyPostBattle:
	.string "post$"

MidneorFalls_Text_SchuliIntro:
	.string "intro$"

MidneorFalls_Text_SchuliDefeated:
	.string "defeat$"

MidneorFalls_Text_SchuliPostBattle:
	.string "post$"

MidneorFalls_Text_GerierIntro:
	.string "intro$"

MidneorFalls_Text_GerierDefeated:
	.string "defeat$"

MidneorFalls_Text_GerierPostBattle:
	.string "post$"

MidneorFalls_Text_GonzerosIntro:
	.string "intro$"

MidneorFalls_Text_GonzerosDefeated:
	.string "defeat$"

MidneorFalls_Text_GonzerosPostBattle:
	.string "post$"

MidneorFalls_Text_OzoneDoingResearch:
	.string "Sorry! Can't let you any\n"
	.string "deeper into the Falls right now.\l"
	.string "Upper management doesn't want\l"
	.string "weaker looking trainers like you\l"
	.string "to be around while we test\l"
	.string "the effectiveness of powerful\l"
	.string "Pokemon deep underwater.\p"
	.string "Maybe get a few more battling\n"
	.string "notches under your belt?\l"
	.string "Then I could consider it.$"

MidneorFalls_Text_NameWallace:
	.string "Wallace$"

MidneorFalls_Text_ISenseOneNearby:
	.string "I sense that one of the\n"
	.string "Legendary Fish of the Lake\l"
	.string "are nearby. If you are in need\l"
	.string "of my help, I will be there.\l"
	.string "Otherwise, I believe you and\l"
	.string "your team are strong enough to\l"
	.string "take them on.$"

MidneorFalls_Text_GoToShayon:
	.string "Luo-Shan... upon its defeat,\n"
	.string "it regressed into this red orb.\l"
	.string "It seems to me dormant.\p"
	.string "I will need Sha-Yon to be\n"
	.string "pacified and return to its\l"
	.string "orb form before we can\l"
	.string "restore the lake.\l"
	.string "I believe it to have fled to\l"
	.string "the highest point of Hoenn...\l"
	.string "Crimney Caldera, the summit of\l"
	.string "the climb leading up Mt. Chimney.\p"
	.string "Go there, and I will accompany\n"
	.string "you to procure the second orb.$"

MidneorFalls_Text_TheFishWentToEGR:
	.string "That makes both of the orbs procured,\n"
	.string "along with both Groudon and Kyogre\l"
	.string "sent back into dormancy,\l"
	.string "at least, for now.\l"
	.string "Excellent...\p"
	.string "In order to restore Sha-Yon\n"
	.string "and Luo-Shan to their original forms,\l"
	.string "it will require partaking in\l"
	.string "a special ritual.\l"
	.string "We will need the assistance\l"
	.string "of multiple talented individuals\l"
	.string "to complete said ritual.\l"
	.string "Of course, I am saying this to\l"
	.string "preface my invitation to you.\p"
	.string "The ritual shall be taking place\n"
	.string "at the Golden Plains... a holy\l"
	.string "site of worship off the coast\l"
	.string "of southeastern Hoenn.\p"
	.string "There is no way to travel there\n"
	.string "right now besides the air.\l"
	.string "I will set things up with Maxie\l"
	.string "and Archie so that they can\l"
	.string "personally fly you there.\p"
	.string "Go to the Ozone Institute when\n"
	.string "you are prepared thoroughly.\l"
	.string "I very much look forward\l"
	.string "to your attendance, {PLAYER}!$"
