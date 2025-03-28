.set LOCALID_MONK, 9
.set LOCALID_HINTMONK, 26
.set LOCALID_EGGNEGGMA1, 10
.set LOCALID_EGGNEGGMA2, 11
.set LOCALID_EGGNEGGMA3, 12
.set LOCALID_EGGNEGGMA4, 13
.set LOCALID_EGGNEGGMA5, 14
.set LOCALID_EGGNEGGMA6, 15
.set LOCALID_YANDEMIC, 18

MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_OnLoad
	.byte 0

MossdeepCity_OnLoad:
	call MossdeepCity_EventScript_SetEggState
	call_if_ge VAR_NOTICED_BY_YANDEMIC, 5, MossdeepCity_EventScript_RemoveYandemic
	call_if_lt VAR_PISCES_STORY_PROGRESS, 2, MossdeepCity_EventScript_RemoveHintMonk
	call_if_set FLAG_DEFEATED_PANIC_EVENT, MossdeepCity_EventScript_RemoveHintMonk
	goto_if_lt VAR_SPACE_CENTER_QUEST_STATE, 3, MossdeepCity_EventScript_HideMeteors
	end

MossdeepCity_EventScript_RemoveYandemic::
	removeobject LOCALID_YANDEMIC
	setflag FLAG_TEMP_B
	setvar VAR_TEMP_9, 1
	return

MossdeepCity_EventScript_RemoveHintMonk::
	removeobject LOCALID_HINTMONK
	setflag FLAG_TEMP_7
	return

MossdeepCity_EventScript_SetEggState::
	goto_if_set FLAG_MOSSDEEP_EGG, MossdeepCity_EventScript_EggGotten
	setflag FLAG_TEMP_18
	setflag FLAG_TEMP_19
	setflag FLAG_TEMP_1A
	setflag FLAG_TEMP_1B
	setflag FLAG_TEMP_1C
	return

MossdeepCity_EventScript_EggGotten::
	setflag FLAG_TEMP_17
	setflag FLAG_TEMP_18
	setflag FLAG_TEMP_19
	setflag FLAG_TEMP_1A
	setflag FLAG_TEMP_1B
	setflag FLAG_TEMP_1C
	setvar VAR_TEMP_4, 6
	return

MossdeepCity_EventScript_HideMeteors::
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	end

MossdeepCity_EventScript_MonkEncounter1::
	lock
	setflag FLAG_VISITED_MOSSDEEP_CITY
	applymovement LOCALID_MONK, MossdeepCity_Movement_MeetPlayer1
	waitmovement 0
	goto MossdeepCity_EventScript_MonkTakeToHouse1
	release
	end

MossdeepCity_Movement_MeetPlayer1:
	walk_left
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_EventScript_MonkEncounter2::
	lock
	setflag FLAG_VISITED_MOSSDEEP_CITY
	applymovement LOCALID_MONK, MossdeepCity_Movement_MeetPlayer2
	waitmovement 0
	goto MossdeepCity_EventScript_MonkTakeToHouse2
	release
	end

MossdeepCity_Movement_MeetPlayer2:
	walk_left
	walk_up
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_EventScript_MonkTakeToHouse1::
	msgbox MossdeepCity_Text_MonkGreeting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MONK, MossdeepCity_Movement_MonkTakePlayer1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerFollow1
	waitmovement 0
	msgbox MossdeepCity_Text_Gugumbir, MSGBOX_DEFAULT
	warp MAP_STEVEN_HOUSE, 3, 7
	waitstate
	release
	end

MossdeepCity_Movement_MonkTakePlayer1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
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
	face_down
	step_end

MossdeepCity_Movement_PlayerFollow1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
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
	step_end

MossdeepCity_EventScript_MonkTakeToHouse2::
	msgbox MossdeepCity_Text_MonkGreeting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MONK, MossdeepCity_Movement_MonkTakePlayer2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerFollow2
	waitmovement 0
	msgbox MossdeepCity_Text_Gugumbir, MSGBOX_DEFAULT
	warp MAP_STEVEN_HOUSE, 3, 7
	waitstate
	release
	end

MossdeepCity_Movement_MonkTakePlayer2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
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
	face_down
	step_end

MossdeepCity_Movement_PlayerFollow2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
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
	step_end

