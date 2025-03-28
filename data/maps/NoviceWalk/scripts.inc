NoviceWalk_MapScripts::
	.byte 0

NoviceWalk_EventScript_Joey::
    trainerbattle_single TRAINER_P_JOEY, NoviceWalk_Text_JoeyIntro, NoviceWalk_Text_JoeyDefeated
    msgbox NoviceWalk_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Josephine::
    trainerbattle_single TRAINER_P_JOSEPHINE, NoviceWalk_Text_JosephineIntro, NoviceWalk_Text_JosephineDefeated
    msgbox NoviceWalk_Text_JosephinePostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Lenny::
    trainerbattle_single TRAINER_P_LENNY, NoviceWalk_Text_LennyIntro, NoviceWalk_Text_LennyDefeated
    msgbox NoviceWalk_Text_LennyPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Bridget::
    trainerbattle_single TRAINER_P_BRIDGET, NoviceWalk_Text_BridgetIntro, NoviceWalk_Text_BridgetDefeated
    msgbox NoviceWalk_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Darwin::
    trainerbattle_single TRAINER_P_DARWIN, NoviceWalk_Text_DarwinIntro, NoviceWalk_Text_DarwinDefeated
    msgbox NoviceWalk_Text_DarwinPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Gumball::
    trainerbattle_single TRAINER_P_GUMBALL, NoviceWalk_Text_GumballIntro, NoviceWalk_Text_GumballDefeated
    msgbox NoviceWalk_Text_GumballPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Jimmy::
    trainerbattle_single TRAINER_P_JIMMY_2, NoviceWalk_Text_JimmyIntro, NoviceWalk_Text_JimmyDefeated
    msgbox NoviceWalk_Text_JimmyPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Timmy::
    trainerbattle_single TRAINER_P_TIMMY_2, NoviceWalk_Text_TimmyIntro, NoviceWalk_Text_TimmyDefeated
    msgbox NoviceWalk_Text_TimmyPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Joe::
    trainerbattle_single TRAINER_P_JOE, NoviceWalk_Text_JoeIntro, NoviceWalk_Text_JoeDefeated
    msgbox NoviceWalk_Text_JoePostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Sasha::
    trainerbattle_single TRAINER_P_SASHA, NoviceWalk_Text_SashaIntro, NoviceWalk_Text_SashaDefeated
    msgbox NoviceWalk_Text_SashaPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Elle::
    trainerbattle_single TRAINER_P_ELLE, NoviceWalk_Text_ElleIntro, NoviceWalk_Text_ElleDefeated
    msgbox NoviceWalk_Text_EllePostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_Tay::
    trainerbattle_single TRAINER_P_TAY, NoviceWalk_Text_TayIntro, NoviceWalk_Text_TayDefeated
    msgbox NoviceWalk_Text_TayPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_EthanAndKai::
    trainerbattle_double TRAINER_P_ETHAN_AND_KAI, NoviceWalk_Text_EthanAndKaiIntro, NoviceWalk_Text_EthanAndKaiDefeated, NoviceWalk_Text_EthanAndKaiNeedTwoMons
    msgbox NoviceWalk_Text_EthanAndKaiPostBattle, MSGBOX_AUTOCLOSE
    end

NoviceWalk_EventScript_NWSign::
    msgbox NoviceWalk_Text_NWSign, MSGBOX_SIGN
    end

NoviceWalk_Text_NWSign:
	.string "NOVICE'S WALK\n"
	.string "A place for new trainers to\l"
	.string "get their footing!\p"
	.string "Head NORTH for OLDALE TOWN,\n"
	.string "SOUTH for LITTLEROOT TOWN$"

NoviceWalk_Text_JoeyIntro:
	.string "ALL of my Pokemon are in the\n"
	.string "top percentage of their species!\l"
	.string "I think I have you beat!$"

NoviceWalk_Text_JoeyDefeated:
	.string "Oh... I'm out of Pokemon\n"
	.string "that can fight.$"

NoviceWalk_Text_JoeyPostBattle:
	.string "I'll become the one percent OF\n"
	.string "the one percent! Just you wait!$"

NoviceWalk_Text_JosephineIntro:
	.string "I like jackets! They're comfy\n"
	.string "and easy to wear!$"

NoviceWalk_Text_JosephineDefeated:
	.string "Are you stronger because you...\n"
	.string "don't wear a jacket?$"

NoviceWalk_Text_JosephinePostBattle:
	.string "I'll come back with a flowery,\n"
	.string "colorful shirt like you!\l"
	.string "Then, maybe I can win more.$"

NoviceWalk_Text_LennyIntro:
	.string "I like to pretend I'm a\n"
	.string "grub that lives in the soil!$"

NoviceWalk_Text_LennyDefeated:
	.string "(He's writhing uselessly.)$"

NoviceWalk_Text_LennyPostBattle:
	.string "I'm merely in my larval stage\n"
	.string "right now. Come back when I'm done\l"
	.string "pupating, and you'll get a REAL\l"
	.string "kick in the nose...$"

