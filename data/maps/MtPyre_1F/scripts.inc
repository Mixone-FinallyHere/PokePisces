.set LOCALID_BARRELFISHER, 7

MtPyre_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MtPyre_1F_OnLoad
	.byte 0

MtPyre_1F_OnLoad:
	call MtPyre_1F_EventScript_RemoveBarrelFisher
	end

MtPyre_1F_EventScript_RemoveBarrelFisher::
	removeobject LOCALID_BARRELFISHER
	setflag FLAG_TEMP_1E
	return

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_Pearl::
    trainerbattle_single TRAINER_P_PEARL, MtPyre_1F_Text_PearlIntro, MtPyre_1F_Text_PearlDefeated
    msgbox MtPyre_1F_Text_PearlPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_1F_EventScript_Neko::
    trainerbattle_single TRAINER_P_NEKO, MtPyre_1F_Text_NekoIntro, MtPyre_1F_Text_NekoDefeated
    msgbox MtPyre_1F_Text_NekoPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_1F_EventScript_Ayumu::
    trainerbattle_single TRAINER_P_AYUMU, MtPyre_1F_Text_AyumuIntro, MtPyre_1F_Text_AyumuDefeated
    msgbox MtPyre_1F_Text_AyumuPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_1F_EventScript_Reimu::
    trainerbattle_single TRAINER_P_REIMU, MtPyre_1F_Text_ReimuIntro, MtPyre_1F_Text_ReimuDefeated
    msgbox MtPyre_1F_Text_ReimuPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_1F_EventScript_Miko::
    trainerbattle_single TRAINER_P_MIKO, MtPyre_1F_Text_MikoIntro, MtPyre_1F_Text_MikoDefeated
    msgbox MtPyre_1F_Text_MikoPostBattle, MSGBOX_AUTOCLOSE
    end

MtPyre_1F_EventScript_LostKin::
	lock
	goto_if_set FLAG_ZOTPYRE_PSYCHICS, MtPyre_1F_EventScript_Teleporter
	faceplayer
	setflag FLAG_ZOTPYRE_PSYCHICS
	msgbox MtPyre_1F_Text_IReuniteWithMyKin, MSGBOX_DEFAULT
	goto MtPyre_1F_EventScript_Teleporter
	release
	end

MtPyre_1F_EventScript_Teleporter::
	lock
	faceplayer
	msgbox MtPyre_1F_Text_WouldYouLikeToWarp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MtPyre_1F_EventScript_WarpToCenter
	msgbox MtPyre_1F_Text_MaybeAnotherTime, MSGBOX_AUTOCLOSE
	release
	end

MtPyre_1F_EventScript_WarpToCenter::
	warp MAP_LILYCOVE_CITY_POKEMON_CENTER_2F, 12, 3
	release
	end

MtPyre_1F_EventScript_SpookBarrelCheck::
    lock
	checkitem ITEM_TM_POUNCE
	goto_if_eq VAR_RESULT, TRUE, MtPyre_1F_EventScript_SpookBarrel
	setvar VAR_TEMP_1, 1
	release
	end

MtPyre_1F_EventScript_SpookBarrel::
	clearflag FLAG_TEMP_1E
	addobject LOCALID_BARRELFISHER
	delay 4
	applymovement LOCALID_BARRELFISHER, MtPyre_1F_Movement_JumpFromBarrel
	waitmovement 0
	checkitem ITEM_TM_SPOOK
	goto_if_eq VAR_RESULT, TRUE, MtPyre_1F_EventScript_GaveSpook
	msgbox MtPyre_1F_Text_GotYou, MSGBOX_DEFAULT
	giveitem ITEM_TM_SPOOK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_TEMP_1, 1
	removeobject LOCALID_BARRELFISHER
	setflag FLAG_TEMP_1E
	applymovement LOCALID_BARRELFISHER, MtPyre_1F_Movement_JumpIntoBarrel
	waitmovement 0
	release
	end

MtPyre_1F_Movement_JumpFromBarrel:
	set_visible
	jump_left
	face_left
	step_end

