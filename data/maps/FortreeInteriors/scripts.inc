.set LOCALID_YANDEMIC, 2

FortreeInteriors_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FortreeInteriors_OnLoad
	.byte 0

FortreeInteriors_OnLoad:
	call FortreeInteriors_EventScript_RemoveYandemic
	end

FortreeInteriors_EventScript_RemoveYandemic::
	removeobject LOCALID_YANDEMIC
	setflag FLAG_TEMP_11
	return

FortreeInteriors_EventScript_YandemicEncounterNorth1::
	lock
	delay 4
	clearflag FLAG_TEMP_11
	addobject LOCALID_YANDEMIC
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playse SE_EXIT
	waitse
	applymovement LOCALID_YANDEMIC, FortreeInteriors_Movement_YandemicEncounterNorth1
	waitmovement 0
	goto FortreeInteriors_EventScript_YandemicJoinsTheParty
	release
	end

FortreeInteriors_Movement_YandemicEncounterNorth1:
	walk_left
	face_up
	step_end

FortreeInteriors_EventScript_YandemicEncounterNorth2::
	lock
	delay 4
	clearflag FLAG_TEMP_11
	addobject LOCALID_YANDEMIC
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playse SE_EXIT
	waitse
	goto FortreeInteriors_EventScript_YandemicJoinsTheParty
	release
	end

FortreeInteriors_EventScript_YandemicEncounterWest1::
	lock
	delay 4
	clearflag FLAG_TEMP_11
	addobject LOCALID_YANDEMIC
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_EXIT
	waitse
	turnobject LOCALID_YANDEMIC, DIR_WEST
	delay 4
	goto FortreeInteriors_EventScript_YandemicJoinsTheParty
	release
	end

FortreeInteriors_EventScript_YandemicJoinsTheParty::
	playmoncry SPECIES_YANDEMIC, CRY_MODE_NORMAL
	waitmoncry
	msgbox FortreeInteriors_Text_YandemicWantsToBeWithYou, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_YANDEMIC
	givemon SPECIES_YANDEMIC, 31
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, FortreeInteriors_EventScript_ReceiveYandemicParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, FortreeInteriors_EventScript_ReceiveYandemicPC
	goto Common_EventScript_NoMoreRoomForPokemon
	goto FortreeInteriors_EventScript_WatchedForever
	release
	end

FortreeInteriors_EventScript_ReceiveYandemicParty::
	call FortreeInteriors_EventScript_ReceivedYandemicFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeInteriors_EventScript_WatchedForever
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto FortreeInteriors_EventScript_WatchedForever
	release
	end

FortreeInteriors_EventScript_ReceiveYandemicPC::
	call FortreeInteriors_EventScript_ReceivedYandemicFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeInteriors_EventScript_SendYandemicToPC
	call Common_EventScript_NameReceivedBoxMon
	goto FortreeInteriors_EventScript_SendYandemicToPC
	release
	end

FortreeInteriors_EventScript_SendYandemicToPC::
	call Common_EventScript_TransferredToPC
	goto FortreeInteriors_EventScript_WatchedForever
	release
	end

FortreeInteriors_EventScript_ReceivedYandemicFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message FortreeInteriors_Text_PlayerReceivedYandemic
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_YANDEMIC
	return

FortreeInteriors_EventScript_WatchedForever::
	removeobject LOCALID_YANDEMIC
	setflag FLAG_TEMP_11
	delay 4
	setvar VAR_NOTICED_BY_YANDEMIC, 5
	msgbox FortreeInteriors_Text_WatchedForever, MSGBOX_AUTOCLOSE
	release
	end

FortreeInteriors_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_BOOZARD_TRADE_COMPLETED, FortreeInteriors_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_BOOZARD
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox FortreeInteriors_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeInteriors_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FortreeInteriors_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, FortreeInteriors_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox FortreeInteriors_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_BOOZARD_TRADE_COMPLETED
	release
	end

FortreeInteriors_EventScript_DeclineTrade::
	msgbox FortreeInteriors_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

