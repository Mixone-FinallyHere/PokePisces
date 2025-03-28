.set LOCALID_WORKER1, 15
.set LOCALID_WORKER2, 16
.set LOCALID_WORKER3, 17
.set LOCALID_TABITHA, 18
.set LOCALID_MATT, 19
.set LOCALID_GUARD, 21
.set LOCALID_MAXIE, 22
.set LOCALID_ARCHIE, 23
.set LOCALID_TABITHA2, 24
.set LOCALID_MATT2, 25

OzoneLilycoveHQ_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, OzoneLilycoveHQ_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OzoneLilycoveHQ_OnFrame
	.byte 0

OzoneLilycoveHQ_OnFrame:
	map_script_2 VAR_OZONE_ADMINS_STATE, 0, OzoneLilycoveHQ_EventScript_NoBusinessHere
	map_script_2 VAR_OZONE_ADMINS_STATE, 1, OzoneLilycoveHQ_EventScript_SomeBusinessHere
	.2byte 0

OzoneLilycoveHQ_OnLoad:
	call OzoneLilycoveHQ_EventScript_RemoveOzoners
	call_if_lt VAR_OZONE_ADMINS_STATE, 3, OzoneLilycoveHQ_EventScript_RemoveGuard
	end

OzoneLilycoveHQ_EventScript_RemoveGuard::
	removeobject LOCALID_GUARD
	setflag FLAG_TEMP_11
	return

OzoneLilycoveHQ_EventScript_RemoveOzoners::
	removeobject LOCALID_MAXIE
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_TABITHA2
	removeobject LOCALID_MATT2
	setflag FLAG_TEMP_12
	return

OzoneLilycoveHQ_EventScript_NoBusinessHere::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, OzoneLilycoveHQ_Movement_ToTheCounter
	waitmovement 0
	msgbox OzoneLilycoveHQ_Text_NoBusinessHere, MSGBOX_AUTOCLOSE
	applymovement OBJ_EVENT_ID_PLAYER, OzoneLilycoveHQ_Movement_BackOutside
	waitmovement 0
	warp MAP_LILYCOVE_CITY, 64, 15
	waitstate
	release
	end

OzoneLilycoveHQ_Movement_ToTheCounter:
	walk_up
	walk_up
	step_end

OzoneLilycoveHQ_Movement_BackOutside:
	walk_down
	walk_down
	step_end

OzoneLilycoveHQ_EventScript_SomeBusinessHere::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, OzoneLilycoveHQ_Movement_ToTheCounter
	waitmovement 0
	msgbox OzoneLilycoveHQ_Text_SomeBusinessHere, MSGBOX_AUTOCLOSE
	setvar VAR_OZONE_ADMINS_STATE, 2
	release
	end

OzoneLilycoveHQ_EventScript_Landon::
    trainerbattle_single TRAINER_P_LANDON, OzoneLilycoveHQ_Text_LandonIntro, OzoneLilycoveHQ_Text_LandonDefeated
    msgbox OzoneLilycoveHQ_Text_LandonPostBattle, MSGBOX_AUTOCLOSE
    end

OzoneLilycoveHQ_EventScript_Terra::
    trainerbattle_single TRAINER_P_TERRA, OzoneLilycoveHQ_Text_TerraIntro, OzoneLilycoveHQ_Text_TerraDefeated
    msgbox OzoneLilycoveHQ_Text_TerraPostBattle, MSGBOX_AUTOCLOSE
    end

OzoneLilycoveHQ_EventScript_Sean::
    trainerbattle_single TRAINER_P_OZONE_SEAN, OzoneLilycoveHQ_Text_SeanIntro, OzoneLilycoveHQ_Text_SeanDefeated
    msgbox OzoneLilycoveHQ_Text_SeanPostBattle, MSGBOX_AUTOCLOSE
    end

OzoneLilycoveHQ_EventScript_Marina::
    trainerbattle_single TRAINER_P_MARINA, OzoneLilycoveHQ_Text_MarinaIntro, OzoneLilycoveHQ_Text_MarinaDefeated
    msgbox OzoneLilycoveHQ_Text_MarinaPostBattle, MSGBOX_AUTOCLOSE
    end

