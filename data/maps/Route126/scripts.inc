.set LOCALID_RAY, 5
.set LOCALID_PARRYER, 21
.set LOCALID_DIRECTOR, 32
.set LOCALID_GABBY, 25
.set LOCALID_TY, 24

Route126_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route126_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, Route126_OnTransition
	.byte 0

Route126_OnTransition:
	call_if_eq VAR_GABBY_AND_TY_STATE, 0, Route126_EventScript_RemoveInterviewers
	call_if_lt VAR_ORBS_QUEST_STATE, 7, Route126_EventScript_RemoveDirector
	call_if_gt VAR_ORBS_QUEST_STATE, 7, Route126_EventScript_RemoveDirector
	goto_if_lt VAR_SPACE_CENTER_QUEST_STATE, 3, Route126_EventScript_HideMeteors
	end

Route126_EventScript_RemoveInterviewers::
	removeobject LOCALID_GABBY
	removeobject LOCALID_TY
	setflag FLAG_TEMP_19
	return

Route126_EventScript_RemoveDirector::
	removeobject LOCALID_DIRECTOR
	setflag FLAG_TEMP_1D
	return

Route126_EventScript_HideMeteors::
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	setflag FLAG_TEMP_13
	setflag FLAG_TEMP_14
	setflag FLAG_TEMP_15
	setflag FLAG_TEMP_16
	end

Route126_OnFrame:
	map_script_2 VAR_SPACE_CENTER_QUEST_STATE, 69, Route126_EventScript_StartInvasion
	.2byte 0

Route126_EventScript_StartInvasion::
	lock
	setvar VAR_SPACE_CENTER_QUEST_STATE, 2
	applymovement OBJ_EVENT_ID_PLAYER, Route126_Movement_WalkToRocket
	waitmovement 0
	speakername Route126_Text_NameLovelace
	msgbox Route126_Text_TheyreInvading, MSGBOX_DEFAULT
	setwildbattle SPECIES_UHEFOE, 18
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 0, 0, 2
	playmoncry SPECIES_UHEFOE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	speakername NULL
	msgbox Route126_Text_UhefoeCry, MSGBOX_DEFAULT
	waitmessage
	setmetatile 62, 9, METATILE_Mossdeep_RocketUhefoeLeft, TRUE
	setmetatile 63, 9, METATILE_Mossdeep_RocketUhefoeRight, TRUE
	special DrawWholeMapView
	speakername Route126_Text_NameLovelace
	msgbox Route126_Text_UhefoeAppears, MSGBOX_DEFAULT
	speakername NULL
	closemessage
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	goto Route126_EventScript_YouDidIt
	release
	end

Route126_Movement_WalkToRocket:
	walk_up
	walk_up
	walk_up
	step_end

Route126_EventScript_YouDidIt::
	setmetatile 62, 9, METATILE_Mossdeep_RocketNormalLeft, TRUE
	setmetatile 63, 9, METATILE_Mossdeep_RocketNormalRight, TRUE
	special DrawWholeMapView
	speakername Route126_Text_NameLovelace
	msgbox Route126_Text_YouDidIt, MSGBOX_DEFAULT
	speakername NULL
	giveitem ITEM_GRAVITY_CORE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_SPACE_CENTER_QUEST_STATE, 50
	warp MAP_COSMOSS_SPACE_CENTER, 10, 28
	waitstate
	release
	end

Route126_EventScript_Lovelace::
	lock
	goto_if_ge VAR_SPACE_CENTER_QUEST_STATE, 3, Route126_EventScript_LovelacePost
	msgbox Route126_Text_Lovelace, MSGBOX_AUTOCLOSE
	release
	end

Route126_EventScript_LovelacePost::
	speakername Route126_Text_NameLovelace
	msgbox Route126_Text_LovelacePost, MSGBOX_AUTOCLOSE
	release
	end

Route126_EventScript_Stella::
    trainerbattle_single TRAINER_P_STELLA, Route126_Text_StellaIntro, Route126_Text_StellaDefeated
    msgbox Route126_Text_StellaPostBattle, MSGBOX_AUTOCLOSE
    end

