.set LOCALID_TUBER1, 7
.set LOCALID_TUBER2, 9
.set LOCALID_TUBER3, 10
.set LOCALID_TUBER4, 13
.set LOCALID_POMELONIAN, 8
.set LOCALID_VICTIM1, 6
.set LOCALID_VICTIM2, 11
.set LOCALID_VICTIM3, 12
.set LOCALID_PARASOL1, 19
.set LOCALID_PARASOL2, 20
.set LOCALID_PARASOL3, 21
.set LOCALID_PARASOL4, 22
.set LOCALID_PARASOL5, 23
.set LOCALID_PARASOL6, 24

NewSunbeach_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewSunbeach_OnTransition
	.byte 0

NewSunbeach_OnTransition:
	call_if_set FLAG_SUNBEACH_TUBER_1, NewSunbeach_EventScript_SetTuberTempFlags1
	call_if_set FLAG_SUNBEACH_TUBER_2, NewSunbeach_EventScript_SetTuberTempFlags2
	call_if_set FLAG_SUNBEACH_TUBER_3, NewSunbeach_EventScript_SetTuberTempFlags3
	call_if_gt VAR_PARASOL_QUEST_STATE, 1, NewSunbeach_EventScript_SetParasolTempVar
	end

NewSunbeach_EventScript_SetTuberTempFlags1::
	setvar VAR_TEMP_5, 2
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	return

NewSunbeach_EventScript_SetTuberTempFlags2::
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	return

NewSunbeach_EventScript_SetTuberTempFlags3::
	setvar VAR_TEMP_6, 2
	setflag FLAG_TEMP_17
	setflag FLAG_TEMP_18
	return

NewSunbeach_EventScript_SetParasolTempVar::
	setvar VAR_TEMP_4, 2
	return

NewSunbeach_EventScript_BladeTrainer::
	lock
	faceplayer
	checkitem ITEM_LEADERS_CREST
	goto_if_eq VAR_RESULT, TRUE, NewSunbeach_EventScript_AlreadyGaveLeadersCrest
	msgbox NewSunbeach_Text_BeautyOfBlades, MSGBOX_DEFAULT
	checkpartynonhmmove MOVE_EXECUTION
	goto_if_eq VAR_RESULT, PARTY_SIZE, NewSunbeach_EventScript_NoExecution
	msgbox NewSunbeach_Text_YouKnowTheArt, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_LEADERS_CREST
	closemessage
	release
	end

NewSunbeach_EventScript_NoExecution::
	msgbox NewSunbeach_Text_NoExecution, MSGBOX_AUTOCLOSE
	release
	end

NewSunbeach_EventScript_AlreadyGaveLeadersCrest::
	msgbox NewSunbeach_Text_AlreadyGaveLeadersCrest, MSGBOX_AUTOCLOSE
	release
	end

NewSunbeach_Text_BeautyOfBlades:
	.string "You have come all the way\n"
	.string "to the Sunset Palm, stranger?\p"
	.string "Heh. You seem naive. This is\n"
	.string "a location bathed in a bloody\l"
	.string "history... though that time\l"
	.string "has since passed.\p"
	.string "Legends tell of samurai carrying out\n"
	.string "executions under this very palm.\l"
	.string "Murder, you see, can be described\l"
	.string "as an artform, if you are so\l"
	.string "inclined to. There is a certain\l"
	.string "beauty in a clean swing...\p"
	.string "Should you possess a Pokemon that\n"
	.string "channels the knowledge of\l"
	.string "those ancient executions...\l"
	.string "I have a very important item to bestow.$"

NewSunbeach_Text_NoExecution:
	.string "...So you are just as naive\n"
	.string "as I had surmised. Heh...\l"
	.string "ignorance is bliss, child.$"

NewSunbeach_Text_YouKnowTheArt:
	.string "...So, you do know the art\n"
	.string "of death's blade...\p"
	.string "Excellent. You will make\n"
	.string "exceptional use of this shard.$"

NewSunbeach_Text_AlreadyGaveLeadersCrest:
	.string "The Blade Shard you now own\n"
	.string "are remnants of those olden samurai.\l"
	.string "Treat it with respect, and\l"
	.string "carry on the artform of the blade.$"
