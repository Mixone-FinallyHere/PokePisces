PendingDev_MapScripts::
	.byte 0

PendingDev_EventScript_Gunfried::
    trainerbattle_single TRAINER_P_GUNFRIED, PendingDev_Text_GunfriedIntro, PendingDev_Text_GunfriedDefeated
    msgbox PendingDev_Text_GunfriedPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_EventScript_Rex::
    trainerbattle_single TRAINER_P_REX, PendingDev_Text_RexIntro, PendingDev_Text_RexDefeated
    msgbox PendingDev_Text_RexPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_EventScript_Guinda::
    trainerbattle_single TRAINER_P_GUINDA, PendingDev_Text_GuindaIntro, PendingDev_Text_GuindaDefeated
    msgbox PendingDev_Text_GuindaPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_EventScript_Gunder::
    trainerbattle_single TRAINER_P_GUNDER, PendingDev_Text_GunderIntro, PendingDev_Text_GunderDefeated
    msgbox PendingDev_Text_GunderPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_EventScript_Gunhild::
    trainerbattle_single TRAINER_P_GUNHILD, PendingDev_Text_GunhildIntro, PendingDev_Text_GunhildDefeated
    msgbox PendingDev_Text_GunhildPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_EventScript_Elon::
    trainerbattle_single TRAINER_P_ELON, PendingDev_Text_ElonIntro, PendingDev_Text_ElonDefeated
    msgbox PendingDev_Text_ElonPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_EventScript_Lilith::
    trainerbattle_single TRAINER_P_LILITH, PendingDev_Text_LilithIntro, PendingDev_Text_LilithDefeated
    msgbox PendingDev_Text_LilithPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_EventScript_SodAndSandy::
    trainerbattle_double TRAINER_P_SOD_AND_SANDY, PendingDev_Text_SodAndSandyIntro, PendingDev_Text_SodAndSandyDefeated, PendingDev_Text_SodAndSandyNeedTwoMons
    msgbox PendingDev_Text_SodAndSandyPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_EventScript_Pendragon::
    trainerbattle_single TRAINER_P_PENDRAGON, PendingDev_Text_PendragonIntro, PendingDev_Text_PendragonDefeated
    msgbox PendingDev_Text_PendragonPostBattle, MSGBOX_AUTOCLOSE
    end

PendingDev_Text_GunfriedIntro:
	.string "Oooooh? You're shneaking around\n"
	.string "the shrubbery too?\l"
	.string "Well, there ishn't room for the\l"
	.string "both of us...!$"

PendingDev_Text_GunfriedDefeated:
	.string "This shucks!$"

PendingDev_Text_GunfriedPostBattle:
	.string "I've been looking hard\n"
	.string "for a Fooltage... I think they're\l"
	.string "shcarce here...$"

PendingDev_Text_RexIntro:
	.string "My team is PART-ICULARY legendary!\n"
	.string "Try not to bust out crying when\l"
	.string "you crumble before them!\l"
	.string "Mwahahaha!$"

PendingDev_Text_RexDefeated:
	.string "I couldn't just spam my legendary\n"
	.string "Pokemon and win!!! What is going\l"
	.string "ON here!!???$"

PendingDev_Text_RexPostBattle:
	.string "Leave me be, while I figure out\n"
	.string "where the heck I went wrong!$"

PendingDev_Text_GuindaIntro:
	.string "Those jocks and bullies at school\n"
	.string "keep telling me Capybara is\l"
	.string "gross and dumb looking...\l"
	.string "they just don't understand!$"

PendingDev_Text_GuindaDefeated:
	.string "Don't worry, Capybara and\n"
	.string "Abarbinash... i-it wasn't\l"
	.string "your guys' fault...$"

PendingDev_Text_GuindaPostBattle:
	.string "I'll never stop loving\n"
	.string "these Pokemon! E-Ever!$"

PendingDev_Text_GunderIntro:
	.string "Abarbinash is just about the\n"
	.string "most hideous, terrible looking\l"
	.string "Pokemon I have ever seen...\l"
	.string "but, my mom gave me it, so...$"

PendingDev_Text_GunderDefeated:
	.string "My heart wasn't in that one.$"

PendingDev_Text_GunderPostBattle:
	.string "Think my mom will notice if I\n"
	.string "trade for a Walrust and paint\l"
	.string "it red?$"

PendingDev_Text_GunhildIntro:
	.string "People k-keep accusing me of\n"
	.string "always having s-sticky hands...\p"
	.string "(Her hands are visibly sticky.)\p"
	.string "You too!?$"

PendingDev_Text_GunhildDefeated:
	.string "I k-kept getting stuck!$"

PendingDev_Text_GunhildPostBattle:
	.string "I won't stop playing with glue\n"
	.string "and eating it after... it'd\l"
	.string "be l-like giving up breathing.$"

PendingDev_Text_ElonIntro:
	.string "A sparring match between trainers,\n"
	.string "hmm? I suppose a little extra cash\l"
	.string "on hand never hurts...$"

PendingDev_Text_ElonDefeated:
	.string "What!? ...My money! No!$"

PendingDev_Text_ElonPostBattle:
	.string "I cannot believe I had to cough\n"
	.string "up cash to your coffers...!\l"
	.string "No matter. That was simply a\l"
	.string "pittance compared to my entire,\l"
	.string "well-stocked, portfolio!$"

PendingDev_Text_LilithIntro:
	.string "If you beat me, I will buy up\n"
	.string "one of these open land plots!$"

PendingDev_Text_LilithDefeated:
	.string "I just wanted an excuse to do it!$"

PendingDev_Text_LilithPostBattle:
	.string "What should I turn it into, I\n"
	.string "wonder... a fourth home?\l"
	.string "A knick-knack shop? A haunted\l"
	.string "house attraction?$"

PendingDev_Text_SodAndSandyIntro:
	.string "SOD: We're preparing the land here\n"
	.string "for the new buildings.\l"
	.string "SANDY: Hey, the ground there just\l"
	.string "got paved! Don't mess it up!$"

PendingDev_Text_SodAndSandyDefeated:
	.string "SOD: All that trampling actually\n"
	.string "levelled out the terrain well!\l"
	.string "SANDY: Thanks for the help.$"

PendingDev_Text_SodAndSandyPostBattle:
	.string "SOD: It was a shame to lose a good\n"
	.string "amount of trees in this area.\l"
	.string "SANDY: If I had things my way, this\l"
	.string "route would stay more narural.$"

PendingDev_Text_SodAndSandyNeedTwoMons:
	.string "(They seem to be busy leveling\n"
	.string "the terrain around them...)$"

PendingDev_Text_PendragonIntro:
	.string "I got da scoop! I got da scoop!\n"
	.string "Come lissen!\p"
	.string "GMH was eyin' up this acre for\n"
	.string "years! Now they've finally\l"
	.string "got hold'a it, they're turnin'\l"
	.string "this into an extension of the\l"
	.string "Sea Mauville city!\p"
	.string "Locals in Littleroot are furious!\n"
	.string "I'll be reaching out to 'em\l"
	.string "for further comment.\p"
	.string "...\p"
	.string "Oh, right. We supposta battle?$"

PendingDev_Text_PendragonDefeated:
	.string "Front page story:\n"
	.string "my team is ASS!$"

PendingDev_Text_PendragonPostBattle:
	.string "Hey, so, if ya know anybody\n"
	.string "in Littleroot that might care\l"
	.string "about this whole thing, tell\l"
	.string "'em to hit me up.$"
