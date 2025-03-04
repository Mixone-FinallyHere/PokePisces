.set LOCALID_P_MAN, 3
.set LOCALID_SCOTT, 2
.set LOCALID_WATTSON, 1
.set LOCALID_WALLY, 8

VerdanturfInteriors_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfInteriors_OnFrame
	.byte 0

VerdanturfInteriors_OnFrame:
	map_script_2 VAR_WALLY_QUEST_STATE, 0, VerdanturfInteriors_EventScript_WallyHouse
	.2byte 0

VerdanturfInteriors_EventScript_WallyHouse::
	lock
	setvar VAR_WALLY_QUEST_STATE, 1
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfInteriors_Movement_PlayerWalkIn
	applymovement LOCALID_WALLY, VerdanturfInteriors_Movement_WallyWalkIn
	waitmovement 0
	speakername VerdanturfInteriors_Text_NameWally
	msgbox VerdanturfInteriors_Text_LetsCatchUp, MSGBOX_DEFAULT
	setflag FLAG_MET_WALLY_VERDANTURF
	release
	end

VerdanturfInteriors_Movement_PlayerWalkIn:
	walk_up
	step_end

VerdanturfInteriors_Movement_WallyWalkIn:
	walk_up
	walk_up
	face_down
	step_end

VerdanturfInteriors_EventScript_WallyIdle::
	lock
	faceplayer
	speakername VerdanturfInteriors_Text_NameWally
	msgbox VerdanturfInteriors_Text_ImOnMyOwnJourney, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfInteriors_EventScript_MeetingLeftTrigger::
	lock
	goto_if_set FLAG_BADGE06_GET, VerdanturfInteriors_EventScript_TurnBack
	goto_if_eq VAR_OLD_GUYS_STATE, 20, VerdanturfInteriors_EventScript_MoveUpLeft
	goto VerdanturfInteriors_EventScript_TurnBack
	release
	end

VerdanturfInteriors_EventScript_MeetingRightTrigger::
	lock
	goto_if_set FLAG_BADGE06_GET, VerdanturfInteriors_EventScript_TurnBack
	goto_if_eq VAR_OLD_GUYS_STATE, 20, VerdanturfInteriors_EventScript_MoveUpRight
	goto VerdanturfInteriors_EventScript_TurnBack
	release
	end

VerdanturfInteriors_EventScript_TurnBack::
	msgbox VerdanturfInteriors_Text_TurnBack, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfInteriors_Movement_WalkDown
	waitmovement 0
	delay 8
	closemessage
	release
	end

VerdanturfInteriors_Movement_WalkDown:
	walk_down
	step_end

VerdanturfInteriors_EventScript_MoveUpLeft::
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfInteriors_Movement_MoveUpLeft
	waitmovement 0
	goto VerdanturfInteriors_EventScript_MeetWattsonAndScott
	release
	end

VerdanturfInteriors_Movement_MoveUpLeft:
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfInteriors_EventScript_MoveUpRight::
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfInteriors_Movement_MoveUpRight
	waitmovement 0
	goto VerdanturfInteriors_EventScript_MeetWattsonAndScott
	release
	end

VerdanturfInteriors_Movement_MoveUpRight:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfInteriors_EventScript_MeetWattsonAndScott::
	delay 8
	applymovement LOCALID_P_MAN, VerdanturfInteriors_Movement_Shocked
	waitmovement 0
	msgbox VerdanturfInteriors_Text_WhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_P_MAN, VerdanturfInteriors_Movement_ManWalkIntoRoom
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfInteriors_Movement_PlayerWalkIntoRoom
	waitmovement 0
	delay 16
	speakername VerdanturfInteriors_Text_NameScott
	msgbox VerdanturfInteriors_Text_ANewFace, MSGBOX_DEFAULT
	speakername VerdanturfInteriors_Text_NameWattson
	msgbox VerdanturfInteriors_Text_JustGiveTheBadge, MSGBOX_DEFAULT
	speakername VerdanturfInteriors_Text_NameScott
	msgbox VerdanturfInteriors_Text_HereYouGo, MSGBOX_DEFAULT
	message VerdanturfInteriors_Text_ReceivedMetroBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_BADGE06_GET
	setflag FLAG_DEFEATED_MAUVILLE_GYM
	setvar VAR_PISCES_STORY_PROGRESS, 7
	speakername VerdanturfInteriors_Text_NameWattson
	msgbox VerdanturfInteriors_Text_YouMayNowLeave, MSGBOX_DEFAULT
	speakername NULL
	msgbox VerdanturfInteriors_Text_StandYourGround, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, VerdanturfInteriors_EventScript_BattleWattsonAndScott
	msgbox VerdanturfInteriors_Text_LeaveAwkwardly, MSGBOX_DEFAULT
	closemessage
	warp MAP_VERDANTURF_NEW, 32, 9
	waitstate
	release
	end

