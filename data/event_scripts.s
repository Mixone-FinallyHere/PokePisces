#include "config/battle.h"
#include "config/item.h"
#include "constants/global.h"
#include "constants/apprentice.h"
#include "constants/battle.h"
#include "constants/battle_arena.h"
#include "constants/battle_dome.h"
#include "constants/battle_factory.h"
#include "constants/battle_frontier.h"
#include "constants/battle_palace.h"
#include "constants/battle_pike.h"
#include "constants/battle_pyramid.h"
#include "constants/battle_setup.h"
#include "constants/battle_tent.h"
#include "constants/battle_tower.h"
#include "constants/berry.h"
#include "constants/cable_club.h"
#include "constants/coins.h"
#include "constants/contest.h"
#include "constants/daycare.h"
#include "constants/decorations.h"
#include "constants/easy_chat.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"
#include "constants/field_effects.h"
#include "constants/field_poison.h"
#include "constants/field_specials.h"
#include "constants/field_tasks.h"
#include "constants/field_weather.h"
#include "constants/flags.h"
#include "constants/frontier_util.h"
#include "constants/game_stat.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/heal_locations.h"
#include "constants/layouts.h"
#include "constants/lilycove_lady.h"
#include "constants/map_scripts.h"
#include "constants/maps.h"
#include "constants/mauville_old_man.h"
#include "constants/metatile_labels.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
#include "constants/pokemon.h"
#include "constants/roulette.h"
#include "constants/script_menu.h"
#include "constants/secret_bases.h"
#include "constants/songs.h"
#include "constants/sound.h"
#include "constants/species.h"
#include "constants/trade.h"
#include "constants/trainer_hill.h"
#include "constants/trainers.h"
#include "constants/tv.h"
#include "constants/union_room.h"
#include "constants/vars.h"
#include "constants/weather.h"
	.include "asm/macros.inc"
	.include "asm/macros/event.inc"
	.include "constants/constants.inc"

	.section script_data, "aw", %progbits

	.include "data/script_cmd_table.inc"

gSpecialVars::
	.4byte gSpecialVar_0x8000
	.4byte gSpecialVar_0x8001
	.4byte gSpecialVar_0x8002
	.4byte gSpecialVar_0x8003
	.4byte gSpecialVar_0x8004
	.4byte gSpecialVar_0x8005
	.4byte gSpecialVar_0x8006
	.4byte gSpecialVar_0x8007
	.4byte gSpecialVar_0x8008
	.4byte gSpecialVar_0x8009
	.4byte gSpecialVar_0x800A
	.4byte gSpecialVar_0x800B
	.4byte gSpecialVar_Facing
	.4byte gSpecialVar_Result
	.4byte gSpecialVar_ItemId
	.4byte gSpecialVar_LastTalked
	.4byte gSpecialVar_ContestRank
	.4byte gSpecialVar_ContestCategory
	.4byte gSpecialVar_MonBoxId
	.4byte gSpecialVar_MonBoxPos
	.4byte gSpecialVar_Unused_0x8014
	.4byte gTrainerBattleOpponent_A

	.include "data/specials.inc"

gStdScripts::
	.4byte Std_ObtainItem              @ STD_OBTAIN_ITEM
	.4byte Std_FindItem                @ STD_FIND_ITEM
	.4byte Std_MsgboxNPC               @ MSGBOX_NPC
	.4byte Std_MsgboxSign              @ MSGBOX_SIGN
	.4byte Std_MsgboxDefault           @ MSGBOX_DEFAULT
	.4byte Std_MsgboxYesNo             @ MSGBOX_YESNO
	.4byte Std_MsgboxAutoclose         @ MSGBOX_AUTOCLOSE
	.4byte Std_ObtainDecoration        @ STD_OBTAIN_DECORATION
	.4byte Std_RegisteredInMatchCall   @ STD_REGISTER_MATCH_CALL
	.4byte Std_MsgboxGetPoints         @ MSGBOX_GETPOINTS
	.4byte Std_MsgboxPokenav           @ MSGBOX_POKENAV
