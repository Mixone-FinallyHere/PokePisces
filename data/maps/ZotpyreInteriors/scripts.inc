ZotpyreInteriors_MapScripts::
	.byte 0

ZotpyreInteriors_EventScript_SpiritBreak::
	lock
	faceplayer
	checkitem ITEM_TM_SPIRIT_BREAK
	goto_if_eq VAR_RESULT, TRUE, ZotpyreInteriors_EventScript_GaveSpiritBreak
	msgbox ZotpyreInteriors_Text_SpiritBreak, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_TM_SPIRIT_BREAK
	closemessage
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	release
	end

ZotpyreInteriors_EventScript_GaveSpiritBreak::
	msgbox ZotpyreInteriors_Text_GaveSpiritBreak, MSGBOX_AUTOCLOSE
	release
	end

ZotpyreInteriors_EventScript_ZoruaEventFather::
	lock
	faceplayer
	goto_if_eq VAR_ZORUA_QUEST_STATE, 1, ZotpyreInteriors_EventScript_WantToSee3Mons
	goto_if_ge VAR_ZORUA_QUEST_STATE, 2, ZotpyreInteriors_EventScript_MySonMightBeOutThere
	msgbox ZotpyreInteriors_Text_AboutMySon, MSGBOX_DEFAULT
	setvar VAR_ZORUA_QUEST_STATE, 1
	goto ZotpyreInteriors_EventScript_WantToSee3Mons
	release
	end

ZotpyreInteriors_EventScript_WantToSee3Mons::
	msgbox ZotpyreInteriors_Text_IWantToSee3Mons, MSGBOX_DEFAULT
	getcaughtmon SPECIES_DUNSPARCE
	goto_if_eq VAR_RESULT, TRUE, ZotpyreInteriors_EventScript_Check2
	msgbox ZotpyreInteriors_Text_WillWaitForWorthyTrainer, MSGBOX_AUTOCLOSE
	release
	end

ZotpyreInteriors_EventScript_Check2::
	getcaughtmon SPECIES_CROAGUNK
	goto_if_eq VAR_RESULT, TRUE, ZotpyreInteriors_EventScript_Check3
	msgbox ZotpyreInteriors_Text_WillWaitForWorthyTrainer, MSGBOX_AUTOCLOSE
	release
	end

ZotpyreInteriors_EventScript_Check3::
	getcaughtmon SPECIES_BISHARP
	goto_if_eq VAR_RESULT, TRUE, ZotpyreInteriors_EventScript_FinalQuestion
	msgbox ZotpyreInteriors_Text_WillWaitForWorthyTrainer, MSGBOX_AUTOCLOSE
	release
	end

ZotpyreInteriors_EventScript_FinalQuestion::
	message ZotpyreInteriors_Text_LifePhilosophy
	waitmessage
	multichoice 20, 8, MULTI_LIFE_PHILOSOPHY, TRUE
	goto_if_eq VAR_RESULT, 0, ZotpyreInteriors_EventScript_Comedy
	goto_if_eq VAR_RESULT, 1, ZotpyreInteriors_EventScript_Tragedy
	release
	end

ZotpyreInteriors_EventScript_Comedy::
	setvar VAR_ZORUA_QUEST_STATE, 2
	msgbox ZotpyreInteriors_Text_ComedyHuh, MSGBOX_DEFAULT
	goto ZotpyreInteriors_EventScript_GiveZorua
	release
	end

ZotpyreInteriors_EventScript_Tragedy::
	setvar VAR_ZORUA_QUEST_STATE, 3
	msgbox ZotpyreInteriors_Text_TragedyHuh, MSGBOX_DEFAULT
	goto ZotpyreInteriors_EventScript_GiveZorua
	release
	end

ZotpyreInteriors_EventScript_GiveZorua::
	msgbox ZotpyreInteriors_Text_Zorua, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZORUA
	givemon SPECIES_ZORUA, 28
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, ZotpyreInteriors_EventScript_ReceiveZoruaParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, ZotpyreInteriors_EventScript_ReceiveZoruaPC
	goto Common_EventScript_NoMoreRoomForPokemon
	goto ZotpyreInteriors_EventScript_MySonMightBeOutThere
	release
	end

ZotpyreInteriors_EventScript_ReceiveZoruaParty::
	call ZotpyreInteriors_EventScript_ReceivedZoruaFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ZotpyreInteriors_EventScript_MySonMightBeOutThere
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto ZotpyreInteriors_EventScript_MySonMightBeOutThere
	release
	end

