SweltornPalaceOutside_MapScripts::
	.byte 0

SweltornPalaceOutside_EventScript_Cy::
    trainerbattle_single TRAINER_P_CY, SweltornPalaceOutside_Text_CyIntro, SweltornPalaceOutside_Text_CyDefeated
    msgbox SweltornPalaceOutside_Text_CyPostBattle, MSGBOX_AUTOCLOSE
    end

SweltornPalaceOutside_EventScript_WendyAndGale::
    trainerbattle_double TRAINER_P_WENDY_AND_GALE, SweltornPalaceOutside_Text_WendyAndGaleIntro, SweltornPalaceOutside_Text_WendyAndGaleDefeated, SweltornPalaceOutside_Text_WendyAndGaleNeedTwoMons
    msgbox SweltornPalaceOutside_Text_WendyAndGalePostBattle, MSGBOX_AUTOCLOSE
    end

SweltornPalaceOutside_EventScript_TrainingMonk::
	lock
	goto_if_defeated TRAINER_P_KAKU, SweltornPalaceOutside_EventScript_GaveFocusSash
	msgbox SweltornPalaceOutside_Text_UpForAToughBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SweltornPalaceOutside_EventScript_Kaku
	msgbox SweltornPalaceOutside_Text_IMayBeTooTough, MSGBOX_AUTOCLOSE
	release
	end

SweltornPalaceOutside_EventScript_Kaku::
    trainerbattle_single TRAINER_P_KAKU, SweltornPalaceOutside_Text_KakuIntro, SweltornPalaceOutside_Text_KakuDefeated, SweltornPalaceOutside_EventScript_KakuBeaten
    release
    end

SweltornPalaceOutside_EventScript_KakuBeaten::
	msgbox SweltornPalaceOutside_Text_AVeryThrillingMatch, MSGBOX_DEFAULT
	giveitem ITEM_FOCUS_SASH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

SweltornPalaceOutside_EventScript_GaveFocusSash::
	msgbox SweltornPalaceOutside_Text_MustContinueTraining, MSGBOX_AUTOCLOSE
	release
	end

SweltornPalaceOutside_Text_UpForAToughBattle:
	.string ".  .  .\p"
	.string ".  .  .\p"
	.string ".  . . . ..I have indeed\n"
	.string "recognized that you are standing\l"
	.string "there, young one.\p"
	.string "I have been meditating in the\n"
	.string "searing desert sun to bring\l"
	.string "my consciousness to higher\l"
	.string "levels of being.\p"
	.string "You have chosen to interrupt\n"
	.string "my task. Is this because\l"
	.string "you desire a battle with me?\p"
	.string "I must warn you, I have never\n"
	.string "once been slain. And I train\l"
	.string "only one solitary Pokemon...\p"
	.string "Does your resolve\n"
	.string "still stand resolutely?$"

SweltornPalaceOutside_Text_IMayBeTooTough:
	.string "Then I ask you to leave me\n"
	.string "to my meditation.$"

SweltornPalaceOutside_Text_AVeryThrillingMatch:
	.string "Through that battle, I could easily\n"
	.string "sense your honed focus.\p"
	.string "That talent can potentially\n"
	.string "go even further beyond.\l"
	.string "Please, accept this before you\l"
	.string "take your leave.$"

SweltornPalaceOutside_Text_MustContinueTraining:
	.string "I must continue my training...\n"
	.string "only then, can enlightenment\l"
	.string "be reached...$"

SweltornPalaceOutside_Text_CyIntro:
	.string "intro$"

SweltornPalaceOutside_Text_CyDefeated:
	.string "defeat$"

SweltornPalaceOutside_Text_CyPostBattle:
	.string "post$"

SweltornPalaceOutside_Text_WendyAndGaleIntro:
	.string "intro$"

SweltornPalaceOutside_Text_WendyAndGaleDefeated:
	.string "defeat$"

SweltornPalaceOutside_Text_WendyAndGalePostBattle:
	.string "post$"

SweltornPalaceOutside_Text_WendyAndGaleNeedTwoMons:
	.string "need 2 dood$"

SweltornPalaceOutside_Text_KakuIntro:
	.string "This shall be one for\n"
	.string "the ages...\p"
	.string "Basked in the sun's glow,\n"
	.string "we commence our duel!$"

SweltornPalaceOutside_Text_KakuDefeated:
	.string "I am much impressed, young one.\n"
	.string "Not many can command a team\l"
	.string "as dominant as your own.$"

SweltornPalaceOutside_Text_KakuPostBattle:
	.string "post$"
