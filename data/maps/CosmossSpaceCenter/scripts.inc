CosmossSpaceCenter_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CosmossSpaceCenter_OnFrame
	.byte 0

CosmossSpaceCenter_OnFrame:
	map_script_2 VAR_SPACE_CENTER_QUEST_STATE, 50, CosmossSpaceCenter_EventScript_AfterInvasion
	map_script_2 VAR_ORBS_QUEST_STATE, 8, CosmossSpaceCenter_EventScript_AfterJacobi
	.2byte 0

CosmossSpaceCenter_EventScript_AfterInvasion::
	lock
	applymovement 12, CosmossSpaceCenter_LookRight
	applymovement OBJ_EVENT_ID_PLAYER, CosmossSpaceCenter_LookLeft
	msgbox CosmossSpaceCenter_Text_SavedTheRocket, MSGBOX_DEFAULT
	setvar VAR_SPACE_CENTER_QUEST_STATE, 3
	msgbox CosmossSpaceCenter_Text_MeteorsFallen, MSGBOX_AUTOCLOSE
	waitmessage
	applymovement 12, CosmossSpaceCenter_Movement_FaceUp
	waitmovement 0
	release
	end

CosmossSpaceCenter_LookLeft:
	face_left
	step_end

CosmossSpaceCenter_LookRight:
	face_right
	step_end

CosmossSpaceCenter_EventScript_AfterJacobi::
	lock
	delay 4
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox CosmossSpaceCenter_Text_SavedTheCenter, MSGBOX_DEFAULT
	setvar VAR_ORBS_QUEST_STATE, 9
	giveitem ITEM_LIFE_ORB
	msgbox CosmossSpaceCenter_Text_ThanksForSaving, MSGBOX_DEFAULT
	closemessage
	delay 16
	playse SE_M_SWORDS_DANCE
	waitse
	playse SE_M_BUBBLE_BEAM2
	msgbox CosmossSpaceCenter_Text_TheMapPointsToRustboro, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_AIBlock::
	lock
	playse SE_PC_ON
	waitse
	msgbox CosmossSpaceCenter_Text_NoAccess, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, CosmossSpaceCenter_Movement_BackUp
	waitmovement 0
	release
	end

CosmossSpaceCenter_Movement_BackUp:
	walk_down
	step_end

CosmossSpaceCenter_EventScript_RocketResearcher::
	lock
	goto_if_gt VAR_SPACE_CENTER_QUEST_STATE, 0, CosmossSpaceCenter_EventScript_RocketFunded
	msgbox CosmossSpaceCenter_Text_NeedHelpFunding, MSGBOX_DEFAULT
	faceplayer
	showmoneybox 0, 0
	msgbox CosmossSpaceCenter_Text_WillYouFund, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CosmossSpaceCenter_EventScript_CheckMoneyForFund
	goto_if_eq VAR_RESULT, NO, CosmossSpaceCenter_EventScript_ThenGoAway
	closemessage
	hidemoneybox
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_FaceUp
	waitmovement 0
	release
	end

CosmossSpaceCenter_Movement_FaceUp:
	face_up
	step_end

CosmossSpaceCenter_EventScript_ThenGoAway::
	msgbox CosmossSpaceCenter_Text_ThenGoAway, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_FaceUp
	waitmovement 0
	release
	end

CosmossSpaceCenter_EventScript_CheckMoneyForFund::
	checkmoney 5000
	goto_if_eq VAR_RESULT, FALSE, CosmossSpaceCenter_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 5000
	updatemoneybox
	delay 40
	hidemoneybox
	msgbox CosmossSpaceCenter_Text_ThanksForFunding, MSGBOX_DEFAULT
	giveitem ITEM_EJECT_BUTTON
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_SPACE_CENTER_QUEST_STATE, 1
	msgbox CosmossSpaceCenter_Text_YouCanNowGoUpstairs, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_FaceUp
	waitmovement 0
	playse SE_PC_ON
	waitse
	msgbox CosmossSpaceCenter_Text_AccessGranted, MSGBOX_AUTOCLOSE
	release
	end

CosmossSpaceCenter_EventScript_NotEnoughMoney::
	msgbox CosmossSpaceCenter_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_FaceUp
	waitmovement 0
	release
	end

