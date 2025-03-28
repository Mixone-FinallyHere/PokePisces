.set LOCALID_BREAD, 26

EverGrandeRoad_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeRoad_OnLoad
	.byte 0

EverGrandeRoad_OnLoad:
	call EverGrandeRoad_EventScript_RemoveBreadwinner
	call_if_gt VAR_BREADWINNER_STATE, 5, EverGrandeRoad_EventScript_SetTempVar
	end

EverGrandeRoad_EventScript_RemoveBreadwinner::
	removeobject LOCALID_BREAD
	setflag FLAG_TEMP_13
	return

EverGrandeRoad_EventScript_SetTempVar::
	setvar VAR_TEMP_4, 1
	return

EverGrandeRoad_EventScript_MusicTrigger::
	end

EverGrandeRoad_EventScript_BreadEncounter1::
	lock
	clearflag FLAG_TEMP_13
	addobject LOCALID_BREAD
	delay 4
	applymovement LOCALID_BREAD, EverGrandeRoad_Movement_PlayerNotice
	waitmovement 0
	applymovement LOCALID_BREAD, EverGrandeRoad_Movement_BreadWalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeRoad_Movement_PlayerChaseBread1
	waitmovement 0
	goto EverGrandeRoad_EventScript_BreadwinnerBattle
	release
	end

EverGrandeRoad_Movement_PlayerNotice:
	face_down
	emote_exclamation_mark
	step_end

EverGrandeRoad_Movement_BreadWalkUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandeRoad_Movement_PlayerChaseBread1:
	walk_down
	walk_right
	face_down
	step_end

EverGrandeRoad_EventScript_BreadEncounter2::
	lock
	clearflag FLAG_TEMP_13
	addobject LOCALID_BREAD
	delay 4
	applymovement LOCALID_BREAD, EverGrandeRoad_Movement_PlayerNotice
	waitmovement 0
	applymovement LOCALID_BREAD, EverGrandeRoad_Movement_BreadWalkUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeRoad_Movement_PlayerChaseBread2
	waitmovement 0
	goto EverGrandeRoad_EventScript_BreadwinnerBattle
	release
	end

EverGrandeRoad_Movement_PlayerChaseBread2:
	walk_down
	walk_left
	face_down
	step_end

EverGrandeRoad_EventScript_BreadEncounter3::
	lock
	clearflag FLAG_TEMP_13
	addobject LOCALID_BREAD
	delay 4
	applymovement LOCALID_BREAD, EverGrandeRoad_Movement_PlayerNotice
	waitmovement 0
	applymovement LOCALID_BREAD, EverGrandeRoad_Movement_BreadWalkUp
	waitmovement 0
	delay 4
	goto EverGrandeRoad_EventScript_BreadwinnerBattle
	release
	end

EverGrandeRoad_EventScript_BreadwinnerBattle::
	delay 8
	setvar VAR_TEMP_4, 1
	speakername EverGrandeRoad_Text_NamePandou
	msgbox EverGrandeRoad_Text_BreadwinnerIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_PANDOU_6, EverGrandeRoad_Text_BreadwinnerDefeat
	goto EverGrandeRoad_EventScript_BreadRun
	release
	end

EverGrandeRoad_EventScript_BreadRun::
	setvar VAR_BREADWINNER_STATE, 6
	speakername EverGrandeRoad_Text_NamePandou
	msgbox EverGrandeRoad_Text_BreadwinnerRunAway, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BREAD, EverGrandeRoad_Movement_BreadEscape
	waitmovement 0
	opendoor 79, 5
	applymovement LOCALID_BREAD, EverGrandeRoad_Movement_BreadGoThruDoor
	waitmovement 0
	closedoor 79, 5
	removeobject LOCALID_BREAD
	setflag FLAG_TEMP_13
	release
	end

EverGrandeRoad_Movement_BreadEscape:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	face_up
	step_end

EverGrandeRoad_Movement_BreadGoThruDoor:
	walk_up
	step_end

