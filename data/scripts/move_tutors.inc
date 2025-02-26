SlateportCity_PokemonFanClub_EventScript_SwaggerTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_SWAGGER, MoveTutor_EventScript_SwaggerTaught
	msgbox MoveTutor_Text_SwaggerTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_SwaggerDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_SwaggerDeclined
	msgbox MoveTutor_Text_SwaggerWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SWAGGER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_SwaggerDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_SWAGGER
	goto MoveTutor_EventScript_SwaggerTaught
	end

MoveTutor_EventScript_SwaggerDeclined::
	msgbox MoveTutor_Text_SwaggerDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_SwaggerTaught::
	msgbox MoveTutor_Text_SwaggerTaught, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RolloutTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_ROLLOUT, MoveTutor_EventScript_RolloutTaught
	msgbox MoveTutor_Text_RolloutTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_RolloutDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_RolloutDeclined
	msgbox MoveTutor_Text_RolloutWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ROLLOUT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_RolloutDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_ROLLOUT
	goto MoveTutor_EventScript_RolloutTaught
	end

MoveTutor_EventScript_RolloutDeclined::
	msgbox MoveTutor_Text_RolloutDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_RolloutTaught::
	msgbox MoveTutor_Text_RolloutTaught, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_FuryCutterTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_FURY_CUTTER, MoveTutor_EventScript_FuryCutterTaught
	msgbox MoveTutor_Text_FuryCutterTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_FuryCutterDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_FuryCutterDeclined
	msgbox MoveTutor_Text_FuryCutterWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FURY_CUTTER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_FuryCutterDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_FURY_CUTTER
	goto MoveTutor_EventScript_FuryCutterTaught
	end

MoveTutor_EventScript_FuryCutterDeclined::
	msgbox MoveTutor_Text_FuryCutterDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_FuryCutterTaught::
	msgbox MoveTutor_Text_FuryCutterTaught, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_House_EventScript_MimicTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_MIMIC, MoveTutor_EventScript_MimicTaught
	msgbox MoveTutor_MimicTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_MimicDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_MimicDeclined
	msgbox MoveTutor_Text_MimicWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MIMIC
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_MimicDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_MIMIC
	goto MoveTutor_EventScript_MimicTaught
	end

MoveTutor_EventScript_MimicDeclined::
	msgbox MoveTutor_MimicDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_MimicTaught::
	msgbox MoveTutor_Text_MimicTaught, MSGBOX_DEFAULT
	release
	end

FallarborTown_Mart_EventScript_MetronomeTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_METRONOME, MoveTutor_EventScript_MetronomeTaught
	msgbox MoveTutor_Text_MetronomeTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_MetronomeDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_MetronomeDeclined
	msgbox MoveTutor_Text_MetronomeWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_METRONOME
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_MetronomeDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_METRONOME
	goto MoveTutor_EventScript_MetronomeTaught
	end

MoveTutor_EventScript_MetronomeDeclined::
	msgbox MoveTutor_Text_MetronomeDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_MetronomeTaught::
	msgbox MoveTutor_Text_MetronomeTaught, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_SleepTalkTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_SLEEP_TALK, MoveTutor_EventScript_SleepTalkTaught
	msgbox MoveTutor_Text_SleepTalkTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_SleepTalkDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_SleepTalkDeclined
	msgbox MoveTutor_Text_SleepTalkWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SLEEP_TALK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_SleepTalkDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_SLEEP_TALK
	goto MoveTutor_EventScript_SleepTalkTaught
	end

MoveTutor_EventScript_SleepTalkDeclined::
	msgbox MoveTutor_Text_SleepTalkDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_SleepTalkTaught::
	msgbox MoveTutor_Text_SleepTalkTaught, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_SubstituteTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_SUBSTITUTE, MoveTutor_EventScript_SubstituteTaught
	msgbox MoveTutor_Text_SubstituteTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_SubstituteDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_SubstituteDeclined
	msgbox MoveTutor_Text_SubstituteWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SUBSTITUTE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_SubstituteDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_SUBSTITUTE
	goto MoveTutor_EventScript_SubstituteTaught
	end