CosmossSpaceCenter_EventScript_RocketFunded::
	msgbox CosmossSpaceCenter_Text_RocketFuel, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_FaceUp
	waitmovement 0
	release
	end

CosmossSpaceCenter_EventScript_AlienResearcher::
	lock
	faceplayer
	goto_if_gt VAR_SPACE_CENTER_QUEST_STATE, 1, CosmossSpaceCenter_EventScript_AboutCryplin
	msgbox CosmossSpaceCenter_Text_BattleMyCryplin, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CosmossSpaceCenter_EventScript_MinkowskiBattle
	goto_if_eq VAR_RESULT, NO, CosmossSpaceCenter_EventScript_Understandable
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_Understandable::
	msgbox CosmossSpaceCenter_Text_Understandable, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_MinkowskiBattle::
	trainerbattle_single TRAINER_P_MINKOWSKI, CosmossSpaceCenter_Text_MinkowskiIntro, CosmossSpaceCenter_Text_MinkowskiDefeat, CosmossSpaceCenter_EventScript_LearnedALot
	release
	end

CosmossSpaceCenter_EventScript_LearnedALot::
	msgbox CosmossSpaceCenter_Text_LearnedALot, MSGBOX_DEFAULT
	giveitem ITEM_EJECT_PACK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_SPACE_CENTER_QUEST_STATE, 2
	msgbox CosmossSpaceCenter_Text_HelpMyFriend, MSGBOX_AUTOCLOSE
	release
	end

CosmossSpaceCenter_EventScript_AboutCryplin::
	msgbox CosmossSpaceCenter_Text_AboutCryplin, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_UFOResearcher::
	lock
	faceplayer
	goto_if_lt VAR_SPACE_CENTER_QUEST_STATE, 2, CosmossSpaceCenter_EventScript_RadioWaves
	goto_if_gt VAR_SPACE_CENTER_QUEST_STATE, 2, CosmossSpaceCenter_EventScript_AboutUhefoe
	msgbox CosmossSpaceCenter_Text_HelpFightUFO, MSGBOX_DEFAULT
	closemessage
	playse SE_BOO
	waitse
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_Surprised
	waitmovement 0
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_FaceUp
	msgbox CosmossSpaceCenter_Text_AskFightUFO, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CosmossSpaceCenter_EventScript_PrepForUhefoeInvasion
	goto_if_eq VAR_RESULT, NO, CosmossSpaceCenter_EventScript_Matrix
	closemessage
	release
	end

CosmossSpaceCenter_Movement_Surprised:
	emote_exclamation_mark
	step_end

CosmossSpaceCenter_EventScript_Matrix::
	msgbox CosmossSpaceCenter_Text_Matrix, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_PrepForUhefoeInvasion::
	msgbox CosmossSpaceCenter_Text_ToTheField, MSGBOX_DEFAULT
	setvar VAR_SPACE_CENTER_QUEST_STATE, 69
	warp MAP_ROUTE126, 61, 15
	waitstate
	release
	end

CosmossSpaceCenter_EventScript_RadioWaves::
	msgbox CosmossSpaceCenter_Text_RadioWaves, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_FaceUp
	waitmovement 0
	release
	end

CosmossSpaceCenter_EventScript_AboutUhefoe::
	msgbox CosmossSpaceCenter_Text_AboutUhefoe, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, CosmossSpaceCenter_Movement_FaceUp
	waitmovement 0
	release
	end

CosmossSpaceCenter_EventScript_AsteroidResearcher::
	lock
	faceplayer
	goto_if_lt VAR_SPACE_CENTER_QUEST_STATE, 3, CosmossSpaceCenter_EventScript_CivilianNo
	call_if_eq VAR_SPACE_CENTER_QUEST_STATE, 3, CosmossSpaceCenter_EventScript_GoCollectMinior
	goto_if_gt VAR_SPACE_CENTER_QUEST_STATE, 4, CosmossSpaceCenter_EventScript_ThankYou
	specialvar VAR_RESULT, CheckMiniorRed
	goto_if_eq VAR_RESULT, TRUE, CosmossSpaceCenter_EventScript_CheckOrange
	msgbox CosmossSpaceCenter_Text_NotEnoughMinior, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_CivilianNo::
	msgbox CosmossSpaceCenter_Text_CivilianNo, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_GoCollectMinior::
	setvar VAR_SPACE_CENTER_QUEST_STATE, 4
	msgbox CosmossSpaceCenter_Text_GoCollectMinior, MSGBOX_DEFAULT
	return