EverGrandeRoad_EventScript_RaoTwunne::
    trainerbattle_single TRAINER_P_RAO_TWUNNE, EverGrandeRoad_Text_RaoTwunneIntro, EverGrandeRoad_Text_RaoTwunneDefeated
    msgbox EverGrandeRoad_Text_RaoTwunnePostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Jamiroquai::
    trainerbattle_single TRAINER_P_JAMIROQUAI, EverGrandeRoad_Text_JamiroquaiIntro, EverGrandeRoad_Text_JamiroquaiDefeated
    msgbox EverGrandeRoad_Text_JamiroquaiPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Kumqot::
    trainerbattle_single TRAINER_P_KUMQOT, EverGrandeRoad_Text_KumqotIntro, EverGrandeRoad_Text_KumqotDefeated
    msgbox EverGrandeRoad_Text_KumqotPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Dorian::
    trainerbattle_single TRAINER_P_DORIAN, EverGrandeRoad_Text_DorianIntro, EverGrandeRoad_Text_DorianDefeated
    msgbox EverGrandeRoad_Text_DorianPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Lytxi::
    trainerbattle_single TRAINER_P_LYTXI, EverGrandeRoad_Text_LytxiIntro, EverGrandeRoad_Text_LytxiDefeated
    msgbox EverGrandeRoad_Text_LytxiPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Sherimoya::
    trainerbattle_single TRAINER_P_SHERIMOYA, EverGrandeRoad_Text_SherimoyaIntro, EverGrandeRoad_Text_SherimoyaDefeated
    msgbox EverGrandeRoad_Text_SherimoyaPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Melulu::
    trainerbattle_single TRAINER_P_MELULU, EverGrandeRoad_Text_MeluluIntro, EverGrandeRoad_Text_MeluluDefeated
    msgbox EverGrandeRoad_Text_MeluluPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_PyoRin::
    trainerbattle_single TRAINER_P_PYORIN, EverGrandeRoad_Text_PyoRinIntro, EverGrandeRoad_Text_PyoRinDefeated
    msgbox EverGrandeRoad_Text_PyoRinPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Min::
    trainerbattle_single TRAINER_P_MIN, EverGrandeRoad_Text_MinIntro, EverGrandeRoad_Text_MinDefeated
    msgbox EverGrandeRoad_Text_MinPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Max::
    trainerbattle_single TRAINER_P_MAX, EverGrandeRoad_Text_MaxIntro, EverGrandeRoad_Text_MaxDefeated
    msgbox EverGrandeRoad_Text_MaxPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Artemis::
    trainerbattle_single TRAINER_P_ARTEMIS, EverGrandeRoad_Text_ArtemisIntro, EverGrandeRoad_Text_ArtemisDefeated
    msgbox EverGrandeRoad_Text_ArtemisPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Garena::
    trainerbattle_single TRAINER_P_GARENA, EverGrandeRoad_Text_GarenaIntro, EverGrandeRoad_Text_GarenaDefeated
    msgbox EverGrandeRoad_Text_GarenaPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Goro::
    trainerbattle_single TRAINER_P_GORO, EverGrandeRoad_Text_GoroIntro, EverGrandeRoad_Text_GoroDefeated
    msgbox EverGrandeRoad_Text_GoroPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Miernie::
    trainerbattle_single TRAINER_P_MIERNIE, EverGrandeRoad_Text_MiernieIntro, EverGrandeRoad_Text_MiernieDefeated
    msgbox EverGrandeRoad_Text_MierniePostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Badumka::
    trainerbattle_single TRAINER_P_BADUMKA, EverGrandeRoad_Text_BadumkaIntro, EverGrandeRoad_Text_BadumkaDefeated
    msgbox EverGrandeRoad_Text_BadumkaPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Anatina::
    trainerbattle_single TRAINER_P_ANATINA, EverGrandeRoad_Text_AnatinaIntro, EverGrandeRoad_Text_AnatinaDefeated
    msgbox EverGrandeRoad_Text_AnatinaPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Taipus::
    trainerbattle_single TRAINER_P_TAIPUS, EverGrandeRoad_Text_TaipusIntro, EverGrandeRoad_Text_TaipusDefeated
    msgbox EverGrandeRoad_Text_TaipusPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Marcelus::
    trainerbattle_single TRAINER_P_MARCELUS, EverGrandeRoad_Text_MarcelusIntro, EverGrandeRoad_Text_MarcelusDefeated
    msgbox EverGrandeRoad_Text_MarcelusPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Devia::
    trainerbattle_single TRAINER_P_DEVIA, EverGrandeRoad_Text_DeviaIntro, EverGrandeRoad_Text_DeviaDefeated
    msgbox EverGrandeRoad_Text_DeviaPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Unseld::
    trainerbattle_single TRAINER_P_UNSELD, EverGrandeRoad_Text_UnseldIntro, EverGrandeRoad_Text_UnseldDefeated
    msgbox EverGrandeRoad_Text_UnseldPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Immy::
    trainerbattle_single TRAINER_P_IMMY, EverGrandeRoad_Text_ImmyIntro, EverGrandeRoad_Text_ImmyDefeated
    msgbox EverGrandeRoad_Text_ImmyPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Parponix::
    trainerbattle_single TRAINER_P_PARPONIX, EverGrandeRoad_Text_ParponixIntro, EverGrandeRoad_Text_ParponixDefeated
    msgbox EverGrandeRoad_Text_ParponixPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Lanaya::
    trainerbattle_single TRAINER_P_LANAYA, EverGrandeRoad_Text_LanayaIntro, EverGrandeRoad_Text_LanayaDefeated
    msgbox EverGrandeRoad_Text_LanayaPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_Ophelia::
    trainerbattle_single TRAINER_P_OPHELIA, EverGrandeRoad_Text_OpheliaIntro, EverGrandeRoad_Text_OpheliaDefeated
    msgbox EverGrandeRoad_Text_OpheliaPostBattle, MSGBOX_AUTOCLOSE
    end