MossdeepCity_EventScript_MudShotGuy::
    lock
	faceplayer
	checkitem ITEM_TM_MUD_SHOT
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_EventScript_GaveMudShot
	msgbox MossdeepCity_Text_HaveMudShot, MSGBOX_DEFAULT
	giveitem ITEM_TM_MUD_SHOT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

MossdeepCity_EventScript_GaveMudShot::
    msgbox MossdeepCity_Text_GaveMudShot, MSGBOX_AUTOCLOSE
    release
    end

MossdeepCity_EventScript_Rawr::
	lock
	faceplayer
	checkitem ITEM_TM_SNARL
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_EventScript_GaveSnarl
	msgbox MossdeepCity_Text_WantToSeeMonGrowl, MSGBOX_DEFAULT
	checkpartynonhmmove MOVE_GROWL
	goto_if_eq VAR_RESULT, PARTY_SIZE, MossdeepCity_EventScript_NoGrowl
	msgbox MossdeepCity_Text_HaveSnarl, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNARL
	release
	end

MossdeepCity_EventScript_NoGrowl::
	msgbox MossdeepCity_Text_NoGrowl, MSGBOX_AUTOCLOSE
	release
	end

MossdeepCity_EventScript_GaveSnarl::
	msgbox MossdeepCity_Text_GaveSnarl, MSGBOX_AUTOCLOSE
	release
	end

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_Gugumbir, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_Gugumbir, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	end

MossdeepCity_EventScript_EggEncounter1North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA1, MossdeepCity_Movement_EggRunAway1North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA1
	setflag FLAG_TEMP_17
	clearflag FLAG_TEMP_18
	setvar VAR_TEMP_4, 1
	release
	end

MossdeepCity_Movement_EggRunAway1North:
	emote_exclamation_mark
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

MossdeepCity_EventScript_EggEncounter1West::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA1, MossdeepCity_Movement_EggRunAway1West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA1
	setflag FLAG_TEMP_17
	clearflag FLAG_TEMP_18
	setvar VAR_TEMP_4, 1
	release
	end

MossdeepCity_Movement_EggRunAway1West:
	emote_exclamation_mark
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

MossdeepCity_EventScript_EggEncounter2South::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, MossdeepCity_Movement_EggRunAway2South
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_18
	clearflag FLAG_TEMP_19
	setvar VAR_TEMP_4, 2
	release
	end

MossdeepCity_Movement_EggRunAway2South:
	emote_exclamation_mark
	face_right
	delay_8
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

MossdeepCity_EventScript_EggEncounter2North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA2, MossdeepCity_Movement_EggRunAway2North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA2
	setflag FLAG_TEMP_18
	clearflag FLAG_TEMP_1C
	setvar VAR_TEMP_4, 5
	release
	end

MossdeepCity_Movement_EggRunAway2North:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

MossdeepCity_EventScript_EggEncounter3East::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA3, MossdeepCity_Movement_EggRunAway3East
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA3
	setflag FLAG_TEMP_19
	clearflag FLAG_TEMP_1A
	setvar VAR_TEMP_4, 3
	release
	end

MossdeepCity_Movement_EggRunAway3East:
	emote_exclamation_mark
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

MossdeepCity_EventScript_EggEncounter3West::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA3, MossdeepCity_Movement_EggRunAway3West
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA3
	setflag FLAG_TEMP_19
	clearflag FLAG_TEMP_18
	setvar VAR_TEMP_4, 1
	release
	end

MossdeepCity_Movement_EggRunAway3West:
	emote_exclamation_mark
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MossdeepCity_EventScript_EggEncounter4North::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA4, MossdeepCity_Movement_EggRunAway4North
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA4
	setflag FLAG_TEMP_1A
	clearflag FLAG_TEMP_1B
	setvar VAR_TEMP_4, 4
	release
	end

MossdeepCity_Movement_EggRunAway4North:
	emote_exclamation_mark
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

MossdeepCity_EventScript_EggEncounter5South::
	lock
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA5, MossdeepCity_Movement_EggRunAway5South
	waitmovement 0
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	removeobject LOCALID_EGGNEGGMA5
	setflag FLAG_TEMP_1B
	clearflag FLAG_TEMP_17
	setvar VAR_TEMP_4, 0
	release
	end

