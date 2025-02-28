SSTidalMidTeriors_MapScripts::
	.byte 0

SSTidalMidTeriors_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_SCALLYWARG_TRADE_COMPLETED, SSTidalMidTeriors_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SCALLYWARG
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox SSTidalMidTeriors_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SSTidalMidTeriors_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SSTidalMidTeriors_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, SSTidalMidTeriors_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox SSTidalMidTeriors_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_SCALLYWARG_TRADE_COMPLETED
	release
	end

SSTidalMidTeriors_EventScript_DeclineTrade::
	msgbox SSTidalMidTeriors_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

SSTidalMidTeriors_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox SSTidalMidTeriors_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

SSTidalMidTeriors_EventScript_TradeCompleted::
	msgbox SSTidalMidTeriors_Text_ThanksForTrading, MSGBOX_DEFAULT
	release
	end

SSTidalMidTeriors_EventScript_ColfinFan::
	lock
	faceplayer
	checkitem ITEM_FRIEND_RIBBON
	goto_if_eq VAR_RESULT, TRUE, SSTidalMidTeriors_EventScript_AlreadyGaveFriendRibbon
	msgbox SSTidalMidTeriors_Text_ColfinNeedGoodRoleModel, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_FRIEND_RIBBON
	closemessage
	release
	end

SSTidalMidTeriors_EventScript_AlreadyGaveFriendRibbon::
	msgbox SSTidalMidTeriors_Text_AlreadyGaveFriendRibbon, MSGBOX_AUTOCLOSE
	release
	end

SSTidalMidTeriors_Text_IllTradeIfYouWant:
	.string "I'll trade you my {STR_VAR_2} for\n"
	.string "a {STR_VAR_1} if you want.$"

SSTidalMidTeriors_Text_PleaseBeGoodToMyPokemon:
	.string "Please be good to my POKéMON.$"

SSTidalMidTeriors_Text_DoesntLookLikeMonToMe:
	.string "Huh? That doesn't look anything like\n"
	.string "a {STR_VAR_1} to me.$"

SSTidalMidTeriors_Text_YouDontWantToThatsOkay:
	.string "Oh, if you don't want to, that's okay.$"

SSTidalMidTeriors_Text_ThanksForTrading:
	.string "Thanks for the trade.$"

SSTidalMidTeriors_Text_ColfinNeedGoodRoleModel:
	.string "My absolute favorite Pokemon\n"
	.string "is Colfin. What a cutie-patootie!\p"
	.string "Their brains are like childrens'.\n"
	.string "Very susceptible to influence.\l"
	.string "Let one fall in with the\l"
	.string "wrong crowd... and it may evolve\l"
	.string "to become a pretty mean Pokemon.\p"
	.string "I have been starting a movement\n"
	.string "for trainers to be more caring\l"
	.string "towards their Colfin! We give\l"
	.string "out these ribbons to trainers\l"
	.string "to try and encourage them to\l"
	.string "really be a good influence!$"

SSTidalMidTeriors_Text_AlreadyGaveFriendRibbon:
	.string "With a Friend Ribbon, a Colfin\n"
	.string "can be just as useful in battle\l"
	.string "as its evolution. So, no need\l"
	.string "to let its conscience darken!$"