MoveTutor_EventScript_SubstituteDeclined::
	msgbox MoveTutor_Text_SubstituteDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_SubstituteTaught::
	msgbox MoveTutor_Text_SubstituteTaught, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DynamicPunchTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_DYNAMICPUNCH, MoveTutor_EventScript_DynamicPunchTaught
	msgbox MoveTutor_Text_DynamicPunchTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_DynamicPunchDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_DynamicPunchDeclined
	msgbox MoveTutor_Text_DynamicPunchWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DYNAMIC_PUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_DynamicPunchDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_DYNAMICPUNCH
	goto MoveTutor_EventScript_DynamicPunchTaught
	end

MoveTutor_EventScript_DynamicPunchDeclined::
	msgbox MoveTutor_Text_DynamicPunchDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_DynamicPunchTaught::
	msgbox MoveTutor_Text_DynamicPunchTaught, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_DoubleEdgeTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_DOUBLE_EDGE, MoveTutor_EventScript_DoubleEdgeTaught
	msgbox MoveTutor_Text_DoubleEdgeTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_DoubleEdgeDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_DoubleEdgeDeclined
	msgbox MoveTutor_Text_DoubleEdgeWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DOUBLE_EDGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_DoubleEdgeDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_DOUBLE_EDGE
	goto MoveTutor_EventScript_DoubleEdgeTaught
	end

MoveTutor_EventScript_DoubleEdgeDeclined::
	msgbox MoveTutor_Text_DoubleEdgeDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_DoubleEdgeTaught::
	msgbox MoveTutor_Text_DoubleEdgeTaught, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_ExplosionTutor::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_EXPLOSION, MoveTutor_EventScript_ExplosionTaught
	msgbox MoveTutor_Text_ExplosionTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_ExplosionDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnce
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_ExplosionDeclined
	msgbox MoveTutor_Text_ExplosionWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_EXPLOSION
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExplosionDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_EXPLOSION
	goto MoveTutor_EventScript_ExplosionTaught
	end

MoveTutor_EventScript_ExplosionDeclined::
	msgbox MoveTutor_Text_ExplosionDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_ExplosionTaught::
	msgbox MoveTutor_Text_ExplosionTaught, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_NoCoralCrowns::
	msgbox MoveTutor_Text_NoCoralCrowns, MSGBOX_DEFAULT
	closemessage
	release
	end

MoveTutor_EventScript_NoGoldTooth::
	msgbox MoveTutor_Text_NoGoldTooth, MSGBOX_DEFAULT
	closemessage
	release
	end

ZotpyreInteriors_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_ZOTPYRE_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_FloralHealing
	case 1, MoveTutor_EventScript_Hearthwarm
	case 2, MoveTutor_EventScript_Roost
	case 3, MoveTutor_EventScript_Ingrain
	case 4, MoveTutor_EventScript_PainSplit
	case 5, MoveTutor_EventScript_Wish
	case 6, MoveTutor_EventScript_HealPulse
	case 7, MoveTutor_EventScript_AquaRing
	case 8, MoveTutor_EventScript_LifeDew
	case 9, MoveTutor_EventScript_SlackOff
	case 10, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_FloralHealing::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FLORAL_HEALING
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Hearthwarm::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HEARTHWARM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Roost::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ROOST
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Ingrain::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_INGRAIN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_PainSplit::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PAIN_SPLIT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Wish::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_WISH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_HealPulse::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HEAL_PULSE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_AquaRing::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AQUA_RING
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_LifeDew::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_LIFE_DEW
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SlackOff::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SLACK_OFF
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

ZotpyreInteriors_EventScript_MoveTutor2::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_ZOTPYRE_MOVE_TUTOR_2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Aromatherapy
	case 1, MoveTutor_EventScript_HealBell
	case 2, MoveTutor_EventScript_Safeguard
	case 3, MoveTutor_EventScript_MagicCoat
	case 4, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Aromatherapy::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AROMATHERAPY
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_HealBell::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HEAL_BELL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Safeguard::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SAFEGUARD
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_MagicCoat::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MAGIC_COAT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

