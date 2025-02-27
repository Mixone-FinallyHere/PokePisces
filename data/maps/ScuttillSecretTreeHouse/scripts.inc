.set LOCALID_EGGNEGGMA1, 1
.set LOCALID_EGGNEGGMA2, 2
.set LOCALID_EGGNEGGMA3, 3
.set LOCALID_EGGNEGGMA4, 4
.set LOCALID_EGGNEGGMA5, 5
.set LOCALID_EGGNEGGMA6, 6
.set LOCALID_EGGNEGGMA7, 7
.set LOCALID_EGGNEGGMA8, 8
.set LOCALID_EGGNEGGMA9, 9
.set LOCALID_EGGNEGGMA10, 17
.set LOCALID_OLDLADY, 15
.set LOCALID_OLDLADY2, 16

ScuttillSecretTreeHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ScuttillSecretTreeHouse_OnTransition
	.byte 0

ScuttillSecretTreeHouse_OnTransition:
	call ScuttillSecretTreeHouse_EventScript_SetEggState
	end

ScuttillSecretTreeHouse_EventScript_SetEggState::
	goto_if_set FLAG_SCUTTILL_EGG, ScuttillSecretTreeHouse_EventScript_EggGotten
	goto_if_set FLAG_FAKE_EGG, ScuttillSecretTreeHouse_EventScript_FakeEggGotten
	setvar VAR_TEMP_4, 69
	setvar VAR_TEMP_6, 3
	setflag FLAG_TEMP_10
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	setflag FLAG_TEMP_17
	setflag FLAG_TEMP_18
	setflag FLAG_TEMP_19
	setflag FLAG_TEMP_1D
	return

ScuttillSecretTreeHouse_EventScript_FakeEggGotten::
	getcaughtmon SPECIES_WANNEGG
	goto_if_eq VAR_RESULT, TRUE, ScuttillSecretTreeHouse_EventScript_WanneggHatched
	setvar VAR_TEMP_4, 69
	setflag FLAG_TEMP_10
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	setflag FLAG_TEMP_17
	setflag FLAG_TEMP_18
	setflag FLAG_TEMP_19
	setflag FLAG_TEMP_1C
	return

ScuttillSecretTreeHouse_EventScript_WanneggHatched::
	setvar VAR_TEMP_4, 9
	setvar VAR_TEMP_6, 2
	setflag FLAG_TEMP_10
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	setflag FLAG_TEMP_17
	setflag FLAG_TEMP_19
	setflag FLAG_TEMP_1C
	return

ScuttillSecretTreeHouse_EventScript_EggGotten::
	setvar VAR_TEMP_4, 69
	setflag FLAG_TEMP_10
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	setflag FLAG_TEMP_17
	setflag FLAG_TEMP_18
	setflag FLAG_TEMP_19
	setflag FLAG_TEMP_1C
	setflag FLAG_TEMP_1D
	return

ScuttillSecretTreeHouse_EventScript_ReceiveWannegg::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, ScuttillSecretTreeHouse_Movement_PlayerConfrontEgg
	waitmovement 0
	applymovement LOCALID_OLDLADY, ScuttillSecretTreeHouse_Movement_OldLadySayHello
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, ScuttillSecretTreeHouse_Movement_PlayerFaceLady
	waitmovement 0
	msgbox ScuttillSecretTreeHouse_Text_TakeCareOfThis, MSGBOX_DEFAULT
	setvar VAR_TEMP_6, 0
	setflag FLAG_FAKE_EGG
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EXEGGCUTE
	giveegg SPECIES_WANNEGG
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, ScuttillSecretTreeHouse_EventScript_ReceiveWanneggParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, ScuttillSecretTreeHouse_EventScript_ReceiveWanneggPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

ScuttillSecretTreeHouse_Movement_OldLadySayHello:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_right
	step_end

ScuttillSecretTreeHouse_Movement_PlayerFaceLady:
	face_left
	step_end

ScuttillSecretTreeHouse_EventScript_ReceiveWanneggParty::
	call ScuttillSecretTreeHouse_EventScript_ReceivedWanneggFanfare
	release
	end

