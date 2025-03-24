.set LOCALID_BIRCH, 2

BirchMaritimeLab_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BirchMaritimeLab_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, BirchMaritimeLab_OnLoad
	.byte 0

BirchMaritimeLab_OnFrame:
	map_script_2 VAR_BIRCH_LAB_STATE, 2, BirchMaritimeLab_EventScript_BeforeStarter
	map_script_2 VAR_BIRCH_LAB_STATE, 6, BirchMaritimeLab_EventScript_BeatenRangers
	.2byte 0

BirchMaritimeLab_OnLoad:
	call_if_gt VAR_BIRCH_LAB_STATE, 4, BirchMaritimeLab_EventScript_ReplaceTable
	end

BirchMaritimeLab_EventScript_ReplaceTable::
	setmetatile 9, 2, METATILE_BirchLab_BirchTable1, FALSE
	setmetatile 10, 2, METATILE_BirchLab_BirchTable2, FALSE
	setmetatile 9, 3, METATILE_BirchLab_BirchTable3, TRUE
	setmetatile 10, 3, METATILE_BirchLab_BirchTable4, TRUE
	special DrawWholeMapView
	return

BirchMaritimeLab_EventScript_BeforeStarter::
	lockall
	setobjectxyperm LOCALID_BIRCH, 9, 13
	applymovement LOCALID_BIRCH, BirchMaritimeLab_Movement_BirchEnterLabForPokedex
	applymovement OBJ_EVENT_ID_PLAYER, BirchMaritimeLab_Movement_PlayerEnterLabForPokedex
	waitmovement 0
	goto BirchMaritimeLab_EventScript_PickYourStarter
	end

BirchMaritimeLab_Movement_BirchEnterLabForPokedex:
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
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_right
	step_end

BirchMaritimeLab_Movement_PlayerEnterLabForPokedex:
	walk_up
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
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

BirchMaritimeLab_EventScript_PickYourStarter::
	lock
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_TakeStarter, MSGBOX_DEFAULT
	closemessage
	speakername NULL
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	waitstate
	clearflag FLAG_HIDE_BIRCH_AFTER_STARTER
	setflag FLAG_HIDE_BIRCH_BEFORE_STARTER
	setflag FLAG_BRINEY_MIDGAME_VISIT
	special HealPlayerParty
	setvar VAR_ROUTE101_STATE, 3
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	goto BirchMaritimeLab_EventScript_GiveStarterEvent
	end

BirchMaritimeLab_EventScript_GiveStarterEvent::
	lockall
	bufferleadmonspeciesname STR_VAR_1
	setmetatile 9, 2, METATILE_BirchLab_BirchTable1, FALSE
	setmetatile 10, 2, METATILE_BirchLab_BirchTable2, FALSE
	setmetatile 9, 3, METATILE_BirchLab_BirchTable3, TRUE
	setmetatile 10, 3, METATILE_BirchLab_BirchTable4, TRUE
	special DrawWholeMapView
	speakername NULL
	message BirchMaritimeLab_Text_ReceivedStarter
	waitmessage
	playfanfare MUS_SLOTS_JACKPOT
	waitfanfare
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_WhyNotGiveNicknameToMon, MSGBOX_YESNO
	speakername NULL
	goto_if_eq VAR_RESULT, YES, BirchMaritimeLab_EventScript_NicknameStarter
	goto_if_eq VAR_RESULT, NO, BirchMaritimeLab_EventScript_GivePokedex
	end

BirchMaritimeLab_EventScript_NicknameStarter::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto BirchMaritimeLab_EventScript_GivePokedex
	end

