FieryPath_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FieryPath_OnTransition
	.byte 0

FieryPath_OnTransition:
	call_if_unset FLAG_LANDMARK_FIERY_PATH, FieryPath_EventScript_MoveScottToFallarbor
	setflag FLAG_LANDMARK_FIERY_PATH
	end

FieryPath_EventScript_MoveScottToFallarbor::
	setflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	clearflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	return

FieryPath_EventScript_Cass::
    trainerbattle_single TRAINER_P_CASS, FieryPath_Text_CassIntro, FieryPath_Text_CassDefeated
    msgbox FieryPath_Text_CassPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Sandy::
    trainerbattle_single TRAINER_P_SANDY, FieryPath_Text_SandyIntro, FieryPath_Text_SandyDefeated
    msgbox FieryPath_Text_SandyPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Jan::
    trainerbattle_single TRAINER_P_JAN, FieryPath_Text_JanIntro, FieryPath_Text_JanDefeated
    msgbox FieryPath_Text_JanPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Catt::
    trainerbattle_single TRAINER_P_CATHY, FieryPath_Text_CattIntro, FieryPath_Text_CattDefeated
    msgbox FieryPath_Text_CattPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Celia::
    trainerbattle_single TRAINER_P_CELIA, FieryPath_Text_CeliaIntro, FieryPath_Text_CeliaDefeated
    msgbox FieryPath_Text_CeliaPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_REDACTED::
    trainerbattle_single TRAINER_P_REDACTED, FieryPath_Text_REDACTEDIntro, FieryPath_Text_REDACTEDDefeated
    msgbox FieryPath_Text_REDACTEDPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Dimitri::
    trainerbattle_single TRAINER_P_DIMITRI, FieryPath_Text_DimitriIntro, FieryPath_Text_DimitriDefeated
    msgbox FieryPath_Text_DimitriPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_CliffAndIssa::
    trainerbattle_double TRAINER_P_CLIFF_AND_ISSA, FieryPath_Text_CliffAndIssaIntro, FieryPath_Text_CliffAndIssaDefeated, FieryPath_Text_CliffAndIssaNeedTwoMons
    msgbox FieryPath_Text_CliffAndIssaPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Gerode::
    trainerbattle_single TRAINER_P_GERODE, FieryPath_Text_GerodeIntro, FieryPath_Text_GerodeDefeated
    msgbox FieryPath_Text_GerodePostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Mezra::
    trainerbattle_single TRAINER_P_MEZRA, FieryPath_Text_MezraIntro, FieryPath_Text_MezraDefeated
    msgbox FieryPath_Text_MezraPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Lane::
    trainerbattle_single TRAINER_P_LANE, FieryPath_Text_LaneIntro, FieryPath_Text_LaneDefeated
    msgbox FieryPath_Text_LanePostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Bonnie::
    trainerbattle_single TRAINER_P_BONNIE, FieryPath_Text_BonnieIntro, FieryPath_Text_BonnieDefeated
    msgbox FieryPath_Text_BonniePostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Hedon::
    trainerbattle_single TRAINER_P_HEDON, FieryPath_Text_HedonIntro, FieryPath_Text_HedonDefeated
    msgbox FieryPath_Text_HedonPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Rye::
    trainerbattle_single TRAINER_P_RYE, FieryPath_Text_RyeIntro, FieryPath_Text_RyeDefeated
    msgbox FieryPath_Text_RyePostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_Ingrid::
    trainerbattle_single TRAINER_P_INGRID, FieryPath_Text_IngridIntro, FieryPath_Text_IngridDefeated
    msgbox FieryPath_Text_IngridPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_BlaiseAndMar::
    trainerbattle_double TRAINER_P_BLAISE_AND_MAR, FieryPath_Text_BlaiseAndMarIntro, FieryPath_Text_BlaiseAndMarDefeated, FieryPath_Text_BlaiseAndMarNeedTwoMons
    msgbox FieryPath_Text_BlaiseAndMarPostBattle, MSGBOX_AUTOCLOSE
    end

