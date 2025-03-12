.set LOCALID_YOUTUBER1, 2
.set LOCALID_YOUTUBER2, 3
.set LOCALID_YOUTUBER3, 4
.set LOCALID_YOUTUBER4, 5

SlateportSodaShop_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SlateportSodaShop_OnLoad
	.byte 0

SlateportSodaShop_OnLoad:
	call_if_defeated TRAINER_P_BEAST, SlateportSodaShop_EventScript_RemoveYoutubers
	end

SlateportSodaShop_EventScript_RemoveYoutubers::
	removeobject LOCALID_YOUTUBER1
	removeobject LOCALID_YOUTUBER2
	removeobject LOCALID_YOUTUBER3
	removeobject LOCALID_YOUTUBER4
	setflag FLAG_TEMP_8
	return

SlateportSodaShop_EventScript_MrBeast::
    trainerbattle_single TRAINER_P_BEAST, SlateportSodaShop_Text_MrBeastIntro, SlateportSodaShop_Text_MrBeastDefeated
    msgbox SlateportSodaShop_Text_MrBeastPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportSodaShop_EventScript_KaiSenat::
    trainerbattle_single TRAINER_P_KAISENAT, SlateportSodaShop_Text_KaiSenatIntro, SlateportSodaShop_Text_KaiSenatDefeated
    msgbox SlateportSodaShop_Text_KaiSenatPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportSodaShop_EventScript_SodaShopOwner::
	lock
	faceplayer
	checkitem ITEM_YELLOW_SODA
	goto_if_eq VAR_RESULT, TRUE, SlateportSodaShop_EventScript_AlreadyGaveYellowSoda
	msgbox SlateportSodaShop_Text_RunningAPromotion, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_YELLOW_SODA
	closemessage
	msgbox SlateportSodaShop_Text_NowGetLost, MSGBOX_AUTOCLOSE
	release
	end

SlateportSodaShop_EventScript_AlreadyGaveYellowSoda::
	msgbox SlateportSodaShop_Text_AlreadyGaveYellowSoda, MSGBOX_AUTOCLOSE
	release
	end

SlateportSodaShop_EventScript_YoutuberBlock1::
    msgbox SlateportSodaShop_Text_YoutuberBlock1, MSGBOX_NPC
    end

SlateportSodaShop_EventScript_YoutuberBlock2::
    msgbox SlateportSodaShop_Text_YoutuberBlock2, MSGBOX_NPC
    end

SlateportSodaShop_Text_MrBeastIntro:
	.string "(This guy is tensing up every\n"
	.string "single one of his veins.\l"
	.string "Gearing up for one, solid, shout.)\p"
	.string "mmmmMMMMMMMMMMIIIISSSTTERRRRRRRR\n"
	.string "BEEEEAAAAASSSSSTT-TYYYYYYYPPPE...!$"

SlateportSodaShop_Text_MrBeastDefeated:
	.string "GONE WRONG!$"

SlateportSodaShop_Text_MrBeastPostBattle:
	.string "Look, it's not every day you\n"
	.string "get to run into an e-celeb like me.\l"
	.string "And you're just gonna waltz by?\l"
	.string "No autograph? No begging for money?\l"
	.string "Why won't you give me attention!?!?$"

SlateportSodaShop_Text_KaiSenatIntro:
	.string "What's UP guys, Kai here,\n"
	.string "and to-DAY, we're gonna be\l"
	.string "CRUSHING these NPCs in\l"
	.string "Pokemon Battles!\p"
	.string "Oh look what we got here, guys!\n"
	.string "Some rando! They'll go down easy!$"

SlateportSodaShop_Text_KaiSenatDefeated:
	.string "I stopped recording the instant\n"
	.string "one of my 'mons fainted!$"

SlateportSodaShop_Text_KaiSenatPostBattle:
	.string "I'll explain it all away as\n"
	.string "a glitch, or something. I don't\l"
	.string "lose, 'least in the eyes of my fans.$"

SlateportSodaShop_Text_YoutuberBlock1:
	.string "Try To Get Past Me Challenge!\n"
	.string "(FAILED)$"

SlateportSodaShop_Text_YoutuberBlock2:
	.string "I Spent 4 Hours BLOCKING This Path!\n"
	.string "(EMOTIONAL)$"

SlateportSodaShop_Text_RunningAPromotion:
	.string "The Seashore House wasn't seeing\n"
	.string "a lot of hubbub lately. Then I\l"
	.string "had the brilliant idea of inviting\l"
	.string "these clout goblins to the beach!\p"
	.string "We've been SWIMMING in dough since!\n"
	.string "And hey, I bet you heard about\l"
	.string "our current promotion. If you can\l"
	.string "beat the trainers in the\l"
	.string "Seashore House and get to me,\l"
	.string "you get to try an experimental\l"
	.string "new soda flavor!\p"
	.string "...And it looks like you already\n"
	.string "did just that! Here's our new,\l"
	.string "never before tested flavor...\l"
	.string "...Yellow!$"

SlateportSodaShop_Text_NowGetLost:
	.string "We hope you enjoy it! And hey,\n"
	.string "while you're here, why not\l"
	.string "check in with those e-celebs?\l"
	.string "You're a youngin! You love 'em!$"

SlateportSodaShop_Text_AlreadyGaveYellowSoda:
	.string "Ah-ah-ah! No more free samples!\p"
	.string "You'll have to come back next\n"
	.string "week when we debut the newest\l"
	.string "flavor, macaroni and cheese...\p"
	.string "N-Named after the COLOR, not\n"
	.string "the food...$"