NoviceWalk_Text_BridgetIntro:
	.string "I just obtained these Pokemon\n"
	.string "30 minutes ago! Let's try 'em\l"
	.string "out in my first battle!$"

NoviceWalk_Text_BridgetDefeated:
	.string "Awww! Well, I just gotta\n"
	.string "learn from it!$"

NoviceWalk_Text_BridgetPostBattle:
	.string "I got these Pokemon from my Mama!\n"
	.string "She was training to be a Grass\l"
	.string "type Gym Leader!$"

NoviceWalk_Text_DarwinIntro:
	.string "Darwin always wins.$"

NoviceWalk_Text_DarwinDefeated:
	.string "I won.\p"
	.string "(The kid is showing you a picture\n"
	.string "of the faces of four bird Pokemon.)\p"
	.string "(You don't know what this means.)$"

NoviceWalk_Text_DarwinPostBattle:
	.string "Darwin... ALWAYS. Wins.$"

NoviceWalk_Text_GumballIntro:
	.string "I'll show you the amazing world\n"
	.string "of Dragon types!$"

NoviceWalk_Text_GumballDefeated:
	.string "Y-You chewed them up! And\n"
	.string "s-spat them out!$"

NoviceWalk_Text_GumballPostBattle:
	.string "Garzilla, are you ok, bud...?$"

NoviceWalk_Text_JimmyIntro:
	.string "It's the Jimmy-Timmy Power Hour!\n"
	.string "Prepare to be annihilated!$"

NoviceWalk_Text_JimmyDefeated:
	.string "From a Power Hour to a\n"
	.string "Cower Hour...!$"

NoviceWalk_Text_JimmyPostBattle:
	.string "History repeated itself, I see...\n"
	.string "maybe Timmy and I still have one\l"
	.string "more sequel in us?$"

NoviceWalk_Text_TimmyIntro:
	.string "We remember you from way back!\n"
	.string "At Flotshore Trail!\p"
	.string "You wiped the floor with us then,\n"
	.string "but we've been training together\l"
	.string "for a long time to eventually\l"
	.string "take you out!$"

NoviceWalk_Text_TimmyDefeated:
	.string "I wish everything was back to normal!$"

NoviceWalk_Text_TimmyPostBattle:
	.string "Your Pokemon are really magical!\n"
	.string "We were really not gonna stand\l"
	.string "a chance.$"

NoviceWalk_Text_JoeIntro:
	.string "You really gotta show some spunk\n"
	.string "to make it in the big leagues!\p"
	.string "I'm ready to get there, are you!?$"

NoviceWalk_Text_JoeDefeated:
	.string "YEAH! THAT'S what I'm talking about!$"

NoviceWalk_Text_JoePostBattle:
	.string "Keep that energy going all the\n"
	.string "way to the end!$"

NoviceWalk_Text_SashaIntro:
	.string "We've locked eyes. Time to\n"
	.string "lay it all out on the battlefield.$"

NoviceWalk_Text_SashaDefeated:
	.string "I still have a ways to go...\n"
	.string "but my head will be held high\l"
	.string "through it all.$"

NoviceWalk_Text_SashaPostBattle:
	.string "You need guts and determination\n"
	.string "to see your personal challenges\l"
	.string "through to their conclusion.$"

NoviceWalk_Text_ElleIntro:
	.string "Heya! It's Elle! And I'm about\n"
	.string "to make you take the L!$"

NoviceWalk_Text_ElleDefeated:
	.string "Oh, you turned it into a W\n"
	.string "along the way?$"

NoviceWalk_Text_EllePostBattle:
	.string "Let every win fuel you, and let\n"
	.string "every loss be something to learn\l"
	.string "from for the future!$"

NoviceWalk_Text_TayIntro:
	.string "Have you been using held items\n"
	.string "to the best of their caliber?\l"
	.string "I know I try to. Lets see\l"
	.string "if practice pays off.$"

NoviceWalk_Text_TayDefeated:
	.string "You weathered everything I had\n"
	.string "up my sleeves...$"

NoviceWalk_Text_TayPostBattle:
	.string "Make sure your Pokemon have the\n"
	.string "held item most suited for them.\l"
	.string "Don't ever just leave that slot\l"
	.string "open. A good item can make or\l"
	.string "break a Pokemon's usefulness.$"

NoviceWalk_Text_EthanAndKaiIntro:
	.string "ETHAN: I am Kai's strongest soldier!\n"
	.string "KAI: And I am his princess!$"

NoviceWalk_Text_EthanAndKaiDefeated:
	.string "ETHAN: I'll protect you until\n"
	.string "the end, Kai...\l"
	.string "KAI: I'd want nothing more...$"

NoviceWalk_Text_EthanAndKaiPostBattle:
	.string "KAI: Ethan, if a Karodoraug\n"
	.string "kidnapped me and took me\l"
	.string "to a castle, would you come\l"
	.string "save me?\l"
	.string "ETHAN: Without question.$"

NoviceWalk_Text_EthanAndKaiNeedTwoMons:
	.string "ETHAN: I can easily defend\n"
	.string "my love against one Pokemon!$"
