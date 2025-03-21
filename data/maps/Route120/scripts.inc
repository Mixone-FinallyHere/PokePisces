Route120_MapScripts::
	.byte 0

Route120_EventScript_TreePath1::
	lock
	goto_if_set FLAG_TEMP_1A, Route120_EventScript_AlreadyCut1
	msgbox Route120_Text_PathThroughTree, MSGBOX_DEFAULT
	goto_if_unset FLAG_BADGE03_GET, Route120_EventScript_CantCut
	checkpartymove MOVE_CUT
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route120_EventScript_CantCut
	msgbox Route120_Text_WantToUseCut, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route120_EventScript_CutPath1
	release
	end

Route120_EventScript_CantCut::
	msgbox Route120_Text_NoCut, MSGBOX_AUTOCLOSE
	release
	end

Route120_EventScript_AlreadyCut1::
	setflag FLAG_TEMP_1A
	setmetatile 20, 75, METATILE_General_SecretBase_VineRight, FALSE
	special DrawWholeMapView
	msgbox Route120_Text_AlreadyCut, MSGBOX_AUTOCLOSE
	release
	end

Route120_EventScript_CutPath1::
	playse SE_M_CUT
	waitse
	setflag FLAG_TEMP_1A
	setmetatile 20, 75, METATILE_General_SecretBase_VineRight, FALSE
	special DrawWholeMapView
	release
	end

Route120_EventScript_TreePath2::
	lock
	goto_if_set FLAG_TEMP_1B, Route120_EventScript_AlreadyCut2
	msgbox Route120_Text_PathThroughTree, MSGBOX_DEFAULT
	goto_if_unset FLAG_BADGE03_GET, Route120_EventScript_CantCut
	checkpartymove MOVE_CUT
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route120_EventScript_CantCut
	msgbox Route120_Text_WantToUseCut, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route120_EventScript_CutPath2
	release
	end

Route120_EventScript_AlreadyCut2::
	setflag FLAG_TEMP_1B
	setmetatile 22, 26, METATILE_General_SecretBase_VineRight, FALSE
	special DrawWholeMapView
	msgbox Route120_Text_AlreadyCut, MSGBOX_AUTOCLOSE
	release
	end

Route120_EventScript_CutPath2::
	playse SE_M_CUT
	waitse
	setflag FLAG_TEMP_1B
	setmetatile 22, 26, METATILE_General_SecretBase_VineRight, FALSE
	special DrawWholeMapView
	release
	end

Route120_EventScript_TreePath3::
	lock
	goto_if_set FLAG_TEMP_1C, Route120_EventScript_AlreadyCut3
	msgbox Route120_Text_PathThroughTree, MSGBOX_DEFAULT
	goto_if_unset FLAG_BADGE03_GET, Route120_EventScript_CantCut
	checkpartymove MOVE_CUT
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route120_EventScript_CantCut
	msgbox Route120_Text_WantToUseCut, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route120_EventScript_CutPath3
	release
	end

Route120_EventScript_AlreadyCut3::
	setflag FLAG_TEMP_1C
	setmetatile 17, 21, METATILE_General_SecretBase_VineRight, FALSE
	special DrawWholeMapView
	msgbox Route120_Text_AlreadyCut, MSGBOX_AUTOCLOSE
	release
	end

Route120_EventScript_CutPath3::
	playse SE_M_CUT
	waitse
	setflag FLAG_TEMP_1C
	setmetatile 17, 21, METATILE_General_SecretBase_VineRight, FALSE
	special DrawWholeMapView
	release
	end

Route120_EventScript_TreePath4::
	lock
	goto_if_set FLAG_TEMP_1D, Route120_EventScript_AlreadyCut1
	msgbox Route120_Text_PathThroughTree, MSGBOX_DEFAULT
	goto_if_unset FLAG_BADGE03_GET, Route120_EventScript_CantCut
	checkpartymove MOVE_CUT
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route120_EventScript_CantCut
	msgbox Route120_Text_WantToUseCut, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route120_EventScript_CutPath4
	release
	end

