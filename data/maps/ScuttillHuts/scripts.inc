ScuttillHuts_MapScripts::
	.byte 0

ScuttillHuts_EventScript_Vespa::
    trainerbattle_single TRAINER_P_VESPA, ScuttillHuts_Text_VespaIntro, ScuttillHuts_Text_VespaDefeated
    msgbox ScuttillHuts_Text_VespaPostBattle, MSGBOX_AUTOCLOSE
    end

ScuttillHuts_EventScript_Crabro::
    trainerbattle_single TRAINER_P_CRABRO, ScuttillHuts_Text_CrabroIntro, ScuttillHuts_Text_CrabroDefeated
    msgbox ScuttillHuts_Text_CrabroPostBattle, MSGBOX_AUTOCLOSE
    end

ScuttillHuts_Text_VespaIntro:
	.string "intro$"

ScuttillHuts_Text_VespaDefeated:
	.string "defeat$"

ScuttillHuts_Text_VespaPostBattle:
	.string "post$"

ScuttillHuts_Text_CrabroIntro:
	.string "intro$"

ScuttillHuts_Text_CrabroDefeated:
	.string "defeat$"

ScuttillHuts_Text_CrabroPostBattle:
	.string "post$"
