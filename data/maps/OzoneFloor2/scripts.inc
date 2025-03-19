.set LOCALID_RAY, 1

OzoneFloor2_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, OzoneFloor2_OnLoad
	.byte 0

OzoneFloor2_OnLoad:
	call_if_gt VAR_RAY_STATE, 6, OzoneFloor2_EventScript_RemoveRay
	end

OzoneFloor2_EventScript_RemoveRay::
	removeobject LOCALID_RAY
	setflag FLAG_TEMP_13
	return

OzoneFloor2_EventScript_RayEncounter1::
	lock
	applymovement LOCALID_RAY, OzoneFloor2_Movement_RayEncounter1
	waitmovement 0
	goto OzoneFloor2_EventScript_RayBattleStart
	release
	end

OzoneFloor2_Movement_RayEncounter1:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

OzoneFloor2_EventScript_RayEncounter2::
	lock
	applymovement LOCALID_RAY, OzoneFloor2_Movement_RayEncounter2
	waitmovement 0
	goto OzoneFloor2_EventScript_RayBattleStart
	release
	end

OzoneFloor2_Movement_RayEncounter2:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

OzoneFloor2_EventScript_RayEncounter3::
	lock
	applymovement LOCALID_RAY, OzoneFloor2_Movement_RayEncounter3
	waitmovement 0
	goto OzoneFloor2_EventScript_RayBattleStart
	release
	end

OzoneFloor2_Movement_RayEncounter3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

OzoneFloor2_EventScript_RayEncounter4::
	lock
	applymovement LOCALID_RAY, OzoneFloor2_Movement_RayEncounter4
	waitmovement 0
	goto OzoneFloor2_EventScript_RayBattleStart
	release
	end

OzoneFloor2_Movement_RayEncounter4:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

OzoneFloor2_EventScript_RayBattleStart::
	speakername OzoneFloor2_Text_NameRay
	msgbox OzoneFloor2_Text_RayIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_RAY_7, OzoneFloor2_Text_RayDefeat
	goto OzoneFloor2_EventScript_RayLeaves
	speakername NULL
	release
	end

OzoneFloor2_EventScript_RayLeaves::
	speakername OzoneFloor2_Text_NameRay
	msgbox OzoneFloor2_Text_RayLeaves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RAY, OzoneFloor2_Movement_RayLeaves
	waitmovement 0
	removeobject LOCALID_RAY
	speakername NULL
	setflag FLAG_TEMP_13
	setvar VAR_RAY_STATE, 7
	release
	end

OzoneFloor2_Movement_RayLeaves:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

OzoneFloor2_EventScript_Nurse::
	lock
	msgbox gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, OzoneFloor2_EventScript_HealPkmn
	message gText_WeHopeToSeeYouAgain
	closemessage
	release
	end

OzoneFloor2_EventScript_HealPkmn::
	special HealPlayerParty
	message gText_RestoredPkmnToFullHealth
	waitmessage
	message gText_WeHopeToSeeYouAgain
	waitmessage
	waitbuttonpress
	closemessage
	release
	end

OzoneFloor2_EventScript_EliteFourTrigger::
	msgbox OzoneFloor2_Text_NoGoingBack, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, YES, OzoneFloor2_EventScript_EnterEliteFour
	applymovement OBJ_EVENT_ID_PLAYER, OzoneFloor2_Movement_WalkAway
	waitmovement 0
	release
	end

OzoneFloor2_EventScript_EnterEliteFour::
	applymovement OBJ_EVENT_ID_PLAYER, OzoneFloor2_Movement_EnterEliteFour
	waitmovement 0
	warp MAP_OZONE_ELITE_FOUR_HUB, 13, 9
	waitstate
	release
	end

OzoneFloor2_Movement_EnterEliteFour:
	walk_up
	step_end

OzoneFloor2_Movement_WalkAway:
	walk_down
	step_end

OzoneFloor2_Text_NameRay:
	.string "Ray$"

OzoneFloor2_Text_RayIntro:
	.string "Well, well, well.\n"
	.string "It is {PLAYER}.\p"
	.string "It seems only fitting that I should\n"
	.string "encounter bad luck (seeing you)\l"
	.string "after a stroke of massively\l"
	.string "good luck (winning the lottery).\p"
	.string "My superiors and co-workers seem\n"
	.string "to have developed a liking for you.\l"
	.string "I (a now-millionaire) have not\l"
	.string "developed a liking for you.\l"
	.string "It is not for lack of trying.\l"
	.string "You are just so very unlikeable.\p"
	.string "They have, however, ordered me to\n"
	.string "be here on this occasion to mark\l"
	.string "the end of your (very flawed) journey.\p"
	.string "So, fight we must.\n"
	.string "This is a known factor between\l"
	.string "you and I (a now-millionaire).\p"
	.string "I have accepted that you may\n"
	.string "win this bout. But that is okay,\l"
	.string "for I have already won in life.\l"
	.string "(And the lottery)\p"
	.string "Let's get things started.$"

OzoneFloor2_Text_RayDefeat:
	.string "(Ray writes you a check\n"
	.string "for zero dollars.)\p"
	.string "A winner is you.\n"
	.string "What an anti-climax.$"

OzoneFloor2_Text_RayLeaves:
	.string "How sad that someone barely fit\n"
	.string "to be a side character ends\l"
	.string "up having such protagonistic energy.\p"
	.string "Do not fret. You can have this one.\n"
	.string "I may soon have my own\l"
	.string "main journey in the near future\l"
	.string "(and you are not invited).\p"
	.string "Because I am ever so generous\n"
	.string "(and rich), I will give you the\l"
	.string "courtesy of getting to ask one\l"
	.string "question about The Great, Ray.\p"
	.string "(You mull it over for a minute\n"
	.string "before taking them up on\l"
	.string "the offer.)\p"
	.string "...What's my full name?\n"
	.string "A bit personal. But I suppose\l"
	.string "I can reguile you with the\l"
	.string "information.\p"
	.string "The name “Ray” is short form.\n"
	.string "Short, for “Coriander”.\l"
	.string "Coriander Jones.\p"
	.string "Leak this information, and\n"
	.string "you will find your (ugly) face\l"
	.string "on milk cartons.\p"
	.string "...At last, this is where we part\n"
	.string "ways for good, {PLAYER}.\l"
	.string "I hope to never see you again.$"

OzoneFloor2_Text_NoGoingBack:
	.string "(Once you enter this door,\n"
	.string "there is no going back.\l"
	.string "You will need to complete\l"
	.string "the Ozone Challenge before\l"
	.string "you can leave again.)\p"
	.string "(Knowing this, do you still enter?)$"
