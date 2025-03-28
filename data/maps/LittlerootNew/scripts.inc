LittlerootNew_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootNew_OnTransition
	.byte 0

LittlerootNew_OnTransition:
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	end

LittlerootNew_EventScript_NormanSign::
    msgbox LittlerootNew_Text_NormanSign, MSGBOX_SIGN
    end

LittlerootNew_EventScript_PenultimaSign::
    msgbox LittlerootNew_Text_PenultimaSign, MSGBOX_SIGN
    end

LittlerootNew_EventScript_LittlerootSign::
    msgbox LittlerootNew_Text_LittlerootSign, MSGBOX_SIGN
    end

LittlerootNew_EventScript_PebblerSign::
    msgbox LittlerootNew_Text_PebblerSign, MSGBOX_SIGN
    end

LittlerootNew_Text_NormanSign:
	.string "Norman's House\n$"

LittlerootNew_Text_PenultimaSign:
	.string "Home of the Starter Pokemon\n"
	.string "Move Tutor, Penultima$"

LittlerootNew_Text_LittlerootSign:
	.string "LITTLEROOT TOWN\n"
	.string "Despite all that may come, the\l"
	.string "nostalgic visage of this town\l"
	.string "shall never fade.$"

LittlerootNew_Text_PebblerSign:
	.string "PEBBLER PLATOON PRODUCTIONS$"