FieryPath_EventScript_MasonriedSign::
	msgbox FieryPath_Text_MasonriedSign, MSGBOX_SIGN
	end

FieryPath_EventScript_FallarborSign::
	msgbox FieryPath_Text_FallarborSign, MSGBOX_SIGN
	end

FieryPath_EventScript_LavaridgeSign::
	msgbox FieryPath_Text_LavaridgeSign, MSGBOX_SIGN
	end

FieryPath_Text_MasonriedSign::
	.string "Masonried Hike Exit$"

FieryPath_Text_FallarborSign:
	.string "Fallarbor Town Exit$"

FieryPath_Text_LavaridgeSign:
	.string "Lavaridge Town Exit$"

FieryPath_Text_CassIntro:
	.string "Money is but a number.\n"
	.string "If you beat me, I will gladly\l"
	.string "give you a lump sum.$"

FieryPath_Text_CassDefeated:
	.string "As promised!$"

FieryPath_Text_CassPostBattle:
	.string "Once you've set up enough sources\n"
	.string "of passive income like me, it\l"
	.string "becomes impossible to be poor.$"

FieryPath_Text_SandyIntro:
	.string "... You remind me of someone I battled a\n"
	.string "long time ago...$"

FieryPath_Text_SandyDefeated:
	.string "Yep... I lost to them, too...$"

FieryPath_Text_SandyPostBattle:
	.string "Right, I remember now...\p"
	.string "Back when Maxie was trying to awaken\n"
	.string "Groudon, I tried to stop them and we\l"
	.string "ended up losing.\p"
	.string "Uh, what a blast from the past!$"

FieryPath_Text_JanIntro:
	.string "I'm a janitor! I do it for free!$"

FieryPath_Text_JanDefeated:
	.string "Maybe I should demand a pay raise...$"

FieryPath_Text_JanPostBattle:
	.string "I take my job very seriously.$"

FieryPath_Text_CattIntro:
	.string "You will serve as a springboard\n"
	.string "for my ambition!$"

FieryPath_Text_CattDefeated:
	.string "Me?! Lose?! Impossible!$"

FieryPath_Text_CattPostBattle:
	.string "In the end I only served as a\n"
	.string "springboard for your own\l"
	.string "ambitions, how humiliating.$"

FieryPath_Text_CeliaIntro:
	.string "I'm totally lost in this place...\n"
	.string "Little help?$"

FieryPath_Text_CeliaDefeated:
	.string "I must be stupid or something...$"

FieryPath_Text_CeliaPostBattle:
	.string "On second thought...\n"
	.string "I think I'll just stay here.$"

FieryPath_Text_REDACTEDIntro:
	.string "It's a secret to everybody.$"

FieryPath_Text_REDACTEDDefeated:
	.string "(DATA EXPUNGED)$"

FieryPath_Text_REDACTEDPostBattle:
	.string "This speech intentionally left blank.$"

FieryPath_Text_DimitriIntro:
	.string "Hope you saved room for\n"
	.string "some cool treats!$"

FieryPath_Text_DimitriDefeated:
	.string "That battle was a treat\n"
	.string "in and of itself!$"

FieryPath_Text_DimitriPostBattle:
	.string "Look out for a grumpy ol'\n"
	.string "vendor in Crimney Climb.\l"
	.string "He's a bit of a weenie.$"

FieryPath_Text_CliffAndIssaIntro:
	.string "CLIFF: Hey kid, why ya lookin'\n"
	.string "       at me that way!?\p"
	.string "ISSA: Do you always have to act\n"
	.string "      like this...?$"

FieryPath_Text_CliffAndIssaDefeated:
	.string "ISSA: We lost... because of YOU!\n"
	.string "  You, and your pride, and your ego!\l"
	.string "CLIFF: We had a good thing goin'\l"
	.string "  until you got in my way!$"

FieryPath_Text_CliffAndIssaPostBattle:
	.string "CLIFF: Ya itchin' for another battle?\n"
	.string "ISSA: You can't ever take a break,\l"
	.string "      can you?$"