OzoneLilycoveHQ_EventScript_UmbrellaResearcher::
	lock
	faceplayer
	goto_if_eq VAR_PARASOL_QUEST_STATE, 0, OzoneLilycoveHQ_EventScript_HelpWithBrellas
	goto_if_eq VAR_PARASOL_QUEST_STATE, 1, OzoneLilycoveHQ_EventScript_GoGetBrellas
	goto_if_eq VAR_PARASOL_QUEST_STATE, 2, OzoneLilycoveHQ_EventScript_HaveBrella
	goto_if_gt VAR_PARASOL_QUEST_STATE, 2, OzoneLilycoveHQ_EventScript_NoMoreBrella
	release
	end

OzoneLilycoveHQ_EventScript_HelpWithBrellas::
	setvar VAR_PARASOL_QUEST_STATE, 1
	msgbox OzoneLilycoveHQ_Text_BrellaHelp, MSGBOX_AUTOCLOSE
	goto OzoneLilycoveHQ_EventScript_GoGetBrellas
	release
	end

OzoneLilycoveHQ_EventScript_GoGetBrellas::
	msgbox OzoneLilycoveHQ_Text_BrellaGoGettem, MSGBOX_DEFAULT
	closemessage
	release
	end

OzoneLilycoveHQ_EventScript_HaveBrella::
	msgbox OzoneLilycoveHQ_Text_BrellaThanks, MSGBOX_DEFAULT
	giveitem ITEM_UTILITY_UMBRELLA
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_PARASOL_QUEST_STATE, 3
	msgbox OzoneLilycoveHQ_Text_BrellaAbout, MSGBOX_AUTOCLOSE
	release
	end

OzoneLilycoveHQ_EventScript_NoMoreBrella::
	msgbox OzoneLilycoveHQ_Text_BrellaNoMore, MSGBOX_AUTOCLOSE
	release
	end

OzoneLilycoveHQ_EventScript_BoardroomMeeting::
	lock
	getdoublessizeforgym
	goto_if_eq VAR_RESULT, 0, OzoneLilycoveHQ_EventScript_NotEnoughPokemon
	msgbox OzoneLilycoveHQ_Text_Boardroom1, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, OzoneLilycoveHQ_Movement_PlayerHide
	waitmovement 0
	applymovement LOCALID_WORKER2, OzoneLilycoveHQ_Movement_Worker2Talking
	msgbox OzoneLilycoveHQ_Text_Boardroom2, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	applymovement LOCALID_MATT, OzoneLilycoveHQ_Movement_MattTalking
	msgbox OzoneLilycoveHQ_Text_Matt1, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameTabitha
	applymovement LOCALID_TABITHA, OzoneLilycoveHQ_Movement_TabithaTalking
	msgbox OzoneLilycoveHQ_Text_Tabitha1, MSGBOX_DEFAULT
	speakername NULL
	applymovement LOCALID_WORKER1, OzoneLilycoveHQ_Movement_Worker1Talking
	msgbox OzoneLilycoveHQ_Text_Boardroom3, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	applymovement LOCALID_MATT, OzoneLilycoveHQ_Movement_MattTalking
	msgbox OzoneLilycoveHQ_Text_Matt2, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameTabitha
	applymovement LOCALID_TABITHA, OzoneLilycoveHQ_Movement_TabithaTalking
	msgbox OzoneLilycoveHQ_Text_Tabitha2, MSGBOX_DEFAULT
	speakername NULL
	applymovement LOCALID_WORKER3, OzoneLilycoveHQ_Movement_Worker3Talking
	msgbox OzoneLilycoveHQ_Text_Boardroom4, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, OzoneLilycoveHQ_Movement_PlayerEnters
	waitmovement 0
	applymovement LOCALID_WORKER2, OzoneLilycoveHQ_Movement_WorkerFlabbergasted
	msgbox OzoneLilycoveHQ_Text_Boardroom5, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameTabitha
	applymovement LOCALID_TABITHA, OzoneLilycoveHQ_Movement_TabithaTalking
	msgbox OzoneLilycoveHQ_Text_Tabitha3, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	applymovement LOCALID_MATT, OzoneLilycoveHQ_Movement_MattAngry
	msgbox OzoneLilycoveHQ_Text_Matt3, MSGBOX_DEFAULT
	playse SE_M_SWEET_SCENT
	speakername NULL
	msgbox OzoneLilycoveHQ_Text_BoardSigh, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	applymovement LOCALID_MATT, OzoneLilycoveHQ_Movement_MattTalking
	msgbox OzoneLilycoveHQ_Text_Matt4, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameTabitha
	applymovement LOCALID_TABITHA, OzoneLilycoveHQ_Movement_TabithaTalking
	msgbox OzoneLilycoveHQ_Text_Tabitha4, MSGBOX_DEFAULT
	speakername NULL
	msgbox OzoneLilycoveHQ_Text_YouNod, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	applymovement LOCALID_MATT, OzoneLilycoveHQ_Movement_MattJumping
	waitmovement 0
	msgbox OzoneLilycoveHQ_Text_Matt5, MSGBOX_DEFAULT
	speakername NULL
	setflag FLAG_TEMP_13
	clearflag FLAG_TEMP_12
	trainerbattle_two_trainers TRAINER_P_OZONE_MATT_1, OzoneLilycoveHQ_Text_MattDefeated, TRAINER_P_OZONE_TABITHA_1, OzoneLilycoveHQ_Text_TabithaDefeated, OzoneLilycoveHQ_EventScript_AdminsDefeated, NO_MUSIC
	goto OzoneLilycoveHQ_EventScript_AdminsDefeated
	release
	end

