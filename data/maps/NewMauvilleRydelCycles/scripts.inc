.set LOCALID_RYDEL, 1
.set LOCALID_APPRENTICE, 2
.set LOCALID_P_MAN, 3

NewMauvilleRydelCycles_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, NewMauvilleRydelCycles_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewMauvilleRydelCycles_OnFrame
	.byte 0

NewMauvilleRydelCycles_OnLoad:
	call NewMauvilleRydelCycles_EventScript_RemoveKizuna
	call_if_eq VAR_OLD_GUYS_STATE, 5, NewMauvilleRydelCycles_EventScript_SetMauvilleOldManGfx
	call_if_eq VAR_OLD_GUYS_STATE, 6, NewMauvilleRydelCycles_EventScript_SetMauvilleOldManGfx
	call_if_lt VAR_OLD_GUYS_STATE, 5, NewMauvilleRydelCycles_EventScript_RemoveRydel
	call_if_gt VAR_OLD_GUYS_STATE, 6, NewMauvilleRydelCycles_EventScript_RemoveRydel
	end

NewMauvilleRydelCycles_OnFrame:
	map_script_2 VAR_OLD_GUYS_STATE, 6, NewMauvilleRydelCycles_EventScript_GoToChallenge
	.2byte 0

NewMauvilleRydelCycles_EventScript_SetMauvilleOldManGfx::
	setvar VAR_BARD_COLOR, MAUVILLE_MAN_HIPSTER
	special SetMauvilleOldManObjEventGfx
	return

NewMauvilleRydelCycles_EventScript_RemoveKizuna::
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	return

NewMauvilleRydelCycles_EventScript_RemoveRydel::
	removeobject LOCALID_RYDEL
	setflag FLAG_TEMP_12
	return

NewMauvilleRydelCycles_EventScript_Rydel::
	lock
	goto_if_eq VAR_OLD_GUYS_STATE, 6, NewMauvilleRydelCycles_EventScript_RydelPostChallenge
	speakername NewMauvilleRydelCycles_Text_NameRydel
	msgbox NewMauvilleRydelCycles_Text_IAmTheHipster, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OLD_GUYS_STATE, 6
	playse SE_DOOR
	clearflag FLAG_TEMP_11
	addobject LOCALID_P_MAN
	applymovement LOCALID_P_MAN, NewMauvilleRydelCycles_Movement_KizunaEnterRoom
	speakername NewMauvilleRydelCycles_Text_NameKizuna
	msgbox NewMauvilleRydelCycles_Text_YouTheNextGuy, MSGBOX_DEFAULT
	speakername NewMauvilleRydelCycles_Text_NameRydel
	msgbox NewMauvilleRydelCycles_Text_TakeMyChallenge, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	applymovement LOCALID_P_MAN, NewMauvilleRydelCycles_Movement_KizunaFaceRight
	speakername NewMauvilleRydelCycles_Text_NameKizuna
	msgbox NewMauvilleRydelCycles_Text_AsLongAsYoureUpForIt, MSGBOX_DEFAULT
	speakername NewMauvilleRydelCycles_Text_NameRydel
	msgbox NewMauvilleRydelCycles_Text_BrilliantLetsBegin, MSGBOX_DEFAULT
	closemessage
	warp MAP_ROUTE110_SEASIDE_CYCLING_ROAD_NORTH_ENTRANCE, 4, 4
	waitstate
	release
	end

NewMauvilleRydelCycles_Movement_KizunaEnterRoom:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewMauvilleRydelCycles_Movement_KizunaFaceRight:
	face_right
	step_end

NewMauvilleRydelCycles_EventScript_RydelPostChallenge::
	msgbox NewMauvilleRydelCycles_Text_RydelPostChallenge, MSGBOX_AUTOCLOSE
	release
	end

NewMauvilleRydelCycles_EventScript_GoToChallenge::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewMauvilleRydelCycles_Movement_PlayerGoToCounter
	waitmovement 0
	speakername NewMauvilleRydelCycles_Text_NameRydel
	msgbox NewMauvilleRydelCycles_Text_RydelPostChallenge, MSGBOX_DEFAULT
	closemessage
	delay 8
	warp MAP_ROUTE110_SEASIDE_CYCLING_ROAD_NORTH_ENTRANCE, 4, 4
	waitstate
	release
	end

