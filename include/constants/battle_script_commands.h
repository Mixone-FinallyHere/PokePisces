#ifndef GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H
#define GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H

// The following correspond to the struct members of BattleScripting by adding their offset
#define sPAINSPLIT_HP                (gBattleScripting + 0x00) // painSplitHp
#define sBIDE_DMG                    (gBattleScripting + 0x04) // bideDmg
#define sMULTIHIT_STRING             (gBattleScripting + 0x08) // multihitString
#define sEXP_CATCH                   (gBattleScripting + 0x0E) // expOnCatch
#define sTWOTURN_STRINGID            (gBattleScripting + 0x0F) // twoTurnsMoveStringId
#define sB_ANIM_ARG1                 (gBattleScripting + 0x10) // animArg1
#define sB_ANIM_ARG2                 (gBattleScripting + 0x11) // animArg2
#define sTRIPLE_KICK_POWER           (gBattleScripting + 0x12) // tripleKickPower
#define sMOVEEND_STATE               (gBattleScripting + 0x14) // moveendState
#define sSAVED_STAT_CHANGER          (gBattleScripting + 0x15) // savedStatChanger
#define sSHIFT_SWITCHED              (gBattleScripting + 0x16) // shiftSwitched
#define sBATTLER                     (gBattleScripting + 0x17) // battler
#define sB_ANIM_TURN                 (gBattleScripting + 0x18) // animTurn
#define sB_ANIM_TARGETS_HIT          (gBattleScripting + 0x19) // animTargetsHit
#define sSTATCHANGER                 (gBattleScripting + 0x1A) // statChanger
#define sSTAT_ANIM_PLAYED            (gBattleScripting + 0x1B) // statAnimPlayed
#define sGIVEEXP_STATE               (gBattleScripting + 0x1C) // getexpState
#define sBATTLE_STYLE                (gBattleScripting + 0x1D) // battleStyle
#define sLVLBOX_STATE                (gBattleScripting + 0x1E) // drawlvlupboxState
#define sLEARNMOVE_STATE             (gBattleScripting + 0x1F) // learnMoveState
#define sSAVED_BATTLER               (gBattleScripting + 0x20) // savedBattler
#define sRESHOW_MAIN_STATE           (gBattleScripting + 0x21) // reshowMainState
#define sRESHOW_HELPER_STATE         (gBattleScripting + 0x22) // reshowHelperState
#define sLVLUP_HP                    (gBattleScripting + 0x23) // levelUpHP
#define sWINDOWS_TYPE                (gBattleScripting + 0x24) // windowsType
#define sMULTIPLAYER_ID              (gBattleScripting + 0x25) // multiplayerId
#define sSPECIAL_TRAINER_BATTLE_TYPE (gBattleScripting + 0x26) // specialTrainerBattleType
#define sMON_CAUGHT                  (gBattleScripting + 0x27) // monCaught
#define sSAVED_DMG                   (gBattleScripting + 0x28) // savedDmg
#define sSAVED_MOVE_EFFECT           (gBattleScripting + 0x2C) // savedMoveEffect
#define sMOVE_EFFECT                 (gBattleScripting + 0x2E) // moveEffect
#define sMULTIHIT_EFFECT             (gBattleScripting + 0x30) // multihitMoveEffect
#define sILLUSION_NICK_HACK          (gBattleScripting + 0x32) // illusionNickHack
#define sFIXED_ABILITY_POPUP         (gBattleScripting + 0x33) // fixedPopup
#define sABILITY_OVERWRITE           (gBattleScripting + 0x34) // abilityPopupOverwrite
#define sSWITCH_CASE                 (gBattleScripting + 0x36) // switchCase
#define sBERRY_OVERRIDE              (gBattleScripting + 0x37) // overrideBerryRequirements
#define sSTICKY_WEB_STAT_DROP        (gBattleScripting + 0x38) // stickyWebStatDrop