OzoneLilycoveHQ_EventScript_AdminsDefeated::
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_WORKER1
	removeobject LOCALID_WORKER2
	removeobject LOCALID_WORKER3
	removeobject LOCALID_TABITHA
	removeobject LOCALID_MATT
	setflag FLAG_TEMP_13
	clearflag FLAG_TEMP_12
	addobject LOCALID_MAXIE
	addobject LOCALID_ARCHIE
	delay 16
	fadescreen FADE_FROM_BLACK
	addobject LOCALID_TABITHA2
	addobject LOCALID_MATT2
	speakername OzoneLilycoveHQ_Text_NameTabitha
	applymovement LOCALID_TABITHA2, OzoneLilycoveHQ_Movement_TabithaTalking
	msgbox OzoneLilycoveHQ_Text_Tabitha5, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	applymovement LOCALID_MATT2, OzoneLilycoveHQ_Movement_MattTalking
	msgbox OzoneLilycoveHQ_Text_Matt6, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameTabitha
	applymovement LOCALID_TABITHA2, OzoneLilycoveHQ_Movement_TabithaTalking
	waitmovement 0
	msgbox OzoneLilycoveHQ_Text_Tabitha6, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	applymovement LOCALID_MATT2, OzoneLilycoveHQ_Movement_MattTalking
	msgbox OzoneLilycoveHQ_Text_Matt7, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAXIE, OzoneLilycoveHQ_Movement_MaxieWalkIn
	applymovement LOCALID_ARCHIE, OzoneLilycoveHQ_Movement_ArchieWalkIn
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	speakername OzoneLilycoveHQ_Text_NameArchie
	msgbox OzoneLilycoveHQ_Text_WhatsGoingOnHere, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	msgbox OzoneLilycoveHQ_Text_BackMeUpHere, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMaxie
	msgbox OzoneLilycoveHQ_Text_NoSquabbling, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMatt
	msgbox OzoneLilycoveHQ_Text_FineIllLeave, MSGBOX_DEFAULT
	applymovement LOCALID_MATT2, OzoneLilycoveHQ_Movement_MattLeaves
	waitmovement 0
	applymovement LOCALID_MAXIE, OzoneLilycoveHQ_Movement_MaxieGiveNav
	waitmovement 0
	speakername OzoneLilycoveHQ_Text_NameMaxie
	msgbox OzoneLilycoveHQ_Text_YouAreBirchsKid, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameTabitha
	msgbox OzoneLilycoveHQ_Text_TheyWantToGetThroughArc, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMaxie
	msgbox OzoneLilycoveHQ_Text_OhYoureDoingGyms, MSGBOX_DEFAULT
	speakername NULL
	playfanfare MUS_OBTAIN_ITEM
	message OzoneLilycoveHQ_Text_ReceivedPokenav
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	speakername OzoneLilycoveHQ_Text_NameArchie
	msgbox OzoneLilycoveHQ_Text_ThatPokenavIsCool, MSGBOX_DEFAULT
	speakername OzoneLilycoveHQ_Text_NameMaxie
	msgbox OzoneLilycoveHQ_Text_TabithaWillAssistYou, MSGBOX_DEFAULT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	speakername OzoneLilycoveHQ_Text_NameTabitha
	applymovement LOCALID_TABITHA2, OzoneLilycoveHQ_Movement_TabithaTalking
	msgbox OzoneLilycoveHQ_Text_Tabitha7, MSGBOX_AUTOCLOSE
	speakername NULL
	setvar VAR_OZONE_ADMINS_STATE, 3
	setvar VAR_PISCES_STORY_PROGRESS, 3
	warp MAP_THE_COLD_MINES, 56, 35
	waitstate
	release
	end