Route126_EventScript_Isaac::
    trainerbattle_single TRAINER_P_ISAAC, Route126_Text_IsaacIntro, Route126_Text_IsaacDefeated
    msgbox Route126_Text_IsaacPostBattle, MSGBOX_AUTOCLOSE
    end

Route126_EventScript_Rise::
    trainerbattle_single TRAINER_P_RISE, Route126_Text_RiseIntro, Route126_Text_RiseDefeated
    msgbox Route126_Text_RisePostBattle, MSGBOX_AUTOCLOSE
    end

Route126_EventScript_Yu::
    trainerbattle_single TRAINER_P_YU, Route126_Text_YuIntro, Route126_Text_YuDefeated
    msgbox Route126_Text_YuPostBattle, MSGBOX_AUTOCLOSE
    end

Route126_EventScript_Geiger::
    trainerbattle_single TRAINER_P_GEIGER, Route126_Text_GeigerIntro, Route126_Text_GeigerDefeated
    msgbox Route126_Text_GeigerPostBattle, MSGBOX_AUTOCLOSE
    end

Route126_EventScript_York::
    trainerbattle_single TRAINER_P_YORK, Route126_Text_YorkIntro, Route126_Text_YorkDefeated
    msgbox Route126_Text_YorkPostBattle, MSGBOX_AUTOCLOSE
    end

Route126_EventScript_Rika::
    trainerbattle_single TRAINER_P_RIKA, Route126_Text_RikaIntro, Route126_Text_RikaDefeated
    msgbox Route126_Text_RikaPostBattle, MSGBOX_AUTOCLOSE
    end

Route126_EventScript_Pete::
    trainerbattle_single TRAINER_P_PETE, Route126_Text_PeteIntro, Route126_Text_PeteDefeated
    msgbox Route126_Text_PetePostBattle, MSGBOX_AUTOCLOSE
    end

Route126_EventScript_RayEncounterNorth::
	lock
	setflag FLAG_TEMP_18
	applymovement LOCALID_RAY, Route126_Movement_RayEncounterNorth
	waitmovement 0
	goto Route126_EventScript_RayBattleStart
	release
	end

Route126_Movement_RayEncounterNorth:
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	emote_question_mark
	walk_left
	walk_left
	walk_left
	step_end

Route126_EventScript_RayEncounterSouth::
	lock
	setflag FLAG_TEMP_17
	applymovement LOCALID_RAY, Route126_Movement_RayEncounterSouth
	waitmovement 0
	goto Route126_EventScript_RayBattleStart
	release
	end

Route126_Movement_RayEncounterSouth:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	emote_question_mark
	walk_left
	walk_left
	walk_left
	step_end

Route126_EventScript_RayBattleStart::
	msgbox Route126_Text_RayIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_RAY_1, Route126_Text_RayDefeat
	goto Route126_EventScript_RayLeaves
	release
	end

Route126_EventScript_RayLeaves::
	speakername Route126_Text_NameRay
	msgbox Route126_Text_RayLeaves, MSGBOX_DEFAULT
	closemessage
	speakername NULL
	goto_if_set FLAG_TEMP_18, Route126_EventScript_RayLeavesNorth
	goto_if_set FLAG_TEMP_17, Route126_EventScript_RayLeavesSouth
	release
	end

Route126_EventScript_RayLeavesNorth::
	applymovement LOCALID_RAY, Route126_Movement_RayLeavesNorth
	waitmovement 0
	removeobject LOCALID_RAY
	setflag FLAG_HIDE_RAY
	setvar VAR_RAY_STATE, 1
	release
	end

Route126_Movement_RayLeavesNorth:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route126_EventScript_RayLeavesSouth::
	applymovement LOCALID_RAY, Route126_Movement_RayLeavesSouth
	waitmovement 0
	removeobject LOCALID_RAY
	setflag FLAG_HIDE_RAY
	setvar VAR_RAY_STATE, 1
	release
	end

