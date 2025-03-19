PlaneInFlight_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PlaneInFlight_OnFrame
	.byte 0

PlaneInFlight_OnFrame:
	map_script_2 VAR_TEMP_4, 0, PlaneInFlight_EventScript_FlightTime
	.2byte 0

PlaneInFlight_EventScript_FlightTime::
	lock
	delay 32
	setrespawn HEAL_LOCATION_EVER_GRANDE_REST_AREA
	setflag FLAG_EGR_NO_FLY
	speakername PlaneInFlight_Text_NameArchie
	msgbox PlaneInFlight_Text_BeenAWhileSinceWeFlied, MSGBOX_DEFAULT
	speakername PlaneInFlight_Text_NameMaxie
	msgbox PlaneInFlight_Text_NeverThoughtWedBeFriends, MSGBOX_DEFAULT
	speakername PlaneInFlight_Text_NameArchie
	msgbox PlaneInFlight_Text_ICanSeeTheGoldCoast, MSGBOX_DEFAULT
	speakername PlaneInFlight_Text_NameMaxie
	msgbox PlaneInFlight_Text_PrepareToLand, MSGBOX_DEFAULT
	warp MAP_EVER_GRANDE_REST_AREA, 6, 10
	waitstate
	release
	end

PlaneInFlight_Text_NameArchie:
	.string "Archie$"

PlaneInFlight_Text_NameMaxie:
	.string "Maxie$"

PlaneInFlight_Text_BeenAWhileSinceWeFlied:
	.string "It's been a while since we last\n"
	.string "flied together, eh Maxie?$"

PlaneInFlight_Text_NeverThoughtWedBeFriends:
	.string "Quite.\p"
	.string "...\p"
	.string "...Predictability can be such\n"
	.string "a fickle mistress, hmm...\p"
	.string "I would have never predicted that\n"
	.string "you and I would grow so\l"
	.string "close, Archibald.\l"
	.string "Yet, against all odds...\l"
	.string "I find you an inseparable partner.\p"
	.string "{PLAYER}. Do you have someone\n"
	.string "who you value as a partner?\l"
	.string "That sort of bond can change\l"
	.string "your life.$"

PlaneInFlight_Text_ICanSeeTheGoldCoast:
	.string "Hah! Don't put the kid on the\n"
	.string "spot like that! I'm sure\l"
	.string "{PLAYER}'s got a massive story.\l"
	.string "Too big to tell!\p"
	.string "Ah...! There, I've spotted the\n"
	.string "golden coasts of Ever Grande Road...\l"
	.string "What a sight!$"

PlaneInFlight_Text_PrepareToLand:
	.string "Delectable.\n"
	.string "Let us prepare to disembark...$"
