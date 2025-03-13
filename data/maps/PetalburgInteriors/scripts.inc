PetalburgInteriors_MapScripts::
	.byte 0

PetalburgInteriors_EventScript_CardTrader::
	lock
	faceplayer
	checkitem ITEM_LEGEND_CARD
	goto_if_eq VAR_RESULT, TRUE, PetalburgInteriors_EventScript_TradeForCard
	checkitem ITEM_UNO_CARD
	goto_if_eq VAR_RESULT, TRUE, PetalburgInteriors_EventScript_GaveYouMyCard
	msgbox PetalburgInteriors_Text_WhatINeed, MSGBOX_AUTOCLOSE
	release
	end

PetalburgInteriors_EventScript_TradeForCard::
	msgbox PetalburgInteriors_Text_WillYouTradeCards, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgInteriors_EventScript_CardTrade
	release
	end

PetalburgInteriors_EventScript_CardTrade::
	delay 4
	msgbox PetalburgInteriors_Text_AboutThatCard, MSGBOX_DEFAULT
	closemessage
	removeitem ITEM_LEGEND_CARD
	giveitem ITEM_UNO_CARD
	closemessage
	release
	end

PetalburgInteriors_EventScript_GaveYouMyCard::
	msgbox PetalburgInteriors_Text_GaveYouMyCard, MSGBOX_AUTOCLOSE
	release
	end

PetalburgInteriors_Text_WhatINeed:
	.string "I keep telling card enthusiasts\n"
	.string "that I possess one of the most\l"
	.string "powerful, game-breaking cards\l"
	.string "of any card game! Nobody believes me.\l"
	.string "But I know that what I have\l"
	.string "is worth something!\p"
	.string "If you can get your hands on\n"
	.string "a truly LEGENDARY card...\l"
	.string "I may be willing to part with\l"
	.string "it. MAY. We'll see.$"

PetalburgInteriors_Text_WillYouTradeCards:
	.string "I keep telling card enthusiasts\n"
	.string "that I possess one of the most\l"
	.string "powerful, game-breaking cards\l"
	.string "of any card game! Nobody believes me.\l"
	.string "But I know that what I have\l"
	.string "is worth something!\p"
	.string "If you can get your hands on\n"
	.string "a truly LEGENDARY card...\l"
	.string "I may be willing to part with\l"
	.string "it. MAY. We'll see.\p"
	.string "(You flash your Legend Card\n"
	.string "at the braggart.)\p"
	.string "Don't screw with me! You're REALLY\n"
	.string "looking to trade?\p"
	.string "Hmm... this card is rather powerful\n"
	.string "in its game's meta. I think\l"
	.string "it will be sufficient.\p"
	.string "So? Trading time?\n$"

PetalburgInteriors_Text_AboutThatCard:
	.string "You won't be disappointed with this\n"
	.string "card's TREMENDOUS power, trust me.\p"
	.string "I like to play it in any tournament.\n"
	.string "Regardless of the rules.\l"
	.string "Regardless of what game, even.\l"
	.string "It's THAT good.$"

PetalburgInteriors_Text_GaveYouMyCard:
	.string "The next one I have to search\n"
	.string "for is the elusive Plus Four card...$"
