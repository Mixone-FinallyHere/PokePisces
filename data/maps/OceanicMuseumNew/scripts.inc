OceanicMuseumNew_MapScripts::
	.byte 0

OceanicMuseumNew_EventScript_Stern::
	lock
	goto_if_lt VAR_OLD_GUYS_STATE, 8, OceanicMuseumNew_EventScript_SternPreDock
	faceplayer
	goto_if_gt VAR_OLD_GUYS_STATE, 8, OceanicMuseumNew_EventScript_SternPostDock
	goto_if_set FLAG_DOCK_QUEST_FOUND_STERN, OceanicMuseumNew_EventScript_SternGatherOthers
	setflag FLAG_DOCK_QUEST_FOUND_STERN
	msgbox OceanicMuseumNew_Text_ImCaptStern, MSGBOX_DEFAULT
	speakername OceanicMuseumNew_Text_NameStern
	msgbox OceanicMuseumNew_Text_DockWantsMe, MSGBOX_AUTOCLOSE
	release
	end

OceanicMuseumNew_EventScript_SternPreDock::
	msgbox OceanicMuseumNew_Text_SternPreDock, MSGBOX_AUTOCLOSE
	release
	end

OceanicMuseumNew_EventScript_SternGatherOthers::
	speakername OceanicMuseumNew_Text_NameStern
	msgbox OceanicMuseumNew_Text_SternGatherOthers, MSGBOX_AUTOCLOSE
	release
	end

OceanicMuseumNew_EventScript_SternPostDock::
	speakername OceanicMuseumNew_Text_NameStern
	msgbox OceanicMuseumNew_Text_SternPostDock, MSGBOX_AUTOCLOSE
	release
	end

OceanicMuseumNew_EventScript_Moon::
    trainerbattle_single TRAINER_P_MOON, OceanicMuseumNew_Text_MoonIntro, OceanicMuseumNew_Text_MoonDefeated
    msgbox OceanicMuseumNew_Text_MoonPostBattle, MSGBOX_AUTOCLOSE
    end

OceanicMuseumNew_EventScript_Venus::
    trainerbattle_single TRAINER_P_VENUS, OceanicMuseumNew_Text_VenusIntro, OceanicMuseumNew_Text_VenusDefeated
    msgbox OceanicMuseumNew_Text_VenusPostBattle, MSGBOX_AUTOCLOSE
    end

OceanicMuseumNew_Text_NameStern:
	.string "Cpt. Stern$"

OceanicMuseumNew_Text_SternPreDock:
	.string "(He seems to be doing something\n"
	.string "important on the computer...\l"
	.string "you should just leave him be.)$"

OceanicMuseumNew_Text_ImCaptStern:
	.string "Yes? If you're looking for Stern,\n"
	.string "that would be me.$"

OceanicMuseumNew_Text_DockWantsMe:
	.string "...Oh, yes. Dock has been emailing\n"
	.string "me constantly about his party.\l"
	.string "Trust me, I am aware.\p"
	.string "I simply had to finish a few orders.\n"
	.string "And... yes, I'm just about done.\l"
	.string "I will be at the Shipyard shortly.\p"
	.string "You're looking for Archie and Drake\n"
	.string "as well? Well, Archie should be\l"
	.string "at the Ozone Institute, as usual.\l"
	.string "And I believe Drake has a home\l"
	.string "north of Fallarbor in an area\l"
	.string "called Fossil Shores. That should\l"
	.string "account for them both. Good luck.$"

OceanicMuseumNew_Text_SternGatherOthers:
	.string "You're looking for Archie and Drake\n"
	.string "as well? Well, Archie should be\l"
	.string "at the Ozone Institute, as usual.\l"
	.string "And I believe Drake has a home\l"
	.string "north of Fallarbor in an area\l"
	.string "called Fossil Shores. That should\l"
	.string "account for them both. Good luck.$"

OceanicMuseumNew_Text_SternPostDock:
	.string "Dock is a good man. I'm happy\n"
	.string "to have had him with me for so long.\l"
	.string "Sincerely, I wish him a\l"
	.string "happy retirement.$"

OceanicMuseumNew_Text_MoonIntro:
	.string "By the power of the tides,\n"
	.string "I shall defeat you!$"

OceanicMuseumNew_Text_MoonDefeated:
	.string "This is lunacy!$"

OceanicMuseumNew_Text_MoonPostBattle:
	.string "Now, where did the rest of\n"
	.string "my sailor squad run off to...$"

OceanicMuseumNew_Text_VenusIntro:
	.string "I'll stick ya in a mean\n"
	.string "greenhouse, stranger!$"

OceanicMuseumNew_Text_VenusDefeated:
	.string "Did ya sweat somethin'\n"
	.string "fierce, at least?$"

OceanicMuseumNew_Text_VenusPostBattle:
	.string "The pH levels in this museum\n"
	.string "need to be adjusted, I think.$"
