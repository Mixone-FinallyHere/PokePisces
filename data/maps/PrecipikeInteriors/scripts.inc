PrecipikeInteriors_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PrecipikeInteriors_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, PrecipikeInteriors_OnTransition
	.byte 0

PrecipikeInteriors_OnFrame:
	map_script_2 VAR_TEMP_4, 69, PrecipikeInteriors_EventScript_GiveEgg
	.2byte 0

PrecipikeInteriors_OnTransition:
	call_if_set FLAG_PISCES_D, PrecipikeInteriors_EventScript_SetTempVar
	end

PrecipikeInteriors_EventScript_SetTempVar::
	setvar VAR_TEMP_4, 69
	return

PrecipikeInteriors_EventScript_GiveEgg::
	applymovement OBJ_EVENT_ID_PLAYER, PrecipikeInteriors_Movement_FaceLady
	msgbox PrecipikeInteriors_Text_CaughtThatRascal, MSGBOX_DEFAULT
	setflag FLAG_PRECIPIKE_EGG
	setvar VAR_TEMP_4, 0
	clearflag FLAG_PISCES_D
	clearflag FLAG_TRAP_PRECIPIKE_EGGNEGGMA
	goto PrecipikeInteriors_EventScript_ReceiveEgg
	end

PrecipikeInteriors_EventScript_ReceiveEgg::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EXEGGCUTE
	giveegg SPECIES_DRAKULARK
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, PrecipikeInteriors_EventScript_ReceiveEggParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, PrecipikeInteriors_EventScript_ReceiveEggPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

PrecipikeInteriors_EventScript_ReceiveEggParty::
	call PrecipikeInteriors_EventScript_ReceivedEggFanfare
	end

PrecipikeInteriors_EventScript_ReceiveEggPC::
	call PrecipikeInteriors_EventScript_ReceivedEggFanfare
	call Common_EventScript_TransferredToPC
	end

PrecipikeInteriors_EventScript_ReceivedEggFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message PrecipikeInteriors_Text_PlayerReceivedEgg
	waitmessage
	waitfanfare
	closemessage
	return

PrecipikeInteriors_Movement_FaceLady:
	face_up
	step_end

PrecipikeInteriors_EventScript_EggLady::
	lock
	faceplayer
	goto_if_set FLAG_SCUTTILL_EGG, PrecipikeInteriors_EventScript_TheEggDemon
	goto_if_set FLAG_PRECIPIKE_EGG, PrecipikeInteriors_EventScript_GoToScuttill
	msgbox PrecipikeInteriors_Text_HelloILikeEggs, MSGBOX_DEFAULT
	goto_if_defeated TRAINER_P_WREN, PrecipikeInteriors_EventScript_CheckMangrottoEgg
	msgbox PrecipikeInteriors_Text_GoHuntSomeEggThieves, MSGBOX_DEFAULT
	closemessage
	release
	end

PrecipikeInteriors_EventScript_CheckMangrottoEgg::
	goto_if_set FLAG_MANGROTTO_EGG, PrecipikeInteriors_EventScript_CheckMossdeepEgg
	msgbox PrecipikeInteriors_Text_GoHuntSomeEggThieves, MSGBOX_DEFAULT
	closemessage
	release
	end

PrecipikeInteriors_EventScript_CheckMossdeepEgg::
	goto_if_set FLAG_MOSSDEEP_EGG, PrecipikeInteriors_EventScript_WantToCatchEgg
	msgbox PrecipikeInteriors_Text_GoHuntSomeEggThieves, MSGBOX_DEFAULT
	closemessage
	release
	end

PrecipikeInteriors_EventScript_WantToCatchEgg::
	msgbox PrecipikeInteriors_Text_WeShouldCatchThatGuy, MSGBOX_DEFAULT
	setflag FLAG_TRAP_PRECIPIKE_EGGNEGGMA
	closemessage
	release
	end

