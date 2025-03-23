.set LOCALID_MATT, 14
.set LOCALID_OZONE1, 15
.set LOCALID_OZONE2, 16
.set LOCALID_OZONE3, 17

SweltornDesert_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SweltornDesert_OnLoad
	.byte 0

SweltornDesert_OnLoad:
	call_if_unset FLAG_SUMMONED_PEBB_METEOR, SweltornDesert_EventScript_NoMeteorite
	call_if_set FLAG_GOT_PEBBLERITE, SweltornDesert_EventScript_NoPebblerite
	call_if_lt VAR_OZONE_ADMINS_STATE, 8, SweltornDesert_EventScript_RemoveMattAndMinions
	call_if_gt VAR_OZONE_ADMINS_STATE, 8, SweltornDesert_EventScript_RemoveMattAndMinions
	end

SweltornDesert_EventScript_NoMeteorite::
	setmetatile 10, 19, METATILE_desert_MeteorlessCorner, FALSE
	setmetatile 11, 19, METATILE_desert_MeteorlessTop, FALSE
	setmetatile 12, 19, METATILE_desert_MeteorlessTop, FALSE
	setmetatile 13, 19, METATILE_desert_MeteorlessTop, FALSE
	setmetatile 9, 20, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 10, 20, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 11, 20, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 12, 20, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 13, 20, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 14, 20, METATILE_desert_MeteorlessBone, TRUE
	setmetatile 9, 21, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 10, 21, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 11, 21, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 12, 21, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 13, 21, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 14, 21, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 9, 22, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 10, 22, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 11, 22, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 12, 22, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 13, 22, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 14, 22, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 9, 23, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 10, 23, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 11, 23, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 12, 23, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 13, 23, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 14, 23, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 9, 24, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 10, 24, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 11, 24, METATILE_desert_MeteorlessRock, FALSE
	setmetatile 12, 24, METATILE_desert_MeteorlessRock, FALSE
	special DrawWholeMapView
	return

SweltornDesert_EventScript_NoPebblerite::
	setmetatile 13, 21, METATILE_desert_NoPebbleriteTop, TRUE
	setmetatile 13, 22, METATILE_desert_NoPebbleriteBottom, TRUE
	special DrawWholeMapView
	return

SweltornDesert_EventScript_RemoveMattAndMinions::
	removeobject LOCALID_MATT
	setflag FLAG_TEMP_11
	removeobject LOCALID_OZONE1
	setflag FLAG_TEMP_12
	removeobject LOCALID_OZONE2
	setflag FLAG_TEMP_13
	removeobject LOCALID_OZONE3
	setflag FLAG_TEMP_14
	return

SweltornDesert_EventScript_MattEncounterLeft1::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerLeft
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetLeft1
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleLeft
	release
	end

SweltornDesert_Movement_MattNoticePlayerLeft:
	face_left
	emote_exclamation_mark
	step_end

SweltornDesert_Movement_PlayerMeetLeft1:
	walk_right
	walk_down
	walk_right
	walk_down
	face_right
	step_end

SweltornDesert_EventScript_MattEncounterLeft2::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerLeft
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetLeft2
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleLeft
	release
	end

SweltornDesert_Movement_PlayerMeetLeft2:
	walk_right
	walk_down
	walk_right
	step_end

SweltornDesert_EventScript_MattEncounterLeft3::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerLeft
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetLeft3
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleLeft
	release
	end

SweltornDesert_Movement_PlayerMeetLeft3:
	walk_right
	walk_right
	step_end

SweltornDesert_EventScript_MattEncounterLeft4::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerLeft
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetLeft4
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleLeft
	release
	end

SweltornDesert_Movement_PlayerMeetLeft4:
	walk_right
	walk_up
	walk_right
	step_end

SweltornDesert_EventScript_MattEncounterLeft5::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerLeft
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetLeft5
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleLeft
	release
	end

SweltornDesert_Movement_PlayerMeetLeft5:
	walk_up
	walk_right
	walk_up
	walk_right
	step_end

