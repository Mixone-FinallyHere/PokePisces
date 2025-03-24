JaggroPass_MapScripts::
	.byte 0

JaggroPass_EventScript_GravelitoIdle::
	lock
	setflag FLAG_TEMP_A
	clearflag FLAG_TEMP_B
	msgbox JaggroPass_Text_ItsHumming, MSGBOX_DEFAULT
	goto JaggroPass_EventScript_CheckSing
	release
	end

JaggroPass_EventScript_MegalitoIdle::
	lock
	clearflag FLAG_TEMP_A
	setflag FLAG_TEMP_B
	msgbox JaggroPass_Text_ItsBellowing, MSGBOX_DEFAULT
	goto JaggroPass_EventScript_CheckSing
	release
	end

JaggroPass_EventScript_CheckSing::
	checkpartynonhmmove MOVE_SING
	goto_if_eq VAR_RESULT, PARTY_SIZE, JaggroPass_EventScript_CheckPerishSong
	goto_if_set FLAG_TEMP_A, JaggroPass_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, JaggroPass_EventScript_MegalitoBattle
	release
	end

JaggroPass_EventScript_CheckPerishSong::
	checkpartynonhmmove MOVE_PERISH_SONG
	goto_if_eq VAR_RESULT, PARTY_SIZE, JaggroPass_EventScript_CheckGrassWhistle
	goto_if_set FLAG_TEMP_A, JaggroPass_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, JaggroPass_EventScript_MegalitoBattle
	release
	end

JaggroPass_EventScript_CheckGrassWhistle::
	checkpartynonhmmove MOVE_GRASS_WHISTLE
	goto_if_eq VAR_RESULT, PARTY_SIZE, JaggroPass_EventScript_CheckRound
	goto_if_set FLAG_TEMP_A, JaggroPass_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, JaggroPass_EventScript_MegalitoBattle
	release
	end

JaggroPass_EventScript_CheckRound::
	checkpartynonhmmove MOVE_ROUND
	goto_if_eq VAR_RESULT, PARTY_SIZE, JaggroPass_EventScript_CheckSparklingAria
	goto_if_set FLAG_TEMP_A, JaggroPass_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, JaggroPass_EventScript_MegalitoBattle
	release
	end

JaggroPass_EventScript_CheckSparklingAria::
	checkpartynonhmmove MOVE_SPARKLING_ARIA
	goto_if_eq VAR_RESULT, PARTY_SIZE, JaggroPass_EventScript_CheckTorchSong
	goto_if_set FLAG_TEMP_A, JaggroPass_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, JaggroPass_EventScript_MegalitoBattle
	release
	end

JaggroPass_EventScript_CheckTorchSong::
	checkpartynonhmmove MOVE_TORCH_SONG
	goto_if_eq VAR_RESULT, PARTY_SIZE, JaggroPass_EventScript_CheckBeatbox
	goto_if_set FLAG_TEMP_A, JaggroPass_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, JaggroPass_EventScript_MegalitoBattle
	release
	end

JaggroPass_EventScript_CheckBeatbox::
	checkpartynonhmmove MOVE_BEATBOX
	goto_if_eq VAR_RESULT, PARTY_SIZE, JaggroPass_EventScript_CheckBeatDrop
	goto_if_set FLAG_TEMP_A, JaggroPass_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, JaggroPass_EventScript_MegalitoBattle
	release
	end

JaggroPass_EventScript_CheckBeatDrop::
	checkpartynonhmmove MOVE_BEAT_DROP
	goto_if_eq VAR_RESULT, PARTY_SIZE, JaggroPass_EventScript_NoSingingMoves
	goto_if_set FLAG_TEMP_A, JaggroPass_EventScript_GravelitoBattle
	goto_if_set FLAG_TEMP_B, JaggroPass_EventScript_MegalitoBattle
	release
	end

JaggroPass_EventScript_NoSingingMoves::
	msgbox JaggroPass_Text_NoSingingMove, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

JaggroPass_EventScript_GravelitoBattle::
	lock
	msgbox JaggroPass_Text_ItBecameLively, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_GRAVELITO, 31
	playmoncry SPECIES_GRAVELITO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	removeobject VAR_LAST_TALKED
	release
	end

JaggroPass_EventScript_MegalitoBattle::
	lock
	msgbox JaggroPass_Text_ItBecameLively, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_MEGALITO, 35
	playmoncry SPECIES_MEGALITO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	removeobject VAR_LAST_TALKED
	release
	end

JaggroPass_EventScript_Emmy::
    trainerbattle_single TRAINER_P_EMMY, JaggroPass_Text_EmmyIntro, JaggroPass_Text_EmmyDefeated
    msgbox JaggroPass_Text_EmmyPostBattle, MSGBOX_AUTOCLOSE
    end

JaggroPass_EventScript_Dayton::
    trainerbattle_single TRAINER_P_DAYTON, JaggroPass_Text_DaytonIntro, JaggroPass_Text_DaytonDefeated
    msgbox JaggroPass_Text_DaytonPostBattle, MSGBOX_AUTOCLOSE
    end

JaggroPass_EventScript_Anto::
    trainerbattle_single TRAINER_P_ANTO, JaggroPass_Text_AntoIntro, JaggroPass_Text_AntoDefeated
    msgbox JaggroPass_Text_AntoPostBattle, MSGBOX_AUTOCLOSE
    end