FortreeInteriors_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeInteriors_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

FortreeInteriors_EventScript_TradeCompleted::
	msgbox FortreeInteriors_Text_ThanksForTrading, MSGBOX_DEFAULT
	release
	end

FortreeInteriors_EventScript_ChoiceItems::
	lock
	faceplayer
	goto_if_set FLAG_CHOICE_ITEM_1, FortreeInteriors_EventScript_MadeYourChoice
	msgbox FortreeInteriors_Text_PickAChoiceItem, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_CHOICE_ITEM_PICK, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	goto_if_eq VAR_TEMP_1, 0, FortreeInteriors_EventScript_GiveChoiceBand
	goto_if_eq VAR_TEMP_1, 1, FortreeInteriors_EventScript_GiveChoiceSpecs
	goto_if_eq VAR_TEMP_1, 2, FortreeInteriors_EventScript_GiveChoiceScarf
	msgbox FortreeInteriors_Text_ChoiceParalysis, MSGBOX_DEFAULT
	closemessage
	release
	end

FortreeInteriors_EventScript_GiveChoiceBand::
	closemessage
	giveitem ITEM_CHOICE_BAND
	closemessage
	setflag FLAG_CHOICE_ITEM_1
	msgbox FortreeInteriors_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

FortreeInteriors_EventScript_GiveChoiceSpecs::
	closemessage
	giveitem ITEM_CHOICE_SPECS
	closemessage
	setflag FLAG_CHOICE_ITEM_1
	msgbox FortreeInteriors_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

FortreeInteriors_EventScript_GiveChoiceScarf::
	closemessage
	giveitem ITEM_CHOICE_SCARF
	closemessage
	setflag FLAG_CHOICE_ITEM_1
	msgbox FortreeInteriors_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

FortreeInteriors_EventScript_MadeYourChoice::
	msgbox FortreeInteriors_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

FortreeInteriors_Text_PickAChoiceItem:
	.string "Sometimes in life, you must make\n"
	.string "hard choices! You cannot just\l"
	.string "get everything you would like.\p"
	.string "I propose a choice to YOU,\n"
	.string "stranger. I am in possession of\l"
	.string "3 of the Choice items.\l"
	.string "The Band, for Attack.\l"
	.string "The Specs, for Special Attack.\l"
	.string "The Scarf, for Speed.\p"
	.string "You may have one...\n"
	.string "and ONLY one...!\p"
	.string "It is up to you which you get!\n$"

FortreeInteriors_Text_ChoiceParalysis:
	.string "You must have choice paralysis!\n"
	.string "How very weak!$"

FortreeInteriors_Text_MadeYourChoice:
	.string "You have now made your choice!\n"
	.string "And you must live with that.$"

FortreeInteriors_Text_IllTradeIfYouWant:
	.string "I'll trade you my {STR_VAR_2} for\n"
	.string "a {STR_VAR_1} if you want.$"

FortreeInteriors_Text_PleaseBeGoodToMyPokemon:
	.string "Please be good to my POKéMON.$"

FortreeInteriors_Text_DoesntLookLikeMonToMe:
	.string "Huh? That doesn't look anything like\n"
	.string "a {STR_VAR_1} to me.$"

FortreeInteriors_Text_YouDontWantToThatsOkay:
	.string "Oh, if you don't want to, that's okay.$"

FortreeInteriors_Text_ThanksForTrading:
	.string "Thanks for the trade.$"

FortreeInteriors_Text_YandemicWantsToBeWithYou:
	.string "(It's that Pokemon that has\n"
	.string "been following you...)\p"
	.string "(It seems to yearn to be\n"
	.string "with you on your journey.)$"

FortreeInteriors_Text_PlayerReceivedYandemic:
	.string "{PLAYER} received a Yandemic!$"

FortreeInteriors_Text_WatchedForever:
	.string "(You feel as if Yandemic\n"
	.string "will be watching you...\l"
	.string "forever...)$"
