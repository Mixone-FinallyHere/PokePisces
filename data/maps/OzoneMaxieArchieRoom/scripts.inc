.set LOCALID_MAXIE, 2
.set LOCALID_ARCHIE, 1

OzoneMaxieArchieRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OzoneMaxieArchieRoom_OnFrame
	.byte 0

OzoneMaxieArchieRoom_OnFrame:
	map_script_2 VAR_TEMP_4, 0, OzoneMaxieArchieRoom_EventScript_FightMaxieArchie
	.2byte 0

OzoneMaxieArchieRoom_EventScript_FightMaxieArchie::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, OzoneMaxieArchieRoom_Movement_WalkToBattle
	waitmovement 0
	delay 8
	setvar VAR_TEMP_4, 1
	getdoublessizeforgym
	goto_if_eq VAR_RESULT, 0, OzoneMaxieArchieRoom_EventScript_NotEnoughPokemon
	speakername OzoneMaxieArchieRoom_Text_NameMaxie
	msgbox OzoneMaxieArchieRoom_Text_HowImpressive, MSGBOX_DEFAULT
	speakername OzoneMaxieArchieRoom_Text_NameArchie
	msgbox OzoneMaxieArchieRoom_Text_ThisIsYourLastFight, MSGBOX_DEFAULT
	speakername OzoneMaxieArchieRoom_Text_NameMaxie
	msgbox OzoneMaxieArchieRoom_Text_MyAnalysis, MSGBOX_DEFAULT
	speakername OzoneMaxieArchieRoom_Text_NameArchie
	msgbox OzoneMaxieArchieRoom_Text_LetsGetToIt, MSGBOX_DEFAULT
	speakername NULL
	trainerbattle_two_trainers TRAINER_P_MAXIE, OzoneMaxieArchieRoom_Text_MaxieDefeat, TRAINER_P_ARCHIE, OzoneMaxieArchieRoom_Text_ArchieDefeat, OzoneMaxieArchieRoom_EventScript_LeadersDefeated, NO_MUSIC
	goto OzoneMaxieArchieRoom_EventScript_LeadersDefeated
	release
	end

OzoneMaxieArchieRoom_EventScript_NotEnoughPokemon::
	clearflag FLAG_WITHIN_GYM
	speakername OzoneMaxieArchieRoom_Text_NameMaxie
	msgbox OzoneMaxieArchieRoom_Text_NotEnoughPokemon, MSGBOX_DEFAULT
	closemessage
	warp MAP_OZONE_INT, 15, 4
	waitstate
	release
	end

OzoneMaxieArchieRoom_Movement_WalkToBattle:
	walk_up
	jump_2_up
	step_end

OzoneMaxieArchieRoom_EventScript_LeadersDefeated::
	lock
	setflag FLAG_DEFEATED_OZONE_MAXIE_ARCHIE
	speakername OzoneMaxieArchieRoom_Text_NameArchie
	msgbox OzoneMaxieArchieRoom_Text_ThatWasGreat, MSGBOX_DEFAULT
	speakername OzoneMaxieArchieRoom_Text_NameMaxie
	msgbox OzoneMaxieArchieRoom_Text_ToCommemorateTheOccasion, MSGBOX_DEFAULT
	closemessage
	delay 16
	playbgm MUS_ABNORMAL_WEATHER, FALSE
	setweather WEATHER_ABNORMAL
	doweather
	applymovement LOCALID_ARCHIE, OzoneMaxieArchieRoom_Movement_Confused
	applymovement LOCALID_MAXIE, OzoneMaxieArchieRoom_Movement_Confused
	delay 8
	setvar VAR_PISCES_STORY_PROGRESS, 11
	turnobject LOCALID_ARCHIE, DIR_EAST
	speakername OzoneMaxieArchieRoom_Text_NameArchie
	msgbox OzoneMaxieArchieRoom_Text_ItsLikeBefore, MSGBOX_DEFAULT
	speakername OzoneMaxieArchieRoom_Text_NameMaxie
	msgbox OzoneMaxieArchieRoom_Text_SomethingIsVeryWrong, MSGBOX_DEFAULT
	closemessage
	delay 4
	warp MAP_OZONE_SITUATION_ROOM, 3, 4
	waitstate
	release
	end

OzoneMaxieArchieRoom_Movement_Confused:
	emote_question_mark
	step_end

OzoneMaxieArchieRoom_Text_NameMaxie:
	.string "Maxie$"

OzoneMaxieArchieRoom_Text_NameArchie:
	.string "Archie$"

OzoneMaxieArchieRoom_Text_HowImpressive:
	.string "How impressive, {PLAYER}.\n"
	.string "You seem to have made quick work\l"
	.string "of our subordinates.$"

OzoneMaxieArchieRoom_Text_ThisIsYourLastFight:
	.string "They tried to pull out all\n"
	.string "the stops! I hope they weren't\l"
	.string "total pushovers, ah-hah-hah-hah!\p"
	.string "Still, they were never even in the\n"
	.string "same ballpark as the two of us.\l"
	.string "However hard you thought those\l"
	.string "chumps were? Multiply that tenfold!$"

OzoneMaxieArchieRoom_Text_MyAnalysis:
	.string "I have been watching and analyzing\n"
	.string "each and every one of those\l"
	.string "previous four battles. And, I have\l"
	.string "mapped out a path for sure victory.\l"
	.string "Victory for Archibald and I,\l"
	.string "of course.$"

OzoneMaxieArchieRoom_Text_LetsGetToIt:
	.string "This is it, {PLAYER}!\n"
	.string "The final battle, winner take all!\l"
	.string "Bombs... away...!$"

OzoneMaxieArchieRoom_Text_MaxieDefeat:
	.string "You always were such an\n"
	.string "unpredictable variable...$"

OzoneMaxieArchieRoom_Text_ArchieDefeat:
	.string "I salute you, {PLAYER}!\n"
	.string "I haven't gotten my behind kicked\l"
	.string "that hard in ages! Gah-hah-hah!$"

OzoneMaxieArchieRoom_Text_ThatWasGreat:
	.string "Yyaarrrr....! That was exhilerating!$"

OzoneMaxieArchieRoom_Text_ToCommemorateTheOccasion:
	.string "Indeed. I am glad to have met\n"
	.string "you, {PLAYER}. And I do hope\l"
	.string "that the Ozone Challenge gave you\l"
	.string "a satisfactory amount of closure\l"
	.string "to your adventure.\p"
	.string "To commemorate the occasion, I\n"
	.string "would like to-$"

OzoneMaxieArchieRoom_Text_ItsLikeBefore:
	.string "This weather... Maxie, it\n"
	.string "has to be...\p"
	.string "It's just like when...\n"
	.string "well....$"

OzoneMaxieArchieRoom_Text_SomethingIsVeryWrong:
	.string "Like Sootopolis years ago?\n"
	.string "I was thinking similarly.\p"
	.string "Something is very wrong.\n"
	.string "{PLAYER}, please come with us\l"
	.string "to the situation room.\l"
	.string "We could be in the midst of\l"
	.string "an event with dire consequences...$"

OzoneMaxieArchieRoom_Text_NotEnoughPokemon:
	.string "This is quite the predicament,\n"
	.string "{PLAYER}. For, you see, I have\l"
	.string "calculated your odds of winning\l"
	.string "this upcoming battle. And they are\l"
	.string "a flat zero.\p"
	.string "Your team is not healthy enough\n"
	.string "to power through this encounter.\l"
	.string "You must try the Ozone Challenge\l"
	.string "again, I am afraid.$"
