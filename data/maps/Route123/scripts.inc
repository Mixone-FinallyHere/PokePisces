.set LOCALID_BREAD, 1
.set LOCALID_FUZKY, 13
.set LOCALID_SNOWNINJA, 14

Route123_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route123_OnTransition
	.byte 0

Route123_OnTransition:
	call_if_gt VAR_BREADWINNER_STATE, 1, Route123_EventScript_RemoveBreadwinner
	call Route123_EventScript_RemoveSnowNinja
	end

Route123_EventScript_FogTrigger::
	setweather WEATHER_FOG_DIAGONAL
	doweather
	end

Route123_EventScript_SnowTrigger::
	setweather WEATHER_SNOW
	doweather
	end

Route123_EventScript_RemoveBreadwinner::
	setflag FLAG_TEMP_11
	removeobject LOCALID_BREAD
	return

Route123_EventScript_RemoveSnowNinja::
	setflag FLAG_TEMP_16
	removeobject LOCALID_SNOWNINJA
	return

Route123_EventScript_BreadPos1::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, Route123_Movement_PlayerMoveIntoPos1
	waitmovement 0
	goto Route123_EventScript_BreadwinnerEncounter
	release
	end

Route123_Movement_PlayerMoveIntoPos1:
	walk_right
	face_up
	step_end

Route123_EventScript_BreadPos2::
	lock
	goto Route123_EventScript_BreadwinnerEncounter
	release
	end

Route123_EventScript_BreadwinnerEncounter::
	lock
	speakername Route123_Text_NamePandou
	applymovement OBJ_EVENT_ID_PLAYER, Route123_Movement_PlayerWalkUpStairs
	applymovement LOCALID_BREAD, Route123_Movement_BreadEnc
	waitmovement 0
	playse SE_WALL_HIT
	applymovement LOCALID_BREAD, Route123_Movement_BreadBackUp
	waitmovement 0
	msgbox Route123_Text_BreadwinnerIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_PANDOU_2, Route123_Text_BreadwinnerDefeat
	goto Route123_EventScript_BreadRun
	speakername NULL
	release
	end

Route123_Movement_PlayerWalkUpStairs:
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

Route123_Movement_BreadEnc:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route123_Movement_BreadBackUp:
	walk_right
	face_left
	step_end

Route123_EventScript_BreadRun::
	setvar VAR_BREADWINNER_STATE, 2
	speakername Route123_Text_NamePandou
	msgbox Route123_Text_BreadwinnerRunAway, MSGBOX_DEFAULT
	closemessage
	playse SE_FLEE
	applymovement LOCALID_BREAD, Route123_Movement_BreadEscape
	waitmovement 0
	speakername NULL
	msgbox Route123_Text_ProtectTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_PROTECT
	setweather WEATHER_FOG_DIAGONAL
	doweather
	setflag FLAG_TEMP_11
	removeobject LOCALID_BREAD
	release
	end

