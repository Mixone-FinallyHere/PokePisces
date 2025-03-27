RustburgWharf_MapScripts::
	.byte 0

RustburgWharf_EventScript_Britney::
    trainerbattle_single TRAINER_P_BRITNEY, RustburgWharf_Text_BritneyIntro, RustburgWharf_Text_BritneyDefeated
    msgbox RustburgWharf_Text_BritneyPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Cora::
    trainerbattle_single TRAINER_P_CORA, RustburgWharf_Text_CoraIntro, RustburgWharf_Text_CoraDefeated
    msgbox RustburgWharf_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Mel::
    trainerbattle_single TRAINER_P_MEL, RustburgWharf_Text_MelIntro, RustburgWharf_Text_MelDefeated
    msgbox RustburgWharf_Text_MelPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Line::
    trainerbattle_single TRAINER_P_LINE, RustburgWharf_Text_LineIntro, RustburgWharf_Text_LineDefeated
    msgbox RustburgWharf_Text_LinePostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Hook::
    trainerbattle_single TRAINER_P_HOOK, RustburgWharf_Text_HookIntro, RustburgWharf_Text_HookDefeated
    msgbox RustburgWharf_Text_HookPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Yukari::
    trainerbattle_single TRAINER_P_YUKARI, RustburgWharf_Text_YukariIntro, RustburgWharf_Text_YukariDefeated
    msgbox RustburgWharf_Text_YukariPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Makoto::
    trainerbattle_single TRAINER_P_MAKOTO, RustburgWharf_Text_MakotoIntro, RustburgWharf_Text_MakotoDefeated
    msgbox RustburgWharf_Text_MakotoPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Inigo::
    trainerbattle_single TRAINER_P_INIGO, RustburgWharf_Text_InigoIntro, RustburgWharf_Text_InigoDefeated
    msgbox RustburgWharf_Text_InigoPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Fezzik::
    trainerbattle_single TRAINER_P_FEZZIK, RustburgWharf_Text_FezzikIntro, RustburgWharf_Text_FezzikDefeated
    msgbox RustburgWharf_Text_FezzikPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_JeanAndJackitt::
    trainerbattle_double TRAINER_P_JEAN_AND_JACKITT, RustburgWharf_Text_JeanAndJackittIntro, RustburgWharf_Text_JeanAndJackittDefeated, RustburgWharf_Text_JeanAndJackittNeedTwoMons
    msgbox RustburgWharf_Text_JeanAndJackittPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_LunaAndStar::
    trainerbattle_double TRAINER_P_LUNA_AND_STAR, RustburgWharf_Text_LunaAndStarIntro, RustburgWharf_Text_LunaAndStarDefeated, RustburgWharf_Text_LunaAndStarNeedTwoMons
    msgbox RustburgWharf_Text_LunaAndStarPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Lance::
    trainerbattle_single TRAINER_P_LANCE, RustburgWharf_Text_LanceIntro, RustburgWharf_Text_LanceDefeated
    msgbox RustburgWharf_Text_LancePostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Micycle::
    trainerbattle_single TRAINER_P_MICYCLE, RustburgWharf_Text_MicycleIntro, RustburgWharf_Text_MicycleDefeated
    msgbox RustburgWharf_Text_MicyclePostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Skipper::
    trainerbattle_single TRAINER_P_SKIPPER, RustburgWharf_Text_SkipperIntro, RustburgWharf_Text_SkipperDefeated
    msgbox RustburgWharf_Text_SkipperPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Twoffany::
    trainerbattle_single TRAINER_P_TWOFFANY, RustburgWharf_Text_TwoffanyIntro, RustburgWharf_Text_TwoffanyDefeated
    msgbox RustburgWharf_Text_TwoffanyPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Olivier::
    trainerbattle_single TRAINER_P_OLIVIER, RustburgWharf_Text_OlivierIntro, RustburgWharf_Text_OlivierDefeated
    msgbox RustburgWharf_Text_OlivierPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Tiktaalik::
    trainerbattle_single TRAINER_P_TIKTAALIK, RustburgWharf_Text_TiktaalikIntro, RustburgWharf_Text_TiktaalikDefeated
    msgbox RustburgWharf_Text_TiktaalikPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_Patrick::
    trainerbattle_single TRAINER_P_PATRICK, RustburgWharf_Text_PatrickIntro, RustburgWharf_Text_PatrickDefeated
    msgbox RustburgWharf_Text_PatrickPostBattle, MSGBOX_AUTOCLOSE
    end

RustburgWharf_EventScript_RustboroSign::
    msgbox RustburgWharf_Text_RustboroSign, MSGBOX_SIGN
    end

RustburgWharf_Text_RustboroSign:
	.string "RUSTBORO CITY GATE$"

