.set LOCALID_RYDEL, 2
.set LOCALID_P_MAN, 3

Route110_SeasideCyclingRoadSouthEntrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_SeasideCyclingRoadSouthEntrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route110_SeasideCyclingRoadSouthEntrance_OnLoad
	.byte 0

Route110_SeasideCyclingRoadSouthEntrance_OnLoad:
	call_if_eq VAR_OLD_GUYS_STATE, 6, Route110_SeasideCyclingRoadSouthEntrance_EventScript_SetMauvilleOldManGfx
	call_if_lt VAR_OLD_GUYS_STATE, 6, Route110_SeasideCyclingRoadSouthEntrance_EventScript_RemoveRydelAndKizuna
	call_if_gt VAR_OLD_GUYS_STATE, 6, Route110_SeasideCyclingRoadSouthEntrance_EventScript_RemoveRydelAndKizuna
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_SetMauvilleOldManGfx::
	setvar VAR_BARD_COLOR, MAUVILLE_MAN_HIPSTER
	special SetMauvilleOldManObjEventGfx
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_RemoveRydelAndKizuna::
	removeobject LOCALID_RYDEL
	setflag FLAG_TEMP_12
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	return

Route110_SeasideCyclingRoadSouthEntrance_OnTransition:
	call_if_eq VAR_CYCLING_CHALLENGE_STATE, 3, Route110_SeasideCyclingRoadSouthEntrance_EventScript_RestartChallenge
	call_if_eq VAR_CYCLING_CHALLENGE_STATE, 2, Route110_SeasideCyclingRoadSouthEntrance_EventScript_RestartChallenge
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_RestartChallenge::
	setvar VAR_CYCLING_CHALLENGE_STATE, 1
	return

Route110_SeasideCyclingRoadSouthEntrance_EventScript_Clerk::
	lock
	faceplayer
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_GoAllOutOnCyclingRoad, MSGBOX_DEFAULT
	release
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_BikeCheck::
	lockall
	specialvar VAR_RESULT, GetPlayerAvatarBike
	goto_if_eq VAR_RESULT, 0, Route110_SeasideCyclingRoadSouthEntrance_EventScript_NoBike
	goto_if_eq VAR_RESULT, 1, Route110_SeasideCyclingRoadSouthEntrance_EventScript_NoMachBike
	setflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 1
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_NoBike::
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_TooDangerousToWalk, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route110_SeasideCyclingRoadSouthEntrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_NoMachBike::
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_NoMachBike, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route110_SeasideCyclingRoadSouthEntrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_ClearCyclingRoad::
	lockall
	setvar VAR_CYCLING_CHALLENGE_STATE, 0
	clearflag FLAG_SYS_CYCLING_ROAD
	setvar VAR_TEMP_1, 0
	releaseall
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_KizunaCongrats::
	speakername Route110_SeasideCyclingRoadSouthEntrance_Text_NameKizuna
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_KizunaCongrats, MSGBOX_NPC
	end

Route110_SeasideCyclingRoadSouthEntrance_EventScript_RydelRetires::
	lock
	speakername Route110_SeasideCyclingRoadSouthEntrance_Text_NameRydel
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_YouDidIt, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Route110_SeasideCyclingRoadSouthEntrance_Movement_FaceRight
	fadenewbgm MUS_VERDANTURF
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_TimeToRetire, MSGBOX_DEFAULT
	applymovement LOCALID_RYDEL, Route110_SeasideCyclingRoadSouthEntrance_Movement_FaceUp
	applymovement LOCALID_P_MAN, Route110_SeasideCyclingRoadSouthEntrance_Movement_FaceDown
	speakername Route110_SeasideCyclingRoadSouthEntrance_Text_NameKizuna
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_ImReadyAreYou, MSGBOX_DEFAULT
	closemessage
	playse SE_M_MEGA_KICK
	applymovement LOCALID_P_MAN, Route110_SeasideCyclingRoadSouthEntrance_Movement_AbsorbRydel
	waitmovement 0
	removeobject LOCALID_RYDEL
	setflag FLAG_TEMP_12
	setvar VAR_OLD_GUYS_STATE, 7
	playse SE_M_FAINT_ATTACK
	waitse
	fadenewbgm MUS_NONE
	speakername Route110_SeasideCyclingRoadSouthEntrance_Text_NameKizuna
	msgbox Route110_SeasideCyclingRoadSouthEntrance_Text_ThisIsHard, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_P_MAN, Route110_SeasideCyclingRoadSouthEntrance_Movement_KizunaLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	release
	end

Route110_SeasideCyclingRoadSouthEntrance_Movement_FaceRight:
	face_right
	step_end

Route110_SeasideCyclingRoadSouthEntrance_Movement_FaceUp:
	face_up
	step_end

