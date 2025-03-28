.set LOCALID_RAY, 1

Route122_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route122_OnTransition
	.byte 0

Route122_OnTransition:
	call_if_gt VAR_RAY_STATE, 1, Route122_EventScript_SetTempFlags
	call_if_ge VAR_NOTICED_BY_YANDEMIC, 5, Route122_EventScript_RemoveYandemic
	end

Route122_EventScript_RemoveYandemic::
	removeobject LOCALID_YANDEMIC
	setflag FLAG_TEMP_12
	setvar VAR_TEMP_4, 1
	return

Route122_EventScript_SetTempFlags::
	setflag FLAG_TEMP_11
	removeobject LOCALID_RAY
	return

Route122_EventScript_RayEncounterWest::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Route122_Movement_RayEncounterWest
	applymovement LOCALID_RAY, Route122_Movement_RaySquaresUp
	waitmovement 0
	goto Route122_EventScript_RayBattleStart
	release
	end

Route122_Movement_RayEncounterWest:
	walk_up
	walk_right
	face_up
	step_end

Route122_Movement_RaySquaresUp:
	walk_down
	walk_down
	walk_down
	emote_exclamation_mark
	delay_16
	delay_8
	walk_fast_down
	walk_fast_left
	face_down
	step_end

Route122_EventScript_RayEncounterEast::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Route122_Movement_RayEncounterEast
	applymovement LOCALID_RAY, Route122_Movement_RaySquaresUp
	waitmovement 0
	goto Route122_EventScript_RayBattleStart
	release
	end

Route122_Movement_RayEncounterEast:
	walk_up
	step_end

Route122_EventScript_RayBattleStart::
	speakername Route122_Text_NameRay
	msgbox Route122_Text_RayIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_RAY_2, Route122_Text_RayDefeat
	goto Route122_EventScript_RayLeaves
	release
	end

Route122_EventScript_RayLeaves::
	setmetatile 25, 19, METATILE_Snow_PunchedMan1, TRUE
	setmetatile 26, 19, METATILE_Snow_PunchedMan2, TRUE
	setmetatile 26, 20, METATILE_Snow_PunchedMan3, FALSE
	special DrawWholeMapView
	delay 4
	speakername Route122_Text_NameRay
	msgbox Route122_Text_RayLeaves, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route122_Movement_PlayerOutOfWay
	waitmovement 0
	applymovement LOCALID_RAY, Route122_Movement_RayLeaves
	waitmovement 0
	removeobject LOCALID_RAY
	speakername NULL
	setflag FLAG_TEMP_11
	setvar VAR_RAY_STATE, 2
	setflag FLAG_VISITED_ZOTPYRE
	release
	end

Route122_Movement_PlayerOutOfWay:
	walk_right
	face_left
	step_end

Route122_Movement_RayLeaves:
	walk_down
	walk_down
	walk_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	set_invisible
	step_end

Route122_EventScript_ElderMan::
	lock
	faceplayer
	goto_if_eq VAR_GRAVE_QUEST_STATE, 3, Route122_EventScript_BindingBand
	goto_if_eq VAR_GRAVE_QUEST_STATE, 4, Route122_EventScript_GoFindHerSpirit
	goto_if_eq VAR_GRAVE_QUEST_STATE, 5, Route122_EventScript_DestinyKnot
	goto_if_eq VAR_GRAVE_QUEST_STATE, 6, Route122_EventScript_ThankYou
	msgbox Route122_Text_GreetingsChild, MSGBOX_AUTOCLOSE
	release
	end

Route122_EventScript_BindingBand::
	msgbox Route122_Text_ISeeThatBindingBand, MSGBOX_AUTOCLOSE
	setvar VAR_GRAVE_QUEST_STATE, 4
	release
	end

Route122_EventScript_GoFindHerSpirit::
	msgbox Route122_Text_GoFindHerSpirit, MSGBOX_AUTOCLOSE
	release
	end

Route122_EventScript_DestinyKnot::
	msgbox Route122_Text_YouHelpedHerFindPeace, MSGBOX_DEFAULT
	giveitem ITEM_DESTINY_KNOT
	setvar VAR_GRAVE_QUEST_STATE, 6
	msgbox Route122_Text_ThankYou, MSGBOX_AUTOCLOSE
	release
	end

Route122_EventScript_ThankYou::
	msgbox Route122_Text_ThankYou, MSGBOX_AUTOCLOSE
	release
	end

Route122_EventScript_LostKin::
	lock
	goto_if_set FLAG_ZOTPYRE_PSYCHICS, Route122_EventScript_Teleporter
	faceplayer
	setflag FLAG_ZOTPYRE_PSYCHICS
	msgbox Route122_Text_IReuniteWithMyKin, MSGBOX_DEFAULT
	goto Route122_EventScript_Teleporter
	release
	end

Route122_EventScript_Teleporter::
	lock
	faceplayer
	msgbox Route122_Text_WouldYouLikeToWarp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route122_EventScript_WarpToCenter
	msgbox Route122_Text_MaybeAnotherTime, MSGBOX_AUTOCLOSE
	release
	end

