.set LOCALID_RYDEL, 1
.set LOCALID_TABITHA, 2
.set LOCALID_MERCHANT, 7
.set LOCALID_GATEKEEPER1, 3
.set LOCALID_GATEKEEPER2, 4
.set LOCALID_PIG1, 5
.set LOCALID_PIG2, 6

FallarborNew_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FallarborNew_OnLoad
	.byte 0

FallarborNew_OnLoad:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	call_if_lt VAR_OLD_GUYS_STATE, 5, FallarborNew_EventScript_SetRydelGfx
	call_if_ge VAR_OLD_GUYS_STATE, 5, FallarborNew_EventScript_RemoveRydel
	call FallarborNew_EventScript_RemoveTabitha
	call_if_gt VAR_ORBS_QUEST_STATE, 0, FallarborNew_EventScript_RemoveMerchant
	call_if_lt VAR_ORBS_QUEST_STATE, 4, FallarborNew_EventScript_RemovePigs
	call_if_ge VAR_ORBS_QUEST_STATE, 4, FallarborNew_EventScript_RemoveGatekeepers
	end

FallarborNew_EventScript_SetRydelGfx::
	setvar VAR_BARD_COLOR, MAUVILLE_MAN_HIPSTER
	special SetMauvilleOldManObjEventGfx
	return

FallarborNew_EventScript_RemoveRydel::
	removeobject LOCALID_RYDEL
	setflag FLAG_TEMP_12
	return

FallarborNew_EventScript_RemoveTabitha::
	removeobject LOCALID_TABITHA
	setflag FLAG_TEMP_11
	return

FallarborNew_EventScript_RemoveMerchant::
	removeobject LOCALID_MERCHANT
	setflag FLAG_TEMP_13
	return

FallarborNew_EventScript_RemoveGatekeepers::
	removeobject LOCALID_GATEKEEPER1
	setflag FLAG_TEMP_14
	removeobject LOCALID_GATEKEEPER2
	setflag FLAG_TEMP_15
	return

FallarborNew_EventScript_RemovePigs::
	removeobject LOCALID_PIG1
	setflag FLAG_TEMP_16
	removeobject LOCALID_PIG2
	setflag FLAG_TEMP_17
	return

FallarborNew_EventScript_TabithaEncounter1::
	lock
	goto_if_set FLAG_TEMP_1E, FallarborNew_EventScript_TabithaReleaseOut
	opendoor 29, 34
	waitdooranim
	clearflag FLAG_TEMP_11
	addobject LOCALID_TABITHA
	applymovement LOCALID_TABITHA, FallarborNew_Movement_TabOutOfDoor
	waitmovement 0
	closedoor 29, 34
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerMeetTab1
	waitmovement 0
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_JustVisitedCosmo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FallarborNew_EventScript_TabithaBattle
	setflag FLAG_TEMP_1E
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_IWillGiveYouSomeTime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerBackAway
	waitmovement 0
	release
	end

FallarborNew_Movement_TabOutOfDoor:
	walk_down
	step_end

FallarborNew_Movement_PlayerMeetTab1:
	walk_down
	walk_right
	walk_down
	walk_right
	face_up
	step_end

FallarborNew_EventScript_TabithaEncounter2::
	lock
	goto_if_set FLAG_TEMP_1E, FallarborNew_EventScript_TabithaReleaseOut
	opendoor 29, 34
	waitdooranim
	clearflag FLAG_TEMP_11
	addobject LOCALID_TABITHA
	applymovement LOCALID_TABITHA, FallarborNew_Movement_TabOutOfDoor
	waitmovement 0
	closedoor 29, 34
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerMeetTab2
	waitmovement 0
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_JustVisitedCosmo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FallarborNew_EventScript_TabithaBattle
	setflag FLAG_TEMP_1E
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_IWillGiveYouSomeTime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerBackAway
	waitmovement 0
	release
	end

FallarborNew_Movement_PlayerMeetTab2:
	walk_right
	walk_down
	walk_right
	face_up
	step_end