Route126_Movement_RayLeavesSouth:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route126_EventScript_SpaceCenterVarTest::
	lock
	setvar VAR_SPACE_CENTER_QUEST_STATE, 3
	msgbox Route126_Text_VarTest, MSGBOX_AUTOCLOSE
	release
	end

Route126_EventScript_ParryRocketScientist::
	lock
	faceplayer
	checkitem ITEM_TM_DETECT
	goto_if_eq VAR_RESULT, TRUE, Route126_EventScript_GaveDetectRS
	goto_if_eq VAR_TEMP_5, 3, Route126_EventScript_HitTheRocket
	msgbox Route126_Text_WorkingOnTheRocket, MSGBOX_AUTOCLOSE
	release
	end

Route126_EventScript_GaveDetectRS::
	msgbox Route126_Text_GaveDetectRS, MSGBOX_AUTOCLOSE
    release
    end

Route126_EventScript_HitTheRocket::
	msgbox Route126_Text_SayNoMore, MSGBOX_DEFAULT
	applymovement LOCALID_PARRYER, Route126_Movement_BBWalkUp
	applymovement OBJ_EVENT_ID_PLAYER, Route126_Movement_PlayerWatch
	waitmovement 0
	msgbox Route126_Text_ReadyToParry, MSGBOX_DEFAULT
	playse SE_M_MEGA_KICK
	waitse
	applymovement LOCALID_PARRYER, Route126_Movement_BBParry
	waitmovement 0
	playse SE_M_MEGA_KICK2
	waitse
	applymovement LOCALID_PARRYER, Route126_Movement_BBVictorious
	msgbox Route126_Text_Victorious, MSGBOX_DEFAULT
	giveitem ITEM_TM_DETECT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	applymovement LOCALID_PARRYER, Route126_Movement_BBWalkAway
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Route126_Movement_PlayerLookBack
	waitmovement 0
	msgbox Route126_Text_ThatWasEntertaining, MSGBOX_AUTOCLOSE
	release
	end

Route126_Movement_BBWalkUp:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

Route126_Movement_PlayerWatch:
	face_left
	step_end

Route126_Movement_BBParry:
	face_up
	delay_16
	delay_16
	delay_16
	jump_in_place_up
	walk_in_place_fast_up
	delay_8
	step_end

Route126_Movement_BBVictorious:
	face_right
	walk_in_place_right
	step_end

Route126_Movement_BBWalkAway:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	face_down
	step_end

Route126_Movement_PlayerLookBack:
	face_right
	step_end

Route126_EventScript_ParryBlackBelt::
	lock
	faceplayer
	checkitem ITEM_TM_DETECT
	goto_if_eq VAR_RESULT, TRUE, Route126_EventScript_GaveDetectBB
	setvar VAR_TEMP_5, 3
	msgbox Route126_Text_IWantToParry, MSGBOX_AUTOCLOSE
	release
	end

Route126_EventScript_GaveDetectBB::
	msgbox Route126_Text_GaveDetectBB, MSGBOX_AUTOCLOSE
    release
    end

Route126_EventScript_SwiftGirl::
    lock
	faceplayer
	checkitem ITEM_TM_SWIFT
	goto_if_eq VAR_RESULT, TRUE, Route126_EventScript_GaveSwift
	msgbox Route126_Text_ShootingStars, MSGBOX_DEFAULT
	giveitem ITEM_TM_SWIFT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

Route126_EventScript_GaveSwift::
    msgbox Route126_Text_GaveSwift, MSGBOX_AUTOCLOSE
    release
    end

Route126_EventScript_OzoneRoadblocker1::
	msgbox Route126_Text_OzoneRoadblocker1, MSGBOX_NPC
	end

Route126_EventScript_OzoneRoadblocker2::
	msgbox Route126_Text_OzoneRoadblocker2, MSGBOX_NPC
	end

Route126_EventScript_OzoneRoadblocker3::
	msgbox Route126_Text_OzoneRoadblocker3, MSGBOX_NPC
	end

