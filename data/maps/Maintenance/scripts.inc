Maintenance_MapScripts::
	.byte 0

Maintenance_EventScript_Figliosi::
    trainerbattle_single TRAINER_P_FIGLIOSI, Maintenance_Text_FigliosiIntro, Maintenance_Text_FigliosiDefeated
    msgbox Maintenance_Text_FigliosiPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Olly::
    trainerbattle_single TRAINER_P_OLLY, Maintenance_Text_OllyIntro, Maintenance_Text_OllyDefeated
    msgbox Maintenance_Text_OllyPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Polly::
    trainerbattle_single TRAINER_P_POLLY, Maintenance_Text_PollyIntro, Maintenance_Text_PollyDefeated
    msgbox Maintenance_Text_PollyPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Edward::
    trainerbattle_single TRAINER_P_EDWARD, Maintenance_Text_EdwardIntro, Maintenance_Text_EdwardDefeated
    msgbox Maintenance_Text_EdwardPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Yancy::
    trainerbattle_single TRAINER_P_YANCY, Maintenance_Text_YancyIntro, Maintenance_Text_YancyDefeated
    msgbox Maintenance_Text_YancyPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Ernest::
    trainerbattle_single TRAINER_P_ERNEST, Maintenance_Text_ErnestIntro, Maintenance_Text_ErnestDefeated
    msgbox Maintenance_Text_ErnestPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Latty::
    trainerbattle_single TRAINER_P_LATTY, Maintenance_Text_LattyIntro, Maintenance_Text_LattyDefeated
    msgbox Maintenance_Text_LattyPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Alice::
    trainerbattle_single TRAINER_P_ALICE, Maintenance_Text_AliceIntro, Maintenance_Text_AliceDefeated
    msgbox Maintenance_Text_AlicePostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Anon::
    trainerbattle_single TRAINER_P_ANON, Maintenance_Text_AnonIntro, Maintenance_Text_AnonDefeated
    msgbox Maintenance_Text_AnonPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Robin::
    trainerbattle_single TRAINER_P_ROBIN, Maintenance_Text_RobinIntro, Maintenance_Text_RobinDefeated
    msgbox Maintenance_Text_RobinPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Charity::
    trainerbattle_single TRAINER_P_CHARITY, Maintenance_Text_CharityIntro, Maintenance_Text_CharityDefeated
    msgbox Maintenance_Text_CharityPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_Sin::
    trainerbattle_single TRAINER_P_SIN, Maintenance_Text_SinIntro, Maintenance_Text_SinDefeated
    msgbox Maintenance_Text_SinPostBattle, MSGBOX_AUTOCLOSE
    end

Maintenance_EventScript_GeneResearcher::
	lock
	faceplayer
	checkitem ITEM_BERSERK_GENE
	goto_if_eq VAR_RESULT, TRUE, Maintenance_EventScript_AlreadyGaveBerserkGene
	msgbox Maintenance_Text_ResearchBreakthrough, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_BERSERK_GENE
	closemessage
	msgbox Maintenance_Text_HurtsTheirBrains, MSGBOX_AUTOCLOSE
	release
	end

Maintenance_EventScript_AlreadyGaveBerserkGene::
	msgbox Maintenance_Text_AlreadyGaveBerserkGene, MSGBOX_AUTOCLOSE
	release
	end

Maintenance_Text_ResearchBreakthrough:
	.string "I have been doing intense research\n"
	.string "into the Pokemon genome...\l"
	.string "and through that...! I have made\l"
	.string "a discovery!\p"
	.string "An... unpopular, discovery.\n"
	.string "There is a certain gene in Pokemon\l"
	.string "DNA that has been bred out\l"
	.string "over decades... but I have found a\l"
	.string "way to re-introduce it temporarily.\p"
	.string "The Berserk Gene...\n"
	.string "it grants power at the cost of sanity.\l"
	.string "Naturally, I can't go public\l"
	.string "with this. It'll be a Pokemon rights\l"
	.string "kerfuffle and all that.\p"
	.string "Buuuuuttt...... I DO want to\n"
	.string "get field testing for the gene...\l"
	.string "Sooooo.... if you were willing to\l"
	.string "help a lady out... on the down low...\p"
	.string "(This might as well happen.)\p"
	.string "Thanks.\n$"

Maintenance_Text_HurtsTheirBrains:
	.string "Use that on whatever Pokemon\n"
	.string "you want to go berserk...\l"
	.string "as, uh, ethically as possible...\l"
	.string "I guess...$"

Maintenance_Text_AlreadyGaveBerserkGene:
	.string "It seems certain Bug Pokemon\n"
	.string "react to that gene stronger than\l"
	.string "other species...$"

Maintenance_Text_FigliosiIntro:
	.string "intro$"

Maintenance_Text_FigliosiDefeated:
	.string "defeat$"

Maintenance_Text_FigliosiPostBattle:
	.string "post$"

Maintenance_Text_OllyIntro:
	.string "intro$"

Maintenance_Text_OllyDefeated:
	.string "defeat$"

Maintenance_Text_OllyPostBattle:
	.string "post$"

Maintenance_Text_PollyIntro:
	.string "intro$"

Maintenance_Text_PollyDefeated:
	.string "defeat$"

Maintenance_Text_PollyPostBattle:
	.string "post$"

Maintenance_Text_EdwardIntro:
	.string "intro$"

Maintenance_Text_EdwardDefeated:
	.string "defeat$"

Maintenance_Text_EdwardPostBattle:
	.string "post$"

Maintenance_Text_YancyIntro:
	.string "intro$"

Maintenance_Text_YancyDefeated:
	.string "defeat$"

Maintenance_Text_YancyPostBattle:
	.string "post$"

Maintenance_Text_ErnestIntro:
	.string "intro$"

Maintenance_Text_ErnestDefeated:
	.string "defeat$"

Maintenance_Text_ErnestPostBattle:
	.string "post$"

Maintenance_Text_LattyIntro:
	.string "intro$"

Maintenance_Text_LattyDefeated:
	.string "defeat$"

Maintenance_Text_LattyPostBattle:
	.string "post$"

Maintenance_Text_AliceIntro:
	.string "intro$"

Maintenance_Text_AliceDefeated:
	.string "defeat$"

Maintenance_Text_AlicePostBattle:
	.string "post$"

Maintenance_Text_AnonIntro:
	.string "intro$"

Maintenance_Text_AnonDefeated:
	.string "defeat$"

Maintenance_Text_AnonPostBattle:
	.string "post$"

Maintenance_Text_RobinIntro:
	.string "intro$"

Maintenance_Text_RobinDefeated:
	.string "defeat$"

Maintenance_Text_RobinPostBattle:
	.string "post$"

Maintenance_Text_CharityIntro:
	.string "intro$"

Maintenance_Text_CharityDefeated:
	.string "defeat$"

Maintenance_Text_CharityPostBattle:
	.string "post$"

Maintenance_Text_SinIntro:
	.string "intro$"

Maintenance_Text_SinDefeated:
	.string "defeat$"

Maintenance_Text_SinPostBattle:
	.string "post$"