Route120_EventScript_AlreadyCut4::
	setflag FLAG_TEMP_1D
	setmetatile 25, 9, METATILE_General_SecretBase_VineRight, FALSE
	special DrawWholeMapView
	msgbox Route120_Text_AlreadyCut, MSGBOX_AUTOCLOSE
	release
	end

Route120_EventScript_CutPath4::
	playse SE_M_CUT
	waitse
	setflag FLAG_TEMP_1D
	setmetatile 25, 9, METATILE_General_SecretBase_VineRight, FALSE
	special DrawWholeMapView
	release
	end

Route120_EventScript_Colby::
    trainerbattle_single TRAINER_P_COLBY, Route120_Text_ColbyIntro, Route120_Text_ColbyDefeated
    msgbox Route120_Text_ColbyPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_KatAndAna::
    trainerbattle_double TRAINER_P_KAT_AND_ANA, Route120_Text_KatAndAnaIntro, Route120_Text_KatAndAnaDefeated, Route120_Text_KatAndAnaNeedTwoMons
    msgbox Route120_Text_KatAndAnaPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Thatcher::
    trainerbattle_single TRAINER_P_THATCHER, Route120_Text_ThatcherIntro, Route120_Text_ThatcherDefeated
    msgbox Route120_Text_ThatcherPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Cherie::
    trainerbattle_single TRAINER_P_CHERIE, Route120_Text_CherieIntro, Route120_Text_CherieDefeated
    msgbox Route120_Text_CheriePostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Finn::
    trainerbattle_single TRAINER_P_FINN, Route120_Text_FinnIntro, Route120_Text_FinnDefeated
    msgbox Route120_Text_FinnPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Junie::
    trainerbattle_single TRAINER_P_JUNIE, Route120_Text_JunieIntro, Route120_Text_JunieDefeated
    msgbox Route120_Text_JuniePostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Kiwi::
    trainerbattle_single TRAINER_P_KIWI, Route120_Text_KiwiIntro, Route120_Text_KiwiDefeated
    msgbox Route120_Text_KiwiPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_JimBob::
    trainerbattle_single TRAINER_P_JIM_BOB, Route120_Text_JimBobIntro, Route120_Text_JimBobDefeated
    msgbox Route120_Text_JimBobPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_MaddyAndCross::
    trainerbattle_double TRAINER_P_MADDY_AND_CROSS, Route120_Text_MaddyAndCrossIntro, Route120_Text_MaddyAndCrossDefeated, Route120_Text_MaddyAndCrossNeedTwoMons
    msgbox Route120_Text_MaddyAndCrossPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Hector::
    trainerbattle_single TRAINER_P_HECTOR, Route120_Text_HectorIntro, Route120_Text_HectorDefeated
    msgbox Route120_Text_HectorPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Patrasche::
    trainerbattle_single TRAINER_P_PATRASCHE, Route120_Text_PatrascheIntro, Route120_Text_PatrascheDefeated
    msgbox Route120_Text_PatraschePostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Amira::
    trainerbattle_single TRAINER_P_AMIRA, Route120_Text_AmiraIntro, Route120_Text_AmiraDefeated
    msgbox Route120_Text_AmiraPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_Leilei::
    trainerbattle_single TRAINER_P_LEILEI, Route120_Text_LeileiIntro, Route120_Text_LeileiDefeated
    msgbox Route120_Text_LeileiPostBattle, MSGBOX_AUTOCLOSE
    end

Route120_EventScript_CutPathTutorial::
    msgbox Route120_Text_CutPathTutorial, MSGBOX_NPC
    end

Route120_EventScript_ColdMinesNorthSign::
	msgbox Route120_Text_ColdMinesNorthSign, MSGBOX_SIGN
	end

Route120_EventScript_PrettyPetalsSign::
	msgbox Route120_Text_PrettyPetalsSign, MSGBOX_SIGN
	end

Route120_EventScript_HutsSign::
	msgbox Route120_Text_HutsSign, MSGBOX_SIGN
	end

Route120_EventScript_ScuttillSettlementSign::
	msgbox Route120_Text_ScuttillSettlementSign, MSGBOX_SIGN
	end

Route120_EventScript_NoAliensSign::
	msgbox Route120_Text_NoAliensSign, MSGBOX_SIGN
	end