ZotpyreInteriors_EventScript_MoveTutor3::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_ZOTPYRE_MOVE_TUTOR_3
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_LeechLife
	case 1, MoveTutor_EventScript_PollenPuff
	case 2, MoveTutor_EventScript_Paracharge
	case 3, MoveTutor_EventScript_GigaDrain
	case 4, MoveTutor_EventScript_VenomDrain
	case 5, MoveTutor_EventScript_DreamEater
	case 6, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_LeechLife::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_LEECH_LIFE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_PollenPuff::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_POLLEN_PUFF
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Paracharge::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PARABOLIC_CHARGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_GigaDrain::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GIGA_DRAIN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_VenomDrain::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_VENOM_DRAIN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_DreamEater::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DREAM_EATER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

ZotpyreInteriors_EventScript_MoveTutor4::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_ZOTPYRE_MOVE_TUTOR_4
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_FinalGambit
	case 1, MoveTutor_EventScript_Reversal
	case 2, MoveTutor_EventScript_Flail
	case 3, MoveTutor_EventScript_MiseryWail
	case 4, MoveTutor_EventScript_Substitute
	case 5, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_FinalGambit::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FINAL_GAMBIT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Reversal::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_REVERSAL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Flail::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FLAIL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_MiseryWail::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MISERY_WAIL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Substitute::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SUBSTITUTE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

OzoneInt_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_OZONE_INS_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Hail
	case 1, MoveTutor_EventScript_Blizzard
	case 2, MoveTutor_EventScript_Verglastrom
	case 3, MoveTutor_EventScript_AuroraVeil
	case 4, MoveTutor_EventScript_ColdMend
	case 5, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Hail::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HAIL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Blizzard::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BLIZZARD
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Verglastrom::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_VERGLASTROM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_AuroraVeil::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AURORA_VEIL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_ColdMend::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_COLD_MEND
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

OzoneInt_EventScript_MoveTutor2::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_OZONE_INS_MOVE_TUTOR_2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_RainDance
	case 1, MoveTutor_EventScript_Aquascade
	case 2, MoveTutor_EventScript_Hurricane
	case 3, MoveTutor_EventScript_Thunder
	case 4, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_RainDance::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_RAIN_DANCE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Aquascade::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AQUASCADE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Hurricane::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HURRICANE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Thunder::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_THUNDER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

OzoneInt_EventScript_MoveTutor3::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_OZONE_INS_MOVE_TUTOR_3
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Sandstorm
	case 1, MoveTutor_EventScript_DuneSlicer
	case 2, MoveTutor_EventScript_RazorBeam
	case 3, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Sandstorm::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SANDSTORM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_DuneSlicer::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DUNE_SLICER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_RazorBeam::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_RAZOR_BEAM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

OzoneInt_EventScript_MoveTutor4::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_OZONE_INS_MOVE_TUTOR_4
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_SunnyDay
	case 1, MoveTutor_EventScript_SolarBeam
	case 2, MoveTutor_EventScript_SolarBlade
	case 3, MoveTutor_EventScript_Synthesis
	case 4, MoveTutor_EventScript_SunBask
	case 5, MoveTutor_EventScript_Growth
	case 6, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_SunnyDay::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SUNNY_DAY
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SolarBeam::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SOLAR_BEAM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SolarBlade::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SOLAR_BLADE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Synthesis::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SYNTHESIS
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SunBask::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SUN_BASK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Growth::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GROWTH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

FortreeInteriors_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_FORTREE_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_ElectricTerrain
	case 1, MoveTutor_EventScript_RisingVoltage
	case 2, MoveTutor_EventScript_Charge
	case 3, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_ElectricTerrain::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ELECTRIC_TERRAIN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_RisingVoltage::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_RISING_VOLTAGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Charge::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CHARGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

FortreeInteriors_EventScript_MoveTutor2::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_FORTREE_MOVE_TUTOR_2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_GrassyTerrain
	case 1, MoveTutor_EventScript_GrassyGlide
	case 2, MoveTutor_EventScript_GrassCannon
	case 3, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_GrassyTerrain::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GRASSY_TERRAIN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_GrassyGlide::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GRASSY_GLIDE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_GrassCannon::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GRASS_CANNON
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

