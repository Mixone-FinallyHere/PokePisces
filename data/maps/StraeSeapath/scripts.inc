StraeSeapath_MapScripts::
	.byte 0

StraeSeapath_EventScript_Mary::
    trainerbattle_single TRAINER_P_MARY, StraeSeapath_Text_MaryIntro, StraeSeapath_Text_MaryDefeated
    msgbox StraeSeapath_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_Jose::
    trainerbattle_single TRAINER_P_JOSE, StraeSeapath_Text_JoseIntro, StraeSeapath_Text_JoseDefeated
    msgbox StraeSeapath_Text_JosePostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_Daria::
    trainerbattle_single TRAINER_P_DARIA, StraeSeapath_Text_DariaIntro, StraeSeapath_Text_DariaDefeated
    msgbox StraeSeapath_Text_DariaPostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_Jean::
    trainerbattle_single TRAINER_P_JEAN, StraeSeapath_Text_JeanIntro, StraeSeapath_Text_JeanDefeated
    msgbox StraeSeapath_Text_JeanPostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_Lynn::
    trainerbattle_single TRAINER_P_LYNN, StraeSeapath_Text_LynnIntro, StraeSeapath_Text_LynnDefeated
    msgbox StraeSeapath_Text_LynnPostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_Aiofe::
    trainerbattle_single TRAINER_P_AIOFE, StraeSeapath_Text_AiofeIntro, StraeSeapath_Text_AiofeDefeated
    msgbox StraeSeapath_Text_AiofePostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_DickAndJane::
    trainerbattle_double TRAINER_P_DICK_AND_JANE, StraeSeapath_Text_DickAndJaneIntro, StraeSeapath_Text_DickAndJaneDefeated, StraeSeapath_Text_DickAndJaneNeedTwoMons
    msgbox StraeSeapath_Text_DickAndJanePostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_RosieAndPalms::
    trainerbattle_double TRAINER_P_ROSIE_AND_PALMS, StraeSeapath_Text_RosieAndPalmsIntro, StraeSeapath_Text_RosieAndPalmsDefeated, StraeSeapath_Text_RosieAndPalmsNeedTwoMons
    msgbox StraeSeapath_Text_RosieAndPalmsPostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_Maomao::
    trainerbattle_single TRAINER_P_MAOMAO, StraeSeapath_Text_MaomaoIntro, StraeSeapath_Text_MaomaoDefeated
    msgbox StraeSeapath_Text_MaomaoPostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_EventScript_Barnaby::
    trainerbattle_single TRAINER_P_BARNABY, StraeSeapath_Text_BarnabyIntro, StraeSeapath_Text_BarnabyDefeated
    msgbox StraeSeapath_Text_BarnabyPostBattle, MSGBOX_AUTOCLOSE
    end

StraeSeapath_Text_MaryIntro:
	.string "Into the briny depths with you!$"

StraeSeapath_Text_MaryDefeated:
	.string "Into foam, I wash away...$"

StraeSeapath_Text_MaryPostBattle:
	.string "The gilded rocks of the Seapath\n"
	.string "shake me to my core.$"

StraeSeapath_Text_JoseIntro:
	.string "Chaw, man, someone's in my way!$"

StraeSeapath_Text_JoseDefeated:
	.string "Crushed!$"

StraeSeapath_Text_JosePostBattle:
	.string "Gotta go with the flow, man...$"

StraeSeapath_Text_DariaIntro:
	.string "Don't you try and take the gold\n"
	.string "from these stones, sweet pea!$"

StraeSeapath_Text_DariaDefeated:
	.string "You didn't let me finish\n"
	.string "my advice.$"

StraeSeapath_Text_DariaPostBattle:
	.string "I was going to tell you that\n"
	.string "the golde you may see here is\l"
	.string "actually mostly pyrite, sweet pea.\l"
	.string "Fool's gold, they call it.\l"
	.string "It's rather worthless.$"

StraeSeapath_Text_JeanIntro:
	.string "Hmph! I'd say there's a 50-50\n"
	.string "chance you lose.\l"
	.string "Wanna bet on it?$"

