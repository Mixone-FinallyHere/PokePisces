#ifndef GUARD_HOLD_EFFECTS_H
#define GUARD_HOLD_EFFECTS_H

#define HOLD_EFFECT_NONE            0
#define HOLD_EFFECT_RESTORE_HP      1
#define HOLD_EFFECT_CURE_PAR        2
#define HOLD_EFFECT_CURE_SLP        3
#define HOLD_EFFECT_CURE_PSN        4
#define HOLD_EFFECT_CURE_BRN        5
#define HOLD_EFFECT_CURE_FRZ        6
#define HOLD_EFFECT_RESTORE_PP      7
#define HOLD_EFFECT_CURE_CONFUSION  8
#define HOLD_EFFECT_CURE_STATUS     9
#define HOLD_EFFECT_CONFUSE_SPICY  10
#define HOLD_EFFECT_CONFUSE_DRY    11
#define HOLD_EFFECT_CONFUSE_SWEET  12
#define HOLD_EFFECT_CONFUSE_BITTER 13
#define HOLD_EFFECT_CONFUSE_SOUR   14
#define HOLD_EFFECT_ATTACK_UP      15
#define HOLD_EFFECT_DEFENSE_UP     16
#define HOLD_EFFECT_SPEED_UP       17
#define HOLD_EFFECT_SP_ATTACK_UP   18
#define HOLD_EFFECT_SP_DEFENSE_UP  19
#define HOLD_EFFECT_CRITICAL_UP    20
#define HOLD_EFFECT_RANDOM_STAT_UP 21
#define HOLD_EFFECT_EVASION_UP     22
#define HOLD_EFFECT_RESTORE_STATS  23
#define HOLD_EFFECT_MACHO_BRACE    24
#define HOLD_EFFECT_EXP_SHARE      25
#define HOLD_EFFECT_QUICK_CLAW     26
#define HOLD_EFFECT_FRIENDSHIP_UP  27
#define HOLD_EFFECT_MENTAL_HERB    28
#define HOLD_EFFECT_CHOICE_BAND    29
#define HOLD_EFFECT_FLINCH         30
#define HOLD_EFFECT_BUG_POWER      31
#define HOLD_EFFECT_DOUBLE_PRIZE   32
#define HOLD_EFFECT_REPEL          33
#define HOLD_EFFECT_SOUL_DEW       34
#define HOLD_EFFECT_DEEP_SEA_TOOTH 35
#define HOLD_EFFECT_DEEP_SEA_SCALE 36
#define HOLD_EFFECT_CAN_ALWAYS_RUN 37
#define HOLD_EFFECT_PREVENT_EVOLVE 38
#define HOLD_EFFECT_FOCUS_BAND     39
#define HOLD_EFFECT_LUCKY_EGG      40
#define HOLD_EFFECT_SCOPE_LENS     41
#define HOLD_EFFECT_STEEL_POWER    42
#define HOLD_EFFECT_LEFTOVERS      43
#define HOLD_EFFECT_DRAGON_SCALE   44
#define HOLD_EFFECT_LIGHT_BALL     45
#define HOLD_EFFECT_GROUND_POWER   46
#define HOLD_EFFECT_ROCK_POWER     47
#define HOLD_EFFECT_GRASS_POWER    48
#define HOLD_EFFECT_DARK_POWER     49
#define HOLD_EFFECT_FIGHTING_POWER 50
#define HOLD_EFFECT_ELECTRIC_POWER 51
#define HOLD_EFFECT_WATER_POWER    52
#define HOLD_EFFECT_FLYING_POWER   53
#define HOLD_EFFECT_POISON_POWER   54
#define HOLD_EFFECT_ICE_POWER      55
#define HOLD_EFFECT_GHOST_POWER    56
#define HOLD_EFFECT_PSYCHIC_POWER  57
#define HOLD_EFFECT_FIRE_POWER     58
#define HOLD_EFFECT_DRAGON_POWER   59
#define HOLD_EFFECT_NORMAL_POWER   60
#define HOLD_EFFECT_UPGRADE        61
#define HOLD_EFFECT_SHELL_BELL     62
#define HOLD_EFFECT_LUCKY_PUNCH    63
#define HOLD_EFFECT_METAL_POWDER   64
#define HOLD_EFFECT_THICK_CLUB     65
#define HOLD_EFFECT_LEEK           66

