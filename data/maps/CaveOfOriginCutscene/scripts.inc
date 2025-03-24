CaveOfOriginCutscene_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveOfOriginCutscene_OnFrame
	.byte 0

CaveOfOriginCutscene_OnFrame:
	map_script_2 VAR_NEW_COO_STATE, 6, CaveOfOriginCutscene_EventScript_FishMissing
	.2byte 0

CaveOfOriginCutscene_EventScript_FishMissing::
	lock
	speakername CaveOfOriginCutscene_Text_NameWallace
	msgbox CaveOfOriginCutscene_Text_WereTooLate, MSGBOX_DEFAULT
	speakername CaveOfOriginCutscene_Text_NameMaxie
	msgbox CaveOfOriginCutscene_Text_WhatCanWeDoNow, MSGBOX_DEFAULT
	speakername CaveOfOriginCutscene_Text_NameWallace
	msgbox CaveOfOriginCutscene_Text_TrackThemDown, MSGBOX_DEFAULT
	speakername CaveOfOriginCutscene_Text_NameArchie
	msgbox CaveOfOriginCutscene_Text_HighestAndLowest, MSGBOX_DEFAULT
	speakername CaveOfOriginCutscene_Text_NameWallace
	msgbox CaveOfOriginCutscene_Text_YouMayComePlayer, MSGBOX_DEFAULT
	warp MAP_NEW_SOOTO, 31, 31
	waitstate
	release
	end

CaveOfOriginCutscene_Text_NameWallace:
	.string "Wallace$"

CaveOfOriginCutscene_Text_NameMaxie:
	.string "Maxie$"

CaveOfOriginCutscene_Text_NameArchie:
	.string "Archie$"

CaveOfOriginCutscene_Text_WereTooLate:
	.string "Y-Yes, as you can see...\n"
	.string "the lake no longer runs red...\p"
	.string "It appears as though Groudon\n"
	.string "and Kyogre's fighting disturbed\l"
	.string "the fish of the lake,\l"
	.string "Luo-Shan and Sha-Yon, causing them\l"
	.string "to depart for parts unknown...\p"
	.string "If the two fish are not returned\n"
	.string "soon, untold calamity could\l"
	.string "potentially befall Hoenn.$"

CaveOfOriginCutscene_Text_WhatCanWeDoNow:
	.string "Well, let us not roll over and die.\n"
	.string "We will puzzle a way out of\l"
	.string "this predicament.\p"
	.string "In your opinion, Deacon Wallace,\n"
	.string "what should be the best\l"
	.string "course of action?$"

CaveOfOriginCutscene_Text_TrackThemDown:
	.string "We must track them down.\n"
	.string "Given that the tumultuous\l"
	.string "weather has subsided, it is\l"
	.string "unlikely that Groudon and Kyogre\l"
	.string "are battling it out elsewhere.\p"
	.string "Which... could mean that they have\n"
	.string "each fled to somewhere with\l"
	.string "Luo-Shan and Sha-Yon.\p"
	.string "Luo-Shan is the deity of Falling.\n"
	.string "It will naturally seek out the\l"
	.string "lowest point in Hoenn...\l"
	.string "most likely Etheor Nadir, the\l"
	.string "undersea trench below Etheor Falls.\l"
	.string "Kyogre may have pursued it to\l"
	.string "there, given its affinity\l"
	.string "for the ocean.\p"
	.string "Conversely, Sha-Yon, being the\n"
	.string "deity of Rising, will go to\l"
	.string "Hoenn's highest point. That would\l"
	.string "be Crimney Caldera, the peak\l"
	.string "of Mt. Chimney. As that is a\l"
	.string "volcanic environment, I can see\l"
	.string "Groudon pursuing it there as well.$"

CaveOfOriginCutscene_Text_HighestAndLowest:
	.string "The highest and the lowest points\n"
	.string "of the region... sounds like a plan.\l"
	.string "We can quell Groudon and Kyogre\l"
	.string "and retrieve Luo-Shan and Sha-Yon\l"
	.string "all in one fell swoop!$"

CaveOfOriginCutscene_Text_YouMayComePlayer:
	.string "I am inclined to nominate\n"
	.string "{PLAYER} to assist us in this\l"
	.string "endeavor. Please, do seek out\l"
	.string "the places I have mentioned,\l"
	.string "and do what you must with these\l"
	.string "Legendary Pokemon.\l"
	.string "A truly master-level trainer\l"
	.string "like you... I think can\l"
	.string "handle them.$"
