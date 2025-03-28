.set LOCALID_GABBY, 1
.set LOCALID_TY, 2

LilycoveMuseumNew_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LilycoveMuseumNew_OnLoad
	.byte 0

LilycoveMuseumNew_OnLoad:
	call_if_eq VAR_GABBY_AND_TY_STATE, 0, LilycoveMuseumNew_EventScript_RemoveInterviewers
	call_if_ge VAR_BALL_QUEST_STATE, 1, LilycoveMuseumNew_EventScript_PlacePainting1
	call_if_ge VAR_BALL_QUEST_STATE, 2, LilycoveMuseumNew_EventScript_PlacePainting2
	call_if_ge VAR_BALL_QUEST_STATE, 3, LilycoveMuseumNew_EventScript_PlacePainting3
	call_if_ge VAR_BALL_QUEST_STATE, 4, LilycoveMuseumNew_EventScript_PlacePainting4
	call_if_ge VAR_BALL_QUEST_STATE, 5, LilycoveMuseumNew_EventScript_PlacePainting5
	call_if_ge VAR_BALL_QUEST_STATE, 6, LilycoveMuseumNew_EventScript_PlacePainting6
	call_if_ge VAR_BALL_QUEST_STATE, 7, LilycoveMuseumNew_EventScript_PlacePainting7
	call_if_ge VAR_BALL_QUEST_STATE, 8, LilycoveMuseumNew_EventScript_PlacePainting8
	call_if_ge VAR_BALL_QUEST_STATE, 9, LilycoveMuseumNew_EventScript_PlacePainting9
	call_if_ge VAR_BALL_QUEST_STATE, 10, LilycoveMuseumNew_EventScript_PlacePainting10
	call_if_ge VAR_BALL_QUEST_STATE, 11, LilycoveMuseumNew_EventScript_PlacePainting11
	call_if_ge VAR_BALL_QUEST_STATE, 12, LilycoveMuseumNew_EventScript_PlacePainting12
	call_if_ge VAR_BALL_QUEST_STATE, 13, LilycoveMuseumNew_EventScript_PlacePainting13
	call_if_ge VAR_BALL_QUEST_STATE, 14, LilycoveMuseumNew_EventScript_PlacePainting14
	end

LilycoveMuseumNew_EventScript_RemoveInterviewers::
	removeobject LOCALID_GABBY
	removeobject LOCALID_TY
	setflag FLAG_TEMP_19
	return

