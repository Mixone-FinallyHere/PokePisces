.set LOCALID_DRAKE, 2
.set LOCALID_YANDEMIC, 7
.set LOCALID_ROLAND, 23

NewSooto_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, NewSooto_OnLoad
	.byte 0

NewSooto_OnLoad:
	setflag FLAG_VISITED_SOOTOPOLIS_CITY
	call_if_ge VAR_NOTICED_BY_YANDEMIC, 5, NewSooto_EventScript_RemoveYandemic
	call_if_lt VAR_NEW_COO_STATE, 1, NewSooto_EventScript_RemoveDrake
	call_if_gt VAR_NEW_COO_STATE, 1, NewSooto_EventScript_RemoveDrakeAndBlocker
	call NewSooto_EventScript_RemoveRoland
	end

NewSooto_EventScript_RemoveYandemic::
	removeobject LOCALID_YANDEMIC
	setflag FLAG_TEMP_11
	setvar VAR_TEMP_4, 1
	return

NewSooto_EventScript_RemoveDrake::
	removeobject LOCALID_DRAKE
	setflag FLAG_TEMP_12
	return

NewSooto_EventScript_RemoveDrakeAndBlocker::
	removeobject LOCALID_DRAKE
	setflag FLAG_TEMP_12
	removeobject LOCALID_BLOCKER
	setflag FLAG_TEMP_13
	return

NewSooto_EventScript_RemoveRoland::
	removeobject LOCALID_ROLAND
	setflag FLAG_TEMP_17
	return

NewSooto_EventScript_DontGoInCave::
	lock
	msgbox NewSooto_Text_BestNotTo, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerGoAway
	waitmovement 0
	release
	end

NewSooto_Movement_PlayerGoAway:
	walk_down
	step_end

NewSooto_EventScript_TakePlayerToCave1::
	lock
	playse SE_PIN
	applymovement LOCALID_DRAKE, NewSooto_Movement_DrakeNoticeLeft
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerWalkToCave1
	waitmovement 0
	speakername NewSooto_Text_NameDrake
	msgbox NewSooto_Text_CheckOutTheCave, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerWalkToCave5
	waitmovement 0
	speakername NULL
	warp MAP_CAVE_OF_ORIGIN, 14, 4
	waitstate
	release
	end

NewSooto_Movement_DrakeNoticeLeft:
	emote_exclamation_mark
	face_left
	step_end

NewSooto_Movement_PlayerWalkToCave1:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	face_right
	step_end

NewSooto_Movement_PlayerWalkToCave5:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewSooto_EventScript_TakePlayerToCave2::
	lock
	playse SE_PIN
	applymovement LOCALID_DRAKE, NewSooto_Movement_DrakeNoticeLeft
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerWalkToCave2
	waitmovement 0
	speakername NewSooto_Text_NameDrake
	msgbox NewSooto_Text_CheckOutTheCave, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerWalkToCave5
	waitmovement 0
	speakername NULL
	warp MAP_CAVE_OF_ORIGIN, 14, 4
	waitstate
	release
	end

NewSooto_Movement_PlayerWalkToCave2:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	face_right
	step_end

NewSooto_EventScript_TakePlayerToCave3::
	lock
	playse SE_PIN
	applymovement LOCALID_DRAKE, NewSooto_Movement_DrakeNoticeRight
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerWalkToCave3
	waitmovement 0
	speakername NewSooto_Text_NameDrake
	msgbox NewSooto_Text_CheckOutTheCave, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerWalkToCave5
	waitmovement 0
	speakername NULL
	warp MAP_CAVE_OF_ORIGIN, 14, 4
	waitstate
	release
	end

NewSooto_Movement_DrakeNoticeRight:
	emote_exclamation_mark
	face_right
	delay_8
	delay_8
	delay_8
	face_left
	step_end

NewSooto_Movement_PlayerWalkToCave3:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_right
	step_end

NewSooto_EventScript_TakePlayerToCave4::
	lock
	playse SE_PIN
	applymovement LOCALID_DRAKE, NewSooto_Movement_DrakeNoticeRight
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerWalkToCave4
	waitmovement 0
	speakername NewSooto_Text_NameDrake
	msgbox NewSooto_Text_CheckOutTheCave, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerWalkToCave5
	waitmovement 0
	speakername NULL
	warp MAP_CAVE_OF_ORIGIN, 14, 4
	waitstate
	release
	end