PrecipikeInteriors_EventScript_GoToScuttill::
	msgbox PrecipikeInteriors_Text_GoToScuttill, MSGBOX_AUTOCLOSE
	release
	end

PrecipikeInteriors_EventScript_TheEggDemon::
	goto_if_set FLAG_RECEIVED_LUCKY_EGGS, PrecipikeInteriors_EventScript_TheEggDemon2
	msgbox PrecipikeInteriors_Text_HaveTheseEggs, MSGBOX_DEFAULT
	giveitem ITEM_LUCKY_EGG, 3
	setflag FLAG_RECEIVED_LUCKY_EGGS
	msgbox PrecipikeInteriors_Text_TheEggDemon, MSGBOX_AUTOCLOSE
	release
	end

PrecipikeInteriors_EventScript_TheEggDemon2::
	msgbox PrecipikeInteriors_Text_TheEggDemon, MSGBOX_AUTOCLOSE
	release
	end

PrecipikeInteriors_EventScript_SadFisherman::
	lock
	faceplayer
	speakername PrecipikeInteriors_Text_NameSadFisher
	goto_if_unset FLAG_RECEIVED_OLD_ROD, PrecipikeInteriors_EventScript_NoOldRod
	goto_if_set FLAG_RECEIVED_GOOD_ROD, PrecipikeInteriors_EventScript_HowsFishing
	msgbox PrecipikeInteriors_Text_GettingItchToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PrecipikeInteriors_EventScript_BattleSadFisher
	goto_if_eq VAR_RESULT, NO, PrecipikeInteriors_EventScript_NotGettingItchToFish
	end

PrecipikeInteriors_EventScript_NoOldRod::
	msgbox PrecipikeInteriors_Text_NoOldRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PrecipikeInteriors_EventScript_BattleSadFisherNoOldRod
	msgbox PrecipikeInteriors_Text_DontLetDoorHitYa, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

PrecipikeInteriors_EventScript_BattleSadFisherNoOldRod::
	trainerbattle_single TRAINER_P_SADFISHER_2, PrecipikeInteriors_Text_SadFisherIntro, PrecipikeInteriors_Text_SadFisherDefeat, PrecipikeInteriors_EventScript_GiveOldAndGoodRod
	release
	end

PrecipikeInteriors_EventScript_GiveOldAndGoodRod::
	msgbox PrecipikeInteriors_Text_PostNoOld, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	giveitem ITEM_GOOD_ROD
	setflag FLAG_RECEIVED_GOOD_ROD
	msgbox PrecipikeInteriors_Text_FishingAdviceNoOld, MSGBOX_DEFAULT
	speakername NULL
	release
	end

PrecipikeInteriors_EventScript_BattleSadFisher::
	trainerbattle_single TRAINER_P_SADFISHER_2, PrecipikeInteriors_Text_SadFisherIntro, PrecipikeInteriors_Text_SadFisherDefeat, PrecipikeInteriors_EventScript_GiveGoodRod
	release
	end

PrecipikeInteriors_EventScript_GiveGoodRod::
	msgbox PrecipikeInteriors_Text_GiveYouOneOfMyRods, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	setflag FLAG_RECEIVED_GOOD_ROD
	msgbox PrecipikeInteriors_Text_ThrowInFishingAdvice, MSGBOX_DEFAULT
	speakername NULL
	release
	end

PrecipikeInteriors_EventScript_NotGettingItchToFish::
	msgbox PrecipikeInteriors_Text_ThatsTooBadThen, MSGBOX_DEFAULT
	speakername NULL
	release
	end

PrecipikeInteriors_EventScript_HowsFishing::
	msgbox PrecipikeInteriors_Text_HowsYourFishing, MSGBOX_AUTOCLOSE
	specialvar VAR_RESULT, CheckAllSadsod
	goto_if_eq VAR_RESULT, TRUE, PrecipikeInteriors_EventScript_SaltyTear
	speakername NULL
	release
	end