gStdScripts_End::

	.include "data/maps/PetalburgCity/scripts.inc"
	.include "data/maps/SlateportCity/scripts.inc"
	.include "data/maps/MauvilleCity/scripts.inc"
	.include "data/maps/RustboroCity/scripts.inc"
	.include "data/maps/FortreeCity/scripts.inc"
	.include "data/maps/LilycoveCity/scripts.inc"
	.include "data/maps/MossdeepCity/scripts.inc"
	.include "data/maps/SootopolisCity/scripts.inc"
	.include "data/maps/EverGrandeCity/scripts.inc"
	.include "data/maps/LittlerootTown/scripts.inc"
	.include "data/maps/OldaleTown/scripts.inc"
	.include "data/maps/DewfordTown/scripts.inc"
	.include "data/maps/LavaridgeTown/scripts.inc"
	.include "data/maps/FallarborTown/scripts.inc"
	.include "data/maps/VerdanturfTown/scripts.inc"
	.include "data/maps/PacifidlogTown/scripts.inc"
	.include "data/maps/Route101/scripts.inc"
	.include "data/maps/Route102/scripts.inc"
	.include "data/maps/Route103/scripts.inc"
	.include "data/maps/Route104/scripts.inc"
	.include "data/maps/Route105/scripts.inc"
	.include "data/maps/Route106/scripts.inc"
	.include "data/maps/Route107/scripts.inc"
	.include "data/maps/Route108/scripts.inc"
	.include "data/maps/Route109/scripts.inc"
	.include "data/maps/Route110/scripts.inc"
	.include "data/maps/Route111/scripts.inc"
	.include "data/maps/Route112/scripts.inc"
	.include "data/maps/Route113/scripts.inc"
	.include "data/maps/Route114/scripts.inc"
	.include "data/maps/Route115/scripts.inc"
	.include "data/maps/Route116/scripts.inc"
	.include "data/maps/Route117/scripts.inc"
	.include "data/maps/Route118/scripts.inc"
	.include "data/maps/Route119/scripts.inc"
	.include "data/maps/Route120/scripts.inc"
	.include "data/maps/Route121/scripts.inc"
	.include "data/maps/Route122/scripts.inc"
	.include "data/maps/Route123/scripts.inc"
	.include "data/maps/Route124/scripts.inc"
	.include "data/maps/Route125/scripts.inc"
	.include "data/maps/Route126/scripts.inc"
	.include "data/maps/Route127/scripts.inc"
	.include "data/maps/Route128/scripts.inc"
	.include "data/maps/Route129/scripts.inc"
	.include "data/maps/Route130/scripts.inc"
	.include "data/maps/Route131/scripts.inc"
	.include "data/maps/Route132/scripts.inc"
	.include "data/maps/Route133/scripts.inc"
	.include "data/maps/Route134/scripts.inc"
	.include "data/maps/Underwater_Route124/scripts.inc"
	.include "data/maps/Underwater_Route126/scripts.inc"
	.include "data/maps/Underwater_Route127/scripts.inc"
	.include "data/maps/Underwater_Route128/scripts.inc"
	.include "data/maps/Underwater_Route129/scripts.inc"
	.include "data/maps/Underwater_Route105/scripts.inc"
	.include "data/maps/Underwater_Route125/scripts.inc"
	.include "data/maps/LittlerootTown_BrendansHouse_1F/scripts.inc"
	.include "data/maps/LittlerootTown_BrendansHouse_2F/scripts.inc"
	.include "data/maps/LittlerootTown_MaysHouse_1F/scripts.inc"
	.include "data/maps/LittlerootTown_MaysHouse_2F/scripts.inc"
	.include "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.inc"
	.include "data/maps/OldaleTown_House1/scripts.inc"
	.include "data/maps/OldaleTown_House2/scripts.inc"
	.include "data/maps/OldaleTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/OldaleTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/OldaleTown_Mart/scripts.inc"
	.include "data/maps/DewfordTown_House1/scripts.inc"
	.include "data/maps/DewfordTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/DewfordTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/DewfordTown_Gym/scripts.inc"
	.include "data/maps/DewfordTown_Hall/scripts.inc"
	.include "data/maps/DewfordTown_House2/scripts.inc"
	.include "data/maps/LavaridgeTown_HerbShop/scripts.inc"
	.include "data/maps/LavaridgeTown_Gym_1F/scripts.inc"
	.include "data/maps/LavaridgeTown_Gym_B1F/scripts.inc"
	.include "data/maps/LavaridgeTown_House/scripts.inc"
	.include "data/maps/LavaridgeTown_Mart/scripts.inc"
	.include "data/maps/LavaridgeTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/LavaridgeTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/FallarborTown_Mart/scripts.inc"
	.include "data/maps/FallarborTown_BattleTentLobby/scripts.inc"
	.include "data/maps/FallarborTown_BattleTentCorridor/scripts.inc"
	.include "data/maps/FallarborTown_BattleTentBattleRoom/scripts.inc"
	.include "data/maps/FallarborTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/FallarborTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/FallarborTown_CozmosHouse/scripts.inc"
	.include "data/maps/FallarborTown_MoveRelearnersHouse/scripts.inc"
	.include "data/maps/VerdanturfTown_BattleTentLobby/scripts.inc"
	.include "data/maps/VerdanturfTown_BattleTentCorridor/scripts.inc"
	.include "data/maps/VerdanturfTown_BattleTentBattleRoom/scripts.inc"
	.include "data/maps/VerdanturfTown_Mart/scripts.inc"
	.include "data/maps/VerdanturfTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/VerdanturfTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/VerdanturfTown_WandasHouse/scripts.inc"
	.include "data/maps/VerdanturfTown_FriendshipRatersHouse/scripts.inc"
	.include "data/maps/VerdanturfTown_House/scripts.inc"
	.include "data/maps/PacifidlogTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/PacifidlogTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/PacifidlogTown_House1/scripts.inc"
	.include "data/maps/PacifidlogTown_House2/scripts.inc"
	.include "data/maps/PacifidlogTown_House3/scripts.inc"
	.include "data/maps/PacifidlogTown_House4/scripts.inc"
	.include "data/maps/PacifidlogTown_House5/scripts.inc"
	.include "data/maps/PetalburgCity_WallysHouse/scripts.inc"
	.include "data/maps/PetalburgCity_Gym/scripts.inc"
	.include "data/maps/PetalburgCity_House1/scripts.inc"
	.include "data/maps/PetalburgCity_House2/scripts.inc"
	.include "data/maps/PetalburgCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/PetalburgCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/PetalburgCity_Mart/scripts.inc"
	.include "data/maps/SlateportCity_SternsShipyard_1F/scripts.inc"
	.include "data/maps/SlateportCity_SternsShipyard_2F/scripts.inc"
	.include "data/maps/SlateportCity_BattleTentLobby/scripts.inc"
	.include "data/maps/SlateportCity_BattleTentCorridor/scripts.inc"
	.include "data/maps/SlateportCity_BattleTentBattleRoom/scripts.inc"
	.include "data/maps/SlateportCity_NameRatersHouse/scripts.inc"
	.include "data/maps/SlateportCity_PokemonFanClub/scripts.inc"
	.include "data/maps/SlateportCity_OceanicMuseum_1F/scripts.inc"
	.include "data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc"
	.include "data/maps/SlateportCity_Harbor/scripts.inc"
	.include "data/maps/SlateportCity_House/scripts.inc"
	.include "data/maps/SlateportCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/SlateportCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/SlateportCity_Mart/scripts.inc"
	.include "data/maps/MauvilleCity_Gym/scripts.inc"
	.include "data/maps/MauvilleCity_BikeShop/scripts.inc"
	.include "data/maps/MauvilleCity_House1/scripts.inc"
	.include "data/maps/MauvilleCity_GameCorner/scripts.inc"
	.include "data/maps/MauvilleCity_House2/scripts.inc"
	.include "data/maps/MauvilleCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/MauvilleCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/MauvilleCity_Mart/scripts.inc"
	.include "data/maps/RustboroCity_DevonCorp_1F/scripts.inc"
	.include "data/maps/RustboroCity_DevonCorp_2F/scripts.inc"
	.include "data/maps/RustboroCity_DevonCorp_3F/scripts.inc"
	.include "data/maps/RustboroCity_Gym/scripts.inc"
	.include "data/maps/RustboroCity_PokemonSchool/scripts.inc"
	.include "data/maps/RustboroCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/RustboroCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/RustboroCity_Mart/scripts.inc"
	.include "data/maps/RustboroCity_Flat1_1F/scripts.inc"
	.include "data/maps/RustboroCity_Flat1_2F/scripts.inc"
	.include "data/maps/RustboroCity_House1/scripts.inc"
	.include "data/maps/RustboroCity_CuttersHouse/scripts.inc"
	.include "data/maps/RustboroCity_House2/scripts.inc"
	.include "data/maps/RustboroCity_Flat2_1F/scripts.inc"
	.include "data/maps/RustboroCity_Flat2_2F/scripts.inc"
	.include "data/maps/RustboroCity_Flat2_3F/scripts.inc"
	.include "data/maps/RustboroCity_House3/scripts.inc"
	.include "data/maps/FortreeCity_House1/scripts.inc"
	.include "data/maps/FortreeCity_Gym/scripts.inc"
	.include "data/maps/FortreeCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/FortreeCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/FortreeCity_Mart/scripts.inc"
	.include "data/maps/FortreeCity_House2/scripts.inc"
	.include "data/maps/FortreeCity_House3/scripts.inc"
	.include "data/maps/FortreeCity_House4/scripts.inc"
	.include "data/maps/FortreeCity_House5/scripts.inc"
	.include "data/maps/FortreeCity_DecorationShop/scripts.inc"
	.include "data/maps/LilycoveCity_CoveLilyMotel_1F/scripts.inc"
	.include "data/maps/LilycoveCity_CoveLilyMotel_2F/scripts.inc"
	.include "data/maps/LilycoveCity_LilycoveMuseum_1F/scripts.inc"
	.include "data/maps/LilycoveCity_LilycoveMuseum_2F/scripts.inc"
	.include "data/maps/LilycoveCity_ContestLobby/scripts.inc"
	.include "data/maps/LilycoveCity_ContestHall/scripts.inc"
	.include "data/maps/LilycoveCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/LilycoveCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/LilycoveCity_UnusedMart/scripts.inc"
	.include "data/maps/LilycoveCity_PokemonTrainerFanClub/scripts.inc"
	.include "data/maps/LilycoveCity_Harbor/scripts.inc"
	.include "data/maps/LilycoveCity_MoveDeletersHouse/scripts.inc"
	.include "data/maps/LilycoveCity_House1/scripts.inc"
	.include "data/maps/LilycoveCity_House2/scripts.inc"
	.include "data/maps/LilycoveCity_House3/scripts.inc"
	.include "data/maps/LilycoveCity_House4/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_1F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_2F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_3F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_4F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_5F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStoreRooftop/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStoreElevator/scripts.inc"
	.include "data/maps/MossdeepCity_Gym/scripts.inc"
	.include "data/maps/MossdeepCity_House1/scripts.inc"
	.include "data/maps/MossdeepCity_House2/scripts.inc"
	.include "data/maps/MossdeepCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/MossdeepCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/MossdeepCity_Mart/scripts.inc"
	.include "data/maps/MossdeepCity_House3/scripts.inc"
	.include "data/maps/MossdeepCity_StevensHouse/scripts.inc"
	.include "data/maps/MossdeepCity_House4/scripts.inc"
	.include "data/maps/MossdeepCity_SpaceCenter_1F/scripts.inc"
	.include "data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc"
	.include "data/maps/MossdeepCity_GameCorner_1F/scripts.inc"
	.include "data/maps/MossdeepCity_GameCorner_B1F/scripts.inc"
	.include "data/maps/SootopolisCity_Gym_1F/scripts.inc"
	.include "data/maps/SootopolisCity_Gym_B1F/scripts.inc"
	.include "data/maps/SootopolisCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/SootopolisCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/SootopolisCity_Mart/scripts.inc"
	.include "data/maps/SootopolisCity_House1/scripts.inc"
	.include "data/maps/SootopolisCity_House2/scripts.inc"
	.include "data/maps/SootopolisCity_House3/scripts.inc"
	.include "data/maps/SootopolisCity_House4/scripts.inc"
	.include "data/maps/SootopolisCity_House5/scripts.inc"
	.include "data/maps/SootopolisCity_House6/scripts.inc"
	.include "data/maps/SootopolisCity_House7/scripts.inc"
	.include "data/maps/SootopolisCity_LotadAndSeedotHouse/scripts.inc"
	.include "data/maps/SootopolisCity_MysteryEventsHouse_1F/scripts.inc"
	.include "data/maps/SootopolisCity_MysteryEventsHouse_B1F/scripts.inc"
	.include "data/maps/EverGrandeCity_SidneysRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_PhoebesRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_GlaciasRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_DrakesRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_ChampionsRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall1/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall2/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall3/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall4/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall5/scripts.inc"
	.include "data/maps/EverGrandeCity_PokemonLeague_1F/scripts.inc"
	.include "data/maps/EverGrandeCity_HallOfFame/scripts.inc"
	.include "data/maps/EverGrandeCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/EverGrandeCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/EverGrandeCity_PokemonLeague_2F/scripts.inc"
	.include "data/maps/Route104_MrBrineysHouse/scripts.inc"
	.include "data/maps/Route104_PrettyPetalFlowerShop/scripts.inc"
	.include "data/maps/Route111_WinstrateFamilysHouse/scripts.inc"
	.include "data/maps/Route111_OldLadysRestStop/scripts.inc"
	.include "data/maps/Route112_CableCarStation/scripts.inc"
	.include "data/maps/MtChimney_CableCarStation/scripts.inc"
	.include "data/maps/Route114_FossilManiacsHouse/scripts.inc"
	.include "data/maps/Route114_FossilManiacsTunnel/scripts.inc"
	.include "data/maps/Route114_LanettesHouse/scripts.inc"
	.include "data/maps/Route116_TunnelersRestHouse/scripts.inc"
	.include "data/maps/Route117_PokemonDayCare/scripts.inc"
	.include "data/maps/Route121_SafariZoneEntrance/scripts.inc"
	.include "data/maps/MeteorFalls_1F_1R/scripts.inc"
	.include "data/maps/MeteorFalls_1F_2R/scripts.inc"
	.include "data/maps/MeteorFalls_B1F_1R/scripts.inc"
	.include "data/maps/MeteorFalls_B1F_2R/scripts.inc"
	.include "data/maps/RusturfTunnel/scripts.inc"
	.include "data/maps/Underwater_SootopolisCity/scripts.inc"
	.include "data/maps/DesertRuins/scripts.inc"
	.include "data/maps/GraniteCave_1F/scripts.inc"
	.include "data/maps/GraniteCave_B1F/scripts.inc"
	.include "data/maps/GraniteCave_B2F/scripts.inc"
	.include "data/maps/GraniteCave_StevensRoom/scripts.inc"
	.include "data/maps/PetalburgWoods/scripts.inc"
	.include "data/maps/MtChimney/scripts.inc"
	.include "data/maps/JaggedPass/scripts.inc"
	.include "data/maps/FieryPath/scripts.inc"
	.include "data/maps/MtPyre_1F/scripts.inc"
	.include "data/maps/MtPyre_2F/scripts.inc"
	.include "data/maps/MtPyre_3F/scripts.inc"
	.include "data/maps/MtPyre_4F/scripts.inc"
	.include "data/maps/MtPyre_5F/scripts.inc"
	.include "data/maps/MtPyre_6F/scripts.inc"
	.include "data/maps/MtPyre_Exterior/scripts.inc"
	.include "data/maps/MtPyre_Summit/scripts.inc"
	.include "data/maps/AquaHideout_1F/scripts.inc"
	.include "data/maps/AquaHideout_B1F/scripts.inc"
	.include "data/maps/AquaHideout_B2F/scripts.inc"
	.include "data/maps/Underwater_SeafloorCavern/scripts.inc"
	.include "data/maps/SeafloorCavern_Entrance/scripts.inc"
	.include "data/maps/SeafloorCavern_Room1/scripts.inc"
	.include "data/maps/SeafloorCavern_Room2/scripts.inc"
	.include "data/maps/SeafloorCavern_Room3/scripts.inc"
	.include "data/maps/SeafloorCavern_Room4/scripts.inc"
	.include "data/maps/SeafloorCavern_Room5/scripts.inc"
	.include "data/maps/SeafloorCavern_Room6/scripts.inc"
	.include "data/maps/SeafloorCavern_Room7/scripts.inc"
	.include "data/maps/SeafloorCavern_Room8/scripts.inc"
	.include "data/maps/SeafloorCavern_Room9/scripts.inc"
	.include "data/maps/CaveOfOrigin_Entrance/scripts.inc"
	.include "data/maps/CaveOfOrigin_1F/scripts.inc"
	.include "data/maps/CaveOfOrigin_UnusedRubySapphireMap1/scripts.inc"
	.include "data/maps/CaveOfOrigin_UnusedRubySapphireMap2/scripts.inc"
	.include "data/maps/CaveOfOrigin_UnusedRubySapphireMap3/scripts.inc"
	.include "data/maps/CaveOfOrigin_B1F/scripts.inc"
	.include "data/maps/VictoryRoad_1F/scripts.inc"
	.include "data/maps/VictoryRoad_B1F/scripts.inc"
	.include "data/maps/VictoryRoad_B2F/scripts.inc"
	.include "data/maps/ShoalCave_LowTideEntranceRoom/scripts.inc"
	.include "data/maps/ShoalCave_LowTideInnerRoom/scripts.inc"
	.include "data/maps/ShoalCave_LowTideStairsRoom/scripts.inc"
	.include "data/maps/ShoalCave_LowTideLowerRoom/scripts.inc"
	.include "data/maps/ShoalCave_HighTideEntranceRoom/scripts.inc"
	.include "data/maps/ShoalCave_HighTideInnerRoom/scripts.inc"
	.include "data/maps/NewMauville_Entrance/scripts.inc"
	.include "data/maps/NewMauville_Inside/scripts.inc"
	.include "data/maps/AbandonedShip_Deck/scripts.inc"
	.include "data/maps/AbandonedShip_Corridors_1F/scripts.inc"
	.include "data/maps/AbandonedShip_Rooms_1F/scripts.inc"
	.include "data/maps/AbandonedShip_Corridors_B1F/scripts.inc"
	.include "data/maps/AbandonedShip_Rooms_B1F/scripts.inc"
	.include "data/maps/AbandonedShip_Rooms2_B1F/scripts.inc"
	.include "data/maps/AbandonedShip_Underwater1/scripts.inc"
	.include "data/maps/AbandonedShip_Room_B1F/scripts.inc"
	.include "data/maps/AbandonedShip_Rooms2_1F/scripts.inc"
	.include "data/maps/AbandonedShip_CaptainsOffice/scripts.inc"
	.include "data/maps/AbandonedShip_Underwater2/scripts.inc"
	.include "data/maps/AbandonedShip_HiddenFloorCorridors/scripts.inc"
	.include "data/maps/AbandonedShip_HiddenFloorRooms/scripts.inc"
	.include "data/maps/IslandCave/scripts.inc"
	.include "data/maps/AncientTomb/scripts.inc"
	.include "data/maps/Underwater_Route134/scripts.inc"
	.include "data/maps/Underwater_SealedChamber/scripts.inc"
	.include "data/maps/SealedChamber_OuterRoom/scripts.inc"
	.include "data/maps/SealedChamber_InnerRoom/scripts.inc"
	.include "data/maps/ScorchedSlab/scripts.inc"
	.include "data/maps/AquaHideout_UnusedRubyMap1/scripts.inc"
	.include "data/maps/AquaHideout_UnusedRubyMap2/scripts.inc"
	.include "data/maps/AquaHideout_UnusedRubyMap3/scripts.inc"
	.include "data/maps/SkyPillar_Entrance/scripts.inc"
	.include "data/maps/SkyPillar_Outside/scripts.inc"
	.include "data/maps/SkyPillar_1F/scripts.inc"
	.include "data/maps/SkyPillar_2F/scripts.inc"
	.include "data/maps/SkyPillar_3F/scripts.inc"
	.include "data/maps/SkyPillar_4F/scripts.inc"
	.include "data/maps/ShoalCave_LowTideIceRoom/scripts.inc"
	.include "data/maps/SkyPillar_5F/scripts.inc"
	.include "data/maps/SkyPillar_Top/scripts.inc"
	.include "data/maps/MagmaHideout_1F/scripts.inc"
	.include "data/maps/MagmaHideout_2F_1R/scripts.inc"
	.include "data/maps/MagmaHideout_2F_2R/scripts.inc"
	.include "data/maps/MagmaHideout_3F_1R/scripts.inc"
	.include "data/maps/MagmaHideout_3F_2R/scripts.inc"
	.include "data/maps/MagmaHideout_4F/scripts.inc"
	.include "data/maps/MagmaHideout_3F_3R/scripts.inc"
	.include "data/maps/MagmaHideout_2F_3R/scripts.inc"
	.include "data/maps/MirageTower_1F/scripts.inc"
	.include "data/maps/MirageTower_2F/scripts.inc"
	.include "data/maps/MirageTower_3F/scripts.inc"
	.include "data/maps/MirageTower_4F/scripts.inc"
	.include "data/maps/DesertUnderpass/scripts.inc"
	.include "data/maps/ArtisanCave_B1F/scripts.inc"
	.include "data/maps/ArtisanCave_1F/scripts.inc"
	.include "data/maps/Underwater_MarineCave/scripts.inc"
	.include "data/maps/MarineCave_Entrance/scripts.inc"
	.include "data/maps/MarineCave_End/scripts.inc"
	.include "data/maps/TerraCave_Entrance/scripts.inc"
	.include "data/maps/TerraCave_End/scripts.inc"
	.include "data/maps/AlteringCave/scripts.inc"
	.include "data/maps/MeteorFalls_StevensCave/scripts.inc"
	.include "data/scripts/shared_secret_base.inc"
	.include "data/maps/BattleColosseum_2P/scripts.inc"
	.include "data/maps/TradeCenter/scripts.inc"
	.include "data/maps/RecordCorner/scripts.inc"
	.include "data/maps/BattleColosseum_4P/scripts.inc"
	.include "data/maps/ContestHall/scripts.inc"
	.include "data/maps/InsideOfTruck/scripts.inc"
	.include "data/maps/SSTidalCorridor/scripts.inc"
	.include "data/maps/SSTidalLowerDeck/scripts.inc"
	.include "data/maps/SSTidalRooms/scripts.inc"
	.include "data/maps/BattlePyramidSquare01/scripts.inc"
	.include "data/maps/UnionRoom/scripts.inc"
	.include "data/maps/SafariZone_Northwest/scripts.inc"
	.include "data/maps/SafariZone_North/scripts.inc"
	.include "data/maps/SafariZone_Southwest/scripts.inc"
	.include "data/maps/SafariZone_South/scripts.inc"
	.include "data/maps/BattleFrontier_OutsideWest/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerElevator/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.inc"
	.include "data/maps/SouthernIsland_Exterior/scripts.inc"
	.include "data/maps/SouthernIsland_Interior/scripts.inc"
	.include "data/maps/SafariZone_RestHouse/scripts.inc"
	.include "data/maps/SafariZone_Northeast/scripts.inc"
	.include "data/maps/SafariZone_Southeast/scripts.inc"
	.include "data/maps/BattleFrontier_OutsideEast/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerMultiPartnerRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerMultiCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerMultiBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleDomeLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattleDomeCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattleDomePreBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleDomeBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePalaceLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePalaceCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePalaceBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePyramidLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePyramidFloor/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePyramidTop/scripts.inc"
	.include "data/maps/BattleFrontier_BattleArenaLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattleArenaCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattleArenaBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleFactoryLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattleFactoryPreBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleFactoryBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeThreePathRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeRoomNormal/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeRoomFinal/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeRoomWildMons/scripts.inc"
	.include "data/maps/BattleFrontier_RankingHall/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge1/scripts.inc"
	.include "data/maps/BattleFrontier_ExchangeServiceCorner/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge2/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge3/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge4/scripts.inc"
	.include "data/maps/BattleFrontier_ScottsHouse/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge5/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge6/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge7/scripts.inc"
	.include "data/maps/BattleFrontier_ReceptionGate/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge8/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge9/scripts.inc"
	.include "data/maps/BattleFrontier_PokemonCenter_1F/scripts.inc"
	.include "data/maps/BattleFrontier_PokemonCenter_2F/scripts.inc"
	.include "data/maps/BattleFrontier_Mart/scripts.inc"
	.include "data/maps/FarawayIsland_Entrance/scripts.inc"
	.include "data/maps/FarawayIsland_Interior/scripts.inc"
	.include "data/maps/BirthIsland_Exterior/scripts.inc"
	.include "data/maps/BirthIsland_Harbor/scripts.inc"
	.include "data/maps/TrainerHill_Entrance/scripts.inc"
	.include "data/maps/TrainerHill_1F/scripts.inc"
	.include "data/maps/TrainerHill_2F/scripts.inc"
	.include "data/maps/TrainerHill_3F/scripts.inc"
	.include "data/maps/TrainerHill_4F/scripts.inc"
	.include "data/maps/TrainerHill_Roof/scripts.inc"
	.include "data/maps/NavelRock_Exterior/scripts.inc"
	.include "data/maps/NavelRock_Harbor/scripts.inc"
	.include "data/maps/NavelRock_Entrance/scripts.inc"
	.include "data/maps/NavelRock_B1F/scripts.inc"
	.include "data/maps/NavelRock_Fork/scripts.inc"
	.include "data/maps/NavelRock_Up1/scripts.inc"
	.include "data/maps/NavelRock_Up2/scripts.inc"
	.include "data/maps/NavelRock_Up3/scripts.inc"
	.include "data/maps/NavelRock_Up4/scripts.inc"
	.include "data/maps/NavelRock_Top/scripts.inc"
	.include "data/maps/NavelRock_Down01/scripts.inc"
	.include "data/maps/NavelRock_Down02/scripts.inc"
	.include "data/maps/NavelRock_Down03/scripts.inc"
	.include "data/maps/NavelRock_Down04/scripts.inc"
	.include "data/maps/NavelRock_Down05/scripts.inc"
	.include "data/maps/NavelRock_Down06/scripts.inc"
	.include "data/maps/NavelRock_Down07/scripts.inc"
	.include "data/maps/NavelRock_Down08/scripts.inc"
	.include "data/maps/NavelRock_Down09/scripts.inc"
	.include "data/maps/NavelRock_Down10/scripts.inc"
	.include "data/maps/NavelRock_Down11/scripts.inc"
	.include "data/maps/NavelRock_Bottom/scripts.inc"
	.include "data/maps/TrainerHill_Elevator/scripts.inc"
	.include "data/maps/Route104_Prototype/scripts.inc"
	.include "data/maps/Route104_PrototypePrettyPetalFlowerShop/scripts.inc"
	.include "data/maps/Route109_SeashoreHouse/scripts.inc"
	.include "data/maps/Route110_TrickHouseEntrance/scripts.inc"
	.include "data/maps/Route110_TrickHouseEnd/scripts.inc"
	.include "data/maps/Route110_TrickHouseCorridor/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle1/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle2/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle3/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle4/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle5/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle6/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle7/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle8/scripts.inc"
	.include "data/maps/Route110_SeasideCyclingRoadNorthEntrance/scripts.inc"
	.include "data/maps/Route110_SeasideCyclingRoadSouthEntrance/scripts.inc"
	.include "data/maps/Route113_GlassWorkshop/scripts.inc"
	.include "data/maps/Route123_BerryMastersHouse/scripts.inc"
	.include "data/maps/Route119_WeatherInstitute_1F/scripts.inc"
	.include "data/maps/Route119_WeatherInstitute_2F/scripts.inc"
	.include "data/maps/Route119_House/scripts.inc"
	.include "data/maps/Route124_DivingTreasureHuntersHouse/scripts.inc"

	.include "data/scripts/std_msgbox.inc"
	.include "data/scripts/trainer_battle.inc"
	.include "data/scripts/new_game.inc"
	.include "data/scripts/hall_of_fame.inc"

	.include "data/scripts/debug.inc"