NewSooto_Movement_PlayerWalkToCave4:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_right
	step_end

NewSooto_EventScript_PaperSeller::
    lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BLUNDER_POLICY, NewSooto_EventScript_NoMorePolicies
	showmoneybox 0, 0
	msgbox NewSooto_Text_WantAPaper, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewSooto_EventScript_CheckMoneyForBP
	closemessage
	hidemoneybox
	release
	end

NewSooto_EventScript_CheckMoneyForBP::
	checkmoney 1000
	goto_if_eq VAR_RESULT, FALSE, NewSooto_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 1000
	updatemoneybox
	delay 40
	hidemoneybox
	giveitem ITEM_BLUNDER_POLICY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_BLUNDER_POLICY
	msgbox NewSooto_Text_ThanksForBuying, MSGBOX_AUTOCLOSE
	release
	end

NewSooto_EventScript_NoMorePolicies::
    msgbox NewSooto_Text_NoMorePolicies, MSGBOX_AUTOCLOSE
    release
    end

NewSooto_EventScript_NotEnoughMoney::
	msgbox NewSooto_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

NewSooto_EventScript_Thief::
    lock
	faceplayer
	checkitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, TRUE, NewSooto_EventScript_GaveThief
	msgbox NewSooto_Text_FinnaCheckCovet, MSGBOX_DEFAULT
	checkpartynonhmmove MOVE_COVET
	goto_if_eq VAR_RESULT, PARTY_SIZE, NewSooto_EventScript_NoCovet
	msgbox NewSooto_Text_HereHaveThief, MSGBOX_DEFAULT
	giveitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

NewSooto_EventScript_GaveThief::
    msgbox NewSooto_Text_GaveThief, MSGBOX_AUTOCLOSE
    release
    end

NewSooto_EventScript_NoCovet::
	msgbox NewSooto_Text_NoCovet, MSGBOX_AUTOCLOSE
    release
    end

NewSooto_EventScript_FloatStone::
    lock
	faceplayer
	goto_if_set FLAG_RECEIVED_FLOAT_STONE, NewSooto_EventScript_GaveFloatStone
	getcaughtmon SPECIES_BALBYRN
	goto_if_eq VAR_RESULT, TRUE, NewSooto_EventScript_GiveFloatStone
	getcaughtmon SPECIES_SAINTISOW
	goto_if_eq VAR_RESULT, TRUE, NewSooto_EventScript_GiveFloatStone
	getcaughtmon SPECIES_UMBRAT
	goto_if_eq VAR_RESULT, TRUE, NewSooto_EventScript_GiveFloatStone
	getcaughtmon SPECIES_DRAKULARK
	goto_if_eq VAR_RESULT, TRUE, NewSooto_EventScript_GiveFloatStone
	msgbox NewSooto_Text_WantToSeeFlyingMon, MSGBOX_AUTOCLOSE
	release
	end

NewSooto_EventScript_GiveFloatStone::
	msgbox NewSooto_Text_FloatStone, MSGBOX_DEFAULT
	giveitem ITEM_FLOAT_STONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FLOAT_STONE
	release
	end

NewSooto_EventScript_GaveFloatStone::
    msgbox NewSooto_Text_GaveFloatStone, MSGBOX_AUTOCLOSE
    release
    end

NewSooto_EventScript_OzoneRoadblockAhead::
    msgbox NewSooto_Text_OzoneRoadblockAhead, MSGBOX_NPC
	end

NewSooto_EventScript_YandemicNoticed::
	lock
	setvar VAR_TEMP_4, 1
	call_if_lt VAR_NOTICED_BY_YANDEMIC, 4, NewSooto_EventScript_YandemicAddVar
	msgbox NewSooto_Text_YouFeelWatched, MSGBOX_AUTOCLOSE
	release
	end

NewSooto_EventScript_YandemicAddVar::
	addvar VAR_NOTICED_BY_YANDEMIC, 1
	return

NewSooto_EventScript_NaturalLandscapeBoy::
	msgbox NewSooto_Text_NaturalLandscapeBoy, MSGBOX_NPC
	end

