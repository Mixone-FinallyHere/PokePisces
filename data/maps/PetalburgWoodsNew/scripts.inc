.set LOCALID_BREAD, 13

PetalburgWoodsNew_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PetalburgWoodsNew_OnLoad
	.byte 0

PetalburgWoodsNew_OnLoad:
	call PetalburgWoodsNew_EventScript_RemoveBreadwinner
	end

PetalburgWoodsNew_EventScript_RemoveBreadwinner::
	removeobject LOCALID_BREAD
	setflag FLAG_TEMP_13
	return

PetalburgWoodsNew_EventScript_BreadwinnerEncounter1::
	lock
	clearflag FLAG_TEMP_13
	addobject LOCALID_BREAD
	delay 4
	applymovement LOCALID_BREAD, PetalburgWoodsNew_Movement_BreadEnc1
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 4
	playse SE_PIN
	applymovement LOCALID_BREAD, PetalburgWoodsNew_Movement_BreadSurprised
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoodsNew_Movement_PlayerChaseBread1
	applymovement LOCALID_BREAD, PetalburgWoodsNew_Movement_BreadChased1
	waitmovement 0
	goto PetalburgWoodsNew_EventScript_BreadwinnerBattle
	release
	end

PetalburgWoodsNew_Movement_BreadEnc1:
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_left
	step_end

PetalburgWoodsNew_Movement_BreadSurprised:
	emote_exclamation_mark
	step_end

PetalburgWoodsNew_Movement_PlayerChaseBread1:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	face_right
	step_end

PetalburgWoodsNew_Movement_BreadChased1:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	step_end

PetalburgWoodsNew_EventScript_BreadwinnerEncounter2::
	lock
	clearflag FLAG_TEMP_13
	addobject LOCALID_BREAD
	delay 4
	applymovement LOCALID_BREAD, PetalburgWoodsNew_Movement_BreadEnc2
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 4
	playse SE_PIN
	applymovement LOCALID_BREAD, PetalburgWoodsNew_Movement_BreadSurprised
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgWoodsNew_Movement_PlayerChaseBread2
	applymovement LOCALID_BREAD, PetalburgWoodsNew_Movement_BreadChased2
	waitmovement 0
	goto PetalburgWoodsNew_EventScript_BreadwinnerBattle
	release
	end

PetalburgWoodsNew_Movement_BreadEnc2:
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_left
	step_end

PetalburgWoodsNew_Movement_PlayerChaseBread2:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	face_right
	step_end

PetalburgWoodsNew_Movement_BreadChased2:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	step_end

PetalburgWoodsNew_EventScript_BreadwinnerBattle::
	delay 8
	applymovement LOCALID_BREAD, PetalburgWoodsNew_Movement_BreadCornered
	waitmovement 0
	speakername PetalburgWoodsNew_Text_NamePandou
	trainerbattle_single TRAINER_P_PANDOU_5, PetalburgWoodsNew_Text_BreadwinnerIntro, PetalburgWoodsNew_Text_BreadwinnerDefeat, PetalburgWoodsNew_EventScript_BreadRun
	release
	end

PetalburgWoodsNew_EventScript_BreadRun::
	setvar VAR_BREADWINNER_STATE, 5
	speakername PetalburgWoodsNew_Text_NamePandou
	msgbox PetalburgWoodsNew_Text_BreadwinnerRunAway, MSGBOX_DEFAULT
	closemessage
	playse SE_FLEE
	applymovement LOCALID_BREAD, PetalburgWoodsNew_Movement_BreadEscape
	waitmovement 0
	removeobject LOCALID_BREAD
	setflag FLAG_TEMP_13
	release
	end

PetalburgWoodsNew_Movement_BreadCornered:
	face_right
	delay_16
	face_up
	delay_16
	face_down
	delay_16
	face_left
	delay_16
	step_end

PetalburgWoodsNew_Movement_BreadEscape:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoodsNew_EventScript_BirdhouseShishima::
	lock
	goto_if_set FLAG_DEFEATED_SHISHIMA, PetalburgWoodsNew_EventScript_BirdPost
	msgbox PetalburgWoodsNew_Text_DoYouLookInside, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgWoodsNew_EventScript_ShishimaBattle
	msgbox PetalburgWoodsNew_Text_ProbablyShouldnt, MSGBOX_AUTOCLOSE
	release
	end