OzoneLilycoveHQ_EventScript_NotEnoughPokemon::
	msgbox OzoneLilycoveHQ_Text_NotEnoughPokemon, MSGBOX_DEFAULT
	closemessage
	warp MAP_OZONE_LILYCOVE_HQ, 2, 3
	waitstate
	release
	end

OzoneLilycoveHQ_Movement_PlayerHide:
	walk_right
	walk_up
	face_right
	step_end

OzoneLilycoveHQ_Movement_Worker2Talking:
	walk_in_place_slow_up
	step_end

OzoneLilycoveHQ_Movement_MattTalking:
	walk_in_place_slow_down
	step_end

OzoneLilycoveHQ_Movement_TabithaTalking:
	walk_in_place_down
	step_end

OzoneLilycoveHQ_Movement_Worker1Talking:
	walk_in_place_slow_right
	step_end

OzoneLilycoveHQ_Movement_Worker3Talking:
	walk_in_place_slow_left
	step_end

OzoneLilycoveHQ_Movement_PlayerEnters:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

OzoneLilycoveHQ_Movement_WorkerFlabbergasted:
	delay_16
	emote_question_mark
	delay_16
	walk_in_place_fast_left
	step_end

OzoneLilycoveHQ_Movement_MattAngry:
	walk_in_place_fast_left
	step_end

OzoneLilycoveHQ_Movement_MattJumping:
	emote_exclamation_mark
	delay_4
	jump_in_place_down
	step_end

OzoneLilycoveHQ_Movement_TabithaDeclaration:
	walk_left
	walk_down
	walk_down
	walk_right
	face_down
	step_end

OzoneLilycoveHQ_Movement_MattUpset:
	walk_in_place_faster_down
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

OzoneLilycoveHQ_Movement_MattLeaves:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

OzoneLilycoveHQ_Movement_MaxieWalkIn:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

OzoneLilycoveHQ_Movement_ArchieWalkIn:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

OzoneLilycoveHQ_Movement_MaxieGiveNav:
	walk_right
	face_up
	step_end

OzoneLilycoveHQ_EventScript_Receptionist::
	msgbox OzoneLilycoveHQ_Text_Receptionist, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_NeedOzonesHelp1::
	msgbox OzoneLilycoveHQ_Text_NeedOzonesHelp1, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_NeedOzonesHelp2::
	msgbox OzoneLilycoveHQ_Text_NeedOzonesHelp2, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_NeedOzonesHelp3::
	msgbox OzoneLilycoveHQ_Text_NeedOzonesHelp3, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_AboutSun::
	msgbox OzoneLilycoveHQ_Text_AboutSun, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_AboutRain::
	msgbox OzoneLilycoveHQ_Text_AboutRain, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_AboutHail::
	msgbox OzoneLilycoveHQ_Text_AboutHail, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_AboutSandstorm::
	msgbox OzoneLilycoveHQ_Text_AboutSandstorm, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_SteadfastGuard::
	msgbox OzoneLilycoveHQ_Text_SteadfastGuard, MSGBOX_NPC
	end

OzoneLilycoveHQ_EventScript_ExasperatedGuard::
	msgbox OzoneLilycoveHQ_Text_ExasperatedGuard, MSGBOX_NPC
	end

OzoneLilycoveHQ_Text_Receptionist:
	.string "Our workers are always looking\n"
	.string "for a fun battle to pass time!\p"
	.string "...Hopefully not TOO much of\n"
	.string "their time, but hey, I'm\l"
	.string "not their manager.$"

OzoneLilycoveHQ_Text_NeedOzonesHelp1:
	.string "The harsh sunlight in Masonried Hike\n"
	.string "is making it difficult to grow\l"
	.string "my crops there...\l"
	.string "I was hoping Team Ozone could\l"
	.string "assist me.$"

OzoneLilycoveHQ_Text_NeedOzonesHelp2:
	.string "I tell ya hwat, Canopour Wilds\n"
	.string "gets absolutely inundated with\l"
	.string "heavy rain durin' this season!\p"
	.string "It makes growin' berry trees real\n"
	.string "difficult sometimes!$"