FallarborNew_EventScript_TabithaEncounter3::
	lock
	goto_if_set FLAG_TEMP_1E, FallarborNew_EventScript_TabithaReleaseOut
	opendoor 29, 34
	waitdooranim
	clearflag FLAG_TEMP_11
	addobject LOCALID_TABITHA
	applymovement LOCALID_TABITHA, FallarborNew_Movement_TabOutOfDoor
	waitmovement 0
	closedoor 29, 34
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerMeetTab3
	waitmovement 0
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_JustVisitedCosmo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FallarborNew_EventScript_TabithaBattle
	setflag FLAG_TEMP_1E
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_IWillGiveYouSomeTime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerBackAway
	waitmovement 0
	release
	end

FallarborNew_Movement_PlayerMeetTab3:
	walk_right
	walk_right
	face_up
	step_end

FallarborNew_Movement_PlayerBackAway:
	walk_left
	walk_left
	walk_left
	step_end

FallarborNew_EventScript_TabithaReleaseOut::
	release
	end

FallarborNew_EventScript_TabithaReEncounter::
	lock
	faceplayer
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_HowAboutNow, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FallarborNew_EventScript_TabithaReGoAway
	goto_if_eq VAR_FACING, DIR_EAST, FallarborNew_EventScript_TabithaReEastFormUp
	goto_if_eq VAR_FACING, DIR_WEST, FallarborNew_EventScript_TabithaReWestFormUp
	goto_if_eq VAR_FACING, DIR_NORTH, FallarborNew_EventScript_TabithaReNorthFormUp
	release
	end

FallarborNew_EventScript_TabithaReGoAway::
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_IWillGiveYouSomeTime, MSGBOX_AUTOCLOSE
	release
	end

FallarborNew_EventScript_TabithaReEastFormUp::
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerReEastFormUp
	waitmovement 0
	goto FallarborNew_EventScript_TabithaBattle
	release
	end

FallarborNew_Movement_PlayerReEastFormUp:
	walk_down
	walk_down
	walk_right
	face_up
	step_end

FallarborNew_EventScript_TabithaReWestFormUp::
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerReWestFormUp
	waitmovement 0
	goto FallarborNew_EventScript_TabithaBattle
	release
	end

FallarborNew_Movement_PlayerReWestFormUp:
	walk_down
	walk_down
	walk_left
	face_up
	step_end

FallarborNew_EventScript_TabithaReNorthFormUp::
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerReNorthFormUp
	waitmovement 0
	goto FallarborNew_EventScript_TabithaBattle
	release
	end

FallarborNew_Movement_PlayerReNorthFormUp:
	walk_down
	face_up
	step_end

FallarborNew_EventScript_TabithaBattle::
	setflag FLAG_CABLE_CAR_UNLOCKED
	turnobject LOCALID_TABITHA, DIR_SOUTH
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_TabithaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_TABITHA_2, FallarborNew_Text_TabithaDefeated
	goto FallarborNew_EventScript_TabithaPostBattle
	release
	end

FallarborNew_EventScript_TabithaPostBattle::
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_GoodBattle, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TABITHA, FallarborNew_Movement_TabWalkToRydel
	applymovement OBJ_EVENT_ID_PLAYER, FallarborNew_Movement_PlayerWalkToRydel
	waitmovement 0
	delay 32
	speakername NULL
	turnobject LOCALID_RYDEL, DIR_SOUTH
	msgbox FallarborNew_Text_WhatsUp, MSGBOX_DEFAULT
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_PlayerNeedsABike, MSGBOX_DEFAULT
	speakername FallarborNew_Text_NameRydel
	msgbox FallarborNew_Text_FineByMe, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	speakername FallarborNew_Text_NameRydel
	msgbox FallarborNew_Text_ThatShouldGetYouUpMt, MSGBOX_DEFAULT
	turnobject LOCALID_TABITHA, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 4
	speakername FallarborNew_Text_NameTabitha
	msgbox FallarborNew_Text_HopeThatHelpsSeeYa, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OZONE_ADMINS_STATE, 8
	applymovement LOCALID_TABITHA, FallarborNew_Movement_TabLeaves
	waitmovement 0
	removeobject LOCALID_TABITHA
	setflag FLAG_TEMP_11
	speakername FallarborNew_Text_NameRydel
	msgbox FallarborNew_Text_OhTakeThisIfYouWannaCallMe, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_BUSINESS_CARD
	closemessage
	release
	end

FallarborNew_Movement_TabWalkToRydel:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

FallarborNew_Movement_PlayerWalkToRydel:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

FallarborNew_Movement_TabLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

