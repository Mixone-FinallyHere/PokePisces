.set LOCALID_RAY, 5

OzoneInstitute_MapScripts::
	.byte 0

OzoneInstitute_EventScript_RayEncounterWest1::
	lock
	applymovement LOCALID_RAY, OzoneInstitute_Movement_RayEncounterWest1
	waitmovement 0
	goto OzoneInstitute_EventScript_RayBattleStart
	release
	end

OzoneInstitute_Movement_RayEncounterWest1:
	walk_left
	walk_left
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
	step_end

OzoneInstitute_EventScript_RayEncounterWest2::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_RAY, OzoneInstitute_Movement_RayEncounterWest2
	waitmovement 0
	goto OzoneInstitute_EventScript_RayBattleStart
	release
	end

OzoneInstitute_Movement_RayEncounterWest2:
	walk_left
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
	step_end

OzoneInstitute_EventScript_RayEncounterEast1::
	lock
	applymovement LOCALID_RAY, OzoneInstitute_Movement_RayEncounterEast1
	waitmovement 0
	goto OzoneInstitute_EventScript_RayBattleStart
	release
	end

OzoneInstitute_Movement_RayEncounterEast1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OzoneInstitute_EventScript_RayEncounterEast2::
	lock
	applymovement LOCALID_RAY, OzoneInstitute_Movement_RayEncounterEast2
	waitmovement 0
	goto OzoneInstitute_EventScript_RayBattleStart
	release
	end

OzoneInstitute_Movement_RayEncounterEast2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OzoneInstitute_EventScript_RayEncounterEast3::
	lock
	applymovement LOCALID_RAY, OzoneInstitute_Movement_RayEncounterEast3
	waitmovement 0
	goto OzoneInstitute_EventScript_RayBattleStart
	release
	end

OzoneInstitute_Movement_RayEncounterEast3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OzoneInstitute_EventScript_RayEncounterEast4::
	lock
	applymovement LOCALID_RAY, OzoneInstitute_Movement_RayEncounterEast4
	waitmovement 0
	goto OzoneInstitute_EventScript_RayBattleStart
	release
	end

OzoneInstitute_Movement_RayEncounterEast4:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OzoneInstitute_EventScript_RayBattleStart::
	speakername OzoneInstitute_Text_NameRay
	msgbox OzoneInstitute_Text_RayIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_RAY_3, OzoneInstitute_Text_RayDefeat
	goto OzoneInstitute_EventScript_RayLeaves
	speakername NULL
	release
	end

OzoneInstitute_EventScript_RayLeaves::
	speakername OzoneInstitute_Text_NameRay
	msgbox OzoneInstitute_Text_RayLeaves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RAY, OzoneInstitute_Movement_RayLeaves
	waitmovement 0
	removeobject LOCALID_RAY
	speakername NULL
	setflag FLAG_BEAT_RAY_3
	setvar VAR_RAY_STATE, 3
	setflag FLAG_VISITED_OZONE_INSTITUTE
	setflag FLAG_HIDE_MAXIE_OZONE
	release
	end

OzoneInstitute_Movement_RayLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OzoneInstitute_EventScript_Gale::
    trainerbattle_single TRAINER_P_GALE, OzoneInstitute_Text_GaleIntro, OzoneInstitute_Text_GaleDefeated
    msgbox OzoneInstitute_Text_GalePostBattle, MSGBOX_AUTOCLOSE
    end

OzoneInstitute_EventScript_Smokey::
    trainerbattle_single TRAINER_P_SMOKEY, OzoneInstitute_Text_SmokeyIntro, OzoneInstitute_Text_SmokeyDefeated
    msgbox OzoneInstitute_Text_SmokeyPostBattle, MSGBOX_AUTOCLOSE
    end

OzoneInstitute_EventScript_DessAndEmber::
    trainerbattle_double TRAINER_P_DESS_AND_EMBER, OzoneInstitute_Text_DessAndEmberIntro, OzoneInstitute_Text_DessAndEmberDefeated, OzoneInstitute_Text_DessAndEmberNeedTwoMons
    msgbox OzoneInstitute_Text_DessAndEmberPostBattle, MSGBOX_AUTOCLOSE
    end

OzoneInstitute_EventScript_OzoneSign::
	msgbox OzoneInstitute_Text_OzoneSign, MSGBOX_SIGN
	end

OzoneInstitute_EventScript_FortreeSign::
	msgbox OzoneInstitute_Text_FortreeSign, MSGBOX_SIGN
	end

OzoneInstitute_EventScript_ArctaigaSign::
	msgbox OzoneInstitute_Text_ArctaigaSign, MSGBOX_SIGN
	end

OzoneInstitute_EventScript_SweltornSign::
	msgbox OzoneInstitute_Text_SweltornSign, MSGBOX_SIGN
	end

OzoneInstitute_EventScript_MasonriedSign::
	msgbox OzoneInstitute_Text_MasonriedSign, MSGBOX_SIGN
	end