VerdanturfInteriors_Movement_Shocked:
	face_down
	delay_4
	emote_exclamation_mark
	step_end

VerdanturfInteriors_Movement_ManWalkIntoRoom:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	face_left
	step_end

VerdanturfInteriors_Movement_PlayerWalkIntoRoom:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	face_right
	step_end

VerdanturfInteriors_EventScript_BattleWattsonAndScott::
	speakername VerdanturfInteriors_Text_NameWattson
	msgbox VerdanturfInteriors_Text_HowArrogant, MSGBOX_DEFAULT
	speakername NULL
	trainerbattle_two_trainers TRAINER_P_WATTSON, VerdanturfInteriors_Text_WattsonDefeat, TRAINER_P_SCOTT, VerdanturfInteriors_Text_ScottDefeat, VerdanturfInteriors_EventScript_LeadersDefeated, NO_MUSIC
	goto VerdanturfInteriors_EventScript_LeadersDefeated
	release
	end

VerdanturfInteriors_EventScript_LeadersDefeated::
	speakername VerdanturfInteriors_Text_NameWattson
	msgbox VerdanturfInteriors_Text_DidThatSuffice, MSGBOX_DEFAULT
	speakername VerdanturfInteriors_Text_NameScott
	msgbox VerdanturfInteriors_Text_IKindaHadFun, MSGBOX_DEFAULT
	speakername VerdanturfInteriors_Text_NameWattson
	msgbox VerdanturfInteriors_Text_IMustStressThatYouLeave, MSGBOX_DEFAULT
	closemessage
	warp MAP_VERDANTURF_NEW, 32, 9
	waitstate
	release
	end

VerdanturfInteriors_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_GAOTERRA_TRADE_COMPLETED, VerdanturfInteriors_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_GAOTERRA
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox VerdanturfInteriors_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VerdanturfInteriors_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, VerdanturfInteriors_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, VerdanturfInteriors_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox VerdanturfInteriors_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_GAOTERRA_TRADE_COMPLETED
	release
	end

VerdanturfInteriors_EventScript_DeclineTrade::
	msgbox VerdanturfInteriors_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

VerdanturfInteriors_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox VerdanturfInteriors_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

VerdanturfInteriors_EventScript_TradeCompleted::
	msgbox VerdanturfInteriors_Text_ThanksForTrading, MSGBOX_DEFAULT
	release
	end

VerdanturfInteriors_Text_IllTradeIfYouWant:
	.string "I'll trade you my {STR_VAR_2} for\n"
	.string "a {STR_VAR_1} if you want.$"

VerdanturfInteriors_Text_PleaseBeGoodToMyPokemon:
	.string "Please be good to my POKéMON.$"

VerdanturfInteriors_Text_DoesntLookLikeMonToMe:
	.string "Huh? That doesn't look anything like\n"
	.string "a {STR_VAR_1} to me.$"

VerdanturfInteriors_Text_YouDontWantToThatsOkay:
	.string "Oh, if you don't want to, that's okay.$"

VerdanturfInteriors_Text_ThanksForTrading:
	.string "Thanks for the trade.$"

VerdanturfInteriors_Text_NameScott:
	.string "Scott$"

VerdanturfInteriors_Text_NameWattson:
	.string "Wattson$"

VerdanturfInteriors_Text_TurnBack:
	.string "(You sense you are somewhere\n"
	.string "that you are not welcome.)$"

VerdanturfInteriors_Text_WhoAreYou:
	.string "Excuse me, I am going\n"
	.string "to have to ask you to leave.\l"
	.string "This building is only for\l"
	.string "those truste-\p"
	.string "Oh.\p"
	.string "You must be... {PLAYER}?\n"
	.string "Yes, I've just recalled.\l"
	.string "A personal friend of Augustus?\l"
	.string "That's a bit unusual...\l"
	.string "but it's not like we'll refuse\l"
	.string "a request from him.\p"
	.string "Wattson and Scott are in our\n"
	.string "boardroom. Allow me to take you...$"

VerdanturfInteriors_Text_ANewFace:
	.string "That's a face I haven't seen\n"
	.string "before! This rookie looking trainer\l"
	.string "is a friend of the old boss?$"

