.set LOCALID_GYMBLOCKER, 1

DewfordNew_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, DewfordNew_OnLoad
	.byte 0

DewfordNew_OnLoad:
	setflag FLAG_VISITED_DEWFORD_TOWN
	call DewfordNew_EventScript_SetTempFlag
	call_if_set FLAG_TEMP_12, DewfordNew_EventScript_RemoveGymBlock
	end

DewfordNew_EventScript_SetTempFlag::
	goto_if_set FLAG_FOUND_SHELLY, DewfordNew_EventScript_CheckBrawly
	return

DewfordNew_EventScript_CheckBrawly::
	goto_if_set FLAG_FOUND_BRAWLY, DewfordNew_EventScript_TempFlagSet
	return

DewfordNew_EventScript_TempFlagSet::
	setflag FLAG_TEMP_12
	return

DewfordNew_EventScript_RemoveGymBlock::
	removeobject LOCALID_GYMBLOCKER
	setflag FLAG_TEMP_11
	return

DewfordNew_EventScript_GymBlock::
	lock
	faceplayer
	goto_if_set FLAG_FOUND_SHELLY, DewfordNew_EventScript_GoFindBrawly
	goto_if_set FLAG_FOUND_BRAWLY, DewfordNew_EventScript_GoFindShelly
	msgbox DewfordNew_Text_GoFindTheLeaders, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_GoFindShelly::
	msgbox DewfordNew_Text_GoFindShelly, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_GoFindBrawly::
	msgbox DewfordNew_Text_GoFindBrawly, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_BrineyFastTravel::
	lock
	faceplayer
	clearflag FLAG_BRINEY_MIDGAME_VISIT
	setflag FLAG_BRINEY_DEWFORD_VISIT
	speakername DewfordNew_Text_NameBriney
	msgbox DewfordNew_Text_WantToVoyage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordNew_EventScript_WarpToTidal
	msgbox DewfordNew_Text_IllBeHere, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

DewfordNew_EventScript_WarpToTidal::
	msgbox DewfordNew_Text_BonVoyage, MSGBOX_DEFAULT
	speakername NULL
	warp MAP_SS_TIDAL_MID_TERIORS, 33, 4
	release
	end

DewfordNew_EventScript_Shellylouh::
	lock
	faceplayer
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_3, DewfordNew_EventScript_ShellyBrewShop
	goto_if_set FLAG_BADGE07_GET, DewfordNew_EventScript_ShellyBrewActivateShop
	msgbox DewfordNew_Text_ShellRiddle, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_ShellyBrewActivateShop::
	msgbox DewfordNew_Text_UnlockedShop, MSGBOX_DEFAULT
	setflag FLAG_SHELLYLOUH_RIDDLE_3
	giveitem ITEM_SHELLY_BREW
	goto DewfordNew_EventScript_ShellyBrewShop
	release
	end

DewfordNew_EventScript_ShellyBrewShop::
	showmoneybox 0, 0
	msgbox DewfordNew_Text_WillYouBuyShellyBrew, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordNew_EventScript_CheckMoneyForSB
	closemessage
	hidemoneybox
	goto DewfordNew_EventScript_SeekOutOtherShelly
	release
	end

DewfordNew_EventScript_CheckMoneyForSB::
	checkmoney 5000
	goto_if_eq VAR_RESULT, FALSE, DewfordNew_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 5000
	updatemoneybox
	delay 40
	hidemoneybox
	giveitem ITEM_SHELLY_BREW
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	delay 4
	goto DewfordNew_EventScript_ShellyBrewShop
	release
	end

DewfordNew_EventScript_NotEnoughMoney::
	msgbox DewfordNew_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	goto DewfordNew_EventScript_SeekOutOtherShelly
	release
	end

DewfordNew_EventScript_SeekOutOtherShelly::
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_1, DewfordNew_EventScript_CheckRiddle2
	msgbox DewfordNew_Text_SeekOutOtherShelly, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_CheckRiddle2::
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_2, DewfordNew_EventScript_AllRiddles
	msgbox DewfordNew_Text_SeekOutOtherShelly, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_AllRiddles::
	checkitem ITEM_BIG_PEARL
	goto_if_eq VAR_RESULT, TRUE, DewfordNew_EventScript_GaveBigPearl
	msgbox DewfordNew_Text_YouEarnedThisBigPearl, MSGBOX_DEFAULT
	giveitem ITEM_BIG_PEARL
	closemessage
	release
	end