Route123_Movement_BreadEscape:
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route123_EventScript_Rami::
    trainerbattle_single TRAINER_P_RAMI, Route123_Text_RamiIntro, Route123_Text_RamiDefeated
    msgbox Route123_Text_RamiPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Tsunami::
    trainerbattle_single TRAINER_P_TSUNAMI, Route123_Text_TsunamiIntro, Route123_Text_TsunamiDefeated
    msgbox Route123_Text_TsunamiPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Jinxie::
    trainerbattle_single TRAINER_P_JINXIE, Route123_Text_JinxieIntro, Route123_Text_JinxieDefeated
    msgbox Route123_Text_JinxiePostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Carolina::
    trainerbattle_single TRAINER_P_CAROLINA, Route123_Text_CarolinaIntro, Route123_Text_CarolinaDefeated
    msgbox Route123_Text_CarolinaPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Betty::
    trainerbattle_single TRAINER_P_BETTY, Route123_Text_BettyIntro, Route123_Text_BettyDefeated
    msgbox Route123_Text_BettyPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Hazakura::
    trainerbattle_single TRAINER_P_HAZAKURA, Route123_Text_HazakuraIntro, Route123_Text_HazakuraDefeated
    msgbox Route123_Text_HazakuraPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Mia::
    trainerbattle_single TRAINER_P_MIA, Route123_Text_MiaIntro, Route123_Text_MiaDefeated
    msgbox Route123_Text_MiaPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Maya::
    trainerbattle_single TRAINER_P_MAYA, Route123_Text_MayaIntro, Route123_Text_MayaDefeated
    msgbox Route123_Text_MayaPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Kumori::
    trainerbattle_single TRAINER_P_KUMORI, Route123_Text_KumoriIntro, Route123_Text_KumoriDefeated
    msgbox Route123_Text_KumoriPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Hoth::
    trainerbattle_single TRAINER_P_HOTH, Route123_Text_HothIntro, Route123_Text_HothDefeated
    msgbox Route123_Text_HothPostBattle, MSGBOX_AUTOCLOSE
    end

Route123_EventScript_Gravestone1::
	lock
	goto_if_ge VAR_GRAVE_QUEST_STATE, 3, Route123_EventScript_KeepMoving
	goto_if_set FLAG_TEMP_13, Route123_EventScript_KeepMoving
	msgbox Route123_Text_WantToPayRespects1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route123_EventScript_Grave1Respects
	release
	end

Route123_EventScript_Grave1Respects::
	msgbox Route123_Text_YouFoldYourHands, MSGBOX_AUTOCLOSE
	fadeoutbgm 1
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	fadeinbgm 1
	addvar VAR_GRAVE_QUEST_STATE, 1
	setflag FLAG_TEMP_13
	msgbox Route123_Text_MayTheyRestInPeace, MSGBOX_AUTOCLOSE
	goto_if_eq VAR_GRAVE_QUEST_STATE, 3, Route123_EventScript_BindingBand
	release
	end

Route123_EventScript_KeepMoving::
	msgbox Route123_Text_GottaKeepMoving, MSGBOX_AUTOCLOSE
	release
	end

Route123_EventScript_Gravestone2::
	lock
	goto_if_ge VAR_GRAVE_QUEST_STATE, 3, Route123_EventScript_KeepMoving
	goto_if_set FLAG_TEMP_14, Route123_EventScript_KeepMoving
	msgbox Route123_Text_WantToPayRespects2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route123_EventScript_Grave2Respects
	release
	end

Route123_EventScript_Grave2Respects::
	msgbox Route123_Text_YouFoldYourHands, MSGBOX_AUTOCLOSE
	fadeoutbgm 1
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	fadeinbgm 1
	addvar VAR_GRAVE_QUEST_STATE, 1
	setflag FLAG_TEMP_14
	msgbox Route123_Text_MayTheyRestInPeace, MSGBOX_AUTOCLOSE
	goto_if_eq VAR_GRAVE_QUEST_STATE, 3, Route123_EventScript_BindingBand
	release
	end

Route123_EventScript_Gravestone3::
	lock
	goto_if_ge VAR_GRAVE_QUEST_STATE, 3, Route123_EventScript_KeepMoving
	goto_if_set FLAG_TEMP_15, Route123_EventScript_KeepMoving
	msgbox Route123_Text_WantToPayRespects3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route123_EventScript_Grave3Respects
	release
	end

Route123_EventScript_Grave3Respects::
	msgbox Route123_Text_YouFoldYourHands, MSGBOX_AUTOCLOSE
	fadeoutbgm 1
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	delay 60
	fadeinbgm 1
	addvar VAR_GRAVE_QUEST_STATE, 1
	setflag FLAG_TEMP_15
	msgbox Route123_Text_MayTheyRestInPeace, MSGBOX_AUTOCLOSE
	goto_if_eq VAR_GRAVE_QUEST_STATE, 3, Route123_EventScript_BindingBand
	release
	end

