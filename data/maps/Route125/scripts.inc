.set LOCALID_EGGNEGGMA1, 17
.set LOCALID_EGGNEGGMA2, 14
.set LOCALID_EGGNEGGMA3, 15
.set LOCALID_EGGNEGGMA4, 16
.set LOCALID_BIRDWATCHER, 8
.set LOCALID_EGGLIKERMAN, 18
.set LOCALID_EGGLIKERLADY, 19

Route125_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route125_OnTransition
	.byte 0

Route125_OnTransition:
	call Route125_EventScript_SetEggState
	goto_if_unset FLAG_DEFEATED_PANIC_EVENT, Route125_EventScript_SurferBlocking
	end

Route125_EventScript_SetEggState::
	goto_if_set FLAG_TRAP_PRECIPIKE_EGGNEGGMA, Route125_EventScript_CaptureEggneggmaState
	goto_if_set FLAG_PRECIPIKE_EGG, Route125_EventScript_EggGotten
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	return

Route125_EventScript_CaptureEggneggmaState::
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	return

Route125_EventScript_EggGotten::
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	setvar VAR_TEMP_4, 5
	return

Route125_EventScript_SurferBlocking::
	setflag FLAG_TEMP_17
	end

Route125_EventScript_LeftRoadblocker::
	lock
	msgbox Route125_Text_Left_1, MSGBOX_AUTOCLOSE
	release
	end

Route125_EventScript_LeftRoadblockerPost::
	lock
	msgbox Route125_Text_Left_2, MSGBOX_AUTOCLOSE
	release
	end

Route125_EventScript_RightRoadblocker::
	lock
	goto_if_set FLAG_DEFEATED_PANIC_EVENT, Route125_EventScript_RightRoadblockerPost
	msgbox Route125_Text_Right_1, MSGBOX_AUTOCLOSE
	release
	end

Route125_EventScript_RightRoadblockerPost::
	faceplayer
	msgbox Route125_Text_Right_2, MSGBOX_AUTOCLOSE
	release
	end

Route125_EventScript_EggEncounter1South::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA1, Route125_Movement_EggRunAway1South
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA1
	setflag FLAG_TEMP_11
	clearflag FLAG_TEMP_12
	setvar VAR_TEMP_4, 1
	release
	end

Route125_Movement_EggRunAway1South:
	emote_exclamation_mark
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route125_EventScript_EggEncounter1North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA1, Route125_Movement_EggRunAway1North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA1
	setflag FLAG_TEMP_11
	clearflag FLAG_TEMP_14
	setvar VAR_TEMP_4, 3
	release
	end

Route125_Movement_EggRunAway1North:
	emote_exclamation_mark
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route125_EventScript_EggEncounter2East::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, Route125_Movement_EggRunAway2East
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_12
	clearflag FLAG_TEMP_13
	setvar VAR_TEMP_4, 2
	release
	end

Route125_Movement_EggRunAway2East:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route125_EventScript_EggEncounter2WestTop::
	lock
	goto_if_set FLAG_TRAP_PRECIPIKE_EGGNEGGMA, Route125_EventScript_EggEncounterTrapTop
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, Route125_Movement_EggRunAway2West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_12
	clearflag FLAG_TEMP_11
	setvar VAR_TEMP_4, 0
	release
	end

Route125_Movement_EggRunAway2West:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route125_EventScript_EggEncounter2WestBottom::
	lock
	goto_if_set FLAG_TRAP_PRECIPIKE_EGGNEGGMA, Route125_EventScript_EggEncounterTrapBottom
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, Route125_Movement_EggRunAway2West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_12
	clearflag FLAG_TEMP_11
	setvar VAR_TEMP_4, 0
	release
	end

Route125_EventScript_EggEncounter3North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA3, Route125_Movement_EggRunAway3North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA3
	setflag FLAG_TEMP_13
	clearflag FLAG_TEMP_14
	setvar VAR_TEMP_4, 3
	release
	end

Route125_Movement_EggRunAway3North:
	emote_exclamation_mark
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route125_EventScript_EggEncounter3South::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA3, Route125_Movement_EggRunAway3South
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA3
	setflag FLAG_TEMP_13
	clearflag FLAG_TEMP_12
	setvar VAR_TEMP_4, 1
	release
	end

Route125_Movement_EggRunAway3South:
	emote_exclamation_mark
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route125_EventScript_EggEncounter4West::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA4, Route125_Movement_EggRunAway4West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA4
	setflag FLAG_TEMP_14
	clearflag FLAG_TEMP_11
	setvar VAR_TEMP_4, 0
	release
	end

Route125_Movement_EggRunAway4West:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Route125_EventScript_EggEncounter4East::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA4, Route125_Movement_EggRunAway4East
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA4
	setflag FLAG_TEMP_14
	clearflag FLAG_TEMP_13
	setvar VAR_TEMP_4, 2
	release
	end

