MossdeepInteriors_MapScripts::
	.byte 0

MossdeepInteriors_EventScript_ArtTeacher::
	lock
	faceplayer
	checkitem ITEM_TRIUMPH_STAR
	goto_if_eq VAR_RESULT, TRUE, MossdeepInteriors_EventScript_AlreadyGaveTriumphStar
	goto_if_set FLAG_JUDGED_PAINTING, MossdeepInteriors_EventScript_GiveTriumphStar
	goto_if_set FLAG_WILL_JUDGE_PAINTING, MossdeepInteriors_EventScript_GoToLilycove
	msgbox MossdeepInteriors_Text_DoAPaperForMe, MSGBOX_DEFAULT
	setflag FLAG_WILL_JUDGE_PAINTING
	closemessage
	release
	end

MossdeepInteriors_EventScript_GoToLilycove::
	msgbox MossdeepInteriors_Text_GoToLilycove, MSGBOX_AUTOCLOSE
	release
	end

MossdeepInteriors_EventScript_GiveTriumphStar::
	msgbox MossdeepInteriors_Text_HaveATriumphStar, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_TRIUMPH_STAR
	closemessage
	release
	end

MossdeepInteriors_EventScript_AlreadyGaveTriumphStar::
	msgbox MossdeepInteriors_Text_AlreadyGaveTriumphStar, MSGBOX_AUTOCLOSE
	release
	end

MossdeepInteriors_Text_DoAPaperForMe:
	.string "Oh, what is an art teacher to do\n"
	.string "during the off season for school...\p"
	.string "Eureka! I will student-ify this\n"
	.string "child that has infiltrated my home!\p"
	.string "You are hearing me! I have\n"
	.string "an insatiable urge... to grade!\l"
	.string "A paper! Specifically, a paper\l"
	.string "dissecting a work of art!\p"
	.string "Write up a critique for me...\n"
	.string "and I shall grade it!$"

MossdeepInteriors_Text_GoToLilycove:
	.string "Where can you find a work of art?\n"
	.string "Well, some might say, all around us.\l"
	.string "But a not-annoying answer should\l"
	.string "be the Lilycove Museum.\l"
	.string "The artist Phillipe hangs up\l"
	.string "his paintings there.$"

MossdeepInteriors_Text_HaveATriumphStar:
	.string "Ah, you have brought to me\n"
	.string "your carefully crafted critique!\p"
	.string "...\p"
	.string "\n"
	.string "... ...\p"
	.string "\n"
	.string "...Erm, hmm...\p"
	.string "...How should I say this?\n"
	.string "This paper, well...\l"
	.string "Pay more attention in grammar\l"
	.string "classes next year, is all I'll say.\p"
	.string "(Your paper was returned to you\n"
	.string "with something attached...)$"

MossdeepInteriors_Text_AlreadyGaveTriumphStar:
	.string "Hmm? What do you mean, that tacky\n"
	.string "gold star I stuck onto your essay\l"
	.string "gives the Ledian family\l"
	.string "special stat boosts?\p"
	.string "I, erm, kind of want that back?\n$"