SweltornDesert_EventScript_MattBattleLeft::
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_BeenSpelunking, MSGBOX_DEFAULT
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_MattIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_MATT_2, SweltornDesert_Text_MattDefeated
	goto SweltornDesert_EventScript_MattPostBattleLeft
	release
	end

SweltornDesert_EventScript_MattPostBattleLeft::
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_GoodBattleIllMoveMyGuys, MSGBOX_DEFAULT
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattLeavesLeft
	waitmovement 0
	setvar VAR_OZONE_ADMINS_STATE, 9
	removeobject LOCALID_MATT
	setflag FLAG_TEMP_11
	removeobject LOCALID_OZONE1
	setflag FLAG_TEMP_12
	removeobject LOCALID_OZONE2
	setflag FLAG_TEMP_13
	removeobject LOCALID_OZONE3
	setflag FLAG_TEMP_14
	release
	end

SweltornDesert_Movement_MattLeavesLeft:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

SweltornDesert_EventScript_MattEncounterRight1::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerRight
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetRight1
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleRight
	release
	end

SweltornDesert_Movement_MattNoticePlayerRight:
	face_right
	emote_exclamation_mark
	step_end

SweltornDesert_Movement_PlayerMeetRight1:
	walk_down
	walk_left
	walk_down
	walk_left
	step_end

SweltornDesert_EventScript_MattEncounterRight2::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerRight
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetRight2
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleRight
	release
	end

SweltornDesert_Movement_PlayerMeetRight2:
	walk_left
	walk_down
	walk_left
	step_end

SweltornDesert_EventScript_MattEncounterRight3::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerRight
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetRight3
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleRight
	release
	end

SweltornDesert_Movement_PlayerMeetRight3:
	walk_left
	walk_left
	step_end

SweltornDesert_EventScript_MattEncounterRight4::
	lock
	playse SE_PIN
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattNoticePlayerRight
	waitmovement 0
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_IsThatYou, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, SweltornDesert_Movement_PlayerMeetRight4
	waitmovement 0
	goto SweltornDesert_EventScript_MattBattleRight
	release
	end

SweltornDesert_Movement_PlayerMeetRight4:
	walk_left
	walk_up
	walk_left
	step_end

SweltornDesert_EventScript_MattBattleRight::
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_BeenSpelunking, MSGBOX_DEFAULT
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_MattIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_MATT_2, SweltornDesert_Text_MattDefeated
	goto SweltornDesert_EventScript_MattPostBattleRight
	release
	end

SweltornDesert_EventScript_MattPostBattleRight::
	speakername SweltornDesert_Text_NameMatt
	msgbox SweltornDesert_Text_GoodBattleIllMoveMyGuys, MSGBOX_DEFAULT
	applymovement LOCALID_MATT, SweltornDesert_Movement_MattLeavesRight
	waitmovement 0
	setvar VAR_OZONE_ADMINS_STATE, 9
	removeobject LOCALID_MATT
	setflag FLAG_TEMP_11
	removeobject LOCALID_OZONE1
	setflag FLAG_TEMP_12
	removeobject LOCALID_OZONE2
	setflag FLAG_TEMP_13
	removeobject LOCALID_OZONE3
	setflag FLAG_TEMP_14
	release
	end

SweltornDesert_Movement_MattLeavesRight:
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SweltornDesert_EventScript_OzoneRoadblocker1::
	msgbox SweltornDesert_Text_OzoneRoadblocker1, MSGBOX_NPC
    end

SweltornDesert_EventScript_OzoneRoadblocker2::
	msgbox SweltornDesert_Text_OzoneRoadblocker2, MSGBOX_NPC
    end

SweltornDesert_EventScript_OzoneRoadblocker3::
	msgbox SweltornDesert_Text_OzoneRoadblocker3, MSGBOX_NPC
    end

