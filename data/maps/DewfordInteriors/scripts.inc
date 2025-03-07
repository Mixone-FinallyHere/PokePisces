DewfordInteriors_MapScripts::
	.byte 0

DewfordInteriors_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_GLAREYALE_TRADE_COMPLETED, DewfordInteriors_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_GLAREYALE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox DewfordInteriors_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DewfordInteriors_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, DewfordInteriors_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, DewfordInteriors_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox DewfordInteriors_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_GLAREYALE_TRADE_COMPLETED
	release
	end

DewfordInteriors_EventScript_DeclineTrade::
	msgbox DewfordInteriors_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

DewfordInteriors_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox DewfordInteriors_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

DewfordInteriors_EventScript_TradeCompleted::
	msgbox DewfordInteriors_Text_ThanksForTrading, MSGBOX_DEFAULT
	release
	end

DewfordInteriors_EventScript_SpitfaxLiker::
	lock
	faceplayer
	getcaughtmon SPECIES_SPITFAX
	goto_if_eq VAR_RESULT, TRUE, DewfordInteriors_EventScript_SpitfaxCaught
	goto_if_eq setvar VAR_SPITFAX_QUEST_STATE, 2, DewfordInteriors_EventScript_SpitfaxDirections
	goto_if_eq VAR_SPITFAX_QUEST_STATE, 1, DewfordInteriors_EventScript_SpitfaxLikerEnterCode
	msgbox DewfordInteriors_Text_WereCryptidEnthusiasts, MSGBOX_DEFAULT
	setvar VAR_SPITFAX_QUEST_STATE, 1
	closemessage
	release
	end

DewfordInteriors_EventScript_SpitfaxLikerEnterCode::
	msgbox DewfordInteriors_Text_EnterCodeText, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq VAR_RESULT, NO, DewfordInteriors_EventScript_CodeEntryRelease
    special EnterCode
    waitstate
    special GetCodeFeedback
    goto_if_eq VAR_RESULT, 2, DewfordInteriors_EventScript_CodeEntrySuccess
	goto DewfordInteriors_EventScript_CodeEntryFail
	release
	end

DewfordInteriors_EventScript_CodeEntrySuccess::
	setvar VAR_SPITFAX_QUEST_STATE, 2
	msgbox DewfordInteriors_Text_CodeEntrySuccess, MSGBOX_AUTOCLOSE
	release
	end

DewfordInteriors_EventScript_CodeEntryFail::
	msgbox DewfordInteriors_Text_CodeEntryFail, MSGBOX_AUTOCLOSE
	release
	end

DewfordInteriors_EventScript_CodeEntryRelease::
	release
	end

DewfordInteriors_EventScript_SpitfaxDirections::
	msgbox DewfordInteriors_Text_SpitfaxDirections, MSGBOX_AUTOCLOSE
	release
	end

DewfordInteriors_EventScript_SpitfaxCaught::
	msgbox DewfordInteriors_Text_SpitfaxCaught, MSGBOX_AUTOCLOSE
	release
	end

DewfordInteriors_Text_WereCryptidEnthusiasts:
	.string "(This man is snickering annoyingly.)\p"
	.string "So, you're wanting to join\n"
	.string "our Cryptid Club, huh...\p"
	.string "We all are convinced that there\n"
	.string "are Pokemon out there that exist\l"
	.string "when many say they don't!\l"
	.string "Even though I've never seen\l"
	.string "one, I know that Spitfax HAS to\l"
	.string "exist! There's too much evidence\l"
	.string "gathered over the years for it\l"
	.string "to not be real somehow!\p"
	.string "You want to find Spitfax too.\n"
	.string "I know it! I can sense it\l"
	.string "within you. BUT...\l"
	.string "we don't let in outsiders\l"
	.string "quite so easily...\p"
	.string "To prove you're a capable cryptid\n"
	.string "investigator, you're going to\l"
	.string "have to solve MY mystery first!\p"
	.string "Somewhere deep within the waters\n"
	.string "of Hoenn, the Cryptid Club has\l"
	.string "parked its submarine...\l"
	.string "It's defunct now, so we could\l"
	.string "afford to just leave it.\l"
	.string "To this day, its black box sends\l"
	.string "out a message...\p"
	.string "If you can find the sub and\n"
	.string "tell me the message it is spouting,\l"
	.string "I'll let you into the club!\p"
	.string "Then we can REALLY get to business.\n"
	.string "Happy hunting...!$"

