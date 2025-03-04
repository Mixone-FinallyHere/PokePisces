.set LOCALID_P_MAN, 11
.set LOCALID_P_MAN2, 9
.set LOCALID_P_MAN3, 12
.set LOCALID_BARD, 8
.set LOCALID_TRADER, 10
.set LOCALID_DRAKE, 7
.set LOCALID_ARCHIE, 5
.set LOCALID_STERN, 6
.set LOCALID_NUE, 2
.set LOCALID_ROADBLOCKER_1, 16
.set LOCALID_ROADBLOCKER_2, 17
.set LOCALID_ROADBLOCKER_3, 18
.set LOCALID_ROADBLOCKER_4, 19

SeaMauville_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SeaMauville_OnLoad
	.byte 0

SeaMauville_OnLoad:
	setflag FLAG_VISITED_SLATEPORT_CITY
	call_if_lt VAR_OLD_GUYS_STATE, 9, SeaMauville_EventScript_SetTraderGfx
	call_if_eq VAR_OLD_GUYS_STATE, 9, SeaMauville_EventScript_SetBardGfx
	call_if_eq VAR_OLD_GUYS_STATE, 11, SeaMauville_EventScript_SetTraderGfx
	call_if_eq VAR_OLD_GUYS_STATE, 12, SeaMauville_EventScript_SetTraderGfx
	call_if_eq VAR_OLD_GUYS_STATE, 13, SeaMauville_EventScript_SetTraderGfx
	call_if_eq VAR_OLD_GUYS_STATE, 14, SeaMauville_EventScript_SetTraderGfx
	call_if_eq VAR_OLD_GUYS_STATE, 15, SeaMauville_EventScript_SetTraderGfx
	call_if_lt VAR_OLD_GUYS_STATE, 9, SeaMauville_EventScript_RemoveSeafarers
	call_if_gt VAR_OLD_GUYS_STATE, 9, SeaMauville_EventScript_RemoveSeafarers
	call SeaMauville_EventScript_RemoveKizuna
	call SeaMauville_EventScript_RemoveNue
	call_if_eq VAR_OLD_GUYS_STATE, 9, SeaMauville_EventScript_RemoveNob
	call_if_eq VAR_OLD_GUYS_STATE, 10, SeaMauville_EventScript_RemoveNob
	call_if_ge VAR_OLD_GUYS_STATE, 16, SeaMauville_EventScript_RemoveNob
	call_if_gt VAR_WALLY_QUEST_STATE, 2, SeaMauville_EventScript_RemoveRoadblock
	end

SeaMauville_EventScript_SetTraderGfx::
	setvar VAR_BARD_COLOR, MAUVILLE_MAN_TRADER
	special SetMauvilleOldManObjEventGfx
	return

SeaMauville_EventScript_SetBardGfx::
	setvar VAR_BARD_COLOR, MAUVILLE_MAN_BARD
	special SetMauvilleOldManObjEventGfx
	return

SeaMauville_EventScript_RemoveSeafarers::
	removeobject LOCALID_ARCHIE
	setflag FLAG_TEMP_14
	removeobject LOCALID_STERN
	setflag FLAG_TEMP_15
	removeobject LOCALID_DRAKE
	setflag FLAG_TEMP_16
	removeobject LOCALID_BARD
	setflag FLAG_TEMP_17
	removeobject LOCALID_P_MAN2
	setflag FLAG_TEMP_18
	return

SeaMauville_EventScript_RemoveKizuna::
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	removeobject LOCALID_P_MAN3
	setflag FLAG_TEMP_19
	return

SeaMauville_EventScript_RemoveNue::
	removeobject LOCALID_NUE
	setflag FLAG_TEMP_13
	return

SeaMauville_EventScript_RemoveNob::
	removeobject LOCALID_TRADER
	setflag FLAG_TEMP_12
	return	

SeaMauville_EventScript_RemoveRoadblock::
	removeobject LOCALID_ROADBLOCKER_1
	setflag FLAG_TEMP_A
	removeobject LOCALID_ROADBLOCKER_2
	setflag FLAG_TEMP_B
	removeobject LOCALID_ROADBLOCKER_3
	setflag FLAG_TEMP_C
	removeobject LOCALID_ROADBLOCKER_4
	setflag FLAG_TEMP_D
	return