OzoneLilycoveHQ_Text_NeedOzonesHelp3:
	.string "My appointment should be soon...\p"
	.string "I'm from Fallarbor Town. The ash\n"
	.string "falling from Mt. Chimney nearby\l"
	.string "has really taken a toll on my\l"
	.string "lungs' health...\p"
	.string "Team Ozone offers relocation\n"
	.string "assistance for these types\l"
	.string "of problems... it is very kind.$"

OzoneLilycoveHQ_Text_AboutSun:
	.string "You like summer days, bud?\n"
	.string "Well, then Sun may be the weather\l"
	.string "for you!\p"
	.string "When Harsh Sunlight is summoned,\n"
	.string "Fire type moves get slightly boosted,\l"
	.string "and Water moves, conversely,\l"
	.string "get slightly weakened.\p"
	.string "If the Pokemon using the Fire type\n"
	.string "move is a Fire type itself, that\l"
	.string "boost increases a little bit!\p"
	.string "Plus, there's moves like Solar Beam\n"
	.string "and abilities like Chlorophyll\l"
	.string "that synergize with the weather.\p"
	.string "Sun really can benefit your team\n"
	.string "if you invest building your\l"
	.string "party around it!$"

OzoneLilycoveHQ_Text_AboutRain:
	.string "In a bit of an erratic mood?\n"
	.string "One thing that always calms me\l"
	.string "down is the pitter-patter of Rain.\p"
	.string "Rain can be summoned in Pokemon\n"
	.string "battles by certain moves\l"
	.string "and abilities. It will strengthen\l"
	.string "Water type moves and weaken\l"
	.string "Fire type moves each by about\l"
	.string "a third of their normal damage.\p"
	.string "Water type Pokemon get to enjoy\n"
	.string "a bit more of a boost. And, they\l"
	.string "also tend to learn more moves\l"
	.string "that benefit from Rain,\l"
	.string "like Aquascade.\p"
	.string "Get good at utilizing Rain,\n"
	.string "and opponents can find themselves\l"
	.string "getting washed away...$"

OzoneLilycoveHQ_Text_AboutHail:
	.string "It may be the rarest weather\n"
	.string "here in Hoenn, but Hail is\l"
	.string "my personal favorite.\p"
	.string "It heightens the Defense stat\n"
	.string "of Ice type Pokemon, and hurts\l"
	.string "all other typed Pokemon on the\l"
	.string "field every turn.\p"
	.string "Plus, if your Pokemon get access\n"
	.string "to stuff like Blizzard or\l"
	.string "Slush Rush, they can turn Hail\l"
	.string "into a deadly cold sweep!\p"
	.string "Hail is a good weather to try\n"
	.string "out if you're using a bunch\l"
	.string "of Ice Pokemon. They can\l"
	.string "be pretty frail otherwise!$"

OzoneLilycoveHQ_Text_AboutSandstorm:
	.string "Ah, the Sandstorm... the harshest\n"
	.string "of the four weathers in battle.\p"
	.string "All Pokemon that are not Rock,\n"
	.string "Ground, or Steel types get hit\l"
	.string "for chip damage every turn.\l"
	.string "It isn't so bad if you have one\l"
	.string "of those types ready, especially\l"
	.string "Rock Pokemon, as they receive\l"
	.string "a boost to their Special Defense.\p"
	.string "Moves like Dune Slicer and those\n"
	.string "with abilities like Sand Rush\l"
	.string "get ever deadlier in Sandstorm...\l"
	.string "Maybe that'd be something up\l"
	.string "your alley. Or maybe not...$"

OzoneLilycoveHQ_Text_SteadfastGuard:
	.string "The meeting room is currently\n"
	.string "closed, visitor.\l"
	.string "I can't let you through.$"

OzoneLilycoveHQ_Text_ExasperatedGuard:
	.string "On my lunch break right now.\n"
	.string "Have to listen to the managers\l"
	.string "argue on and on in the next room.\l"
	.string "Rather tiring.\p"
	.string "Uhhh.... you're a visitor, right?\n"
	.string "I guess you can listen in too...\l"
	.string "just, please don't disturb them.$"

OzoneLilycoveHQ_Text_NameMatt:
	.string "Matt$"

OzoneLilycoveHQ_Text_NameTabitha:
	.string "Tabitha$"

OzoneLilycoveHQ_Text_NameArchie:
	.string "Archie$"

OzoneLilycoveHQ_Text_NameMaxie:
	.string "Maxie$"

OzoneLilycoveHQ_Text_Boardroom1:
	.string "(There appears to be some\n"
	.string "kind of meeting going on…)$"

