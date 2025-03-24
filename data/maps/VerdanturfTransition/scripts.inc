.set LOCALID_BONDING, 2
.set LOCALID_GUARD, 1

VerdanturfTransition_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, VerdanturfTransition_OnLoad
	.byte 0

VerdanturfTransition_OnLoad:
	call VerdanturfTransition_EventScript_RemoveMrBonding
	call_if_ge VAR_OLD_GUYS_STATE, 20, VerdanturfTransition_EventScript_SetTempVar
	call_if_set FLAG_PAID_FOR_BADGE_06, VerdanturfTransition_EventScript_SetTempVar
	end

VerdanturfTransition_EventScript_RemoveMrBonding::
	removeobject LOCALID_BONDING
	setflag FLAG_TEMP_12
	return

VerdanturfTransition_EventScript_SetTempVar::
	setvar VAR_TEMP_4, 1
	return

VerdanturfTransition_EventScript_Roadblock::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTransition_Movement_FaceDown
	waitmovement 0
	msgbox VerdanturfTransition_Text_ExclusiveAccess, MSGBOX_DEFAULT
	goto_if_eq VAR_OLD_GUYS_STATE, 19, VerdanturfTransition_EventScript_MrBondingAppears
	showmoneybox 0, 0
	msgbox VerdanturfTransition_Text_WillYouPay, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, VerdanturfTransition_EventScript_CheckMoney
	hidemoneybox
	msgbox VerdanturfTransition_Text_SorryToHear, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTransition_Movement_MoveRight
	waitmovement 0
	closemessage
	release
	end

VerdanturfTransition_Movement_FaceDown:
	face_down
	step_end

VerdanturfTransition_Movement_MoveRight:
	walk_right
	step_end

VerdanturfTransition_EventScript_CheckMoney::
	checkmoney 100000
	goto_if_eq VAR_RESULT, FALSE, VerdanturfTransition_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 100000
	updatemoneybox
	delay 40
	hidemoneybox
	msgbox VerdanturfTransition_Text_Delightful, MSGBOX_DEFAULT
	message VerdanturfTransition_Text_ReceivedMetroBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_PAID_FOR_BADGE_06
	setflag FLAG_BADGE06_GET
	clearflag FLAG_WITHIN_GYM
	setflag FLAG_DEFEATED_MAUVILLE_GYM
	setvar VAR_PISCES_STORY_PROGRESS, 7
	setvar VAR_TEMP_4, 1
	msgbox VerdanturfTransition_Text_WeWillAlsoThrowIn, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	msgbox VerdanturfTransition_Text_HaveAGoodJourney, MSGBOX_DEFAULT
	closemessage
	release
	end

VerdanturfTransition_EventScript_NotEnoughMoney::
	msgbox VerdanturfTransition_Text_NotEnoughMoney, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTransition_Movement_MoveRight
	waitmovement 0
	closemessage
	release
	end

VerdanturfTransition_EventScript_MrBondingAppears::
	closemessage
	clearflag FLAG_TEMP_12
	addobject LOCALID_BONDING
	playse SE_DOOR
	waitse
	applymovement LOCALID_GUARD, VerdanturfTransition_Movement_GuardShocked
	waitmovement 0
	applymovement LOCALID_BONDING, VerdanturfTransition_Movement_MrBondingArrives
	waitmovement 0
	speakername VerdanturfTransition_Text_NameMrBonding
	msgbox VerdanturfTransition_Text_HelloGuard, MSGBOX_DEFAULT
	speakername NULL
	msgbox VerdanturfTransition_Text_IsThatAugustus, MSGBOX_DEFAULT
	speakername VerdanturfTransition_Text_NameMrBonding
	msgbox VerdanturfTransition_Text_LetInPlayer, MSGBOX_DEFAULT
	speakername NULL
	msgbox VerdanturfTransition_Text_SureThing, MSGBOX_DEFAULT
	applymovement LOCALID_GUARD, VerdanturfTransition_Movement_FaceUp
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTransition_Movement_FaceRight
	applymovement LOCALID_BONDING, VerdanturfTransition_Movement_MrBondingTalkToPlayer
	waitmovement 0
	speakername VerdanturfTransition_Text_NameMrBonding
	msgbox VerdanturfTransition_Text_YouveGotThis, MSGBOX_DEFAULT
	setvar VAR_OLD_GUYS_STATE, 20
	setvar VAR_TEMP_4, 1
	closemessage
	applymovement LOCALID_BONDING, VerdanturfTransition_Movement_MrBondingLeaves
	waitmovement 0
	removeobject LOCALID_BONDING
	setflag FLAG_TEMP_12
	playse SE_EXIT
	release
	end