Route120_EventScript_ClearingSign::
	msgbox Route120_Text_ClearingSign, MSGBOX_SIGN
	end

Route120_EventScript_CharcoalArtistSign::
	msgbox Route120_Text_CharcoalArtistSign, MSGBOX_SIGN
	end

Route120_Text_ColdMinesNorthSign:
	.string "Northern Entrance to\n"
	.string "THE COLD MINES$"

Route120_Text_PrettyPetalsSign:
	.string "Ä Pretty Petals Flower Shop Ä\n"
	.string "We also sell Berries!$"

Route120_Text_HutsSign:
	.string "If you have access to Cut,\n"
	.string "Scuttill Huts continues\l"
	.string "beyond this point.$"

Route120_Text_ScuttillSettlementSign:
	.string "SCUTTILL SETTLEMENT$"

Route120_Text_NoAliensSign:
	.string "NO ALIENS ALLOWED\p"
	.string "P.S. - If you are a human,\n"
	.string "disregard this message.\l"
	.string "I'm just writing this in case\l"
	.string "it works.$"

Route120_Text_ClearingSign:
	.string "Notice:\n"
	.string "Taking one or two flowers from\l"
	.string "this clearing is fine! However,\l"
	.string "please make sure to water them!\l"
	.string "This public patch can only be\l"
	.string "maintained with the community's\l"
	.string "full cooperation!\p"
	.string "Signed, Pretty Petals Flower Shop$"

Route120_Text_CharcoalArtistSign:
	.string "Charcoal art for commission!$"

Route120_Text_ColbyIntro:
	.string "I bet you can't beat my full team of 6!$"

Route120_Text_ColbyDefeated:
	.string "Huh? What about my\n"
	.string "strength in numbers...?$"

Route120_Text_ColbyPostBattle:
	.string "A team with more Pokémon should have a\n"
	.string "natural advantage, right?\p"
	.string "Or is there more to it than that...?$"

Route120_Text_KatAndAnaIntro:
	.string "KAT: We're so in sync, we finish\n"
	.string "     each other's...\p"
	.string "ANA: ...Sandwiches!$"

Route120_Text_KatAndAnaDefeated:
	.string "KAT: We're finished! You...\n"
	.string "ANA: ...Uhh. Beats me!$"

Route120_Text_KatAndAnaPostBattle:
	.string "KAT: We battle everyone together, and...\n"
	.string "ANA: ...We always lose together too!$"

Route120_Text_KatAndAnaNeedTwoMons:
	.string "KAT: Two! Two! You need...\n"
	.string "ANA: ...more than one.$"

Route120_Text_ThatcherIntro:
	.string "I'm both creepy AND crawly!$"

Route120_Text_ThatcherDefeated:
	.string "Whoa! I've been stomped!$"

Route120_Text_ThatcherPostBattle:
	.string "Time for me to skitter on out of here!$"

Route120_Text_CherieIntro:
	.string "We're going on a trainer hunt!\n"
	.string "We're gonna catch a big one!$"

Route120_Text_CherieDefeated:
	.string "What a beautiful day!$"

Route120_Text_CheriePostBattle:
	.string "We're not going on a trainer hunt again.$"

Route120_Text_FinnIntro:
	.string "Hey there! Wanna battle my\n"
	.string "cute Pokémon?$"

Route120_Text_FinnDefeated:
	.string "Oops! ...Did I trick you?$"

Route120_Text_FinnPostBattle:
	.string "Looks can be decieving, my friend.$"

Route120_Text_JunieIntro:
	.string "Hey, stop rustling the grass!\n"
	.string "My little one is allergic!$"

Route120_Text_JunieDefeated:
	.string "I guess you didn't mean\n"
	.string "to rustle it that much.$"

Route120_Text_JuniePostBattle:
	.string "Make sure to cover your legs\n"
	.string "and arms when going through the\l"
	.string "thickets... you could get\l"
	.string "scraped up.$"

Route120_Text_KiwiIntro:
	.string "I'm supposed to be a bird watcher,\n"
	.string "but I like other Flying type Pokemon\l"
	.string "much better!\p"
	.string "Let me show you some!$"