EventScript_WhiteOut::
	call EverGrandeCity_HallOfFame_EventScript_ResetEliteFour
	goto EventScript_ResetMrBriney
	end

EventScript_ResetMrBriney::
	goto_if_eq VAR_BRINEY_LOCATION, 1, EventScript_MoveMrBrineyToHouse
	goto_if_eq VAR_BRINEY_LOCATION, 2, EventScript_MoveMrBrineyToDewford
	goto_if_eq VAR_BRINEY_LOCATION, 3, EventScript_MoveMrBrineyToRoute109
	end

EventScript_MoveMrBrineyToHouse::
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	end

EventScript_MoveMrBrineyToDewford::
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	end

EventScript_MoveMrBrineyToRoute109::
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	end

EverGrandeCity_HallOfFame_EventScript_ResetEliteFour::
	clearflag FLAG_DEFEATED_ELITE_4_SIDNEY
	clearflag FLAG_DEFEATED_ELITE_4_PHOEBE
	clearflag FLAG_DEFEATED_ELITE_4_GLACIA
	clearflag FLAG_DEFEATED_ELITE_4_DRAKE
	setvar VAR_ELITE_4_STATE, 0
	return

Common_EventScript_UpdateBrineyLocation::
	goto_if_unset FLAG_RECEIVED_POKENAV, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, Common_EventScript_NopReturn
	goto_if_unset FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT, EventScript_SetBrineyLocation_House
	goto_if_unset FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN, EventScript_SetBrineyLocation_Dewford
	goto_if_unset FLAG_HIDE_ROUTE_109_MR_BRINEY, EventScript_SetBrineyLocation_Route109
	return

EventScript_SetBrineyLocation_House::
	setvar VAR_BRINEY_LOCATION, 1
	return

EventScript_SetBrineyLocation_Dewford::
	setvar VAR_BRINEY_LOCATION, 2
	return

EventScript_SetBrineyLocation_Route109::
	setvar VAR_BRINEY_LOCATION, 3
	return

	.include "data/scripts/pkmn_center_nurse.inc"
	.include "data/scripts/obtain_item.inc"
	.include "data/scripts/record_mix.inc"
	.include "data/scripts/pc.inc"

@ scripts/notices.inc? signs.inc? See comment about text/notices.inc
Common_EventScript_ShowPokemartSign::
	msgbox gText_PokemartSign, MSGBOX_SIGN
	end

Common_EventScript_ShowPokemonCenterSign::
	msgbox gText_PokemonCenterSign, MSGBOX_SIGN
	end

Common_ShowEasyChatScreen::
	fadescreen FADE_TO_BLACK
	special ShowEasyChatScreen
	fadescreen FADE_FROM_BLACK
	return

Common_EventScript_ReadyPetalburgGymForBattle::
	clearflag FLAG_HIDE_PETALBURG_GYM_GREETER
	setflag FLAG_PETALBURG_MART_EXPANDED_ITEMS
	return

