.set LOCALID_BARD, 1
.set LOCALID_P_MAN, 4

SlateportCity_SternsShipyard_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SlateportCity_SternsShipyard_1F_OnLoad
	.byte 0

SlateportCity_SternsShipyard_1F_OnLoad:
	call_if_lt VAR_OLD_GUYS_STATE, 9, SlateportCity_SternsShipyard_1F_EventScript_SetBardGfx
	call SlateportCity_SternsShipyard_1F_EventScript_RemoveKizuna
	call_if_ge VAR_OLD_GUYS_STATE, 9, SlateportCity_SternsShipyard_1F_EventScript_RemoveDock
	end

SlateportCity_SternsShipyard_1F_EventScript_SetBardGfx::
	setvar VAR_BARD_COLOR, MAUVILLE_MAN_BARD
	special SetMauvilleOldManObjEventGfx
	return

SlateportCity_SternsShipyard_1F_EventScript_RemoveKizuna::
	removeobject LOCALID_P_MAN
	setflag FLAG_TEMP_11
	return

SlateportCity_SternsShipyard_1F_EventScript_RemoveDock::
	removeobject LOCALID_BARD
	setflag FLAG_TEMP_12
	return	

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lock
	faceplayer
	goto_if_set FLAG_DOCK_QUEST_FOUND_STERN, SlateportCity_SternsShipyard_1F_EventScript_DockCheckDrake
	goto_if_lt VAR_OLD_GUYS_STATE, 7, SlateportCity_SternsShipyard_1F_EventScript_DockPreRydel
	goto_if_eq VAR_OLD_GUYS_STATE, 8, SlateportCity_SternsShipyard_1F_EventScript_DockDuringMission
	msgbox SlateportCity_SternsShipyard_1F_Text_IAmTheBard, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	clearflag FLAG_TEMP_11
	addobject LOCALID_P_MAN
	applymovement LOCALID_P_MAN, SlateportCity_SternsShipyard_1F_Movement_KizunaEnters
	waitmovement 0
	speakername SlateportCity_SternsShipyard_1F_Text_NameKizuna
	msgbox SlateportCity_SternsShipyard_1F_Text_YoureOurNextGuy, MSGBOX_DEFAULT
	speakername SlateportCity_SternsShipyard_1F_Text_NameDock
	msgbox SlateportCity_SternsShipyard_1F_Text_BeforeIRetire, MSGBOX_DEFAULT
	speakername SlateportCity_SternsShipyard_1F_Text_NameKizuna
	msgbox SlateportCity_SternsShipyard_1F_Text_WeCanDoThat, MSGBOX_DEFAULT
	setvar VAR_OLD_GUYS_STATE, 8
	closemessage
	release
	end

SlateportCity_SternsShipyard_1F_Movement_KizunaEnters:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SlateportCity_SternsShipyard_1F_EventScript_DockCheckDrake::
	goto_if_set FLAG_DOCK_QUEST_FOUND_DRAKE, SlateportCity_SternsShipyard_1F_EventScript_DockCheckArchie
	speakername SlateportCity_SternsShipyard_1F_Text_NameDock
	msgbox SlateportCity_SternsShipyard_1F_Text_DockDuringMission, MSGBOX_AUTOCLOSE
	release
	end	

SlateportCity_SternsShipyard_1F_EventScript_DockCheckArchie::
	goto_if_set FLAG_DOCK_QUEST_FOUND_ARCHIE, SlateportCity_SternsShipyard_1F_EventScript_DockFoundAll
	speakername SlateportCity_SternsShipyard_1F_Text_NameDock
	msgbox SlateportCity_SternsShipyard_1F_Text_DockDuringMission, MSGBOX_AUTOCLOSE
	release
	end	

SlateportCity_SternsShipyard_1F_EventScript_DockFoundAll::
	speakername SlateportCity_SternsShipyard_1F_Text_NameDock
	msgbox SlateportCity_SternsShipyard_1F_Text_TheyreAllReady, MSGBOX_DEFAULT
	setvar VAR_OLD_GUYS_STATE, 9
	warp MAP_SEA_MAUVILLE, 41, 54
	closemessage
	release
	end

SlateportCity_SternsShipyard_1F_EventScript_DockPreRydel::
	msgbox SlateportCity_SternsShipyard_1F_Text_DockPreRydel, MSGBOX_AUTOCLOSE
	release
	end	

SlateportCity_SternsShipyard_1F_EventScript_DockDuringMission::
	speakername SlateportCity_SternsShipyard_1F_Text_NameDock
	msgbox SlateportCity_SternsShipyard_1F_Text_DockDuringMission, MSGBOX_AUTOCLOSE
	release
	end	

