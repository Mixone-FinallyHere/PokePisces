OzoneTabithaRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OzoneTabithaRoom_OnFrame
	.byte 0

OzoneTabithaRoom_OnFrame:
	map_script_2 VAR_TEMP_4, 0, OzoneTabithaRoom_EventScript_FightTabitha
	.2byte 0

OzoneTabithaRoom_EventScript_FightTabitha::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, OzoneTabithaRoom_Movement_WalkToBattle
	waitmovement 0
	delay 8
	setvar VAR_TEMP_4, 1
	speakername OzoneTabithaRoom_Text_NameTabitha
	msgbox OzoneTabithaRoom_Text_TabithaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_TABITHA_3, OzoneTabithaRoom_Text_TabithaDefeated
	goto OzoneTabithaRoom_EventScript_TabithaBeaten
	release
	end

OzoneTabithaRoom_Movement_WalkToBattle:
	walk_up
	walk_up
	walk_left
	walk_up
	face_right
	step_end

OzoneTabithaRoom_EventScript_TabithaBeaten::
	lock
	speakername OzoneTabithaRoom_Text_NameTabitha
	msgbox OzoneTabithaRoom_Text_TabithaPost, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_FINAL_OZONE_BEAT_TABITHA
	warp MAP_OZONE_ELITE_FOUR_HUB, 19, 6
	waitstate
	release
	end

OzoneTabithaRoom_Text_NameTabitha:
	.string "Tabitha$"

OzoneTabithaRoom_Text_TabithaIntro:
	.string "As soon as Maxie briefed me\n"
	.string "on what we would be doing today,\l"
	.string "I knew the trainer we would be\l"
	.string "battling would be you, {PLAYER}.\p"
	.string "I am inclined to believe you may\n"
	.string "well be the best Pokemon Trainer\l"
	.string "Hoenn has seen in some time.\l"
	.string "It is an honor to have sparred\l"
	.string "with you in the past, and it will\l"
	.string "again be an honor today.\p"
	.string "Hold nothing back, {PLAYER}.\n"
	.string "I certainly will not...!$"

OzoneTabithaRoom_Text_TabithaDefeated:
	.string "You continually impress me...$"

OzoneTabithaRoom_Text_TabithaPost:
	.string "Even through hail and sleet,\n"
	.string "you and your team never\l"
	.string "extinguished your inner fire...\p"
	.string "You should be proud of where\n"
	.string "you are at, skill-wise.\l"
	.string "I have no doubt the others will\l"
	.string "fold like paper to your team.\p"
	.string "Go forth with your head held high!$"