SweltornDesert_EventScript_Santo::
    trainerbattle_single TRAINER_P_SANTO, SweltornDesert_Text_SantoIntro, SweltornDesert_Text_SantoDefeated
    msgbox SweltornDesert_Text_SantoPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Dorothy::
    trainerbattle_single TRAINER_P_DOROTHY, SweltornDesert_Text_DorothyIntro, SweltornDesert_Text_DorothyDefeated
    msgbox SweltornDesert_Text_DorothyPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Erin::
    trainerbattle_single TRAINER_P_ERIN, SweltornDesert_Text_ErinIntro, SweltornDesert_Text_ErinDefeated
    msgbox SweltornDesert_Text_ErinPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Aaron::
    trainerbattle_single TRAINER_P_AARON, SweltornDesert_Text_AaronIntro, SweltornDesert_Text_AaronDefeated
    msgbox SweltornDesert_Text_AaronPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Thad::
    trainerbattle_single TRAINER_P_THAD, SweltornDesert_Text_ThadIntro, SweltornDesert_Text_ThadDefeated
    msgbox SweltornDesert_Text_ThadPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Leela::
    trainerbattle_single TRAINER_P_LEELA, SweltornDesert_Text_LeelaIntro, SweltornDesert_Text_LeelaDefeated
    msgbox SweltornDesert_Text_LeelaPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Ickle::
    trainerbattle_single TRAINER_P_ICKLE, SweltornDesert_Text_IckleIntro, SweltornDesert_Text_IckleDefeated
    msgbox SweltornDesert_Text_IcklePostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Staph::
    trainerbattle_single TRAINER_P_STAPH, SweltornDesert_Text_StaphIntro, SweltornDesert_Text_StaphDefeated
    msgbox SweltornDesert_Text_StaphPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Hwarang::
    trainerbattle_single TRAINER_P_HWARANG, SweltornDesert_Text_HwarangIntro, SweltornDesert_Text_HwarangDefeated
    msgbox SweltornDesert_Text_HwarangPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Takeshi::
    trainerbattle_single TRAINER_P_TAKESHI, SweltornDesert_Text_TakeshiIntro, SweltornDesert_Text_TakeshiDefeated
    msgbox SweltornDesert_Text_TakeshiPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Beat::
    trainerbattle_single TRAINER_P_BEAT, SweltornDesert_Text_BeatIntro, SweltornDesert_Text_BeatDefeated
    msgbox SweltornDesert_Text_BeatPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_Dotty::
    trainerbattle_single TRAINER_P_DOTTY, SweltornDesert_Text_DottyIntro, SweltornDesert_Text_DottyDefeated
    msgbox SweltornDesert_Text_DottyPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornDesert_EventScript_TakePebblerite::
	lock
	goto_if_unset FLAG_SUMMONED_PEBB_METEOR, SweltornDesert_EventScript_ReleaseOut
	goto_if_set FLAG_GOT_PEBBLERITE, SweltornDesert_EventScript_PebbleriteGotten
	msgbox SweltornDesert_Text_TakePebblerite, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_PEBBLERITE
	closemessage
	call SweltornDesert_EventScript_NoPebblerite
	delay 8
	setflag FLAG_GOT_PEBBLERITE
	release
	end

SweltornDesert_EventScript_PebbleriteGotten::
	msgbox SweltornDesert_Text_PebbleriteGotten, MSGBOX_AUTOCLOSE
	release
	end

SweltornDesert_EventScript_ReleaseOut::
	release
	end

SweltornDesert_EventScript_OzoneSign::
	msgbox SweltornDesert_Text_OzoneSign, MSGBOX_SIGN
	end

SweltornDesert_Text_OzoneSign:
	.string "This tunnel leads to the\n"
	.string "Ozone Institute.$"

SweltornDesert_Text_TakePebblerite:
	.string "(It's a giant meteor!\n"
	.string "It is glowing green with\l"
	.string "radioactive energy...)\p"
	.string "(You see a peculiar looking gem\n"
	.string "embedded in the front.\l"
	.string "...Couldn't hurt to take it.)$"

SweltornDesert_Text_PebbleriteGotten:
	.string "(You've already taken the gem.)$"

SweltornDesert_Text_SantoIntro:
	.string "Hold it, kid! Sweltorn Desert is\n"
	.string "experiencing a pretty severe\l"
	.string "sandstorm right now.\p"
	.string "Do you have a pair of Go-Goggles?$"

