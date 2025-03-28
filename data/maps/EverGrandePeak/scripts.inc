.set LOCALID_MONKBLOCK1, 1
.set LOCALID_MONKBLOCK2, 2
.set LOCALID_MONKBLOCK3, 3
.set LOCALID_MONKBLOCK4, 4
.set LOCALID_WALLACE, 5
.set LOCALID_STEVEN, 6
.set LOCALID_MAY, 7
.set LOCALID_BRENDAN, 8

EverGrandePeak_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandePeak_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandePeak_OnFrame
	.byte 0

EverGrandePeak_OnFrame:
	map_script_2 VAR_PISCES_STORY_PROGRESS, 12, EverGrandePeak_EventScript_ToTheHallOfFame
	.2byte 0

EverGrandePeak_OnLoad:
	call_if_gt VAR_NEW_COO_STATE, 10, EverGrandePeak_EventScript_RemoveMonkBlock
	call EverGrandePeak_EventScript_RemoveBrendanMay
	call_if_gt VAR_PISCES_STORY_PROGRESS, 12, EverGrandePeak_EventScript_RemoveStevenWallace
	call_if_set FLAG_SHAYON_ORB, EverGrandePeak_EventScript_AddShayonOrb
	call_if_set FLAG_LUOSHAN_ORB, EverGrandePeak_EventScript_AddLuoshanOrb
	end

EverGrandePeak_EventScript_RemoveMonkBlock::
	removeobject LOCALID_MONKBLOCK1
	setflag FLAG_TEMP_2
	removeobject LOCALID_MONKBLOCK2
	setflag FLAG_TEMP_3
	removeobject LOCALID_MONKBLOCK3
	setflag FLAG_TEMP_4
	removeobject LOCALID_MONKBLOCK4
	setflag FLAG_TEMP_5
	return

EverGrandePeak_EventScript_RemoveBrendanMay::
	removeobject LOCALID_BRENDAN
	setflag FLAG_TEMP_11
	removeobject LOCALID_MAY
	setflag FLAG_TEMP_12
	return

EverGrandePeak_EventScript_RemoveStevenWallace::
	removeobject LOCALID_WALLACE
	setflag FLAG_TEMP_13
	removeobject LOCALID_STEVEN
	setflag FLAG_TEMP_14
	return

EverGrandePeak_EventScript_AddShayonOrb::
	setmetatile 6, 1, METATILE_Golden_ShaYonOrbTop, TRUE
	setmetatile 6, 2, METATILE_Golden_ShaYonOrbBottom, TRUE
	special DrawWholeMapView
	return

EverGrandePeak_EventScript_AddLuoshanOrb::
	setmetatile 70, 67, METATILE_Golden_LuoShanOrbTop, TRUE
	setmetatile 70, 68, METATILE_Golden_LuoShanOrbBottom, TRUE
	special DrawWholeMapView
	return

EverGrandePeak_EventScript_ToTheHallOfFame::
	lock
	turnobject LOCALID_WALLACE, DIR_SOUTH
	turnobject LOCALID_STEVEN, DIR_SOUTH
	delay 8
	speakername EverGrandePeak_Text_NameWallace
	msgbox EverGrandePeak_Text_OurWorldsTruth, MSGBOX_DEFAULT
	speakername EverGrandePeak_Text_NameSteven
	msgbox EverGrandePeak_Text_YoureAGreatTrainer, MSGBOX_DEFAULT
	speakername NULL
	msgbox EverGrandePeak_Text_TheMeaningOfItAll, MSGBOX_DEFAULT
	speakername EverGrandePeak_Text_NameWallace
	msgbox EverGrandePeak_Text_GoToTheHallOfFame, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_EGR_NO_FLY
	setvar VAR_PISCES_STORY_PROGRESS, 13
	delay 4
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	release
	end