PrecipikeInteriors_EventScript_SaltyTear::
	checkitem ITEM_SALTY_TEAR
	goto_if_eq VAR_RESULT, TRUE, PrecipikeInteriors_EventScript_GaveSaltyTear
	msgbox PrecipikeInteriors_Text_SadsodMaster, MSGBOX_DEFAULT
	giveitem ITEM_SALTY_TEAR
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	speakername NULL
	release
	end

PrecipikeInteriors_EventScript_GaveSaltyTear::
	msgbox PrecipikeInteriors_Text_AlreadyGaveIt, MSGBOX_AUTOCLOSE
	speakername NULL
	release
	end

PrecipikeInteriors_Text_NameSadFisher:
	.string "Sad Fisher$"

PrecipikeInteriors_Text_GettingItchToFish:
	.string "Surprised to come upon me again, eh?\n"
	.string "Well, the shores have a way of\l"
	.string "keepin' fishers connected.\p"
	.string "I see you've been gettin' good use\n"
	.string "out of your current fishin' skills.\l"
	.string "Maybe it's time you got yourself\l"
	.string "a shiny new upgrade.\p"
	.string "Lucky you. I have a spare rod.\n"
	.string "Bit of a step up from your gear.\l"
	.string "But I ain't givin' it up\l"
	.string "without a battle, rookie.\p"
	.string "You prepared?\n"
	.string "I ain't goin' easy on ya this time.$"

PrecipikeInteriors_Text_NoOldRod:
	.string "...Hey, stranger.\p"
	.string "Hmm... you've gotten this far\n"
	.string "without any fishin' whatsoever!?\l"
	.string "Must be equally foolish, and lucky.\p"
	.string "MAYBE I shouldn't give you the\n"
	.string "courtesy of offerin' a Good Rod.\l"
	.string "But... eh, what's a hobby\l"
	.string "if ya don't try sharin' it.\p"
	.string "Best me in battle, I give ya\n"
	.string "an Old AND Good Rod. But I'm\l"
	.string "a high level competitor...\p"
	.string "Sound like a plan?\n$"

PrecipikeInteriors_Text_SadFisherIntro:
	.string "Don't you shed a tear\n"
	.string "when you get whooped, y'hear?$"

PrecipikeInteriors_Text_SadFisherDefeat:
	.string "...Showed me up.$"

PrecipikeInteriors_Text_GiveYouOneOfMyRods:
	.string "Time for the next level, {PLAYER}.$"

PrecipikeInteriors_Text_ThrowInFishingAdvice:
	.string "This rod is more enticing\n"
	.string "to a broad range of aquatic Pokemon.\l"
	.string "I'd advise usin' it whenever\l"
	.string "you see water. You'll haul in\l"
	.string "quite a few new catches.$"

PrecipikeInteriors_Text_ThatsTooBadThen:
	.string "Hah!\n"
	.string "Once a rookie, always a rookie.$"

PrecipikeInteriors_Text_DontLetDoorHitYa:
	.string "Then don't let the door hit ya\n"
	.string "on your way out.$"

PrecipikeInteriors_Text_PostNoOld:
	.string "Fair n' square. Here's your gear.$"

PrecipikeInteriors_Text_FishingAdviceNoOld:
	.string "Take them there rods out to any\n"
	.string "shoreline and let 'em rip.\l"
	.string "Huge variety of Pokemon in\l"
	.string "the water that you can't be\l"
	.string "gettin' anywhere else.\p"
	.string "Don't remain ignorant to the\n"
	.string "call of the seas, got it?\l"
	.string "...n' best of luck to ya.$"

PrecipikeInteriors_Text_HowsYourFishing:
	.string "Sadsod's my most liked Pokemon.\n"
	.string "There's somethin' in their\l"
	.string "demeanor that makes ya want\l"
	.string "to care for 'em.\p"
	.string "Catch one and give it a good home.$"