// Gen4 hold effects.
#define HOLD_EFFECT_CHOICE_SCARF   67
#define HOLD_EFFECT_CHOICE_SPECS   68
#define HOLD_EFFECT_DAMP_ROCK      69
#define HOLD_EFFECT_GRIP_CLAW      70
#define HOLD_EFFECT_HEAT_ROCK      71
#define HOLD_EFFECT_ICY_ROCK       72
#define HOLD_EFFECT_LIGHT_CLAY     73
#define HOLD_EFFECT_SMOOTH_ROCK    74
#define HOLD_EFFECT_POWER_HERB     75
#define HOLD_EFFECT_BIG_ROOT       76
#define HOLD_EFFECT_EXPERT_BELT    77
#define HOLD_EFFECT_LIFE_ORB       78
#define HOLD_EFFECT_METRONOME      79
#define HOLD_EFFECT_MUSCLE_BAND    80
#define HOLD_EFFECT_WIDE_LENS      81
#define HOLD_EFFECT_WISE_GLASSES   82
#define HOLD_EFFECT_ZOOM_LENS      83
#define HOLD_EFFECT_LAGGING_TAIL   84
#define HOLD_EFFECT_FOCUS_SASH     85
#define HOLD_EFFECT_FLAME_ORB      86
#define HOLD_EFFECT_TOXIC_ORB      87
#define HOLD_EFFECT_STICKY_BARB    88
#define HOLD_EFFECT_IRON_BALL      89
#define HOLD_EFFECT_BLACK_SLUDGE   90
#define HOLD_EFFECT_DESTINY_KNOT   91
#define HOLD_EFFECT_SHED_SHELL     92
#define HOLD_EFFECT_QUICK_POWDER   93
#define HOLD_EFFECT_ADAMANT_ORB    94
#define HOLD_EFFECT_LUSTROUS_ORB   95
#define HOLD_EFFECT_GRISEOUS_ORB   96
#define HOLD_EFFECT_ENIGMA_BERRY   97
#define HOLD_EFFECT_RESIST_BERRY   98
#define HOLD_EFFECT_POWER_ITEM     99
#define HOLD_EFFECT_RESTORE_PCT_HP 100
#define HOLD_EFFECT_MICLE_BERRY    101
#define HOLD_EFFECT_CUSTAP_BERRY   102
#define HOLD_EFFECT_JABOCA_BERRY   103
#define HOLD_EFFECT_ROWAP_BERRY    104
#define HOLD_EFFECT_KEE_BERRY      105
#define HOLD_EFFECT_MARANGA_BERRY  106
#define HOLD_EFFECT_PLATE          107

// Gen5 hold effects
#define HOLD_EFFECT_FLOAT_STONE    117
#define HOLD_EFFECT_EVIOLITE       118
#define HOLD_EFFECT_ASSAULT_VEST   119
#define HOLD_EFFECT_DRIVE          120
#define HOLD_EFFECT_GEMS           121
#define HOLD_EFFECT_ROCKY_HELMET   122
#define HOLD_EFFECT_AIR_BALLOON    123
#define HOLD_EFFECT_RED_CARD       124
#define HOLD_EFFECT_RING_TARGET    125
#define HOLD_EFFECT_BINDING_BAND   126
#define HOLD_EFFECT_EJECT_BUTTON   127
#define HOLD_EFFECT_ABSORB_BULB    128
#define HOLD_EFFECT_CELL_BATTERY   129

// Gen6 hold effects
#define HOLD_EFFECT_FAIRY_POWER     139
#define HOLD_EFFECT_MEGA_STONE      140
#define HOLD_EFFECT_SAFETY_GOGGLES  141
#define HOLD_EFFECT_LUMINOUS_MOSS   142
#define HOLD_EFFECT_SNOWBALL        143
#define HOLD_EFFECT_WEAKNESS_POLICY 144
#define HOLD_EFFECT_PRIMAL_ORB      145

// Gen7 hold effects
#define HOLD_EFFECT_PROTECTIVE_PADS  154
#define HOLD_EFFECT_TERRAIN_EXTENDER 155
#define HOLD_EFFECT_SEEDS            156
#define HOLD_EFFECT_ADRENALINE_ORB   157
#define HOLD_EFFECT_MEMORY           158
#define HOLD_EFFECT_Z_CRYSTAL        159