OzoneLilycoveHQ_Text_Boardroom2:
	.string "We are awaiting the directive from our\n"
	.string "administers, regarding where to funnel\l"
	.string "our time and resources.\p"
	.string "I was hoping we could get a concrete\n"
	.string "plan put into motion today?$"

OzoneLilycoveHQ_Text_Matt1:
	.string "I've been tellin' this knucklehead\n"
	.string "that we should keep on\l"
	.string "surveyin' the desert!\p"
	.string "Bound to be a crap-ton of historical\n"
	.string "finds buried there still!$"

OzoneLilycoveHQ_Text_Tabitha1:
	.string "Ridiculous, as usual.\n"
	.string "I remain firm in my assessment,\l"
	.string "being that the arctic regions\l"
	.string "of Hoenn should be focused on.\p"
	.string "I believe it noble to supply the\n"
	.string "subzero-dwelling monks and village\l"
	.string "goers with all they need to thrive\l"
	.string "in a harsh climate.$"

OzoneLilycoveHQ_Text_Boardroom3:
	.string "Well, ehem, Sweltorn Desert is not\n"
	.string "exactly the pinnacle of living\l"
	.string "conditions, either.$"

OzoneLilycoveHQ_Text_Matt2:
	.string "Damn right! Was JUST gonna say that!\p"
	.string "Sweltorn's people need help much more!$"

OzoneLilycoveHQ_Text_Tabitha2:
	.string "Are we really to believe that your\n"
	.string "intentions were altruistic,\l"
	.string "instead of what amounts to a\l"
	.string "juvenile treasure hunt…?$"

OzoneLilycoveHQ_Text_Boardroom4:
	.string "I… I d-don't see why we can't just…\n"
	.string "uhh…\l"
	.string "split resources?\p"
	.string "(Matt and Tabitha, in unison:)\n"
	.string "No.\p"
	.string "(You decide now is the… perfect, time\n"
	.string "to voice your opinion.)$"

OzoneLilycoveHQ_Text_Boardroom5:
	.string "Who is this? Are you on the committee?\p"
	.string "(You talk about the cave-in\n"
	.string "at the mines.)$"

OzoneLilycoveHQ_Text_Tabitha3:
	.string "This one has some common sense.\p"
	.string "I agree, we should make that our\n"
	.string "priority, post-haste.$"

OzoneLilycoveHQ_Text_Matt3:
	.string "WAIT UP! THAT AIN'T FAIR!$"

OzoneLilycoveHQ_Text_BoardSigh:
	.string "(A defeated sigh erupts from nearly\n"
	.string "everyone in the room.)$"

OzoneLilycoveHQ_Text_Matt4:
	.string "Why are we even gonna take orders\n"
	.string "from some rando?\p"
	.string "I bet this kid doesn't know jack\n"
	.string "about management!$"

OzoneLilycoveHQ_Text_Tabitha4:
	.string "Though I truly loathe you with every\n"
	.string "bone in my body, you do have some\l"
	.string "semblance of a point.\p"
	.string "Stranger, I personally believe the\n"
	.string "best way to read a person\l"
	.string "is through battle.\p"
	.string "Will you entertain my request?$"

OzoneLilycoveHQ_Text_YouNod:	
	.string "(You nod.)$"

OzoneLilycoveHQ_Text_Matt5:
	.string "Hey! Don't leave me outta this!$"

OzoneLilycoveHQ_Text_MattDefeated:
	.string "Ay caramba…! You weren't just some\n"
	.string "street rat after all!$"

OzoneLilycoveHQ_Text_TabithaDefeated:
	.string "Your team clearly trusts your judgment…\n"
	.string "I believe we should too.$"

OzoneLilycoveHQ_Text_Tabitha5:
	.string "{PLAYER}, well done…\n"
	.string "Matt, you were actively detrimental,\l"
	.string "at best.$"

OzoneLilycoveHQ_Text_Matt6:
	.string "Not my fault you insist on a crappy\n"
	.string "hail team! Sand is king, baby!$"

OzoneLilycoveHQ_Text_Tabitha6:
	.string "Hmph.\n"
	.string "You know what, this experience has\l"
	.string "been enlightening in more ways\l"
	.string "than one.\p"
	.string "Matt, you imbecile. I believe you unfit\n"
	.string "to be an admin.\p"
	.string "Henceforth, I refuse to\n"
	.string "work alongside you.$"