PetalburgWoodsNew_EventScript_ShishimaBattle::
	setwildbattle SPECIES_SHISHIMA, 66
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 5, 0, 1, 5, 1, 1
	playmoncry SPECIES_SHISHIMA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox PetalburgWoodsNew_Text_PunishingPresence, MSGBOX_DEFAULT
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	goto PetalburgWoodsNew_EventScript_ShishimaDefeat
	release
	end

PetalburgWoodsNew_EventScript_ShishimaDefeat::
	msgbox PetalburgWoodsNew_Text_ShishimaBecameEgg, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SHISHIMA
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EXEGGCUTE
	giveegg SPECIES_SHISHIMA
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, PetalburgWoodsNew_EventScript_ReceiveEggParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, PetalburgWoodsNew_EventScript_ReceiveEggPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

PetalburgWoodsNew_EventScript_BirdhouseOlFlookie::
	lock
	goto_if_set FLAG_DEFEATED_OLFLOOKIE, PetalburgWoodsNew_EventScript_BirdPost
	msgbox PetalburgWoodsNew_Text_DoYouLookInside, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgWoodsNew_EventScript_OlFlookieBattle
	msgbox PetalburgWoodsNew_Text_ProbablyShouldnt, MSGBOX_AUTOCLOSE
	release
	end

PetalburgWoodsNew_EventScript_OlFlookieBattle::
	setwildbattle SPECIES_OLFLOOKIE, 66
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 5, 0, 1, 5, 1, 1
	playmoncry SPECIES_OLFLOOKIE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox PetalburgWoodsNew_Text_BigPresence, MSGBOX_DEFAULT
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	goto PetalburgWoodsNew_EventScript_OlFlookieDefeat
	release
	end

PetalburgWoodsNew_EventScript_OlFlookieDefeat::
	msgbox PetalburgWoodsNew_Text_OlFlookieBecameEgg, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_OLFLOOKIE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EXEGGCUTE
	giveegg SPECIES_OLFLOOKIE
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, PetalburgWoodsNew_EventScript_ReceiveEggParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, PetalburgWoodsNew_EventScript_ReceiveEggPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

PetalburgWoodsNew_EventScript_BirdhouseJustricha::
	lock
	goto_if_set FLAG_DEFEATED_JUSTRICHA, PetalburgWoodsNew_EventScript_BirdPost
	msgbox PetalburgWoodsNew_Text_DoYouLookInside, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgWoodsNew_EventScript_JustrichaBattle
	msgbox PetalburgWoodsNew_Text_ProbablyShouldnt, MSGBOX_AUTOCLOSE
	release
	end

PetalburgWoodsNew_EventScript_JustrichaBattle::
	setwildbattle SPECIES_JUSTRICHA, 66
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 5, 0, 1, 5, 1, 1
	playmoncry SPECIES_JUSTRICHA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox PetalburgWoodsNew_Text_JudgingPresence, MSGBOX_DEFAULT
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	goto PetalburgWoodsNew_EventScript_JustrichaDefeat
	release
	end

PetalburgWoodsNew_EventScript_JustrichaDefeat::
	msgbox PetalburgWoodsNew_Text_JustrichaBecameEgg, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_JUSTRICHA
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EXEGGCUTE
	giveegg SPECIES_JUSTRICHA
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, PetalburgWoodsNew_EventScript_ReceiveEggParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, PetalburgWoodsNew_EventScript_ReceiveEggPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

PetalburgWoodsNew_EventScript_BirdPost::
	msgbox PetalburgWoodsNew_Text_BirdIsGone, MSGBOX_AUTOCLOSE
	release
	end

PetalburgWoodsNew_EventScript_ReceiveEggParty::
	call PetalburgWoodsNew_EventScript_ReceivedEggFanfare
	release
	end

PetalburgWoodsNew_EventScript_ReceiveEggPC::
	call PetalburgWoodsNew_EventScript_ReceivedEggFanfare
	call Common_EventScript_TransferredToPC
	release
	end