NewSooto_EventScript_UsedToBeExclusive::
	msgbox NewSooto_Text_UsedToBeExclusive, MSGBOX_NPC
	end

NewSooto_EventScript_LegendaryKid::
	msgbox NewSooto_Text_LegendaryKid, MSGBOX_NPC
	end

NewSooto_EventScript_CaveOfOriginImportantGirl::
	msgbox NewSooto_Text_CaveOfOriginImportantGirl, MSGBOX_NPC
	end

NewSooto_EventScript_JuanFangirl::
	msgbox NewSooto_Text_JuanFangirl, MSGBOX_NPC
	end

NewSooto_EventScript_LivedHereManyYears::
	msgbox NewSooto_Text_LivedHereManyYears, MSGBOX_NPC
	end

NewSooto_EventScript_JuanEntrepeneur::
	msgbox NewSooto_Text_JuanEntrepeneur, MSGBOX_NPC
	end

NewSooto_EventScript_CastleHiker::
	msgbox NewSooto_Text_CastleHiker, MSGBOX_NPC
	end

NewSooto_EventScript_YoungCoupleGirl::
	lock
	msgbox NewSooto_Text_YoungCoupleGirl, MSGBOX_AUTOCLOSE
	release
	end

NewSooto_EventScript_YoungCoupleBoy::
	lock
	msgbox NewSooto_Text_YoungCoupleBoy, MSGBOX_AUTOCLOSE
	release
	end

NewSooto_EventScript_SebastianFriend::
	msgbox NewSooto_Text_SebastianFriend, MSGBOX_NPC
	end

NewSooto_EventScript_MangrottoBlocker::
	msgbox NewSooto_Text_MangrottoBlocker, MSGBOX_NPC
	end

NewSooto_EventScript_SootopolisSign::
	msgbox NewSooto_Text_SootopolisSign, MSGBOX_SIGN
	end

NewSooto_EventScript_NoSwimmingInCratersSign::
	msgbox NewSooto_Text_NoSwimmingInCratersSign, MSGBOX_SIGN
	end

NewSooto_EventScript_CaveOfOriginSign::
	msgbox NewSooto_Text_CaveOfOriginSign, MSGBOX_SIGN
	end

NewSooto_EventScript_MangrottoTunnelSign::
	msgbox NewSooto_Text_MangrottoTunnelSign, MSGBOX_SIGN
	end

NewSooto_EventScript_JuancoreRestaurantSign::
	msgbox NewSooto_Text_JuancoreRestaurantSign, MSGBOX_SIGN
	end

NewSooto_EventScript_CosmossBridgeSign::
	msgbox NewSooto_Text_CosmossBridgeSign, MSGBOX_SIGN
	end

NewSooto_EventScript_RolandEncounter1::
	lock
	setvar VAR_TEMP_6, 1
	goto_if_eq VAR_ROLAND_STATE, 0, NewSooto_EventScript_RolandAdvice1
	goto_if_eq VAR_ROLAND_STATE, 2, NewSooto_EventScript_RolandYouLost1
	release
	end

NewSooto_EventScript_RolandAdvice1::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland1
	waitmovement 0
	call NewSooto_EventScript_RolandAdviceBulk
	release
	end

NewSooto_EventScript_RolandYouLost1::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland1
	waitmovement 0
	call NewSooto_EventScript_RolandYouLostBulk
	release
	end

NewSooto_Movement_PlayerMeetRoland1:
	walk_down
	walk_right
	walk_right
	face_up
	step_end

NewSooto_EventScript_RolandEncounter2::
	lock
	setvar VAR_TEMP_6, 1
	goto_if_eq VAR_ROLAND_STATE, 0, NewSooto_EventScript_RolandAdvice2
	goto_if_eq VAR_ROLAND_STATE, 2, NewSooto_EventScript_RolandYouLost2
	release
	end

NewSooto_EventScript_RolandAdvice2::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland2
	waitmovement 0
	call NewSooto_EventScript_RolandAdviceBulk
	release
	end

NewSooto_EventScript_RolandYouLost2::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland2
	waitmovement 0
	call NewSooto_EventScript_RolandYouLostBulk
	release
	end