OzoneLilycoveHQ_Text_Matt7:
	.string "What!? What a joke, you crudmuncher!\p"
	.string "Fine! I don't wanna work\n"
	.string "with you either!\p"
	.string "You can keep THESE nerds…\n"
	.string "I'll get perms to lead my OWN branch\l"
	.string "from the bosses!\p"
	.string "You'll be fired in a week\n"
	.string "tops without my help!$"

OzoneLilycoveHQ_Text_WhatsGoingOnHere:
	.string "What's with all the voice raising\n"
	.string "in the meeting room!? I swear,\l"
	.string "Maxie and I leave you bilgeheads\l"
	.string "alone for too long and you go rabid!$"

OzoneLilycoveHQ_Text_BackMeUpHere:
	.string "B-Boss...\n"
	.string "Sorry, man, but I gotta\l"
	.string "hold my ground! Back me up!\l"
	.string "Tabby-boy is drivin' me nuts!$"

OzoneLilycoveHQ_Text_NoSquabbling:
	.string "That is quite enough, Matthew.\n"
	.string "Go to a separate room to cool\l"
	.string "your emotions. I will get Archibald\l"
	.string "to converse with you two\l"
	.string "individually later to determine\l"
	.string "how your roles will change,\l"
	.string "if at all. Dismissed.$"

OzoneLilycoveHQ_Text_FineIllLeave:
	.string "Urgh, fine.$"

OzoneLilycoveHQ_Text_YouAreBirchsKid:
	.string "Terribly sorry you had to\n"
	.string "listen to our workplace drama.\l"
	.string "You are the Professor's child,\l"
	.string "is that correct? I seem to remember\l"
	.string "you being a steadfast ally\l"
	.string "to the former champion.$"

OzoneLilycoveHQ_Text_TheyWantToGetThroughArc:
	.string "Maxie, sir. {PLAYER} came\n"
	.string "to us hoping we could clear\l"
	.string "the avalanche blocking up\l"
	.string "the Cold Mines. Would you allow\l"
	.string "us to allocate our men there\l"
	.string "to start excavating?$"

OzoneLilycoveHQ_Text_OhYoureDoingGyms:
	.string "That should work. Get to that\n"
	.string "whenever possible, Tabitha.\p"
	.string "Going through the Cold Mines\n"
	.string "to get to the gym in\l"
	.string "Zotpyre Village, I should assume?\l"
	.string "That is quite the trek.\l"
	.string "Do you possess a PokeNav?\p"
	.string "...No? Well, we cannot have that.\n"
	.string "You may have one of our spares.$"

OzoneLilycoveHQ_Text_ReceivedPokenav:
	.string "{PLAYER} received a PokéNav.$"

OzoneLilycoveHQ_Text_ThatPokenavIsCool:
	.string "That 'Nav has assisted me on\n"
	.string "many a voyage! If you get lost,\l"
	.string "keep an eye on the map\l"
	.string "included with it.$"

OzoneLilycoveHQ_Text_TabithaWillAssistYou:
	.string "Indeed.\n"
	.string "Now, I must be going back\l"
	.string "to the main building.\l"
	.string "Tabitha, you shall see to it\l"
	.string "that {PLAYER} can make it\l"
	.string "to their next destination.$"

OzoneLilycoveHQ_Text_Tabitha7:
	.string "Yes, sir.\p"
	.string "Come with me, {PLAYER}.\n"
	.string "We will get to work post-haste.$"

OzoneLilycoveHQ_Text_BrellaHelp:
	.string "I've been doing extensive field testing\n"
	.string "for a product I gather that most\l"
	.string "don't think is important;\l"
	.string "umbrellas.\p"
	.string "A potent protector from precipitation,\n"
	.string "AND UV rays to boot!?\l"
	.string "Fantastic!\p"
	.string "I yearn to make Hoenn's\n"
	.string "best ever parasol!\p"
	.string "To that end, I have been supplying a\n"
	.string "few Parasol Ladies some test\l"
	.string "products to see how they fare.\p"
	.string "Problem, though…\p"
	.string "They have… refused to give them back.\p"
	.string "Those women have expressed that they\n"
	.string "will not return my umbrellas until\l"
	.string "they are defeated in COMBAT!\l"
	.string "Pokémon combat, I'd hope…\p"
	.string "You look tough. Would you be willing\n"
	.string "to fight them for me?\l"
	.string "A marvelous parasol would be in store…$"

