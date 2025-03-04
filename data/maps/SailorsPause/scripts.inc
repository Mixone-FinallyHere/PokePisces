.set LOCALID_RAY, 4

SailorsPause_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SailorsPause_OnLoad
	.byte 0

SailorsPause_OnLoad:
	call_if_gt VAR_RAY_STATE, 4, SailorsPause_EventScript_RemoveRay
	end

SailorsPause_EventScript_RemoveRay::
	removeobject LOCALID_RAY
	setflag FLAG_TEMP_13
	return

SailorsPause_EventScript_RayEncounter::
	lock
	applymovement LOCALID_RAY, SailorsPause_Movement_RayEncounter
	waitmovement 0
	speakername SailorsPause_Text_NameRay
	msgbox SailorsPause_Text_RayIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_RAY_5, SailorsPause_Text_RayDefeat
	goto SailorsPause_EventScript_RayLeaves
	speakername NULL
	release
	end

SailorsPause_Movement_RayEncounter:
	emote_exclamation_mark
	delay_16
	jump_in_place_up
	jump_in_place_up
	jump_in_place_up
	step_end

SailorsPause_EventScript_RayLeaves::
	speakername SailorsPause_Text_NameRay
	msgbox SailorsPause_Text_RayLeaves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RAY, SailorsPause_Movement_RayLeaves
	waitmovement 0
	removeobject LOCALID_RAY
	speakername NULL
	setflag FLAG_TEMP_13
	setvar VAR_RAY_STATE, 5
	release
	end

SailorsPause_Movement_RayLeaves:
	walk_fast_right
	jump_2_right
	jump_2_down
	walk_fast_right
	jump_2_right
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	jump_2_right
	step_end

SailorsPause_EventScript_MirageIslandSailor::
	lock
	faceplayer
	goto_if_ge VAR_ZORUA_QUEST_STATE, 4, SailorsPause_EventScript_MirageIslandGone
	msgbox SailorsPause_Text_NeedMiragePokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, CheckZorua
	goto_if_eq VAR_RESULT, TRUE, SailorsPause_EventScript_SailToMirageIsland
	msgbox SailorsPause_Text_ComeBackIfYouFind, MSGBOX_AUTOCLOSE
	release
	end

SailorsPause_EventScript_SailToMirageIsland::
	msgbox SailorsPause_Text_LetsSetSail, MSGBOX_DEFAULT
	closemessage
	delay 8
	warp MAP_MIRAGE_ISLAND, 6, 16
	waitstate
	release
	end

SailorsPause_EventScript_MirageIslandGone::
	msgbox SailorsPause_Text_MirageIslandGone, MSGBOX_AUTOCLOSE
	release
	end

SailorsPause_EventScript_Valerie::
    trainerbattle_single TRAINER_P_VALERIE, SailorsPause_Text_ValerieIntro, SailorsPause_Text_ValerieDefeated
    msgbox SailorsPause_Text_ValeriePostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPause_EventScript_Queequeg::
    trainerbattle_single TRAINER_P_QUEEQUEG, SailorsPause_Text_QueequegIntro, SailorsPause_Text_QueequegDefeated
    msgbox SailorsPause_Text_QueequegPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPause_EventScript_Jess::
    trainerbattle_single TRAINER_P_JESS, SailorsPause_Text_JessIntro, SailorsPause_Text_JessDefeated
    msgbox SailorsPause_Text_JessPostBattle, MSGBOX_AUTOCLOSE
    end

SailorsPause_Text_ValerieIntro:
	.string "intro$"

SailorsPause_Text_ValerieDefeated:
	.string "defeat$"

SailorsPause_Text_ValeriePostBattle:
	.string "post$"

SailorsPause_Text_QueequegIntro:
	.string "intro$"

SailorsPause_Text_QueequegDefeated:
	.string "defeat$"

SailorsPause_Text_QueequegPostBattle:
	.string "post$"

SailorsPause_Text_JessIntro:
	.string "intro$"

SailorsPause_Text_JessDefeated:
	.string "defeat$"

SailorsPause_Text_JessPostBattle:
	.string "post$"

SailorsPause_Text_NameRay:
	.string "Ray$"

SailorsPause_Text_RayIntro:
	.string "...By jove. Even at sea,\n"
	.string "I cannot be rid of you.\p"
	.string "For your information, Archie\n"
	.string "(the pompous fool that he is) sent\l"
	.string "me on a mission to scan the oceans\l"
	.string "nearby to Pacifidlog and Sootopolis\l"
	.string "for any illegal garbage dumping\l"
	.string "boats offloading trash.\p"
	.string "He gave me the option of using a\n"
	.string "brand new motorboat (loud and\l"
	.string "obnoxious) or a simple wooden\l"
	.string "rowboat (lets you build arm muscle).\l"
	.string "You can see how easy the choice was.\p"
	.string "Yet, I have yet to come upon\n"
	.string "any garbage vessels. Yet.\l"
	.string "Oh, but I did happen upon you.\l"
	.string "Technically, counting as\l"
	.string "a garbage vessel.\p"
	.string "So, this defeat you will soon\n"
	.string "suffer (a full wipe, likely)\l"
	.string "is just me doing my job.\l"
	.string "Simply business.$"

SailorsPause_Text_RayDefeat:
	.string "You kept... making...\n"
	.string "urp... my boat... rock...$"

SailorsPause_Text_RayLeaves:
	.string "Shocking development...\n"
	.string "the great and indominatable Ray...\l"
	.string "is getting... urp...\l"
	.string "sea sick...\p"
	.string "This is an unheard... of...\n"
	.string "devel-... URP...! ....ment.\l"
	.string "I must... must get to...\l"
	.string "terra... firma...!$"

SailorsPause_Text_NeedMiragePokemon:
	.string "Ahoy, trainer. I have been\n"
	.string "researchin' the tale o'\l"
	.string "Mirage Island extensively.\p"
	.string "Y'ever hear of the island?\n"
	.string "Said to lie in the seas of\l"
	.string "Hoenn, it only fully appears\l"
	.string "extremely rarely. Buncha\l"
	.string "seadogs don't even believe\l"
	.string "it to be a real place.\p"
	.string "But, I've been chartin' the waters.\n"
	.string "I'd wager I've pinpointed\l"
	.string "its location, dead on.\p"
	.string "Problem is, if I'm gonna head\n"
	.string "out there, I would want a\l"
	.string "Pokemon with me that has\l"
	.string "an affinity for mirages.\l"
	.string "Y'know... in case I somehow\l"
	.string "get my tuckus trapped there.$"

SailorsPause_Text_ComeBackIfYouFind:
	.string "If you can find me a Pokemon\n"
	.string "that's a veritable mirage expert,\l"
	.string "head on back here n' I'll\l"
	.string "take ya to the island with me.$"

SailorsPause_Text_LetsSetSail:
	.string "That Zorua you have...\n"
	.string "It will do nicely.\p"
	.string "I've 'eard many a tale of\n"
	.string "their powers of illusion.\l"
	.string "Hope the little bugger\l"
	.string "will assist us 'ere.\p"
	.string "Let's set off!$"

SailorsPause_Text_MirageIslandGone:
	.string "Ahoy. How've ya been?\p"
	.string "Mirage Island, from what I\n"
	.string "can tell, has disappeared again.\l"
	.string "Couldn't take ya back if I\l"
	.string "wanted to. Shame.$"
