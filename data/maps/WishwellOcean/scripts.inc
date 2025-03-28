WishwellOcean_MapScripts::
	.byte 0

WishwellOcean_EventScript_Xerxes::
    trainerbattle_single TRAINER_P_XERXES, WishwellOcean_Text_XerxesIntro, WishwellOcean_Text_XerxesDefeated
    msgbox WishwellOcean_Text_XerxesPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Yvette::
    trainerbattle_single TRAINER_P_YVETTE, WishwellOcean_Text_YvetteIntro, WishwellOcean_Text_YvetteDefeated
    msgbox WishwellOcean_Text_YvettePostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_PiAndSees::
    trainerbattle_double TRAINER_P_PI_AND_SEES, WishwellOcean_Text_PiAndSeesIntro, WishwellOcean_Text_PiAndSeesDefeated, WishwellOcean_Text_PiAndSeesNeedTwoMons
    msgbox WishwellOcean_Text_PiAndSeesPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_KuAndMori::
    trainerbattle_double TRAINER_P_KU_AND_MORI, WishwellOcean_Text_KuAndMoriIntro, WishwellOcean_Text_KuAndMoriDefeated, WishwellOcean_Text_KuAndMoriNeedTwoMons
    msgbox WishwellOcean_Text_KuAndMoriPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Persephone::
    trainerbattle_single TRAINER_P_PERSEPHONE, WishwellOcean_Text_PersephoneIntro, WishwellOcean_Text_PersephoneDefeated
    msgbox WishwellOcean_Text_PersephonePostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Xavier::
    trainerbattle_single TRAINER_P_XAVIER, WishwellOcean_Text_XavierIntro, WishwellOcean_Text_XavierDefeated
    msgbox WishwellOcean_Text_XavierPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Nafi::
    trainerbattle_single TRAINER_P_NAFI, WishwellOcean_Text_NafiIntro, WishwellOcean_Text_NafiDefeated
    msgbox WishwellOcean_Text_NafiPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Madeline::
    trainerbattle_single TRAINER_P_MADELINE, WishwellOcean_Text_MadelineIntro, WishwellOcean_Text_MadelineDefeated
    msgbox WishwellOcean_Text_MadelinePostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Enrique::
    trainerbattle_single TRAINER_P_ENRIQUE, WishwellOcean_Text_EnriqueIntro, WishwellOcean_Text_EnriqueDefeated
    msgbox WishwellOcean_Text_EnriquePostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Maria::
    trainerbattle_single TRAINER_P_MARIA, WishwellOcean_Text_MariaIntro, WishwellOcean_Text_MariaDefeated
    msgbox WishwellOcean_Text_MariaPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Fern::
    trainerbattle_single TRAINER_P_FERN, WishwellOcean_Text_FernIntro, WishwellOcean_Text_FernDefeated
    msgbox WishwellOcean_Text_FernPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Dudley::
    trainerbattle_single TRAINER_P_DUDLEY, WishwellOcean_Text_DudleyIntro, WishwellOcean_Text_DudleyDefeated
    msgbox WishwellOcean_Text_DudleyPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Gustavo::
    trainerbattle_single TRAINER_P_GUSTAVO, WishwellOcean_Text_GustavoIntro, WishwellOcean_Text_GustavoDefeated
    msgbox WishwellOcean_Text_GustavoPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_EventScript_Neil::
    trainerbattle_single TRAINER_P_NEIL, WishwellOcean_Text_NeilIntro, WishwellOcean_Text_NeilDefeated
    msgbox WishwellOcean_Text_NeilPostBattle, MSGBOX_AUTOCLOSE
    end

WishwellOcean_Text_XerxesIntro:
	.string "Who needs luck when you have\n"
	.string "PURE ARCANE AFFINITY!?$"

WishwellOcean_Text_XerxesDefeated:
	.string "Maybe... I c-coulda used some luck!$"

WishwellOcean_Text_XerxesPostBattle:
	.string "I'll make a wish here in these\n"
	.string "waters, that my next Pokemon battle\l"
	.string "ends in success for me.$"

WishwellOcean_Text_YvetteIntro:
	.string "I can summon the northern lights\n"
	.string "at will... and I will do so for\l"
	.string "this battle! Come, gods of\l"
	.string "the northern winds! Aid me\l"
	.string "in this upcoming brawl!$"

WishwellOcean_Text_YvetteDefeated:
	.string "The northern lights did so appear...\n"
	.string "though that does not aid me\l"
	.string "very much in battle, I see...$"

WishwellOcean_Text_YvettePostBattle:
	.string "Aurora borealis... at this time\n"
	.string "of year... localized entirely\l"
	.string "within this route...$"

WishwellOcean_Text_PiAndSeesIntro:
	.string "(This Lovey-Dovey couple are\n"
	.string "kissing. Get a room!)$"

WishwellOcean_Text_PiAndSeesDefeated:
	.string "PI: Have you ever experienced\n"
	.string "    a true love's kiss?\l"
	.string "SEES: Your worldview completely\l"
	.string "      changes after that.$"

WishwellOcean_Text_PiAndSeesPostBattle:
	.string "(They went back to the kissing.)$"