FortreeInteriors_EventScript_MoveTutor3::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_FORTREE_MOVE_TUTOR_3
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_MistyTerrain
	case 1, MoveTutor_EventScript_MistyExplosion
	case 2, MoveTutor_EventScript_AromaticMist
	case 3, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_MistyTerrain::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MISTY_TERRAIN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_MistyExplosion::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MISTY_EXPLOSION
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_AromaticMist::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AROMATIC_MIST
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

FortreeInteriors_EventScript_MoveTutor4::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_FORTREE_MOVE_TUTOR_4
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_PsychicTerrain
	case 1, MoveTutor_EventScript_ExpandingForce
	case 2, MoveTutor_EventScript_Kinesis
	case 3, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_PsychicTerrain::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PSYCHIC_TERRAIN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_ExpandingForce::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_EXPANDING_FORCE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Kinesis::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_KINESIS
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

FortreeInteriors_EventScript_MoveTutor5::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_FORTREE_MOVE_TUTOR_5
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_TerrainPulse
	case 1, MoveTutor_EventScript_TerrainSnap
	case 2, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_TerrainPulse::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TERRAIN_PULSE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_TerrainSnap::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TERRAIN_SNAP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

FortreeInteriors_EventScript_MoveTutor6::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_FORTREE_MOVE_TUTOR_6
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Tailwind
	case 1, MoveTutor_EventScript_AirCannon
	case 2, MoveTutor_EventScript_SharpGlide
	case 3, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Tailwind::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TAILWIND
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_AirCannon::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AIR_CANNON
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SharpGlide::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SHARP_GLIDE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

FortreeInteriors_EventScript_MoveTutor7::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_FORTREE_MOVE_TUTOR_7
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_CastleCrash
	case 1, MoveTutor_EventScript_Defog
	case 2, MoveTutor_EventScript_Demolisher
	case 3, MoveTutor_EventScript_IceSpinner
	case 4, MoveTutor_EventScript_SteelRoller
	case 5, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_CastleCrash::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CASTLE_CRASH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Defog::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DEFOG
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Demolisher::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DEMOLISHER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_IceSpinner::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ICE_SPINNER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SteelRoller::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_STEEL_ROLLER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

LavaridgeHouses_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_LAVARIDGE_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Brutalize
	case 1, MoveTutor_EventScript_DracoMeteor
	case 2, MoveTutor_EventScript_FleurCannon
	case 3, MoveTutor_EventScript_CloseCombat
	case 4, MoveTutor_EventScript_SuperPower
	case 5, MoveTutor_EventScript_Overheat
	case 6, MoveTutor_EventScript_LeafStorm
	case 7, MoveTutor_EventScript_HeadlongRush
	case 8, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Brutalize::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BRUTALIZE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_DracoMeteor::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DRACO_METEOR
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_FleurCannon::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FLEUR_CANNON
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_CloseCombat::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CLOSE_COMBAT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SuperPower::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SUPERPOWER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Overheat::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_OVERHEAT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_LeafStorm::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_LEAF_STORM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_HeadlongRush::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HEADLONG_RUSH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

NewMauvilleFloor1_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_NEW_MAUVILLE_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_UTurn
	case 1, MoveTutor_EventScript_HitNRun
	case 2, MoveTutor_EventScript_VoltSwitch
	case 3, MoveTutor_EventScript_GlacialShift
	case 4, MoveTutor_EventScript_AllySwitch
	case 5, MoveTutor_EventScript_PowerSwap
	case 6, MoveTutor_EventScript_GuardSwap
	case 7, MoveTutor_EventScript_SpeedSwap
	case 8, MoveTutor_EventScript_SkillSwap
	case 9, MoveTutor_EventScript_FlipTurn
	case 10, MoveTutor_EventScript_Maneuver
	case 11, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_UTurn::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_U_TURN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_HitNRun::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HIT_N_RUN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_VoltSwitch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_VOLT_SWITCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_GlacialShift::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GLACIAL_SHIFT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_AllySwitch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ALLY_SWITCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_PowerSwap::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_POWER_SWAP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_GuardSwap::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GUARD_SWAP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_SpeedSwap::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SPEED_SWAP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_SkillSwap::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SKILL_SWAP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_FlipTurn::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FLIP_TURN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_Maneuver::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MANEUVER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