ScuttillSecretTreeHouse_EventScript_ReceiveWanneggPC::
	call ScuttillSecretTreeHouse_EventScript_ReceivedWanneggFanfare
	call Common_EventScript_TransferredToPC
	release
	end

ScuttillSecretTreeHouse_EventScript_ReceivedWanneggFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message ScuttillSecretTreeHouse_Text_PlayerReceivedWanegg
	waitmessage
	waitfanfare
	return	

ScuttillSecretTreeHouse_EventScript_EggneggmaHasAppeared::
	lock
	setvar VAR_TEMP_6, 0
	addobject LOCALID_OLDLADY2
	applymovement LOCALID_EGGNEGGMA1, ScuttillSecretTreeHouse_Movement_OldLadyWarning
	waitmovement 0
	msgbox ScuttillSecretTreeHouse_Text_EggWarning, MSGBOX_AUTOCLOSE
	release
	end

ScuttillSecretTreeHouse_Movement_OldLadyWarning:
	walk_left
	walk_left
	walk_left
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter1East::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA1, ScuttillSecretTreeHouse_Movement_EggRunAway1East
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA1
	setflag FLAG_TEMP_10
	addobject LOCALID_EGGNEGGMA4
	clearflag FLAG_TEMP_13
	setvar VAR_TEMP_4, 4
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway1East:
	emote_exclamation_mark
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter1South::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA1, ScuttillSecretTreeHouse_Movement_EggRunAway1South
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA1
	setflag FLAG_TEMP_10
	addobject LOCALID_EGGNEGGMA2
	clearflag FLAG_TEMP_11
	setvar VAR_TEMP_4, 2
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway1South:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter2East::
	lock
	goto_if_eq VAR_TEMP_5, 2, ScuttillSecretTreeHouse_EventScript_EggGoToNest
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, ScuttillSecretTreeHouse_Movement_EggRunAway2East
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_11
	addobject LOCALID_EGGNEGGMA1
	clearflag FLAG_TEMP_10
	setvar VAR_TEMP_4, 1
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway2East:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter2West::
	lock
	goto_if_eq VAR_TEMP_5, 2, ScuttillSecretTreeHouse_EventScript_EggGoToNest
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, ScuttillSecretTreeHouse_Movement_EggRunAway2West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_11
	addobject LOCALID_EGGNEGGMA3
	clearflag FLAG_TEMP_12
	setvar VAR_TEMP_4, 3
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway2West:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter2South::
	lock
	goto_if_eq VAR_TEMP_5, 2, ScuttillSecretTreeHouse_EventScript_EggGoToNest
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, ScuttillSecretTreeHouse_Movement_EggRunAway2South
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_11
	addobject LOCALID_EGGNEGGMA1
	clearflag FLAG_TEMP_10
	setvar VAR_TEMP_4, 1
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway2South:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter3South::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA3, ScuttillSecretTreeHouse_Movement_EggRunAway3South
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA3
	setflag FLAG_TEMP_12
	addobject LOCALID_EGGNEGGMA2
	clearflag FLAG_TEMP_11
	setvar VAR_TEMP_4, 2
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway3South:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter3West::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA3, ScuttillSecretTreeHouse_Movement_EggRunAway3West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA3
	setflag FLAG_TEMP_12
	addobject LOCALID_EGGNEGGMA6
	clearflag FLAG_TEMP_15
	setvar VAR_TEMP_4, 6
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway3West:
	emote_exclamation_mark
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter4North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA4, ScuttillSecretTreeHouse_Movement_EggRunAway4North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA4
	setflag FLAG_TEMP_13
	addobject LOCALID_EGGNEGGMA5
	clearflag FLAG_TEMP_14
	setvar VAR_TEMP_4, 5
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway4North:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter4EastOrSouth::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA4, ScuttillSecretTreeHouse_Movement_EggRunAway4EastOrSouth
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA4
	setflag FLAG_TEMP_13
	addobject LOCALID_EGGNEGGMA1
	clearflag FLAG_TEMP_10
	setvar VAR_TEMP_4, 1
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway4EastOrSouth:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter5North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA5, ScuttillSecretTreeHouse_Movement_EggRunAway5North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 50
	waitmoncry
	removeobject LOCALID_EGGNEGGMA5
	setflag FLAG_TEMP_14
	addobject LOCALID_EGGNEGGMA8
	clearflag FLAG_TEMP_17
	setvar VAR_TEMP_4, 8
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway5North:
	emote_exclamation_mark
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter5West::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA5, ScuttillSecretTreeHouse_Movement_EggRunAway5West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 50
	waitmoncry
	removeobject LOCALID_EGGNEGGMA5
	setflag FLAG_TEMP_14
	addobject LOCALID_EGGNEGGMA6
	clearflag FLAG_TEMP_15
	setvar VAR_TEMP_4, 6
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway5West:
	emote_exclamation_mark
	walk_fast_right
	jump_2_right
	walk_fast_right
	walk_fast_right
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter5East::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA5, ScuttillSecretTreeHouse_Movement_EggRunAway5East
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 50
	waitmoncry
	removeobject LOCALID_EGGNEGGMA5
	setflag FLAG_TEMP_14
	addobject LOCALID_EGGNEGGMA4
	clearflag FLAG_TEMP_13
	setvar VAR_TEMP_4, 4
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway5East:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter5South::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA5, ScuttillSecretTreeHouse_Movement_EggRunAway5South
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 50
	waitmoncry
	removeobject LOCALID_EGGNEGGMA5
	setflag FLAG_TEMP_14
	addobject LOCALID_EGGNEGGMA2
	clearflag FLAG_TEMP_11
	setvar VAR_TEMP_4, 2
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway5South:
	emote_exclamation_mark
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter6North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA6, ScuttillSecretTreeHouse_Movement_EggRunAway6North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA6
	setflag FLAG_TEMP_15
	addobject LOCALID_EGGNEGGMA9
	clearflag FLAG_TEMP_18
	setvar VAR_TEMP_4, 9
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway6North:
	emote_exclamation_mark
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter6WestOrSouth::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA6, ScuttillSecretTreeHouse_Movement_EggRunAway6WestOrSouth
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA6
	setflag FLAG_TEMP_15
	addobject LOCALID_EGGNEGGMA3
	clearflag FLAG_TEMP_12
	setvar VAR_TEMP_4, 6
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway6WestOrSouth:
	emote_exclamation_mark
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter7North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA7, ScuttillSecretTreeHouse_Movement_EggRunAway7North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA7
	setflag FLAG_TEMP_16
	addobject LOCALID_EGGNEGGMA8
	clearflag FLAG_TEMP_17
	setvar VAR_TEMP_4, 8
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway7North:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter7East::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA7, ScuttillSecretTreeHouse_Movement_EggRunAway7East
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA7
	setflag FLAG_TEMP_16
	addobject LOCALID_EGGNEGGMA4
	clearflag FLAG_TEMP_13
	setvar VAR_TEMP_4, 4
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway7East:
	emote_exclamation_mark
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter8North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA8, ScuttillSecretTreeHouse_Movement_EggRunAway8North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA8
	setflag FLAG_TEMP_17
	addobject LOCALID_EGGNEGGMA7
	clearflag FLAG_TEMP_16
	setvar VAR_TEMP_4, 7
	setvar VAR_TEMP_5, 2
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway8North:
	emote_exclamation_mark
	walk_slow_down
	walk_slow_down
	delay_16
	delay_8
	jump_in_place_up
	jump_in_place_up
	jump_in_place_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter8East::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA8, ScuttillSecretTreeHouse_Movement_EggRunAway8East
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA8
	setflag FLAG_TEMP_17
	addobject LOCALID_EGGNEGGMA7
	clearflag FLAG_TEMP_16
	setvar VAR_TEMP_4, 7
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway8East:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter8West::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA8, ScuttillSecretTreeHouse_Movement_EggRunAway8West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA8
	setflag FLAG_TEMP_17
	addobject LOCALID_EGGNEGGMA9
	clearflag FLAG_TEMP_18
	setvar VAR_TEMP_4, 9
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway8West:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter9WestOrEast::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA9, ScuttillSecretTreeHouse_Movement_EggRunAway9WestOrEast
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA9
	setflag FLAG_TEMP_18
	addobject LOCALID_EGGNEGGMA6
	clearflag FLAG_TEMP_15
	setvar VAR_TEMP_4, 6
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway9WestOrEast:
	emote_exclamation_mark
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