BirchMaritimeLab_EventScript_GivePokedex::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	delay 4
	playbgm MUS_ENCOUNTER_MAY, FALSE
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_HeardYouBeatRivalTakePokedex, MSGBOX_DEFAULT
	call BirchMaritimeLab_EventScript_ReceivePokedex
	msgbox BirchMaritimeLab_Text_ExplainPokedex, MSGBOX_DEFAULT
	closemessage
	call BirchMaritimeLab_EventScript_GivePokeBalls
	setvar VAR_BIRCH_LAB_STATE, 5
	setflag FLAG_ADVENTURE_STARTED
	setvar VAR_OLDALE_TOWN_STATE, 1
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4
	setvar VAR_LITTLEROOT_TOWN_STATE, 3
	speakername NULL
	releaseall
	end

BirchMaritimeLab_EventScript_ReceivePokedex::
	speakername NULL
	playfanfare MUS_OBTAIN_ITEM
	message BirchMaritimeLab_Text_ReceivedPokedex
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
	return

BirchMaritimeLab_EventScript_GivePokeBalls::
	msgbox BirchMaritimeLab_Text_TakeBalls, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 10
	giveitem ITEM_SODA_POP, 5
	giveitem ITEM_ETHER, 3
	giveitem ITEM_REVIVE, 1
	giveitem ITEM_STAR_PIECE, 1
	call_if_eq VAR_RESULT, FALSE, BirchMaritimeLab_EventScript_NoRoomForPokeBalls
	msgbox BirchMaritimeLab_Text_GoFightTheRangers, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	return

BirchMaritimeLab_EventScript_NoRoomForPokeBalls::
	msgbox BirchMaritimeLab_Text_OhYourBagsFull, MSGBOX_DEFAULT
	return

BirchMaritimeLab_EventScript_BeatenRangers::
	special HealPlayerParty
	setflag FLAG_HIDE_SKY_PILLAR_RANGERS
	setvar VAR_BIRCH_LAB_STATE, 7
	applymovement OBJ_EVENT_ID_PLAYER, BirchMaritimeLab_Movement_PlayerReturnFromSkyPillar
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_HaveEXPShare, MSGBOX_DEFAULT
	speakername NULL
	giveitem ITEM_EXP_SHARE
	setflag FLAG_RECEIVED_TM_POUNCE
	setflag FLAG_RECEIVED_EXP_SHARE
	setvar VAR_BALL_QUEST_STATE, 69
	delay 4
	setflag FLAG_I_EXP_SHARE
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_GoToSootopolis, MSGBOX_AUTOCLOSE
	speakername NULL
	releaseall
	end

BirchMaritimeLab_EventScript_BirchIdle::
	lock
	faceplayer
	goto_if_set FLAG_VISITED_SOOTOPOLIS_CITY, BirchMaritimeLab_EventScript_BirchCheckDex
	goto_if_set FLAG_HIDE_SKY_PILLAR_RANGERS, BirchMaritimeLab_EventScript_BirchPostSkyPillar
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_AfterGettingStarter, MSGBOX_DEFAULT
	closemessage
	release
	end

BirchMaritimeLab_EventScript_BirchPostSkyPillar::
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_BirchPostSkyPillar, MSGBOX_DEFAULT
	closemessage
	release
	end

BirchMaritimeLab_EventScript_BirchCheckDex::
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_HowsCatchingPokemon, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008
	buffernumberstring STR_VAR_2, VAR_0x8009
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_BirchTellDexCount, MSGBOX_DEFAULT
	goto_if_gt VAR_0x8009, 99, BirchMaritimeLab_EventScript_Birch100Caught
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_KeepOnCatching, MSGBOX_DEFAULT
	closemessage
	release
	end

BirchMaritimeLab_EventScript_Birch100Caught::
	goto_if_set FLAG_GOT_FAVOR_SCARF, BirchMaritimeLab_EventScript_BirchCheck200
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_Wow100HaveFavorScarf, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_FAVOR_SCARF
	closemessage
	setflag FLAG_GOT_FAVOR_SCARF
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_GoFor200, MSGBOX_DEFAULT
	closemessage
	release
	end

BirchMaritimeLab_EventScript_BirchCheck200::
	goto_if_gt VAR_0x8009, 199, BirchMaritimeLab_EventScript_Birch200Caught
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_GoFor200, MSGBOX_DEFAULT
	closemessage
	release
	end

