.set LOCALID_WINONA, 7
.set LOCALID_GYMGUARD, 6

FortreeGymNew_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeGymNew_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeGymNew_OnWarp
	.byte 0

FortreeGymNew_OnTransition:
	special RotatingGate_InitPuzzle
	end

FortreeGymNew_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeGymNew_EventScript_InitRotatingGates
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
FortreeGymNew_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeGymNew_EventScript_DoorGuard::
	lock
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 4, FortreeGymNew_EventScript_WantToGoIn
	goto_if_gt VAR_PISCES_STORY_PROGRESS, 4, FortreeGymNew_EventScript_CantGoIn
	release
	end

FortreeGymNew_EventScript_WantToGoIn::
	applymovement LOCALID_GYMGUARD, FortreeGymNew_Movement_GuardFacesYou
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_YouFaceGuard
	msgbox FortreeGymNew_Text_AreYouReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeGymNew_EventScript_PrepForGym
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_MoveAway
	waitmovement 0
	msgbox FortreeGymNew_Text_ThenGoPrepare, MSGBOX_AUTOCLOSE
	release
	end

FortreeGymNew_EventScript_PrepForGym::
	getdoublessizeforgym
	goto_if_eq VAR_RESULT, 0, FortreeGymNew_EventScript_NotEnoughMons
	clearflag FLAG_PISCES_A
	clearflag FLAG_PISCES_B
	clearflag FLAG_PISCES_C
	clearflag FLAG_PISCES_D
	clearflag FLAG_PISCES_E
	clearflag FLAG_PISCES_F
	setflag FLAG_WITHIN_GYM
	cleartrainerflag TRAINER_P_FUJI
	cleartrainerflag TRAINER_P_DENALI
	cleartrainerflag TRAINER_P_RAINIER
	cleartrainerflag TRAINER_P_EVEREST
	cleartrainerflag TRAINER_P_LHOTSE
	msgbox FortreeGymNew_Text_TimeForGym, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_IntoGym
	waitmovement 0
	release
	end

FortreeGymNew_EventScript_NotEnoughMons::
	msgbox FortreeGymNew_Text_NotEnoughMons, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_MoveAway
	waitmovement 0
	release
	end

FortreeGymNew_EventScript_CantGoIn::
	applymovement LOCALID_GYMGUARD, FortreeGymNew_Movement_GuardFacesYou
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_YouFaceGuard
	msgbox FortreeGymNew_Text_YouAlreadyDidThis, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_MoveAway
	waitmovement 0
	release
	end

FortreeGymNew_Movement_GuardFacesYou:
	face_right
	step_end

FortreeGymNew_Movement_YouFaceGuard:
	face_left
	step_end

FortreeGymNew_Movement_MoveAway:
	walk_up
	step_end

FortreeGymNew_Movement_IntoGym:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

FortreeGymNew_EventScript_CantStopNow::
	lock
	msgbox FortreeGymNew_Text_CantStopNow, MSGBOX_AUTOCLOSE
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_CantStopChallenge
	waitmovement 0
	release
	end

FortreeGymNew_Movement_CantStopChallenge:
	walk_left
	step_end

FortreeGymNew_EventScript_JumpToArena::
	lock
	faceplayer
	speakername FortreeGymNew_Text_NameWinona
	msgbox FortreeGymNew_Text_SurprisedToSeeYou, MSGBOX_DEFAULT
	applymovement LOCALID_WINONA, FortreeGymNew_Movement_FaceUp
	msgbox FortreeGymNew_Text_TakeALeapOfFaith, MSGBOX_DEFAULT
	waitmessage
	applymovement LOCALID_WINONA, FortreeGymNew_Movement_JumpOff
	waitmovement 0
	closemessage
	speakername NULL
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_MoveAway
	waitmovement 0
	delay 16
	applymovement OBJ_EVENT_ID_PLAYER, FortreeGymNew_Movement_JumpOff
	waitmovement 0
	warp MAP_FORTREE_GYM_BATTLE_LOCATION, 7, 6
	waitstate
	release
	end

FortreeGymNew_Movement_FaceUp:
	face_up
	step_end

FortreeGymNew_Movement_JumpOff:
	jump_2_up
	set_invisible
	step_end

FortreeGymNew_EventScript_Everest::
    trainerbattle_single TRAINER_P_EVEREST, FortreeGymNew_Text_EverestIntro, FortreeGymNew_Text_EverestDefeated
    msgbox FortreeGymNew_Text_EverestPostBattle, MSGBOX_AUTOCLOSE
    end

FortreeGymNew_EventScript_Lhotse::
    trainerbattle_single TRAINER_P_LHOTSE, FortreeGymNew_Text_LhotseIntro, FortreeGymNew_Text_LhotseDefeated
    msgbox FortreeGymNew_Text_LhotsePostBattle, MSGBOX_AUTOCLOSE
    end

FortreeGymNew_EventScript_Denali::
    trainerbattle_single TRAINER_P_DENALI, FortreeGymNew_Text_DenaliIntro, FortreeGymNew_Text_DenaliDefeated
    msgbox FortreeGymNew_Text_DenaliPostBattle, MSGBOX_AUTOCLOSE
    end

