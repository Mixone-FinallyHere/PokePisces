#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gBattleMoves[MOVE_POWDER_SNOW].effect == EFFECT_FREEZE_HIT);
}

SINGLE_BATTLE_TEST("Powder Snow inflicts frostbite")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_POWDER_SNOW); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POWDER_SNOW, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRS, opponent);
        STATUS_ICON(opponent, frostbite: TRUE);
    }
}

SINGLE_BATTLE_TEST("Powder Snow cannot frostbite an Ice-type")
{
    GIVEN {
        ASSUME(gSpeciesInfo[SPECIES_SNORUNT].types[0] == TYPE_ICE);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNORUNT);
    } WHEN {
        TURN { MOVE(player, MOVE_POWDER_SNOW); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POWDER_SNOW, player);
        HP_BAR(opponent);
        NOT ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRZ, opponent);
        NOT STATUS_ICON(opponent, freeze: TRUE);
    }
}