BirchMaritimeLab_EventScript_Birch200Caught::
	checkitem ITEM_CATCHING_CHARM
	goto_if_eq VAR_RESULT, TRUE, BirchMaritimeLab_EventScript_BirchCheckAllCaught
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_Wow200HaveCatchingCharm, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_CATCHING_CHARM
	closemessage
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_GoForAllCaught, MSGBOX_DEFAULT
	closemessage
	release
	end

BirchMaritimeLab_EventScript_BirchCheckAllCaught::
	goto_if_gt VAR_0x8009, 279, BirchMaritimeLab_EventScript_BirchAllCaught
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_GoForAllCaught, MSGBOX_DEFAULT
	closemessage
	release
	end

BirchMaritimeLab_EventScript_BirchAllCaught::
	speakername BirchMaritimeLab_Text_NameBirch
	msgbox BirchMaritimeLab_Text_WowAllCaught, MSGBOX_DEFAULT
	closemessage
	release
	end

BirchMaritimeLab_EventScript_GrangerPostSkyPillar::
	speakername BirchMaritimeLab_Text_NameGranger
	msgbox BirchMaritimeLab_Text_GrangerPostSkyPillar, MSGBOX_NPC
	speakername NULL
	end

BirchMaritimeLab_EventScript_JeanniePostSkyPillar::
	speakername BirchMaritimeLab_Text_NameJeannie
	msgbox BirchMaritimeLab_Text_JeanniePostSkyPillar, MSGBOX_NPC
	speakername NULL
	end

BirchMaritimeLab_EventScript_RickyPostSkyPillar::
	speakername BirchMaritimeLab_Text_NameRicky
	msgbox BirchMaritimeLab_Text_RickyPostSkyPillar, MSGBOX_NPC
	speakername NULL
	end

BirchMaritimeLab_Movement_PlayerReturnFromSkyPillar:
	face_up
	step_end

BirchMaritimeLab_EventScript_JollyAide::
	msgbox BirchMaritimeLab_Text_JollyAide, MSGBOX_NPC
	end

BirchMaritimeLab_EventScript_TiredAide::
	msgbox BirchMaritimeLab_Text_TiredAide, MSGBOX_NPC
	end

BirchMaritimeLab_EventScript_StudiousAide::
	msgbox BirchMaritimeLab_Text_StudiousAide, MSGBOX_NPC
	end

BirchMaritimeLab_Text_NameBirch:
	.string "Dad$"

BirchMaritimeLab_Text_NameGranger:
	.string "Granger$"

BirchMaritimeLab_Text_NameJeannie:
	.string "Jeannie$"

BirchMaritimeLab_Text_NameRicky:
	.string "Ricky$"

BirchMaritimeLab_Text_TakeStarter:
	.string "For a journey as long and,\n"
	.string "hopefully, fruitful as it seems\l"
	.string "this one will be... I'd love\l"
	.string "to give you one of these\l"
	.string "three Starter Pokémon, as a\l"
	.string "close traveling companion.\p"
	.string "Just like old times, huh?\p"
	.string "With the move to Pacifidlog,\n"
	.string "I had to start collecting 3 new\l"
	.string "species of Pokémon to give out\l"
	.string "to budding trainers.\p"
	.string "I think you'll really take to them!$"

BirchMaritimeLab_Text_ReceivedStarter:
	.string "{PLAYER} has received their\n"
	.string "Starter Pokémon, {STR_VAR_1}!$"

BirchMaritimeLab_Text_AfterGettingStarter:
	.string "Go get 'em, champ!$"

BirchMaritimeLab_Text_WhyNotGiveNicknameToMon:
	.string "Ah! Your new friend is wanting\n"
	.string "to show you its loyalty!\p"
	.string "Want to give it a nickname?$"