LilycoveMuseumNew_EventScript_PlacePainting1::
	setmetatile 8, 10, METATILE_OldStoneBuildings_Painting1TopLeft, TRUE
	setmetatile 9, 10, METATILE_OldStoneBuildings_Painting1TopRight, TRUE
	setmetatile 8, 11, METATILE_OldStoneBuildings_Painting1BottomLeft, TRUE
	setmetatile 9, 11, METATILE_OldStoneBuildings_Painting1BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting2::
	setmetatile 17, 8, METATILE_OldStoneBuildings_Painting2TopLeft, TRUE
	setmetatile 18, 8, METATILE_OldStoneBuildings_Painting2TopRight, TRUE
	setmetatile 17, 9, METATILE_OldStoneBuildings_Painting2BottomLeft, TRUE
	setmetatile 18, 9, METATILE_OldStoneBuildings_Painting2BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting3::
	setmetatile 4, 0, METATILE_OldStoneBuildings_Painting3TopLeft, TRUE
	setmetatile 5, 0, METATILE_OldStoneBuildings_Painting3TopRight, TRUE
	setmetatile 4, 1, METATILE_OldStoneBuildings_Painting3BottomLeft, TRUE
	setmetatile 5, 1, METATILE_OldStoneBuildings_Painting3BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting4::
	setmetatile 4, 5, METATILE_OldStoneBuildings_Painting4TopLeft, TRUE
	setmetatile 5, 5, METATILE_OldStoneBuildings_Painting4TopRight, TRUE
	setmetatile 4, 6, METATILE_OldStoneBuildings_Painting4BottomLeft, TRUE
	setmetatile 5, 6, METATILE_OldStoneBuildings_Painting4BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting5::
	setmetatile 21, 8, METATILE_OldStoneBuildings_Painting5TopLeft, TRUE
	setmetatile 22, 8, METATILE_OldStoneBuildings_Painting5TopRight, TRUE
	setmetatile 21, 9, METATILE_OldStoneBuildings_Painting5BottomLeft, TRUE
	setmetatile 22, 9, METATILE_OldStoneBuildings_Painting5BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting6::
	setmetatile 17, 3, METATILE_OldStoneBuildings_Painting6TopLeft, TRUE
	setmetatile 18, 3, METATILE_OldStoneBuildings_Painting6TopRight, TRUE
	setmetatile 17, 4, METATILE_OldStoneBuildings_Painting6BottomLeft, TRUE
	setmetatile 18, 4, METATILE_OldStoneBuildings_Painting6BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting7::
	setmetatile 10, 0, METATILE_OldStoneBuildings_Painting7TopLeft, TRUE
	setmetatile 11, 0, METATILE_OldStoneBuildings_Painting7TopRight, TRUE
	setmetatile 10, 1, METATILE_OldStoneBuildings_Painting7BottomLeft, TRUE
	setmetatile 11, 1, METATILE_OldStoneBuildings_Painting7BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting8::
	setmetatile 0, 5, METATILE_OldStoneBuildings_Painting8TopLeft, TRUE
	setmetatile 1, 5, METATILE_OldStoneBuildings_Painting8TopRight, TRUE
	setmetatile 0, 6, METATILE_OldStoneBuildings_Painting8BottomLeft, TRUE
	setmetatile 1, 6, METATILE_OldStoneBuildings_Painting8BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting9::
	setmetatile 4, 10, METATILE_OldStoneBuildings_Painting9TopLeft, TRUE
	setmetatile 5, 10, METATILE_OldStoneBuildings_Painting9TopRight, TRUE
	setmetatile 4, 11, METATILE_OldStoneBuildings_Painting9BottomLeft, TRUE
	setmetatile 5, 11, METATILE_OldStoneBuildings_Painting9BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting10::
	setmetatile 1, 0, METATILE_OldStoneBuildings_Painting10TopLeft, TRUE
	setmetatile 2, 0, METATILE_OldStoneBuildings_Painting10TopRight, TRUE
	setmetatile 1, 1, METATILE_OldStoneBuildings_Painting10BottomLeft, TRUE
	setmetatile 2, 1, METATILE_OldStoneBuildings_Painting10BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting11::
	setmetatile 21, 3, METATILE_OldStoneBuildings_Painting11TopLeft, TRUE
	setmetatile 22, 3, METATILE_OldStoneBuildings_Painting11TopRight, TRUE
	setmetatile 21, 4, METATILE_OldStoneBuildings_Painting11BottomLeft, TRUE
	setmetatile 22, 4, METATILE_OldStoneBuildings_Painting11BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting12::
	setmetatile 8, 5, METATILE_OldStoneBuildings_Painting12TopLeft, TRUE
	setmetatile 9, 5, METATILE_OldStoneBuildings_Painting12TopRight, TRUE
	setmetatile 8, 6, METATILE_OldStoneBuildings_Painting12BottomLeft, TRUE
	setmetatile 9, 6, METATILE_OldStoneBuildings_Painting12BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting13::
	setmetatile 7, 0, METATILE_OldStoneBuildings_Painting13TopLeft, TRUE
	setmetatile 8, 0, METATILE_OldStoneBuildings_Painting13TopRight, TRUE
	setmetatile 7, 1, METATILE_OldStoneBuildings_Painting13BottomLeft, TRUE
	setmetatile 8, 1, METATILE_OldStoneBuildings_Painting13BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PlacePainting14::
	setmetatile 0, 10, METATILE_OldStoneBuildings_Painting14TopLeft, TRUE
	setmetatile 1, 10, METATILE_OldStoneBuildings_Painting14TopRight, TRUE
	setmetatile 0, 11, METATILE_OldStoneBuildings_Painting14BottomLeft, TRUE
	setmetatile 1, 11, METATILE_OldStoneBuildings_Painting14BottomRight, TRUE
	special DrawWholeMapView
	return