EverGrandePeak_EventScript_SWTriggerWest1::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWWest1
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWWest1:
	walk_down
	walk_right
	walk_down
	walk_right
	walk_right
	face_up
	step_end

EverGrandePeak_EventScript_SWTriggerWest2::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWWest2
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWWest2:
	walk_right
	walk_down
	walk_right
	walk_right
	face_up
	step_end

EverGrandePeak_EventScript_SWTriggerWest3::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWWest3
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWWest3:
	walk_right
	walk_right
	walk_right
	face_up
	step_end

EverGrandePeak_EventScript_SWTriggerEast1::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWEast1
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWEast1:
	walk_down
	walk_left
	walk_down
	walk_left
	walk_left
	face_up
	step_end

EverGrandePeak_EventScript_SWTriggerEast2::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWEast2
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWEast2:
	walk_left
	walk_down
	walk_left
	walk_left
	face_up
	step_end

EverGrandePeak_EventScript_SWTriggerEast3::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWEast3
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWEast3:
	walk_left
	walk_left
	walk_left
	face_up
	step_end

EverGrandePeak_EventScript_SWTriggerSouth1::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWSouth1
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWSouth1:
	walk_up
	walk_right
	face_up
	step_end

EverGrandePeak_EventScript_SWTriggerSouth2::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWSouth2
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWSouth2:
	walk_up
	face_up
	step_end

EverGrandePeak_EventScript_SWTriggerSouth3::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWSouth3
	waitmovement 0
	goto EverGrandePeak_EventScript_StevenWallaceBattle
	release
	end

EverGrandePeak_Movement_PlayerSWSouth3:
	walk_up
	walk_left
	face_up
	step_end

EverGrandePeak_EventScript_StevenWallaceBattle::
	delay 16
	turnobject LOCALID_WALLACE, DIR_SOUTH
	turnobject LOCALID_STEVEN, DIR_SOUTH
	delay 8
	special HealPlayerParty
	speakername EverGrandePeak_Text_NameWallace
	msgbox EverGrandePeak_Text_Welcome, MSGBOX_DEFAULT
	speakername EverGrandePeak_Text_NameSteven
	msgbox EverGrandePeak_Text_YouveDoneWell, MSGBOX_DEFAULT
	speakername EverGrandePeak_Text_NameWallace
	msgbox EverGrandePeak_Text_DoYouHaveTheOrbs, MSGBOX_DEFAULT
	speakername EverGrandePeak_Text_NameSteven
	msgbox EverGrandePeak_Text_OneLastTest, MSGBOX_DEFAULT
	speakername NULL
	trainerbattle_two_trainers TRAINER_P_WALLACE, EverGrandePeak_Text_WallaceDefeat, TRAINER_P_STEVEN, EverGrandePeak_Text_StevenDefeat, EverGrandePeak_EventScript_SWDefeated, NO_MUSIC
	goto EverGrandePeak_EventScript_SWDefeated
	release
	end

EverGrandePeak_EventScript_SWDefeated::
	setvar VAR_NEW_COO_STATE, 11
	speakername EverGrandePeak_Text_NameSteven
	msgbox EverGrandePeak_Text_YouAreWorthy, MSGBOX_DEFAULT
	speakername EverGrandePeak_Text_NameWallace
	msgbox EverGrandePeak_Text_TakeTheOrbsToTheirShrines, MSGBOX_DEFAULT
	call EverGrandePeak_EventScript_RemoveMonkBlock
	speakername EverGrandePeak_Text_NameSteven
	msgbox EverGrandePeak_Text_WeWillBeWaiting, MSGBOX_AUTOCLOSE
	release
	end

EverGrandePeak_EventScript_ShayonShrine::
	lock
	goto_if_set FLAG_SHAYON_ORB, EverGrandePeak_EventScript_ShayonShrineOrbSet
	msgbox EverGrandePeak_Text_HighestPoint, MSGBOX_DEFAULT
	playse SE_SHINY
	call EverGrandePeak_EventScript_AddShayonOrb
	setflag FLAG_SHAYON_ORB
	closemessage
	delay 8
	goto_if_set FLAG_LUOSHAN_ORB, EverGrandePeak_EventScript_BothOrbsSet
	release
	end