EverGrandeRoad_EventScript_TrainingMonk::
	lock
	goto_if_defeated TRAINER_P_SEIMAN, EverGrandeRoad_EventScript_GaveShinyCharm
	msgbox EverGrandeRoad_Text_UpForAToughBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EverGrandeRoad_EventScript_Seiman
	msgbox EverGrandeRoad_Text_IMayBeTooTough, MSGBOX_AUTOCLOSE
	release
	end

EverGrandeRoad_EventScript_Seiman::
    trainerbattle_single TRAINER_P_SEIMAN, EverGrandeRoad_Text_SeimanIntro, EverGrandeRoad_Text_SeimanDefeated, EverGrandeRoad_EventScript_SeimanBeaten
    release
    end

EverGrandeRoad_EventScript_SeimanBeaten::
	msgbox EverGrandeRoad_Text_AVeryThrillingMatch, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

EverGrandeRoad_EventScript_GaveShinyCharm::
	msgbox EverGrandeRoad_Text_MustContinueTraining, MSGBOX_AUTOCLOSE
	release
	end

EverGrandeRoad_EventScript_EGRSign::
    msgbox EverGrandeRoad_Text_EGRSign, MSGBOX_SIGN
    end

EverGrandeRoad_Text_EGRSign:
	.string "EVER GRANDE ROAD\n"
	.string "Hoenn's Final Frontier$"

EverGrandeRoad_Text_UpForAToughBattle:
	.string "Under this waterfall I sit,\n"
	.string "young master. For eons, and eons.\l"
	.string "Awaiting my perfect opponent.\p"
	.string "Many have challenged me.\n"
	.string "ALL have fallen. I have had\l"
	.string "victories numbering in\l"
	.string "the thousands...\p"
	.string "Could you be my one true\n"
	.string "match in skill...?$"

EverGrandeRoad_Text_IMayBeTooTough:
	.string "So... you were not\n"
	.string "the one, after all...$"

EverGrandeRoad_Text_AVeryThrillingMatch:
	.string "I have naught left to offer\n"
	.string "to a trainer of your excellence.\p"
	.string "Except... for this special charm.$"

EverGrandeRoad_Text_MustContinueTraining:
	.string "I must continue my training...\n"
	.string "only then, can enlightenment\l"
	.string "be reached...$"

EverGrandeRoad_Text_SeimanIntro:
	.string "Do not leave anything behind,\n"
	.string "young master. This is a true\l"
	.string "fight to the finish...!$"

EverGrandeRoad_Text_SeimanDefeated:
	.string "It is done.\p"
	.string "You have beaten what was\n"
	.string "thought unbeatable.\l"
	.string "Conquered the unconquerable.$"

EverGrandeRoad_Text_SeimanPostBattle:
	.string "You may now leave.$"

EverGrandeRoad_Text_RaoTwunneIntro:
	.string "Do you truly remember your\n"
	.string "humble beginnings? If not, the\l"
	.string "very first leg of your journey\l"
	.string "may come back to haunt you...$"

EverGrandeRoad_Text_RaoTwunneDefeated:
	.string "You have exceeded the\n"
	.string "accomplishments of your past self!$"

EverGrandeRoad_Text_RaoTwunnePostBattle:
	.string "Stay humble, {PLAYER}. NEVER\n"
	.string "forget the places from which\l"
	.string "you have come.$"