LilycoveMuseumNew_EventScript_PaintingDesc1::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 1, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc1, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc2::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 2, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc2, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc3::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 3, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc3, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc4::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 4, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc4, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc5::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 5, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc5, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc6::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 6, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc6, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc7::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 7, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc7, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc8::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 8, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc8, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc9::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 9, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc9, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc10::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 10, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc10, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc11::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 11, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc11, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc12::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 12, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc12, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc13::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 13, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc13, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingDesc14::
	lock
	goto_if_lt VAR_BALL_QUEST_STATE, 14, LilycoveMuseumNew_EventScript_PaintingEmpty
	msgbox LilycoveMuseumNew_Text_PaintingDesc14, MSGBOX_DEFAULT
	closemessage
	call_if_set FLAG_WILL_JUDGE_PAINTING, LilycoveMuseumNew_EventScript_PaintingJudged
	release
	end

LilycoveMuseumNew_EventScript_PaintingJudged::
	setflag FLAG_JUDGED_PAINTING
	clearflag FLAG_WILL_JUDGE_PAINTING
	msgbox LilycoveMuseumNew_Text_PaintingJudged, MSGBOX_DEFAULT
	closemessage
	return

LilycoveMuseumNew_EventScript_PaintingEmpty::
	msgbox LilycoveMuseumNew_Text_PaintingEmpty, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_Phillipe::
	lock
	faceplayer
	goto_if_lt VAR_BALL_QUEST_STATE, 1, LilycoveMuseumNew_EventScript_PhillipePreQuest
	goto_if_eq VAR_BALL_QUEST_STATE, 1, LilycoveMuseumNew_EventScript_PhillipeInCosmoss
	goto_if_eq VAR_BALL_QUEST_STATE, 2, LilycoveMuseumNew_EventScript_PhillipeInSunbeach
	goto_if_eq VAR_BALL_QUEST_STATE, 3, LilycoveMuseumNew_EventScript_PhillipeInBrumist
	goto_if_eq VAR_BALL_QUEST_STATE, 4, LilycoveMuseumNew_EventScript_PhillipeInScuttill
	goto_if_eq VAR_BALL_QUEST_STATE, 5, LilycoveMuseumNew_EventScript_PhillipeInPerplume
	goto_if_eq VAR_BALL_QUEST_STATE, 6, LilycoveMuseumNew_EventScript_PhillipeInAshlands
	goto_if_eq VAR_BALL_QUEST_STATE, 7, LilycoveMuseumNew_EventScript_PhillipeInCrimney
	goto_if_eq VAR_BALL_QUEST_STATE, 8, LilycoveMuseumNew_EventScript_PhillipeInJaggro
	goto_if_eq VAR_BALL_QUEST_STATE, 9, LilycoveMuseumNew_EventScript_PhillipeInSweltorn
	goto_if_eq VAR_BALL_QUEST_STATE, 10, LilycoveMuseumNew_EventScript_PhillipeInCyclingRoad
	goto_if_eq VAR_BALL_QUEST_STATE, 11, LilycoveMuseumNew_EventScript_PhillipeInStrae
	goto_if_eq VAR_BALL_QUEST_STATE, 12, LilycoveMuseumNew_EventScript_PhillipeInGranipline
	goto_if_eq VAR_BALL_QUEST_STATE, 13, LilycoveMuseumNew_EventScript_PhillipeInLittleroot
	goto_if_ge VAR_BALL_QUEST_STATE, 14, LilycoveMuseumNew_EventScript_PhillipeQuestComplete
	release
	end

LilycoveMuseumNew_EventScript_PhillipePreQuest::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipePreQuest, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInCosmoss::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInCosmoss, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInSunbeach::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInSunbeach, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInBrumist::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInBrumist, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInScuttill::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInScuttill, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInPerplume::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInPerplume, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInAshlands::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInAshlands, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInCrimney::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInCrimney, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInJaggro::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInJaggro, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInSweltorn::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInSweltorn, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInCyclingRoad::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInCyclingRoad, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInStrae::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInStrae, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInGranipline::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInGranipline, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeInLittleroot::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeInLittleroot, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeQuestComplete::
	checkitem ITEM_OBJECT_D_ARC
	goto_if_eq VAR_RESULT, TRUE, LilycoveMuseumNew_EventScript_PhillipeQuestPost
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_MyTravelsInKalos, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_OBJECT_D_ARC
	closemessage
	release
	end

