.set LOCALID_NURSE, 1

PacifidlogTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_PokemonCenter_1F_OnTransition
	.byte 0

PacifidlogTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PACIFIDLOG_TOWN
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Girl::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_Woman::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola, MSGBOX_NPC
	end

PacifidlogTown_PokemonCenter_1F_EventScript_OldMan::
	msgbox PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats, MSGBOX_NPC
	end

PacifidlogTown_EventScript_BlackSheepWoman::
	msgbox PacifidlogTown_Text_BlackSheepWoman, MSGBOX_NPC
	end

PacifidlogTown_EventScript_BoredKidsWoman::
	msgbox PacifidlogTown_Text_BoredKidsWoman, MSGBOX_NPC
	end

PacifidlogTown_EventScript_VisitSadFisher::
	msgbox PacifidlogTown_Text_VisitSadFisher, MSGBOX_NPC
	end

PacifidlogTown_EventScript_MoveNerd::
	msgbox PacifidlogTown_Text_MoveNerd, MSGBOX_NPC
	end

PacifidlogTown_Text_MoveNerd:
	.string "Ever make your Pokemon forget\n"
	.string "a move, and regret that decision\l"
	.string "later? Boy have I!\p"
	.string "You just gotta remember to check\n"
	.string "the relearning menu in your party.\l"
	.string "Your Pokemon are able to relearn\l"
	.string "any move they could have gotten\l"
	.string "via level-up. It comes in\l"
	.string "super handy if you want to test\l"
	.string "out many different movesets!$"

PacifidlogTown_Text_BlackSheepWoman:
	.string "You look like you're about to\n"
	.string "start a big journey! That's great!\l"
	.string "Here, have some advice.\p"
	.string "The absolute best way to find\n"
	.string "consistent success in trainer\l"
	.string "battles? Full preparation!\l"
	.string "Whenever you put someone on your\l"
	.string "team, read up on everything\l"
	.string "about them! Their moves, their\l"
	.string "ability, their stat spread.\l"
	.string "Don't just assume you know\l"
	.string "everything! A successful trainer\l"
	.string "is a knowledgeable trainer.\p"
	.string "Just make sure you read, okay?\n"
	.string "Promise? Fortune will then\l"
	.string "find you, no doubt.$"

PacifidlogTown_Text_BoredKidsWoman:
	.string "My Pokemon are so eager to\n"
	.string "evolve when their time comes!\l"
	.string "They will signal to me when\l"
	.string "they reach their requirement.\l"
	.string "Nevertheless, it always helps\l"
	.string "to check your party once in\l"
	.string "a while to see if one of your\l"
	.string "Pokemon can evolve. Especially\l"
	.string "if they need high friendship,\l"
	.string "like Saintisow!$"

PacifidlogTown_Text_VisitSadFisher:
	.string "You a trainer? Ya got that\n"
	.string "look in your eye.\p"
	.string "If you're wantin' to train\n"
	.string "some fish Pokemon, maybe go hit\l"
	.string "up that one angler at the\l"
	.string "southeastern part of town.\l"
	.string "He's been advertisin'.$"

PacifidlogTown_PokemonCenter_1F_Text_WhatColorTrainerCard:
	.string "What color is your TRAINER CARD?\n"
	.string "Mine's copper!$"

PacifidlogTown_PokemonCenter_1F_Text_OnColonyOfCorsola:
	.string "PACIFIDLOG TOWN floats on top of\n"
	.string "a colony of CORSOLA.\p"
	.string "If I told you that, would you believe\n"
	.string "me?$"

PacifidlogTown_PokemonCenter_1F_Text_AncestorsLivedOnBoats:
	.string "The ancestors of the people in\n"
	.string "PACIFIDLOG were said to have been\l"
	.string "born on boats and then lived and died \l"
	.string "aboard them.\p"
	.string "I understand that they lived that way\n"
	.string "because they were searching for\l"
	.string "something.$"

