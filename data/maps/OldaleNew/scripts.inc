OldaleNew_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleNew_OnTransition
	.byte 0

OldaleNew_OnTransition:
	setflag FLAG_VISITED_OLDALE_TOWN
	end

OldaleNew_EventScript_Natasha::
    trainerbattle_single TRAINER_P_NATASHA, OldaleNew_Text_NatashaIntro, OldaleNew_Text_NatashaDefeated
    msgbox OldaleNew_Text_NatashaPostBattle, MSGBOX_AUTOCLOSE
    end

OldaleNew_EventScript_ChoiceItems::
	lock
	faceplayer
	goto_if_set FLAG_CHOICE_ITEM_3, OldaleNew_EventScript_MadeYourChoice
	msgbox OldaleNew_Text_PickAChoiceItem, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_CHOICE_ITEM_PICK, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	goto_if_eq VAR_TEMP_1, 0, OldaleNew_EventScript_GiveChoiceBand
	goto_if_eq VAR_TEMP_1, 1, OldaleNew_EventScript_GiveChoiceSpecs
	goto_if_eq VAR_TEMP_1, 2, OldaleNew_EventScript_GiveChoiceScarf
	msgbox OldaleNew_Text_ChoiceParalysis, MSGBOX_DEFAULT
	closemessage
	release
	end

OldaleNew_EventScript_GiveChoiceBand::
	closemessage
	giveitem ITEM_CHOICE_BAND
	closemessage
	setflag FLAG_CHOICE_ITEM_3
	msgbox OldaleNew_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

OldaleNew_EventScript_GiveChoiceSpecs::
	closemessage
	giveitem ITEM_CHOICE_SPECS
	closemessage
	setflag FLAG_CHOICE_ITEM_3
	msgbox OldaleNew_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

OldaleNew_EventScript_GiveChoiceScarf::
	closemessage
	giveitem ITEM_CHOICE_SCARF
	closemessage
	setflag FLAG_CHOICE_ITEM_3
	msgbox OldaleNew_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

OldaleNew_EventScript_MadeYourChoice::
	msgbox OldaleNew_Text_MadeYourChoice, MSGBOX_AUTOCLOSE
	release
	end

OldaleNew_EventScript_OldaleSign::
    msgbox OldaleNew_Text_OldaleSign, MSGBOX_SIGN
    end

OldaleNew_EventScript_WoodsSign::
    msgbox OldaleNew_Text_WoodsSign, MSGBOX_SIGN
    end

OldaleNew_EventScript_HatchloamSign::
    msgbox OldaleNew_Text_HatchloamSign, MSGBOX_SIGN
    end

OldaleNew_EventScript_NovicesWalkSign::
    msgbox OldaleNew_Text_NovicesWalkSign, MSGBOX_SIGN
    end

OldaleNew_Text_OldaleSign:
	.string "OLDALE TOWN\n"
	.string "Settle down into quiet mundanity.$"

OldaleNew_Text_WoodsSign:
	.string "PETALBURG WOODS AHEAD$"

OldaleNew_Text_HatchloamSign:
	.string "NORTH - HATCHLOAM FIELD$"

OldaleNew_Text_NovicesWalkSign:
	.string "SOUTH - NOVICE'S WALK$"

OldaleNew_Text_PickAChoiceItem:
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

OldaleNew_Text_ChoiceParalysis:
	.string "You must have choice paralysis!\n"
	.string "How very weak!$"

OldaleNew_Text_MadeYourChoice:
	.string "You have now made your choice!\n"
	.string "And you must live with that.$"

OldaleNew_Text_NatashaIntro:
	.string "Hello! I'm Natasha, an Oldale doctor.\n"
	.string "Feeling sick?$"

OldaleNew_Text_NatashaDefeated:
	.string "Sick... of trainers encountering\n"
	.string "you when you want to go heal?$"

OldaleNew_Text_NatashaPostBattle:
	.string "I know, that was a bit dirty.\n"
	.string "I apologize. I just thought it\l"
	.string "would be rather humorous.$"
