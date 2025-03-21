.set LOCALID_YANDEMIC, 4

LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	.byte 0

LilycoveCity_OnTransition:
	setflag FLAG_VISITED_LILYCOVE_CITY
	call_if_ge VAR_NOTICED_BY_YANDEMIC, 5, LilycoveCity_EventScript_RemoveYandemic
	end

LilycoveCity_EventScript_RemoveYandemic::
	removeobject LOCALID_YANDEMIC
	setflag FLAG_TEMP_11
	setvar VAR_TEMP_4, 1
	return

LilycoveCity_EventScript_FalseSwipeGiver::
	lock
	faceplayer
	checkitem ITEM_TM_FALSE_SWIPE
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_GaveFalseSwipe
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008
	buffernumberstring STR_VAR_2, VAR_0x8009
	goto_if_gt VAR_0x8009, 39, LilycoveCity_EventScript_GiveFalseSwipe
	msgbox LilycoveCity_Text_WantToSee40CaughtMons, MSGBOX_AUTOCLOSE
	release
	end

LilycoveCity_EventScript_GiveFalseSwipe::
	msgbox LilycoveCity_Text_LotsOfCaughtMons, MSGBOX_DEFAULT
	giveitem ITEM_TM_FALSE_SWIPE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

LilycoveCity_EventScript_GaveFalseSwipe::
	msgbox LilycoveCity_Text_GaveFS, MSGBOX_AUTOCLOSE
	release
	end

LilycoveCity_EventScript_ThisIsMyWorkplace::
	msgbox LilycoveCity_Text_ThisIsMyWorkplace, MSGBOX_NPC
	end

LilycoveCity_EventScript_YandemicNoticed::
	lock
	setvar VAR_TEMP_4, 1
	call_if_lt VAR_NOTICED_BY_YANDEMIC, 4, LilycoveCity_EventScript_YandemicAddVar
	msgbox MossdeepCity_Text_YouFeelWatched, MSGBOX_AUTOCLOSE
	release
	end

LilycoveCity_EventScript_YandemicAddVar::
	addvar VAR_NOTICED_BY_YANDEMIC, 1
	return

LilycoveCity_EventScript_KamenRider::
	lock
	faceplayer
	checkitem ITEM_KAMEN_SCARF
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_AlreadyGaveKamenScarf
	msgbox LilycoveCity_Text_ShowMeYourMuscles, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_KAMEN_SCARF
	closemessage
	msgbox LilycoveCity_Text_FlexToOthers, MSGBOX_AUTOCLOSE
	release
	end

LilycoveCity_EventScript_AlreadyGaveKamenScarf::
	msgbox LilycoveCity_Text_AlreadyGaveKamenScarf, MSGBOX_AUTOCLOSE
	release
	end

LilycoveCity_EventScript_LilycoveCitySign::
	msgbox LilycoveCity_Text_LilycoveCitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_OLBHQSign::
	msgbox LilycoveCity_Text_OLBHQSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_BattleStudioSign::
	msgbox LilycoveCity_Text_BattleStudioSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_BrineysHouseSign::
	msgbox LilycoveCity_Text_BrineysHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_LilycoveMuseumSign::
	msgbox LilycoveCity_Text_LilycoveMuseumSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ColdMinesSouthSign::
	msgbox LilycoveCity_Text_ColdMinesSouthSign, MSGBOX_SIGN
	end

LilycoveCity_Text_LilycoveCitySign:
	.string "LILYCOVE CITY\n"
	.string "A lively hub by the ocean!$"

LilycoveCity_Text_OLBHQSign:
	.string "OZONE LILYCOVE BRANCH HEADQUARTERS\n"
	.string "Meetings done by appointment!$"

LilycoveCity_Text_BattleStudioSign:
	.string "BATTLE STUDIO\n"
	.string "Come take the Battle Swap Challenge!$"

LilycoveCity_Text_BrineysHouseSign:
	.string "Mr. Briney's Boathouse$"

LilycoveCity_Text_LilycoveMuseumSign:
	.string "LILYCOVE MUSEUM\n"
	.string "Currently housing the paintings\l"
	.string "of Kalosian Artist, Phillipe!$"

LilycoveCity_Text_ColdMinesSouthSign:
	.string "Southern Entrance to\n"
	.string "THE COLD MINES$"

LilycoveCity_Text_YouFeelWatched:
	.string "(You begin to notice that\n"
	.string "you are being intently watched...)$"

LilycoveCity_Text_ThisIsMyWorkplace:
	.string "This here is my workplace! The\n"
	.string "Ozone Lilycove Branch HQ.\p"
	.string "Or as most of us call it,\n"
	.string "the Ol' Bihq.\p"
	.string "It sounds a lot better if you say it\n"
	.string "with a southern drawl!$"

LilycoveCity_Text_WantToSee40CaughtMons:
	.string "Catching Pokemon is fun, yeah?\n"
	.string "Well, most of the time.\p"
	.string "Some Pokemon can be a pain to\n"
	.string "whittle down without\l"
	.string "having them faint.\p"
	.string "Now, I DO have a spare TM\n"
	.string "for a move that may help you there.\l"
	.string "But you really gotta PROVE to me\l"
	.string "that you've got capturing chops.\p"
	.string "If you can produce a 40 caught\n"
	.string "count in your Pokedex, I'll\l"
	.string "hand the TM over. Deal?$"

LilycoveCity_Text_LotsOfCaughtMons:
	.string "You're a pretty experienced\n"
	.string "catcher, I take it. 40 caught?\l"
	.string "Not a bad number.\p"
	.string "Here, take this TM for False Swipe.\n"
	.string "It should help you get that\l"
	.string "number even higher.$"

LilycoveCity_Text_GaveFS:
	.string "Combining False Swipe with\n"
	.string "a status move that causes\l"
	.string "paralysis or sleep is one of\l"
	.string "the best ways to weaken Pokemon\l"
	.string "for a quick capture.$"

LilycoveCity_Text_ShowMeYourMuscles:
	.string "Man, I tell ya, cycling is\n"
	.string "one of THE best ways to build\l"
	.string "a crap-ton of MUSCLE! GRAHH!\p"
	.string "Hey, little dude! Show me\n"
	.string "a good flex! Are you RIPPED!?\p"
	.string "(You half-heartedly tense up\n"
	.string "the muscles in your chest.)\p"
	.string "AWESOME! I still got a ways to go.\p"
	.string "You know the Pokemon Shockore?\n"
	.string "Man, that thing is just a\l"
	.string "LIVING SIX PACK. Nothing can\l"
	.string "penetrate THOSE abs. So if you\l"
	.string "can't beat 'em, join 'em!$"

LilycoveCity_Text_FlexToOthers:
	.string "Have your own Shockore wear\n"
	.string "that scarf, and it'll turn\l"
	.string "into basically an IMMOVABLE OBJECT.\p"
	.string "The two of you can be flex partners!$"

LilycoveCity_Text_AlreadyGaveKamenScarf:
	.string "I need to really beef up\n"
	.string "my legs to deliver some more\l"
	.string "potent Raidakikku...$"
