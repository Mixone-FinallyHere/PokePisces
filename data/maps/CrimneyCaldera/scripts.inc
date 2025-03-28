CrimneyCaldera_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CrimneyCaldera_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CrimneyCaldera_OnFrame
	.byte 0

CrimneyCaldera_OnLoad:
	call_if_set FLAG_DEFEATED_SHA_GROU, CrimneyCaldera_EventScript_RemoveShaGrou
	end

CrimneyCaldera_OnFrame:
	map_script_2 VAR_NEW_COO_STATE, 7, CrimneyCaldera_EventScript_WallaceOrbEvent
	.2byte 0

CrimneyCaldera_EventScript_RemoveShaGrou::
	setvar VAR_TEMP_4, 1
	setmetatile 17, 5, METATILE_Lavaridge_LavaBubbleTile, FALSE
	setmetatile 18, 5, METATILE_Lavaridge_LavaTile, FALSE
	setmetatile 19, 5, METATILE_Lavaridge_LavaTile, FALSE
	setmetatile 20, 5, METATILE_Lavaridge_LavaTile, FALSE
	setmetatile 21, 5, METATILE_Lavaridge_LavaTile, FALSE
	setmetatile 17, 6, METATILE_Lavaridge_LavaTile, FALSE
	setmetatile 18, 6, METATILE_Lavaridge_LavaTile, FALSE
	setmetatile 19, 6, METATILE_Lavaridge_LavaTile, FALSE
	setmetatile 20, 6, METATILE_Lavaridge_LavaTile, FALSE
	setmetatile 21, 6, METATILE_Lavaridge_LavaBubbleTile, FALSE
	special DrawWholeMapView
	return

CrimneyCaldera_EventScript_LegendaryEncounter::
	lock
	msgbox CrimneyCaldera_Text_TheyreFighting, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_SHAYON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox CrimneyCaldera_Text_TimeToStepIn, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_SHAYON, 80, ITEM_WIDE_ARMOR, SPECIES_GROUDON, 80, ITEM_WIDE_ARMOR
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	setwildbattlemusic MUS_VS_RISING_LEGEND
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	setwildbattlemusic MUS_VS_WILD2
	playmoncry SPECIES_SHAYON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	playmoncry SPECIES_GROUDON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox CrimneyCaldera_Text_BreakThemUp, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_DEFEATED_SHA_GROU
	delay 16
	setseenmon SPECIES_GROUDON
	setcaughtmon SPECIES_GROUDON
	setseenmon SPECIES_SHAYON
	setcaughtmon SPECIES_SHAYON
	setvar VAR_NEW_COO_STATE, 7
	warp MAP_CRIMNEY_CALDERA, 19, 13
	waitstate
	release
	end

CrimneyCaldera_EventScript_WallaceIdle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SHA_GROU, CrimneyCaldera_EventScript_WallaceIdleBeatSha
	speakername CrimneyCaldera_Text_NameWallace
	msgbox CrimneyCaldera_Text_ISenseOneNearby, MSGBOX_AUTOCLOSE
	release
	end

CrimneyCaldera_EventScript_WallaceIdleBeatSha::
	goto_if_set FLAG_DEFEATED_LUO_KYO, CrimneyCaldera_EventScript_WallaceIdleBeatBoth
	speakername CrimneyCaldera_Text_NameWallace
	msgbox CrimneyCaldera_Text_GoToLuoshan, MSGBOX_AUTOCLOSE
	release
	end

CrimneyCaldera_EventScript_WallaceIdleBeatBoth::
	speakername CrimneyCaldera_Text_NameWallace
	msgbox CrimneyCaldera_Text_TheFishWentToEGR, MSGBOX_AUTOCLOSE
	release
	end

CrimneyCaldera_EventScript_WallaceOrbEvent::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, CrimneyCaldera_Movement_WalkToWallace
	waitmovement 0
	goto_if_set FLAG_DEFEATED_LUO_KYO, CrimneyCaldera_EventScript_BeatBothLegends
	setvar VAR_NEW_COO_STATE, 6
	speakername CrimneyCaldera_Text_NameWallace
	msgbox CrimneyCaldera_Text_GoToLuoshan, MSGBOX_DEFAULT
	release
	end

CrimneyCaldera_Movement_WalkToWallace:
	walk_down
	walk_right
	step_end

CrimneyCaldera_EventScript_BeatBothLegends::
	speakername CrimneyCaldera_Text_NameWallace
	msgbox CrimneyCaldera_Text_TheFishWentToEGR, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEW_COO_STATE, 9
	setflag FLAG_DEFEATED_TWO_PISCES_LEGENDS
	clearflag FLAG_HIDE_MAXIE_OZONE
	release
	end

