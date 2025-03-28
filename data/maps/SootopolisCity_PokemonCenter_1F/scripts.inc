.set LOCALID_NURSE, 1

SootopolisCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_PokemonCenter_1F_OnTransition
	.byte 0

SootopolisCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_NEW_SOOTO
	end

SootopolisCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_Gentleman::
	lock
	faceplayer
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, SootopolisCity_PokemonCenter_1F_EventScript_GentlemanNoLegendaries
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_PokemonCenter_1F_EventScript_GentlemanNoLegendaries
	msgbox SootopolisCity_PokemonCenter_1F_Text_EveryoneTakenRefuge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_GentlemanNoLegendaries::
	msgbox SootopolisCity_PokemonCenter_1F_Text_WallaceToughestInHoenn, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_Woman::
	lock
	faceplayer
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, SootopolisCity_PokemonCenter_1F_EventScript_WomanNoLegendaries
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_PokemonCenter_1F_EventScript_WomanNoLegendaries
	msgbox SootopolisCity_PokemonCenter_1F_Text_ArentPokemonOurFriends, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_WomanNoLegendaries::
	msgbox SootopolisCity_PokemonCenter_1F_Text_AlwaysBeFriendsWithPokemon, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_LevelCap1::
    msgbox SootopolisCity_PokemonCenter_1F_Text_LevelCap1, MSGBOX_NPC
    end

SootopolisCity_PokemonCenter_1F_EventScript_LevelCap2::
    msgbox SootopolisCity_PokemonCenter_1F_Text_LevelCap2, MSGBOX_NPC
    end

SootopolisCity_PokemonCenter_1F_EventScript_IceFrostbite::
    msgbox SootopolisCity_PokemonCenter_1F_Text_IceFrostbite, MSGBOX_NPC
    end

SootopolisCity_PokemonCenter_1F_EventScript_SEAndSTAB::
    msgbox SootopolisCity_PokemonCenter_1F_Text_SEAndSTAB, MSGBOX_NPC
    end

SootopolisCity_PokemonCenter_1F_EventScript_FairyResistDragon::
    msgbox SootopolisCity_PokemonCenter_1F_Text_FairyResistDragon, MSGBOX_NPC
    end

SootopolisCity_PokemonCenter_1F_Text_LevelCap1:
	.string "Seen some folk 'round here get\n"
	.string "frustrated n' all that when their\l"
	.string "Pokemon stop gainin' levels.\p"
	.string "'S only natural them critters want\n"
	.string "to see some results of their\l"
	.string "trainin' before growin' more.\p"
	.string "My advice to 'em? Take out a\n"
	.string "big ol' target like a gym leader!$"

SootopolisCity_PokemonCenter_1F_Text_LevelCap2:
	.string "The Pokemon squad I have assembled\n"
	.string "have all just about plateaued in EXP.\l"
	.string "Admittedly, I've been a bit scared\l"
	.string "to challenge the gym...\l"
	.string "but, perhaps this is their way\l"
	.string "of accepting the challenge head-on!$"

SootopolisCity_PokemonCenter_1F_Text_IceFrostbite:
	.string "I used to work for Juan in the\n"
	.string "Sootopolis Gym. Want some tidbits\l"
	.string "I know about the Ice type?\p"
	.string "Obviously, Ice completely frosts\n"
	.string "over Grass, Dragon, Ground, and\l"
	.string "Flying type Pokemon. And yes,\l"
	.string "it can be a frail type. However,\l"
	.string "contrary to popular belief,\l"
	.string "Ice does resist Water. And, even\l"
	.string "though Steel type moves shatter\l"
	.string "Ice type Pokemon, Steel 'mons\l"
	.string "do not resist Ice moves.\p"
	.string "Ice type Pokemon have access to\n"
	.string "a status called Frostbite.\l"
	.string "It damages the afflicted every\l"
	.string "turn, and dulls their mental\l"
	.string "abilities, making them effectively\l"
	.string "have their Special Attack cut\l"
	.string "right in half.\p"
	.string "I have no doubt Juan will make\n"
	.string "the full use of the type against\l"
	.string "any who challenge him.\l"
	.string "If you have a Fire or Rock type\l"
	.string "Pokemon, those could be\l"
	.string "your best bet.$"

SootopolisCity_PokemonCenter_1F_Text_SEAndSTAB:
	.string "Hey! Hey!\p"
	.string "Hey!\p"
	.string "Didja know that Super Effective\n"
	.string "Moves work differently than ya??\l"
	.string "may think? I did!\p"
	.string "Super Effective Moves do like,\n"
	.string "twice the damage they normally\n"
	.string "would when they hit an\l"
	.string "opponent's weakness.\l"
	.string "So, you'd think when hitting\l"
	.string "an opponent with a move that\l"
	.string "it is doubly weak to, that\l"
	.string "the damage would end up being\l"
	.string "four times as much! But no,\l"
	.string "that gets capped at three times.\p"
	.string "Also, something I've noticed when\n"
	.string "using moves of the same type as\l"
	.string "my Pokémon. Those moves\l"
	.string "get a lil' bonus in power...\l"
	.string "I'd say about a quarter more?\p"
	.string "But get this! Normal type Pokemon\n"
	.string "get a bigger same type attack\l"
	.string "bonus on their moves!$"

SootopolisCity_PokemonCenter_1F_Text_FairyResistDragon:
	.string "I have a buddy that really likes\n"
	.string "Fairy type Pokemon. He keeps\l"
	.string "trying to sell me on the fact\l"
	.string "that they are immune to Dragon moves.\p"
	.string "What an exaggeration! Sure, Fairy\n"
	.string "RESISTS Dragon, but it doesn't\l"
	.string "nullify the damage!\p"
	.string "Thinking about downgrading him\n"
	.string "from “buddy” to “acquaintance”\l"
	.string "for that misinfo.$"

SootopolisCity_PokemonCenter_1F_Text_WallaceToughestInHoenn:
	.string "WALLACE is rumored to be the toughest\n"
	.string "TRAINER in the whole HOENN region.\p"
	.string "This town's GYM is led by the TRAINER\n"
	.string "who taught WALLACE.\p"
	.string "But the ELITE FOUR… They're said to be\n"
	.string "even stronger than WALLACE's mentor.\p"
	.string "How strong could they be?$"

SootopolisCity_PokemonCenter_1F_Text_EveryoneTakenRefuge:
	.string "Everyone in town has taken refuge\n"
	.string "and won't come out of their homes.\p"
	.string "Even I would rather not venture\n"
	.string "outside.$"

SootopolisCity_PokemonCenter_1F_Text_AlwaysBeFriendsWithPokemon:
	.string "Whenever, wherever, and whatever\n"
	.string "happens, I will always be friends with\l"
	.string "POKéMON.\p"
	.string "Because it's fun to be with POKéMON!$"

SootopolisCity_PokemonCenter_1F_Text_ArentPokemonOurFriends:
	.string "Aren't POKéMON our friends?\p"
	.string "Why are they going wild this way?$"