FortreeGymNew_EventScript_Rainier::
    trainerbattle_single TRAINER_P_RAINIER, FortreeGymNew_Text_RainierIntro, FortreeGymNew_Text_RainierDefeated
    msgbox FortreeGymNew_Text_RainierPostBattle, MSGBOX_AUTOCLOSE
    end

FortreeGymNew_EventScript_Fuji::
    trainerbattle_single TRAINER_P_FUJI, FortreeGymNew_Text_FujiIntro, FortreeGymNew_Text_FujiDefeated
    msgbox FortreeGymNew_Text_FujiPostBattle, MSGBOX_AUTOCLOSE
    end

FortreeGymNew_Text_EverestIntro:
	.string "Here I can stand proud and tall!$"

FortreeGymNew_Text_EverestDefeated:
	.string "Oops! Bumped my head...$"

FortreeGymNew_Text_EverestPostBattle:
	.string "I like looking down at the people on the\n"
	.string "bottom. I'm taller than everyone!$"

FortreeGymNew_Text_LhotseIntro:
	.string "Many have tried to clip my wings before,\n"
	.string "they have all failed.$"

FortreeGymNew_Text_LhotseDefeated:
	.string "It would seem I flew too close to the\n"
	.string "sun...$"

FortreeGymNew_Text_LhotsePostBattle:
	.string "There is no feeling better than soaring\n"
	.string "among the clouds with your Pokémon!\p"
	.string "You should try it sometime.$"

FortreeGymNew_Text_DenaliIntro:
	.string "With the power of my Pokémon, the\n"
	.string "sky's the limit!$"

FortreeGymNew_Text_DenaliDefeated:
	.string "No way! Did I reach my limit already?!$"

FortreeGymNew_Text_DenaliPostBattle:
	.string "This reminds me of the time I took to\n"
	.string "the sky during a thunderstorm.\p"
	.string "That also didn't turn out all too well.$"

FortreeGymNew_Text_RainierIntro:
	.string "Birds are just smaller dinosaurs, aren't\n"
	.string "they?$"

FortreeGymNew_Text_RainierDefeated:
	.string "You sure taught this old fossil a\n"
	.string "lesson!$"

FortreeGymNew_Text_RainierPostBattle:
	.string "Birds come from the land too, just as\n"
	.string "much as you and I do.\p"
	.string "Maybe some day humans will\n"
	.string "have wings, too?$"

FortreeGymNew_Text_FujiIntro:
	.string "Every bird loves a high perch!$"

FortreeGymNew_Text_FujiDefeated:
	.string "Don't look down on me 'cuz I lost...$"

FortreeGymNew_Text_FujiPostBattle:
	.string "Winona and Aarune are real different,\n"
	.string "but they both love adventures!$"

FortreeGymNew_Text_AreYouReady:
	.string "Welcome to the\n"
	.string "Fortree Gym, challenger.\p"
	.string "We are prepared to receive you.\p"
	.string "However, please be warned that upon\n"
	.string "entry, you will be unable to leave the\l"
	.string "Gym unless your entire\l"
	.string "Pokémon party faints.\p"
	.string "Knowing all this, do you feel that you\n"
	.string "are adequately prepared to\l"
	.string "challenge this gym?$"

FortreeGymNew_Text_ThenGoPrepare:
	.string "That's perfectly fine.\n"
	.string "Please do come back when you are ready.$"

FortreeGymNew_Text_TimeForGym:
	.string "Good luck, challenger.$"

FortreeGymNew_Text_YouAlreadyDidThis:
	.string "You appear to already possess the\n"
	.string "Horizon Badge.\p"
	.string "Apologies, but this challenge is only\n"
	.string "for those lacking said badge.$"

FortreeGymNew_Text_CantStopNow:
	.string "(No going back now.)$"

FortreeGymNew_Text_SurprisedToSeeYou:
	.string "Oh. Hello...\p"
	.string "...I didn't expect a visitor up\n"
	.string "this high in altitude.\p"
	.string "Aarune... wants me to come meet\n"
	.string "him on ground level?\l"
	.string "So we can... fight the challenger?\p"
	.string "Hmmm... it IS hard to say no to him.$"

FortreeGymNew_Text_TakeALeapOfFaith:
	.string "Alright. How about... you\n"
	.string "come with me?\l"
	.string "Let's take a leap of faith...\l"
	.string "off the mountaintop.\p"
	.string "Don't worry... this area is\n"
	.string "populated with Flying-type\l"
	.string "Pokemon... the gusts will\l"
	.string "carry you safely downwards...\p"
	.string "...Come along...$"

FortreeGymNew_Text_NameWinona:
	.string "Winona$"

FortreeGymNew_Text_NotEnoughMons:
	.string "Oh? I am very sorry, but you\n"
	.string "appear to only have one non-fainted\l"
	.string "Pokemon in your party. As this is\l"
	.string "a gym that culminates in a\l"
	.string "double battle, having more than\l"
	.string "one Pokemon is required.\p"
	.string "Please come back with more than\n"
	.string "one non-fainted Pokemon.$"
