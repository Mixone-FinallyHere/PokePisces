SlateportShore_MapScripts::
	.byte 0

SlateportShore_EventScript_Jello::
    trainerbattle_single TRAINER_P_JELLO, SlateportShore_Text_JelloIntro, SlateportShore_Text_JelloDefeated
    msgbox SlateportShore_Text_JelloPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Len::
    trainerbattle_single TRAINER_P_LEN, SlateportShore_Text_LenIntro, SlateportShore_Text_LenDefeated
    msgbox SlateportShore_Text_LenPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Rin::
    trainerbattle_single TRAINER_P_RIN, SlateportShore_Text_RinIntro, SlateportShore_Text_RinDefeated
    msgbox SlateportShore_Text_RinPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_RoseAndThorn::
    trainerbattle_double TRAINER_P_ROSE_AND_THORN, SlateportShore_Text_RoseAndThornIntro, SlateportShore_Text_RoseAndThornDefeated, SlateportShore_Text_RoseAndThornNeedTwoMons
    msgbox SlateportShore_Text_RoseAndThornPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Tex::
    trainerbattle_single TRAINER_P_TEX, SlateportShore_Text_TexIntro, SlateportShore_Text_TexDefeated
    msgbox SlateportShore_Text_TexPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Dawn::
    trainerbattle_single TRAINER_P_DAWN, SlateportShore_Text_DawnIntro, SlateportShore_Text_DawnDefeated
    msgbox SlateportShore_Text_DawnPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Louise::
    trainerbattle_single TRAINER_P_LOUISE, SlateportShore_Text_LouiseIntro, SlateportShore_Text_LouiseDefeated
    msgbox SlateportShore_Text_LouisePostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Prag::
    trainerbattle_single TRAINER_P_PRAG, SlateportShore_Text_PragIntro, SlateportShore_Text_PragDefeated
    msgbox SlateportShore_Text_PragPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Mark::
    trainerbattle_single TRAINER_P_MARK, SlateportShore_Text_MarkIntro, SlateportShore_Text_MarkDefeated
    msgbox SlateportShore_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Sacred::
    trainerbattle_single TRAINER_P_SACRED, SlateportShore_Text_SacredIntro, SlateportShore_Text_SacredDefeated
    msgbox SlateportShore_Text_SacredPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Mandalore::
    trainerbattle_single TRAINER_P_MANDALORE, SlateportShore_Text_MandaloreIntro, SlateportShore_Text_MandaloreDefeated
    msgbox SlateportShore_Text_MandalorePostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_Beast::
    trainerbattle_single TRAINER_P_BEAST, SlateportShore_Text_BeastIntro, SlateportShore_Text_BeastDefeated
    msgbox SlateportShore_Text_BeastPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_CaseyNat::
    trainerbattle_single TRAINER_P_KAISENAT, SlateportShore_Text_CaseyNatIntro, SlateportShore_Text_CaseyNatDefeated
    msgbox SlateportShore_Text_CaseyNatPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportShore_EventScript_SeashoreHouseSign::
	msgbox SlateportShore_Text_SeashoreHouseSign, MSGBOX_SIGN
	end

SlateportShore_Text_SeashoreHouseSign:
	.string "The Seashore House\n"
	.string "Currently running a promotion!\l"
	.string "Come inside for details.$"

SlateportShore_Text_JelloIntro:
	.string "Yo! You dig on multiverses?$"

SlateportShore_Text_JelloDefeated:
	.string "In another universe, I won.$"

SlateportShore_Text_JelloPostBattle:
	.string "Even if something bad happens to me,\n"
	.string "in another universe something good\l"
	.string "happened to me.$"

SlateportShore_Text_LenIntro:
	.string "Let's go girl! Let's go Rin!\n"
	.string "If she's here, then we will win!$"

SlateportShore_Text_LenDefeated:
	.string "R-Rin? You couldn't pull through?$"

SlateportShore_Text_LenPostBattle:
	.string "Maybe cheerleaders aren't meant\n"
	.string "to support each other...$"

SlateportShore_Text_RinIntro:
	.string "Let's go gal! Let's go Len!\n"
	.string "If she can't triumph, no one can!$"

SlateportShore_Text_RinDefeated:
	.string "Len, c'mon! I thought\n"
	.string "you had this on lock!$"

SlateportShore_Text_RinPostBattle:
	.string "Len should consider becoming a\n"
	.string "Battle Gal instead.$"

SlateportShore_Text_RoseAndThornIntro:
	.string "ROSE: Every Rose has their Thorn!\n"
	.string "THORN: Just like every Lucas...\l"
	.string "       has their Dawn!$"

SlateportShore_Text_RoseAndThornDefeated:
	.string "ROSE: YEAH! MESS WITH ROSE,\n"
	.string "      YOU GET THE THORNS!\p"
	.string "THORN: ...Rose? We lost.\n$"