NewSooto_Movement_PlayerMeetRoland2:
	walk_right
	walk_right
	face_up
	step_end

NewSooto_EventScript_RolandEncounter3::
	lock
	setvar VAR_TEMP_6, 1
	goto_if_eq VAR_ROLAND_STATE, 0, NewSooto_EventScript_RolandAdvice3
	goto_if_eq VAR_ROLAND_STATE, 2, NewSooto_EventScript_RolandYouLost3
	release
	end

NewSooto_EventScript_RolandAdvice3::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland3
	waitmovement 0
	call NewSooto_EventScript_RolandAdviceBulk
	release
	end

NewSooto_EventScript_RolandYouLost3::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland3
	waitmovement 0
	call NewSooto_EventScript_RolandYouLostBulk
	release
	end

NewSooto_Movement_PlayerMeetRoland3:
	walk_up
	walk_right
	walk_right
	face_up
	step_end

NewSooto_EventScript_RolandEncounter4::
	lock
	setvar VAR_TEMP_6, 1
	goto_if_eq VAR_ROLAND_STATE, 0, NewSooto_EventScript_RolandAdvice4
	goto_if_eq VAR_ROLAND_STATE, 2, NewSooto_EventScript_RolandYouLost4
	release
	end

NewSooto_EventScript_RolandAdvice4::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland4
	waitmovement 0
	call NewSooto_EventScript_RolandAdviceBulk
	release
	end

NewSooto_EventScript_RolandYouLost4::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland4
	waitmovement 0
	call NewSooto_EventScript_RolandYouLostBulk
	release
	end

NewSooto_Movement_PlayerMeetRoland4:
	walk_down
	walk_left
	walk_left
	face_up
	step_end

NewSooto_EventScript_RolandEncounter5::
	lock
	setvar VAR_TEMP_6, 1
	goto_if_eq VAR_ROLAND_STATE, 0, NewSooto_EventScript_RolandAdvice5
	goto_if_eq VAR_ROLAND_STATE, 2, NewSooto_EventScript_RolandYouLost5
	release
	end

NewSooto_EventScript_RolandAdvice5::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland5
	waitmovement 0
	call NewSooto_EventScript_RolandAdviceBulk
	release
	end

NewSooto_EventScript_RolandYouLost5::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland5
	waitmovement 0
	call NewSooto_EventScript_RolandYouLostBulk
	release
	end

NewSooto_Movement_PlayerMeetRoland5:
	walk_left
	walk_left
	face_up
	step_end

NewSooto_EventScript_RolandEncounter6::
	lock
	setvar VAR_TEMP_6, 1
	goto_if_eq VAR_ROLAND_STATE, 0, NewSooto_EventScript_RolandAdvice6
	goto_if_eq VAR_ROLAND_STATE, 2, NewSooto_EventScript_RolandYouLost6
	release
	end

NewSooto_EventScript_RolandAdvice6::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland6
	waitmovement 0
	call NewSooto_EventScript_RolandAdviceBulk
	release
	end

NewSooto_EventScript_RolandYouLost6::
	opendoor 41, 15
	waitdooranim
	clearflag FLAG_TEMP_17
	addobject LOCALID_ROLAND
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandOutOfDoor
	waitmovement 0
	closedoor 41, 15
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, NewSooto_Movement_PlayerMeetRoland6
	waitmovement 0
	call NewSooto_EventScript_RolandYouLostBulk
	release
	end

NewSooto_Movement_PlayerMeetRoland6:
	walk_up
	walk_left
	walk_left
	face_up
	step_end

NewSooto_EventScript_RolandAdviceBulk::
	msgbox NewSooto_Text_AboutTheGym, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_RARE_CANDY
	closemessage
	msgbox NewSooto_Text_AboutRareCandies, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ROLAND_STATE, 1
	delay 4
	turnobject LOCALID_ROLAND, DIR_NORTH
	opendoor 41, 15
	waitdooranim
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandLeaves
	waitmovement 0
	removeobject LOCALID_ROLAND
	setflag FLAG_TEMP_17
	closedoor 41, 15
	waitdooranim
	return

