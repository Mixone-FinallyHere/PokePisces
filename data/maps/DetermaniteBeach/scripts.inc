DetermaniteBeach_MapScripts::
	.byte 0

DetermaniteBeach_EventScript_Mimi::
    trainerbattle_single TRAINER_P_MIMI, DetermaniteBeach_Text_MimiIntro, DetermaniteBeach_Text_MimiDefeated
    msgbox DetermaniteBeach_Text_MimiPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Seamus::
    trainerbattle_single TRAINER_P_SEAMUS, DetermaniteBeach_Text_SeamusIntro, DetermaniteBeach_Text_SeamusDefeated
    msgbox DetermaniteBeach_Text_SeamusPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Laura::
    trainerbattle_single TRAINER_P_LAURA, DetermaniteBeach_Text_LauraIntro, DetermaniteBeach_Text_LauraDefeated
    msgbox DetermaniteBeach_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Laharl::
    trainerbattle_single TRAINER_P_LAHARL, DetermaniteBeach_Text_LaharlIntro, DetermaniteBeach_Text_LaharlDefeated
    msgbox DetermaniteBeach_Text_LaharlPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Etna::
    trainerbattle_single TRAINER_P_ETNA, DetermaniteBeach_Text_EtnaIntro, DetermaniteBeach_Text_EtnaDefeated
    msgbox DetermaniteBeach_Text_EtnaPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Flonne::
    trainerbattle_single TRAINER_P_FLONNE, DetermaniteBeach_Text_FlonneIntro, DetermaniteBeach_Text_FlonneDefeated
    msgbox DetermaniteBeach_Text_FlonnePostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Yasuke::
    trainerbattle_single TRAINER_P_YASUKE, DetermaniteBeach_Text_YasukeIntro, DetermaniteBeach_Text_YasukeDefeated
    msgbox DetermaniteBeach_Text_YasukePostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Gatherer::
    trainerbattle_single TRAINER_P_GATHERER, DetermaniteBeach_Text_GathererIntro, DetermaniteBeach_Text_GathererDefeated
    msgbox DetermaniteBeach_Text_GathererPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Yue::
    trainerbattle_single TRAINER_P_YUE, DetermaniteBeach_Text_YueIntro, DetermaniteBeach_Text_YueDefeated
    msgbox DetermaniteBeach_Text_YuePostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_Prince::
    trainerbattle_single TRAINER_P_PRINCE, DetermaniteBeach_Text_PrinceIntro, DetermaniteBeach_Text_PrinceDefeated
    msgbox DetermaniteBeach_Text_PrincePostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_King::
    trainerbattle_single TRAINER_P_KING, DetermaniteBeach_Text_KingIntro, DetermaniteBeach_Text_KingDefeated
    msgbox DetermaniteBeach_Text_KingPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_SaiAndMisha::
    trainerbattle_double TRAINER_P_SAI_AND_MISHA, DetermaniteBeach_Text_SaiAndMishaIntro, DetermaniteBeach_Text_SaiAndMishaDefeated, DetermaniteBeach_Text_SaiAndMishaNeedTwoMons
    msgbox DetermaniteBeach_Text_SaiAndMishaPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteBeach_EventScript_QuarrySign::
    msgbox DetermaniteBeach_Text_QuarrySign, MSGBOX_SIGN
    end

DetermaniteBeach_EventScript_WishwellSign::
    msgbox DetermaniteBeach_Text_WishwellSign, MSGBOX_SIGN
    end

DetermaniteBeach_Text_QuarrySign:
	.string "GRANIPLINE QUARRY$"

DetermaniteBeach_Text_WishwellSign:
	.string "NORTH - WISHWELL OCEAN$"

DetermaniteBeach_Text_MimiIntro:
	.string "Me, me! Let me have a go!$"

DetermaniteBeach_Text_MimiDefeated:
	.string "My, my... that didn't go so well.$"

DetermaniteBeach_Text_MimiPostBattle:
	.string "Me oh my, I need to learn a\n"
	.string "few things to catch up.$"

DetermaniteBeach_Text_SeamusIntro:
	.string "Seamus sells sea shells\n"
	.string "by the sea shore...$"

DetermaniteBeach_Text_SeamusDefeated:
	.string "And now I have to shell\n"
	.string "this out...$"

DetermaniteBeach_Text_SeamusPostBattle:
	.string "Seamus sells... sea shells...\n"
	.string "What? I don't REALLY sell my\l"
	.string "shells. I just like tongue twisters!$"

DetermaniteBeach_Text_LauraIntro:
	.string "You have WEAK aura! I'll show you\n"
	.string "how someone with STRONG aura fights!$"