SeaMauville_EventScript_BrineyFastTravel::
	lock
	faceplayer
	clearflag FLAG_BRINEY_MIDGAME_VISIT
	goto_if_eq VAR_OLD_GUYS_STATE, 9, SeaMauville_EventScript_BrineyGoToSouthernIsland
	speakername SeaMauville_Text_NameBriney
	msgbox SeaMauville_Text_WantToVoyage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SeaMauville_EventScript_WarpToTidal
	msgbox SeaMauville_Text_IllBeHere, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

SeaMauville_EventScript_WarpToTidal::
	msgbox SeaMauville_Text_BonVoyage, MSGBOX_DEFAULT
	speakername NULL
	warp MAP_SS_TIDAL_MID_TERIORS, 33, 4
	release
	end

SeaMauville_EventScript_BrineyGoToSouthernIsland::
	speakername SeaMauville_Text_NameBriney
	msgbox SeaMauville_Text_ReadyForSouthernIsland, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SeaMauville_EventScript_WarpToSouthernIsland
	msgbox SeaMauville_Text_IllBeHere, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

SeaMauville_EventScript_WarpToSouthernIsland::
	setvar VAR_OLD_GUYS_STATE, 10
	msgbox SeaMauville_Text_BonVoyage, MSGBOX_DEFAULT
	speakername NULL
	warp MAP_SOUTHERN_ISLAND, 5, 3
	release
	end

SeaMauville_EventScript_DrakeIdle::
	speakername SeaMauville_Text_NameDrake
	msgbox SeaMauville_Text_DrakeIdle, MSGBOX_NPC
	end

SeaMauville_EventScript_ArchieIdle::
	speakername SeaMauville_Text_NameArchie
	msgbox SeaMauville_Text_ArchieIdle, MSGBOX_NPC
	end

SeaMauville_EventScript_SternIdle::
	speakername SeaMauville_Text_NameStern
	msgbox SeaMauville_Text_SternIdle, MSGBOX_NPC
	end

SeaMauville_EventScript_KizunaIdle::
	speakername SeaMauville_Text_NameKizuna
	msgbox SeaMauville_Text_KizunaIdle, MSGBOX_NPC
	end

SeaMauville_EventScript_DockIdle::
	speakername SeaMauville_Text_NameDock
	msgbox SeaMauville_Text_DockIdle, MSGBOX_NPC
	end

SeaMauville_EventScript_MustSail::
	lock
	msgbox SeaMauville_Text_MustSail, MSGBOX_AUTOCLOSE 
	applymovement OBJ_EVENT_ID_PLAYER, SeaMauville_Movement_WalkRight
	waitmovement 0
	release
	end

SeaMauville_Movement_WalkRight:
	walk_right
	step_end

SeaMauville_EventScript_PostIslandUpperTrigger::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, SeaMauville_Movement_MoveToRight
	goto SeaMauville_EventScript_KizunaPostIsland
	release
	end

SeaMauville_EventScript_KizunaPostIsland::
	lock
	clearflag FLAG_TEMP_19
	addobject LOCALID_P_MAN3
	playse SE_DOOR
	waitse
	applymovement LOCALID_P_MAN3, SeaMauville_Movement_KizunaGetOffShip
	waitmovement 0
	speakername SeaMauville_Text_NameKizuna
	msgbox SeaMauville_Text_AboutDock, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_P_MAN3, SeaMauville_Movement_KizunaGoToMarket
	waitmovement 0
	setvar VAR_OLD_GUYS_STATE, 12
	removeobject LOCALID_P_MAN3
	setflag FLAG_TEMP_19
	release
	end

SeaMauville_Movement_MoveToRight:
	walk_right
	face_down
	step_end

SeaMauville_Movement_KizunaGetOffShip:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