ScuttillSecretTreeHouse_EventScript_EggEncounter9North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA9, ScuttillSecretTreeHouse_Movement_EggRunAway9North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA9
	setflag FLAG_TEMP_18
	addobject LOCALID_EGGNEGGMA8
	clearflag FLAG_TEMP_17
	setvar VAR_TEMP_4, 8
	release
	end

ScuttillSecretTreeHouse_Movement_EggRunAway9North:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

ScuttillSecretTreeHouse_EventScript_EggGoToNest::
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, ScuttillSecretTreeHouse_Movement_EggGoToNest
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 60
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_11
	addobject LOCALID_EGGNEGGMA10
	clearflag FLAG_TEMP_19
	setvar VAR_TEMP_4, 10
	release
	end

ScuttillSecretTreeHouse_Movement_EggGoToNest::
	emote_exclamation_mark
	face_down
	face_left
	face_right
	face_up
	delay_16
	delay_16
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_left
	walk_fast_up
	step_end

ScuttillSecretTreeHouse_EventScript_CaughtEggneggma::
	lock
	setvar VAR_TEMP_5, 3
	applymovement OBJ_EVENT_ID_PLAYER, ScuttillSecretTreeHouse_Movement_PlayerConfrontEgg
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA10, ScuttillSecretTreeHouse_Movement_EggBumpIntoPlayer
	waitmovement 0
	playse SE_WALL_HIT
	waitse
	msgbox ScuttillSecretTreeHouse_Text_DroppedEgg, MSGBOX_DEFAULT
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	applymovement LOCALID_EGGNEGGMA10, ScuttillSecretTreeHouse_Movement_EggFlee
	waitmovement 0
	removeobject LOCALID_EGGNEGGMA10
	setflag FLAG_TEMP_19
	setflag FLAG_SCUTTILL_EGG
	setvar VAR_TEMP_4, 69
	goto ScuttillSecretTreeHouse_EventScript_ReceiveEgg
	release
	end

