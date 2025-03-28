SeasideCasinoVIPLounges_MapScripts::
	.byte 0

SeasideCasinoVIPLounges_EventScript_Akagi::
    trainerbattle_single TRAINER_P_AKAGI, SeasideCasinoVIPLounges_Text_AkagiIntro, SeasideCasinoVIPLounges_Text_AkagiDefeated
    msgbox SeasideCasinoVIPLounges_Text_AkagiPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoVIPLounges_EventScript_Moneywell::
    trainerbattle_single TRAINER_P_MONEYWELL, SeasideCasinoVIPLounges_Text_MoneywellIntro, SeasideCasinoVIPLounges_Text_MoneywellDefeated
    msgbox SeasideCasinoVIPLounges_Text_MoneywellPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoVIPLounges_EventScript_Dante::
    trainerbattle_single TRAINER_P_DANTE, SeasideCasinoVIPLounges_Text_DanteIntro, SeasideCasinoVIPLounges_Text_DanteDefeated
    msgbox SeasideCasinoVIPLounges_Text_DantePostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoVIPLounges_EventScript_Shinjiro::
    trainerbattle_single TRAINER_P_SHINJIRO, SeasideCasinoVIPLounges_Text_ShinjiroIntro, SeasideCasinoVIPLounges_Text_ShinjiroDefeated
    msgbox SeasideCasinoVIPLounges_Text_ShinjiroPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoVIPLounges_EventScript_Skyler::
    trainerbattle_single TRAINER_P_SKYLER, SeasideCasinoVIPLounges_Text_SkylerIntro, SeasideCasinoVIPLounges_Text_SkylerDefeated
    msgbox SeasideCasinoVIPLounges_Text_SkylerPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoVIPLounges_EventScript_Walter::
    trainerbattle_single TRAINER_P_WALTER, SeasideCasinoVIPLounges_Text_WalterIntro, SeasideCasinoVIPLounges_Text_WalterDefeated
    msgbox SeasideCasinoVIPLounges_Text_WalterPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoVIPLounges_EventScript_Knuckles::
    trainerbattle_single TRAINER_P_KNUCKLES, SeasideCasinoVIPLounges_Text_KnucklesIntro, SeasideCasinoVIPLounges_Text_KnucklesDefeated
    msgbox SeasideCasinoVIPLounges_Text_KnucklesPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoVIPLounges_EventScript_Fingers::
    trainerbattle_single TRAINER_P_FINGERS, SeasideCasinoVIPLounges_Text_FingersIntro, SeasideCasinoVIPLounges_Text_FingersDefeated
    msgbox SeasideCasinoVIPLounges_Text_FingersPostBattle, MSGBOX_AUTOCLOSE
    end

SeasideCasinoVIPLounges_Text_AkagiIntro:
	.string "Want to play some Blackjack?\n$"

SeasideCasinoVIPLounges_Text_AkagiDefeated:
	.string "You could have just said no!\n$"

SeasideCasinoVIPLounges_Text_AkagiPostBattle:
	.string "Maybe I should just stick to\n"
	.string "Go Faered...$"

SeasideCasinoVIPLounges_Text_MoneywellIntro:
	.string "I've written a big book on how\n"
	.string "to strike it rich, child!\p"
	.string "Step one... is to smother\n"
	.string "weaklings like you, and take\l"
	.string "the winnings!$"

SeasideCasinoVIPLounges_Text_MoneywellDefeated:
	.string "Ah, that's why step one failed.\n"
	.string "You were... no weakling.$"

SeasideCasinoVIPLounges_Text_MoneywellPostBattle:
	.string "Business IS ruthlessness, child.\n"
	.string "Throw away friends, family, love.\l"
	.string "None compare to the joy of\l"
	.string "cold, hard cash!$"

SeasideCasinoVIPLounges_Text_DanteIntro:
	.string "I've been hiding in here to escape\n"
	.string "from that Hunter... it feels\l"
	.string "like my clock is ticking.\p"
	.string "...He didn't send you to snatch\n"
	.string "me, did he!?$"

SeasideCasinoVIPLounges_Text_DanteDefeated:
	.string "This is some kind of personal hell.$"

SeasideCasinoVIPLounges_Text_DantePostBattle:
	.string "I really don't want to talk about\n"
	.string "it further... if Vergil did send\l"
	.string "you, please, just tell him\l"
	.string "that I died.$"

SeasideCasinoVIPLounges_Text_ShinjiroIntro:
	.string "Want to press your luck?\n"
	.string "No whammies?$"

SeasideCasinoVIPLounges_Text_ShinjiroDefeated:
	.string "Ah, quite an unlucky streak\n"
	.string "I've found myself on...$"

SeasideCasinoVIPLounges_Text_ShinjiroPostBattle:
	.string "Luck doesn't favor anyone, but\n"
	.string "you can manipulate your odds.\l"
	.string "That... is why the house\l"
	.string "ALWAYS wins.$"

SeasideCasinoVIPLounges_Text_SkylerIntro:
	.string "We dance together!$"

SeasideCasinoVIPLounges_Text_SkylerDefeated:
	.string "We lost together...$"

SeasideCasinoVIPLounges_Text_SkylerPostBattle:
	.string "When two Pokemon have the Dancer\n"
	.string "ability, they can dance together\l"
	.string "all the time!$"

SeasideCasinoVIPLounges_Text_WalterIntro:
	.string "I AM the dancer.\n"
	.string "I... am the one who swings.$"

SeasideCasinoVIPLounges_Text_WalterDefeated:
	.string "A Waltzer opens his door and gets\n"
	.string "beaten in a Pokemon battle,\l"
	.string "and you think that of ME!?$"

SeasideCasinoVIPLounges_Text_WalterPostBattle:
	.string "Dancing is hard, but I like it.\n"
	.string "...I'm good at it.$"

SeasideCasinoVIPLounges_Text_KnucklesIntro:
	.string "You're about to see why they\n"
	.string "call me Knuckles...!$"

SeasideCasinoVIPLounges_Text_KnucklesDefeated:
	.string "Eh... yeah, I punch a lot\n"
	.string "better than I command Pokemon.$"

SeasideCasinoVIPLounges_Text_KnucklesPostBattle:
	.string "Unlike Fingers, I don't chuckle.\n"
	.string "I'd rather flex my knuckles.$"

SeasideCasinoVIPLounges_Text_FingersIntro:
	.string "Know why err'body call me Fingers?$"

SeasideCasinoVIPLounges_Text_FingersDefeated:
	.string "I don't know either!$"

SeasideCasinoVIPLounges_Text_FingersPostBattle:
	.string "One day in grade school, eh,\n"
	.string "my teacher called me eh, “kid\l"
	.string "named Fingers”, n' the bullyin'\l"
	.string "man, it was non-STOP!$"
