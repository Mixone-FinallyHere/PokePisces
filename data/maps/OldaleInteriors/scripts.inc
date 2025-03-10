OldaleInteriors_MapScripts::
	.byte 0

OldaleInteriors_EventScript_TreasureSeeker::
	lock
	faceplayer
	goto_if_set FLAG_CHOSE_SANDSTONE, OldaleInteriors_EventScript_AskToSeeDunewich
	goto_if_set FLAG_CHOSE_SANDBAG, OldaleInteriors_EventScript_AskToSeeMajadijunn
	msgbox OldaleInteriors_Text_FriendIsHuntingTreasure, MSGBOX_AUTOCLOSE
	release
	end

OldaleInteriors_EventScript_AskToSeeDunewich::
	goto_if_set FLAG_CHOSE_SANDBAG, OldaleInteriors_EventScript_AllItemsGiven
	msgbox OldaleInteriors_Text_AskToSeeDunewich, MSGBOX_DEFAULT
	getcaughtmon SPECIES_DUNEWICH
	goto_if_eq VAR_RESULT, TRUE, OldaleInteriors_EventScript_GiveSandbag
	msgbox OldaleInteriors_Text_NoDunewich, MSGBOX_AUTOCLOSE
	release
	end

OldaleInteriors_EventScript_GiveSandbag::
	msgbox OldaleInteriors_Text_ThereIsDunewich, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SANDBAG
	closemessage
	setflag FLAG_CHOSE_SANDBAG
	goto OldaleInteriors_EventScript_GiveCoarseSand
	release
	end

OldaleInteriors_EventScript_AskToSeeMajadijunn::
	goto_if_set FLAG_CHOSE_SANDSTONE, OldaleInteriors_EventScript_AllItemsGiven
	msgbox OldaleInteriors_Text_AskToSeeMajadijunn, MSGBOX_DEFAULT
	getcaughtmon SPECIES_MAJADIJUNN
	goto_if_eq VAR_RESULT, TRUE, OldaleInteriors_EventScript_GiveSandstone
	msgbox OldaleInteriors_Text_NoMajadijunn, MSGBOX_AUTOCLOSE
	release
	end

OldaleInteriors_EventScript_GiveSandstone::
	msgbox OldaleInteriors_Text_ThereIsMajadijunn, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_SANDSTONE
	closemessage
	setflag FLAG_CHOSE_SANDSTONE
	goto OldaleInteriors_EventScript_GiveCoarseSand
	release
	end

OldaleInteriors_EventScript_GiveCoarseSand::
	msgbox OldaleInteriors_Text_AlsoCouldUseThis, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_COARSE_SAND
	closemessage
	release
	end

OldaleInteriors_EventScript_AllItemsGiven::
	msgbox OldaleInteriors_Text_AllItemsGiven, MSGBOX_AUTOCLOSE
	release
	end

OldaleInteriors_Text_FriendIsHuntingTreasure:
	.string "My brother-in-hunting is out\n"
	.string "there somewhere looking for\l"
	.string "bountiful treasure.\l"
	.string "Maybe you'll find him someday.$"

OldaleInteriors_Text_AskToSeeDunewich:
	.string "I have a question for you.\n"
	.string "Have you been in possession\l"
	.string "of the Pokemon Pebbler?\l"
	.string "If so, have you evolved it\l"
	.string "into Dunewich?\p"
	.string "I hear the item needed to evolve\n"
	.string "that Pokemon is rather rare.\l"
	.string "I would love to see its Pokedex\l"
	.string "entry if you managed it!$"

OldaleInteriors_Text_NoDunewich:
	.string "Ah, I suppose not.\n"
	.string "That's a shame!$"

OldaleInteriors_Text_ThereIsDunewich:
	.string "Oh, there it is! You needed\n"
	.string "the Sandstone to evolve that\l"
	.string "Pebbler, correct?\p"
	.string "I am actually holding on to\n"
	.string "a Sandbag, the other item\l"
	.string "needed for Pebbler's alternative\l"
	.string "evolution method. Since you're\l"
	.string "such an enthusiast already,\l"
	.string "why don't you take it?$"

OldaleInteriors_Text_AskToSeeMajadijunn:
	.string "I have a question for you.\n"
	.string "Have you been in possession\l"
	.string "of the Pokemon Pebbler?\l"
	.string "If so, have you evolved it\l"
	.string "into Majadijunn?\p"
	.string "I hear the item needed to evolve\n"
	.string "that Pokemon is rather rare.\l"
	.string "I would love to see its Pokedex\l"
	.string "entry if you managed it!$"

OldaleInteriors_Text_NoMajadijunn:
	.string "Ah, I suppose not.\n"
	.string "That's a shame!$"

OldaleInteriors_Text_ThereIsMajadijunn:
	.string "Oh, there it is! You needed\n"
	.string "the Sandbag to evolve that\l"
	.string "Pebbler, correct?\p"
	.string "I am actually holding on to\n"
	.string "a Sandstone, the other item\l"
	.string "needed for Pebbler's alternative\l"
	.string "evolution method. Since you're\l"
	.string "such an enthusiast already,\l"
	.string "why don't you take it?$"

OldaleInteriors_Text_AlsoCouldUseThis:
	.string "There's also this special\n"
	.string "sand I have collected for an\l"
	.string "art display that my very own\l"
	.string "Pebbler seems to enjoy.\l"
	.string "I'm sure yours will too!$"

OldaleInteriors_Text_AllItemsGiven:
	.string "Pebbler is a Pokemon that\n"
	.string "is very susceptible to stimuli!\l"
	.string "It can evolve in a couple of ways.\l"
	.string "The Sandbag and Sandstone being\l"
	.string "the main two, but rumors tell\l"
	.string "of an alternative third path\l"
	.string "for Pebbler to evolve...$"
