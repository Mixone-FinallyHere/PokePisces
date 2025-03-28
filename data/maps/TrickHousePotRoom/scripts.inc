TrickHousePotRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, TrickHousePotRoom_OnLoad
	.byte 0

TrickHousePotRoom_OnLoad:
	call_if_set FLAG_POTTRICIA_DEFEATED, TrickHousePotRoom_EventScript_RemovePottricia
	end

TrickHousePotRoom_EventScript_RemovePottricia::
	setmetatile 4, 1, METATILE_TrickHouseNew_TickHouseDoor, FALSE
	setmetatile 4, 2, METATILE_TrickHouseNew_PottriciaDownLeft, FALSE
	setmetatile 5, 2, METATILE_TrickHouseNew_PottriciaDownMiddle, FALSE
	setmetatile 6, 2, METATILE_TrickHouseNew_PottriciaDownRight, FALSE
	special DrawWholeMapView
	return

TrickHousePotRoom_EventScript_Pottricia::
	lock
	goto_if_set FLAG_POTTRICIA_DEFEATED, TrickHousePotRoom_EventScript_PottriciaPost
	goto TrickHousePotRoom_EventScript_PottriciaBattle
	release
	end

TrickHousePotRoom_EventScript_PottriciaBattle::
	setwildbattle SPECIES_POTTRICIA, 100
	msgbox TrickHousePotRoom_Text_ThisPotIsInYourWay, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	goto TrickHousePotRoom_EventScript_PottriciaDefeat
	release
	end

TrickHousePotRoom_EventScript_PottriciaDefeat::
	msgbox TrickHousePotRoom_Text_AHardEarnedVictory, MSGBOX_DEFAULT
	delay 16
	setmetatile 4, 1, METATILE_TrickHouseNew_TickHouseDoor, FALSE
	setmetatile 4, 2, METATILE_TrickHouseNew_PottriciaDownLeft, FALSE
	setmetatile 5, 2, METATILE_TrickHouseNew_PottriciaDownMiddle, FALSE
	setmetatile 6, 2, METATILE_TrickHouseNew_PottriciaDownRight, FALSE
	special DrawWholeMapView
	setflag FLAG_POTTRICIA_DEFEATED
	playse SE_ICE_CRACK
	waitse
	closemessage
	release
	end

TrickHousePotRoom_EventScript_PottriciaPost::
	msgbox TrickHousePotRoom_Text_PottriciaHasBeenSlain, MSGBOX_AUTOCLOSE
	release
	end

TrickHousePotRoom_Text_ThisPotIsInYourWay:
	.string "(There is a potted plant\n"
	.string "blocking the exit.)\p"
	.string "(It has a name scribbled\n"
	.string "on a tag on its base.)\p"
	.string "“Pottricia”\p"
	.string "…\p"
	.string "(Pottricia is in your way.)\p"
	.string "…$"

TrickHousePotRoom_Text_AHardEarnedVictory:
	.string "(A hard-fought victory.)$"

TrickHousePotRoom_Text_PottriciaHasBeenSlain:
	.string "(Pottricia has been slain.)$"