Route125_Movement_EggRunAway4East:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route125_EventScript_EggEncounterTrapTop::
	applymovement OBJ_EVENT_ID_PLAYER, Route125_Movement_PlayerGetIntoPos
	goto Route125_EventScript_EggEncounterTrapBottom
	release
	end

Route125_Movement_PlayerGetIntoPos:
	walk_down
	face_right
	step_end

Route125_EventScript_EggEncounterTrapBottom::
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, Route125_Movement_EggNervous
	waitmovement 0
	msgbox Route125_Text_WeHaveYouCornered, MSGBOX_DEFAULT
	applymovement LOCALID_EGGLIKERMAN, Route125_Movement_BlockEgg1
	applymovement LOCALID_EGGLIKERLADY, Route125_Movement_BlockEgg2
	applymovement LOCALID_BIRDWATCHER, Route125_Movement_BlockEgg3
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	applymovement LOCALID_EGGNEGGMA2, Route125_Movement_EggUpset
	waitmovement 0
	setflag FLAG_PISCES_D
	clearflag FLAG_TRAP_PRECIPIKE_EGGNEGGMA
	msgbox Route125_Text_GotYouBitch, MSGBOX_DEFAULT
	warp MAP_PRECIPIKE_INTERIORS, 6, 4
	waitstate
	release
	end

Route125_Movement_EggNervous:
	emote_exclamation_mark
	delay_16
	face_left
	step_end

Route125_Movement_BlockEgg1:
	walk_down
	walk_right
	step_end

Route125_Movement_BlockEgg2:
	walk_fast_down
	walk_left
	walk_left
	walk_left
	step_end

Route125_Movement_BlockEgg3:
	walk_left
	walk_left
	step_end

Route125_Movement_EggUpset:
	face_right
	delay_8
	face_left
	delay_8
	face_right
	delay_8
	face_left
	jump_in_place_down
	step_end

Route125_EventScript_Shellylouh::
	lock
	faceplayer
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_1, Route125_EventScript_SeekOutOtherShelly
	checkitem ITEM_PEARL_STRING
	goto_if_eq VAR_RESULT, TRUE, Route125_EventScript_GiveSnailPolish
	msgbox Route125_Text_ShellRiddle1, MSGBOX_AUTOCLOSE
	release
	end

Route125_EventScript_GiveSnailPolish::
	msgbox Route125_Text_HereIsShellPolish, MSGBOX_DEFAULT
	removeitem ITEM_PEARL_STRING
	giveitem ITEM_SHELL_POLISH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SHELLYLOUH_RIDDLE_1
	goto Route125_EventScript_SeekOutOtherShelly
	release
	end

Route125_EventScript_SeekOutOtherShelly::
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_2, Route125_EventScript_CheckRiddle3
	msgbox Route125_Text_SeekOutOtherShelly, MSGBOX_AUTOCLOSE
	release
	end

Route125_EventScript_CheckRiddle3::
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_3, Route125_EventScript_AllRiddles
	msgbox Route125_Text_SeekOutOtherShelly, MSGBOX_AUTOCLOSE
	release
	end

Route125_EventScript_AllRiddles::
	checkitem ITEM_BIG_PEARL
	goto_if_eq VAR_RESULT, TRUE, Route125_EventScript_GaveBigPearl
	msgbox Route125_Text_YouEarnedThisBigPearl, MSGBOX_DEFAULT
	giveitem ITEM_BIG_PEARL
	closemessage
	release
	end

Route125_EventScript_GaveBigPearl::
	msgbox Route125_Text_GaveBigPearl, MSGBOX_AUTOCLOSE
	release
	end

Route125_EventScript_GravelitoIdle::
	lock
	setflag FLAG_TEMP_A
	clearflag FLAG_TEMP_B
	msgbox Route125_Text_ItsHumming, MSGBOX_DEFAULT
	goto Route125_EventScript_CheckSing
	release
	end

Route125_EventScript_MegalitoIdle::
	lock
	clearflag FLAG_TEMP_A
	setflag FLAG_TEMP_B
	msgbox Route125_Text_ItsBellowing, MSGBOX_DEFAULT
	goto Route125_EventScript_CheckSing
	release
	end

Route125_EventScript_CheckSing::
	checkpartynonhmmove MOVE_SING
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route125_EventScript_CheckPerishSong
	goto_if_set FLAG_TEMP_A, Route125_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, Route125_EventScript_MegalitoBattle
	release
	end

Route125_EventScript_CheckPerishSong::
	checkpartynonhmmove MOVE_PERISH_SONG
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route125_EventScript_CheckGrassWhistle
	goto_if_set FLAG_TEMP_A, Route125_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, Route125_EventScript_MegalitoBattle
	release
	end