EverGrandeRoad_Text_JamiroquaiIntro:
	.string "If you are not careful, my\n"
	.string "team will wear you down with\l"
	.string "seven thousand strikes!$"

EverGrandeRoad_Text_JamiroquaiDefeated:
	.string "Even with all of that additional\n"
	.string "damage, you stayed stalwart.$"

EverGrandeRoad_Text_JamiroquaiPostBattle:
	.string "End bouts with one, decisive blow?\n"
	.string "Or drag them out to slowly chip\l"
	.string "away at your opponent? The choice,\l"
	.string "ultimately, is yours.$"

EverGrandeRoad_Text_KumqotIntro:
	.string "I used to be the protagonistic\n"
	.string "type like you... until my\l"
	.string "rocket crash-landed. Since then,\l"
	.string "I have suffered immensely, day\l"
	.string "by day. Despite this... I have one\l"
	.string "last go in me.$"

EverGrandeRoad_Text_KumqotDefeated:
	.string "I can't help but choke back\n"
	.string "my tears, trainer...$"

EverGrandeRoad_Text_KumqotPostBattle:
	.string "May your life never take a\n"
	.string "turn for the worst as mine did.$"

EverGrandeRoad_Text_DorianIntro:
	.string "I'm in Ever Grande Road.\n"
	.string "And I. Will. ...Strut my stuff.$"

EverGrandeRoad_Text_DorianDefeated:
	.string "You quantum-leaped beyond what\n"
	.string "I could manage.$"

EverGrandeRoad_Text_DorianPostBattle:
	.string "I need to find my car. It may be\n"
	.string "time to bust out of here and\l"
	.string "go on a nice, long road trip.$"

EverGrandeRoad_Text_LytxiIntro:
	.string "My reputation's on the line, here!$"

EverGrandeRoad_Text_LytxiDefeated:
	.string "You're cool as cool can be! You may\n"
	.string "just well usurp my rep!$"

EverGrandeRoad_Text_LytxiPostBattle:
	.string "I need to get my butt back to\n"
	.string "the city, where I really belong...$"

EverGrandeRoad_Text_SherimoyaIntro:
	.string "Strange... I had expected someone\n"
	.string "like you to show up. Mayhaps it was\l"
	.string "always slated to be.$"

EverGrandeRoad_Text_SherimoyaDefeated:
	.string "Whether it be happiness, freedom,\n"
	.string "or perhaps wealth that you seek,\l"
	.string "never give up your agency.$"

EverGrandeRoad_Text_SherimoyaPostBattle:
	.string "You must make things right.$"

EverGrandeRoad_Text_MeluluIntro:
	.string "OH. MY. GOSH!\n"
	.string "HELLOOOOO!$"

EverGrandeRoad_Text_MeluluDefeated:
	.string "That is like, SUCH\n"
	.string "a bummer.$"

EverGrandeRoad_Text_MeluluPostBattle:
	.string "Idol ÄMeluluÄ might have lost,\n"
	.string "but her love power never fails!$"

EverGrandeRoad_Text_PyoRinIntro:
	.string "ÄHi-hi!Ä$"

EverGrandeRoad_Text_PyoRinDefeated:
	.string "ÄOhÄ$"

EverGrandeRoad_Text_PyoRinPostBattle:
	.string "I do this whole acolyte thing\n"
	.string "as a side gig. My main passion\l"
	.string "is being an idol, and doing\l"
	.string "photoshoots!\p"
	.string "Don't get starstruck when you\n"
	.string "eventually meet me without\l"
	.string "my topaz robesÄ!$"

EverGrandeRoad_Text_MinIntro:
	.string "If you cannot put in what I consider\n"
	.string "the bare minimum, then what gives\l"
	.string "you the right to be here?$"

EverGrandeRoad_Text_MinDefeated:
	.string "Mayhaps the sweet spot lies in\n"
	.string "the middle... the golden mean.$"

EverGrandeRoad_Text_MinPostBattle:
	.string "Falling, and falling... that,\n"
	.string "is the nature of Luo-shan.\l"
	.string "Not everything can stay high\l"
	.string "forever. But, pits are never\l"
	.string "bottomless. There is always a\l"
	.string "floor.$"

EverGrandeRoad_Text_MaxIntro:
	.string "You have to give this battle your\n"
	.string "all! The MAXIMUM! 100 percent!$"

EverGrandeRoad_Text_MaxDefeated:
	.string "I went and over-exerted again...$"