// Array entries for battle communication
#define MULTIUSE_STATE          0
#define CURSOR_POSITION         1
#define TASK_ID                 1 // task Id and cursor position share the same field
#define SPRITES_INIT_STATE1     1 // shares the Id as well
#define SPRITES_INIT_STATE2     2
#define MOVE_EFFECT_BYTE        3
#define ACTIONS_CONFIRMED_COUNT 4
#define MULTISTRING_CHOOSER     5
#define MISS_TYPE               6
#define MSG_DISPLAY             7
#define BATTLE_COMMUNICATION_ENTRIES_COUNT  8

#define cMULTISTRING_CHOOSER (gBattleCommunication + MULTISTRING_CHOOSER)
#define cMISS_TYPE           (gBattleCommunication + MISS_TYPE)

// Battle Script defines for getting the wanted battler
#define BS_TARGET                   0
#define BS_ATTACKER                 1
#define BS_EFFECT_BATTLER           2
#define BS_FAINTED                  3
#define BS_ATTACKER_WITH_PARTNER    4 // for Cmd_updatestatusicon
#define BS_FAINTED_LINK_MULTIPLE_1  5 // for openpartyscreen
#define BS_FAINTED_LINK_MULTIPLE_2  6 // for openpartyscreen
#define BS_BATTLER_0                7
#define BS_ATTACKER_SIDE            8 // for Cmd_jumpifability
#define BS_TARGET_SIDE              9 // for Cmd_jumpifability
#define BS_SCRIPTING                10
#define BS_PLAYER1                  11
#define BS_OPPONENT1                12
#define BS_PLAYER2                  13 // for Cmd_updatestatusicon
#define BS_OPPONENT2                14
#define BS_ABILITY_BATTLER          15
#define BS_ATTACKER_PARTNER         16

// Cmd_accuracycheck
#define NO_ACC_CALC_CHECK_LOCK_ON 0xFFFF
#define ACC_CURR_MOVE 0

// compare operands
#define CMP_EQUAL               0
#define CMP_NOT_EQUAL           1
#define CMP_GREATER_THAN        2
#define CMP_LESS_THAN           3
#define CMP_COMMON_BITS         4
#define CMP_NO_COMMON_BITS      5

