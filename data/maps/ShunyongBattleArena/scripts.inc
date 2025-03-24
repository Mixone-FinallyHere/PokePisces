.set LOCALID_MAY, 1
.set LOCALID_BRENDAN, 2

ShunyongBattleArena_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ShunyongBattleArena_OnFrame
	.byte 0

ShunyongBattleArena_OnFrame:
	map_script_2 VAR_TEMP_4, 0, ShunyongBattleArena_EventScript_FacingShunyong
	.2byte 0

ShunyongBattleArena_EventScript_FacingShunyong::
	lock
	setvar VAR_TEMP_4, 1
	msgbox ShunyongBattleArena_Text_LoreDump, MSGBOX_DEFAULT
	closemessage
	delay 4
	fadenewbgm MUS_PISCES_TITLE
	delay 16
	msgbox ShunyongBattleArena_Text_ThisIsYourFinalTest, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_SHUNYONG, CRY_MODE_NORMAL
	waitmoncry
	doshunyongbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShunyongBattleArena_EventScript_CantEscape
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShunyongBattleArena_EventScript_CantEscape
	goto ShunyongBattleArena_EventScript_ShunyongVictory
	release
	end

ShunyongBattleArena_EventScript_CantEscape::
	lock
	msgbox ShunyongBattleArena_Text_CantEscapeShunyong, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_SHUNYONG, CRY_MODE_NORMAL
	waitmoncry
	doshunyongbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShunyongBattleArena_EventScript_CantEscape
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShunyongBattleArena_EventScript_CantEscape
	goto ShunyongBattleArena_EventScript_ShunyongVictory
	release
	end

ShunyongBattleArena_EventScript_ShunyongVictory::
	lock
	delay 8
	msgbox ShunyongBattleArena_Text_YouBeatShunyong, MSGBOX_DEFAULT
	turnobject LOCALID_MAY, DIR_EAST
	turnobject LOCALID_BRENDAN, DIR_WEST
	msgbox ShunyongBattleArena_Text_TimeToGetOutOfHere, MSGBOX_DEFAULT
	setvar VAR_PISCES_STORY_PROGRESS, 12
	closemessage
	delay 16
	warp MAP_EVER_GRANDE_PEAK, 39, 47
	waitstate
	release
	end

ShunyongBattleArena_EventScripts_ShunyongTest::
	lock
	doshunyongbattle
	release
	end

ShunyongBattleArena_Text_LoreDump:
	.string "(You and your rival awake\n"
	.string "within an infinite ocean.)\p"
	.string "(You can hear an unfathomably\n"
	.string "intimidating voice ring through\l"
	.string "your head...)\p"
	.string "Sha-Yon... the Rising Deity...\n"
	.string "Luo-Shan... the Falling Deity...\p"
	.string "When met in the middle...\n"
	.string "the Deity of the Golden Mean...\p"
	.string "That... is I.\p"
	.string "Why did you herald my return...?\n"
	.string "...You need not answer.\p"
	.string "You desire a period of peace\n"
	.string "and prosperity in Hoenn.\l"
	.string "A selfless yearning...\l"
	.string "Though, I do sense that your\l"
	.string "intentions are not entirely that.\p"
	.string "You wish for the notoriety of\n"
	.string "that of your bonded friend,\l"
	.string "standing beside you...\l"
	.string "It is what you have always\l"
	.string "desired most. Do I speak lies...?\p"
	.string "(How could it...)\p"
	.string "How could I know this, you surmise?\p"
	.string "In this space, {PLAYER},\n"
	.string "I am aware of all matters.\p"
	.string "Enough. I will grant your wish\n"
	.string "for the good of the region.\p"
	.string "...However.\p"
	.string "You must defeat me.$"

ShunyongBattleArena_Text_ThisIsYourFinalTest:
	.string "Every step of your journey,\n"
	.string "you have been tested.\p"
	.string "Every test, you have passed\n"
	.string "with aplomb.\p"
	.string "This will be unlike any tribulation\n"
	.string "you have encountered thus far.\l"
	.string "I will bring you to your knees,\l"
	.string "and you will beg for mercy...\p"
	.string "Withstand my onslaught and slay\n"
	.string "even a fraction of my essence...\l"
	.string "and turmoil will never\l"
	.string "befall the Hoenn region again.\p"
	.string "(You can do this.)\p"
	.string "(...No, you HAVE to do this!)\p"
	.string "(Deity, or not...\n"
	.string "nothing can stand in your way!)$"

ShunyongBattleArena_Text_CantEscapeShunyong:
	.string "Fleeing is useless, {PLAYER}.\n"
	.string "You should know this.$"

ShunyongBattleArena_Text_YouBeatShunyong:
	.string "(It's as if the world itself buckled\n"
	.string "under the weight of that\l"
	.string "climactic showdown...)\p"
	.string "...Impressive...\p"
	.string "I will honor our deal, {PLAYER}.\n"
	.string "Because of you, Hoenn\l"
	.string "will know peace for generations.\p"
	.string "All will return to the\n"
	.string "Golden Mean...!$"

ShunyongBattleArena_Text_TimeToGetOutOfHere:
	.string "(You and your rival gaze\n"
	.string "at each other...)\p"
	.string "(Before you both\n"
	.string "lose consciousness...)$"