Route123_EventScript_BindingBand::
	msgbox Route123_Text_TheresSomethingOnYourWrist, MSGBOX_DEFAULT
	giveitem ITEM_BINDING_BAND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Route123_Text_TheEngravingSays, MSGBOX_AUTOCLOSE
	release
	end

Route123_EventScript_LureFuzky::
	lock
	goto_if_set FLAG_DEFEATED_MANTLE_FUZKY, Route123_EventScript_FuzkyGone
	msgbox Route123_Text_TheresAnOddFuzky, MSGBOX_DEFAULT
	checkitem ITEM_WEIRD_STICK
	goto_if_eq VAR_RESULT, TRUE, Route123_EventScript_WantToThrowStick
	release
	end

Route123_EventScript_WantToThrowStick::
	msgbox Route123_Text_WantToThrowStick, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route123_EventScript_FuzkyBattle
	release
	end

Route123_EventScript_FuzkyBattle::
	removeitem ITEM_WEIRD_STICK, 1
	msgbox Route123_Text_YouThrowTheStick, MSGBOX_DEFAULT
	applymovement LOCALID_FUZKY, Route123_Movement_FuzkyAttacks
	waitmovement 0
	setwildbattle SPECIES_FUZKY, 26
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 3, 1, 2, 3, 2
	playmoncry SPECIES_FUZKY, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox Route123_Text_TheFuzkyWantsToBattle, MSGBOX_DEFAULT
	setflag FLAG_WILD_NO_CATCHING_FLAG
	setflag FLAG_WILD_NO_RUNNING_FLAG
	setflag FLAG_SMART_WILD_AI_FLAG
	delay 4
	dowildbattle
	delay 8
	clearflag FLAG_WILD_NO_CATCHING_FLAG
	clearflag FLAG_WILD_NO_RUNNING_FLAG
	clearflag FLAG_SMART_WILD_AI_FLAG
	goto Route123_EventScript_FuzkyDefeat
	release
	end

Route123_Movement_FuzkyAttacks:
	walk_fast_right
	walk_fast_up
	jump_up
	step_end

Route123_EventScript_FuzkyDefeat::
	msgbox Route123_Text_ItTakesOffTheMantle, MSGBOX_DEFAULT
	giveitem ITEM_LOST_MANTLE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	applymovement LOCALID_FUZKY, Route123_Movement_FuzkyRunAway
	waitmovement 0
	removeobject LOCALID_FUZKY
	setflag FLAG_DEFEATED_MANTLE_FUZKY
	release
	end

Route123_Movement_FuzkyRunAway:
	jump_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	jump_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route123_EventScript_FuzkyGone::
	msgbox Route123_Text_FuzkyGone, MSGBOX_AUTOCLOSE
	release
	end

Route123_EventScript_SnowNinjaTrigger::
	lock
	setvar VAR_TEMP_5, 1
	checkitem ITEM_SMOKE_BALL
	goto_if_eq VAR_RESULT, TRUE, Route123_EventScript_SnowNinjaRelease
	goto_if_set FLAG_SNOWBALL_BOY, Route123_EventScript_SnowNinja
	release
	end

Route123_EventScript_SnowNinja::
	clearflag FLAG_TEMP_16
	addobject LOCALID_SNOWNINJA
	delay 16
	applymovement LOCALID_SNOWNINJA, Route123_Movement_Ambush
	waitmovement 0
	msgbox Route123_Text_HazakuraIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_HAZAKURA, Route123_Text_HazakuraDefeated
	goto Route123_EventScript_SmokeBall
	release
	end

Route123_Movement_Ambush:
	jump_right
	face_up
	step_end

