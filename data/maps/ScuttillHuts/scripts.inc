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
	.string "Fear the power of my Bugs!$"

ScuttillHuts_Text_VespaDefeated:
	.string "No... they failed me!?$"

ScuttillHuts_Text_VespaPostBattle:
	.string "Didja know that Bug type Pokemon\n"
	.string "can infiltrate through\l"
	.string "screens and Substitutes?\l"
	.string "They have a way of getting\l"
	.string "into places you don't want 'em to!$"

ScuttillHuts_Text_CrabroIntro:
	.string "BUG POWER BEATS ALL!$"

ScuttillHuts_Text_CrabroDefeated:
	.string "All but... you?$"

ScuttillHuts_Text_CrabroPostBattle:
	.string "Hmph, it won't take much longer\n"
	.string "for my Bugs to become unstoppable,\l"
	.string "even by the likes of you!$"