FallarborNew_EventScript_Rydel::
	lock
	faceplayer
	goto_if_lt VAR_OZONE_ADMINS_STATE, 8, FallarborNew_EventScript_RydelPreTab
	speakername FallarborNew_Text_NameRydel
	msgbox FallarborNew_Text_HowsTheAcroBike, MSGBOX_AUTOCLOSE
	release
	end

FallarborNew_EventScript_RydelPreTab::
	msgbox FallarborNew_Text_StrangeBikeMan, MSGBOX_AUTOCLOSE
	release
	end

FallarborNew_EventScript_Merchant::
	lock
	faceplayer
	goto_if_ge VAR_ORBS_QUEST_STATE, 1, FallarborNew_EventScript_MerchantPost
	msgbox FallarborNew_Text_LookingForSomeonePure, MSGBOX_DEFAULT
	giveitem ITEM_OLD_SEA_MAP
	msgbox FallarborNew_Text_FollowThatMapForTreasure, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ORBS_QUEST_STATE, 1
	delay 16
	playse SE_M_SWORDS_DANCE
	waitse
	playse SE_M_BUBBLE_BEAM2
	msgbox FallarborNew_Text_TheMapPointsToSootopolis, MSGBOX_DEFAULT
	closemessage
	release
	end

FallarborNew_EventScript_MerchantPost::
	msgbox FallarborNew_Text_ListenToTheMap, MSGBOX_AUTOCLOSE
	release
	end

FallarborNew_EventScript_Gatekeeper1::
	msgbox FallarborNew_Text_Gatekeeper1, MSGBOX_NPC
	end

FallarborNew_EventScript_Gatekeeper2::
	msgbox FallarborNew_Text_Gatekeeper2, MSGBOX_NPC
	end

FallarborNew_EventScript_Pig1::
	msgbox FallarborNew_Text_Pig1, MSGBOX_NPC
	end

FallarborNew_EventScript_Pig2::
	msgbox FallarborNew_Text_Pig2, MSGBOX_NPC
	end

FallarborNew_EventScript_FallarborSign::
	msgbox FallarborNew_Text_FallarborSign, MSGBOX_SIGN
	end

FallarborNew_EventScript_JaggroSign::
	msgbox FallarborNew_Text_JaggroSign, MSGBOX_SIGN
	end

FallarborNew_EventScript_CozmosHouseSign::
	msgbox FallarborNew_Text_CozmosHouseSign, MSGBOX_SIGN
	end

FallarborNew_Text_FallarborSign:
	.string "FALLARBOR TOWN\n"
	.string "A land humble and refined.$"

FallarborNew_Text_JaggroSign:
	.string "Continue West to\n"
	.string "reach Jaggro Pass$"

FallarborNew_Text_CozmosHouseSign:
	.string "Professor Cozmo's House$"

FallarborNew_Text_NameTabitha:
	.string "Tabitha$"

FallarborNew_Text_NameRydel:
	.string "Rydel$"

FallarborNew_Text_JustVisitedCosmo:
	.string "You are a bit tardy, {PLAYER}.\n"
	.string "I have gotten what I needed\l"
	.string "from the good professor.\p"
	.string "Hmmm... you know, {PLAYER},\n"
	.string "I keep thinking back to our\l"
	.string "initial battle. Without words,\l"
	.string "it told me a lot about you\l"
	.string "as a person. Especially given\l"
	.string "how you are quite the mute.\p"
	.string "I would like to connect with\n"
	.string "you again in battle, if\l"
	.string "that is alright. My old partner...\l"
	.string "if you could not tell, never\l"
	.string "stimulated my brain as I would\l"
	.string "like from a close comrade.\p"
	.string "This time, it will be just\n"
	.string "you and I. Will you show me how\l"
	.string "you have grown as a trainer?$"

FallarborNew_Text_IWillGiveYouSomeTime:
	.string "Ah, so you're unprepared.\n"
	.string "That is understandable.\l"
	.string "I will be waiting here, then.$"

FallarborNew_Text_HowAboutNow:
	.string "Are you now ready for battle?$"

FallarborNew_Text_TabithaIntro:
	.string "Then let us have at it!$"

FallarborNew_Text_TabithaDefeated:
	.string "You have accelerated beyond\n"
	.string "my expectations, {PLAYER}.$"

