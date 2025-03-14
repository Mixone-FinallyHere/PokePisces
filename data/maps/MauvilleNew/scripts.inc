.set LOCALID_P_MAN, 7
.set LOCALID_BONDING, 8
.set LOCALID_RAY, 9

MauvilleNew_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MauvilleNew_OnLoad
	.byte 0

MauvilleNew_OnLoad:
	call_if_gt VAR_RAY_STATE, 3, MauvilleNew_EventScript_RemoveRay
	call_if_lt VAR_OLD_GUYS_STATE, 2, MauvilleNew_EventScript_RemovePowerlessMan
	call_if_gt VAR_OLD_GUYS_STATE, 2, MauvilleNew_EventScript_RemovePowerlessMan
	call_if_lt VAR_OLD_GUYS_STATE, 18, MauvilleNew_EventScript_RemoveMrBonding
	end

MauvilleNew_EventScript_RemoveRay::
	removeobject LOCALID_RAY
	setflag FLAG_TEMP_13
	return

MauvilleNew_EventScript_RemovePowerlessMan::
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	return

MauvilleNew_EventScript_RemoveMrBonding::
	removeobject LOCALID_BONDING
	setflag FLAG_TEMP_12
	return

MauvilleNew_EventScript_Kizuna::
	speakername MauvilleNew_Text_NameKizuna
	msgbox MauvilleNew_Text_LookingForClues, MSGBOX_NPC
    end

MauvilleNew_EventScript_Clue1::
	msgbox MauvilleNew_Text_Clue1, MSGBOX_NPC
    end

MauvilleNew_EventScript_Clue2::
	msgbox MauvilleNew_Text_Clue2, MSGBOX_NPC
    end

MauvilleNew_EventScript_Clue3::
	msgbox MauvilleNew_Text_Clue3, MSGBOX_NPC
    end

MauvilleNew_EventScript_Clue4::
	msgbox MauvilleNew_Text_Clue4, MSGBOX_NPC
    end

MauvilleNew_EventScript_MrBonding::
	lock
	faceplayer
	goto_if_eq VAR_OLD_GUYS_STATE, 19, MauvilleNew_EventScript_MrBondingPostBattle
	goto_if_ge VAR_OLD_GUYS_STATE, 20, MauvilleNew_EventScript_MrBondingAfterGym
	speakername MauvilleNew_Text_NameMrBonding
	msgbox MauvilleNew_Text_YouHaveArrived, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BONDING, MauvilleNew_Movement_FaceDown
	waitmovement 0
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleNew_EventScript_PlayerNorthMove
	call_if_eq VAR_FACING, DIR_EAST, MauvilleNew_EventScript_PlayerEastMove
	call_if_eq VAR_FACING, DIR_SOUTH, MauvilleNew_EventScript_PlayerSouthMove
	call_if_eq VAR_FACING, DIR_WEST, MauvilleNew_EventScript_PlayerWestMove
	delay 4
	speakername MauvilleNew_Text_NameMrBonding
	msgbox MauvilleNew_Text_BondingIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_MR_BONDING, MauvilleNew_Text_BondingDefeated
	goto MauvilleNew_EventScript_MrBondingBeaten
	release
	end

MauvilleNew_Movement_FaceDown:
	face_down
	step_end

MauvilleNew_EventScript_PlayerNorthMove::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleNew_Movement_GetIntoPosNorth
	waitmovement 0
	delay 4
	return

MauvilleNew_Movement_GetIntoPosNorth:
	walk_down
	walk_down
	walk_down
	face_up
	step_end

MauvilleNew_EventScript_PlayerEastMove::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleNew_Movement_GetIntoPosEast
	waitmovement 0
	delay 4
	return

MauvilleNew_Movement_GetIntoPosEast:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	face_up
	step_end

MauvilleNew_EventScript_PlayerSouthMove::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleNew_Movement_GetIntoPosSouth
	waitmovement 0
	delay 4
	return

MauvilleNew_Movement_GetIntoPosSouth:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	face_up
	step_end

MauvilleNew_EventScript_PlayerWestMove::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleNew_Movement_GetIntoPosWest
	waitmovement 0
	delay 4
	return

MauvilleNew_Movement_GetIntoPosWest:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	face_up
	step_end

