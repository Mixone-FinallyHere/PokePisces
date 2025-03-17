OzoneShellyRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OzoneShellyRoom_OnFrame
	.byte 0

OzoneShellyRoom_OnFrame:
	map_script_2 VAR_TEMP_4, 0, OzoneShellyRoom_EventScript_FightShelly
	.2byte 0

OzoneShellyRoom_EventScript_FightShelly::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, OzoneShellyRoom_Movement_WalkToBattle
	waitmovement 0
	delay 8
	setvar VAR_TEMP_4, 1
	speakername OzoneShellyRoom_Text_NameShelly
	msgbox OzoneShellyRoom_Text_ShellyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_SHELLY_2, OzoneShellyRoom_Text_ShellyDefeated
	goto OzoneShellyRoom_EventScript_ShellyBeaten
	release
	end

OzoneShellyRoom_Movement_WalkToBattle:
	walk_up
	walk_up
	walk_left
	walk_up
	face_right
	step_end

OzoneShellyRoom_EventScript_ShellyBeaten::
	lock
	speakername OzoneShellyRoom_Text_NameShelly
	msgbox OzoneShellyRoom_Text_ShellyPost, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_FINAL_OZONE_BEAT_SHELLY
	warp MAP_OZONE_ELITE_FOUR_HUB, 24, 6
	waitstate
	release
	end

OzoneShellyRoom_Text_NameShelly:
	.string "Shelly$"

OzoneShellyRoom_Text_ShellyIntro:
	.string "Z z  z ......\p"
	.string "...Oh, it's you again...\p"
	.string "I don't even know why I'm\n"
	.string "one of the four here,\l"
	.string "to be... yawn... honest...\p"
	.string "But, Maxie and Archie, uhm,\n"
	.string "called up all the former\l"
	.string "Aqua and... yawn... Magma Admins\l"
	.string "for this event, and I felt\l"
	.string "awkward being the only one\l"
	.string "to say no...\p"
	.string "...So here I am.\n"
	.string "Might as well try hard to beat you.\l"
	.string "Well... hard, for my standards...$"

OzoneShellyRoom_Text_ShellyDefeated:
	.string "What a nightmare...$"

OzoneShellyRoom_Text_ShellyPost:
	.string "Trusties... I was trying to\n"
	.string "be aggressive in that fight...\p"
	.string "...Would I lie Ä?\p"
	.string "I think you should...\n"
	.string "get going, y'know...?$"