SweltornDesert_Text_SantoDefeated:
	.string "Good, it seems you're prepared...$"

SweltornDesert_Text_SantoPostBattle:
	.string "Sandstorms around this area used to\n"
	.string "be pretty minor, but now they're\l"
	.string "out of control...\p"
	.string "...But don't worry, kid!\n"
	.string "Team Ozone will have everything\l"
	.string "under control in no time!$"

SweltornDesert_Text_DorothyIntro:
	.string "Do you have the grace and serenity\n"
	.string "to withstand my Pokemon?$"

SweltornDesert_Text_DorothyDefeated:
	.string "Even with my myriad of\n"
	.string "added effects...?$"

SweltornDesert_Text_DorothyPostBattle:
	.string "If you happen upon a Pokemon\n"
	.string "with Serene Grace, you shalt not\l"
	.string "find yourself dissapointed...$"

SweltornDesert_Text_ErinIntro:
	.string "Who do you think these\n"
	.string "big ol' bones belong to?$"

SweltornDesert_Text_ErinDefeated:
	.string "I wasn't talking about myself!$"

SweltornDesert_Text_ErinPostBattle:
	.string "I'm trying to find out what sort of \n"
	.string "colossal Pokémon these bones\n"
	.string "once were...\n"
	.string "Or maybe it wasn't a Pokémon at all...?$"

SweltornDesert_Text_AaronIntro:
	.string "Dust is nothin' to a guy\n"
	.string "without sight!$"

SweltornDesert_Text_AaronDefeated:
	.string "Yes, I heard that defeat.\n"
	.string "Loud and clear.$"

SweltornDesert_Text_AaronPostBattle:
	.string "Craverave is a great Pokemon to\n"
	.string "have as a partner, as a blind guy.\l"
	.string "They're great at communicating.$"

SweltornDesert_Text_ThadIntro:
	.string "There are some wicked creatures\n"
	.string "lying just below the sand!$"

SweltornDesert_Text_ThadDefeated:
	.string "I've been buried!$"

SweltornDesert_Text_ThadPostBattle:
	.string "If something gets dragged too\n"
	.string "deep into the sea of sand,\l"
	.string "you may never see it again.$"

SweltornDesert_Text_LeelaIntro:
	.string "Is this the right address?\n"
	.string "I think I'm lost...$"

SweltornDesert_Text_LeelaDefeated:
	.string "Can you give me a five-star review,\n"
	.string "please?$"

SweltornDesert_Text_LeelaPostBattle:
	.string "Hmm, this isn't right...\n"
	.string "I'm trying to find “Yes Town”.\p"
	.string "You don't suppose someone's punking\n"
	.string "me, do you?$"

SweltornDesert_Text_IckleIntro:
	.string "Woof.. sure is hot here.$"

SweltornDesert_Text_IckleDefeated:
	.string "Good weather for some ice cold treats.$"

SweltornDesert_Text_IcklePostBattle:
	.string "Have some dessert in the desert.$"

SweltornDesert_Text_StaphIntro:
	.string "...Eh? Trainers, out here!?$"

SweltornDesert_Text_StaphDefeated:
	.string "I specifically wanted to avoid this.$"

SweltornDesert_Text_StaphPostBattle:
	.string "Have you been drinking water?\n"
	.string "Yeah, I bet you haven't, you're sweating\l"
	.string "like a Sadsod. Stock up.$"

SweltornDesert_Text_HwarangIntro:
	.string "Spend enough time in dust devils,\n"
	.string "and the irritants stop irritating.\p"
	.string "I feel more rock than man!\n"
	.string "Let's test out my strength...\l"
	.string "on YOU!$"

SweltornDesert_Text_HwarangDefeated:
	.string "Ah, another master of the\n"
	.string "Majadijunn style...$"

SweltornDesert_Text_HwarangPostBattle:
	.string "The desert certainly isn't\n"
	.string "for any Martial Artist.$"

SweltornDesert_Text_TakeshiIntro:
	.string "Those eyes... You hold a love for battle,\n"
	.string "don't you?\p"
	.string "Very well then, show me your\n"
	.string "passion combat!$"

