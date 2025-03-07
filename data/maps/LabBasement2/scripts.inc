LabBasement2_MapScripts::
	.byte 0

LabBasement2_EventScript_MorseCode::
	lock
	msgbox LabBasement2_Text_MorseCode, MSGBOX_AUTOCLOSE
	release
	end

LabBasement2_Text_MorseCode:
	.string "(This submarine is spouting\n"
	.string "something in morse code...)\p"
	.string "..-. .- -.-- .-.. ..- .-. .$"
