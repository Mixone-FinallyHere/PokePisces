.set LOCALID_POMATIA1, 1
.set LOCALID_POMATIA2, 2
.set LOCALID_POMATIA3, 3
.set LOCALID_POMATIA4, 4

SecretMossdeepCave_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SecretMossdeepCave_OnTransition
	.byte 0

SecretMossdeepCave_OnTransition:
	call_if_set FLAG_SHELLYLOUH_RIDDLE_1, SecretMossdeepCave_EventScript_SetTempFlags
	end

SecretMossdeepCave_EventScript_SetTempFlags::
	removeobject LOCALID_POMATIA1
	removeobject LOCALID_POMATIA2
	removeobject LOCALID_POMATIA3
	removeobject LOCALID_POMATIA4
	setflag FLAG_TEMP_11
	return

SecretMossdeepCave_EventScript_PomAndAtia::
	trainerbattle_double TRAINER_P_POM_AND_ATIA, SecretMossdeepCave_Text_PomAtiaIntro, SecretMossdeepCave_Text_PomAtiaDefeated, SecretMossdeepCave_Text_PomAtiaNeedTwoMons, SecretMossdeepCave_EventScript_GiveShellPolish
    msgbox SecretMossdeepCave_Text_PomAtiaPostBattle, MSGBOX_AUTOCLOSE
    end

SecretMossdeepCave_EventScript_GiveShellPolish::
	msgbox SecretMossdeepCave_Text_HaveSP, MSGBOX_DEFAULT
	giveitem ITEM_PEARL_STRING
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

SecretMossdeepCave_Text_PomAtiaIntro:
	.string "Clever trainer, to come upon us\n"
	.string "in this cave.\p"
	.string "We have made many snail friends here!\p"
	.string "Ours are especially glistening\n"
	.string "and battle-hardened.\p"
	.string "No way you can take us down!$"

SecretMossdeepCave_Text_PomAtiaDefeated:
	.string "Our pace was too sluggish…$"

SecretMossdeepCave_Text_PomAtiaNeedTwoMons:
	.string "need 2 dood$"

SecretMossdeepCave_Text_PomAtiaPostBattle:
	.string "tsuinsu$"

SecretMossdeepCave_Text_HaveSP:
	.string "Snelfrend are wonderful\n"
	.string "little Pokémon.\p"
	.string "Since they had a good time fighting\n"
	.string "with you, have this item!$"