SeaMauville_Movement_KizunaGoToMarket:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SeaMauville_EventScript_Nob::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TEA, SeaMauville_EventScript_NobRetire
	goto_if_lt VAR_OLD_GUYS_STATE, 12, SeaMauville_EventScript_NobPreDock
	goto_if_eq VAR_OLD_GUYS_STATE, 13, SeaMauville_EventScript_NobStartedQuest
	goto_if_eq VAR_OLD_GUYS_STATE, 14, SeaMauville_EventScript_NobStartedQuest
	goto_if_eq VAR_OLD_GUYS_STATE, 15, SeaMauville_EventScript_NobStartedQuest
	msgbox SeaMauville_Text_TraderGreeting, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OLD_GUYS_STATE, 13
	clearflag FLAG_TEMP_11
	addobject LOCALID_P_MAN
	delay 8
	applymovement LOCALID_P_MAN, SeaMauville_Movement_KizunaGreetNob
	waitmovement 0
	speakername SeaMauville_Text_NameKizuna
	msgbox SeaMauville_Text_HesSpeakingJapanese, MSGBOX_DEFAULT
	speakername SeaMauville_Text_NameNob
	msgbox SeaMauville_Text_IWantThis, MSGBOX_DEFAULT
	speakername SeaMauville_Text_NameKizuna
	msgbox SeaMauville_Text_LetsTryAndFigureItOut, MSGBOX_AUTOCLOSE
	setflag FLAG_TEMP_11
	release
	end

SeaMauville_Movement_KizunaGreetNob:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

SeaMauville_EventScript_NobPreDock::
	msgbox SeaMauville_Text_NobPreDock, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_NobStartedQuest::
	speakername SeaMauville_Text_NameNob
	msgbox SeaMauville_Text_NobStartedQuest, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_NobRetire::
	speakername SeaMauville_Text_NameNob
	msgbox SeaMauville_Text_IWillTradeForThatItem, MSGBOX_DEFAULT
	removeitem ITEM_TEA, 1
	giveitem ITEM_BASEMENT_KEY
	speakername SeaMauville_Text_NameNob
	msgbox SeaMauville_Text_ThanksForYourTime, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_TEMP_11
	addobject LOCALID_P_MAN
	delay 8
	applymovement LOCALID_P_MAN, SeaMauville_Movement_KizunaGreetNob
	waitmovement 0
	speakername SeaMauville_Text_NameKizuna
	msgbox SeaMauville_Text_YouAllSet, MSGBOX_DEFAULT
	fadenewbgm MUS_VERDANTURF
	speakername SeaMauville_Text_NameNob
	msgbox SeaMauville_Text_YesItsMyTimeToGo, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SeaMauville_Movement_PlayerMoveOutOfWay
	waitmovement 0
	playse SE_M_MEGA_KICK
	applymovement LOCALID_P_MAN, SeaMauville_Movement_KizunaAbsorbNob
	waitmovement 0
	removeobject LOCALID_TRADER
	setflag FLAG_TEMP_12
	setvar VAR_OLD_GUYS_STATE, 16
	playse SE_M_FAINT_ATTACK
	waitse
	fadenewbgm MUS_NONE
	applymovement LOCALID_P_MAN, SeaMauville_Movement_KizunaFormUp
	waitmovement 0
	speakername SeaMauville_Text_NameKizuna
	msgbox SeaMauville_Text_OneMoreToGo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_P_MAN, SeaMauville_Movement_KizunaWalkAway
	waitmovement 0
	fadenewbgm MUS_SLATEPORT
	delay 16
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	release
	end

SeaMauville_Movement_PlayerMoveOutOfWay:
	walk_right
	delay_4
	face_left
	step_end

SeaMauville_Movement_KizunaAbsorbNob:
	walk_fast_right
	walk_slow_up
	step_end

SeaMauville_Movement_KizunaFormUp:
	walk_slow_down
	delay_8
	face_right
	step_end

SeaMauville_Movement_KizunaWalkAway:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

SeaMauville_EventScript_KizunaIdle2::
	speakername SeaMauville_Text_NameKizuna
	msgbox SeaMauville_Text_KizunaIdle2, MSGBOX_NPC
	end

