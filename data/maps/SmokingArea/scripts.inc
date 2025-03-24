.set LOCALID_P_MAN, 5
.set LOCALID_STORYTELLER, 1
.set LOCALID_BONDING, 6

SmokingArea_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SmokingArea_OnLoad
	.byte 0

SmokingArea_OnLoad:
	call_if_eq VAR_OLD_GUYS_STATE, 17, SmokingArea_EventScript_SetStorytellerGfx
	call_if_lt VAR_OLD_GUYS_STATE, 17, SmokingArea_EventScript_RemoveStoryteller
	call_if_gt VAR_OLD_GUYS_STATE, 17, SmokingArea_EventScript_RemoveStoryteller
	call SmokingArea_EventScript_RemoveKizuna
	end

SmokingArea_EventScript_SetStorytellerGfx::
	setvar VAR_BARD_COLOR, MAUVILLE_MAN_STORYTELLER
	special SetMauvilleOldManObjEventGfx
	return

SmokingArea_EventScript_RemoveStoryteller::
	removeobject LOCALID_STORYTELLER
	setflag FLAG_TEMP_12
	return

SmokingArea_EventScript_RemoveKizuna::
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	removeobject LOCALID_BONDING
	setflag FLAG_TEMP_13
	return

SmokingArea_EventScript_Storyteller::
	lock
	faceplayer
	msgbox SmokingArea_Text_IAmTheStoryteller, MSGBOX_DEFAULT
	closemessage
	delay 32
	clearflag FLAG_TEMP_11
	addobject LOCALID_P_MAN
	playse SE_DOOR
	waitse
	applymovement OBJ_EVENT_ID_PLAYER, SmokingArea_Movement_PlayerMoveOutOfWay
	applymovement LOCALID_P_MAN, SmokingArea_Movement_KizunaEnters
	waitmovement 0
	speakername SmokingArea_Text_NameKizuna
	msgbox SmokingArea_Text_YoureTheLastGuy, MSGBOX_DEFAULT
	speakername SmokingArea_Text_NameStoryteller
	msgbox SmokingArea_Text_LetMeTellMyStory, MSGBOX_DEFAULT
	fadenewbgm MUS_VERDANTURF
	msgbox SmokingArea_Text_MauvilleStory, MSGBOX_DEFAULT
	fadenewbgm MUS_NONE
	speakername SmokingArea_Text_NameKizuna
	msgbox SmokingArea_Text_ISee, MSGBOX_DEFAULT
	speakername SmokingArea_Text_NameStoryteller
	msgbox SmokingArea_Text_TimeToRetire, MSGBOX_DEFAULT
	closemessage
	playse SE_M_MEGA_KICK
	applymovement LOCALID_P_MAN, SmokingArea_Movement_KizunaAbsorbST
	waitmovement 0
	removeobject LOCALID_STORYTELLER
	setflag FLAG_TEMP_12
	playse SE_M_FAINT_ATTACK
	waitse
	delay 32
	applymovement LOCALID_P_MAN, SmokingArea_Movement_KizunaWalkUp
	waitmovement 0
	playse SE_BANG
	waitse
	delay 24
	applymovement LOCALID_P_MAN, SmokingArea_Movement_KizunaWalkUp
	waitmovement 0
	playse SE_BANG
	waitse
	delay 24
	applymovement LOCALID_P_MAN, SmokingArea_Movement_KizunaWalkUp
	waitmovement 0
	playse SE_BANG
	waitse
	delay 32
	playbgm MUS_RG_ENCOUNTER_DEOXYS, FALSE
	applymovement OBJ_EVENT_ID_PLAYER, SmokingArea_Movement_PlayerConcern
	waitmovement 0
	playse SE_M_MEGA_KICK
	waitse
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	delay 4
	playse SE_SHINY
	clearflag FLAG_TEMP_13
	addobject LOCALID_BONDING
	applymovement LOCALID_BONDING, SmokingArea_Movement_BondingFaceDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, SmokingArea_Movement_PlayerConfused
	waitmovement 0
	speakername SmokingArea_Text_NameKizuna2
	msgbox SmokingArea_Text_IHaveBeenReborn, MSGBOX_DEFAULT
	speakername SmokingArea_Text_NameMrBonding
	msgbox SmokingArea_Text_IndulgeMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BONDING, SmokingArea_Movement_BondingWalkAway
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_BONDING
	setflag FLAG_TEMP_13
	setvar VAR_OLD_GUYS_STATE, 18
	playbgm MUS_NONE, FALSE
	delay 16
	release
	end

SmokingArea_Movement_PlayerMoveOutOfWay:
	delay_16
	face_up
	delay_16
	delay_8
	walk_left
	face_right
	step_end

SmokingArea_Movement_KizunaEnters:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_left
	walk_slow_down
	walk_slow_down
	step_end

SmokingArea_Movement_KizunaAbsorbST:
	walk_slow_down
	face_up
	step_end

SmokingArea_Movement_KizunaWalkUp:
	walk_slow_up
	step_end

SmokingArea_Movement_PlayerConcern:
	walk_right
	face_up
	step_end

SmokingArea_Movement_BondingFaceDown:
	face_down
	step_end

