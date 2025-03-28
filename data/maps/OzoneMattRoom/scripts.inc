OzoneMattRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OzoneMattRoom_OnFrame
	.byte 0

OzoneMattRoom_OnFrame:
	map_script_2 VAR_TEMP_4, 0, OzoneMattRoom_EventScript_FightMatt
	.2byte 0

OzoneMattRoom_EventScript_FightMatt::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, OzoneMattRoom_Movement_WalkToBattle
	waitmovement 0
	delay 8
	setvar VAR_TEMP_4, 1
	speakername OzoneMattRoom_Text_NameMatt
	msgbox OzoneMattRoom_Text_MattIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_MATT_3, OzoneMattRoom_Text_MattDefeated
	goto OzoneMattRoom_EventScript_MattBeaten
	release
	end

OzoneMattRoom_Movement_WalkToBattle:
	walk_up
	walk_up
	walk_left
	walk_up
	face_right
	step_end

OzoneMattRoom_EventScript_MattBeaten::
	lock
	speakername OzoneMattRoom_Text_NameMatt
	msgbox OzoneMattRoom_Text_MattPost, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_FINAL_OZONE_BEAT_MATT
	warp MAP_OZONE_ELITE_FOUR_HUB, 7, 6
	waitstate
	release
	end

OzoneMattRoom_Text_NameMatt:
	.string "Matt$"

OzoneMattRoom_Text_MattIntro:
	.string "Oh, hey! I didn't realize\n"
	.string "YOU would be that trainer Archie\l"
	.string "told me to get ready for!\p"
	.string "You've sure come a long way,\n"
	.string "not-so-small-fry! And here, I\l"
	.string "thought you'd be fodder!\p"
	.string "I'm more than happy to give\n"
	.string "you a challenge. Ain't no way\l"
	.string "you're getting by me with\l"
	.string "your whole team intact!$"

OzoneMattRoom_Text_MattDefeated:
	.string "Blast! I thought I had you!$"

OzoneMattRoom_Text_MattPost:
	.string "That was a damn good showing!\n"
	.string "You weathered my sandstorm like\l"
	.string "you were born in the desert!\p"
	.string "Ah, I can't keep ya forever.\n"
	.string "Go show the others what's what!\l"
	.string "I'll be cheerin' you on!$"
