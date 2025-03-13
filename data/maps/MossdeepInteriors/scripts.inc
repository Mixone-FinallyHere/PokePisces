MossdeepInteriors_MapScripts::
	.byte 0

MossdeepInteriors_EventScript_ArtTeacher::
	lock
	faceplayer
	checkitem ITEM_TRIUMPH_STAR
	goto_if_eq VAR_RESULT, TRUE, MossdeepInteriors_EventScript_AlreadyGaveTriumphStar
	goto_if_set FLAG_JUDGED_PAINTING, MossdeepInteriors_EventScript_GiveTriumphStar
	goto_if_set FLAG_WILL_JUDGE_PAINTING, MossdeepInteriors_EventScript_GoToLilycove
	msgbox MossdeepInteriors_Text_DoAPaperForMe, MSGBOX_DEFAULT
	setflag FLAG_WILL_JUDGE_PAINTING
	closemessage
	release
	end

MossdeepInteriors_EventScript_GoToLilycove::
	msgbox MossdeepInteriors_Text_GoToLilycove, MSGBOX_AUTOCLOSE
	release
	end

MossdeepInteriors_EventScript_GiveTriumphStar::
	msgbox MossdeepInteriors_Text_HaveATriumphStar, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_TRIUMPH_STAR
	closemessage
	release
	end

MossdeepInteriors_EventScript_AlreadyGaveTriumphStar::
	msgbox MossdeepInteriors_Text_AlreadyGaveTriumphStar, MSGBOX_AUTOCLOSE
	release
	end

MossdeepInteriors_EventScript_CardTrader::
	lock
	faceplayer
	checkitem ITEM_BUSINESS_CARD
	goto_if_eq VAR_RESULT, TRUE, MossdeepInteriors_EventScript_TradeForCard
	checkitem ITEM_LEGEND_CARD
	goto_if_eq VAR_RESULT, TRUE, MossdeepInteriors_EventScript_GaveYouMyCard
	msgbox MossdeepInteriors_Text_WhatINeed, MSGBOX_AUTOCLOSE
	release
	end

MossdeepInteriors_EventScript_TradeForCard::
	msgbox MossdeepInteriors_Text_WillYouTradeCards, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MossdeepInteriors_EventScript_CardTrade
	release
	end

MossdeepInteriors_EventScript_CardTrade::
	delay 4
	msgbox MossdeepInteriors_Text_AboutThatCard, MSGBOX_DEFAULT
	closemessage
	removeitem ITEM_BUSINESS_CARD
	giveitem ITEM_LEGEND_CARD
	closemessage
	release
	end

MossdeepInteriors_EventScript_GaveYouMyCard::
	msgbox MossdeepInteriors_Text_GaveYouMyCard, MSGBOX_AUTOCLOSE
	release
	end

MossdeepInteriors_EventScript_BikeChild::
	msgbox MossdeepInteriors_Text_BikeChild, MSGBOX_NPC
	end

MossdeepInteriors_Text_WhatINeed:
	.string "My son is so full of energy\n"
	.string "at his age... Oh, I'm exhausted!\p"
	.string "His birthday is coming up, and I\n"
	.string "have no clue what he'll want best!\l"
	.string "Oh, whatever can I do...$"

MossdeepInteriors_Text_WillYouTradeCards:
	.string "My son is so full of energy\n"
	.string "at his age... Oh, I'm exhausted!\p"
	.string "His birthday is coming up, and I\n"
	.string "have no clue what he'll want best!\l"
	.string "Oh, whatever can I do...\p"
	.string "(You flash Rydel's Business Card\n"
	.string "at the distraught man.)\p"
	.string "R-Rydel? Ah, that's it!\n"
	.string "I'll get him a bicycle from\l"
	.string "Rydel's Cycles! It's perfect!\l"
	.string "Please, c-can I have that card?\l"
	.string "I'll give you something good\l"
	.string "in return for the favor!$"

MossdeepInteriors_Text_AboutThatCard:
	.string "You're a lifesaver!\p"
	.string "Let's see here...\n"
	.string "...You're giving me a card,\l"
	.string "so I think it's fitting to\l"
	.string "give YOU a card in return.\p"
	.string "This Legend Card is one from\n"
	.string "my collection! It has a pretty\l"
	.string "high value these days. Maybe\l"
	.string "you can get a pretty penny for it!\l"
	.string "Or maybe you can trade it to\l"
	.string "another collector.\p"
	.string "Either way, it's yours!\n$"

MossdeepInteriors_Text_GaveYouMyCard:
	.string "I sure hope they sell bikes\n"
	.string "at that shop for such little kids...$"

MossdeepInteriors_Text_BikeChild:
	.string "I wanna ride an Acro Bike!\n"
	.string "So so bad! Pewww....!\l"
	.string "Hop-hop-hop!$"

MossdeepInteriors_Text_DoAPaperForMe:
	.string "Oh, what is an art teacher to do\n"
	.string "during the off season for school...\p"
	.string "Eureka! I will student-ify this\n"
	.string "child that has infiltrated my home!\p"
	.string "You are hearing me! I have\n"
	.string "an insatiable urge... to grade!\l"
	.string "A paper! Specifically, a paper\l"
	.string "dissecting a work of art!\p"
	.string "Write up a critique for me...\n"
	.string "and I shall grade it!$"

MossdeepInteriors_Text_GoToLilycove:
	.string "Where can you find a work of art?\n"
	.string "Well, some might say, all around us.\l"
	.string "But a not-annoying answer should\l"
	.string "be the Lilycove Museum.\l"
	.string "The artist Phillipe hangs up\l"
	.string "his paintings there.$"

MossdeepInteriors_Text_HaveATriumphStar:
	.string "Ah, you have brought to me\n"
	.string "your carefully crafted critique!\p"
	.string "...\p"
	.string "\n"
	.string "... ...\p"
	.string "\n"
	.string "...Erm, hmm...\p"
	.string "...How should I say this?\n"
	.string "This paper, well...\l"
	.string "Pay more attention in grammar\l"
	.string "classes next year, is all I'll say.\p"
	.string "(Your paper was returned to you\n"
	.string "with something attached...)$"

MossdeepInteriors_Text_AlreadyGaveTriumphStar:
	.string "Hmm? What do you mean, that tacky\n"
	.string "gold star I stuck onto your essay\l"
	.string "gives the Ledian family\l"
	.string "special stat boosts?\p"
	.string "I, erm, kind of want that back?\n$"