FieryPath_Text_CliffAndIssaNeedTwoMons:
	.string "CLIFF: This kid's so weak and puny, they\n"
	.string "       can't even battle us!\p"
	.string "ISSA: Or maybe you're so weak they won't\n"
	.string "      bring themselves to beat you?$"

FieryPath_Text_GerodeIntro:
	.string "The true greatest force of nature?\n"
	.string "EROSION! ...Dragons are number 2!$"

FieryPath_Text_GerodeDefeated:
	.string "You're number 1 AND 2...$"

FieryPath_Text_GerodePostBattle:
	.string "Number 3... the third greatest force\n"
	.string "of nature... is, um...\l"
	.string "Angry mom?$"

FieryPath_Text_MezraIntro:
	.string "Come, gods of power, gods of sight!\n"
	.string "Show me the awful things\l"
	.string "occuring here tonight!\p"
	.string "Sacred dance, symbol of my clan,\n"
	.string "please show us all you could-\l"
	.string "I MEAN, CAN! Show us all you CAN!\p"
	.string "Show us this... {PLAYER}!$"

FieryPath_Text_MezraDefeated:
	.string "Ka ha ha! My predictions\n"
	.string "never fail me!$"

FieryPath_Text_MezraPostBattle:
	.string "Call upon the gods whenever\n"
	.string "you are in need of help...$"

FieryPath_Text_LaneIntro:
	.string "Something here smells funny...\n"
	.string "Oh, it's just you!$"

FieryPath_Text_LaneDefeated:
	.string "Don't forget to flush!$"

FieryPath_Text_LanePostBattle:
	.string "(sniff, sniff) Wait, that smell isn't\n"
	.string "you. I must be plumb crazy...$"

FieryPath_Text_BonnieIntro:
	.string "Swing your arms from side to side!$"

FieryPath_Text_BonnieDefeated:
	.string "....Juuust liiike thaaat!$"

FieryPath_Text_BonniePostBattle:
	.string "Come on, it's time to go!$"

FieryPath_Text_HedonIntro:
	.string "I'll destroy you like a Kaiju!$"

FieryPath_Text_HedonDefeated:
	.string "Lost to an unlikely source...\n"
	.string "just like a Kaiju...$"

FieryPath_Text_HedonPostBattle:
	.string "If i could be a towering monster\n"
	.string "instead of a human, I would!$"

FieryPath_Text_RyeIntro:
	.string "A balanced team is like\n"
	.string "a balanced breakfast!\p"
	.string "If you have it, you can\n"
	.string "take on anything!$"

FieryPath_Text_RyeDefeated:
	.string "Done like dinner!$"

FieryPath_Text_RyePostBattle:
	.string "My Spiritoast cooks my\n"
	.string "breakfast for me! It's\l"
	.string "really good at it!$"

FieryPath_Text_IngridIntro:
	.string "Time to wake up\n"
	.string "and smell the bacon, sleepy!$"

FieryPath_Text_IngridDefeated:
	.string "Ack! You were wide awake!$"

FieryPath_Text_IngridPostBattle:
	.string "Keep your energy up, trainer.\n"
	.string "Lest you lose your alertness.$"

FieryPath_Text_BlaiseAndMarIntro:
	.string "BLAISE: I'm a weather expert, you know.\n"
	.string "MAR: So am I! Don't discount me!$"

FieryPath_Text_BlaiseAndMarDefeated:
	.string "BLAISE: Why am I all wet?\n"
	.string "MAR: What happened?$"

FieryPath_Text_BlaiseAndMarPostBattle:
	.string "MAR: Well, now I'm all dried up...\n"
	.string "BLAISE: You doused my chances\l"
	.string "        chances of winning!$"

FieryPath_Text_BlaiseAndMarNeedTwoMons:
	.string "BLAISE: We should double battle for\n"
	.string "        a change.\p"
	.string "MAR: That sounds good to me...$"