PetalburgWoodsNew_EventScript_ReceivedEggFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message PetalburgWoodsNew_Text_PlayerReceivedEgg
	waitmessage
	waitfanfare
	return

PetalburgWoodsNew_EventScript_Tutu::
    trainerbattle_single TRAINER_P_TUTU, PetalburgWoodsNew_Text_TutuIntro, PetalburgWoodsNew_Text_TutuDefeated
    msgbox PetalburgWoodsNew_Text_TutuPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Duck::
    trainerbattle_single TRAINER_P_DUCK, PetalburgWoodsNew_Text_DuckIntro, PetalburgWoodsNew_Text_DuckDefeated
    msgbox PetalburgWoodsNew_Text_DuckPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Violet::
    trainerbattle_single TRAINER_P_VIOLET, PetalburgWoodsNew_Text_VioletIntro, PetalburgWoodsNew_Text_VioletDefeated
    msgbox PetalburgWoodsNew_Text_VioletPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Elizabeth::
    trainerbattle_single TRAINER_P_ELIZABETH, PetalburgWoodsNew_Text_ElizabethIntro, PetalburgWoodsNew_Text_ElizabethDefeated
    msgbox PetalburgWoodsNew_Text_ElizabethPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Artie::
    trainerbattle_single TRAINER_P_ARTIE, PetalburgWoodsNew_Text_ArtieIntro, PetalburgWoodsNew_Text_ArtieDefeated
    msgbox PetalburgWoodsNew_Text_ArtiePostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Gyomaru::
    trainerbattle_single TRAINER_P_GYOMARU, PetalburgWoodsNew_Text_GyomaruIntro, PetalburgWoodsNew_Text_GyomaruDefeated
    msgbox PetalburgWoodsNew_Text_GyomaruPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Suzume::
    trainerbattle_single TRAINER_P_SUZUME, PetalburgWoodsNew_Text_SuzumeIntro, PetalburgWoodsNew_Text_SuzumeDefeated
    msgbox PetalburgWoodsNew_Text_SuzumePostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Mio::
    trainerbattle_single TRAINER_P_MIO, PetalburgWoodsNew_Text_MioIntro, PetalburgWoodsNew_Text_MioDefeated
    msgbox PetalburgWoodsNew_Text_MioPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Lemmy::
    trainerbattle_single TRAINER_P_LEMMY, PetalburgWoodsNew_Text_LemmyIntro, PetalburgWoodsNew_Text_LemmyDefeated
    msgbox PetalburgWoodsNew_Text_LemmyPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_Ichi::
    trainerbattle_single TRAINER_P_ICHI, PetalburgWoodsNew_Text_IchiIntro, PetalburgWoodsNew_Text_IchiDefeated
    msgbox PetalburgWoodsNew_Text_IchiPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_EventScript_InuAndPersia::
    trainerbattle_double TRAINER_P_INU_AND_PERSIA, PetalburgWoodsNew_Text_InuAndPersiaIntro, PetalburgWoodsNew_Text_InuAndPersiaDefeated, PetalburgWoodsNew_Text_InuAndPersiaNeedTwoMons
    msgbox PetalburgWoodsNew_Text_InuAndPersiaPostBattle, MSGBOX_AUTOCLOSE
    end

PetalburgWoodsNew_Text_TutuIntro:
	.string "Happiness is a tale,\n"
	.string "granted by fate.$"

PetalburgWoodsNew_Text_TutuDefeated:
	.string "Happiness is a tale,\n"
	.string "a dream so distant...$"

PetalburgWoodsNew_Text_TutuPostBattle:
	.string "Go chase that happiness, little\n"
	.string "goose. Go chase that fading dream.$"

PetalburgWoodsNew_Text_DuckIntro:
	.string "Fall, wallow in despair! This\n"
	.string "story needs an ending most tragic!$"

PetalburgWoodsNew_Text_DuckDefeated:
	.string "I, the tragic heroine, swallowed\n"
	.string "by hardships!$"

PetalburgWoodsNew_Text_DuckPostBattle:
	.string "A tale that ends in bliss is\n"
	.string "the epitome of boredom.$"

PetalburgWoodsNew_Text_VioletIntro:
	.string "Behold, my regal indigo hue!$"

