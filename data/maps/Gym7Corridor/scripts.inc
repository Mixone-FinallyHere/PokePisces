.set LOCALID_GYMGUARD, 1

Gym7Corridor_MapScripts::
	.byte 0

Gym7Corridor_EventScript_DoorGuard::
	lock
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 7, Gym7Corridor_EventScript_WantToGoIn
	goto_if_gt VAR_PISCES_STORY_PROGRESS, 7, Gym7Corridor_EventScript_CantGoIn
	release
	end

Gym7Corridor_EventScript_WantToGoIn::
	applymovement LOCALID_GYMGUARD, Gym7Corridor_Movement_GuardFacesYou
	applymovement OBJ_EVENT_ID_PLAYER, Gym7Corridor_Movement_YouFaceGuard
	msgbox Gym7Corridor_Text_AreYouReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Gym7Corridor_EventScript_PrepForGym
	applymovement OBJ_EVENT_ID_PLAYER, Gym7Corridor_Movement_MoveAway
	waitmovement 0
	msgbox Gym7Corridor_Text_ThenGoPrepare, MSGBOX_AUTOCLOSE
	release
	end

Gym7Corridor_EventScript_PrepForGym::
	clearflag FLAG_PISCES_A
	clearflag FLAG_PISCES_B
	clearflag FLAG_PISCES_C
	clearflag FLAG_PISCES_D
	clearflag FLAG_PISCES_E
	clearflag FLAG_PISCES_F
	setflag FLAG_WITHIN_GYM
	cleartrainerflag TRAINER_P_TAHOE
	cleartrainerflag TRAINER_P_HURON
	cleartrainerflag TRAINER_P_EYRE
	cleartrainerflag TRAINER_P_CASPIAN
	cleartrainerflag TRAINER_P_VICTORIA
	cleartrainerflag TRAINER_P_ALBERT
	cleartrainerflag TRAINER_P_MARCEL
	cleartrainerflag TRAINER_P_NESSIE
	msgbox Gym7Corridor_Text_TimeForGym, MSGBOX_DEFAULT
	warp MAP_DEWFORD_GYM_NEW, 33, 21
	waitstate
	release
	end

Gym7Corridor_EventScript_CantGoIn::
	applymovement LOCALID_GYMGUARD, Gym7Corridor_Movement_GuardFacesYou
	applymovement OBJ_EVENT_ID_PLAYER, Gym7Corridor_Movement_YouFaceGuard
	msgbox Gym7Corridor_Text_YouAlreadyDidThis, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Gym7Corridor_Movement_MoveAway
	waitmovement 0
	release
	end

Gym7Corridor_Movement_GuardFacesYou:
	face_right
	step_end

Gym7Corridor_Movement_YouFaceGuard:
	face_left
	step_end

Gym7Corridor_Movement_MoveAway:
	walk_down
	step_end

Gym7Corridor_Text_AreYouReady:
	.string "Welcome to the\n"
	.string "Dewford Gym, challenger.\p"
	.string "We are prepared to receive you.\p"
	.string "However, please be warned that upon\n"
	.string "entry, you will be unable to leave the\l"
	.string "Gym unless your entire\l"
	.string "Pokémon party faints.\p"
	.string "Knowing all this, do you feel that you\n"
	.string "are adequately prepared to\l"
	.string "challenge this gym?$"

Gym7Corridor_Text_ThenGoPrepare:
	.string "That's perfectly fine.\n"
	.string "Please do come back when you are ready.$"

Gym7Corridor_Text_TimeForGym:
	.string "Good luck, challenger.$"

Gym7Corridor_Text_YouAlreadyDidThis:
	.string "You appear to already possess the\n"
	.string "Beach Badge.\p"
	.string "Apologies, but this challenge is only\n"
	.string "for those lacking said badge.$"