EverGrandeRoad_Text_MaxPostBattle:
	.string "Sha-yon is a Legendary Pokemon\n"
	.string "that represents everything related\l"
	.string "to rising. However, there must\l"
	.string "be some sort of ceiling to this...$"

EverGrandeRoad_Text_ArtemisIntro:
	.string "I have you trapped within\n"
	.string "my domain! There is no escape!$"

EverGrandeRoad_Text_ArtemisDefeated:
	.string "You somehow puzzled a way out...?$"

EverGrandeRoad_Text_ArtemisPostBattle:
	.string "My next trap will have to be much\n"
	.string "more inscrutable...$"

EverGrandeRoad_Text_GarenaIntro:
	.string "Do you believe yourself to be flying\n"
	.string "high right now? Soaring?\p"
	.string "Well, allow me to bring you\n"
	.string "back down to Earth!$"

EverGrandeRoad_Text_GarenaDefeated:
	.string "The weight of your accolades\n"
	.string "was naught a burden...!$"

EverGrandeRoad_Text_GarenaPostBattle:
	.string "I hope you can comprehend the\n"
	.string "gravity of where you now stand.$"

EverGrandeRoad_Text_GoroIntro:
	.string "The ground doth quake with\n"
	.string "every one of my footsteps!\l"
	.string "Will you buckle!?$"

EverGrandeRoad_Text_GoroDefeated:
	.string "Not a single tremor!?$"

EverGrandeRoad_Text_GoroPostBattle:
	.string "You are the one building that\n"
	.string "stands tall among its knocked-\l"
	.string "over compatriots. Keep going!$"

EverGrandeRoad_Text_MiernieIntro:
	.string "Don't you panic, now.\n"
	.string "Lest you succumb to madness!$"

EverGrandeRoad_Text_MiernieDefeated:
	.string "You remain unperturbed?$"

EverGrandeRoad_Text_MierniePostBattle:
	.string "Strong in mind, is\n"
	.string "strong in self.$"

EverGrandeRoad_Text_BadumkaIntro:
	.string "The pressure is on, trainer.\n"
	.string "Try your best to not crack.$"

EverGrandeRoad_Text_BadumkaDefeated:
	.string "Nothing I could do could rend\n"
	.string "your focus asunder...$"

EverGrandeRoad_Text_BadumkaPostBattle:
	.string "Take deep breaths, {PLAYER}.\n"
	.string "In, and out. Slowly.\l"
	.string "Don't let your nerves get\l"
	.string "the best of you.$"

EverGrandeRoad_Text_AnatinaIntro:
	.string "THE PLAGUE ROTS ALL!!\n"
	.string "BECOME INFECTED BY PESTILENCE!!$"

EverGrandeRoad_Text_AnatinaDefeated:
	.string "IT WASN'T NEARLY POTENT ENOUGH!!$"

EverGrandeRoad_Text_AnatinaPostBattle:
	.string "YOU AVOIDED CERTAIN DEATH...!!\n"
	.string "BUT I WILL HAVE MY REVENGE!!$"

EverGrandeRoad_Text_TaipusIntro:
	.string "Are you getting worn down yet...?\n"
	.string "Maybe I could put you out\l"
	.string "of your misery...$"

EverGrandeRoad_Text_TaipusDefeated:
	.string "Still on your own two feet...?\n"
	.string "Even after all that...?$"

EverGrandeRoad_Text_TaipusPostBattle:
	.string "The difference between a healthy\n"
	.string "team and a negelcted team, going\l"
	.string "into a match... is the difference\l"
	.string "between a win and a loss.$"

EverGrandeRoad_Text_MarcelusIntro:
	.string "What good is your strategy and\n"
	.string "preparation if I stonewall any\l"
	.string "attempt at executing it?$"

EverGrandeRoad_Text_MarcelusDefeated:
	.string "You didn't even FLINCH!?$"

EverGrandeRoad_Text_MarcelusPostBattle:
	.string "Keep your eyes on the prize.\n"
	.string "If you look away, for even a second,\l"
	.string "it could disappear before you.$"

EverGrandeRoad_Text_DeviaIntro:
	.string "I'll knock you around fifteen\n"
	.string "different ways! You'll be\l"
	.string "seein' nothin' but stars!$"

EverGrandeRoad_Text_DeviaDefeated:
	.string "Total knockout!$"

EverGrandeRoad_Text_DeviaPostBattle:
	.string "It's always a good idea to shut down\n"
	.string "someone's setup before it gets\l"
	.string "too out of hand.$"