NewMauvilleRydelCycles_Movement_PlayerGoToCounter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewMauvilleRydelCycles_EventScript_RydelLackey::
	lock
	faceplayer
	goto_if_lt VAR_OLD_GUYS_STATE, 6, NewMauvilleRydelCycles_EventScript_RydelLackeyPreRetire
	msgbox NewMauvilleRydelCycles_Text_RydelLackeyPost, MSGBOX_AUTOCLOSE
	release
	end

NewMauvilleRydelCycles_EventScript_RydelLackeyPreRetire::
	msgbox NewMauvilleRydelCycles_Text_RydelLackeyPreRetire, MSGBOX_AUTOCLOSE
	release
	end

NewMauvilleRydelCycles_Text_NameRydel:
	.string "Rydel$"

NewMauvilleRydelCycles_Text_NameKizuna:
	.string "Kizuna$"

NewMauvilleRydelCycles_Text_IAmTheHipster:
	.string "Righteous! You that cool cat\n"
	.string "I gave a bike to in Fallarbor?\l"
	.string "Hope you've been shreddin'\l"
	.string "it up out there, fo sho!$"

NewMauvilleRydelCycles_Text_YouTheNextGuy:
	.string "Mr. Rydel, we're sorry to\n"
	.string "bother you, but we are looking to\l"
	.string "get in touch with The Storyteller.\l"
	.string "I assume you know who I'm\l"
	.string "talking about, right?\l"
	.string "Seems like you were a mutual\l"
	.string "friend to him and the Trick Master.$"

NewMauvilleRydelCycles_Text_TakeMyChallenge:
	.string "Well, I'll tell ya it ain't\n"
	.string "bogus, bro. I was tight with\l"
	.string "both of 'em. Bunch of us old heads\l"
	.string "had a clique, feel me? And\l"
	.string "we all had dope titles!\l"
	.string "I was The Hipster!\p"
	.string "We were always stoked n' revved\n"
	.string "up for puzzles and games\l"
	.string "and all that hizzup! So yeah,\l"
	.string "ya boy is feelin' up for\l"
	.string "a good challenge!\p"
	.string "You want the deets on the\n"
	.string "Storyteller, dig? Then you\l"
	.string "gotta demolish the...\p"
	.string "MACH   BIKE   CHALLENGE\p"
	.string "You take this Mach Bike, yeah?\n"
	.string "Fastest bike we sell! And you\l"
	.string "straight book it across the\l"
	.string "road fast as ya can.\l"
	.string "I'll be timin' ya. Gotta get\l"
	.string "a good time to impress me!\l"
	.string "I've seen it all!\p"
	.string "You impress me? I spill the\n"
	.string "beans on what I know.\p"
	.string "So? Ya down, clown?$"

NewMauvilleRydelCycles_Text_AsLongAsYoureUpForIt:
	.string "Jeez, the things we have to do\n"
	.string "to get information nowadays...\p"
	.string "Sorry, {PLAYER}. It shouldn't\n"
	.string "be TOO hard, right? I bet\l"
	.string "you can clear any record he\l"
	.string "might've set.$"

NewMauvilleRydelCycles_Text_BrilliantLetsBegin:
	.string "Totally EPIC, bro!\n"
	.string "Let's getcha set up!$"

NewMauvilleRydelCycles_Text_RydelPostChallenge:
	.string "Uhhh.... what the sigma?\n"
	.string "You LEFT mid-challenge, bro!\l"
	.string "That ain't gonna fly!\l"
	.string "Get back in there and do\l"
	.string "it fo realsies this time!$"

NewMauvilleRydelCycles_Text_RydelLackeyPreRetire:
	.string "Hey, dude. Welcome to Rydel's Cycles\n"
	.string "and all that...\p"
	.string "The boss is out on some kinda\n"
	.string "journey or whatever. So, we only\l"
	.string "offer mechanical fixes to bikes,\l"
	.string "no new ones till he gets back.$"

NewMauvilleRydelCycles_Text_RydelLackeyPost:
	.string "Oh, what's up, dude.\n"
	.string "Yeah, uh, Rydel kinda fell off\l"
	.string "the radar. No one's been able\l"
	.string "to get a hold of him. Bummer.\p"
	.string "Guess I have to inherit the shop.\n"
	.string "Well, that ain't all bad.\l"
	.string "Maybe it'll make me look like\l"
	.string "I have status for once.$"
