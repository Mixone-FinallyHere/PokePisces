.set LOCALID_P_MAN, 8
.set LOCALID_BARD, 4
.set LOCALID_BRINEY, 7
.set LOCALID_BRINEY2, 2
.set LOCALID_DRAKE, 5
.set LOCALID_ARCHIE, 3
.set LOCALID_STERN, 6

SouthernIsland_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SouthernIsland_OnLoad
	.byte 0

SouthernIsland_OnLoad:
	call_if_eq VAR_OLD_GUYS_STATE, 10, SouthernIsland_EventScript_RemoveBriney2
	call_if_eq VAR_OLD_GUYS_STATE, 10, SouthernIsland_EventScript_SetBardGfx
	call_if_lt VAR_OLD_GUYS_STATE, 10, SouthernIsland_EventScript_RemoveSeafarers
	call_if_gt VAR_OLD_GUYS_STATE, 10, SouthernIsland_EventScript_RemoveSeafarers
	end

SouthernIsland_EventScript_SetBardGfx::
	setvar VAR_BARD_COLOR, MAUVILLE_MAN_BARD
	special SetMauvilleOldManObjEventGfx
	end

SouthernIsland_EventScript_RemoveSeafarers::
	removeobject LOCALID_ARCHIE
	setflag FLAG_TEMP_14
	removeobject LOCALID_STERN
	setflag FLAG_TEMP_15
	removeobject LOCALID_DRAKE
	setflag FLAG_TEMP_16
	removeobject LOCALID_BARD
	setflag FLAG_TEMP_17
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	removeobject LOCALID_BRINEY
	setflag FLAG_TEMP_12
	return

SouthernIsland_EventScript_RemoveBriney2::
	removeobject LOCALID_BRINEY2
	setflag FLAG_TEMP_13
	return

SouthernIsland_EventScript_BrineyFastTravel::
	lock
	faceplayer
	speakername SouthernIsland_Text_NameBriney
	msgbox SouthernIsland_Text_WantToVoyage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SouthernIsland_EventScript_WarpToTidal
	msgbox SouthernIsland_Text_IllBeHere, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

SouthernIsland_EventScript_WarpToTidal::
	msgbox SouthernIsland_Text_BonVoyage, MSGBOX_DEFAULT
	speakername NULL
	warp MAP_SS_TIDAL_MID_TERIORS, 33, 4
	release
	end

SouthernIsland_EventScript_BardSingsSong::
	lock
	applymovement LOCALID_P_MAN, SouthernIsland_Movement_FaceRight
	applymovement OBJ_EVENT_ID_PLAYER, SouthernIsland_Movement_JoinParty
	waitmovement 0
	applymovement LOCALID_P_MAN, SouthernIsland_Movement_FaceLeft
	applymovement LOCALID_BARD, SouthernIsland_Movement_LookAround
	waitmovement 0
	speakername SouthernIsland_Text_NameDock
	msgbox SouthernIsland_Text_ISeeEveryoneHasGathered, MSGBOX_DEFAULT
	speakername SouthernIsland_Text_NameBriney
	msgbox SouthernIsland_Text_SingYourSongBro, MSGBOX_DEFAULT
	speakername SouthernIsland_Text_NameStern
	msgbox SouthernIsland_Text_ImExcited, MSGBOX_DEFAULT
	fadenewbgm MUS_NONE
	speakername SouthernIsland_Text_NameDock
	msgbox SouthernIsland_Text_Ahem, MSGBOX_DEFAULT
	closemessage
	fadenewbgm MUS_END
	delay 16
	delay 16
	speakername SouthernIsland_Text_NameDock
	msgbox SouthernIsland_Text_SongLyrics, MSGBOX_DEFAULT
	closemessage
	delay 16
	delay 16
	fadenewbgm MUS_NONE
	speakername SouthernIsland_Text_NameStern
	msgbox SouthernIsland_Text_ThatWasGreat, MSGBOX_DEFAULT
	speakername SouthernIsland_Text_NameDrake
	msgbox SouthernIsland_Text_TakesMeBack, MSGBOX_DEFAULT
	applymovement LOCALID_BARD, SouthernIsland_Movement_FaceRight
	fadenewbgm MUS_VERDANTURF
	speakername SouthernIsland_Text_NameDock
	msgbox SouthernIsland_Text_ItsTimeToRetire, MSGBOX_DEFAULT
	speakername SouthernIsland_Text_NameKizuna
	msgbox SouthernIsland_Text_AsYouWish, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_P_MAN, SouthernIsland_Movement_KizunaFormUp
	waitmovement 0
	playse SE_M_MEGA_KICK
	applymovement LOCALID_P_MAN, SouthernIsland_Movement_KizunaAbsorbGiddy
	waitmovement 0
	removeobject LOCALID_BARD
	setflag FLAG_TEMP_17
	setvar VAR_OLD_GUYS_STATE, 11
	playse SE_M_FAINT_ATTACK
	waitse
	applymovement LOCALID_ARCHIE, SouthernIsland_Movement_ArchieWalkToKizuna
	speakername SouthernIsland_Text_NameArchie
	msgbox SouthernIsland_Text_DockYouveOutdoneYourself, MSGBOX_DEFAULT
	applymovement LOCALID_P_MAN, SouthernIsland_Movement_Question
	speakername SouthernIsland_Text_NameKizuna
	msgbox SouthernIsland_Text_What, MSGBOX_DEFAULT
	speakername SouthernIsland_Text_NameStern
	msgbox SouthernIsland_Text_DontBeModest, MSGBOX_DEFAULT
	speakername SouthernIsland_Text_NameBriney
	msgbox SouthernIsland_Text_LetsHitTheSea, MSGBOX_DEFAULT
	warp MAP_SEA_MAUVILLE, 44, 54
	waitstate
	release
	end

