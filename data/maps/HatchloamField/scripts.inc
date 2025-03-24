.set LOCALID_ROADBLOCKER_1, 16
.set LOCALID_ROADBLOCKER_2, 17
.set LOCALID_ROADBLOCKER_3, 18
.set LOCALID_ROADBLOCKER_4, 19
.set LOCALID_COURTNEY, 15

HatchloamField_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, HatchloamField_OnLoad
	.byte 0

HatchloamField_OnLoad:
	call_if_gt VAR_WALLY_QUEST_STATE, 2, HatchloamField_EventScript_RemoveRoadblock
	end

HatchloamField_EventScript_RemoveRoadblock::
	removeobject LOCALID_ROADBLOCKER_1
	setflag FLAG_TEMP_11
	removeobject LOCALID_ROADBLOCKER_2
	setflag FLAG_TEMP_12
	removeobject LOCALID_ROADBLOCKER_3
	setflag FLAG_TEMP_13
	removeobject LOCALID_ROADBLOCKER_4
	setflag FLAG_TEMP_14
	return

HatchloamField_EventScript_Courtney::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_A, HatchloamField_EventScript_CourtneyIdlePostBattle
	goto_if_eq VAR_OZONE_ADMINS_STATE, 9, HatchloamField_EventScript_CourtneyWantToBattle
	goto_if_gt VAR_OZONE_ADMINS_STATE, 9, HatchloamField_EventScript_CourtneyIdle
	release
	end

HatchloamField_EventScript_CourtneyWantToBattle::
	speakername HatchloamField_Text_NameCourtney
	msgbox HatchloamField_Text_NiceToSeeYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, HatchloamField_EventScript_CourtneyBattle
	speakername HatchloamField_Text_NameCourtney
	msgbox HatchloamField_Text_ThatsTooBad, MSGBOX_AUTOCLOSE
	release
	end

HatchloamField_EventScript_CourtneyBattle::
	msgbox HatchloamField_Text_CourtneyIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_P_COURTNEY_1, HatchloamField_Text_CourtneyDefeated
	goto HatchloamField_EventScript_CourtneyPostBattle

HatchloamField_EventScript_CourtneyPostBattle::
	speakername HatchloamField_Text_NameCourtney
	msgbox HatchloamField_Text_ThatWasFun, MSGBOX_DEFAULT
	setvar VAR_OZONE_ADMINS_STATE, 10
	setflag FLAG_TEMP_A
	turnobject LOCALID_COURTNEY, DIR_NORTH
	speakername HatchloamField_Text_NameCourtney
	msgbox HatchloamField_Text_IllStockNewBerries, MSGBOX_DEFAULT
	closemessage
	release
	end

HatchloamField_EventScript_CourtneyIdlePostBattle::
	speakername HatchloamField_Text_NameCourtney
	msgbox HatchloamField_Text_TrickHouseIsNorth, MSGBOX_AUTOCLOSE
	release
	end

HatchloamField_EventScript_CourtneyIdle::
	speakername HatchloamField_Text_NameCourtney
	msgbox HatchloamField_Text_HowIsYourJourney, MSGBOX_AUTOCLOSE
	release
	end

