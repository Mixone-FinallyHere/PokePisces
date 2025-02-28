LilycoveMuseumNew_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LilycoveMuseumNew_OnLoad
	.byte 0

LilycoveMuseumNew_OnLoad:
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
	goto_if_lt VAR_BALL_QUEST_STATE, 8, LilycoveMuseumNew_EventScript_PhillipeFirstHalfQuest
	goto_if_lt VAR_BALL_QUEST_STATE, 14, LilycoveMuseumNew_EventScript_PhillipeSecondHalfQuest
	goto_if_ge VAR_BALL_QUEST_STATE, 14, LilycoveMuseumNew_EventScript_PhillipeQuestComplete
	release
	end

LilycoveMuseumNew_EventScript_PhillipePreQuest::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipePreQuest, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeFirstHalfQuest::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeFirstHalfQuest, MSGBOX_AUTOCLOSE
	release
	end

LilycoveMuseumNew_EventScript_PhillipeSecondHalfQuest::
	speakername LilycoveMuseumNew_Text_NamePhillipe
	msgbox LilycoveMuseumNew_Text_PhillipeSecondHalfQuest, MSGBOX_AUTOCLOSE
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
	.string "who are you again$"

LilycoveMuseumNew_Text_PhillipeFirstHalfQuest:
	.string "go catch what i want$"

LilycoveMuseumNew_Text_PhillipeSecondHalfQuest:
	.string "getting close w paintings$"

LilycoveMuseumNew_Text_MyTravelsInKalos:
	.string "in kalos i found this$"

LilycoveMuseumNew_Text_PhillipeQuestPost:
	.string "un artiste supreme$"