ScuttillSecretTreeHouse_EventScript_ReceiveEgg::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EXEGGCUTE
	giveegg SPECIES_CHIKA
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, ScuttillSecretTreeHouse_EventScript_ReceiveEggParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, ScuttillSecretTreeHouse_EventScript_ReceiveEggPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

ScuttillSecretTreeHouse_EventScript_ReceiveEggParty::
	call ScuttillSecretTreeHouse_EventScript_ReceivedEggFanfare
	release
	end

ScuttillSecretTreeHouse_EventScript_ReceiveEggPC::
	call ScuttillSecretTreeHouse_EventScript_ReceivedEggFanfare
	call Common_EventScript_TransferredToPC
	release
	end

ScuttillSecretTreeHouse_EventScript_ReceivedEggFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message ScuttillSecretTreeHouse_Text_PlayerReceivedEgg
	waitmessage
	waitfanfare
	return

ScuttillSecretTreeHouse_Movement_PlayerConfrontEgg:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

ScuttillSecretTreeHouse_Movement_EggBumpIntoPlayer:
	emote_exclamation_mark
	delay 30
	delay 30
	walk_fast_down
	step_end

ScuttillSecretTreeHouse_Movement_EggFlee:
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

ScuttillSecretTreeHouse_EventScript_EggLadyState1::
	lock
	faceplayer
	goto_if_set FLAG_FAKE_EGG, ScuttillSecretTreeHouse_EventScript_EggLadyState2
	msgbox ScuttillSecretTreeHouse_Text_DontMindMe, MSGBOX_AUTOCLOSE
	release
	end

