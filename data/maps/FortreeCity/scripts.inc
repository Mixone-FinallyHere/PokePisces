.set LOCALID_YANDEMIC, 1
.set LOCALID_ROADBLOCK1, 2
.set LOCALID_ROADBLOCK2, 3
.set LOCALID_ROADBLOCK3, 4
.set LOCALID_ROADBLOCK4, 5

FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_FORTREE_CITY
	call_if_ge VAR_NOTICED_BY_YANDEMIC, 5, FortreeCity_EventScript_RemoveYandemic
	call_if_ge VAR_PISCES_STORY_PROGRESS, 5, FortreeCity_EventScript_RemoveRoadblock
	end

FortreeCity_EventScript_RemoveYandemic::
	removeobject LOCALID_YANDEMIC
	setflag FLAG_TEMP_11
	return

FortreeCity_EventScript_RemoveRoadblock::
	removeobject LOCALID_ROADBLOCK1
	removeobject LOCALID_ROADBLOCK2
	removeobject LOCALID_ROADBLOCK3
	removeobject LOCALID_ROADBLOCK4
	setflag FLAG_TEMP_12
	return

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Ozoner1::
    msgbox FortreeCity_Text_Ozoner1, MSGBOX_NPC
    end

FortreeCity_EventScript_Ozoner2::
    msgbox FortreeCity_Text_Ozoner2, MSGBOX_NPC
    end

FortreeCity_EventScript_FortreeSign::
	msgbox FortreeCity_Text_FortreeSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_TerrainHouseSign::
	msgbox FortreeCity_Text_TerrainHouseSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_WestToGymSign::
	msgbox FortreeCity_Text_WestToGymSign, MSGBOX_SIGN
	end

FortreeCity_Text_FortreeSign:
	.string "FORTREE CITY\n"
	.string "Atop the trees, bathed with nature.$"

FortreeCity_Text_TerrainHouseSign:
	.string "All visitors welcome\n"
	.string "to the Fortree City Terrain House!\p"
	.string "Want moves to help your\n"
	.string "Pokemon in various terrains?\l"
	.string "We are happy to help!$"

FortreeCity_Text_WestToGymSign:
	.string "Head West to reach the\n"
	.string "Fortree City Gym!$"

FortreeCity_Text_Ozoner1:
	.string "Yo. Do you mind?\n"
	.string "Team Ozone's doing a bit\l"
	.string "of area surveying here.\p"
	.string "Surveying of what? ...\p"
	.string "...Just don't pass us!$"

FortreeCity_Text_Ozoner2:
	.string "We're letting our Pokemon roam\n"
	.string "around here to monitor their\l"
	.string "reactions to the rain.\p"
	.string "Fire Pokemon really dislike\n"
	.string "the rain. Thats why those\l"
	.string "Parasol Ladies love to train them.\l"
	.string "Their umbrellas keep them dry.$"