Route125_EventScript_CheckGrassWhistle::
	checkpartynonhmmove MOVE_GRASS_WHISTLE
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route125_EventScript_CheckRound
	goto_if_set FLAG_TEMP_A, Route125_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, Route125_EventScript_MegalitoBattle
	release
	end

Route125_EventScript_CheckRound::
	checkpartynonhmmove MOVE_ROUND
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route125_EventScript_CheckSparklingAria
	goto_if_set FLAG_TEMP_A, Route125_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, Route125_EventScript_MegalitoBattle
	release
	end

Route125_EventScript_CheckSparklingAria::
	checkpartynonhmmove MOVE_SPARKLING_ARIA
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route125_EventScript_CheckTorchSong
	goto_if_set FLAG_TEMP_A, Route125_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, Route125_EventScript_MegalitoBattle
	release
	end

Route125_EventScript_CheckTorchSong::
	checkpartynonhmmove MOVE_TORCH_SONG
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route125_EventScript_CheckBeatbox
	goto_if_set FLAG_TEMP_A, Route125_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, Route125_EventScript_MegalitoBattle
	release
	end

Route125_EventScript_CheckBeatbox::
	checkpartynonhmmove MOVE_BEATBOX
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route125_EventScript_CheckBeatDrop
	goto_if_set FLAG_TEMP_A, Route125_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, Route125_EventScript_MegalitoBattle
	release
	end

Route125_EventScript_CheckBeatDrop::
	checkpartynonhmmove MOVE_BEAT_DROP
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route125_EventScript_NoSingingMoves
	goto_if_set FLAG_TEMP_A, Route125_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, Route125_EventScript_MegalitoBattle
	release
	end

Route125_EventScript_NoSingingMoves::
	msgbox Route125_Text_NoSingingMove, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

Route125_EventScript_GravelitoBattle::
	lock
	msgbox Route125_Text_ItBecameLively, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_GRAVELITO, 16
	playmoncry SPECIES_GRAVELITO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	removeobject VAR_LAST_TALKED
	release
	end

Route125_EventScript_MegalitoBattle::
	lock
	msgbox Route125_Text_ItBecameLively, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_MEGALITO, 35
	playmoncry SPECIES_MEGALITO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	removeobject VAR_LAST_TALKED
	release
	end

Route125_EventScript_Van::
    trainerbattle_single TRAINER_P_VAN, Route125_Text_VanIntro, Route125_Text_VanDefeated
    msgbox Route125_Text_VanPostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_AprilMae::
    trainerbattle_double TRAINER_P_APRIL_AND_MAE, Route125_Text_AprilMaeIntro, Route125_Text_AprilMaeDefeated, Route125_Text_AprilMaeNeedTwoMons
    msgbox Route125_Text_AprilMaePostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_Wren::
    trainerbattle_single TRAINER_P_WREN, Route125_Text_WrenIntro, Route125_Text_WrenDefeated
    msgbox Route125_Text_WrenPostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_Raine::
    trainerbattle_single TRAINER_P_RAINE, Route125_Text_RaineIntro, Route125_Text_RaineDefeated
    msgbox Route125_Text_RainePostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_Skye::
    trainerbattle_single TRAINER_P_SKYE, Route125_Text_SkyeIntro, Route125_Text_SkyeDefeated
    msgbox Route125_Text_SkyePostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_Guunther::
    trainerbattle_single TRAINER_P_GUUNTHER, Route125_Text_GuuntherIntro, Route125_Text_GuuntherDefeated
    msgbox Route125_Text_GuuntherPostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_Ava::
    trainerbattle_single TRAINER_P_AVA, Route125_Text_AvaIntro, Route125_Text_AvaDefeated
    msgbox Route125_Text_AvaPostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_Junichi::
    trainerbattle_single TRAINER_P_JUNICHI, Route125_Text_JunichiIntro, Route125_Text_JunichiDefeated
    msgbox Route125_Text_JunichiPostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_Nelly::
    trainerbattle_single TRAINER_P_NELLY, Route125_Text_NellyIntro, Route125_Text_NellyDefeated
    msgbox Route125_Text_NellyPostBattle, MSGBOX_AUTOCLOSE
    end

Route125_EventScript_Joan::
    trainerbattle_single TRAINER_P_JOAN, Route125_Text_JoanIntro, Route125_Text_JoanDefeated
    msgbox Route125_Text_JoanPostBattle, MSGBOX_AUTOCLOSE
    end

Route125_Text_VanIntro:
	.string "intro$"

Route125_Text_VanDefeated:
	.string "defeat$"

Route125_Text_VanPostBattle:
	.string "post$"

Route125_Text_AprilMaeIntro:
	.string "intro$"