SeaMauville_EventScript_SuitcaseInterceptor::
	lock
	faceplayer
	goto_if_eq VAR_OLD_GUYS_STATE, 13, SeaMauville_EventScript_GoGetThatSuitcase
	goto_if_eq VAR_OLD_GUYS_STATE, 14, SeaMauville_EventScript_SuitcaseInstructions
	goto_if_eq VAR_OLD_GUYS_STATE, 15, SeaMauville_EventScript_TradeSuitcaseForTeachyTV
	goto_if_gt VAR_OLD_GUYS_STATE, 15, SeaMauville_EventScript_ThanksForSuitcase
	msgbox SeaMauville_Text_ImUpToNoGood, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_GoGetThatSuitcase::
	setvar VAR_OLD_GUYS_STATE, 14
	msgbox SeaMauville_Text_GoGetMeASuitcase, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_SuitcaseInstructions::
	msgbox SeaMauville_Text_SuitcaseInstructions, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_TradeSuitcaseForTeachyTV::
	msgbox SeaMauville_Text_YouGotTheStuff, MSGBOX_DEFAULT
	removeitem ITEM_DEVON_PARTS, 1
	giveitem ITEM_TEACHY_TV
	msgbox SeaMauville_Text_ThanksForSuitcase, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_ThanksForSuitcase::
	msgbox SeaMauville_Text_ThanksForSuitcase, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_AmbushTriggerTop::
	lock
	msgbox SeaMauville_Text_TimeToIntercept, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SeaMauville_Movement_AmbushTriggerTop
	waitmovement 0
	goto SeaMauville_EventScript_AmbushNue
	release
	end

SeaMauville_Movement_AmbushTriggerTop:
	walk_down
	walk_down
	face_up
	step_end

SeaMauville_EventScript_AmbushTriggerMiddle::
	lock
	msgbox SeaMauville_Text_TimeToIntercept, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SeaMauville_Movement_AmbushTriggerMiddle
	waitmovement 0
	goto SeaMauville_EventScript_AmbushNue
	release
	end

SeaMauville_Movement_AmbushTriggerMiddle:
	walk_down
	face_up
	step_end

SeaMauville_EventScript_AmbushTriggerBottom::
	lock
	msgbox SeaMauville_Text_TimeToIntercept, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SeaMauville_Movement_AmbushTriggerBottom
	waitmovement 0
	goto SeaMauville_EventScript_AmbushNue
	release
	end

SeaMauville_Movement_AmbushTriggerBottom:
	face_up
	step_end

SeaMauville_EventScript_AmbushNue::
	delay 32
	clearflag FLAG_TEMP_13
	addobject LOCALID_NUE
	applymovement LOCALID_NUE, SeaMauville_Movement_NueWalkingAlong
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, SeaMauville_Movement_PlayerBlockNue
	applymovement LOCALID_NUE, SeaMauville_Movement_NueWalkingIntoPlayer
	waitmovement 0
	playse SE_WALL_HIT
	waitse
	delay 16
	playse SE_PIN
	applymovement LOCALID_NUE, SeaMauville_Movement_NueSurprised
	msgbox SeaMauville_Text_NueIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_NUE, SeaMauville_Text_NueDefeated
	goto SeaMauville_EventScript_TakeNueSuitcase
	release
	end

SeaMauville_Movement_NueWalkingAlong:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SeaMauville_Movement_PlayerBlockNue:
	walk_fast_up
	face_right
	step_end

SeaMauville_Movement_NueWalkingIntoPlayer:
	walk_left
	step_end

SeaMauville_Movement_NueSurprised:
	emote_exclamation_mark
	step_end

SeaMauville_EventScript_TakeNueSuitcase::
	msgbox SeaMauville_Text_NuePostBattle, MSGBOX_DEFAULT
	giveitem ITEM_DEVON_PARTS
	closemessage
	delay 8
	applymovement LOCALID_NUE, SeaMauville_Movement_NueRunAway
	waitmovement 0
	removeobject LOCALID_NUE
	setflag FLAG_TEMP_13
	setvar VAR_OLD_GUYS_STATE, 15
	release
	end

SeaMauville_Movement_NueRunAway:
	walk_faster_up
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	step_end