Common_Lottery_EventScript_LotteryClerk::
	lock
	faceplayer
	goto_if_eq VAR_NEW_LOTTERY_STATE, 0, Common_Lottery_EventScript_LottoIntroduction
	msgbox gText_WelcomeToLottery, MSGBOX_DEFAULT
	call_if_set FLAG_BADGE01_GET, Common_Lottery_EventScript_LotteryCheckBadge1
	call_if_set FLAG_BADGE02_GET, Common_Lottery_EventScript_LotteryCheckBadge2
	call_if_set FLAG_BADGE03_GET, Common_Lottery_EventScript_LotteryCheckBadge3
	call_if_set FLAG_BADGE04_GET, Common_Lottery_EventScript_LotteryCheckBadge4
	call_if_set FLAG_BADGE05_GET, Common_Lottery_EventScript_LotteryCheckBadge5
	call_if_set FLAG_BADGE06_GET, Common_Lottery_EventScript_LotteryCheckBadge6
	call_if_set FLAG_BADGE07_GET, Common_Lottery_EventScript_LotteryCheckBadge7
	call_if_set FLAG_BADGE08_GET, Common_Lottery_EventScript_LotteryCheckBadge8
	goto Common_Lottery_EventScript_LotteryMenu
	release
	end

Common_Lottery_EventScript_LottoIntroduction::
	msgbox gText_LottoIntroduction, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_MYSTIC_TICKET, 3
	closemessage
	setvar VAR_NEW_LOTTERY_STATE, 1
	goto Common_Lottery_EventScript_LotteryMenu
	release
	end

Common_Lottery_EventScript_LotteryCheckBadge1::
	goto_if_eq VAR_NEW_LOTTERY_STATE, 1, Common_Lottery_EventScript_LotteryGiveFreeTicket
	return

Common_Lottery_EventScript_LotteryCheckBadge2::
	goto_if_eq VAR_NEW_LOTTERY_STATE, 2, Common_Lottery_EventScript_LotteryGiveFreeTicket
	return

Common_Lottery_EventScript_LotteryCheckBadge3::
	goto_if_eq VAR_NEW_LOTTERY_STATE, 3, Common_Lottery_EventScript_LotteryGiveFreeTicket
	return

Common_Lottery_EventScript_LotteryCheckBadge4::
	goto_if_eq VAR_NEW_LOTTERY_STATE, 4, Common_Lottery_EventScript_LotteryGiveFreeTicket
	return

Common_Lottery_EventScript_LotteryCheckBadge5::
	goto_if_eq VAR_NEW_LOTTERY_STATE, 5, Common_Lottery_EventScript_LotteryGiveFreeTicket
	return

Common_Lottery_EventScript_LotteryCheckBadge6::
	goto_if_eq VAR_NEW_LOTTERY_STATE, 6, Common_Lottery_EventScript_LotteryGiveFreeTicket
	return

Common_Lottery_EventScript_LotteryCheckBadge7::
	goto_if_eq VAR_NEW_LOTTERY_STATE, 7, Common_Lottery_EventScript_LotteryGiveFreeTicket
	return

Common_Lottery_EventScript_LotteryCheckBadge8::
	goto_if_eq VAR_NEW_LOTTERY_STATE, 8, Common_Lottery_EventScript_LotteryGiveFreeTicket
	return

Common_Lottery_EventScript_LotteryGiveFreeTicket::
	msgbox gText_LotteryGiveFreeTicket, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_MYSTIC_TICKET
	addvar VAR_NEW_LOTTERY_STATE, 1
	return

Common_Lottery_EventScript_LotteryMenu::
	msgbox gText_WhatLottoThingYouWant, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_LOTTO_MENU_CHOICE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	goto_if_eq VAR_TEMP_1, 0, Common_Lottery_EventScript_AttemptToPlayLotto
	goto_if_eq VAR_TEMP_1, 1, Common_Lottery_EventScript_WantLottoTicket
	goto_if_eq VAR_TEMP_1, 2, Common_Lottery_EventScript_PrizeExplanation
	closemessage
	release
	end

Common_Lottery_EventScript_AttemptToPlayLotto::
	checkitem ITEM_MYSTIC_TICKET
	goto_if_eq VAR_RESULT, FALSE, Common_Lottery_EventScript_NoLottoTickets
	msgbox gText_WillYouSpendALottoTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_Lottery_EventScript_ReleaseOut
	playse SE_SHOP
	removeitem ITEM_MYSTIC_TICKET, 1
	msgbox gText_LetsDrawYourNumber, MSGBOX_DEFAULT
	random 10  @ 1/10 chance of first prize
	goto_if_ne VAR_RESULT, 0, Common_Lottery_EventScript_LottoWinNothing
	random 10  @ 1/100 chance of second prize
	goto_if_ne VAR_RESULT, 0, Common_Lottery_EventScript_LottoWinBeastBall
	random 10  @ 1/1000 chance of third prize
	goto_if_ne VAR_RESULT, 0, Common_Lottery_EventScript_LottoWinAmuletCoin
	goto Common_Lottery_EventScript_LottoWinNeoBattery
	release
	end

Common_Lottery_EventScript_LottoWinNothing::
	playfanfare MUS_TOO_BAD
	message gText_PlayerWonNothing
	waitfanfare
	waitmessage
	msgbox gText_HopeYouPlayLottoAgain, MSGBOX_AUTOCLOSE
	release
	end

Common_Lottery_EventScript_LottoWinBeastBall::
	playfanfare MUS_SLOTS_WIN
	message gText_PlayerWonBeastBall
	waitfanfare
	waitmessage
	giveitem ITEM_BEAST_BALL
	closemessage
	msgbox gText_HopeYouPlayLottoAgain, MSGBOX_AUTOCLOSE
	release
	end

Common_Lottery_EventScript_LottoWinAmuletCoin::
	playfanfare MUS_SLOTS_JACKPOT
	message gText_PlayerWonAmuletCoin
	waitfanfare
	waitmessage
	giveitem ITEM_AMULET_COIN
	closemessage
	msgbox gText_HopeYouPlayLottoAgain, MSGBOX_AUTOCLOSE
	release
	end

Common_Lottery_EventScript_LottoWinNeoBattery::
	playfanfare MUS_OBTAIN_SYMBOL
	message gText_PlayerWonNeoBattery
	waitfanfare
	waitmessage
	giveitem ITEM_NEO_BATTERY
	closemessage
	msgbox gText_HopeYouPlayLottoAgain, MSGBOX_AUTOCLOSE
	release
	end

Common_Lottery_EventScript_NoLottoTickets::
	msgbox gText_NoLottoTickets, MSGBOX_AUTOCLOSE
	release
	end

Common_Lottery_EventScript_WantLottoTicket::
	delay 4
	showmoneybox 0, 0
	delay 4
	msgbox gText_WantLottoTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_Lottery_EventScript_HideMoneyReleaseOut
	checkmoney 5000
	goto_if_eq VAR_RESULT, FALSE, Common_Lottery_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 5000
	updatemoneybox
	delay 40
	hidemoneybox
	giveitem ITEM_MYSTIC_TICKET
	closemessage
	goto Common_Lottery_EventScript_WantLottoTicket
	release
	end

Common_Lottery_EventScript_ReleaseOut::
	release
	end

Common_Lottery_EventScript_HideMoneyReleaseOut::
	hidemoneybox
	closemessage
	release
	end

Common_Lottery_EventScript_NotEnoughMoney::
	hidemoneybox
	msgbox gText_NoLottoMoney, MSGBOX_AUTOCLOSE
	release
	end

Common_Lottery_EventScript_PrizeExplanation::
	msgbox gText_LottoPrizes, MSGBOX_AUTOCLOSE
	release
	end

Common_Lottery_EventScript_LotteryClerkOLD::
	lock
	faceplayer
	dotimebasedevents
	goto_if_ne VAR_POKELOT_PRIZE_ITEM, ITEM_NONE, Common_Lottery_EventScript_GivePrizeFromEarlier
	goto_if_set FLAG_DAILY_PICKED_LOTO_TICKET, Common_Lottery_EventScript_ComeBackTomorrow
	msgbox Common_Lottery_Text_LotteryCornerDrawTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_Lottery_EventScript_PleaseVisitAgain
	setflag FLAG_DAILY_PICKED_LOTO_TICKET
	message Common_Lottery_Text_PleasePickTicket
	waitmessage
	special RetrieveLotteryNumber
	copyvar VAR_0x8008, VAR_RESULT
	special BufferLottoTicketNumber
	msgbox Common_Lottery_Text_TicketNumberIsXPleaseWait, MSGBOX_DEFAULT
	applymovement LOCALID_LOTTERY_CLERK, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	playse SE_CONTEST_MONS_TURN
	special PickLotteryCornerTicket
	delay 220
	applymovement LOCALID_LOTTERY_CLERK, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_eq VAR_0x8004, 0, Common_Lottery_EventScript_NoMatch
	incrementgamestat GAME_STAT_WON_POKEMON_LOTTERY
	call_if_eq VAR_0x8006, 0, Common_Lottery_EventScript_TicketMatchPartyMon
	call_if_eq VAR_0x8006, 1, Common_Lottery_EventScript_TicketMatchPCMon
	bufferitemname STR_VAR_1, VAR_0x8005
	call_if_eq VAR_0x8004, 1, Common_Lottery_EventScript_TwoDigitMatch
	call_if_eq VAR_0x8004, 2, Common_Lottery_EventScript_ThreeDigitMatch
	call_if_eq VAR_0x8004, 3, Common_Lottery_EventScript_FourDigitMatch
	call_if_eq VAR_0x8004, 4, Common_Lottery_EventScript_FullMatch
	giveitem VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, Common_Lottery_EventScript_RecordPrizeNoRoom
	special TryPutLotteryWinnerReportOnAir
	goto Common_Lottery_EventScript_PleaseVisitAgain2
	end

Common_Lottery_EventScript_TicketMatchPartyMon::
	msgbox Common_Lottery_Text_TicketMatchesPartyMon, MSGBOX_DEFAULT
	return

Common_Lottery_EventScript_TicketMatchPCMon::
	msgbox Common_Lottery_Text_TicketMatchesPCMon, MSGBOX_DEFAULT
	return

Common_Lottery_EventScript_ComeBackTomorrow::
	msgbox Common_Lottery_Text_ComeBackTomorrow, MSGBOX_DEFAULT
	release
	end

Common_Lottery_EventScript_PleaseVisitAgain::
	msgbox Common_Lottery_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

Common_Lottery_EventScript_NoMatch::
	msgbox Common_Lottery_Text_NoNumbersMatched, MSGBOX_DEFAULT
	goto Common_Lottery_EventScript_PleaseVisitAgain2
	end

Common_Lottery_EventScript_PleaseVisitAgain2::
	msgbox Common_Lottery_Text_PleaseVisitAgain2, MSGBOX_DEFAULT
	release
	end

Common_Lottery_EventScript_TwoDigitMatch::
	msgbox Common_Lottery_Text_TwoDigitsMatched, MSGBOX_DEFAULT
	return

Common_Lottery_EventScript_ThreeDigitMatch::
	msgbox Common_Lottery_Text_ThreeDigitsMatched, MSGBOX_DEFAULT
	return

Common_Lottery_EventScript_FourDigitMatch::
	msgbox Common_Lottery_Text_FourDigitsMatched, MSGBOX_DEFAULT
	return

Common_Lottery_EventScript_FullMatch::
	msgbox Common_Lottery_Text_AllFiveDigitsMatched, MSGBOX_DEFAULT
	return

Common_Lottery_EventScript_RecordPrizeNoRoom::
	copyvar VAR_POKELOT_PRIZE_PLACE, VAR_0x8004
	copyvar VAR_POKELOT_PRIZE_ITEM, VAR_0x8005
	goto Common_Lottery_EventScript_NoRoomForPrize
	end

Common_Lottery_EventScript_NoRoomForPrize::
	msgbox Common_Lottery_Text_NoRoomForThis, MSGBOX_DEFAULT
	release
	end

Common_Lottery_EventScript_GivePrizeFromEarlier::
	msgbox Common_Lottery_Text_PrizeWeveBeenHolding, MSGBOX_DEFAULT
	giveitem VAR_POKELOT_PRIZE_ITEM
	goto_if_eq VAR_RESULT, FALSE, Common_Lottery_EventScript_NoRoomForPrize
	copyvar VAR_0x8004, VAR_POKELOT_PRIZE_PLACE
	copyvar VAR_0x8005, VAR_POKELOT_PRIZE_ITEM
	special TryPutLotteryWinnerReportOnAir
	setvar VAR_POKELOT_PRIZE_ITEM, ITEM_NONE
	setvar VAR_POKELOT_PRIZE_PLACE, 0
	release
	end