MossdeepCity_Movement_EggRunAway5South:
	emote_exclamation_mark
	face_left
	delay_4
	face_right
	delay_16
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	jump_right
	step_end

MossdeepCity_EventScript_EggEncounter6FinalLeft::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerBlockLeft
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA6, MossdeepCity_Movement_EggBumpIntoPlayer
	waitmovement 0
	playse SE_WALL_HIT
	waitse
	msgbox MossdeepCity_Text_DroppedEgg, MSGBOX_DEFAULT
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	applymovement LOCALID_EGGNEGGMA6, MossdeepCity_Movement_EggFlee
	waitmovement 0
	removeobject LOCALID_EGGNEGGMA6
	setflag FLAG_TEMP_1C
	setflag FLAG_MOSSDEEP_EGG
	setvar VAR_TEMP_4, 6
	goto MossdeepCity_EventScript_ReceiveEgg
	release
	end

MossdeepCity_EventScript_ReceiveEgg::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EXEGGCUTE
	giveegg SPECIES_SQUEESHY
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MossdeepCity_EventScript_ReceiveEggParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MossdeepCity_EventScript_ReceiveEggPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

MossdeepCity_EventScript_ReceiveEggParty::
	call MossdeepCity_EventScript_ReceivedEggFanfare
	release
	end

MossdeepCity_EventScript_ReceiveEggPC::
	call MossdeepCity_EventScript_ReceivedEggFanfare
	call Common_EventScript_TransferredToPC
	release
	end

MossdeepCity_EventScript_ReceivedEggFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message MossdeepCity_Text_PlayerReceivedEgg
	waitmessage
	waitfanfare
	return

MossdeepCity_Movement_PlayerBlockLeft:
	walk_up
	walk_right
	face_up
	step_end

MossdeepCity_Movement_EggBumpIntoPlayer:
	emote_exclamation_mark
	face_down
	delay_16
	delay_16
	delay_16
	walk_fast_down
	walk_fast_down
	step_end

MossdeepCity_Movement_EggFlee:
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MossdeepCity_EventScript_EggEncounter6FinalRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerBlockRight
	playse SE_PIN
	applymovement LOCALID_EGGNEGGMA6, MossdeepCity_Movement_EggBumpIntoPlayer
	waitmovement 0
	playse SE_WALL_HIT
	waitse
	msgbox MossdeepCity_Text_DroppedEgg, MSGBOX_DEFAULT
	playmoncry SPECIES_EGGNEGGMA, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	applymovement LOCALID_EGGNEGGMA6, MossdeepCity_Movement_EggFlee
	waitmovement 0
	removeobject LOCALID_EGGNEGGMA6
	setflag FLAG_TEMP_1C
	setflag FLAG_MOSSDEEP_EGG
	setvar VAR_TEMP_4, 6
	goto MossdeepCity_EventScript_ReceiveEgg
	release
	end

MossdeepCity_Movement_PlayerBlockRight:
	walk_up
	face_up
	step_end

MossdeepCity_EventScript_ThicketTooThick::
	lock
	msgbox MossdeepCity_Text_ThicketTooThick, MSGBOX_AUTOCLOSE
	release
	end

MossdeepCity_EventScript_BrineyFastTravel::
	lock
	faceplayer
	speakername MossdeepCity_Text_NameBriney
	msgbox MossdeepCity_Text_WantToVoyage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MossdeepCity_EventScript_WarpToTidal
	msgbox MossdeepCity_Text_IllBeHere, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

MossdeepCity_EventScript_WarpToTidal::
	msgbox MossdeepCity_Text_BonVoyage, MSGBOX_DEFAULT
	speakername NULL
	warp MAP_SS_TIDAL_MID_TERIORS, 33, 4
	release
	end

MossdeepCity_EventScript_WallyBlackout::
	lock
	msgbox MossdeepCity_Text_YouFeelFaint, MSGBOX_DEFAULT
	closemessage
	delay 8
	warp MAP_WALLY_ARENA, 9, 24
	waitstate
	release
	end

