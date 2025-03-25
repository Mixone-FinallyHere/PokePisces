ShoalCaveNewFloor1_MapScripts::
	.byte 0

ShoalCaveNewFloor1_EventScript_Ludi::
    trainerbattle_single TRAINER_P_LUDI, ShoalCaveNewFloor1_Text_LudiIntro, ShoalCaveNewFloor1_Text_LudiDefeated
    msgbox ShoalCaveNewFloor1_Text_LudiPostBattle, MSGBOX_AUTOCLOSE
    end

ShoalCaveNewFloor1_EventScript_Solaire::
    trainerbattle_single TRAINER_P_SOLAIRE, ShoalCaveNewFloor1_Text_SolaireIntro, ShoalCaveNewFloor1_Text_SolaireDefeated
    msgbox ShoalCaveNewFloor1_Text_SolairePostBattle, MSGBOX_AUTOCLOSE
    end

ShoalCaveNewFloor1_EventScript_Luna::
    trainerbattle_single TRAINER_P_LUNA, ShoalCaveNewFloor1_Text_LunaIntro, ShoalCaveNewFloor1_Text_LunaDefeated
    msgbox ShoalCaveNewFloor1_Text_LunaPostBattle, MSGBOX_AUTOCLOSE
    end

ShoalCaveNewFloor1_EventScript_Wu::
    trainerbattle_single TRAINER_P_WU, ShoalCaveNewFloor1_Text_WuIntro, ShoalCaveNewFloor1_Text_WuDefeated
    msgbox ShoalCaveNewFloor1_Text_WuPostBattle, MSGBOX_AUTOCLOSE
    end

ShoalCaveNewFloor1_EventScript_Tang::
    trainerbattle_single TRAINER_P_TANG, ShoalCaveNewFloor1_Text_TangIntro, ShoalCaveNewFloor1_Text_TangDefeated
    msgbox ShoalCaveNewFloor1_Text_TangPostBattle, MSGBOX_AUTOCLOSE
    end

ShoalCaveNewFloor1_Text_LudiIntro:
	.string "Just what IS that strange echoing\n"
	.string "noise I hear? Is it\l"
	.string "some sort of monster?$"

ShoalCaveNewFloor1_Text_LudiDefeated:
	.string "That's ludicrous!$"

ShoalCaveNewFloor1_Text_LudiPostBattle:
	.string "It's so scary sounding in here!\n"
	.string "I should file a noise complaint.$"

ShoalCaveNewFloor1_Text_SolaireIntro:
	.string "Stay back! My... my hand!\n"
	.string "Grrrrraaaaaghhhhh! I can't\l"
	.string "hold it back!$"

ShoalCaveNewFloor1_Text_SolaireDefeated:
	.string "...Phew. It has calmed down.\p"
	.string "Are you also... an Astroplaner?$"

ShoalCaveNewFloor1_Text_SolairePostBattle:
	.string "You see, I'm The Black Hand of\n"
	.string "the Misted Plains. On my right\l"
	.string "hand, I've sealed the greater evil\l"
	.string "Yurlungr, whom I've engaged in\l"
	.string "a battle of life or death with for\l"
	.string "centuries. Due to its immense power, my\l"
	.string "right hand often loses control and\l"
	.string "leaks out the evil energies Yurlungr\l"
	.string "emits. Only a fellow Astralplaner can\l"
	.string "get it under control. You, unknown\l"
	.string "Astralplaner, you know when the\l"
	.string "next invasion will come won't you?\l"
	.string "I sense it in you...\p"
	.string "(He continues to ramble on.)$"

ShoalCaveNewFloor1_Text_LunaIntro:
	.string "Wish my partner would take\n"
	.string "his ESP more seriously.$"

ShoalCaveNewFloor1_Text_LunaDefeated:
	.string "Here he goes again...$"

ShoalCaveNewFloor1_Text_LunaPostBattle:
	.string "You wouldn't happen to have\n"
	.string "the number of any psychologists\l"
	.string "on hand, do you?$"

ShoalCaveNewFloor1_Text_WuIntro:
	.string "Back in my day, trainers would\n"
	.string "train THEMSELVES alongside\l"
	.string "their Pokemon!$"

ShoalCaveNewFloor1_Text_WuDefeated:
	.string "Hmm. How peculiar.$"

ShoalCaveNewFloor1_Text_WuPostBattle:
	.string "You train your Pokemon well,\n"
	.string "child. But remember, there is\l"
	.string "always room to improve!$"

ShoalCaveNewFloor1_Text_TangIntro:
	.string "When I was your age, I had\n"
	.string "beaten the gym challenge already!$"

ShoalCaveNewFloor1_Text_TangDefeated:
	.string "You make me hopeful\n"
	.string "for the next generation.$"

ShoalCaveNewFloor1_Text_TangPostBattle:
	.string "Of course, in my time, the\n"
	.string "gym challenge was much different...$"