JaggroPass_EventScript_Baze::
    trainerbattle_single TRAINER_P_BAZE, JaggroPass_Text_BazeIntro, JaggroPass_Text_BazeDefeated
    msgbox JaggroPass_Text_BazePostBattle, MSGBOX_AUTOCLOSE
    end

JaggroPass_EventScript_Chinzao::
    trainerbattle_single TRAINER_P_CHINZAO, JaggroPass_Text_ChinzaoIntro, JaggroPass_Text_ChinzaoDefeated
    msgbox JaggroPass_Text_ChinzaoPostBattle, MSGBOX_AUTOCLOSE
    end

JaggroPass_EventScript_Marimar::
    trainerbattle_single TRAINER_P_MARIMAR, JaggroPass_Text_MarimarIntro, JaggroPass_Text_MarimarDefeated
    msgbox JaggroPass_Text_MarimarPostBattle, MSGBOX_AUTOCLOSE
    end

JaggroPass_EventScript_Jelly::
    trainerbattle_single TRAINER_P_JELLY, JaggroPass_Text_JellyIntro, JaggroPass_Text_JellyDefeated
    msgbox JaggroPass_Text_JellyPostBattle, MSGBOX_AUTOCLOSE
    end

JaggroPass_EventScript_AreYouLostSign::
	msgbox JaggroPass_Text_AreYouLostSign, MSGBOX_SIGN
	end

JaggroPass_Text_AreYouLostSign:
	.string "Greetings, travelers!\n"
	.string "Are you lost? This sign can\l"
	.string "point you in the right direction.\p"
	.string "NORTH is Jaggro Pass, which leads\n"
	.string "into Fallarbor Town.\p"
	.string "EAST is Crimney Climb, with access\n"
	.string "to the Catacombs and Lavaridge Town.\p"
	.string "SOUTH leads to Rustboro City,\n"
	.string "through Whisper Cliff.\p"
	.string "WEST leads to Etheor Falls,\n"
	.string "if you are able to cross the water.$"

JaggroPass_Text_EmmyIntro:
	.string "Submarines, planes, I've\n"
	.string "worked on every vessel!$"

JaggroPass_Text_EmmyDefeated:
	.string "I sunk while you soared!$"

JaggroPass_Text_EmmyPostBattle:
	.string "I only work on planes or subs\n"
	.string "when they're on dry land.\l"
	.string "I hate flying, and I\l"
	.string "hate being underwater too!$"

JaggroPass_Text_DaytonIntro:
	.string "Let's soak up some Vitamin D!\n"
	.string "It's good for you!$"

JaggroPass_Text_DaytonDefeated:
	.string "I've just absorbed some\n"
	.string "Vitamin D-feat...$"

JaggroPass_Text_DaytonPostBattle:
	.string "All kinds of Pokémon like the bright\n"
	.string "sun. Berries like the sun, too!$"

JaggroPass_Text_AntoIntro:
	.string "Na-a-a! Wrong way.$"

JaggroPass_Text_AntoDefeated:
	.string "I SAID, wrong way!!$"

JaggroPass_Text_AntoPostBattle:
	.string "Fine, you can go, since you\n"
	.string "took down my grandpa.$"

JaggroPass_Text_BazeIntro:
	.string "I must train the next\n"
	.string "generation to surpass me!\l"
	.string "Otherwise, my bloodline will end!\l"
	.string "My granddaughter and I\l"
	.string "will demolish you...!$"

JaggroPass_Text_BazeDefeated:
	.string "And so doth the bloodline cease.$"

JaggroPass_Text_BazePostBattle:
	.string "Young Anto still has\n"
	.string "much, MUCH to learn...$"

JaggroPass_Text_ChinzaoIntro:
	.string "Oh, a customer? Splendid!\n"
	.string "What would you like?$"

JaggroPass_Text_ChinzaoDefeated:
	.string "That's one battle, charged\n"
	.string "straight to your credit card!$"

JaggroPass_Text_ChinzaoPostBattle:
	.string "Do you want something else?$"

JaggroPass_Text_MarimarIntro:
	.string "Hey, dollface! Did it hurt\n"
	.string "when you fell from heaven?$"

JaggroPass_Text_MarimarDefeated:
	.string "Ouchie! That hurt...\n$"

JaggroPass_Text_MarimarPostBattle:
	.string "Did it NOT hurt when you fell\n"
	.string "from heaven?\p"
	.string "Because you have a tough outer\n"
	.string "shell, just like Minior...$"

JaggroPass_Text_JellyIntro:
	.string "It has come to my attention\n"
	.string "that my surname is quite puerile.\l"
	.string "I believe our family's reputation\l"
	.string "precedes us, still!$"

JaggroPass_Text_JellyDefeated:
	.string "I have been stuck in a jam!$"

JaggroPass_Text_JellyPostBattle:
	.string "It is said that my family had once\n"
	.string "made regular visits to the castle\l"
	.string "in Sootopolis before it fell\l"
	.string "into abandonment...$"

JaggroPass_Text_ItsHumming:
	.string "(This strange plant seems\n"
	.string "to be humming a tune...)$"

JaggroPass_Text_ItsBellowing:
	.string "(This strange plant seems to be\n"
	.string "bellowing out an operetta...)$"

JaggroPass_Text_NoSingingMove:
	.string "(...Nothing you can really\n"
	.string "do with it right now.)$"

JaggroPass_Text_ItBecameLively:
	.string "(Your Pokemon used a singing move\n"
	.string "to add to the harmony...)\p"
	.string "(The plant became lively!\n"
	.string "It's a Wild Pokemon!)$"