RustburgWharf_Text_BritneyIntro:
	.string "I'm always eager to walk the piers!\n"
	.string "No fears on this pier, hee-hee!$"

RustburgWharf_Text_BritneyDefeated:
	.string "Well, that was a shock on this dock!$"

RustburgWharf_Text_BritneyPostBattle:
	.string "If only I had brought my boat.\n"
	.string "Then, I could be aghast by the mast!$"

RustburgWharf_Text_CoraIntro:
	.string "D'aagghhhh... I keep fishin' up\n"
	.string "nothin' but trash.\l"
	.string "Pollutin' punks...$"

RustburgWharf_Text_CoraDefeated:
	.string "Hey, you're trash too.\n"
	.string "For wastin' my time.\l"
	.string "...Heh. Waste.$"

RustburgWharf_Text_CoraPostBattle:
	.string "Please don't go throwin' crud\n"
	.string "in the ocean. Unless, that is,\l"
	.string "you wanna start eatin' Grimer\l"
	.string "for supper...$"

RustburgWharf_Text_MelIntro:
	.string "Even lil' minnows can put\n"
	.string "up a big fight.$"

RustburgWharf_Text_MelDefeated:
	.string "Tryna make me look small?$"

RustburgWharf_Text_MelPostBattle:
	.string "Some'a my competition always hyper-\n"
	.string "focus on the big catches.\l"
	.string "They're missin' the big picture, see.\l"
	.string "In that time, I can catch\l"
	.string "a hundred Minote. They'll end\l"
	.string "up sellin' for more in bulk.$"

RustburgWharf_Text_LineIntro:
	.string "Last one I caught was THIS big.\n"
	.string "Here, I'll show ya.$"

RustburgWharf_Text_LineDefeated:
	.string "I swear, they looked bigger\n"
	.string "when I reeled 'em in.$"

RustburgWharf_Text_LinePostBattle:
	.string "Aim big when fishin', kid.\n"
	.string "You may find yourself surprised.$"

RustburgWharf_Text_HookIntro:
	.string "Ah, you fell for my bait!\n"
	.string "Hook, line, and...!$"

RustburgWharf_Text_HookDefeated:
	.string "Hook... line... and, uhm...$"

RustburgWharf_Text_HookPostBattle:
	.string "I keep forgetting how...\n"
	.string "that phrase ends? Strange...$"

RustburgWharf_Text_YukariIntro:
	.string "I'm going to major as an actress\n"
	.string "when I go to college! Let me\l"
	.string "practice how I am going to look\l"
	.string "when defeating a foe... on you!$"

RustburgWharf_Text_YukariDefeated:
	.string "Oh, do I still look in character?\n"
	.string "Did I take my loss well?$"

RustburgWharf_Text_YukariPostBattle:
	.string "One of these days, I'll be\n"
	.string "a huge starlet! Watch for me!$"

RustburgWharf_Text_MakotoIntro:
	.string "(This guy walks up to you silently,\n"
	.string "and simply makes a “shooting gun\l"
	.string "at his head” motion.)$"

RustburgWharf_Text_MakotoDefeated:
	.string "(Makoto quiety accepted his loss.)$"

RustburgWharf_Text_MakotoPostBattle:
	.string "...$"

RustburgWharf_Text_InigoIntro:
	.string "Hello. My name... is Inigo Montoya.\n"
	.string "You defeated my father.\l"
	.string "Prepare to lose.$"

RustburgWharf_Text_InigoDefeated:
	.string "I-I was not prepared for\n"
	.string "you to win.$"

RustburgWharf_Text_InigoPostBattle:
	.string "Wait, you're saying you never\n"
	.string "defeated my father?\l"
	.string "...Then, who did...?$"

RustburgWharf_Text_FezzikIntro:
	.string "We face each other as intended. No\n"
	.string "tricks, just skill, and skill alone.$"

RustburgWharf_Text_FezzikDefeated:
	.string "I just want you to know,\n"
	.string "you're doing very well.$"

RustburgWharf_Text_FezzikPostBattle:
	.string "Did you know?\p"
	.string "I can't swim. I can only do the\n"
	.string "Pomelonian paddle.$"

RustburgWharf_Text_JeanAndJackittIntro:
	.string "JEAN: We're fit to fight at\n"
	.string "      any time!\l"
	.string "JACKITT: That's right!$"

RustburgWharf_Text_JeanAndJackittDefeated:
	.string "JEAN: Did we exert too little?\n"
	.string "      Or too much?\l"
	.string "JACKITT: Maybe it was a separate\l"
	.string "         issue...$"