VerdanturfTransition_Movement_GuardShocked:
	face_right
	emote_exclamation_mark
	step_end

VerdanturfTransition_Movement_MrBondingArrives:
	walk_left
	walk_left
	step_end

VerdanturfTransition_Movement_FaceUp:
	face_up
	step_end

VerdanturfTransition_Movement_FaceRight:
	face_right
	step_end

VerdanturfTransition_Movement_MrBondingTalkToPlayer:
	walk_up
	walk_up
	face_left
	step_end

VerdanturfTransition_Movement_MrBondingLeaves:
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

VerdanturfTransition_EventScript_Guard::
	lock
	msgbox VerdanturfTransition_Text_WelcomeValuedCitizen, MSGBOX_AUTOCLOSE
	release
	end

VerdanturfTransition_Text_NameMrBonding:
	.string "Mr. Bonding$"

VerdanturfTransition_Text_ExclusiveAccess:
	.string "Verdanturf Town is a gated\n"
	.string "community. If you do not have your\l"
	.string "pass designating you as a\l"
	.string "resident, nor special permission\l"
	.string "from Wattson or Scott, I must\l"
	.string "ask you to leave.$"

VerdanturfTransition_Text_WillYouPay:
	.string "(You explain that you are\n"
	.string "here to obtain the gym badge.)\p"
	.string "Ah, so you are looking to pay\n"
	.string "the fine for instant access\l"
	.string "to the Metro Badge?\l"
	.string "You are aware of the steep price\l"
	.string "for this service, correct?\p"
	.string "If you are serious about this, then\n"
	.string "we require a payment of ¥100,000.$"

VerdanturfTransition_Text_SorryToHear:
	.string "Well, I am sorry to hear that\n"
	.string "you decline the offer.\l"
	.string "We must ask you to vacate\l"
	.string "the premises, then.$"

VerdanturfTransition_Text_Delightful:
	.string "That's all ¥100,000 accounted for.\n"
	.string "Here is your badge!$"

VerdanturfTransition_Text_ReceivedMetroBadge:
	.string "{PLAYER} received the\n"
	.string "Metro Badge\l"
	.string "through the power of money!$"

VerdanturfTransition_Text_WeWillAlsoThrowIn:
	.string "This badge allows you to use the\n"
	.string "Field Move Surf outside of battle.\p"
	.string "Due to Greater Mauville Holdings'\n"
	.string "infinite generosity, we will\l"
	.string "also throw in this prize.$"

VerdanturfTransition_Text_HaveAGoodJourney:
	.string "And! We will also give you\n"
	.string "a residency pass to explore\l"
	.string "Verdanturf Town if you so wish.\p"
	.string "Please do not be a disturbance.\n"
	.string "Have a nice evening.$"

VerdanturfTransition_Text_NotEnoughMoney:
	.string "Apologies. But that is clearly\n"
	.string "not enough to pay the fine.\p"
	.string "We must ask you to leave.$"

VerdanturfTransition_Text_HelloGuard:
	.string "Ah, salutations, sir.\p"
	.string "I believe you recognize me, yes?$"

VerdanturfTransition_Text_IsThatAugustus:
	.string "M-M-Mr. Augustus!?\n"
	.string "It is a p-pleasure to meet you,\l"
	.string "sir! I've heard much about\l"
	.string "you from the higher-ups...$"

VerdanturfTransition_Text_LetInPlayer:
	.string "My reputation precedes me.\n"
	.string "Now, you will be letting in my\l"
	.string "cherished friend {PLAYER}, yes?\p"
	.string "I want them to be treated as\n"
	.string "a resident of the town. No fines\l"
	.string "paid. And I would like you\l"
	.string "to phone your boss for me...\l"
	.string "to let him know that {PLAYER}\l"
	.string "will be meeting with him,\l"
	.string "on orders from his superior.$"

VerdanturfTransition_Text_SureThing:
	.string "Y-Y-Yes, sir! I will do so!\n"
	.string "You are more than welcome\l"
	.string "in Verdanturf, {PLAYER}!$"

VerdanturfTransition_Text_YouveGotThis:
	.string "You can do this, my friend.\n"
	.string "Go show Wattson a battle\l"
	.string "he will not soon forget.$"

VerdanturfTransition_Text_WelcomeValuedCitizen:
	.string "Welcome to Verdanturf Town,\n"
	.string "valued citizen!$"