Route126_EventScript_Launchpad1::
	msgbox Route126_Text_Launchpad1, MSGBOX_SIGN
	end

Route126_EventScript_Launchpad2::
	msgbox Route126_Text_Launchpad2, MSGBOX_SIGN
	end

Route126_EventScript_Launchpad3::
	msgbox Route126_Text_Launchpad3, MSGBOX_SIGN
	end

Route126_EventScript_SpaceCenterSign::
	msgbox Route126_Text_SpaceCenterSign, MSGBOX_SIGN
	end

Route126_EventScript_CosmossSign::
	msgbox Route126_Text_CosmossSign, MSGBOX_SIGN
	end

Route126_EventScript_WereUnderSiege::
	lock
	faceplayer
	msgbox Route126_Text_WereUnderSiege, MSGBOX_DEFAULT
	closemessage
	warp MAP_SPACE_CENTER_SIEGE_CUTSCENE, 3, 7
	waitstate
	release
	end

Route126_Text_CosmossSign:
	.string "COSMOSS BRIDGE\n"
	.string "The link between Sootopolis City\l"
	.string "and Mossdeep City$"

Route126_Text_Launchpad1:
	.string "Rocket Launch Pad No. 01$"

Route126_Text_Launchpad2:
	.string "Rocket Launch Pad No. 02$"

Route126_Text_Launchpad3:
	.string "Rocket Launch Pad No. 03$"

Route126_Text_SpaceCenterSign:
	.string "THE COSMOSS SPACE CENTER\n"
	.string "To The Stars And Beyond!$"

Route126_Text_OzoneRoadblocker1:
	.string "Apologies, but I'm afraid that Cosmoss\n"
	.string "Bridge has a temporary closure.\p"
	.string "A meteorite impacted the bridge this\n"
	.string "morning and damaged its structural\l"
	.string "integrity.\p"
	.string "It shouldn't take much longer to be\n"
	.string "cleared up.$"

Route126_Text_OzoneRoadblocker2:
	.string "It's not every day that we get to\n"
	.string "crack open a fresh metorite\l"
	.string "and study it!\l"
	.string "Exciting developments!$"

Route126_Text_OzoneRoadblocker3:
	.string "Team Ozone and the Cosmoss Space\n"
	.string "Center work together regularly.\l"
	.string "Took us no time at all to come in\l"
	.string "with the assist!$"

Route126_Text_ShootingStars:
	.string "Ah, the beauty of shooting stars...\p"
	.string "You know, this bridge is a hotspot\n"
	.string "for viewing them. How romantic!\p"
	.string "Teach your Pokémon this move;\n"
	.string "that way, you can make your own\l"
	.string "personal meteor shower!$"

Route126_Text_GaveSwift:
	.string "I don't believe on making\n"
	.string "more than one wish on a shooting\l"
	.string "star. I'll save it for just\l"
	.string "the right moment in my life!$"

Route126_Text_WorkingOnTheRocket:
	.string "Very much hoping that this\n"
	.string "rocket's structural integrity\l"
	.string "is sound enough for launch...$"

Route126_Text_GaveDetectRS:
	.string "Thanks to that parry, I KNOW\n"
	.string "the rocket is sturdy as\l"
	.string "all get out!$"

Route126_Text_SayNoMore:
	.string "...What's that you're telling me?\n"
	.string "C-Can the rocket... fight?\p"
	.string "Surely you're joking. This is\n"
	.string "a state of the art vessel made of\l"
	.string "many tonnes of steel.\p"
	.string "Nothing could dent thi-\p"
	.string "SAY NO MORE!$"

Route126_Text_ReadyToParry:
	.string "Rocket-kun... my new arch-nemesis...!\n"
	.string "I have what it takes to match your\l"
	.string "strikes...! You will NOT win!\p"
	.string "(He is winding up...)$"

Route126_Text_Victorious:
	.string "(Blue energy is flaring around\n"
	.string "the black belt...)\p"
	.string "Victorious once again!\n"
	.string "Seems you were all talk, Rocket-kun...\p"
	.string "Allow me to pass some of my skills\n"
	.string "to your Pokémon... in the form of a TM.$"

