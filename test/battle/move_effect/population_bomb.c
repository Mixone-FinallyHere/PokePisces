#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Mass Attack can hit ten times")
{
    GIVEN {
        ASSUME(gBattleMoves[MOVE_POPULATION_BOMB].strikeCount == 10);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_POPULATION_BOMB); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POPULATION_BOMB, player);
        MESSAGE("Hit 10 time(s)!");
    }
}

TO_DO_BATTLE_TEST("Accuracy for Mass Attack is checked independently for each hit")
TO_DO_BATTLE_TEST("Accuracy for Mass Attack is only checked for the first hit with Skill Link")
TO_DO_BATTLE_TEST("Accuracy for Mass Attack is only checked for the first hit with Loaded Dice")
