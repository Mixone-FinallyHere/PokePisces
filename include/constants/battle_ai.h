#ifndef GUARD_CONSTANTS_BATTLE_AI_H
#define GUARD_CONSTANTS_BATTLE_AI_H

// battlers
#define AI_TARGET 0
#define AI_USER 1
#define AI_TARGET_PARTNER 2
#define AI_USER_PARTNER 3

// get_type command
#define AI_TYPE1_TARGET 0
#define AI_TYPE1_USER 1
#define AI_TYPE2_TARGET 2
#define AI_TYPE2_USER 3
#define AI_TYPE_MOVE 4

// type effectiveness
#define AI_EFFECTIVENESS_x8     7
#define AI_EFFECTIVENESS_x4     6
#define AI_EFFECTIVENESS_x2     5
#define AI_EFFECTIVENESS_x1     4
#define AI_EFFECTIVENESS_x0_5   3
#define AI_EFFECTIVENESS_x0_25  2
#define AI_EFFECTIVENESS_x0_125 1
#define AI_EFFECTIVENESS_x0     0

// ai weather
#define AI_WEATHER_NONE 0
#define AI_WEATHER_SUN 1
#define AI_WEATHER_RAIN 2
#define AI_WEATHER_SANDSTORM 3
#define AI_WEATHER_HAIL 4
#define AI_WEATHER_SNOW 5

// get_how_powerful_move_is
#define MOVE_POWER_OTHER  0
#define MOVE_POWER_BEST   1
#define MOVE_POWER_GOOD   2 // Similar dmg range with best.
#define MOVE_POWER_WEAK   3 // Significantly lower than best and good.

// AI Flags. Most run specific functions to update score, new flags are used for internal logic in other scripts
#define AI_FLAG_CHECK_BAD_MOVE        (1 << 0)
#define AI_FLAG_TRY_TO_FAINT          (1 << 1)
#define AI_FLAG_CHECK_VIABILITY       (1 << 2)
#define AI_FLAG_SETUP_FIRST_TURN      (1 << 3)
#define AI_FLAG_RISKY                 (1 << 4)
#define AI_FLAG_PREFER_STRONGEST_MOVE (1 << 5)
#define AI_FLAG_PREFER_BATON_PASS     (1 << 6)
#define AI_FLAG_DOUBLE_BATTLE         (1 << 7)   // removed, split between AI_FLAG_CHECK_BAD_MOVE & AI_FLAG_CHECK_GOOD_MOVE
#define AI_FLAG_HP_AWARE              (1 << 8)
// New, Trainer Handicap Flags
#define AI_FLAG_NEGATE_UNAWARE        (1 << 9)   // AI is NOT aware of negating effects like wonder room, mold breaker, etc
#define AI_FLAG_WILL_SUICIDE          (1 << 10)  // AI will use explosion / self destruct / final gambit / etc
// New, Trainer Strategy Flags
#define AI_FLAG_HELP_PARTNER          (1 << 11)  // AI can try to help partner. If not set, will tend not to target partner
#define AI_FLAG_PREFER_STATUS_MOVES   (1 << 12)  // AI gets a score bonus for status moves. Should be combined with AI_FLAG_CHECK_BAD_MOVE to prevent using only status moves
#define AI_FLAG_STALL                 (1 << 13)  // AI stalls battle and prefers secondary damage/trapping/etc. TODO not finished
#define AI_FLAG_SCREENER              (1 << 14)  // AI prefers screening effects like reflect, mist, etc. TODO unfinished
#define AI_FLAG_SMART_SWITCHING       (1 << 15)  // AI includes a lot more switching checks
#define AI_FLAG_ACE_POKEMON           (1 << 16)  // AI has an Ace Pokemon. The last Pokemon in the party will not be used until it's the last one remaining.
#define AI_FLAG_OMNISCIENT            (1 << 17)  // AI has full knowledge of player moves, abilities, hold items
#define AI_FLAG_SEBASTIANS_TRICK      (1 << 18)
#define AI_FLAG_PASSAWARY             (1 << 19)
#define AI_FLAG_DOUBLE_ACE_POKEMON    (1 << 20)  // AI has *two* Ace Pokémon. The last two Pokémons in the party won't be used unless they're the last ones remaining. Goes well in battles where the trainer ID equals to twins, couples, etc.

#define AI_FLAG_COUNT                       21

// 'other' ai logic flags
#define AI_FLAG_ROAMING               (1 << 29)
#define AI_FLAG_SAFARI                (1 << 30)
#define AI_FLAG_FIRST_BATTLE          (1 << 31)

#define AI_FLAGS_SHUNYONG   (AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_PREFER_STRONGEST_MOVE)

#endif // GUARD_CONSTANTS_BATTLE_AI_H