CosmossSpaceCenter_EventScript_CheckOrange::
	specialvar VAR_RESULT, CheckMiniorOrange
	goto_if_eq VAR_RESULT, TRUE, CosmossSpaceCenter_EventScript_CheckYellow
	msgbox CosmossSpaceCenter_Text_NotEnoughMinior, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_CheckYellow::
	specialvar VAR_RESULT, CheckMiniorYellow
	goto_if_eq VAR_RESULT, TRUE, CosmossSpaceCenter_EventScript_CheckGreen
	msgbox CosmossSpaceCenter_Text_NotEnoughMinior, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_CheckGreen::
	specialvar VAR_RESULT, CheckMiniorGreen
	goto_if_eq VAR_RESULT, TRUE, CosmossSpaceCenter_EventScript_CheckBlue
	msgbox CosmossSpaceCenter_Text_NotEnoughMinior, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_CheckBlue::
	specialvar VAR_RESULT, CheckMiniorBlue
	goto_if_eq VAR_RESULT, TRUE, CosmossSpaceCenter_EventScript_CheckViolet
	msgbox CosmossSpaceCenter_Text_NotEnoughMinior, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_CheckViolet::
	specialvar VAR_RESULT, CheckMiniorViolet
	goto_if_eq VAR_RESULT, TRUE, CosmossSpaceCenter_EventScript_ReceiveShinyMinior
	msgbox CosmossSpaceCenter_Text_NotEnoughMinior, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_ReceiveShinyMinior::
	msgbox CosmossSpaceCenter_Text_HaveThisShinyMinior, MSGBOX_DEFAULT
	setflag FLAG_FORCED_SHINY
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MINIOR_METEOR_INDIGO
	givemon SPECIES_MINIOR_METEOR_INDIGO, 17, ITEM_COMET_SHARD
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, CosmossSpaceCenter_EventScript_ReceiveShinyMiniorParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, CosmossSpaceCenter_EventScript_ReceiveShinyMiniorPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

CosmossSpaceCenter_EventScript_ReceiveShinyMiniorParty::
	call CosmossSpaceCenter_EventScript_ReceivedShinyMiniorFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CosmossSpaceCenter_EventScript_ExplainShinyMinior
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto CosmossSpaceCenter_EventScript_ExplainShinyMinior
	end

CosmossSpaceCenter_EventScript_ReceiveShinyMiniorPC::
	call CosmossSpaceCenter_EventScript_ReceivedShinyMiniorFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CosmossSpaceCenter_EventScript_SendShinyMiniorToPC
	call Common_EventScript_NameReceivedBoxMon
	goto CosmossSpaceCenter_EventScript_SendShinyMiniorToPC
	end

CosmossSpaceCenter_EventScript_SendShinyMiniorToPC::
	call Common_EventScript_TransferredToPC
	goto CosmossSpaceCenter_EventScript_ExplainShinyMinior
	end

CosmossSpaceCenter_EventScript_ReceivedShinyMiniorFanfare::
	playfanfare MUS_OBTAIN_ITEM
	clearflag FLAG_FORCED_SHINY
	message CosmossSpaceCenter_Text_PlayerReceivedShinyMinior
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_MINIOR
	return

CosmossSpaceCenter_EventScript_ExplainShinyMinior::
	msgbox CosmossSpaceCenter_Text_YoureTheBest, MSGBOX_DEFAULT
	setvar VAR_SPACE_CENTER_QUEST_STATE, 5
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_ThankYou::
	msgbox CosmossSpaceCenter_Text_YoureTheBest, MSGBOX_DEFAULT
	closemessage
	release
	end