SlateportCity_SternsShipyard_1F_EventScript_KizunaIdle::
	msgbox SlateportCity_SternsShipyard_1F_Text_KizunaIdle, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_NameKizuna:
	.string "Kizuna$"

SlateportCity_SternsShipyard_1F_Text_NameDock:
	.string "Dock$"

SlateportCity_SternsShipyard_1F_Text_DockPreRydel:
	.string "(He's working on some sort of\n"
	.string "boat motor on the table.)\p"
	.string "...Oh, dag-nabbit. Still no good\n"
	.string "with these new-fangled parts...$"

SlateportCity_SternsShipyard_1F_Text_IAmTheBard:
	.string "...\p"
	.string "...Ah, what's that? You are...\p"
	.string "...{PLAYER}? And, err... Rydel\n"
	.string "sent you to me? Well, that is\l"
	.string "a surprise, to be sure.$"

SlateportCity_SternsShipyard_1F_Text_YoureOurNextGuy:
	.string "Hello, Mr. Dock. Sorry to take\n"
	.string "time away from what you're doing.\l"
	.string "But, we really need to talk.\p"
	.string "Your old friend Rydel sent us here.\n"
	.string "To make a long story short, we've\l"
	.string "had run-ins with him and Giddy,\l"
	.string "trying to locate The Storyteller.\l"
	.string "Yes, we know that all of you\l"
	.string "are in a group together called\l"
	.string "the Old Guys. ...So, do you\l"
	.string "have any information to offer?$"

SlateportCity_SternsShipyard_1F_Text_BeforeIRetire:
	.string "I see. Sorry to dissapoint, but\n"
	.string "I'm an awfully busy man these days.\l"
	.string "Back when I was known as The Bard,\l"
	.string "I was a lot more of a free spirit.\l"
	.string "But that doesn't pay the bills.\p"
	.string "...Err, well, I suppose that I'm\n"
	.string "not going to be busy for much longer.\l"
	.string "My retirement party is today.\l"
	.string "I've invited a few of my old\l"
	.string "sea dog colleagues, but their minds\l"
	.string "must be going, as usual.\l"
	.string "Only Ol' Briney showed up!\p"
	.string "Listen, if you can do me a favor here,\n"
	.string "I might do you one back.\l"
	.string "All you need to do is fetch my\l"
	.string "senile colleagues.\l"
	.string "Stern, Archie, and Drake.\l"
	.string "Without them, I won't be holding\l"
	.string "my small party.$"

SlateportCity_SternsShipyard_1F_Text_WeCanDoThat:
	.string "R-Retirement, huh...\p"
	.string "...Ahem, anyways, yes, I think\n"
	.string "we can do that. {PLAYER},\l"
	.string "the closest one I know of to\l"
	.string "here is probably Cpt. Stern.\l"
	.string "He should be in the Oceanic Museum\l"
	.string "in the same city we're in right now.\p"
	.string "Let's get going.$"

SlateportCity_SternsShipyard_1F_Text_KizunaIdle:
	.string "Alright {PLAYER},\n"
	.string "the closest one I know of to\l"
	.string "here is probably Cpt. Stern.\l"
	.string "He should be in the Oceanic Museum\l"
	.string "in the same city we're in right now.\p"
	.string "Let's get going.$"

SlateportCity_SternsShipyard_1F_Text_DockDuringMission:
	.string "My colleagues still have yet to\n"
	.string "all arrive. Stern, Archie, Drake...\l"
	.string "dimentia's already setting in!$"

SlateportCity_SternsShipyard_1F_Text_TheyreAllReady:
	.string "Thank you for gathering my\n"
	.string "colleagues. They've all\l"
	.string "just arrived. Since you've been\l"
	.string "so helpful, why don't you\l"
	.string "come along with us? It will\l"
	.string "be a fun voyage.$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
	.string "MR. BRINEY: Ah, {PLAYER}{KUN}!\n"
	.string "It's been too long!\p"
	.string "Aye, since I met you, this old sea dog's\n"
	.string "been feeling frisky!\p"
	.string "So I've decided to help DOCK make\n"
	.string "a ferry.\p"
	.string "Aye, after all, a ferry would be able\n"
	.string "to carry a lot of people.\p"
	.string "But, you know, that DOCK is really\n"
	.string "something special.\p"
	.string "With his knack for technology and\n"
	.string "my experience, I'm sure that we can\l"
	.string "build one great ship, aye!$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
	.string "The seasons, the weather, where\n"
	.string "the moon sits in the sky…\p"
	.string "These and other conditions make\n"
	.string "the sea change its expression.\p"
	.string "That's right!\n"
	.string "The sea is like a living thing!$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
	.string "I get seasick real easily.\n"
	.string "So I get to help out here instead.$"