Route126_Text_ThatWasEntertaining:
	.string "???? Ok???\p"
	.string "Didn't seem like he really did\n"
	.string "anything???$"

Route126_Text_IWantToParry:
	.string "Hai. I have trained for eons in\n"
	.string "the art... of parrying.\p"
	.string "I have not been challenged in\n"
	.string "quite some time.\p"
	.string "Could you possibly find me...\n"
	.string "a worthy opponent?$"

Route126_Text_GaveDetectBB:
	.string "The next opponent awaits me...$"

Route126_Text_MeteorsTest:
	.string "meteors unset$"

Route126_Text_NameRay:
	.string "Ray$"

Route126_Text_RayIntro:
	.string "Woah, woah, woah, slow down\n"
	.string "there, buster!\p"
	.string "This bridge is supposed to be off\n"
	.string "limits to non-Ozone-workers while we\l"
	.string "conduct VERY valuable research.\l"
	.string "I have to ask you to leave!\p"
	.string "…The rest of my teammates\n"
	.string "have left already?\p"
	.string "Hah! Nice attempt. Trying to pull a\n"
	.string "fast one… on me, THE Ray\l"
	.string "(of Team Ozone)!\p"
	.string "Hm… wait a tick.\p"
	.string "I think I recognize you!\p"
	.string "Yeah, that's right.\n"
	.string "You're that (supposed) hotshot\l"
	.string "(unconfirmed) from Littleroot!\p"
	.string "Now I REALLY feel a desire to knock\n"
	.string "you down a peg!\p"
	.string "(Ray makes a “come at me” gesture.)\p"
	.string "Let's tussle!!$"

Route126_Text_RayDefeat:
	.string "Are you KIDDING me!?$"

Route126_Text_RayLeaves:
	.string "Huff… that was a straight up fluke.\p"
	.string "You cheated, I let you win, I'm feeling\n"
	.string "under the weather, et cetera.\p"
	.string "In my post-loss-clarity state, I am\n"
	.string "now realizing that my team HAS left.\p"
	.string "Mm.\p"
	.string "Likely your fault.\p"
	.string "As we established, you are THE dirty\n"
	.string "cheat (worst of the worst) who\l"
	.string "smells (bad)!\p"
	.string "This won't be the last you see of Ray.\p"
	.string "I'll make sure of THAT!$"

Route126_Text_VarTest:
	.string "space center var set 3$"

Route126_Text_NameLovelace:
	.string "Cpt. Lovelace$"

Route126_Text_Lovelace:
	.string "All systems nominal here.\n"
	.string "Itching to embark whenever it's time.$"

Route126_Text_TheyreInvading:
	.string "…Hmm?\p"
	.string "Eiffel's reporting some\n"
	.string "kind of problem? Nonsense.\p"
	.string "His lazy bum is probably using this as\n"
	.string "an excuse to get sent home early.$"

Route126_Text_UhefoeCry:
	.string "(You hear a Pokémon's cry.)$"

Route126_Text_UhefoeAppears:
	.string "Crud, watch out…\n"
	.string "looks like something wants to give us\l"
	.string "a warm welcome…!$"

Route126_Text_YouDidIt:
	.string "Thanks for taking care of that thing.\p"
	.string "Here, take this;\n"
	.string "the Pokémon was holding it.\p"
	.string "Think of it as a… trophy.$"

Route126_Text_LovelacePost:
	.string "I'm on high alert for Uhefoe now.\n"
	.string "None of those barrels of bolts\l"
	.string "are making it past me!$"

Route126_Text_StellaIntro:
	.string "Fixing up problems with the\n"
	.string "launch pads is hard work!\l"
	.string "How about I cool down with a battle?$"

Route126_Text_StellaDefeated:
	.string "You rocketted up the rankings!$"

