.set LOCALID_OZONE_BLOCKER1, 36
.set LOCALID_OZONE_BLOCKER2, 37

CrimneyClimb_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CrimneyClimb_OnLoad
	.byte 0

CrimneyClimb_OnLoad:
	call_if_ge VAR_NEW_COO_STATE, 6, CrimneyClimb_EventScript_RemoveOzoneBlockers
	end

CrimneyClimb_EventScript_RemoveOzoneBlockers::
	removeobject LOCALID_OZONE_BLOCKER1
	removeobject LOCALID_OZONE_BLOCKER2
	setflag FLAG_TEMP_1B
	return

CrimneyClimb_EventScript_Lara::
    trainerbattle_single TRAINER_P_LARA, CrimneyClimb_Text_LaraIntro, CrimneyClimb_Text_LaraDefeated
    msgbox CrimneyClimb_Text_LaraPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Erica::
    trainerbattle_single TRAINER_P_ERICA, CrimneyClimb_Text_EricaIntro, CrimneyClimb_Text_EricaDefeated
    msgbox CrimneyClimb_Text_EricaPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Jin::
    trainerbattle_single TRAINER_P_JIN, CrimneyClimb_Text_JinIntro, CrimneyClimb_Text_JinDefeated
    msgbox CrimneyClimb_Text_JinPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_AkiAndMitsu::
    trainerbattle_double TRAINER_P_AKI_AND_MITSU, CrimneyClimb_Text_AkiAndMitsuIntro, CrimneyClimb_Text_AkiAndMitsuDefeated, CrimneyClimb_Text_AkiAndMitsuNeedTwoMons
    msgbox CrimneyClimb_Text_AkiAndMitsuPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Daisy::
    trainerbattle_single TRAINER_P_DAISY, CrimneyClimb_Text_DaisyIntro, CrimneyClimb_Text_DaisyDefeated
    msgbox CrimneyClimb_Text_DaisyPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Gwunivere::
    trainerbattle_single TRAINER_P_GWUNIVERE, CrimneyClimb_Text_GwunivereIntro, CrimneyClimb_Text_GwunivereDefeated
    msgbox CrimneyClimb_Text_GwuniverePostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Yisan::
    trainerbattle_single TRAINER_P_YISAN, CrimneyClimb_Text_YisanIntro, CrimneyClimb_Text_YisanDefeated
    msgbox CrimneyClimb_Text_YisanPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Hamm::
    trainerbattle_single TRAINER_P_HAMM, CrimneyClimb_Text_HammIntro, CrimneyClimb_Text_HammDefeated
    msgbox CrimneyClimb_Text_HammPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Frank::
    trainerbattle_single TRAINER_P_FRANK, CrimneyClimb_Text_FrankIntro, CrimneyClimb_Text_FrankDefeated
    msgbox CrimneyClimb_Text_FrankPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Weiner::
    trainerbattle_single TRAINER_P_WEINER, CrimneyClimb_Text_WeinerIntro, CrimneyClimb_Text_WeinerDefeated
    msgbox CrimneyClimb_Text_WeinerPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Evelynn::
    trainerbattle_single TRAINER_P_EVELYNN, CrimneyClimb_Text_EvelynnIntro, CrimneyClimb_Text_EvelynnDefeated
    msgbox CrimneyClimb_Text_EvelynnPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Dyna::
    trainerbattle_single TRAINER_P_DYNA, CrimneyClimb_Text_DynaIntro, CrimneyClimb_Text_DynaDefeated
    msgbox CrimneyClimb_Text_DynaPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_Audrey::
    trainerbattle_single TRAINER_P_AUDREY, CrimneyClimb_Text_AudreyIntro, CrimneyClimb_Text_AudreyDefeated
    msgbox CrimneyClimb_Text_AudreyPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_AudreyII::
    trainerbattle_single TRAINER_P_AUDREY_II, CrimneyClimb_Text_AudreyIIIntro, CrimneyClimb_Text_AudreyIIDefeated
    msgbox CrimneyClimb_Text_AudreyIIPostBattle, MSGBOX_AUTOCLOSE
    end