MauvilleNew_EventScript_MrBondingBeaten::
	speakername MauvilleNew_Text_NameMrBonding
	msgbox MauvilleNew_Text_WellDone, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleNew_Movement_RejoinMrBonding
	waitmovement 0
	setvar VAR_OLD_GUYS_STATE, 19
	msgbox MauvilleNew_Text_SomeLoreDrops, MSGBOX_DEFAULT
	giveitem ITEM_LOADED_DICE
	speakername MauvilleNew_Text_NameMrBonding
	msgbox MauvilleNew_Text_GoToVerdanturf, MSGBOX_DEFAULT
	closemessage
	release
	end

MauvilleNew_Movement_RejoinMrBonding:
	walk_up
	walk_up
	walk_up
	step_end

MauvilleNew_EventScript_MrBondingPostBattle::
	speakername MauvilleNew_Text_NameMrBonding
	msgbox MauvilleNew_Text_TheBadgeAwaits, MSGBOX_AUTOCLOSE
	release
	end

MauvilleNew_EventScript_MrBondingAfterGym::
	speakername MauvilleNew_Text_NameMrBonding
	msgbox MauvilleNew_Text_ThankYouSincerely, MSGBOX_AUTOCLOSE
	release
	end

MauvilleNew_EventScript_RayEncounter1::
	lock
	applymovement LOCALID_RAY, MauvilleNew_Movement_RayEncounter1
	waitmovement 0
	goto MauvilleNew_EventScript_RayBattleStart
	release
	end

MauvilleNew_Movement_RayEncounter1:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	step_end

MauvilleNew_EventScript_RayEncounter2::
	lock
	applymovement LOCALID_RAY, MauvilleNew_Movement_RayEncounter2
	waitmovement 0
	goto MauvilleNew_EventScript_RayBattleStart
	release
	end

MauvilleNew_Movement_RayEncounter2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MauvilleNew_EventScript_RayEncounter3::
	lock
	applymovement LOCALID_RAY, MauvilleNew_Movement_RayEncounter3
	waitmovement 0
	goto MauvilleNew_EventScript_RayBattleStart
	release
	end

MauvilleNew_Movement_RayEncounter3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	step_end

MauvilleNew_EventScript_RayEncounter4::
	lock
	applymovement LOCALID_RAY, MauvilleNew_Movement_RayEncounter4
	waitmovement 0
	goto MauvilleNew_EventScript_RayBattleStart
	release
	end

MauvilleNew_Movement_RayEncounter4:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

MauvilleNew_EventScript_RayBattleStart::
	speakername MauvilleNew_Text_NameRay
	msgbox MauvilleNew_Text_RayIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_RAY_4, MauvilleNew_Text_RayDefeat
	goto MauvilleNew_EventScript_RayLeaves
	speakername NULL
	release
	end

MauvilleNew_EventScript_RayLeaves::
	speakername MauvilleNew_Text_NameRay
	msgbox MauvilleNew_Text_RayLeaves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RAY, MauvilleNew_Movement_RayLeaves
	waitmovement 0
	removeobject LOCALID_RAY
	speakername NULL
	setflag FLAG_TEMP_13
	setvar VAR_RAY_STATE, 4
	release
	end

MauvilleNew_Movement_RayLeaves:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleNew_EventScript_Meralcore::
	lock
	msgbox MauvilleNew_Text_DisturbMeralcore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleNew_EventScript_MeralcoreBattle
	closemessage
	release
	end

MauvilleNew_EventScript_MeralcoreBattle::
	delay 16
	setwildbattle SPECIES_MERALCORE, 40
	playmoncry SPECIES_MERALCORE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	removeobject VAR_LAST_TALKED
	release
	end

MauvilleNew_EventScript_Kurt::
    trainerbattle_single TRAINER_P_KURT, MauvilleNew_Text_KurtIntro, MauvilleNew_Text_KurtDefeated
    msgbox MauvilleNew_Text_KurtPostBattle, MSGBOX_AUTOCLOSE
    end

MauvilleNew_EventScript_Kirst::
    trainerbattle_single TRAINER_P_KIRST, MauvilleNew_Text_KirstIntro, MauvilleNew_Text_KirstDefeated
    msgbox MauvilleNew_Text_KirstPostBattle, MSGBOX_AUTOCLOSE
    end

MauvilleNew_EventScript_Maia::
    trainerbattle_single TRAINER_P_MAIA, MauvilleNew_Text_MaiaIntro, MauvilleNew_Text_MaiaDefeated
    msgbox MauvilleNew_Text_MaiaPostBattle, MSGBOX_AUTOCLOSE
    end