// Cmd_various
#define VARIOUS_CANCEL_MULTI_TURN_MOVES              0
#define VARIOUS_SET_MAGIC_COAT_TARGET                1
#define VARIOUS_IS_RUNNING_IMPOSSIBLE                2
#define VARIOUS_GET_MOVE_TARGET                      3
#define VARIOUS_GET_BATTLER_FAINTED                  4
#define VARIOUS_RESET_SWITCH_IN_ABILITY_BITS         5
#define VARIOUS_UPDATE_CHOICE_MOVE_ON_LVL_UP         6
#define VARIOUS_RESET_PLAYER_FAINTED                 7
#define VARIOUS_PALACE_FLAVOR_TEXT                   8
#define VARIOUS_ARENA_JUDGMENT_WINDOW                9
#define VARIOUS_ARENA_OPPONENT_MON_LOST              10
#define VARIOUS_ARENA_PLAYER_MON_LOST                11
#define VARIOUS_ARENA_BOTH_MONS_LOST                 12
#define VARIOUS_EMIT_YESNOBOX                        13
#define VARIOUS_DRAW_ARENA_REF_TEXT_BOX              14
#define VARIOUS_ERASE_ARENA_REF_TEXT_BOX             15
#define VARIOUS_ARENA_JUDGMENT_STRING                16
#define VARIOUS_ARENA_WAIT_STRING                    17
#define VARIOUS_WAIT_CRY                             18
#define VARIOUS_RETURN_OPPONENT_MON1                 19
#define VARIOUS_RETURN_OPPONENT_MON2                 20
#define VARIOUS_VOLUME_DOWN                          21
#define VARIOUS_VOLUME_UP                            22
#define VARIOUS_SET_ALREADY_STATUS_MOVE_ATTEMPT      23
#define VARIOUS_PALACE_TRY_ESCAPE_STATUS             24
#define VARIOUS_SET_TELEPORT_OUTCOME                 25
#define VARIOUS_PLAY_TRAINER_DEFEATED_MUSIC          26
#define VARIOUS_STAT_TEXT_BUFFER                     27
#define VARIOUS_SWITCHIN_ABILITIES                   28
#define VARIOUS_SAVE_TARGET                          29
#define VARIOUS_RESTORE_TARGET                       30
#define VARIOUS_INSTANT_HP_DROP                      31
#define VARIOUS_CLEAR_STATUS                         32
#define VARIOUS_RESTORE_PP                           33
#define VARIOUS_TRY_ACTIVATE_MOXIE                   34
#define VARIOUS_TRY_ACTIVATE_FELL_STINGER            35
#define VARIOUS_PLAY_MOVE_ANIMATION                  36
#define VARIOUS_SET_LUCKY_CHANT                      37
#define VARIOUS_SUCKER_PUNCH_CHECK                   38
#define VARIOUS_SET_SIMPLE_BEAM                      39
#define VARIOUS_TRY_ENTRAINMENT                      40
#define VARIOUS_SET_LAST_USED_ABILITY                41
#define VARIOUS_TRY_HEAL_PULSE                       42 //Unused
#define VARIOUS_TRY_QUASH                            43
#define VARIOUS_INVERT_STAT_STAGES                   44
#define VARIOUS_TRY_ME_FIRST                         45
#define VARIOUS_JUMP_IF_BATTLE_END                   46
#define VARIOUS_TRY_ELECTRIFY                        47
#define VARIOUS_TRY_REFLECT_TYPE                     48
#define VARIOUS_TRY_SOAK                             49
#define VARIOUS_HANDLE_MEGA_EVO                      50
#define VARIOUS_TRY_LAST_RESORT                      51
#define VARIOUS_ARGUMENT_STATUS_EFFECT               52
#define VARIOUS_TRY_HIT_SWITCH_TARGET                53
#define VARIOUS_TRY_AUTOTOMIZE                       54
#define VARIOUS_ABILITY_POPUP                        55
#define VARIOUS_DEFOG                                56
#define VARIOUS_JUMP_IF_TARGET_ALLY                  57
#define VARIOUS_TRY_SYNCHRONOISE                     58
#define VARIOUS_PSYCHO_SHIFT                         59
#define VARIOUS_CURE_STATUS                          60
#define VARIOUS_POWER_TRICK                          61
#define VARIOUS_AFTER_YOU                            62
#define VARIOUS_BESTOW                               63
#define VARIOUS_ARGUMENT_TO_MOVE_EFFECT              64
#define VARIOUS_JUMP_IF_NOT_GROUNDED                 65
#define VARIOUS_HANDLE_TRAINER_SLIDE_MSG             66
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_FIRST_OFF      67
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_LAST_ON        68
#define VARIOUS_SET_AURORA_VEIL                      69
#define VARIOUS_TRY_THIRD_TYPE                       70
#define VARIOUS_ACUPRESSURE                          71
#define VARIOUS_SET_POWDER                           72
#define VARIOUS_SPECTRAL_THIEF                       73
#define VARIOUS_GRAVITY_ON_AIRBORNE_MONS             74
#define VARIOUS_CHECK_IF_GRASSY_TERRAIN_HEALS        75
#define VARIOUS_JUMP_IF_ROAR_FAILS                   76
#define VARIOUS_TRY_INSTRUCT                         77
#define VARIOUS_JUMP_IF_NOT_BERRY                    78
#define VARIOUS_TRACE_ABILITY                        79
#define VARIOUS_UPDATE_NICK                          80
#define VARIOUS_TRY_ILLUSION_OFF                     81
#define VARIOUS_SET_SPRITEIGNORE0HP                  82
#define VARIOUS_HANDLE_FORM_CHANGE                   83
#define VARIOUS_GET_STAT_VALUE                       84
#define VARIOUS_JUMP_IF_FULL_HP                      85
#define VARIOUS_LOSE_TYPE                            86
#define VARIOUS_TRY_ACTIVATE_SOULHEART               87
#define VARIOUS_TRY_ACTIVATE_RECEIVER                88
#define VARIOUS_TRY_ACTIVATE_BEAST_BOOST             89
#define VARIOUS_TRY_FRISK                            90
#define VARIOUS_JUMP_IF_SHIELDS_DOWN_PROTECTED       91
#define VARIOUS_TRY_FAIRY_LOCK                       92
#define VARIOUS_JUMP_IF_NO_ALLY                      93
#define VARIOUS_POISON_TYPE_IMMUNITY                 94
#define VARIOUS_JUMP_IF_NO_HOLD_EFFECT               95
#define VARIOUS_INFATUATE_WITH_BATTLER               96
#define VARIOUS_SET_LAST_USED_ITEM                   97
#define VARIOUS_PARALYZE_TYPE_IMMUNITY               98
#define VARIOUS_JUMP_IF_ABSENT                       99
#define VARIOUS_DESTROY_ABILITY_POPUP                100
#define VARIOUS_TOTEM_BOOST                          101
#define VARIOUS_TRY_ACTIVATE_GRIM_NEIGH              102
#define VARIOUS_MOVEEND_ITEM_EFFECTS                 103
#define VARIOUS_TERRAIN_SEED                         104
#define VARIOUS_MAKE_INVISIBLE                       105
#define VARIOUS_ROOM_SERVICE                         106
#define VARIOUS_EERIE_SPELL_PP_REDUCE                107
#define VARIOUS_JUMP_IF_TEAM_HEALTHY                 108
#define VARIOUS_TRY_HEAL_QUARTER_HP                  109
#define VARIOUS_REMOVE_TERRAIN                       110
#define VARIOUS_JUMP_IF_PRANKSTER_BLOCKED            111
#define VARIOUS_TRY_TO_CLEAR_PRIMAL_WEATHER          112
#define VARIOUS_GET_ROTOTILLER_TARGETS               113
#define VARIOUS_JUMP_IF_NOT_ROTOTILLER_AFFECTED      114
#define VARIOUS_TRY_ACTIVATE_BATTLE_BOND             115
#define VARIOUS_CONSUME_BERRY                        116
#define VARIOUS_JUMP_IF_CANT_REVERT_TO_PRIMAL        117
#define VARIOUS_APPLY_PLASMA_FISTS                   118
#define VARIOUS_JUMP_IF_SPECIES                      119
#define VARIOUS_UPDATE_ABILITY_POPUP                 120
#define VARIOUS_JUMP_IF_WEATHER_AFFECTED             121
#define VARIOUS_JUMP_IF_LEAF_GUARD_PROTECTED         122
#define VARIOUS_SET_ATTACKER_STICKY_WEB_USER         123
#define VARIOUS_PHOTON_GEYSER_CHECK                  124
#define VARIOUS_SHELL_SIDE_ARM_CHECK                 125
#define VARIOUS_TRY_NO_RETREAT                       126
#define VARIOUS_TRY_TAR_SHOT                         127
#define VARIOUS_CAN_TAR_SHOT_WORK                    128
#define VARIOUS_CHECK_POLTERGEIST                    129
#define VARIOUS_SET_OCTOLOCK                         130
#define VARIOUS_CUT_1_3_HP_RAISE_STATS               131
#define VARIOUS_TRY_END_NEUTRALIZING_GAS             132
#define VARIOUS_JUMP_IF_UNDER_200                    133
#define VARIOUS_SET_SKY_DROP                         134
#define VARIOUS_CLEAR_SKY_DROP                       135
#define VARIOUS_SKY_DROP_YAWN                        136
#define VARIOUS_JUMP_IF_HOLD_EFFECT                  137
#define VARIOUS_CURE_CERTAIN_STATUSES                138
#define VARIOUS_TRY_RESET_NEGATIVE_STAT_STAGES       139
#define VARIOUS_JUMP_IF_LAST_USED_ITEM_BERRY         140
#define VARIOUS_JUMP_IF_LAST_USED_ITEM_HOLD_EFFECT   141
#define VARIOUS_SAVE_BATTLER_ITEM                    142
#define VARIOUS_RESTORE_BATTLER_ITEM                 143
#define VARIOUS_BATTLER_ITEM_TO_LAST_USED_ITEM       144
#define VARIOUS_SET_BEAK_BLAST                       145
#define VARIOUS_SWAP_SIDE_STATUSES                   146
#define VARIOUS_SWAP_STATS                           147
#define VARIOUS_TEATIME_INVUL                        148
#define VARIOUS_TEATIME_TARGETS                      149
#define VARIOUS_TRY_WIND_RIDER_POWER                 150
#define VARIOUS_ACTIVATE_WEATHER_CHANGE_ABILITIES    151
#define VARIOUS_ACTIVATE_TERRAIN_CHANGE_ABILITIES    152
#define VARIOUS_STORE_HEALING_WISH                   153
#define VARIOUS_HIT_SWITCH_TARGET_FAILED             154
#define VARIOUS_TRY_REVIVAL_BLESSING                 155
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_Z_MOVE         156
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_MEGA_EVOLUTION 157
#define VARIOUS_SET_SPIDER_WEB                       158
#define VARIOUS_TRY_ACTIVATE_APPETITE                159
#define VARIOUS_SET_SILENCE                          160
#define VARIOUS_SEIZE_CHANCE_CHECK                   161
#define VARIOUS_JUMP_IF_EERIE_MASK_PROTECTED         162
#define VARIOUS_DESTINY_KNOT_DISABLE                 163
#define VARIOUS_DESTINY_KNOT_TORMENT                 164
#define VARIOUS_DESTINY_KNOT_TAUNT                   165
#define VARIOUS_DESTINY_KNOT_ENCORE                  166
#define VARIOUS_DESTINY_KNOT_HEAL_BLOCK              167
#define VARIOUS_CHEESING                             168
#define VARIOUS_TRY_YELLOW_SODA_FOCUS_ENERGY         169
#define VARIOUS_TRY_NORMALISE_SPEED                  170
#define VARIOUS_TRY_TO_CLEAR_WEATHER                 171
#define VARIOUS_TRY_HEAL_ALL_HEALTH                  172
#define VARIOUS_REMODEL_CHECK                        173
#define VARIOUS_JUMP_IF_STATUS4                      174
#define VARIOUS_BOUNDARY_OF_DEATH                    175
#define VARIOUS_TRY_DANCE_MANIA                      176
#define VARIOUS_JUMP_IF_SPECIES_HAS_NO_LEGS          177
#define VARIOUS_JUMP_IF_ALLY_HAS_NO_LEGS             178
#define VARIOUS_JUMP_IF_HP_THRESHOLD                 179
#define VARIOUS_REMOVE_TAILWIND                      180
#define VARIOUS_SET_PUMP                             181
#define VARIOUS_POWER_SHIFT                          182
#define VARIOUS_TRY_DAMPING                          183
#define VARIOUS_CHECK_MEAN_LOOK                      184
#define VARIOUS_CHECK_GUARD_SPLIT                    185
#define VARIOUS_CHECK_GUARD_SWAP                     186
#define VARIOUS_CHECK_POWER_SPLIT                    187
#define VARIOUS_CHECK_POWER_SWAP                     188
#define VARIOUS_CHECK_SPEED_SWAP                     189
#define VARIOUS_STAGGER_DAMAGE                       190
#define VARIOUS_HIGH_ROLL_HIT                        191
#define VARIOUS_ARBITER_DAMAGE                       192
#define VARIOUS_TRY_GAIN_CHEESE                      193
#define VARIOUS_JUMP_IF_TERU_CHARM_PROTECTED         194
#define VARIOUS_SAVE_DANCE_TARGETS                   195
#define VARIOUS_INVERT_NEGATIVE_STAT_STAGES          196
#define VARIOUS_SET_PURPLE_HAZE                      197
#define VARIOUS_SET_MAGMA_ARMORED                    198
#define VARIOUS_SET_OVERTAKE_TARGET                  199
#define VARIOUS_BLUK_BERRY_PP_REDUCE                 200
#define VARIOUS_TRY_RESET_STAT_STAGES                201
#define VARIOUS_TRY_DEFEND_ORDER                     202
#define VARIOUS_STORE_HEAL_ORDER                     203
#define VARIOUS_TRY_RESET_POSITIVE_STAT_STAGES       204
#define VARIOUS_SPELL_TAG_PP_REDUCE                  205
#define VARIOUS_SET_PURIFIED                         206
#define VARIOUS_TRY_CRITICAL_REPAIR                  207
#define VARIOUS_CRAFTY_SHIELD                        208
#define VARIOUS_APPLY_EXHAUSTION_COUNTER             209
#define VARIOUS_REMOVE_SUPER_GEAR                    210
#define VARIOUS_JUMP_IF_GEAR_MAGNET                  211
#define VARIOUS_SUPERCHARGED                         212
#define VARIOUS_GEARED_UP                            213
#define VARIOUS_APPLY_PHANTOM                        214
#define VARIOUS_TRY_ACTIVATE_SHADOW_FORCE            215
#define VARIOUS_SET_ACID_ARMOR                       216
#define VARIOUS_TRY_ACTIVATE_STAR_ASSAULT            217
#define VARIOUS_SOLAR_POWER_DAMAGE                   218
#define VARIOUS_TRY_BLAZING_SOUL                     219
#define VARIOUS_APPLY_DAYBREAK_COUNTER               220
#define VARIOUS_REMOVE_DAYBREAK_COUNTER              221
#define VARIOUS_APPLY_FRENZY_COUNTER                 222
#define VARIOUS_TRY_ACTIVATE_HEART_CARVE             223
#define VARIOUS_CUT_HP                               224
#define VARIOUS_JUMP_IF_INFATUATED_SPECIFIC          225
#define VARIOUS_DISABLE_CHOSEN_MOVE                  226
#define VARIOUS_MIND_GAP_CHECK                       227
#define VARIOUS_REMOVE_FRENZY_COUNTER                228
#define VARIOUS_GET_ERODE_FIELD_TARGETS              229
#define VARIOUS_JUMP_IF_NOT_ERODE_FIELD_AFFECTED     230
#define VARIOUS_JUMP_IF_MOON_MIRRORED                231
#define VARIOUS_JUMP_IF_SPECIES_MEGA_BOSS            232
#define VARIOUS_FEAR_FACTOR                          233
#define VARIOUS_RANDOM_STAT_DROP                     234
#define VARIOUS_ALLURE                               235
#define VARIOUS_TRY_DOUBLE_TEAM                      236
#define VARIOUS_SET_SPOTLIGHT                        237
#define VARIOUS_TRY_SET_IMPRISON                     238
#define VARIOUS_INVERT_POSITIVE_STAT_STAGES          239
#define VARIOUS_SET_BABY_BLUES                       240
#define VARIOUS_SET_DOUBLES_MOVE_SUCCEED             241
#define VARIOUS_JUMP_IF_DOUBLES_MOVE_SUCCEED         242
#define VARIOUS_FLORESCENCE_CHECK                    243
#define VARIOUS_SET_SWITCH_IN_ABILITY_SUCCEED        244
#define VARIOUS_JUMP_IF_SWITCH_IN_ABILITY_SUCCEED    245
#define VARIOUS_JUMP_IF_FOCUS_ENERGY                 246
#define VARIOUS_TRY_HEAL_THIRD_HEALTH                247
#define VARIOUS_TRY_HEAL_SIXTH_HEALTH                248

