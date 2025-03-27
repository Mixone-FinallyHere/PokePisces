UnduraTunnels_MapScripts::
	.byte 0

UnduraTunnels_EventScript_Guntilda::
    trainerbattle_single TRAINER_P_GUNTILDA, UnduraTunnels_Text_GuntildaIntro, UnduraTunnels_Text_GuntildaDefeated
    msgbox UnduraTunnels_Text_GuntildaPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnels_EventScript_Laios::
    trainerbattle_single TRAINER_P_LAIOS, UnduraTunnels_Text_LaiosIntro, UnduraTunnels_Text_LaiosDefeated
    msgbox UnduraTunnels_Text_LaiosPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnels_EventScript_Gio::
    trainerbattle_single TRAINER_P_GIO, UnduraTunnels_Text_GioIntro, UnduraTunnels_Text_GioDefeated
    msgbox UnduraTunnels_Text_GioPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnels_EventScript_Eunmi::
    trainerbattle_single TRAINER_P_EUNMI, UnduraTunnels_Text_EunmiIntro, UnduraTunnels_Text_EunmiDefeated
    msgbox UnduraTunnels_Text_EunmiPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnels_EventScript_Thyme::
    trainerbattle_single TRAINER_P_THYME, UnduraTunnels_Text_ThymeIntro, UnduraTunnels_Text_ThymeDefeated
    msgbox UnduraTunnels_Text_ThymePostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnels_EventScript_Basil::
    trainerbattle_single TRAINER_P_BASIL, UnduraTunnels_Text_BasilIntro, UnduraTunnels_Text_BasilDefeated
    msgbox UnduraTunnels_Text_BasilPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnels_EventScript_RustburgSign::
    msgbox UnduraTunnels_Text_RustburgSign, MSGBOX_SIGN
    end

UnduraTunnels_EventScript_RustboroSign::
    msgbox UnduraTunnels_Text_RustboroSign, MSGBOX_SIGN
    end

UnduraTunnels_EventScript_EtheorSign::
    msgbox UnduraTunnels_Text_EtheorSign, MSGBOX_SIGN
    end

UnduraTunnels_Text_RustburgSign:
	.string "UNDURA TUNNELS\n"
	.string "RUSTBURG WHARF EXIT$"

UnduraTunnels_Text_RustboroSign:
	.string "UNDURA TUNNELS\n"
	.string "RUSTBORO CITY EXIT$"

UnduraTunnels_Text_EtheorSign:
	.string "UNDURA TUNNELS\n"
	.string "ETHEOR FALLS EXIT$"

UnduraTunnels_Text_GuntildaIntro:
	.string "Uuuuu-waahhhhh! I'll show them!\n"
	.string "I make proper life choices!$"

UnduraTunnels_Text_GuntildaDefeated:
	.string "I can't even win one fight...$"

UnduraTunnels_Text_GuntildaPostBattle:
	.string "Uuuu-huuuuu... I met two mean\n"
	.string "students from Rustboro, and\l"
	.string "they made fun of meeeeee....!$"

UnduraTunnels_Text_LaiosIntro:
	.string "I have been searching for a\n"
	.string "delicious Pokemon... battle.\l"
	.string "Yes, a battle...$"

UnduraTunnels_Text_LaiosDefeated:
	.string "That sure worked up an appetite.\n"
	.string "Let us eat!$"

UnduraTunnels_Text_LaiosPostBattle:
	.string "You may not be aware, but when\n"
	.string "boiled, Vaiking are at their\l"
	.string "most scrumptious. Pair it with\l"
	.string "Gumberree salad, and... oh,\l"
	.string "it is to die for.$"

UnduraTunnels_Text_GioIntro:
	.string "Looks like we got ourselves\n"
	.string "another loser, here! Fu-fu-fu...$"

UnduraTunnels_Text_GioDefeated:
	.string "Look at this weakling. They're\n"
	.string "so proud to have won! How naive.$"

UnduraTunnels_Text_GioPostBattle:
	.string "You absolute buffoon. Clown, even.\n"
	.string "Did dat win getcha what you wanted?\l"
	.string "Fu-fu-fu...$"

UnduraTunnels_Text_EunmiIntro:
	.string "I'm gonna make you cry\n"
	.string "like a baby.$"

UnduraTunnels_Text_EunmiDefeated:
	.string "Wah, wah, wah...\n"
	.string "that's all I hear from you.$"

UnduraTunnels_Text_EunmiPostBattle:
	.string "Geheheheh! Look at you.\n"
	.string "Wastin' your time here playin'\l"
	.string "with your little Pokemons.\l"
	.string "I'm sure your dud of a life\l"
	.string "is real rivetin'!$"

UnduraTunnels_Text_ThymeIntro:
	.string "I'm gonna end up missing the bell!\n"
	.string "How do you leave this cave!?$"

UnduraTunnels_Text_ThymeDefeated:
	.string "Sis, please, I'm telling you!\n"
	.string "We're LOST!$"

UnduraTunnels_Text_ThymePostBattle:
	.string "She keeps pointing us in directions\n"
	.string "that lead to dead ends. I don't\l"
	.string "even KNOW how we ended up HERE\l"
	.string "from Littleroot Town.$"

UnduraTunnels_Text_BasilIntro:
	.string "Oh, could you be a dear, and\n"
	.string "direct us to the Rustboro City\l"
	.string "exit of the tunnel?$"

UnduraTunnels_Text_BasilDefeated:
	.string "I THINK it's that way...?$"

UnduraTunnels_Text_BasilPostBattle:
	.string "My brother is terribly late\n"
	.string "for his class in Rustboro, but\l"
	.string "I lost my contacts... so I have\l"
	.string "been relying on scent\l"
	.string "to find our way.$"
