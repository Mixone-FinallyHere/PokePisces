SailorsPauseShips_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SailorsPauseShips_OnLoad
	.byte 0

SailorsPauseShips_OnLoad:
	call_if_set FLAG_FOUND_SHELLY, SailorsPauseShips_EventScript_RemoveShelly
	end

SailorsPauseShips_EventScript_RemoveShelly::
	setmetatile 39, 1, METATILE_InsideShip_ShellyGoneTop, TRUE
	setmetatile 39, 2, METATILE_InsideShip_ShellyGoneBottom, TRUE
	special DrawWholeMapView
	return

SailorsPauseShips_EventScript_Shelly::
	lockall
	goto_if_set FLAG_FOUND_SHELLY, SailorsPauseShips_EventScript_ShellyGone
	msgbox SailorsPauseShips_Text_ShellyGreeting, MSGBOX_DEFAULT
	setflag FLAG_FOUND_SHELLY
	delay 32
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setmetatile 39, 1, METATILE_InsideShip_ShellyGoneTop, TRUE
	setmetatile 39, 2, METATILE_InsideShip_ShellyGoneBottom, TRUE
	special DrawWholeMapView
	delay 16
	fadescreen FADE_FROM_BLACK
	releaseall
	end

SailorsPauseShips_EventScript_ShellyGone::
	msgbox SailorsPauseShips_Text_ShellyGone, MSGBOX_AUTOCLOSE
	releaseall
	end

SailorsPauseShips_EventScript_Ami::
    trainerbattle_single TRAINER_P_AMI, SailorsPauseShips_Text_AmiIntro, SailorsPauseShips_Text_AmiDefeated
    msgbox SailorsPauseShips_Text_AmiPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_EventScript_Marcy::
    trainerbattle_single TRAINER_P_MARCY, SailorsPauseShips_Text_MarcyIntro, SailorsPauseShips_Text_MarcyDefeated
    msgbox SailorsPauseShips_Text_MarcyPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_EventScript_Sponge::
    trainerbattle_single TRAINER_P_SPONGE, SailorsPauseShips_Text_SpongeIntro, SailorsPauseShips_Text_SpongeDefeated
    msgbox SailorsPauseShips_Text_SpongePostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_EventScript_Walton::
    trainerbattle_single TRAINER_P_WALTON, SailorsPauseShips_Text_WaltonIntro, SailorsPauseShips_Text_WaltonDefeated
    msgbox SailorsPauseShips_Text_WaltonPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_EventScript_Joshu::
    trainerbattle_single TRAINER_P_JOSHU, SailorsPauseShips_Text_JoshuIntro, SailorsPauseShips_Text_JoshuDefeated
    msgbox SailorsPauseShips_Text_JoshuPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_EventScript_Janelle::
    trainerbattle_single TRAINER_P_JANELLE, SailorsPauseShips_Text_JanelleIntro, SailorsPauseShips_Text_JanelleDefeated
    msgbox SailorsPauseShips_Text_JanellePostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_EventScript_Nunya::
    trainerbattle_single TRAINER_P_NUNYA, SailorsPauseShips_Text_NunyaIntro, SailorsPauseShips_Text_NunyaDefeated
    msgbox SailorsPauseShips_Text_NunyaPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_EventScript_Jack::
    trainerbattle_single TRAINER_P_JACK, SailorsPauseShips_Text_JackIntro, SailorsPauseShips_Text_JackDefeated
    msgbox SailorsPauseShips_Text_JackPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_EventScript_Rose::
    trainerbattle_single TRAINER_P_ROSE, SailorsPauseShips_Text_RoseIntro, SailorsPauseShips_Text_RoseDefeated
    msgbox SailorsPauseShips_Text_RosePostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseShips_Text_AmiIntro:
	.string "There are MANY lost spirits\n"
	.string "that roam this area...$"

SailorsPauseShips_Text_AmiDefeated:
	.string "Have you become lost, too...?$"

SailorsPauseShips_Text_AmiPostBattle:
	.string "Do not become chained to this\n"
	.string "realm as I did...$"

SailorsPauseShips_Text_MarcyIntro:
	.string "Don't look at me like that!\n"
	.string "I don't bite! ...Much.$"

SailorsPauseShips_Text_MarcyDefeated:
	.string "Owwwwwch! No fair!$"