FallarborNew_Text_GoodBattle:
	.string "I am fully satisfied with that...\n"
	.string "thank you very much.\p"
	.string "Right. I did promise that I\n"
	.string "would provide you means of\l"
	.string "traversing the mountain easier.\l"
	.string "As luck would have it, just\l"
	.string "the right man is in town for this.\l"
	.string "Come.$"

FallarborNew_Text_WhatsUp:
	.string "Hey-YO, my dudes!\n"
	.string "What's crack-a-lackin'?$"

FallarborNew_Text_PlayerNeedsABike:
	.string "My comrade here is in dire need\n"
	.string "of an Acro Bike, Rydel.\l"
	.string "They are a valued part of\l"
	.string "Team Ozone's operations, so could\l"
	.string "I bother you to part with one?$"

FallarborNew_Text_FineByMe:
	.string "Sounds like a radical idea!\n"
	.string "Eeeeyyyyikers, I'm shocked thatcha\l"
	.string "even got here without one.$"

FallarborNew_Text_ThatShouldGetYouUpMt:
	.string "Dude, you'll love it. This beaut'll\n"
	.string "getcha over those rough slopes\l"
	.string "no problemo! It lets you pop\l"
	.string "wheelies for sick trick action, too!\l"
	.string "Yowza! You'll soon be a BMX champ!$"

FallarborNew_Text_HopeThatHelpsSeeYa:
	.string "This will be your key to deeply\n"
	.string "exploring Mt. Chimney's many\l"
	.string "nooks and crannies.\l"
	.string "Take it for a productive ride.\l"
	.string "It should be the only way you\l"
	.string "can access Lavaridge Town, and\l"
	.string "hence, your next badge.\p"
	.string "I must be going, {PLAYER}.\n"
	.string "Safe travels.$"

FallarborNew_Text_OhTakeThisIfYouWannaCallMe:
	.string "Here, dude! Cop this cizzard!\n"
	.string "We'll keep in touch.\p"
	.string "(You purposefully neglect to tell\n"
	.string "Rydel that your Pokenav\l"
	.string "cannot make calls.)$"

FallarborNew_Text_StrangeBikeMan:
	.string "(Its a strange looking man\n"
	.string "with a pack full of bicycles.)\p"
	.string "Bro, WHERE can a guy get enough\n"
	.string "speed for a nine-hundo\l"
	.string "around here...!?$"

FallarborNew_Text_HowsTheAcroBike:
	.string "Hey, dudeski! How's the bike?\n"
	.string "Sick as can be?\p"
	.string "There's a lot of GNARLY terrain\n"
	.string "on the mountain to take it for\l"
	.string "a spin on! No insurance policy\l"
	.string "for broken ankles, though! Hah!$"

FallarborNew_Text_LookingForSomeonePure:
	.string "Ahh...\p"
	.string "Hello, traveler. This humble\n"
	.string "vagabond has... been searching\l"
	.string "for one pure of soul.\p"
	.string "I sense it within you...\n"
	.string "please, take this magical map.\l"
	.string "I have been holding onto\l"
	.string "it for decades...$"

FallarborNew_Text_FollowThatMapForTreasure:
	.string "The magical map has a mind of\n"
	.string "its own... it chose you, traveler.\p"
	.string "Follow where it marks...\n"
	.string "and you shall find great treasure.$"

FallarborNew_Text_TheMapPointsToSootopolis:
	.string "(Your magical map is glowing...!)\p"
	.string "(It is pointing you to\n"
	.string "the inner chambers of\l"
	.string "a castle in Sootopolis City...)$"

FallarborNew_Text_ListenToTheMap:
	.string "You are about to embark\n"
	.string "on a journey, I can tell...\p"
	.string "That map will lead you\n"
	.string "to places wondrous...$"

FallarborNew_Text_Gatekeeper1:
	.string "We can't let you past this point.\n"
	.string "In a house in the woods, lives\l"
	.string "a dark creature. We will be\l"
	.string "keeping the townsfolk safe from it.$"

FallarborNew_Text_Gatekeeper2:
	.string "There's a monster with magic powers\n"
	.string "in those woods! Too unsafe\l"
	.string "to let you pass.$"

FallarborNew_Text_Pig1:
	.string "Oink! Hoinko! Snort!$"

FallarborNew_Text_Pig2:
	.string "Puhiiii....!\n"
	.string "Puhihoink!$"
