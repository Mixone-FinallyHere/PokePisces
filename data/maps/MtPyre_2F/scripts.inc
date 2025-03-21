MtPyre_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F
	end

MtPyre_2F_EventScript_Deacon::
    trainerbattle_single TRAINER_P_DEACON, MtPyre_2F_Text_DeaconIntro, MtPyre_2F_Text_DeaconDefeated
    msgbox MtPyre_2F_Text_DeaconPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_2F_EventScript_Alodia::
    trainerbattle_single TRAINER_P_ALODIA, MtPyre_2F_Text_AlodiaIntro, MtPyre_2F_Text_AlodiaDefeated
    msgbox MtPyre_2F_Text_AlodiaPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_2F_EventScript_Raeliana::
    trainerbattle_single TRAINER_P_RAELIANA, MtPyre_2F_Text_RaelianaIntro, MtPyre_2F_Text_RaelianaDefeated
    msgbox MtPyre_2F_Text_RaelianaPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_2F_EventScript_Morgan::
    trainerbattle_single TRAINER_P_MORGAN, MtPyre_2F_Text_MorganIntro, MtPyre_2F_Text_MorganDefeated
    msgbox MtPyre_2F_Text_MorganPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_2F_EventScript_CheckMia::
	lock
	faceplayer
	checkitem ITEM_SPECTRAL_IDOL
	goto_if_eq VAR_RESULT, TRUE, MtPyre_2F_EventScript_MistyPost
	msgbox MtPyre_2F_Text_MistyGreetings, MSGBOX_DEFAULT
	goto_if_defeated TRAINER_P_MIA, MtPyre_2F_EventScript_CheckMaya
	msgbox MtPyre_2F_Text_MistyNotAllMediumsBeaten, MSGBOX_AUTOCLOSE
	release
	end

MtPyre_2F_EventScript_CheckMaya::
	goto_if_defeated TRAINER_P_MAYA, MtPyre_2F_EventScript_CheckPearl
	msgbox MtPyre_2F_Text_MistyNotAllMediumsBeaten, MSGBOX_AUTOCLOSE
	release
	end

MtPyre_2F_EventScript_CheckPearl::
	goto_if_defeated TRAINER_P_PEARL, MtPyre_2F_EventScript_CheckMorgan
	msgbox MtPyre_2F_Text_MistyNotAllMediumsBeaten, MSGBOX_AUTOCLOSE
	release
	end

MtPyre_2F_EventScript_CheckMorgan::
	goto_if_defeated TRAINER_P_MORGAN, MtPyre_2F_EventScript_Misty
	msgbox MtPyre_2F_Text_MistyNotAllMediumsBeaten, MSGBOX_AUTOCLOSE
	release
	end

MtPyre_2F_EventScript_Misty::
    trainerbattle_single TRAINER_P_MISTY, MtPyre_2F_Text_MistyIntro, MtPyre_2F_Text_MistyDefeated, MtPyre_2F_EventScript_GiveCleanseTag
    msgbox MtPyre_2F_Text_MistyPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_2F_EventScript_GiveCleanseTag::
	msgbox MtPyre_2F_Text_HaveSpectralIdol, MSGBOX_DEFAULT
	giveitem ITEM_SPECTRAL_IDOL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	release
	end

MtPyre_2F_EventScript_MistyPost::
	msgbox MtPyre_2F_Text_MistyPostBattle, MSGBOX_AUTOCLOSE
	release
    end

MtPyre_2F_EventScript_Teleporter::
	lock
	faceplayer
	msgbox MtPyre_2F_Text_WouldYouLikeToWarp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MtPyre_2F_EventScript_WarpToCave
	msgbox MtPyre_2F_Text_MaybeAnotherTime, MSGBOX_AUTOCLOSE
	release
	end

MtPyre_2F_EventScript_WarpToCave::
	warp MAP_THE_COLD_MINES, 6, 13
	release
	end

MtPyre_2F_Text_WouldYouLikeToWarp:
	.string "My elder sibling is currently\n"
	.string "snooping about a hidden passage\l"
	.string "in the Cold Mines...\p"
	.string "If you would like to visit her,\n"
	.string "I have the ability to warp\l"
	.string "you across space...$"

MtPyre_2F_Text_MaybeAnotherTime:
	.string "Not everyone can handle warping...$"

MtPyre_2F_Text_DeaconIntro:
	.string "I can sense your aura.$"

MtPyre_2F_Text_DeaconDefeated:
	.string "It would seem your aura dwarfs my own.$"

MtPyre_2F_Text_DeaconPostBattle:
	.string "I will need to meditate on this loss.$"

MtPyre_2F_Text_AlodiaIntro:
	.string "I dance, I call! Each step\n"
	.string "shakes my very soul!$"

MtPyre_2F_Text_AlodiaDefeated:
	.string "We who sing and dance\n"
	.string "the language of dragons!$"

MtPyre_2F_Text_AlodiaPostBattle:
	.string "I dance, I call! Each step\n"
	.string "quakes my body whole!$"

MtPyre_2F_Text_RaelianaIntro:
	.string "Zotpyre Shrine... elegant,\n"
	.string "yet bearing malevolent energy...\p"
	.string "Oh-ho-ho... it reminds me of\n"
	.string "yours truly...$"

MtPyre_2F_Text_RaelianaDefeated:
	.string "I take my defeat\n"
	.string "with honor and grace.$"

MtPyre_2F_Text_RaelianaPostBattle:
	.string "Compose yourself, trainer.\n"
	.string "Lest you stick around in the\l"
	.string "afterlife...$"

MtPyre_2F_Text_MorganIntro:
	.string "GET...\n"
	.string "                ...OUT!$"

MtPyre_2F_Text_MorganDefeated:
	.string "...Or keep going.\n"
	.string "I'm not a cop.$"

MtPyre_2F_Text_MorganPostBattle:
	.string "...$"

MtPyre_2F_Text_MistyIntro:
	.string "Ah... you have placated them...\n"
	.string "my beloved family...\p"
	.string "It will not be long before the\n"
	.string "malevolent spirits leave their\l"
	.string "bodies... thank you.\p"
	.string "I simply must test the meddle\n"
	.string "of a trainer of your caliber...\l"
	.string "If you could handle the others\l"
	.string "of the Fey Family, surely\l"
	.string "you can withstand my onslaught?$"

MtPyre_2F_Text_MistyDefeated:
	.string "Your soul remains pure...$"

MtPyre_2F_Text_MistyPostBattle:
	.string "...$"

MtPyre_2F_Text_MistyNotAllMediumsBeaten:
	.string "They are suffering. I sense that\n"
	.string "Mia, Maya, Pearl, and Morgan have\l"
	.string "all been terribly possessed...\p"
	.string "Please, seek them out...\n"
	.string "they will be aggressive, no doubt...\l"
	.string "but their souls must be placated.$"

MtPyre_2F_Text_MistyGreetings:
	.string "The various spirit mediums that\n"
	.string "you have no doubt run into\l"
	.string "in your travels up to this point...$"

MtPyre_2F_Text_HaveSpectralIdol:
	.string "Please, trainer... you must\n"
	.string "take this totem with you...\p"
	.string "It has likewise been possessed...\n"
	.string "but, mayhaps, it can be of use...$"