BirchMaritimeLab_Text_HeardYouBeatRivalTakePokedex:
	.string "Very good then!\n"
	.string "Along with your Starter Pokémon,\l"
	.string "I'd be remiss if I didn't also\l"
	.string "give you a brand new Pokédex as well!$"

BirchMaritimeLab_Text_ExplainPokedex:
	.string "This model is much the same\n"
	.string "as the one you had used some time\l"
	.string "ago. Be aware, though, that the\l"
	.string "slate has been wiped clean,\l"
	.string "so to speak.\p"
	.string "I'm sure you will encounter\n"
	.string "many new faces in your\l"
	.string "journey across the Hoenn region!$"

BirchMaritimeLab_Text_ReceivedPokedex:
	.string "{PLAYER} received a new POKéDEX!$"

BirchMaritimeLab_Text_TakeBalls:
	.string "Now, {PLAYER}, kiddo...\p"
	.string "I know you're really wanting\n"
	.string "to get started and blitz through\l"
	.string "the path forward, but I don't\l"
	.string "think you've battled in a while,\l"
	.string "would I have that right?\p"
	.string "So, I took the liberty of\n"
	.string "contracting a few kindhearted\l"
	.string "Rangers to give you some\l"
	.string "warm-up fights!\p"
	.string "You'll find them atop Sky Pillar\n"
	.string "to the north.\p"
	.string "...Oh! And if you want to\n"
	.string "catch any more POKéMON along the\l"
	.string "way there, you'll need, uhm...\p"
	.string "Oh, and you'd also maybe like...\n"
	.string "some... hmm, some healing items...\l"
	.string "Let's see here...\p"
	.string "(Your dad shuffles through\n"
	.string "his labcoat pockets haphazardly.)$"

BirchMaritimeLab_Text_GoFightTheRangers:
	.string "That should suffice!\p"
	.string "...Alrighty! That's about all\n"
	.string "your pops has got to give.\p"
	.string "Please stay safe out there,\n"
	.string "alright kiddo?\p"
	.string "Good luck; I'm always in your corner!$"

BirchMaritimeLab_Text_OhYourBagsFull:
	.string "uh oh spaghettios$"

BirchMaritimeLab_Text_HaveEXPShare:
	.string "Great job, kiddo!\n"
	.string "Heard they got a good whoopin'.\p"
	.string "You should be off properly, now.\p"
	.string "If you want to fill out the badge case,\n"
	.string "Sootopolis City is the place to be!\p"
	.string "You can get there by leaving via the\n"
	.string "east exit of Pacifidlog,\l"
	.string "and hiking up the coastal rocks.\p"
	.string "Oh!\p"
	.string "And I suspect you're going to want to\n"
	.string "raise a lot of team members.\p"
	.string "Here; this EXP Share should help\n"
	.string "with that!$"

BirchMaritimeLab_Text_GoToSootopolis:
	.string "You can turn on the EXP Share from your\n"
	.string "bag, {PLAYER}.\l"
	.string "When on, it'll share EXP to Pokémon\l"
	.string "in your party, even if\l"
	.string "they didn't battle.\p"
	.string "Hah!\n"
	.string "You look about ready\l"
	.string "to take on anything!\p"
	.string "Go get 'em, champ;\n"
	.string "dear ol' dad is rooting you on!$"

BirchMaritimeLab_Text_BirchPostSkyPillar:
	.string "{PLAYER}, don't forget;\n"
	.string "your goal right now should be\l"
	.string "getting to Sootopolis City.\p"
	.string "It's a simple trek east!\n"
	.string "Make me proud, and be safe!$"

BirchMaritimeLab_Text_GrangerPostSkyPillar:
	.string "Ah, {PLAYER}!\p"
	.string "You've proven yourself a\n"
	.string "blossoming talent!\p"
	.string "We have nothing left to assist you\n"
	.string "with. Explore Hoenn to your heart's\l"
	.string "content. Be safe out there!$"