CosmossSpaceCenter_EventScript_EncryptionExpert::
	lock
	faceplayer
	goto_if_set FLAG_SUMMONED_PEBB_METEOR, CosmossSpaceCenter_EventScript_CheckSweltorn
	goto_if_unset FLAG_SUMMONED_PEBB_METEOR, CosmossSpaceCenter_EventScript_EnterPebbleriteCodes
	release
	end

CosmossSpaceCenter_EventScript_EnterPebbleriteCodes::
	msgbox CosmossSpaceCenter_Text_EnterCodeText, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CosmossSpaceCenter_EventScript_CodeEntryRelease
    special EnterCode
    waitstate
    special GetCodeFeedback
    goto_if_eq VAR_RESULT, 3, CosmossSpaceCenter_EventScript_CheckCode2
	goto CosmossSpaceCenter_EventScript_CodeEntryFail
	release
	end

CosmossSpaceCenter_EventScript_CheckCode2::
	msgbox CosmossSpaceCenter_Text_EnterCode2, MSGBOX_DEFAULT
    special EnterCode
    waitstate
    special GetCodeFeedback
    goto_if_eq VAR_RESULT, 4, CosmossSpaceCenter_EventScript_CheckCode3
	goto CosmossSpaceCenter_EventScript_CodeEntryFail
	release
	end

CosmossSpaceCenter_EventScript_CheckCode3::
	msgbox CosmossSpaceCenter_Text_EnterCode3, MSGBOX_DEFAULT
    special EnterCode
    waitstate
    special GetCodeFeedback
    goto_if_eq VAR_RESULT, 5, CosmossSpaceCenter_EventScript_CheckCode4
	goto CosmossSpaceCenter_EventScript_CodeEntryFail
	release
	end

CosmossSpaceCenter_EventScript_CheckCode4::
	msgbox CosmossSpaceCenter_Text_EnterCode4, MSGBOX_DEFAULT
    special EnterCode
    waitstate
    special GetCodeFeedback
    goto_if_eq VAR_RESULT, 6, CosmossSpaceCenter_EventScript_CodeEntrySuccess
	goto CosmossSpaceCenter_EventScript_CodeEntryFail
	release
	end

CosmossSpaceCenter_EventScript_CodeEntrySuccess::
	setflag FLAG_SUMMONED_PEBB_METEOR
	msgbox CosmossSpaceCenter_Text_CodeEntrySuccess, MSGBOX_AUTOCLOSE
	release
	end

CosmossSpaceCenter_EventScript_CodeEntryFail::
	msgbox CosmossSpaceCenter_Text_CodeEntryFail, MSGBOX_AUTOCLOSE
	release
	end

CosmossSpaceCenter_EventScript_CodeEntryRelease::
	release
	end

CosmossSpaceCenter_EventScript_CheckSweltorn::
	msgbox CosmossSpaceCenter_Text_CheckSweltorn, MSGBOX_AUTOCLOSE
	release
	end

CosmossSpaceCenter_EventScript_AboutHera::
	msgbox CosmossSpaceCenter_B1F_Text_AboutHera, MSGBOX_NPC
	end

CosmossSpaceCenter_EventScript_AboutKepler::
	msgbox CosmossSpaceCenter_B1F_Text_AboutKepler, MSGBOX_NPC
	end

CosmossSpaceCenter_EventScript_AboutGravity::
	msgbox CosmossSpaceCenter_B1F_Text_AboutGravity, MSGBOX_NPC
	end

CosmossSpaceCenter_EventScript_AboutTerrains::
	msgbox CosmossSpaceCenter_B1F_Text_AboutTerrains, MSGBOX_NPC
	end

CosmossSpaceCenter_EventScript_AboutMinkowski::
	msgbox CosmossSpaceCenter_B1F_Text_AboutMinkowski, MSGBOX_NPC
	end

CosmossSpaceCenter_EventScript_AboutOrbitBalls::
	msgbox CosmossSpaceCenter_B1F_Text_AboutOrbitBalls, MSGBOX_NPC
	end

CosmossSpaceCenter_B1F_Text_AboutHera:
	.string "About 6 months ago, command\n"
	.string "installed a complex AI to manage\l"
	.string "the Space Center.\p"
	.string "You can hear her yell at you\n"
	.string "sometimes. We call her Hera.\p"
	.string "Though she isn't human, we've\n"
	.string "gotten so used to her presence\l"
	.string "and personality that we kinda\l"
	.string "treat her as one.\p"
	.string "Modern tech, man...\n$"

