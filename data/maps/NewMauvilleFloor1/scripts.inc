.set LOCALID_P_MAN, 4
.set LOCALID_RYDEL_GUARD, 13

NewMauvilleFloor1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, NewMauvilleFloor1_OnLoad
	.byte 0

NewMauvilleFloor1_OnLoad:
	call_if_gt VAR_OLD_GUYS_STATE, 0, NewMauvilleFloor1_EventScript_RemovePowerlessMan
	call_if_lt VAR_OLD_GUYS_STATE, 6, NewMauvilleFloor1_EventScript_RemoveRydelGuard
	call_if_gt VAR_OLD_GUYS_STATE, 6, NewMauvilleFloor1_EventScript_RemoveRydelGuard
	call_if_lt VAR_OLD_GUYS_STATE, 17, NewMauvilleFloor1_EventScript_CloseElevator
	end

NewMauvilleFloor1_EventScript_RemovePowerlessMan::
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	return

NewMauvilleFloor1_EventScript_RemoveRydelGuard::
	removeobject LOCALID_RYDEL_GUARD
	setflag FLAG_TEMP_12
	return

NewMauvilleFloor1_EventScript_CloseElevator::
	setmetatile 46, 2, METATILE_Shop_MaintenanceDoorLocked, TRUE
	special DrawWholeMapView
	return

NewMauvilleFloor1_EventScript_PowerlessManTrigger1::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, NewMauvilleFloor1_Movement_PlayerGetIntoPos1
	goto NewMauvilleFloor1_EventScript_PowerlessManEvent
	releaseall
	end

NewMauvilleFloor1_Movement_PlayerGetIntoPos1:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	step_end

NewMauvilleFloor1_EventScript_PowerlessManTrigger2::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, NewMauvilleFloor1_Movement_PlayerGetIntoPos2
	goto NewMauvilleFloor1_EventScript_PowerlessManEvent
	releaseall
	end

NewMauvilleFloor1_Movement_PlayerGetIntoPos2:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

NewMauvilleFloor1_EventScript_PowerlessManTrigger3::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, NewMauvilleFloor1_Movement_PlayerGetIntoPos3
	goto NewMauvilleFloor1_EventScript_PowerlessManEvent
	releaseall
	end

NewMauvilleFloor1_Movement_PlayerGetIntoPos3:
	walk_right
	walk_right
	walk_right
	face_down
	step_end

NewMauvilleFloor1_EventScript_PowerlessManEvent::
	applymovement LOCALID_P_MAN, NewMauvilleFloor1_Movement_PManPassby
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_P_MAN, NewMauvilleFloor1_Movement_PManNotice
	waitmovement 0
	msgbox NewMauvilleFloor1_Text_ItsYouFromTheTidal, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, NewMauvilleFloor1_Movement_PlayerJoinUp
	applymovement LOCALID_P_MAN, NewMauvilleFloor1_Movement_PManJoinUp
	speakername NewMauvilleFloor1_Text_NameKizuna
	msgbox NewMauvilleFloor1_Text_AboutWattsonAndMauville, MSGBOX_DEFAULT
	speakername NULL
	closemessage
	applymovement LOCALID_P_MAN, NewMauvilleFloor1_Movement_PManGoToElevator
	waitmovement 0
	opendoor 26, 2
	waitdooranim
	applymovement LOCALID_P_MAN, NewMauvilleFloor1_Movement_PManEntersElevator
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	closedoor 26, 2
	waitdooranim
	setflag FLAG_VISITED_MAUVILLE_CITY
	setvar VAR_OLD_GUYS_STATE, 1
	releaseall
	end

NewMauvilleFloor1_Movement_PManPassby:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewMauvilleFloor1_Movement_PManNotice:
	emote_exclamation_mark
	delay_16
	delay_16
	face_down
	step_end

NewMauvilleFloor1_Movement_PlayerJoinUp:
	walk_up
	step_end

NewMauvilleFloor1_Movement_PManJoinUp:
	walk_right
	walk_down
	step_end

NewMauvilleFloor1_Movement_PManGoToElevator:
	walk_left
	walk_up
	step_end

NewMauvilleFloor1_Movement_PManEntersElevator:
	walk_up
	step_end