SailorsPauseShips_Text_MarcyPostBattle:
	.string "Ghost type Pokemon feed on\n"
	.string "human energy, don't they?\l"
	.string "Hmm. Maybe that's why I'm all\l"
	.string "worn out...$"

SailorsPauseShips_Text_SpongeIntro:
	.string "I'm not happy.$"

SailorsPauseShips_Text_SpongeDefeated:
	.string "(He sobs so cartoonishly much,\n"
	.string "that his mustache becomes a mop.)$"

SailorsPauseShips_Text_SpongePostBattle:
	.string "It's ok... it's all in my\n"
	.string "family's business...$"

SailorsPauseShips_Text_WaltonIntro:
	.string "It's time to do the Poke-box step!$"

SailorsPauseShips_Text_WaltonDefeated:
	.string "Wait! Wait! Forget what I\n"
	.string "just said!$"

SailorsPauseShips_Text_WaltonPostBattle:
	.string "If my fellow Waltzers find out that\n"
	.string "I never actually learned the waltz,\l"
	.string "I'll lose my certification!$"

SailorsPauseShips_Text_JoshuIntro:
	.string "'Ey. Think you can just come\n"
	.string "into this ship unannounced?$"

SailorsPauseShips_Text_JoshuDefeated:
	.string "I respect someone that has the\n"
	.string "cajones to stand up to someone\l"
	.string "intimidatin'.$"

SailorsPauseShips_Text_JoshuPostBattle:
	.string "I'll letcha go downstairs.\n"
	.string "Just this once.$"

SailorsPauseShips_Text_JanelleIntro:
	.string "I'm WAY too tired to get much\n"
	.string "of anything done today...\l"
	.string "Maybe a battle could perk\l"
	.string "me right up!$"

SailorsPauseShips_Text_JanelleDefeated:
	.string "Oh, well... aw.\n"
	.string "I just feel more sleepy...$"

SailorsPauseShips_Text_JanellePostBattle:
	.string "Maybe I just need to woman\n"
	.string "up and ask for time off...$"

SailorsPauseShips_Text_NunyaIntro:
	.string "What's my name, ya ask?\n"
	.string "Fufufu... well...$"

SailorsPauseShips_Text_NunyaDefeated:
	.string "NUNYA BIZNESS!$"

SailorsPauseShips_Text_NunyaPostBattle:
	.string "Now BEAT IT, chump,\n"
	.string "before things get ugly!$"

SailorsPauseShips_Text_JackIntro:
	.string "Oooooo! THOSE are some fine\n"
	.string "specimens you possess.\l"
	.string "How much? For the set of 6?$"

SailorsPauseShips_Text_JackDefeated:
	.string "What do you mean, they\n"
	.string "aren't for sale?$"

SailorsPauseShips_Text_JackPostBattle:
	.string "Whatever! If your Pokemon are\n"
	.string "anything like you, they'll\l"
	.string "attract Flague in droves!$"

SailorsPauseShips_Text_RoseIntro:
	.string "Your metaphorical ship is\n"
	.string "about to hit a metaphorical iceberg!\l"
	.string "Metaphorically!$"

SailorsPauseShips_Text_RoseDefeated:
	.string "We've been sunk!$"

SailorsPauseShips_Text_RosePostBattle:
	.string "Jack and I took a trip on\n"
	.string "this very ship, the day it crashed...\l"
	.string "thankfully, we were saved.$"

SailorsPauseShips_Text_ShellyGreeting:
	.string "(This woman is asleep in\n"
	.string "a hammock. In a derelict\l"
	.string "ship, of all places.)\p"
	.string "(You loudly clear your throat\n"
	.string "to try and wake her up.)\p"
	.string "....Whuzzat? Oh.\n"
	.string "Whoopsies... I was supposed\l"
	.string "to, uhm... head back to the gym...\p"
	.string "If you were worried about the\n"
	.string "garbage dumpers that we got a...\l"
	.string "uhm, tip about...\l"
	.string "I did a pretty thorough\l"
	.string "investigation and... turned up\l"
	.string "nothing suspicious...\p"
	.string "Looks like it was a, yawn...\n"
	.string "false flag...\p"
	.string "Anywaysies... I'll be headed\n"
	.string "back to Dewford... See ya...$"

SailorsPauseShips_Text_ShellyGone:
	.string "(An empty hammock.)$"