NewMauvilleFloor1_EventScript_MoveTutor2::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_NEW_MAUVILLE_MOVE_TUTOR_2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Evaporate
	case 1, MoveTutor_EventScript_SnuffOut
	case 2, MoveTutor_EventScript_FreezeDry
	case 3, MoveTutor_EventScript_HeatSink
	case 4, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Evaporate::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_EVAPORATE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_SnuffOut::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SNUFF_OUT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_FreezeDry::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FREEZE_DRY
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_HeatSink::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HEAT_SINK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

NewMauvilleFloor1_EventScript_MoveTutor3::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_NEW_MAUVILLE_MOVE_TUTOR_3
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_ThunderPunch
	case 1, MoveTutor_EventScript_MachPunch
	case 2, MoveTutor_EventScript_FirePunch
	case 3, MoveTutor_EventScript_IcePunch
	case 4, MoveTutor_EventScript_BulletPunch
	case 5, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_ThunderPunch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_THUNDER_PUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_MachPunch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MACH_PUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_FirePunch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FIRE_PUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_IcePunch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ICE_PUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_BulletPunch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BULLET_PUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

NewMauvilleFloor1_EventScript_MoveTutor4::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_NEW_MAUVILLE_MOVE_TUTOR_4
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_XScissor
	case 1, MoveTutor_EventScript_NightSlash
	case 2, MoveTutor_EventScript_SacredSword
	case 3, MoveTutor_EventScript_AerialAce
	case 4, MoveTutor_EventScript_SoulCutter
	case 5, MoveTutor_EventScript_CrossPoison
	case 6, MoveTutor_EventScript_PsychoCut
	case 7, MoveTutor_EventScript_SilverEdge
	case 8, MoveTutor_EventScript_AquaCutter
	case 9, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_XScissor::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_X_SCISSOR
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_NightSlash::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_NIGHT_SLASH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_SacredSword::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SACRED_SWORD
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_AerialAce::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AERIAL_ACE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_SoulCutter::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SOUL_CUTTER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_CrossPoison::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CROSS_POISON
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_PsychoCut::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PSYCHO_CUT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_SilverEdge::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SILVER_EDGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_AquaCutter::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AQUA_CUTTER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

NewMauvilleFloor1_EventScript_MoveTutor5::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_NEW_MAUVILLE_MOVE_TUTOR_5
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_PinMissile
	case 1, MoveTutor_EventScript_BeatUp
	case 2, MoveTutor_EventScript_ScaleShot
	case 3, MoveTutor_EventScript_DoubleSlap
	case 4, MoveTutor_EventScript_TripleKick
	case 5, MoveTutor_EventScript_FuryAttack
	case 6, MoveTutor_EventScript_BulletSeed
	case 7, MoveTutor_EventScript_TripleAxel
	case 8, MoveTutor_EventScript_BarbBarrage
	case 9, MoveTutor_EventScript_CometPunch
	case 10, MoveTutor_EventScript_GemBlaster
	case 11, MoveTutor_EventScript_SpikeCannon
	case 12, MoveTutor_EventScript_Bubble
	case 13, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_PinMissile::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PIN_MISSILE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_BeatUp::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SCALE_SHOT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_ScaleShot::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SCALE_SHOT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_DoubleSlap::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DOUBLE_SLAP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_TripleKick::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TRIPLE_KICK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_FuryAttack::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FURY_ATTACK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_BulletSeed::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BULLET_SEED
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_TripleAxel::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TRIPLE_AXEL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_BarbBarrage::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BARB_BARRAGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_CometPunch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_COMET_PUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_GemBlaster::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GEM_BLASTER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_SpikeCannon::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SPIKE_CANNON
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_Bubble::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BUBBLE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

NewMauvilleFloor1_EventScript_MoveTutor6::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_NEW_MAUVILLE_MOVE_TUTOR_6
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_BugBite
	case 1, MoveTutor_EventScript_Crunch
	case 2, MoveTutor_EventScript_ThunderFang
	case 3, MoveTutor_EventScript_FireFang
	case 4, MoveTutor_EventScript_IceFang
	case 5, MoveTutor_EventScript_PsychicFangs
	case 6, MoveTutor_EventScript_JawLock
	case 7, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_BugBite::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BUG_BITE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_Crunch::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CRUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_ThunderFang::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_THUNDER_FANG
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_FireFang::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FIRE_FANG
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_IceFang::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ICE_FANG
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_PsychicFangs::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PSYCHIC_FANGS
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_JawLock::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_JAW_LOCK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

