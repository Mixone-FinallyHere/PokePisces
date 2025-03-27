DetermaniteQuarry_MapScripts::
	.byte 0

DetermaniteQuarry_EventScript_Joshuone::
    trainerbattle_single TRAINER_P_JOSHUONE, DetermaniteQuarry_Text_JoshuoneIntro, DetermaniteQuarry_Text_JoshuoneDefeated
    msgbox DetermaniteQuarry_Text_JoshuonePostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarry_EventScript_Astolfo::
    trainerbattle_single TRAINER_P_ASTOLFO, DetermaniteQuarry_Text_AstolfoIntro, DetermaniteQuarry_Text_AstolfoDefeated
    msgbox DetermaniteQuarry_Text_AstolfoPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarry_EventScript_Roberts::
    trainerbattle_single TRAINER_P_ROBERTS, DetermaniteQuarry_Text_RobertsIntro, DetermaniteQuarry_Text_RobertsDefeated
    msgbox DetermaniteQuarry_Text_RobertsPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarry_EventScript_Buttercup::
    trainerbattle_single TRAINER_P_BUTTERCUP, DetermaniteQuarry_Text_ButtercupIntro, DetermaniteQuarry_Text_ButtercupDefeated
    msgbox DetermaniteQuarry_Text_ButtercupPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarry_EventScript_Gwunette::
    trainerbattle_single TRAINER_P_GWUNNETTE, DetermaniteQuarry_Text_GwunetteIntro, DetermaniteQuarry_Text_GwunetteDefeated
    msgbox DetermaniteQuarry_Text_GwunettePostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarry_EventScript_Cody::
    trainerbattle_single TRAINER_P_CODY, DetermaniteQuarry_Text_CodyIntro, DetermaniteQuarry_Text_CodyDefeated
    msgbox DetermaniteQuarry_Text_CodyPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarry_EventScript_Michiko::
    trainerbattle_single TRAINER_P_MICHIKO, DetermaniteQuarry_Text_MichikoIntro, DetermaniteQuarry_Text_MichikoDefeated
    msgbox DetermaniteQuarry_Text_MichikoPostBattle, MSGBOX_AUTOCLOSE
    end

DetermaniteQuarry_Text_JoshuoneIntro:
	.string "You may look like a rookie, but\n"
	.string "I've never made the mistake\l"
	.string "of underestimating my opponents.$"

DetermaniteQuarry_Text_JoshuoneDefeated:
	.string "Even with myself being\n"
	.string "completely prepared...?$"

DetermaniteQuarry_Text_JoshuonePostBattle:
	.string "That was a good showing.\n"
	.string "Not many can brag that they\l"
	.string "bested a well-prepared foe\l"
	.string "like me.$"

DetermaniteQuarry_Text_AstolfoIntro:
	.string "Let's skip the small talk,\n"
	.string "and get right into the action!$"

DetermaniteQuarry_Text_AstolfoDefeated:
	.string "Hmmm. Not bad!$"

DetermaniteQuarry_Text_AstolfoPostBattle:
	.string "Have a good day, trainer.\n"
	.string "It was a pleasure battling you!$"

DetermaniteQuarry_Text_RobertsIntro:
	.string "It is simply inconceivable for\n"
	.string "me to lose this match.$"

DetermaniteQuarry_Text_RobertsDefeated:
	.string "Inconceivable...!$"

DetermaniteQuarry_Text_RobertsPostBattle:
	.string "Harrumph... the more I keep that\n"
	.string "word in my lexicon, the less I\l"
	.string "remember what it even means...$"

DetermaniteQuarry_Text_ButtercupIntro:
	.string "It doesn't matter where you run,\n"
	.string "my Sworduc will track you down.$"

DetermaniteQuarry_Text_ButtercupDefeated:
	.string "I didn't say it could beat you...$"

DetermaniteQuarry_Text_ButtercupPostBattle:
	.string "Despite how intense it looks,\n"
	.string "my Sworduc is quite the softie.\l"
	.string "She's pretty laid back.$"

DetermaniteQuarry_Text_GwunetteIntro:
	.string "C-Can you please hold my\n"
	.string "hand in this dark cave?$"

DetermaniteQuarry_Text_GwunetteDefeated:
	.string "What!? I didn't h-have\n"
	.string "any ulterior motive!$"

DetermaniteQuarry_Text_GwunettePostBattle:
	.string "Do not worry, Armagatton...\n"
	.string "I will get you those you seek...$"

DetermaniteQuarry_Text_CodyIntro:
	.string "Roight, bruv. I'm thinkin'\n"
	.string "you need to go!$"

DetermaniteQuarry_Text_CodyDefeated:
	.string "Thought I could have the\n"
	.string "cave all to meself!$"

DetermaniteQuarry_Text_CodyPostBattle:
	.string "Guess I'll letcha\n"
	.string "poke your nose around.$"

DetermaniteQuarry_Text_MichikoIntro:
	.string "From the shadows, I appear!\n"
	.string "And to the shadows, you will go!$"

DetermaniteQuarry_Text_MichikoDefeated:
	.string "My team forgot the jutsu\n"
	.string "I'd taught them...$"

DetermaniteQuarry_Text_MichikoPostBattle:
	.string "I have been trying fruitlessly\n"
	.string "to make my Pokemon learn a\l"
	.string "fifth move. I have heard rumblings\l"
	.string "that Abarbinash has some hidden\l"
	.string "potential... could that be true?$"