NewMauvilleFloor1_EventScript_Roy::
    trainerbattle_single TRAINER_P_ROY, NewMauvilleFloor1_Text_RoyIntro, NewMauvilleFloor1_Text_RoyDefeated
    msgbox NewMauvilleFloor1_Text_RoyPostBattle, MSGBOX_AUTOCLOSE
    end

NewMauvilleFloor1_EventScript_McKayleigh::
    trainerbattle_single TRAINER_P_MCKAYLEIGH, NewMauvilleFloor1_Text_McKayleighIntro, NewMauvilleFloor1_Text_McKayleighDefeated
    msgbox NewMauvilleFloor1_Text_McKayleighPostBattle, MSGBOX_AUTOCLOSE
    end

NewMauvilleFloor1_EventScript_Aiden::
    trainerbattle_single TRAINER_P_AIDEN, NewMauvilleFloor1_Text_AidenIntro, NewMauvilleFloor1_Text_AidenDefeated
    msgbox NewMauvilleFloor1_Text_AidenPostBattle, MSGBOX_AUTOCLOSE
    end

NewMauvilleFloor1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_NYARLY_TRADE_COMPLETED, NewMauvilleFloor1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_NYARLY
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox NewMauvilleFloor1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewMauvilleFloor1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, NewMauvilleFloor1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, NewMauvilleFloor1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox NewMauvilleFloor1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_NYARLY_TRADE_COMPLETED
	release
	end

NewMauvilleFloor1_EventScript_DeclineTrade::
	msgbox NewMauvilleFloor1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

NewMauvilleFloor1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox NewMauvilleFloor1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

NewMauvilleFloor1_EventScript_TradeCompleted::
	msgbox NewMauvilleFloor1_Text_ThanksForTrading, MSGBOX_DEFAULT
	release
	end

NewMauvilleFloor1_EventScript_ShopXItems::
	lock
	faceplayer
	message NewMauvilleFloor1_Text_WelcomeToShopXItems
	waitmessage
	pokemart NewMauvilleFloor1_Mart_ShopXItems
	msgbox NewMauvilleFloor1_Text_HaveAGoodDay, MSGBOX_AUTOCLOSE
	release
	end

	.align 2
NewMauvilleFloor1_Mart_ShopXItems:
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_SP_DEF
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_NONE
	release
	end	

NewMauvilleFloor1_EventScript_ShopSeeds::
	lock
	faceplayer
	message NewMauvilleFloor1_Text_WelcomeToShopSeeds
	waitmessage
	pokemart NewMauvilleFloor1_Mart_ShopSeeds
	msgbox NewMauvilleFloor1_Text_HaveAGoodDay, MSGBOX_AUTOCLOSE
	release
	end

	.align 2
NewMauvilleFloor1_Mart_ShopSeeds:
	.2byte ITEM_ELECTRIC_SEED
	.2byte ITEM_GRASSY_SEED
	.2byte ITEM_MISTY_SEED
	.2byte ITEM_PSYCHIC_SEED
	.2byte ITEM_NONE
	release
	end	

NewMauvilleFloor1_EventScript_ShopHerbs::
	lock
	faceplayer
	message NewMauvilleFloor1_Text_WelcomeToShopHerbs
	waitmessage
	pokemart NewMauvilleFloor1_Mart_ShopHerbs
	msgbox NewMauvilleFloor1_Text_HaveAGoodDay, MSGBOX_AUTOCLOSE
	release
	end

	.align 2
NewMauvilleFloor1_Mart_ShopHerbs:
	.2byte ITEM_WHITE_HERB
	.2byte ITEM_MENTAL_HERB
	.2byte ITEM_POWER_HERB
	.2byte ITEM_MIRROR_HERB
	.2byte ITEM_NONE
	release
	end	

NewMauvilleFloor1_EventScript_ShopDebilitatingItems::
	lock
	faceplayer
	message NewMauvilleFloor1_Text_WelcomeToShopDebilitatingItems
	waitmessage
	pokemart NewMauvilleFloor1_Mart_ShopDebilitatingItems
	msgbox NewMauvilleFloor1_Text_HaveAGoodDay, MSGBOX_AUTOCLOSE
	release
	end

	.align 2
