UnduraTunnelsDeep_MapScripts::
	.byte 0

UnduraTunnelsDeep_EventScript_Coheed::
    trainerbattle_single TRAINER_P_COHEED, UnduraTunnelsDeep_Text_CoheedIntro, UnduraTunnelsDeep_Text_CoheedDefeated
    msgbox UnduraTunnelsDeep_Text_CoheedPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnelsDeep_EventScript_Cambria::
    trainerbattle_single TRAINER_P_CAMBRIA, UnduraTunnelsDeep_Text_CambriaIntro, UnduraTunnelsDeep_Text_CambriaDefeated
    msgbox UnduraTunnelsDeep_Text_CambriaPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnelsDeep_EventScript_Serling::
    trainerbattle_single TRAINER_P_SERLING, UnduraTunnelsDeep_Text_SerlingIntro, UnduraTunnelsDeep_Text_SerlingDefeated
    msgbox UnduraTunnelsDeep_Text_SerlingPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnelsDeep_EventScript_Mariana::
    trainerbattle_single TRAINER_P_MARIANA, UnduraTunnelsDeep_Text_MarianaIntro, UnduraTunnelsDeep_Text_MarianaDefeated
    msgbox UnduraTunnelsDeep_Text_MarianaPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnelsDeep_EventScript_Coral::
    trainerbattle_single TRAINER_P_CORAL, UnduraTunnelsDeep_Text_CoralIntro, UnduraTunnelsDeep_Text_CoralDefeated
    msgbox UnduraTunnelsDeep_Text_CoralPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnelsDeep_EventScript_Gus::
    trainerbattle_single TRAINER_P_GUS, UnduraTunnelsDeep_Text_GusIntro, UnduraTunnelsDeep_Text_GusDefeated
    msgbox UnduraTunnelsDeep_Text_GusPostBattle, MSGBOX_AUTOCLOSE
    end

UnduraTunnelsDeep_Text_CoheedIntro:
	.string "(It's a diver! Without words,\n"
	.string "they reach out their Pokeball\l"
	.string "to start a battle...)$"

UnduraTunnelsDeep_Text_CoheedDefeated:
	.string "(The diver hangs their head\n"
	.string "in defeat...)$"

UnduraTunnelsDeep_Text_CoheedPostBattle:
	.string "(No real way to communicate\n"
	.string "with them. Best to move on.)$"

UnduraTunnelsDeep_Text_CambriaIntro:
	.string "(It's a diver! Without words,\n"
	.string "they reach out their Pokeball\l"
	.string "to start a battle...)$"

UnduraTunnelsDeep_Text_CambriaDefeated:
	.string "(The diver hangs their head\n"
	.string "in defeat...)$"

UnduraTunnelsDeep_Text_CambriaPostBattle:
	.string "(No real way to communicate\n"
	.string "with them. Best to move on.)$"

UnduraTunnelsDeep_Text_SerlingIntro:
	.string "(It's a diver! Without words,\n"
	.string "they reach out their Pokeball\l"
	.string "to start a battle...)$"

UnduraTunnelsDeep_Text_SerlingDefeated:
	.string "(The diver hangs their head\n"
	.string "in defeat...)$"

UnduraTunnelsDeep_Text_SerlingPostBattle:
	.string "(No real way to communicate\n"
	.string "with them. Best to move on.)$"

UnduraTunnelsDeep_Text_MarianaIntro:
	.string "(It's a diver! Without words,\n"
	.string "they reach out their Pokeball\l"
	.string "to start a battle...)$"

UnduraTunnelsDeep_Text_MarianaDefeated:
	.string "(The diver hangs their head\n"
	.string "in defeat...)$"

UnduraTunnelsDeep_Text_MarianaPostBattle:
	.string "(No real way to communicate\n"
	.string "with them. Best to move on.)$"

UnduraTunnelsDeep_Text_CoralIntro:
	.string "(It's a diver! Without words,\n"
	.string "they reach out their Pokeball\l"
	.string "to start a battle...)$"

UnduraTunnelsDeep_Text_CoralDefeated:
	.string "(The diver hangs their head\n"
	.string "in defeat...)$"

UnduraTunnelsDeep_Text_CoralPostBattle:
	.string "(No real way to communicate\n"
	.string "with them. Best to move on.)$"

UnduraTunnelsDeep_Text_GusIntro:
	.string "(It's a diver! Without words,\n"
	.string "they reach out their Pokeball\l"
	.string "to start a battle...)$"

UnduraTunnelsDeep_Text_GusDefeated:
	.string "(The diver hangs their head\n"
	.string "in defeat...)$"

UnduraTunnelsDeep_Text_GusPostBattle:
	.string "(No real way to communicate\n"
	.string "with them. Best to move on.)$"