Route123_EventScript_SmokeBall::
	lock
	msgbox Route123_Text_BackToTheSnow, MSGBOX_DEFAULT
	applymovement LOCALID_SNOWNINJA, Route123_Movement_BackToTheSnow
	waitmovement 0
	removeobject LOCALID_SNOWNINJA
	setflag FLAG_TEMP_16
	msgbox Route123_Text_HeLeftBehindSomething, MSGBOX_DEFAULT
	giveitem ITEM_SMOKE_BALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	release
	end

Route123_Movement_BackToTheSnow:
	jump_left
	step_end

Route123_EventScript_SnowNinjaRelease::
	closemessage
	release
	end

Route123_EventScript_ShrineSign::
	msgbox Route123_Text_ShrineSign, MSGBOX_SIGN
	end

Route123_EventScript_ZotpyreSign::
	msgbox Route123_Text_ZotpyreSign, MSGBOX_SIGN
	end

Route123_Text_ShrineSign:
	.string "ZOTPYRE SHRINE\n"
	.string "We ask that you practice respect\l"
	.string "when in this spiritual place.$"

Route123_Text_ZotpyreSign:
	.string "Zotpyre-Brumist Bridge$"

Route123_Text_BackToTheSnow:
	.string "Even after plotting my revenge over a\n"
	.string "painstaking 20 minutes…\l"
	.string "I lose…\p"

Route123_Text_HeLeftBehindSomething:
	.string "(The boy disappears,\n"
	.string "leaving behind an item.)$"

Route123_Text_WantToPayRespects1:
	.string "(Would you like to take a moment of\n"
	.string "silence to respect the dead?)$"

Route123_Text_WantToPayRespects2:
	.string "(Would you like to pay respects\n"
	.string "again here?)$"

Route123_Text_WantToPayRespects3:
	.string "(It's another epitaph.\n"
	.string "Pay respects again?)$"

Route123_Text_YouFoldYourHands:
	.string "…$"

Route123_Text_MayTheyRestInPeace:
	.string "(May they rest in peace.)$"

Route123_Text_GottaKeepMoving:
	.string "(...It's best not to loiter\n"
	.string "at the graves. Let them have\l"
	.string "their eternal rest...)$"

Route123_Text_TheresSomethingOnYourWrist:
	.string "(After your prayer, you look down to\n"
	.string "your wrist to find that there is\l"
	.string "a band around it.)$"

Route123_Text_TheEngravingSays:
	.string "(It's engraved…)\p"
	.string "OUR GRATITUDE$"

Route123_Text_TheresAnOddFuzky:
	.string "(You can see a Fuzky pacing around\n"
	.string "in the area that you can't reach.)\p"
	.string "(It is wearing a red hood.)$"

Route123_Text_WantToThrowStick:
	.string "(You have a Stick in your inventory.\n"
	.string "Throw the Stick?)$"

Route123_Text_YouThrowTheStick:
	.string "(You toss the stick in front\n"
	.string "of you in an attempt to lure over\l"
	.string "the odd Pokemon.)$"

Route123_Text_TheFuzkyWantsToBattle:
	.string "(The Fuzky is attacking!)$"

Route123_Text_ItTakesOffTheMantle:
	.string "(The Fuzky, beaten, drops the\n"
	.string "red hood it was wearing.)$"

Route123_Text_RamiIntro:
	.string "Hey! Wanna have a snowball fight?$"

Route123_Text_RamiDefeated:
	.string "Yay! Again! Again!$"

Route123_Text_RamiPostBattle:
	.string "Snowball fights are so much more fun\n"
	.string "with Pokémon! Don't you agree?!$"

Route123_Text_TsunamiIntro:
	.string "I always come crashin' down\n"
	.string "the mountain! Nothing beats\l"
	.string "that thrill!\p"
	.string "Well, maybe an exhilerating\n"
	.string "battle will!$"

Route123_Text_TsunamiDefeated:
	.string "Cowabunga!!$"

Route123_Text_TsunamiPostBattle:
	.string "People always tell me to\n"
	.string "take up surfing.\l"
	.string "But I HATE high temperatures, man!$"