MossdeepCity_EventScript_YandemicNoticed::
	lock
	setvar VAR_TEMP_9, 1
	call_if_lt VAR_NOTICED_BY_YANDEMIC, 4, MossdeepCity_EventScript_YandemicAddVar
	msgbox MossdeepCity_Text_YouFeelWatched, MSGBOX_AUTOCLOSE
	release
	end

MossdeepCity_EventScript_YandemicAddVar::
	addvar VAR_NOTICED_BY_YANDEMIC, 1
	return

MossdeepCity_EventScript_HintMonk::
	msgbox MossdeepCity_Text_HintMonk, MSGBOX_NPC
	end

MossdeepCity_EventScript_WestEntrance::
	msgbox MossdeepCity_Text_WestEntrance, MSGBOX_SIGN
	end

MossdeepCity_EventScript_EastEntrance::
	msgbox MossdeepCity_Text_EastEntrance, MSGBOX_SIGN
	end

MossdeepCity_EventScript_MossdeepCitySign::
	msgbox MossdeepCity_Text_MossdeepCitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_StevenHouseSign::
	msgbox MossdeepCity_Text_StevenHouseSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_MangrottoSign::
	msgbox MossdeepCity_Text_MangrottoSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_Mossdeeper1::
    msgbox MossdeepCity_Text_Mossdeeper1, MSGBOX_NPC
    end

MossdeepCity_EventScript_Mossdeeper2::
    msgbox MossdeepCity_Text_Mossdeeper2, MSGBOX_NPC
    end

MossdeepCity_EventScript_Mossdeeper3::
    msgbox MossdeepCity_Text_Mossdeeper3, MSGBOX_NPC
    end

MossdeepCity_EventScript_Mossdeeper4::
    msgbox MossdeepCity_Text_Mossdeeper4, MSGBOX_NPC
    end

MossdeepCity_EventScript_Mossdeeper5::
    msgbox MossdeepCity_Text_Mossdeeper5, MSGBOX_NPC
    end

MossdeepCity_EventScript_Mossdeeper6::
    msgbox MossdeepCity_Text_Mossdeeper6, MSGBOX_NPC
    end

MossdeepCity_EventScript_Mossdeeper7::
    msgbox MossdeepCity_Text_Mossdeeper7, MSGBOX_NPC
    end

MossdeepCity_Text_Mossdeeper1:
	.string "Seems like everyone I know wants\n"
	.string "to apply to be an astronaut!\l"
	.string "Not gonna lie... it sounds mega cool!$"

MossdeepCity_Text_Mossdeeper2:
	.string "The gym here used to be a double\n"
	.string "battle not too long ago. The\l"
	.string "current leader, Liza, would battle\l"
	.string "alongside her brother, Tate.\p"
	.string "He ended up leaving on a journey to\n"
	.string "find himself in the mountains.\l"
	.string "So, Liza fights alone...\l"
	.string "ironic, considering every other\l"
	.string "Hoenn gym is now a double battle.$"

MossdeepCity_Text_Mossdeeper3:
	.string "Do you invest any time in\n"
	.string "learning about erosion?\p"
	.string "Over thousands and thousands\n"
	.string "of years, water and ice will chisel\l"
	.string "out even the hardest of rocks.\p"
	.string "Perhaps, if the conditions are\n"
	.string "right, a rock can be carved into a\l"
	.string "perfect sculpture of a Pokemon\l"
	.string "by nothing but the waves.$"

MossdeepCity_Text_Mossdeeper4:
	.string "One of these days, I'll be attuned\n"
	.string "enough with my sixth sense that\l"
	.string "I can bend a spoon with my mind!\p"
	.string "The last guy I saw do that had his\n"
	.string "hair turn white. But it's a price\l"
	.string "I'm willing to pay!$"

MossdeepCity_Text_Mossdeeper5:
	.string "Seeking out a Good Rod, youngun'?\n"
	.string "Pal'a mine set up a dwellin' at\l"
	.string "Precipike Bluff. It's just north\l"
	.string "of the city. He may be willin'\l"
	.string "to give one out to ya.$"

MossdeepCity_Text_Mossdeeper6:
	.string "The mangrove trees of Mossdeep\n"
	.string "are so very resilient! Some of\l"
	.string "these plants have been around\l"
	.string "for centuries.$"

