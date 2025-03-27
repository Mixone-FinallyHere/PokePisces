.set LOCALID_DOORGUARD, 1
.set LOCALID_TABITHA, 4

OzoneInt_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OzoneInt_OnTransition
	.byte 0

OzoneInt_OnTransition:
	setrespawn HEAL_LOCATION_OZONE_INSTITUTE
	end

OzoneInt_EventScript_DoorGuard::
	lock
	faceplayer
	goto_if_eq VAR_NEW_COO_STATE, 5, OzoneInt_EventScript_GuardGetOutOfWay
	goto_if_gt VAR_NEW_COO_STATE, 6, OzoneInt_EventScript_GuardPostBattles
	msgbox OzoneInt_Text_CantLetYouUpstairs, MSGBOX_AUTOCLOSE
	release
	end

OzoneInt_EventScript_GuardGetOutOfWay::
	msgbox OzoneInt_Text_ReadyForTheChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOORGUARD, OzoneInt_Movement_GuardGetOutOfWay
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_DOORGUARD
	setflag FLAG_TEMP_11
	release
	end

OzoneInt_Movement_GuardGetOutOfWay:
	walk_slow_up
	step_end

OzoneInt_EventScript_GuardPostBattles::
	msgbox OzoneInt_Text_GuardPostBattles, MSGBOX_AUTOCLOSE
	release
	end

OzoneInt_EventScript_Maxie::
	lock
	faceplayer
	speakername OzoneInt_Text_NameMaxie
	msgbox OzoneInt_Text_ThingsHaveGottenSerious, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, OzoneInt_EventScript_PlaneWarp
	msgbox OzoneInt_Text_PrepareAdequately, MSGBOX_AUTOCLOSE
	release
	end

OzoneInt_EventScript_PlaneWarp::
	speakername OzoneInt_Text_NameMaxie
	msgbox OzoneInt_Text_NoGoingBack, MSGBOX_DEFAULT
	closemessage
	warp MAP_PLANE_IN_FLIGHT, 7, 5
	waitstate
	release
	end

OzoneInt_EventScript_Archie::
	lock
	faceplayer
	goto_if_lt VAR_OLD_GUYS_STATE, 8, OzoneInt_EventScript_ArchiePreDock
	goto_if_gt VAR_OLD_GUYS_STATE, 8, OzoneInt_EventScript_ArchiePostDock
	goto_if_set FLAG_DOCK_QUEST_FOUND_ARCHIE, OzoneInt_EventScript_ArchieGatherOthers
	setflag FLAG_DOCK_QUEST_FOUND_ARCHIE
	speakername OzoneInt_Text_NameArchie
	msgbox OzoneInt_Text_DockNeedsMe, MSGBOX_AUTOCLOSE
	release
	end

OzoneInt_EventScript_ArchiePreDock::
	speakername OzoneInt_Text_NameArchie
	msgbox OzoneInt_Text_ArchiePreDock, MSGBOX_AUTOCLOSE
	release
	end

OzoneInt_EventScript_ArchiePostDock::
	speakername OzoneInt_Text_NameArchie
	msgbox OzoneInt_Text_ArchiePostDock, MSGBOX_AUTOCLOSE
	release
	end

OzoneInt_EventScript_ArchieGatherOthers::
	speakername OzoneInt_Text_NameArchie
	msgbox OzoneInt_Text_ArchieGatherOthers, MSGBOX_AUTOCLOSE
	release
	end

OzoneInt_EventScript_Tabitha::
	lock
	faceplayer
	speakername OzoneInt_Text_NameTabitha
	msgbox OzoneInt_Text_TabithaBolterockAdvice, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OZONE_ADMINS_STATE, 6
	goto_if_eq VAR_FACING, DIR_NORTH, OzoneInt_EventScript_TabithaLeaveGoAroundPlayer
	applymovement LOCALID_TABITHA, OzoneInt_Movement_TabithaLeave
	waitmovement 0
	removeobject LOCALID_TABITHA
	setflag FLAG_HIDE_TABITHA_OZONE
	release
	end

OzoneInt_Movement_TabithaLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	step_end

OzoneInt_EventScript_TabithaLeaveGoAroundPlayer::
	applymovement LOCALID_TABITHA, OzoneInt_Movement_TabithaLeaveGoAroundPlayer
	waitmovement 0
	removeobject LOCALID_TABITHA
	setflag FLAG_HIDE_TABITHA_OZONE
	release
	end

OzoneInt_Movement_TabithaLeaveGoAroundPlayer:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	step_end

OzoneInt_EventScript_OzoneChallengeSign::
    msgbox OzoneInt_Text_OzoneChallengeSign, MSGBOX_SIGN
    end

OzoneInt_Text_OzoneChallengeSign:
	.string "Upstairs is the seldom-used site\n"
	.string "of the Ozone Challenge.\l"
	.string "Said challenge may return when\l"
	.string "we find a worthy enough trainer.$"

OzoneInt_Text_NameMaxie:
	.string "Maxie$"

OzoneInt_Text_NameArchie:
	.string "Archie$"

OzoneInt_Text_NameTabitha:
	.string "Tabitha$"