Common_EventScript_TannerShop::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 0, Common_EventScript_TannerShop0Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 1, Common_EventScript_TannerShop1Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 2, Common_EventScript_TannerShop2Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 3, Common_EventScript_TannerShop3Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 4, Common_EventScript_TannerShop4Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 5, Common_EventScript_TannerShop5Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 6, Common_EventScript_TannerShop6Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 7, Common_EventScript_TannerShop7Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 8, Common_EventScript_TannerShop8Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 9, Common_EventScript_TannerShop9Progress
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 10, Common_EventScript_TannerShop10Progress
	goto_if_gt VAR_PISCES_STORY_PROGRESS, 10, Common_EventScript_TannerShop10Progress
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Common_EventScript_TannerShop0Progress::
	pokemart Common_Mart_TannerShop0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop0:
	.2byte ITEM_SODA_POP
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop1Progress::
	pokemart Common_Mart_TannerShop1
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop1:
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop2Progress::
	pokemart Common_Mart_TannerShop2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop2:
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop3Progress::
	pokemart Common_Mart_TannerShop3
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop3:
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop4Progress::
	pokemart Common_Mart_TannerShop4
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop4:
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_RELAXANT
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop5Progress::
	pokemart Common_Mart_TannerShop5
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop5:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ELIXIR
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_RELAXANT
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop6Progress::
	pokemart Common_Mart_TannerShop6
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop6:
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ELIXIR
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_RELAXANT
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop7Progress::
	pokemart Common_Mart_TannerShop7
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop7:
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_ELIXIR
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ELIXIR
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_RELAXANT
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop8Progress::
	pokemart Common_Mart_TannerShop8
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop8:
	.2byte ITEM_MAX_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_ELIXIR
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ELIXIR
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_RELAXANT
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop9Progress::
	pokemart Common_Mart_TannerShop9
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop9:
	.2byte ITEM_MAX_POTION
	.2byte ITEM_MAX_REVIVE
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_ELIXIR
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ELIXIR
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_RELAXANT
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_NONE
	release
	end

Common_EventScript_TannerShop10Progress::
	pokemart Common_Mart_TannerShop10
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_TannerShop10:
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_MAX_REVIVE
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_ELIXIR
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ELIXIR
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_RELAXANT
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_NONE
	release
	end

Common_EventScript_KodoughShop::
	lock
	faceplayer
	message gText_KodoughAtCounter
	waitmessage
	goto Common_EventScript_KodoughInventory
	msgbox gText_KodoughGoodbye, MSGBOX_DEFAULT
	release
	end

Common_EventScript_KodoughInventory::
	pokemart Common_Mart_KodoughShop
	msgbox gText_KodoughGoodbye, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_KodoughShop:
	.2byte ITEM_DOUGH_STICK
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_POTION
	.2byte ITEM_MAX_REVIVE
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_ELIXIR
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ELIXIR
	.2byte ITEM_MAX_ETHER
	.2byte ITEM_REVIVE
	.2byte ITEM_POTION
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ETHER
	.2byte ITEM_SODA_POP
	.2byte ITEM_POKE_BALL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_REPEL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_RELAXANT
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop::
	lock
	faceplayer
	message gText_WhatDoYouWant
	waitmessage
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 0, Common_EventScript_BallShop0Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 1, Common_EventScript_BallShop1Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 2, Common_EventScript_BallShop2Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 3, Common_EventScript_BallShop2Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 4, Common_EventScript_BallShop3Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 5, Common_EventScript_BallShop4Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 6, Common_EventScript_BallShop5Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 7, Common_EventScript_BallShop6Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 8, Common_EventScript_BallShop7Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 9, Common_EventScript_BallShop8Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 10, Common_EventScript_BallShop8Badge
	goto_if_eq VAR_PISCES_STORY_PROGRESS, 11, Common_EventScript_BallShop8Badge
	goto_if_ge VAR_PISCES_STORY_PROGRESS, 12, Common_EventScript_BallShop8Badge
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

Common_EventScript_BallShop0Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop0B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop0B1Q

Common_EventScript_BallShop0B0Q::
	pokemart Common_Mart_BallShop0B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop0B0Q:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop0B1Q::
	pokemart Common_Mart_BallShop0B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop0B1Q:
	.2byte ITEM_LURE_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop1Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop1B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop1B1Q
	goto_if_eq VAR_BALL_QUEST_STATE, 2, Common_EventScript_BallShop1B2Q

Common_EventScript_BallShop1B0Q::
	pokemart Common_Mart_BallShop1B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop1B0Q:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop1B1Q::
	pokemart Common_Mart_BallShop1B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop1B1Q:
	.2byte ITEM_LURE_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop1B2Q::
	pokemart Common_Mart_BallShop1B2Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop1B2Q:
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop2Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop2B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop2B1Q
	goto_if_eq VAR_BALL_QUEST_STATE, 2, Common_EventScript_BallShop2B2Q
	goto_if_eq VAR_BALL_QUEST_STATE, 3, Common_EventScript_BallShop2B3Q
	goto_if_eq VAR_BALL_QUEST_STATE, 4, Common_EventScript_BallShop2B4Q

Common_EventScript_BallShop2B0Q::
	pokemart Common_Mart_BallShop2B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop2B0Q:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop2B1Q::
	pokemart Common_Mart_BallShop2B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop2B1Q:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop2B2Q::
	pokemart Common_Mart_BallShop2B2Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop2B2Q:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop2B3Q::
	pokemart Common_Mart_BallShop2B3Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop2B3Q:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop2B4Q::
	pokemart Common_Mart_BallShop2B4Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop2B4Q:
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop3Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop3B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop3B1Q
	goto_if_eq VAR_BALL_QUEST_STATE, 2, Common_EventScript_BallShop3B2Q
	goto_if_eq VAR_BALL_QUEST_STATE, 3, Common_EventScript_BallShop3B3Q
	goto_if_eq VAR_BALL_QUEST_STATE, 4, Common_EventScript_BallShop3B4Q
	goto_if_eq VAR_BALL_QUEST_STATE, 5, Common_EventScript_BallShop3B5Q
	goto_if_eq VAR_BALL_QUEST_STATE, 6, Common_EventScript_BallShop3B6Q

Common_EventScript_BallShop3B0Q::
	pokemart Common_Mart_BallShop3B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop3B0Q:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop3B1Q::
	pokemart Common_Mart_BallShop3B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop3B1Q:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop3B2Q::
	pokemart Common_Mart_BallShop3B2Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop3B2Q:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop3B3Q::
	pokemart Common_Mart_BallShop3B3Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop3B3Q:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop3B4Q::
	pokemart Common_Mart_BallShop3B4Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop3B4Q:
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop3B5Q::
	pokemart Common_Mart_BallShop3B5Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop3B5Q:
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop3B6Q::
	pokemart Common_Mart_BallShop3B6Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop3B6Q:
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop4B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop4B1Q
	goto_if_eq VAR_BALL_QUEST_STATE, 2, Common_EventScript_BallShop4B2Q
	goto_if_eq VAR_BALL_QUEST_STATE, 3, Common_EventScript_BallShop4B3Q
	goto_if_eq VAR_BALL_QUEST_STATE, 4, Common_EventScript_BallShop4B4Q
	goto_if_eq VAR_BALL_QUEST_STATE, 5, Common_EventScript_BallShop4B5Q
	goto_if_eq VAR_BALL_QUEST_STATE, 6, Common_EventScript_BallShop4B6Q
	goto_if_eq VAR_BALL_QUEST_STATE, 7, Common_EventScript_BallShop4B7Q
	goto_if_eq VAR_BALL_QUEST_STATE, 8, Common_EventScript_BallShop4B8Q
	goto_if_eq VAR_BALL_QUEST_STATE, 9, Common_EventScript_BallShop4B9Q

Common_EventScript_BallShop4B0Q::
	pokemart Common_Mart_BallShop4B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B0Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B1Q::
	pokemart Common_Mart_BallShop4B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B1Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B2Q::
	pokemart Common_Mart_BallShop4B2Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B2Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B3Q::
	pokemart Common_Mart_BallShop4B3Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B3Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B4Q::
	pokemart Common_Mart_BallShop4B4Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B4Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B5Q::
	pokemart Common_Mart_BallShop4B5Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B5Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B6Q::
	pokemart Common_Mart_BallShop4B6Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B6Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B7Q::
	pokemart Common_Mart_BallShop4B7Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B7Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B8Q::
	pokemart Common_Mart_BallShop4B8Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B8Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop4B9Q::
	pokemart Common_Mart_BallShop4B9Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop4B9Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop5B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop5B1Q
	goto_if_eq VAR_BALL_QUEST_STATE, 2, Common_EventScript_BallShop5B2Q
	goto_if_eq VAR_BALL_QUEST_STATE, 3, Common_EventScript_BallShop5B3Q
	goto_if_eq VAR_BALL_QUEST_STATE, 4, Common_EventScript_BallShop5B4Q
	goto_if_eq VAR_BALL_QUEST_STATE, 5, Common_EventScript_BallShop5B5Q
	goto_if_eq VAR_BALL_QUEST_STATE, 6, Common_EventScript_BallShop5B6Q
	goto_if_eq VAR_BALL_QUEST_STATE, 7, Common_EventScript_BallShop5B7Q
	goto_if_eq VAR_BALL_QUEST_STATE, 8, Common_EventScript_BallShop5B8Q
	goto_if_eq VAR_BALL_QUEST_STATE, 9, Common_EventScript_BallShop5B9Q
	goto_if_eq VAR_BALL_QUEST_STATE, 10, Common_EventScript_BallShop5B10Q
	goto_if_eq VAR_BALL_QUEST_STATE, 11, Common_EventScript_BallShop5B11Q

Common_EventScript_BallShop5B0Q::
	pokemart Common_Mart_BallShop5B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B0Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B1Q::
	pokemart Common_Mart_BallShop5B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B1Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B2Q::
	pokemart Common_Mart_BallShop5B2Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B2Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B3Q::
	pokemart Common_Mart_BallShop5B3Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B3Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B4Q::
	pokemart Common_Mart_BallShop5B4Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B4Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B5Q::
	pokemart Common_Mart_BallShop5B5Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B5Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B6Q::
	pokemart Common_Mart_BallShop5B6Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B6Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B7Q::
	pokemart Common_Mart_BallShop5B7Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B7Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B8Q::
	pokemart Common_Mart_BallShop5B8Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B8Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B9Q::
	pokemart Common_Mart_BallShop5B9Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B9Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B10Q::
	pokemart Common_Mart_BallShop5B10Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B10Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop5B11Q::
	pokemart Common_Mart_BallShop5B11Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop5B11Q:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop6B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop6B1Q
	goto_if_eq VAR_BALL_QUEST_STATE, 2, Common_EventScript_BallShop6B2Q
	goto_if_eq VAR_BALL_QUEST_STATE, 3, Common_EventScript_BallShop6B3Q
	goto_if_eq VAR_BALL_QUEST_STATE, 4, Common_EventScript_BallShop6B4Q
	goto_if_eq VAR_BALL_QUEST_STATE, 5, Common_EventScript_BallShop6B5Q
	goto_if_eq VAR_BALL_QUEST_STATE, 6, Common_EventScript_BallShop6B6Q
	goto_if_eq VAR_BALL_QUEST_STATE, 7, Common_EventScript_BallShop6B7Q
	goto_if_eq VAR_BALL_QUEST_STATE, 8, Common_EventScript_BallShop6B8Q
	goto_if_eq VAR_BALL_QUEST_STATE, 9, Common_EventScript_BallShop6B9Q
	goto_if_eq VAR_BALL_QUEST_STATE, 10, Common_EventScript_BallShop6B10Q
	goto_if_eq VAR_BALL_QUEST_STATE, 11, Common_EventScript_BallShop6B11Q
	goto_if_eq VAR_BALL_QUEST_STATE, 12, Common_EventScript_BallShop6B12Q
	goto_if_eq VAR_BALL_QUEST_STATE, 13, Common_EventScript_BallShop6B13Q