NewMauvilleFloor1_EventScript_MoveTutor7::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_NEW_MAUVILLE_MOVE_TUTOR_7
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Megahorn
	case 1, MoveTutor_EventScript_BoltBeak
	case 2, MoveTutor_EventScript_DrillPeck
	case 3, MoveTutor_EventScript_HornLeech
	case 4, MoveTutor_EventScript_DrillRun
	case 5, MoveTutor_EventScript_GlacialLance
	case 6, MoveTutor_EventScript_BreakLance
	case 7, MoveTutor_EventScript_PoisonJab
	case 8, MoveTutor_EventScript_Pinpoint
	case 9, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Megahorn::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MEGAHORN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_BoltBeak::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BOLT_BEAK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_DrillPeck::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DRILL_PECK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_HornLeech::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HORN_LEECH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_DrillRun::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DRILL_RUN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_GlacialLance::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GLACIAL_LANCE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_BreakLance::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BREAK_LANCE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_PoisonJab::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_POISON_JAB
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

MoveTutor_EventScript_Pinpoint::
	checkitem ITEM_GOLD_TOOTH, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoGoldTooth
	msgbox MoveTutor_Text_WillTakeYourGoldTooth, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PINPOINT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaughtGoldTooth
	end

DewfordInteriors_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_DEWFORD_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_PowerUpPunch
	case 1, MoveTutor_EventScript_FlameCharge
	case 2, MoveTutor_EventScript_Trailblaze
	case 3, MoveTutor_EventScript_RapidSpin
	case 4, MoveTutor_EventScript_PsyshieldBash
	case 5, MoveTutor_EventScript_MeteorBeam
	case 6, MoveTutor_EventScript_SteelWing
	case 7, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_PowerUpPunch::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_POWER_UP_PUNCH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_FlameCharge::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FLAME_CHARGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Trailblaze::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TRAILBLAZE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_RapidSpin::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_RAPID_SPIN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_PsyshieldBash::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PSYSHIELD_BASH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_MeteorBeam::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_METEOR_BEAM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SteelWing::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_STEEL_WING
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

DewfordInteriors_EventScript_MoveTutor2::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_DEWFORD_MOVE_TUTOR_2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_PowerTrip
	case 1, MoveTutor_EventScript_StoredPower
	case 2, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_PowerTrip::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_POWER_TRIP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_StoredPower::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_STORED_POWER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

RustboroInteriors_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_RUSTBORO_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Embargo
	case 1, MoveTutor_EventScript_Flatter
	case 2, MoveTutor_EventScript_Taunt
	case 3, MoveTutor_EventScript_Torment
	case 4, MoveTutor_EventScript_FairyLock
	case 5, MoveTutor_EventScript_SweetKiss
	case 6, MoveTutor_EventScript_ConfuseRay
	case 7, MoveTutor_EventScript_Nightmare
	case 8, MoveTutor_EventScript_TrickOrTreat
	case 9, MoveTutor_EventScript_ForestsCurse
	case 10, MoveTutor_EventScript_LeechSeed
	case 11, MoveTutor_EventScript_Attract
	case 12, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Embargo::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_EMBARGO
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Flatter::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TAUNT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Taunt::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TAUNT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Torment::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TORMENT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_FairyLock::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FAIRY_LOCK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SweetKiss::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SWEET_KISS
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_ConfuseRay::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CONFUSE_RAY
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Nightmare::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_NIGHTMARE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_TrickOrTreat::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TRICK_OR_TREAT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_ForestsCurse::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FORESTS_CURSE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_LeechSeed::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_LEECH_SEED
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Attract::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ATTRACT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