MauvilleNew_EventScript_Miguel::
    trainerbattle_single TRAINER_P_MIGUEL, MauvilleNew_Text_MiguelIntro, MauvilleNew_Text_MiguelDefeated
    msgbox MauvilleNew_Text_MiguelPostBattle, MSGBOX_AUTOCLOSE
    end

MauvilleNew_Text_KurtIntro:
	.string "intro$"

MauvilleNew_Text_KurtDefeated:
	.string "defeat$"

MauvilleNew_Text_KurtPostBattle:
	.string "post$"

MauvilleNew_Text_KirstIntro:
	.string "intro$"

MauvilleNew_Text_KirstDefeated:
	.string "defeat$"

MauvilleNew_Text_KirstPostBattle:
	.string "post$"

MauvilleNew_Text_MaiaIntro:
	.string "intro$"

MauvilleNew_Text_MaiaDefeated:
	.string "defeat$"

MauvilleNew_Text_MaiaPostBattle:
	.string "post$"

MauvilleNew_Text_MiguelIntro:
	.string "intro$"

MauvilleNew_Text_MiguelDefeated:
	.string "defeat$"

MauvilleNew_Text_MiguelPostBattle:
	.string "post$"

MauvilleNew_Text_NameKizuna:
	.string "Kizuna$"

MauvilleNew_Text_NameMrBonding:
	.string "Mr. Bonding$"

MauvilleNew_Text_LookingForClues:
	.string "I've been asking anyone who\n"
	.string "will listen. But I got nothing.\l"
	.string "Let's try and pry for info.$"

MauvilleNew_Text_Clue1:
	.string "I've been really wanting\n"
	.string "to explore the Trick House!\l"
	.string "I hear its like an indoor\l"
	.string "theme park. The Trick Master,\l"
	.string "Giddy, keeps a tight lip on its\l"
	.string "location, though.\p"
	.string "I've at least heard that it's\n"
	.string "nearby New Mauville.$"

MauvilleNew_Text_Clue2:
	.string "The Trick House? Yeah, I've been.\n"
	.string "But ol' Giddy doesn't like\l"
	.string "people revealing the location.\l"
	.string "He says it's like the puzzle\l"
	.string "before the puzzle, or whatever.\p"
	.string "I'll give you a hint.\n"
	.string "From the front door, you can\l"
	.string "smell fresh crops.$"

MauvilleNew_Text_Clue3:
	.string "I live in an apartment on the\n"
	.string "west side of New Mauville.\l"
	.string "And I tell you, I sometimes\l"
	.string "hear the darndest noises.\l"
	.string "It's like there's some carnival\l"
	.string "going on just outside of the city!\p"
	.string "But I haven't heard of any\n"
	.string "travelling circus coming near\l"
	.string "New Mauville in some time.\l"
	.string "Curious...$"

MauvilleNew_Text_Clue4:
	.string "That old nutjob Giddy sometimes\n"
	.string "shops for props in the mall.\p"
	.string "I often see him with tree bristles\n"
	.string "stuck into his outfit.\l"
	.string "Either that's his fashion sense,\l"
	.string "or he has to brush past a lot\l"
	.string "of trees to make it here\l"
	.string "from his house.\p"
	.string "Either is likely.$"

MauvilleNew_Text_YouHaveArrived:
	.string "Ah! You have arrived, {PLAYER}.\n"
	.string "I'm happy to see you.\p"
	.string "Since my... transformation, I\n"
	.string "have unlocked mental power beyond\l"
	.string "my wildest machinations.\l"
	.string "It is both overwhelming, yet\l"
	.string "in the same amounts comforting.\p"
	.string "Why do I call myself the moniker\n"
	.string "of Mr. Bonding? Simple. I am\l"
	.string "a living representation of the\l"
	.string "unbreakable bonds between humans.\p"
	.string "Think about it. There are 6\n"
	.string "sets of memories in my brain.\l"
	.string "6 sets of emotions in my heart.\l"
	.string "And they have all been united\l"
	.string "in peace.\p"
	.string "...In fact, all 6 of those\n"
	.string "consciousnesses would like to\l"
	.string "battle you now, {PLAYER}.\l"
	.string "Will you do us the honor?$"

MauvilleNew_Text_BondingIntro:
	.string "Let's get started, shall we?\n"
	.string "It's Bonding time!$"

MauvilleNew_Text_BondingDefeated:
	.string "Much like how you defeated\n"
	.string "six Pokemon just now, you have\l"
	.string "likewise defeated six men.\p"
	.string "Bravo.$"