NewSooto_EventScript_RolandYouLostBulk::
	msgbox NewSooto_Text_TryAndPrepare, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_RARE_CANDY, 3
	closemessage
	giveitem ITEM_REVIVE, 1
	closemessage
	msgbox NewSooto_Text_YouCanDoIt, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ROLAND_STATE, 1
	delay 4
	turnobject LOCALID_ROLAND, DIR_NORTH
	opendoor 41, 15
	waitdooranim
	applymovement LOCALID_ROLAND, NewSooto_Movement_RolandLeaves
	waitmovement 0
	removeobject LOCALID_ROLAND
	setflag FLAG_TEMP_17
	closedoor 41, 15
	waitdooranim
	return

NewSooto_Movement_RolandOutOfDoor:
	walk_down
	step_end

NewSooto_Movement_RolandLeaves:
	walk_up
	step_end

NewSooto_Text_YouFeelWatched:
	.string "(You begin to notice that\n"
	.string "you are being intently watched...)$"

NewSooto_Text_NameDrake:
	.string "Drake$"

NewSooto_Text_OzoneRoadblockAhead:
	.string "Looking to cross the bridge?\p"
	.string "Outta luck; there's a Team Ozone\n"
	.string "blockade up ahead.$"

NewSooto_Text_WantToSeeFlyingMon:
	.string "I am doing important research\n"
	.string "on Hoenn's atmosphere on behalf\l"
	.string "of Team Ozone.\p"
	.string "If you can show me a Flying type\n"
	.string "Pokémon in your dex, it\l"
	.string "could potentially help me fill\l"
	.string "in some blanks.$"

NewSooto_Text_FloatStone:
	.string "Let me see your Pokédex for\n"
	.string "a quick second...\p"
	.string "Ah! You have caught at least\n"
	.string "one Flying type! Let me just\l"
	.string "jot down some notes...\p"
	.string "...There. Now, in exchange, I'd\n"
	.string "Like you to have this odd pebble\l"
	.string "I've been studying.$"

NewSooto_Text_GaveFloatStone:
	.string "Utilizing the flight pattern of\n"
	.string "the Pokémon you showed me, I've\l"
	.string "been hard at work developing\l"
	.string "revolutionary drone tech!$"

NewSooto_Text_FinnaCheckCovet:
	.string "Ey! No snitchin'! I'm scopin'\n"
	.string "out this property... for, uh,\l"
	.string "tax purposes.\p"
	.string "Look, I ain't yappin' on with\n"
	.string "a kid who don't know nothin'\l"
	.string "about my trade.\p"
	.string "Now, if one of them Pokémon on\n"
	.string "ya knew Covet, maybe I'd\l"
	.string "sing a different tone.$"

NewSooto_Text_HereHaveThief:
	.string "Heh-heh-heh...\p"
	.string "So ya DO have a knack for\n"
	.string "stealin', kid...\p"
	.string "(He pulls a disc from his pocket.)\p"
	.string "This 'ere? My favorite move.\n"
	.string "It's basically like Covet, but\l"
	.string "for Dark type 'mons.\p"
	.string "The ol' five finger discount!$"

NewSooto_Text_GaveThief:
	.string "I should hightail it on\n"
	.string "outta here soon, kid.\l"
	.string "Keep usin' Thief out there; some\l"
	.string "of them 'mons are carrying\l"
	.string "valuable goodies out there!$"

NewSooto_Text_NoCovet:
	.string "So, scram!$"

NewSooto_Text_CheckOutTheCave:
	.string "Hurrumph!\n"
	.string "If it isn't that {PLAYER} fellow.\p"
	.string "I hope you have been faring well.\p"
	.string "What begets my audience in Sootopolis?…\n"
	.string "The Legends I had discussed with you\l"
	.string "aboard the Tidal, of course.\p"
	.string "This borough has seen many an\n"
	.string "encounter with the divine and\l"
	.string "powerful, after all.\p"
	.string "You seem interested, my friend.\p"
	.string "Head forth into the Cave of Origin.\p"
	.string "You will meet a man who bore witness\n"
	.string "to the clash between the Behemoth\l"
	.string "and the Leviathan…\p"
	.string "I just finished up conversing with the\n"
	.string "fellow, I believe it will\l"
	.string "pique your curiosity.$"