// Cmd_manipulatedamage
#define DMG_CHANGE_SIGN            0
#define DMG_RECOIL_FROM_MISS       1
#define DMG_DOUBLED                2
#define DMG_1_8_TARGET_HP          3
#define DMG_FULL_ATTACKER_HP       4
#define DMG_CURR_ATTACKER_HP       5
#define DMG_BIG_ROOT               6
#define DMG_1_2_ATTACKER_HP        7
#define DMG_RECOIL_FROM_IMMUNE     8 // Used to calculate recoil for the Gen 4 version of Jump Kick
#define DMG_1_3_ATTACKER_HP        9
#define DMG_1_10_TARGET_HP        10

// Cmd_jumpifcantswitch
#define SWITCH_IGNORE_ESCAPE_PREVENTION   (1 << 7)

// Cmd_statbuffchange
#define STAT_CHANGE_ALLOW_PTR               (1 << 0)   // If set, allow use of jumpptr. Set in every use of statbuffchange
#define STAT_CHANGE_MIRROR_ARMOR            (1 << 1)   // Stat change redirection caused by Mirror Armor ability.
#define STAT_CHANGE_NOT_PROTECT_AFFECTED    (1 << 5)
#define STAT_CHANGE_UPDATE_MOVE_EFFECT      (1 << 6)

