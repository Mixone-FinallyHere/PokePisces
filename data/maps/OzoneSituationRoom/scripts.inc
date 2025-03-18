.set LOCALID_MAXIE, 2
.set LOCALID_ARCHIE, 1
.set LOCALID_RAY, 3
.set LOCALID_COURTNEY, 4
.set LOCALID_TABITHA, 5
.set LOCALID_MATT, 6

OzoneSituationRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OzoneSituationRoom_OnFrame
	.byte 0

OzoneSituationRoom_OnFrame:
	map_script_2 VAR_TEMP_4, 0, OzoneSituationRoom_EventScript_Situation
	.2byte 0

OzoneSituationRoom_EventScript_Situation::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	speakername OzoneSituationRoom_Text_NameMaxie
	msgbox OzoneSituationRoom_Text_GroudonAndKyogreAreFighting, MSGBOX_DEFAULT
	speakername OzoneSituationRoom_Text_NameTabitha
	msgbox OzoneSituationRoom_Text_WhatCourseOfAction, MSGBOX_DEFAULT
	speakername OzoneSituationRoom_Text_NameMaxie
	msgbox OzoneSituationRoom_Text_ToTheCaveOfOrigin, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEW_COO_STATE, 6
	setvar VAR_TEMP_4, 1
	release
	end

OzoneSituationRoom_EventScript_MaxieIdle::
	lock
	faceplayer
	speakername OzoneSituationRoom_Text_NameMaxie
	msgbox OzoneSituationRoom_Text_GetReady, MSGBOX_AUTOCLOSE
	release
	end

OzoneSituationRoom_EventScript_ArchieIdle::
	lock
	speakername OzoneSituationRoom_Text_NameArchie
	msgbox OzoneSituationRoom_Text_NeverThoughtThisWouldHappen, MSGBOX_AUTOCLOSE
	release
	end

OzoneSituationRoom_EventScript_RayIdle::
	lock
	faceplayer
	speakername OzoneSituationRoom_Text_NameRay
	msgbox OzoneSituationRoom_Text_YouAlwaysCauseTrouble, MSGBOX_AUTOCLOSE
	release
	end

OzoneSituationRoom_EventScript_CourtneyIdle::
	lock
	faceplayer
	speakername OzoneSituationRoom_Text_NameCourtney
	msgbox OzoneSituationRoom_Text_TheCrops, MSGBOX_AUTOCLOSE
	release
	end

OzoneSituationRoom_EventScript_TabithaIdle::
	lock
	faceplayer
	speakername OzoneSituationRoom_Text_NameTabitha
	msgbox OzoneSituationRoom_Text_MakingAPlan, MSGBOX_AUTOCLOSE
	release
	end

OzoneSituationRoom_EventScript_MattIdle::
	lock
	faceplayer
	speakername OzoneSituationRoom_Text_NameMatt
	msgbox OzoneSituationRoom_Text_ThisRilesMeUp, MSGBOX_AUTOCLOSE
	release
	end

OzoneSituationRoom_Text_NameMaxie:
	.string "Maxie$"

OzoneSituationRoom_Text_NameArchie:
	.string "Archie$"

OzoneSituationRoom_Text_NameRay:
	.string "Ray$"

OzoneSituationRoom_Text_NameCourtney:
	.string "Courtney$"

OzoneSituationRoom_Text_NameTabitha:
	.string "Tabitha$"

OzoneSituationRoom_Text_NameMatt:
	.string "Matt$"

OzoneSituationRoom_Text_GroudonAndKyogreAreFighting:
	.string "It is just as we had feared,\n"
	.string "unfortunately...\l"
	.string "Our weather analysis has concluded\l"
	.string "that Groudon and Kyogre must\l"
	.string "have returned from their slumber,\l"
	.string "and are fighting somewhere\l"
	.string "as we speak...$"

OzoneSituationRoom_Text_WhatCourseOfAction:
	.string "What is our course of action?\n"
	.string "Surely, we possess the resources\l"
	.string "to quash those two?$"

OzoneSituationRoom_Text_ToTheCaveOfOrigin:
	.string "...We must first head to the\n"
	.string "Cave of Origin, and converse\l"
	.string "with Deacon Wallace.\l"
	.string "He possesses countless knowledge\l"
	.string "about the Legendary Pokemon\l"
	.string "of Hoenn. In addition, the last\l"
	.string "time Groudon and Kyogre battled,\l"
	.string "it was in front of the\l"
	.string "Cave of Origin. There is a high\l"
	.string "likelihood they are there once more.\p"
	.string "{PLAYER}, you will be coming\n"
	.string "with us. We will need a masterful\l"
	.string "trainer like you on our side.$"

OzoneSituationRoom_Text_GetReady:
	.string "Prepare however you see fit.\n"
	.string "Once you are ready, we will\l"
	.string "follow you out of the building.$"

OzoneSituationRoom_Text_NeverThoughtThisWouldHappen:
	.string "Never, in a million years,\n"
	.string "was I prepared for this to happen\l"
	.string "again so soon...$"

OzoneSituationRoom_Text_YouAlwaysCauseTrouble:
	.string "You always seem to cause trouble.\n"
	.string "This potentially world-altering\l"
	.string "event was not on my schedule.$"

OzoneSituationRoom_Text_TheCrops:
	.string "I need to be off to the farm\n"
	.string "to check on the crops with this\l"
	.string "crazy weather... but, Maxie is\l"
	.string "not allowing me to leave...\p"
	.string "Oh, I hope they will be alright...$"

OzoneSituationRoom_Text_MakingAPlan:
	.string "I am drafting up a plan for\n"
	.string "us Admins to do what we are able\l"
	.string "to assist people who may be affected\l"
	.string "by the sudden abnormal weather.\l"
	.string "If it means Matt and I must\l"
	.string "band together again... so be it.$"

OzoneSituationRoom_Text_ThisRilesMeUp:
	.string "This really riles me up, man!\n"
	.string "Just who do these Pokemon think\l"
	.string "they are that they can just\l"
	.string "cause an apocalypse on a whim!?$"