CosmossSpaceCenter_B1F_Text_AboutKepler:
	.string "That man in the black suit\n"
	.string "over there? That's Colonel Kepler...\l"
	.string "He's in charge of the center.\p"
	.string "He's outwardly polite, but I have\n"
	.string "to warn you, he is THE scariest\l"
	.string "person I have ever interacted with.\l"
	.string "When he wants something done,\l"
	.string "it gets done.\p"
	.string "You don't want to get on his\n"
	.string "bad side, trust me...$"

CosmossSpaceCenter_B1F_Text_AboutGravity:
	.string "Have you ever tried utilizing\n"
	.string "the field effect, Gravity?\l"
	.string "It's a bit niche, but it has\l"
	.string "some fun uses.\p"
	.string "During Gravity, the accuracy of\n"
	.string "all moves are raised, so you can\l"
	.string "try and use some moves that were\l"
	.string "too risky prior. Psychic type Pokemon,\l"
	.string "though, are smart enough to dodge\l"
	.string "attacks regularly in Gravity.\p"
	.string "This also obviously grounds all\n"
	.string "Pokemon on the field, so Flying type\l"
	.string "and Levitating ones can be hit by\l"
	.string "Ground type moves. In addition,\l"
	.string "they can't use moves like Fly that\l"
	.string "involve the user leaving the ground.\p"
	.string "Gravity can synergize with other\n"
	.string "moves too! Think, moves that have\l"
	.string "to do with weight, like Low Kick.\l"
	.string "They will do more damage!\p"
	.string "Give Gravity a spin the next time\n"
	.string "you're able to.$"

CosmossSpaceCenter_B1F_Text_AboutTerrains:
	.string "I like to use Terrains in battle\n"
	.string "to shake things up! There's a few\l"
	.string "of them, but they all have\l"
	.string "one thing in common: they only\l"
	.string "affect grounded Pokemon.\p"
	.string "So, if your Pokemon is a Flying type\n"
	.string "or has an ability like Levitate,\l"
	.string "well, Terrains don't matter to them!$"

CosmossSpaceCenter_B1F_Text_AboutMinkowski:
	.string "Lieutenant Minkowski used\n"
	.string "to be in charge around here before\l"
	.string "the Colonel stepped in and took\l"
	.string "the reins. She's been pretty\l"
	.string "angry about it, but she still\l"
	.string "does her job.\p"
	.string "If it came down to it, I'd defect\n"
	.string "to her over the Colonel. But I'd\l"
	.string "never tell either that.$"

CosmossSpaceCenter_B1F_Text_AboutOrbitBalls:
	.string "I've been cooperating with\n"
	.string "Devon... err, well, Greater\l"
	.string "Mauville Holdings, to work a bit\l"
	.string "on the Orbit Balls!\p"
	.string "They're a type of Pokeball that\n"
	.string "has a higher catch rate on\l"
	.string "Pokemon that come from, or are\l"
	.string "heavily associated with, outer space.\p"
	.string "Stomaway and Cryplin are a few\n"
	.string "examples. Try Orbit Balls out\l"
	.string "if you can get your hands on any!$"

CosmossSpaceCenter_Text_EnterCodeText:
	.string "Oi. I've been put in charge\n"
	.string "of the Space Center's\l"
	.string "encryption department.\p"
	.string "You'd be surprised how many\n"
	.string "encrypted messages and files\l"
	.string "find their way to our network\l"
	.string "from deep space. Most of the\l"
	.string "time, they're gibberish.\l"
	.string "Seems like they're all coincidences\l"
	.string "or scrambled data from satellites.\p"
	.string "There's this one I haven't been\n"
	.string "able to crack, though. And it's\l"
	.string "been on my mind for months.\l"
	.string "This one exe file that actually\l"
	.string "opened a basic program, asking\l"
	.string "for a four word passcode.\p"
	.string "I've tried so many combos, bruv.\n"
	.string "All came up short. So I've been\l"
	.string "hitting up anyone interested to\l"
	.string "take a crack at it.\p"
	.string "So? Want to enter the first of\n"
	.string "the four words? Can't hurt to try.$"