Route125_Text_AprilMaeDefeated:
	.string "defeat$"

Route125_Text_AprilMaeNeedTwoMons:
	.string "need 2 dood$"

Route125_Text_AprilMaePostBattle:
	.string "post$"

Route125_Text_WrenIntro:
	.string "intro$"

Route125_Text_WrenDefeated:
	.string "defeat$"

Route125_Text_WrenPostBattle:
	.string "post$"

Route125_Text_RaineIntro:
	.string "intro$"

Route125_Text_RaineDefeated:
	.string "defeat$"

Route125_Text_RainePostBattle:
	.string "post$"

Route125_Text_SkyeIntro:
	.string "intro$"

Route125_Text_SkyeDefeated:
	.string "defeat$"

Route125_Text_SkyePostBattle:
	.string "post$"

Route125_Text_GuuntherIntro:
	.string "intro$"

Route125_Text_GuuntherDefeated:
	.string "defeat$"

Route125_Text_GuuntherPostBattle:
	.string "post$"

Route125_Text_AvaIntro:
	.string "intro$"

Route125_Text_AvaDefeated:
	.string "defeat$"

Route125_Text_AvaPostBattle:
	.string "post$"

Route125_Text_JunichiIntro:
	.string "intro$"

Route125_Text_JunichiDefeated:
	.string "defeat$"

Route125_Text_JunichiPostBattle:
	.string "post$"

Route125_Text_NellyIntro:
	.string "intro$"

Route125_Text_NellyDefeated:
	.string "defeat$"

Route125_Text_NellyPostBattle:
	.string "post$"

Route125_Text_JoanIntro:
	.string "intro$"

Route125_Text_JoanDefeated:
	.string "defeat$"

Route125_Text_JoanPostBattle:
	.string "post$"

Route125_Text_ShellRiddle1:
	.string "In shores along the mossy deep\n"
	.string "a path for you to trail\l"
	.string "Below the bluffs behind the tree\l"
	.string "a gate beyond the veil\l"
	.string "Beneath the silence two you find\l"
	.string "clandestine and serene\l"
	.string "Retrieve the pearly strand they hold\l"
	.string "and earn your precious sheen$"

Route125_Text_HereIsShellPolish:
	.string "(This Pokemon seems pleased\n"
	.string "with you. She is gesturing towards\l"
	.string "your Pearl String.)\p"
	.string "(You hand the String over, and she\n"
	.string "gifts you something in return.)$"

Route125_Text_SeekOutOtherShelly:
	.string "There may yet be more of my kind\n"
	.string "At peaceful beaches, shall you find\l"
	.string "Solve their riddles with haste\l"
	.string "And your effort won't go to waste$"

Route125_Text_YouEarnedThisBigPearl:
	.string "All of our coven stand impressed\n"
	.string "with your pursuing of our quest\l"
	.string "A pearl that shines above all ores\l"
	.string "you are able to now call... yours.$"

Route125_Text_GaveBigPearl:
	.string "We have a fondness for you\n"
	.string "for always helping Shellylouh!$"

Route125_Text_WeHaveYouCornered:
	.string "We've got the jump on\n"
	.string "you now, Eggneggma...!$"

Route125_Text_Left_1:
	.string "(Two men are locked here in a\n"
	.string "fierce grapple.)\p"
	.string "K-Kushiwara-San…! I WILL NOT…\n"
	.string "FALL… TO YOU…!\p"
	.string "(This seems to be their final battle…)$"

Route125_Text_Right_1:
	.string "(Two men are locked here in a\n"
	.string "fierce grapple.)\p"
	.string "BOKIKOOO…!\p"
	.string "GIVE ME… ALL YOU'VE GOT…!$"
	.string "(This seems to be their final battle…)$"

Route125_Text_Left_2:
	.string "Helloooo…! Up there!\p"
	.string "I won't lose next time…!$"

Route125_Text_Right_2:
	.string "I gave it my all…\n"
	.string "and vanquished my lifelong rival…\p"
	.string "Over… what, you ask?\p"
	.string "He called me a… grrRR…!\n"
	.string "A DOO-DOO HEAD!!$"

Route125_Text_GotYouBitch:
	.string "You're completely surrounded!\n"
	.string "Time to give up that Egg you filched!$"

Route125_Text_ItsHumming:
	.string "(This strange plant seems\n"
	.string "to be humming a tune...)$"

Route125_Text_ItsBellowing:
	.string "(Your Pokemon used a singing move\n"
	.string "to add to the harmony...)$"

Route125_Text_NoSingingMove:
	.string "(...Nothing you can really\n"
	.string "do with it right now.)$"

Route125_Text_ItBecameLively:
	.string "(The plant became lively!\n"
	.string "It's a Wild Pokemon!)$"