VerdanturfInteriors_Text_JustGiveTheBadge:
	.string "Harrumph.\n"
	.string "...Just give the kid the\l"
	.string "badge, Scott.$"

VerdanturfInteriors_Text_HereYouGo:
	.string "Yeah, yeah, I will. The rookie\n"
	.string "looks pretty intriguing, I'll admit.\l"
	.string "Go on, take the badge!$"

VerdanturfInteriors_Text_ReceivedMetroBadge:
	.string "{PLAYER} received the\n"
	.string "Metro Badge\l"
	.string "from Scott and Wattson.\p"
	.string "It felt a little hollow.$"

VerdanturfInteriors_Text_YouMayNowLeave:
	.string "That is all the time I have\n"
	.string "allotted for this meaning, kid.\l"
	.string "You may now leave us be.\l"
	.string "Go on with your adventure.$"

VerdanturfInteriors_Text_StandYourGround:
	.string "...\p"
	.string "(Should you really just...\n"
	.string "leave without battling them?\l"
	.string "Something doesn't feel right\l"
	.string "about that.)\p"
	.string "(Will you stand your ground\n"
	.string "and demand a gym battle?)$"

VerdanturfInteriors_Text_LeaveAwkwardly:
	.string "(You feel too intimidated\n"
	.string "to properly speak your mind...)$"

VerdanturfInteriors_Text_HowArrogant:
	.string "...That is amusing.\n"
	.string "You have the gall to stand there\l"
	.string "and demand a battle, eh?\l"
	.string "You sure do have a nerve\l"
	.string "in you. That could very well\l"
	.string "be a good thing. Or maybe not!\p"
	.string "Fine. We will give you your battle.\n"
	.string "Rest assured, you will be\l"
	.string "absolutely pulverized...!$"

VerdanturfInteriors_Text_WattsonDefeat:
	.string "...Harrumph.$"

VerdanturfInteriors_Text_ScottDefeat:
	.string "You didn't hold anything back!\n"
	.string "I must say I'm impressed by you!$"

VerdanturfInteriors_Text_DidThatSuffice:
	.string "Did that suffice, kid? Give you\n"
	.string "the satisfaction you wanted?\l"
	.string "You may do well to keep that\l"
	.string "gall of yours in check in the future.\l"
	.string "Other people may not be\l"
	.string "so graceful...$"

VerdanturfInteriors_Text_IKindaHadFun:
	.string "Lighten up, old boy! I had some\n"
	.string "fun with that match. You\l"
	.string "remind me a lot of that particularly\l"
	.string "strong trainer from some time ago...$"

VerdanturfInteriors_Text_IMustStressThatYouLeave:
	.string "Yes, yes. How sunshine and rainbows.\n"
	.string "Now, we have business to discuss.\l"
	.string "WITHOUT you, kid.\l"
	.string "I must stress that you leave\l"
	.string "this building.$"

VerdanturfInteriors_Text_NameWally:
	.string "Wally$"

VerdanturfInteriors_Text_LetsCatchUp:
	.string "S-So, I see you're doing\n"
	.string "the gym challenge over again.\p"
	.string "That's pretty cool! Personally,\n"
	.string "I-I think my time for adventuring\l"
	.string "has passed, if I'm being honest.\l"
	.string "Cough... my lungs haven't\l"
	.string "exactly gotten better over time,\l"
	.string "hahaha...\p"
	.string "Listen, I know we were both kinda\n"
	.string "rivals to the former champ, b-but\l"
	.string "they always seemed closer to you...\l"
	.string "have you h-heard anything\l"
	.string "from them at all? Any letters?\p"
	.string "Nothing for you either, huh...\n"
	.string "Th-that's a shame. I hope\l"
	.string "they're doing okay...\p"
	.string "Either or... I wish you\n"
	.string "lots of luck doing the\l"
	.string "new gym challenge! It seems\l"
	.string "a lot tougher than when\l"
	.string "I did it back then.\p"
	.string "I'm going to be on a bit of\n"
	.string "a trek of my own to search\l"
	.string "for some medicine. Maybe\l"
	.string "w-we'll run into each other\l"
	.string "on the road!\p"
	.string "I think I've, uh, held you\n"
	.string "long enough. Have a great\l"
	.string "day, {PLAYER}!$"

VerdanturfInteriors_Text_ImOnMyOwnJourney:
	.string "Oh, the time has f-flown by...\n"
	.string "I'm supposed to be headed\l"
	.string "out soon to the pharmacy...$"