CosmossSpaceCenter_Text_EnterCode2:
	.string "W-Woah, alright, bruv. Seems like\n"
	.string "that first guess was on the money...!\p"
	.string "I've never seen it go to the\n"
	.string "second code before. We're in\l"
	.string "uncharted waters now.\p"
	.string "Maybe you know something I don't.\n"
	.string "Anyways, get ready for code 2.$"

CosmossSpaceCenter_Text_EnterCode3:
	.string "That's it! Cripes, never expected\n"
	.string "something like this outta you!\l"
	.string "Keep on keepin' on,\l"
	.string "here's code number 3.$"

CosmossSpaceCenter_Text_EnterCode4:
	.string "On more left to get right!\n"
	.string "I know you've probably got it!$"

CosmossSpaceCenter_Text_CodeEntrySuccess:
	.string "All four right? I'm very impressed!\p"
	.string "...\p"
	.string "...It just... closed the program?\n"
	.string "Did nothing else happen?\l"
	.string "Hold up, let me check task manager...\p"
	.string "...O-Oh, the uh, Network usage\n"
	.string "skyrocketted...\l"
	.string "Looks like my computer is sending\l"
	.string "out some sort of signal to space...?\p"
	.string "...Oh, no.\p"
	.string "SOMETHING just crash landed in\n"
	.string "Sweltorn Desert! I-I gotta brief\l"
	.string "my superiors, on the double!$"

CosmossSpaceCenter_Text_CodeEntryFail:
	.string "Ah, nuts! The program locked\n"
	.string "up again. Looks like that passcode\l"
	.string "wasn't entirely correct.$"

CosmossSpaceCenter_Text_CheckSweltorn:
	.string "Beans... I don't know what in\n"
	.string "the hell we just caused to happen,\l"
	.string "but it seems like something\l"
	.string "crashed in the desert.$"

CosmossSpaceCenter_Text_NoAccess:
	.string "(You hear a sassy female voice\n"
	.string "on the loudspeakers.)\p"
	.string "Excuse me!\p"
	.string "Where do you think you're going!?\n"
	.string "The upstairs is for trusted\l"
	.string "personnel only.$"

CosmossSpaceCenter_Text_AccessGranted:
	.string "(You hear a sassy female voice\n"
	.string "on the loudspeakers.)\p"
	.string "I've skimmed your public records…\p"
	.string "{PLAYER}, is it?\n"
	.string "Dr. Hilbert put in a good word,\l"
	.string "but I'm keeping my A-Eyes on you.\p"
	.string "Don't try anything funny.$"

CosmossSpaceCenter_Text_NeedHelpFunding:
	.string "Ah. A visitor.\p"
	.string "(The scientist tries ignoring you.)\p"
	.string "…What? You want big party?\n"
	.string "Bah, am currently in the middle of\l"
	.string "important work.\p"
	.string "Have been attempting to synthesize new\n"
	.string "green, reliable fuel for rockets.\l"
	.string "No dice.\p"
	.string "Have asked command for funding to help\n"
	.string "research go more smoothly.\l"
	.string "No dice.$"

CosmossSpaceCenter_Text_WillYouFund:
	.string "Would need approximately ¥5000 to\n"
	.string "gather necessary chemicals.\p"
	.string "(Hand over funding money?)$"

CosmossSpaceCenter_Text_ThenGoAway:
	.string "Still here?…\n"
	.string "If not helping, please leave my station.$"

CosmossSpaceCenter_Text_ThanksForFunding:
	.string "…Is quite… kind, of you.\n"
	.string "This will be put to good use.\p"
	.string "Here… take this as payment.$"

CosmossSpaceCenter_Text_YouCanNowGoUpstairs:
	.string "Will tell building AI that\n"
	.string "you assisted me…\l"
	.string "She may allow upstairs access now.$"

CosmossSpaceCenter_Text_NotEnoughMoney:
	.string "Still here?…\n"
	.string "If not helping, please leave my station.$"

CosmossSpaceCenter_Text_RocketFuel:
	.string "Mmph. Research making…\n"
	.string "many breakthroughs.$"

