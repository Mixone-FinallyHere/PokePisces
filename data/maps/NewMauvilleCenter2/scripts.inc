.set LOCALID_MOVE_RELEARNER, 1

NewMauvilleCenter2_MapScripts::
	.byte 0

NewMauvilleCenter2_EventScript_MoveRelearner::
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, NewMauvilleCenter2_EventScript_AskTeachMove
	msgbox NewMauvilleCenter2_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto NewMauvilleCenter2_EventScript_AskTeachMove
	end

NewMauvilleCenter2_EventScript_AskTeachMove::
	checkitem ITEM_CARROT_HORN
	goto_if_eq VAR_RESULT, FALSE, NewMauvilleCenter2_EventScript_ComeBackWithHeartScale
	msgbox NewMauvilleCenter2_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, NewMauvilleCenter2_EventScript_ComeBackWithHeartScale
	goto NewMauvilleCenter2_EventScript_ChooseMon
	end

NewMauvilleCenter2_EventScript_ChooseMon::
	msgbox NewMauvilleCenter2_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, NewMauvilleCenter2_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, NewMauvilleCenter2_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, NewMauvilleCenter2_EventScript_NoMoveToTeachMon
	goto NewMauvilleCenter2_EventScript_ChooseMove
	end

NewMauvilleCenter2_EventScript_ChooseMove::
	msgbox NewMauvilleCenter2_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, NewMauvilleCenter2_EventScript_ChooseMon
	msgbox NewMauvilleCenter2_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_CARROT_HORN
	goto NewMauvilleCenter2_EventScript_ComeBackWithHeartScale
	end

NewMauvilleCenter2_EventScript_NoMoveToTeachMon::
	msgbox NewMauvilleCenter2_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto NewMauvilleCenter2_EventScript_ChooseMon
	end

NewMauvilleCenter2_EventScript_CantTeachEgg::
	msgbox NewMauvilleCenter2_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto NewMauvilleCenter2_EventScript_ChooseMon
	end

NewMauvilleCenter2_EventScript_ComeBackWithHeartScale::
	msgbox NewMauvilleCenter2_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	end

NewMauvilleCenter2_Text_ImTheMoveTutor:
	.string "I am THE Move Tutor.\n"
	.string "Unlike all those other tutors who\l"
	.string "can only teach a certain pool\l"
	.string "of techniques, I'm a step above.\p"
	.string "I know all the moves that Pokemon\n"
	.string "learn... yes, every Pokemon.\l"
	.string "They all have special moves\l"
	.string "deep in their memories that\l"
	.string "can only be unlocked with\l"
	.string "the correct stimuli.\p"
	.string "I just so happen to know exactly\n"
	.string "how to stimulate their brains!\l"
	.string "I, err... just need...\l"
	.string "a sharp object...\p"
	.string "Like... a Carrot Horn! Give me one,\n"
	.string "and I'll teach one special\l"
	.string "move in exchange.$"

NewMauvilleCenter2_Text_ThatsAHeartScaleWantMeToTeachMove:
	.string "Ah! That's it! A Carrot Horn!\n"
	.string "Alright then, let's begin.$"

NewMauvilleCenter2_Text_TutorWhichMon:
	.string "Which Pokémon needs tutoring?$"

NewMauvilleCenter2_Text_TeachWhichMove:
	.string "Which move should I teach?$"

NewMauvilleCenter2_Text_DontHaveMoveToTeachPokemon:
	.string "Sorry…\p"
	.string "It doesn't appear as if I have any move\n"
	.string "I can teach that Pokémon.$"

NewMauvilleCenter2_Text_HandedOverHeartScale:
	.string "{PLAYER} handed over one Carrot Horn\n"
	.string "in exchange.$"

NewMauvilleCenter2_Text_ComeBackWithHeartScale:
	.string "If your Pokémon need to learn a move,\n"
	.string "come back with a Carrot Horn.$"

NewMauvilleCenter2_Text_CantTeachEgg:
	.string "Hunh? There isn't a single move that\n"
	.string "I can teach an EGG.$"
