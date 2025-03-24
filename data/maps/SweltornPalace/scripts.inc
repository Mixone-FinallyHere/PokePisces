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
	multichoice 19, 4, MULTI_SAND_ITEM_PICK, FALSE
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
	.string "We came here on special assignment\n"
	.string "to investigate this Palace\l"
	.string "for signs of Relic type Pokemon.\l"
	.string "Have you seen any?$"

SweltornPalace_Text_ReliDefeated:
	.string "I meant, other than ours!$"

SweltornPalace_Text_ReliPostBattle:
	.string "Relic type Pokemon tend to guard\n"
	.string "ancient places... though, I fear\l"
	.string "that tomb raiders may have defeated\l"
	.string "them all already...$"

SweltornPalace_Text_CastleIntro:
	.string "Tell us anything you know\n"
	.string "about the Pokemon that reside here!$"

SweltornPalace_Text_CastleDefeated:
	.string "Hmm, that didn't go as planned.$"

SweltornPalace_Text_CastlePostBattle:
	.string "The Relic type is not\n"
	.string "fully understood by science\l"
	.string "as of yet.\p"
	.string "We're trying our best to\n"
	.string "change that.$"

SweltornPalace_Text_KatrinaIntro:
	.string "So you've sought shelter too, eh?\n"
	.string "Don't think that people in here\l"
	.string "don't want a battle!$"

SweltornPalace_Text_KatrinaDefeated:
	.string "Pretty good showing!$"

SweltornPalace_Text_KatrinaPostBattle:
	.string "The Palace provides some\n"
	.string "well-needed shelter from\l"
	.string "the constant sandstorms.\p"
	.string "Us Ozone members like hanging\n"
	.string "out in here whenever Matt lets us.$"

SweltornPalace_Text_GertrudeIntro:
	.string "I've been on the hunt for new\n"
	.string "discoveries since you were\l"
	.string "in diapers!$"

SweltornPalace_Text_GertrudeDefeated:
	.string "Old wisdom just can't keep up\n"
	.string "with new spunk, huh...$"

SweltornPalace_Text_GertrudePostBattle:
	.string "I'm lucky enough to still have\n"
	.string "two good legs to continue\l"
	.string "travelling the world!\l"
	.string "You'll understand, someday!$"

SweltornPalace_Text_TootsieIntro:
	.string "You're about to get rolled, mate!$"

SweltornPalace_Text_TootsieDefeated:
	.string "Crikey...! I've been right popped!$"

SweltornPalace_Text_TootsiePostBattle:
	.string "How many digs will it take\n"
	.string "to get to the center of this\l"
	.string "pyramid, I wonder...$"