PrecipikeInteriors_Text_SadsodMaster:
	.string "Well, I'll be damned!\n"
	.string "A whole party of Sadsod, like me...\l"
	.string "you have pristine piscine taste.\p"
	.string "Listen up. I don't have plans\n"
	.string "to evolve mine, but... you might.\l"
	.string "And to do that, Sadsod must be...\l"
	.string "err, pushed, more than most.\p"
	.string "This item may help ya.\n"
	.string "But take caution, as the little guy\l"
	.string "may get even sadder...$"

PrecipikeInteriors_Text_AlreadyGaveIt:
	.string "I can hear your Sadsod grunting\n"
	.string "occassionally. That means they\l"
	.string "like ya.$"

PrecipikeInteriors_Text_CaughtThatRascal:
	.string "Nice wrangling! I made sure\n"
	.string "to get that Eggneggma put away\l"
	.string "in a shelter.\p"
	.string "It was holding this Egg that it\n"
	.string "probably stole from somewhere.\l"
	.string "Consider it yours!$"

PrecipikeInteriors_Text_PlayerReceivedEgg:
	.string "{PLAYER} received an Egg!$"

PrecipikeInteriors_Text_HelloILikeEggs:
	.string "Salutations. I am what you\n"
	.string "may call an Egg Connoisseur.\p"
	.string "Hatching Pokemon Eggs used to be\n"
	.string "a lot more common in Hoenn.\l"
	.string "Though, recently, no one likes\l"
	.string "to do it anymore.\p"
	.string "The Pokemon Eggneggma has been\n"
	.string "taking advantage of\l"
	.string "peoples' lethargy, and stealing\l"
	.string "Eggs from breeders whenever\l"
	.string "they feel they can get away with it.\p"
	.string "Those blasted thieves!\n"
	.string "I wish they'd be taught a lesson!$"

PrecipikeInteriors_Text_GoHuntSomeEggThieves:
	.string "I'm pretty sure that there are\n"
	.string "thieving Eggneggma in\l"
	.string "Mangrotto Tunnel and Mossdeep City.\p"
	.string "Let me know if they've been...\n"
	.string "scrambled, so to speak.$"

PrecipikeInteriors_Text_WeShouldCatchThatGuy:
	.string "Oh? You've been doing your\n"
	.string "due diligence in chasing down\l"
	.string "those little psychos?\p"
	.string "That puts a smile on my face!\n"
	.string "Just what I like to hear.\p"
	.string "...What? There's another at\n"
	.string "large outside my home as we speak?\l"
	.string "Well, say no more!\l"
	.string "I'll get my husband and daughter\l"
	.string "and we'll corner it!$"

PrecipikeInteriors_Text_GoToScuttill:
	.string "I've heard from the grapevine\n"
	.string "that there's been thievery\l"
	.string "in the Scuttill Way area.\l"
	.string "Keep your eyes peeled!$"

PrecipikeInteriors_Text_HaveTheseEggs:
	.string "I've heard you've really been\n"
	.string "hunting down those egg thieves!\l"
	.string "Here, take these as a token\l"
	.string "of appreciation from me.$"

PrecipikeInteriors_Text_TheEggDemon:
	.string "You got the Scuttill Way\n"
	.string "thief as well? Amazing!\l"
	.string "Those loons can't slip away\l"
	.string "under your watch!\p"
	.string "I often wonder what their goal is.\n"
	.string "It seems like a good amount of\l"
	.string "the Eggneggma in this region\l"
	.string "are bringing their stolen Eggs\l"
	.string "to some central source.\l"
	.string "Maybe some sort of Queen?\p"
	.string "Hmm. The only leads I have on\n"
	.string "the matter is some rumblings\l"
	.string "of Eggneggma activity in\l"
	.string "Basalin Coast. But I haven't\l"
	.string "personally seen any there...$"