RustboroInteriors_EventScript_MoveTutor2::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_RUSTBORO_MOVE_TUTOR_2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Block
	case 1, MoveTutor_EventScript_Camouflage
	case 2, MoveTutor_EventScript_Encore
	case 3, MoveTutor_EventScript_Entrainment
	case 4, MoveTutor_EventScript_Foresight
	case 5, MoveTutor_EventScript_MeanLook
	case 6, MoveTutor_EventScript_OdorSleuth
	case 7, MoveTutor_EventScript_PerishSong
	case 8, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Block::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BLOCK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Camouflage::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CAMOUFLAGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Encore::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ENCORE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Entrainment::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ENTRAINMENT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Foresight::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FORESIGHT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_MeanLook::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MEAN_LOOK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_OdorSleuth::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ODOR_SLEUTH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_PerishSong::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PERISH_SONG
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

RustboroInteriors_EventScript_MoveTutor3::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_RUSTBORO_MOVE_TUTOR_3
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_ReflectType
	case 1, MoveTutor_EventScript_SimpleBeam
	case 2, MoveTutor_EventScript_Swagger
	case 3, MoveTutor_EventScript_TeeterDance
	case 4, MoveTutor_EventScript_Yawn
	case 5, MoveTutor_EventScript_GastroAcid
	case 6, MoveTutor_EventScript_HealBlock
	case 7, MoveTutor_EventScript_MagicPowder
	case 8, MoveTutor_EventScript_MiracleEye
	case 9, MoveTutor_EventScript_RolePlay
	case 10, MoveTutor_EventScript_Telekinesis
	case 11, MoveTutor_EventScript_Soak
	case 12, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_ReflectType::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_REFLECT_TYPE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SimpleBeam::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SIMPLE_BEAM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Swagger::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SWAGGER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_TeeterDance::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TEETER_DANCE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Yawn::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_YAWN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_GastroAcid::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GASTRO_ACID
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_HealBlock::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HEAL_BLOCK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_MagicPowder::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MAGIC_POWDER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_MiracleEye::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MIRACLE_EYE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_RolePlay::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ROLE_PLAY
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Telekinesis::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TELEKINESIS
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Soak::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SOAK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

OldaleInteriors_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_OLDALE_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Cut
	case 1, MoveTutor_EventScript_Surf
	case 2, MoveTutor_EventScript_Strength
	case 3, MoveTutor_EventScript_RockSmash
	case 4, MoveTutor_EventScript_Waterfall
	case 5, MoveTutor_EventScript_Dive
	case 6, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Cut::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CUT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Surf::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SURF
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Strength::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_STRENGTH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_RockSmash::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ROCK_SMASH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Waterfall::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_WATERFALL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Dive::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DIVE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

OldaleInteriors_EventScript_MoveTutor2::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_OLDALE_MOVE_TUTOR_2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Flash
	case 1, MoveTutor_EventScript_Fly
	case 2, MoveTutor_EventScript_RockClimb
	case 3, MoveTutor_EventScript_Whirlpool
	case 4, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Flash::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FLASH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Fly::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FLY
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_RockClimb::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_ROCK_CLIMB
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Whirlpool::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_WHIRLPOOL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

PetalburgInteriors_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_PETALBURG_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_Facade
	case 1, MoveTutor_EventScript_Frustration
	case 2, MoveTutor_EventScript_Return
	case 3, MoveTutor_EventScript_GigaImpact
	case 4, MoveTutor_EventScript_GrandSlam
	case 5, MoveTutor_EventScript_HyperBeam
	case 6, MoveTutor_EventScript_WorkUp
	case 7, MoveTutor_EventScript_Substitute
	case 8, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_Facade::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FACADE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Frustration::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FRUSTRATION
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_Return::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_RETURN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_GigaImpact::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GIGA_IMPACT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_GrandSlam::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_GRAND_SLAM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_HyperBeam::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HYPER_BEAM
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_WorkUp::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_WORK_UP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

LittlerootInteriors_EventScript_MoveTutor1::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_LITTLEROOT_MOVE_TUTOR_1
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_FrenzyPlant
	case 1, MoveTutor_EventScript_BlastBurn
	case 2, MoveTutor_EventScript_HydroCannon
	case 3, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_FrenzyPlant::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FRENZY_PLANT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_BlastBurn::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BLAST_BURN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_HydroCannon::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HYDRO_CANNON
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