DetermaniteBeach_Text_LauraDefeated:
	.string "Screw it, we ball!$"

DetermaniteBeach_Text_LauraPostBattle:
	.string "I don't like using lots of strategy\n"
	.string "in fights. Just use the highest\l"
	.string "power move over and over!\l"
	.string "What could go wrong?$"

DetermaniteBeach_Text_LaharlIntro:
	.string "Don't you for a SECOND think that\n"
	.string "you're gettin' outta here\l"
	.string "with alla your fingers!$"

DetermaniteBeach_Text_LaharlDefeated:
	.string "You still gots all ten!?$"

DetermaniteBeach_Text_LaharlPostBattle:
	.string "Snip-snip! Where's my scissors!?\n$"

DetermaniteBeach_Text_EtnaIntro:
	.string "Mwah-hah-hah! When I'm done with\n"
	.string "you, you'll be in debt... FOREVER!$"

DetermaniteBeach_Text_EtnaDefeated:
	.string "You'll PAY for this,\n"
	.string "mark my words!!$"

DetermaniteBeach_Text_EtnaPostBattle:
	.string "We'll be watching you, trainer...\n"
	.string "ALWAYS watching...$"

DetermaniteBeach_Text_FlonneIntro:
	.string "I don't need to grow up!\n"
	.string "I'm tough, even as a Lass!$"

DetermaniteBeach_Text_FlonneDefeated:
	.string "The big kids just can't let\n"
	.string "me win, even now...$"

DetermaniteBeach_Text_FlonnePostBattle:
	.string "I'll be a Madame eventually! Then\n"
	.string "there's no WAY I'll let you pass!$"

DetermaniteBeach_Text_YasukeIntro:
	.string "Whoa, whoa. You betta have a\n"
	.string "damn good reason for traipsin'\l"
	.string "into my turf...$"

DetermaniteBeach_Text_YasukeDefeated:
	.string "D-Did Roxanne send ya!?$"

DetermaniteBeach_Text_YasukePostBattle:
	.string "Oh, phew... you ain't wit another\n"
	.string "gang, huh...$"

DetermaniteBeach_Text_GathererIntro:
	.string "A man provides for his family.\n"
	.string "I will bring them home a big\l"
	.string "payday today, with money\l"
	.string "taken from you...$"

DetermaniteBeach_Text_GathererDefeated:
	.string "Tsk. You were more man than I.$"

DetermaniteBeach_Text_GathererPostBattle:
	.string "I hope you use the money you\n"
	.string "took from me wisely.$"

DetermaniteBeach_Text_YueIntro:
	.string "Oh, dear... just how did a young\n"
	.string "buck like you make it this far?$"

DetermaniteBeach_Text_YueDefeated:
	.string "It seems I have learned the reason.$"

DetermaniteBeach_Text_YuePostBattle:
	.string "You are one fine battler...\n"
	.string "but do not let that go to your head.$"

DetermaniteBeach_Text_PrinceIntro:
	.string "Just half a year ago, I\n"
	.string "used to be a Martial Artist!\l"
	.string "Quite the transformation,\l"
	.string "wouldn't you say?$"

DetermaniteBeach_Text_PrinceDefeated:
	.string "Y-Yeah, I got kicked out\n"
	.string "of my dojo...$"

DetermaniteBeach_Text_PrincePostBattle:
	.string "I've been treated so unfairly!\n"
	.string "I'm just not good at any martial art!$"

DetermaniteBeach_Text_KingIntro:
	.string "Not all who swim are those who surf!$"

DetermaniteBeach_Text_KingDefeated:
	.string "This loss undeters me!$"

DetermaniteBeach_Text_KingPostBattle:
	.string "A true king swims without implement!$"

DetermaniteBeach_Text_SaiAndMishaIntro:
	.string "SAI: In battle and in cultivation,\n"
	.string "     one must take over the field!\l"
	.string "MISHA: Let's show you how it's done!$"

DetermaniteBeach_Text_SaiAndMishaDefeated:
	.string "SAI: You bulldozed us!\n"
	.string "MISHA: And paved us over!$"

DetermaniteBeach_Text_SaiAndMishaPostBattle:
	.string "MISHA: We're for hire if you\n"
	.string "       ever need a yard landscaper!\l"
	.string "SAI: We'll stick fog machines\l"
	.string "     EVERYWHERE if you want some\l"
	.string "     Misty Terrain!$"

DetermaniteBeach_Text_SaiAndMishaNeedTwoMons:
	.string "SAI: One is too little for a\n"
	.string "     project as big as this!\l"
	.string "MISHA: Come back with an actual team.$"