ScuttillSecretTreeHouse_EventScript_EggLadyState2::
	msgbox ScuttillSecretTreeHouse_Text_HatchThatEgg, MSGBOX_AUTOCLOSE
	release
	end

ScuttillSecretTreeHouse_EventScript_EggLadyState3::
	lock
	faceplayer
	goto_if_set FLAG_FAKE_EGG, ScuttillSecretTreeHouse_EventScript_EggLadyState4
	msgbox ScuttillSecretTreeHouse_Text_ThisAreaHotspot, MSGBOX_AUTOCLOSE
	release
	end

ScuttillSecretTreeHouse_EventScript_EggLadyState4::
	msgbox ScuttillSecretTreeHouse_Text_MayNowBeSafe, MSGBOX_AUTOCLOSE
	release
	end

ScuttillSecretTreeHouse_EventScript_HowToCatchEgg::
	msgbox ScuttillSecretTreeHouse_Text_HowToCatchEgg, MSGBOX_NPC
	end

ScuttillSecretTreeHouse_Text_DontMindMe:
	.string "Oh, don't mind an old hag like me...\n"
	.string "I just enjoy looking after\l"
	.string "the little Coffiddle...$"

ScuttillSecretTreeHouse_Text_TakeCareOfThis:
	.string "So you're interested in this\n"
	.string "Coffiddle nest?\p"
	.string "These munchkins bring abandoned\n"
	.string "eggs here and dance nearby\l"
	.string "to them. It appears to help\l"
	.string "them hatch somewhat quicker.\l"
	.string "Then, the Coffiddle gets\l"
	.string "a new dance partner!\p"
	.string "You seem to be a Pokemon Trainer.\n"
	.string "Take one of these eggs and\l"
	.string "give it a good home.$"

ScuttillSecretTreeHouse_Text_PlayerReceivedWanegg:
	.string "{PLAYER} took one of the Eggs!$"

ScuttillSecretTreeHouse_Text_HatchThatEgg:
	.string "Even I don't know what Pokemon\n"
	.string "could hatch from that Egg...\l"
	.string "They were all abandoned,\l"
	.string "so it's anybody's guess.$"

ScuttillSecretTreeHouse_Text_ThisAreaHotspot:
	.string "That Coffiddle nest is\n"
	.string "unfortunately a target for those\l"
	.string "dastardly Eggneggma.\l"
	.string "I try to get them shooed\l"
	.string "whenever I'm able.$"

ScuttillSecretTreeHouse_Text_EggWarning:
	.string "Oh! You have returned.\n"
	.string "I see that Egg you took with you\l"
	.string "turned out to be a Wannegg\l"
	.string "in disguise.\p"
	.string "It appears that an Eggneggma planted\n"
	.string "one of its young to be taken\l"
	.string "to the nest, so it could\l"
	.string "determine where it was located.\p"
	.string "...Oh, bother... an Eggneggma\n"
	.string "is likely en route to the nest\l"
	.string "right this moment...$"

ScuttillSecretTreeHouse_Text_DroppedEgg:
	.string "(The Eggneggma dropped the\n"
	.string "Egg it was holding!)$"

ScuttillSecretTreeHouse_Text_PlayerReceivedEgg:
	.string "{PLAYER} rescued another Egg!$"

ScuttillSecretTreeHouse_Text_MayNowBeSafe:
	.string "The Eggneggma has been fended off\n"
	.string "for now. On behalf of those\l"
	.string "dancing critters, I thank you.$"

ScuttillSecretTreeHouse_Text_HowToCatchEgg:
	.string "Whenever those egg bandits show\n"
	.string "their ugly mugs around here,\l"
	.string "ya gotta chase 'em off.\p"
	.string "Best way to intimidate them\n"
	.string "is to make 'em feel cornered.\l"
	.string "Even if it escapes an attempt,\l"
	.string "if you manage to corner it for\l"
	.string "even a moment, it will start\l"
	.string "to panic, and maybe make\l"
	.string "mistakes that it wouldn't normally.$"