MossdeepCity_Text_Mossdeeper7:
	.string "Such an inconvenient ledge...\n"
	.string "Mossdeep City is RIGHT THERE!\l"
	.string "Would it kill them to carve out\l"
	.string "some simple stone stairs?$"

MossdeepCity_Text_MangrottoSign:
	.string "ENTRANCE TO MANGROTTO TUNNEL$"

MossdeepCity_Text_WestEntrance:
	.string "MOSSDEEP CITY - West Entrance\n"
	.string "Continue West for Cosmoss Bridge$"

MossdeepCity_Text_EastEntrance:
	.string "MOSSDEEP CITY - East Entrance\n"
	.string "Continue Northeast for\l"
	.string "Precipike Bluff$"

MossdeepCity_Text_MossdeepCitySign:
	.string "Mossdeep City is a PROUD sponsor\n"
	.string "of Hoenn's Space Program!\l"
	.string "One day, we will reach the moon!$"

MossdeepCity_Text_StevenHouseSign:
	.string "Steven Stone's Residence$"

MossdeepCity_Text_HintMonk:
	.string "Greetings and Good Fortune.\n"
	.string "{PLAYER}, it seems that Steven\l"
	.string "would like to speak with you.\l"
	.string "I would suggest heading\l"
	.string "to his home, post-haste.$"

MossdeepCity_Text_YouFeelWatched:
	.string "(You begin to notice that\n"
	.string "you are being intently watched...)$"

MossdeepCity_Text_NameBriney:
	.string "Cpt. Briney$"

MossdeepCity_Text_WantToVoyage:
	.string "Ahoy there {PLAYER}!\p"
	.string "The Tidal is docked and\n"
	.string "itching for another voyage.\p"
	.string "Will you be joining us?$"

MossdeepCity_Text_IllBeHere:
	.string "You're always welcome aboard!\n"
	.string "Have a good one.$"

MossdeepCity_Text_BonVoyage:
	.string "About time to haul anchor, then!$"

MossdeepCity_Text_DroppedEgg:
	.string "(The strange wild Pokémon dropped\n"
	.string "the egg it was holding!)$"

MossdeepCity_Text_PlayerReceivedEgg:
	.string "{PLAYER} received an Egg!$"

MossdeepCity_Text_ThicketTooThick:
	.string "(This thicket is too thick\n"
	.string "...et, to venture into.)$"

MossdeepCity_Text_HaveMudShot:
	.string "I love the feel of the beach\n"
	.string "beneath my feet!\p"
	.string "You know, certain kinds of mud have\n"
	.string "healing, soothing properties.\p"
	.string "Especially ones made by Pokémon!\p"
	.string "With this TM, you too can\n"
	.string "enjoy the smoothness of mud!$"

MossdeepCity_Text_GaveMudShot:
	.string "I have a mud bath appointment\n"
	.string "coming up soon...$"

MossdeepCity_Text_WantToSeeMonGrowl:
	.string "Grr... Rrrraaarghhh...\p"
	.string "(He's scowling and growling...)\p"
	.string "(Perhaps he wants you to...\n"
	.string "...growl... back??)$"

MossdeepCity_Text_HaveSnarl:
	.string "(You growl at the odd man.)\p"
	.string "GRRAHHRRAHHRGH!! GRRAROAGH!!\p"
	.string "(He hands you something...)$"

MossdeepCity_Text_NoGrowl:
	.string "(You feel intimidated by the\n"
	.string "snarling man...)$"

MossdeepCity_Text_GaveSnarl:
	.string "(You respect each others' turf.)$"

MossdeepCity_Text_MonkGreeting:
	.string "Greetings and Good Fortune.\p"
	.string "I am speaking to {PLAYER}, correct?\p"
	.string "A very special someone wishes\n"
	.string "to speak with you.\p"
	.string "Allow me to escort you…$"

MossdeepCity_Text_Gugumbir:
	.string "Please treat his dwellings with\n"
	.string "the same amount of respect\l"
	.string "as you would your own.$"

MossdeepCity_Text_YouFeelFaint:
	.string "(You are about to reach Steven's\n"
	.string "home when...)\p"
	.string "(The smell of... spider lilies...\n"
	.string "fills your... nostrils...)\p"
	.string "(Feeling...\n"
	.string "                ...faint...)$"