HatchloamField_EventScript_Dustin::
    trainerbattle_single TRAINER_P_DUSTIN, HatchloamField_Text_DustinIntro, HatchloamField_Text_DustinDefeated
    msgbox HatchloamField_Text_DustinPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_Hayley::
    trainerbattle_single TRAINER_P_HAYLEY, HatchloamField_Text_HayleyIntro, HatchloamField_Text_HayleyDefeated
    msgbox HatchloamField_Text_HayleyPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_EnaAndMina::
    trainerbattle_double TRAINER_P_ENA_AND_MINA, HatchloamField_Text_EnaAndMinaIntro, HatchloamField_Text_EnaAndMinaDefeated, HatchloamField_Text_EnaAndMinaNeedTwoMons
    msgbox HatchloamField_Text_EnaAndMinaPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_Dill::
    trainerbattle_single TRAINER_P_DILL, HatchloamField_Text_DillIntro, HatchloamField_Text_DillDefeated
    msgbox HatchloamField_Text_DillPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_Delilah::
    trainerbattle_single TRAINER_P_DELILAH, HatchloamField_Text_DelilahIntro, HatchloamField_Text_DelilahDefeated
    msgbox HatchloamField_Text_DelilahPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_JiyuAndShirou::
    trainerbattle_double TRAINER_P_JIYU_AND_SHIROU, HatchloamField_Text_JiyuAndShirouIntro, HatchloamField_Text_JiyuAndShirouDefeated, HatchloamField_Text_JiyuAndShirouNeedTwoMons
    msgbox HatchloamField_Text_JiyuAndShirouPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_Samuel::
    trainerbattle_single TRAINER_P_SAMUEL, HatchloamField_Text_SamuelIntro, HatchloamField_Text_SamuelDefeated
    msgbox HatchloamField_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_YerbaAndBuena::
    trainerbattle_double TRAINER_P_YERBA_AND_BUENA, HatchloamField_Text_YerbaAndBuenaIntro, HatchloamField_Text_YerbaAndBuenaDefeated, HatchloamField_Text_YerbaAndBuenaNeedTwoMons
    msgbox HatchloamField_Text_YerbaAndBuenaPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_LexAndTrish::
    trainerbattle_double TRAINER_P_LEX_AND_TRISH, HatchloamField_Text_LexAndTrishIntro, HatchloamField_Text_LexAndTrishDefeated, HatchloamField_Text_LexAndTrishNeedTwoMons
    msgbox HatchloamField_Text_LexAndTrishPostBattle, MSGBOX_AUTOCLOSE
    end

HatchloamField_EventScript_DayCareSign::
	msgbox HatchloamField_Text_DayCareSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_HatchloamSign::
	msgbox HatchloamField_Text_HatchloamSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_TrickHouseSign::
	msgbox HatchloamField_Text_TrickHouseSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_VerdanturfSign::
	msgbox HatchloamField_Text_VerdanturfSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_OldaleSign::
	msgbox HatchloamField_Text_OldaleSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_BerriesSign::
	msgbox HatchloamField_Text_BerriesSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_FirTreesSign::
	msgbox HatchloamField_Text_FirTreesSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_ColumnarTreesSign::
	msgbox HatchloamField_Text_ColumnarTreesSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_FlowersSign::
	msgbox HatchloamField_Text_FlowersSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_PondSign::
	msgbox HatchloamField_Text_PondSign, MSGBOX_SIGN
	end

HatchloamField_EventScript_ExcessSign::
	msgbox HatchloamField_Text_ExcessSign, MSGBOX_SIGN
	end

HatchloamField_Text_DayCareSign:
	.string "Everyone Is Welcome At The\n"
	.string "Hatchloam Day Care!\l"
	.string "We Sell Many Berries!$"

HatchloamField_Text_HatchloamSign:
	.string "Now Entering Hatchloam Field!\n"
	.string "Please Treat The Crops Well!$"

HatchloamField_Text_TrickHouseSign:
	.string "COULD THIS BE???\n"
	.string "THE TRICK HOUSE???$"

HatchloamField_Text_VerdanturfSign:
	.string "VERDANTURF TOWN CHECKPOINT\n"
	.string "Only those with residency passes\l"
	.string "will be allowed access.$"

HatchloamField_Text_OldaleSign:
	.string "SOUTH - OLDALE TOWN$"

HatchloamField_Text_BerriesSign:
	.string "The Soil In These Plots Is\n"
	.string "Planned For Berries!\l"
	.string "You Can Pick From Our Latest Harvest\l"
	.string "In The Day Care!$"

HatchloamField_Text_FirTreesSign:
	.string "Fir Tree Grove$"

HatchloamField_Text_ColumnarTreesSign:
	.string "Columnar Tree Grove$"

HatchloamField_Text_FlowersSign:
	.string "Hatchloam Field's Renowned\n"
	.string "Flower Patch$"

HatchloamField_Text_PondSign:
	.string "This Pond Is Being Used To\n"
	.string "Grow Algae And Moss! Do Not\l"
	.string "Disturb The Waters!$"

HatchloamField_Text_ExcessSign:
	.string "Excess Flower Storage$"

HatchloamField_Text_DustinIntro:
	.string "These here Pokémon are the finest\n"
	.string "I have ever bred!$"