StraeSeapath_Text_JeanDefeated:
	.string "You're lucky I'm a betting man.\n$"

StraeSeapath_Text_JeanPostBattle:
	.string "Don't get too into gambling.\n"
	.string "You may end up like, shudder...\l"
	.string "a Choice Specs user...$"

StraeSeapath_Text_LynnIntro:
	.string "I raised these Pokemon from eggs!\n$"

StraeSeapath_Text_LynnDefeated:
	.string "You crack me up...$"

StraeSeapath_Text_LynnPostBattle:
	.string "Do you know how to tell Wannegg\n"
	.string "apart from regular Eggs? They're\l"
	.string "ever-so-slightly less round!$"

StraeSeapath_Text_AiofeIntro:
	.string "Some child asked me why I, a\n"
	.string "Dragon Caller, lack a cellular\l"
	.string "device. How crude! I am in\l"
	.string "no need of such technology!$"

StraeSeapath_Text_AiofeDefeated:
	.string "If you proclaim I\n"
	.string "“phoned that one in”, I will\l"
	.string "personally kick your shins.$"

StraeSeapath_Text_AiofePostBattle:
	.string "Calling a Pokemon for assistance\n"
	.string "by using a telephone...\l"
	.string "it would be absurdly inconvenient.$"

StraeSeapath_Text_DickAndJaneIntro:
	.string "DICK: Let's get in sync for this!\n"
	.string "JANE: Sure thing!$"

StraeSeapath_Text_DickAndJaneDefeated:
	.string "DICK: Oh, I meant strategically,\n"
	.string "      not emotionally!\l"
	.string "JANE: My bad...$"

StraeSeapath_Text_DickAndJanePostBattle:
	.string "DICK: There's an angry couple on\n"
	.string "      the shores just north of here.\l"
	.string "      Our love sensor SCREAMS that\l"
	.string "      they really do care for each\l"
	.string "      other deeply.\l"
	.string "JANE: They may look like they hate\l"
	.string "      each other, but they can't\l"
	.string "      fool us! I can see the longing\l"
	.string "      in their eyes...$"

StraeSeapath_Text_DickAndJaneNeedTwoMons:
	.string "(They're too busy being publicly\n"
	.string "affectionate to notice you.)$"

StraeSeapath_Text_RosieAndPalmsIntro:
	.string "ROSIE: A date with YOU never\n"
	.string "       ends well.\l"
	.string "PALMS: Then just let me go it alone!$"

StraeSeapath_Text_RosieAndPalmsDefeated:
	.string "ROSIE: My Helping Hand didn't help?\n"
	.string "PALMS: Friggin' typical...$"

StraeSeapath_Text_RosieAndPalmsPostBattle:
	.string "ROSIE: You fool! You need to\n"
	.string "       go on the offensive!\l"
	.string "PALMS: I find YOU offensive!$"

StraeSeapath_Text_RosieAndPalmsNeedTwoMons:
	.string "(They're too busy being publicly\n"
	.string "non-affectionate to notice you.)$"

StraeSeapath_Text_MaomaoIntro:
	.string "There is naught a more elegant\n"
	.string "Pokemon than Solasu...$"

StraeSeapath_Text_MaomaoDefeated:
	.string "Perhaps I needed to show\n"
	.string "more grit and fury...$"

StraeSeapath_Text_MaomaoPostBattle:
	.string "I must go ask for another blessing\n"
	.string "from the maidens of Zotpyre...$"

StraeSeapath_Text_BarnabyIntro:
	.string "There ain't a more tough sun\n"
	.string "of a gun than Orrocast...$"

StraeSeapath_Text_BarnabyDefeated:
	.string "Huh. Maybe I just gotta\n"
	.string "show more composure...$"

StraeSeapath_Text_BarnabyPostBattle:
	.string "Almost time for me to get on\n"
	.string "back to Pacifidlog to cash in\l"
	.string "my daily haul.$"