CosmossSpaceCenter_Text_BattleMyCryplin:
	.string "At ease.\p"
	.string "…\p"
	.string "Oh, I'm sorry, I thought you\n"
	.string "were an employee.\l"
	.string "My mistake.\p"
	.string "Though, I must say…\n"
	.string "you must be something special if Hera\l"
	.string "allowed you to come up here.\p"
	.string "I am a military lieutenant, on orders\n"
	.string "to assist the scientists here with the\l"
	.string "field research of extraterrestrial\l"
	.string "Pokémon.\p"
	.string "I have a few rowdy ones with\n"
	.string "me right now.\l"
	.string "Don't suppose you'd want to help them\l"
	.string "let off some steam?$"

CosmossSpaceCenter_Text_Understandable:
	.string "Understandable.\n"
	.string "Come see me if you change your mind.$"

CosmossSpaceCenter_Text_MinkowskiIntro:
	.string "Alright then.\p"
	.string "Cryplin!\n"
	.string "Get on out there; that's an order!$"

CosmossSpaceCenter_Text_MinkowskiDefeat:
	.string "A commanding victory!$"

CosmossSpaceCenter_Text_LearnedALot:
	.string "You displayed some real tactical moves\n"
	.string "with your team.\l"
	.string "I'm impressed.\p"
	.string "Here, I want you to take this\n"
	.string "Eject Pack; one of these has gotten\l"
	.string "me out of a precarious situation\l"
	.string "before, I tell you.$"

CosmossSpaceCenter_Text_HelpMyFriend:
	.string "If you have time, please check on my\n"
	.string "comms officer, Eiffel.\p"
	.string "He's the lackadaisical man pretending\n"
	.string "to work at the rightmost laptop.\p"
	.string "He, regrettably, is easily…\n"
	.string "distracted.$"

CosmossSpaceCenter_Text_AboutCryplin:
	.string "Our battle brought to mind the time\n"
	.string "I had to defend the facility from a\l"
	.string "rampaging Cardiovor.\p"
	.string "Hah… good times.\p"
	.string "If you have time, please check on my\n"
	.string "comms officer, Eiffel.\p"
	.string "He's the lackadaisical man pretending\n"
	.string "to work at the rightmost laptop.\p"
	.string "He, regrettably, is easily…\n"
	.string "distracted.$"

CosmossSpaceCenter_Text_HelpFightUFO:
	.string "What now?\p"
	.string "…Minkowski wants me to\n"
	.string "stop slacking off?\p"
	.string "Haha!\n"
	.string "Do birds chirp?\p"
	.string "Look, I dunno what command\n"
	.string "is expecting here.\p"
	.string "Do they really believe that my daily\n"
	.string "ET-Phoning-Home is gonna…$"

CosmossSpaceCenter_Text_AskFightUFO:
	.string "…Uhhh… am I officially off my rocker,\n"
	.string "or… am I seeing an unidentified signal\l"
	.string "at Launch Pad B…?\p"
	.string "C-could I get you to check\n"
	.string "that out for me?$"

CosmossSpaceCenter_Text_RadioWaves:
	.string "Oh, hey.\p"
	.string "Welcome to Casa-de-Doug, home of the\n"
	.string "“Useless Task Club.”\l"
	.string "On the docket today?\p"
	.string "Oh, lookin' like another 8 hours of\n"
	.string "sending out radio signals and\l"
	.string "seeing jack all.\p"
	.string "Fantastic.$"

CosmossSpaceCenter_Text_Matrix:
	.string "Right, right…\n"
	.string "must be a glitch in the matrix…$"

CosmossSpaceCenter_Text_ToTheField:
	.string "Okay…\n"
	.string "I'll send you over to Captain Lovelace.$"

CosmossSpaceCenter_Text_SavedTheRocket:
	.string "Watched you beat the crap out of that\n"
	.string "freaky floatin' curling stone\l"
	.string "from here. Kudos!$"

CosmossSpaceCenter_Text_MeteorsFallen:
	.string "While that was going on, I happened to\n"
	.string "spot a couple chunks of meteorite on\l"
	.string "a crash course for the\l"
	.string "bridge and the city.\p"
	.string "Seems like none of 'em\n"
	.string "did any major damage.\p"
	.string "If you want to go pick yourself up a\n"
	.string "genuine space rock, here's your shot.$"