Common_EventScript_BallShop6B0Q::
	pokemart Common_Mart_BallShop6B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B0Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B1Q::
	pokemart Common_Mart_BallShop6B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B1Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B2Q::
	pokemart Common_Mart_BallShop6B2Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B2Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B3Q::
	pokemart Common_Mart_BallShop6B3Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B3Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B4Q::
	pokemart Common_Mart_BallShop6B4Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B4Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B5Q::
	pokemart Common_Mart_BallShop6B5Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B5Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B6Q::
	pokemart Common_Mart_BallShop6B6Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B6Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B7Q::
	pokemart Common_Mart_BallShop6B7Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B7Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B8Q::
	pokemart Common_Mart_BallShop6B8Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B8Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B9Q::
	pokemart Common_Mart_BallShop6B9Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B9Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B10Q::
	pokemart Common_Mart_BallShop6B10Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B10Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B11Q::
	pokemart Common_Mart_BallShop6B11Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B11Q:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B12Q::
	pokemart Common_Mart_BallShop6B12Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B12Q:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_COOL_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop6B13Q::
	pokemart Common_Mart_BallShop6B13Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop6B13Q:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_COOL_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop7B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop7B1Q
	goto_if_eq VAR_BALL_QUEST_STATE, 2, Common_EventScript_BallShop7B2Q
	goto_if_eq VAR_BALL_QUEST_STATE, 3, Common_EventScript_BallShop7B3Q
	goto_if_eq VAR_BALL_QUEST_STATE, 4, Common_EventScript_BallShop7B4Q
	goto_if_eq VAR_BALL_QUEST_STATE, 5, Common_EventScript_BallShop7B5Q
	goto_if_eq VAR_BALL_QUEST_STATE, 6, Common_EventScript_BallShop7B6Q
	goto_if_eq VAR_BALL_QUEST_STATE, 7, Common_EventScript_BallShop7B7Q
	goto_if_eq VAR_BALL_QUEST_STATE, 8, Common_EventScript_BallShop7B8Q
	goto_if_eq VAR_BALL_QUEST_STATE, 9, Common_EventScript_BallShop7B9Q
	goto_if_eq VAR_BALL_QUEST_STATE, 10, Common_EventScript_BallShop7B10Q
	goto_if_eq VAR_BALL_QUEST_STATE, 11, Common_EventScript_BallShop7B11Q
	goto_if_eq VAR_BALL_QUEST_STATE, 12, Common_EventScript_BallShop7B12Q
	goto_if_eq VAR_BALL_QUEST_STATE, 13, Common_EventScript_BallShop7B13Q

Common_EventScript_BallShop7B0Q::
	pokemart Common_Mart_BallShop7B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B0Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B1Q::
	pokemart Common_Mart_BallShop7B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B1Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B2Q::
	pokemart Common_Mart_BallShop7B2Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B2Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B3Q::
	pokemart Common_Mart_BallShop7B3Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B3Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B4Q::
	pokemart Common_Mart_BallShop7B4Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B4Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B5Q::
	pokemart Common_Mart_BallShop7B5Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B5Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B6Q::
	pokemart Common_Mart_BallShop7B6Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B6Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B7Q::
	pokemart Common_Mart_BallShop7B7Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B7Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B8Q::
	pokemart Common_Mart_BallShop7B8Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B8Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B9Q::
	pokemart Common_Mart_BallShop7B9Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B9Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B10Q::
	pokemart Common_Mart_BallShop7B10Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B10Q:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B11Q::
	pokemart Common_Mart_BallShop7B11Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B11Q:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B12Q::
	pokemart Common_Mart_BallShop7B12Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B12Q:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_COOL_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop7B13Q::
	pokemart Common_Mart_BallShop7B13Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop7B13Q:
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_COOL_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8Badge::
	goto_if_eq VAR_BALL_QUEST_STATE, 0, Common_EventScript_BallShop8B0Q
	goto_if_eq VAR_BALL_QUEST_STATE, 1, Common_EventScript_BallShop8B1Q
	goto_if_eq VAR_BALL_QUEST_STATE, 2, Common_EventScript_BallShop8B2Q
	goto_if_eq VAR_BALL_QUEST_STATE, 3, Common_EventScript_BallShop8B3Q
	goto_if_eq VAR_BALL_QUEST_STATE, 4, Common_EventScript_BallShop8B4Q
	goto_if_eq VAR_BALL_QUEST_STATE, 5, Common_EventScript_BallShop8B5Q
	goto_if_eq VAR_BALL_QUEST_STATE, 6, Common_EventScript_BallShop8B6Q
	goto_if_eq VAR_BALL_QUEST_STATE, 7, Common_EventScript_BallShop8B7Q
	goto_if_eq VAR_BALL_QUEST_STATE, 8, Common_EventScript_BallShop8B8Q
	goto_if_eq VAR_BALL_QUEST_STATE, 9, Common_EventScript_BallShop8B9Q
	goto_if_eq VAR_BALL_QUEST_STATE, 10, Common_EventScript_BallShop8B10Q
	goto_if_eq VAR_BALL_QUEST_STATE, 11, Common_EventScript_BallShop8B11Q
	goto_if_eq VAR_BALL_QUEST_STATE, 12, Common_EventScript_BallShop8B12Q
	goto_if_eq VAR_BALL_QUEST_STATE, 13, Common_EventScript_BallShop8B13Q
	goto_if_eq VAR_BALL_QUEST_STATE, 14, Common_EventScript_BallShop8B14Q

Common_EventScript_BallShop8B0Q::
	pokemart Common_Mart_BallShop8B0Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B0Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B1Q::
	pokemart Common_Mart_BallShop8B1Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B1Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B2Q::
	pokemart Common_Mart_BallShop8B2Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B2Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B3Q::
	pokemart Common_Mart_BallShop8B3Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B3Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B4Q::
	pokemart Common_Mart_BallShop8B4Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B4Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B5Q::
	pokemart Common_Mart_BallShop8B5Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B5Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B6Q::
	pokemart Common_Mart_BallShop8B6Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B6Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B7Q::
	pokemart Common_Mart_BallShop8B7Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B7Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B8Q::
	pokemart Common_Mart_BallShop8B8Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B8Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B9Q::
	pokemart Common_Mart_BallShop8B9Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B9Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B10Q::
	pokemart Common_Mart_BallShop8B10Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B10Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B11Q::
	pokemart Common_Mart_BallShop8B11Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B11Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B12Q::
	pokemart Common_Mart_BallShop8B12Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B12Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_COOL_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B13Q::
	pokemart Common_Mart_BallShop8B13Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B13Q:
	.2byte ITEM_PARK_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_COOL_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BallShop8B14Q::
	pokemart Common_Mart_BallShop8B14Q
	msgbox gText_SafeTravels, MSGBOX_DEFAULT
	release
	end

	.align 2
Common_Mart_BallShop8B14Q:
	.2byte ITEM_CHERISH_BALL
	.2byte ITEM_PARK_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_SAFARI_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_COOL_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_POKE_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_NONE
	release
	end

Common_EventScript_BufferTrendyPhrase::
	dotimebasedevents
	setvar VAR_0x8004, 0
	special BufferTrendyPhraseString
	return

EventScript_BackupMrBrineyLocation::
	copyvar VAR_0x8008, VAR_BRINEY_LOCATION
	setvar VAR_BRINEY_LOCATION, 0
	return

	.include "data/scripts/surf.inc"
	.include "data/scripts/rival_graphics.inc"
	.include "data/scripts/set_gym_trainers.inc"

Common_EventScript_ShowBagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

Common_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	return

Common_EventScript_ShowNoRoomForDecor::
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	release
	end

Common_EventScript_NoRoomForDecor::
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	return

Common_EventScript_SetAbnormalWeather::
	setweather WEATHER_ABNORMAL
	return

Common_EventScript_PlayGymBadgeFanfare::
	playfanfare MUS_OBTAIN_BADGE
	waitfanfare
	return

Common_EventScript_OutOfCenterPartyHeal::
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	fadescreen FADE_FROM_BLACK
	return

EventScript_RegionMap::
	lockall
	msgbox Common_Text_LookCloserAtMap, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special FieldShowRegionMap
	waitstate
	releaseall
	end

Common_EventScript_PlayBrineysBoatMusic::
	setflag FLAG_DONT_TRANSITION_MUSIC
	playbgm MUS_SAILING, FALSE
	return

Common_EventScript_StopBrineysBoatMusic::
	clearflag FLAG_DONT_TRANSITION_MUSIC
	fadedefaultbgm
	return

	.include "data/scripts/prof_birch.inc"

@ Below could be split as ferry.inc aside from the Rusturf tunnel script
Common_EventScript_FerryDepart::
	delay 60
	applymovement VAR_0x8004, Movement_FerryDepart
	waitmovement 0
	return

Movement_FerryDepart:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

EventScript_HideMrBriney::
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 0
	return

RusturfTunnel_EventScript_SetRusturfTunnelOpen::
	removeobject LOCALID_WANDAS_BF
	removeobject LOCALID_WANDA
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WANDA
	setvar VAR_RUSTURF_TUNNEL_STATE, 6
	setflag FLAG_RUSTURF_TUNNEL_OPENED
	return

EventScript_UnusedBoardFerry::
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	showobjectat OBJ_EVENT_ID_PLAYER, 0
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, Movement_UnusedBoardFerry
	waitmovement 0
	delay 30
	return

Movement_UnusedBoardFerry:
	walk_up
	step_end

Common_EventScript_FerryDepartIsland::
	call_if_eq VAR_FACING, DIR_SOUTH, Ferry_EventScript_DepartIslandSouth
	call_if_eq VAR_FACING, DIR_WEST, Ferry_EventScript_DepartIslandWest
	delay 30
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	call Common_EventScript_FerryDepart
	return

	.include "data/scripts/cave_of_origin.inc"
	.include "data/scripts/kecleon.inc"

Common_EventScript_NameReceivedPartyMon::
	fadescreen FADE_TO_BLACK
	special ChangePokemonNickname
	waitstate
	return

Common_EventScript_PlayerHandedOverTheItem::
	bufferitemname STR_VAR_1, VAR_0x8004
	playfanfare MUS_OBTAIN_TMHM
	message gText_PlayerHandedOverTheItem
	waitmessage
	waitfanfare
	removeitem VAR_0x8004
	return

	.include "data/scripts/elite_four.inc"
	.include "data/scripts/movement.inc"
	.include "data/scripts/check_furniture.inc"
	.include "data/text/record_mix.inc"
	.include "data/text/pc.inc"
	.include "data/text/pkmn_center_nurse.inc"
	.include "data/text/mart_clerk.inc"
	.include "data/text/obtain_item.inc"

@ The below and surf.inc could be split into some text/notices.inc
gText_PokemartSign::
	.string "“Selected items for your convenience!”\n"
	.string "POKéMON MART$"

gText_PokemonCenterSign::
	.string "“Rejuvenate your tired partners!”\n"
	.string "POKéMON CENTER$"

gText_MomOrDadMightLikeThisProgram::
	.string "{STR_VAR_1} might like this program.\n"
	.string "… … … … … … … … … … … … … … … …\p"
	.string "Better get going!$"

gText_WhichFloorWouldYouLike::
	.string "Welcome to LILYCOVE DEPARTMENT STORE.\p"
	.string "Which floor would you like?$"

gText_SandstormIsVicious::
	.string "The sandstorm is vicious.\n"
	.string "It's impossible to keep going.$"

gText_SelectWithoutRegisteredItem::
	.string "An item in the BAG can be\n"
	.string "registered to SELECT for easy use.$"

gText_PokemonTrainerSchoolEmail::
	.string "There's an e-mail from POKéMON TRAINER\n"
	.string "SCHOOL.\p"
	.string "… … … … … …\p"
	.string "A POKéMON may learn up to four moves.\p"
	.string "A TRAINER's expertise is tested on the\n"
	.string "move sets chosen for POKéMON.\p"
	.string "… … … … … …$"

