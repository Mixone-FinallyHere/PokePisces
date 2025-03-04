CrimneyInteriors_MapScripts::
	.byte 0

CrimneyInteriors_EventScript_CableCarMasonriedSide::
	lock
	faceplayer
	goto_if_unset FLAG_CABLE_CAR_UNLOCKED, CrimneyInteriors_EventScript_CableCarWorkedOn
	msgbox CrimneyInteriors_Text_RideCarToCrimney, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CrimneyInteriors_EventScript_WarpToCrimney
	closemessage
	release
	end

CrimneyInteriors_EventScript_CableCarWorkedOn::
	msgbox CrimneyInteriors_Text_CableCarWorkedOn, MSGBOX_AUTOCLOSE
	release
	end

CrimneyInteriors_EventScript_WarpToCrimney::
	warp MAP_CRIMNEY_INTERIORS, 26, 7
	waitstate
	release
	end

CrimneyInteriors_EventScript_CableCarCrimneySide::
	lock
	faceplayer
	setflag FLAG_CABLE_CAR_UNLOCKED
	msgbox CrimneyInteriors_Text_RideCarToMasonried, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CrimneyInteriors_EventScript_WarpToMasonried
	closemessage
	release
	end

CrimneyInteriors_EventScript_WarpToMasonried::
	warp MAP_CRIMNEY_INTERIORS, 6, 7
	waitstate
	release
	end

CrimneyInteriors_Text_CableCarWorkedOn:
	.string "Ey, sorry there paisano.\n"
	.string "Can't be lettin' ya on the\l"
	.string "cable car path right now.\l"
	.string "Fixin' a few kinks what with\l"
	.string "the electrical lines.\p"
	.string "You're gonna have to hoof it\n"
	.string "up the mountain if ya have\l"
	.string "any business up there.$"

CrimneyInteriors_Text_RideCarToCrimney:
	.string "You lookin' to ride the cable car\n"
	.string "to the west side of the mountain?$"

CrimneyInteriors_Text_RideCarToMasonried:
	.string "You fixin' to take the cable car\n"
	.string "to the east side of the mountain?$"
