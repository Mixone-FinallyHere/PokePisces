RustboroTransitionBuilding_MapScripts::
	.byte 0

RustboroTransitionBuilding_EventScript_RustboroEnterTrigger::
	lock
	goto_if_set FLAG_VISITED_RUSTBORO_CITY, RustboroTransitionBuilding_EventScript_ReleaseOut
	msgbox RustboroTransitionBuilding_Text_CantEnterRustboro, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, RustboroTransitionBuilding_Movement_PlayerBackUp
	waitmovement 0
	release
	end

RustboroTransitionBuilding_Movement_PlayerBackUp:
	walk_down
	step_end

RustboroTransitionBuilding_EventScript_ReleaseOut::
	setvar VAR_TEMP_6, 1
	release
	end

RustboroTransitionBuilding_Text_CantEnterRustboro:
	.string "We're very sorry, but access to\n"
	.string "Rustboro City through the\l"
	.string "main gate is currently prohibited.\l"
	.string "We are investigating reports\l"
	.string "of potential gang members\l"
	.string "infiltrating our city. Until\l"
	.string "we perform our thorough checks,\l"
	.string "no outsiders shall be\l"
	.string "allowed entry.$"