CosmossSpaceCenter_Text_AboutUhefoe:
	.string "Yawn… back on the nada grind.\p"
	.string "Should steal myself more coffee\n"
	.string "when Minkowski isn't looking…$"

CosmossSpaceCenter_Text_CivilianNo:
	.string "Ah, hello there.\p"
	.string "You're a civilian, no?\p"
	.string "As the boss, I have to ask you to\n"
	.string "leave my team to their work.\l"
	.string "No distractions when we're making\l"
	.string "so much progress!$"

CosmossSpaceCenter_Text_GoCollectMinior:
	.string "Well, now, if it isn't Officer\n"
	.string "{PLAYER}!\p"
	.string "Oh? You're no officer?\p"
	.string "Pish-posh! Let's see the\n"
	.string "bigger picture here:\p"
	.string "You've been outperforming\n"
	.string "my subordinates! I'll have to give them\l"
	.string "a… stern talking to.\p"
	.string "While you're here, Officer {PLAYER},\n"
	.string "I could use some help.\p"
	.string "You see, I have an interest in those\n"
	.string "meteorites that have recently landed.\p"
	.string "I have concluded that they contain the\n"
	.string "Pokémon Minior, hiding inside.\p"
	.string "They come in many color variants.\n"
	.string "May I ask you to seek and capture all\l"
	.string "six? You will be rewarded.$"

CosmossSpaceCenter_Text_HaveThisShinyMinior:
	.string "Wonderful! You have all\n"
	.string "colors of Minior!\l"
	.string "What a pretty little rainbow.\p"
	.string "Except…\p"
	.string "Missing a color, aren't you?\p"
	.string "That's right, any self-respecting\n"
	.string "Minior expert would know there's 7\l"
	.string "variants.\p"
	.string "…But those are only found in\n"
	.string "Etheor Falls to the north.\p"
	.string "In fact, I have a special indigo\n"
	.string "colored Minior with your name on it.\p"
	.string "On behalf of all of us at the space\n"
	.string "center, you may have it.$"

CosmossSpaceCenter_Text_PlayerReceivedShinyMinior:
	.string "{PLAYER} received a special\n"
	.string "Indigo Minior!$"

CosmossSpaceCenter_Text_YoureTheBest:
	.string "My team sends their regards,\n"
	.string "Officer {PLAYER}.\l"
	.string "You can always feel welcome here!$"

CosmossSpaceCenter_Text_NotEnoughMinior:
	.string "From the looks of it, you don't have\n"
	.string "all six Minior forms on you.\p"
	.string "What a shame…\p"
	.string "Come meet me with all 6 in your party.$"

CosmossSpaceCenter_Text_SavedTheCenter:
	.string "Thank you for busting up\n"
	.string "that impressive automaton.\l"
	.string "I actually think Jacobi did a\l"
	.string "phenomenal job crafting it,\l"
	.string "though he did use parts from\l"
	.string "the generator without sanctions...\l"
	.string "so, as far as I'm concerned,\l"
	.string "he's dead to me.\p"
	.string "And you know what? He's dead\n"
	.string "to everyone else too! Because\l"
	.string "I was able to detonate that bomb\l"
	.string "strapped to his chest soon as\l"
	.string "he was isolated from Cosmoss Bridge.\l"
	.string "Kaboom! And there he went.\l"
	.string "Nothing but a crater.\p"
	.string "And it's all thanks to you!\n"
	.string "As a token of my appreciation,\l"
	.string "you can have this orb that was\l"
	.string "powering that massive robot.\l"
	.string "We have more potent energy sources\l"
	.string "lying around than that, trust me.$"

CosmossSpaceCenter_Text_ThanksForSaving:
	.string "Thank you for seeing the\n"
	.string "bigger picture in all this,\l"
	.string "Officer {PLAYER}. Toodles!$"

CosmossSpaceCenter_Text_TheMapPointsToRustboro:
	.string "(Your magical map shines once more,\n"
	.string "pointing you to your final location.)\p"
	.string "(This time, it is leading you to a\n"
	.string "structure in a cave you don't recognize...)$"