LilycoveMuseumNew_EventScript_PhillipeQuestPost::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeQuestPost, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_JumpIntoPainting::
	lock
	goto_if_lt VAR_ORBS_QUEST_STATE, 6, LilycoveMuseumNew_EventScript_PaintingOfMuseum
	goto_if_gt VAR_ORBS_QUEST_STATE, 6, LilycoveMuseumNew_EventScript_PaintingOfMuseum
	msgbox LilycoveMuseumNew_Text_JumpIntoPainting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LilycoveMuseumNew_EventScript_WarpToSanctum
	msgbox LilycoveMuseumNew_Text_SillyThought, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PaintingOfMuseum::
	msgbox LilycoveMuseumNew_Text_PaintingOfMuseum, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_WarpToSanctum::
	delay 4
	playse SE_BIKE_HOP
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveMuseumNew_Movement_JumpIntoPainting
	waitmovement 0
	warp MAP_MUSEUM_SANCTUM, 1, 10
	waitstate
	release
	end

LilycoveMuseumNew_Movement_JumpIntoPainting:
	jump_up
	step_end

LilycoveMuseumNew_EventScript_UpstairsGuard::
	msgbox LilycoveMuseumNew_Text_UpstairsGuard, MSGBOX_NPC
	end

LilycoveMuseumNew_Text_UpstairsGuard:
	.string "The second floor is off limits!\n"
	.string "We're currently workshopping a\l"
	.string "new dinosaur exhibit.\l"
	.string "No peeking!$"

LilycoveMuseumNew_Text_PaintingOfMuseum:
	.string "(It's a painting of a museum,\n"
	.string "much like the one you\l"
	.string "are currently standing in.)$"

LilycoveMuseumNew_Text_JumpIntoPainting:
	.string "(...)\p"
	.string "(Something compells you to jump\n"
	.string "into the painting. Is that\l"
	.string "where the map wants you to go...?)$"

LilycoveMuseumNew_Text_SillyThought:
	.string "(A silly thought, yeah.)$"

LilycoveMuseumNew_Text_PaintingDesc1:
	.string "(It's a landscape depicting\n"
	.string "a stark white, almost angelic\l"
	.string "palace built into a cave.)$"

LilycoveMuseumNew_Text_PaintingDesc2:
	.string "(It's a landscape depicting\n"
	.string "a sunken pirate ship\l"
	.string "nestled in a dank cavern.)$"

LilycoveMuseumNew_Text_PaintingDesc3:
	.string "(It's a landscape depicting\n"
	.string "the sunset view at a haunted\l"
	.string "resort's beach.)$"

LilycoveMuseumNew_Text_PaintingDesc4:
	.string "(It's a landscape depicting\n"
	.string "the icy mountain ranges extending\l"
	.string "outwards from atop a castle.)$"

LilycoveMuseumNew_Text_PaintingDesc5:
	.string "(It's a landscape depicting\n"
	.string "a dense jungle, hiding danger\l"
	.string "and secrets just underneath.)$"

LilycoveMuseumNew_Text_PaintingDesc6:
	.string "(It's a landscape depicting\n"
	.string "a sleepy town's hilltop overlook,\l"
	.string "sun setting in the distance.)$"

LilycoveMuseumNew_Text_PaintingDesc7:
	.string "(It's a landscape depicting\n"
	.string "an oddball city in the desert\l"
	.string "where radiation has taken over.)$"

LilycoveMuseumNew_Text_PaintingDesc8:
	.string "(It's a landscape depicting\n"
	.string "the front courtyard of a manor.\l"
	.string "A brown dog is sitting out front.)$"

LilycoveMuseumNew_Text_PaintingDesc9:
	.string "(It's a landscape depicting\n"
	.string "the luminous peak of a volcano.\l"
	.string "A dragon is perched atop it.)$"

LilycoveMuseumNew_Text_PaintingDesc10:
	.string "(It's a landscape depicting\n"
	.string "the glowing, moth-attracting\l"
	.string "lightbulbs of a hidden storeroom.)$"

LilycoveMuseumNew_Text_PaintingDesc11:
	.string "(It's a landscape depicting\n"
	.string "an alien planet with lizard\l"
	.string "and insect nests.)$"

