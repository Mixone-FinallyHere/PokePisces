ScuttillInteriors_MapScripts::
	.byte 0

ScuttillInteriors_EventScript_BurningABranch::
	lock
	faceplayer
	msgbox ScuttillInteriors_Text_WhenYouBurnJustRight, MSGBOX_DEFAULT
	checkitem ITEM_BURNT_BRANCH
	goto_if_eq VAR_RESULT, TRUE, ScuttillInteriors_EventScript_AlreadyGaveBurntBranch
	checkitem ITEM_WEIRD_STICK, 5
	goto_if_eq VAR_RESULT, FALSE, ScuttillInteriors_EventScript_GetMoreSticks
	msgbox ScuttillInteriors_Text_TakeBurningBranch, MSGBOX_DEFAULT
	removeitem ITEM_WEIRD_STICK, 5
	giveitem ITEM_BURNT_BRANCH
	msgbox ScuttillInteriors_Text_IHearAMonEvolves, MSGBOX_DEFAULT
	closemessage
	release
	end

ScuttillInteriors_EventScript_GetMoreSticks::
	msgbox ScuttillInteriors_Text_GetMoreSticks, MSGBOX_AUTOCLOSE
	release
	end

ScuttillInteriors_EventScript_AlreadyGaveBurntBranch::
	msgbox ScuttillInteriors_Text_AlreadyGaveBurntBranch, MSGBOX_AUTOCLOSE
	release
	end

ScuttillInteriors_Text_WhenYouBurnJustRight:
	.string "I like to get a little fancy\n"
	.string "when charcoal painting. Lots\l"
	.string "of artists use those pre-made\l"
	.string "charcoal pencils. Not me!\l"
	.string "I like to hand-burn a stick to use.\l"
	.string "It makes it feel way more authentic!$"

ScuttillInteriors_Text_GetMoreSticks:
	.string "I can make one for you if\n"
	.string "you're interested. I would just\l"
	.string "need a stick to burn...\l"
	.string "and a few extras as a payment.\l"
	.string "Bring me 5 sticks, and I'll\l"
	.string "make the perfect charred one!$"

ScuttillInteriors_Text_TakeBurningBranch:
	.string "Oh, you have enough sticks\n"
	.string "to pay me to make one, eh?\l"
	.string "Well, I am more than happy\l"
	.string "to oblige!\p"
	.string "Let me just take those 5 sticks...\p"
	.string "...\p"
	.string "And... there! Watch your fingers,\n"
	.string "it's pretty hot!$"

ScuttillInteriors_Text_IHearAMonEvolves:
	.string "You can use that Burnt Branch\n"
	.string "for drawing, but I also hear that\l"
	.string "some trainers use them for battling.\p"
	.string "There is a particular Grass type\n"
	.string "Pokemon that has an affinity for it!$"

ScuttillInteriors_Text_AlreadyGaveBurntBranch:
	.string "If you manage to make some cool\n"
	.string "art with that charred stick,\l"
	.string "I'd love to see it! I make a lot\l"
	.string "of that kind of art myself.$"