CrimneyClimb_EventScript_OzoneBlocker1::
    msgbox CrimneyClimb_Text_OzoneBlocker1, MSGBOX_NPC
    end

CrimneyClimb_EventScript_OzoneBlocker2::
    msgbox CrimneyClimb_Text_OzoneBlocker2, MSGBOX_NPC
    end

CrimneyClimb_EventScript_CableCarSign::
	msgbox CrimneyClimb_Text_CableCarSign, MSGBOX_SIGN
	end

CrimneyClimb_Text_CableCarSign:
	.string "MT. CHIMNEY CABLE CAR\n"
	.string "CRIMNEY CLIMB STATION$"

CrimneyClimb_Text_OzoneBlocker1:
	.string "Whoa, hold it there, sport!\n"
	.string "Can't be lettin' you into\l"
	.string "this part of the Catacombs.\p"
	.string "This tunnel leads straight\n"
	.string "to the summit of Mt. Chimney.\l"
	.string "Y'know, an active volcano?\l"
	.string "Ain't no way I'm letting anyone\l"
	.string "unauthorized up there.\l"
	.string "You could get seriously hurt.$"

CrimneyClimb_Text_OzoneBlocker2:
	.string "Look, I know getting close\n"
	.string "to lava SOUNDS cool on paper.\l"
	.string "But if you aren't careful,\l"
	.string "you'll go up in flames like\l"
	.string "a human firework!\p"
	.string "So no, you can't pass through\n"
	.string "to the Caldera.$"

CrimneyClimb_Text_LaraIntro:
	.string "I used to be a legendary tomb\n"
	.string "raider when I was young!\l"
	.string "But I've still got it!$"

CrimneyClimb_Text_LaraDefeated:
	.string "You're a crofty, err, I mean,\n"
	.string "crafty sort of trainer!$"

CrimneyClimb_Text_LaraPostBattle:
	.string "If you ever find the Sweltorn\n"
	.string "Palace, just know that I took\l"
	.string "the best treasures out of there\l"
	.string "ages ago!$"

CrimneyClimb_Text_EricaIntro:
	.string "Watch me juggle!$"

CrimneyClimb_Text_EricaDefeated:
	.string "Ashes, ashes...\n"
	.string "they all fall down!$"

CrimneyClimb_Text_EricaPostBattle:
	.string "You have to use both\n"
	.string "hands to juggle, silly!$"

CrimneyClimb_Text_JinIntro:
	.string "The heat and smoke fuels\n"
	.string "me like a raging fire!!$"

CrimneyClimb_Text_JinDefeated:
	.string "My fury cannot be tempered!!$"

CrimneyClimb_Text_JinPostBattle:
	.string "Don't mess with us Martial Artists,\n"
	.string "if you know what's good for you.$"

CrimneyClimb_Text_AkiAndMitsuIntro:
	.string "AKI: You have to make your Pokemon\n"
	.string "     really EARN their evolution!\l"
	.string "MITSU: This will be the battle\l"
	.string "       that proves their worth!$"

CrimneyClimb_Text_AkiAndMitsuDefeated:
	.string "AKI: They really didn't hit\n"
	.string "     their mark...\l"
	.string "MITSU: No honor in that.$"

CrimneyClimb_Text_AkiAndMitsuPostBattle:
	.string "AKI: It's important to make sure\n"
	.string "    your Pokemon stay humble.\l"
	.string "MITSU: Don't let them evolve\l"
	.string "   until they've proved themselves!$"

CrimneyClimb_Text_AkiAndMitsuNeedTwoMons:
	.string "MISTU: Aki, I don't think there'd\n"
	.string "       be any honor in challenging\l"
	.string "       someone with one Pokemon...\l"
	.string "AKI: That, you are right!$"

CrimneyClimb_Text_DaisyIntro:
	.string "HI, I'M DAISY!!!$"

CrimneyClimb_Text_DaisyDefeated:
	.string "Sorry, I uh, came on too strong...$"