LittlerootInteriors_EventScript_MoveTutor2::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_LITTLEROOT_MOVE_TUTOR_2
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_LeafBlade
	case 1, MoveTutor_EventScript_SpikyShield
	case 2, MoveTutor_EventScript_SpiritShackle
	case 3, MoveTutor_EventScript_DrumBeating
	case 4, MoveTutor_EventScript_TripleArrows
	case 5, MoveTutor_EventScript_FlowerTrick
	case 6, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_LeafBlade::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_LEAF_BLADE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SpikyShield::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SPIKY_SHIELD
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SpiritShackle::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SPIRIT_SHACKLE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_DrumBeating::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DRUM_BEATING
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_TripleArrows::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TRIPLE_ARROWS
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_FlowerTrick::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_FLOWER_TRICK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

LittlerootInteriors_EventScript_MoveTutor3::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_LITTLEROOT_MOVE_TUTOR_3
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_BlazeKick
	case 1, MoveTutor_EventScript_HeatCrash
	case 2, MoveTutor_EventScript_MysticalFire
	case 3, MoveTutor_EventScript_DarkestLariat
	case 4, MoveTutor_EventScript_PyroBall
	case 5, MoveTutor_EventScript_InfernalParade
	case 6, MoveTutor_EventScript_TorchSong
	case 7, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_BlazeKick::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_BLAZE_KICK
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_HeatCrash::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_HEAT_CRASH
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_MysticalFire::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MYSTICAL_FIRE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_DarkestLariat::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DARKEST_LARIAT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_PyroBall::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_PYRO_BALL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_InfernalParade::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_INFERNAL_PARADE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_TorchSong::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_TORCH_SONG
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

LittlerootInteriors_EventScript_MoveTutor4::
	lock
	faceplayer
	msgbox MoveTutor_Text_LearnMove, MSGBOX_DEFAULT
	setvar VAR_0x8004, SCROLL_MULTI_LITTLEROOT_MOVE_TUTOR_4
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, MoveTutor_EventScript_MuddyWater
	case 1, MoveTutor_EventScript_RazorShell
	case 2, MoveTutor_EventScript_WaterShuriken
	case 3, MoveTutor_EventScript_SparklingAria
	case 4, MoveTutor_EventScript_SnipeShot
	case 5, MoveTutor_EventScript_CeaselessEdge
	case 6, MoveTutor_EventScript_AquaStep
	case 7, MoveTutor_EventScript_ExitRules
	case MULTI_B_PRESSED, MoveTutor_EventScript_ExitRules
	end

MoveTutor_EventScript_MuddyWater::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_MUDDY_WATER
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_RazorShell::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_RAZOR_SHELL
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_WaterShuriken::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_WATER_SHURIKEN
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SparklingAria::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SPARKLING_ARIA
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_SnipeShot::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_SNIPE_SHOT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_CeaselessEdge::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_CEASELESS_EDGE
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_AquaStep::
	checkitem ITEM_CORAL_CROWN, 1
	goto_if_eq VAR_RESULT, FALSE, MoveTutor_EventScript_NoCoralCrowns
	msgbox MoveTutor_Text_WillTakeYourCoralCrown, MSGBOX_DEFAULT
	msgbox MoveTutor_Text_WhoWillLearnTheMove, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_AQUA_STEP
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_ExitRules
	goto MoveTutor_EventScript_MoveTaught
	end

MoveTutor_EventScript_ExitRules::
	release
	end

MoveTutor_EventScript_MoveTaught::
	removeitem ITEM_CORAL_CROWN, 1
	msgbox MoveTutor_Text_MoveTaught, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_MoveTaughtGoldTooth::
	removeitem ITEM_GOLD_TOOTH, 1
	msgbox MoveTutor_Text_MoveTaught, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_OpenPartyMenu::
	special ChooseMonForMoveTutor
	waitstate
	lock
	faceplayer
	return

MoveTutor_EventScript_CanOnlyBeLearnedOnce::
	msgbox MoveTutor_Text_ThisMoveCanOnlyBeLearnedOnce, MSGBOX_YESNO
	return