ZotpyreInteriors_EventScript_ReceiveZoruaPC::
	call ZotpyreInteriors_EventScript_ReceivedZoruaFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ZotpyreInteriors_EventScript_SendZoruaToPC
	call Common_EventScript_NameReceivedBoxMon
	goto ZotpyreInteriors_EventScript_SendZoruaToPC
	release
	end

ZotpyreInteriors_EventScript_SendZoruaToPC::
	call Common_EventScript_TransferredToPC
	goto ZotpyreInteriors_EventScript_MySonMightBeOutThere
	release
	end

ZotpyreInteriors_EventScript_ReceivedZoruaFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message ZotpyreInteriors_Text_PlayerReceivedZorua
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_ZORUA
	return

ZotpyreInteriors_EventScript_MySonMightBeOutThere::
	msgbox ZotpyreInteriors_Text_MySonMightBeOutThere, MSGBOX_AUTOCLOSE
	release
	end

ZotpyreInteriors_EventScript_CardTrader::
	lock
	faceplayer
	checkitem ITEM_UNO_CARD
	goto_if_eq VAR_RESULT, TRUE, ZotpyreInteriors_EventScript_TradeForCard
	checkitem ITEM_MAGIC_CARD
	goto_if_eq VAR_RESULT, TRUE, ZotpyreInteriors_EventScript_GaveYouMyCard
	msgbox ZotpyreInteriors_Text_WhatINeed, MSGBOX_AUTOCLOSE
	release
	end

ZotpyreInteriors_EventScript_TradeForCard::
	msgbox ZotpyreInteriors_Text_WillYouTradeCards, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ZotpyreInteriors_EventScript_CardTrade
	release
	end

ZotpyreInteriors_EventScript_CardTrade::
	delay 4
	msgbox ZotpyreInteriors_Text_AboutThatCard, MSGBOX_DEFAULT
	closemessage
	removeitem ITEM_UNO_CARD
	giveitem ITEM_MAGIC_CARD
	closemessage
	release
	end

ZotpyreInteriors_EventScript_GaveYouMyCard::
	msgbox ZotpyreInteriors_Text_GaveYouMyCard, MSGBOX_AUTOCLOSE
	release
	end

ZotpyreInteriors_Text_WhatINeed:
	.string "Bah! I am a lover of all things Magic!\n"
	.string "And I mean REAL magic!\l"
	.string "These “Poke Off Morn” creatures\l"
	.string "that people adore? They are\l"
	.string "all dark magic users to me!\l"
	.string "What happened to the simpler\l"
	.string "days of simple tricks and conjurings?\p"
	.string "By the stars above, I remember\n"
	.string "my very first spell.\l"
	.string "Reversi Isrever! It made someone\l"
	.string "speak backwards until you used\l"
	.string "the spell on them again!\l"
	.string "Ah! The good old days!\p"
	.string "If only I could find someone\n"
	.string "with reversal abilities like\l"
	.string "that... I may part with one\l"
	.string "of my prized magic cards...!$"

ZotpyreInteriors_Text_WillYouTradeCards:
	.string "Bah! I am a lover of all things Magic!\n"
	.string "And I mean REAL magic!\l"
	.string "These “Poke Off Morn” creatures\l"
	.string "that people adore? They are\l"
	.string "all dark magic users to me!\l"
	.string "What happened to the simpler\l"
	.string "days of simple tricks and conjurings?\p"
	.string "By the stars above, I remember\n"
	.string "my very first spell.\l"
	.string "Reversi Isrever! It made someone\l"
	.string "speak backwards until you used\l"
	.string "the spell on them again!\l"
	.string "Ah! The good old days!\p"
	.string "If only I could find someone\n"
	.string "with reversal abilities like\l"
	.string "that... I may part with one\l"
	.string "of my prized magic cards...!\p"
	.string "(You flash your Uno Reverse Card\n"
	.string "at the wizardlike gent.)\p"
	.string "Could it be...!? A card bearer!?\p"
	.string "Please, I beseech you...\n"
	.string "Deliver onto me thy card!$"

ZotpyreInteriors_Text_AboutThatCard:
	.string "(You hand the Uno Card over.)\p"
	.string "!semit dlo ekil ,desreveR !suolevraM\n"
	.string "!kcab em sekat siht ,hO\p"
	.string ".draC cigaM ym evah yam uoY\n"
	.string "!drow doog eht hcaerp dna ti ekaT$"

ZotpyreInteriors_Text_GaveYouMyCard:
	.string "lleps dlo taht did woh ,woN\n"
	.string "...niaga og esrever-nu ot$"