NewSooto_Text_WantAPaper:
	.string "Papers! Papers!\n"
	.string "Get'cha mornin' papers here!\p"
	.string "Hey! I can tell ya wanna paper.\n"
	.string "How's ¥1000 sound?\l"
	.string "It's a great deal!$"

NewSooto_Text_ThanksForBuying:
	.string "Alrighty!\p"
	.string "(The Paper Boy shuffles\n"
	.string "through his pack.)\p"
	.string "Ah, here's one'a the best!$"

NewSooto_Text_NoMorePolicies:
	.string "Hmm? Nah, I ain't got no news papers.\p"
	.string "I got, uh… let's see here…\p"
	.string "Old tax return…\n"
	.string "condemned buildin' notice…\l"
	.string "D- math test…$"

NewSooto_Text_NotEnoughMoney:
	.string "Ah, maybe next time.\n"
	.string "Won't nab a better paper anywhere else!$"

NewSooto_Text_BestNotTo:
	.string "(Looks like an intimidating cave.\n"
	.string "...best to wait until you're\l"
	.string "a bit stronger.)$"

NewSooto_Text_NaturalLandscapeBoy:
	.string "Sootopolis is quite a\n"
	.string "beautiful natural landscape, huh?\l"
	.string "Amazing how an event that caused\l"
	.string "so much destruction resulted\l"
	.string "in so much life years later.$"

NewSooto_Text_UsedToBeExclusive:
	.string "I somewhat missed the days when\n"
	.string "Sootopolis City was more exclusive.\p"
	.string "With all these bridges getting\n"
	.string "built, we've drawn in some\l"
	.string "increasing tourism.$"

NewSooto_Text_LegendaryKid:
	.string "My paw told me that some\n"
	.string "real big animals made those\l"
	.string "rocks and holes in the lake!\p"
	.string "I wanna see the big\n"
	.string "strong animals!$"

NewSooto_Text_CaveOfOriginImportantGirl:
	.string "The Cave of Origin in the center\n"
	.string "of the city is protected as\l"
	.string "a place of worship.\l"
	.string "I'm not allowed in there,\l"
	.string "but that just makes me want in\l"
	.string "even more...!$"

NewSooto_Text_JuanFangirl:
	.string "My gosh, Juan is just\n"
	.string "THE dreamiest! He's by far\l"
	.string "the most suave of the\l"
	.string "gym leaders...!\p"
	.string "He puts on a one-man show\n"
	.string "once a week. He's a singer,\l"
	.string "comedian, debater, the whole\l"
	.string "nine yards. Such a talented\l"
	.string "catch of a man...!$"

NewSooto_Text_LivedHereManyYears:
	.string "Despite being an island, the water\n"
	.string "in the caldera is fresh and warm.\l"
	.string "The local water in other\l"
	.string "cities doesn't quite match up.\p"
	.string "I couldn't have picked a\n"
	.string "better locale to retire!$"

NewSooto_Text_JuanEntrepeneur:
	.string "Juan is a self-made man, you know.\n"
	.string "The city loved to boast about him.\l"
	.string "Wallace, a former Champion, also\l"
	.string "hails from Sootopolis.\l"
	.string "Stars here are just\l"
	.string "born differently!$"

NewSooto_Text_CastleHiker:
	.string "This city's great for the legs!\n"
	.string "So many stairs!\p"
	.string "Been wantin' to hike up to that\n"
	.string "there old castle, but the rocks\l"
	.string "are too steep to walk up.\l"
	.string "Gotta be some better way\l"
	.string "to get on up there...$"

NewSooto_Text_YoungCoupleGirl:
	.string "I'm excited to have front\n"
	.string "row seats for Juan's next\l"
	.string "performance! We're going\l"
	.string "to have a splendid time!$"

NewSooto_Text_YoungCoupleBoy:
	.string "My wallet is thick enough\n"
	.string "to keep affording show tickets,\l"
	.string "but that Juan is charging\l"
	.string "ridiculous prices...$"

NewSooto_Text_SebastianFriend:
	.string "Juan's family butler Sebastian\n"
	.string "is an old friend of mine.\l"
	.string "That man is not very assertive,\l"
	.string "but he has more innate talent\l"
	.string "than Juan could ever hope to boast.\p"
	.string "He seems content to stay\n"
	.string "in the background, however.$"

