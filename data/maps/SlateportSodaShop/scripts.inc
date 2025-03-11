.set LOCALID_YOUTUBER1, 2
.set LOCALID_YOUTUBER2, 3
.set LOCALID_YOUTUBER3, 4
.set LOCALID_YOUTUBER4, 5

SlateportSodaShop_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SlateportSodaShop_OnLoad
	.byte 0

SlateportSodaShop_OnLoad:
	call_if_defeated TRAINER_P_BEAST, SlateportSodaShop_EventScript_RemoveYoutubers
	end

SlateportSodaShop_EventScript_RemoveYoutubers::
	removeobject LOCALID_YOUTUBER1
	removeobject LOCALID_YOUTUBER2
	removeobject LOCALID_YOUTUBER3
	removeobject LOCALID_YOUTUBER4
	setflag FLAG_TEMP_8
	return

SlateportSodaShop_EventScript_MrBeast::
    trainerbattle_single TRAINER_P_BEAST, SlateportSodaShop_Text_MrBeastIntro, SlateportSodaShop_Text_MrBeastDefeated
    msgbox SlateportSodaShop_Text_MrBeastPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportSodaShop_EventScript_KaiSenat::
    trainerbattle_single TRAINER_P_KAISENAT, SlateportSodaShop_Text_KaiSenatIntro, SlateportSodaShop_Text_KaiSenatDefeated
    msgbox SlateportSodaShop_Text_KaiSenatPostBattle, MSGBOX_AUTOCLOSE
    end

SlateportSodaShop_EventScript_SodaShopOwner::
	lock
	faceplayer
	checkitem ITEM_YELLOW_SODA
	goto_if_eq VAR_RESULT, TRUE, SlateportSodaShop_EventScript_AlreadyGaveYellowSoda
	msgbox SlateportSodaShop_Text_RunningAPromotion, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_YELLOW_SODA
	closemessage
	msgbox SlateportSodaShop_Text_NowGetLost, MSGBOX_AUTOCLOSE
	release
	end

SlateportSodaShop_EventScript_AlreadyGaveYellowSoda::
	msgbox SlateportSodaShop_Text_AlreadyGaveYellowSoda, MSGBOX_AUTOCLOSE
	release
	end

SlateportSodaShop_EventScript_YoutuberBlock1::
    msgbox SlateportSodaShop_Text_YoutuberBlock1, MSGBOX_NPC
    end

SlateportSodaShop_EventScript_YoutuberBlock2::
    msgbox SlateportSodaShop_Text_YoutuberBlock2, MSGBOX_NPC
    end

SlateportSodaShop_Text_MrBeastIntro:
	.string "intro$"

SlateportSodaShop_Text_MrBeastDefeated:
	.string "defeat$"

SlateportSodaShop_Text_MrBeastPostBattle:
	.string "post$"

SlateportSodaShop_Text_KaiSenatIntro:
	.string "intro$"

SlateportSodaShop_Text_KaiSenatDefeated:
	.string "defeat$"

SlateportSodaShop_Text_KaiSenatPostBattle:
	.string "post$"

SlateportSodaShop_Text_YoutuberBlock1:
	.string "blockin u$"

SlateportSodaShop_Text_YoutuberBlock2:
	.string "blockin u$"

SlateportSodaShop_Text_RunningAPromotion:
	.string "runnin a promo$"

SlateportSodaShop_Text_NowGetLost:
	.string "get out$"

SlateportSodaShop_Text_AlreadyGaveYellowSoda:
	.string "alr gave u yellow soda$"