ZotpyreInteriors_Text_AboutMySon:
	.string "Welcome to my dwellings.\p"
	.string "Pardon an old codger's ramblings,\n"
	.string "but you remind me an awful lot\l"
	.string "about my son. I don't suppose that\l"
	.string "you'd want to hear about him?\p"
	.string "(You empathize and say yes.)\p"
	.string "Well, my boy... he was always\n"
	.string "destined for big things in life.\p"
	.string "As youth often do, he got bored of\n"
	.string "the quiet life here in Zotpyre.\p"
	.string "His mind and heart were set on moving\n"
	.string "to the melting pot of Unova.\l"
	.string "I wanted the best for him, so I\l"
	.string "gave him my blessing to leave the nest.\p"
	.string "To say I miss him every hour would be\n"
	.string "an understatement. He would write\l"
	.string "me occasionally, even send me\l"
	.string "some Pokémon that he'd found\l"
	.string "in his travels.\p"
	.string "I cherish them very much.\p"
	.string "One day, last year, I recieve another\n"
	.string "parchment. He is planning a visit!\p"
	.string "With this parcel came a very special\n"
	.string "and rare Pokémon, Zorua. I have met\l"
	.string "a few folks that claim it to be a myth!\p"
	.string "But... after that, all communication\n"
	.string "ceased from my son. I worry time in and\l"
	.string "time out what may have happened to him.\p"
	.string "...The Zorua he sent me... I feel awful,\n"
	.string "but I cannot look at it without\l"
	.string "pangs of wistfulness.\p"
	.string "It's like I can see my son's face...$"

ZotpyreInteriors_Text_IWantToSee3Mons:
	.string "I am on the lookout for a worthy,\n"
	.string "passionate Pokémon trainer like my boy\l"
	.string "to take this Zorua with them.\p"
	.string "Tell you what, kind one...\p"
	.string "If you can show me a select few\n"
	.string "Pokémon that my son used to write\l"
	.string "to me about, I will trust you with Zorua.\p"
	.string "Specifically, Dunsparce, Croagunk,\n"
	.string "and Bisharp. Those were his favorites.$"

ZotpyreInteriors_Text_WillWaitForWorthyTrainer:
	.string "...I see you haven't what I\n"
	.string "am looking for. Oh well...\l"
	.string "My search shall continue.$"

ZotpyreInteriors_Text_LifePhilosophy:
	.string "(You show the man your Pokédex.)\p"
	.string "That... that is all of them.\n"
	.string "Excellent, trainer.\p"
	.string "Now, before I entrust you with\n"
	.string "Zorua, I have one final question\l"
	.string "pertaining to... your worldview.\p"
	.string "Everyone on a lifelong journey has\n"
	.string "a philosophy they strive to uphold.\p"
	.string "Tell me. What do you think the purpose\n"
	.string "of our short time in this world is?\p"
	.string "In your eyes, is life simply a grand\n"
	.string "comedy? Or an inevitable tragedy?$"

ZotpyreInteriors_Text_ComedyHuh:
	.string "A comedy, huh...\p"
	.string "I can see that angle. If we only are\n"
	.string "alive for a fraction of time, we might\l"
	.string "as well smile till our last hour.$"

ZotpyreInteriors_Text_TragedyHuh:
	.string "A tragedy, huh...\p"
	.string "I can understand that. Oftentimes, life\n"
	.string "is purposelessly cruel. Unfair.\l"
	.string "It is what we do to cope with that\l"
	.string "that defines human expression, I feel.$"

ZotpyreInteriors_Text_Zorua:
	.string "Oh... I can sense Zorua getting\n"
	.string "impatient inside its ball.\p"
	.string "Please, cherish and take care of\n"
	.string "this Pokémon for me.$"

ZotpyreInteriors_Text_PlayerReceivedZorua:
	.string "{PLAYER} received a Zorua!$"

ZotpyreInteriors_Text_MySonMightBeOutThere:
	.string "I have not fully given up hope that\n"
	.string "my son is out there somewhere.\p"
	.string "Though, meeting and talking about it\n"
	.string "with you, kind one...\p"
	.string "It has put my mind more at ease.$"

ZotpyreInteriors_Text_SpiritBreak:
	.string "My spirit remains as solid\n"
	.string "as that of a Mismagius, in spite\l"
	.string "of the harshness of my life.\p"
	.string "I have my strong will to thank\n"
	.string "for that. Though not everyone has\l"
	.string "a will that can't be broken.\l"
	.string "In fact, in a battle, you should\l"
	.string "take advantage of those\l"
	.string "weak in spirit.\p"
	.string "Take this TM, and you may\n"
	.string "break them...$"

ZotpyreInteriors_Text_GaveSpiritBreak:
	.string "Stay determined, no matter what.\n"
	.string "The stronger mind always\l"
	.string "trumps the stronger body...$"
