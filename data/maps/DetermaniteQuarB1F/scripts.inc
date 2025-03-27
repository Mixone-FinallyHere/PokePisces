DetermaniteQuarB1F_MapScripts::
	.byte 0

DetermaniteQuarB1F_EventScript_Jiggles::
    trainerbattle_single TRAINER_P_JIGGLES, DetermaniteQuarB1F_Text_JigglesIntro, DetermaniteQuarB1F_Text_JigglesDefeated
    msgbox DetermaniteQuarB1F_Text_JigglesPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarB1F_EventScript_Dahlia::
    trainerbattle_single TRAINER_P_DAHLIA, DetermaniteQuarB1F_Text_DahliaIntro, DetermaniteQuarB1F_Text_DahliaDefeated
    msgbox DetermaniteQuarB1F_Text_DahliaPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarB1F_EventScript_June::
    trainerbattle_single TRAINER_P_JUNE, DetermaniteQuarB1F_Text_JuneIntro, DetermaniteQuarB1F_Text_JuneDefeated
    msgbox DetermaniteQuarB1F_Text_JunePostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarB1F_EventScript_August::
    trainerbattle_single TRAINER_P_AUGUST, DetermaniteQuarB1F_Text_AugustIntro, DetermaniteQuarB1F_Text_AugustDefeated
    msgbox DetermaniteQuarB1F_Text_AugustPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarB1F_EventScript_Mildred::
    trainerbattle_single TRAINER_P_MILDRED, DetermaniteQuarB1F_Text_MildredIntro, DetermaniteQuarB1F_Text_MildredDefeated
    msgbox DetermaniteQuarB1F_Text_MildredPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarB1F_EventScript_Grey::
    trainerbattle_single TRAINER_P_GREY, DetermaniteQuarB1F_Text_GreyIntro, DetermaniteQuarB1F_Text_GreyDefeated
    msgbox DetermaniteQuarB1F_Text_GreyPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarB1F_Text_JigglesIntro:
	.string "Honk-honk!$"

DetermaniteQuarB1F_Text_JigglesDefeated:
	.string "Aw, honk...$"

DetermaniteQuarB1F_Text_JigglesPostBattle:
	.string "Honk!?$"

DetermaniteQuarB1F_Text_DahliaIntro:
	.string "Huff-puff...$"

DetermaniteQuarB1F_Text_DahliaDefeated:
	.string "I can't stop panting...\n"
	.string "I'm too... huff... exhausted...$"

DetermaniteQuarB1F_Text_DahliaPostBattle:
	.string "I must muster the strength\n"
	.string "to go a little bit further...!$"

DetermaniteQuarB1F_Text_JuneIntro:
	.string "Now presenting... the wonderful,\n"
	.string "the beautiful... August!$"

DetermaniteQuarB1F_Text_JuneDefeated:
	.string "I can tell August at least\n"
	.string "tried her best!$"

DetermaniteQuarB1F_Text_JunePostBattle:
	.string "My partner doesn't need words\n"
	.string "if I hype her up! She can just\l"
	.string "focus on her moves!$"

DetermaniteQuarB1F_Text_AugustIntro:
	.string "(This Dancer starts ABSOLUTELY\n"
	.string "breakin' it down. Her moves are\l"
	.string "so good, you forget that she's\l"
	.string "about to fight you.)$"

DetermaniteQuarB1F_Text_AugustDefeated:
	.string "(She's still dancing,\n"
	.string "even in defeat.)$"

DetermaniteQuarB1F_Text_AugustPostBattle:
	.string "(August is bowing to you.)$"

DetermaniteQuarB1F_Text_MildredIntro:
	.string "Awful lot of Relic type Pokemon\n"
	.string "'round these parts, eh?$"

DetermaniteQuarB1F_Text_MildredDefeated:
	.string "Now, don't go callin' me\n"
	.string "a Relic, too, whippersnapper!$"

DetermaniteQuarB1F_Text_MildredPostBattle:
	.string "I was there helpin' ol' Spenser\n"
	.string "dig up the first evidence of\l"
	.string "the Relic type. Our first live\l"
	.string "specimens were here in Granipline\l"
	.string "Quarry! Fascinating times.$"

DetermaniteQuarB1F_Text_GreyIntro:
	.string "What shape do you think\n"
	.string "is the best of them all?$"

DetermaniteQuarB1F_Text_GreyDefeated:
	.string "Because it should be Octagons.$"

DetermaniteQuarB1F_Text_GreyPostBattle:
	.string "Octagons are the best-agons.$"