HatchloamField_Text_DustinDefeated:
	.string "What?! No way!\n"
	.string "My finely bred Pokémon, defeated?!$"

HatchloamField_Text_DustinPostBattle:
	.string "How could my Pokémon be bested by a\n"
	.string "bunch of wild-caught savages!?\p"
	.string "It just doesn't make sense.$"

HatchloamField_Text_HayleyIntro:
	.string "It amazes me how many trainers are\n"
	.string "stumped why an egg 'appears' at the\l"
	.string "daycare...$"

HatchloamField_Text_HayleyDefeated:
	.string "I wonder... have their parents ever\n"
	.string "given them the 'talk'?...$"

HatchloamField_Text_HayleyPostBattle:
	.string "Don't look at me like that!\n"
	.string "I'm not gonna be the one to explain the\l"
	.string "beauty of life to them!...\p"
	.string "Way too embarrassing...$"

HatchloamField_Text_EnaAndMinaIntro:
	.string "ENA: We move in unison.\n"
	.string "MINA: We are one.$"

HatchloamField_Text_EnaAndMinaDefeated:
	.string "ENA: Us two, bested.\n"
	.string "MINA: By your single hand.$"

HatchloamField_Text_EnaAndMinaPostBattle:
	.string "ENA: We espers need more training.\n"
	.string "MINA: To best you, of course.$"

HatchloamField_Text_EnaAndMinaNeedTwoMons:
	.string "ENA: We are two in one.\n"
	.string "MINA: But you'd need two to keep up.$"

HatchloamField_Text_DillIntro:
	.string "Shush! Your loud footsteps are scaring\n"
	.string "them all away!$"

HatchloamField_Text_DillDefeated:
	.string "What?! How dare you disrespect me?!\n"
	.string "The most famous Bug researcher in\l"
	.string "all of Hoenn!?$"

HatchloamField_Text_DillPostBattle:
	.string "W-what do you mean you don't know who I\n"
	.string "am?! Hmph, kids these days...\l"
	.string "no respect I say, no respect at all!$"

HatchloamField_Text_DelilahIntro:
	.string "(sniff, sniff...)\n"
	.string "Yes, I smell a strong trainer!$"

HatchloamField_Text_DelilahDefeated:
	.string "(sniffle, sniffle...)\n"
	.string "Yes, that's it...\p"
	.string "The agonizing scent of defeat...$"

HatchloamField_Text_DelilahPostBattle:
	.string "Your eyes can betray you, but your nose\n"
	.string "knows all.$"

HatchloamField_Text_JiyuAndShirouIntro:
	.string "JIYU: Ah, Shirou! This will be\n"
	.string "      a worthy adversary!\l"
	.string "SHIROU: To test the new sword\l"
	.string "        technique? O-Okay...$"

HatchloamField_Text_JiyuAndShirouDefeated:
	.string "SHIROU: Our Pokemon's blades\n"
	.string "        were too dull...\l"
	.string "JIYU: That is perfectly fine!\l"
	.string "      They'll sharpen with time.$"

HatchloamField_Text_JiyuAndShirouPostBattle:
	.string "JIYU: Shirou and I and our Pokemon\n"
	.string "      train by dueling, blades drawn!\l"
	.string "SHIROU: Pawniard and its evolutions\l"
	.string "        are precise, if you train\l"
	.string "        them well...$"

HatchloamField_Text_JiyuAndShirouNeedTwoMons:
	.string "JIYU: I don't think this\n"
	.string "      adversary is quite worthy...\l"
	.string "SHIROU: They're lacking in\l"
	.string "        blade discipline.$"

HatchloamField_Text_SamuelIntro:
	.string "Back and forth... Back and forth...\n"
	.string "Oh! An interruption!$"

HatchloamField_Text_SamuelDefeated:
	.string "Well, off I go now...$"

HatchloamField_Text_SamuelPostBattle:
	.string "Wanna know why I'm biking back and\n"
	.string "forth?\p"
	.string "I'm hatching Pokémon eggs, of course!$"

HatchloamField_Text_YerbaAndBuenaIntro:
	.string "YERBA: Let us have a friendly\n"
	.string "       match among the gorgeous\l"
	.string "       greenery of the field!\p"
	.string "BUENA: What could be more perfect?$"