Route122_EventScript_WarpToCenter::
	warp MAP_LILYCOVE_CITY_POKEMON_CENTER_2F, 12, 3
	waitstate
	release
	end

Route122_EventScript_YandemicNoticed::
	lock
	setvar VAR_TEMP_4, 1
	call_if_lt VAR_NOTICED_BY_YANDEMIC, 4, Route122_EventScript_YandemicAddVar
	msgbox MossdeepCity_Text_YouFeelWatched, MSGBOX_AUTOCLOSE
	release
	end

Route122_EventScript_YandemicAddVar::
	addvar VAR_NOTICED_BY_YANDEMIC, 1
	return

Route122_EventScript_ZotpyreSign::
	msgbox Route122_Text_ZotpyreSign, MSGBOX_SIGN
	end

Route122_Text_ZotpyreSign:
	.string "ZOTPYRE VILLAGE\n"
	.string "A site of repose for\l"
	.string "the living and dead.$"

Route122_Text_YouFeelWatched:
	.string "(You begin to notice that\n"
	.string "you are being intently watched...)$"

Route122_Text_WouldYouLikeToWarp:
	.string "I am able to warp you to my kin\n"
	.string "in the Brumist Cliffs route center.\p"
	.string "Is that something you are\n"
	.string "prepared to do?$"

Route122_Text_MaybeAnotherTime:
	.string "Maybe another time, then!$"

Route122_Text_IReuniteWithMyKin:
	.string "Ohm.... Ohm....\p"
	.string "Aha...! I have found my kin once\n"
	.string "more among the psychic etherplane.\p"
	.string "I should be able to harness our\n"
	.string "combined ESP to teleport objects...\l"
	.string "and maybe people...?\p"
	.string "You there. Would you care to be\n"
	.string "our guinea pig?$"

Route122_Text_GreetingsChild:
	.string "A pleasant welcome to\n"
	.string "our village, stranger.\p"
	.string "I am the Elder of Zotpyre.\p"
	.string "We sincerely hope you can find respite\n"
	.string "in our humble abodes.$"

Route122_Text_ISeeThatBindingBand:
	.string "…That band on your wrist…\p"
	.string "…Hm.\p"
	.string "I take it that the spirits of this land\n"
	.string "are quite fond of you.\p"
	.string "…Mayhaps you can be the one\n"
	.string "to calm her spirit.\p"
	.string "The basement of the inn…\n"
	.string "I ask you, kindly, to investigate.$"

Route122_Text_GoFindHerSpirit:
	.string "A troubled remnant is lingering in the\n"
	.string "basement of the inn…\p"
	.string "Mayhaps you can connect with her.$"

Route122_Text_YouHelpedHerFindPeace:
	.string "You do not need to brief me.\n"
	.string "I can feel that her presence has,\l"
	.string "at last, left this plane.\p"
	.string "My wife, the former elder…\p"
	.string "In her last days, her brain ebbed away.\n"
	.string "She lost herself.\l"
	.string "Even in death, she was fractured.\p"
	.string "Thank you very much for being that\n"
	.string "spark to get her to move on.\p"
	.string "Truly.\p"
	.string "Please accept… this.$"

Route122_Text_ThankYou:
	.string "You have my gratitude.\n"
	.string "May your soul find peace when you,\l"
	.string "too, pass on someday.$"

Route122_Text_NameRay:
	.string "Ray$"

Route122_Text_RayIntro:
	.string "Oh.\p"
	.string "It's THAT troublemaker again.\p"
	.string "First Tabitha and Matt splinter focus\n"
	.string "(idiotic strat), THEN I'm forced to\l"
	.string "play mediator (I was not hired for this),\l"
	.string "and RIGHT as I'm about to head\l"
	.string "out of this freezing (and boring)\l"
	.string "hovel, your dopey face blocks my path.\p"
	.string "Can you spell the word “sabotage?”\n"
	.string "Because you are doing that.\l"
	.string "Sabotaging Ray (and their patience).\p"
	.string "I think I'll knock your smug\n"
	.string "confidence down a few pegs.\l"
	.string "You won't be able to HANDLE this!$"

Route122_Text_RayDefeat:
	.string "(Ray punches a nearby snowman\n"
	.string "in the face.)\p"
	.string "I'm in AWE of your tricksy cheatery!$"

Route122_Text_RayLeaves:
	.string "Terrain teams are the meta.\n"
	.string "I'm convinced. You\l"
	.string "(the loser, in personality)\l"
	.string "must be rigging things.\l"
	.string "Mayhaps you swapped my Misty Terrain\l"
	.string "for Sissy Terrain when my\l"
	.string "back was turned.\p"
	.string "My only solace is my confidence that\n"
	.string "you will not make it past the\l"
	.string "pearly gates in the afterlife.\p"
	.string "(I will.)\p"
	.string "Don't get in my peripheral vision\n"
	.string "again, thank you.$"