CrimneyClimb_Text_DaisyPostBattle:
	.string "How did I get all three\n"
	.string "Spryte evolutions?\p"
	.string "Oh, well Spryte evolves based\n"
	.string "on the last move it was hit by.\l"
	.string "Slashing, piercing, and blunt\l"
	.string "moves each produce a different\l"
	.string "evolution.$"

CrimneyClimb_Text_GwunivereIntro:
	.string "Take it easy on me...!\n"
	.string "I'm just a baby!\l"
	.string "A 31 year old baby!$"

CrimneyClimb_Text_GwunivereDefeated:
	.string "MY BLABBU...!$"

CrimneyClimb_Text_GwuniverePostBattle:
	.string "Blabbu and I are so alike.\n"
	.string "We're both babycore.\p"
	.string "(You express immense disgust\n"
	.string "at that word.)$"

CrimneyClimb_Text_YisanIntro:
	.string "Let my wings strike\n"
	.string "down my foes!$"

CrimneyClimb_Text_YisanDefeated:
	.string "My wings are beaten\n"
	.string "and broken...$"

CrimneyClimb_Text_YisanPostBattle:
	.string "Fly...\n"
	.string "Fly, my broken wings...!$"

CrimneyClimb_Text_HammIntro:
	.string "Ehhh!? No, I ain't stealin' nuttin'!\n"
	.string "No sir!$"

CrimneyClimb_Text_HammDefeated:
	.string "Oh, this eh, bag I got?\p"
	.string "I found it... on the uh,\n"
	.string "side'a the road...?$"

CrimneyClimb_Text_HammPostBattle:
	.string "Just don't rat on me\n"
	.string "to dem coppers.$"

CrimneyClimb_Text_FrankIntro:
	.string "Allow me to be frank with you...\n"
	.string "I'm out of beef franks.\p"
	.string "But I'm hankerin' for\n"
	.string "a good battle!$"

CrimneyClimb_Text_FrankDefeated:
	.string "Frankly, my dear...\n"
	.string "I didn't give it my all.$"

CrimneyClimb_Text_FrankPostBattle:
	.string "My partner here kind of has\n"
	.string "a stick up his... uh, popsicle.$"

CrimneyClimb_Text_WeinerIntro:
	.string "We're supposed to be\n"
	.string "vending snacks, here,\l"
	.string "not getting into fights!$"

CrimneyClimb_Text_WeinerDefeated:
	.string "Alright, the battle's over,\n"
	.string "whoopdie-doo.\p"
	.string "Now, will ya browse our selection?$"

CrimneyClimb_Text_WeinerPostBattle:
	.string "Business is business,\n"
	.string "whether it's real estate or\l"
	.string "ice cold treats.$"

CrimneyClimb_Text_EvelynnIntro:
	.string "The sunlight's real bad around here.\n"
	.string "Got on sunblock?$"

CrimneyClimb_Text_EvelynnDefeated:
	.string "Mess with the sun, get burned...$"

CrimneyClimb_Text_EvelynnPostBattle:
	.string "Keep your skin protected!\n"
	.string "You'll thank me later.$"

CrimneyClimb_Text_DynaIntro:
	.string "I lost a bomb...\n"
	.string "could you have nabbed it?$"

CrimneyClimb_Text_DynaDefeated:
	.string "Don't play with matches.$"

CrimneyClimb_Text_DynaPostBattle:
	.string "Wait, is it over there?$"

CrimneyClimb_Text_AudreyIntro:
	.string "That girl over there has the\n"
	.string "same name as me.\l"
	.string "But I'm the better Audrey!$"

CrimneyClimb_Text_AudreyDefeated:
	.string "Can't you see?$"

CrimneyClimb_Text_AudreyPostBattle:
	.string "Don't you have a stake\n"
	.string "in this conflict?$"

CrimneyClimb_Text_AudreyIIIntro:
	.string "That girl over there has the\n"
	.string "same name as me.\l"
	.string "But I'm the better Aüdrey!$"

CrimneyClimb_Text_AudreyIIDefeated:
	.string "See! See!$"

CrimneyClimb_Text_AudreyIIPostBattle:
	.string "I TOLD you!\n"
	.string "I'm the better of the two!$"