SweltornDesert_Text_TakeshiDefeated:
	.string "Hmph, as to be expected!$"

SweltornDesert_Text_TakeshiPostBattle:
	.string "You are a very unique trainer.\n"
	.string "Do not squander such a gift!$"

SweltornDesert_Text_BeatIntro:
	.string "You really wanna take on\n"
	.string "our challenge?$"

SweltornDesert_Text_BeatDefeated:
	.string "The solution is always violence!$"

SweltornDesert_Text_BeatPostBattle:
	.string "If someone tries to give you\n"
	.string "a treasure map, my advice is\l"
	.string "to beat the daylights out of 'em!$"

SweltornDesert_Text_DottyIntro:
	.string "Ah, I have been searching for an\n"
	.string "oasis... but this desert\l"
	.string "is particularly dry!$"

SweltornDesert_Text_DottyDefeated:
	.string "I'm too parched to continue!$"

SweltornDesert_Text_DottyPostBattle:
	.string "At this point, I'll believe\n"
	.string "any mirage I see...$"

SweltornDesert_Text_NameMatt:
	.string "Matt$"

SweltornDesert_Text_IsThatYou:
	.string "Aye, is that that trainer\n"
	.string "that whooped my butt at Lilycove?\p"
	.string "Gaha! It is! Get on over here\n"
	.string "real quick. I won't bite!$"

SweltornDesert_Text_BeenSpelunking:
	.string "I've been spelunking in Sweltorn\n"
	.string "Palace all day! Sweatin' my\l"
	.string "ASS off, I'll tell you that!\l"
	.string "But, it's been a blast piecing\l"
	.string "together its history.\p"
	.string "The people that live here in the\n"
	.string "desert get a lot of their money\l"
	.string "from research grants. And I find\l"
	.string "the archaeology real damned cool!\l"
	.string "So I push to get 'em funded\l"
	.string "whenever I can.\p"
	.string "That crudmuncher Tabitha could\n"
	.string "never understand my thought\l"
	.string "process on it. Hey, at least I'm\l"
	.string "rid of that chump. Archie\l"
	.string "teared me a new one for the\l"
	.string "splintering, but in the end I\l"
	.string "got what I wanted!$"

SweltornDesert_Text_MattIntro:
	.string "And you know what? When we battled\n"
	.string "the first time with you as a team?\l"
	.string "That didn't let me show off\l"
	.string "jack all about my true skillset!\l"
	.string "I promise you that!\p"
	.string "I've half a mind to re-battle you!\n"
	.string "...Make that full a mind!\l"
	.string "Let's have at it!$"

SweltornDesert_Text_MattDefeated:
	.string "Offed even on my own!\n"
	.string "You sure as hell ain't\l"
	.string "no pipsqueak!$"

SweltornDesert_Text_GoodBattleIllMoveMyGuys:
	.string "That really fired me up!\n"
	.string "Thanks for the good battle.\l"
	.string "You're something else!\p"
	.string "Check out the palace if you're\n"
	.string "in the mood to spelunk.\l"
	.string "The craftsmanship is unreal!\l"
	.string "Anyways, I've gotta get going.\l"
	.string "My squad's waitin' for me at\l"
	.string "the southern gate. See ya!$"

SweltornDesert_Text_OzoneRoadblocker1:
	.string "Matt was always the spacier,\n"
	.string "looser one of our department's\l"
	.string "old admins. Since the splinter,\l"
	.string "I went with him. I like not being\l"
	.string "micromanaged but, like, he\l"
	.string "needs to stick to SOME\l"
	.string "time schedule someday...$"

SweltornDesert_Text_OzoneRoadblocker2:
	.string "Where's our manager gone off to?\p"
	.string "Ehh. He probably got distracted\n"
	.string "by Sweltorn Palace yet again.\l"
	.string "The guy practically lives in there.$"

SweltornDesert_Text_OzoneRoadblocker3:
	.string "Sorry, can't really afford letting\n"
	.string "people through the gate without\l"
	.string "the admin's approval.$"