Route123_Text_JinxieIntro:
	.string "Oooooh... Be afraid...$"

Route123_Text_JinxieDefeated:
	.string "...Be, uh... more afraid...\p"
	.string "...Please?\n$"

Route123_Text_JinxiePostBattle:
	.string "Haha, got you!\n"
	.string "You totally thought I was\l"
	.string "possessed, didn't you!$"

Route123_Text_CarolinaIntro:
	.string "This big heavy backpack is stuffed\n"
	.string "chock-full of necessary items!\p"
	.string "Take a look!$"

Route123_Text_CarolinaDefeated:
	.string "Huff.. Puff...\n"
	.string "The weight of my defeat is heavy, too.$"

Route123_Text_CarolinaPostBattle:
	.string "Carry a lighter load? No way!\n"
	.string "You never know when you'll need\l"
	.string "99 Elixirs!$"

Route123_Text_BettyIntro:
	.string "I've broken so many bones doing this!$"

Route123_Text_BettyDefeated:
	.string "Now my ego is broken too.$"

Route123_Text_BettyPostBattle:
	.string "I wish I had crashed into a tree,\n"
	.string "rather than you.$"

Route123_Text_HazakuraIntro:
	.string "Your guard was down, and I strike!\n"
	.string "This'll teach you not to mess with me!$"

Route123_Text_HazakuraDefeated:
	.string "Buried in the snow once more…!$"

Route123_Text_HazakuraPostBattle:
	.string "That's cold.$"

Route123_Text_MiaIntro:
	.string "... You will lose yourself here...$"

Route123_Text_MiaDefeated:
	.string "... Heed my warning...$"

Route123_Text_MiaPostBattle:
	.string "...$"

Route123_Text_MayaIntro:
	.string "...The soul is more malleable\n"
	.string "than one may expect...$"

Route123_Text_MayaDefeated:
	.string "...Would you like a demonstration?...$"

Route123_Text_MayaPostBattle:
	.string "...$"

Route123_Text_KumoriIntro:
	.string "Do you want to see my snow Froslass?$"

Route123_Text_KumoriDefeated:
	.string "It's really cool...$"

Route123_Text_KumoriPostBattle:
	.string "I love making snow Froslass,\n"
	.string "it's so much fun...\p"
	.string "What do you think?$"

Route123_Text_HothIntro:
	.string "I've got a bad feeling about\n"
	.string "this...$"

Route123_Text_HothDefeated:
	.string "Why, you... nerf-herder!$"

Route123_Text_HothPostBattle:
	.string "I could use a blanket.$"

Route123_Text_NamePandou:
	.string "Pandou$"

Route123_Text_BreadwinnerIntro:
	.string "Many p-p-pardons!\p"
	.string "This c-c-cold is so b-bitter,\n"
	.string "it's d-d-dulling my senses…!\l"
	.string "Not t-to mention, my g-g-glasses\l"
	.string "are fogging right up!\p"
	.string "…\p"
	.string "…What!?\n"
	.string "B-b-b-battle!?\l"
	.string "Now!?\l"
	.string "That's prepostero-$"

Route123_Text_BreadwinnerDefeat:
	.string "I can BARELY even s-s-see!$"

Route123_Text_BreadwinnerRunAway:
	.string "(Pandou rummages through his briefcase\n"
	.string "to find a glasses wipe.)\p"
	.string "YOU!? Golly… you're s-s-super\n"
	.string "b-battle hungry!\p"
	.string "D-do you have it out for me or\n"
	.string "s-s-something…?\p"
	.string "Jeez Louise…\n"
	.string "I'm way p-p-past schedule!\l"
	.string "I g-gotta make up some t-t-time!$"

Route123_Text_ProtectTM:
	.string "(He seems to have dropped something.)$"

Route123_Text_FuzkyGone:
	.string "(That Fuzky has left.)$"