NewSooto_Text_MangrottoBlocker:
	.string "Sorry, young one.\n"
	.string "There is a worship ceremony\l"
	.string "being carried out in the\l"
	.string "Cave of Origin right now.\l"
	.string "The surrounding cave system\l"
	.string "must be clear so there is\l"
	.string "minimal interfering noise.\p"
	.string "It won't be too much longer.\n"
	.string "Why not attend the show or\l"
	.string "eat at the restaurant?$"

NewSooto_Text_SootopolisSign:
	.string "SOOTOPOLIS CITY\n"
	.string "The mystical place\l"
	.string "where history slumbers.$"

NewSooto_Text_NoSwimmingInCratersSign:
	.string "CITY NOTICE\n"
	.string "No recreational swimming\l"
	.string "in the central crater!\l"
	.string "It is a historic site.$"

NewSooto_Text_CaveOfOriginSign:
	.string "THE CAVE OF ORIGIN$"

NewSooto_Text_MangrottoTunnelSign:
	.string "NORTH - MANGROTTO TUNNEL\n"
	.string "Closed during worship hours.$"

NewSooto_Text_JuancoreRestaurantSign:
	.string "Juan-Core Cuisine!\n"
	.string "OPEN$"

NewSooto_Text_CosmossBridgeSign:
	.string "EAST - COSMOSS BRIDGE,\n"
	.string "COSMOSS SPACE CENTER$"

NewSooto_Text_AboutTheGym:
	.string "Oh, hey there! It's you!\n"
	.string "That aspiring gym challenger\l"
	.string "from the S.S. Tidal!\l"
	.string "Good to see you again.\p"
	.string "I see you're making good on\n"
	.string "your desires to re-do the challenge!\l"
	.string "That's pretty commendable.\p"
	.string "Here's a few things you may want\n"
	.string "to know about the new gyms.\l"
	.string "First, is that they are all\l"
	.string "gauntlets now. As in, once you\l"
	.string "start the gym, you won't be able\l"
	.string "to leave until you either complete\l"
	.string "it, or you have a full party wipe.\p"
	.string "The trainers inside will rematch you\n"
	.string "each time you re-challenge a gym.\l"
	.string "So make sure you're well prepared\l"
	.string "for it all before going in!\p"
	.string "It tends to be easier to prepare\n"
	.string "your team once you have reached a\l"
	.string "city with a gym in it. Your Pokemon\l"
	.string "will feel a deep resolve to beat it,\l"
	.string "and will gain experience at a much\l"
	.string "faster rate until you get the badge!\p"
	.string "Not that they can go above a certain\n"
	.string "level threshold until you obtain\l"
	.string "said badge, but still, this should\l"
	.string "help getting lower leveled team\l"
	.string "members all caught up.\p"
	.string "Speaking of helping low leveled\n"
	.string "Pokemon, have one of these!$"

NewSooto_Text_AboutRareCandies:
	.string "Rare Candies are a good way to\n"
	.string "level without battling. They don't\l"
	.string "let your Pokemon go above the\l"
	.string "level threshold for a gym, but they\l"
	.string "certainly help with catch-up.\p"
	.string "One last thing is that losing in\n"
	.string "the gym is not so bad! You get to\l"
	.string "learn a lot from the loss and\l"
	.string "re-apply your knowledge.\l"
	.string "Gym trainers and the leaders also\l"
	.string "don't take your money when\l"
	.string "you lose to them.\p"
	.string "Give it your best shot, challenger!\n"
	.string "I'll be in the audience of Juan's\l"
	.string "show. I hope to be impressed!$"

NewSooto_Text_TryAndPrepare:
	.string "Hey there! I saw your loss\n"
	.string "in the gym fights back there.\l"
	.string "Remember what I told you!\l"
	.string "Use the opportunity to learn\l"
	.string "and re-strategize. Don't just throw\l"
	.string "in the towel!\p"
	.string "Here, have a few more gifts from\n"
	.string "me to maybe ease your time\l"
	.string "in the gym.$"

NewSooto_Text_YouCanDoIt:
	.string "You can do it, challenger!\n"
	.string "I believe in your abilities.\l"
	.string "Give it another good try!$"