SeaMauville_EventScript_CreamOwner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_GOLD_TEETH, SeaMauville_EventScript_CreamOwnerPostTeeth
	goto_if_set FLAG_RECEIVED_POKE_FLUTE, SeaMauville_EventScript_TradeFlute
	msgbox SeaMauville_Text_MyCreamHasTroubleWakingUp, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_TradeFlute::
	msgbox SeaMauville_Text_TradeFlute, MSGBOX_DEFAULT
	removeitem ITEM_POKE_FLUTE, 1
	giveitem ITEM_GOLD_TEETH
	setflag FLAG_RECEIVED_GOLD_TEETH
	closemessage
	release
	end

SeaMauville_EventScript_CreamOwnerPostTeeth::
	msgbox SeaMauville_Text_FluteWorked, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_CreamTeeth::
	goto_if_set FLAG_RECEIVED_GOLD_TEETH, SeaMauville_EventScript_CreamFlute
	msgbox SeaMauville_Text_CreamTeeth, MSGBOX_NPC
	end

SeaMauville_EventScript_CreamFlute::
	msgbox SeaMauville_Text_CreamFlute, MSGBOX_NPC
	end

SeaMauville_EventScript_Gary::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TEA, SeaMauville_EventScript_GaryPostBattle
	goto_if_set FLAG_RECEIVED_GOLD_TEETH, SeaMauville_EventScript_GetTeeth
	msgbox SeaMauville_Text_SellingTeaMauville, MSGBOX_AUTOCLOSE
	release
	end

SeaMauville_EventScript_GetTeeth::
	msgbox SeaMauville_Text_ThoseTeethWillDoNicely, MSGBOX_DEFAULT
	closemessage
	playse SE_DING_DONG
	waitse
	msgbox SeaMauville_Text_SorryLetMeTakeThis, MSGBOX_DEFAULT
	msgbox SeaMauville_Text_GaryIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_GARY, SeaMauville_Text_GaryDefeated
	goto SeaMauville_EventScript_GiveTea
	release
	end

SeaMauville_EventScript_GiveTea::
	msgbox SeaMauville_Text_OkayFineTakeTea, MSGBOX_DEFAULT
	removeitem ITEM_GOLD_TEETH, 1
	giveitem ITEM_TEA
	setflag FLAG_RECEIVED_TEA
	closemessage
	release
	end

SeaMauville_EventScript_GaryPostBattle::
    msgbox SeaMauville_Text_GaryPostBattle, MSGBOX_AUTOCLOSE
	release
    end

SeaMauville_Text_NameBriney:
	.string "Cpt. Briney$"

SeaMauville_Text_NameKizuna:
	.string "Kizuna$"

SeaMauville_Text_NameArchie:
	.string "Archie$"

SeaMauville_Text_NameDrake:
	.string "Drake$"

SeaMauville_Text_NameStern:
	.string "Cpt. Stern$"

SeaMauville_Text_NameDock:
	.string "Dock$"

SeaMauville_Text_NameNob:
	.string "Nob$"

SeaMauville_Text_NueIntro:
	.string "W-What? You want to battle?\n"
	.string "Well, I'm kind of carrying\l"
	.string "important cargo. Can't it wai-$"

SeaMauville_Text_NueDefeated:
	.string "Agh! Why so aggressive?$"

SeaMauville_Text_NuePostBattle:
	.string "Look, you want the briefcase?\n"
	.string "Just... take it and leave me alone!$"

SeaMauville_Text_GaryIntro:
	.string "It was YOU who stole that\n"
	.string "briefcase from my colleague!\p"
	.string "I see the guilt in your eyes.\n"
	.string "Have at thee!!$"

SeaMauville_Text_GaryDefeated:
	.string "Now I see how Nue lost...!$"

SeaMauville_Text_GaryPostBattle:
	.string "Step rrrright up! Try out\n"
	.string "the homely, once forgotten taste\l"
	.string "of Tea Mauville!\p"
	.string "(The coward is ignoring you.)$"

SeaMauville_Text_WantToVoyage:
	.string "Ahoy there {PLAYER}!\p"
	.string "The Tidal is docked and\n"
	.string "itching for another voyage.\p"
	.string "Will you be joining us?$"

SeaMauville_Text_IllBeHere:
	.string "You're always welcome aboard!\n"
	.string "Have a good one.$"