EverGrandeRoad_Text_UnseldIntro:
	.string "I'll go berserk and attack anything\n"
	.string "that moves!!!$"

EverGrandeRoad_Text_UnseldDefeated:
	.string "Grrraaaarrr!! Everything is\n"
	.string "destroyed!! Even ME!!$"

EverGrandeRoad_Text_UnseldPostBattle:
	.string "Leave NOTHING behind when\n"
	.string "you lay waste to the other acolytes!$"

EverGrandeRoad_Text_ImmyIntro:
	.string "You will be beset with a barrage\n"
	.string "of nuclear proportions!$"

EverGrandeRoad_Text_ImmyDefeated:
	.string "My team... had a meltdown!$"

EverGrandeRoad_Text_ImmyPostBattle:
	.string "Sometimes, just blowing the\n"
	.string "battlefield to smithereens with\l"
	.string "your best attacks is the\l"
	.string "correct call!$"

EverGrandeRoad_Text_ParponixIntro:
	.string "Are you fully prepared to take\n"
	.string "on every Hoenn-native Pokemon?\l"
	.string "Even the rare ones like these?$"

EverGrandeRoad_Text_ParponixDefeated:
	.string "A well-honed base of knowledge\n"
	.string "can be the bedrock of any unknown\l"
	.string "foe's defeat...$"

EverGrandeRoad_Text_ParponixPostBattle:
	.string "Have you nearly completed that\n"
	.string "Pokedex the Professor gave you?\l"
	.string "You can learn so much by\l"
	.string "capturing every one of them...$"

EverGrandeRoad_Text_LanayaIntro:
	.string "Never stop growing! Even at\n"
	.string "the end of your adventure!$"

EverGrandeRoad_Text_LanayaDefeated:
	.string "If you stilt your growth in the\n"
	.string "final hour, you may never\l"
	.string "reach your fullest potential!$"

EverGrandeRoad_Text_LanayaPostBattle:
	.string "The conclusion draws incredibly\n"
	.string "near. Hold your head high,\l"
	.string "all the way to the finish line!$"

EverGrandeRoad_Text_OpheliaIntro:
	.string "You may have blossomed into quite\n"
	.string "the formidable trainer, but\l"
	.string "could you survive the harsh winter?$"

EverGrandeRoad_Text_OpheliaDefeated:
	.string "Could you survive... anything?$"

EverGrandeRoad_Text_OpheliaPostBattle:
	.string "...Take care. I mean that.$"

EverGrandeRoad_Text_NamePandou:
	.string "Pandou$"

EverGrandeRoad_Text_BreadwinnerIntro:
	.string "Y-Y-Y-YOU!\p"
	.string "What are you doing here at\n"
	.string "my place of work?\l"
	.string "I thought we'd agreed that w-we\l"
	.string "would stay out of each other's way...\p"
	.string "N-No! It's time... time for me\n"
	.string "to really toughen up here!\l"
	.string "This Pokemon Center...\l"
	.string "I'm the manager! W-Well, that isn't\l"
	.string "entirely correct...\p"
	.string "I'm the manager of EVERY Pokemon\n"
	.string "Center in Hoenn...! This is just\l"
	.string "the one I personally run myself.\p"
	.string "Every Nurse you've ran into in\n"
	.string "those Centers? They're my daughters!\l"
	.string "I-I... have 31... daughters...\l"
	.string "in fact...\p"
	.string "M-My wife and I just started\n"
	.string "with 1 kid... then, as luck\l"
	.string "would have it... 3 sets of\l"
	.string "dectuplets in a row... oy, vey...\p"
	.string "Th-That's why I need to be\n"
	.string "the Breadwinner for my beloved\l"
	.string "family! My daughters all deserve\l"
	.string "bright futures!\p"
	.string "So, if... if you want a b-battle,\n"
	.string "I'll give you one you won't\l"
	.string "ever forget...!$"

EverGrandeRoad_Text_BreadwinnerDefeat:
	.string "Sigh...\n"
	.string "Even on my home t-turf...$"

EverGrandeRoad_Text_BreadwinnerRunAway:
	.string "Well. At least I'm not\n"
	.string "late for work anymore...\p"
	.string "If you want a heal for your\n"
	.string "Pokemon, my eldest daughter\l"
	.string "will gladly assist you inside.\p"
	.string "Just p-please, no fighting indoors!$"
