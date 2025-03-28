NavigulfWaves_MapScripts::
	.byte 0

NavigulfWaves_EventScript_Chad::
    trainerbattle_single TRAINER_P_CHAD, NavigulfWaves_Text_ChadIntro, NavigulfWaves_Text_ChadDefeated
    msgbox NavigulfWaves_Text_ChadPostBattle, MSGBOX_AUTOCLOSE
    end

NavigulfWaves_EventScript_Chaz::
    trainerbattle_single TRAINER_P_CHAZ, NavigulfWaves_Text_ChazIntro, NavigulfWaves_Text_ChazDefeated
    msgbox NavigulfWaves_Text_ChazPostBattle, MSGBOX_AUTOCLOSE
    end

NavigulfWaves_EventScript_Brody::
    trainerbattle_single TRAINER_P_BRODY, NavigulfWaves_Text_BrodyIntro, NavigulfWaves_Text_BrodyDefeated
    msgbox NavigulfWaves_Text_BrodyPostBattle, MSGBOX_AUTOCLOSE
    end

NavigulfWaves_EventScript_Dela::
    trainerbattle_single TRAINER_P_DELA, NavigulfWaves_Text_DelaIntro, NavigulfWaves_Text_DelaDefeated
    msgbox NavigulfWaves_Text_DelaPostBattle, MSGBOX_AUTOCLOSE
    end

NavigulfWaves_EventScript_Kiera::
    trainerbattle_single TRAINER_P_KIERA, NavigulfWaves_Text_KieraIntro, NavigulfWaves_Text_KieraDefeated
    msgbox NavigulfWaves_Text_KieraPostBattle, MSGBOX_AUTOCLOSE
    end

NavigulfWaves_EventScript_Libra::
    trainerbattle_single TRAINER_P_LIBRA, NavigulfWaves_Text_LibraIntro, NavigulfWaves_Text_LibraDefeated
    msgbox NavigulfWaves_Text_LibraPostBattle, MSGBOX_AUTOCLOSE
    end

NavigulfWaves_Text_ChadIntro:
	.string "Wanna have a totally tubular battle?$"

NavigulfWaves_Text_ChadDefeated:
	.string "Awww, wipeout!$"

NavigulfWaves_Text_ChadPostBattle:
	.string "Where do I keep my Poké Balls?\n"
	.string "Teehee, man's secret!$"

NavigulfWaves_Text_ChazIntro:
	.string "Way Cool!$"

NavigulfWaves_Text_ChazDefeated:
	.string "Gnarly...$"

NavigulfWaves_Text_ChazPostBattle:
	.string "Groovy! Mondo! Outrageous! Funky!$"

NavigulfWaves_Text_BrodyIntro:
	.string "Surf's up, dude!$"

NavigulfWaves_Text_BrodyDefeated:
	.string "Surf's.... down!?!?$"

NavigulfWaves_Text_BrodyPostBattle:
	.string "Duuude...\n"
	.string "I don't know where the surf went.$"

NavigulfWaves_Text_DelaIntro:
	.string "One thing about chess?\n"
	.string "You always protect the queen!$"

NavigulfWaves_Text_DelaDefeated:
	.string "I've been out-gambited!$"

NavigulfWaves_Text_DelaPostBattle:
	.string "Always protect your Octohime,\n"
	.string "if you have one. She deserves it!$"

NavigulfWaves_Text_KieraIntro:
	.string "I'm a bit lost right now!\n"
	.string "I'll take out those frustrations...\l"
	.string "on you!$"

NavigulfWaves_Text_KieraDefeated:
	.string "I got turned around again!$"

NavigulfWaves_Text_KieraPostBattle:
	.string "The ocean can sometimes feel\n"
	.string "straight-up endless, huh?$"

NavigulfWaves_Text_LibraIntro:
	.string "Surprised, to see me floating\n"
	.string "atop the water? It is only\l"
	.string "natural for someone of my\l"
	.string "psychic caliber.\p"
	.string "Don't worry, I won't hurt\n"
	.string "your Pokemon... too much...$"

NavigulfWaves_Text_LibraDefeated:
	.string "Gh...! My levitation took\n"
	.string "up too much of my power...!$"

NavigulfWaves_Text_LibraPostBattle:
	.string "I am not amused.$"