SeaMauville_Text_BonVoyage:
	.string "About time to haul anchor, then!$"

SeaMauville_Text_ReadyForSouthernIsland:
	.string "Ahoy there {PLAYER}!\n"
	.string "Are you ready to disembark\l"
	.string "for Southern Island?$"

SeaMauville_Text_DrakeIdle:
	.string "I am always one to love the ocean!\n"
	.string "Especially with a spectacular\l"
	.string "crew like today.$"

SeaMauville_Text_KizunaIdle:
	.string "We sure do keep getting sucked\n"
	.string "into odd situations, huh...\p"
	.string "Whatever. Let's enjoy ourselves\n"
	.string "on the trip.$"

SeaMauville_Text_ArchieIdle:
	.string "Shame Briney won't let me take\n"
	.string "the helm, fufufu... I would get\l"
	.string "us there hyper-fast! Briney\l"
	.string "plays it too safe. Where's\l"
	.string "the fun in that?$"

SeaMauville_Text_SternIdle:
	.string "I would hope this voyage doesn't\n"
	.string "take us too terribly long.\l"
	.string "I wouldn't want to miss anything\l"
	.string "vital at the Museum.$"

SeaMauville_Text_DockIdle:
	.string "Ah, it's like the good ol' days.\n"
	.string "I can't help but smile!$"

SeaMauville_Text_MustSail:
	.string "(Shouldn't back out of this one.)$"

SeaMauville_Text_AboutDock:
	.string "This journey just gets stranger\n"
	.string "and stranger...\p"
	.string "Seems like people will see me\n"
	.string "as Dock. Or, well, maybe those\l"
	.string "men saw me as Dock. And... anyone\l"
	.string "who was close to Rydel would see\l"
	.string "me as Rydel. And so on.\p"
	.string "When I... absorbed, Dock,\n"
	.string "I got his memories, like the others.\l"
	.string "He would meet up with the last\l"
	.string "remaining Old Guy we haven't\l"
	.string "heard of in name yet.\l"
	.string "A man named Nob, also known as\l"
	.string "The Trader. He's actually\l"
	.string "in town... we might have even talked\l"
	.string "to him before.\p"
	.string "He should be in the Sea Mauville\n"
	.string "Market. I'll meet you there.$"

SeaMauville_Text_TraderGreeting:
	.string "{JPN}アイ アム ザー トレーダー\n"
	.string "{JPN}マイ ネーム イズ ノブ$"

SeaMauville_Text_HesSpeakingJapanese:
	.string "A-Ah, hello there, Nob.\n"
	.string "Do you... recognize me?\l"
	.string "As Dock? Or maybe as Giddy?\p"
	.string "I can somewhat understand\n"
	.string "Japanese, so I'll try and translate\l"
	.string "for us, {PLAYER}.$"

SeaMauville_Text_IWantThis:
	.string "{JPN}イフ ユー ウッド ライク ター トレード\n"
	.string "{JPN}アイ ウィル ギブ ユー アー キー\l"
	.string "{JPN}イン エクスチェーンジ フォー ティー$"

SeaMauville_Text_LetsTryAndFigureItOut:
	.string "So, uh, I believe he wants\n"
	.string "to trade us some sort of key?\l"
	.string "But he would like some Tea\l"
	.string "in return. I... I'm sorry,\l"
	.string "I don't quite know what kind of\l"
	.string "tea he wants.\p"
	.string "Maybe we should ask around the\n"
	.string "market and see if we can get\l"
	.string "what The Trader wants.$"

SeaMauville_Text_NobPreDock:
	.string "{JPN}マイ アポロジズ\n"
	.string "{JPN}カレントリー セティング アップ ヒア$"

SeaMauville_Text_NobStartedQuest:
	.string "{JPN}アイ ウィル ギブ ユー アー キー\n"
	.string "{JPN}イン エクスチェーンジ フォー ティー$"

SeaMauville_Text_IWillTradeForThatItem:
	.string "{JPN}ブリリアント！\n"
	.string "{JPN}ザー ティー スメルズ デライトフル$"