Route120_Text_KiwiDefeated:
	.string "Oh no! My fliers!$"

Route120_Text_KiwiPostBattle:
	.string "Most of Hoenn's strongest birds\n"
	.string "are in Petalburg Woods.\l"
	.string "Can I go there someday?$"

Route120_Text_JimBobIntro:
	.string "My mom says I'll be an entomologist\n"
	.string "when I grow up! How cool is that?!$"

Route120_Text_JimBobDefeated:
	.string "Just have to learn\n"
	.string "what that word means first...$"

Route120_Text_JimBobPostBattle:
	.string "Hopefully it has something to do with\n"
	.string "bugs! I just love bugs!$"

Route120_Text_MaddyAndCrossIntro:
	.string "MADDY: Dibs on this trainer!\n"
	.string "CROSS: No way, I'll get them first!$"

Route120_Text_MaddyAndCrossDefeated:
	.string "CROSS: Huh!!??\n"
	.string "MADDY: What!!!???$"

Route120_Text_MaddyAndCrossPostBattle:
	.string "MADDY: You totally screwed me up!\n"
	.string "CROSS: No way! You're the one who ruined\l"
	.string "       my perfect strategy...$"

Route120_Text_MaddyAndCrossNeedTwoMons:
	.string "MADDY: Are you even good enough\n"
	.string "       for us?\l"
	.string "CROSS: Let's not even bother\l"
	.string "       with this one.$"

Route120_Text_HectorIntro:
	.string "Let me show you my finest specimens...\n"
	.string "Hee hee.$"

Route120_Text_HectorDefeated:
	.string "You've damaged my collection!\n"
	.string "How dare you!??$"

Route120_Text_HectorPostBattle:
	.string "We Collectors are proud of our rare\n"
	.string "Pokémon. If you happen upon one, you'll\l"
	.string "never know what to expect! Hee hee.$"

Route120_Text_PatrascheIntro:
	.string "Trainer, I must ask for a battle...\n"
	.string "My Linoone and I are rather low\l"
	.string "on money, and selling papers\l"
	.string "is not bringing in enough...$"

Route120_Text_PatrascheDefeated:
	.string "That's more money leaving\n"
	.string "my pockets... sigh...$"

Route120_Text_PatraschePostBattle:
	.string "Flanders and I are inseperable.\n"
	.string "I'd rescued him from almost\l"
	.string "starving after being abandoned...\p"
	.string "Don't worry, we'll find a way\n"
	.string "to make some money.$"

Route120_Text_AmiraIntro:
	.string "Would you like to become a fairy?$"

Route120_Text_AmiraDefeated:
	.string "Not everyone can handle it...$"

Route120_Text_AmiraPostBattle:
	.string "Faefolk are the final step\n"
	.string "in human evolution...$"

Route120_Text_LeileiIntro:
	.string "I've got a RAGE that can\n"
	.string "only be soothed on the BATTLEFIELD!$"

Route120_Text_LeileiDefeated:
	.string "Ah... much calmer...$"

Route120_Text_LeileiPostBattle:
	.string "Breathe in...\n"
	.string "Breathe out...$"

Route120_Text_PathThroughTree:
	.string "(There appears to be a path into\n"
	.string "the thicket through this tree,\l"
	.string "but there are many branches\l"
	.string "in the way...)$"

Route120_Text_WantToUseCut:
	.string "(Would you like to have your\n"
	.string "Pokemon cut through the branches?)$"

Route120_Text_NoCut:
	.string "(...But you have no means of\n"
	.string "cutting through those branches.)$"

Route120_Text_AlreadyCut:
	.string "(The pathway into the thicket\n"
	.string "has been opened.)$"

Route120_Text_CutPathTutorial:
	.string "The way forward through Scuttill\n"
	.string "Way is to cut your own path\l"
	.string "into the thicket of trees!\p"
	.string "That conifer tree straight north\n"
	.string "of me is something you can cut\l"
	.string "a path through. Just interact with\l"
	.string "it like you would one of those\l"
	.string "smaller cut trees like the one you\l"
	.string "cut down to get here. If you\l"
	.string "have a Pokemon with cut, it will\l"
	.string "open up a path into the trees!$"