Route126_Text_StellaPostBattle:
	.string "As you could maybe imagine, a lot\n"
	.string "of crap goes wrong on the bridge.\l"
	.string "And of course, its with expensive\l"
	.string "as heck equipment, too!$"

Route126_Text_IsaacIntro:
	.string "Did... did you throw an\n"
	.string "apple at my head?$"

Route126_Text_IsaacDefeated:
	.string "Seems my hypothesis\n"
	.string "was proven false.$"

Route126_Text_IsaacPostBattle:
	.string "Must have been gravity or something\n"
	.string "that brought that apple down\l"
	.string "on my noggin.\p"
	.string "But, erm... I uh, don't see\n"
	.string "any trees nearby...\p"
	.string "Maybe someone DID throw\n"
	.string "one at me!$"

Route126_Text_RiseIntro:
	.string "Well, well, well.\p"
	.string "Look what we have here!\n"
	.string "My new HUMAN WALLET!$"

Route126_Text_RiseDefeated:
	.string "You couldn't even spare\n"
	.string "me a coin!?$"

Route126_Text_RisePostBattle:
	.string "I just wanted some ice cream...\n"
	.string "waaahhhhh....!\p"
	.string "(Those tears are definitely fake.)$"

Route126_Text_YuIntro:
	.string "Give me some money!\n"
	.string "Or else... I shoot!$"

Route126_Text_YuDefeated:
	.string "ACK! I forgot to fill it!$"

Route126_Text_YuPostBattle:
	.string "Look, I didn't mean anything I said!\n"
	.string "Please don't get me time-out!\l"
	.string "PLEASE!$"

Route126_Text_GeigerIntro:
	.string "Daddy funded this specific rocket.\n"
	.string "Isn't that impressive? Ah,\l"
	.string "it feels SPLENDID to be rich!$"

Route126_Text_GeigerDefeated:
	.string "This loss is nothing.\n"
	.string "I win by pure net worth alone!$"

Route126_Text_GeigerPostBattle:
	.string "Shoo-shoo now! I'll end up\n"
	.string "catching your poverty.$"

Route126_Text_YorkIntro:
	.string "Batten down the hatches!\n"
	.string "Trainer ahoy!$"

Route126_Text_YorkDefeated:
	.string "Left me high and dry!$"

Route126_Text_YorkPostBattle:
	.string "And here I thought besting you\n"
	.string "would be smooth sailing.\l"
	.string "Whelp. Guess I don't run as tight\l"
	.string "of a ship as I first thought.$"

Route126_Text_RikaIntro:
	.string "A battle? Well, I suppose I have\n"
	.string "the time until my crew sets sail.$"

Route126_Text_RikaDefeated:
	.string "Whoa! Rocked me like a hurricane!$"

Route126_Text_RikaPostBattle:
	.string "Hopefully the others don't mind if\n"
	.string "I visit the Pokemon Center before\l"
	.string "we set sail...$"

Route126_Text_PeteIntro:
	.string "Extree, extree! Read all about it!\p"
	.string "(The Paper Boy hands you a sheet\n"
	.string "of white paper with the words,\l"
	.string "“You're About To Lose” on it.)$"

Route126_Text_PeteDefeated:
	.string "SHOCKING SCANDAL!\n"
	.string "Paper Boy Pete LOSES in\l"
	.string "landslide to {PLAYER}!$"

Route126_Text_PetePostBattle:
	.string "I am just going to embellish\n"
	.string "the story some when I get a chance.$"

Route126_Text_GugumbirNeedTwoMons:
	.string "need 2 dood$"

Route126_Text_WereUnderSiege:
	.string "Officer! You're an officer, yes?\n"
	.string "Well, even if you aren't, I\l"
	.string "designate you an honorary one\l"
	.string "for the time being. You look\l"
	.string "strong. We need your help.\p"
	.string "Jacobi... that fool...!\n"
	.string "He has somehow built some\l"
	.string "infernal death machine without\l"
	.string "our knowledge and is planning\l"
	.string "on using it to destroy\l"
	.string "our beloved space center!\p"
	.string "You have to help us stop him!$"