SouthernIsland_Movement_FaceRight:
	face_right
	step_end

SouthernIsland_Movement_JoinParty:
	walk_left
	walk_left
	step_end

SouthernIsland_Movement_FaceLeft:
	face_left
	step_end

SouthernIsland_Movement_LookAround:
	face_left
	delay_16
	face_right
	delay_16
	face_down
	delay_8
	step_end

SouthernIsland_Movement_KizunaFormUp:
	walk_left
	walk_left
	walk_left
	walk_up
	face_left
	step_end

SouthernIsland_Movement_KizunaAbsorbGiddy:
	walk_slow_left
	step_end

SouthernIsland_Movement_ArchieWalkToKizuna:
	walk_right
	walk_right
	walk_up
	walk_up
	face_right
	step_end

SouthernIsland_Movement_Question:
	emote_question_mark
	face_down
	step_end

SouthernIsland_Text_NameDock:
	.string "Dock$"

SouthernIsland_Text_NameBriney:
	.string "Cpt. Briney$"

SouthernIsland_Text_NameStern:
	.string "Cpt. Stern$"

SouthernIsland_Text_NameDrake:
	.string "Drake$"

SouthernIsland_Text_NameKizuna:
	.string "Kizuna$"

SouthernIsland_Text_NameArchie:
	.string "Archie$"

SouthernIsland_Text_WantToVoyage:
	.string "Ahoy there {PLAYER}!\p"
	.string "The Tidal is docked and\n"
	.string "itching for another voyage.\p"
	.string "Will you be joining us?$"

SouthernIsland_Text_IllBeHere:
	.string "You're always welcome aboard!\n"
	.string "Have a good one.$"

SouthernIsland_Text_BonVoyage:
	.string "About time to haul anchor, then!$"

SouthernIsland_Text_ISeeEveryoneHasGathered:
	.string "I see everyone has gathered!\n"
	.string "Excellent. I'm so thankful to\l"
	.string "have you all with me here\l"
	.string "on the day of my retirement.\l"
	.string "I've made many friends in my time\l"
	.string "at the Shipyard, and you all\l"
	.string "were the deepest of those connections.\p"
	.string "I've prepared one last short song,\n"
	.string "of sorts. You know, kind of calling\l"
	.string "back to my days as a bard.\l"
	.string "I'm a bit rusty in the vocal\l"
	.string "department, but...\l"
	.string "I have to give it a shot.$"

SouthernIsland_Text_SingYourSongBro:
	.string "That's delightful, Dock!\n"
	.string "Show us you've still got it!$"

SouthernIsland_Text_ImExcited:
	.string "Oh, Dock. Ever the sentimentalist.\p"
	.string "I am looking forward to\n"
	.string "the performance. You're grinning\l"
	.string "from ear to ear, hahaha...$"

SouthernIsland_Text_Ahem:
	.string "Ahem.$"

SouthernIsland_Text_SongLyrics:
	.string "Those whose memories fade seek to\n"
	.string "carve them in their hearts...\p"
	.string "All dreams are but another reality.\n"
	.string "Never forget...$"

SouthernIsland_Text_ThatWasGreat:
	.string "You possess such great range in\n"
	.string "your voice, Dock. Maybe you could\l"
	.string "have made it as an opera singer.$"

SouthernIsland_Text_TakesMeBack:
	.string "You have not lost your\n"
	.string "touch one iota, chum. That sure\l"
	.string "took me back to the past.$"

SouthernIsland_Text_ItsTimeToRetire:
	.string "Ah-ha-ha-ha...\n"
	.string "I...I'm sorry, lads, I can't\l"
	.string "help but cry tears of joy.\l"
	.string "I'm so glad you all are with me.\p"
	.string "I'll make it official, then.\n"
	.string "Today is my retirement day!\l"
	.string "It feels good to finally say it.\p"
	.string "...Err, Kizuna, right?\n"
	.string "Giddy, and Rydel...\l"
	.string "I would like to reunite with them.\l"
	.string "...You know what to do, hmm?$"

SouthernIsland_Text_AsYouWish:
	.string "Ah...\p"
	.string "I had figured that this would be\n"
	.string "what was waiting for us here.\p"
	.string "You wish for retirement?\n"
	.string "Granted.$"

SouthernIsland_Text_DockYouveOutdoneYourself:
	.string "Dock, my boy! This was quite fun!\n"
	.string "Maybe we should all get together\l"
	.string "again next month? If we can get\l"
	.string "any time away, that is!$"

SouthernIsland_Text_What:
	.string "W-What...? You're calling me...\n"
	.string "Dock...?$"

SouthernIsland_Text_DontBeModest:
	.string "Oh, I'm sorry. You really should\n"
	.string "be called The Bard, for that\l"
	.string "performance, hahaha...$"

SouthernIsland_Text_LetsHitTheSea:
	.string "Let's sail back home now,\n"
	.string "gentlemen! Bon voyage!$"