CrimneyCaldera_EventScript_Meiyu::
    trainerbattle_single TRAINER_P_MEIYU, CrimneyCaldera_Text_MeiyuIntro, CrimneyCaldera_Text_MeiyuDefeated
    msgbox CrimneyCaldera_Text_MeiyuPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyCaldera_EventScript_Centauri::
    trainerbattle_single TRAINER_P_CENTAURI, CrimneyCaldera_Text_CentauriIntro, CrimneyCaldera_Text_CentauriDefeated
    msgbox CrimneyCaldera_Text_CentauriPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyCaldera_Text_MeiyuIntro:
	.string "The smell of ash and brimstone\n"
	.string "has always brought me calm.\l"
	.string "With a clear head, I will be\l"
	.string "taking you out!$"

CrimneyCaldera_Text_MeiyuDefeated:
	.string "I mixed up too many weathers!$"

CrimneyCaldera_Text_MeiyuPostBattle:
	.string "Looks like I wasn't as clear-minded\n"
	.string "as I has assumed. Maybe I should\l"
	.string "really hone in on one weather...$"

CrimneyCaldera_Text_CentauriIntro:
	.string "I call upon the power of the sun!\n"
	.string "Come, bathe me in your bright light!\l"
	.string "Burn this foe... to a crisp!$"

CrimneyCaldera_Text_CentauriDefeated:
	.string "I was blinded by my faith\n"
	.string "in the sun...$"

CrimneyCaldera_Text_CentauriPostBattle:
	.string "Groudon is the true ruler of the\n"
	.string "land, and the weather that is\l"
	.string "harsh sunlight. In fact, the drought\l"
	.string "it brings into battle is so blazing,\l"
	.string "that Water type attacks evaporate.$"

CrimneyCaldera_Text_TheyreFighting:
	.string "(It's Groudon and Sha-Yon!\n"
	.string "They're locked in combat...)$"

CrimneyCaldera_Text_TimeToStepIn:
	.string "(You strengthen your resolve,\n"
	.string "and jump into the fray.)$"

CrimneyCaldera_Text_BreakThemUp:
	.string "(Through a tough battle,\n"
	.string "you manage to split up and\l"
	.string "weaken the two Legendary Pokemon!)\p"
	.string "(Groudon begins its retreat,\n"
	.string "and Sha-Yon starts to glow a\l"
	.string "bright white...)$"

CrimneyCaldera_Text_NameWallace:
	.string "Wallace$"

CrimneyCaldera_Text_ISenseOneNearby:
	.string "I sense that one of the\n"
	.string "Legendary Fish of the Lake\l"
	.string "are nearby. If you are in need\l"
	.string "of my help, I will be there.\l"
	.string "Otherwise, I believe you and\l"
	.string "your team are strong enough to\l"
	.string "take them on.$"

CrimneyCaldera_Text_GoToLuoshan:
	.string "Sha-Yon... upon its defeat,\n"
	.string "it regressed into this red orb.\l"
	.string "It seems to me dormant.\p"
	.string "I will need Luo-Shan to be\n"
	.string "pacified and return to its\l"
	.string "orb form before we can\l"
	.string "restore the lake.\l"
	.string "I believe it to have fled to\l"
	.string "the lowest point of Hoenn...\l"
	.string "Etheor Nadir, the trench\l"
	.string "beneath Etheor Falls.\p"
	.string "Go there, and I will accompany\n"
	.string "you to procure the second orb.$"

CrimneyCaldera_Text_TheFishWentToEGR:
	.string "That makes both of the orbs procured,\n"
	.string "along with both Groudon and Kyogre\l"
	.string "sent back into dormancy,\l"
	.string "at least, for now.\l"
	.string "Excellent...\p"
	.string "In order to restore Sha-Yon\n"
	.string "and Luo-Shan to their original forms,\l"
	.string "it will require partaking in\l"
	.string "a special ritual.\l"
	.string "We will need the assistance\l"
	.string "of multiple talented individuals\l"
	.string "to complete said ritual.\l"
	.string "Of course, I am saying this to\l"
	.string "preface my invitation to you.\p"
	.string "The ritual shall be taking place\n"
	.string "at the Golden Plains... a holy\l"
	.string "site of worship off the coast\l"
	.string "of southeastern Hoenn.\p"
	.string "There is no way to travel there\n"
	.string "right now besides the air.\l"
	.string "I will set things up with Maxie\l"
	.string "and Archie so that they can\l"
	.string "personally fly you there.\p"
	.string "Go to the Ozone Institute when\n"
	.string "you are prepared thoroughly.\l"
	.string "I very much look forward\l"
	.string "to your attendance, {PLAYER}!$"