EverGrandePeak_EventScript_ShayonShrineOrbSet::
	msgbox EverGrandePeak_Text_ShayonShrineOrbSet, MSGBOX_AUTOCLOSE
	release
	end

EverGrandePeak_EventScript_LuoshanShrine::
	lock
	goto_if_set FLAG_LUOSHAN_ORB, EverGrandePeak_EventScript_LuoshanShrineOrbSet
	msgbox EverGrandePeak_Text_LowestPoint, MSGBOX_DEFAULT
	playse SE_SHINY
	call EverGrandePeak_EventScript_AddLuoshanOrb
	setflag FLAG_LUOSHAN_ORB
	closemessage
	delay 8
	goto_if_set FLAG_SHAYON_ORB, EverGrandePeak_EventScript_BothOrbsSet
	release
	end

EverGrandePeak_EventScript_LuoshanShrineOrbSet::
	msgbox EverGrandePeak_Text_LuoshanShrineOrbSet, MSGBOX_AUTOCLOSE
	release
	end

EverGrandePeak_EventScript_BothOrbsSet::
	setvar VAR_NEW_COO_STATE, 12
	msgbox EverGrandePeak_Text_BothOrbsSet, MSGBOX_AUTOCLOSE
	release
	end

EverGrandePeak_EventScript_BMTriggerWest1::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWWest1
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BMTriggerWest2::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWWest2
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BMTriggerWest3::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWWest3
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BMTriggerEast1::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWEast1
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BMTriggerEast2::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWEast2
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BMTriggerEast3::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWEast3
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BMTriggerSouth1::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWSouth1
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BMTriggerSouth2::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWSouth2
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BMTriggerSouth3::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerSWSouth3
	waitmovement 0
	goto EverGrandePeak_EventScript_BrendanMayBattle
	release
	end

EverGrandePeak_EventScript_BrendanMayBattle::
	delay 16
	turnobject LOCALID_WALLACE, DIR_SOUTH
	turnobject LOCALID_STEVEN, DIR_SOUTH
	delay 8
	speakername EverGrandePeak_Text_NameWallace
	msgbox EverGrandePeak_Text_IFeelTheOrbsPower, MSGBOX_DEFAULT
	speakername EverGrandePeak_Text_NameSteven
	msgbox EverGrandePeak_Text_OneMoreThingToDo, MSGBOX_DEFAULT
	closemessage
	special HealPlayerParty
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandePeak_EventScript_MayBattle
	goto_if_eq VAR_RESULT, FEMALE, EverGrandePeak_EventScript_BrendanBattle
	release
	end

EverGrandePeak_EventScript_MayBattle::
	clearflag FLAG_TEMP_12
	addobject LOCALID_MAY
	delay 16
	applymovement LOCALID_MAY, EverGrandePeak_Movement_MayWalkOnScreen
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerNoticeRival
	waitmovement 0
	delay 16
	playbgm MUS_ENCOUNTER_MAY, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerWalkToRival
	waitmovement 0
	delay 8
	goto_if_set FLAG_DEFEATED_GOLDEN_PLAINS_RIVAL, EverGrandePeak_EventScript_ShunyongAwakens
	speakername NULL
	msgbox EverGrandePeak_Text_YouLockEyes, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_MAY_FINAL, EverGrandePeak_Text_MayDefeated
	setflag FLAG_DEFEATED_GOLDEN_PLAINS_RIVAL
	goto EverGrandePeak_EventScript_ShunyongAwakens
	release
	end