MauvilleNew_Text_WellDone:
	.string "The bond between you and your\n"
	.string "Pokemon shows no bounds.\l"
	.string "I am happy to call you\l"
	.string "a friend, {PLAYER}.$"

MauvilleNew_Text_SomeLoreDrops:
	.string "I must tell you that upon\n"
	.string "reaching this form, I became\l"
	.string "privy to the true origins of those\l"
	.string "five elderly men.\p"
	.string "They were, at one point,\n"
	.string "just a single individual.\l"
	.string "This individual was gifted by\l"
	.string "some miracle with a set\l"
	.string "of powers known as O-Powers.\p"
	.string "The point of those O-Powers were\n"
	.string "to gift to others, to make their\l"
	.string "days better or easier.\l"
	.string "A true act of kindness.\p"
	.string "Towards the end of that individual's\n"
	.string "life, they fell ill. They then\l"
	.string "wandered into the desert, alone,\l"
	.string "for five whole days.\p"
	.string "They never returned.\p"
	.string "Who did return... but the\n"
	.string "five old men.\l"
	.string "Giddy. Rydel. Dock. Nob.\l"
	.string "And The Storyteller.\p"
	.string "Each not knowing their exact\n"
	.string "origin, but still harboring an\l"
	.string "inner drive to bring people together.\p"
	.string "That original individual was the\n"
	.string "very first Mr. Bonding.\l"
	.string "And I... am the second.\p"
	.string "...Why was Kizuna the ideal vessel\n"
	.string "for the powers of those old men?\l"
	.string "Simple.\p"
	.string "A man who feels himself to be\n"
	.string "powerless may well be the perfect\l"
	.string "blueprint upon which to infuse power.\p"
	.string "...\p"
	.string "The part of my brain that contains\n"
	.string "Kizuna's mind is urging me\l"
	.string "to give to you this.$"

MauvilleNew_Text_GoToVerdanturf:
	.string "It seems he much enjoyed that item.\n"
	.string "Regardless, I have a favor to repay.\p"
	.string "Go forth to the gate of Verdanturf.\n"
	.string "I will be getting you a personal\l"
	.string "audience with the Gym Leader.$"

MauvilleNew_Text_TheBadgeAwaits:
	.string "Go forth to the gate of Verdanturf.\n"
	.string "I will be getting you a personal\l"
	.string "audience with the Gym Leader.$"

MauvilleNew_Text_ThankYouSincerely:
	.string "I see you proudly wearing\n"
	.string "Wattson's badge on your lapel.\p"
	.string "You've made me proud, {PLAYER}.\n"
	.string "Thank you for all you've done\l"
	.string "for... all 6 of them.$"

MauvilleNew_Text_NameRay:
	.string "Ray$"

MauvilleNew_Text_RayIntro:
	.string "Colour me surprised.\n"
	.string "The pastel-colored single-celled\l"
	.string "organism arrived, manging around\l"
	.string "like a Fuzky without its collar.\l"
	.string "I will need to consume collard greens\l"
	.string "to recover from the calorie\l"
	.string "intake your presence infuses\l"
	.string "within me.\p"
	.string "You wish to tussle. (Violent)\n"
	.string "I wish to tussle. (Self-defense)\l"
	.string "No more words need be said.\p"
	.string "Following your defeat, I shall have\n"
	.string "a painting commisioned. And\l"
	.string "it will be enchristened\l"
	.string "“Baby's Last Words”.$"

MauvilleNew_Text_RayDefeat:
	.string "The tattered rogue pulls a fast\n"
	.string "one on the gallant hero in green\l"
	.string "again? (Ludo-narrative Dissonance)$"

MauvilleNew_Text_RayLeaves:
	.string "I must admit you vex me so.\n"
	.string "How do I continue to lose\l"
	.string "to the likes of you (unkempt)\l"
	.string "over and over? There is no\l"
	.string "earthly (or marsly) explanation\l"
	.string "for these events.\p"
	.string "I shudder to think I am growing\n"
	.string "to enjoy our periodic bouts\l"
	.string "(must be Stockholm Syndrome).\l"
	.string "Though it is only because I\l"
	.string "do not often lose. Not because\l"
	.string "of your repugnant stench.\l"
	.string "And terrible smile.\l"
	.string "I could go on.\p"
	.string "But I will not.\n"
	.string "Try not to burgle the many\l"
	.string "shops in New Mauville.\l"
	.string "That just registers to me\l"
	.string "as something you would attempt\l"
	.string "(and likely fail).$"

MauvilleNew_Text_DisturbMeralcore:
	.string "disturb this mf?$"
