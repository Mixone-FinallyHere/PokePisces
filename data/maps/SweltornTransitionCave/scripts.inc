SweltornTransitionCave_MapScripts::
	.byte 0

SweltornTransitionCave_EventScript_OzoneSign::
	msgbox SweltornTransitionCave_Text_OzoneSign, MSGBOX_SIGN
	end

SweltornTransitionCave_EventScript_LavaridgeSign::
	msgbox SweltornTransitionCave_Text_LavaridgeSign, MSGBOX_SIGN
	end

SweltornTransitionCave_EventScript_DesertSign::
	msgbox SweltornTransitionCave_Text_DesertSign, MSGBOX_SIGN
	end

SweltornTransitionCave_EventScript_NewMauvilleSign::
	msgbox SweltornTransitionCave_Text_NewMauvilleSign, MSGBOX_SIGN
	end

SweltornTransitionCave_Text_OzoneSign:
	.string "OZONE INSTITUTE EXIT$"

SweltornTransitionCave_Text_LavaridgeSign:
	.string "LAVARIDGE TOWN EXIT$"

SweltornTransitionCave_Text_DesertSign:
	.string "LEADS BACK TO SWELTORN DESERT$"

SweltornTransitionCave_Text_NewMauvilleSign:
	.string "NEW MAUVILLE EXIT$"