OzoneInstitute_Text_OzoneSign:
	.string "OZONE INSTITUTE\n"
	.string "The epicenter of all things weather!$"

OzoneInstitute_Text_FortreeSign:
	.string "NORTH - FORTREE CITY\n"
	.string "A biome beset with heavy rain.$"

OzoneInstitute_Text_ArctaigaSign:
	.string "EAST - ARCTAIGA ROAD\n"
	.string "A biome beset with snow and hail.$"

OzoneInstitute_Text_SweltornSign:
	.string "SOUTH - SWELTORN DESERT\n"
	.string "A biome beset with sandstorms.$"

OzoneInstitute_Text_MasonriedSign:
	.string "WEST - MASONRIED HIKE\n"
	.string "A biome beset with harsh sunlight.$"

OzoneInstitute_Text_GaleIntro:
	.string "You're in the eye of the storm\n"
	.string "right now! That means things\l"
	.string "can only get worse!$"

OzoneInstitute_Text_GaleDefeated:
	.string "My storm dissipated...$"

OzoneInstitute_Text_GalePostBattle:
	.string "Ozone Institute is smack dab\n"
	.string "in the middle of four types of\l"
	.string "weather. It's why we set up\l"
	.string "shop here to begin with!$"

OzoneInstitute_Text_SmokeyIntro:
	.string "Why is it that every time\n"
	.string "I try and get some calm me-time,\l"
	.string "some half-wit comes over?$"

OzoneInstitute_Text_SmokeyDefeated:
	.string "That's 5 minutes of my break I'm\n"
	.string "not taking now...$"

OzoneInstitute_Text_SmokeyPostBattle:
	.string "What, you want to be healed?\n"
	.string "I got... mmm, 30 more minutes\l"
	.string "of off-the-clock time. Uh-uh.$"

OzoneInstitute_Text_DessAndEmberIntro:
	.string "DESS: Honey, you've got a\n"
	.string "      big storm comin'!\l"
	.string "EMBER: Oh, it's gonna be COLD.$"

OzoneInstitute_Text_DessAndEmberDefeated:
	.string "DESS: My forecast was correct!\n"
	.string "EMBER: ...But you braved that storm!$"

OzoneInstitute_Text_DessAndEmberPostBattle:
	.string "EMBER: Maybe I should have worn\n"
	.string "       more layers...\p"
	.string "DESS: Um, Ember? You train\n"
	.string "      Ice type Pokemon.$"

OzoneInstitute_Text_DessAndEmberNeedTwoMons:
	.string "DESS: You're not ready to hear\n"
	.string "      my forecast.\l"
	.string "EMBER: Maybe bring a friend with you?$"

OzoneInstitute_Text_NameRay:
	.string "Ray$"

OzoneInstitute_Text_RayIntro:
	.string "Allow me to set a scene for you.\p"
	.string "Enter, stage left. Scout in green\n"
	.string "(viciously attractive).\p"
	.string "Scout walks north. What does our\n"
	.string "gallant hero encounter?\l"
	.string "The human traffic jam, {PLAYER}!\p"
	.string "You make me want to drive down\n"
	.string "the opposite lane of a freeway.\l"
	.string "I would, of course, swerve\l"
	.string "masterfully and avoid death, but\l"
	.string "it WOULD raise my blood pressure.\p"
	.string "(Ray produces a blood\n"
	.string "pressure monitoring device.\l"
	.string "They force you to pump it up.)\p"
	.string "Told you. Look at the number\n"
	.string "you made my blood pressure climb to.\l"
	.string "128 over 85!\l"
	.string "(That's bad. (I think.))\p"
	.string "My aim with this upcoming beatdown\n"
	.string "is to raise yours higher.\l"
	.string "If a heart attack were to\l"
	.string "happen, so be it. (Darwinism)$"

OzoneInstitute_Text_RayDefeat:
	.string "It seems 128 over 85 was\n"
	.string "actually my odds of victory.$"

OzoneInstitute_Text_RayLeaves:
	.string "Whatever. Winning was not\n"
	.string "my objective this time anyway.\p"
	.string "(Ray monitors your blood pressure.)\p"
	.string "131...over...92...\n"
	.string "Well. The numbers are bigger.\l"
	.string "I count this as a decisive win.\p"
	.string "Hmph. ...Now that I think about it,\n"
	.string "what are you doing, showing up\l"
	.string "to my place of work (In that\l"
	.string "outfit, too)?\p"
	.string "If your plan is to apply to\n"
	.string "become part of Team Ozone, trust\l"
	.string "me, I will pull rank and get\l"
	.string "that application terminated.\p"
	.string "Go pal around with my managers\n"
	.string "all you want. It will get you\l"
	.string "nowhere (and potentially\l"
	.string "kicked out).\p"
	.string "I would much rather you get\n"
	.string "a job that takes you far away\l"
	.string "(ice road trucker maybe).\p"
	.string "I am off.$"