WishwellOcean_Text_PiAndSeesNeedTwoMons:
	.string "(This Lovey-Dovey couple are\n"
	.string "kissing. Get a room!)$"

WishwellOcean_Text_KuAndMoriIntro:
	.string "KU: We whisper our orders\n"
	.string "to each other in battle.\l"
	.string "MORI: So our opponents can't hear!$"

WishwellOcean_Text_KuAndMoriDefeated:
	.string "KU: AW, GOODY GUMDROPS!\n"
	.string "MORI: HON! How about you calm down?\l"
	.string "That was harsh language...$"

WishwellOcean_Text_KuAndMoriPostBattle:
	.string "(They're whispering “I Love You”\n"
	.string "to each other over and over.)$"

WishwellOcean_Text_KuAndMoriNeedTwoMons:
	.string "KU: What's that? We can't hear you!\n"
	.string "MORI: You're too quiet to fight us.$"

WishwellOcean_Text_PersephoneIntro:
	.string "I just surfaced from a diving\n"
	.string "expedition down real deep!\l"
	.string "Here's some Pokemon I found!$"

WishwellOcean_Text_PersephoneDefeated:
	.string "I took a dive...$"

WishwellOcean_Text_PersephonePostBattle:
	.string "There are some Pokemon that\n"
	.string "can only be found very deep\l"
	.string "underwater! Try lookin' for them!$"

WishwellOcean_Text_XavierIntro:
	.string "Eh. Too much water.$"

WishwellOcean_Text_XavierDefeated:
	.string "I'd rate that battle about\n"
	.string "a seven point eight outta ten.$"

WishwellOcean_Text_XavierPostBattle:
	.string "I'm drowning! Help!\p"
	.string "...Just kidding! Hah!$"

WishwellOcean_Text_NafiIntro:
	.string "My top secret plan to freeze the\n"
	.string "oceans of Hoenn is almost a go!\p"
	.string "...What, you want to stop me!?$"

WishwellOcean_Text_NafiDefeated:
	.string "FOILED!$"

WishwellOcean_Text_NafiPostBattle:
	.string "Admittedly... I haven't figured out\n"
	.string "yet how to get all the salt out\l"
	.string "of the water, first...$"

WishwellOcean_Text_MadelineIntro:
	.string "Just breathe. You can do this.$"

WishwellOcean_Text_MadelineDefeated:
	.string "That was as difficult as\n"
	.string "climbing a mountain...!$"

WishwellOcean_Text_MadelinePostBattle:
	.string "I once hiked for 3 days alone in\n"
	.string "the Zotpyre Mountain Range area.\l"
	.string "Long journeys like that tend to\l"
	.string "have you find yourself.$"

WishwellOcean_Text_EnriqueIntro:
	.string "Where oh where do the ships I\n"
	.string "see here end up?$"

WishwellOcean_Text_EnriqueDefeated:
	.string "It's a mystery at sea!$"

WishwellOcean_Text_EnriquePostBattle:
	.string "Well, I guess I COULD just look\n"
	.string "up the boats' routes, but that\l"
	.string "ruins the fun.$"

WishwellOcean_Text_MariaIntro:
	.string "There are so many fascinating\n"
	.string "Pokemon in this world. Let me\l"
	.string "show you some of my favorites.$"

WishwellOcean_Text_MariaDefeated:
	.string "Did you see any you\n"
	.string "particularly liked?$"

WishwellOcean_Text_MariaPostBattle:
	.string "Dudunspars comes in multiple\n"
	.string "variants, you see. I was lucky\l"
	.string "enough to get a three-segmented one!$"

WishwellOcean_Text_FernIntro:
	.string "Those who visit this route do so\n"
	.string "to make their wishes, and hope\l"
	.string "that they come true.\p"
	.string "I wish... that I shall win this!$"

WishwellOcean_Text_FernDefeated:
	.string "Mayhaps I did not specify\n"
	.string "clearly enough.$"

WishwellOcean_Text_FernPostBattle:
	.string "My next wish shall be...\n"
	.string "for eternal, unending happiness.$"

WishwellOcean_Text_DudleyIntro:
	.string "Ah, marvelous! I was JUST\n"
	.string "looking for someone to shine\l"
	.string "my shoes...$"

WishwellOcean_Text_DudleyDefeated:
	.string "The audacity!$"

WishwellOcean_Text_DudleyPostBattle:
	.string "And to think, I was to give\n"
	.string "you the privelege to touch my\l"
	.string "beloved footwear!$"

WishwellOcean_Text_GustavoIntro:
	.string "Was once baker... did not work out.\n"
	.string "Now, I choose to grill...\l"
	.string "and into fire you go.$"

WishwellOcean_Text_GustavoDefeated:
	.string "Battle also... did not work out.$"

WishwellOcean_Text_GustavoPostBattle:
	.string "Will try and learn life lesson.$"

WishwellOcean_Text_NeilIntro:
	.string "Ain't hard to catch some runt\n"
	.string "like you faffin' about the beaches.$"

WishwellOcean_Text_NeilDefeated:
	.string "Now, are ya gonna be buyin'\n"
	.string "anything? If not, get outta here!$"

WishwellOcean_Text_NeilPostBattle:
	.string "Always got window shoppin' eyes,\n"
	.string "but no window shoppin' money, eh?$"
