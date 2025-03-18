.set LOCALID_MAXIE, 2
.set LOCALID_ARCHIE, 1
.set LOCALID_WALLACE, 3

OzoneOutsideCutscene_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OzoneOutsideCutscene_OnFrame
	.byte 0

OzoneOutsideCutscene_OnFrame:
	map_script_2 VAR_TEMP_4, 0, OzoneOutsideCutscene_EventScript_MeetWallace
	.2byte 0

OzoneOutsideCutscene_EventScript_MeetWallace::
	lock
	setvar VAR_TEMP_4, 1
	applymovement OBJ_EVENT_ID_PLAYER, OzoneOutsideCutscene_Movement_PlayerWalkToWallace
	applymovement LOCALID_MAXIE, OzoneOutsideCutscene_Movement_MaxieWalkToWallace
	applymovement LOCALID_ARCHIE, OzoneOutsideCutscene_Movement_ArchieWalkToWallace
	waitmovement 0
	applymovement LOCALID_WALLACE, OzoneOutsideCutscene_Movement_WallaceWalksIn
	waitmovement 0
	delay 8
	speakername OzoneOutsideCutscene_Text_NameArchie
	msgbox OzoneOutsideCutscene_Text_HeyWallace, MSGBOX_DEFAULT
	speakername OzoneOutsideCutscene_Text_NameWallace
	msgbox OzoneOutsideCutscene_Text_OriginIsUnderSiege, MSGBOX_DEFAULT
	speakername OzoneOutsideCutscene_Text_NameMaxie
	msgbox OzoneOutsideCutscene_Text_LetsGetTherePostHaste, MSGBOX_DEFAULT
	closemessage
	warp MAP_CAVE_OF_ORIGIN_CUTSCENE, 8, 7
	waitstate
	release
	end

OzoneOutsideCutscene_Movement_PlayerWalkToWallace:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

OzoneOutsideCutscene_Movement_MaxieWalkToWallace:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	step_end

OzoneOutsideCutscene_Movement_ArchieWalkToWallace:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

OzoneOutsideCutscene_Movement_WallaceWalksIn:
	walk_right
	walk_right
	step_end

OzoneOutsideCutscene_Text_NameMaxie:
	.string "Maxie$"

OzoneOutsideCutscene_Text_NameArchie:
	.string "Archie$"

OzoneOutsideCutscene_Text_NameWallace:
	.string "Wallace$"

OzoneOutsideCutscene_Text_HeyWallace:
	.string "...Wallace! We were just on\n"
	.string "our way to come talk with you.\l"
	.string "What's the word on Sootopolis?$"

OzoneOutsideCutscene_Text_OriginIsUnderSiege:
	.string "Funny how fate works its magic\n"
	.string "sometimes, for I was also seeking\l"
	.string "to rendezvous with you all.\p"
	.string "Groudon and Kyogre have awoken.\n"
	.string "And, yes... they commenced a battle\l"
	.string "within the Cave of Origin.\l"
	.string "I was, at least, able to fend them\l"
	.string "off with my Pokemon, but...\l"
	.string "there were... complications...$"

OzoneOutsideCutscene_Text_LetsGetTherePostHaste:
	.string "I suppose we will get the answers\n"
	.string "we seek with our own eyes better\l"
	.string "than hearing your words.\l"
	.string "Let us head to the Cave of Origin,\l"
	.string "post-haste.$"
