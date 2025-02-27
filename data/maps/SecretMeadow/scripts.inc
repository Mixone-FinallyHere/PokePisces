SecretMeadow_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SecretMeadow_OnLoad
	.byte 0

SecretMeadow_OnLoad:
	call_if_set FLAG_DEFEATED_YOLKWEEN, SecretMeadow_EventScript_RemoveYolkween
	end

SecretMeadow_EventScript_RemoveYolkween::
	setvar VAR_TEMP_4, 1
	setmetatile 11, 7, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 12, 7, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 13, 7, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 11, 8, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 12, 8, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 13, 8, METATILE_BossArenas_YolkGrass, FALSE
	special DrawWholeMapView
	return

SecretMeadow_EventScript_YolkweenTrigger1::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, SecretMeadow_Movement_GotoYolkween1
	waitmovement 0
	goto SecretMeadow_EventScript_YolkweenBattle
	release
	end

SecretMeadow_Movement_GotoYolkween1:
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

SecretMeadow_EventScript_YolkweenTrigger2::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, SecretMeadow_Movement_GotoYolkween2
	waitmovement 0
	goto SecretMeadow_EventScript_YolkweenBattle
	release
	end

SecretMeadow_Movement_GotoYolkween2:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

SecretMeadow_EventScript_YolkweenTrigger3::
	lock
	delay 4
	applymovement OBJ_EVENT_ID_PLAYER, SecretMeadow_Movement_GotoYolkween3
	waitmovement 0
	goto SecretMeadow_EventScript_YolkweenBattle
	release
	end

SecretMeadow_Movement_GotoYolkween3:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

SecretMeadow_EventScript_YolkweenBattle::
	setwildbattle SPECIES_YOLKWEEN, 66
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 1, 1, 1, 1
	playmoncry SPECIES_YOLKWEEN, CRY_MODE_NORMAL
	delay 40
	waitmoncry
	msgbox SecretMeadow_Text_ItsTheQueen, MSGBOX_DEFAULT
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	setflag FLAG_DEFEATED_YOLKWEEN
	setvar VAR_TEMP_4, 1
	setmetatile 11, 7, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 12, 7, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 13, 7, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 11, 8, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 12, 8, METATILE_BossArenas_YolkGrass, FALSE
	setmetatile 13, 8, METATILE_BossArenas_YolkGrass, FALSE
	special DrawWholeMapView
	msgbox SecretMeadow_Text_ItLeftBehindSomething, MSGBOX_DEFAULT
	closemessage
	goto SecretMeadow_EventScript_ReceiveEgg
	release
	end

SecretMeadow_EventScript_ReceiveEgg::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EXEGGCUTE
	giveegg SPECIES_TAILLOW
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, SecretMeadow_EventScript_ReceiveEggParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, SecretMeadow_EventScript_ReceiveEggPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

SecretMeadow_EventScript_ReceiveEggParty::
	call SecretMeadow_EventScript_ReceivedEggFanfare
	release
	end

SecretMeadow_EventScript_ReceiveEggPC::
	call SecretMeadow_EventScript_ReceivedEggFanfare
	call Common_EventScript_TransferredToPC
	release
	end

SecretMeadow_EventScript_ReceivedEggFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message SecretMeadow_Text_PlayerReceivedEgg
	waitmessage
	waitfanfare
	closemessage
	return

SecretMeadow_Text_ItsTheQueen:
	.string "(You look on in awe at what appears\n"
	.string "to be the matriarch of all\l"
	.string "Wannegg and Eggneggma.)\p"
	.string "(She looks at you with\n"
	.string "complete and utter disdain.)\p"
	.string "(It's time for a battle that\n"
	.string "isn't going to be over easy...!)$"

SecretMeadow_Text_ItLeftBehindSomething:
	.string "(The queen has departed from\n"
	.string "this meadow, taking her\l"
	.string "stash of Pokemon Eggs with her...)\p"
	.string "(...However, she did leave\n"
	.string "one behind...)$"

SecretMeadow_Text_PlayerReceivedEgg:
	.string "{PLAYER} received an Egg!$"
