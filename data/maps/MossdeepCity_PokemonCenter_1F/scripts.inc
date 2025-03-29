.set LOCALID_NURSE, 1

MossdeepCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_PokemonCenter_1F_OnTransition
	.byte 0

MossdeepCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_MOSSDEEP_CITY
	end

MossdeepCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MossdeepCity_PokemonCenter_1F_EventScript_Woman::
	msgbox MossdeepCity_PokemonCenter_1F_Text_GymLeaderDuoFormidable, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_EventScript_Girl::
	msgbox MossdeepCity_PokemonCenter_1F_Text_AbilitiesMightChangeMoves, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_EventScript_EVEditing::
	msgbox MossdeepCity_PokemonCenter_1F_Text_EVEditing, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_EventScript_IVsNoMore::
	msgbox MossdeepCity_PokemonCenter_1F_Text_IVsNoMore, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_EventScript_PsychicRundown::
	msgbox MossdeepCity_PokemonCenter_1F_Text_PsychicRundown, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_EventScript_DarkRundown::
	msgbox MossdeepCity_PokemonCenter_1F_Text_DarkRundown, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_EventScript_BestTimeToPrepare::
	msgbox MossdeepCity_PokemonCenter_1F_Text_BestTimeToPrepare, MSGBOX_NPC
	end

MossdeepCity_PokemonCenter_1F_Text_EVEditing:
	.string "Cop this fat tip, pal-o. Ever catch\n"
	.string "wind of EVs? Lil' values built up\l"
	.string "by your squad that affect their\l"
	.string "main stats and whatnot.\p"
	.string "Didja know you can check them\n"
	.string "bad boys whenever? I've seen some\l"
	.string "cats ignore it. Not only that,\l"
	.string "y'know. You can swap around the\l"
	.string "points a 'mon's accumulated to\l"
	.string "its other stats however you wanna\l"
	.string "slice 'em.\p"
	.string "Can really take a build from good\n"
	.string "to great, know what I'm sayin'!?$"

MossdeepCity_PokemonCenter_1F_Text_IVsNoMore:
	.string "Why, hello. I'm doing research\n"
	.string "on centuries-old Pokemon traits\l"
	.string "and abnormalities.\p"
	.string "Curiously, it seems that Pokemon\n"
	.string "used to possess a set of\l"
	.string "“Individual Values” that were semi-\l"
	.string "unique to each specimen. This,\l"
	.string "inherently, made some specimens\l"
	.string "weaker than others of the same\l"
	.string "species by default.\p"
	.string "It appears that, with time, these\n"
	.string "values homogenized, making them\l"
	.string "irrelevant in modern times.$"

MossdeepCity_PokemonCenter_1F_Text_PsychicRundown:
	.string "The gym leader in Mossdeep, Liza,\n"
	.string "specializes in the Psychic type.\l"
	.string "I do too. Let me tell you some\l"
	.string "strengths of the type...\p"
	.string "Psychic type Pokemon have minds\n"
	.string "like no other, and as such, they\l"
	.string "are immune to becoming confused,\l"
	.string "or falling to hypnosis. They also\l"
	.string "particularly use Gravity to\l"
	.string "its fullest potential.\p"
	.string "I have seen some trainers try to\n"
	.string "wall my Psychic type Pokemon with\l"
	.string "Steel type Pokemon, however, that\l"
	.string "is misplaced judgment. They do not\l"
	.string "resist Psychic moves.\p"
	.string "The best way to counter a Psychic\n"
	.string "type Pokemon, is of course, by\l"
	.string "having a Dark type Pokemon, as they\l"
	.string "are immune to Psychic moves.\l"
	.string "The best way for Psychic users to\l"
	.string "counterplay Dark users is making\l"
	.string "good play of the coverage moves\l"
	.string "their Pokemon will learn.$"

MossdeepCity_PokemonCenter_1F_Text_DarkRundown:
	.string "Hey, wide-eyed rookie. Y'ever\n"
	.string "try out some Dark types in your\l"
	.string "time yet? They're my favorite\l"
	.string "types to play around with.\p"
	.string "The best part about 'em? They're\n"
	.string "immune to Psychic moves and\l"
	.string "the Shadow Tag ability. It's cuz\l"
	.string "they know a good trick when they\l"
	.string "see one. Not only that, but a 'mon\l"
	.string "with Prankster? They can't pull\l"
	.string "their fast ones, so they lose\l"
	.string "priority.\p"
	.string "Then again, Fairies negate Prankster\n"
	.string "too. I swear, they're a Dark type's\l"
	.string "worst nightmare.$"

MossdeepCity_PokemonCenter_1F_Text_BestTimeToPrepare:
	.string "The best time to prepare up your\n"
	.string "team is before you head into\l"
	.string "the most recent gym.\p"
	.string "Stock up on items and set up your\n"
	.string "moves on your Pokemon. It's also\l"
	.string "the best time to add in new members,\l"
	.string "since they will get more EXP if you\l"
	.string "have reached the town where a gym\l"
	.string "is, but have not beaten it yet.\p"
	.string "Good luck!\n$"

MossdeepCity_PokemonCenter_1F_Text_GymLeaderDuoFormidable:
	.string "The GYM LEADERS in this town are\n"
	.string "a formidable duo.\p"
	.string "Their combination attacks are, like,\n"
	.string "excellent and wow!$"

MossdeepCity_PokemonCenter_1F_Text_AbilitiesMightChangeMoves:
	.string "Depending on the special abilities of\n"
	.string "POKéMON, some moves might change\l"
	.string "or not work at all.$"