SeaMauville_Text_ThanksForYourTime:
	.string "{JPN}アイ バリュー ザット ユー トゥック\n"
	.string "{JPN}ザー タイム フォー マイ レクェスト$"

SeaMauville_Text_YouAllSet:
	.string "So, you guys have made the\n"
	.string "trade, right? That's awesome.\p"
	.string "...Ah. My body is reacting again...\n"
	.string "without even hearing your words,\l"
	.string "Nob, I think I know what you want.\l"
	.string "Is it your time to go as well?$"

SeaMauville_Text_YesItsMyTimeToGo:
	.string "{JPN}イェス⋯\n"
	.string "{JPN}イット イズ マイ タイム ター ゴー\p"
	.string "{JPN}レタイエムント ハズ エルーディッド ミー\n"
	.string "{JPN}フォー デケードズ ナウ\p"
	.string "{JPN}アイ クッド ノット ストップ トレーディング\n"
	.string "{JPN}アイ アドー ザー ハント\p"
	.string "{JPN}ザット キー ウォズ マイ\n"
	.string "{JPN}ラースト グッド ター ギフト\p"
	.string "{JPN}レッディー キザナー$"

SeaMauville_Text_OneMoreToGo:
	.string "So that is number four out of five.\n"
	.string "Hah... I'm becoming a rather\l"
	.string "complex system of individuals, eh?\p"
	.string "With Nob's memories, I can tell\n"
	.string "what that key he traded you is for.\l"
	.string "It's to open the Maintenance level\l"
	.string "of New Mauville, underneath\l"
	.string "the city proper. A lot of engineering\l"
	.string "projects are greenlit and tested\l"
	.string "down there, so I hear.\p"
	.string "It's also where we will find\n"
	.string "The Storyteller. I'm sure of it...\p"
	.string "This might be the last leg of\n"
	.string "the journey, {PLAYER}. Let's\l"
	.string "go find that door this key\l"
	.string "goes to in New Mauville.$"

SeaMauville_Text_KizunaIdle2:
	.string "So, uh, I believe he wants\n"
	.string "to trade us some sort of key?\l"
	.string "But he would like some Tea\l"
	.string "in return. I... I'm sorry,\l"
	.string "I don't quite know what kind of\l"
	.string "tea he wants.\p"
	.string "Maybe we should ask around the\n"
	.string "market and see if we can get\l"
	.string "what The Trader wants.$"

SeaMauville_Text_ImUpToNoGood:
	.string "Nothing suspicious going on here!\n"
	.string "No sirree! Nuh uh!$"

SeaMauville_Text_GoGetMeASuitcase:
	.string "You look like a person who's\n"
	.string "in need of somethin' nice.\l"
	.string "Maybe you can... trade it for\l"
	.string "somethin' better.\p"
	.string "Well, I got just the deal for ya.\n"
	.string "Help me intercept a package, and\l"
	.string "I'll give ya some of what's in there.\p"
	.string "Now, a friend'a mine is gonna come\n"
	.string "strolling down the road behind\l"
	.string "the Pokemon Center in a bit.\l"
	.string "You go and loiter back there.\l"
	.string "When she pops up, you can't miss her.\l"
	.string "Lady with sheet-white hair.\p"
	.string "No matter what she says, battle\n"
	.string "her and then take her briefcase.\l"
	.string "Don't worry, 's all part\l"
	.string "of the plan!\p"
	.string "Then, you come bring dat case\n"
	.string "back to me. We split the contents.\l"
	.string "All's done. Capische?$"

SeaMauville_Text_SuitcaseInstructions:
	.string "Now, a friend'a mine is gonna come\n"
	.string "strolling down the road behind\l"
	.string "the Pokemon Center in a bit.\l"
	.string "You go and loiter back there.\l"
	.string "When she pops up, you can't miss her.\l"
	.string "Lady with sheet-white hair.\p"
	.string "No matter what she says, battle\n"
	.string "her and then take her briefcase.\l"
	.string "Don't worry, 's all part\l"
	.string "of the plan!\p"
	.string "Then, you come bring dat case\n"
	.string "back to me. We split the contents.\l"
	.string "All's done. Capische?$"