gText_PlayerHouseBootPC::
	.string "{PLAYER} booted up the PC.$"

gText_PokeblockLinkCanceled::
	.string "The link was canceled.$"

gText_UnusedNicknameReceivedPokemon::
	.string "Want to give a nickname to\n"
	.string "the {STR_VAR_2} you received?$"

gText_PlayerWhitedOut::
	.string "{PLAYER} is out of usable\n"
	.string "POKéMON!\p{PLAYER} whited out!$"

gText_RegisteredTrainerinPokeNav::
	.string "Registered {STR_VAR_1} {STR_VAR_2}\n"
	.string "in the POKéNAV.$"

gText_ComeBackWithSecretPower::
	.string "Do you know the TM SECRET POWER?\p"
	.string "Our group, we love the TM SECRET\n"
	.string "POWER.\p"
	.string "One of our members will give it to you.\n"
	.string "Come back and show me if you get it.\p"
	.string "We'll accept you as a member and sell\n"
	.string "you good stuff in secrecy.$"

gText_PokerusExplanation::
	.string "Your POKéMON may be infected with\n"
	.string "POKéRUS.\p"
	.string "Little is known about the POKéRUS\n"
	.string "except that they are microscopic life-\l"
	.string "forms that attach to POKéMON.\p"
	.string "While infected, POKéMON are said to\n"
	.string "grow exceptionally well.$"

gText_WelcomeToLottery:
	.string "Welcome to the Lottery Corner!$"

gText_WhatLottoThingYouWant:
	.string "What do you want to do?$"

gText_LottoIntroduction:
	.string "Ah! I haven't seen your face\n"
	.string "before. Let me explain to you\l"
	.string "how the Lottery Corner works!\p"
	.string "It's pretty simple. You can buy\n"
	.string "Lottery Tickets and spend them\l"
	.string "on Lottery Pulls! We will run\l"
	.string "the Lottery Pull immediately after\l"
	.string "you spend a Ticket. A number\l"
	.string "will then be rolled between\l"
	.string "1 and 1000. Depending on that number,\l"
	.string "you can win fabulous prizes!\p"
	.string "Here are three tickets on\n"
	.string "the house to get you started!$"

gText_LotteryGiveFreeTicket:
	.string "The staff at the Center has\n"
	.string "been keeping track of your badges!\l"
	.string "Seems like you picked up a new one.\p"
	.string "You can have this free ticket\n"
	.string "in the name of encouragement!$"

gText_WillYouSpendALottoTicket:
	.string "You would like to do a\n"
	.string "Lottery Pull? That will cost\l"
	.string "you one Lottery Ticket!$"

gText_LetsDrawYourNumber:
	.string "Alright then! I'll\n"
	.string "take your Ticket...\p"
	.string "Let's draw your number!$"

gText_PlayerWonNothing:
	.string "Aw, too bad! Your number\n"
	.string "matches none of our prize numbers!$"

gText_PlayerWonBeastBall:
	.string "Your number has an 8 in it! That's\n"
	.string "enough for a third tier prize...!$"

gText_PlayerWonAmuletCoin:
	.string "Your number has two 2s in it! That's\n"
	.string "enough for a second tier prize...!$"

gText_PlayerWonNeoBattery:
	.string "Incredible! You rolled a 777!\n"
	.string "That's a first tier prize!$"

gText_HopeYouPlayLottoAgain:
	.string "We hope you come back\n"
	.string "to play the Lottery in the future!$"

gText_NoLottoTickets:
	.string "You don't have any Lottery Tickets!\n"
	.string "You can buy some with Pokedollars\l"
	.string "if you so wish.$"

gText_WantLottoTicket:
	.string "You would like a Lottery Ticket?\n"
	.string "That will cost you ¥5000.$"

gText_NoLottoMoney:
	.string "You don't have enough money\n"
	.string "for that! If you're that poor,\l"
	.string "errm, maybe you shouldn't\l"
	.string "be gambling...$"

gText_LottoPrizes:
	.string "We have three tiers of prizes!\p"
	.string "The third tier prize, for getting\n"
	.string "a number with an 8 in it,\l"
	.string "is a Beast Ball!\l"
	.string "That's about a 1 in 10 chance.\p"
	.string "The second tier prize, for getting\n"
	.string "a number with two 2s in it,\l"
	.string "is an Amulet Coin!\l"
	.string "That's about a 1 in 100 chance.\p"
	.string "The first tier prize, for getting\n"
	.string "exactly the number 777,\l"
	.string "is a Neo Battery!\l"
	.string "That's about a 1 in 1000 chance.\p"
	.string "If you're lucky, you\n"
	.string "could win big!$"

	.include "data/text/surf.inc"

gText_DoorOpenedFarAway::
	.string "It sounded as if a door opened\n"
	.string "somewhere far away.$"

gText_BigHoleInTheWall::
	.string "There is a big hole in the wall.$"

gText_SorryWirelessClubAdjustments::
	.string "I'm terribly sorry.\n"
	.string "The POKéMON WIRELESS CLUB is\l"
	.string "undergoing adjustments now.$"

gText_UndergoingAdjustments::
	.string "It appears to be undergoing\n"
	.string "adjustments…$"

@ Unused
gText_SorryTradeCenterInspections::
	.string "I'm terribly sorry. The TRADE CENTER\n"
	.string "is undergoing inspections.$"

@ Unused
gText_SorryRecordCornerPreparation::
	.string "I'm terribly sorry. The RECORD CORNER\n"
	.string "is under preparation.$"

gText_PlayerHandedOverTheItem::
	.string "{PLAYER} handed over the\n"
	.string "{STR_VAR_1}.$"

gText_ThankYouForAccessingMysteryGift::
	.string "Thank you for accessing the\n"
	.string "MYSTERY GIFT System.$"

gText_PlayerFoundOneTMHM::
	.string "{PLAYER} found one {STR_VAR_1}\n"
	.string "{STR_VAR_2}!$"

gText_Sudowoodo_Attacked::
	.string "The weird tree doesn't like the\n"
	.string "WAILMER PAIL!\p"
	.string "The weird tree attacked!$"

gText_LegendaryFlewAway::
	.string "The {STR_VAR_1} flew away!$"

	.include "data/text/pc_transfer.inc"
	.include "data/text/questionnaire.inc"
	.include "data/text/abnormal_weather.inc"

EventScript_SelectWithoutRegisteredItem::
	msgbox gText_SelectWithoutRegisteredItem, MSGBOX_SIGN
	end

	.include "data/scripts/field_poison.inc"

Common_EventScript_NopReturn::
	return

@ Unused
EventScript_CableClub_SetVarResult1::
	setvar VAR_RESULT, 1
	return

EventScript_CableClub_SetVarResult0::
	setvar VAR_RESULT, 0
	return

Common_EventScript_UnionRoomAttendant::
	call CableClub_EventScript_UnionRoomAttendant
	end

Common_EventScript_WirelessClubAttendant::
	call CableClub_EventScript_WirelessClubAttendant
	end

Common_EventScript_DirectCornerAttendant::
	call CableClub_EventScript_DirectCornerAttendant
	end

Common_EventScript_RemoveStaticPokemon::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