BirchMaritimeLab_Text_JeanniePostSkyPillar:
	.string "Well, what are you waiting for?\n"
	.string "the world's your oyster!\l"
	.string "Make us proud!$"

BirchMaritimeLab_Text_RickyPostSkyPillar:
	.string "You're on FIRE!!\p"
	.string "Burned through the three of us like\n"
	.string "we was dry paper!\p"
	.string "Keep it up, don't let that passion'a\n"
	.string "yours die out. Go show Hoenn\l"
	.string "what you're made of!$"

BirchMaritimeLab_Text_JollyAide:
	.string "I was pleased as punch when\n"
	.string "the Professor relocated to\l"
	.string "Pacifidlog Town!\l"
	.string "It's my dream settle-down-town!$"

BirchMaritimeLab_Text_TiredAide:
	.string "Moving all of the lab's\n"
	.string "notes and equipment here was\l"
	.string "one big process, I tell you.\p"
	.string "Your pops has got a knack\n"
	.string "for keeping his records\l"
	.string "physical over digital, which\l"
	.string "has its pros and cons...$"

BirchMaritimeLab_Text_StudiousAide:
	.string "I'm really wanting to branch\n"
	.string "out in this new environment\l"
	.string "and take on projects I\l"
	.string "wouldn't back in Littleroot.$"

BirchMaritimeLab_Text_HowsCatchingPokemon:
	.string "Hey, kiddo! Hope your big 'ol\n"
	.string "adventure is going great!\p"
	.string "Have you been catching lots of\n"
	.string "new friends and filling out\l"
	.string "your Pokedex? Ahaha, yes, your\l"
	.string "old man is nosy! Let me see\l"
	.string "your Pokedex progress!$"

BirchMaritimeLab_Text_BirchTellDexCount:
	.string "So, you've seen {STR_VAR_1} Pokemon\n"
	.string "and caught {STR_VAR_2} of them...$"

BirchMaritimeLab_Text_KeepOnCatching:
	.string "That is a respectable amount so far!\n"
	.string "Try and aim for registering\l"
	.string "100 Pokemon in your 'Dex...\l"
	.string "I'll gift you a special somethin'!$"

BirchMaritimeLab_Text_Wow100HaveFavorScarf:
	.string "You've caught over 100 Pokemon?\n"
	.string "That's amazing, kiddo! An\l"
	.string "accomplishment like that deserves\l"
	.string "a reward, so here, I want you\l"
	.string "to take this!\p"
	.string "I, err, took a few lessons in\n"
	.string "crocheting to make it...\l"
	.string "the things a dad does for\l"
	.string "his little prodigy!$"

BirchMaritimeLab_Text_GoFor200:
	.string "You gotta aim for the big 200\n"
	.string "registered in the Pokedex next!\l"
	.string "I'll make you something\l"
	.string "even more creative... I promise!$"

BirchMaritimeLab_Text_Wow200HaveCatchingCharm:
	.string "You've hit the 200 mark, kiddo!\n"
	.string "You're something else! Really\l"
	.string "makes me a proud pops, hahaha!\p"
	.string "As promised, I have honed my\n"
	.string "arts and crafts skills more...\l"
	.string "I invested a lot of energy\l"
	.string "into hand-making this charm\l"
	.string "for you, kiddo. I hope you\l"
	.string "wear it around on these last\l"
	.string "legs of your journey!$"

BirchMaritimeLab_Text_GoForAllCaught:
	.string "You're getting close to registering\n"
	.string "all 280 Pokemon in the Hoenn Pokedex...\l"
	.string "That'll be a herculean task\l"
	.string "to finish out, but I know you're\l"
	.string "tenacious enough to see it through!\l"
	.string "Go get 'em, champ!$"

BirchMaritimeLab_Text_WowAllCaught:
	.string "You've caught every single Pokemon!\n"
	.string "What a legendary kid you turned\l"
	.string "out to be... oh, who am I kidding?\l"
	.string "I always knew you had it in you!$"
