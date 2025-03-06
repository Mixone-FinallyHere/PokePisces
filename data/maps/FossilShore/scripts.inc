FossilShore_MapScripts::
	.byte 0

FossilShore_EventScript_Shellylouh::
	lock
	faceplayer
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_2, FossilShore_EventScript_SeekOutOtherShelly
	checkitem ITEM_PEARL_STRING
	goto_if_eq VAR_RESULT, TRUE, FossilShore_EventScript_GiveReward
	msgbox FossilShore_Text_ShellRiddle, MSGBOX_AUTOCLOSE
	release
	end

FossilShore_EventScript_GiveReward::
	msgbox FossilShore_Text_HereIsReward, MSGBOX_DEFAULT
	removeitem ITEM_PEARL_STRING
	giveitem ITEM_VIBRANT_SCALE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SHELLYLOUH_RIDDLE_2
	goto FossilShore_EventScript_SeekOutOtherShelly
	release
	end

FossilShore_EventScript_SeekOutOtherShelly::
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_1, FossilShore_EventScript_CheckRiddle3
	msgbox FossilShore_Text_SeekOutOtherShelly, MSGBOX_AUTOCLOSE
	release
	end

FossilShore_EventScript_CheckRiddle3::
	goto_if_set FLAG_SHELLYLOUH_RIDDLE_3, FossilShore_EventScript_AllRiddles
	msgbox FossilShore_Text_SeekOutOtherShelly, MSGBOX_AUTOCLOSE
	release
	end

FossilShore_EventScript_AllRiddles::
	checkitem ITEM_BIG_PEARL
	goto_if_eq VAR_RESULT, TRUE, FossilShore_EventScript_GaveBigPearl
	msgbox FossilShore_Text_YouEarnedThisBigPearl, MSGBOX_DEFAULT
	giveitem ITEM_BIG_PEARL
	closemessage
	release
	end

FossilShore_EventScript_GaveBigPearl::
	msgbox FossilShore_Text_GaveBigPearl, MSGBOX_AUTOCLOSE
	release
	end

FossilShore_Text_GaveBigPearl:
	.string "We have a fondness for you\n"
	.string "for always helping Shellylouh!$"

FossilShore_Text_ShellRiddle:
	.string "I want a Pearl String.\n"
	.string "You can get pearls by stealing them\l"
	.string "from wild Spoink or Bivague.\l"
	.string "3 can then be given to a man\l"
	.string "in the Ashlands to craft them\l"
	.string "into a Pearl String.\l"
	.string "This is debug text.$"

FossilShore_Text_HereIsReward:
	.string "(This Pokemon seems pleased\n"
	.string "with you. She is gesturing towards\l"
	.string "your Pearl String.)\p"
	.string "(You hand the String over, and she\n"
	.string "gifts you something in return.)$"

FossilShore_Text_SeekOutOtherShelly:
	.string "There may yet be more of my kind\n"
	.string "At peaceful beaches, shall you find\l"
	.string "Solve their riddles with haste\l"
	.string "And your effort won't go to waste$"

FossilShore_Text_YouEarnedThisBigPearl:
	.string "All of our coven stand impressed\n"
	.string "with your pursuing of our quest\l"
	.string "A pearl that shines above all ores\l"
	.string "you are able to now call... yours.$"