OzoneInt_Text_DockNeedsMe:
	.string "...You're telling me Dock is\n"
	.string "expecting me? I hadn't gotten\l"
	.string "the memo! Someone's going to get\l"
	.string "reprimanded for losing my mail...!\p"
	.string "Well, that's none of your business.\n"
	.string "I'll get on my way to Sea Mauville\l"
	.string "in a bit.$"

OzoneInt_Text_ArchiePreDock:
	.string "Oh! It's the Professor's kid!\n"
	.string "How've you been? In good health?\p"
	.string "The new management style took some\n"
	.string "time getting used to, but I sure\l"
	.string "as hell do not mind! Now that I\l"
	.string "get to actually do some meaningful\l"
	.string "change, I've been a lot happier.\p"
	.string "Maybe you can join our ranks\n"
	.string "someday! But I don't want to distract\l"
	.string "you from your gym challenge right now.\l"
	.string "Go dominate!$"

OzoneInt_Text_ArchiePostDock:
	.string "Oh! It's {PLAYER}!\n"
	.string "How've you been? In good health?\p"
	.string "The new management style took some\n"
	.string "time getting used to, but I sure\l"
	.string "as hell do not mind! Now that I\l"
	.string "get to actually do some meaningful\l"
	.string "change, I've been a lot happier.\p"
	.string "Maybe you can join our ranks\n"
	.string "someday! But I don't want to distract\l"
	.string "you from your gym challenge right now.\l"
	.string "Go dominate!$"

OzoneInt_Text_ArchieGatherOthers:
	.string "Lookin' for Ol' Drake? That codger.\n"
	.string "I believe he built his own house\l"
	.string "somewhere north of Fallarbor Town.\p"
	.string "No, of course he doesn't use\n"
	.string "computers. You'd sooner see\l"
	.string "a Bolterock fly!$"

OzoneInt_Text_CantLetYouUpstairs:
	.string "Sorry, I can't let you upstairs\n"
	.string "without explicit permission\l"
	.string "from the higher-ups.$"

OzoneInt_Text_ReadyForTheChallenge:
	.string "{PLAYER}! Thanks for coming!\p"
	.string "I'm assuming you're here for\n"
	.string "the Ozone Challenge that\l"
	.string "Maxie and Archie organized?\p"
	.string "Great! Well, I hope you've\n"
	.string "adequately prepared. When you're\l"
	.string "good to go, come on in!$"

OzoneInt_Text_GuardPostBattles:
	.string "Hope you had a fun time\n"
	.string "doing the Ozone Challenge!$"

OzoneInt_Text_ThingsHaveGottenSerious:
	.string "Hello, {PLAYER}. Deacon Wallace\n"
	.string "has briefed me on recent events.\p"
	.string "So, we are to be chauffeuring you\n"
	.string "to the Golden Plains, mm?\l"
	.string "It would be my pleasure.\p"
	.string "However, I must warn you.\n"
	.string "The only place for the plane to\l"
	.string "safely land will be at the western\l"
	.string "end of that island. The Plains\l"
	.string "lie on the eastern end.\p"
	.string "The Ever Grande Road, which spans\n"
	.string "these two locations, is a place\l"
	.string "for only the best of the best\l"
	.string "trainers to battle with their\l"
	.string "Pokemon. It will be a trek\l"
	.string "most grueling.\p"
	.string "I strongly suggest that you\n"
	.string "tie up any loose ends that you\l"
	.string "must before we embark.\l"
	.string "Archibald and I will be able to\l"
	.string "provide you basic necessities\l"
	.string "such as healing, a PC, and\l"
	.string "basic items. But that is all\l"
	.string "that we can guarantee.\p"
	.string "Knowing all this, do you\n"
	.string "wish to leave now?$"

OzoneInt_Text_PrepareAdequately:
	.string "I do not blame you.\n"
	.string "Please, go take care of anything\l"
	.string "that you may need to.\l"
	.string "Then, come see me when\l"
	.string "you are truly prepared.$"

OzoneInt_Text_NoGoingBack:
	.string "Affirmative, {PLAYER}.\n"
	.string "There will be no going back.\p"
	.string "I will get the aeroplane ready.$"

OzoneInt_Text_TabithaBolterockAdvice:
	.string "It is nice to see you, {PLAYER}.\n"
	.string "I have been spending a lot more\l"
	.string "time here at Ozone's main\l"
	.string "facility thanks to that buffoon's\l"
	.string "fracturing of our department.\p"
	.string "I am planning a trip west to\n"
	.string "obtain some sensitive research\l"
	.string "files from a colleague of ours,\l"
	.string "Professor Cosmo, in Fallarbor Town.\p"
	.string "How many badges do you possess\n"
	.string "as of now? Four? Hmm. Your next\l"
	.string "stop should be Lavaridge, then.\p"
	.string "Perfect! That is in the same\n"
	.string "general area. I can assist you\l"
	.string "with traversing the rugged\l"
	.string "mountainous terrain ahead, if\l"
	.string "you will accompany me to\l"
	.string "Fallarbor Town.\p"
	.string "I assume that is acceptable.\n"
	.string "We shall meet up on Masonried\l"
	.string "Hike due west. Best not\l"
	.string "to dawdle, {PLAYER}.$"