SlateportShore_Text_RoseAndThornPostBattle:
	.string "THORN: All that glitters\n"
	.string "       is not gold!\l"
	.string "ROSE: Stop talking in platitudes...$"

SlateportShore_Text_RoseAndThornNeedTwoMons:
	.string "ROSE: Aw, you only have one Pokemon?\n"
	.string "THORN: You'll need the peanut butter\l"
	.string "       to your jelly!$"

SlateportShore_Text_TexIntro:
	.string "Watch out, landlubber!\n"
	.string "You're in deep waters now!$"

SlateportShore_Text_TexDefeated:
	.string "Guess I was the one who was\n"
	.string "in deep water.$"

SlateportShore_Text_TexPostBattle:
	.string "Watch your step, landlubber, don't want\n"
	.string "you fallin' in the water now, do we?$"

SlateportShore_Text_DawnIntro:
	.string "I'm here until dusk! You won't\n"
	.string "be tiring me out!$"

SlateportShore_Text_DawnDefeated:
	.string "Fallen like the evening sun...$"

SlateportShore_Text_DawnPostBattle:
	.string "Those people over there are\n"
	.string "singing about SOMETHING...\l"
	.string "and all I keep hearing is my name.\l"
	.string "Isn't that suspicious?$"

SlateportShore_Text_LouiseIntro:
	.string "Jeez, do you mind? I've been having\n"
	.string "one hell of a catching day!$"

SlateportShore_Text_LouiseDefeated:
	.string "You took the bait and ripped\n"
	.string "my line clean off!$"

SlateportShore_Text_LouisePostBattle:
	.string "If you want to catch water-dwelling\n"
	.string "Pokemon in big batches, I suggest\l"
	.string "investing in Lure Balls.$"

SlateportShore_Text_PragIntro:
	.string "Hey guys, what's up and WELCOME\n"
	.string "back to my channel. Today, we\l"
	.string "are going to be ranking the\l"
	.string "TOP THREE HOENN POKEMON.\p"
	.string "Number three...!$"

SlateportShore_Text_PragDefeated:
	.string "And that does it for the video!\n"
	.string "Thank YOU for watching!$"

SlateportShore_Text_PragPostBattle:
	.string "Hey, thanks for not talking\n"
	.string "during that whole vid. I'll spruce\l"
	.string "things up with editing magic\l"
	.string "in post.$"

SlateportShore_Text_MarkIntro:
	.string "Hell-ooo everybody my name is Mark\n"
	.string "and welcome to Five Days at\l"
	.string "Slateport Shore, an indie tourist\l"
	.string "destination that you guys suggested\l"
	.string "en masse and I saw that Brawly went\l"
	.string "here and he said it was really,\l"
	.string "REALLY good. So I'm very eager to\l"
	.string "see what is up!$"

SlateportShore_Text_MarkDefeated:
	.string "And THAT was a very terrifying\n"
	.string "random trainer!$"

SlateportShore_Text_MarkPostBattle:
	.string "If you guys REALLY want me to\n"
	.string "fight this person again and\l"
	.string "try to BEAT them!?\l"
	.string "LET me know in the comments below!\l"
	.string "Thanks again everybody, and as\l"
	.string "always, I will see YOU...\l"
	.string "in the next video.\p"
	.string "BYE-BYE!$"

SlateportShore_Text_SacredIntro:
	.string "What IS this? Nah bro,\n"
	.string "you're playin'... a TRAINER?\l"
	.string "ALREADY?$"

SlateportShore_Text_SacredDefeated:
	.string "Bruh...$"

SlateportShore_Text_SacredPostBattle:
	.string "Nah cuz like.\n"
	.string "I wasn't ready for THAT.\l"
	.string "Like, bro. Seriously.$"

SlateportShore_Text_MandaloreIntro:
	.string "Woah, guys... let's see if\n"
	.string "we can get a reaction out of\l"
	.string "this guy!\p"
	.string "HEY! HEY YOU! Why're you here\n"
	.string "today? Can I hang out? Huh?\p"
	.string "(You attack him on impulse.)\n$"

SlateportShore_Text_MandaloreDefeated:
	.string "H-Hey! You're making me look\n"
	.string "bad on stream!$"

SlateportShore_Text_MandalorePostBattle:
	.string "I didn't do anything wrong!\n"
	.string "You're just a hater!$"

SlateportShore_Text_BeastIntro:
	.string "intro$"

SlateportShore_Text_BeastDefeated:
	.string "defeat$"

SlateportShore_Text_BeastPostBattle:
	.string "post$"

SlateportShore_Text_CaseyNatIntro:
	.string "intro$"

SlateportShore_Text_CaseyNatDefeated:
	.string "defeat$"

SlateportShore_Text_CaseyNatPostBattle:
	.string "post$"
