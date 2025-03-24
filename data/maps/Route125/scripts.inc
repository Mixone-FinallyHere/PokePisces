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

Route125_EventScript_EggHusband::
	msgbox Route125_Text_EggHusband, MSGBOX_NPC
	end

Route125_EventScript_EggWife::
	msgbox Route125_Text_EggWife, MSGBOX_NPC
	end

Route125_EventScript_PrecipikeSign::
	msgbox Route125_Text_PrecipikeSign, MSGBOX_SIGN
	end

Route125_EventScript_EggEnthusiastHouse::
	msgbox Route125_Text_EggEnthusiastHouse, MSGBOX_SIGN
	end

Route125_EventScript_IcipikeSign::
	msgbox Route125_Text_IcipikeSign, MSGBOX_SIGN
	end

Route125_Text_EggHusband:
	.string "Go ahead and lure that Eggneggma\n"
	.string "over to this bridge.\p"
	.string "Then, you and I will run\n"
	.string "at it from this direction,\l"
	.string "right into my wife!\l"
	.string "She'll nab the thing!$"

Route125_Text_EggWife:
	.string "We'll catch that dastardly thief!\n"
	.string "Get it to come over here,\l"
	.string "and we'll have it cornered!$"

Route125_Text_PrecipikeSign:
	.string "PRECIPIKE BLUFF\n"
	.string "Watch your step!\l"
	.string "Steep cliffs ahead!$"

Route125_Text_EggEnthusiastHouse:
	.string "Egg Enthusiast's House\n"
	.string "Please report all Egg Thief\l"
	.string "findings to us!$"

Route125_Text_IcipikeSign:
	.string "ICIPIKE CAVE\n"
	.string "Interior is iced over!\l"
	.string "Wear safety gear when entering!$"

Route125_Text_VanIntro:
	.string "My parents really wanted to live\n"
	.string "in a van their whole lives.\l"
	.string "So much so that they named\l"
	.string "me after a van. A VAN.\p"
	.string "So yeah, I'm a grumpy kid!\n"
	.string "And I gotta take it out on SOMEBODY!$"

Route125_Text_VanDefeated:
	.string "My brother Winnebago may have\n"
	.string "held his own better...$"

Route125_Text_VanPostBattle:
	.string "Man am I SICK of traveling.\n"
	.string "Just let me stay in one school!$"

Route125_Text_AprilMaeIntro:
	.string "APRIL: Try and guess what month\n"
	.string "       my sister and I were born in!\l"
	.string "MAE: Yeah, guess!\p"
	.string "(This has to be a trick question.)$"

Route125_Text_AprilMaeDefeated:
	.string "That's right! August!$"

Route125_Text_AprilMaeNeedTwoMons:
	.string "We won't give you the time of\n"
	.string "day unless you have more than\l"
	.string "one Pokemon with you!$"

Route125_Text_AprilMaePostBattle:
	.string "APRIL: We were supposed to be\n"
	.string "      triplets until the last second!\l"
	.string "MAE: Poor June got absorbed\l"
	.string "     in Mom's belly...$"

Route125_Text_WrenIntro:
	.string "I'm keeping an eye out\n"
	.string "for Egg Thieves!\p"
	.string "You better not be thinking\n"
	.string "anything underhanded!$"

Route125_Text_WrenDefeated:
	.string "Cracked and scrambled...$"

Route125_Text_WrenPostBattle:
	.string "My mom's been looking for Egg\n"
	.string "Thieves too. She's in that house\l"
	.string "by the cliff. If you wanna help,\l"
	.string "that is!$"

Route125_Text_RaineIntro:
	.string "The high seas call my name!$"

Route125_Text_RaineDefeated:
	.string "I feel like I got wrecked\n"
	.string "by a massive wave!$"

Route125_Text_RainePostBattle:
	.string "There's nothing better than\n"
	.string "a journey on the water!$"

Route125_Text_SkyeIntro:
	.string "Huh? A battle?\n"
	.string "Uhh... oookay!$"

Route125_Text_SkyeDefeated:
	.string "Checkmate, I guess.\n$"

Route125_Text_SkyePostBattle:
	.string "I tried playing chess with\n"
	.string "my Pidium the other day and\l"
	.string "I just COULDN'T win!\p"
	.string "It's like he knows every move\n"
	.string "I'm 'bout to make before I\l"
	.string "even do it...$"

Route125_Text_GuuntherIntro:
	.string "You can't beat me!\n"
	.string "I have studied and learned the\l"
	.string "best styles of Pokemon battling\l"
	.string "from only the GREATEST Unovan\l"
	.string "films ever made!\p"
	.string "Feel my wrath!!$"

Route125_Text_GuuntherDefeated:
	.string "How could my movie knowledge fail me?\n"
	.string "This...\l"
	.string "This can't be happening...!$"

Route125_Text_GuuntherPostBattle:
	.string "Once I save up enough moolah, I'm\n"
	.string "gonna take a trip to Unova\l"
	.string "to experience the grandiosity\l"
	.string "of PokeStar Studios firsthand!$"

Route125_Text_AvaIntro:
	.string "Don't you...\n"
	.string "d-don't you know about the birds?$"

Route125_Text_AvaDefeated:
	.string "Well.\p"
	.string "Everybody knows!\n"
	.string "'cept me, I guess...$"

Route125_Text_AvaPostBattle:
	.string "I wish birds were real...$"

Route125_Text_JunichiIntro:
	.string "Wanna hear a cool bug fact!?$"

Route125_Text_JunichiDefeated:
	.string "Too bad!\n"
	.string "I'm tellin' you anyways!$"

Route125_Text_JunichiPostBattle:
	.string "When a Maggorde evolves into Flague,\n"
	.string "all of its siblings evolve too!\p"
	.string "That's your daily bug fact!$"

Route125_Text_NellyIntro:
	.string "Oh, I'm going STRAIGHT to detention\n"
	.string "when I walk in THIS late to class...$"

Route125_Text_NellyDefeated:
	.string "Might as well stop and\n"
	.string "smell the roses!$"

Route125_Text_NellyPostBattle:
	.string "I'm late almost every day...\n"
	.string "I'm just really unlucky in\l"
	.string "the mornings, I guess.$"

Route125_Text_JoanIntro:
	.string "The acoustics in between the two\n"
	.string "cliff faces here are KILLER!$"

Route125_Text_JoanDefeated:
	.string "Oof... Gotta work on\n"
	.string "my feedback.$"

Route125_Text_JoanPostBattle:
	.string "My practice scares the Pokemon\n"
	.string "away sometimes.\p"
	.string "At least the Gravelito\n"
	.string "seem to enjoy it!$"

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