EverGrandePeak_EventScript_BrendanBattle::
	clearflag FLAG_TEMP_11
	addobject LOCALID_BRENDAN
	delay 16
	applymovement LOCALID_BRENDAN, EverGrandePeak_Movement_BrendanWalkOnScreen
	waitmovement 0
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerNoticeRival
	waitmovement 0
	delay 16
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandePeak_Movement_PlayerWalkToRival
	waitmovement 0
	delay 8
	goto_if_set FLAG_DEFEATED_GOLDEN_PLAINS_RIVAL, EverGrandePeak_EventScript_ShunyongAwakens
	speakername NULL
	msgbox EverGrandePeak_Text_YouLockEyes, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_BRENDAN_FINAL, EverGrandePeak_Text_BrendanDefeated
	setflag FLAG_DEFEATED_GOLDEN_PLAINS_RIVAL
	goto EverGrandePeak_EventScript_ShunyongAwakens
	release
	end

EverGrandePeak_Movement_MayWalkOnScreen:
	walk_right
	walk_up
	walk_up
	step_end

EverGrandePeak_Movement_BrendanWalkOnScreen:
	walk_left
	walk_up
	walk_up
	step_end

EverGrandePeak_Movement_PlayerNoticeRival:
	face_down
	emote_exclamation_mark
	step_end

EverGrandePeak_Movement_PlayerWalkToRival:
	walk_down
	walk_down
	step_end

EverGrandePeak_EventScript_ShunyongAwakens::
	playbgm MUS_NONE, FALSE
	msgbox EverGrandePeak_Text_HardFoughtVictory, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_WALLACE, DIR_NORTH
	turnobject LOCALID_STEVEN, DIR_NORTH
	delay 16
	special SpawnCameraObject
	delay 16
	applymovement OBJ_EVENT_ID_CAMERA, EverGrandePeak_Movement_CameraPanUp
	waitmovement 0
	pike_flashscreen
	playse SE_INTRO_BLAST
	pike_flashscreen
	waitse
	delay 16
	pike_flashscreen
	special HealPlayerParty
	playmoncry SPECIES_SHUNYONG, CRY_MODE_NORMAL
	waitmoncry
	delay 8
	warp MAP_SHUNYONG_BATTLE_ARENA, 4, 7
	waitstate
	release
	end

EverGrandePeak_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandePeak_EventScript_EGREndsSign::
    msgbox EverGrandePeak_Text_EGREndsSign, MSGBOX_SIGN
    end

EverGrandePeak_EventScript_GoldenPlainsSign::
    msgbox EverGrandePeak_Text_GoldenPlainsSign, MSGBOX_SIGN
    end

EverGrandePeak_EventScript_PathToLSSign::
    msgbox EverGrandePeak_Text_PathToLSSign, MSGBOX_SIGN
    end

EverGrandePeak_EventScript_LuoShanSign::
    msgbox EverGrandePeak_Text_LuoShanSign, MSGBOX_SIGN
    end

EverGrandePeak_EventScript_PathToSYSign::
    msgbox EverGrandePeak_Text_PathToSYSign, MSGBOX_SIGN
    end

EverGrandePeak_EventScript_ShaYonSign::
    msgbox EverGrandePeak_Text_ShaYonSign, MSGBOX_SIGN
    end

EverGrandePeak_Text_EGREndsSign:
	.string "Ever Grande Road ends here.\n"
	.string "Welcome to the Golden Plains.$"

EverGrandePeak_Text_GoldenPlainsSign:
	.string "Before you lies the center\n"
	.string "of the Golden Plains.\l"
	.string "A fountain, erected in honor\l"
	.string "of the duality between\l"
	.string "rising and falling.$"

EverGrandePeak_Text_PathToLSSign:
	.string "Continue along this path to reach\n"
	.string "the shrine of Luo-Shan.$"

EverGrandePeak_Text_LuoShanSign:
	.string "SHRINE OF LUO-SHAN$"

EverGrandePeak_Text_PathToSYSign:
	.string "Continue along this path to reach\n"
	.string "the shrine of Sha-Yon.$"