DewfordInteriors_Text_EnterCodeText:
	.string "Did you end up finding our\n"
	.string "submarine? You know how to prove it.\l"
	.string "Will you tell me the message?$"

DewfordInteriors_Text_CodeEntrySuccess:
	.string "...\p"
	.string "Well, I'll be DAMNED!\n"
	.string "Good hunting, cryptid enthusiast...\p"
	.string "...Or should I say,\n"
	.string "CRYPTID CLUB MEMBER! That's\l"
	.string "right, you've passed initiation!\l"
	.string "Now you can know all of our\l"
	.string "juicy Spitfax intel!\p"
	.string "Here's all the information we\n"
	.string "know about that elusive Pokemon.\l"
	.string "It lives in heavily forested areas,\l"
	.string "where it collects berries to hoard.\l"
	.string "It is a simple and small creature.\l"
	.string "Some reports say it is red,\l"
	.string "others dark brown.\p"
	.string "There is also one particularly odd\n"
	.string "report, claiming that a hunter once\l"
	.string "saw a Spitfax dart into the trees\l"
	.string "when looking west from a stone.\l"
	.string "He said there were exactly three\l"
	.string "stones in his vicinity, and he was\l"
	.string "looking west from the\l"
	.string "northernmost rock.\p"
	.string "Though you'd think that'd be\n"
	.string "enough info to pin down, rocks\l"
	.string "and trees are pretty common, no?\l"
	.string "So we haven't had any luck.\p"
	.string "Anyways, that's all I know!$"

DewfordInteriors_Text_CodeEntryFail:
	.string "Nope! That's not it. Sorry!\n"
	.string "Keep on huntin'!$"

DewfordInteriors_Text_SpitfaxDirections:
	.string "Here's all the information we\n"
	.string "know about that elusive Pokemon.\l"
	.string "It lives in heavily forested areas,\l"
	.string "where it collects berries to hoard.\l"
	.string "It is a simple and small creature.\l"
	.string "Some reports say it is red,\l"
	.string "others dark brown.\p"
	.string "There is also one particularly odd\n"
	.string "report, claiming that a hunter once\l"
	.string "saw a Spitfax dart into the trees\l"
	.string "when looking west from a stone.\l"
	.string "He said there were exactly three\l"
	.string "stones in his vicinity, and he was\l"
	.string "looking west from the\l"
	.string "northernmost rock.\p"
	.string "Though you'd think that'd be\n"
	.string "enough info to pin down, rocks\l"
	.string "and trees are pretty common, no?\l"
	.string "So we haven't had any luck.\p"
	.string "Anyways, that's all I know!$"

DewfordInteriors_Text_SpitfaxCaught:
	.string "Hmm? What's up, club member?\p"
	.string "(You show the guy your Spitfax's\n"
	.string "entry in the Pokedex.)\p"
	.string "Oh, sick! That's really good\n"
	.string "art of what it's assumed to look\l"
	.string "like. And the lore is on point!\p"
	.string "...You're saying you caught one?\n"
	.string "Look, sorry. I'm not buying it!\l"
	.string "Wouldn't it be all over the news?\p"
	.string "Nice try, but I don't think finding\n"
	.string "Spitfax is gonna be that easy...$"

DewfordInteriors_Text_IllTradeIfYouWant:
	.string "I'll trade you my {STR_VAR_2} for\n"
	.string "a {STR_VAR_1} if you want.$"

DewfordInteriors_Text_PleaseBeGoodToMyPokemon:
	.string "Please be good to my POKéMON.$"

DewfordInteriors_Text_DoesntLookLikeMonToMe:
	.string "Huh? That doesn't look anything like\n"
	.string "a {STR_VAR_1} to me.$"

DewfordInteriors_Text_YouDontWantToThatsOkay:
	.string "Oh, if you don't want to, that's okay.$"

DewfordInteriors_Text_ThanksForTrading:
	.string "Thanks for the trade.$"
