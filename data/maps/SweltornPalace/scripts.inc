SweltornPalace_MapScripts::
	.byte 0

SweltornPalace_EventScript_Reli::
    trainerbattle_single TRAINER_P_RELI, SweltornPalace_Text_ReliIntro, SweltornPalace_Text_ReliDefeated
    msgbox SweltornPalace_Text_ReliPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornPalace_EventScript_Castle::
    trainerbattle_single TRAINER_P_CASTLE, SweltornPalace_Text_CastleIntro, SweltornPalace_Text_CastleDefeated
    msgbox SweltornPalace_Text_CastlePostBattle, MSGBOX_AUTOCLOSE
    end

SweltornPalace_EventScript_Katrina::
    trainerbattle_single TRAINER_P_KATRINA, SweltornPalace_Text_KatrinaIntro, SweltornPalace_Text_KatrinaDefeated
    msgbox SweltornPalace_Text_KatrinaPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornPalace_EventScript_Gertrude::
    trainerbattle_single TRAINER_P_GERTRUDE, SweltornPalace_Text_GertrudeIntro, SweltornPalace_Text_GertrudeDefeated
    msgbox SweltornPalace_Text_GertrudePostBattle, MSGBOX_AUTOCLOSE
    end

SweltornPalace_EventScript_Tootsie::
    trainerbattle_single TRAINER_P_TOOTSIE, SweltornPalace_Text_TootsieIntro, SweltornPalace_Text_TootsieDefeated
    msgbox SweltornPalace_Text_TootsiePostBattle, MSGBOX_AUTOCLOSE
    end

SweltornPalace_EventScript_TreasureSeeker::
	lock
	faceplayer
	goto_if_set FLAG_CHOSE_SANDSTONE, SweltornPalace_EventScript_CantTakeAnother
	goto_if_set FLAG_CHOSE_SANDBAG, SweltornPalace_EventScript_CantTakeAnother
	msgbox SweltornPalace_Text_IFoundTreasure, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_CHOICE_ITEM_PICK, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	goto_if_eq VAR_TEMP_1, 0, SweltornPalace_EventScript_TakeSandbag
	goto_if_eq VAR_TEMP_1, 1, SweltornPalace_EventScript_TakeSandstone
	msgbox SweltornPalace_Text_ComeBackIfYouWantOne, MSGBOX_AUTOCLOSE
	release
	end

SweltornPalace_EventScript_TakeSandbag::
	msgbox SweltornPalace_Text_GoodChoice, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SANDBAG
	closemessage
	setflag FLAG_CHOSE_SANDBAG
	release
	end

SweltornPalace_EventScript_TakeSandstone::
	msgbox SweltornPalace_Text_GoodChoice, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SANDSTONE
	closemessage
	setflag FLAG_CHOSE_SANDSTONE
	release
	end

SweltornPalace_EventScript_CantTakeAnother::
	msgbox SweltornPalace_Text_CantTakeAnother, MSGBOX_AUTOCLOSE
	release
	end

SweltornPalace_Text_IFoundTreasure:
	.string "I have been trekking about this\n"
	.string "ruin for several days. Gone\l"
	.string "far, far deeper than most are willing.\l"
	.string "And I have come out of this\l"
	.string "expedition with some rather\l"
	.string "rare treasures...!\p"
	.string "These treasures, however, are of\n"
	.string "no practical use to me, as\l"
	.string "they are meant for Pokemon evolution.\l"
	.string "I am no trainer. However,\l"
	.string "you seem to be!\p"
	.string "I will offer you one of my two\n"
	.string "treasures, and I will keep the\l"
	.string "remaining one as a souvenier.\l"
	.string "Each of them evolves a\l"
	.string "certain Pokemon, Pebbler.\p"
	.string "Which of them would you like?\n"
	.string "The Sandbag, or the Sandstone?$"

SweltornPalace_Text_ComeBackIfYouWantOne:
	.string "Return to me if you still\n"
	.string "wish to take my offer.$"

SweltornPalace_Text_GoodChoice:
	.string "An excellent choice.$"

SweltornPalace_Text_CantTakeAnother:
	.string "I will be taking the remaining\n"
	.string "treasure home as a conversation\l"
	.string "piece. Some say these trinkets\l"
	.string "belong in a museum.\l"
	.string "I believe that to be horsewash.$"

SweltornPalace_Text_ReliIntro:
	.string "intro$"

SweltornPalace_Text_ReliDefeated:
	.string "defeat$"

SweltornPalace_Text_ReliPostBattle:
	.string "post$"

SweltornPalace_Text_CastleIntro:
	.string "intro$"

SweltornPalace_Text_CastleDefeated:
	.string "defeat$"

SweltornPalace_Text_CastlePostBattle:
	.string "post$"

SweltornPalace_Text_KatrinaIntro:
	.string "intro$"

SweltornPalace_Text_KatrinaDefeated:
	.string "defeat$"

SweltornPalace_Text_KatrinaPostBattle:
	.string "post$"

SweltornPalace_Text_GertrudeIntro:
	.string "intro$"

SweltornPalace_Text_GertrudeDefeated:
	.string "defeat$"

SweltornPalace_Text_GertrudePostBattle:
	.string "post$"

SweltornPalace_Text_TootsieIntro:
	.string "intro$"

SweltornPalace_Text_TootsieDefeated:
	.string "defeat$"

SweltornPalace_Text_TootsiePostBattle:
	.string "post$"