EverGrandePeak_Text_ShaYonSign:
	.string "SHRINE OF SHA-YON$"

EverGrandePeak_EventScripts_ShunyongTest::
	lock
	doshunyongbattle
	release
	end

EverGrandePeak_Text_NameWallace:
	.string "Wallace$"

EverGrandePeak_Text_NameSteven:
	.string "Steven$"

EverGrandePeak_Text_Welcome:
	.string "Welcome to the Golden Plains.\p"
	.string "This holy site has been protected\n"
	.string "by the strongest in Hoenn for\l"
	.string "generations, now...\p"
	.string "Steven and I, former champions,\n"
	.string "have been appointed as Deacons,\l"
	.string "training the Monks and Acolytes\l"
	.string "to protect this place from those\l"
	.string "who would seek to defile it.$"

EverGrandePeak_Text_YouveDoneWell:
	.string "This used to be where the\n"
	.string "Pokemon League challenge in\l"
	.string "Ever Grande City was located...\l"
	.string "before the decision was made\l"
	.string "to do away with it.\p"
	.string "You've done quite well to reach\n"
	.string "us here, {PLAYER}.\l"
	.string "It's no coincidence that many\l"
	.string "an experienced trainer was\l"
	.string "in your path... and you\l"
	.string "vanquished all of our\l"
	.string "disciples with ease.\l"
	.string "Quite commendable.$"

EverGrandePeak_Text_DoYouHaveTheOrbs:
	.string "I have with me the two red orbs,\n"
	.string "containing the dormant souls\l"
	.string "of Sha-Yon and Luo-Shan.\l"
	.string "With these, we should be able to\l"
	.string "restore the two Legendary Pokemon\l"
	.string "and hopefully reap the divine\l"
	.string "rewards of their bond once more.$"

EverGrandePeak_Text_OneLastTest:
	.string "...But, we must task you\n"
	.string "with one final trial.\p"
	.string "{PLAYER}. Do you recall our\n"
	.string "initial meeting in Mossdeep City?\l"
	.string "I had, once, considered you to\l"
	.string "be unimposing. Unexceptional.\l"
	.string "Yet, within you undeniably\l"
	.string "blossomed the greatest trainer\l"
	.string "I have seen in generations.\p"
	.string "It would not do well to start\n"
	.string "this ritual without a battle.\l"
	.string "Three champion level trainers,\l"
	.string "dueling in lockstep...\l"
	.string "It would be quite an honor.\p"
	.string "Let us not delay!$"

EverGrandePeak_Text_WallaceDefeat:
	.string "Amen.$"

EverGrandePeak_Text_StevenDefeat:
	.string "I have been definitively\n"
	.string "proven wrong, {PLAYER}.\p"
	.string "Even at the start of this battle,\n"
	.string "I was surmising that we could\l"
	.string "handedly defeat you. That...\l"
	.string "was not the case.$"

EverGrandePeak_Text_YouAreWorthy:
	.string "I would say {PLAYER} is\n"
	.string "more than capable of leading\l"
	.string "the ritual. Wallace?$"

EverGrandePeak_Text_TakeTheOrbsToTheirShrines:
	.string "I concur!\p"
	.string "Take the two crimson orbs to\n"
	.string "their respective shrines at\l"
	.string "the lowest, and highest, points\l"
	.string "of the Golden Plains.\p"
	.string "Once they are both left in\n"
	.string "said shrines, you may return\l"
	.string "to the central fountain.$"

EverGrandePeak_Text_WeWillBeWaiting:
	.string "We will be waiting with bated breath.$"

EverGrandePeak_Text_HighestPoint:
	.string "(It's the highest point of\n"
	.string "the Golden Plains...)\p"
	.string "(You place Sha-Yon's orb.)$"

EverGrandePeak_Text_ShayonShrineOrbSet:
	.string "(Sha-Yon's orb has been placed.)$"

