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

Maintenance_EventScript_FloorPlan::
	msgbox Maintenance_Text_FloorPlan, MSGBOX_SIGN
	end

Maintenance_Text_FloorPlan:
	.string "(It's a rough floor plan\n"
	.string "of the Maintenance area...)\p"
	.string "(The break lounge is at the\n"
	.string "north end. Maybe that's where\l"
	.string "one could find the Storyteller...)$"

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
	.string "Stinks I can't bike in here...\n"
	.string "you wouldn't know it, maybe, but\l"
	.string "I'm a BMX Superstar! WAHOO!$"

Maintenance_Text_FigliosiDefeated:
	.string "Mama mia... that was spicy!$"

Maintenance_Text_FigliosiPostBattle:
	.string "Have you met my bruddah, Lane,\n"
	.string "somewhere out there?\l"
	.string "He likes jokin' around!$"

Maintenance_Text_OllyIntro:
	.string "GET RRRRRRREADY...\n"
	.string "FOR A SHOCKING...! BATTLE!!!$"

Maintenance_Text_OllyDefeated:
	.string "GZZZRT! SHORT-CIRCUITED!$"

Maintenance_Text_OllyPostBattle:
	.string "THAT BLEW UP IN MY FACE!\n$"

Maintenance_Text_PollyIntro:
	.string "Don't go touching anything\n"
	.string "you're not supposed to!$"

Maintenance_Text_PollyDefeated:
	.string "You made me look like a tool!$"

Maintenance_Text_PollyPostBattle:
	.string "Olly keeps breaking anything\n"
	.string "electrical that he touches. It's\l"
	.string "like he has a high voltage current\l"
	.string "running through him at all times!$"

Maintenance_Text_EdwardIntro:
	.string "20 long years of crankin' gears...\n"
	.string "dum dee dum dee doo...$"

Maintenance_Text_EdwardDefeated:
	.string "Singin' is how I keep my mind\n"
	.string "occupied on the job!$"

Maintenance_Text_EdwardPostBattle:
	.string "20 long years of crankin' gears...\n"
	.string "dum dee dum dee doo...$"

Maintenance_Text_YancyIntro:
	.string "To battle? It takes two, it takes\n"
	.string "two, me-n-you!$"

Maintenance_Text_YancyDefeated:
	.string "Ah! I see now!\p"
	.string "It also takes two to beat me;\n"
	.string "you, AND, your Pokemon!$"

Maintenance_Text_YancyPostBattle:
	.string "The tango has always been hard\n"
	.string "for me to master...$"

Maintenance_Text_ErnestIntro:
	.string "A Hardhatter's job is never done!$"

Maintenance_Text_ErnestDefeated:
	.string "It ain't much, but it's honest work.$"

Maintenance_Text_ErnestPostBattle:
	.string "Maybe I should try runnin'\n"
	.string "for mayor.$"

Maintenance_Text_LattyIntro:
	.string "I'm about to mop the floor\n"
	.string "with you!$"

Maintenance_Text_LattyDefeated:
	.string "Huh!\p"
	.string "...Maybe I n-need to work\n"
	.string "on my trash talk?$"

Maintenance_Text_LattyPostBattle:
	.string "Hey, I thought the little\n"
	.string "pun was humorous...$"

Maintenance_Text_AliceIntro:
	.string "C'mon, let's mosh!$"

Maintenance_Text_AliceDefeated:
	.string "Ow! Ow!\n"
	.string "Owww!$"

Maintenance_Text_AlicePostBattle:
	.string "Don't get too rough in the pit!\n"
	.string "We're all just here to have fun.$"

Maintenance_Text_AnonIntro:
	.string "Your package has arrived\n"
	.string "at the warehouse.\p"
	.string "Please confirm your address.$"

Maintenance_Text_AnonDefeated:
	.string "Delivery failed!$"

Maintenance_Text_AnonPostBattle:
	.string "Abort! Abort!\n"
	.string "Abandon ship! AAAGGHH!$"

Maintenance_Text_RobinIntro:
	.string "You're no match for these\n"
	.string "Pokemon I “acquired”!$"

Maintenance_Text_RobinDefeated:
	.string "Oops, ehhh... may have\n"
	.string "mixed up my Balls...$"

Maintenance_Text_RobinPostBattle:
	.string "Eyy, that waddn't a fair fight!\n"
	.string "What gives? You didn't “give”\l"
	.string "me one'a your dudes first!$"

Maintenance_Text_CharityIntro:
	.string "Hmmm....? Oh! Is it a trainer?$"

Maintenance_Text_CharityDefeated:
	.string "Ah, it was!$"

Maintenance_Text_CharityPostBattle:
	.string "Sorry... I can't see very well,\n"
	.string "so I rely on scents to\l"
	.string "identify others.$"

Maintenance_Text_SinIntro:
	.string "Do you think you're a star?\n"
	.string "We'll see about that...$"

Maintenance_Text_SinDefeated:
	.string "You may be a star after all!$"

Maintenance_Text_SinPostBattle:
	.string "What star sign are you? Pisces?$"
