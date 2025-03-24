Route113_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route113_OnTransition
	.byte 0

Route113_OnResume:
	setstepcallback STEP_CB_ASH
	end

Route113_OnTransition:
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	call Route113_EventScript_CheckSetAshWeather
	end

Route113_EventScript_CheckSetAshWeather::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_lt VAR_TEMP_0, 19, Route113_EventScript_DontSetAshWeather
	goto_if_gt VAR_TEMP_0, 84, Route113_EventScript_DontSetAshWeather
	setweather WEATHER_VOLCANIC_ASH
	return

Route113_EventScript_DontSetAshWeather::
	return

Route113_EventScript_Ashe::
    trainerbattle_single TRAINER_P_ASHE, Route113_Text_AsheIntro, Route113_Text_AsheDefeated
    msgbox Route113_Text_AshePostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Sara::
    trainerbattle_single TRAINER_P_SARA, Route113_Text_SaraIntro, Route113_Text_SaraDefeated
    msgbox Route113_Text_SaraPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Togedemaru::
    trainerbattle_single TRAINER_P_TOGEDEMARU, Route113_Text_TogedemaruIntro, Route113_Text_TogedemaruDefeated
    msgbox Route113_Text_TogedemaruPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Jucika::
    trainerbattle_single TRAINER_P_JUCIKA, Route113_Text_JucikaIntro, Route113_Text_JucikaDefeated
    msgbox Route113_Text_JucikaPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Naruto::
    trainerbattle_single TRAINER_P_NARUTO, Route113_Text_NarutoIntro, Route113_Text_NarutoDefeated
    msgbox Route113_Text_NarutoPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Kushina::
    trainerbattle_single TRAINER_P_KUSHINA, Route113_Text_KushinaIntro, Route113_Text_KushinaDefeated
    msgbox Route113_Text_KushinaPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Callum::
    trainerbattle_single TRAINER_P_CALLUM, Route113_Text_CallumIntro, Route113_Text_CallumDefeated
    msgbox Route113_Text_CallumPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Kusuo::
    trainerbattle_single TRAINER_P_KUSUO, Route113_Text_KusuoIntro, Route113_Text_KusuoDefeated
    msgbox Route113_Text_KusuoPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Mirai::
    trainerbattle_single TRAINER_P_MIRAI, Route113_Text_MiraiIntro, Route113_Text_MiraiDefeated
    msgbox Route113_Text_MiraiPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Kurenai::
    trainerbattle_single TRAINER_P_KURENAI, Route113_Text_KurenaiIntro, Route113_Text_KurenaiDefeated
    msgbox Route113_Text_KurenaiPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_Sakurai::
    trainerbattle_single TRAINER_P_SAKURAI, Route113_Text_SakuraiIntro, Route113_Text_SakuraiDefeated
    msgbox Route113_Text_SakuraiPostBattle, MSGBOX_AUTOCLOSE
    end

Route113_EventScript_AshlandsSign::
	msgbox Route113_Text_AshlandsSign, MSGBOX_SIGN
	end

Route113_EventScript_CraftsmansSign::
	msgbox Route113_Text_CraftsmansSign, MSGBOX_SIGN
	end

Route113_Text_AshlandsSign:
	.string "Welcome to the Ashlands!\n"
	.string "Watch your lungs!$"

Route113_Text_CraftsmansSign:
	.string "Home of the Ashlands Craftsman$"

Route113_Text_AsheIntro:
	.string "What, you didn't bring an umbrella?$"

Route113_Text_AsheDefeated:
	.string "Have fun getting ashed on...$"

Route113_Text_AshePostBattle:
	.string "I'm no Seattlite.$"

Route113_Text_SaraIntro:
	.string "I have a great burden to bear.$"

Route113_Text_SaraDefeated:
	.string "Soooo... Heavy....$"

Route113_Text_SaraPostBattle:
	.string "I shouldn't have packed\n"
	.string "my folding bicycle.$"

Route113_Text_TogedemaruIntro:
	.string "Prepare to be Ninja'd!$"

Route113_Text_TogedemaruDefeated:
	.string "Hey! I'll be the one doin' the\n"
	.string "Ninja-ing around here!$"

Route113_Text_TogedemaruPostBattle:
	.string "...Do ya mind?...\n"
	.string "I'm tryin' to brood over here!$"

Route113_Text_JucikaIntro:
	.string "Oh, how great, another interruption.$"

Route113_Text_JucikaDefeated:
	.string "...Great.$"

Route113_Text_JucikaPostBattle:
	.string "Will you leave now?\n"
	.string "I have work to do.$"

Route113_Text_NarutoIntro:
	.string "Nin nin nin!!$"

Route113_Text_NarutoDefeated:
	.string "Doryaaaah!!$"

Route113_Text_NarutoPostBattle:
	.string "Im an assassin! Nin, nin...$"

Route113_Text_KushinaIntro:
	.string "Don't mind my son...\n"
	.string "he really thinks he's some\l"
	.string "sort of chosen one.\p"
	.string "Could you humor us with a battle?\n$"

Route113_Text_KushinaDefeated:
	.string "He thinks he won.\n"
	.string "Play along, please...?$"

Route113_Text_KushinaPostBattle:
	.string "He loves to ramble about\n"
	.string "how he'll be the Hokage some day.\p"
	.string "At least he's aiming high!$"

Route113_Text_CallumIntro:
	.string "Hey. My name's Callum.\n"
	.string "Some may call me a Hoodlum.\l"
	.string "You don't think that, do you?$"

Route113_Text_CallumDefeated:
	.string "If only Pantney was a lizard...$"

Route113_Text_CallumPostBattle:
	.string "There's these people that keep\n"
	.string "trying to get me to read weird\l"
	.string "paragraphs about Mustybane.\l"
	.string "I think they get a kick out\l"
	.string "of the nonsense.$"

Route113_Text_KusuoIntro:
	.string "These powers are a curse.$"

Route113_Text_KusuoDefeated:
	.string "You beat me, even with my curse?$"

Route113_Text_KusuoPostBattle:
	.string "You truly are remarkable.$"

Route113_Text_MiraiIntro:
	.string "Hai-YAH!$"

Route113_Text_MiraiDefeated:
	.string "I'm out of chakra!$"

Route113_Text_MiraiPostBattle:
	.string "Dangit... my plan to summon\n"
	.string "the King Orrowhelm, jump inside\l"
	.string "his mouth, and teleport away,\l"
	.string "despite having no chakra left...\l"
	.string "it didn't work!\p"
	.string "It would be pretty silly if it did.$"

Route113_Text_KurenaiIntro:
	.string "My son is my future!\n"
	.string "For him, I will fight every day!$"

Route113_Text_KurenaiDefeated:
	.string "Your future... it appears\n"
	.string "to be very promising!$"

Route113_Text_KurenaiPostBattle:
	.string "My son's father had passed away\n"
	.string "before he was born. If only\l"
	.string "he could see his little boy now...$"

Route113_Text_SakuraiIntro:
	.string "This ultimate brawl will be no\n"
	.string "doubt super! A melee with\l"
	.string "64 thousand potential outcomes...$"

Route113_Text_SakuraiDefeated:
	.string "I need to take a long vacation...$"

Route113_Text_SakuraiPostBattle:
	.string "Do not ask me for anything\n"
	.string "ever again.$"