EverGrandePeak_Text_LowestPoint:
	.string "(It's the lowest point of\n"
	.string "the Golden Plains...)\p"
	.string "(You place Luo-Shan's orb.)$"

EverGrandePeak_Text_LuoshanShrineOrbSet:
	.string "(Luo-Shan's orb has been placed.)$"

EverGrandePeak_Text_BothOrbsSet:
	.string "(Both of the Legendary Pokemon's\n"
	.string "red orbs have been placed correctly.)\p"
	.string "(You should head back to\n"
	.string "the central fountain...)$"

EverGrandePeak_Text_IFeelTheOrbsPower:
	.string "Both of the orbs have found repose?\n"
	.string "That is great news...$"

EverGrandePeak_Text_OneMoreThingToDo:
	.string "There is but one thing left to do.\n"
	.string "In order to complete this ritual\l"
	.string "to restore Sha-Yon and Luo-Shan...\l"
	.string "the central fountain must\l"
	.string "bear witness to a showcase of a\l"
	.string "true bond between two individuals.\p"
	.string "You, {PLAYER}, are one of two.\p"
	.string "The other...$"

EverGrandePeak_Text_YouLockEyes:
	.string "(...)\p"
	.string "(...Somehow, you felt this\n"
	.string "was coming.)\p"
	.string "(You and your old rival...\n"
	.string "the former champion...)\p"
	.string "(The two of you lock eyes.\n"
	.string "And, when two trainers lock eyes...)\p"
	.string "(It's time for a Pokemon Battle.)$"

EverGrandePeak_Text_MayDefeated:
	.string "(May closes her eyes in defeat.)$"

EverGrandePeak_Text_BrendanDefeated:
	.string "(Brendan closes his eyes in defeat.)$"

EverGrandePeak_Text_HardFoughtVictory:
	.string "(Without words, you and your rival\n"
	.string "understood each other like no one\l"
	.string "else could hope to.)\p"
	.string "(It was a hard fought victory.)\p"
	.string "(Does that mean...\n"
	.string "the ritual... was complete?)$"

EverGrandePeak_Text_OurWorldsTruth:
	.string "You've returned...!\n"
	.string "{PLAYER}, you and the former\l"
	.string "champion both disappeared...\l"
	.string "While this is well within line\l"
	.string "of the ritual, it did take\l"
	.string "me aback just how long you\l"
	.string "two were away...\p"
	.string "...Shunyong battled...you?\n"
	.string "That... I have never heard\l"
	.string "of before. It must have been\l"
	.string "an incredible honor!\p"
	.string "But, I must ask...\n"
	.string "where could your rival be?$"

EverGrandePeak_Text_YoureAGreatTrainer:
	.string "They may still be out there,\n"
	.string "in the infinite sea, trying\l"
	.string "to find some meaning that\l"
	.string "you could not, {PLAYER}...\p"
	.string "They had already a habit of\n"
	.string "going on journeys away\l"
	.string "from the rest of the world...\l"
	.string "this, is no different.\p"
	.string "Regardless. The ritual\n"
	.string "is now completed in full.\l"
	.string "Thank you tremendously\l"
	.string "for your participation in this.\p"
	.string "I will make sure that Hoenn\n"
	.string "never forgets the name {PLAYER}!$"

EverGrandePeak_Text_TheMeaningOfItAll:
	.string "(Throughout this adventure,\n"
	.string "you kept prying in your mind.)\p"
	.string "(What is my purpose?\n"
	.string "What is my legacy?)\p"
	.string "(...The journey was what\n"
	.string "gave meaning to your life.)$"

EverGrandePeak_Text_GoToTheHallOfFame:
	.string "Let us go enshrine your name\n"
	.string "within the Hall of Fame.\l"
	.string "While we lack the Pokemon League\l"
	.string "these days, I still wish to\l"
	.string "uphold that tradition.\p"
	.string "Come, I will escort you.\n$"