Route110_SeasideCyclingRoadSouthEntrance_Movement_FaceDown:
	face_down
	step_end

Route110_SeasideCyclingRoadSouthEntrance_Movement_AbsorbRydel:
	walk_slow_down
	step_end

Route110_SeasideCyclingRoadSouthEntrance_Movement_KizunaLeave:
	walk_slow_up
	walk_slow_left
	walk_slow_left
	walk_slow_up
	step_end

Route110_SeasideCyclingRoadSouthEntrance_Text_NameRydel:
	.string "Rydel$"

Route110_SeasideCyclingRoadSouthEntrance_Text_NameKizuna:
	.string "Kizuna$"

Route110_SeasideCyclingRoadSouthEntrance_Text_KizunaCongrats:
	.string "Wow, good job on your cycling!\n"
	.string "E-Even though you ended up\l"
	.string "stopping a few times, I think\l"
	.string "the time is enough. Let's hope.$"

Route110_SeasideCyclingRoadSouthEntrance_Text_YouDidIt:
	.string "...\p"
	.string "That... was...\p"
	.string "TUBULAR! WAY COOL! MONDO!\n"
	.string "You were gnarly as hell out there!\l"
	.string "Who even cares about the time limit?\l"
	.string "I'd say you rocked my socks!\p"
	.string "Aight, here's the skinny. You got\n"
	.string "a lot right, probs. I'm one of\l"
	.string "the Old Guys, a group'a dudes who've\l"
	.string "kinda run Mauville from the\l"
	.string "shadows for decades. There's\l"
	.string "actually 5 of us. You met\l"
	.string "my homie Giddy, and 'course you're\l"
	.string "on the prowl for The Storyteller.\p"
	.string "Though, my b, but I don't got any\n"
	.string "deets on where ol' ST got off to.\l"
	.string "I do know that both of the other\l"
	.string "remainin' Old Guys are chillin'\l"
	.string "in Sea Mauville just south of here\l"
	.string "these days.\p"
	.string "Y'know what? Check with Dock.\n"
	.string "He's got a crapload of connections.\l"
	.string "Prolly your best bet, dig?$"

Route110_SeasideCyclingRoadSouthEntrance_Text_TimeToRetire:
	.string "...Whelp. That's 'bout it\n"
	.string "for The Hipster, bros.\l"
	.string "I'm ready to retire and get\l"
	.string "to chillin' like a villain.\p"
	.string "I didn't tell ya this before,\n"
	.string "dude in red. But I could tell\l"
	.string "Giddy was inside ya somehow.\l"
	.string "Pretty nutso.\p"
	.string "Maybe I can join him?$"

Route110_SeasideCyclingRoadSouthEntrance_Text_ImReadyAreYou:
	.string "Sigh...\n"
	.string "Look, I don't know what's going\l"
	.string "on with you Old Guys.\p"
	.string "But yknow what, I could tell\n"
	.string "that... whatever, happened with\l"
	.string "Giddy in the Trick House put\l"
	.string "his soul at ease. My body...\l"
	.string "it's almost drawn to do what\l"
	.string "it's about to. Maybe it's destiny.\p"
	.string "Alright, Rydel. Time to retire.$"

Route110_SeasideCyclingRoadSouthEntrance_Text_ThisIsHard:
	.string "...And...there...he went.\p"
	.string "Like Giddy before him, I can feel\n"
	.string "Rydel's memories course through\l"
	.string "my brain. It's like... I'm\l"
	.string "three people in one.\p"
	.string "Truth be told, I have chosen to\n"
	.string "stop questioning what's happening.\l"
	.string "Mostly... because my heart is telling\l"
	.string "me that it's the right thing.\l"
	.string "I could be wrong. But we have\l"
	.string "to press on regardless.\p"
	.string "Dock, huh? He's Captain Stern's\n"
	.string "right hand man. The guy should be\l"
	.string "in the shipyard building in\l"
	.string "Slateport. Err, well, Sea Mauville.\l"
	.string "Keep forgetting they re-branded.\p"
	.string "Let's get going, {PLAYER}.$"

Route110_SeasideCyclingRoadSouthEntrance_Text_GoAllOutOnCyclingRoad:
	.string "On Cycling Road, you can go all out\n"
	.string "and cycle as fast as you'd like.\p"
	.string "It feels great to go that fast, but try\n"
	.string "not to crash into anyone!$"

Route110_SeasideCyclingRoadSouthEntrance_Text_TooDangerousToWalk:
	.string "Sorry, you can't walk on Cycling\n"
	.string "Road. It's too dangerous.\p"
	.string "Please come back with a Bike.$"

Route110_SeasideCyclingRoadSouthEntrance_Text_NoMachBike:
	.string "Your Acro Bike is not quite fast\n"
	.string "enough to be allowed on Cycling Road.\p"
	.string "Please come back with a Mach Bike.$"