MtPyre_1F_Movement_JumpIntoBarrel:
	jump_right
	face_right
	set_invisible
	step_end

MtPyre_1F_EventScript_GaveSpook::
    msgbox MtPyre_1F_Text_AlreadyGotYou, MSGBOX_AUTOCLOSE
	setvar VAR_TEMP_1, 1
	setflag FLAG_RECEIVED_TM_POUNCE
	applymovement LOCALID_BARRELFISHER, MtPyre_1F_Movement_JumpIntoBarrel
	waitmovement 0
    release
    end

MtPyre_1F_Text_GotYou:
	.string "BOOGA BOOGA BOOGA!!!\p"
	.string "HAH! I gotcha AGAIN!\n"
	.string "Weren't expectin' the ol' barrel\l"
	.string "fisher in a place like this, huh?\p"
	.string "Hey! Don't be glarin' at me!\n"
	.string "I'll supply ya with another\l"
	.string "TM. This time, for Spook!\p"
	.string "Learning the art of the scare\n"
	.string "may help you avoid me in the future!\p"
	.string "....or maybe not, hehehe!$"

MtPyre_1F_Text_AlreadyGotYou:
	.string "BOOGA...boo...ga...\p"
	.string "Listen bud. We gotta stop\n"
	.string "meeting like this...$"

MtPyre_1F_Text_WouldYouLikeToWarp:
	.string "wanna warp$"

MtPyre_1F_Text_MaybeAnotherTime:
	.string "maybe nexttime$"

MtPyre_1F_Text_IReuniteWithMyKin:
	.string "psychic connection activate$"

MtPyre_1F_Text_PearlIntro:
	.string "...Leave this place...$"

MtPyre_1F_Text_PearlDefeated:
	.string "You do not belong...!$"

MtPyre_1F_Text_PearlPostBattle:
	.string "...$"

MtPyre_1F_Text_NekoIntro:
	.string "I'll exorcise you!$"

MtPyre_1F_Text_NekoDefeated:
	.string "Ah, there are no spirits\n"
	.string "within you, child.$"

MtPyre_1F_Text_NekoPostBattle:
	.string "Beware the possessed Mediums...$"

MtPyre_1F_Text_AyumuIntro:
	.string "I shall cleanse you of miasma!$"

MtPyre_1F_Text_AyumuDefeated:
	.string "Oh, it seems you've\n"
	.string "been blessed already.$"

MtPyre_1F_Text_AyumuPostBattle:
	.string "A purifying spell has been placed on\n"
	.string "you already.\p"
	.string "You probably have met one of my own\n"
	.string "along the way here.$"

MtPyre_1F_Text_ReimuIntro:
	.string "Stay back!$"

MtPyre_1F_Text_ReimuDefeated:
	.string "Okay, the barrier has been set up.$"

MtPyre_1F_Text_ReimuPostBattle:
	.string "We do daily maintenance on the\n"
	.string "spiritual barrier protecting the town.\p"
	.string "It wards off impure spirits with evil\l"
	.string "intent while allowing in good spirits\l"
	.string "that bless the shrine.$"

MtPyre_1F_Text_MikoIntro:
	.string "Please do not interrupt the ritual.$"

MtPyre_1F_Text_MikoDefeated:
	.string "You may now pass.$"

MtPyre_1F_Text_MikoPostBattle:
	.string "Right now evil spirits are running\n"
	.string "rampant and have been overwhelming our\l"
	.string "local Mediums, but don't worry, most of\l"
	.string "the time they'll be fine... eventually.$"

MtPyre_1F_Text_TakeThisForYourOwnGood:
	.string "All sorts of beings wander the\n"
	.string "slopes of Zotpyre…\p"
	.string "There is no telling what may happen.\n"
	.string "Take this. It's for your own good.$"

MtPyre_1F_Text_ExplainCleanseTag:
	.string "Have a Pokémon hold that\n"
	.string "Cleanse Tag.\p"
	.string "It will help ward off evil.$"
