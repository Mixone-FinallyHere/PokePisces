AshlandsHouse_MapScripts::
	.byte 0

AshlandsHouse_EventScript_SpindaLover::
	lock
	faceplayer
	goto_if_set FLAG_CAUGHT_ALL_SPINDA, AshlandsHouse_EventScript_GavePlainsSpinda
	msgbox AshlandsHouse_Text_ILoveSpinda, MSGBOX_DEFAULT
	specialvar VAR_RESULT, CheckSpindaAsh
	goto_if_eq VAR_RESULT, TRUE, AshlandsHouse_EventScript_CheckMountain
	msgbox AshlandsHouse_Text_NotEnoughSpinda, MSGBOX_DEFAULT
	closemessage
	release
	end

AshlandsHouse_EventScript_GavePlainsSpinda::
	msgbox AshlandsHouse_Text_GavePlainsSpinda, MSGBOX_DEFAULT
	closemessage
	release
	end

AshlandsHouse_EventScript_CheckMountain::
	specialvar VAR_RESULT, CheckSpindaMountain
	goto_if_eq VAR_RESULT, TRUE, AshlandsHouse_EventScript_CheckCave
	msgbox AshlandsHouse_Text_NotEnoughSpinda, MSGBOX_DEFAULT
	closemessage
	release
	end

AshlandsHouse_EventScript_CheckCave::
	specialvar VAR_RESULT, CheckSpindaCave
	goto_if_eq VAR_RESULT, TRUE, AshlandsHouse_EventScript_CheckForest
	msgbox AshlandsHouse_Text_NotEnoughSpinda, MSGBOX_DEFAULT
	closemessage
	release
	end

AshlandsHouse_EventScript_CheckForest::
	specialvar VAR_RESULT, CheckSpindaForest
	goto_if_eq VAR_RESULT, TRUE, AshlandsHouse_EventScript_CheckDesert
	msgbox AshlandsHouse_Text_NotEnoughSpinda, MSGBOX_DEFAULT
	closemessage
	release
	end

AshlandsHouse_EventScript_CheckDesert::
	specialvar VAR_RESULT, CheckSpindaDesert
	goto_if_eq VAR_RESULT, TRUE, AshlandsHouse_EventScript_ReceivePlainsSpinda
	msgbox AshlandsHouse_Text_NotEnoughSpinda, MSGBOX_DEFAULT
	closemessage
	release
	end

AshlandsHouse_EventScript_ReceivePlainsSpinda::
	msgbox AshlandsHouse_Text_HaveThisPlainsSpinda, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SPINDA_PLAINS
	givemon SPECIES_SPINDA_PLAINS, 40
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, AshlandsHouse_EventScript_ReceivePlainsSpindaParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, AshlandsHouse_EventScript_ReceivePlainsSpindaPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

AshlandsHouse_EventScript_ReceivePlainsSpindaParty::
	call AshlandsHouse_EventScript_ReceivedPlainsSpindaFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AshlandsHouse_EventScript_ExplainPlainsSpinda
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto AshlandsHouse_EventScript_ExplainPlainsSpinda
	end

AshlandsHouse_EventScript_ReceivePlainsSpindaPC::
	call AshlandsHouse_EventScript_ReceivedPlainsSpindaFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AshlandsHouse_EventScript_SendPlainsSpindaToPC
	call Common_EventScript_NameReceivedBoxMon
	goto AshlandsHouse_EventScript_SendPlainsSpindaToPC
	end

AshlandsHouse_EventScript_SendPlainsSpindaToPC::
	call Common_EventScript_TransferredToPC
	goto AshlandsHouse_EventScript_ExplainPlainsSpinda
	end

AshlandsHouse_EventScript_ReceivedPlainsSpindaFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message AshlandsHouse_Text_PlayerReceivedPlainsSpinda
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_SPINDA
	return

AshlandsHouse_EventScript_ExplainPlainsSpinda::
	msgbox AshlandsHouse_Text_RareSpinda, MSGBOX_DEFAULT
	setflag FLAG_CAUGHT_ALL_SPINDA
	closemessage
	release
	end

AshlandsHouse_Text_ILoveSpinda:
	.string "(This woman's head is\n"
	.string "spinning as if she's in a daze.)\p"
	.string "U... hhey! Are you a...\n"
	.string "Spinda fanatic...? I sure am...!\p"
	.string "My eyes are filled with... visions...\n"
	.string "of swirls and twirls...!\p"
	.string "Did... did you know... that\n"
	.string "the Spinda here in the Ash...\l"
	.string "Lands... are not the only\l"
	.string "variant of Spinda...\p"
	.string "There exists rare... uu...\n"
	.string "variants of Spinda... that\l"
	.string "tend to hide... in small groups...\p"
	.string "Forest... Mountain... Cave...\n"
	.string "Ashlands... Desert...\l"
	.string "Bring all the kinds to me...\l"
	.string "We can... dance together!$"

AshlandsHouse_Text_NotEnoughSpinda:
	.string "I've checked your party...\n"
	.string "not... enough... spinning...$"

AshlandsHouse_Text_HaveThisPlainsSpinda:
	.string "Uuuwawawa....!!!\n"
	.string "All of them...!\l"
	.string "You caught... all of them!\p"
	.string "Uuhuu... so lovely...\n"
	.string "so cute and clumsy...\p"
	.string "H-Here... uuu... have the last\n"
	.string "kind of Spinda... complete\l"
	.string "the family...!$"

AshlandsHouse_Text_PlayerReceivedPlainsSpinda:
	.string "{PLAYER} recieved a Plains Spinda!$"

AshlandsHouse_Text_RareSpinda:
	.string "Uu...huu...\n"
	.string "That Spinda... it is my good friend.\p"
	.string "It belongs with its family...\n"
	.string "take... good care of Spinda...$"

AshlandsHouse_Text_GavePlainsSpinda:
	.string "My dizziness is fading away...\n"
	.string "This is probably a good thing,\l"
	.string "but... I miss spinning with Spinda...$"
