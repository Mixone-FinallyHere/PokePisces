EverGrandeRestArea_MapScripts::
	.byte 0

EverGrandeRestArea_EventScript_Archie::
	lock
	faceplayer
	speakername EverGrandeRestArea_Text_NameArchie
	msgbox EverGrandeRestArea_Text_WantToRest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EverGrandeRestArea_EventScript_HealPkmn
	message EverGrandeRestArea_Text_GoodLuck
	closemessage
	release
	end

EverGrandeRestArea_EventScript_HealPkmn::
	special HealPlayerParty
	speakername EverGrandeRestArea_Text_NameArchie
	msgbox EverGrandeRestArea_Text_IveRestoredThem, MSGBOX_DEFAULT
	closemessage
	speakername EverGrandeRestArea_Text_NameArchie
	message EverGrandeRestArea_Text_GoodLuck
	waitmessage
	waitbuttonpress
	closemessage
	release
	end

EverGrandeRestArea_EventScript_Maxie::
	lock
	faceplayer
	speakername EverGrandeRestArea_Text_NameMaxie
	msgbox EverGrandeRestArea_Text_WantToAccessPC, MSGBOX_YESNO
	speakername NULL
	goto_if_eq VAR_RESULT, YES, EventScript_PC
	speakername EverGrandeRestArea_Text_NameMaxie
	msgbox EverGrandeRestArea_Text_NoPCThen, MSGBOX_AUTOCLOSE
	release
	end

EverGrandeRestArea_EventScript_EGRSign::
    msgbox EverGrandeRestArea_Text_EGRSign, MSGBOX_SIGN
    end

EverGrandeRestArea_Text_EGRSign:
	.string "EVER GRANDE ROAD IS AHEAD$"

EverGrandeRestArea_Text_NameMaxie:
	.string "Maxie$"

EverGrandeRestArea_Text_NameArchie:
	.string "Archie$"

EverGrandeRestArea_Text_WantToRest:
	.string "Want to rest your Pokemon\n"
	.string "for a bit, {PLAYER}?$"

EverGrandeRestArea_Text_IveRestoredThem:
	.string "There ya are! Back to full health!$"

EverGrandeRestArea_Text_GoodLuck:
	.string "Good luck in the Road, short stuff!$"

EverGrandeRestArea_Text_WantToAccessPC:
	.string "Do you wish to access your PC?\n"
	.string "I have a portable one with me.$"

EverGrandeRestArea_Text_NoPCThen:
	.string "Alright then. Come to me\n"
	.string "if you desire PC assistance.$"