NewMauvilleFloor1_Mart_ShopDebilitatingItems:
	.2byte ITEM_IRON_BALL
	.2byte ITEM_LAGGING_TAIL
	.2byte ITEM_RING_TARGET
	.2byte ITEM_STICKY_BARB
	.2byte ITEM_GLUE_TUBE
	.2byte ITEM_NONE
	release
	end	

NewMauvilleFloor1_EventScript_CookieSeller::
    lock
	faceplayer
	showmoneybox 0, 0
	msgbox NewMauvilleFloor1_Text_WantCookie, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewMauvilleFloor1_EventScript_CheckMoneyForCookie
	closemessage
	hidemoneybox
	release
	end

NewMauvilleFloor1_EventScript_CheckMoneyForCookie::
	checkmoney 5000
	goto_if_eq VAR_RESULT, FALSE, NewMauvilleFloor1_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 5000
	updatemoneybox
	delay 40
	hidemoneybox
	giveitem ITEM_ABILITY_CAPSULE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

NewMauvilleFloor1_EventScript_BlackSaladSeller::
    lock
	faceplayer
	showmoneybox 0, 0
	msgbox NewMauvilleFloor1_Text_WantBlackSalad, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewMauvilleFloor1_EventScript_CheckMoneyForBlackSalad
	closemessage
	hidemoneybox
	release
	end

NewMauvilleFloor1_EventScript_CheckMoneyForBlackSalad::
	checkmoney 8000
	goto_if_eq VAR_RESULT, FALSE, NewMauvilleFloor1_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 8000
	updatemoneybox
	delay 40
	hidemoneybox
	giveitem ITEM_BLACK_SALAD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

NewMauvilleFloor1_EventScript_LavaCookieSeller::
    lock
	faceplayer
	showmoneybox 0, 0
	msgbox NewMauvilleFloor1_Text_WantLavaCookie, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewMauvilleFloor1_EventScript_CheckMoneyForLavaCookie
	closemessage
	hidemoneybox
	release
	end

NewMauvilleFloor1_EventScript_CheckMoneyForLavaCookie::
	checkmoney 600
	goto_if_eq VAR_RESULT, FALSE, NewMauvilleFloor1_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 600
	updatemoneybox
	delay 40
	hidemoneybox
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

NewMauvilleFloor1_EventScript_IcePopSeller::
    lock
	faceplayer
	showmoneybox 0, 0
	msgbox NewMauvilleFloor1_Text_WantIcePop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewMauvilleFloor1_EventScript_CheckMoneyForIcePop
	closemessage
	hidemoneybox
	release
	end

NewMauvilleFloor1_EventScript_CheckMoneyForIcePop::
	checkmoney 600
	goto_if_eq VAR_RESULT, FALSE, NewMauvilleFloor1_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 600
	updatemoneybox
	delay 40
	hidemoneybox
	giveitem ITEM_ICE_POP
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

NewMauvilleFloor1_EventScript_NotEnoughMoney::
	msgbox NewMauvilleFloor1_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

NewMauvilleFloor1_EventScript_2F3FElevatorSign::
	msgbox NewMauvilleFloor1_Text_2F3FElevatorSign, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_MaintenanceElevatorSign::
	msgbox NewMauvilleFloor1_Text_MaintenanceElevatorSign, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_RoofElevatorSign::
	msgbox NewMauvilleFloor1_Text_RoofElevatorSign, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_RydelCyclesSign::
	msgbox NewMauvilleFloor1_Text_RydelCyclesSign, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_GoldToothSign::
	msgbox NewMauvilleFloor1_Text_GoldToothSign, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_FoodMenu1::
	msgbox NewMauvilleFloor1_Text_FoodMenu1, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_FoodMenu2::
	msgbox NewMauvilleFloor1_Text_FoodMenu2, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_FoodMenu3::
	msgbox NewMauvilleFloor1_Text_FoodMenu3, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_FoodMenu4::
	msgbox NewMauvilleFloor1_Text_FoodMenu4, MSGBOX_SIGN
	end

NewMauvilleFloor1_EventScript_RydelGuard::
	msgbox NewMauvilleFloor1_Text_RydelGuard, MSGBOX_NPC
	end

