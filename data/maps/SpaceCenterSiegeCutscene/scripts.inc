.set LOCALID_JACOBI, 1

SpaceCenterSiegeCutscene_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SpaceCenterSiegeCutscene_OnFrame
	.byte 0

SpaceCenterSiegeCutscene_OnFrame:
	map_script_2 VAR_ORBS_QUEST_STATE, 7, SpaceCenterSiegeCutscene_EventScript_FightCREGC
	.2byte 0

SpaceCenterSiegeCutscene_EventScript_FightCREGC::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, SpaceCenterSiegeCutscene_Movement_PlayerWalkToJacobi
	waitmovement 0
	delay 8
	turnobject LOCALID_JACOBI, DIR_SOUTH
	delay 8
	msgbox SpaceCenterSiegeCutscene_Text_TryAndStopMe, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_JACOBI, SpaceCenterSiegeCutscene_Text_JacobiDefeat
	goto SpaceCenterSiegeCutscene_EventScript_PostFight
	release
	end

SpaceCenterSiegeCutscene_EventScript_PostFight::
	msgbox SpaceCenterSiegeCutscene_Text_INeedaJet, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ORBS_QUEST_STATE, 8
	applymovement LOCALID_JACOBI, SpaceCenterSiegeCutscene_Movement_JacobiRunAway
	waitmovement 0
	warp MAP_COSMOSS_SPACE_CENTER, 2, 8
	waitstate
	release
	end

SpaceCenterSiegeCutscene_Movement_PlayerWalkToJacobi:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_up
	step_end

SpaceCenterSiegeCutscene_Movement_JacobiRunAway:
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	step_end

SpaceCenterSiegeCutscene_Text_TryAndStopMe:
	.string "Ah-hah. THIS is who Kepler\n"
	.string "sent in to wrangle me? What a joke.\l"
	.string "But not a particularly funny one.\p"
	.string "So, I'm guessing he's given\n"
	.string "you his little spiel?\l"
	.string "And what are you gonna do about it?\l"
	.string "Arrest me?\p"
	.string "I'm backed by 7 tonnes of steel\n"
	.string "and potent engineering.\l"
	.string "There's no way you'll\l"
	.string "stand a chance against my firepower.\p"
	.string "BOMBS AWAY!$"

SpaceCenterSiegeCutscene_Text_JacobiDefeat:
	.string "Even C.R.E.G.C fell!?\n"
	.string "I can't believe this!$"

SpaceCenterSiegeCutscene_Text_INeedaJet:
	.string "(Jacobi opens his labcoat,\n"
	.string "revealing a bomb strapped\l"
	.string "to his chest.)\p"
	.string "That's right... that is RIGHT...!\n"
	.string "Don't you even think of trying\l"
	.string "ANYTHING else! One false\l"
	.string "move, and me and you are\l"
	.string "gonna meet our makers...!\p"
	.string "I'll rebuild C.R.E.G.C.\n"
	.string "And when that happens,\l"
	.string "Cosmoss- no, all of HOENN\l"
	.string "will be under my thumb!$"
