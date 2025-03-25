SailorsPauseUnderwater_MapScripts::
	.byte 0

SailorsPauseUnderwater_EventScript_Sandeep::
    trainerbattle_single TRAINER_P_SANDEEP, SailorsPauseUnderwater_Text_SandeepIntro, SailorsPauseUnderwater_Text_SandeepDefeated
    msgbox SailorsPauseUnderwater_Text_SandeepPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPauseUnderwater_Text_SandeepIntro:
	.string "(It's a diver! Without words,\n"
	.string "they reach out their Pokeball\l"
	.string "to start a battle...)$"

SailorsPauseUnderwater_Text_SandeepDefeated:
	.string "(The diver hangs their head\n"
	.string "in defeat...)$"

SailorsPauseUnderwater_Text_SandeepPostBattle:
	.string "(No real way to communicate\n"
	.string "with them. Best to move on.)$"