NewMauvilleFloor1_Text_2F3FElevatorSign:
	.string "The elevator labelled 2F\n"
	.string "leads to the apartments.\p"
	.string "The elevator labelled 3F\n"
	.string "leads to a heightened segment\l"
	.string "of the roof, only accessible\l"
	.string "via said elevator.$"

NewMauvilleFloor1_Text_MaintenanceElevatorSign:
	.string "NOTICE:\n"
	.string "This elevator descends to the\l"
	.string "Maintenance floor underneath\l"
	.string "the city proper.\p"
	.string "Employees must clock in with\n"
	.string "their keys at the main entrance\l"
	.string "at the south side of New Mauville\l"
	.string "in order to freely use this!$"

NewMauvilleFloor1_Text_RoofElevatorSign:
	.string "Green elevators lead to\n"
	.string "the rooftop terraces.$"

NewMauvilleFloor1_Text_RydelCyclesSign:
	.string "RYDEL'S CYCLES!$"

NewMauvilleFloor1_Text_GoldToothSign:
	.string "There are many move tutors\n"
	.string "in New Mauville! We pride\l"
	.string "ourselves on our variety.\l"
	.string "Tutors here have taken to using\l"
	.string "a unique currency; Gold Teeth.\l"
	.string "Take any you find to a tutor!$"

NewMauvilleFloor1_Text_FoodMenu1:
	.string "(It's a restaurant menu.\n"
	.string "Ability Snacks are on the list.)$"

NewMauvilleFloor1_Text_FoodMenu2:
	.string "(It's a restaurant menu.\n"
	.string "Black Salad is on the list.)$"

NewMauvilleFloor1_Text_FoodMenu3:
	.string "(It's a restaurant menu.\n"
	.string "Lava Cookies are on the list.)$"

NewMauvilleFloor1_Text_FoodMenu4:
	.string "(It's a restaurant menu.\n"
	.string "Ice Pops are on the list.)$"

NewMauvilleFloor1_Text_IllTradeIfYouWant:
	.string "I'll trade you my {STR_VAR_2} for\n"
	.string "a {STR_VAR_1} if you want.$"

NewMauvilleFloor1_Text_PleaseBeGoodToMyPokemon:
	.string "Please be good to my POKéMON.$"

NewMauvilleFloor1_Text_DoesntLookLikeMonToMe:
	.string "Huh? That doesn't look anything like\n"
	.string "a {STR_VAR_1} to me.$"

NewMauvilleFloor1_Text_YouDontWantToThatsOkay:
	.string "Oh, if you don't want to, that's okay.$"

NewMauvilleFloor1_Text_ThanksForTrading:
	.string "Thanks for the trade.$"

NewMauvilleFloor1_Text_NameKizuna:
	.string "Kizuna$"

NewMauvilleFloor1_Text_RoyIntro:
	.string "Do you love the color of the sky?$"

NewMauvilleFloor1_Text_RoyDefeated:
	.string "...Which one?$"

NewMauvilleFloor1_Text_RoyPostBattle:
	.string "The colors of my Spinda inspire\n"
	.string "me to make fine art... yet,\l"
	.string "here I am, spray-painting.$"

NewMauvilleFloor1_Text_McKayleighIntro:
	.string "Looooooook at how cuuuuuute\n"
	.string "my team is!$"

NewMauvilleFloor1_Text_McKayleighDefeated:
	.string "Cuteness is no match for, ugh...\n"
	.string "UGLY brute strength. Ewww!$"

NewMauvilleFloor1_Text_McKayleighPostBattle:
	.string "Leave my cute Pokemon alone,\n"
	.string "you brutish buffoon!$"

NewMauvilleFloor1_Text_AidenIntro:
	.string "Who are YOU to bother ME!?$"

NewMauvilleFloor1_Text_AidenDefeated:
	.string "How DARE you. Such disrespect!$"

NewMauvilleFloor1_Text_AidenPostBattle:
	.string "I SPIT at you!\n"
	.string "Ptooey!$"

NewMauvilleFloor1_Text_ItsYouFromTheTidal:
	.string "Oh! Hey, there!\p"
	.string "You, uh... might not remember me.\n"
	.string "I do look a bit... unremarkable,\l"
	.string "but I remember you! We were on\l"
	.string "the S.S. Tidal together!$"