OzoneLilycoveHQ_Text_BrellaGoGettem:
	.string "Most excellent!\p"
	.string "Last I'd heard, this herd of hoarders\n"
	.string "grouped up on the south beach of\l"
	.string "Sunbeach Strait.\p"
	.string "Go give 'em what's what!$"

OzoneLilycoveHQ_Text_BrellaThanks:
	.string "Gasp! My parasols! All intact!\n"
	.string "Thank the stars!\p"
	.string "I hope that bout wasn't\n"
	.string "too rough for you.\l"
	.string "Rest assured, your reward\l"
	.string "will be grand…\p"
	.string "…\p"
	.string "(He begins to tinker.)\p"
	.string "…That should do it!\n"
	.string "I proudly present…the…!\p"
	.string "Um, I have yet to think of\n"
	.string "a winning name.$"

OzoneLilycoveHQ_Text_BrellaAbout:
	.string "This masterpiece will protect you from\n"
	.string "the harsh weathers of life!\p"
	.string "I couldn't have completed this\n"
	.string "without you.\l"
	.string "Thanks a bundle!$"

OzoneLilycoveHQ_Text_BrellaNoMore:
	.string "Hope you're enjoying the new\n"
	.string "Umbrella prototype!$"

OzoneLilycoveHQ_Text_LandonIntro:
	.string "The sun's always shining at\n"
	.string "Ol' Bihq!$"

OzoneLilycoveHQ_Text_LandonDefeated:
	.string "Burnt like a pasty guy\n"
	.string "in the summer!$"

OzoneLilycoveHQ_Text_LandonPostBattle:
	.string "I much prefer working with\n"
	.string "Tabitha than Matt! I guess it's\l"
	.string "because I used to be a Magma Grunt.$"

OzoneLilycoveHQ_Text_TerraIntro:
	.string "Landon and I are in-sync!\n"
	.string "You won't be able to muscle\l"
	.string "through this sun team!$"

OzoneLilycoveHQ_Text_TerraDefeated:
	.string "Lights out...!$"

OzoneLilycoveHQ_Text_TerraPostBattle:
	.string "I used to originally work for\n"
	.string "Team Aqua. But for some reason,\l"
	.string "I find myself preferring Tabitha\l"
	.string "as a manager over Matt.\p"
	.string "I feel like the former knows what\n"
	.string "he's doing more, even though he\l"
	.string "can be cold.$"

OzoneLilycoveHQ_Text_SeanIntro:
	.string "Hope you're used to fighting\n"
	.string "in the rain, kid!$"

OzoneLilycoveHQ_Text_SeanDefeated:
	.string "Doused and tossed aside...!$"

OzoneLilycoveHQ_Text_SeanPostBattle:
	.string "Back in the day, I would run\n"
	.string "sun-using teams. But I've decided\l"
	.string "to try and branch out with rain!\p"
	.string "Didn't go so well that time...\n$"

OzoneLilycoveHQ_Text_MarinaIntro:
	.string "You remind me of me when I was your age.$"

OzoneLilycoveHQ_Text_MarinaDefeated:
	.string "Oh yeah, I was kind of a twerp at your\n"
	.string "age, too...$"

OzoneLilycoveHQ_Text_MarinaPostBattle:
	.string "Team Ozone is dedicated to keeping\n"
	.string "Hoenn in one piece.\p"
	.string "Remember that, kid!$"

OzoneLilycoveHQ_Text_NoBusinessHere:
	.string "Welcome to the\n"
	.string "Ozone Lilycove Branch HQ;\l"
	.string "how may I help you?\p"
	.string "I see. Well, if you have no\n"
	.string "business here... I must ask\l"
	.string "you to leave, so we can give\l"
	.string "full attention to those with\l"
	.string "upcoming appointments...$"

OzoneLilycoveHQ_Text_SomeBusinessHere:
	.string "Welcome to the\n"
	.string "Ozone Lilycove Branch HQ;\l"
	.string "how may I help you?\p"
	.string "Oh? You are wanting to see Tabitha?\p"
	.string "He is in a brief meeting right now.\n"
	.string "However, most of the office is on\l"
	.string "lunch break; it could help you pass\l"
	.string "the time to chat around.\p"
	.string "I'll have the guards grant you access\n"
	.string "to the upper floors.$"

OzoneLilycoveHQ_Text_NotEnoughPokemon:
	.string "(Your team may not be healthy\n"
	.string "enough for what is to come, if\l"
	.string "a battle is ahead.)\p"
	.string "(May be best to heal up first.)$"