PetalburgWoodsNew_Text_VioletDefeated:
	.string "What? You look as if you've\n"
	.string "seen a ghost...$"

PetalburgWoodsNew_Text_VioletPostBattle:
	.string "I'm a Hex Maniac! I especially\n"
	.string "love the hex color 5548A6.\l"
	.string "What is yours?$"

PetalburgWoodsNew_Text_ElizabethIntro:
	.string "My dynasty shall outlive yours!$"

PetalburgWoodsNew_Text_ElizabethDefeated:
	.string "Conquered so soon...!?$"

PetalburgWoodsNew_Text_ElizabethPostBattle:
	.string "My family line will\n"
	.string "seek power, no matter the cost...$"

PetalburgWoodsNew_Text_ArtieIntro:
	.string "Let me guess, your Pokemon\n"
	.string "were wild-caught, right?\l"
	.string "Hmph, to be expected.$"

PetalburgWoodsNew_Text_ArtieDefeated:
	.string "What!? No way... my finely\n"
	.string "bred and raised team, taken down!?$"

PetalburgWoodsNew_Text_ArtiePostBattle:
	.string "How could my Pokemon be trounced\n"
	.string "by a bunch of wild savages? It\l"
	.string "just doesn't make any sense!$"

PetalburgWoodsNew_Text_GyomaruIntro:
	.string "Many a malevolent entity resides\n"
	.string "within this thicket... could\l"
	.string "you be influenced by them?$"

PetalburgWoodsNew_Text_GyomaruDefeated:
	.string "...My reconaissance remains\n"
	.string "inconclusive.$"

PetalburgWoodsNew_Text_GyomaruPostBattle:
	.string "Keep a level head, trainer, lest\n"
	.string "you lose yourself in these woods...$"

PetalburgWoodsNew_Text_SuzumeIntro:
	.string "My younger sister and I... we\n"
	.string "will show you true determination!$"

PetalburgWoodsNew_Text_SuzumeDefeated:
	.string "Father, forgive us... we could\n"
	.string "not win this melee...$"

PetalburgWoodsNew_Text_SuzumePostBattle:
	.string "I wish that I could have the\n"
	.string "carefree attitude of my sibling.\l"
	.string "May she never grow up.$"

PetalburgWoodsNew_Text_MioIntro:
	.string "If I'm with my sister...\n"
	.string "we can do anything!$"

PetalburgWoodsNew_Text_MioDefeated:
	.string "We had on our rose-tinted glasses...$"

PetalburgWoodsNew_Text_MioPostBattle:
	.string "I can't wait to be just like\n"
	.string "Suzume when I get older!$"

PetalburgWoodsNew_Text_LemmyIntro:
	.string "With my brother and I on the prowl,\n"
	.string "we'll collect every Pokemon\l"
	.string "in Hoenn!$"

PetalburgWoodsNew_Text_LemmyDefeated:
	.string "We didn't stay calm and collected!$"

PetalburgWoodsNew_Text_LemmyPostBattle:
	.string "My brother and I really could\n"
	.string "do better if he wasn't so obsessed\l"
	.string "with hunting Shiny Pokemon.$"

PetalburgWoodsNew_Text_IchiIntro:
	.string "Nyee-hee...! I have a PARTICULARLY\n"
	.string "rare Pokemon to show off!\l"
	.string "It will look amazing as it\l"
	.string "PUMMELS you!$"

PetalburgWoodsNew_Text_IchiDefeated:
	.string "M-M-M-MY PRIZED POSSESSION!$"

PetalburgWoodsNew_Text_IchiPostBattle:
	.string "Shiny Pokemon are the ONLY ONES\n"
	.string "that really matter. Those common\l"
	.string "colored variants... forget them!$"

PetalburgWoodsNew_Text_InuAndPersiaIntro:
	.string "INU: Canine Pokemon...\n"
	.string "PERSIA: Feline Pokemon...\p"
	.string "INU: Together...\n"
	.string "PERSIA: They dominate!$"

PetalburgWoodsNew_Text_InuAndPersiaDefeated:
	.string "INU: We're all bark, no bite...\n"
	.string "PERSIA: And you were the cat's meow!$"