NewMauvilleFloor1_Text_AboutWattsonAndMauville:
	.string "To formally introduce myself,\n"
	.string "my name is Kizuna. I'm a\l"
	.string "middle manager for Devo-...\l"
	.string "I mean, Greater Mauville Holdings.\p"
	.string "You had said you were going to\n"
	.string "embark on a journey to get every\l"
	.string "gym badge in Hoenn, right?\l"
	.string "It figures you would find yourself\l"
	.string "here in New Mauville.\p"
	.string "...Yes, it USED to be just\n"
	.string "Mauville City. But Wattson and\l"
	.string "his company basically bulldozed\l"
	.string "the old city and built this\l"
	.string "megastructure on top. Silly\l"
	.string "to change the name, I know, but\l"
	.string "that's just the kind of guy he is.\p"
	.string "He's still the gym leader here.\n"
	.string "Well, mostly only in name. He's\l"
	.string "a 'very busy man', so he claims,\l"
	.string "so he has started needing an\l"
	.string "appointment to battle him.\l"
	.string "The waiting list for those\l"
	.string "appointments is pretty long.\p"
	.string "There IS an alternative...\n"
	.string "which, is straight up buying\l"
	.string "the gym badge with cash. You\l"
	.string "can do that in Verdanturf to\l"
	.string "the west, where Wattson relocated\l"
	.string "the gym after the renovations.\p"
	.string "...That's no fun? Yeah, I guess not.\p"
	.string "I... MAY know of another...\n"
	.string "sneakier method. But I haven't\l"
	.string "really tested it.\p"
	.string "If you want to humor me, come meet\n"
	.string "me in my apartment on the\l"
	.string "second floor. If not, that's fine.\l"
	.string "Hope you enjoy your time here!$"

NewMauvilleFloor1_Text_WelcomeToShopXItems:
	.string "Welcome to the X Item Shop!$"

NewMauvilleFloor1_Text_WelcomeToShopSeeds:
	.string "Welcome to the Seed Shop!$"

NewMauvilleFloor1_Text_WelcomeToShopHerbs:
	.string "Welcome to the Herb Shop!$"

NewMauvilleFloor1_Text_WelcomeToShopDebilitatingItems:
	.string "Welcome to the Debilitating Item Shop!$"

NewMauvilleFloor1_Text_WelcomeToShopMints:
	.string "Welcome to the Mint Shop!$"

NewMauvilleFloor1_Text_HaveAGoodDay:
	.string "Have a good day!$"

NewMauvilleFloor1_Text_RydelGuard:
	.string "Hey, uh, just to let you know...\n"
	.string "Probably shouldn't've left\l"
	.string "the race when you did, uh...\l"
	.string "Rydel's a bit peeved, dude.\l"
	.string "Gotta go in through the\l"
	.string "outside entrance, he said.$"

NewMauvilleFloor1_Text_WantCookie:
	.string "I bake tasty Ability Snacks!\n"
	.string "Pokemon love them. If you give\l"
	.string "one to a Pokemon, it can change\l"
	.string "its ability to another!\p"
	.string "Would you like to buy one?\n"
	.string "They cost ¥5000 each.$"

NewMauvilleFloor1_Text_WantBlackSalad:
	.string "Unlike that absolute CURR by\n"
	.string "my side, I only sell the\l"
	.string "cleanest, healthiest of foods.\p"
	.string "The black salad.\n"
	.string "The purest a salad can be.\p"
	.string "One may be yours\n"
	.string "for a measly ¥8000...$"

NewMauvilleFloor1_Text_WantLavaCookie:
	.string "I'm from Lavaridge Town, bringing\n"
	.string "one of our cultural delicacies\l"
	.string "to a wider market!\p"
	.string "Durin Berries didn't go over well.\n"
	.string "But people seem to like these\l"
	.string "Lava Cookies! Want one?\l"
	.string "That'd be ¥600 a pop.$"

NewMauvilleFloor1_Text_WantIcePop:
	.string "Ice Pops! Ice Pops!\n"
	.string "Get yer Ice Pops here!\l"
	.string "Nice n' cold! Only ¥600!$"

NewMauvilleFloor1_Text_NotEnoughMoney:
	.string "You don't have enough money!$"