LilycoveMuseumNew_Text_PaintingDesc12:
	.string "(It's a landscape depicting\n"
	.string "a wild and wistful autumn wood\l"
	.string "with bamboo reed structures.)$"

LilycoveMuseumNew_Text_PaintingDesc13:
	.string "(It's a landscape depicting\n"
	.string "a spherical planetoid made of\l"
	.string "water overlooking a starry sky.)$"

LilycoveMuseumNew_Text_PaintingDesc14:
	.string "(It's a landscape depicting\n"
	.string "a glittering, golden land.)$"

LilycoveMuseumNew_Text_PaintingJudged:
	.string "...\p"
	.string "(You've jotted down a critique\n"
	.string "to hand to the art teacher.)$"

LilycoveMuseumNew_Text_PaintingEmpty:
	.string "(This painting frame\n"
	.string "is currently empty.)$"

LilycoveMuseumNew_Text_NamePhillipe:
	.string "Phillipe$"

LilycoveMuseumNew_Text_PhillipePreQuest:
	.string "Mmm? Mon étrangére, I do not\n"
	.string "recognize you. My deepest thanks\l"
	.string "for coming to mon exposition!\l"
	.string "As of this moment, I have not\l"
	.string "put up any paintings yet...\l"
	.string "But n'aie pas peur! I am\l"
	.string "gathering inspiration as we speak.\p"
	.string "If you would like to help me\n"
	.string "kindle my artistic mind, come to\l"
	.string "the Basalin Coast Pokemon Center.\l"
	.string "Until then, étrangére...\l"
	.string "I bid you adieu!$"

LilycoveMuseumNew_Text_PhillipeInCosmoss:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Cosmoss Bridge.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInSunbeach:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Sunbeach Strait.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInBrumist:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Brumist Cliffs.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInScuttill:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Scuttill Way.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInPerplume:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Perplume Maze.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInAshlands:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in The Ashlands.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInCrimney:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Crimney Climb.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInJaggro:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Jaggro Pass.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInSweltorn:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Sweltorn Desert.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInCyclingRoad:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Cycling Road.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInStrae:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Strae Seapath.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInGranipline:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Granipline Beach.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_PhillipeInLittleroot:
	.string "Amie! It is good to see you\n"
	.string "here at mon exposition!\p"
	.string "I have been putting up paintings\n"
	.string "slowly, but surely.\p"
	.string "Honh-honh! I see un sparkle in\n"
	.string "your eye, amie! You wish to help\l"
	.string "me paint more!\p"
	.string "If that is the case, we shall\n"
	.string "rendezvous at the Pokemon Center\l"
	.string "in Littleroot Town.\p"
	.string "Until then, au revoir!$"

LilycoveMuseumNew_Text_MyTravelsInKalos:
	.string "Ah, mon meilleur ami.\n"
	.string "Because of your help, I have\l"
	.string "filled the entire museum!\l"
	.string "I cannot thank you enough!\p"
	.string "...Will you allow me to\n"
	.string "open up to you a little?\l"
	.string "I feel we have gotten close.\p"
	.string "As you may know, I hail from\n"
	.string "Kalos. Though, that is only\l"
	.string "partially true. The truth is,\l"
	.string "my dialect has been me faking\l"
	.string "it for some time now. What can\l"
	.string "I say? Patrons love it!\l"
	.string "Art reaches more eyes if\l"
	.string "its creator seems foreign.\p"
	.string "I was originally born here\n"
	.string "in Hoenn, but moved to Kalos\l"
	.string "at 18. There, I became a\l"
	.string "professional photographer.\l"
	.string "I earned the name, Phil the\l"
	.string "Photo Guy!\p"
	.string "Naturally this led to an interest\n"
	.string "in making my own landscapes.\l"
	.string "So, I packed my bags, came back\l"
	.string "to my homeland, and got to work.\p"
	.string "I'm very proud to call this\n"
	.string "exhibit complete!\p"
	.string "To show my appreciation, you can\n"
	.string "have this item I picked up during\l"
	.string "my time in Kalos. It is\l"
	.string "quite the fascinating statue.$"

LilycoveMuseumNew_Text_PhillipeQuestPost:
	.string "Tu es un artiste supreme!\n"
	.string "Well, by association.\l"
	.string "Enjoy the paintings!$"