PetalburgWoodsNew_Text_InuAndPersiaPostBattle:
	.string "INU: Maybe we should switch to\n"
	.string "     training equine Pokemon instead.\l"
	.string "PERSIA: I'll start looking!$"

PetalburgWoodsNew_Text_InuAndPersiaNeedTwoMons:
	.string "INU: It'll start raining cats\n"
	.string "     and dogs before we fight\l"
	.string "     you with only one 'mon!$"

PetalburgWoodsNew_Text_NamePandou:
	.string "Pandou$"

PetalburgWoodsNew_Text_BreadwinnerIntro:
	.string "...Is this some sort of\n"
	.string "divine punishment...?\p"
	.string "I get lost in the woods on my\n"
	.string "way to work, only to be\l"
	.string "cornered by you again when\l"
	.string "I finally get my bearings...\l"
	.string "life has its ways of kicking\l"
	.string "you while you're down, I suppose...\p"
	.string "Sigh... A-Alright, you just want\n"
	.string "your battle, right? That's all?\p"
	.string "(You nod. He seems to finally\n"
	.string "understand the deal here.)\p"
	.string "You know, my Kodough don't seem\n"
	.string "to mind the fights. They're\l"
	.string "squishy and don't particularly\l"
	.string "get bruised... so, since\l"
	.string "they like it, I'll cooperate.\p"
	.string "B-But, at least make it kind of\n"
	.string "quick... I still have to clock in...$"

PetalburgWoodsNew_Text_BreadwinnerDefeat:
	.string "The Kodough are giggling\n"
	.string "with glee...! That makes me\l"
	.string "want to smile, too...\p"
	.string "(He glances at his watch.)\p"
	.string "B-Blast! I can't keep wasting time!$"

PetalburgWoodsNew_Text_BreadwinnerRunAway:
	.string "Alright, th-there's your battle...\n"
	.string "satisfied? I hope?\p"
	.string "Look, I'll battle you again someday,\n"
	.string "just, stay out of my commute path\l"
	.string "for the time being, okay...?\p"
	.string "(You are moderately accepting\n"
	.string "of this proposal. Moderately.)\p"
	.string "I've got to make tracks...\n"
	.string "g-goodbye...$"

PetalburgWoodsNew_Text_DoYouLookInside:
	.string "(It's an oversized birdhouse...)\p"
	.string "(You can hear scratching noises\n"
	.string "inside... do you attempt to make\l"
	.string "whatever is in there come out?)$"

PetalburgWoodsNew_Text_ProbablyShouldnt:
	.string "(That WOULD probably be a bad idea.)$"

PetalburgWoodsNew_Text_PunishingPresence:
	.string "(You sense a punishing aura\n"
	.string "emanating from the birdhouse...!)\p"
	.string "(A Pokemon came out to attack you!)$"

PetalburgWoodsNew_Text_BigPresence:
	.string "(You sense a large presence\n"
	.string "emanating from the birdhouse...!)\p"
	.string "(A Pokemon came out to attack you!)$"

PetalburgWoodsNew_Text_JudgingPresence:
	.string "(You sense a feeling of judgment\n"
	.string "emanating from the birdhouse...!)\p"
	.string "(A Pokemon came out to attack you!)$"

PetalburgWoodsNew_Text_ShishimaBecameEgg:
	.string "(The felled Wild Shishima\n"
	.string "transformed into an Egg before\l"
	.string "your very eyes...)\p"
	.string "(Guess you should take it?)$"

PetalburgWoodsNew_Text_OlFlookieBecameEgg:
	.string "(The felled Wild Ol'Flookie\n"
	.string "transformed into an Egg before\l"
	.string "your very eyes...)\p"
	.string "(Guess you should take it?)$"

PetalburgWoodsNew_Text_JustrichaBecameEgg:
	.string "(The felled Wild Justricha\n"
	.string "transformed into an Egg before\l"
	.string "your very eyes...)\p"
	.string "(Guess you should take it?)$"

PetalburgWoodsNew_Text_PlayerReceivedEgg:
	.string "{PLAYER} received an Egg!$"

PetalburgWoodsNew_Text_BirdIsGone:
	.string "(That abnormal avian Pokemon\n"
	.string "is no longer in its birdhouse.)$"