// Gen8 hold effects
#define HOLD_EFFECT_UTILITY_UMBRELLA    169
#define HOLD_EFFECT_EJECT_PACK          170
#define HOLD_EFFECT_ROOM_SERVICE        171
#define HOLD_EFFECT_BLUNDER_POLICY      172
#define HOLD_EFFECT_HEAVY_DUTY_BOOTS    173
#define HOLD_EFFECT_THROAT_SPRAY        174

// Gen9 hold effects
#define HOLD_EFFECT_ABILITY_SHIELD      175
#define HOLD_EFFECT_CLEAR_AMULET        176
#define HOLD_EFFECT_MIRROR_HERB         177 // Not implemented.
#define HOLD_EFFECT_PUNCHING_GLOVE      178
#define HOLD_EFFECT_COVERT_CLOAK        179
#define HOLD_EFFECT_LOADED_DICE         180
#define HOLD_EFFECT_BOOSTER_ENERGY      181 // Not implemented.

// Gen2 hold effect
#define HOLD_EFFECT_BERSERK_GENE        182

// New Hold effects
#define HOLD_EFFECT_BURNT_BRANCH        183
#define HOLD_EFFECT_CURSED_AMULET       184
#define HOLD_EFFECT_LEADERS_CREST       185
#define HOLD_EFFECT_BATTLE_HELM         186
#define HOLD_EFFECT_GLUE_TUBE           187
#define HOLD_EFFECT_FROST_ORB           188
#define HOLD_EFFECT_POISON_ORB          189
#define HOLD_EFFECT_BLOOM_ORB           190
#define HOLD_EFFECT_PANIC_ORB           191
#define HOLD_EFFECT_TRIUMPH_STAR        192
#define HOLD_EFFECT_VIBRANT_SCALE       193
#define HOLD_EFFECT_ZIG_SASH            194
#define HOLD_EFFECT_DOUGH_STICK         195
#define HOLD_EFFECT_DRIP_SHOES          196
#define HOLD_EFFECT_OBJECT_D_ARC        197
#define HOLD_EFFECT_KEYCHAIN            198
#define HOLD_EFFECT_GRAVITY_CORE        199
#define HOLD_EFFECT_LOST_MANTLE         200
#define HOLD_EFFECT_WIDE_ARMOR          201
#define HOLD_EFFECT_SALTY_TEAR          202
#define HOLD_EFFECT_ROOM_EXTENDER       203
#define HOLD_EFFECT_FAVOR_SCARF         204
#define HOLD_EFFECT_DILATANT_MOD        205
#define HOLD_EFFECT_SHELL_POLISH        206
#define HOLD_EFFECT_FAMILY_MOSS         207
#define HOLD_EFFECT_EERIE_MASK          208
#define HOLD_EFFECT_A_THING             209
#define HOLD_EFFECT_TRADING_CARD        210
#define HOLD_EFFECT_CHEESE              211
#define HOLD_EFFECT_FROTHY_CHEESE       212
#define HOLD_EFFECT_SPECTRAL_IDOL       213
#define HOLD_EFFECT_ODD_STONE           214
#define HOLD_EFFECT_COARSE_SAND         215
#define HOLD_EFFECT_TAMATO_BERRY        216
#define HOLD_EFFECT_YELLOW_SODA         217
#define HOLD_EFFECT_FLIP_COIN           218
#define HOLD_EFFECT_FAIRY_RING          219
#define HOLD_EFFECT_STILETTO            220
#define HOLD_EFFECT_BLACK_SALAD         221
#define HOLD_EFFECT_DISTILL_MOD         222
#define HOLD_EFFECT_SOLAR_SWORD         223
#define HOLD_EFFECT_FRIEND_RIBBON       224
#define HOLD_EFFECT_KAMEN_SCARF         225
#define HOLD_EFFECT_CURE_PANIC          226
#define HOLD_EFFECT_RAZOR_FANG          227
#define HOLD_EFFECT_CLEANSE_TAG         228
#define HOLD_EFFECT_PESKY_PLUSH         229
#define HOLD_EFFECT_CORRODE_MOD         230
#define HOLD_EFFECT_GEMSTONE            231
#define HOLD_EFFECT_TERU_CHARM          232
#define HOLD_EFFECT_LONG_NOSE           233
#define HOLD_EFFECT_CRYPTIC_PLATE       234
#define HOLD_EFFECT_MOON_MIRROR         235
#define HOLD_EFFECT_WATMEL_BERRY        236
#define HOLD_EFFECT_MAGOST_BERRY        237
#define HOLD_EFFECT_KELPSY_BERRY        238
#define HOLD_EFFECT_QUALOT_BERRY        239
#define HOLD_EFFECT_GREPA_BERRY         240
#define HOLD_EFFECT_CORNN_BERRY         241
#define HOLD_EFFECT_RABUTA_BERRY        242
#define HOLD_EFFECT_SPELON_BERRY        243
#define HOLD_EFFECT_BELUE_BERRY         244
#define HOLD_EFFECT_PINAP_BERRY         245
#define HOLD_EFFECT_RAZZ_BERRY          246
#define HOLD_EFFECT_RIZZ_BERRY          247
#define HOLD_EFFECT_NOMEL_BERRY         248
#define HOLD_EFFECT_BLUK_BERRY          249
#define HOLD_EFFECT_NANAB_BERRY         250
#define HOLD_EFFECT_HONDEW_BERRY        251
#define HOLD_EFFECT_WEPEAR_BERRY        252
#define HOLD_EFFECT_DURIN_BERRY         253
#define HOLD_EFFECT_CHUPACABRA          254
#define HOLD_EFFECT_HEART_GIFT          255
#define HOLD_EFFECT_SILVER_POWDER   256    // bug power +20%, 50% chance to leave powder on foe when using bug type move
#define HOLD_EFFECT_METAL_COAT      257  // steel power +20%, reduce chance to be hit by secondary effect by 50%
#define HOLD_EFFECT_SOFT_SAND       258  // ground power +20%, ground type moves have 30% chance to lower accuracy
#define HOLD_EFFECT_HARD_STONE      259  // rock power +20%. when use rock move, next attack on you does 20% less dmg
#define HOLD_EFFECT_MIRACLE_SEED    260  // grass power +20%, additional 20% chance to gain blooming when using grass moves
#define HOLD_EFFECT_BLACK_GLASSES   261    // dark power +20%, dark moves have 20% chance to inflict panic
#define HOLD_EFFECT_BLACK_BELT      262  // fighting power +20%, additional 20% if super effective
#define HOLD_EFFECT_MAGNET          263  // electric power +20%, boost ally electric power by 20%    
#define HOLD_EFFECT_MYSTIC_WATER    264  // water power +20%, and 30% chance to reset users negative stat changes when using water move
#define HOLD_EFFECT_SHARP_BEAK      265 // flying power +20%, additional +10% against grounded foes    
#define HOLD_EFFECT_POISON_BARB     266  // poison power +20%, additional 15% of target maxHP if they're poisoned
#define HOLD_EFFECT_NEVER_MELT_ICE  267  // ice power +20%, prevents burn
#define HOLD_EFFECT_SPELL_TAG       268  // ghost power +20%, ghost moves reduce targets last used move PP by 2
#define HOLD_EFFECT_TWISTED_SPOON   269  // psychic power +20%, +30% more if target has a reduced stat
#define HOLD_EFFECT_CHARCOAL        270  // fire power +20%, additional +20% if target is burned
#define HOLD_EFFECT_DRAGON_FANG     271  // dragon power +20%, additional +40% if move not very effective
#define HOLD_EFFECT_SILK_SCARF      272  // normal power +20%, 10% boost to all other typed moves
#define HOLD_EFFECT_FAIRY_FEATHER   273  // fairy power +20% and secondary effect chance -> 100%
#define HOLD_EFFECT_POMEG_BERRY     274
#define HOLD_EFFECT_SILVER_CROWN    275
#define HOLD_EFFECT_WINTAMEL_TEA    276

#define HOLD_EFFECT_CHOICE(holdEffect)((holdEffect == HOLD_EFFECT_CHOICE_BAND || holdEffect == HOLD_EFFECT_CHOICE_SCARF || holdEffect == HOLD_EFFECT_CHOICE_SPECS))

// Terrain seed params
#define HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN  0
#define HOLD_EFFECT_PARAM_GRASSY_TERRAIN    1
#define HOLD_EFFECT_PARAM_MISTY_TERRAIN     2
#define HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN   3

#endif // GUARD_HOLD_EFFECTS_H