HatchloamField_Text_YerbaAndBuenaDefeated:
	.string "YERBA: I had a good time! It does\n"
	.string "       a body good to smile.\l"
	.string "BUENA: You always owe it to\l"
	.string "       yourself to appreciate what's\l"
	.string "       all around you.$"

HatchloamField_Text_YerbaAndBuenaPostBattle:
	.string "YERBA: Plants need a lot of love and\n"
	.string "       care. Well, actually,\l"
	.string "       everything in life does.\l"
	.string "BUENA: Practice kindness,\l"
	.string "       and you will be rewarded.$"

HatchloamField_Text_YerbaAndBuenaNeedTwoMons:
	.string "(They're busy right now\n"
	.string "preparing the soil...)$"

HatchloamField_Text_LexAndTrishIntro:
	.string "LEX: Oh, someone made it to us!\n"
	.string "TRISH: You didn't trample the\l"
	.string "       flowers, did you?$"

HatchloamField_Text_LexAndTrishDefeated:
	.string "TRISH: We had to stop and\n"
	.string "       smell the roses!\l"
	.string "LEX: Yeah, we stopped paying\l"
	.string "     attention to this battle\l"
	.string "     long ago...$"

HatchloamField_Text_LexAndTrishPostBattle:
	.string "LEX: Think they'll let us take\n"
	.string "     some of the flowers home\l"
	.string "     to plant?\l"
	.string "TRISH: It can't hurt to ask!$"

HatchloamField_Text_LexAndTrishNeedTwoMons:
	.string "(They're busy right now\n"
	.string "preparing the soil...)$"

HatchloamField_Text_NameCourtney:
	.string "Courtney$"

HatchloamField_Text_NiceToSeeYou:
	.string "Welcome to Hatchloam Field,\n"
	.string "{PLAYER}. It's nice to see\l"
	.string "you again! I hope you've\l"
	.string "been well.\p"
	.string "I must tell you, watching you\n"
	.string "taking on the sisters at\l"
	.string "Pretty Petals really made me want\l"
	.string "to pick up battling again.\p"
	.string "I'm a bit rusty, but I'd like\n"
	.string "to try out my team on you.\l"
	.string "Does that sound like it'd\l"
	.string "be up your alley?$"

HatchloamField_Text_ThatsTooBad:
	.string "That's too bad. Come talk\n"
	.string "to me again if you change your mind.\l"
	.string "Oh, and check out the berry shop\l"
	.string "in the farmhouse too!$"

HatchloamField_Text_CourtneyIntro:
	.string "Excellent! Here goes nothing!$"

HatchloamField_Text_CourtneyDefeated:
	.string "I'll concede defeat.\n"
	.string "I'm still far too rusty...$"

HatchloamField_Text_ThatWasFun:
	.string "I had a good time! Ever since\n"
	.string "leaving Team Magma, I hung\l"
	.string "up my trainer's cap, so to speak.\l"
	.string "It feels nice to battle for fun\l"
	.string "instead of for... them.$"

HatchloamField_Text_IllStockNewBerries:
	.string "I will tell Teala to offer you\n"
	.string "the more deluxe selection of\l"
	.string "berries the next time you are\l"
	.string "in the shop, since I consider\l"
	.string "you a friend.\l"
	.string "It's my pleasure.\p"
	.string "...Oh? Have you been looking\n"
	.string "for the Trick House? I see.\l"
	.string "Well, Giddy had made me promise\l"
	.string "to zip my lips, but...\p"
	.string "...I'll let the secret slip.\n"
	.string "If you squeeze through the pine\l"
	.string "trees at the north end of\l"
	.string "the farm, there is a secret\l"
	.string "passage leading to the\l"
	.string "Trick House. But you didn't\l"
	.string "hear that from me!$"

HatchloamField_Text_TrickHouseIsNorth:
	.string "If you squeeze through the pine\n"
	.string "trees at the north end of\l"
	.string "the farm, there is a secret\l"
	.string "passage leading to the\l"
	.string "Trick House. But you didn't\l"
	.string "hear that from me!$"

HatchloamField_Text_HowIsYourJourney:
	.string "How has your journey been\n"
	.string "treating you, {PLAYER}?\p"
	.string "The harvest has been bountiful\n"
	.string "this year. I'm very thankful!$"
