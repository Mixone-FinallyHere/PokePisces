OzoneTransitionBuildings_MapScripts::
	.byte 0

OzoneTransitionBuildings_EventScript_SandSign::
	msgbox OzoneTransitionBuildings_Text_SandSign, MSGBOX_SIGN
	end

OzoneTransitionBuildings_EventScript_HailSign::
	msgbox OzoneTransitionBuildings_Text_HailSign, MSGBOX_SIGN
	end

OzoneTransitionBuildings_Text_SandSign:
	.string "Access to Sweltorn Desert ahead!\n"
	.string "Protective eyewear recommended.$"

OzoneTransitionBuildings_Text_HailSign:
	.string "Access to the Cold Mines ahead!\n"
	.string "Protective headgear recommended.$"