SeaMauville_Text_YouGotTheStuff:
	.string "Nice! You got the stuff!\p"
	.string "(The man rummages through the\n"
	.string "suitcase to check what's in it.)\p"
	.string "Yep, recon didn't lie. Some\n"
	.string "valuable stuff in here... but\l"
	.string "I'll have to lay low after...\p"
	.string "...Ah, yeah. You can, uh...\n"
	.string "have this. Might come in handy!\l"
	.string "Or something.$"

SeaMauville_Text_ThanksForSuitcase:
	.string "Good doin' business with ya.\n"
	.string "Don't tell nobody about this.$"

SeaMauville_Text_TimeToIntercept:
	.string "!\p"
	.string "(You see your target.)$"

SeaMauville_Text_MyCreamHasTroubleWakingUp:
	.string "Sigh...\n"
	.string "My poor little Cream has\l"
	.string "been a bit... narcoleptic, recently.\p"
	.string "I wanna spend a lot of time with\n"
	.string "the lil' guy, but he's sleepy\l"
	.string "so often these days.$"

SeaMauville_Text_TradeFlute:
	.string "Hmmm? A Poke Flute, you say?\p"
	.string "Why, yes, I have seen how they\n"
	.string "can keep Pokemon energetic.\p"
	.string "That's very sweet of you to offer!\n"
	.string "...Let's see, what could I give\l"
	.string "you in return...\p"
	.string "Ah. I know! A few weeks back, my\n"
	.string "Cream was getting pestered by\l"
	.string "a Grimer with yellow teeth.\l"
	.string "He ended up taking the teeth\l"
	.string "right out of its mouth!\p"
	.string "I thought it was gross, but\n"
	.string "upon further inspection,\l"
	.string "all the teeth were made of\l"
	.string "solid gold!\p"
	.string "Hope it fetches a pretty penny.\n"
	.string "Here you go.$"

SeaMauville_Text_FluteWorked:
	.string "That flute is doing wonders\n"
	.string "for lil' Cream's attention span!\p"
	.string "He's a lot more attentive and\n"
	.string "playful after hearing me play it.$"

SeaMauville_Text_CreamTeeth:
	.string "(Cream is groggily futzing around\n"
	.string "with some yellow teeth...)$"

SeaMauville_Text_CreamFlute:
	.string "(Cream is humming a little\n"
	.string "tune to itself...)$"

SeaMauville_Text_SellingTeaMauville:
	.string "Thtep wwwwight up! Twy out\n"
	.string "the homewy, onthe fowgotten tathe\l"
	.string "of Tea Mauviwwe!\p"
	.string "One hewping oph Tea for you?\n"
	.string "Wonderfuw! That wiww come out to...\l"
	.string "theventy-fouw Thimoweons.\p"
	.string "...You potheth no Thimoweons?\n"
	.string "Thowwy, no ethchanges for othew\l"
	.string "cuwwenthy. Bad wuck!\p"
	.string "Mayhapth ath bad ath mine, aftew\n"
	.string "mithplathing my teef...$"

SeaMauville_Text_ThoseTeethWillDoNicely:
	.string "Ouw those gowd teef?\n"
	.string "Pweathe, I beg... give\l"
	.string "'em to me...\p"
	.string "(He pops in the gilded dentures.)\p"
	.string "Much better! Such a kind act will\n"
	.string "not go unrewarded, patron.\l"
	.string "I'll gift you the tea, on the house.$"

SeaMauville_Text_SorryLetMeTakeThis:
	.string "Sorry, that was my cell.\n"
	.string "Give me a moment.\p"
	.string "...\p"
	.string "Yes, Nue? ...Oh?\p"
	.string "...That's terrible! What did\n"
	.string "the assailant look like?\p"
	.string "...Hmm.\p"
	.string "...I don't think it shall be\n"
	.string "necessary. I will handle it.\p"
	.string "...$"

SeaMauville_Text_OkayFineTakeTea:
	.string "You've roughed me up quite good.\n"
	.string "What is your end goal, ruffian?\p"
	.string "...Just...the tea...?\p"
	.string "Fine, fine. Take it and\n"
	.string "leave my sight. I want no\l"
	.string "further trouble.$"