DewfordNew_EventScript_GaveBigPearl::
	msgbox DewfordNew_Text_GaveBigPearl, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_ChoiceItems::
	lock
	faceplayer
	goto_if_set FLAG_CHOICE_ITEM_2, DewfordNew_EventScript_MadeYourChoice
	msgbox DewfordNew_Text_PickAChoiceItem, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_CHOICE_ITEM_PICK, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	goto_if_eq VAR_TEMP_1, 0, DewfordNew_EventScript_GiveChoiceBand
	goto_if_eq VAR_TEMP_1, 1, DewfordNew_EventScript_GiveChoiceSpecs
	goto_if_eq VAR_TEMP_1, 2, DewfordNew_EventScript_GiveChoiceScarf
	msgbox DewfordNew_Text_ChoiceParalysis, MSGBOX_DEFAULT
	closemessage
	release
	end

DewfordNew_EventScript_GiveChoiceBand::
	closemessage
	giveitem ITEM_CHOICE_BAND
	closemessage
	setflag FLAG_CHOICE_ITEM_2
	msgbox DewfordNew_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_GiveChoiceSpecs::
	closemessage
	giveitem ITEM_CHOICE_SPECS
	closemessage
	setflag FLAG_CHOICE_ITEM_2
	msgbox DewfordNew_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_GiveChoiceScarf::
	closemessage
	giveitem ITEM_CHOICE_SCARF
	closemessage
	setflag FLAG_CHOICE_ITEM_2
	msgbox DewfordNew_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_EventScript_MadeYourChoice::
	msgbox DewfordNew_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

DewfordNew_Text_PickAChoiceItem:
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

DewfordNew_Text_ChoiceParalysis:
	.string "You must have choice paralysis!\n"
	.string "How very weak!$"

DewfordNew_Text_MadeYourChoice:
	.string "You have now made your choice!\n"
	.string "And you must live with that.$"

DewfordNew_Text_GaveBigPearl:
	.string "We have a fondness for you\n"
	.string "for always helping Shellylouh!$"

DewfordNew_Text_ShellRiddle:
	.string "You must beat Shelly in the\n"
	.string "Dewford Gym to unlock this shop.\l"
	.string "This is debug text.$"

DewfordNew_Text_UnlockedShop:
	.string "You've unlocked the Shelly Brew shop!\n"
	.string "Take one as a sample.$"

DewfordNew_Text_WillYouBuyShellyBrew:
	.string "Would you like to buy\n"
	.string "another Shelly Brew?$"

DewfordNew_Text_NotEnoughMoney:
	.string "You don't have enough money...$"

DewfordNew_Text_SeekOutOtherShelly:
	.string "There may yet be more of my kind\n"
	.string "At peaceful beaches, shall you find\l"
	.string "Solve their riddles with haste\l"
	.string "And your effort won't go to waste$"

DewfordNew_Text_YouEarnedThisBigPearl:
	.string "All of our coven stand impressed\n"
	.string "with your pursuing of our quest\l"
	.string "A pearl that shines above all ores\l"
	.string "you are able to now call... yours.$"

DewfordNew_Text_NameBriney:
	.string "Cpt. Briney$"

DewfordNew_Text_GoFindTheLeaders:
	.string "Dewford Gym is currently closed!\n"
	.string "Sorry, but both Gym Leaders\l"
	.string "got called away to investigate\l"
	.string "suspicious activity at sea.\l"
	.string "I pray nothing is\l"
	.string "seriously wrong...\p"
	.string "They both went eastward to the\n"
	.string "oceanic routes around the\l"
	.string "Pacifidlog, Sootopolis, and\l"
	.string "Mossdeep areas. I sure\l"
	.string "hope they make it back safely...$"

DewfordNew_Text_GoFindShelly:
	.string "Dewford Gym is currently closed!\n"
	.string "Sorry, but Shelly is still\l"
	.string "somewhere out at sea.\l"
	.string "Can't open the gym without\l"
	.string "one of its leaders!\p"
	.string "I had heard from Brawly that\n"
	.string "she went to Sailor's Pause\l"
	.string "to investigate suspicious\l"
	.string "activity... hmm.$"

DewfordNew_Text_GoFindBrawly:
	.string "Dewford Gym is currently closed!\n"
	.string "Sorry, but Brawly is still\l"
	.string "somewhere out at sea.\l"
	.string "Can't open the gym without\l"
	.string "one of its leaders!\p"
	.string "I had heard from Shelly that\n"
	.string "he went to Precipike Bluff\l"
	.string "to investigate suspicious\l"
	.string "activity... hmm.$"

DewfordNew_Text_WantToVoyage:
	.string "Ahoy there {PLAYER}!\p"
	.string "The Tidal is docked and\n"
	.string "itching for another voyage.\p"
	.string "Will you be joining us?$"

DewfordNew_Text_IllBeHere:
	.string "You're always welcome aboard!\n"
	.string "Have a good one.$"

DewfordNew_Text_BonVoyage:
	.string "About time to haul anchor, then!$"