Common_EventScript_LegendaryFlewAway::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	release
	end

	.include "data/scripts/pc_transfer.inc"
	.include "data/scripts/questionnaire.inc"
	.include "data/scripts/abnormal_weather.inc"
	.include "data/scripts/trainer_script.inc"
	.include "data/scripts/berry_tree.inc"
	.include "data/scripts/secret_base.inc"
	.include "data/scripts/cable_club.inc"
	.include "data/text/cable_club.inc"
	.include "data/scripts/contest_hall.inc"
	.include "data/text/contest_strings.inc"
	.include "data/text/contest_link.inc"
	.include "data/text/contest_painting.inc"
	.include "data/text/trick_house_mechadolls.inc"
	.include "data/scripts/tv.inc"
	.include "data/text/tv.inc"
	.include "data/scripts/interview.inc"
	.include "data/scripts/gabby_and_ty.inc"
	.include "data/text/pokemon_news.inc"
	.include "data/scripts/mauville_man.inc"
	.include "data/scripts/field_move_scripts.inc"
	.include "data/scripts/item_ball_scripts.inc"
	.include "data/scripts/profile_man.inc"
	.include "data/scripts/day_care.inc"
	.include "data/scripts/flash.inc"
	.include "data/scripts/players_house.inc"
	.include "data/scripts/berry_blender.inc"
	.include "data/text/mauville_man.inc"
	.include "data/text/trainers.inc"
	.include "data/scripts/repel.inc"
	.include "data/scripts/safari_zone.inc"
	.include "data/scripts/roulette.inc"
	.include "data/text/pokedex_rating.inc"
	.include "data/text/lottery_corner.inc"
	.include "data/text/event_ticket_1.inc"
	.include "data/text/braille.inc"
	.include "data/text/berries.inc"
	.include "data/text/shoal_cave.inc"
	.include "data/text/check_furniture.inc"
	.include "data/scripts/cave_hole.inc"
	.include "data/scripts/lilycove_lady.inc"
	.include "data/text/match_call.inc"
	.include "data/scripts/apprentice.inc"
	.include "data/text/apprentice.inc"
	.include "data/text/battle_dome.inc"
	.include "data/scripts/battle_pike.inc"
	.include "data/text/blend_master.inc"
	.include "data/text/battle_tent.inc"
	.include "data/text/event_ticket_2.inc"
	.include "data/text/move_tutors.inc"
	.include "data/scripts/move_tutors.inc"
	.include "data/scripts/trainer_hill.inc"
	.include "data/scripts/test_signpost.inc"
	.include "data/text/frontier_brain.inc"
	.include "data/text/save.inc"
	.include "data/text/birch_speech.inc"

	.include "data/maps/MangrottoTunnel/scripts.inc"

	.include "data/maps/ScuttillHuts/scripts.inc"

	.include "data/maps/TestMap/scripts.inc"

	.include "data/maps/CanopourWilds/scripts.inc"

	.include "data/maps/PerplumeMaze/scripts.inc"

	.include "data/maps/OzoneInstitute/scripts.inc"

	.include "data/maps/SweltornDesert/scripts.inc"

	.include "data/maps/MasoriedHike/scripts.inc"

	.include "data/maps/CrimneyClimb/scripts.inc"

	.include "data/maps/JaggroPass/scripts.inc"

	.include "data/maps/FallarborNew/scripts.inc"

	.include "data/maps/MauvilleNew/scripts.inc"

	.include "data/maps/CyclingRoad/scripts.inc"

	.include "data/maps/HatchloamField/scripts.inc"

	.include "data/maps/VerdanturfNew/scripts.inc"

	.include "data/maps/SeaMauville/scripts.inc"

	.include "data/maps/SlateportShore/scripts.inc"

	.include "data/maps/StraeSeapath/scripts.inc"

	.include "data/maps/SailorsPause/scripts.inc"

	.include "data/maps/NavigulfWaves/scripts.inc"

	.include "data/maps/DewfordNew/scripts.inc"

	.include "data/maps/DetermaniteBeach/scripts.inc"

	.include "data/maps/WishwellOcean/scripts.inc"

	.include "data/maps/LavaridgeInt/scripts.inc"

	.include "data/maps/SweltornPalace/scripts.inc"

	.include "data/maps/SweltornPalaceOutside/scripts.inc"

	.include "data/maps/SweltornTransitionCave/scripts.inc"

	.include "data/maps/ShoalCaveNewFloor1/scripts.inc"

	.include "data/maps/ShoalCaveNewFloor2/scripts.inc"

	.include "data/maps/SailorsPauseShips/scripts.inc"

	.include "data/maps/PetalburgNew/scripts.inc"

	.include "data/maps/RustburgWharf/scripts.inc"

	.include "data/maps/RustboroNew/scripts.inc"

	.include "data/maps/DetermaniteQuarry/scripts.inc"

	.include "data/maps/DetermaniteQuarB1F/scripts.inc"

	.include "data/maps/SkyPillarNew/scripts.inc"

	.include "data/maps/PetalburgWoodsNew/scripts.inc"

	.include "data/maps/OldaleNew/scripts.inc"

	.include "data/maps/NoviceWalk/scripts.inc"

	.include "data/maps/LittlerootNew/scripts.inc"

	.include "data/maps/PendingDev/scripts.inc"

	.include "data/maps/MidneorFalls/scripts.inc"

	.include "data/maps/WhisperCliff/scripts.inc"

	.include "data/maps/EverGrandeRoad/scripts.inc"

	.include "data/maps/EverGrandePeak/scripts.inc"

	.include "data/maps/CaveOfOrigin/scripts.inc"

	.include "data/maps/UnduraTunnels/scripts.inc"

	.include "data/maps/UnduraTunnelsDeep/scripts.inc"

	.include "data/maps/MidneorFallsCave/scripts.inc"

	.include "data/maps/MeteorNadir/scripts.inc"

	.include "data/maps/EverGrandeTransitionCave/scripts.inc"

	.include "data/maps/CrimneyCaldera/scripts.inc"

	.include "data/maps/Maintenance/scripts.inc"

	.include "data/maps/MaintenanceBondingArena/scripts.inc"

	.include "data/maps/NewMauvilleFloor1/scripts.inc"

	.include "data/maps/NewMauvilleFloor2/scripts.inc"

	.include "data/maps/NewMauvilleCenter1/scripts.inc"

	.include "data/maps/NewMauvilleCenter2/scripts.inc"

	.include "data/maps/Flotshore/scripts.inc"

	.include "data/maps/BirchMaritimeLab/scripts.inc"

	.include "data/maps/PacifidlogInteriors/scripts.inc"

	.include "data/maps/SkyPillarInteriors/scripts.inc"

	.include "data/maps/SSTidalInteriors/scripts.inc"

	.include "data/maps/LabBasement/scripts.inc"

	.include "data/maps/LabBasement2/scripts.inc"

	.include "data/maps/BasalinCoast/scripts.inc"

	.include "data/maps/RivalRoom/scripts.inc"

	.include "data/maps/SSTidalExterior/scripts.inc"

	.include "data/maps/NewSooto/scripts.inc"

	.include "data/maps/Gym1Corridor/scripts.inc"

	.include "data/maps/SootopolisInteriors/scripts.inc"

	.include "data/maps/SootoRestaurant/scripts.inc"

	.include "data/maps/CosmossSpaceCenter/scripts.inc"

	.include "data/maps/MossdeepInteriors/scripts.inc"

	.include "data/maps/Gym2Corridor/scripts.inc"

	.include "data/maps/StevenHouse/scripts.inc"

	.include "data/maps/StevenCorridor/scripts.inc"

	.include "data/maps/StevenMaze/scripts.inc"

	.include "data/maps/SecretMossdeepCave/scripts.inc"

	.include "data/maps/PrecipikeInteriors/scripts.inc"

	.include "data/maps/OzoneLilycoveHQ/scripts.inc"

	.include "data/maps/LilycoveInteriors/scripts.inc"

	.include "data/maps/LilycoveMuseumNew/scripts.inc"

	.include "data/maps/SSTidalMidgame/scripts.inc"

	.include "data/maps/SSTidalMidTeriors/scripts.inc"

	.include "data/maps/MangrottoRockSmashRoom/scripts.inc"

	.include "data/maps/TheColdMines/scripts.inc"

	.include "data/maps/PrettyPetalsScuttill/scripts.inc"

	.include "data/maps/ZotpyreGym/scripts.inc"

	.include "data/maps/ScuttillSecretTreeHouse/scripts.inc"

	.include "data/maps/Gym3Corridor/scripts.inc"

	.include "data/maps/ZotpyreInteriors/scripts.inc"

	.include "data/maps/ZotpyreSecretBasement/scripts.inc"

	.include "data/maps/NewSunbeach/scripts.inc"

	.include "data/maps/FamilyMossCave/scripts.inc"

	.include "data/maps/BattleStudioLobby/scripts.inc"

	.include "data/maps/NewMap1/scripts.inc"

	.include "data/maps/BattleStudioStorage/scripts.inc"

	.include "data/maps/BattleStudioOffice/scripts.inc"

	.include "data/maps/BattleStudioFakeLobby/scripts.inc"

	.include "data/maps/BattleStudioFakeArena/scripts.inc"

	.include "data/maps/BattleStudioCages/scripts.inc"

	.include "data/maps/Gym4Corridor/scripts.inc"

	.include "data/maps/Gym5Corridor/scripts.inc"

	.include "data/maps/Gym6Corridor/scripts.inc"

	.include "data/maps/Gym7Corridor/scripts.inc"

	.include "data/maps/Gym8Corridor/scripts.inc"

	.include "data/maps/CultipexCave/scripts.inc"

	.include "data/maps/SweltornTransitionHallway/scripts.inc"

	.include "data/maps/NavigulfUnderwater/scripts.inc"

	.include "data/maps/SailorsPauseUnderwater/scripts.inc"

	.include "data/maps/StraeSeapathUnderwater/scripts.inc"

	.include "data/maps/FortreeGymNew/scripts.inc"

	.include "data/maps/FortreeTransitionArea/scripts.inc"

	.include "data/maps/FortreeGymBattleLocation/scripts.inc"

	.include "data/maps/LavaridgeGymNew/scripts.inc"

	.include "data/maps/LavaridgeHouses/scripts.inc"

	.include "data/maps/TrickHousePotRoom/scripts.inc"

	.include "data/maps/TrickHouseUpsideDownRoom/scripts.inc"

	.include "data/maps/TrickHouseMainPortion/scripts.inc"

	.include "data/maps/TrickHouseDarkRoom/scripts.inc"

	.include "data/maps/TrickHouseLeverRooms/scripts.inc"

	.include "data/maps/TrickHouseBallRoom/scripts.inc"

	.include "data/maps/TrickHouseEntrance/scripts.inc"

	.include "data/maps/NewMauvilleFloor2Rooms/scripts.inc"

	.include "data/maps/NewMauvilleRydelCycles/scripts.inc"

	.include "data/maps/OceanicMuseumNew/scripts.inc"

	.include "data/maps/SouthernIsland/scripts.inc"

	.include "data/maps/VerdanturfGym/scripts.inc"

	.include "data/maps/SlateportInteriors/scripts.inc"

	.include "data/maps/FossilShore/scripts.inc"

	.include "data/maps/FossilShoreHouses/scripts.inc"

	.include "data/maps/SmokingArea/scripts.inc"

	.include "data/maps/VerdanturfInteriors/scripts.inc"

	.include "data/maps/VerdanturfTransition/scripts.inc"

	.include "data/maps/HatchloamDayCare/scripts.inc"

	.include "data/maps/DewfordGymNew/scripts.inc"

	.include "data/maps/DewfordInteriors/scripts.inc"

	.include "data/maps/FortreeInteriors/scripts.inc"

	.include "data/maps/FallarborInteriors/scripts.inc"

	.include "data/maps/OzoneTransitionBuildings/scripts.inc"

	.include "data/maps/FortreeGymTransitionBuilding/scripts.inc"

	.include "data/maps/RustGymEntryHallways/scripts.inc"

	.include "data/maps/RustGymLockerHallway/scripts.inc"

	.include "data/maps/RustGymExtracurricularHallway/scripts.inc"

	.include "data/maps/RustGymCafeteria/scripts.inc"

	.include "data/maps/RustGymGym/scripts.inc"

	.include "data/maps/RustGymComputerLab/scripts.inc"

	.include "data/maps/RustGymLibrary/scripts.inc"

	.include "data/maps/RustGymClassroom/scripts.inc"

	.include "data/maps/RustGymDarkHallway/scripts.inc"

	.include "data/maps/RustGymDarkLockers/scripts.inc"

	.include "data/maps/RustGymDarkCafeteria/scripts.inc"

	.include "data/maps/RustGymDarkClassroom/scripts.inc"

	.include "data/maps/RustGymPrincipalsOffice/scripts.inc"

	.include "data/maps/SeasideCasino/scripts.inc"

	.include "data/maps/RustGymPrincipalsOfficeShort/scripts.inc"

	.include "data/maps/RustGymDarkCafeArena/scripts.inc"

	.include "data/maps/RustboroTransitionBuilding/scripts.inc"

	.include "data/maps/RustboroInteriors/scripts.inc"

	.include "data/maps/DevonCorp/scripts.inc"

	.include "data/maps/WallyArena/scripts.inc"

	.include "data/maps/WallyArenaLeadup/scripts.inc"

	.include "data/maps/LittlerootNormanHouse/scripts.inc"

	.include "data/maps/SeasideCasinoTheater/scripts.inc"

	.include "data/maps/SeasideCasinoBackrooms/scripts.inc"

	.include "data/maps/SeasideCasinoVIPLounges/scripts.inc"

	.include "data/maps/SeasideCasinoBattleRoom/scripts.inc"

	.include "data/maps/SouthMossdeep/scripts.inc"

	.include "data/maps/OzoneInt/scripts.inc"

	.include "data/maps/OzoneFloor2/scripts.inc"

	.include "data/maps/OzoneMattRoom/scripts.inc"

	.include "data/maps/OzoneTabithaRoom/scripts.inc"

	.include "data/maps/OzoneCourtneyRoom/scripts.inc"

	.include "data/maps/OzoneShellyRoom/scripts.inc"

	.include "data/maps/OzoneEliteFourHub/scripts.inc"

	.include "data/maps/OzoneMaxieArchieRoom/scripts.inc"

	.include "data/maps/PlaneInFlight/scripts.inc"

	.include "data/maps/OzoneSituationRoom/scripts.inc"

	.include "data/maps/OzoneOutsideCutscene/scripts.inc"

	.include "data/maps/EverGrandeRoadPC/scripts.inc"

	.include "data/maps/CaveOfOriginCutscene/scripts.inc"

	.include "data/maps/EverGrandeRestArea/scripts.inc"

	.include "data/maps/SweltornInteriors/scripts.inc"

	.include "data/maps/ShunyongBattleArena/scripts.inc"

	.include "data/maps/MirageIsland/scripts.inc"

	.include "data/maps/SootopolisCastle/scripts.inc"

	.include "data/maps/CanopourBushes/scripts.inc"

	.include "data/maps/PerplumeTreehouse/scripts.inc"

	.include "data/maps/FallarborSteeple/scripts.inc"

	.include "data/maps/FallarborSteepleInterior/scripts.inc"

	.include "data/maps/PiratesGrotto/scripts.inc"

	.include "data/maps/MuseumSanctum/scripts.inc"

	.include "data/maps/DetermaniteUnderwater/scripts.inc"

	.include "data/maps/ScuttillInteriors/scripts.inc"

	.include "data/maps/ShiftryArena/scripts.inc"

	.include "data/maps/SecretMeadow/scripts.inc"

	.include "data/maps/BasalinCave/scripts.inc"

	.include "data/maps/ArctaigaSpindaDen/scripts.inc"

	.include "data/maps/ChimneySpindaArea/scripts.inc"

	.include "data/maps/ScuttillSpindaDen/scripts.inc"

	.include "data/maps/SweltornSpindaDen/scripts.inc"

	.include "data/maps/AshlandsHouse/scripts.inc"

	.include "data/maps/CrimneyInteriors/scripts.inc"

	.include "data/maps/OldaleInteriors/scripts.inc"

	.include "data/maps/SlateportSodaShop/scripts.inc"

	.include "data/maps/SeasideCasinoEggGachaRoom/scripts.inc"

	.include "data/maps/PetalburgInteriors/scripts.inc"

	.include "data/maps/RustburgWharfHouse/scripts.inc"

	.include "data/maps/LittlerootNewHouseTwo/scripts.inc"

	.include "data/maps/PebblerLab/scripts.inc"

	.include "data/maps/SpaceCenterSiegeCutscene/scripts.inc"