RustburgWharf_Text_JeanAndJackittPostBattle:
	.string "JEAN: Pokemon come in all shapes\n"
	.string "      and sizes.\l"
	.string "JACKITT: Big or small doesn't\l"
	.string "         matter. What does is how\l"
	.string "         you utilize them!$"

RustburgWharf_Text_JeanAndJackittNeedTwoMons:
	.string "JEAN: We're too big for you!\n"
	.string "JACKITT: And you're too small for us!$"

RustburgWharf_Text_LunaAndStarIntro:
	.string "LUNA: We look towards the\n"
	.string "      constellations for guidance!\l"
	.string "STAR: And your horoscope...\l"
	.string "      it is dire!$"

RustburgWharf_Text_LunaAndStarDefeated:
	.string "LUNA: Could the meanings of the\n"
	.string "      constellations led us astray?\l"
	.string "STAR: Hmmm... perhaps, we\l"
	.string "      interpreted them wrong.$"

RustburgWharf_Text_LunaAndStarPostBattle:
	.string "STAR: To become truly connected\n"
	.string "      with the cosmos, you should\l"
	.string "      consider visiting Etheor Falls.\l"
	.string "LUNA: We got our Minior from there.$"

RustburgWharf_Text_LunaAndStarNeedTwoMons:
	.string "LUNA: The stars do not align\n"
	.string "      for us to fight you now!$"

RustburgWharf_Text_LanceIntro:
	.string "I'm the fastest Cyclist around!\n"
	.string "Think you can keep up?$"

RustburgWharf_Text_LanceDefeated:
	.string "You took me for a tour de force!$"

RustburgWharf_Text_LancePostBattle:
	.string "W-What? You're saying I am\n"
	.string "doping? By using a Choice Scarf?\l"
	.string "Puh-lease! Everyone does that\l"
	.string "these days.$"

RustburgWharf_Text_MicycleIntro:
	.string "I wonder where my real\n"
	.string "family is today...$"

RustburgWharf_Text_MicycleDefeated:
	.string "The mountains... they call me.$"

RustburgWharf_Text_MicyclePostBattle:
	.string "I was separated from my birth family\n"
	.string "at an early age, and adopted by\l"
	.string "a family of prestiged bikers.\p"
	.string "All I know about my birth family,\n"
	.string "is that they were hikers...$"

RustburgWharf_Text_SkipperIntro:
	.string "Bugs may be teensy-tiny, but\n"
	.string "they pack a punch FAR greater\l"
	.string "than their stature! Let's ROLL!$"

RustburgWharf_Text_SkipperDefeated:
	.string "You packed a punch even greater\n"
	.string "than theirs!$"

RustburgWharf_Text_SkipperPostBattle:
	.string "Some people believe the Bug type\n"
	.string "to be the worst of them all...\l"
	.string "I will vow to prove them wrong!$"

RustburgWharf_Text_TwoffanyIntro:
	.string "Aren't you excited about what\n"
	.string "today's adventures could entail?$"

RustburgWharf_Text_TwoffanyDefeated:
	.string "Even if I lose, that doesn't mean\n"
	.string "I have to stop looking forward\l"
	.string "to tomorrow.$"

RustburgWharf_Text_TwoffanyPostBattle:
	.string "Every new day comes with something\n"
	.string "to look forward to! So, keep\l"
	.string "going forward!$"

RustburgWharf_Text_OlivierIntro:
	.string "Like this... like that.\n"
	.string "Like this, like that...$"

RustburgWharf_Text_OlivierDefeated:
	.string "I like it, I like it!$"

RustburgWharf_Text_OlivierPostBattle:
	.string "This is this, that is that.$"

RustburgWharf_Text_TiktaalikIntro:
	.string "I just feel like having a\n"
	.string "nice stroll!$"

RustburgWharf_Text_TiktaalikDefeated:
	.string "A walk in the park!$"

RustburgWharf_Text_TiktaalikPostBattle:
	.string "Nothing feels better than the\n"
	.string "grass beneath my feet, am I right?$"

RustburgWharf_Text_PatrickIntro:
	.string "Oi, oi! You hear the news?\p"
	.string "Rustboro's been seein' some gang\n"
	.string "activity recently! So they may\l"
	.string "close down the gate 'till they sort\l"
	.string "out the problem.\p"
	.string "You can read all about it in my\n"
	.string "newspaper! ...And you'll ALSO\l"
	.string "be reading about how I OWNED you!$"

RustburgWharf_Text_PatrickDefeated:
	.string "Whelp, scratch that last topic...$"

RustburgWharf_Text_PatrickPostBattle:
	.string "If the City does end up\n"
	.string "temporarily closin', I hear there's\l"
	.string "a secret way in not a lotta folks\l"
	.string "try... in the tunnels.$"
