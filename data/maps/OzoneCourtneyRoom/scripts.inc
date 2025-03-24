OzoneCourtneyRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OzoneCourtneyRoom_OnFrame
	.byte 0

OzoneCourtneyRoom_OnFrame:
	map_script_2 VAR_TEMP_4, 0, OzoneCourtneyRoom_EventScript_FightCourtney
	.2byte 0

OzoneCourtneyRoom_EventScript_FightCourtney::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, OzoneCourtneyRoom_Movement_WalkToBattle
	waitmovement 0
	delay 8
	setvar VAR_TEMP_4, 1
	speakername OzoneCourtneyRoom_Text_NameCourtney
	msgbox OzoneCourtneyRoom_Text_CourtneyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_COURTNEY_2, OzoneCourtneyRoom_Text_CourtneyDefeated
	goto OzoneCourtneyRoom_EventScript_CourtneyBeaten
	release
	end

OzoneCourtneyRoom_Movement_WalkToBattle:
	walk_up
	walk_up
	walk_left
	walk_up
	face_right
	step_end

OzoneCourtneyRoom_EventScript_CourtneyBeaten::
	lock
	speakername OzoneCourtneyRoom_Text_NameCourtney
	msgbox OzoneCourtneyRoom_Text_CourtneyPost, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_FINAL_OZONE_BEAT_COURTNEY
	warp MAP_OZONE_ELITE_FOUR_HUB, 2, 6
	waitstate
	release
	end

OzoneCourtneyRoom_Text_NameCourtney:
	.string "Courtney$"

OzoneCourtneyRoom_Text_CourtneyIntro:
	.string "Surprised to see me?\n"
	.string "Yes, I know. Back with Team Ozone\l"
	.string "after saying I wanted to\l"
	.string "have some separation. And yes,\l"
	.string "that is still true. I don't plan\l"
	.string "on re-joining the team outside\l"
	.string "of this special occasion.\p"
	.string "But, when I heard you were here,\n"
	.string "{PLAYER}? It made me really want\l"
	.string "to go out and battle with all\l"
	.string "my might, like the old times.\p"
	.string "So now, I stand in your way.\n"
	.string "I may be rusty, but I think\l"
	.string "I've planned out my team well.\l"
	.string "Here I come!$"

OzoneCourtneyRoom_Text_CourtneyDefeated:
	.string "You're even brighter than\n"
	.string "I could hope to be!$"

OzoneCourtneyRoom_Text_CourtneyPost:
	.string "Deep within, I knew I couldn't\n"
	.string "beat you, {PLAYER}.\p"
	.string "But I had a good time regardless!\n"
	.string "I'm glad I ended up attending\l"
	.string "the challenge.\p"
	.string "Go destroy the rest of my\n"
	.string "old co-workers for me!\l"
	.string "They won't stand a chance.$"