// stat change flags for Cmd_playstatchangeanimation
#define STAT_CHANGE_NEGATIVE             (1 << 0)
#define STAT_CHANGE_BY_TWO               (1 << 1)
#define STAT_CHANGE_MULTIPLE_STATS       (1 << 2)
#define STAT_CHANGE_CANT_PREVENT         (1 << 3)

// stat flags for Cmd_playstatchangeanimation
#define BIT_HP                      (1 << 0)
#define BIT_ATK                     (1 << 1)
#define BIT_DEF                     (1 << 2)
#define BIT_SPEED                   (1 << 3)
#define BIT_SPATK                   (1 << 4)
#define BIT_SPDEF                   (1 << 5)
#define BIT_ACC                     (1 << 6)
#define BIT_EVASION                 (1 << 7)

#define PARTY_SCREEN_OPTIONAL (1 << 7) // Flag for first argument to openpartyscreen

// cases for Cmd_moveend
#define MOVEEND_SUM_DAMAGE                        0
#define MOVEEND_PROTECT_LIKE_EFFECT               1
#define MOVEEND_RAGE                              2
#define MOVEEND_SYNCHRONIZE_TARGET                3
#define MOVEEND_ABILITIES                         4
#define MOVEEND_ABILITIES_ATTACKER                5
#define MOVEEND_STATUS_IMMUNITY_ABILITIES         6
#define MOVEEND_SYNCHRONIZE_ATTACKER              7
#define MOVEEND_CHOICE_MOVE                       8
#define MOVEEND_ATTACKER_INVISIBLE                9
#define MOVEEND_ATTACKER_VISIBLE                  10
#define MOVEEND_TARGET_VISIBLE                    11
#define MOVEEND_ITEM_EFFECTS_TARGET               12
#define MOVEEND_ITEM_EFFECTS_ALL                  13
#define MOVEEND_KINGSROCK                         14    // These item effects will occur each strike of a multi-hit move
#define MOVEEND_NUM_HITS                          15
#define MOVEEND_SUBSTITUTE                        16
#define MOVEEND_SKY_DROP_CONFUSE                  17
#define MOVEEND_UPDATE_LAST_MOVES                 18
#define MOVEEND_MIRROR_MOVE                       19
#define MOVEEND_NEXT_TARGET                       20   // Everything up until here is handled for each strike of a multi-hit move
#define MOVEEND_MULTIHIT_MOVE                     21
#define MOVEEND_DEFROST                           22
#define MOVEEND_MOVE_EFFECTS2                     23
#define MOVEEND_RECOIL                            24
#define MOVEEND_MAGICIAN                          25    // Occurs after final multi-hit strike, and after other items/abilities would activate
#define MOVEEND_EJECT_ITEMS                       26
#define MOVEEND_WHITE_HERB                        27
#define MOVEEND_RED_CARD                          28
#define MOVEEND_LIFEORB_SHELLBELL                 29    // Includes shell bell, throat spray, etc
#define MOVEEND_CHANGED_ITEMS                     30
#define MOVEEND_PICKPOCKET                        31
#define MOVEEND_SYMBIOSIS                         32
#define MOVEEND_SAME_MOVE_TURNS                   33
#define MOVEEND_SLICING_MOVE_TURNS                34
#define MOVEEND_STORM_BREW                        35
#define MOVEEND_NEXT_DANCE_TARGET                 36
#define MOVEEND_DANCER                            37
#define MOVEEND_CLEAR_BITS                        38
#define MOVEEND_COUNT                             39

// switch cases
#define B_SWITCH_NORMAL     0
#define B_SWITCH_HIT        1   // dragon tail, circle throw
#define B_SWITCH_RED_CARD   2

// Argument labels for EFFECT_HIT_SET_REMOVE_TERRAIN
#define ARG_SET_PSYCHIC_TERRAIN        0
#define ARG_TRY_REMOVE_TERRAIN_HIT     1
#define ARG_TRY_REMOVE_TERRAIN_FAIL    2
#define ARG_SET_GRASSY_TERRAIN         3

#endif // GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H