SmokingArea_Movement_PlayerConfused:
	emote_question_mark
	step_end

SmokingArea_Movement_BondingWalkAway:
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	step_end

SmokingArea_EventScript_Nurse::
	msgbox SmokingArea_Text_Nurse, MSGBOX_NPC
	end

SmokingArea_Text_Nurse:
	.string "(She's on her smoke break.\n"
	.string "May be wise to not bother her.)$"

SmokingArea_Text_NameKizuna:
	.string "Kizuna$"

SmokingArea_Text_NameStoryteller:
	.string "Storyteller$"

SmokingArea_Text_NameKizuna2:
	.string "Kizuna?$"

SmokingArea_Text_NameMrBonding:
	.string "Mr. Bonding$"

SmokingArea_Text_IAmTheStoryteller:
	.string "...Yes...\n"
	.string "...I am The Storyteller...$"

SmokingArea_Text_YoureTheLastGuy:
	.string "I knew it.\p"
	.string "Mr. Storyteller. You have no idea\n"
	.string "how long we have been journeying\l"
	.string "to find you.\p"
	.string "Can you... can you feel that\n"
	.string "the other Old Guys are within me?\l"
	.string "Giddy? Rydel? Dock? Nob?$"

SmokingArea_Text_LetMeTellMyStory:
	.string "Ah, yes, I do. My dearest friends...\n"
	.string "it brings me joy to know\l"
	.string "that they have retired happily.\p"
	.string "I yearn to retire as well, you know.\n"
	.string "...But I must tell one last tale\l"
	.string "before my time comes.$"

SmokingArea_Text_MauvilleStory:
	.string "My true name does not matter.\n"
	.string "What does matter is that, at a\l"
	.string "certain point in time, I was the\l"
	.string "wealthiest man in Hoenn.\p"
	.string "In my ambition, I sought to fund\n"
	.string "and supervise the creation of\l"
	.string "Hoenn's largest urban area.\l"
	.string "It would become Mauville City.\p"
	.string "My company, Greater Mauville Holdings,\n"
	.string "led many projects afterwards,\l"
	.string "often supervised by my closest\l"
	.string "subordinate, Wattson.\p"
	.string "No project was ever as successful\n"
	.string "as Mauville City.\p"
	.string "The original New Mauville was a\n"
	.string "resource swallowing nightmare.\l"
	.string "A 70 floor supercomplex underground\l"
	.string "that could house a city bigger\l"
	.string "than any other... the ideas did\l"
	.string "not match its execution.\l"
	.string "It was shelved soon after the first\l"
	.string "floor was finished.\p"
	.string "The original Sea Mauville was another.\n"
	.string "A hybrid research facility and\l"
	.string "oil rig in the Hoenn seas...\l"
	.string "it caused too many environmental\l"
	.string "concerns. We were shut down\l"
	.string "early into construction.\p"
	.string "I began to think of myself as a hack.\n"
	.string "Someone whose wealth did not match\l"
	.string "his skills. So, in shame, I resigned.\l"
	.string "Wattson took my place.\p"
	.string "Now, Wattson is a genius. He was\n"
	.string "able to make New and Sea Mauville\l"
	.string "a reality, in his own way.\l"
	.string "But his greed does concern me.\l"
	.string "Partnering with the tycoon Scott\l"
	.string "and buying out Devon Corp...\l"
	.string "the making of a monopoly is\l"
	.string "in progress.\p"
	.string "I am aware you wish to meet\n"
	.string "with him. And I will make that happen.\p"
	.string "As long as you empart onto him\n"
	.string "my final message.\p"
	.string "You must be humble.\n$"

SmokingArea_Text_ISee:
	.string "I see. We can do that easily,\n"
	.string "Mr. Storyteller. Thank you\l"
	.string "for speaking with us and\l"
	.string "hearing our request.\p"
	.string "It's been an honor!$"

SmokingArea_Text_TimeToRetire:
	.string "That is nice...\p"
	.string "I am so very tired, Kizuna.\n"
	.string "Retirement... it will be upon me.\l"
	.string "I cannot wait.$"

SmokingArea_Text_IHaveBeenReborn:
	.string "{PLAYER}.\n"
	.string "I understand everything now...\p"
	.string "With the powers of those five men\n"
	.string "spiraling within me...\l"
	.string "I have been reborn.\p"
	.string "No longer do I identify with the\n"
	.string "name Kizuna... no. That would not\l"
	.string "be fitting for who I now am.\p"
	.string "Rather, you may call me\n"
	.string "Mr. Bonding.$"

SmokingArea_Text_IndulgeMe:
	.string "Now that The Storyteller's soul\n"
	.string "has returned to me, I possess\l"
	.string "the ability to get you an\l"
	.string "audience with Wattson.\p"
	.string "And I will do so. But will you\n"
	.string "please indulge me first...\p"
	.string "This newfound power behooves me\n"
	.string "to test it on the battlefield.\l"
	.string "I have grown quite fond of you,\l"
	.string "and I hope that we will have\l"
	.string "a Pokemon battle that will\l"
	.string "shake the very earth.\p"
	.string "I will be awaiting your arrival\n"
	.string "at the rooftop battling arena\l"
	.string "in New Mauville.$"
