.set LOCALID_DEVONEMPLOYEE, 1

RustboroNew_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroNew_OnTransition
	.byte 0

RustboroNew_OnTransition:
	setflag FLAG_VISITED_RUSTBORO_CITY
	end

RustboroNew_EventScript_DevonEncounterStartUpLeft::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, RustboroNew_Movement_PlayerStartUpLeft
	waitmovement 0
	applymovement LOCALID_DEVONEMPLOYEE, RustboroNew_Movement_EmployeeStartUpLeft
	waitmovement 0
	delay 4
	goto RustboroNew_EventScript_DevonEncounter
	release
	end

RustboroNew_Movement_PlayerStartUpLeft:
	face_right
	step_end

RustboroNew_Movement_EmployeeStartUpLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RustboroNew_EventScript_DevonEncounterStartDownLeft::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, RustboroNew_Movement_PlayerStartDownLeft
	waitmovement 0
	applymovement LOCALID_DEVONEMPLOYEE, RustboroNew_Movement_EmployeeStartDownLeft
	waitmovement 0
	delay 4
	goto RustboroNew_EventScript_DevonEncounter
	release
	end

RustboroNew_Movement_PlayerStartDownLeft:
	face_right
	step_end

RustboroNew_Movement_EmployeeStartDownLeft:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RustboroNew_EventScript_DevonEncounterStartDown::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, RustboroNew_Movement_PlayerStartDown
	waitmovement 0
	applymovement LOCALID_DEVONEMPLOYEE, RustboroNew_Movement_EmployeeStartDown
	waitmovement 0
	delay 4
	goto RustboroNew_EventScript_DevonEncounter
	release
	end

RustboroNew_Movement_PlayerStartDown:
	face_up
	step_end

RustboroNew_Movement_EmployeeStartDown:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

RustboroNew_EventScript_DevonEncounterStartDownRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, RustboroNew_Movement_PlayerStartDownRight
	waitmovement 0
	applymovement LOCALID_DEVONEMPLOYEE, RustboroNew_Movement_EmployeeStartDownRight
	waitmovement 0
	delay 4
	goto RustboroNew_EventScript_DevonEncounter
	release
	end

RustboroNew_Movement_PlayerStartDownRight:
	face_right
	step_end

RustboroNew_Movement_EmployeeStartDownRight:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RustboroNew_EventScript_DevonEncounterStartUpRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, RustboroNew_Movement_PlayerStartUpRight
	waitmovement 0
	applymovement LOCALID_DEVONEMPLOYEE, RustboroNew_Movement_EmployeeStartUpRight
	waitmovement 0
	delay 4
	goto RustboroNew_EventScript_DevonEncounter
	release
	end

RustboroNew_Movement_PlayerStartUpRight:
	face_right
	step_end

RustboroNew_Movement_EmployeeStartUpRight:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RustboroNew_EventScript_DevonEncounter::
	setvar VAR_RUST_GYM_STATE, 15
	msgbox RustboroNew_Text_DevonNeedsYou, MSGBOX_DEFAULT
	closemessage
	release
	end

RustboroNew_EventScript_DevonEnterTrigger::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, RustboroNew_Movement_PlayerIntoBuilding
	waitmovement 0
	warp MAP_DEVON_CORP, 12, 33
	waitstate
	release
	end

RustboroNew_Movement_PlayerIntoBuilding:
	walk_up
	step_end

RustboroNew_EventScript_DevonEmployee::
	lock
	faceplayer
	goto_if_ge VAR_RUST_GYM_STATE, 15, RustboroNew_EventScript_DontBeLate
	msgbox RustboroNew_Text_OurPresident, MSGBOX_AUTOCLOSE
	release
	end

RustboroNew_EventScript_DontBeLate::
	msgbox RustboroNew_Text_DontBeLate, MSGBOX_AUTOCLOSE
	release
	end

RustboroNew_EventScript_RustboroSign::
    msgbox RustboroNew_Text_RustboroSign, MSGBOX_SIGN
    end

RustboroNew_EventScript_UnduraSign::
    msgbox RustboroNew_Text_UnduraSign, MSGBOX_SIGN
    end

RustboroNew_EventScript_GymSign::
    msgbox RustboroNew_Text_GymSign, MSGBOX_SIGN
    end

RustboroNew_EventScript_DevonSign::
    msgbox RustboroNew_Text_DevonSign, MSGBOX_SIGN
    end

RustboroNew_EventScript_BridgeSign::
    msgbox RustboroNew_Text_BridgeSign, MSGBOX_SIGN
    end

RustboroNew_EventScript_WhisperCliffSign::
    msgbox RustboroNew_Text_WhisperCliffSign, MSGBOX_SIGN
    end

RustboroNew_Text_RustboroSign:
	.string "RUSTBORO CITY\n"
	.string "A Metropolis Where Education\l"
	.string "Takes Center Stage.$"

RustboroNew_Text_UnduraSign:
	.string "TO UNDURA TUNNELS\n"
	.string "Diving Gear Suggested!$"

RustboroNew_Text_GymSign:
	.string "RUSTBORO UNIVERSITY\n"
	.string "AKA, RUSTBORO GYM$"

RustboroNew_Text_DevonSign:
	.string "Devon Corp. Headquarters$"

RustboroNew_Text_BridgeSign:
	.string "RUSTBORO BRIDGE\n"
	.string "You are currently leaving\l"
	.string "city limits! The bridge will\l"
	.string "link you up with the Mt. Chimney\l"
	.string "region to the north. Be sure\l"
	.string "to bring a Pokemon who can take\l"
	.string "you across the water!$"

RustboroNew_Text_WhisperCliffSign:
	.string "NORTH - WHISPER CLIFF\n"
	.string "Connection to ETHEOR FALLS\l"
	.string "to the EAST$"

RustboroNew_Text_DevonNeedsYou:
	.string "Greetings!\n"
	.string "If I have the right information,\l"
	.string "your name is {PLAYER}.\p"
	.string "You have been summoned\n"
	.string "to the President of\l"
	.string "Devon Corp's office.\p"
	.string "It is quite the urgent matter.\n"
	.string "Please come to our building\l"
	.string "as soon as possible.$"

RustboroNew_Text_OurPresident:
	.string "I am often tasked with delivering\n"
	.string "messages on behalf of Devon Corp's\l"
	.string "President.\p"
	.string "You have not been summoned. You would\n"
	.string "definitely know if you were.$"

RustboroNew_Text_DontBeLate:
	.string "Please do not keep our President\n"
	.string "waiting much longer.$"
