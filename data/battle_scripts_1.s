#include "config.h"
#include "config/battle.h"
#include "constants/global.h"
#include "constants/battle.h"
#include "constants/pokemon.h"
#include "constants/battle_arena.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_anim.h"
#include "constants/battle_string_ids.h"
#include "constants/abilities.h"
#include "constants/hold_effects.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/game_stat.h"
#include "constants/trainers.h"
#include "constants/species.h"
	.include "asm/macros.inc"
	.include "asm/macros/battle_script.inc"
	.include "constants/constants.inc"

	.section script_data, "aw", %progbits

.align 2
gBattleScriptsForMoveEffects::
	.4byte BattleScript_EffectHit                     @ EFFECT_HIT
	.4byte BattleScript_EffectSleep                   @ EFFECT_SLEEP
	.4byte BattleScript_EffectPoisonHit               @ EFFECT_POISON_HIT
	.4byte BattleScript_EffectAbsorb                  @ EFFECT_ABSORB
	.4byte BattleScript_EffectBurnHit                 @ EFFECT_BURN_HIT
	.4byte BattleScript_EffectFreezeHit               @ EFFECT_FREEZE_HIT
	.4byte BattleScript_EffectParalyzeHit             @ EFFECT_PARALYZE_HIT
	.4byte BattleScript_EffectExplosion               @ EFFECT_EXPLOSION
	.4byte BattleScript_EffectDreamEater              @ EFFECT_DREAM_EATER
	.4byte BattleScript_EffectMirrorMove              @ EFFECT_MIRROR_MOVE
	.4byte BattleScript_EffectAttackUp                @ EFFECT_ATTACK_UP
	.4byte BattleScript_EffectDefenseUp               @ EFFECT_DEFENSE_UP
	.4byte BattleScript_EffectSpeedUp                 @ EFFECT_SPEED_UP
	.4byte BattleScript_EffectSpecialAttackUp         @ EFFECT_SPECIAL_ATTACK_UP
	.4byte BattleScript_EffectSpecialDefenseUp        @ EFFECT_SPECIAL_DEFENSE_UP
	.4byte BattleScript_EffectAccuracyUp              @ EFFECT_ACCURACY_UP
	.4byte BattleScript_EffectEvasionUp               @ EFFECT_EVASION_UP
	.4byte BattleScript_EffectSpecialAttackUp3        @ EFFECT_SPECIAL_ATTACK_UP_3
	.4byte BattleScript_EffectAttackDown              @ EFFECT_ATTACK_DOWN
	.4byte BattleScript_EffectDefenseDown             @ EFFECT_DEFENSE_DOWN
	.4byte BattleScript_EffectSpeedDown               @ EFFECT_SPEED_DOWN
	.4byte BattleScript_EffectSpecialAttackDown       @ EFFECT_SPECIAL_ATTACK_DOWN
	.4byte BattleScript_EffectSpecialDefenseDown      @ EFFECT_SPECIAL_DEFENSE_DOWN
	.4byte BattleScript_EffectAccuracyDown            @ EFFECT_ACCURACY_DOWN
	.4byte BattleScript_EffectEvasionDown             @ EFFECT_EVASION_DOWN
	.4byte BattleScript_EffectHaze                    @ EFFECT_HAZE
	.4byte BattleScript_EffectCosmicPower             @ EFFECT_BIDE
	.4byte BattleScript_EffectRampage                 @ EFFECT_RAMPAGE
	.4byte BattleScript_EffectRoar                    @ EFFECT_ROAR
	.4byte BattleScript_EffectHit                     @ EFFECT_MULTI_HIT
	.4byte BattleScript_EffectConversion              @ EFFECT_CONVERSION
	.4byte BattleScript_EffectFlinchHit               @ EFFECT_FLINCH_HIT
	.4byte BattleScript_EffectRestoreHp               @ EFFECT_RESTORE_HP
	.4byte BattleScript_EffectToxic                   @ EFFECT_TOXIC
	.4byte BattleScript_EffectPayDay                  @ EFFECT_PAY_DAY
	.4byte BattleScript_EffectLightScreen             @ EFFECT_LIGHT_SCREEN
	.4byte BattleScript_EffectTriAttack               @ EFFECT_TRI_ATTACK
	.4byte BattleScript_EffectRest                    @ EFFECT_REST
	.4byte BattleScript_EffectOHKO                    @ EFFECT_OHKO
	.4byte BattleScript_EffectHit                     @ EFFECT_FUSION_COMBO
	.4byte BattleScript_EffectSuperFang               @ EFFECT_SUPER_FANG
	.4byte BattleScript_EffectDragonRage              @ EFFECT_DRAGON_RAGE
	.4byte BattleScript_EffectTrap                    @ EFFECT_TRAP
	.4byte BattleScript_EffectHealBlock               @ EFFECT_HEAL_BLOCK
	.4byte BattleScript_EffectRecoilIfMiss            @ EFFECT_RECOIL_IF_MISS
	.4byte BattleScript_EffectMist                    @ EFFECT_MIST
	.4byte BattleScript_EffectFocusEnergy             @ EFFECT_FOCUS_ENERGY
	.4byte BattleScript_EffectHit                     @ EFFECT_RECOIL_25
	.4byte BattleScript_EffectConfuse                 @ EFFECT_CONFUSE
	.4byte BattleScript_EffectAttackUp2               @ EFFECT_ATTACK_UP_2
	.4byte BattleScript_EffectDefenseUp2              @ EFFECT_DEFENSE_UP_2
	.4byte BattleScript_EffectSpeedUp2                @ EFFECT_SPEED_UP_2
	.4byte BattleScript_EffectSpecialAttackUp2        @ EFFECT_SPECIAL_ATTACK_UP_2
	.4byte BattleScript_EffectSpecialDefenseUp2       @ EFFECT_SPECIAL_DEFENSE_UP_2
	.4byte BattleScript_EffectAccuracyUp2             @ EFFECT_ACCURACY_UP_2
	.4byte BattleScript_EffectEvasionUp2              @ EFFECT_EVASION_UP_2
	.4byte BattleScript_EffectTransform               @ EFFECT_TRANSFORM
	.4byte BattleScript_EffectAttackDown2             @ EFFECT_ATTACK_DOWN_2
	.4byte BattleScript_EffectDefenseDown2            @ EFFECT_DEFENSE_DOWN_2
	.4byte BattleScript_EffectSpeedDown2              @ EFFECT_SPEED_DOWN_2
	.4byte BattleScript_EffectSpecialAttackDown2      @ EFFECT_SPECIAL_ATTACK_DOWN_2
	.4byte BattleScript_EffectSpecialDefenseDown2     @ EFFECT_SPECIAL_DEFENSE_DOWN_2
	.4byte BattleScript_EffectAccuracyDown2           @ EFFECT_ACCURACY_DOWN_2
	.4byte BattleScript_EffectEvasionDown2            @ EFFECT_EVASION_DOWN_2
	.4byte BattleScript_EffectReflect                 @ EFFECT_REFLECT
	.4byte BattleScript_EffectPoison                  @ EFFECT_POISON
	.4byte BattleScript_EffectParalyze                @ EFFECT_PARALYZE
	.4byte BattleScript_EffectAttackDownHit           @ EFFECT_ATTACK_DOWN_HIT
	.4byte BattleScript_EffectDefenseDownHit          @ EFFECT_DEFENSE_DOWN_HIT
	.4byte BattleScript_EffectSpeedDownHit            @ EFFECT_SPEED_DOWN_HIT
	.4byte BattleScript_EffectSpecialAttackDownHit    @ EFFECT_SPECIAL_ATTACK_DOWN_HIT
	.4byte BattleScript_EffectSpecialDefenseDownHit   @ EFFECT_SPECIAL_DEFENSE_DOWN_HIT
	.4byte BattleScript_EffectAccuracyDownHit         @ EFFECT_ACCURACY_DOWN_HIT
	.4byte BattleScript_EffectHit                     @ EFFECT_EVASION_DOWN_HIT
	.4byte BattleScript_EffectTwoTurnsAttack          @ EFFECT_TWO_TURNS_ATTACK
	.4byte BattleScript_EffectConfuseHit              @ EFFECT_CONFUSE_HIT
	.4byte BattleScript_EffectHitSwitchTarget         @ EFFECT_VITAL_THROW
	.4byte BattleScript_EffectSubstitute              @ EFFECT_SUBSTITUTE
	.4byte BattleScript_EffectRecharge                @ EFFECT_RECHARGE
	.4byte BattleScript_EffectRage                    @ EFFECT_RAGE
	.4byte BattleScript_EffectMimic                   @ EFFECT_MIMIC
	.4byte BattleScript_EffectMetronome               @ EFFECT_METRONOME
	.4byte BattleScript_EffectLeechSeed               @ EFFECT_LEECH_SEED
	.4byte BattleScript_EffectDoNothing               @ EFFECT_DO_NOTHING
	.4byte BattleScript_EffectDisable                 @ EFFECT_DISABLE
	.4byte BattleScript_EffectLevelDamage             @ EFFECT_LEVEL_DAMAGE
	.4byte BattleScript_EffectPsywave                 @ EFFECT_PSYWAVE
	.4byte BattleScript_EffectCounter                 @ EFFECT_COUNTER
	.4byte BattleScript_EffectEncore                  @ EFFECT_ENCORE
	.4byte BattleScript_EffectPainSplit               @ EFFECT_PAIN_SPLIT
	.4byte BattleScript_EffectSnore                   @ EFFECT_SNORE
	.4byte BattleScript_EffectConversion2             @ EFFECT_CONVERSION_2
	.4byte BattleScript_EffectLockOn                  @ EFFECT_LOCK_ON
	.4byte BattleScript_EffectSketch                  @ EFFECT_SKETCH
	.4byte BattleScript_EffectHammerArm               @ EFFECT_HAMMER_ARM
	.4byte BattleScript_EffectSleepTalk               @ EFFECT_SLEEP_TALK
	.4byte BattleScript_EffectDestinyBond             @ EFFECT_DESTINY_BOND
	.4byte BattleScript_EffectHit                     @ EFFECT_FLAIL
	.4byte BattleScript_EffectSpite                   @ EFFECT_SPITE
	.4byte BattleScript_EffectHit                     @ EFFECT_FALSE_SWIPE
	.4byte BattleScript_EffectHealBell                @ EFFECT_HEAL_BELL
	.4byte BattleScript_EffectHit                     @ EFFECT_ALWAYS_CRIT
	.4byte BattleScript_EffectTripleKick              @ EFFECT_TRIPLE_KICK
	.4byte BattleScript_EffectThief                   @ EFFECT_THIEF
	.4byte BattleScript_EffectMeanLook                @ EFFECT_MEAN_LOOK
	.4byte BattleScript_EffectNightmare               @ EFFECT_NIGHTMARE
	.4byte BattleScript_EffectMinimize                @ EFFECT_MINIMIZE
	.4byte BattleScript_EffectCurse                   @ EFFECT_CURSE
	.4byte BattleScript_EffectHealingWish             @ EFFECT_HEALING_WISH
	.4byte BattleScript_EffectProtect                 @ EFFECT_PROTECT
	.4byte BattleScript_EffectSpikes                  @ EFFECT_SPIKES
	.4byte BattleScript_EffectForesight               @ EFFECT_FORESIGHT
	.4byte BattleScript_EffectPerishSong              @ EFFECT_PERISH_SONG
	.4byte BattleScript_EffectSandstorm               @ EFFECT_SANDSTORM
	.4byte BattleScript_EffectEndure                  @ EFFECT_ENDURE
	.4byte BattleScript_EffectRollout                 @ EFFECT_ROLLOUT
	.4byte BattleScript_EffectSwagger                 @ EFFECT_SWAGGER
	.4byte BattleScript_EffectFuryCutter              @ EFFECT_FURY_CUTTER
	.4byte BattleScript_EffectAttract                 @ EFFECT_ATTRACT
	.4byte BattleScript_EffectHit                     @ EFFECT_RETURN
	.4byte BattleScript_EffectPresent                 @ EFFECT_PRESENT
	.4byte BattleScript_EffectHit                     @ EFFECT_FRUSTRATION
	.4byte BattleScript_EffectSafeguard               @ EFFECT_SAFEGUARD
	.4byte BattleScript_EffectMagnitude               @ EFFECT_MAGNITUDE
	.4byte BattleScript_EffectBatonPass               @ EFFECT_BATON_PASS
	.4byte BattleScript_EffectHit                     @ EFFECT_PURSUIT
	.4byte BattleScript_EffectRapidSpin               @ EFFECT_RAPID_SPIN
	.4byte BattleScript_EffectSonicBoom               @ EFFECT_SONIC_BOOM
	.4byte BattleScript_EffectCaptivate               @ EFFECT_CAPTIVATE
	.4byte BattleScript_EffectMorningSun              @ EFFECT_MORNING_SUN
	.4byte BattleScript_EffectSynthesis               @ EFFECT_SYNTHESIS
	.4byte BattleScript_EffectMoonlight               @ EFFECT_MOONLIGHT
	.4byte BattleScript_EffectHit                     @ EFFECT_HIDDEN_POWER
	.4byte BattleScript_EffectRainDance               @ EFFECT_RAIN_DANCE
	.4byte BattleScript_EffectSunnyDay                @ EFFECT_SUNNY_DAY
	.4byte BattleScript_EffectDefenseUpHit            @ EFFECT_DEFENSE_UP_HIT
	.4byte BattleScript_EffectAttackUpHit             @ EFFECT_ATTACK_UP_HIT
	.4byte BattleScript_EffectAllStatsUpHit           @ EFFECT_ALL_STATS_UP_HIT
	.4byte BattleScript_EffectHit                     @ EFFECT_FELL_STINGER
	.4byte BattleScript_EffectBellyDrum               @ EFFECT_BELLY_DRUM
	.4byte BattleScript_EffectPsychUp                 @ EFFECT_PSYCH_UP
	.4byte BattleScript_EffectMirrorCoat              @ EFFECT_MIRROR_COAT
	.4byte BattleScript_EffectSkullBash               @ EFFECT_SKULL_BASH
	.4byte BattleScript_EffectEarthquake              @ EFFECT_EARTHQUAKE
	.4byte BattleScript_EffectFutureSight             @ EFFECT_FUTURE_SIGHT
	.4byte BattleScript_EffectGust                    @ EFFECT_GUST
	.4byte BattleScript_EffectSolarBeam               @ EFFECT_SOLAR_BEAM
	.4byte BattleScript_EffectThunder                 @ EFFECT_THUNDER
	.4byte BattleScript_EffectTeleport                @ EFFECT_TELEPORT
	.4byte BattleScript_EffectBeatUp                  @ EFFECT_BEAT_UP
	.4byte BattleScript_EffectSemiInvulnerable        @ EFFECT_SEMI_INVULNERABLE
	.4byte BattleScript_EffectDefenseCurl             @ EFFECT_DEFENSE_CURL
	.4byte BattleScript_EffectSoftboiled              @ EFFECT_SOFTBOILED
	.4byte BattleScript_EffectFakeOut                 @ EFFECT_FAKE_OUT
	.4byte BattleScript_EffectUproar                  @ EFFECT_UPROAR
	.4byte BattleScript_EffectStockpile               @ EFFECT_STOCKPILE
	.4byte BattleScript_EffectSpitUp                  @ EFFECT_SPIT_UP
	.4byte BattleScript_EffectSwallow                 @ EFFECT_SWALLOW
	.4byte BattleScript_EffectWorrySeed               @ EFFECT_WORRY_SEED
	.4byte BattleScript_EffectHail                    @ EFFECT_HAIL
	.4byte BattleScript_EffectTorment                 @ EFFECT_TORMENT
	.4byte BattleScript_EffectFlatter                 @ EFFECT_FLATTER
	.4byte BattleScript_EffectWillOWisp               @ EFFECT_WILL_O_WISP
	.4byte BattleScript_EffectMemento                 @ EFFECT_MEMENTO
	.4byte BattleScript_EffectHit                     @ EFFECT_FACADE
	.4byte BattleScript_EffectFocusPunch              @ EFFECT_FOCUS_PUNCH
	.4byte BattleScript_EffectSmellingsalt            @ EFFECT_SMELLINGSALT
	.4byte BattleScript_EffectFollowMe                @ EFFECT_FOLLOW_ME
	.4byte BattleScript_EffectNaturePower             @ EFFECT_NATURE_POWER
	.4byte BattleScript_EffectCharge                  @ EFFECT_CHARGE
	.4byte BattleScript_EffectTaunt                   @ EFFECT_TAUNT
	.4byte BattleScript_EffectHelpingHand             @ EFFECT_HELPING_HAND
	.4byte BattleScript_EffectTrick                   @ EFFECT_TRICK
	.4byte BattleScript_EffectRolePlay                @ EFFECT_ROLE_PLAY
	.4byte BattleScript_EffectWish                    @ EFFECT_WISH
	.4byte BattleScript_EffectAssist                  @ EFFECT_ASSIST
	.4byte BattleScript_EffectIngrain                 @ EFFECT_INGRAIN
	.4byte BattleScript_EffectSuperpower              @ EFFECT_SUPERPOWER
	.4byte BattleScript_EffectMagicCoat               @ EFFECT_MAGIC_COAT
	.4byte BattleScript_EffectRecycle                 @ EFFECT_RECYCLE
	.4byte BattleScript_EffectHit                     @ EFFECT_REVENGE
	.4byte BattleScript_EffectBrickBreak              @ EFFECT_BRICK_BREAK
	.4byte BattleScript_EffectYawn                    @ EFFECT_YAWN
	.4byte BattleScript_EffectKnockOff                @ EFFECT_KNOCK_OFF
	.4byte BattleScript_EffectEndeavor                @ EFFECT_ENDEAVOR
	.4byte BattleScript_EffectHit                     @ EFFECT_ERUPTION
	.4byte BattleScript_EffectSkillSwap               @ EFFECT_SKILL_SWAP
	.4byte BattleScript_EffectImprison                @ EFFECT_IMPRISON
	.4byte BattleScript_EffectRefresh                 @ EFFECT_REFRESH
	.4byte BattleScript_EffectGrudge                  @ EFFECT_GRUDGE
	.4byte BattleScript_EffectSnatch                  @ EFFECT_SNATCH
	.4byte BattleScript_EffectHit                     @ EFFECT_LOW_KICK
	.4byte BattleScript_EffectSecretPower             @ EFFECT_SECRET_POWER
	.4byte BattleScript_EffectHit                     @ EFFECT_RECOIL_33
	.4byte BattleScript_EffectTeeterDance             @ EFFECT_TEETER_DANCE
	.4byte BattleScript_EffectHitEscape               @ EFFECT_HIT_ESCAPE
	.4byte BattleScript_EffectMudSport                @ EFFECT_MUD_SPORT
	.4byte BattleScript_EffectPoisonFang              @ EFFECT_POISON_FANG
	.4byte BattleScript_EffectHit                     @ EFFECT_WEATHER_BALL
	.4byte BattleScript_EffectOverheat                @ EFFECT_OVERHEAT
	.4byte BattleScript_EffectTickle                  @ EFFECT_TICKLE
	.4byte BattleScript_EffectCosmicPower             @ EFFECT_COSMIC_POWER
	.4byte BattleScript_EffectSkyUppercut             @ EFFECT_SKY_UPPERCUT
	.4byte BattleScript_EffectBulkUp                  @ EFFECT_BULK_UP
	.4byte BattleScript_EffectPlaceholder             @ EFFECT_PLACEHOLDER
	.4byte BattleScript_EffectWaterSport              @ EFFECT_WATER_SPORT
	.4byte BattleScript_EffectCalmMind                @ EFFECT_CALM_MIND
	.4byte BattleScript_EffectDragonDance             @ EFFECT_DRAGON_DANCE
	.4byte BattleScript_EffectCamouflage              @ EFFECT_CAMOUFLAGE
	.4byte BattleScript_EffectHit                     @ EFFECT_PLEDGE
	.4byte BattleScript_EffectFling                   @ EFFECT_FLING
	.4byte BattleScript_EffectNaturalGift             @ EFFECT_NATURAL_GIFT
	.4byte BattleScript_EffectWakeUpSlap              @ EFFECT_WAKE_UP_SLAP
	.4byte BattleScript_EffectHit                     @ EFFECT_WRING_OUT
	.4byte BattleScript_EffectEerieSpell              @ EFFECT_HEX
	.4byte BattleScript_EffectHit                     @ EFFECT_ASSURANCE
	.4byte BattleScript_EffectHit                     @ EFFECT_TRUMP_CARD
	.4byte BattleScript_EffectHit                     @ EFFECT_ACROBATICS
	.4byte BattleScript_EffectHit                     @ EFFECT_HEAT_CRASH
	.4byte BattleScript_EffectHit                     @ EFFECT_PUNISHMENT
	.4byte BattleScript_EffectHit                     @ EFFECT_STORED_POWER
	.4byte BattleScript_EffectHit                     @ EFFECT_ELECTRO_BALL
	.4byte BattleScript_EffectHit                     @ EFFECT_GYRO_BALL
	.4byte BattleScript_EffectHit                     @ EFFECT_ECHOED_VOICE
	.4byte BattleScript_EffectHit                     @ EFFECT_PAYBACK
	.4byte BattleScript_EffectRound                   @ EFFECT_ROUND
	.4byte BattleScript_EffectHit                     @ EFFECT_BRINE
	.4byte BattleScript_EffectHit                     @ EFFECT_VENOSHOCK
	.4byte BattleScript_EffectHit                     @ EFFECT_RETALIATE
	.4byte BattleScript_EffectBulldoze                @ EFFECT_BULLDOZE
	.4byte BattleScript_EffectHit                     @ EFFECT_FOUL_PLAY
	.4byte BattleScript_EffectHit                     @ EFFECT_PSYSHOCK
	.4byte BattleScript_EffectRoost                   @ EFFECT_ROOST
	.4byte BattleScript_EffectGravity                 @ EFFECT_GRAVITY
	.4byte BattleScript_EffectMiracleEye              @ EFFECT_MIRACLE_EYE
	.4byte BattleScript_EffectTailwind                @ EFFECT_TAILWIND
	.4byte BattleScript_EffectEmbargo                 @ EFFECT_EMBARGO
	.4byte BattleScript_EffectAquaRing                @ EFFECT_AQUA_RING
	.4byte BattleScript_EffectTrickRoom               @ EFFECT_TRICK_ROOM
	.4byte BattleScript_EffectWonderRoom              @ EFFECT_WONDER_ROOM
	.4byte BattleScript_EffectMagicRoom               @ EFFECT_MAGIC_ROOM
	.4byte BattleScript_EffectMagnetRise              @ EFFECT_MAGNET_RISE
	.4byte BattleScript_EffectToxicSpikes             @ EFFECT_TOXIC_SPIKES
	.4byte BattleScript_EffectGastroAcid              @ EFFECT_GASTRO_ACID
	.4byte BattleScript_EffectStealthRock             @ EFFECT_STEALTH_ROCK
	.4byte BattleScript_EffectTelekinesis             @ EFFECT_TELEKINESIS
	.4byte BattleScript_EffectPowerSwap               @ EFFECT_POWER_SWAP
	.4byte BattleScript_EffectGuardSwap               @ EFFECT_GUARD_SWAP
	.4byte BattleScript_EffectHeartSwap               @ EFFECT_HEART_SWAP
	.4byte BattleScript_EffectPowerSplit              @ EFFECT_POWER_SPLIT
	.4byte BattleScript_EffectGuardSplit              @ EFFECT_GUARD_SPLIT
	.4byte BattleScript_EffectStickyWeb               @ EFFECT_STICKY_WEB
	.4byte BattleScript_EffectMetalBurst              @ EFFECT_METAL_BURST
	.4byte BattleScript_EffectLuckyChant              @ EFFECT_LUCKY_CHANT
	.4byte BattleScript_EffectSuckerPunch             @ EFFECT_SUCKER_PUNCH
	.4byte BattleScript_EffectSpecialDefenseDownHit2  @ EFFECT_SPECIAL_DEFENSE_DOWN_HIT_2
	.4byte BattleScript_EffectSimpleBeam              @ EFFECT_SIMPLE_BEAM
	.4byte BattleScript_EffectEntrainment             @ EFFECT_ENTRAINMENT
	.4byte BattleScript_EffectHealPulse               @ EFFECT_HEAL_PULSE
	.4byte BattleScript_EffectQuash                   @ EFFECT_QUASH
	.4byte BattleScript_EffectIonDeluge               @ EFFECT_ION_DELUGE
#if B_USE_FROSTBITE == TRUE
	.4byte BattleScript_EffectFrostbiteHit            @ EFFECT_FREEZE_DRY
#else
	.4byte BattleScript_EffectFreezeHit               @ EFFECT_FREEZE_DRY
#endif
	.4byte BattleScript_EffectTopsyTurvy              @ EFFECT_TOPSY_TURVY
	.4byte BattleScript_EffectMistyTerrain            @ EFFECT_MISTY_TERRAIN
	.4byte BattleScript_EffectGrassyTerrain           @ EFFECT_GRASSY_TERRAIN
	.4byte BattleScript_EffectElectricTerrain         @ EFFECT_ELECTRIC_TERRAIN
	.4byte BattleScript_EffectPsychicTerrain          @ EFFECT_PSYCHIC_TERRAIN
	.4byte BattleScript_EffectAttackAccUp             @ EFFECT_ATTACK_ACCURACY_UP
	.4byte BattleScript_EffectAttackSpAttackUp        @ EFFECT_ATTACK_SPATK_UP
	.4byte BattleScript_EffectHurricane               @ EFFECT_HURRICANE
	.4byte BattleScript_EffectHit                     @ EFFECT_TWO_TYPED_MOVE
	.4byte BattleScript_EffectMeFirst                 @ EFFECT_ME_FIRST
	.4byte BattleScript_EffectSpeedUpHit              @ EFFECT_SPEED_UP_HIT
	.4byte BattleScript_EffectQuiverDance             @ EFFECT_QUIVER_DANCE
	.4byte BattleScript_EffectCoil                    @ EFFECT_COIL
	.4byte BattleScript_EffectElectrify               @ EFFECT_ELECTRIFY
	.4byte BattleScript_EffectReflectType             @ EFFECT_REFLECT_TYPE
	.4byte BattleScript_EffectSoak                    @ EFFECT_SOAK
	.4byte BattleScript_EffectGrowth                  @ EFFECT_GROWTH
	.4byte BattleScript_EffectCloseCombat             @ EFFECT_CLOSE_COMBAT
	.4byte BattleScript_EffectLastResort              @ EFFECT_LAST_RESORT
	.4byte BattleScript_EffectHit                     @ EFFECT_RECOIL_33_STATUS
	.4byte BattleScript_EffectFlinchStatus            @ EFFECT_FLINCH_STATUS
	.4byte BattleScript_EffectHit                     @ EFFECT_RECOIL_50
	.4byte BattleScript_EffectShellSmash              @ EFFECT_SHELL_SMASH
	.4byte BattleScript_EffectShiftGear               @ EFFECT_SHIFT_GEAR
	.4byte BattleScript_EffectDefenseUp3              @ EFFECT_DEFENSE_UP_3
	.4byte BattleScript_EffectFakeOut                 @ EFFECT_NOBLE_ROAR
	.4byte BattleScript_EffectVenomDrench             @ EFFECT_VENOM_DRENCH
	.4byte BattleScript_EffectToxicThread             @ EFFECT_TOXIC_THREAD
	.4byte BattleScript_EffectClearSmog               @ EFFECT_CLEAR_SMOG
	.4byte BattleScript_EffectHitSwitchTarget         @ EFFECT_HIT_SWITCH_TARGET
	.4byte BattleScript_EffectFinalGambit             @ EFFECT_FINAL_GAMBIT
	.4byte BattleScript_EffectHit                     @ EFFECT_CHANGE_TYPE_ON_ITEM
	.4byte BattleScript_EffectAutotomize              @ EFFECT_AUTOTOMIZE
	.4byte BattleScript_EffectCopycat                 @ EFFECT_COPYCAT
	.4byte BattleScript_EffectDefog                   @ EFFECT_DEFOG
	.4byte BattleScript_EffectHitEnemyHealAlly        @ EFFECT_HIT_ENEMY_HEAL_ALLY
	.4byte BattleScript_EffectSmackDown               @ EFFECT_SMACK_DOWN
	.4byte BattleScript_EffectSynchronoise            @ EFFECT_SYNCHRONOISE
	.4byte BattleScript_EffectPsychoShift             @ EFFECT_PSYCHO_SHIFT
	.4byte BattleScript_EffectPowerTrick              @ EFFECT_POWER_TRICK
	.4byte BattleScript_EffectFlameBurst              @ EFFECT_FLAME_BURST
	.4byte BattleScript_EffectAfterYou                @ EFFECT_AFTER_YOU
	.4byte BattleScript_EffectBestow                  @ EFFECT_BESTOW
	.4byte BattleScript_EffectRototiller              @ EFFECT_ROTOTILLER
	.4byte BattleScript_EffectFlowerShield            @ EFFECT_FLOWER_SHIELD
	.4byte BattleScript_EffectHitPreventEscape        @ EFFECT_HIT_PREVENT_ESCAPE
	.4byte BattleScript_EffectSpeedSwap               @ EFFECT_SPEED_SWAP
	.4byte BattleScript_EffectDefenseUp2Hit           @ EFFECT_DEFENSE_UP2_HIT
	.4byte BattleScript_EffectHit                     @ EFFECT_REVELATION_DANCE
	.4byte BattleScript_EffectAuroraVeil              @ EFFECT_AURORA_VEIL
	.4byte BattleScript_EffectThirdType               @ EFFECT_THIRD_TYPE
	.4byte BattleScript_EffectFeint                   @ EFFECT_FEINT
	.4byte BattleScript_EffectSparklingAria           @ EFFECT_SPARKLING_ARIA
	.4byte BattleScript_EffectAcupressure             @ EFFECT_ACUPRESSURE
	.4byte BattleScript_EffectAromaticMist            @ EFFECT_AROMATIC_MIST
	.4byte BattleScript_EffectPowder                  @ EFFECT_POWDER
	.4byte BattleScript_EffectSpAtkUpHit              @ EFFECT_SP_ATTACK_UP_HIT
	.4byte BattleScript_EffectSpecialAttackDownHit    @ EFFECT_BELCH
	.4byte BattleScript_EffectPartingShot             @ EFFECT_PARTING_SHOT
	.4byte BattleScript_EffectSpectralThief           @ EFFECT_SPECTRAL_THIEF
	.4byte BattleScript_EffectVCreate                 @ EFFECT_V_CREATE
	.4byte BattleScript_EffectMatBlock                @ EFFECT_MAT_BLOCK
	.4byte BattleScript_EffectHit                     @ EFFECT_STOMPING_TANTRUM
	.4byte BattleScript_EffectCoreEnforcer            @ EFFECT_CORE_ENFORCER
	.4byte BattleScript_EffectInstruct                @ EFFECT_INSTRUCT
	.4byte BattleScript_EffectThroatChop              @ EFFECT_THROAT_CHOP
	.4byte BattleScript_EffectLaserFocus              @ EFFECT_LASER_FOCUS
	.4byte BattleScript_EffectMagneticFlux            @ EFFECT_MAGNETIC_FLUX
	.4byte BattleScript_EffectGearUp                  @ EFFECT_GEAR_UP
	.4byte BattleScript_EffectIncinerate              @ EFFECT_INCINERATE
	.4byte BattleScript_EffectBugBite                 @ EFFECT_BUG_BITE
	.4byte BattleScript_EffectStrengthSap             @ EFFECT_STRENGTH_SAP
	.4byte BattleScript_EffectHit                     @ EFFECT_MIND_BLOWN
	.4byte BattleScript_EffectPurify                  @ EFFECT_PURIFY
	.4byte BattleScript_EffectBurnUp                  @ EFFECT_BURN_UP
	.4byte BattleScript_EffectShoreUp                 @ EFFECT_SHORE_UP
	.4byte BattleScript_EffectGeomancy                @ EFFECT_GEOMANCY
	.4byte BattleScript_EffectFairyLock               @ EFFECT_FAIRY_LOCK
	.4byte BattleScript_EffectAllySwitch              @ EFFECT_ALLY_SWITCH
	.4byte BattleScript_EffectRelicSong               @ EFFECT_RELIC_SONG
	.4byte BattleScript_EffectAttackerDefenseDownHit  @ EFFECT_ATTACKER_DEFENSE_DOWN_HIT
	.4byte BattleScript_EffectHit                     @ EFFECT_BODY_PRESS
	.4byte BattleScript_EffectEerieSpell              @ EFFECT_EERIE_SPELL
	.4byte BattleScript_EffectJungleHealing           @ EFFECT_JUNGLE_HEALING
	.4byte BattleScript_EffectCoaching                @ EFFECT_COACHING
	.4byte BattleScript_EffectHit                     @ EFFECT_LASH_OUT
	.4byte BattleScript_EffectHit                     @ EFFECT_GRASSY_GLIDE
	.4byte BattleScript_EffectHit                     @ EFFECT_DYNAMAX_DOUBLE_DMG
	.4byte BattleScript_EffectDecorate                @ EFFECT_DECORATE
	.4byte BattleScript_EffectHit                     @ EFFECT_SNIPE_SHOT
	.4byte BattleScript_EffectRecoilHP25              @ EFFECT_RECOIL_HP_25
	.4byte BattleScript_EffectStuffCheeks             @ EFFECT_STUFF_CHEEKS
	.4byte BattleScript_EffectGravApple               @ EFFECT_GRAV_APPLE
	.4byte BattleScript_EffectEvasionUpHit            @ EFFECT_EVASION_UP_HIT
	.4byte BattleScript_EffectGlitzyGlow              @ EFFECT_GLITZY_GLOW
	.4byte BattleScript_EffectBaddyBad                @ EFFECT_BADDY_BAD
	.4byte BattleScript_EffectSappySeed               @ EFFECT_SAPPY_SEED
	.4byte BattleScript_EffectFreezyFrost             @ EFFECT_FREEZY_FROST
	.4byte BattleScript_EffectSparklySwirl            @ EFFECT_SPARKLY_SWIRL
	.4byte BattleScript_EffectPlasmaFists             @ EFFECT_PLASMA_FISTS
	.4byte BattleScript_EffectHyperspaceFury          @ EFFECT_HYPERSPACE_FURY
	.4byte BattleScript_EffectAuraWheel               @ EFFECT_AURA_WHEEL
	.4byte BattleScript_EffectPhotonGeyser            @ EFFECT_PHOTON_GEYSER
	.4byte BattleScript_EffectShellSideArm            @ EFFECT_SHELL_SIDE_ARM
	.4byte BattleScript_EffectHit                     @ EFFECT_TERRAIN_PULSE
	.4byte BattleScript_EffectJawLock                 @ EFFECT_JAW_LOCK
	.4byte BattleScript_EffectNoRetreat               @ EFFECT_NO_RETREAT
	.4byte BattleScript_EffectTarShot                 @ EFFECT_TAR_SHOT
	.4byte BattleScript_EffectPoltergeist             @ EFFECT_POLTERGEIST
	.4byte BattleScript_EffectOctolock                @ EFFECT_OCTOLOCK
	.4byte BattleScript_EffectClangorousSoul          @ EFFECT_CLANGOROUS_SOUL
	.4byte BattleScript_EffectHit                     @ EFFECT_SEA_JAWS
	.4byte BattleScript_EffectSkyDrop                 @ EFFECT_SKY_DROP
	.4byte BattleScript_EffectHit                     @ EFFECT_EXPANDING_FORCE
	.4byte BattleScript_EffectMeteorBeam              @ EFFECT_METEOR_BEAM
	.4byte BattleScript_EffectHit                     @ EFFECT_RISING_VOLTAGE
	.4byte BattleScript_EffectHit                     @ EFFECT_BEAK_BLAST
	.4byte BattleScript_EffectCourtChange             @ EFFECT_COURT_CHANGE
	.4byte BattleScript_EffectChloroblast             @ EFFECT_CHLOROBLAST
	.4byte BattleScript_EffectExtremeEvoboost         @ EFFECT_EXTREME_EVOBOOST
	.4byte BattleScript_EffectHitSetRemoveTerrain     @ EFFECT_HIT_SET_REMOVE_TERRAIN
	.4byte BattleScript_EffectDarkVoid                @ EFFECT_DARK_VOID
	.4byte BattleScript_EffectSleepHit                @ EFFECT_SLEEP_HIT
	.4byte BattleScript_EffectDoubleShock             @ EFFECT_DOUBLE_SHOCK
	.4byte BattleScript_EffectSpecialAttackUpHit      @ EFFECT_SPECIAL_ATTACK_UP_HIT
	.4byte BattleScript_EffectVictoryDance            @ EFFECT_VICTORY_DANCE
	.4byte BattleScript_EffectTeatime                 @ EFFECT_TEATIME
	.4byte BattleScript_EffectAttackUpUserAlly        @ EFFECT_ATTACK_UP_USER_ALLY
	.4byte BattleScript_EffectShellTrap               @ EFFECT_SHELL_TRAP
	.4byte BattleScript_EffectHit                     @ EFFECT_PSYBLADE
	.4byte BattleScript_EffectHit                     @ EFFECT_HYDRO_STEAM
	.4byte BattleScript_EffectHitSetEntryHazard       @ EFFECT_HIT_SET_ENTRY_HAZARD
	.4byte BattleScript_EffectDireClaw                @ EFFECT_DIRE_CLAW
	.4byte BattleScript_EffectPoisonHit               @ EFFECT_BARB_BARRAGE
	.4byte BattleScript_EffectRevivalBlessing         @ EFFECT_REVIVAL_BLESSING
	.4byte BattleScript_EffectFrostbiteHit            @ EFFECT_FROSTBITE_HIT
	.4byte BattleScript_EffectSnow                    @ EFFECT_SNOWSCAPE
	.4byte BattleScript_EffectTripleArrows            @ EFFECT_TRIPLE_ARROWS
	.4byte BattleScript_EffectInfernalParade          @ EFFECT_INFERNAL_PARADE
	.4byte BattleScript_EffectTakeHeart               @ EFFECT_TAKE_HEART
	.4byte BattleScript_EffectAxeKick                 @ EFFECT_AXE_KICK
	.4byte BattleScript_EffectHit                     @ EFFECT_COLLISION_COURSE
	.4byte BattleScript_EffectSpinOut                 @ EFFECT_SPIN_OUT
	.4byte BattleScript_EffectMakeItRain              @ EFFECT_MAKE_IT_RAIN
	.4byte BattleScript_EffectCorrosiveGas            @ EFFECT_CORROSIVE_GAS
	.4byte BattleScript_EffectHit                     @ EFFECT_POPULATION_BOMB
	.4byte BattleScript_EffectMortalSpin              @ EFFECT_MORTAL_SPIN
	.4byte BattleScript_EffectHit                     @ EFFECT_GIGATON_HAMMER
	.4byte BattleScript_EffectSaltCure                @ EFFECT_SALT_CURE
	.4byte BattleScript_EffectGlaciate                @ EFFECT_GLACIATE
	.4byte BattleScript_EffectChillyAir               @ EFFECT_CHILLY_AIR
	.4byte BattleScript_EffectHit                     @ EFFECT_LAST_RESPECTS
	.4byte BattleScript_EffectHit                     @ EFFECT_RAGE_FIST
	.4byte BattleScript_EffectFilletAway              @ EFFECT_FILLET_AWAY
	.4byte BattleScript_EffectChillyReception         @ EFFECT_CHILLY_RECEPTION
	.4byte BattleScript_EffectShedTail                @ EFFECT_SHED_TAIL
	.4byte BattleScript_EffectFickleBeam              @ EFFECT_FICKLE_BEAM
	.4byte BattleScript_EffectDragonCheer             @ EFFECT_DRAGON_CHEER
	.4byte BattleScript_EffectPsychicNoise            @ EFFECT_PSYCHIC_NOISE
	.4byte BattleScript_EffectHit			          @ EFFECT_SNUFF_OUT
	.4byte BattleScript_EffectColdMend                @ EFFECT_COLD_MEND
	.4byte BattleScript_EffectViperStrike             @ EFFECT_VIPER_STRIKE
	.4byte BattleScript_EffectAllStatsUp2Hit          @ EFFECT_ALL_STATS_UP_2_HIT
	.4byte BattleScript_EffectSpook                   @ EFFECT_SPOOK
	.4byte BattleScript_EffectUTurn                   @ EFFECT_U_TURN
	.4byte BattleScript_EffectSilverWind              @ EFFECT_SILVER_WIND
	.4byte BattleScript_EffectSignalBeam              @ EFFECT_SIGNAL_BEAM
	.4byte BattleScript_EffectRagePowder              @ EFFECT_RAGE_POWDER
	.4byte BattleScript_EffectSpiderWeb               @ EFFECT_SPIDER_WEB
	.4byte BattleScript_EffectHit                     @ EFFECT_RECOIL_50_STATUS
	.4byte BattleScript_EffectEerieImpulse            @ EFFECT_EERIE_IMPULSE
	.4byte BattleScript_EffectFlash                   @ EFFECT_FLASH
	.4byte BattleScript_EffectCharm                   @ EFFECT_CHARM
	.4byte BattleScript_EffectBitterMalice            @ EFFECT_BITTER_MALICE
	.4byte BattleScript_EffectHeartStamp              @ EFFECT_HEART_STAMP
	.4byte BattleScript_EffectMeditate                @ EFFECT_MEDITATE
	.4byte BattleScript_EffectFlipTurn                @ EFFECT_FLIP_TURN
	.4byte BattleScript_EffectAccuracyDownHit         @ EFFECT_MUDDY_WATER
	.4byte BattleScript_EffectDragonRuin              @ EFFECT_DRAGON_RUIN
	.4byte BattleScript_EffectCinderTwirl             @ EFFECT_CINDER_TWIRL
	.4byte BattleScript_EffectCinderDrill             @ EFFECT_CINDER_DRILL
	.4byte BattleScript_EffectSilence                 @ EFFECT_SILENCE
	.4byte BattleScript_EffectVexingKi                @ EFFECT_VEXING_KI
	.4byte BattleScript_EffectEerieSpell              @ EFFECT_DECAY_BEAM
	.4byte BattleScript_EffectWarmWelcome             @ EFFECT_WARM_WELCOME
	.4byte BattleScript_EffectRadioacid               @ EFFECT_RADIOACID
	.4byte BattleScript_EffectPartingCurry            @ EFFECT_PARTING_CURRY
	.4byte BattleScript_EffectSerpentSurge            @ EFFECT_SERPENT_SURGE
	.4byte BattleScript_EffectTidyUp                  @ EFFECT_TIDY_UP
	.4byte BattleScript_EffectAbsorb                  @ EFFECT_DRAINING_KISS
	.4byte BattleScript_EffectHullbreaker             @ EFFECT_HULLBREAKER
	.4byte BattleScript_EffectHeartCarve              @ EFFECT_HEART_CARVE
	.4byte BattleScript_EffectDragonPoker             @ EFFECT_DRAGON_POKER
	.4byte BattleScript_EffectFlinchHit               @ EFFECT_WATERFALL
	.4byte BattleScript_EffectDefenseDownHit          @ EFFECT_CUT
	.4byte BattleScript_EffectRockSmash               @ EFFECT_ROCK_SMASH
	.4byte BattleScript_EffectHit                     @ EFFECT_STRENGTH
	.4byte BattleScript_EffectConfuseHit              @ EFFECT_ROCK_CLIMB
	.4byte BattleScript_EffectHit                     @ EFFECT_SURF
	.4byte BattleScript_EffectSemiInvulnerable        @ EFFECT_DIVE
	.4byte BattleScript_EffectFly                     @ EFFECT_FLY
	.4byte BattleScript_EffectTrap                    @ EFFECT_WHIRLPOOL
	.4byte BattleScript_EffectAbsorb                  @ EFFECT_LONE_SHARK
	.4byte BattleScript_EffectHeartSteal              @ EFFECT_HEART_STEAL
	.4byte BattleScript_EffectHit                     @ EFFECT_IGNA_STRIKE
	.4byte BattleScript_EffectDefAccDownHit           @ EFFECT_ACCURACY_DEFENSE_DOWN_HIT
	.4byte BattleScript_EffectVenomDrain              @ EFFECT_VENOM_DRAIN
	.4byte BattleScript_EffectAllStatsDownHit         @ EFFECT_ALL_STATS_DOWN_HIT
	.4byte BattleScript_EffectHit                     @ EFFECT_WILLPOWER
	.4byte BattleScript_EffectHitEscape               @ EFFECT_MANEUVER
	.4byte BattleScript_EffectScorpFang               @ EFFECT_SCORP_FANG
	.4byte BattleScript_EffectHitSetEntryHazard       @ EFFECT_RECOIL_50_HAZARD
	.4byte BattleScript_EffectFrostbiteHit            @ EFFECT_WICKED_WINDS
	.4byte BattleScript_EffectSandTomb                @ EFFECT_SAND_TOMB
	.4byte BattleScript_EffectConfuseHit              @ EFFECT_SONIC_BURST
	.4byte BattleScript_EffectHit                     @ EFFECT_SOUL_CUTTER
	.4byte BattleScript_EffectVoid                    @ EFFECT_VOID
	.4byte BattleScript_EffectKerfuffle               @ EFFECT_KERFUFFLE
	.4byte BattleScript_EffectVerglastrom             @ EFFECT_VERGLASTROM
	.4byte BattleScript_EffectHit                     @ EFFECT_EXORCISM
	.4byte BattleScript_EffectLoveTap                 @ EFFECT_LOVE_TAP
	.4byte BattleScript_EffectSolarFlare              @ EFFECT_SOLAR_FLARE
	.4byte BattleScript_EffectPanicHit                @ EFFECT_PANIC_HIT
	.4byte BattleScript_EffectBloomingHit             @ EFFECT_BLOOMING_HIT
	.4byte BattleScript_EffectExposedHit              @ EFFECT_EXPOSED_HIT
	.4byte BattleScript_EffectTearfulLook             @ EFFECT_TEARFUL_LOOK
	.4byte BattleScript_EffectAbsorb                  @ EFFECT_BLACK_BUFFET
	.4byte BattleScript_EffectExecution               @ EFFECT_EXECUTION
	.4byte BattleScript_EffectSeizeChance             @ EFFECT_SEIZE_CHANCE
	.4byte BattleScript_EffectRazingSun               @ EFFECT_RAZING_SUN
	.4byte BattleScript_EffectTerrorize               @ EFFECT_TERRORIZE
	.4byte BattleScript_EffectBrutalize               @ EFFECT_BRUTALIZE
	.4byte BattleScript_EffectSuckerPunch             @ EFFECT_ROADBLOCK
	.4byte BattleScript_EffectDefenseDownHit2         @ EFFECT_DEFENSE_DOWN_HIT_2
	.4byte BattleScript_EffectHitSetRemoveTerrain     @ EFFECT_EARTH_SHATTER
	.4byte BattleScript_EffectHit                     @ EFFECT_PILGRIMAGE
	.4byte BattleScript_EffectCloseCombat             @ EFFECT_HEAVY_CANNON
	.4byte BattleScript_EffectCloseCombat             @ EFFECT_GIANTS_SPEAR
	.4byte BattleScript_EffectRedline                 @ EFFECT_REDLINE
	.4byte BattleScript_EffectSpeedDownHit            @ EFFECT_ZAPPER
	.4byte BattleScript_EffectSkySplitter             @ EFFECT_SKY_SPLITTER
	.4byte BattleScript_EffectAllStatsUp2HitFoe       @ EFFECT_ALL_STATS_UP_2_HIT_FOE
	.4byte BattleScript_EffectTickTack                @ EFFECT_TICK_TACK
	.4byte BattleScript_EffectDeepGaze                @ EFFECT_DEEP_GAZE
	.4byte BattleScript_EffectEnervator               @ EFFECT_ENERVATOR
	.4byte BattleScript_EffectErodeField              @ EFFECT_ERODE_FIELD
	.4byte BattleScript_EffectHeavyCell               @ EFFECT_HEAVY_CELL
	.4byte BattleScript_EffectCriticalRepair          @ EFFECT_CRITICAL_REPAIR
	.4byte BattleScript_EffectRemodel                 @ EFFECT_REMODEL
	.4byte BattleScript_EffectHit                     @ EFFECT_BARI_BARI_BEAM
	.4byte BattleScript_EffectHit                     @ EFFECT_BARI_BARI_BASH
	.4byte BattleScript_EffectSpAttackAccUp           @ EFFECT_SP_ATTACK_ACCURACY_UP
	.4byte BattleScript_EffectSunBask                 @ EFFECT_SUN_BASK
	.4byte BattleScript_EffectHearthwarm              @ EFFECT_HEARTHWARM
	.4byte BattleScript_EffectHit                     @ EFFECT_DUNE_SLICER
	.4byte BattleScript_EffectPowerDrain              @ EFFECT_POWER_DRAIN
	.4byte BattleScript_EffectFlorescence             @ EFFECT_FLORESCENCE
	.4byte BattleScript_EffectGrippingNail            @ EFFECT_GRIPPING_NAIL
	.4byte BattleScript_EffectSnapTrap                @ EFFECT_SNAP_TRAP
	.4byte BattleScript_EffectSpeedDownHit2           @ EFFECT_SPEED_DOWN_HIT_2
	.4byte BattleScript_EffectVigorRoot               @ EFFECT_VIGOR_ROOT
	.4byte BattleScript_EffectSeedBomb                @ EFFECT_SEED_BOMB
	.4byte BattleScript_EffectPetalBlizzard           @ EFFECT_PETAL_BLIZZARD
	.4byte BattleScript_EffectSpiritAway              @ EFFECT_SPIRIT_AWAY
	.4byte BattleScript_EffectPhantasm                @ EFFECT_PHANTASM
	.4byte BattleScript_EffectSnapblossom             @ EFFECT_SNAPBLOSSOM
	.4byte BattleScript_EffectGrassCannon             @ EFFECT_GRASS_CANNON
	.4byte BattleScript_EffectSpecialDefenseUpHit     @ EFFECT_SPECIAL_DEFENSE_UP_HIT
	.4byte BattleScript_EffectDefSpDefeUpHit          @ EFFECT_DEF_SP_DEF_UP_HIT
	.4byte BattleScript_EffectHit                     @ EFFECT_SAVAGE_WING
	.4byte BattleScript_EffectBurnHit                 @ EFFECT_PLASMA_CUTTER
	.4byte BattleScript_EffectBoundary                @ EFFECT_BOUNDARY
	.4byte BattleScript_EffectKnockOff                @ EFFECT_PARTY_TRICK
	.4byte BattleScript_EffectDanceMania              @ EFFECT_DANCE_MANIA
	.4byte BattleScript_EffectHit                     @ EFFECT_BEATBOX
	.4byte BattleScript_EffectSpeedUpUserAlly         @ EFFECT_SPEED_UP_USER_ALLY
	.4byte BattleScript_EffectIgnition                @ EFFECT_IGNITION
	.4byte BattleScript_EffectFairyWind               @ EFFECT_FAIRY_WIND
	.4byte BattleScript_EffectFloralHealing           @ EFFECT_FLORAL_HEALING
	.4byte BattleScript_EffectHit                     @ EFFECT_SHARP_GLIDE
	.4byte BattleScript_EffectHit                     @ EFFECT_CRASH_LAND
	.4byte BattleScript_EffectAirCannon               @ EFFECT_AIR_CANNON
	.4byte BattleScript_EffectFeatherDance            @ EFFECT_FEATHER_DANCE
	.4byte BattleScript_EffectBanshriek               @ EFFECT_BANSHRIEK
	.4byte BattleScript_EffectVineWhip                @ EFFECT_VINE_WHIP
	.4byte BattleScript_EffectTrailBlaze              @ EFFECT_TRAILBLAZE
	.4byte BattleScript_EffectNeedleArm               @ EFFECT_NEEDLE_ARM
	.4byte BattleScript_EffectTropKick                @ EFFECT_TROP_KICK
	.4byte BattleScript_EffectDrumBeating             @ EFFECT_DRUM_BEATING
	.4byte BattleScript_EffectWoodHammer              @ EFFECT_WOOD_HAMMER
	.4byte BattleScript_EffectAppleAcid               @ EFFECT_APPLE_ACID
	.4byte BattleScript_EffectEnergyBall              @ EFFECT_ENERGY_BALL
	.4byte BattleScript_EffectPetalDance              @ EFFECT_PETAL_DANCE
	.4byte BattleScript_EffectSnowfade                @ EFFECT_SNOWFADE
	.4byte BattleScript_EffectFrenzyPlant             @ EFFECT_FRENZY_PLANT
	.4byte BattleScript_EffectAromatherapy            @ EFFECT_AROMATHERAPY
	.4byte BattleScript_EffectGreenGuise              @ EFFECT_GREEN_GUISE
	.4byte BattleScript_EffectFreezeHit               @ EFFECT_FROST_SHRED
	.4byte BattleScript_EffectCottonSpore             @ EFFECT_COTTON_SPORE
	.4byte BattleScript_EffectSleepPowder             @ EFFECT_SLEEP_POWDER
	.4byte BattleScript_EffectPlunder                 @ EFFECT_PLUNDER
	.4byte BattleScript_EffectStunSpore               @ EFFECT_STUN_SPORE
	.4byte BattleScript_EffectGoldPlains              @ EFFECT_GOLD_PLAINS
	.4byte BattleScript_EffectDownfall                @ EFFECT_DOWNFALL
	.4byte BattleScript_EffectMtSplendor              @ EFFECT_MT_SPLENDOR
	.4byte BattleScript_EffectHit                     @ EFFECT_GATTLING_PINS
	.4byte BattleScript_EffectConstrict               @ EFFECT_CONSTRICT
	.4byte BattleScript_EffectHyperDrill              @ EFFECT_HYPER_DRILL
	.4byte BattleScript_EffectRechargeReduce          @ EFFECT_RECHARGE_REDUCE
	.4byte BattleScript_EffectPurification            @ EFFECT_PURIFICATION
	.4byte BattleScript_EffectMindReader              @ EFFECT_MIND_READER
	.4byte BattleScript_EffectOdorSleuth              @ EFFECT_ODOR_SLEUTH
	.4byte BattleScript_EffectSurpriseEgg             @ EFFECT_SURPRISE_EGG
	.4byte BattleScript_EffectBlock                   @ EFFECT_BLOCK
	.4byte BattleScript_EffectCutieCry                @ EFFECT_CUTIE_CRY
	.4byte BattleScript_EffectFleurCannon             @ EFFECT_FLEUR_CANNON
	.4byte BattleScript_EffectUpperHand               @ EFFECT_UPPER_HAND
	.4byte BattleScript_EffectWhirlwind               @ EFFECT_WHIRLWIND
	.4byte BattleScript_EffectHitEscape               @ EFFECT_GLACIAL_SHIFT
	.4byte BattleScript_EffectFrostNova               @ EFFECT_FROST_NOVA
	.4byte BattleScript_EffectSuckerPunch             @ EFFECT_POISON_DART
	.4byte BattleScript_EffectSmog                    @ EFFECT_SMOG
	.4byte BattleScript_EffectGunkFunk                @ EFFECT_GUNK_FUNK
	.4byte BattleScript_EffectPoisonPowder            @ EFFECT_POISON_POWDER
	.4byte BattleScript_EffectGravitonArm             @ EFFECT_GRAVITON_ARM
	.4byte BattleScript_EffectMistBall                @ EFFECT_MIST_BALL
	.4byte BattleScript_EffectKinesis                 @ EFFECT_KINESIS
	.4byte BattleScript_EffectReservoir               @ EFFECT_RESERVOIR
	.4byte BattleScript_EffectCannonade               @ EFFECT_CANNONADE
	.4byte BattleScript_EffectBurningEnvy             @ EFFECT_BURNING_ENVY
	.4byte BattleScript_EffectAcidArmor               @ EFFECT_ACID_ARMOR
	.4byte BattleScript_EffectPowerShift              @ EFFECT_POWER_SHIFT
	.4byte BattleScript_EffectMagicPowder             @ EFFECT_MAGIC_POWDER
	.4byte BattleScript_EffectRoar                    @ EFFECT_PSY_SWAP
	.4byte BattleScript_EffectShieldsUp               @ EFFECT_SHIELDS_UP
	.4byte BattleScript_EffectBerryBadJoke            @ EFFECT_BERRY_BAD_JOKE
	.4byte BattleScript_EffectHit                     @ EFFECT_STALAG_BLAST
	.4byte BattleScript_EffectMoonBeam                @ EFFECT_MOON_BEAM
	.4byte BattleScript_EffectHunkerDown              @ EFFECT_HUNKER_DOWN
	.4byte BattleScript_EffectHighRollHit             @ EFFECT_HIGH_ROLL_HIT
	.4byte BattleScript_EffectSpindaSwing             @ EFFECT_SPINDA_SWING
	.4byte BattleScript_EffectWildCharge              @ EFFECT_WILD_CHARGE
	.4byte BattleScript_EffectStormChase              @ EFFECT_STORM_CHASE
	.4byte BattleScript_EffectStormFury               @ EFFECT_STORM_FURY
	.4byte BattleScript_EffectSubmission              @ EFFECT_SUBMISSION
	.4byte BattleScript_EffectDragonClaw              @ EFFECT_DRAGON_CLAW
	.4byte BattleScript_EffectCheeseSteal             @ EFFECT_CHEESE_STEAL
	.4byte BattleScript_EffectLeafTornado             @ EFFECT_LEAF_TORNADO
	.4byte BattleScript_EffectAxelHeel                @ EFFECT_AXEL_HEEL
	.4byte BattleScript_EffectHit                     @ EFFECT_MIND_BREAK
	.4byte BattleScript_EffectHaywire                 @ EFFECT_HAYWIRE
	.4byte BattleScript_EffectHit                     @ EFFECT_FLYING_PRESS
	.4byte BattleScript_EffectTrueLovesKiss           @ EFFECT_TRUE_LOVES_KISS
	.4byte BattleScript_EffectFlinchHit               @ EFFECT_SABRE_BREAK
	.4byte BattleScript_EffectSyrupBomb               @ EFFECT_SYRUP_BOMB
	.4byte BattleScript_EffectOctazooka               @ EFFECT_OCTAZOOKA
	.4byte BattleScript_EffectOvertake                @ EFFECT_OVERTAKE
	.4byte BattleScript_EffectAttackOrder             @ EFFECT_ATTACK_ORDER
	.4byte BattleScript_EffectDefendOrder             @ EFFECT_DEFEND_ORDER
	.4byte BattleScript_EffectHealOrder               @ EFFECT_HEAL_ORDER
	.4byte BattleScript_EffectMountainGale            @ EFFECT_MOUNTAIN_GALE
	.4byte BattleScript_EffectForcePalm               @ EFFECT_FORCE_PALM
	.4byte BattleScript_EffectHit                     @ EFFECT_VACUUM_WAVE
	.4byte BattleScript_EffectHit                     @ EFFECT_FIERY_WRATH
	.4byte BattleScript_EffectDualChop                @ EFFECT_DUAL_CHOP
	.4byte BattleScript_EffectHit                     @ EFFECT_BOLT_BEAK
	.4byte BattleScript_EffectCovet                   @ EFFECT_COVET
	.4byte BattleScript_EffectSweetKiss               @ EFFECT_SWEET_KISS
	.4byte BattleScript_EffectRockPolish              @ EFFECT_ROCK_POLISH
	.4byte BattleScript_EffectHit                     @ EFFECT_POWER_GEM
	.4byte BattleScript_EffectPsychoCut               @ EFFECT_PSYCHO_CUT
	.4byte BattleScript_EffectHit                     @ EFFECT_RAZOR_SHELL
	.4byte BattleScript_EffectBrickBreak              @ EFFECT_PSYSTRIKE
	.4byte BattleScript_EffectCraftyShield            @ EFFECT_CRAFTY_SHIELD
	.4byte BattleScript_EffectMiseryWail              @ EFFECT_MISERY_WAIL
	.4byte BattleScript_EffectOrderUp                 @ EFFECT_ORDER_UP
	.4byte BattleScript_EffectZapCannon               @ EFFECT_ZAP_CANNON
	.4byte BattleScript_EffectGearGrind               @ EFFECT_GEAR_GRIND
	.4byte BattleScript_EffectHit                     @ EFFECT_MAGNET_BOMB
	.4byte BattleScript_EffectMetalSound              @ EFFECT_METAL_SOUND
	.4byte BattleScript_EffectSemiInvulnerable        @ EFFECT_SHADOW_FORCE
	.4byte BattleScript_EffectDearlyDepart            @ EFFECT_DEARLY_DEPART
	.4byte BattleScript_EffectPoisonTail              @ EFFECT_POISON_TAIL
	.4byte BattleScript_EffectHit                     @ EFFECT_DRAGON_PULSE
	.4byte BattleScript_EffectBlazingSoul             @ EFFECT_BLAZING_SOUL
	.4byte BattleScript_EffectConfuseHit              @ EFFECT_BARRAGE
	.4byte BattleScript_EffectRandomStatDropHit       @ EFFECT_PIN_MISSILE
	.4byte BattleScript_EffectDefenseDownHit          @ EFFECT_STELLAR_FIST
	.4byte BattleScript_EffectRechargeBurn            @ EFFECT_RECHARGE_BURN
	.4byte BattleScript_EffectAirCutter               @ EFFECT_AIR_CUTTER
	.4byte BattleScript_EffectHoldHands               @ EFFECT_HOLD_HANDS
	.4byte BattleScript_EffectAmnesia                 @ EFFECT_AMNESIA
	.4byte BattleScript_EffectMindGap                 @ EFFECT_MIND_GAP
	.4byte BattleScript_EffectJungleRage              @ EFFECT_JUNGLE_RAGE
	.4byte BattleScript_EffectAlluringVoice           @ EFFECT_ALLURING_VOICE
	.4byte BattleScript_EffectRockWrecker             @ EFFECT_ROCK_WRECKER
	.4byte BattleScript_EffectHydroCannon             @ EFFECT_HYDRO_CANNON
	.4byte BattleScript_EffectFearFactor              @ EFFECT_FEAR_FACTOR
	.4byte BattleScript_EffectNightDaze               @ EFFECT_NIGHT_DAZE
	.4byte BattleScript_EffectSpringBreeze            @ EFFECT_SPRING_BREEZE
	.4byte BattleScript_EffectHit                     @ EFFECT_AERIAL_ACE
	.4byte BattleScript_EffectDoubleTeam              @ EFFECT_DOUBLE_TEAM
	.4byte BattleScript_EffectSpotlight               @ EFFECT_SPOTLIGHT
	.4byte BattleScript_EffectHit                     @ EFFECT_COMET_PUNCH
	.4byte BattleScript_EffectBrickBreak              @ EFFECT_PSYCHIC_FANGS
	.4byte BattleScript_EffectTrickorTreat            @ EFFECT_TRICK_OR_TREAT
	.4byte BattleScript_EffectWorkUp                  @ EFFECT_WORK_UP
	.4byte BattleScript_EffectAttackUpHit             @ EFFECT_METAL_CLAW
	.4byte BattleScript_EffectDefenseUpHit            @ EFFECT_IRON_TAIL
	.4byte BattleScript_EffectSteelBeam               @ EFFECT_STEEL_BEAM
	.4byte BattleScript_EffectFocusBlast              @ EFFECT_FOCUS_BLAST
	.4byte BattleScript_EffectSpikeCannon             @ EFFECT_SPIKE_CANNON
	.4byte BattleScript_EffectDig                     @ EFFECT_DIG
	.4byte BattleScript_EffectBabyBlues               @ EFFECT_BABY_BLUES
	.4byte BattleScript_EffectLethalChain             @ EFFECT_LETHAL_CHAIN
	.4byte BattleScript_EffectZenHeadbutt             @ EFFECT_ZEN_HEADBUTT

BattleScript_EffectZenHeadbutt::
	jumpifholdeffect BS_ATTACKER, HOLD_EFFECT_MOON_MIRROR, BattleScript_TrueMoonBeam
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	curestatuswithmove BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectLethalChain::
	setmoveeffect MOVE_EFFECT_LETHAL_CHAIN
    goto BattleScript_EffectHit

BattleScript_EffectBabyBlues::
	attackcanceler
	attackstring
	ppreduce
	setbabyblues BS_ATTACKER
	goto BattleScript_PrintReflectLightScreenSafeguardString

BattleScript_EffectSolarFlare::
	jumpifholdeffect BS_ATTACKER, HOLD_EFFECT_SOLAR_SWORD, BattleScript_TrueSolarFlare
	goto BattleScript_EffectHit
BattleScript_TrueSolarFlare::
    call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessened
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRain
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOn
	setsunny
	printfromtable gMoveWeatherChangeStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	goto BattleScript_MoveEnd

BattleScript_EffectDig::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_SecondTurnDig
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_SecondTurnDig
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_DIG
	call BattleScriptFirstChargingTurn
	setsemiinvulnerablebit
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
BattleScript_SecondTurnDig::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	accuracycheck BattleScript_DigMiss, ACC_CURR_MOVE
	clearsemiinvulnerablebit
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_DigSummonGrassyTerrain
	goto BattleScript_HitFromAtkString
BattleScript_DigMiss::
	clearsemiinvulnerablebit
	goto BattleScript_PrintMoveMissed
BattleScript_DigSummonGrassyTerrain::
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	jumpifmovehadnoeffect BattleScript_DigTryFaint
	seteffectwithchance
	setremoveterrain BattleScript_DigTryFaint
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DigTryFaint:
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectSpikeCannon::
	attackcanceler
	accuracycheck BattleScript_EffectSpikeCannonMiss, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendall
	end
BattleScript_EffectSpikeCannonMiss::
	pause B_WAIT_TIME_SHORT
	effectivenesssound
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED
	trysetspikes BS_TARGET, BattleScript_SpikeCannonSkipEffect
	printstring STRINGID_SPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpikeCannonSkipEffect::
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	goto BattleScript_MoveEnd

BattleScript_EffectFocusBlast::
	attackcanceler
	accuracycheck BattleScript_EffectFocusBlastMiss, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendall
	end
BattleScript_EffectFocusBlastMiss::
	pause B_WAIT_TIME_SHORT
	effectivenesssound
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED
	call BattleScript_FocusBlastStatUp
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	goto BattleScript_MoveEnd
BattleScript_FocusBlastStatUp::
	setstatchanger STAT_ATK, 2, FALSE
	attackcanceler
	attackstring
	ppreduce
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_FocusBlastStatUpRet
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_FocusBlastStatUpAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_FocusBlastStatUpPrintString
BattleScript_FocusBlastStatUpAttackAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_FocusBlastStatUpPrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FocusBlastStatUpRet::
	return

BattleScript_EffectSteelBeam::
	setmoveeffect MOVE_EFFECT_DEF_PLUS_2 | MOVE_EFFECT_AFFECTS_USER
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_SteelBeamMiss, ACC_CURR_MOVE
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_SteelBeamAfterSelfDamage
	jumpifability BS_ATTACKER, ABILITY_SUGAR_COAT, BattleScript_SteelBeamAfterSelfDamage
	jumpifterucharmprotected BS_ATTACKER, BattleScript_SteelBeamAfterSelfDamage
	call BattleScript_SteelBeamSelfDamage
BattleScript_SteelBeamAfterSelfDamage::
	waitstate
	tryfaintmon BS_ATTACKER
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd
BattleScript_SteelBeamMiss::
	pause B_WAIT_TIME_SHORT
	effectivenesssound
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_MoveEnd
	jumpifability BS_ATTACKER, ABILITY_SUGAR_COAT, BattleScript_MoveEnd
	jumpifterucharmprotected BS_ATTACKER, BattleScript_MoveEnd
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED
	call BattleScript_SteelBeamSelfDamage
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	goto BattleScript_SteelBeamAfterSelfDamage
BattleScript_SteelBeamSelfDamage::
	dmg_1_2_attackerhp
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	return

BattleScript_EffectWorkUp::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, DEFAULT_STAT_STAGE, BattleScript_EffectWorkUpFromStatUp
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_WorkUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_WorkUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK | BIT_SPEED, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_WorkUpTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WorkUpTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_WorkUpTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_WorkUpTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WorkUpTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_WorkUpTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_WorkUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WorkUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_WorkUpEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectTrickorTreat::
	jumpiftargetally BattleScript_Treat
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	damagetopercentagetargethp
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifholdeffect BS_ATTACKER, HOLD_EFFECT_NONE, BattleScript_TrickKnockOff
	setmoveeffect MOVE_EFFECT_STEAL_ITEM
	seteffectprimary
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_RANDOM_STAT_DROP
	seteffectsecondary
	goto BattleScript_MoveEnd
BattleScript_TrickKnockOff::
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_KNOCK_OFF
	seteffectprimary
	setmoveeffect MOVE_EFFECT_RANDOM_STAT_DROP
	seteffectsecondary
	goto BattleScript_MoveEnd
BattleScript_Treat::
	attackcanceler
	attackstring
	ppreduce
    jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_MoveUsedHealBlockPrevents @ stops pollen puff
    jumpifstatus3 BS_TARGET, STATUS3_HEAL_BLOCK, BattleScript_MoveUsedHealBlockPrevents
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifsubstituteblocks BattleScript_ButItFailed
	tryhealpulse BS_TARGET, BattleScript_TreatTryStatRaise
	trycheesing BS_TARGET, BattleScript_TreatOnlyHeal
	attackanimation
	waitanimation
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	statbuffchange MOVE_EFFECT_CERTAIN, BattleScript_MoveEnd
	printstring STRINGID_DEFENDERSSTATROSE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_TreatTryStatRaise::
	trycheesing BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	statbuffchange MOVE_EFFECT_CERTAIN, BattleScript_MoveEnd
	printstring STRINGID_DEFENDERSSTATROSE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_TreatOnlyHeal::
	attackanimation
	waitanimation
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_HeartSteal::
	printstring STRINGID_SPECTRALTHIEFSTEAL
	waitmessage B_WAIT_TIME_LONG
	setbyte sB_ANIM_ARG2, 0
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	spectralthiefprintstats
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	goto BattleScript_EffectHeartStealFromDamage

BattleScript_EffectHeartSteal::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	tryspectralthiefsteal BattleScript_HeartSteal
BattleScript_EffectHeartStealFromDamage:
	critcalc
	damagecalc
	adjustdamage
	call BattleScript_Hit_RetFromAtkAnimation
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	setallure BattleScript_MoveEnd
	printfromtable gAllureStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectSpotlight::
	attackcanceler
	attackstring
	ppreduce
	.if B_UPDATED_MOVE_DATA >= GEN_6
	jumpifnotbattletype BATTLE_TYPE_DOUBLE, BattleScript_ButItFailed
	.endif
	setspotlight BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCENTERATTENTIONSPOTLIGHT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectDoubleTeam::
	setstatchanger STAT_EVASION, 1, FALSE
	attackcanceler
	attackstring
	ppreduce
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_DoubleTeamMultiHitBoost
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DoubleTeamAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_DoubleTeamPrintString
BattleScript_DoubleTeamAttackAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_DoubleTeamPrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DoubleTeamMultiHitBoost::
	jumpifmovehadnoeffect BattleScript_MoveEnd
	trydoubleteam BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_MULTISTRIKEPOWERUP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSpringBreeze::
    call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	setallure BattleScript_MoveEnd
	printfromtable gAllureStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectNightDaze::
	jumpifstatus BS_TARGET, STATUS1_PANIC, BattleScript_NightDazeTrueEffect
	jumpifstatus2 BS_TARGET, STATUS2_TORMENT, BattleScript_NightDazeTrueEffect
	goto BattleScript_EffectHit
BattleScript_NightDazeTrueEffect::
	setmoveeffect MOVE_EFFECT_ACC_MINUS_1
    call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	eeriespellppreduce BattleScript_MoveEnd
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFearFactor::
	setmoveeffect MOVE_EFFECT_PANIC
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING | HITMARKER_NO_PPDEDUCT, BattleScript_EffectFearFactorTarget
	attackcanceler
	attackstring
	ppreduce
	fearfactordamagecalculation
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MAGNITUDESTRENGTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectFearFactorTarget:
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

BattleScript_EffectRockWrecker::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_RECHARGE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_DEF_MINUS_2
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectHydroCannon::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_RECHARGE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setuserstatus3 STATUS3_AQUA_RING, BattleScript_MoveEnd
	printstring STRINGID_PKMNSURROUNDEDWITHVEILOFWATER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectAlluringVoice::
	checkstatboosts 1, BattleScript_EffectAlluringVoiceConfuse
	goto BattleScript_EffectSpringBreeze
BattleScript_EffectAlluringVoiceConfuse::
	setmoveeffect MOVE_EFFECT_CONFUSION
	goto BattleScript_EffectSpringBreeze

BattleScript_EffectJungleRage::
	checkfrenzycounter 3, BattleScript_JungleRageMaxFrenzy
	goto BattleScript_HeartCarveApplyFrenzy
BattleScript_JungleRageMaxFrenzy::
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_JungleRageMaxFrenzyHealBlock
	setdrainedhp
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_JungleRageMaxFrenzyLiquidOoze
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB
	goto BattleScript_JungleRageMaxFrenzyUpdateHp
BattleScript_JungleRageMaxFrenzyLiquidOoze::
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
BattleScript_JungleRageMaxFrenzyUpdateHp::
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_JungleRageMaxFrenzyTryFainting
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_JungleRageMaxFrenzyTryFainting::
	tryfaintmon BS_ATTACKER
BattleScript_JungleRageMaxFrenzyHealBlock::
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	removeallfrenzycounters BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_USERUSEDUPALLFRENZY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMindGap::
	attackcanceler
	jumpifnotfirstturn BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_MoveEnd
	disablechosenmove BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_PKMNMOVEWASDISABLED
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotDisabledAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectAmnesia::
	setstatchanger STAT_SPDEF, 2, FALSE
	attackcanceler
	attackstring
	ppreduce
	curestatuswithmove BS_ATTACKER, BattleScript_EffectStatUpAfterPPReduce
	attackanimation
	waitanimation
	updatestatusicon BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_StatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_StatUpDoAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_StatUpPrintString

BattleScript_EffectHoldHands::
	attackcanceler
	attackstring
	ppreduce
	jumpifnoally BS_ATTACKER, BattleScript_ButItFailed
	jumpifinfatuatedspecific BS_ATTACKER, BattleScript_EffectHoldHandsEffect
	goto BattleScript_ButItFailed
BattleScript_EffectHoldHandsEffect::
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_HoldHandsDoMoveAnim
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_HoldHandsDoMoveAnim
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_HoldHandsDoMoveAnim
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_HoldHandsDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_ACC, MAX_STAT_STAGE, BattleScript_HoldHandsTryHeal
BattleScript_HoldHandsDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF | BIT_SPATK | BIT_SPDEF | BIT_ACC, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HoldHandsTryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HoldHandsTryDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HoldHandsTryDef::
	setstatchanger BIT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HoldHandsTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HoldHandsTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HoldHandsTrySpAtk::
	setstatchanger BIT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HoldHandsTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HoldHandsTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HoldHandsTrySpDef::
	setstatchanger BIT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HoldHandsTryAccuracy
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HoldHandsTryAccuracy
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HoldHandsTryAccuracy::
	setstatchanger BIT_ACC, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HoldHandsEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HoldHandsEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HoldHandsEnd::
	tryhealquarterhealth BS_TARGET, BattleScript_MoveEnd
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_HoldHandsTryHeal::
	tryhealquarterhealth BS_TARGET, BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectAirCutter::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	removetailwind BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFly::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_SecondTurnFly
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_SecondTurnFly
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_FLY
	call BattleScriptFirstChargingTurn
	setsemiinvulnerablebit
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
BattleScript_SecondTurnFly::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	accuracycheck BattleScript_FlyMiss, ACC_CURR_MOVE
	clearsemiinvulnerablebit
	attackstring
	ppreduce
	jumpifmovehadnoeffect BattleScript_HitFromCritCalc
	removetailwind BS_ATTACKER, BattleScript_FlyTryRemoveFoeTailwind
	removetailwind BS_TARGET, BattleScript_FlyJustRemoveUserTailwind
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_TAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_FlyMiss::
	clearsemiinvulnerablebit
	goto BattleScript_PrintMoveMissed
BattleScript_FlyTryRemoveFoeTailwind::
	removetailwind BS_TARGET, BattleScript_HitFromCritCalc
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_FlyJustRemoveUserTailwind::
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_TAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRechargeBurn::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_RECHARGE_BURN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_HitFromAtkString

BattleScript_EffectRandomStatDropHit::
	setmoveeffect MOVE_EFFECT_RANDOM_STAT_DROP
	goto BattleScript_EffectHit

BattleScript_EffectBlazingSoul::
	setmoveeffect MOVE_EFFECT_BURN
    call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	tryblazingsoul BS_ATTACKER, BattleScript_MoveEnd
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPoisonTail::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	jumpifbyte CMP_EQUAL, gIsCriticalHit, TRUE, BattleScript_SuperPoisonTail
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_POISON
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd
BattleScript_SuperPoisonTail::
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_TOXIC
	seteffectprimary
	goto BattleScript_MoveEnd


BattleScript_EffectGearGrind::
	jumpifstatus4 BS_ATTACKER, STATUS4_SUPERCHARGED, BattleScript_GearGrindCheckGearUp
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_GearGrindLowerDef
	goto BattleScript_EffectHit
BattleScript_GearGrindCheckGearUp:
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_GearGrindLowerDefDestroyItem
	goto BattleScript_GearGrindDestroyItem
BattleScript_GearGrindLowerDef:
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1
	goto BattleScript_EffectHit
BattleScript_GearGrindDestroyItem:
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_KNOCK_OFF
	seteffectprimary
	goto BattleScript_MoveEnd
BattleScript_GearGrindLowerDefDestroyItem:
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1
	seteffectwithchance
	setmoveeffect MOVE_EFFECT_KNOCK_OFF
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectPsychoCut:
	jumpifterrainaffected BS_ATTACKER, STATUS_FIELD_PSYCHIC_TERRAIN, BattleScript_EffectSpecialDefenseDownHit
	goto BattleScript_EffectHit

BattleScript_EffectRockPolish:
	attackcanceler
	attackstring
	ppreduce
BattleScript_EffectRockPolishFromStatUp::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_RockPolishDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_RockPolishDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF | BIT_SPEED, 0
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_RockPolishTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_RockPolishTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RockPolishTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_RockPolishEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_RockPolishEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RockPolishEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSweetKiss:
	jumpifstatus2 BS_TARGET, STATUS2_INFATUATION, BattleScript_EffectSweetKissInfatuate
	checkallurecounter 2, BattleScript_EffectSweetKissInfatuate
	attackcanceler
	attackstring
	ppreduce
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_OwnTempoPrevents
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_OwnTempoPrevents
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_AlreadyConfused
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectSweetKissInfatuate::
	setstatchanger STAT_SPEED, 1, TRUE
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_EffectSweetKissJustSpeed
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_EffectSweetKissJustSpeed
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_EffectSweetKissJustSpeed
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_EffectSweetKissJustSpeed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_EffectSweetKissJustSpeed
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SweetKissStatDownEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SweetKissStatDownDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_SweetKissStatDownEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_SweetKissStatDownPrintString
BattleScript_SweetKissStatDownDoAnim::
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	waitmessage B_WAIT_TIME_LONG
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_SweetKissStatDownPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SweetKissStatDownEnd::
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectSweetKissJustSpeed::
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SweetKissStatDownEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SweetKissStatDownDoAnim2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_SweetKissStatDownEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_SweetKissStatDownPrintString
BattleScript_SweetKissStatDownDoAnim2::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRockSmash::
	setmoveeffect MOVE_EFFECT_ROCK_SMASH
	goto BattleScript_EffectHit

BattleScript_EffectCovet::
	jumpifstatus2 BS_TARGET, STATUS2_INFATUATION, BattleScript_EffectCovetInfatuate
	setmoveeffect MOVE_EFFECT_STEAL_ITEM
	goto BattleScript_EffectHit
BattleScript_EffectCovetInfatuate::
	setmoveeffect MOVE_EFFECT_STEAL_ITEM
    call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_ATK_MINUS_1
	seteffectsecondary
	moveendall
	end

BattleScript_EffectDualChop::
	setmoveeffect MOVE_EFFECT_DUAL_CHOP
	goto BattleScript_EffectHit

BattleScript_EffectForcePalm::
	jumpifstatus BS_TARGET, STATUS1_PARALYSIS, BattleScript_RandomStatLowerHit2
	goto BattleScript_EffectParalyzeHit
BattleScript_RandomStatLowerHit2::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_RANDOM_STAT_DROP_2
	seteffectprimary
	moveendall
	end

BattleScript_EffectOrderUp::
	setmoveeffect MOVE_EFFECT_RANDOM_STAT_RAISE | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectMountainGale::
	jumpifweatheraffected BS_ATTACKER, B_WEATHER_HAIL, BattleScript_EffectFlinchHit
	goto BattleScript_EffectHit

BattleScript_EffectHealOrder::
	attackcanceler
	attackstring
	ppreduce
	tryhealthirdhealth BS_ATTACKER, BattleScript_AlreadyAtFullHp
	storehealorder BS_ATTACKER, BattleScript_HealOrderJustHeal
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_ORDEREDANEXTRAHEAL
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_HealOrderJustHeal::
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectDefendOrder::
	setstatchanger STAT_DEF, 1, FALSE
	attackcanceler
	attackstring
	ppreduce
	trydefendorder BS_TARGET, BattleScript_ButItFailed
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_StatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_StatUpAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_StatUpPrintString

BattleScript_EffectAttackOrder::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_ATTACK_ORDER
	seteffectwithchance
	setmoveeffect MOVE_EFFECT_WRAP
	seteffectsecondary
	moveendall
	end

BattleScript_EffectOctazooka::
	setmoveeffect MOVE_EFFECT_OCTAZOOKA
	goto BattleScript_EffectHit

BattleScript_EffectSyrupBomb::
	setmoveeffect MOVE_EFFECT_SYRUP_BOMB
	goto BattleScript_EffectHit

BattleScript_SyrupBombActivates::
	printstring STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SyrupBombActivatesBlooming::
	printstring STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SyrupBombEndTurn::
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_EVASION, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_SyrupBombTryLowerEvasion
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SyrupBombTryLowerEvasion:
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_SyrupBombTurnDmgEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SyrupBombTurnDmgEnd:
	end2

BattleScript_EffectTrueLovesKiss::
	attackcanceler
	attackstring
	jumpifnoally BS_ATTACKER, BattleScript_ItsJoever
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_TrueLovesKissNoAllure
	jumpifsafeguard BattleScript_TrueLovesKissNoAllure
	setallure BattleScript_TrueLovesKissNoAllure
	attackanimation
	waitanimation
	printstring STRINGID_SLOPPYTOPPY
	waitmessage B_WAIT_TIME_LONG
	printfromtable gAllureStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateAttacker
	goto BattleScript_MoveEnd
BattleScript_ItsJoever:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NOSEX
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_TrueLovesKissNoAllure::
	attackanimation
	waitanimation
	printstring STRINGID_SLOPPYTOPPY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHaywire::
	shellsidearmcheck
	goto BattleScript_EffectHit

BattleScript_EffectAxelHeel::
	@ DecideTurn
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_AXEL_HEEL
	attackcanceler
	printstring STRINGID_EMPTYSTRING3
	ppreduce
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_CHARGING
	setmoveeffect MOVE_EFFECT_CHARGING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	copybyte cMULTISTRING_CHOOSER, sTWOTURN_STRINGID
	printfromtable gFirstTurnOfTwoStringIds
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_ATK_SPEED_PLUS | MOVE_EFFECT_AFFECTS_USER
	seteffectsecondary
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_TwoTurnMovesSecondTurn

BattleScript_EffectLeafTornado::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_LeafTornadoRemoveScreenHazards
	goto BattleScript_EffectAccuracyDownHit
BattleScript_LeafTornadoRemoveScreenHazards:
	setmoveeffect MOVE_EFFECT_ACC_MINUS_1
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	removelightscreenreflect
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	rapidspinfree
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendall
	end

BattleScript_EffectCheeseSteal::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_EffectCheeseStealSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_EffectCheeseStealSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_CHEESE_STEAL
	call BattleScriptFirstChargingTurn
	setsemiinvulnerablebit
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
BattleScript_EffectCheeseStealSecondTurn::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	clearsemiinvulnerablebit
	trygaincheese BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_FOUNDARANDOMCHEESE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectDragonClaw:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	ficklebeamdamagecalculation
	goto BattleScript_HitFromCritCalc
BattleScript_DragonClawBoosted::
	pause B_WAIT_TIME_SHORTEST
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	printstring STRINGID_DRAGONCLAWBOOSTED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSubmission::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryquash BattleScript_HitFromCritCalc
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	printstring STRINGID_QUASHSUCCESS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectStormChase::
	jumpifweatheraffected BS_ATTACKER, B_WEATHER_RAIN, BattleScript_EffectParalyzeHit
	goto BattleScript_EffectHit

BattleScript_EffectStormFury::
	jumpifweatheraffected BS_ATTACKER, B_WEATHER_RAIN, BattleScript_StormFurySpread
	goto BattleScript_EffectRampage
BattleScript_StormFurySpread::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_StormFurySpread2
	ppreduce
BattleScript_StormFurySpread2:
	confuseifrepeatingattackends
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	setmoveeffect MOVE_EFFECT_WILD_CHARGE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectWildCharge::
	setmoveeffect MOVE_EFFECT_WILD_CHARGE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_MoveEffectWildCharge::
	tryfaintmon BS_TARGET
	copybyte sBATTLER, sSAVED_BATTLER
	printstring STRINGID_SPARKINGELECTRICITYHIT
	waitmessage B_WAIT_TIME_LONG
	savetarget
	copybyte gBattlerTarget, sSAVED_BATTLER
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	tryfaintmon BS_TARGET
	restoretarget
	goto BattleScript_MoveEnd

BattleScript_EffectSpindaSwing::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_CONFUSION | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_RANDOM_STAT_DROP
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectHighRollHit::
	attackcanceler
	attackstring
	ppreduce
	highrollhitdamagecalculation
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_HIGHROLLHITROLL
	waitmessage B_WAIT_TIME_LONG
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

BattleScript_DefenderUsedAnExtraMove::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_ABILITYLETITUSEMOVETARGET
	waitmessage B_WAIT_TIME_LONG
	copybyte gEffectBattler, gBattlerTarget
	swapattackerwithtarget
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	critcalc
	damagecalc
	adjustdamage
	playmoveanimation BS_ATTACKER, MOVE_NONE
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	swapattackerwithtarget
	copybyte gBattlerAttacker, sSAVED_BATTLER
	end2

BattleScript_DefenderUsedCinderWaltz::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_ABILITYLETITUSEMOVETARGET
	waitmessage B_WAIT_TIME_LONG
	copybyte gEffectBattler, gBattlerTarget
	swapattackerwithtarget
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	critcalc
	damagecalc
	adjustdamage
	playmoveanimation BS_ATTACKER, MOVE_NONE
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_FLAME_BURST | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	swapattackerwithtarget
	copybyte gBattlerAttacker, sSAVED_BATTLER
	end2

BattleScript_AttackerUsedAnExtraMove::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ABILITYLETITUSEMOVE
	waitmessage B_WAIT_TIME_SHORT
BattleScript_EffectExtraHit::
BattleScript_ExtraHitFromAtkCanceler::
	attackcanceler
BattleScript_ExtraHitFromAccCheck::
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
BattleScript_ExtraHitFromAtkString::
BattleScript_ExtraHitFromCritCalc::
	critcalc
	damagecalc
	adjustdamage
BattleScript_ExtraHitFromAtkAnimation::
	playmoveanimation BS_ATTACKER, MOVE_NONE
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
BattleScript_ExtraExtraMoveEnd::
	moveendall
	end

BattleScript_AttackerUsedFirebrand::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ABILITYLETITUSEMOVE
	waitmessage B_WAIT_TIME_SHORT
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	critcalc
	damagecalc
	adjustdamage
	playmoveanimation BS_ATTACKER, MOVE_NONE
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	jumpifsubstituteblocks BattleScript_FirebrandContinue
	setmoveeffect MOVE_EFFECT_FIREBRAND | MOVE_EFFECT_AFFECTS_USER
	seteffectwithchance
BattleScript_FirebrandContinue::
	setmoveeffect MOVE_EFFECT_FLAME_BURST
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpiffainted BS_TARGET, TRUE, BattleScript_ExtraExtraMoveEnd
	jumpifmovehadnoeffect BattleScript_ExtraExtraMoveEnd
	tryhealquarterhealth BS_ATTACKER, BattleScript_ExtraExtraMoveEnd
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_HEALINGWISHHEALED
	waitmessage B_WAIT_TIME_LONG
	moveendall
	end

BattleScript_EffectOvertake::
	jumpifnotbattletype BATTLE_TYPE_DOUBLE, BattleScript_EffectHit
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	setovertaketarget
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectHunkerDown::
	attackcanceler
	setmoveeffect MOVE_EFFECT_RECHARGE_STATS | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_HunkerDownDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_HunkerDownDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_HunkerDownTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HunkerDownTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HunkerDownTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_HunkerDownEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HunkerDownEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HunkerDownEnd::
	seteffectwithchance
	goto BattleScript_MoveEnd

BattleScript_EffectMoonBeam:
	jumpifholdeffect BS_ATTACKER, HOLD_EFFECT_MOON_MIRROR, BattleScript_TrueMoonBeam
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	curestatuswithmove BS_ATTACKER, BattleScript_MoveEnd
	updatestatusicon BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_TrueMoonBeam::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	tryspectralthiefsteal BattleScript_MoonBeamSteal
BattleScript_EffectMoonBeamFromDamage:
	critcalc
	damagecalc
	adjustdamage
	call BattleScript_Hit_RetFromAtkAnimation
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	curestatuswithmove BS_ATTACKER, BattleScript_MoveEnd
	updatestatusicon BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_MoonBeamSteal::
	printstring STRINGID_SPECTRALTHIEFSTEAL
	waitmessage B_WAIT_TIME_LONG
	setbyte sB_ANIM_ARG2, 0
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	spectralthiefprintstats
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	goto BattleScript_EffectMoonBeamFromDamage

BattleScript_EffectBerryBadJoke::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_BerryBadJokeAddFrostbite
BattleScript_BerryBadJokeContinue:
	jumpifnotberry BS_TARGET, BattleScript_BerryBadJokeNoBerry
	call BattleScript_EffectHit_Ret
	setbyte sBERRY_OVERRIDE, 1
	orword gHitMarker, HITMARKER_NO_ANIMATIONS
	consumeberry BS_TARGET, TRUE
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, 0
	removeitem BS_TARGET
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendall
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut 
	jumpifability BS_TARGET, ABILITY_STALWART, BattleScript_AbilityPreventsPhasingOut 
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	tryhitswitchtarget BattleScript_MoveEnd
	forcerandomswitch BattleScript_HitSwitchTargetForceRandomSwitchFailed
	goto BattleScript_MoveEnd
BattleScript_BerryBadJokeNoBerry:
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendall
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut 
	jumpifability BS_TARGET, ABILITY_STALWART, BattleScript_AbilityPreventsPhasingOut 
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	tryhitswitchtarget BattleScript_MoveEnd
	forcerandomswitch BattleScript_HitSwitchTargetForceRandomSwitchFailed
	goto BattleScript_MoveEnd
BattleScript_BerryBadJokeAddFrostbite:
	setmoveeffect MOVE_EFFECT_FROSTBITE
	goto BattleScript_BerryBadJokeContinue

BattleScript_EffectShieldsUp::
	attackcanceler
	attackstring
	ppreduce
	tryhealquarterhealth BS_ATTACKER, BattleScript_TryStatusAndStatRestore
	curestatuswithmove BS_ATTACKER, BattleScript_HealSuccessStatusCureFailed
	tryresetnegativestatstages BS_ATTACKER
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
    waitmessage B_WAIT_TIME_LONG
	tryshieldsup
	goto BattleScript_MoveEnd
BattleScript_TryStatusAndStatRestore:
	curestatuswithmove BS_ATTACKER, BattleScript_JustRestoreNegativeStats
	tryresetnegativestatstages BS_ATTACKER
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
    waitmessage B_WAIT_TIME_LONG
	tryshieldsup
	goto BattleScript_MoveEnd
BattleScript_JustRestoreNegativeStats:
	tryresetnegativestatstages BS_TARGET
	attackanimation
	waitanimation
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	tryshieldsup
	goto BattleScript_MoveEnd
BattleScript_HealSuccessStatusCureFailed:
	tryresetnegativestatstages BS_ATTACKER
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
    waitmessage B_WAIT_TIME_LONG
	tryshieldsup
	goto BattleScript_MoveEnd

BattleScript_EffectMagicPowder::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_MULTITYPE, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_RKS_SYSTEM, BattleScript_ButItFailed
	jumpifsubstituteblocks BattleScript_ButItFailed
	trysoak BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_VITAL_SPIRIT, BattleScript_JustDoMagicPowder
	jumpifability BS_TARGET, ABILITY_INSOMNIA, BattleScript_JustDoMagicPowder
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_JustDoMagicPowder
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_JustDoMagicPowder
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_JustDoMagicPowder
	jumpifflowerveil BattleScript_JustDoMagicPowder
	jumpifleafguardprotected BS_TARGET, BattleScript_JustDoMagicPowder
	jumpifeeriemaskprotected BS_TARGET, BattleScript_JustDoMagicPowder
	jumpifshieldsdown BS_TARGET, BattleScript_JustDoMagicPowder
	jumpifsubstituteblocks BattleScript_JustDoMagicPowder
	jumpifgearmagnet BS_TARGET, BattleScript_JustDoMagicPowder
	jumpifsafeguard BattleScript_JustDoMagicPowder
	jumpifuproarwakes BattleScript_JustDoMagicPowder
	setyawn BattleScript_JustDoMagicPowder
	attackanimation
	waitanimation
	printstring STRINGID_TARGETCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNWASMADEDROWSY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_JustDoMagicPowder::
	attackanimation
	waitanimation
	printstring STRINGID_TARGETCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGravApple::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_GravAppleFlinch
	goto BattleScript_GravAppleNormal
BattleScript_GravAppleFlinch::
	setmoveeffect MOVE_EFFECT_GRAV_APPLE
BattleScript_GravAppleNormal::
    call BattleScript_EffectHit_Ret
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1
	seteffectsecondary
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendall
	end

BattleScript_EffectPowerShift:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	powershift BS_ATTACKER
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSPATKANDSPDEF
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectAcidArmor:
	setstatchanger STAT_DEF, 2, FALSE
	attackcanceler
	attackstring
	ppreduce
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AcidArmorStatus
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AcidArmorAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_AcidArmorPrintString
BattleScript_AcidArmorAttackAnim::
	attackanimation
	waitanimation
BattleScript_AcidArmorDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_AcidArmorPrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AcidArmorStatus::
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setacidarmor BS_ATTACKER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectBurningEnvy:
	checkstatboosts 3, BattleScript_BurningEnvyTormentandBurn
	goto BattleScript_EffectHit
BattleScript_BurningEnvyTormentandBurn:
	setmoveeffect MOVE_EFFECT_BURN
    call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	settorment BattleScript_MoveEnd
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectCannonade:
	jumpifhpthreshold BS_ATTACKER, BattleScript_EffectCannonadeMalfunctioned
	goto BattleScript_EffectSpecialDefenseDownHit
BattleScript_EffectCannonadeMalfunctioned:
	attackcanceler
	attackstring
	ppreduce
	printstring STRINGID_CANNONADEMALFUNCTIONED
	tryexplosion
	setatkhptozero
	waitstate
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

BattleScript_EffectReservoir:
	attackcanceler
	attackstring
	ppreduce
	setpump BS_ATTACKER
	jumpiffullhp BS_ATTACKER, BattleScript_ReservoirJustPump
	attackanimation
	waitanimation
	copybyte gBattlerTarget, gBattlerAttacker
	setbyte gBattleCommunication, 0
	copybyte gBattlerAttacker, gBattlerTarget
	tryhealhalfhealth BattleScript_Reservoir_TryCureStatus, BS_ATTACKER
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_Reservoir_TryCureStatus:
	jumpifstatus BS_ATTACKER, STATUS1_ANY_NEGATIVE, BattleScript_ReservoirCureStatus
	printstring STRINGID_PKMNPUMPINGPOWER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_ReservoirCureStatus:
	curestatus BS_ATTACKER
	updatestatusicon BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNPUMPINGPOWER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_ReservoirJustPump:
	attackanimation
	waitanimation
	printstring STRINGID_PKMNPUMPINGPOWER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectKinesis:
	jumpifterrainaffected BS_ATTACKER, STATUS_FIELD_PSYCHIC_TERRAIN, BattleScript_KinesisWithExhaustion
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ACC, MIN_STAT_STAGE, BattleScript_KinesisDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_EVASION, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_KinesisDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ACC | BIT_EVASION, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ACC, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_KinesisTryLowerEvasion
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_KinesisTryLowerEvasion
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_KinesisTryLowerEvasion::
	playstatchangeanimation BS_TARGET, BIT_EVASION, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_KinesisEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_KinesisEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_KinesisEnd::
	goto BattleScript_MoveEnd
BattleScript_KinesisWithExhaustion::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ACC, MIN_STAT_STAGE, BattleScript_KinesisWithExhaustionDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_EVASION, MIN_STAT_STAGE, BattleScript_KinesisJustExhaustion
BattleScript_KinesisWithExhaustionDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ACC | BIT_EVASION, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ACC, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_KinesisWithExhaustionTryLowerEvasion
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_KinesisWithExhaustionTryLowerEvasion
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_KinesisWithExhaustionTryLowerEvasion::
	playstatchangeanimation BS_TARGET, BIT_EVASION, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_KinesisWithExhaustionEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_KinesisWithExhaustionEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_KinesisWithExhaustionEnd::
	applyexhaustioncounter BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_TARGETISEXHAUSTED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_KinesisJustExhaustion::
	applyexhaustioncounter BS_TARGET, BattleScript_ButItFailed
	printstring STRINGID_TARGETISEXHAUSTED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMistBall::
	jumpifsideaffecting BS_ATTACKER, SIDE_STATUS_MIST, BattleScript_EffectSpecialAttackDownHit
	setmoveeffect MOVE_EFFECT_SP_ATK_MINUS_1
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	seteffectwithchance
	setmist
	printfromtable gMistUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGravitonArm:
	jumpifword CMP_COMMON_BITS, gFieldStatuses, STATUS_FIELD_GRAVITY, BattleScript_EffectHit
	attackcanceler
	attackstring
	ppreduce
	setgravity BattleScript_ButItFailed
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	printstring STRINGID_GRAVITYINTENSIFIED
	waitmessage B_WAIT_TIME_LONG
	selectfirstvalidtarget
	goto BattleScript_GravityLoop

BattleScript_EffectPoisonPowder::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_PoisonPowderExhaustion
	goto BattleScript_EffectPoison
BattleScript_PoisonPowderExhaustion::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_IMMUNITY, BattleScript_PoisonPowderTryExhaustion
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_PoisonPowderTryExhaustion
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_PoisonPowderTryExhaustion
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_PoisonPowderTryExhaustion
	jumpifability BS_TARGET_SIDE, ABILITY_PASTEL_VEIL, BattleScript_PoisonPowderTryExhaustion
	jumpifflowerveil BattleScript_PoisonPowderTryExhaustion
	jumpifleafguardprotected BS_TARGET, BattleScript_PoisonPowderTryExhaustion
	jumpifeeriemaskprotected BS_TARGET, BattleScript_PoisonPowderTryExhaustion
	jumpifshieldsdown BS_TARGET, BattleScript_PoisonPowderTryExhaustion
	jumpifsubstituteblocks BattleScript_PoisonPowderTryExhaustion
	jumpifgearmagnet BS_TARGET, BattleScript_PoisonPowderTryExhaustion
	jumpifstatus BS_TARGET, STATUS1_POISON, BattleScript_PoisonPowderTryExhaustion
	jumpifstatus BS_TARGET, STATUS1_TOXIC_POISON, BattleScript_PoisonPowderTryExhaustion
	trypoisontype BS_ATTACKER, BS_TARGET, BattleScript_PoisonPowderTryExhaustion
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_PoisonPowderTryExhaustion
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_PoisonPowderTryExhaustion
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_POISON
	seteffectprimary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	applyexhaustioncounter BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_TARGETISEXHAUSTED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_PoisonPowderTryExhaustion::
	applyexhaustioncounter BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TARGETISEXHAUSTED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSmog::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	argumentstatuseffect
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectSnowfade::
	setmoveeffect MOVE_EFFECT_SNOWFADE
	goto BattleScript_EffectHitEscape

BattleScript_EffectPhantasm:
	attackcanceler
	attackstring
	ppreduce
	cuthp BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	applyphantom BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_USERGAINSPHANTOM
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectWhirlwind::
	attackcanceler
	attackstring
	ppreduce
	jumpifroarfails BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut
	jumpifability BS_TARGET, ABILITY_STALWART, BattleScript_AbilityPreventsPhasingOut
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_ButItFailed
	forcerandomswitch BattleScript_ButItFailed

BattleScript_EffectUpperHand:
	suckerpunchcheck BattleScript_EffectHit
	goto BattleScript_EffectFlinchHit

BattleScript_EffectFleurCannon:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_FleurCannonBlooming
	goto BattleScript_EffectOverheat
BattleScript_FleurCannonBlooming:
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	curestatuswithmove BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_PKMNSISNOLONGERBLOOMING
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	tryresetnegativestatstages BS_ATTACKER
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCutieCry:
	jumpifstatus2 BS_TARGET, STATUS2_INFATUATION, BattleScript_CutieCryStatPart
	goto BattleScript_EffectSpringBreeze
BattleScript_CutieCryStatPart:
	setmoveeffect MOVE_EFFECT_ATK_SPATK_DOWN_2
	goto BattleScript_EffectSpringBreeze

BattleScript_EffectBlock::
	setstatchanger STAT_SPEED, 2, TRUE
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_StatDownFromPPReduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_StatDownFromPPReduce
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_BlockSpeedDropEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_BlockSpeedDropDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_BlockSpeedDropEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_BlockSpeedDropPrintString
BattleScript_BlockSpeedDropDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_BlockSpeedDropPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_BlockSpeedDropEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSurpriseEgg::
	attackcanceler
	attackstring
	pause B_WAIT_TIME_SHORT
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	metronome

BattleScript_EffectOdorSleuth:
	jumpifhpthreshold BS_TARGET, BattleScript_OdorSleuthWithStatRaise
BattleScript_OdorSleuthWithStatRaise:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstatus2 BS_TARGET, STATUS2_FORESIGHT, BattleScript_ButItFailed
	setforesight
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_OdorSleuthStatUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_OdorSleuthJustSetForesight
BattleScript_OdorSleuthJustSetForesight:
	attackanimation
	waitanimation
	printstring STRINGID_PKMNIDENTIFIED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_OdorSleuthStatUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPEED, 0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_OdorSleuthStatUpTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_OdorSleuthStatUpTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_OdorSleuthStatUpTrySpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_OdorSleuthStatUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_OdorSleuthStatUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNIDENTIFIED
	waitmessage B_WAIT_TIME_LONG
BattleScript_OdorSleuthStatUpEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectMindReader::
	seizechancecheck BattleScript_MindReaderNoFlinch
	setmoveeffect MOVE_EFFECT_FLINCH
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	setalwayshitflag
	attackanimation
	waitanimation
	printstring STRINGID_PKMNTOOKAIM
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	goto BattleScript_MoveEnd
BattleScript_MindReaderNoFlinch::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	setalwayshitflag
	attackanimation
	waitanimation
	printstring STRINGID_PKMNTOOKAIM
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPurification:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_MULTITYPE, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_RKS_SYSTEM, BattleScript_ButItFailed
	jumpifsubstituteblocks BattleScript_ButItFailed
	trysoak BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TARGETCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	tryresetstatstages BS_TARGET
	printstring STRINGID_TARGETSTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	setpurified BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_TARGETWASPURIFIEDANDCANTCHANGESTATS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRechargeReduce::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_RECHARGE_REDUCE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_HitFromAtkString

BattleScript_EffectHyperDrill::
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	removelightscreenreflect
	critcalc
	damagecalc
	adjustdamage
	jumpifbyte CMP_EQUAL, sB_ANIM_TURN, 0, BattleScript_HyperDrillAnim
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE
BattleScript_HyperDrillAnim::
	attackanimation
	waitanimation
	jumpifbyte CMP_LESS_THAN, sB_ANIM_TURN, 2, BattleScript_HyperDrillDoHit
	printstring STRINGID_THEWALLSHATTERED
	waitmessage B_WAIT_TIME_LONG
BattleScript_HyperDrillDoHit::
	typecalc
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectConstrict::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_EffectConstrict2
	ppreduce
BattleScript_EffectConstrict2:
	confuseifrepeatingattackends
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_CONSTRICT
	seteffectsecondary
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectStunSpore:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_StunSporeFlinch
	goto BattleScript_EffectParalyze
BattleScript_StunSporeFlinch:
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_LIMBER, BattleScript_LimberProtected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	typecalc
	jumpifmovehadnoeffect BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_PARALYSIS, BattleScript_AlreadyParalyzed
	jumpifabsorbaffected BS_TARGET, BattleScript_VoltAbsorbHeal
	tryparalyzetype BS_ATTACKER, BS_TARGET, BattleScript_NotAffected
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	setmoveeffect MOVE_EFFECT_FLINCH
	seteffectsecondary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_PlunderSteal::
	printstring STRINGID_SPECTRALTHIEFSTEAL
	waitmessage B_WAIT_TIME_LONG
	setbyte sB_ANIM_ARG2, 0
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	spectralthiefprintstats
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	goto BattleScript_EffectPlunderFromDamage

BattleScript_EffectPlunder::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	tryspectralthiefsteal BattleScript_PlunderSteal
BattleScript_EffectPlunderFromDamage:
	critcalc
	damagecalc
	adjustdamage
	call BattleScript_Hit_RetFromAtkAnimation
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_PAYDAY
	seteffectprimary
	jumpifbattleend BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_STEAL_ITEM
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectSleepPowder:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectSleepPowderDefenseDrop
	goto BattleScript_EffectSleep
BattleScript_EffectSleepPowderDefenseDrop:
	setstatchanger STAT_DEF, 2, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_SLEEP_ANY, BattleScript_StatDownFromAttackString
	jumpiftype BS_TARGET, TYPE_RELIC, BattleScript_StatDownFromAttackString
	jumpifuproarwakes BattleScript_StatDownFromAttackString
	jumpifability BS_TARGET, ABILITY_INSOMNIA, BattleScript_StatDownFromAttackString
	jumpifability BS_TARGET, ABILITY_VITAL_SPIRIT, BattleScript_StatDownFromAttackString
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_StatDownFromAttackString
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_StatDownFromAttackString
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_StatDownFromAttackString
	jumpifflowerveil BattleScript_StatDownFromAttackString
	jumpifability BS_TARGET_SIDE, ABILITY_SWEET_VEIL, BattleScript_StatDownFromAttackString
	jumpifleafguardprotected BS_TARGET, BattleScript_StatDownFromAttackString
	jumpifeeriemaskprotected BS_TARGET, BattleScript_StatDownFromAttackString
	jumpifshieldsdown BS_TARGET, BattleScript_StatDownFromAttackString
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_StatDownFromAttackString
	jumpifterrainaffected BS_TARGET, STATUS_FIELD_ELECTRIC_TERRAIN, BattleScript_StatDownFromAttackString
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_StatDownFromAttackString
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SleepPowderJustSleep
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SleepPowderDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_SleepPowderJustSleep
	pause B_WAIT_TIME_SHORT
	goto BattleScript_SleepPowderPrintString
BattleScript_SleepPowderDoAnim:
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_SleepPowderPrintString:
	setmoveeffect MOVE_EFFECT_SLEEP
	seteffectprimary
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_SleepPowderJustSleep:
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_SLEEP
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectCottonSpore:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectCottonSporeParalysis
	goto BattleScript_EffectSpeedDown2
BattleScript_EffectCottonSporeParalysis:
	setstatchanger STAT_SPEED, 2, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_CottonSporeWorks
	jumpifstatus BS_TARGET, STATUS1_PARALYSIS, BattleScript_FailedFromAtkString
BattleScript_CottonSporeWorks:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_CottonSporeTryPara
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_CottonSporeDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_CottonSporeTryPara
	pause B_WAIT_TIME_SHORT
	goto BattleScript_CottonSporePrintString
BattleScript_CottonSporeDoAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_CottonSporePrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CottonSporeTryPara::
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectFrostNova:
	checkspeeddrops 1, BattleScript_EffectFrostNova2
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
	goto BattleScript_EffectHit
BattleScript_EffectFrostNova2:
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
	seteffectprimary
	setmoveeffect MOVE_EFFECT_FROSTBITE
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectGreenGuise:
	setstatchanger STAT_EVASION, 1, FALSE
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_GreenGuiseBloomingFailTryFocusEnergy
	jumpiftype BS_ATTACKER, TYPE_FIRE, BattleScript_GreenGuiseBloomingFailTryFocusEnergy
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_GreenGuiseBloomingFailTryFocusEnergy
	jumpifstatus BS_ATTACKER, STATUS1_ANY, BattleScript_GreenGuiseBloomingFailTryFocusEnergy
	jumpifstatus2 BS_ATTACKER, STATUS2_FOCUS_ENERGY_ANY, BattleScript_GreenGuiseBloomingSucceedFocusEnergyFail
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
BattleScript_GreenGuiseFocusEnergy::
	setfocusenergy BS_ATTACKER
	printfromtable gFocusEnergyUsedStringIds
BattleScript_GreenGuiseStatBoost::
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_GreenGuiseStatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GreenGuiseStatUpAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_GreenGuiseStatUpPrintString
BattleScript_GreenGuiseStatUpAttackAnim::
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_GreenGuiseStatUpPrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GreenGuiseStatUpEnd::
	goto BattleScript_MoveEnd
BattleScript_GreenGuiseBloomingFailTryFocusEnergy::
	jumpifstatus2 BS_ATTACKER, STATUS2_FOCUS_ENERGY_ANY, BattleScript_GreenGuiseBloomingFailFocusEnergyFail
	attackanimation
	waitanimation
	goto BattleScript_GreenGuiseFocusEnergy
BattleScript_GreenGuiseBloomingSucceedFocusEnergyFail::
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	goto BattleScript_GreenGuiseStatBoost
BattleScript_GreenGuiseBloomingFailFocusEnergyFail::
	attackanimation
	waitanimation
	goto BattleScript_GreenGuiseStatBoost

BattleScript_EffectAromatherapy:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_AromatherapyAndSafeguard
	attackcanceler
	attackstring
	ppreduce
	healpartystatus
	waitstate
	attackanimation
	waitanimation
	printfromtable gPartyStatusHealStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER_WITH_PARTNER
	waitstate
	goto BattleScript_MoveEnd
BattleScript_AromatherapyAndSafeguard:
	attackcanceler
	attackstring
	ppreduce
	healpartystatus
	waitstate
	setsafeguard
	attackanimation
	waitanimation
	printfromtable gPartyStatusHealStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER_WITH_PARTNER
	waitstate
	printstring STRINGID_PKMNCOVEREDBYVEIL
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFrenzyPlant:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectHit
	goto BattleScript_EffectRecharge

BattleScript_EffectPetalDance::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_EffectPetalDance2
	ppreduce
BattleScript_EffectPetalDance2:
	confuseifrepeatingattackends
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_AFFECTS_USER
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectEnergyBall:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EnergyBallMaxSpDefDropChance
	goto BattleScript_EffectSpecialDefenseDownHit
BattleScript_EnergyBallMaxSpDefDropChance:
	setmoveeffect MOVE_EFFECT_SP_DEF_MINUS_1 | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectAppleAcid:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_AppleAcidBothDefenses
	goto BattleScript_EffectSpecialDefenseDownHit
BattleScript_AppleAcidBothDefenses:
	setmoveeffect MOVE_EFFECT_DEF_SPDEF_DOWN
	goto BattleScript_EffectHit

BattleScript_EffectWoodHammer::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_WoodHammerHitSwitchTarget
	goto BattleScript_EffectHit
BattleScript_WoodHammerHitSwitchTarget:
	curestatuswithmove BS_ATTACKER, BattleScript_WoodHammerBloomCureFailed
BattleScript_WoodHammerBloomCureFailed:
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	moveendall
	printstring STRINGID_PKMNSISNOLONGERBLOOMING
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut 
	jumpifability BS_TARGET, ABILITY_STALWART, BattleScript_AbilityPreventsPhasingOut 
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	tryhitswitchtarget BattleScript_MoveEnd
	forcerandomswitch BattleScript_HitSwitchTargetForceRandomSwitchFailed
	goto BattleScript_MoveEnd

BattleScript_EffectDrumBeating::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectDrumBeatingBlooming
	goto BattleScript_EffectHit
BattleScript_EffectDrumBeatingBlooming::
	call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_DrumBeatingTryFaint
	seteffectwithchance
	setremoveterrain BattleScript_DrumBeatingTryFaint
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DrumBeatingTryFaint:
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectSnapblossom::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_SnapBlossomPlantSeeds
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_SnapBlossomGiveBlooming
	goto BattleScript_EffectAbsorb
BattleScript_SnapBlossomPlantSeeds::
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_SnapblossomHealBlock
	setdrainedhp
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_SnapblossomLiquidOoze
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB
	goto BattleScript_SnapblossomUpdateHp
BattleScript_SnapblossomLiquidOoze::
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
BattleScript_SnapblossomUpdateHp::
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_SnapblossomTryFainting
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SnapblossomTryFainting::
	tryfaintmon BS_ATTACKER
BattleScript_SnapblossomHealBlock::
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifsubstituteblocks BattleScript_MoveEnd
	jumpifstatus3 BS_TARGET, STATUS3_LEECHSEED, BattleScript_MoveEnd
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_MoveEnd
	setseeded
	printfromtable gLeechSeedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_SnapBlossomGiveBlooming::
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectAbsorb

BattleScript_EffectTropKick::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_TropKickCheckInfatuation
	jumpifstatus2 BS_TARGET, STATUS2_INFATUATION, BattleScript_TropKickAtkDefDown
	goto BattleScript_EffectAttackDownHit
BattleScript_TropKickCheckInfatuation::
	jumpifstatus2 BS_TARGET, STATUS2_INFATUATION, BattleScript_TropKickAtkDefDownUserAtkUp
BattleScript_TropKickAtkDefDown::
	setmoveeffect MOVE_EFFECT_ATK_DEF_DOWN
	goto BattleScript_EffectHit
BattleScript_TropKickAtkDefDownUserAtkUp::
	setmoveeffect MOVE_EFFECT_SUPER_TROP_KICK
	goto BattleScript_EffectHit

BattleScript_EffectNeedleArm::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectNeedleArmBlooming
	goto BattleScript_EffectHit
BattleScript_EffectNeedleArmBlooming::
	argumenttomoveeffect
	goto BattleScript_EffectHit

BattleScript_EffectTrailBlaze::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectSpdAccUpHit
	goto BattleScript_EffectSpeedUpHit
BattleScript_EffectSpdAccUpHit::
	setmoveeffect MOVE_EFFECT_SPD_ACC_UP | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectVineWhip::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectTrap
	goto BattleScript_EffectHit

BattleScript_EffectBanshriek::
	setmoveeffect MOVE_EFFECT_BANSHRIEK
	goto BattleScript_EffectHit

BattleScript_EffectFeatherDance:
	jumpifnodamage BattleScript_EffectAttackDown2
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_FeatherDanceWasHitDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_ACC, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_FeatherDanceWasHitDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_NEGATIVE | STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 2, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_FeatherDanceWasHitTryLowerDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_FeatherDanceWasHitTryLowerDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FeatherDanceWasHitTryLowerDef::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ACC, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_FeatherDanceWasHitEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_FeatherDanceWasHitEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FeatherDanceWasHitEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectAirCannon:
	jumpifsideaffecting BS_ATTACKER, SIDE_STATUS_TAILWIND, BattleScript_AirCannonOnFirstTurn
BattleScript_AirCannonDecideTurn:
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_AirCannonSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_AirCannonSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_AIR_CANNON
	call BattleScriptFirstChargingTurn
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_AirCannonSecondTurn
BattleScript_AirCannonOnFirstTurn:
	orword gHitMarker, HITMARKER_CHARGING
	setmoveeffect MOVE_EFFECT_CHARGING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	ppreduce
BattleScript_AirCannonSecondTurn::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifmovehadnoeffect BattleScript_HitFromCritCalc
	removetailwind BS_ATTACKER, BattleScript_AirCannonTryRemoveFoeTailwind
	removetailwind BS_TARGET, BattleScript_AirCannonJustRemoveUserTailwind
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_TAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_AirCannonTryRemoveFoeTailwind::
	removetailwind BS_TARGET, BattleScript_HitFromCritCalc
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_AirCannonJustRemoveUserTailwind::
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_TAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFloralHealing:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_FloralHealingTryRestoreStatDrops
	attackcanceler
	attackstring
	ppreduce
    jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_MoveUsedHealBlockPrevents @ stops pollen puff
    jumpifstatus3 BS_TARGET, STATUS3_HEAL_BLOCK, BattleScript_MoveUsedHealBlockPrevents
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifsubstituteblocks BattleScript_ButItFailed
	tryhealpulse BS_TARGET, BattleScript_AlreadyAtFullHp
	attackanimation
	waitanimation
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_FloralHealingTryRestoreStatDrops:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
    jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_FloralHealingRestoreStatDropsOnly
    jumpifstatus3 BS_TARGET, STATUS3_HEAL_BLOCK, BattleScript_FloralHealingRestoreStatDropsOnly
	jumpifsubstituteblocks BattleScript_FloralHealingRestoreStatDropsOnly
	tryhealpulse BS_TARGET, BattleScript_FloralHealingRestoreStatDropsOnly
	attackanimation
	waitanimation
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	tryresetnegativestatstages BS_TARGET
	printstring STRINGID_TARGETNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_FloralHealingRestoreStatDropsOnly:
	attackanimation
	waitanimation
	tryresetnegativestatstages BS_TARGET
	printstring STRINGID_TARGETNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFairyWind::
	jumpifstatus3 BS_TARGET, STATUS3_MINIMIZED, BattleScript_EffectHit
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setminimize
	printstring STRINGID_TARGETBECAMEMINIMIZED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectIgnition::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_ButItFailed
	halvehp BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	playstatchangeanimation BS_ATTACKER, BIT_SPATK, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPATK, MAX_STAT_STAGE, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	printstring STRINGID_PKMNCUTHPMAXEDSPATK
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSpeedUpUserAlly:
	jumpifspecieshasnolegs BS_ATTACKER, BattleScript_FailedFromAtkCanceler
	jumpifnoally BS_ATTACKER, BattleScript_EffectSpeedUp2
	jumpifallyhasnolegs BS_ATTACKER, BattleScript_EffectSpeedUp2
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_NOT_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_EffectSpeedUpUserAlly_Works
	jumpifstat BS_ATTACKER_PARTNER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ButItFailed
BattleScript_EffectSpeedUpUserAlly_Works:
	attackanimation
	waitanimation
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_EffectSpeedUpUserAlly_TryAlly
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectSpeedUpUserAllyUser_PrintString
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_EffectSpeedUpUserAllyUser_PrintString:
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectSpeedUpUserAlly_TryAlly:
	setallytonexttarget BattleScript_EffectSpeedUpUserAlly_TryAlly_
BattleScript_EffectSpeedUpUserAlly_End:
	goto BattleScript_MoveEnd
BattleScript_EffectSpeedUpUserAlly_TryAlly_:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectSpeedUpUserAlly_End
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectSpeedUpUserAlly_AllyAnim
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectSpeedUpUserAlly_End
BattleScript_EffectSpeedUpUserAlly_AllyAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectSpeedUpUserAlly_End

BattleScript_EffectDanceMania:
	attackcanceler
	attackstring
	ppreduce
	pause 5
	savedancetargets
	trydancemania BattleScript_ButItFailed
	attackanimation
	waitanimation
	setbyte gBattlerTarget, 0 @why?
	printstring STRINGID_STARTEDADANCEMANIA
	waitmessage B_WAIT_TIME_LONG
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	goto BattleScript_MoveEnd

BattleScript_EffectBoundary:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
    boundarydamagecalculation
BattleScript_Boundary30::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_HIGHROLLHITROLL
	waitmessage B_WAIT_TIME_LONG
	setword gBattleMoveDamage, 30
	adjustdamage
	goto BattleScript_HitFromAtkAnimation
BattleScript_Boundary60::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_HIGHROLLHITROLL
	waitmessage B_WAIT_TIME_LONG
	jumpifspeciesmegaboss BS_TARGET, BoundaryAgainstBossShunyong
	setword gBattleMoveDamage, 60
	adjustdamage
	goto BattleScript_HitFromAtkAnimation
BattleScript_Boundary90::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_HIGHROLLHITROLL
	waitmessage B_WAIT_TIME_LONG
	jumpifspeciesmegaboss BS_TARGET, BoundaryAgainstBossShunyong
	setword gBattleMoveDamage, 90
	adjustdamage
	goto BattleScript_HitFromAtkAnimation
BattleScript_BigBoundary::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_BIGBOUNDARY
	waitmessage B_WAIT_TIME_LONG
	jumpifspeciesmegaboss BS_TARGET, BoundaryAgainstBossShunyong
	setword gBattleMoveDamage, 444
	adjustdamage
	goto BattleScript_HitFromAtkAnimation
BoundaryAgainstBossShunyong::
	setword gBattleMoveDamage, 50
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectDefSpDefeUpHit::
	setmoveeffect MOVE_EFFECT_DEF_SPDEF_UP | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectSpecialDefenseUpHit::
	setmoveeffect MOVE_EFFECT_SP_DEF_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectGrassCannon:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_GrassCannonCheckTerrain
	jumpifterrainaffected BS_ATTACKER, STATUS_FIELD_GRASSY_TERRAIN, BattleScript_EffectSpecialDefenseUpHit
	goto BattleScript_EffectHit
BattleScript_GrassCannonCheckTerrain::
	jumpifterrainaffected BS_ATTACKER, STATUS_FIELD_GRASSY_TERRAIN, BattleScript_EffectDefSpDefeUpHit
	goto BattleScript_EffectDefenseUpHit

BattleScript_EffectSpiritAway::
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_SpiritAwayHealBlock
	setdrainedhp
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_SpiritAwayLiquidOoze
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB
	goto BattleScript_SpiritAwayUpdateHp
BattleScript_SpiritAwayLiquidOoze::
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
BattleScript_SpiritAwayUpdateHp::
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_SpiritAwayTryFainting
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpiritAwayTryFainting::
	tryfaintmon BS_ATTACKER
BattleScript_SpiritAwayHealBlock::
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_MULTITYPE, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_RKS_SYSTEM, BattleScript_MoveEnd
	jumpifsubstituteblocks BattleScript_MoveEnd
	trysoak BattleScript_MoveEnd
	printstring STRINGID_TARGETCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPetalBlizzard:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectAccuracyDownHit
	goto BattleScript_EffectHit

BattleScript_EffectSeedBomb:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectSappySeed
	goto BattleScript_EffectHit

BattleScript_EffectVigorRoot:
	attackcanceler
	attackstring
	ppreduce
	tryhealallhealth BS_ATTACKER, BattleScript_VigorRootTryCurseAndStats
	cursetarget BattleScript_VigorRootHealSuccessCurseFailedTryStats
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_VigorRootAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_VigorRootAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_VigorRootAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_VigorRootAtk
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_VigorRootEnd
BattleScript_VigorRootAtk::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootDef::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpAtk::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootEnd::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNLAIDCURSEVIGORROOT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_VigorRootTryCurseAndStats::
	cursetarget BattleScript_VigorRootCurseFailedHealFailed
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_VigorRootAtk2
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_VigorRootAtk2
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_VigorRootAtk2
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_VigorRootAtk2
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_VigorRootEnd2
BattleScript_VigorRootAtk2::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootDef2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootDef2
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootDef2::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpeed2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpeed2
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpeed2::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpAtk2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpAtk2
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpAtk2::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpDef2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpDef2
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpDef2::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootEnd2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootEnd2
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootEnd2::
	printstring STRINGID_PKMNLAIDCURSEVIGORROOT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_VigorRootHealSuccessCurseFailedTryStats::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_VigorRootAtk3
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_VigorRootAtk3
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_VigorRootAtk3
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_VigorRootAtk3
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_VigorRootEnd3
BattleScript_VigorRootAtk3::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootDef3
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootDef3
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootDef3::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpeed3
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpeed3
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpeed3::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpAtk3
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpAtk3
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpAtk3::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpDef3
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpDef3
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpDef3::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootEnd3
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootEnd3
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootEnd3::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_VigorRootCurseFailedHealFailed::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_VigorRootAtk4
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_VigorRootAtk4
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_VigorRootAtk4
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_VigorRootAtk4
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_VigorRootEnd4
BattleScript_VigorRootAtk4::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 4, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootDef4
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootDef4
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootDef4::
	setstatchanger STAT_DEF, 4, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpeed4
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpeed4
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpeed4::
	setstatchanger STAT_SPEED, 4, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpAtk4
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpAtk4
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpAtk4::
	setstatchanger STAT_SPATK, 4, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootSpDef4
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootSpDef4
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootSpDef4::
	setstatchanger STAT_SPDEF, 4, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VigorRootEnd4
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VigorRootEnd4
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VigorRootEnd4::
	goto BattleScript_MoveEnd

BattleScript_EffectSpeedDownHit2::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_2
	goto BattleScript_EffectHit

BattleScript_EffectSnapTrap::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_WRAP
	seteffectprimary
	waitmessage B_WAIT_TIME_LONG
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_SnapTrapPart2
	goto BattleScript_MoveEnd
BattleScript_SnapTrapPart2::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_2
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectGrippingNail::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_GrippingNailBloomingEffect
BattleScript_EffectGrippingNailContinue::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	addbyte sTRIPLE_KICK_POWER, 4
	critcalc
	damagecalc
	adjustdamage
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	setbyte sB_ANIM_TURN, 0
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_TryCursePortion
	jumpifsubstituteblocks BattleScript_TryCursePortion
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_TryCursePortion
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryCursePortion::
	cursetarget BattleScript_MoveEnd
	printstring STRINGID_PKMNLAIDCURSEGRIPPINGNAIL
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_GrippingNailBloomingEffect::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	addbyte sTRIPLE_KICK_POWER, 4
	critcalc
	damagecalc
	adjustdamage
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	setbyte sB_ANIM_TURN, 0
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_TryCursePortion2
	jumpifsubstituteblocks BattleScript_TryCursePortion2
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_TryCursePortion2
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryCursePortion2::
	cursetarget BattleScript_TryLeechSeedPortion
	printstring STRINGID_PKMNLAIDCURSEGRIPPINGNAIL
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryLeechSeedPortion::
	jumpifsubstituteblocks BattleScript_MoveEnd
	jumpifstatus3 BS_TARGET, STATUS3_LEECHSEED, BattleScript_MoveEnd
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_MoveEnd
	setseeded
	printfromtable gLeechSeedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFlorescence:
	attackcanceler
	attackstring
	ppreduce
	florescencecheck BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
BattleScript_EffectFlorescenceSkipAnim:
	copybyte gBattlerTarget, gBattlerAttacker
	setbyte gBattleCommunication, 0
BattleScript_FlorescenceTryCureStatus:
	jumpifstatus BS_TARGET, STATUS1_BLOOMING, BattleScript_FlorescenceTryRestoreAlly
	jumpifstatus BS_TARGET, STATUS1_ANY_NEGATIVE, BattleScript_FlorescenceCureStatus
	goto Florescence_GiveBlooming
Florescence_GiveBlooming:
	copybyte gBattlerAttacker, gBattlerTarget
	jumpifstatus BS_TARGET, STATUS1_BLOOMING, BattleScript_FlorescenceTryRestoreAlly
	jumpiftype BS_TARGET, TYPE_FIRE, BattleScript_FlorescenceTryRestoreAlly
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_FlorescenceTryRestoreAlly
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_FlorescenceTryRestoreAlly
	setmoveeffect MOVE_EFFECT_BLOOMING
	seteffectprimary
	addbyte gBattleCommunication, 1
BattleScript_FlorescenceTryRestoreAlly:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_FlorescenceEnd
	jumpifnoally BS_TARGET, BattleScript_MoveEnd
	setallytonexttarget BattleScript_FlorescenceTryCureStatus
BattleScript_FlorescenceEnd:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed
BattleScript_FlorescenceCureStatus:
	copybyte gBattlerAttacker, gBattlerTarget
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
	printstring STRINGID_FLORESCENCESTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	addbyte gBattleCommunication, 1
	goto BattleScript_FlorescenceTryRestoreAlly

BattleScript_EffectPowerDrain:
	jumpiffullhp BS_ATTACKER, BattleScript_PowerDrainJustTryRemoveElectricType
BattleScript_EffectPowerDrainContinue:
	setstatchanger STAT_SPEED, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_PowerDrainTryLower
	pause B_WAIT_TIME_SHORT
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_PowerDrainElectricLossAfterPPReduce
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_PowerDrainElectricLossAfterPPReduce
BattleScript_PowerDrainTryLower:
	getstatvalue BS_TARGET, STAT_SPEED
	jumpiffullhp BS_ATTACKER, BattleScript_PowerDrainMustLower
	attackanimation
	waitanimation
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_PowerDrainHp
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_PowerDrainHp
BattleScript_PowerDrainLower:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
@ Drain HP without lowering a stat
BattleScript_PowerDrainHp:
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_PowerDrainManipulateDmg
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_PowerDrainElectricLossAfterAnimation
	jumpiffullhp BS_ATTACKER, BattleScript_PowerDrainElectricLossAfterAnimation
BattleScript_PowerDrainManipulateDmg:
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_PowerDrainLiquidOoze
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNENERGYDRAINED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_PowerDrainElectricLossAfterAnimation
BattleScript_PowerDrainLiquidOoze:
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_PowerDrainElectricLossAfterAnimation
BattleScript_PowerDrainMustLower:
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_PowerDrainElectricLossAfterPPReduce
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_PowerDrainElectricLossAfterPPReduce
	attackanimation
	waitanimation
	goto BattleScript_PowerDrainLower
BattleScript_PowerDrainJustTryRemoveElectricType:
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_PowerDrainJustTryRemoveElectricType2
	goto BattleScript_EffectPowerDrainContinue
BattleScript_PowerDrainJustTryRemoveElectricType2:
	jumpiftype BS_TARGET, TYPE_ELECTRIC, BattleScript_PowerDrainElectricLossWorks
	goto BattleScript_EffectPowerDrainContinue
BattleScript_PowerDrainElectricLossWorks:
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	losetype BS_TARGET, TYPE_ELECTRIC
	attackanimation
	waitanimation
	printstring STRINGID_TARGETLOSTELECTRICTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_PowerDrainElectricLossAfterPPReduce:
	jumpiftype BS_TARGET, TYPE_ELECTRIC, BattleScript_PowerDrainElectricLossWorks2
	goto BattleScript_MoveEnd
BattleScript_PowerDrainElectricLossWorks2:
	losetype BS_TARGET, TYPE_ELECTRIC
	attackanimation
	waitanimation
	printstring STRINGID_TARGETLOSTELECTRICTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_PowerDrainElectricLossAfterAnimation:
	jumpiftype BS_TARGET, TYPE_ELECTRIC, BattleScript_PowerDrainElectricLossWorks3
	goto BattleScript_MoveEnd
BattleScript_PowerDrainElectricLossWorks3:
	losetype BS_TARGET, TYPE_ELECTRIC
	printstring STRINGID_TARGETLOSTELECTRICTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHearthwarm:
	jumpifnoally BS_ATTACKER, BattleScript_HearthwarmSingleBattle
	attackcanceler
	attackstring
	ppreduce
	copybyte gBattlerTarget, gBattlerAttacker
	setbyte gBattleCommunication, 0
	copybyte gBattlerAttacker, gBattlerTarget
	setuserstatus4 STATUS4_HEARTHWARM, BattleScript_SetHearthwarmAllySelfFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSURROUNDEDWITHVEILOFHEAT
	waitmessage B_WAIT_TIME_LONG
BattleScript_SetHearthwarmAlly:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_MoveEnd
	addbyte gBattleCommunication, 1
	jumpifnoally BS_TARGET, BattleScript_MoveEnd
	setallytonexttarget SetHearthWarmAlly
SetHearthWarmAlly:
	copybyte gBattlerAttacker, gBattlerTarget
	setuserstatus4 STATUS4_HEARTHWARM, BattleScript_MoveEnd
	printstring STRINGID_PKMNSURROUNDEDWITHVEILOFHEAT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_SetHearthwarmAllySelfFailed:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_ButItFailed
	addbyte gBattleCommunication, 1
	jumpifnoally BS_TARGET, BattleScript_ButItFailed
	setallytonexttarget BattleScript_SetHearthwarmAllySelfFailedTryAlly
BattleScript_SetHearthwarmAllySelfFailedTryAlly:
	copybyte gBattlerAttacker, gBattlerTarget
	setuserstatus4 STATUS4_HEARTHWARM, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSURROUNDEDWITHVEILOFHEAT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_HearthwarmSingleBattle:
	attackcanceler
	attackstring
	ppreduce
	setuserstatus4 STATUS4_HEARTHWARM, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSURROUNDEDWITHVEILOFHEAT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSunBask:
	attackcanceler
	attackstring
	ppreduce
	jumpifweatheraffected BS_ATTACKER, B_WEATHER_SUN, BattleScript_EffectTrySunBaskBlooming
	goto BattleScript_SunBaskStatBoost
BattleScript_EffectTrySunBaskBlooming::
	jumpifstatus BS_TARGET, STATUS1_BLOOMING, BattleScript_SunBaskStatBoost
	jumpiftype BS_TARGET, TYPE_FIRE, BattleScript_SunBaskStatBoost
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_SunBaskStatBoost
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_SunBaskStatBoost
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_SunBaskDoMoveAnimWithBlooming
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_SunBaskJustBloom
BattleScript_SunBaskDoMoveAnimWithBlooming::
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_CERTAIN
	seteffectprimary
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SunBaskTrySpDefWithBlooming
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SunBaskTrySpDefWithBlooming
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SunBaskTrySpDefWithBlooming::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_SunBaskJustBloom::
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_CERTAIN
	goto BattleScript_MoveEnd
BattleScript_SunBaskStatBoost::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_SunBaskDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_SunBaskDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SunBaskTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SunBaskTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SunBaskTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSpAttackAccUp:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_SpAttackAccUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ACC, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_SpAttackAccUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_ACC, 0
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SpAttackAccUpTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SpAttackAccUpTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpAttackAccUpTrySpDef::
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SpAttackAccUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SpAttackAccUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpAttackAccUpEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectRemodel:
	attackcanceler
	attackstring
	ppreduce
	remodelcheck BS_ATTACKER, BattleScript_RemodelDefenseUp
	goto BattleScript_RemodelSpDefenseUp
BattleScript_RemodelDefenseUp:
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_RemodelTryDefUp
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_ButItFailed
BattleScript_RemodelTryDefUp:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF,  0
	setstatchanger STAT_DEF, 3, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_RemodelTrySpDefDown
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_RemodelTrySpDefDown
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RemodelTrySpDefDown:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_SPDEF, 3, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_RemodelEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_RemodelEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RemodelEnd:
	goto BattleScript_MoveEnd
BattleScript_RemodelSpDefenseUp:
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_RemodelTrySpDefUp
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_DEF, MIN_STAT_STAGE, BattleScript_ButItFailed
BattleScript_RemodelTrySpDefUp:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF,  0
	setstatchanger STAT_SPDEF, 3, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_RemodelTryDefDown
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_RemodelTryDefDown
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RemodelTryDefDown:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_DEF, 3, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_RemodelEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_RemodelEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCriticalRepair:
	attackcanceler
	attackstring
	ppreduce
	trycriticalrepair BS_ATTACKER, BattleScript_AlreadyAtFullHp
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHeavyCell::
	attackcanceler
	attackstring
	ppreduce
BattleScript_EffectHeavyCellFromStatUp::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_HeavyCellDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_HeavyCellDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_HeavyCellDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, 0
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_HeavyCellTrySpecialDefense
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HeavyCellTrySpecialDefense
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HeavyCellTrySpecialDefense::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_HeavyCellTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HeavyCellTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HeavyCellTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_HeavyCellEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HeavyCellEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_HeavyCellEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectErodeField::
	attackcanceler
	attackstring
	ppreduce
	geterodefieldtargets BattleScript_ButItFailed
	@ at least one battler is affected
	attackanimation
	waitanimation
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_ErodeFieldLoop:
	movevaluescleanup
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_ErodeFieldCheckAffected
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_ErodeFieldCantRaiseMultipleStats
BattleScript_ErodeFieldCheckAffected:
	jumpifnoterodefieldaffected BS_TARGET, BattleScript_ErodeFieldNoEffect
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPDEF, STAT_CHANGE_MULTIPLE_STATS | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_ErodeFieldTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_ErodeFieldTrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ErodeFieldTrySpDef::
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_ErodeFieldMoveTargetEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_ErodeFieldMoveTargetEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ErodeFieldMoveTargetEnd:
	moveendto MOVEEND_NEXT_TARGET
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_ErodeFieldLoop
	end

BattleScript_ErodeFieldCantRaiseMultipleStats:
	copybyte gBattlerAttacker, gBattlerTarget
	printstring STRINGID_STATSWONTINCREASE2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_ErodeFieldMoveTargetEnd

BattleScript_ErodeFieldNoEffect:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_ErodeFieldMoveTargetEnd

BattleScript_EffectEnervator::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_EnervatorDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_EnervatorDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPEED, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EnervatorTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_EnervatorTrySpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EnervatorTrySpeed::
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EnervatorEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_EnervatorEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EnervatorEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectDeepGaze::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_EXPOSED, BattleScript_AlreadyExposed
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_EXPOSED
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_AlreadyExposed::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNISALREADYEXPOSED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSkySplitter::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifmovehadnoeffect BattleScript_HitFromCritCalc
	removetailwind BS_ATTACKER, BattleScript_SkySplitterTryRemoveFoeTailwind
	removetailwind BS_TARGET, BattleScript_SkySplitterJustRemoveUserTailwind
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_TAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_SkySplitterClearWeatherEnd
BattleScript_SkySplitterTryRemoveFoeTailwind::
	removetailwind BS_TARGET, BattleScript_HitFromCritCalc
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_SkySplitterClearWeatherEnd
BattleScript_SkySplitterJustRemoveUserTailwind::
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	printstring STRINGID_TAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
BattleScript_SkySplitterClearWeatherEnd::
	trytoclearweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRedline::
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	tryresetnegativestatstages BS_ATTACKER
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectDefenseDownHit2::
	setmoveeffect MOVE_EFFECT_DEF_MINUS_2
	goto BattleScript_EffectHit

BattleScript_EffectBrutalize::
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_ATK_TWO_DOWN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	seteffectprimary
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	argumentstatuseffect
	goto BattleScript_MoveEnd

BattleScript_EffectTickTack::
	setmoveeffect MOVE_EFFECT_TICKED
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	damagetopercentagetargethp
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_TickTackHealBlock
	setdrainedhp
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_TickTackLiquidOoze
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB
	goto BattleScript_TickTackUpdateHp
BattleScript_TickTackLiquidOoze::
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
BattleScript_TickTackUpdateHp::
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_TickTackTryFainting
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TickTackTryFainting::
	tryfaintmon BS_ATTACKER
BattleScript_TickTackHealBlock::
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectTerrorize::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_PANIC, BattleScript_AlreadyPanicking
	jumpiftype BS_TARGET, TYPE_DARK, BattleScript_NotAffected
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_NotAffected
	jumpifability BS_TARGET, ABILITY_UNAWARE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PANIC
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_AlreadyPanicking::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNISALREADYPANICKING
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRazingSun::
	jumpifdoublesmovesucceed BS_ATTACKER, BattleScript_NoMoveEffect
    call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_DoublesSkipEffect
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	setdoublesmovesucceed BS_ATTACKER
	checkdaybreakcounter 3, BattleScript_RazingSunWith3Daybreak
	applydaybreakcounter BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_USERGAINEDDAYBREAK
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_RazingSunWith3Daybreak::
	removealldaybreakcounters BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_USERUSEDUPALLDAYBREAK
	waitmessage B_WAIT_TIME_LONG
	tryhealhalfhealth BattleScript_MoveEnd, BS_ATTACKER
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSeizeChance:
	seizechancecheck BattleScript_EffectHit
	goto BattleScript_EffectFlinchHit

BattleScript_EffectExecution::
    call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	applyexhaustioncounter BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_USERHASEXHAUSTION
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectLoveTap::
	setmoveeffect MOVE_EFFECT_CONFUSION
	attackcanceler
	jumpifnotfirstturn BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	tryinfatuating BattleScript_MoveEnd
	printstring STRINGID_PKMNFELLINLOVE
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectVerglastrom::
	jumpifweatheraffected BS_ATTACKER, B_WEATHER_HAIL, BattleScript_EffectTrap
	goto BattleScript_EffectHit

BattleScript_EffectKerfuffle::
	setmoveeffect MOVE_EFFECT_CONFUSION | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectVoid::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	disablelastusedattack BattleScript_TryVoidTorment
	printstring STRINGID_PKMNMOVEWASDISABLED
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotDisabledAttacker
BattleScript_TryVoidTorment::
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_MoveEnd
	settorment BattleScript_MoveEnd
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker	
	goto BattleScript_MoveEnd

BattleScript_EffectSandTomb::
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_WRAP
	seteffectprimary
	jumpifweatheraffected BS_ATTACKER, B_WEATHER_SANDSTORM, BattleScript_EffectSandTombLowerDefense
	goto BattleScript_MoveEnd
BattleScript_EffectSandTombLowerDefense::
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectScorpFang::
	call BattleScript_EffectHit_Ret
	setmoveeffect MOVE_EFFECT_SMACK_DOWN
	seteffectprimary
	setmoveeffect MOVE_EFFECT_POISON
	seteffectsecondary
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_AllStatsDown::
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_AllStatsDownAtk
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_AllStatsDownAtk
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPEED, MIN_STAT_STAGE, BattleScript_AllStatsDownAtk
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPATK, MIN_STAT_STAGE, BattleScript_AllStatsDownAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_AllStatsDownRet
BattleScript_AllStatsDownAtk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsDownDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsDownDef::
	playstatchangeanimation BS_TARGET, BIT_DEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsDownSpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsDownSpeed::
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsDownSpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsDownSpAtk::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsDownSpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsDownSpDef::
	playstatchangeanimation BS_TARGET, BIT_SPDEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsDownRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsDownRet::
	return

BattleScript_DurinBerryAllStatsDown::
	copybyte sBATTLER, gBattlerAttacker
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	printstring STRINGID_DURINBERRYREALLYSTINKS
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_DurinBerryAllStatsDownAtk
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_DurinBerryAllStatsDownAtk
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, MIN_STAT_STAGE, BattleScript_DurinBerryAllStatsDownAtk
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPATK, MIN_STAT_STAGE, BattleScript_DurinBerryAllStatsDownAtk
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_DurinBerryAllStatsDownRet
BattleScript_DurinBerryAllStatsDownAtk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF | BIT_ACC | BIT_EVASION, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_ATTACKER, BIT_ATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_DurinBerryAllStatsDownDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DurinBerryAllStatsDownDef::
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER |  STAT_CHANGE_ALLOW_PTR, BattleScript_DurinBerryAllStatsDownSpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DurinBerryAllStatsDownSpeed::
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER |  STAT_CHANGE_ALLOW_PTR, BattleScript_DurinBerryAllStatsDownSpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DurinBerryAllStatsDownSpAtk::
	playstatchangeanimation BS_ATTACKER, BIT_SPATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER |  STAT_CHANGE_ALLOW_PTR, BattleScript_DurinBerryAllStatsDownSpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DurinBerryAllStatsDownSpDef::
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER |  STAT_CHANGE_ALLOW_PTR, BattleScript_DurinBerryAllStatsDownAccuracy
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_DurinBerryAllStatsDownAccuracy::
	playstatchangeanimation BS_ATTACKER, BIT_ACC, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER |  STAT_CHANGE_ALLOW_PTR, BattleScript_DurinBerryAllStatsDownEvasion
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_DurinBerryAllStatsDownEvasion::
	playstatchangeanimation BS_ATTACKER, BIT_EVASION, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER |  STAT_CHANGE_ALLOW_PTR, BattleScript_DurinBerryAllStatsDownRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_DurinBerryAllStatsDownRet::
	return

BattleScript_PomegBerryInvertEnd2::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	invertnegativestatstages BS_ATTACKER
	printstring STRINGID_POMEGSWITCHEDNEGATIVESTATS
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	end2

BattleScript_PomegBerryInvertReturn::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	invertnegativestatstages BS_SCRIPTING
	printstring STRINGID_POMEGSWITCHEDNEGATIVESTATS
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_HondewBerryActivatesEnd2::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	printstring STRINGID_PKMNSURROUNDEDWITHVEILS
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	end2

BattleScript_HondewBerryActivatesReturn::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	printstring STRINGID_PKMNSURROUNDEDWITHVEILS
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_CheeseActivatesEnd2::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_CheeseRandomStatBoostEnd2
	tryhealthirdhealth BS_ATTACKER, BattleScript_CheeseRandomStatBoostEnd2
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
BattleScript_CheeseRandomStatBoostEnd2:
	trycheesing BS_ATTACKER, BattleScript_CheeseReturn
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CheeseReturn
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CheeseReturn
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CheeseEnd2:
	removeitem BS_ATTACKER
	end2

BattleScript_CheeseActivatesReturn::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	jumpifstatus3 BS_SCRIPTING, STATUS3_HEAL_BLOCK, BattleScript_CheeseRandomStatBoostReturn
	tryhealthirdhealth BS_SCRIPTING, BattleScript_CheeseRandomStatBoostReturn
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
BattleScript_CheeseRandomStatBoostReturn:
	trycheesing BS_SCRIPTING, BattleScript_CheeseReturn
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_CheeseReturn
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CheeseReturn
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CheeseReturn:
	removeitem BS_SCRIPTING
	return

BattleScript_FrothyCheeseActivatesEnd2::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_FrothyCheeseRandomStatBoostEnd2
	tryhealsixthhealth BS_ATTACKER, BattleScript_FrothyCheeseRandomStatBoostEnd2
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
BattleScript_FrothyCheeseRandomStatBoostEnd2:
	tryaccupressure BS_ATTACKER, BattleScript_FrothyCheeseReturn
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_FrothyCheeseReturn
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_FrothyCheeseReturn
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FrothyCheeseEnd2:
	removeitem BS_ATTACKER
	end2

BattleScript_FrothyCheeseActivatesReturn::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	jumpifstatus3 BS_SCRIPTING, STATUS3_HEAL_BLOCK, BattleScript_FrothyCheeseRandomStatBoostReturn
	tryhealsixthhealth BS_SCRIPTING, BattleScript_FrothyCheeseRandomStatBoostReturn
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
BattleScript_FrothyCheeseRandomStatBoostReturn:
	tryaccupressure BS_SCRIPTING, BattleScript_FrothyCheeseReturn
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_FrothyCheeseReturn
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_FrothyCheeseReturn
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FrothyCheeseReturn:
	removeitem BS_SCRIPTING
	return

BattleScript_YellowSodaActivatesEnd2::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	jumpifability BS_ATTACKER, ABILITY_RIPEN, BattleScript_YellowSodaActivatesEnd2Ripen
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_YellowSodaFocusEnergyEnd2
	tryhealhalfhealth BattleScript_YellowSodaFocusEnergyEnd2, BS_ATTACKER
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
BattleScript_YellowSodaFocusEnergyEnd2:
	jumpifstatus2 BS_ATTACKER, STATUS2_FOCUS_ENERGY_ANY, BattleScript_YellowSodaSpeedBoostEnd2
	setfocusenergy BS_ATTACKER
	printfromtable gFocusEnergyUsedStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_YellowSodaSpeedBoostEnd2:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_YellowSodaEnd2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_YellowSodaEnd2
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_YellowSodaEnd2:
	removeitem BS_ATTACKER
	end2
BattleScript_YellowSodaActivatesEnd2Ripen:
	call BattleScript_AbilityPopUp
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_YellowSodaFocusEnergyEnd2Ripen
	tryhealallhealth BS_ATTACKER, BattleScript_YellowSodaFocusEnergyEnd2Ripen
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
BattleScript_YellowSodaFocusEnergyEnd2Ripen:
	jumpifstatus2 BS_ATTACKER, STATUS2_FOCUS_ENERGY_ANY, BattleScript_YellowSodaSpeedBoostEnd2Ripen
	setfocusenergy BS_ATTACKER
	printfromtable gFocusEnergyUsedStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_YellowSodaSpeedBoostEnd2Ripen:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_YellowSodaEnd2Ripen
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_YellowSodaEnd2Ripen
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_YellowSodaEnd2Ripen:
	removeitem BS_ATTACKER
	end2

BattleScript_YellowSodaActivatesReturn::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_YellowSodaActivatesReturnRipen
	jumpifstatus3 BS_SCRIPTING, STATUS3_HEAL_BLOCK, BattleScript_YellowSodaFocusEnergyReturn
	tryhealhalfhealth BattleScript_YellowSodaFocusEnergyReturn, BS_SCRIPTING
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
BattleScript_YellowSodaFocusEnergyReturn:
	jumpifstatus2 BS_SCRIPTING, STATUS2_FOCUS_ENERGY_ANY, BattleScript_YellowSodaSpeedBoostReturn
	setfocusenergy BS_SCRIPTING
	printfromtable gFocusEnergyUsedStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_YellowSodaSpeedBoostReturn:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_YellowSodaReturn
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_YellowSodaReturn
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_YellowSodaReturn:
	removeitem BS_SCRIPTING
	return
BattleScript_YellowSodaActivatesReturnRipen:
	call BattleScript_AbilityPopUp
	jumpifstatus3 BS_SCRIPTING, STATUS3_HEAL_BLOCK, BattleScript_YellowSodaFocusEnergyReturnRipen
	tryhealallhealth BS_SCRIPTING, BattleScript_YellowSodaFocusEnergyReturnRipen
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
BattleScript_YellowSodaFocusEnergyReturnRipen:
	jumpifstatus2 BS_SCRIPTING, STATUS2_FOCUS_ENERGY_ANY, BattleScript_YellowSodaSpeedBoostReturnRipen
	setfocusenergy BS_SCRIPTING
	printfromtable gFocusEnergyUsedStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_YellowSodaSpeedBoostReturnRipen:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_YellowSodaReturnRipen
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_YellowSodaReturnRipen
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_YellowSodaReturnRipen:
	removeitem BS_SCRIPTING
	return

BattleScript_EffectGunkFunk::
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_AllStatsDownHitCertain
	goto BattleScript_EffectAllStatsDownHit

BattleScript_AllStatsDownHitCertain:
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_ALL_STATS_DOWN
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectAllStatsDownHit::
	setmoveeffect MOVE_EFFECT_ALL_STATS_DOWN
	goto BattleScript_EffectHit

BattleScript_EffectVenomDrain:
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_VenomDrain
	goto BattleScript_EffectAbsorb
BattleScript_VenomDrain::
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_VenomDrainHealBlock
	setdrainedhp
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_VenomDrainLiquidOoze
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB
	goto BattleScript_VenomDrainUpdateHp
BattleScript_VenomDrainLiquidOoze::
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
BattleScript_VenomDrainUpdateHp::
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_VenomDrainTryFainting
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrainTryFainting::
	tryfaintmon BS_ATTACKER
BattleScript_VenomDrainHealBlock::
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifsubstituteblocks BattleScript_EffectHit
	setmoveeffect MOVE_EFFECT_REMOVE_STATUS
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectDefAccDownHit::
	setmoveeffect MOVE_EFFECT_DEF_ACC_DOWN
	goto BattleScript_EffectHit

BattleScript_LoneSharkSetUp::
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	playanimation BS_ATTACKER, B_ANIM_FOCUS_PUNCH_SETUP
	setglaiverush
	printstring STRINGID_PKMNLEAVINGITSELFOPEN
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_EffectDragonPoker::
	shellsidearmcheck
	setmoveeffect MOVE_EFFECT_PAYDAY
	attackcanceler
	attackstring
	ppreduce
	dragonpokerdamagecalculation
BattleScript_DragonPokerNoPair::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERNOPAIR
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerOnePair::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERONEPAIR
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerTwoPair::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERTWOPAIR
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerThreeOfAKind::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERTHREEOFAKIND
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerStraight::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERSTRAIGHT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerFlush::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERFLUSH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerFullHouse::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERFULLHOUSE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerFourOfAKind::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERFOUROFAKIND
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerStraightFlush::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERSTRAIGHTFLUSH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc
BattleScript_DragonPokerRoyalFlush::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_DRAGONPOKERROYALFLUSH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc

BattleScript_EffectHeartCarve::
	jumpifstatus2 BS_ATTACKER, STATUS2_INFATUATION, BattleScript_HeartCarveApplyFrenzy
	goto BattleScript_EffectHit
BattleScript_HeartCarveApplyFrenzy::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	applyfrenzycounter BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_USERHASENTEREDAFRENZY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHullbreaker::
	setmoveeffect MOVE_EFFECT_DEF_MINUS_2
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	removelightscreenreflect
	critcalc
	damagecalc
	adjustdamage
	jumpifbyte CMP_EQUAL, sB_ANIM_TURN, 0, BattleScript_HullbreakerAnim
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE
BattleScript_HullbreakerAnim::
	attackanimation
	waitanimation
	jumpifbyte CMP_LESS_THAN, sB_ANIM_TURN, 2, BattleScript_HullbreakerDoHit
	printstring STRINGID_THEWALLSHATTERED
	waitmessage B_WAIT_TIME_LONG
BattleScript_HullbreakerDoHit::
	typecalc
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectTidyUp::
	attackcanceler
	attackstring
	pause B_WAIT_TIME_MED
	ppreduce
	waitstate
	saveattacker
	savetarget
	trytidyup FALSE, BattleScript_EffectTidyUpDoMoveAnimation
	restoreattacker
	restoretarget
	goto BattleScript_EffectDragonDanceFromStatUp

BattleScript_EffectTidyUpDoMoveAnimation::
	attackanimation
	waitanimation
	trytidyup TRUE, NULL
	printstring STRINGID_TIDYINGUPCOMPLETE
	waitmessage B_WAIT_TIME_LONG
	restoreattacker
	restoretarget
	goto BattleScript_EffectVictoryDanceFromStatUp

BattleScript_EffectSerpentSurge:
	shellsidearmcheck
	jumpifability BS_ATTACKER, ABILITY_HYDRATION, BattleScript_EffectAbsorb
	jumpifability BS_ATTACKER, ABILITY_REGENERATOR, BattleScript_EffectHitEscape
	goto BattleScript_EffectHit

BattleScript_EffectPartingCurry:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ACC, MIN_STAT_STAGE, BattleScript_EffectPartingCurryTryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_EVASION, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_EffectPartingCurryTryAtk:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ACC | BIT_EVASION, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ACC, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectPartingCurryTrySpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectPartingCurryTrySpAtk:
	playstatchangeanimation BS_TARGET, BIT_EVASION, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectPartingCurrySwitch
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectPartingCurrySwitch:
	moveendall
	goto BattleScript_MoveSwitch
BattleScript_PartingCurryEnd:
	end

BattleScript_EffectRadioacid:
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_RadioacidDefSpDef
	jumpifstatus BS_TARGET, STATUS1_BURN, BattleScript_RadioacidDefSpDef
	setmoveeffect MOVE_EFFECT_RADIOACID
	goto BattleScript_EffectHit
BattleScript_RadioacidDefSpDef:
	setmoveeffect MOVE_EFFECT_DEF_SPDEF_DOWN
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_ATK_MINUS_1
	seteffectprimary
	moveendall
	end

BattleScript_EffectWarmWelcome:
	printstring STRINGID_PKMNWELCOMETHEAUDIENCE
	waitmessage B_WAIT_TIME_LONG
	jumpifnotberry BS_ATTACKER, BattleScript_EffectSunnyDay
	attackcanceler
	ppreduce
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_SUN_PRIMAL, BattleScript_StuffCheeksEatBerry
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_RAIN_PRIMAL, BattleScript_StuffCheeksEatBerry
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_STRONG_WINDS, BattleScript_StuffCheeksEatBerry
	attackstring
	attackanimation
	waitanimation
	setsunny
	call BattleScript_MoveWeatherChangeRet
	goto BattleScript_StuffCheeksEatBerry
BattleScript_EffectWarmWelcomeSunnyDayFailedStuffCheeksSucceeded::
	attackstring
	attackanimation
	waitanimation
	setbyte sBERRY_OVERRIDE, 1
	orword gHitMarker, HITMARKER_NO_ANIMATIONS
	consumeberry BS_ATTACKER, TRUE
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, 0
	removeitem BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectVexingKi:
	jumpifstatus2 BS_TARGET, STATUS2_TORMENT, BattleScript_EffectPanicHit
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	settorment BattleScript_MoveEnd
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectSilence:
	attackcanceler
	attackstring
	ppreduce
	setsilence BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_SILENCESTARTS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCinderDrill::
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	trycinderdrill
	moveendall
	end

BattleScript_EffectCinderTwirl:
	call BattleScript_EffectHit_Ret
	jumpifhalfword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_RAPIDSPIN | MOVE_EFFECT_AFFECTS_USER
	seteffectwithchance
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_EffectCinderTwirlEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectCinderTwirlEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectCinderTwirlEnd::
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	trycindertwirl
	moveendall
	end

BattleScript_EffectDragonRuin::
	@ DecideTurn
	jumpifdoublesmovesucceed BS_ATTACKER, BattleScript_DragonRuinSecondTurn
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_DragonRuinSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_DragonRuinSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_DRAGON_RUIN
BattleScript_TryDragonRuinCharging:
	call BattleScript_FirstChargingTurnDragonRuin
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
BattleScript_DragonRuinSecondTurn::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_RECHARGE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	seteffectsecondary
	setdoublesmovesucceed BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_FirstChargingTurnDragonRuin::
	attackcanceler
	printstring STRINGID_EMPTYSTRING3
	ppreduce
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_CHARGING
	setmoveeffect MOVE_EFFECT_CHARGING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	copybyte cMULTISTRING_CHOOSER, sTWOTURN_STRINGID
	printfromtable gFirstTurnOfTwoStringIds
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_DEF_SPDEF_UP | MOVE_EFFECT_AFFECTS_USER
	seteffectsecondary
	return

BattleScript_EffectMeditate::
	attackcanceler
	attackstring
	ppreduce
BattleScript_MeditateTryToRaiseStats::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_MeditateDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_MeditateDoMoveAnim::
	attackanimation
	waitanimation
BattleScript_MeditateStatRaise::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MeditateTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MeditateTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MeditateTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MeditateEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MeditateEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MeditateEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectHeartStamp:
	jumpifstatus2 BS_TARGET, STATUS2_INFATUATION, BattleScript_HeartStampAgainstInfatuated
	goto BattleScript_EffectSpringBreeze
BattleScript_HeartStampAgainstInfatuated::
	setmoveeffect MOVE_EFFECT_DEF_MINUS_2
	goto BattleScript_EffectSpringBreeze

BattleScript_EffectCharm:
	jumpifstatus2 BS_TARGET, STATUS2_INFATUATION, BattleScript_EffectAttackDown3
	setstatchanger STAT_ATK, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectAttackDown3:
	setstatchanger STAT_ATK, 3, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectFlash:
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_StatDownFromPPReduce
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_StatDownFromPPReduce
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_StatDownFromPPReduce
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_StatDownFromPPReduce
	jumpifsafeguard BattleScript_StatDownFromPPReduce
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_FlashStatDownEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_FlashStatDownDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_FlashStatDownEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_FlashStatDownPrintString
BattleScript_FlashStatDownDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_FlashStatDownPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FlashStatDownEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectEerieImpulse:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPATK, MIN_STAT_STAGE, BattleScript_EerieImpulseDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_EerieImpulseDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_SPATK | BIT_SPDEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EerieImpulseTryLowerSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_EerieImpulseTryLowerSpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EerieImpulseTryLowerSpDef::
	playstatchangeanimation BS_TARGET, BIT_SPDEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EerieImpulseEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_EerieImpulseEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EerieImpulseEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSpiderWeb:
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setspiderweb BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SpiderWebEndTurn::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPEED, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_SpiderWebTryLowerSpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpiderWebTryLowerSpDef:
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_SpiderWebTurnDmgEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpiderWebTurnDmgEnd:
	end2

BattleScript_EffectRagePowder::
	jumpifnotbattletype BATTLE_TYPE_DOUBLE, BattleScript_EffectTaunt
	jumpifdoublesmovesucceed BS_ATTACKER, BattleScript_EffectRagePowderJustTaunt
	attackcanceler
	attackstring
	ppreduce
	setforcedtarget
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_EffectRagePowderJustFollowMe
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_EffectRagePowderJustFollowMe
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_EffectRagePowderJustFollowMe
	jumpifsafeguard BattleScript_EffectRagePowderJustFollowMe
	settaunt BattleScript_EffectRagePowderJustFollowMe
	attackanimation
	waitanimation
	setdoublesmovesucceed BS_ATTACKER
	printstring STRINGID_PKMNCENTERATTENTION
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNFELLFORTAUNT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTauntAttacker
	goto BattleScript_MoveEnd
BattleScript_EffectRagePowderJustFollowMe::
	attackanimation
	waitanimation
	setdoublesmovesucceed BS_ATTACKER
	printstring STRINGID_PKMNCENTERATTENTION
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectRagePowderJustTaunt::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	settaunt BattleScript_MoveEnd
	attackanimation
	waitanimation
	printstring STRINGID_PKMNFELLFORTAUNT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTauntAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectSignalBeam::
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_SignalBeamStatDrop
	setmoveeffect MOVE_EFFECT_CONFUSION
	goto BattleScript_EffectHit
BattleScript_SignalBeamStatDrop::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_ACC_MINUS_1
	seteffectprimary
	moveendall
	end

BattleScript_EffectSilverWind:
	setmoveeffect MOVE_EFFECT_ALL_STATS_UP | MOVE_EFFECT_AFFECTS_USER
	jumpifstatus2 BS_TARGET, STATUS2_POWDER, BattleScript_EffectHit
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_SilverWind2
	jumpifstatus2 BS_TARGET, STATUS2_POWDER, BattleScript_SilverWind2
	setpowder BS_TARGET
	seteffectwithchance
	printstring STRINGID_COVEREDINPOWDER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_SilverWind2:
	seteffectwithchance
	goto BattleScript_MoveEnd

BattleScript_EffectUTurn:
	setmoveeffect MOVE_EFFECT_FLINCH
	call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_MoveEnd
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendto MOVEEND_ATTACKER_VISIBLE
	moveendfrom MOVEEND_TARGET_VISIBLE
	jumpifbattleend BattleScript_HitEscapeEnd
	jumpifbyte CMP_NOT_EQUAL gBattleOutcome, 0, BattleScript_HitEscapeEnd
	jumpifemergencyexited BS_TARGET, BattleScript_HitEscapeEnd
	goto BattleScript_MoveSwitch

BattleScript_EffectFlipTurn:
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
	call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_MoveEnd
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendto MOVEEND_ATTACKER_VISIBLE
	moveendfrom MOVEEND_TARGET_VISIBLE
	jumpifbattleend BattleScript_HitEscapeEnd
	jumpifbyte CMP_NOT_EQUAL gBattleOutcome, 0, BattleScript_HitEscapeEnd
	jumpifemergencyexited BS_TARGET, BattleScript_HitEscapeEnd
	goto BattleScript_MoveSwitch

BattleScript_EffectSpook::
	attackcanceler
	attackstring
	ppreduce
	jumpifroarfails BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut
	jumpifability BS_TARGET, ABILITY_STALWART, BattleScript_AbilityPreventsPhasingOut
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_ButItFailed
	forcerandomswitch BattleScript_ButItFailed
BattleScript_SpookSuccessSwitch::
	call BattleScript_RoarSuccessRet
	getswitchedmondata BS_TARGET
	switchindataupdate BS_TARGET
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	switchinanim BS_TARGET, FALSE
	waitstate
	printstring STRINGID_PKMNWASDRAGGEDOUT
	switchineffects BS_TARGET
	jumpifbyte CMP_EQUAL, sSWITCH_CASE, B_SWITCH_RED_CARD, BattleScript_SpookSuccessSwitch_Ret
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	damagetopercentagetargethp
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd
BattleScript_SpookSuccessSwitch_Ret:
	swapattackerwithtarget  @ continuation of RedCardActivates
	restoretarget
	restoreattacker
	restoresavedmove
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	damagetopercentagetargethp
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	return

BattleScript_EffectDearlyDepart::
	setstatchanger STAT_SPDEF, 1, TRUE
	attackcanceler
	attackstring
	ppreduce
	jumpifroarfails BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut
	jumpifability BS_TARGET, ABILITY_STALWART, BattleScript_AbilityPreventsPhasingOut
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_ButItFailed
	forcerandomswitch BattleScript_ButItFailed
BattleScript_DearlyDepartSuccessSwitch::
	call BattleScript_RoarSuccessRet
	getswitchedmondata BS_TARGET
	switchindataupdate BS_TARGET
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	switchinanim BS_TARGET, FALSE
	waitstate
	printstring STRINGID_PKMNWASDRAGGEDOUT
	switchineffects BS_TARGET
	jumpifbyte CMP_EQUAL, sSWITCH_CASE, B_SWITCH_RED_CARD, BattleScript_DearlyDepartSuccessSwitch_Ret
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	jumpifsubstituteblocks BattleScript_DearlyDepartStatDownEnd
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_DearlyDepartStatDownEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DearlyDepartStatDownDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_DearlyDepartStatDownEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_DearlyDepartStatDownEnd
BattleScript_DearlyDepartStatDownDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DearlyDepartStatDownEnd::
	goto BattleScript_MoveEnd
BattleScript_DearlyDepartSuccessSwitch_Ret:
	swapattackerwithtarget  @ continuation of RedCardActivates
	restoretarget
	restoreattacker
	restoresavedmove
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	jumpifsubstituteblocks BattleScript_DearlyDepartStatDownRet
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_DearlyDepartStatDownRet
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DearlyDepartStatDownDoAnim2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_DearlyDepartStatDownRet
	pause B_WAIT_TIME_SHORT
	goto BattleScript_DearlyDepartStatDownRet
BattleScript_DearlyDepartStatDownDoAnim2::
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DearlyDepartStatDownRet::
	return

BattleScript_AllStatsUp2::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AllStatsUp2Atk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_AllStatsUp2Atk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_AllStatsUp2Atk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_AllStatsUp2Atk
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_AllStatsUp2Ret
BattleScript_AllStatsUp2Atk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2Def
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2Def
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2Def::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2Speed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2Speed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2Speed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2SpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2SpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2SpAtk::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2SpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2SpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2SpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2Ret
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2Ret
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2Ret::
	return

BattleScript_EffectAllStatsUp2Hit::
	setmoveeffect MOVE_EFFECT_ALL_STATS_UP_2 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectAllStatsUp2HitFoe::
	setmoveeffect MOVE_EFFECT_ALL_STATS_UP_2_FOE
	goto BattleScript_EffectHit

BattleScript_AllStatsUp2Foe::
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AllStatsUp2FoeAtk
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_AllStatsUp2FoeAtk
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_AllStatsUp2FoeAtk
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_AllStatsUp2FoeAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_AllStatsUp2FoeRet
BattleScript_AllStatsUp2FoeAtk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2FoeDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2FoeDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2FoeDef::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2FoeSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2FoeSpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2FoeSpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2FoeSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2FoeSpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2FoeSpAtk::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2FoeSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2FoeSpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2FoeSpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUp2FoeRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AllStatsUp2FoeRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUp2FoeRet::
	return

BattleScript_EffectPsychicNoise:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	sethealblock BattleScript_MoveEnd
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotHealBlockAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectDragonCheer:
	attackcanceler
	attackstring
	ppreduce
	jumpifnoally BS_ATTACKER, BattleScript_ButItFailed
	copybyte gBattlerTarget, gBattlerAttacker
	setallytonexttarget EffectDragonCheer_CheckAllyStats
	goto BattleScript_ButItFailed
EffectDragonCheer_CheckAllyStats:
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ACC, MAX_STAT_STAGE, BattleScript_DragonCheerWorks
	jumpifstatus2 BS_TARGET, STATUS2_FOCUS_ENERGY_ANY, BattleScript_ButItFailed
	goto Battlescript_DragonCheerTryFocusEnergy 
BattleScript_DragonCheerWorks:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ACC, 0x0
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_DragonCheerEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_DragonCheerEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DragonCheerEnd:
	jumpifstatus2 BS_TARGET, STATUS2_FOCUS_ENERGY_ANY, BattleScript_MoveEnd
	setfocusenergy BS_TARGET
	printfromtable gFocusEnergyUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
Battlescript_DragonCheerTryFocusEnergy::
	setfocusenergy BS_TARGET
	attackanimation
	waitanimation
	printfromtable gFocusEnergyUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFickleBeam:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	ficklebeamdamagecalculation
	goto BattleScript_HitFromCritCalc
BattleScript_FickleBeamDoubled::
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_FICKLEBEAMDOUBLED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc

BattleScript_EffectShedTail::
	attackcanceler
	attackstring
	ppreduce
	waitstate
	jumpifstatus2 BS_ATTACKER, STATUS2_SUBSTITUTE, BattleScript_AlreadyHasSubstitute
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_ButItFailed
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_ButItFailed
	setsubstitute
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_SUBSTITUTE_FAILED, BattleScript_SubstituteString
	orword gHitMarker, HITMARKER_PASSIVE_DAMAGE
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_SHEDITSTAIL
	waitmessage B_WAIT_TIME_LONG
	moveendto MOVEEND_ATTACKER_VISIBLE
	moveendfrom MOVEEND_TARGET_VISIBLE
	goto BattleScript_MoveSwitchOpenPartyScreen

BattleScript_EffectChillyReception::
	printstring STRINGID_PKMNTELLCHILLINGRECEPTIONJOKE
	waitmessage B_WAIT_TIME_LONG
	attackcanceler
	ppreduce
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_SUN_PRIMAL, BattleScript_EffectChillyReceptionBlockedByPrimalSun
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_RAIN_PRIMAL, BattleScript_EffectChillyReceptionBlockedByPrimalRain
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_STRONG_WINDS, BattleScript_EffectChillyReceptionBlockedByStrongWinds
	call BattleScript_EffectChillyReceptionPlayAnimation
	sethail
	call BattleScript_MoveWeatherChangeRet
	goto BattleScript_MoveSwitch
BattleScript_EffectChillyReceptionPlayAnimation:
	attackstring
	attackanimation
	waitanimation
	return
BattleScript_EffectChillyReceptionBlockedByPrimalSun:
	call BattleScript_EffectChillyReceptionTrySwitchWeatherFailed
	call BattleScript_ExtremelyHarshSunlightWasNotLessenedRet
	goto BattleScript_MoveSwitch
BattleScript_EffectChillyReceptionBlockedByPrimalRain:
	call BattleScript_EffectChillyReceptionTrySwitchWeatherFailed
	call BattleScript_NoReliefFromHeavyRainRet
	goto BattleScript_MoveSwitch
BattleScript_EffectChillyReceptionBlockedByStrongWinds:
	call BattleScript_EffectChillyReceptionTrySwitchWeatherFailed
	call BattleScript_MysteriousAirCurrentBlowsOnRet
	goto BattleScript_MoveSwitch
BattleScript_EffectChillyReceptionTrySwitchWeatherFailed:
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_FailedFromAtkString
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_FailedFromAtkString
	call BattleScript_EffectChillyReceptionPlayAnimation
	return

BattleScript_CheckPrimalWeather:
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessened
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRain
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOn
	return

BattleScript_MoveSwitch:
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_MoveSwitchEnd
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_MoveSwitchEnd
	printstring STRINGID_PKMNWENTBACK
	waitmessage B_WAIT_TIME_SHORT
BattleScript_MoveSwitchOpenPartyScreen:
	openpartyscreen BS_ATTACKER, BattleScript_MoveSwitchEnd
	switchoutabilities BS_ATTACKER
	waitstate
	switchhandleorder BS_ATTACKER, 2
	returntoball BS_ATTACKER
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, TRUE
	waitstate
	switchineffects BS_ATTACKER
BattleScript_MoveSwitchEnd:
	end

BattleScript_EffectFilletAway::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_FilletAwayTryAttack
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_FilletAwayTryAttack
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ButItFailed
BattleScript_FilletAwayTryAttack::
	cuthp BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK | BIT_SPEED, STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_FilletAwayTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FilletAwayTrySpAtk::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_FilletAwayTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FilletAwayTrySpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_FilletAwayEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FilletAwayEnd::
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectChillyAir:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_EVASION, MIN_STAT_STAGE, BattleScript_ChillyAirDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_ChillyAirDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_EVASION | BIT_SPEED, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_EVASION, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_ChillyAirTryLowerSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_ChillyAirTryLowerSpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ChillyAirTryLowerSpeed::
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_ChillyAirEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_ChillyAirEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ChillyAirEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectGlaciate::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_FROSTBITE, BattleScript_AlreadyFrostbitten
	jumpiftype BS_TARGET, TYPE_ICE, BattleScript_NotAffected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET_SIDE, ABILITY_WATER_VEIL, BattleScript_WaterVeilProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_FROSTBITE
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_AlreadyFrostbitten::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNALREADYHASFROSTBITE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSaltCure:
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpiffainted BS_TARGET, TRUE, BattleScript_EffectSaltCure_End
	jumpifmovehadnoeffect BattleScript_EffectSaltCure_End
	jumpifbattleend BattleScript_EffectSaltCure_End
	jumpifstatus4 BS_TARGET, STATUS4_SALT_CURE, BattleScript_EffectSaltCure_End
	applysaltcure BS_TARGET
	printstring STRINGID_TARGETISBEINGSALTCURED
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectSaltCure_End:
	goto BattleScript_MoveEnd

BattleScript_SaltCureExtraDamage::
	playanimation BS_TARGET, B_ANIM_SALT_CURE_DAMAGE, NULL
	waitanimation
	call BattleScript_HurtTarget_NoString
	printstring STRINGID_TARGETISHURTBYSALTCURE
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_HurtTarget_NoString:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	tryfaintmon BS_TARGET
	return

BattleScript_EffectMortalSpin:
	call BattleScript_EffectHit_Ret
	rapidspinfree
	setmoveeffect MOVE_EFFECT_POISON
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendall
	end

BattleScript_EffectCorrosiveGas:
	setstatchanger STAT_DEF, 1, TRUE
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_CorrosiveGasFail
	jumpifcantloseitem BS_TARGET, BattleScript_StatDownFromPPReduce
	jumpifability BS_TARGET, ABILITY_STICKY_HOLD, BattleScript_StatDownFromPPReduce
	jumpiftype BS_TARGET, TYPE_FAIRY, BattleScript_StatDownFromPPReduce
	attackanimation
	waitanimation
	setlastuseditem BS_TARGET
	removeitem BS_TARGET
	printstring STRINGID_PKMNITEMMELTED
	waitmessage B_WAIT_TIME_LONG
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_CorrosiveGasEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_CorrosiveGasDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_CorrosiveGasEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_CorrosiveGasPrintString
BattleScript_CorrosiveGasDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_CorrosiveGasPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CorrosiveGasEnd::
	goto BattleScript_MoveEnd

BattleScript_CorrosiveGasFail:
	pause B_WAIT_TIME_SHORT
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMakeItRain:
	jumpifdoublesmovesucceed BS_ATTACKER, BattleScript_NoMoveEffect
	setmoveeffect MOVE_EFFECT_PAYDAY
    call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_DoublesSkipEffect
	setdoublesmovesucceed BS_ATTACKER
	seteffectwithchance
	setmoveeffect MOVE_EFFECT_SP_ATK_MINUS_2 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	seteffectprimary
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectSpinOut::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_2 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectAxeKick::
	setmoveeffect MOVE_EFFECT_CONFUSION
	goto BattleScript_EffectRecoilIfMiss

BattleScript_EffectTakeHeart::
	attackcanceler
	attackstring
	ppreduce
	curestatuswithmove BS_ATTACKER, BattleScript_CalmMindTryToRaiseStats
	attackanimation
	waitanimation
	updatestatusicon BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CalmMindStatRaise
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_CalmMindStatRaise
	goto BattleScript_CantRaiseMultipleStats

BattleScript_EffectTripleArrows::
	setmoveeffect MOVE_EFFECT_TRIPLE_ARROWS
	goto BattleScript_EffectHit

BattleScript_EffectRevivalBlessing::
	attackcanceler
	attackstring
	ppreduce
	tryrevivalblessing BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNREVIVEDREADYTOFIGHT
	waitmessage B_WAIT_TIME_LONG
    jumpifbyte CMP_EQUAL, gBattleCommunication, TRUE, BattleScript_EffectRevivalBlessingSendOut
	goto BattleScript_MoveEnd

BattleScript_EffectRevivalBlessingSendOut:
    switchinanim BS_SCRIPTING, FALSE
	waitstate
	switchineffects BS_SCRIPTING
    goto BattleScript_MoveEnd

BattleScript_StealthRockActivates::
	setstealthrock BattleScript_MoveEnd
	printfromtable gDmgHazardsStringIds
	waitmessage B_WAIT_TIME_LONG
	return
BattleScript_ToxicSpikesActivates::
	settoxicspikes BattleScript_MoveEnd
	printstring STRINGID_POISONSPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectDireClaw::
	setmoveeffect MOVE_EFFECT_DIRE_CLAW
	goto BattleScript_EffectHit

BattleScript_EffectHitSetEntryHazard::
	argumenttomoveeffect
	goto BattleScript_EffectHit

BattleScript_SpikesActivates::
	trysetspikes BS_TARGET, BattleScript_MoveEnd
	printfromtable gDmgHazardsStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectAttackUpUserAlly:
	jumpifnoally BS_ATTACKER, BattleScript_EffectAttackUp
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_NOT_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_EffectAttackUpUserAlly_Works
	jumpifstat BS_ATTACKER_PARTNER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_ButItFailed
BattleScript_EffectAttackUpUserAlly_Works:
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_EffectAttackUpUserAlly_TryAlly
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectAttackUpUserAllyUser_PrintString
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_EffectAttackUpUserAllyUser_PrintString:
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectAttackUpUserAlly_TryAlly:
	setallytonexttarget BattleScript_EffectAttackUpUserAlly_TryAlly_
BattleScript_EffectAttackUpUserAlly_End:
	goto BattleScript_MoveEnd
BattleScript_EffectAttackUpUserAlly_TryAlly_:
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectAttackUpUserAlly_End
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectAttackUpUserAlly_AllyAnim
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectAttackUpUserAlly_End
BattleScript_EffectAttackUpUserAlly_AllyAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectAttackUpUserAlly_End

BattleScript_EffectTeatime::
	attackcanceler
	attackstring
	ppreduce
	jumpifteanoberry BattleScript_ButItFailed
@ at least one battler is affected
	attackanimation
	waitanimation
	setbyte gBattlerTarget, 0
BattleScript_TeatimeLoop:
	jumpifrodaffected BS_TARGET, BattleScript_Teatimerod
	jumpifabsorbaffected BS_TARGET, BattleScript_Teatimesorb
	jumpifmotoraffected BS_TARGET, BattleScript_Teatimemotor
	jumpifteainvulnerable BS_TARGET, BattleScript_Teatimevul @ in semi-invulnerable state OR held item is not a Berry
	orword gHitMarker, HITMARKER_NO_ANIMATIONS | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	setbyte sBERRY_OVERRIDE, TRUE   @ override the requirements for eating berries
	consumeberry BS_TARGET, TRUE  @ consume the berry, then restore the item from changedItems
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	setbyte sBERRY_OVERRIDE, FALSE
	removeitem BS_TARGET
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVEEND_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_Teatimevul:
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVEEND_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_Teatimesorb:
	call BattleScript_AbilityPopUpTarget
	tryhealquarterhealth BS_TARGET BattleScript_Teatimesorb_end
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_Teatimesorb_end:
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVEEND_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_Teatimerod:
	call BattleScript_AbilityPopUpTarget
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_TeatimeBuffer
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_TeatimeBuffer
	printfromtable gStatUpStringIds
	waitmessage 0x40
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVEEND_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_Teatimemotor:
	call BattleScript_AbilityPopUpTarget
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_TeatimeBuffer
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_TeatimeBuffer
	printfromtable gStatUpStringIds
	waitmessage 0x40
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVEEND_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_TeatimeBuffer:
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVEEND_CLEAR_BITS
	goto BattleScript_MoveEnd

BattleScript_AffectionBasedEndurance::
	playanimation BS_TARGET, B_ANIM_AFFECTION_HANGED_ON
	printstring STRINGID_TARGETTOUGHEDITOUT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AffectionBasedStatusHeal::
	jumpifstatus BS_ATTACKER, STATUS1_POISON | STATUS1_TOXIC_POISON, BattleScript_AffectionBasedStatus_HealPoisonString
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP_ANY, BattleScript_AffectionBasedStatus_HealSleepString
	jumpifstatus BS_ATTACKER, STATUS1_PARALYSIS, BattleScript_AffectionBasedStatus_HealParalysisString
	jumpifstatus BS_ATTACKER, STATUS1_BURN, BattleScript_AffectionBasedStatus_HealBurnString
	jumpifstatus BS_ATTACKER, STATUS1_FREEZE, BattleScript_AffectionBasedStatus_HealFreezeString
	jumpifstatus BS_ATTACKER, STATUS1_FROSTBITE, BattleScript_AffectionBasedStatus_HealFrostbiteString
	end2
BattleScript_AffectionBasedStatus_HealPoisonString:
	printstring STRINGID_ATTACKEREXPELLEDTHEPOISON
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealSleepString:
	printstring STRINGID_ATTACKERSHOOKITSELFAWAKE
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealParalysisString:
	printstring STRINGID_ATTACKERBROKETHROUGHPARALYSIS
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealBurnString:
	printstring STRINGID_ATTACKERHEALEDITSBURN
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealFreezeString:
	printstring STRINGID_ATTACKERMELTEDTHEICE
	goto BattleScript_AffectionBasedStatusHeal_Continue
BattleScript_AffectionBasedStatus_HealFrostbiteString:
	printstring STRINGID_ATTACKERHEALEDITSFROSTBITE
BattleScript_AffectionBasedStatusHeal_Continue:
	waitmessage B_WAIT_TIME_LONG
	clearstatus BS_ATTACKER
	waitstate
	updatestatusicon BS_ATTACKER
	waitstate
	end2

BattleScript_ShellTrapSetUp::
	printstring STRINGID_EMPTYSTRING3
	waitmessage 0x1
	playanimation BS_ATTACKER, B_ANIM_SHELL_TRAP_SETUP, NULL
	printstring STRINGID_PREPARESHELLTRAP
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_EffectShellTrap::
	attackcanceler
	jumpifshelltrap BS_ATTACKER, BattleScript_HitFromAccCheck
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING | HITMARKER_NO_PPDEDUCT, BattleScript_MoveEnd
	ppreduce
	printstring STRINGID_SHELLTRAPDIDNTWORK
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectChloroblast::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ChloroblastMiss, ACC_CURR_MOVE
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_ChloroblastAfterSelfDamage
	jumpifability BS_ATTACKER, ABILITY_SUGAR_COAT, BattleScript_ChloroblastAfterSelfDamage
	jumpifterucharmprotected BS_ATTACKER, BattleScript_ChloroblastAfterSelfDamage
	call BattleScript_ChloroblastSelfDamage
BattleScript_ChloroblastAfterSelfDamage::
	waitstate
	tryfaintmon BS_ATTACKER
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd
BattleScript_ChloroblastMiss::
	pause B_WAIT_TIME_SHORT
	effectivenesssound
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_MoveEnd
	jumpifability BS_ATTACKER, ABILITY_SUGAR_COAT, BattleScript_MoveEnd
	jumpifterucharmprotected BS_ATTACKER, BattleScript_MoveEnd
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED
	call BattleScript_ChloroblastSelfDamage
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	goto BattleScript_ChloroblastAfterSelfDamage
BattleScript_ChloroblastSelfDamage::
	dmg_1_2_attackerhp
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	return

BattleScript_EffectCourtChange::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	swapsidestatuses
	attackanimation
	waitanimation
	printstring STRINGID_COURTCHANGE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_BeakBlastSetUp::
	setbeakblast BS_ATTACKER
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	playanimation BS_ATTACKER, B_ANIM_BEAK_BLAST_SETUP, NULL
	printstring STRINGID_HEATUPBEAK
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_BeakBlastBurn::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectBurn
	return

BattleScript_EffectMeteorBeam::
	@ DecideTurn
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	jumpifmove MOVE_METEOR_BEAM, BattleScript_SetStringMeteorBeam
	jumpifmove MOVE_ELECTRO_SHOT, BattleScript_SetStringElectroShock
BattleScript_TryCharging:
	call BattleScript_FirstChargingTurnMeteorBeam
	goto BattleScript_TryMeteorBeam
BattleScript_TryMeteorBeam:
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_TwoTurnMovesSecondTurn

BattleScript_SetStringMeteorBeam:
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_METEOR_BEAM
	goto BattleScript_TryCharging

BattleScript_SetStringElectroShock:
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_ELECTRO_SHOCK
	goto BattleScript_TryCharging

BattleScript_FirstChargingTurnMeteorBeam::
	attackcanceler
	printstring STRINGID_EMPTYSTRING3
	ppreduce
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_CHARGING
	setmoveeffect MOVE_EFFECT_CHARGING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	copybyte cMULTISTRING_CHOOSER, sTWOTURN_STRINGID
	printfromtable gFirstTurnOfTwoStringIds
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_SP_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	seteffectsecondary
	return

BattleScript_EffectSkyDrop:
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_SkyDropTurn2
	attackcanceler
	ppreduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpiftargetally BattleScript_ButItFailed
	jumpifunder200 BS_TARGET, BattleScript_SkyDropWork
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_TARGETTOOHEAVY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SkyDropWork:
	setskydrop
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_SKY_DROP
	setsemiinvulnerablebit
	call BattleScriptFirstChargingTurnAfterAttackString
	goto BattleScript_MoveEnd
BattleScript_SkyDropTurn2:
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 0x1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	clearsemiinvulnerablebit
	attackstring
	clearskydrop BattleScript_SkyDropChangedTarget
	jumpiftype BS_TARGET, TYPE_FLYING, BattleScript_SkyDropFlyingType
	goto BattleScript_HitFromCritCalc
BattleScript_SkyDropFlyingType:
	makevisible BS_TARGET
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	makevisible BS_ATTACKER
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_SkyDropFlyingAlreadyConfused
	jumpifstatus2 BS_TARGET, STATUS2_LOCK_CONFUSE, BattleScript_SkyDropFlyingConfuseLock
	goto BattleScript_MoveEnd
BattleScript_SkyDropChangedTarget:
	pause B_WAIT_TIME_SHORT
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	makevisible BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_SkyDropFlyingConfuseLock:
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
BattleScript_SkyDropFlyingAlreadyConfused:
	setmoveeffect MOVE_EFFECT_THRASH
	clearstatusfromeffect BS_TARGET
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_MoveEnd
	setbyte BS_ATTACKER, BS_TARGET
	goto BattleScript_ThrashConfuses

BattleScript_EffectFling:
	attackcanceler
	jumpifcantfling BS_ATTACKER, BattleScript_FailedFromAtkString
	setlastuseditem BS_ATTACKER
	removeitem BS_ATTACKER
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNFLUNG
	waitmessage B_WAIT_TIME_SHORT
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_MED
	resultmessage
	waitmessage B_WAIT_TIME_MED
	jumpiflastuseditemberry BattleScript_EffectFlingConsumeBerry
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_FLAME_ORB, BattleScript_FlingFlameOrb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_FLINCH, BattleScript_FlingFlinch
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_LIGHT_BALL, BattleScript_FlingLightBall
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_MENTAL_HERB, BattleScript_FlingMentalHerb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_POISON_POWER, BattleScript_FlingPoisonBarb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_TOXIC_ORB, BattleScript_FlingToxicOrb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_RESTORE_STATS, BattleScript_FlingWhiteHerb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_FROST_ORB, BattleScript_FlingFrostOrb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_POISON_ORB, BattleScript_FlingPoisonOrb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_BLOOM_ORB, BattleScript_FlingBloomOrb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_PANIC_ORB, BattleScript_FlingPanicOrb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_BLACK_SALAD, BattleScript_FlingBloomOrb
BattleScript_EffectFlingConsumeBerry:
	savebattleritem BS_TARGET
	battleritemtolastuseditem BS_TARGET
	setbyte sBERRY_OVERRIDE, 1 @ override the requirements for eating berries
	orword gHitMarker, HITMARKER_NO_ANIMATIONS
	consumeberry BS_TARGET, TRUE
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, 0
	restorebattleritem BS_TARGET
BattleScript_FlingEnd:
	tryfaintmon BS_TARGET
	trysymbiosis
	goto BattleScript_MoveEnd

BattleScript_FlingFailConsumeItem::
	removeitem BS_ATTACKER
	goto BattleScript_FailedFromAtkString

BattleScript_FlingFlameOrb:
	setmoveeffect MOVE_EFFECT_BURN
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingFlinch:
	setmoveeffect MOVE_EFFECT_FLINCH
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingLightBall:
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingMentalHerb:
	curecertainstatuses BS_TARGET
	savetarget
	copybyte gBattlerAttacker, gBattlerTarget
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, NULL
	printfromtable gMentalHerbCureStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	restoretarget
	goto BattleScript_FlingEnd
BattleScript_FlingPoisonBarb:
	setmoveeffect MOVE_EFFECT_POISON
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingToxicOrb:
	setmoveeffect MOVE_EFFECT_TOXIC
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingWhiteHerb:
	tryresetnegativestatstages BS_TARGET
	swapattackerwithtarget
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_MED
	swapattackerwithtarget
	goto BattleScript_FlingEnd
BattleScript_FlingFrostOrb:
	setmoveeffect MOVE_EFFECT_FROSTBITE
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingPoisonOrb:
	setmoveeffect MOVE_EFFECT_POISON
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingBloomOrb:
	setmoveeffect MOVE_EFFECT_BLOOMING
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingPanicOrb:
	setmoveeffect MOVE_EFFECT_PANIC
	seteffectprimary
	goto BattleScript_FlingEnd

BattleScript_EffectShellSideArm:
	shellsidearmcheck
	setmoveeffect MOVE_EFFECT_POISON
	goto BattleScript_EffectHit

BattleScript_EffectPhotonGeyser:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	photongeysercheck BS_ATTACKER
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectAuraWheel: @ Aura Wheel can only be used by Morpeko
	jumpifspecies BS_ATTACKER, SPECIES_MORPEKO, BattleScript_EffectSpeedUpHit
	jumpifspecies BS_ATTACKER, SPECIES_MORPEKO_HANGRY, BattleScript_EffectSpeedUpHit
	goto BattleScript_PokemonCantUseTheMove

BattleScript_EffectClangorousSoul:
	attackcanceler
	attackstring
	ppreduce
	cutonethirdhpraisestats BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_SKIP_DMG_TRACK | HITMARKER_PASSIVE_DAMAGE | HITMARKER_IGNORE_DISGUISE
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	call BattleScript_AllStatsUp
	goto BattleScript_MoveEnd

BattleScript_EffectOctolock:
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setoctolock BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_OctolockEndTurn::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPDEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_OctolockTryLowerSpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_OctolockTryLowerSpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_OctolockTurnDmgEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_OctolockTurnDmgEnd:
	end2

BattleScript_EffectPoltergeist:
	attackcanceler
	attackstring
	ppreduce
	checkpoltergeist BS_TARGET, BattleScript_ButItFailed
	printstring STRINGID_ABOUTTOUSEPOLTERGEIST
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc

BattleScript_EffectTarShot:
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	cantarshotwork BS_TARGET, BattleScript_FailedFromAtkString
	attackstring
	ppreduce
	setstatchanger STAT_SPEED, 1, TRUE
	attackanimation
	waitanimation
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_TryTarShot
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryTarShot:
	trytarshot BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_PKMNBECAMEWEAKERTOFIRE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectNoRetreat:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	trynoretreat BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	call BattleScript_AllStatsUp
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_CANTESCAPEDUETOUSEDMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectJawLock:
	setmoveeffect MOVE_EFFECT_TRAP_BOTH | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_BothCanNoLongerEscape::
	printstring STRINGID_BOTHCANNOLONGERESCAPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectHyperspaceFury:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setmoveeffect MOVE_EFFECT_FEINT
	seteffectwithchance
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_HitFromCritCalc

BattleScript_ButHoopaCantUseIt:
	printstring STRINGID_BUTHOOPACANTUSEIT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_HyperspaceFuryRemoveProtect::
	printstring STRINGID_BROKETHROUGHPROTECTION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectPlasmaFists:
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	tryfaintmon BS_TARGET
	applyplasmafists
	printstring STRINGID_IONDELUGEON
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSparklySwirl:
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	healpartystatus
	waitstate
	updatestatusicon BS_ATTACKER_WITH_PARTNER
	waitstate
	goto BattleScript_MoveEnd

BattleScript_EffectFreezyFrost:
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	normalisebuffs
	printstring STRINGID_STATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSappySeed:
	jumpifstatus3 BS_TARGET, STATUS3_LEECHSEED, BattleScript_EffectHit
	call BattleScript_EffectHit_Ret
	jumpifhalfword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_NO_EFFECT, BattleScript_MoveEnd
	tryfaintmon BS_TARGET
	jumpifhasnohp BS_TARGET, BattleScript_MoveEnd
	setseeded
	printfromtable gLeechSeedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectBaddyBad:
	jumpifsideaffecting BS_ATTACKER, SIDE_STATUS_REFLECT, BattleScript_EffectHit
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifbattleend BattleScript_MoveEnd
	setreflect
	printfromtable gReflectLightScreenSafeguardStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGlitzyGlow:
	jumpifsideaffecting BS_ATTACKER, SIDE_STATUS_LIGHTSCREEN, BattleScript_EffectHit
	call BattleScript_EffectHit_Ret
	jumpifhalfword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_NO_EFFECT, BattleScript_MoveEnd
	tryfaintmon BS_TARGET
	setlightscreen
	printfromtable gReflectLightScreenSafeguardStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectEvasionUpHit:
	setmoveeffect MOVE_EFFECT_EVS_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectStuffCheeks::
	attackcanceler
	attackstring
	ppreduce
	jumpifnotberry BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
BattleScript_StuffCheeksEatBerry:
	setbyte sBERRY_OVERRIDE, 1
	orword gHitMarker, HITMARKER_NO_ANIMATIONS
	consumeberry BS_ATTACKER, TRUE
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, 0
	removeitem BS_ATTACKER
	jumpifmove MOVE_WARM_WELCOME, BattleScript_StuffCheeksEnd 
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_StuffCheeksEnd
	setgraphicalstatchangevalues
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_StuffCheeksEnd @ cant raise def
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StuffCheeksEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectDecorate:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, 12, BattleScript_DecorateBoost
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPATK, 12, BattleScript_DecorateBoost
	goto BattleScript_ButItFailed
BattleScript_DecorateBoost:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, 0x0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_DecorateBoostSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_DecorateBoostSpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DecorateBoostSpAtk:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCoaching::
	attackcanceler
	attackstring
	ppreduce
	jumpifnoally BS_ATTACKER, BattleScript_ButItFailed
	copybyte gBattlerTarget, gBattlerAttacker
	setallytonexttarget EffectCoaching_CheckAllyStats
	goto BattleScript_ButItFailed
EffectCoaching_CheckAllyStats:
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CoachingWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_DEF, MAX_STAT_STAGE, BattleScript_CoachingWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ACC, MAX_STAT_STAGE, BattleScript_CoachingWorks
	jumpifstatus2 BS_TARGET, STATUS2_FOCUS_ENERGY_ANY, BattleScript_ButItFailed
	goto Battlescript_CoachingTryFocusEnergy   @ ally at max atk, def
BattleScript_CoachingWorks:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF | BIT_ACC, 0x0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_CoachingBoostDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_CoachingBoostDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoachingBoostDef:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_CoachingBoostAcc
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_CoachingBoostAcc
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoachingBoostAcc:
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_CoachingEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_CoachingEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoachingEnd:
	jumpifstatus2 BS_TARGET, STATUS2_FOCUS_ENERGY_ANY, BattleScript_MoveEnd
	setfocusenergy BS_TARGET
	printfromtable gFocusEnergyUsedStringIds
	goto BattleScript_MoveEnd
Battlescript_CoachingTryFocusEnergy::
	setfocusenergy BS_TARGET
	attackanimation
	waitanimation
	printfromtable gFocusEnergyUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectJungleHealing:
	attackcanceler
	attackstring
	ppreduce
	jumpifteamhealthy BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	copybyte gBattlerTarget, gBattlerAttacker
	setbyte gBattleCommunication, 0
JungleHealing_RestoreTargetHealth:
	copybyte gBattlerAttacker, gBattlerTarget
	tryhealthirdhealth BS_TARGET, BattleScript_JungleHealing_TryCureStatus
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_JungleHealing_TryCureStatus:
	jumpifmove MOVE_LIFE_DEW, BattleScript_JungleHealingTryRestoreAlly  @ life dew only heals
	jumpifstatus BS_TARGET, STATUS1_ANY_NEGATIVE, BattleScript_JungleHealingCureStatus
	goto BattleScript_JungleHealingTryRestoreAlly
BattleScript_JungleHealingCureStatus:
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
BattleScript_JungleHealingTryRestoreAlly:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_MoveEnd
	addbyte gBattleCommunication, 1
	jumpifnoally BS_TARGET, BattleScript_MoveEnd
	setallytonexttarget JungleHealing_RestoreTargetHealth
	goto BattleScript_MoveEnd

BattleScript_EffectAttackerDefenseDownHit::
	jumpifdoublesmovesucceed BS_ATTACKER, BattleScript_NoMoveEffect
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
    call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_DoublesSkipEffect
	setdoublesmovesucceed BS_ATTACKER
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd
BattleScript_NoMoveEffect:
	setmoveeffect 0
	goto BattleScript_EffectHit

BattleScript_EffectRelicSong:
	setmoveeffect MOVE_EFFECT_RELIC_SONG | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	argumentstatuseffect
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectAllySwitch:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifnoally BS_ATTACKER, BattleScript_ButItFailed
	allyswitchfailchance BattleScript_ButItFailed
	attackanimation
	waitanimation
	@ The actual data/gfx swap happens in the move animation. Here it's just the gBattlerAttacker / scripting battler change
	allyswitchswapbattlers
	printstring STRINGID_ALLYSWITCHPOSITION
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFairyLock:
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	trysetfairylock BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectBurnUp:
	attackcanceler
	attackstring
	ppreduce
	jumpiftype BS_ATTACKER, TYPE_FIRE, BattleScript_BurnUpWorks
	goto BattleScript_ButItFailed

BattleScript_BurnUpWorks:
	setmoveeffect MOVE_EFFECT_BURN_UP | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

BattleScript_BurnUpRemoveType::
	losetype BS_ATTACKER, TYPE_FIRE
	printstring STRINGID_ATTACKERLOSTFIRETYPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectDoubleShock::
	jumpifdoublesmovesucceed BS_ATTACKER, BattleScript_NoMoveEffect
	jumpifstatus4 BS_ATTACKER, STATUS4_SUPERCHARGED, BattleScript_DoubleShockCheckGearedUp
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_EffectHit
	attackcanceler
	attackstring
	ppreduce
	jumpiftype BS_ATTACKER, TYPE_ELECTRIC, BattleScript_DoubleShockWorks
	goto BattleScript_ButItFailed
BattleScript_DoubleShockWorks:
	setmoveeffect MOVE_EFFECT_DOUBLE_SHOCK | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	jumpifmovehadnoeffect BattleScript_DoublesSkipEffect
	setdoublesmovesucceed BS_ATTACKER
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd
BattleScript_DoubleShockRemoveType::
	losetype BS_ATTACKER, TYPE_ELECTRIC
	printstring STRINGID_ATTACKERLOSTELECTRICTYPE
	waitmessage B_WAIT_TIME_LONG
	return
BattleScript_DoubleShockCheckGearedUp:
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_EffectExplosion
	goto BattleScript_EffectHit

BattleScript_DefDown::
	modifybattlerstatstage BS_TARGET, STAT_DEF, DECREASE, 1, BattleScript_DefDown_Ret, ANIM_ON
BattleScript_DefDown_Ret:
	return

BattleScript_AtkDownAgain::
	modifybattlerstatstage BS_TARGET, STAT_SPATK, DECREASE, 1, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_SpeedDown::
	modifybattlerstatstage BS_TARGET, STAT_SPEED, DECREASE, 1, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_SpAtkDown::
	modifybattlerstatstage BS_TARGET, STAT_SPATK, DECREASE, 1, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_EvaDown::
	modifybattlerstatstage BS_TARGET, STAT_EVASION, DECREASE, 1, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_SpDefDown::
	modifybattlerstatstage BS_TARGET, STAT_SPDEF, DECREASE, 1, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_AccDownAgain::
	modifybattlerstatstage BS_TARGET, STAT_ACC, DECREASE, 1, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_AccDown2::
	modifybattlerstatstage BS_TARGET, STAT_ACC, DECREASE, 2, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_AtkDown2Again::
	modifybattlerstatstage BS_TARGET, STAT_ATK, DECREASE, 2, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_DefDown2::
	modifybattlerstatstage BS_TARGET, STAT_DEF, DECREASE, 2, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_SpAtkDown2Again::
	modifybattlerstatstage BS_TARGET, STAT_SPATK, DECREASE, 2, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_SpDefDown2::
	modifybattlerstatstage BS_TARGET, STAT_SPDEF, DECREASE, 2, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_SpeedDown2::
	modifybattlerstatstage BS_TARGET, STAT_SPEED, DECREASE, 2, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_EvaDown2::
	modifybattlerstatstage BS_TARGET, STAT_EVASION, DECREASE, 2, BattleScript_DefDown_Ret, ANIM_ON
	return

BattleScript_AtkRaise1OU::
	playstatchangeanimation BS_ATTACKER, BIT_ATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkRaise1OURet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkRaise1OURet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkRaise1OURet::
	return

BattleScript_DefRaise1OU::
	playstatchangeanimation BS_ATTACKER, BIT_DEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkRaise1OURet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkRaise1OURet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SpAtkRaise1OU::
	playstatchangeanimation BS_ATTACKER, BIT_SPATK, 0
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkRaise1OURet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkRaise1OURet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SpDefRaise1OU::
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, 0
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkRaise1OURet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkRaise1OURet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SpeedRaise1OU::
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, 0
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkRaise1OURet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkRaise1OURet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_TauntString::
	printstring STRINGID_PKMNFELLFORTAUNT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTauntAttacker
	return

BattleScript_TormentString::
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker
	return

BattleScript_TormentTauntString::
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNFELLFORTAUNT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker
	call BattleScript_TryDestinyKnotTauntAttacker
	return

BattleScript_EffectPurify:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstatus BS_TARGET, STATUS1_ANY_NEGATIVE, BattleScript_PurifyWorks
	goto BattleScript_ButItFailed
BattleScript_PurifyWorks:
	attackanimation
	waitanimation
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
	printstring STRINGID_ATTACKERCUREDTARGETSTATUS
	waitmessage B_WAIT_TIME_LONG
	tryhealallhealth BS_ATTACKER, BattleScript_AlreadyAtFullHp
	goto BattleScript_RestoreHp

BattleScript_EffectStrengthSap:
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_StrengthSapQuash
	setstatchanger STAT_ATK, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, MIN_STAT_STAGE, BattleScript_StrengthSapTryLower
	pause B_WAIT_TIME_SHORT
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_StrengthSapTryLower:
	getstatvalue BS_TARGET, STAT_ATK
	jumpiffullhp BS_ATTACKER, BattleScript_StrengthSapMustLower
	attackanimation
	waitanimation
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_StrengthSapHp
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_StrengthSapHp
BattleScript_StrengthSapLower:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
@ Drain HP without lowering a stat
BattleScript_StrengthSapHp:
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_StrengthSapManipulateDmg
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_MoveEnd
	jumpiffullhp BS_ATTACKER, BattleScript_MoveEnd
BattleScript_StrengthSapManipulateDmg:
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_StrengthSapLiquidOoze
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNENERGYDRAINED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_StrengthSapLiquidOoze:
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd
BattleScript_StrengthSapMustLower:
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_MoveEnd
	attackanimation
	waitanimation
	goto BattleScript_StrengthSapLower
BattleScript_StrengthSapQuash:
	jumpiffullhp BS_ATTACKER, BattleScript_StrengthSapJustQuash
BattleScript_EffectStrengthSapQuashContinue:
	setstatchanger STAT_SPEED, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_StrengthSapQuashTryLower
	pause B_WAIT_TIME_SHORT
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_StrengthSapQuashAfterPPReduce
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_StrengthSapQuashAfterPPReduce
BattleScript_StrengthSapQuashTryLower:
	getstatvalue BS_TARGET, STAT_SPEED
	jumpiffullhp BS_ATTACKER, BattleScript_StrengthSapQuashMustLower
	attackanimation
	waitanimation
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_StrengthSapQuashHp
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_StrengthSapQuashHp
BattleScript_StrengthSapQuashLower:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
@ Drain HP without lowering a stat
BattleScript_StrengthSapQuashHp:
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_StrengthSapQuashManipulateDmg
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_StrengthSapQuashAfterAnimation
	jumpiffullhp BS_ATTACKER, BattleScript_StrengthSapQuashAfterAnimation
BattleScript_StrengthSapQuashManipulateDmg:
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_StrengthSapQuashLiquidOoze
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNENERGYDRAINED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_StrengthSapQuashAfterAnimation
BattleScript_StrengthSapQuashLiquidOoze:
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_StrengthSapQuashAfterAnimation
BattleScript_StrengthSapQuashMustLower:
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_StrengthSapQuashAfterPPReduce
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_StrengthSapQuashAfterPPReduce
	attackanimation
	waitanimation
	goto BattleScript_StrengthSapQuashLower
BattleScript_StrengthSapJustQuash:
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_EffectStrengthSapQuashContinue
	tryquash BattleScript_EffectStrengthSapQuashContinue
BattleScript_StrengthSapJustQuashWorks:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring STRINGID_QUASHSUCCESS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_StrengthSapQuashAfterPPReduce:
	tryquash BattleScript_MoveEnd
	attackanimation
	waitanimation
	printstring STRINGID_QUASHSUCCESS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_StrengthSapQuashAfterAnimation:
	tryquash BattleScript_MoveEnd
	printstring STRINGID_QUASHSUCCESS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectBugBite:
	setmoveeffect MOVE_EFFECT_BUG_BITE
	jumpifmove MOVE_DINE_N_DASH, BattleScript_EffectHitEscape
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	seteffectprimary
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifsubstituteblocks BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_REMOVE_STATUS
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectIncinerate:
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_INCINERATE | MOVE_EFFECT_CERTAIN
	seteffectprimary
	jumpifsubstituteblocks BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_REMOVE_STATUS | MOVE_EFFECT_CERTAIN
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_MoveEffectIncinerate::
	printstring STRINGID_INCINERATEBURN
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectBugBite::
	printstring STRINGID_BUGBITE
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, 1   @ override the requirements for eating berries
	savetarget
	consumeberry BS_ATTACKER, FALSE
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, 0
	trysymbiosis
	restoretarget
	return

BattleScript_EffectCoreEnforcer:
	setmoveeffect MOVE_EFFECT_CORE_ENFORCER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_MoveEffectCoreEnforcer::
	setgastroacid BattleScript_CoreEnforcerRet
	printstring STRINGID_PKMNSABILITYSUPPRESSED
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	tryrevertweatherform
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
BattleScript_CoreEnforcerRet:
	return

BattleScript_EffectLaserFocus:
	jumpifnodamage BattleScript_EffectLaserFocusAttackUp
	attackcanceler
	attackstring
	ppreduce
	setuserstatus3 STATUS3_LASER_FOCUS, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_LASERFOCUS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectLaserFocusAttackUp:
	setstatchanger STAT_ATK, 2, FALSE
	attackcanceler
	attackstring
	ppreduce
	setuserstatus3 STATUS3_LASER_FOCUS, BattleScript_ButItFailed
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_LaserFocusStatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_LaserFocusAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_LaserFocusStatUpPrintString
BattleScript_LaserFocusAnim:
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_LaserFocusStatUpPrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_LASERFOCUS
	waitmessage B_WAIT_TIME_LONG
BattleScript_LaserFocusStatUpEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectVCreate:
	setmoveeffect MOVE_EFFECT_V_CREATE | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_VCreateStatLoss::
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_VCreateStatAnim
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_VCreateStatAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_VCreateStatLossRet
BattleScript_VCreateStatAnim:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF | BIT_SPEED, STAT_CHANGE_NEGATIVE | STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, BattleScript_VCreateTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VCreateTrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VCreateTrySpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, BattleScript_VCreateTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VCreateTrySpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VCreateTrySpeed:
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, BattleScript_VCreateStatLossRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VCreateStatLossRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VCreateStatLossRet:
	return

BattleScript_SpectralThiefSteal::
	printstring STRINGID_SPECTRALTHIEFSTEAL
	waitmessage B_WAIT_TIME_LONG
	setbyte sB_ANIM_ARG2, 0
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	spectralthiefprintstats
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	goto BattleScript_EffectSpectralThiefFromDamage

BattleScript_EffectSpectralThief::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	tryspectralthiefsteal BattleScript_SpectralThiefSteal
BattleScript_EffectSpectralThiefFromDamage:
	critcalc
	damagecalc
	adjustdamage
	call BattleScript_Hit_RetFromAtkAnimation
	tryfaintmon BS_TARGET
	moveendall
	end

BattleScript_EffectPartingShot::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_EffectPartingShotTryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_EffectPartingShotTryAtk:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectPartingShotTrySpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectPartingShotTrySpAtk:
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectPartingShotSwitch
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectPartingShotSwitch:
	moveendall
	goto BattleScript_MoveSwitch
BattleScript_PartingShotEnd:
	end

BattleScript_EffectSpAtkUpHit:
	setmoveeffect MOVE_EFFECT_SP_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectPowder:
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_ACC, MIN_STAT_STAGE, BattleScript_EffectPowderJustPowder
	setstatchanger STAT_ACC, 1, TRUE
	jumpifstatus2 BS_TARGET, STATUS2_POWDER, BattleScript_EffectStatDown
	setpowder BS_TARGET
	call BattleScript_EffectStatDown_Ret
	printstring STRINGID_COVEREDINPOWDER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectPowderJustPowder::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_POWDER, BattleScript_ButItFailed
	setpowder BS_TARGET
	attackanimation
	waitanimation
	printstring STRINGID_COVEREDINPOWDER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectStatDown_Ret:
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
BattleScript_StatDownFromAttackString_Ret:
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_StatDownReturn
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_StatDownDoAnim_Ret
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_StatDownReturn
	pause B_WAIT_TIME_SHORT
	goto BattleScript_StatDownPrintString_Ret
BattleScript_StatDownDoAnim_Ret::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StatDownPrintString_Ret::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StatDownReturn::
	return

BattleScript_EffectAromaticMist:
	jumpifbattletype BATTLE_TYPE_DOUBLE, BattleScript_AromaticMistDoubles
	jumpifterrainaffected BS_ATTACKER, STATUS_FIELD_MISTY_TERRAIN, BattleScript_EffectCalmMind
	goto BattleScript_EffectSpecialDefenseUp
BattleScript_AromaticMistDoubles:
	jumpifterrainaffected BS_TARGET, STATUS_FIELD_MISTY_TERRAIN, BattleScript_AromaticMistDoublesMistyTerrain
	attackcanceler
	attackstring
	ppreduce
	setbyte gBattleCommunication, 0
BattleScript_EffectAromaticMistDoublesCheckStats:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_EffectAromaticMistDoublesTryAtk
BattleScript_EffectAromaticMistDoublesTryAtk:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_EffectAromaticMistDoublesSkipAnim
	attackanimation
	waitanimation
BattleScript_EffectAromaticMistDoublesSkipAnim:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_SPDEF | BIT_SPATK, 0
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectAromaticMistDoublesLoop
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectAromaticMistDoublesLoop
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectAromaticMistDoublesLoop:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectAromaticMistDoublesEnd
	setallytonexttarget BattleScript_EffectAromaticMistDoublesCheckStats
BattleScript_EffectAromaticMistDoublesEnd:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed
BattleScript_AromaticMistDoublesMistyTerrain:
	attackcanceler
	attackstring
	ppreduce
	setbyte gBattleCommunication, 0
BattleScript_EffectAromaticMistDoublesMistyTerrainCheckStats:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_EffectAromaticMistDoublesMistyTerrainTryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_EffectAromaticMistDoublesMistyTerrainLoop
BattleScript_EffectAromaticMistDoublesMistyTerrainTryAtk:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_EffectAromaticMistDoublesMistyTerrainSkipAnim
	attackanimation
	waitanimation
BattleScript_EffectAromaticMistDoublesMistyTerrainSkipAnim:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_SPDEF | BIT_SPATK, 0
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectAromaticMistDoublesMistyTerrainTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectAromaticMistDoublesMistyTerrainTrySpAtk
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectAromaticMistDoublesMistyTerrainTrySpAtk:
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectAromaticMistDoublesMistyTerrainLoop
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectAromaticMistDoublesMistyTerrainLoop
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectAromaticMistDoublesMistyTerrainLoop:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectAromaticMistDoublesMistyTerrainEnd
	setallytonexttarget BattleScript_EffectAromaticMistDoublesMistyTerrainCheckStats
BattleScript_EffectAromaticMistDoublesMistyTerrainEnd:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed

BattleScript_EffectMagneticFlux::
	attackcanceler
	attackstring
	ppreduce
	setbyte gBattleCommunication, 0
BattleScript_EffectMagneticFluxStart:
	jumpifability BS_TARGET, ABILITY_MINUS, BattleScript_EffectMagneticFluxCheckStats
	jumpifability BS_TARGET, ABILITY_PLUS, BattleScript_EffectMagneticFluxCheckStats
	goto BattleScript_EffectMagneticFluxLoop
BattleScript_EffectMagneticFluxCheckStats:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_EffectMagneticFluxTryDef
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_EffectMagneticFluxLoop
BattleScript_EffectMagneticFluxTryDef:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_EffectMagneticFluxSkipAnim
	attackanimation
	waitanimation
BattleScript_EffectMagneticFluxSkipAnim:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectMagneticFluxTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectMagneticFluxTrySpDef
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectMagneticFluxTrySpDef:
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectMagneticFluxGettingSupercharged
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectMagneticFluxGettingSupercharged
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectMagneticFluxGettingSupercharged::
	applysupercharged BattleScript_EffectMagneticFluxLoop
	printstring STRINGID_TARGETBECOMESSUPERCHARGED
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectMagneticFluxLoop:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectMagneticFluxEnd
	setallytonexttarget BattleScript_EffectMagneticFluxStart
BattleScript_EffectMagneticFluxEnd:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed

BattleScript_EffectGearUp::
	attackcanceler
	attackstring
	ppreduce
	setbyte gBattleCommunication, 0
BattleScript_EffectGearUpStart:
	jumpifability BS_TARGET, ABILITY_MINUS, BattleScript_EffectGearUpCheckStats
	jumpifability BS_TARGET, ABILITY_PLUS, BattleScript_EffectGearUpCheckStats
	goto BattleScript_EffectGearUpLoop
BattleScript_EffectGearUpCheckStats:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_EffectGearUpTryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_EffectGearUpLoop
BattleScript_EffectGearUpTryAtk:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_EffectGearUpSkipAnim
	attackanimation
	waitanimation
BattleScript_EffectGearUpSkipAnim:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectGearUpTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectGearUpTrySpAtk
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectGearUpTrySpAtk:
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectGearUpGettingGearedUp
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectGearUpGettingGearedUp
	addbyte gBattleCommunication, 1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectGearUpGettingGearedUp:
	applygearedup BattleScript_EffectGearUpLoop
	printstring STRINGID_TARGETBECOMESGEAREDUP
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectGearUpLoop:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectGearUpEnd
	setallytonexttarget BattleScript_EffectGearUpStart
BattleScript_EffectGearUpEnd:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed

BattleScript_EffectAcupressure:
	attackcanceler
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectAcupressureTry
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_PrintMoveMissed
BattleScript_EffectAcupressureTry:
	attackstring
	ppreduce
	tryaccupressure BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	statbuffchange MOVE_EFFECT_CERTAIN, BattleScript_MoveEnd
	printstring STRINGID_DEFENDERSSTATROSE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCraftyShield:
	attackcanceler
	attackstring
	ppreduce
	applycraftyshield BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PROTECTEDDEFENDER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveEffectFeint::
	printstring STRINGID_FELLFORFEINT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectFeint:
	setmoveeffect MOVE_EFFECT_FEINT
	goto BattleScript_EffectHit

BattleScript_EffectThirdType:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	trysetthirdtype BS_TARGET, BattleScript_ButItFailed
	jumpifmove MOVE_TRICK_OR_TREAT, BattleScript_TrickorTreatSwapItems
	jumpifmove MOVE_FORESTS_CURSE, BattleScript_ForestsCurseCursing
	attackanimation
	waitanimation
	printstring STRINGID_THIRDTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_TrickorTreatSwapItems::
	jumpifsubstituteblocks BattleScript_GhostTypeContinue
	tryswapitems BattleScript_GhostTypeContinue
	attackanimation
	waitanimation
	printstring STRINGID_GHOSTTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNSWITCHEDITEMS
	waitmessage B_WAIT_TIME_LONG
	printfromtable gItemSwapStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_GhostTypeContinue::
	attackanimation
	waitanimation
	printstring STRINGID_GHOSTTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_ForestsCurseCursing::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_ForestsCurseCursingBlooming
	cursetarget BattleScript_GrassTypeContinue
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	setbyte sB_ANIM_TURN, 0
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_GRASSTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNLAIDCURSE
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd
BattleScript_GrassTypeContinue::
	attackanimation
	waitanimation
	printstring STRINGID_GRASSTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_ForestsCurseCursingBlooming::
	curestatuswithmove BS_ATTACKER, BattleScript_ForestsCurseCursingBloomingCureFailed
	printstring STRINGID_PKMNSISNOLONGERBLOOMING
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
BattleScript_ForestsCurseCursingBloomingCureFailed::
	cursetarget BattleScript_ForestCurseTryTrapping
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	setbyte sB_ANIM_TURN, 0
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_ForestsCurseOnlyCurse
	jumpifsubstituteblocks BattleScript_ForestsCurseOnlyCurse
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_ForestsCurseOnlyCurse
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_GRASSTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNLAIDCURSE
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd
BattleScript_ForestCurseTryTrapping::
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_GrassTypeContinue
	jumpifsubstituteblocks BattleScript_GrassTypeContinue
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_GrassTypeContinue
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_GRASSTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_ForestsCurseOnlyCurse::
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_GRASSTYPEADDED
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNLAIDCURSE
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectDefenseUp2Hit:
	setmoveeffect MOVE_EFFECT_DEF_PLUS_2 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectFlowerShield::
	attackcanceler
	attackstring
	ppreduce
	getrototillertargets BattleScript_ButItFailed
	@ at least one battler is affected
	attackanimation
	waitanimation
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_FlowerShieldLoop:
	movevaluescleanup
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_FlowerShieldCheckAffected
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_FlowerShieldCantRaiseMultipleStats
BattleScript_FlowerShieldCheckAffected:
	jumpiffainted BS_TARGET, TRUE, BattleScript_FlowerShieldMoveTargetEnd
	jumpifstatus BS_TARGET, STATUS1_BLOOMING, BattleScript_FlowerShieldNoEffect
	jumpifnotrototilleraffected BS_TARGET, BattleScript_FlowerShieldNoEffect
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_FlowerShieldTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_FlowerShieldTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FlowerShieldTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_FlowerShieldMoveTargetEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_FlowerShieldTryApplyBlooming
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FlowerShieldTryApplyBlooming::
	jumpiftype BS_TARGET, TYPE_FIRE, BattleScript_FlowerShieldMoveTargetEnd
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_FlowerShieldMoveTargetEnd
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_FlowerShieldMoveTargetEnd
	setmoveeffect MOVE_EFFECT_BLOOMING
	seteffectprimary
	goto BattleScript_FlowerShieldMoveTargetEnd
BattleScript_FlowerShieldMoveTargetEnd:
	moveendto MOVEEND_NEXT_TARGET
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_FlowerShieldLoop
	restoretarget
	end

BattleScript_FlowerShieldCantRaiseMultipleStats:
	copybyte gBattlerAttacker, gBattlerTarget
	printstring STRINGID_STATSWONTINCREASE2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_FlowerShieldTryApplyBlooming

BattleScript_FlowerShieldNoEffect:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_FlowerShieldMoveTargetEnd

BattleScript_EffectRototiller::
	attackcanceler
	attackstring
	ppreduce
	getrototillertargets BattleScript_ButItFailed
	@ at least one battler is affected
	attackanimation
	waitanimation
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_RototillerLoop:
	movevaluescleanup
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_RototillerCheckAffected
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_RototillerCantRaiseMultipleStats
BattleScript_RototillerCheckAffected:
	jumpiffainted BS_TARGET, TRUE, BattleScript_RototillerMoveTargetEnd
	jumpifstatus BS_TARGET, STATUS1_BLOOMING, BattleScript_RototillerNoEffect
	jumpifnotrototilleraffected BS_TARGET, BattleScript_RototillerNoEffect
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_RototillerTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_RototillerTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RototillerTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_RototillerTryApplyBlooming
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_RototillerTryApplyBlooming
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_RototillerTryApplyBlooming::
	jumpiftype BS_TARGET, TYPE_FIRE, BattleScript_RototillerMoveTargetEnd
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_RototillerMoveTargetEnd
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_RototillerMoveTargetEnd
	setmoveeffect MOVE_EFFECT_BLOOMING
	seteffectprimary
	goto BattleScript_RototillerMoveTargetEnd
BattleScript_RototillerMoveTargetEnd:
	moveendto MOVEEND_NEXT_TARGET
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_RototillerLoop
	restoretarget
	end

BattleScript_RototillerCantRaiseMultipleStats:
	copybyte gBattlerAttacker, gBattlerTarget
	printstring STRINGID_STATSWONTINCREASE2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_RototillerTryApplyBlooming

BattleScript_RototillerNoEffect:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_RototillerMoveTargetEnd

BattleScript_EffectBestow:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	jumpifnoally BS_ATTACKER, BattleScript_ButItFailed
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_BestowAttackSpAttackUpDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_Bestowing
BattleScript_Bestowing:
	jumpifsubstituteblocks BattleScript_ButItFailed
	trybestow BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_BESTOWITEMGIVING
	waitmessage B_WAIT_TIME_LONG
	trysymbiosis
	goto BattleScript_MoveEnd
BattleScript_BestowAttackSpAttackUpDoMoveAnim::
	jumpifsubstituteblocks BattleScript_ButItFailed
	trybestow BattleScript_ButItFailed
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_BestowAttackSpAttackUpTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_BestowAttackSpAttackUpTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_BestowAttackSpAttackUpTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_BestowAttackSpAttackUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_BestowAttackSpAttackUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_BestowAttackSpAttackUpEnd:
	printstring STRINGID_BESTOWITEMGIVING
	waitmessage B_WAIT_TIME_LONG
	trysymbiosis
	goto BattleScript_MoveEnd

BattleScript_EffectAfterYou:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryafteryou BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_KINDOFFER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFlameBurst:
	setmoveeffect MOVE_EFFECT_FLAME_BURST | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_MoveEffectFlameBurst::
	savetarget
	tryfaintmon BS_TARGET
	copybyte sBATTLER, sSAVED_BATTLER
	printstring STRINGID_BURSTINGFLAMESHIT
	waitmessage B_WAIT_TIME_LONG
	copybyte gBattlerTarget, sSAVED_BATTLER
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	tryfaintmon BS_TARGET
	restoretarget
	goto BattleScript_MoveEnd

BattleScript_EffectPowerTrick:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	powertrick BS_ATTACKER
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDATKANDDEF
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPsychoShift:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstatus BS_ATTACKER, STATUS1_ANY_NEGATIVE, BattleScript_EffectPsychoShiftCanWork
	goto BattleScript_ButItFailed
BattleScript_EffectPsychoShiftCanWork:
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	jumpifsafeguard BattleScript_SafeguardProtected
	trypsychoshift BattleScript_ButItFailed
	attackanimation
	waitanimation
	copybyte gEffectBattler, gBattlerTarget
	printfromtable gStatusConditionsStringIds
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_TARGET
	updatestatusicon BS_TARGET
	curestatus BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectSynchronoise:
	attackcanceler
	attackstring
	ppreduce
	selectfirstvalidtarget
BattleScript_SynchronoiseLoop:
	movevaluescleanup
	jumpifcantusesynchronoise BattleScript_SynchronoiseNoEffect
	accuracycheck BattleScript_SynchronoiseMissed, ACC_CURR_MOVE
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	tryfaintmon BS_TARGET
BattleScript_SynchronoiseMoveTargetEnd:
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_SynchronoiseLoop
	end
BattleScript_SynchronoiseMissed:
	pause B_WAIT_TIME_SHORT
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_SynchronoiseMoveTargetEnd
BattleScript_SynchronoiseNoEffect:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_SynchronoiseMoveTargetEnd

BattleScript_EffectSmackDown:
	jumpifword CMP_COMMON_BITS, gFieldStatuses, STATUS_FIELD_GRAVITY, BattleScript_SmackDownPreventEscape
	setmoveeffect MOVE_EFFECT_SMACK_DOWN
	goto BattleScript_EffectHit
BattleScript_SmackDownPreventEscape:
	call BattleScript_EffectHit_Ret
	setmoveeffect MOVE_EFFECT_SMACK_DOWN
	seteffectprimary
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectsecondary
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_MoveEffectSmackDown::
	printstring STRINGID_FELLSTRAIGHTDOWN
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectHitEnemyHealAlly:
	jumpiftargetally BattleScript_EffectHealPulse
	goto BattleScript_EffectHit

BattleScript_EffectDefog:
	setstatchanger STAT_EVASION, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_DefogIfCanClearHazards
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_EVASION, MIN_STAT_STAGE, BattleScript_DefogWorks
BattleScript_DefogIfCanClearHazards:
	defogclear BS_ATTACKER, FALSE, BattleScript_FailedFromAtkString
BattleScript_DefogWorks:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_DefogTryHazardsWithAnim
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DefogDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_DefogTryHazardsWithAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_DefogPrintString
BattleScript_DefogDoAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_DefogPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefogTryHazards::
	copybyte gEffectBattler, gBattlerAttacker
	defogclear BS_ATTACKER, TRUE, NULL
	copybyte gBattlerAttacker, gEffectBattler
	goto BattleScript_MoveEnd
BattleScript_DefogTryHazardsWithAnim:
	attackanimation
	waitanimation
	goto BattleScript_DefogTryHazards

BattleScript_EffectCopycat:
	attackcanceler
	attackstring
	pause 5
	trycopycat BattleScript_CopycatFail
	attackanimation
	waitanimation
	jumptocalledmove TRUE
BattleScript_CopycatFail:
	ppreduce
	goto BattleScript_ButItFailed

BattleScript_EffectInstruct:
	attackcanceler
	attackstring
	ppreduce
	pause 5
	tryinstruct BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_USEDINSTRUCTEDMOVE
	waitmessage B_WAIT_TIME_LONG
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	jumptocalledmove TRUE

BattleScript_EffectAutotomize:
	jumpifstatus4 BS_ATTACKER, STATUS4_SUPERCHARGED, BattleScript_AutotomizeRaiseSpeedSpAtk
	setstatchanger STAT_SPEED, 2, FALSE
	attackcanceler
	attackstring
	ppreduce
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AutotomizeWeightLoss
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AutotomizeAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_AutotomizePrintString
BattleScript_AutotomizeAttackAnim::
	attackanimation
	waitanimation
BattleScript_AutotomizeDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_AutotomizePrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AutotomizeWeightLoss::
	jumpifmovehadnoeffect BattleScript_MoveEnd
	tryautotomize BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_BECAMENIMBLE
	waitmessage B_WAIT_TIME_LONG
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_AutotomizeClearStatus
	goto BattleScript_MoveEnd
BattleScript_AutotomizeClearStatus:
	curestatuswithmove BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	goto BattleScript_MoveEnd
BattleScript_AutotomizeRaiseSpeedSpAtk:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_Autotomize2DoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_Autotomize2DoMoveAnim:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, 10, BattleScript_Autotomize2SpeedBy1
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_SPATK, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPEED, 2, FALSE
	goto BattleScript_Autotomize2DoSpeed
BattleScript_Autotomize2SpeedBy1:
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_SPATK, 0
	setstatchanger STAT_SPEED, 1, FALSE
BattleScript_Autotomize2DoSpeed:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_Autotomize2TrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_Autotomize2TrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_Autotomize2TrySpAtk:
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_Autotomize2End
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_Autotomize2End
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_Autotomize2ClearStatus
	goto BattleScript_MoveEnd
BattleScript_Autotomize2ClearStatus:
	curestatuswithmove BS_ATTACKER, BattleScript_Autotomize2End
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
BattleScript_Autotomize2End:
	goto BattleScript_MoveEnd

BattleScript_EffectFinalGambit:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	dmgtocurrattackerhp
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	dmgtocurrattackerhp
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	seteffectwithchance
	tryfaintmon BS_ATTACKER
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	goto BattleScript_MoveEnd

BattleScript_EffectHitSwitchTarget:
	call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	moveendall
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut 
	jumpifability BS_TARGET, ABILITY_STALWART, BattleScript_AbilityPreventsPhasingOut 
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	tryhitswitchtarget BattleScript_MoveEnd
	forcerandomswitch BattleScript_HitSwitchTargetForceRandomSwitchFailed
	goto BattleScript_MoveEnd

BattleScript_HitSwitchTargetForceRandomSwitchFailed:
	hitswitchtargetfailed
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	goto BattleScript_MoveEnd

BattleScript_EffectClearSmog:
	setmoveeffect MOVE_EFFECT_CLEAR_SMOG
	goto BattleScript_EffectHit

BattleScript_EffectToxicThread:
	setstatchanger STAT_SPEED, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_ToxicThreadWorks
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_FailedFromAtkString
BattleScript_ToxicThreadWorks:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_ToxicThreadTryPsn
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_ToxicThreadDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_ToxicThreadTryPsn
	pause B_WAIT_TIME_SHORT
	goto BattleScript_ToxicThreadPrintString
BattleScript_ToxicThreadDoAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_ToxicThreadPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ToxicThreadTryPsn::
	setmoveeffect MOVE_EFFECT_POISON
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectVenomDrench:
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_EffectVenomDrenchCanBeUsed
	goto BattleScript_ButItFailed
BattleScript_EffectVenomDrenchCanBeUsed:
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPATK, MIN_STAT_STAGE, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPEED, MIN_STAT_STAGE, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ACC, MIN_STAT_STAGE, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_EVASION, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_VenomDrenchDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF | BIT_SPATK | BIT_SPDEF | BIT_SPEED | BIT_ACC | BIT_EVASION, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchTryLowerDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VenomDrenchTryLowerDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchTryLowerDef::
	playstatchangeanimation BS_TARGET, BIT_DEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchTryLowerSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VenomDrenchTryLowerSpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchTryLowerSpAtk::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchTryLowerSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VenomDrenchTryLowerSpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchTryLowerSpDef::
	playstatchangeanimation BS_TARGET, BIT_SPDEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchTryLowerSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VenomDrenchTryLowerSpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchTryLowerSpeed::
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchTryLowerAcc
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VenomDrenchTryLowerAcc
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchTryLowerAcc::
	playstatchangeanimation BS_TARGET, BIT_ACC, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchTryLowerEvasion
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VenomDrenchTryLowerEvasion
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchTryLowerEvasion::
	playstatchangeanimation BS_TARGET, BIT_EVASION, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_VenomDrenchEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_VenomDrenchEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VenomDrenchEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectTearfulLook:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_TearfulLookDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_TearfulLookDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_TearfulLookTryLowerSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_TearfulLookTryLowerSpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TearfulLookTryLowerSpAtk::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_TearfulLookEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_TearfulLookEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TearfulLookEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectMetalSound:
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_MetalSoundLowerSpDefSpeed
	setstatchanger STAT_SPDEF, 2, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_MetalSoundStatDownDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_MoveEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_MetalSoundStatDownPrintString
BattleScript_MetalSoundStatDownDoAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_MetalSoundStatDownPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	jumpifstatus4 BS_ATTACKER, STATUS4_SUPERCHARGED, BattleScript_MetalSoundSpDefDownPreventHeal
	goto BattleScript_MoveEnd
BattleScript_MetalSoundSpDefDownPreventHeal:
	sethealblock BattleScript_MoveEnd
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotHealBlockAttacker
	goto BattleScript_MoveEnd

BattleScript_MetalSoundLowerSpDefSpeed:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_MetalSoundLowerSpDefSpeedDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_MetalSoundLowerSpDefSpeedDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_SPDEF | BIT_SPEED, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS | STAT_CHANGE_BY_TWO
	playstatchangeanimation BS_TARGET, BIT_SPDEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPDEF, 2, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_MetalSoundLowerSpDefSpeedTryLowerSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_MetalSoundLowerSpDefSpeedTryLowerSpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MetalSoundLowerSpDefSpeedTryLowerSpeed::
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_MetalSoundLowerSpDefSpeedEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_MetalSoundLowerSpDefSpeedEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	jumpifstatus4 BS_ATTACKER, STATUS4_SUPERCHARGED, BattleScript_MetalSoundLowerSpDefSpeedPreventHeal
	goto BattleScript_MoveEnd
BattleScript_MetalSoundLowerSpDefSpeedPreventHeal:
	sethealblock BattleScript_MoveEnd
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotHealBlockAttacker
	goto BattleScript_MoveEnd
BattleScript_MetalSoundLowerSpDefSpeedEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectShellSmash:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_ButItFailed
BattleScript_ShellSmashTryDef::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_ShellSmashTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShellSmashTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashTrySpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_ShellSmashTryAttack
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShellSmashTryAttack
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashTryAttack:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_ATK | BIT_SPEED, STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShellSmashTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShellSmashTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashTrySpAtk:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShellSmashTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShellSmashTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashTrySpeed:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShellSmashEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShellSmashEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShellSmashEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectLastResort:
	attackcanceler
	attackstring
	ppreduce
	jumpifcantuselastresort BS_ATTACKER, BattleScript_ButItFailed
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

BattleScript_EffectGrowth:
	attackcanceler
	attackstring
	ppreduce
	jumpifweatheraffected BS_ATTACKER, B_WEATHER_SUN, BattleScript_EffectTryGrowthBlooming
	goto BattleScript_GrowthStatBoost
BattleScript_EffectTryGrowthBlooming::
	jumpifstatus BS_TARGET, STATUS1_BLOOMING, BattleScript_GrowthStatBoost
	jumpiftype BS_TARGET, TYPE_FIRE, BattleScript_GrowthStatBoost
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_GrowthStatBoost
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_GrowthStatBoost
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_GrowthDoMoveAnimWithBlooming
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_GrowthJustBloom
BattleScript_GrowthDoMoveAnimWithBlooming::
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_CERTAIN
	seteffectprimary
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_GrowthTrySpAtkWithBlooming
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GrowthTrySpAtkWithBlooming
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GrowthTrySpAtkWithBlooming::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_GrowthJustBloom::
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_CERTAIN
	goto BattleScript_MoveEnd
BattleScript_GrowthStatBoost::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_GrowthDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_GrowthDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_GrowthTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GrowthTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GrowthTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSoak:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_MULTITYPE, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_RKS_SYSTEM, BattleScript_ButItFailed
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_DAMP, BattleScript_SoakJustTrySoak
	tryworryseed BattleScript_SoakJustTrySoak
	trysoak BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TARGETCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	tryrevertweatherform
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	goto BattleScript_MoveEnd
BattleScript_SoakJustTrySoak:
	trysoak BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TARGETCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectReflectType:
	setuserstatus4 STATUS4_REFLECTED_TYPE, BattleScript_ReflectTypeContinue
BattleScript_ReflectTypeContinue:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryreflecttype BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_REFLECTTARGETSTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectElectrify:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryelectrify BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TARGETELECTRIFIED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectShiftGear:
	jumpifstatus4 BS_ATTACKER, STATUS4_SUPERCHARGED, BattleScript_ShiftGearCheckGearedUp
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_EffectShiftGear2Atk1Speed
	goto BattleScript_ShiftGearBasic
BattleScript_ShiftGearCheckGearedUp:
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_EffectShiftGear2Atk2Speed
	goto BattleScript_EffectShiftGear1Atk2Speed
BattleScript_ShiftGearBasic:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ShiftGearDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_ShiftGearDoMoveAnim:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_ATK, 0
	setstatchanger STAT_SPEED, 1, FALSE
BattleScript_ShiftGearDoSpeed:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGearTryAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShiftGearTryAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGearTryAtk:
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGearEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShiftGearEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGearEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectShiftGear2Atk1Speed:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ShiftGear2Atk1SpeedDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_ShiftGear2Atk1SpeedDoMoveAnim:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_ATK, 10, BattleScript_ShiftGear2Atk1SpeedSpeedBy1
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPEED, STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 2, FALSE
	goto BattleScript_ShiftGear2Atk1SpeedDoSpeed
BattleScript_ShiftGear2Atk1SpeedSpeedBy1:
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPEED, 0
	setstatchanger STAT_ATK, 1, FALSE
BattleScript_ShiftGear2Atk1SpeedDoSpeed:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGear2Atk1SpeedTryAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShiftGear2Atk1SpeedTryAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGear2Atk1SpeedTryAtk:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGear2Atk1SpeedEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShiftGear2Atk1SpeedEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGear2Atk1SpeedEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectShiftGear1Atk2Speed:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ShiftGear1Atk2SpeedDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_ShiftGear1Atk2SpeedDoMoveAnim:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, 10, BattleScript_ShiftGear1Atk2SpeedSpeedBy1
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_ATK, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPEED, 2, FALSE
	goto BattleScript_ShiftGear1Atk2SpeedDoSpeed
BattleScript_ShiftGear1Atk2SpeedSpeedBy1:
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_ATK, 0
	setstatchanger STAT_SPEED, 1, FALSE
BattleScript_ShiftGear1Atk2SpeedDoSpeed:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGear1Atk2SpeedTryAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShiftGear1Atk2SpeedTryAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGear1Atk2SpeedTryAtk:
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGear1Atk2SpeedEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShiftGear1Atk2SpeedEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGear1Atk2SpeedEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectShiftGear2Atk2Speed:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ShiftGear2Atk2SpeedDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_ShiftGear2Atk2SpeedDoMoveAnim:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, 10, BattleScript_ShiftGear2Atk2SpeedSpeedBy1
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_ATK, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPEED, 2, FALSE
	goto BattleScript_ShiftGear2Atk2SpeedDoSpeed
BattleScript_ShiftGear2Atk2SpeedSpeedBy1:
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_ATK, 0
	setstatchanger STAT_SPEED, 1, FALSE
BattleScript_ShiftGear2Atk2SpeedDoSpeed:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGear2Atk2SpeedTryAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShiftGear2Atk2SpeedTryAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGear2Atk2SpeedTryAtk:
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ShiftGear2Atk2SpeedEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShiftGear2Atk2SpeedEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShiftGear2Atk2SpeedEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectCoil:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_CoilDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_CoilDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ACC, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_CoilDoMoveAnim:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_ACC, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CoilTryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CoilTryDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoilTryDef:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CoilTryAcc
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CoilTryAcc
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoilTryAcc:
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CoilEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CoilEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoilEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectQuiverDance:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_QuiverDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_QuiverDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_QuiverDanceDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_SPDEF | BIT_SPEED, 0
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_QuiverDanceTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_QuiverDanceTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_QuiverDanceTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_QuiverDanceTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_QuiverDanceTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_QuiverDanceTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_QuiverDanceEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_QuiverDanceEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_QuiverDanceEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectVictoryDance:
	attackcanceler
	attackstring
	ppreduce
BattleScript_EffectVictoryDanceFromStatUp::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_VictoryDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_VictoryDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_VictoryDanceDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VictoryDanceTryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VictoryDanceTryDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceTryDef::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VictoryDanceTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VictoryDanceTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_VictoryDanceEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VictoryDanceEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSpeedUpHit:
	setmoveeffect MOVE_EFFECT_SPD_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectMeFirst:
	attackcanceler
	attackstring
	trymefirst BattleScript_FailedFromPpReduce
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	jumptocalledmove TRUE

BattleScript_EffectAttackSpAttackUp:
	attackcanceler
	attackstring
	ppreduce
BattleScript_EffectWorkUpFromStatUp::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AttackSpAttackUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_AttackSpAttackUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AttackSpAttackUpTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AttackSpAttackUpTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackSpAttackUpTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AttackSpAttackUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AttackSpAttackUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackSpAttackUpEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectAttackAccUp:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AttackAccUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ACC, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_AttackAccUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_ACC, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AttackAccUpTryAcc
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AttackAccUpTryAcc
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackAccUpTryAcc::
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AttackAccUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AttackAccUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackAccUpEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectMistyTerrain:
BattleScript_EffectGrassyTerrain:
BattleScript_EffectElectricTerrain:
BattleScript_EffectPsychicTerrain:
	attackcanceler
	attackstring
	ppreduce
	setremoveterrain BattleScript_ButItFailed
	attackanimation
	waitanimation
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	goto BattleScript_MoveEnd

BattleScript_EffectTopsyTurvy:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_DEF, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPATK, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPDEF, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ACC, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_EVASION, 6, BattleScript_ButItFailed
BattleScript_EffectTopsyTurvyWorks:
	attackanimation
	waitanimation
	invertstatstages BS_TARGET
	printstring STRINGID_TOPSYTURVYSWITCHEDSTATS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_ClearSpeed::
	normalisespeed
	printstring STRINGID_SPEEDSTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_EffectIonDeluge:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryelectrify BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TARGETELECTRIFIED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectQuash:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryquash BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_QUASHSUCCESS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHealPulse:
	attackcanceler
	attackstring
	ppreduce
    jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_MoveUsedHealBlockPrevents @ stops pollen puff
    jumpifstatus3 BS_TARGET, STATUS3_HEAL_BLOCK, BattleScript_MoveUsedHealBlockPrevents
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifsubstituteblocks BattleScript_ButItFailed
	tryhealpulse BS_TARGET, BattleScript_AlreadyAtFullHp
	attackanimation
	waitanimation
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectEntrainment:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryentrainment BattleScript_ButItFailed
	attackanimation
	waitanimation
	setlastusedability BS_TARGET
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSimpleBeam:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setabilitysimple BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNACQUIREDSIMPLE
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	tryrevertweatherform
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	tryendneutralizinggas BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectSuckerPunch:
	attackcanceler
	suckerpunchcheck BattleScript_FailedFromAtkString
	jumpifmove MOVE_UPPER_HAND, BattleScript_EffectFlinchHit
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	goto BattleScript_HitFromAtkString

BattleScript_EffectLuckyChant:
	attackcanceler
	attackstring
	ppreduce
	setluckychant BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_SHIELDEDFROMCRITICALHITS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMetalBurst:
	attackcanceler
	metalburstdamagecalculator BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectHealingWish:
	attackcanceler
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_FailedFromAtkString
	attackstring
	ppreduce
	attackanimation
	waitanimation
	instanthpdrop BS_ATTACKER
	setatkhptozero
	tryfaintmon BS_ATTACKER
	storehealingwish BS_ATTACKER
.if B_HEALING_WISH_SWITCH <= GEN_4
	openpartyscreen BS_ATTACKER, BattleScript_EffectHealingWishEnd
	switchoutabilities BS_ATTACKER
	waitstate
	switchhandleorder BS_ATTACKER, 2
	returnatktoball
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, TRUE
	waitstate
	switchineffects BS_ATTACKER
.endif
BattleScript_EffectHealingWishEnd:
	moveendall
	end

BattleScript_HealingWishActivates::
	setbyte cMULTISTRING_CHOOSER, 0
	goto BattleScript_EffectHealingWishRestore
BattleScript_LunarDanceActivates::
	setbyte cMULTISTRING_CHOOSER, 1
	restorepp BS_ATTACKER
BattleScript_EffectHealingWishRestore:
	printfromtable gHealingWishStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_WISH_HEAL
	waitanimation
	dmgtomaxattackerhp
	manipulatedamage DMG_CHANGE_SIGN
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	clearstatus BS_ATTACKER
	waitstate
	updatestatusicon BS_ATTACKER
	waitstate
	printstring STRINGID_HEALINGWISHHEALED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_HealOrderActivates::
	setbyte cMULTISTRING_CHOOSER, 2
	printfromtable gHealingWishStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_WISH_HEAL
	waitanimation
	dmg_1_3_attackerhp
	manipulatedamage DMG_CHANGE_SIGN
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_HEALINGWISHHEALED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_EffectWorrySeed:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_EffectWorrySeedPanicFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_PANIC, BattleScript_EffectWorrySeedPanicFailed
	jumpiftype BS_TARGET, TYPE_DARK, BattleScript_EffectWorrySeedPanicFailed
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_EffectWorrySeedPanicFailed
	jumpifability BS_TARGET, ABILITY_UNAWARE, BattleScript_EffectWorrySeedPanicFailed
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_EffectWorrySeedPanicFailed
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_EffectWorrySeedPanicFailed
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_EffectWorrySeedPanicFailed
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_EffectWorrySeedPanicFailed
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_EffectWorrySeedPanicFailed
	jumpifflowerveil BattleScript_EffectWorrySeedPanicFailed
	jumpifleafguardprotected BS_TARGET, BattleScript_EffectWorrySeedPanicFailed
	jumpifeeriemaskprotected BS_TARGET, BattleScript_EffectWorrySeedPanicFailed
	jumpifshieldsdown BS_TARGET, BattleScript_EffectWorrySeedPanicFailed
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_EffectWorrySeedPanicFailed
	jumpifsafeguard BattleScript_EffectWorrySeedPanicFailed
	tryworryseed BattleScript_EffectWorrySeedFailedPanicSucceeded
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PANIC
	seteffectprimary
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	tryrevertweatherform
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	goto BattleScript_MoveEnd
BattleScript_EffectWorrySeedPanicFailed:
	tryworryseed BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	tryrevertweatherform
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	goto BattleScript_MoveEnd
BattleScript_EffectWorrySeedFailedPanicSucceeded::
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PANIC
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectPowerSplit:
	attackcanceler
	attackstring
	ppreduce
	checkpowersplit BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	averagestats STAT_ATK
	averagestats STAT_SPATK
	attackanimation
	waitanimation
	printstring STRINGID_SHAREDITSPOWER
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_PowerSplitContinue
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_PowerSplitEnd
BattleScript_PowerSplitContinue::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_PowerSplitTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_PowerSplitTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PowerSplitTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_PowerSplitEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_PowerSplitEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PowerSplitEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectGuardSplit:
	attackcanceler
	attackstring
	ppreduce
	checkguardsplit BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	averagestats STAT_DEF
	averagestats STAT_SPDEF
	attackanimation
	waitanimation
	printstring STRINGID_SHAREDITSGUARD
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_GuardSplitContinue
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_GuardSplitEnd
BattleScript_GuardSplitContinue::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_GuardSplitTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GuardSplitTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GuardSplitTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_GuardSplitEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GuardSplitEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GuardSplitEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectHeartSwap:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	swapstatstages STAT_ATK
	swapstatstages STAT_DEF
	swapstatstages STAT_SPEED
	swapstatstages STAT_SPATK
	swapstatstages STAT_SPDEF
	swapstatstages STAT_EVASION
	swapstatstages STAT_ACC
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSTATCHANGES
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPowerSwap:
	attackcanceler
	attackstring
	ppreduce
	checkpowerswap BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	swapstats STAT_ATK
	swapstats STAT_SPATK
	attackanimation
	waitanimation
	printstring STRINGID_ATTACKERSWITCHEDSTATWITHTARGET
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_PowerSwapContinue
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_PowerSwapContinue
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_PowerSwapContinue
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MIN_STAT_STAGE, BattleScript_PowerSwapEnd
BattleScript_PowerSwapContinue::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_PowerSwapTryLowerFoeSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_PowerSwapTryLowerFoeSpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PowerSwapTryLowerFoeSpAtk::
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_PowerSwapTryRaiseUserAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_PowerSwapTryRaiseUserAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PowerSwapTryRaiseUserAtk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_PowerSwapTryRaiseUserSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_PowerSwapTryRaiseUserSpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PowerSwapTryRaiseUserSpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_PowerSwapEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_PowerSwapEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_PowerSwapEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectGuardSwap:
	attackcanceler
	attackstring
	ppreduce
	checkguardswap BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	swapstats STAT_DEF
	swapstats STAT_SPDEF
	attackanimation
	waitanimation
	printstring STRINGID_ATTACKERSWITCHEDSTATWITHTARGET
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_GuardSwapContinue
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_GuardSwapContinue
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_GuardSwapContinue
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_GuardSwapEnd
BattleScript_GuardSwapContinue::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPDEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_GuardSwapTryLowerFoeSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_GuardSwapTryLowerFoeSpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GuardSwapTryLowerFoeSpDef::
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_GuardSwapTryRaiseUserDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_GuardSwapTryRaiseUserDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GuardSwapTryRaiseUserDef::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_GuardSwapTryRaiseUserSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GuardSwapTryRaiseUserSpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GuardSwapTryRaiseUserSpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_GuardSwapEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GuardSwapEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GuardSwapEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSpeedSwap:
	attackcanceler
	attackstring
	ppreduce
	checkspeedswap BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	swapstats STAT_SPEED
	attackanimation
	waitanimation
	printstring STRINGID_ATTACKERSWITCHEDSTATWITHTARGET
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_SpeedSwapContinue
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MIN_STAT_STAGE, BattleScript_SpeedSwapEnd
BattleScript_SpeedSwapContinue::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SpeedSwapTryRaiseUserSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SpeedSwapTryRaiseUserSpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpeedSwapTryRaiseUserSpeed::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, 0
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SpeedSwapEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SpeedSwapEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpeedSwapEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectTelekinesis:
	attackcanceler
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_EffectTelekinesisNoBlock
	jumpifsubstituteblocks BattleScript_EffectTelekinesisNoBlock
.if B_GHOSTS_ESCAPE >= GEN_6
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_EffectTelekinesisNoBlock
.endif
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	settelekinesis BattleScript_ButItFailed
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_HURLEDINTOTHEAIR
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectTelekinesisNoBlock:
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	settelekinesis BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_HURLEDINTOTHEAIR
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectStealthRock:
	attackcanceler
	attackstring
	ppreduce
	setstealthrock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_POINTEDSTONESFLOAT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectStickyWeb:
	attackcanceler
	attackstring
	ppreduce
	setstickyweb BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_STICKYWEBUSED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGastroAcid::
	setgastroacid BattleScript_EffectSpecialDefenseDown
	setstatchanger STAT_SPDEF, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_JustGastroAcid
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_GastroAcidStatDownDoAnimJustGastro
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_GastroAcidStatDownDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_GastroAcidStatDownDoAnimJustGastro
	pause B_WAIT_TIME_SHORT
	goto BattleScript_GastroAcidStatDownPrintString
BattleScript_GastroAcidStatDownDoAnim::
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSABILITYSUPPRESSED
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	tryrevertweatherform
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	tryendneutralizinggas BS_TARGET
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_GastroAcidStatDownPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GastroAcidStatDownEnd::
	goto BattleScript_MoveEnd
BattleScript_JustGastroAcid::
	attackstring
	ppreduce
BattleScript_GastroAcidStatDownDoAnimJustGastro::
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSABILITYSUPPRESSED
	waitmessage B_WAIT_TIME_LONG
	trytoclearprimalweather
	tryrevertweatherform
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	tryendneutralizinggas BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectToxicSpikes:
	attackcanceler
	attackstring
	ppreduce
	settoxicspikes BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_POISONSPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMagnetRise:
	setstatchanger STAT_SPEED, 1, FALSE
	attackcanceler
	attackstring
	ppreduce
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MagnetRiseRising
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MagnetRiseAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_MagnetRisePrintString
BattleScript_MagnetRiseAttackAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_MagnetRisePrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MagnetRiseRising::
	setuserstatus3 STATUS3_MAGNET_RISE, BattleScript_MoveEnd
	printstring STRINGID_PKMNLEVITATEDONELECTROMAGNETISM
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectTrickRoom::
	attackcanceler
	attackstring
	ppreduce
	setroom
	attackanimation
	waitanimation
	printfromtable gRoomsStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryRoomServiceLoop
	goto BattleScript_MoveEnd

BattleScript_TryRoomServiceLoop:
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_RoomServiceLoop:
	copybyte sBATTLER, gBattlerTarget
	tryroomservice BS_TARGET, BattleScript_RoomServiceLoop_NextBattler
	removeitem BS_TARGET
BattleScript_RoomServiceLoop_NextBattler:
	addbyte gBattlerTarget, 0x1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_RoomServiceLoop
	restoretarget
	return

BattleScript_TimeTurnActivated::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNTWISTEDDIMENSIONS
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	call BattleScript_TryRoomServiceLoop
	end3

BattleScript_TimeTurnDeactivated::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TRICKROOMENDS
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	end3

BattleScript_EffectWonderRoom:
BattleScript_EffectMagicRoom:
	attackcanceler
	attackstring
	ppreduce
	setroom
	attackanimation
	waitanimation
	printfromtable gRoomsStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_ReversiActivated::	
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_THETYPECHARTINVERTED
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	end3

BattleScript_ReversiDeactivated::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_INVERSEROOMENDS
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	end3

BattleScript_EffectAquaRing:
	attackcanceler
	attackstring
	ppreduce
	setuserstatus3 STATUS3_AQUA_RING, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSURROUNDEDWITHVEILOFWATER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectEmbargo:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setembargo BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCANTUSEITEMSANYMORE
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectTailwind:
	attackcanceler
	attackstring
	ppreduce
	settailwind BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TAILWINDBLEW
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryTailwindAbilitiesLoop
	goto BattleScript_MoveEnd

BattleScript_TryTailwindAbilitiesLoop:
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_TryTailwindAbilitiesLoop_Iter:
	trywindriderpower BS_TARGET, BattleScript_TryTailwindAbilitiesLoop_Increment
	jumpifability BS_TARGET, ABILITY_WIND_RIDER, BattleScript_TryTailwindAbilitiesLoop_WindRider
	jumpifability BS_TARGET, ABILITY_WIND_POWER, BattleScript_TryTailwindAbilitiesLoop_WindPower
BattleScript_TryTailwindAbilitiesLoop_Increment:
	addbyte gBattlerTarget, 0x1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_TryTailwindAbilitiesLoop_Iter
	restoretarget
	return

BattleScript_TryTailwindAbilitiesLoop_WindRider:
	call BattleScript_AbilityPopUp
	modifybattlerstatstage BS_TARGET, STAT_ATK, INCREASE, 1, BattleScript_TryTailwindAbilitiesLoop_WindRiderAtkEnd, ANIM_ON
BattleScript_TryTailwindAbilitiesLoop_WindRiderAtkEnd:
	modifybattlerstatstage BS_TARGET, STAT_SPATK, INCREASE, 1, BattleScript_TryTailwindAbilitiesLoop_Increment, ANIM_ON
	goto BattleScript_TryTailwindAbilitiesLoop_Increment

BattleScript_TryTailwindAbilitiesLoop_WindPower:
	call BattleScript_AbilityPopUp
	setcharge BS_TARGET
	printstring STRINGID_BEINGHITCHARGEDPKMNWITHPOWER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TryTailwindAbilitiesLoop_Increment

BattleScript_EffectMiracleEye:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	checkstatboosts 1, BattleScript_MiracleEyeStatBoosted
	goto BattleScript_ButItFailed
BattleScript_MiracleEyeStatBoosted:
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_EffectMiracleEyeStatClear
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_EffectMiracleEyeStatClear
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_EffectMiracleEyeStatClear
    jumpifsubstituteblocks BattleScript_EffectMiracleEyeStatClear
    jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_EffectMiracleEyeStatClear
    jumpifsafeguard BattleScript_EffectMiracleEyeStatClear
	tryresetpositivestatstages BS_TARGET
	setmoveeffect MOVE_EFFECT_CONFUSION
	attackanimation
	waitanimation
	printstring STRINGID_TARGETPOSITIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	seteffectprimary
	goto BattleScript_MoveEnd
BattleScript_EffectMiracleEyeStatClear:
	tryresetpositivestatstages BS_TARGET
	attackanimation
	waitanimation
	printstring STRINGID_TARGETPOSITIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGravity:
	attackcanceler
	attackstring
	ppreduce
	setgravity BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_GRAVITYINTENSIFIED
	waitmessage B_WAIT_TIME_LONG
	selectfirstvalidtarget
BattleScript_GravityLoop:
	movevaluescleanup
	jumpifstatus3 BS_TARGET, STATUS3_ON_AIR | STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS, BattleScript_GravityLoopDrop
	goto BattleScript_GravityLoopEnd
BattleScript_GravityLoopDrop:
	bringdownairbornebattler BS_TARGET
	printstring STRINGID_GRAVITYGROUNDING
	waitmessage B_WAIT_TIME_LONG
BattleScript_GravityLoopEnd:
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_GravityLoop
	end

BattleScript_GravityWellActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_GRAVITY
	waitanimation
	printstring STRINGID_ABILITYINTENSIFIEDGRAVITY
	waitmessage B_WAIT_TIME_LONG
	selectfirstvalidtarget
BattleScript_GravityWellGravityLoop:
	movevaluescleanup
	jumpifstatus3 BS_TARGET, STATUS3_ON_AIR | STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS, BattleScript_GravityWellGravityLoopDrop
	goto BattleScript_GravityWellGravityLoopEnd
BattleScript_GravityWellGravityLoopDrop:
	bringdownairbornebattler BS_TARGET
	printstring STRINGID_GRAVITYGROUNDING
	waitmessage B_WAIT_TIME_LONG
BattleScript_GravityWellGravityLoopEnd:
	moveendto MOVEEND_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_GravityWellGravityLoop
	end3

BattleScript_EffectRoost:
	attackcanceler
	attackstring
	ppreduce
	tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_TARGET
	setroost
	goto BattleScript_PresentHealTarget

BattleScript_EffectCaptivate:
	jumpifstatus2 BS_TARGET, STATUS2_INFATUATION, BattleScript_EffectSpecialAttackDown3 
	setstatchanger STAT_SPATK, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialAttackDown3:
	setstatchanger STAT_SPATK, 3, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectHealBlock:
	attackcanceler
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_EffectHealBlockNoBlock
	jumpifsubstituteblocks BattleScript_EffectHealBlockNoBlock
.if B_GHOSTS_ESCAPE >= GEN_6
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_EffectHealBlockNoBlock
.endif
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifsafeguard BattleScript_SafeguardProtected
	sethealblock BattleScript_ButItFailed
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotHealBlockAttacker
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectHealBlockNoBlock:
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifsafeguard BattleScript_SafeguardProtected
	sethealblock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotHealBlockAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectThroatChop:
	jumpifsubstituteblocks BattleScript_EffectHit
	setmoveeffect MOVE_EFFECT_THROAT_CHOP | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectHitEscape:
	call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_MoveEnd
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendto MOVEEND_ATTACKER_VISIBLE
	moveendfrom MOVEEND_TARGET_VISIBLE
	jumpifbattleend BattleScript_HitEscapeEnd
	jumpifbyte CMP_NOT_EQUAL gBattleOutcome, 0, BattleScript_HitEscapeEnd
	jumpifemergencyexited BS_TARGET, BattleScript_HitEscapeEnd
	goto BattleScript_MoveSwitch
BattleScript_HitEscapeEnd:
	end

BattleScript_EffectPlaceholder:
	attackcanceler
	attackstring
	ppreduce
	pause 5
	printstring STRINGID_NOTDONEYET
	goto BattleScript_MoveEnd

BattleScript_EffectRound:
	setmoveeffect MOVE_EFFECT_ROUND
	goto BattleScript_EffectHit

BattleScript_EffectHit::
BattleScript_HitFromAtkCanceler::
	attackcanceler
BattleScript_HitFromAccCheck::
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
BattleScript_HitFromAtkString::
	attackstring
	ppreduce
BattleScript_HitFromCritCalc::
	critcalc
	damagecalc
	adjustdamage
BattleScript_HitFromAtkAnimation::
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
BattleScript_MoveEnd::
	moveendall
	end

BattleScript_EffectHit_Ret::
	attackcanceler
BattleScript_EffectHit_RetFromAccCheck::
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
BattleScript_EffectHit_RetFromCritCalc::
	critcalc
	damagecalc
	adjustdamage
BattleScript_Hit_RetFromAtkAnimation::
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectNaturalGift:
	attackcanceler
	attackstring
	ppreduce
	jumpifnotberry BS_ATTACKER, BattleScript_ButItFailed
	jumpifword CMP_COMMON_BITS, gFieldStatuses, STATUS_FIELD_MAGIC_ROOM, BattleScript_ButItFailed
	jumpifability BS_ATTACKER, ABILITY_KLUTZ, BattleScript_ButItFailed
	jumpifstatus3 BS_ATTACKER, STATUS3_EMBARGO, BattleScript_ButItFailed
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	jumpifmovehadnoeffect BattleScript_EffectNaturalGiftEnd
	checkparentalbondcounter 2, BattleScript_EffectNaturalGiftEnd
	removeitem BS_ATTACKER
BattleScript_EffectNaturalGiftEnd:
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_MakeMoveMissed::
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
BattleScript_PrintMoveMissed::
	attackstring
	ppreduce
BattleScript_MoveMissedPause::
	pause B_WAIT_TIME_SHORT
BattleScript_MoveMissed::
	effectivenesssound
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectDarkVoid::
BattleScript_EffectSleep::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_SLEEP_ANY, BattleScript_AlreadyAsleep
	jumpifmove MOVE_HYPNOSIS, BattleScript_HypnosisCheck
BattleScript_SleepDoTheRest::
	jumpiftype BS_TARGET, TYPE_RELIC, BattleScript_ButItFailed
	jumpifuproarwakes BattleScript_CantMakeAsleep
	jumpifability BS_TARGET, ABILITY_INSOMNIA, BattleScript_InsomniaProtects
	jumpifability BS_TARGET, ABILITY_VITAL_SPIRIT, BattleScript_InsomniaProtects
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifability BS_TARGET_SIDE, ABILITY_SWEET_VEIL, BattleScript_SweetVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	jumpifterrainaffected BS_TARGET, STATUS_FIELD_ELECTRIC_TERRAIN, BattleScript_ElectricTerrainPrevents
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_SLEEP
	seteffectprimary
	goto BattleScript_MoveEnd
BattleScript_HypnosisCheck:
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_ButItFailed
	goto BattleScript_SleepDoTheRest

BattleScript_TerrainPreventsEnd2::
	pause B_WAIT_TIME_SHORT
	printfromtable gTerrainPreventsStringIds
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ElectricTerrainPrevents::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ELECTRICTERRAINPREVENTS
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_MistyTerrainPrevents::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MISTYTERRAINPREVENTS
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_FlowerVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_FLOWERVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_FlowerVeilProtects:
	call BattleScript_FlowerVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_SweetVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_FLOWERVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SweetVeilProtects:
	call BattleScript_SweetVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_AromaVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_AROMAVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AromaVeilProtects::
	call BattleScript_AromaVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_PastelVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PASTELVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PastelVeilProtects:
	call BattleScript_PastelVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_WaterVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_WATERVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_WaterVeilProtects:
	call BattleScript_WaterVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_AbilityProtectsDoesntAffectRet::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityProtectsDoesntAffect:
	call BattleScript_AbilityProtectsDoesntAffectRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_ItemProtectsDoesntAffect:
	pause B_WAIT_TIME_SHORT
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_InsomniaProtects:
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSTAYEDAWAKEUSING
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_AlreadyAsleep::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNALREADYASLEEP
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_WasntAffected::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNWASNTAFFECTED
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_CantMakeAsleep::
	pause B_WAIT_TIME_SHORT
	printfromtable gUproarAwakeStringIds
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_EffectPoisonHit:
	setmoveeffect MOVE_EFFECT_POISON
	goto BattleScript_EffectHit

BattleScript_BarbBarrage::
	seteffectsecondary
	setmoveeffect 0
	return

BattleScript_EffectAbsorb::
	jumpifmove MOVE_GIGA_DRAIN, BattleScript_GigaDrainAbsorb
	jumpifmove MOVE_HORN_LEECH, BattleScript_HornLeechAbsorb
	jumpifmove MOVE_DRAINING_KISS, BattleScript_DrainingKissAbsorb
	goto BattleScript_Absorb
BattleScript_GigaDrainAbsorb::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_GigaDrainLowerSpecialDefense
	goto BattleScript_Absorb
BattleScript_GigaDrainLowerSpecialDefense::
	setmoveeffect MOVE_EFFECT_SP_DEF_MINUS_1
	goto BattleScript_Absorb
BattleScript_HornLeechAbsorb::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_HornLeechLowerDefense
	goto BattleScript_Absorb
BattleScript_HornLeechLowerDefense::
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1
	goto BattleScript_Absorb
BattleScript_DrainingKissAbsorb::
	setmoveeffect MOVE_EFFECT_ATK_MINUS_1
BattleScript_Absorb::
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_AbsorbHealBlock
	setdrainedhp
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_AbsorbLiquidOoze
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB
	goto BattleScript_AbsorbUpdateHp
BattleScript_AbsorbLiquidOoze::
	call BattleScript_AbilityPopUpTarget
	manipulatedamage DMG_CHANGE_SIGN
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABSORB_OOZE
BattleScript_AbsorbUpdateHp::
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_AbsorbTryFainting
	printfromtable gAbsorbDrainStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AbsorbTryFainting::
	tryfaintmon BS_ATTACKER
BattleScript_AbsorbHealBlock::
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectInfernalParade::
BattleScript_EffectBurnHit::
	setmoveeffect MOVE_EFFECT_BURN
	goto BattleScript_EffectHit

BattleScript_EffectBitterMalice::
BattleScript_EffectFrostbiteHit::
	setmoveeffect MOVE_EFFECT_FROSTBITE
	goto BattleScript_EffectHit

BattleScript_EffectSleepHit::
	setmoveeffect MOVE_EFFECT_SLEEP
	goto BattleScript_EffectHit

BattleScript_EffectFreezeHit::
	setmoveeffect MOVE_EFFECT_FREEZE
	goto BattleScript_EffectHit

BattleScript_EffectParalyzeHit::
	setmoveeffect MOVE_EFFECT_PARALYSIS
	goto BattleScript_EffectHit

BattleScript_EffectPanicHit::
	setmoveeffect MOVE_EFFECT_PANIC
    goto BattleScript_EffectHit

BattleScript_EffectBloomingHit::
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_AFFECTS_USER
    goto BattleScript_EffectHit
    
BattleScript_EffectExposedHit::
	setmoveeffect MOVE_EFFECT_EXPOSED
    goto BattleScript_EffectHit

BattleScript_EffectZapCannon::
	jumpifstatus4 BS_ATTACKER, STATUS4_SUPERCHARGED, BattleScript_ZapCannonCheckGearedUp
	goto BattleScript_EffectParalyzeHit
BattleScript_ZapCannonCheckGearedUp:
	jumpifstatus4 BS_ATTACKER, STATUS4_GEARED_UP, BattleScript_ZapCannonRecharge
	goto BattleScript_EffectParalyzeHit
BattleScript_ZapCannonRecharge:
	removesupergear
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_RECHARGE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	seteffectprimary
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectExplosion_AnimDmgRet:
	jumpifbyte CMP_NO_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_MISSED, BattleScript_ExplosionAnimRet
	call BattleScript_PreserveMissedBitDoMoveAnim
	goto BattleScript_ExplosionDmgRet
BattleScript_ExplosionAnimRet:
	attackanimation
	waitanimation
BattleScript_ExplosionDmgRet:
	movevaluescleanup
	critcalc
	damagecalc
	adjustdamage
	accuracycheck BattleScript_ExplosionMissedRet, ACC_CURR_MOVE
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
BattleScript_ExplosionAnimEndRet_Return:
	return
BattleScript_ExplosionMissedRet:
	effectivenesssound
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_ExplosionAnimEndRet_Return

BattleScript_EffectExplosion::
	attackcanceler
	attackstring
	ppreduce
	tryexplosion
	setatkhptozero
	waitstate
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

BattleScript_FaintAttackerForExplosion::
	tryfaintmon BS_ATTACKER
	return

BattleScript_MaxHp50Recoil::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	return

BattleScript_PreserveMissedBitDoMoveAnim:
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED
	attackanimation
	waitanimation
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	return

BattleScript_EffectDreamEater::
	attackcanceler
	jumpifsubstituteblocks BattleScript_DreamEaterNoEffect
	jumpifstatus BS_TARGET, STATUS1_SLEEP_ANY, BattleScript_DreamEaterWorked
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_DreamEaterWorked
BattleScript_DreamEaterNoEffect:
	attackstring
	ppreduce
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_WasntAffected
BattleScript_DreamEaterWorked:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	jumpifstatus3 BS_ATTACKER, STATUS3_HEAL_BLOCK, BattleScript_DreamEaterTryFaintEnd
	setdrainedhp
	manipulatedamage DMG_BIG_ROOT
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_DreamEaterTryFaintEnd
	printstring STRINGID_PKMNDREAMEATEN
	waitmessage B_WAIT_TIME_LONG
BattleScript_DreamEaterTryFaintEnd:
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectMirrorMove::
	attackcanceler
	attackstring
	pause B_WAIT_TIME_LONG
	trymirrormove
	ppreduce
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	printstring STRINGID_MIRRORMOVEFAILED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectAttackUp::
	setstatchanger STAT_ATK, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectDefenseUp::
	setstatchanger STAT_DEF, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialAttackUp::
	setstatchanger STAT_SPATK, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpeedUp:
	setstatchanger STAT_SPEED, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialDefenseUp:
	setstatchanger STAT_SPDEF, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectAccuracyUp:
	setstatchanger STAT_ACC, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectEvasionUp::
	setstatchanger STAT_EVASION, 1, FALSE
BattleScript_EffectStatUp::
	attackcanceler
BattleScript_EffectStatUpAfterAtkCanceler::
	attackstring
	ppreduce
BattleScript_EffectStatUpAfterPPReduce::
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_StatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_StatUpAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_StatUpPrintString
BattleScript_StatUpAttackAnim::
	attackanimation
	waitanimation
BattleScript_StatUpDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StatUpPrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StatUpEnd::
	goto BattleScript_MoveEnd

BattleScript_StatUp::
	playanimation BS_EFFECT_BATTLER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StatUpMsg::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectAttackDown:
	setstatchanger STAT_ATK, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectDefenseDown:
	setstatchanger STAT_DEF, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpeedDown:
	setstatchanger STAT_SPEED, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectAccuracyDown:
	setstatchanger STAT_ACC, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialAttackDown:
	setstatchanger STAT_SPATK, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialDefenseDown:
	setstatchanger STAT_SPDEF, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectEvasionDown:
	setstatchanger STAT_EVASION, 1, TRUE
BattleScript_EffectStatDown:
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
BattleScript_StatDownFromAttackString:
	attackstring
	ppreduce
BattleScript_StatDownFromPPReduce:
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_StatDownEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_StatDownDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_StatDownEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_StatDownPrintString
BattleScript_StatDownDoAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StatDownPrintString::
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StatDownEnd::
	goto BattleScript_MoveEnd

BattleScript_MirrorArmorReflect::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	jumpifsubstituteblocks BattleScript_AbilityNoSpecificStatLoss
BattleScript_MirrorArmorReflectStatLoss:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_MIRROR_ARMOR | STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_MirrorArmorReflectEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_MirrorArmorReflectAnim
	goto BattleScript_MirrorArmorReflectWontFall
BattleScript_MirrorArmorReflectAnim:
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_MirrorArmorReflectPrintString:
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MirrorArmorReflectEnd:
	return

BattleScript_MirrorArmorReflectWontFall:
	copybyte gBattlerTarget, gBattlerAttacker   @ STRINGID_STATSWONTDECREASE uses target
	goto BattleScript_MirrorArmorReflectPrintString

@ gBattlerTarget is battler with Mirror Armor
BattleScript_MirrorArmorReflectStickyWeb:
	call BattleScript_AbilityPopUp
	setattackertostickywebuser
	jumpifbyteequal gBattlerAttacker, gBattlerTarget, BattleScript_StickyWebOnSwitchInEnd   @ Sticky web user not on field -> no stat loss
	call BattleScript_MirrorArmorReflectStatLoss
	goto BattleScript_StickyWebOnSwitchInEnd

BattleScript_MoonMirrorReflect::
	pause B_WAIT_TIME_SHORT
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	jumpifsubstituteblocks BattleScript_ItemNoSpecificStatLoss
BattleScript_MoonMirrorReflectStatLoss:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_MIRROR_ARMOR | STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_MoonMirrorReflectEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_MoonMirrorReflectAnim
	goto BattleScript_MoonMirrorReflectWontFall
BattleScript_MoonMirrorReflectAnim:
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_MoonMirrorReflectPrintString:
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoonMirrorReflectEnd:
	return

BattleScript_MoonMirrorReflectWontFall:
	copybyte gBattlerTarget, gBattlerAttacker   @ STRINGID_STATSWONTDECREASE uses target
	goto BattleScript_MoonMirrorReflectPrintString

@ gBattlerTarget is battler with Mirror Armor
BattleScript_MoonMirrorReflectStickyWeb:
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	setattackertostickywebuser
	jumpifbyteequal gBattlerAttacker, gBattlerTarget, BattleScript_StickyWebOnSwitchInEnd   @ Sticky web user not on field -> no stat loss
	call BattleScript_MoonMirrorReflectStatLoss
	goto BattleScript_StickyWebOnSwitchInEnd

BattleScript_StatDown::
	playanimation BS_EFFECT_BATTLER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectHaze::
	attackcanceler
	attackstring
	pause B_WAIT_TIME_MED
	ppreduce
	waitstate
	attackanimation
	waitanimation
	tryhaze FALSE, BattleScript_EffectHazeDoMoveAnimation
	goto BattleScript_HazeStatNormalize

BattleScript_EffectHazeDoMoveAnimation::
	tryhaze TRUE, NULL
	printstring STRINGID_TIDYINGUPCOMPLETE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HazeStatNormalize

BattleScript_HazeStatNormalize::
	normalisebuffs
	printstring STRINGID_STATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectBide1::
	jumpifmove MOVE_COSMIC_POWER, BattleScript_CantRaiseMultipleStats
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_CHARGING
	setbide
	goto BattleScript_MoveEnd

BattleScript_EffectBide2::
	orword gHitMarker, HITMARKER_CHARGING
	setbide
	goto BattleScript_MoveEnd

BattleScript_EffectRampage::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_EffectRampage2
	ppreduce
BattleScript_EffectRampage2:
	confuseifrepeatingattackends
	goto BattleScript_HitFromCritCalc

BattleScript_EffectRoar::
	attackcanceler
	attackstring
	ppreduce
	jumpifroarfails BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut
	jumpifability BS_TARGET, ABILITY_STALWART, BattleScript_AbilityPreventsPhasingOut
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_ButItFailed
	forcerandomswitch BattleScript_ButItFailed

BattleScript_EffectMultiHit::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setmultihitcounter 0
	initmultihitstring
	sethword sMULTIHIT_EFFECT, 0
BattleScript_MultiHitLoop::
	jumpifhasnohp BS_ATTACKER, BattleScript_MultiHitEnd
	jumpifhasnohp BS_TARGET, BattleScript_MultiHitPrintStrings
	jumpifhalfword CMP_EQUAL, gChosenMove, MOVE_SLEEP_TALK, BattleScript_DoMultiHit
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP_ANY, BattleScript_MultiHitPrintStrings
BattleScript_DoMultiHit::
	movevaluescleanup
	copyhword sMOVE_EFFECT, sMULTIHIT_EFFECT
	critcalc
	damagecalc
	jumpifmovehadnoeffect BattleScript_MultiHitNoMoreHits
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	multihitresultmessage
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	addbyte sMULTIHIT_STRING + 4, 1
	moveendto MOVEEND_NEXT_TARGET
	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_FOE_ENDURED, BattleScript_MultiHitPrintStrings
	decrementmultihit BattleScript_MultiHitLoop
	goto BattleScript_MultiHitPrintStrings
BattleScript_MultiHitNoMoreHits::
	pause B_WAIT_TIME_SHORT
BattleScript_MultiHitPrintStrings::
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	jumpifmovehadnoeffect BattleScript_MultiHitEnd
	copyarray gBattleTextBuff1, sMULTIHIT_STRING, 6
	printstring STRINGID_HITXTIMES
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MultiHitEnd::
	seteffectwithchance
	tryfaintmon BS_TARGET
	moveendcase MOVEEND_SYNCHRONIZE_TARGET
	moveendfrom MOVEEND_STATUS_IMMUNITY_ABILITIES
	end

BattleScript_EffectConversion::
	attackcanceler
	attackstring
	ppreduce
	tryconversiontypechange BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFlinchHit::
	setmoveeffect MOVE_EFFECT_FLINCH
	goto BattleScript_EffectHit

BattleScript_EffectFlinchStatus:
	setmoveeffect MOVE_EFFECT_FLINCH
	call BattleScript_EffectHit_Ret
	seteffectwithchance
	argumentstatuseffect
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectRestoreHp::
	attackcanceler
	attackstring
	ppreduce
	tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_ATTACKER
	attackanimation
	waitanimation
BattleScript_RestoreHp:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectToxic::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_IMMUNITY, BattleScript_ImmunityProtected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET_SIDE, ABILITY_PASTEL_VEIL, BattleScript_PastelVeilProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_POISON | STATUS1_TOXIC_POISON, BattleScript_AlreadyPoisoned
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	trypoisontype BS_ATTACKER, BS_TARGET, BattleScript_NotAffected
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_TOXIC
	seteffectprimary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_AlreadyPoisoned::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_LONG
	printstring STRINGID_PKMNALREADYPOISONED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_ImmunityProtected::
	copybyte gEffectBattler, gBattlerTarget
	call BattleScript_AbilityPopUp
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABILITY_PREVENTS_MOVE_STATUS
	call BattleScript_PSNPrevention
	goto BattleScript_MoveEnd

BattleScript_EffectPayDay::
	setmoveeffect MOVE_EFFECT_PAYDAY
	goto BattleScript_EffectHit

BattleScript_EffectAuroraVeil:
	attackcanceler
	attackstring
	ppreduce
	setauroraveil BS_ATTACKER
	goto BattleScript_PrintReflectLightScreenSafeguardString

BattleScript_EffectLightScreen::
	attackcanceler
	attackstring
	ppreduce
	setlightscreen
	goto BattleScript_PrintReflectLightScreenSafeguardString

BattleScript_EffectTriAttack::
	setmoveeffect MOVE_EFFECT_TRI_ATTACK
	goto BattleScript_EffectHit

BattleScript_EffectViperStrike::
	setmoveeffect MOVE_EFFECT_VIPER_STRIKE
	goto BattleScript_EffectHit

BattleScript_EffectRest::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP_ANY, BattleScript_RestIsAlreadyAsleep
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_RestIsAlreadyAsleep
	jumpifuproarwakes BattleScript_RestCantSleep
	jumpifability BS_TARGET, ABILITY_INSOMNIA, BattleScript_InsomniaProtects
	jumpifability BS_TARGET, ABILITY_VITAL_SPIRIT, BattleScript_InsomniaProtects
.if B_LEAF_GUARD_PREVENTS_REST >= GEN_5
	jumpifleafguardprotected BS_TARGET, BattleScript_LeafGuardPreventsRest
.endif
	trysetrest BattleScript_AlreadyAtFullHp
	pause B_WAIT_TIME_SHORT
	printfromtable gRestUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	waitstate
	goto BattleScript_PresentHealTarget

BattleScript_RestCantSleep::
	pause B_WAIT_TIME_LONG
	printfromtable gUproarAwakeStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_RestIsAlreadyAsleep::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNALREADYASLEEP2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_LeafGuardPreventsRest::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_BUTITFAILED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectOHKO::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	typecalc
	jumpifmovehadnoeffect BattleScript_HitFromAtkAnimation
	tryKO BattleScript_KOFail
	trysetdestinybondtohappen
	goto BattleScript_HitFromAtkAnimation
BattleScript_KOFail::
	pause B_WAIT_TIME_LONG
	printfromtable gKOFailedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_TwoTurnMovesSecondTurn::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	goto BattleScript_HitFromAccCheck

BattleScriptFirstChargingTurn::
	attackcanceler
	printstring STRINGID_EMPTYSTRING3
	ppreduce
	attackstring
BattleScriptFirstChargingTurnAfterAttackString:
	pause B_WAIT_TIME_LONG
	copybyte cMULTISTRING_CHOOSER, sTWOTURN_STRINGID
	printfromtable gFirstTurnOfTwoStringIds
	waitmessage B_WAIT_TIME_LONG
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_CHARGING
	setmoveeffect MOVE_EFFECT_CHARGING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	return

BattleScript_EffectSuperFang::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	damagetopercentagetargethp
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectDragonRage::
	setmoveeffect MOVE_EFFECT_DRAGON_RAGE | MOVE_EFFECT_AFFECTS_USER
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	dmgtolevel
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectTrap::
	setmoveeffect MOVE_EFFECT_WRAP
	goto BattleScript_EffectHit

BattleScript_EffectRecoilIfMiss::
	attackcanceler
	accuracycheck BattleScript_MoveMissedDoDamage, ACC_CURR_MOVE
.if B_CRASH_IF_TARGET_IMMUNE >= GEN_4
	typecalc
	jumpifhalfword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_MoveMissedDoDamage
.endif
	goto BattleScript_HitFromAtkString
BattleScript_MoveMissedDoDamage::
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_PrintMoveMissed
	jumpifability BS_ATTACKER, ABILITY_SUGAR_COAT, BattleScript_PrintMoveMissed
	jumpifterucharmprotected BS_ATTACKER, BattleScript_PrintMoveMissed
	attackstring
	ppreduce
	pause B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
.if B_CRASH_IF_TARGET_IMMUNE < GEN_4
	jumpifhalfword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_MoveEnd
.endif
	moveendcase MOVEEND_PROTECT_LIKE_EFFECT @ Spiky Shield's damage happens before recoil.
	jumpifhasnohp BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_PKMNCRASHED
	waitmessage B_WAIT_TIME_LONG
	damagecalc
	typecalc
	adjustdamage
.if B_CRASH_IF_TARGET_IMMUNE == GEN_4
	manipulatedamage DMG_RECOIL_FROM_IMMUNE
.else
	manipulatedamage DMG_RECOIL_FROM_MISS
.endif
.if B_CRASH_IF_TARGET_IMMUNE >= GEN_4
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE
.else
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED
.endif
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
.if B_CRASH_IF_TARGET_IMMUNE >= GEN_4
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE
.else
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
.endif
	goto BattleScript_MoveEnd

BattleScript_EffectMist::
	attackcanceler
	attackstring
	ppreduce
	setmist
	attackanimation
	waitanimation
	printfromtable gMistUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFocusEnergy::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_ATTACKER, STATUS2_FOCUS_ENERGY_ANY, BattleScript_ButItFailed
	setfocusenergy BS_ATTACKER
	attackanimation
	waitanimation
	printfromtable gFocusEnergyUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectConfuse:
	attackcanceler
	attackstring
	ppreduce
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_OwnTempoPrevents
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_OwnTempoPrevents
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_AlreadyConfused
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_AlreadyConfused::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNALREADYCONFUSED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectAttackUp2::
	setstatchanger STAT_ATK, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectDefenseUp2::
	setstatchanger STAT_DEF, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectDefenseUp3:
	setstatchanger STAT_DEF, 3, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpeedUp2::
	setstatchanger STAT_SPEED, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialAttackUp2::
	setstatchanger STAT_SPATK, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialAttackUp3::
	setstatchanger STAT_SPATK, 3, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialDefenseUp2::
	setstatchanger STAT_SPDEF, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectAccuracyUp2:
	setstatchanger STAT_ACC, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectEvasionUp2:
	setstatchanger STAT_EVASION, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectTransform::
	attackcanceler
	attackstring
	ppreduce
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	transformdataexecution
	attackanimation
	waitanimation
	printfromtable gTransformUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectAttackDown2:
	setstatchanger STAT_ATK, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectDefenseDown2:
	setstatchanger STAT_DEF, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpeedDown2:
	setstatchanger STAT_SPEED, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialDefenseDown2:
	setstatchanger STAT_SPDEF, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialAttackDown2:
	setstatchanger STAT_SPATK, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectAccuracyDown2:
	setstatchanger STAT_ACC, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectEvasionDown2:
	setstatchanger STAT_EVASION, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectReflect::
	attackcanceler
	attackstring
	ppreduce
	setreflect
BattleScript_PrintReflectLightScreenSafeguardString::
	attackanimation
	waitanimation
	printfromtable gReflectLightScreenSafeguardStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPoison::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_IMMUNITY, BattleScript_ImmunityProtected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET_SIDE, ABILITY_PASTEL_VEIL, BattleScript_PastelVeilProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_POISON, BattleScript_AlreadyPoisoned
	jumpifstatus BS_TARGET, STATUS1_TOXIC_POISON, BattleScript_AlreadyPoisoned
	trypoisontype BS_ATTACKER, BS_TARGET, BattleScript_NotAffected
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_POISON
	seteffectprimary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectParalyze:
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_LIMBER, BattleScript_LimberProtected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	typecalc
	jumpifmovehadnoeffect BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_PARALYSIS, BattleScript_AlreadyParalyzed
	jumpifabsorbaffected BS_TARGET, BattleScript_VoltAbsorbHeal
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	tryparalyzetype BS_ATTACKER, BS_TARGET, BattleScript_NotAffected
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_VoltAbsorbHeal:
	copybyte gBattlerAbility, gBattlerTarget
	tryhealquarterhealth BS_TARGET BattleScript_MonMadeMoveUseless @ Check if max hp
	goto BattleScript_MoveHPDrain

BattleScript_AlreadyParalyzed:
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNISALREADYPARALYZED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_LimberProtected::
	copybyte gEffectBattler, gBattlerTarget
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABILITY_PREVENTS_MOVE_STATUS
	call BattleScript_PRLZPrevention
	goto BattleScript_MoveEnd

BattleScript_EffectAttackDownHit::
	setmoveeffect MOVE_EFFECT_ATK_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectDefenseDownHit::
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectSpeedDownHit::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectSpecialAttackDownHit::
	setmoveeffect MOVE_EFFECT_SP_ATK_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectSpecialDefenseDownHit::
	setmoveeffect MOVE_EFFECT_SP_DEF_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectSpecialDefenseDownHit2::
	setmoveeffect MOVE_EFFECT_SP_DEF_MINUS_2
	goto BattleScript_EffectHit

BattleScript_EffectAccuracyDownHit::
	setmoveeffect MOVE_EFFECT_ACC_MINUS_1
	goto BattleScript_EffectHit

BattleScript_PowerHerbActivation:
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_POWERHERB
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_EffectTwoTurnsAttack::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	jumpifmove MOVE_SKY_ATTACK, BattleScript_EffectTwoTurnsAttackSkyAttack
	jumpifmove MOVE_RAZOR_WIND, BattleScript_EffectTwoTurnsAttackRazorWind
	jumpifmove MOVE_ICE_BURN, BattleScript_EffectTwoTurnsAttackIceBurn
	jumpifmove MOVE_FREEZE_SHOCK, BattleScript_EffectTwoTurnsAttackFreezeShock
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_RAZOR_WIND
BattleScript_EffectTwoTurnsAttackContinue:
	call BattleScriptFirstChargingTurn
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_TwoTurnMovesSecondTurn
BattleScript_EffectTwoTurnsAttackSkyAttack:
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_SKY_ATTACK
	goto BattleScript_EffectTwoTurnsAttackContinue
BattleScript_EffectTwoTurnsAttackRazorWind:
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_RAZOR_WIND
	goto BattleScript_EffectTwoTurnsAttackContinue
BattleScript_EffectTwoTurnsAttackIceBurn:
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_RAZOR_WIND
	goto BattleScript_EffectTwoTurnsAttackContinue
BattleScript_EffectTwoTurnsAttackFreezeShock:
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_FREEZE_SHOCK
	goto BattleScript_EffectTwoTurnsAttackContinue

BattleScript_EffectGeomancy:
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_GeomancySecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_GeomancySecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_GEOMANCY
	call BattleScriptFirstChargingTurn
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
BattleScript_GeomancySecondTurn:
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	attackstring
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_GeomancyDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_GeomancyDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_SPDEF | BIT_SPEED, 0
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_GeomancyTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GeomancyTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GeomancyTrySpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_GeomancyEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GeomancyEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GeomancyEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectConfuseHit::
	setmoveeffect MOVE_EFFECT_CONFUSION
	goto BattleScript_EffectHit

BattleScript_EffectSubstitute::
	attackcanceler
	ppreduce
	attackstring
	waitstate
	jumpifstatus2 BS_ATTACKER, STATUS2_SUBSTITUTE, BattleScript_AlreadyHasSubstitute
	setsubstitute
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_SUBSTITUTE_FAILED, BattleScript_SubstituteAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_SubstituteString
BattleScript_SubstituteAnim::
	orword gHitMarker, HITMARKER_PASSIVE_DAMAGE
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
BattleScript_SubstituteString::
	printfromtable gSubstituteUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_AlreadyHasSubstitute::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNHASSUBSTITUTE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRecharge::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_RECHARGE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_HitFromAtkString

BattleScript_MoveUsedMustRecharge::
	printstring STRINGID_PKMNMUSTRECHARGE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveUsedMustRechargeStats::
	printstring STRINGID_PKMNMUSTRECHARGE
	waitmessage B_WAIT_TIME_LONG
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_MoveUsedMustRechargeStatsContinue
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_MoveUsedMustRechargeStatsFail
BattleScript_MoveUsedMustRechargeStatsContinue::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveUsedMustRechargeStatTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveUsedMustRechargeStatTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoveUsedMustRechargeStatTrySpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_MoveUsedMustRechargeStatsFail::
	printstring STRINGID_STATSWONTINCREASE2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRage::
	attackcanceler
	accuracycheck BattleScript_RageMiss, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_RAGE
	seteffectprimary
	setmoveeffect 0
	goto BattleScript_HitFromAtkString
BattleScript_RageMiss::
	setmoveeffect MOVE_EFFECT_RAGE
	clearstatusfromeffect BS_ATTACKER
	goto BattleScript_PrintMoveMissed

BattleScript_EffectMimic::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	mimicattackcopy BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNLEARNEDMOVE2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMetronome::
	attackcanceler
	attackstring
	pause B_WAIT_TIME_SHORT
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	metronome

BattleScript_EffectLeechSeed::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectLeechSeedBloomingEffect
BattleScript_EffectLeechSeedContinue::
	attackcanceler
	attackstring
	pause B_WAIT_TIME_SHORT
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_DoLeechSeed, ACC_CURR_MOVE
BattleScript_DoLeechSeed::
	setseeded
	attackanimation
	waitanimation
	printfromtable gLeechSeedStringIds
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	goto BattleScript_MoveEnd
BattleScript_EffectLeechSeedBloomingEffect::
	setmoveeffect MOVE_EFFECT_WRAP
	goto BattleScript_EffectLeechSeedContinue

BattleScript_EffectDoNothing::
	attackcanceler
	attackstring
	ppreduce
	attackanimation
	waitanimation
	jumpifmove MOVE_CELEBRATE, BattleScript_EffectCelebrate
	jumpifmove MOVE_HAPPY_HOUR, BattleScript_EffectHappyHour
	jumpifmove MOVE_REAL_TEARS, BattleScript_IgnoreIncrementGameStat
	jumpifmove MOVE_NOTHING, BattleScript_IgnoreIncrementGameStat
	incrementgamestat GAME_STAT_USED_SPLASH
BattleScript_IgnoreIncrementGameStat::
	printstring STRINGID_BUTNOTHINGHAPPENED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectCelebrate:
	printstring STRINGID_CELEBRATEMESSAGE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectHappyHour:
	setmoveeffect MOVE_EFFECT_HAPPY_HOUR
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectDisable::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifsafeguard BattleScript_SafeguardProtected
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	disablelastusedattack BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNMOVEWASDISABLED
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotDisabledAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectLevelDamage::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	dmgtolevel
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectPsywave::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	psywavedamageeffect
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectCounter::
	attackcanceler
	counterdamagecalculator BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectEncore::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifsafeguard BattleScript_SafeguardProtected
	trysetencore BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNGOTENCORE
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotEncoreAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectPainSplit::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	painsplitdmgcalc BattleScript_ButItFailed
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	copyword gBattleMoveDamage, sPAINSPLIT_HP
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_SHAREDPAIN
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSnore::
	attackcanceler
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_SnoreIsAsleep
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP_ANY, BattleScript_SnoreIsAsleep
	attackstring
	ppreduce
	goto BattleScript_ButItFailed
BattleScript_SnoreIsAsleep::
	jumpifhalfword CMP_EQUAL, gChosenMove, MOVE_SLEEP_TALK, BattleScript_DoSnore
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
BattleScript_DoSnore::
	attackstring
	ppreduce
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_FLINCH
	goto BattleScript_HitFromCritCalc

BattleScript_EffectConversion2::
	attackcanceler
	attackstring
	ppreduce
	settypetorandomresistance BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectLockOn::
	jumpifnodamage BattleScript_EffectLockOnSpAttackUp
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	setalwayshitflag
	attackanimation
	waitanimation
	printstring STRINGID_PKMNTOOKAIM
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectLockOnSpAttackUp:
	setstatchanger STAT_SPATK, 2, FALSE
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed

	setalwayshitflag
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_LockOnStatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_LockOnAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_LockOnStatUpPrintString
BattleScript_LockOnAnim:
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_LockOnStatUpPrintString::
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNTOOKAIM
	waitmessage B_WAIT_TIME_LONG
BattleScript_LockOnStatUpEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSketch::
	attackcanceler
	attackstring
	ppreduce
	copymovepermanently BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSKETCHEDMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSleepTalk::
	attackcanceler
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_SleepTalkIsAsleep
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP_ANY, BattleScript_SleepTalkIsAsleep
	attackstring
	ppreduce
	goto BattleScript_ButItFailed
BattleScript_SleepTalkIsAsleep::
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	attackstring
	ppreduce
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	trychoosesleeptalkmove BattleScript_SleepTalkUsingMove
	pause B_WAIT_TIME_LONG
	goto BattleScript_ButItFailed
BattleScript_SleepTalkUsingMove::
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	jumptocalledmove TRUE

BattleScript_EffectDestinyBond::
	attackcanceler
	attackstring
	ppreduce
	setdestinybond
	attackanimation
	waitanimation
	printstring STRINGID_PKMNTRYINGTOTAKEFOE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMiseryWail::
	jumpifstatus BS_ATTACKER, STATUS1_ANY, BattleScript_EffectMiseryWailTorments
	goto BattleScript_EffectHit
BattleScript_EffectMiseryWailTorments::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_MoveEnd
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_MoveEnd
	jumpifsafeguard BattleScript_MoveEnd
	settorment BattleScript_MoveEnd
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectEerieSpell::
    call BattleScript_EffectHit_Ret
	tryfaintmon BS_TARGET
	jumpifbattleend BattleScript_MoveEnd
	jumpiffainted BS_TARGET, TRUE, BattleScript_MoveEnd
	jumpifmovehadnoeffect BattleScript_MoveEnd
	eeriespellppreduce BattleScript_MoveEnd
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSpite::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	tryspiteppreduce BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHealBell::
	attackcanceler
	attackstring
	ppreduce
	healpartystatus
	waitstate
	attackanimation
	waitanimation
	printfromtable gPartyStatusHealStringIds
	waitmessage B_WAIT_TIME_LONG
	jumpifnotmove MOVE_HEAL_BELL, BattleScript_PartyHealEnd
	jumpifbyte CMP_NO_COMMON_BITS, cMULTISTRING_CHOOSER, B_MSG_BELL_SOUNDPROOF_ATTACKER, BattleScript_CheckHealBellMon2Unaffected
	printstring STRINGID_PKMNSXBLOCKSY
	waitmessage B_WAIT_TIME_LONG
BattleScript_CheckHealBellMon2Unaffected::
	jumpifbyte CMP_NO_COMMON_BITS, cMULTISTRING_CHOOSER, B_MSG_BELL_SOUNDPROOF_PARTNER, BattleScript_PartyHealEnd
	printstring STRINGID_PKMNSXBLOCKSY2
	waitmessage B_WAIT_TIME_LONG
BattleScript_PartyHealEnd::
	updatestatusicon BS_ATTACKER_WITH_PARTNER
	waitstate
	goto BattleScript_MoveEnd

BattleScript_EffectTripleKick::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	addbyte sTRIPLE_KICK_POWER, 20 @ triple kick/axel gets +20 power
	goto BattleScript_HitFromAtkString

BattleScript_EffectThief::
	setmoveeffect MOVE_EFFECT_STEAL_ITEM
	goto BattleScript_EffectHit

BattleScript_EffectHitPreventEscape:
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	goto BattleScript_EffectHit

BattleScript_EffectMeanLook::
	attackcanceler
	attackstring
	ppreduce
	checkmeanlook BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_ButItFailed
	jumpifsubstituteblocks BattleScript_ButItFailed
.if B_GHOSTS_ESCAPE >= GEN_6
	jumpiftype BS_TARGET, TYPE_GHOST, BattleScript_ButItFailed
.endif
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_FLINCH
	seteffectsecondary
	goto BattleScript_MoveEnd

BattleScript_EffectNightmare::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus2 BS_TARGET, STATUS2_NIGHTMARE, BattleScript_NightmareJustTrySleep
	jumpifstatus BS_TARGET, STATUS1_SLEEP_ANY, BattleScript_OnlyNightmare
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_OnlyNightmare
	jumpiftype BS_TARGET, TYPE_RELIC, BattleScript_ButItFailed
	jumpifuproarwakes BattleScript_CantMakeAsleep
	jumpifability BS_TARGET, ABILITY_INSOMNIA, BattleScript_InsomniaProtects
	jumpifability BS_TARGET, ABILITY_VITAL_SPIRIT, BattleScript_InsomniaProtects
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifability BS_TARGET_SIDE, ABILITY_SWEET_VEIL, BattleScript_SweetVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	jumpifterrainaffected BS_TARGET, STATUS_FIELD_ELECTRIC_TERRAIN, BattleScript_ElectricTerrainPrevents
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
BattleScript_NightmareWorked::
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_SLEEP
	seteffectprimary
	setmoveeffect MOVE_EFFECT_NIGHTMARE
	seteffectsecondary
	printstring STRINGID_PKMNFELLINTONIGHTMARE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_OnlyNightmare::
	setmoveeffect MOVE_EFFECT_NIGHTMARE
	seteffectprimary
	printstring STRINGID_PKMNFELLINTONIGHTMARE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_NightmareJustTrySleep::
	jumpifstatus BS_TARGET, STATUS1_SLEEP_ANY, BattleScript_AlreadyAsleep
	jumpiftype BS_TARGET, TYPE_RELIC, BattleScript_ButItFailed
	jumpifuproarwakes BattleScript_CantMakeAsleep
	jumpifability BS_TARGET, ABILITY_INSOMNIA, BattleScript_InsomniaProtects
	jumpifability BS_TARGET, ABILITY_VITAL_SPIRIT, BattleScript_InsomniaProtects
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifability BS_TARGET_SIDE, ABILITY_SWEET_VEIL, BattleScript_SweetVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	jumpifterrainaffected BS_TARGET, STATUS_FIELD_ELECTRIC_TERRAIN, BattleScript_ElectricTerrainPrevents
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_SLEEP
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectMinimize::
	jumpifstatus3 BS_ATTACKER, STATUS3_MINIMIZED, BattleScript_EffectEvasionUp2
	attackcanceler
	setminimize
	setstatchanger STAT_EVASION, 2, FALSE
	attackstring
	ppreduce
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_StatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_StatUpAttackAnim
	pause B_WAIT_TIME_SHORT
	goto BattleScript_StatUpPrintString
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNBECAMEMINIMIZED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCurse::
	jumpiftype BS_ATTACKER, TYPE_GHOST, BattleScript_GhostCurse
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, MIN_STAT_STAGE, BattleScript_CurseTrySpeed
	jumpifstat BS_ATTACKER, CMP_NOT_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CurseTrySpeed
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_DEF, MAX_STAT_STAGE, BattleScript_ButItFailed
BattleScript_CurseTrySpeed::
	copybyte gBattlerTarget, gBattlerAttacker
	setbyte sB_ANIM_TURN, 1
	attackanimation
	waitanimation
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CurseTryAttack
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CurseTryAttack::
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CurseTryDefense
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CurseTryDefense::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CurseEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CurseEnd::
	goto BattleScript_MoveEnd
BattleScript_GhostCurse::
	jumpifbytenotequal gBattlerAttacker, gBattlerTarget, BattleScript_DoGhostCurse
	getmovetarget BS_ATTACKER
BattleScript_DoGhostCurse::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	cursetarget BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	setbyte sB_ANIM_TURN, 0
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNLAIDCURSE
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectMatBlock::
	attackcanceler
	jumpifnotfirstturn BattleScript_FailedFromAtkString
	goto BattleScript_ProtectLikeAtkString

BattleScript_EffectProtect::
BattleScript_EffectEndure::
	attackcanceler
BattleScript_ProtectLikeAtkString:
	attackstring
	ppreduce
	setprotectlike
	attackanimation
	waitanimation
	printfromtable gProtectLikeUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSpikes::
	attackcanceler
	trysetspikes BS_TARGET, BattleScript_FailedFromAtkString
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring STRINGID_SPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectForesight:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstatus2 BS_TARGET, STATUS2_FORESIGHT, BattleScript_ButItFailed
	setforesight
BattleScript_IdentifiedFoe:
	attackanimation
	waitanimation
	printstring STRINGID_PKMNIDENTIFIED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPerishSong::
	attackcanceler
	attackstring
	ppreduce
	trysetperishsong BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_FAINTINTHREE
	waitmessage B_WAIT_TIME_LONG
	setbyte gBattlerTarget, 0
BattleScript_PerishSongLoop::
	jumpifability BS_TARGET, ABILITY_SOUNDPROOF, BattleScript_PerishSongBlocked
BattleScript_PerishSongLoopIncrement::
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_PerishSongLoop
	goto BattleScript_MoveEnd

BattleScript_PerishSongBlocked::
	copybyte sBATTLER, gBattlerTarget
	printstring STRINGID_PKMNSXBLOCKSY2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_PerishSongLoopIncrement

BattleScript_PerishSongNotAffected:
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_PerishSongLoopIncrement

BattleScript_EffectSandstorm::
	attackcanceler
	attackstring
	ppreduce
	call BattleScript_CheckPrimalWeather
	setsandstorm
	attackanimation
	waitanimation
	printfromtable gMoveWeatherChangeStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_WEATHER_FAILED, BattleScript_SandstormSkipTailwindCheck
	call BattleScript_TryTailwindAbilitiesLoop
BattleScript_SandstormSkipTailwindCheck::
	goto BattleScript_MoveEnd

BattleScript_EffectRollout::
	attackcanceler
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_RolloutCheckAccuracy
	ppreduce
BattleScript_RolloutCheckAccuracy::
	accuracycheck BattleScript_RolloutHit, ACC_CURR_MOVE
BattleScript_RolloutHit::
	typecalc
	handlerollout
	goto BattleScript_HitFromCritCalc

BattleScript_EffectSwagger::
	attackcanceler
	jumpifsubstituteblocks BattleScript_MakeMoveMissed
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifconfusedandstatmaxed STAT_ATK, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SwaggerTryConfuse
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SwaggerTryConfuse
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SwaggerTryConfuse:
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_OwnTempoPrevents
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_OwnTempoPrevents
	jumpifsafeguard BattleScript_SafeguardProtected
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectFuryCutter:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_FuryCutterHit, ACC_CURR_MOVE
BattleScript_FuryCutterHit:
	handlefurycutter
	critcalc
	damagecalc
	jumpifmovehadnoeffect BattleScript_FuryCutterHit
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_TryDestinyKnotInfatuateTarget:
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotInfatuateTargetRet
	infatuatewithbattler BS_TARGET, BS_ATTACKER
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	status2animation BS_TARGET, STATUS2_INFATUATION
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotInfatuateTargetRet:
	return

BattleScript_TryDestinyKnotInfatuateAttacker:
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotInfatuateAttackerRet
	infatuatewithbattler BS_ATTACKER, BS_TARGET
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	status2animation BS_ATTACKER, STATUS2_INFATUATION
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotInfatuateAttackerRet:
	return

BattleScript_TryDestinyKnotDisabledTarget:
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotDisabledTargetRet
	destinyknotdisable BS_TARGET, BattleScript_TryDestinyKnotDisabledAttackerRet
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotDisabledTargetRet:
	return

BattleScript_TryDestinyKnotDisabledAttacker:
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotDisabledAttackerRet
	destinyknotdisable BS_ATTACKER, BattleScript_TryDestinyKnotDisabledAttackerRet
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotDisabledAttackerRet:
	return

BattleScript_TryDestinyKnotTormentAttacker:
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotTormentAttackerRet
	destinyknottorment BS_ATTACKER, BattleScript_TryDestinyKnotTormentAttackerRet
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotTormentAttackerRet:
	return

BattleScript_TryDestinyKnotTormentTarget:
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotTormentTargetRet
	destinyknottorment BS_TARGET, BattleScript_TryDestinyKnotTormentTargetRet
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotTormentTargetRet:
	return

BattleScript_TryDestinyKnotTauntAttacker:
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotTauntAttackerRet
	destinyknottaunt BS_ATTACKER, BattleScript_TryDestinyKnotTauntAttackerRet
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotTauntAttackerRet:
	return

BattleScript_TryDestinyKnotEncoreAttacker:
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotEncoreAttackerRet
	destinyknotencore BS_ATTACKER, BattleScript_TryDestinyKnotEncoreAttackerRet
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotEncoreAttackerRet:
	return

BattleScript_TryDestinyKnotHealBlockAttacker:
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_DESTINY_KNOT, BattleScript_TryDestinyKnotHealBlockAttackerRet
	destinyknothealblock BS_ATTACKER, BattleScript_TryDestinyKnotHealBlockAttackerRet
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_DESTINYKNOTACTIVATES
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryDestinyKnotHealBlockAttackerRet:
	return

BattleScript_EffectAttract::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	jumpifsafeguard BattleScript_SafeguardProtected
	tryinfatuating BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNFELLINLOVE
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectPresent::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	presentdamagecalculation

BattleScript_EffectSafeguard::
	attackcanceler
	attackstring
	ppreduce
	setsafeguard
	goto BattleScript_PrintReflectLightScreenSafeguardString

BattleScript_EffectMagnitude::
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING | HITMARKER_NO_PPDEDUCT, BattleScript_EffectMagnitudeTarget
	attackcanceler
	attackstring
	ppreduce
	magnitudedamagecalculation
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MAGNITUDESTRENGTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectMagnitudeTarget:
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

BattleScript_EffectBatonPass::
	attackcanceler
	attackstring
	ppreduce
	jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_ButItFailed
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	openpartyscreen BS_ATTACKER, BattleScript_ButItFailed
	switchoutabilities BS_ATTACKER
	waitstate
	switchhandleorder BS_ATTACKER, 2
	returntoball BS_ATTACKER
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, TRUE
	waitstate
	switchineffects BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectRapidSpin::
.if B_SPEED_BUFFING_RAPID_SPIN >= GEN_8
	call BattleScript_EffectHit_Ret
	jumpifhalfword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_RAPIDSPIN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	seteffectwithchance
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_EffectRapidSpinEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectRapidSpinEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectRapidSpinEnd::
	tryfaintmon BS_TARGET
	moveendall
	end
.else
	setmoveeffect MOVE_EFFECT_RAPIDSPIN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit
.endif

BattleScript_EffectSonicBoom::
	setmoveeffect MOVE_EFFECT_SP_DEF_MINUS_1
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	dmgtolevel
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectMorningSun::
BattleScript_EffectMoonlight::
BattleScript_EffectShoreUp::
BattleScript_EffectColdMend::
	attackcanceler
	attackstring
	ppreduce
	recoverbasedonsunlight BattleScript_AlreadyAtFullHp
	goto BattleScript_PresentHealTarget

BattleScript_EffectSynthesis::
	jumpifstatus BS_ATTACKER, STATUS1_BLOOMING, BattleScript_EffectSynthesisBlooming
	attackcanceler
	attackstring
	ppreduce
	recoverbasedonsunlight BattleScript_AlreadyAtFullHp
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectSynthesisBlooming:
	attackcanceler
	attackstring
	ppreduce
	recoverbasedonsunlight BattleScript_SynthesisFailedResetNegativeStats
	tryresetnegativestatstages BS_ATTACKER
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_SynthesisFailedResetNegativeStats::
	tryresetnegativestatstages BS_ATTACKER
	attackanimation
	waitanimation
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRainDance::
	attackcanceler
	attackstring
	ppreduce
	call BattleScript_CheckPrimalWeather
	setrain
BattleScript_MoveWeatherChange::
	attackanimation
	waitanimation
	call BattleScript_MoveWeatherChangeRet
	goto BattleScript_MoveEnd

BattleScript_MoveWeatherChangeRet::
	printfromtable gMoveWeatherChangeStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	return

BattleScript_EffectSunnyDay::
	attackcanceler
	attackstring
	ppreduce
	call BattleScript_CheckPrimalWeather
	setsunny
	goto BattleScript_MoveWeatherChange

BattleScript_ExtremelyHarshSunlightWasNotLessened:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_ExtremelyHarshSunlightWasNotLessenedEnd3:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_ExtremelyHarshSunlightWasNotLessenedRet:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_NoReliefFromHeavyRain:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NORELIEFROMHEAVYRAIN
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_NoReliefFromHeavyRainEnd3:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NORELIEFROMHEAVYRAIN
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_NoReliefFromHeavyRainRet:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NORELIEFROMHEAVYRAIN
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MysteriousAirCurrentBlowsOn:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MYSTERIOUSAIRCURRENTBLOWSON
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MysteriousAirCurrentBlowsOnEnd3:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MYSTERIOUSAIRCURRENTBLOWSON
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_MysteriousAirCurrentBlowsOnRet:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MYSTERIOUSAIRCURRENTBLOWSON
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BlockedByPrimalWeatherEnd3::
	call BattleScript_AbilityPopUp
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessenedEnd3
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRainEnd3
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOnEnd3
	end3

BattleScript_BlockedByPrimalWeatherRet::
	call BattleScript_AbilityPopUp
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessenedRet
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRainRet
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, B_WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOnRet
	return

BattleScript_EffectStickyHold::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ATTACKERCANTESCAPENOW
	waitmessage B_WAIT_TIME_SHORT
	return

BattleScript_EffectDefenseUpHit::
	setmoveeffect MOVE_EFFECT_DEF_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectAttackUpHit::
	setmoveeffect MOVE_EFFECT_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectSpecialAttackUpHit::
	setmoveeffect MOVE_EFFECT_SP_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectAllStatsUpHit::
	setmoveeffect MOVE_EFFECT_ALL_STATS_UP | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectBellyDrum::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_ButItFailed
	halvehp BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	playstatchangeanimation BS_ATTACKER, BIT_ATK, STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, MAX_STAT_STAGE, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEnd
	printstring STRINGID_PKMNCUTHPMAXEDATTACK
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPsychUp::
	attackcanceler
	attackstring
	ppreduce
	copyfoestats BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCOPIEDSTATCHANGES
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMirrorCoat::
	attackcanceler
	mirrorcoatdamagecalculator BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectSkullBash::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_SKULL_BASH
	call BattleScriptFirstChargingTurn
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SkullBashEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SkullBashEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SkullBashEnd::
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_TwoTurnMovesSecondTurn

BattleScript_EffectBulldoze:
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
BattleScript_EffectEarthquake:
	goto BattleScript_EffectHit

BattleScript_EffectFutureSight::
	attackcanceler
	attackstring
	ppreduce
	jumpifmove MOVE_DECIMATION, BattleScript_Decimation
BattleScript_EffectFutureSightOnly:
	trysetfutureattack BattleScript_ButItFailed
	attackanimation
	waitanimation
	printfromtable gFutureMoveUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_Decimation::
	jumpifbattletype BATTLE_TYPE_DOUBLE, BattleScript_DecimationDoubles
BattleScript_DecimationContinue:
	setmoveeffect MOVE_EFFECT_SP_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	trysetfutureattack BattleScript_ButItFailed
	attackanimation
	waitanimation
	seteffectprimary
	printstring STRINGID_PKMNISPREPARINGFORDECIMATION
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_DecimationDoubles:
	jumpifword CMP_NO_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING | HITMARKER_NO_PPDEDUCT, BattleScript_DecimationNoMoveEffect
	goto BattleScript_DecimationContinue
BattleScript_DecimationNoMoveEffect:
	setmoveeffect 0
	trysetfutureattack BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNISPREPARINGFORDECIMATION
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGust::
	goto BattleScript_EffectHit

BattleScript_EffectSolarBeam::
	jumpifweatheraffected BS_ATTACKER, B_WEATHER_SUN, BattleScript_SolarBeamOnFirstTurn
BattleScript_SolarBeamDecideTurn::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_SOLAR_BEAM
	call BattleScriptFirstChargingTurn
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_TwoTurnMovesSecondTurn
BattleScript_SolarBeamOnFirstTurn::
	ppreduce
	orword gHitMarker, HITMARKER_CHARGING
	setmoveeffect MOVE_EFFECT_CHARGING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	goto BattleScript_TwoTurnMovesSecondTurn

BattleScript_EffectThunder:
	setmoveeffect MOVE_EFFECT_PARALYSIS
	goto BattleScript_EffectHit

BattleScript_EffectHurricane:
	setmoveeffect MOVE_EFFECT_CONFUSION
	goto BattleScript_EffectHit

BattleScript_EffectTeleport:
.if B_TELEPORT_BEHAVIOR >= GEN_7
	jumpifbattletype BATTLE_TYPE_TRAINER, BattleScript_EffectBatonPass
	jumpifside BS_ATTACKER, B_SIDE_PLAYER, BattleScript_EffectBatonPass
.else
	jumpifbattletype BATTLE_TYPE_TRAINER, BattleScript_FailedFromAtkCanceler
.endif
BattleScript_EffectTeleportTryToRunAway:
	attackcanceler
	attackstring
	ppreduce
	getifcantrunfrombattle BS_ATTACKER
	jumpifbyte CMP_EQUAL, gBattleCommunication, BATTLE_RUN_FORBIDDEN, BattleScript_ButItFailed
	jumpifbyte CMP_EQUAL, gBattleCommunication, BATTLE_RUN_FAILURE, BattleScript_PrintAbilityMadeIneffective
	attackanimation
	waitanimation
	printstring STRINGID_PKMNFLEDFROMBATTLE
	waitmessage B_WAIT_TIME_LONG
	setoutcomeonteleport BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectBeatUp::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
.if B_BEAT_UP >= GEN_5
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	trydobeatup
	goto BattleScript_HitFromAtkAnimation
.else
	attackstring
	pause B_WAIT_TIME_SHORT
	ppreduce
	setbyte gBattleCommunication, 0
BattleScript_BeatUpLoop::
	movevaluescleanup
	trydobeatup BattleScript_BeatUpEnd, BattleScript_ButItFailed
	printstring STRINGID_PKMNATTACK
	critcalc
	jumpifbyte CMP_NOT_EQUAL, gIsCriticalHit, TRUE, BattleScript_BeatUpAttack
	manipulatedamage DMG_DOUBLED
BattleScript_BeatUpAttack::
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	moveendto MOVEEND_NEXT_TARGET
	goto BattleScript_BeatUpLoop
BattleScript_BeatUpEnd::
	end
.endif

BattleScript_EffectSemiInvulnerable::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_SecondTurnSemiInvulnerable
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_SecondTurnSemiInvulnerable
	jumpifmove MOVE_PHANTOM_FORCE, BattleScript_FirstTurnPhantomForce
	jumpifmove MOVE_DIVE, BattleScript_FirstTurnDive
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_BOUNCE
	goto BattleScript_FirstTurnSemiInvulnerable
BattleScript_FirstTurnDive:
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_DIVE
	goto BattleScript_FirstTurnSemiInvulnerable
BattleScript_FirstTurnPhantomForce:
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_PHANTOM_FORCE
BattleScript_FirstTurnSemiInvulnerable::
	call BattleScriptFirstChargingTurn
	setsemiinvulnerablebit
	jumpifmove MOVE_PHANTOM_FORCE, BattleScript_PhaseForcePhantomShenanigans
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
BattleScript_SecondTurnSemiInvulnerable::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
BattleScript_SemiInvulnerableTryHit::
	accuracycheck BattleScript_SemiInvulnerableMiss, ACC_CURR_MOVE
	clearsemiinvulnerablebit
	goto BattleScript_HitFromAtkString
BattleScript_SemiInvulnerableMiss::
	clearsemiinvulnerablebit
	goto BattleScript_PrintMoveMissed
BattleScript_PhaseForcePhantomShenanigans::
	jumpifstatus4 BS_ATTACKER, STATUS4_PHANTOM, BattleScript_SecondTurnSemiInvulnerable
	goto BattleScript_MoveEnd

BattleScript_EffectDefenseCurl::
	attackcanceler
	attackstring
	ppreduce
	setdefensecurlbit
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_DefenseCurlDoStatUpAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_StatUpPrintString
	attackanimation
	waitanimation
BattleScript_DefenseCurlDoStatUpAnim::
	goto BattleScript_StatUpDoAnim

BattleScript_EffectSoftboiled::
	attackcanceler
	attackstring
	ppreduce
	tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_TARGET
BattleScript_PresentHealTarget::
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_AlreadyAtFullHp::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNHPFULL
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFakeOut::
	attackcanceler
	jumpifnotfirstturn BattleScript_FailedFromAtkString
	jumpifmove MOVE_FIRST_IMPRESSION BattleScript_EffectHit
	jumpifmove MOVE_BEAT_DROP BattleScript_EffectHit
	setmoveeffect MOVE_EFFECT_FLINCH
	jumpifmove MOVE_NOBLE_ROAR, BattleScript_NobleRoarSpeedDown
	goto BattleScript_EffectHit
BattleScript_NobleRoarSpeedDown::
	seteffectprimary
	setstatchanger STAT_SPEED, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_FailedFromAtkCanceler::
	attackcanceler
BattleScript_FailedFromAtkString::
	attackstring
BattleScript_FailedFromPpReduce::
	ppreduce
BattleScript_ButItFailed::
	pause B_WAIT_TIME_SHORT
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_NotAffected::
	pause B_WAIT_TIME_SHORT
	orhalfword gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_NotAffectedAbilityPopUp::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpTarget
	orhalfword gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectUproar::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_UPROAR | MOVE_EFFECT_AFFECTS_USER
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_UproarHit
	ppreduce
BattleScript_UproarHit::
	goto BattleScript_HitFromCritCalc

BattleScript_EffectStockpile::
	attackcanceler
	attackstring
	ppreduce
	stockpile BS_ATTACKER, 0
	attackanimation
	waitanimation
	printfromtable gStockpileUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	.if B_STOCKPILE_RAISES_DEFS < GEN_4
	goto BattleScript_EffectStockpileEnd
	.endif
	jumpifmovehadnoeffect BattleScript_EffectStockpileEnd
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_EffectStockpileDef
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_EffectStockpileEnd
BattleScript_EffectStockpileDef:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_EffectStockpileSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectStockpileSpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectStockpileSpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_EffectStockpileEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectStockpileEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectStockpileEnd:
	stockpile BS_ATTACKER, 1
	goto BattleScript_MoveEnd

BattleScript_MoveEffectStockpileWoreOff::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_StockpileWoreOffTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_StockpileWoreOffTrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StockpileWoreOffTrySpDef::
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScriptStockpileWoreOffRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScriptStockpileWoreOffRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScriptStockpileWoreOffRet::
	return

BattleScript_StockpileStatChangeDown:
	statbuffchange MOVE_EFFECT_AFFECTS_USER, BattleScript_StockpileStatChangeDown_Ret
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StockpileStatChangeDown_Ret:
	return

BattleScript_EffectSpitUp::
	attackcanceler
	jumpifbyte CMP_EQUAL, cMISS_TYPE, B_MSG_PROTECTED, BattleScript_SpitUpFailProtect
	attackstring
	ppreduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setbyte gIsCriticalHit, FALSE
	damagecalc
	adjustdamage
	stockpiletobasedamage BattleScript_SpitUpFail
	goto BattleScript_HitFromAtkAnimation
BattleScript_SpitUpFail::
	checkparentalbondcounter 2, BattleScript_SpitUpEnd
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_FAILEDTOSPITUP
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpitUpEnd:
	goto BattleScript_MoveEnd

BattleScript_SpitUpFailProtect::
	attackstring
	ppreduce
	pause B_WAIT_TIME_LONG
	stockpiletobasedamage BattleScript_SpitUpFail
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSwallow::
	attackcanceler
	attackstring
	ppreduce
	stockpiletohpheal BattleScript_SwallowFail
	goto BattleScript_PresentHealTarget

BattleScript_SwallowFail::
	pause B_WAIT_TIME_SHORT
	printfromtable gSwallowFailStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHail::
	attackcanceler
	attackstring
	ppreduce
	call BattleScript_CheckPrimalWeather
	sethail
	goto BattleScript_MoveWeatherChange

BattleScript_EffectTorment::
	jumpifstatus2 BS_TARGET, STATUS2_TORMENT, BattleScript_TormentSuperEffect
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_AbilityProtectsDoesntAffect
	jumpifsafeguard BattleScript_SafeguardProtected
	settorment BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker
	goto BattleScript_MoveEnd
BattleScript_TormentSuperEffect::
	attackcanceler
	attackstring
	ppreduce
	tryrandomstatdrop BS_TARGET, BattleScript_TormentTrySpite
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	statbuffchange MOVE_EFFECT_CERTAIN, BattleScript_CheckTormentSpitePPReduce
	printstring STRINGID_DEFENDERSSTATFELL
	waitmessage B_WAIT_TIME_LONG
BattleScript_CheckTormentSpitePPReduce::
	tryspiteppreduce BattleScript_MoveEnd
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_TormentTrySpite::
	tryspiteppreduce BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_TormentJustRandomStatDrop::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	statbuffchange MOVE_EFFECT_CERTAIN, BattleScript_MoveEnd
	printstring STRINGID_DEFENDERSSTATFELL
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectFlatter::
	attackcanceler
	jumpifsubstituteblocks BattleScript_MakeMoveMissed
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifconfusedandstatmaxed STAT_SPATK, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_FlatterTryConfuse
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_FlatterTryConfuse
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FlatterTryConfuse::
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_OwnTempoPrevents
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_OwnTempoPrevents
	jumpifsafeguard BattleScript_SafeguardProtected
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectWillOWisp::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_BURN, BattleScript_AlreadyBurned
	jumpiftype BS_TARGET, TYPE_FIRE, BattleScript_NotAffected
	jumpifability BS_TARGET, ABILITY_WATER_BUBBLE, BattleScript_WaterVeilPrevents
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET_SIDE, ABILITY_WATER_VEIL, BattleScript_WaterVeilProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	jumpifholdeffect BS_TARGET, HOLD_EFFECT_NEVER_MELT_ICE, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_BURN
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_WaterVeilPrevents::
	call BattleScript_AbilityPopUp
	copybyte gEffectBattler, gBattlerTarget
	setbyte cMULTISTRING_CHOOSER, B_MSG_ABILITY_PREVENTS_MOVE_STATUS
	call BattleScript_BRNPrevention
	goto BattleScript_MoveEnd

BattleScript_AlreadyBurned::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNALREADYHASBURN
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectMemento::
	attackcanceler
	jumpifbyte CMP_EQUAL, cMISS_TYPE, B_MSG_PROTECTED, BattleScript_MementoTargetProtect
	attackstring
	ppreduce
	trymemento BattleScript_ButItFailed
	setatkhptozero
	attackanimation
	waitanimation
	jumpifsubstituteblocks BattleScript_EffectMementoPrintNoEffect
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_NEGATIVE | STAT_CHANGE_BY_TWO | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_NEGATIVE | STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 2, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectMementoTrySpAtk
@ Greater than B_MSG_DEFENDER_STAT_FELL is checking if the stat cannot decrease
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_FELL, BattleScript_EffectMementoTrySpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectMementoTrySpAtk:
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_NEGATIVE | STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPATK, 2, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_EffectMementoTryFaint
@ Greater than B_MSG_DEFENDER_STAT_FELL is checking if the stat cannot decrease
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_FELL, BattleScript_EffectMementoTryFaint
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectMementoTryFaint:
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd
BattleScript_EffectMementoPrintNoEffect:
	printstring STRINGID_BUTNOEFFECT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectMementoTryFaint
@ If the target is protected there's no need to check the target's stats or animate, the user will just faint
BattleScript_MementoTargetProtect:
	attackstring
	ppreduce
	trymemento BattleScript_MementoTargetProtectEnd
BattleScript_MementoTargetProtectEnd:
	setatkhptozero
	pause B_WAIT_TIME_LONG
	effectivenesssound
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectFocusPunch::
	attackcanceler
	jumpiffocusenergy BS_ATTACKER, BattleScript_HitFromAccCheck
	jumpifnodamage BattleScript_HitFromAccCheck
	ppreduce
	printstring STRINGID_PKMNLOSTFOCUS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSmellingsalt:
BattleScript_EffectWakeUpSlap:
BattleScript_EffectSparklingAria:
	jumpifsubstituteblocks BattleScript_EffectHit
	setmoveeffect MOVE_EFFECT_REMOVE_STATUS | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectFollowMe::
	attackcanceler
	attackstring
	ppreduce
	.if B_UPDATED_MOVE_DATA >= GEN_6
	jumpifnotbattletype BATTLE_TYPE_DOUBLE, BattleScript_ButItFailed
	.endif
	setforcedtarget
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCENTERATTENTION
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectNaturePower::
	attackcanceler
	attackstring
	pause B_WAIT_TIME_SHORT
	callterrainattack
	printstring STRINGID_NATUREPOWERTURNEDINTO
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectCharge::
	attackcanceler
	attackstring
	ppreduce
	setcharge BS_ATTACKER
	jumpifterrainaffected BS_ATTACKER, STATUS_FIELD_ELECTRIC_TERRAIN, BattleScript_ChargeElectricTerrain
	attackanimation
	waitanimation
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ChargeEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ChargeEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNCHARGINGPOWER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_ChargeElectricTerrain:
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_ChargeDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_ChargeDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK, 0
	setstatchanger STAT_SPDEF, 1, FALSE
	goto BattleScript_ChargeSpDef
BattleScript_ChargeSpDef:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ChargeTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ChargeTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ChargeTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	goto BattleScript_ChargeSpAtk
BattleScript_ChargeSpAtk:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ChargeEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ChargeEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ChargeEnd:
	printstring STRINGID_PKMNCHARGINGPOWER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectTaunt::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_AbilityProtectsDoesntAffect
	jumpifsafeguard BattleScript_SafeguardProtected
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	settaunt BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNFELLFORTAUNT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTauntAttacker
	goto BattleScript_MoveEnd

BattleScript_EffectHelpingHand::
	attackcanceler
	attackstring
	ppreduce
	trysethelpinghand BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNREADYTOHELP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectTrick::
	attackcanceler
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	tryswapitems BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDITEMS
	waitmessage B_WAIT_TIME_LONG
	printfromtable gItemSwapStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRolePlay::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	trycopyability BattleScript_ButItFailed
	attackanimation
	waitanimation
.if B_ABILITY_POP_UP == TRUE
	setbyte sFIXED_ABILITY_POPUP, TRUE
	showabilitypopup BS_ATTACKER
	pause 60
	sethword sABILITY_OVERWRITE, 0
	updateabilitypopup BS_ATTACKER
	pause 20
	destroyabilitypopup
	pause 40
.endif
	printstring STRINGID_PKMNCOPIEDFOE
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectWish::
	attackcanceler
	attackstring
	ppreduce
	trywish 0, BattleScript_ButItFailed
	attackanimation
	waitanimation
	goto BattleScript_MoveEnd

BattleScript_EffectAssist:
	attackcanceler
	attackstring
	assistattackselect BattleScript_FailedFromPpReduce
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	jumptocalledmove TRUE

BattleScript_EffectIngrain:
	attackcanceler
	attackstring
	ppreduce
	setuserstatus3 STATUS3_ROOTED, BattleScript_IngrainUserBlooming
	jumpiftype BS_ATTACKER, TYPE_FIRE, BattleScript_EffectIngrainSucceededBloomingFailed
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_EffectIngrainSucceededBloomingFailed
	jumpifstatus BS_ATTACKER, STATUS1_ANY, BattleScript_EffectIngrainSucceededBloomingFailed
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	printstring STRINGID_PKMNPLANTEDROOTS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_IngrainUserBlooming::
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpiftype BS_ATTACKER, TYPE_FIRE, BattleScript_ButItFailed
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_ButItFailed
	jumpifstatus BS_ATTACKER, STATUS1_ANY, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_BLOOMING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	goto BattleScript_MoveEnd
BattleScript_EffectIngrainSucceededBloomingFailed::
	attackanimation
	waitanimation
	printstring STRINGID_PKMNPLANTEDROOTS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSuperpower::
	setmoveeffect MOVE_EFFECT_ATK_TWO_DOWN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectCloseCombat:
	setmoveeffect MOVE_EFFECT_DEF_SPDEF_DOWN_USER | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectMagicCoat:
	attackcanceler
	trysetmagiccoat BS_TARGET, BattleScript_FailedFromAtkString
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSHROUDEDITSELF
	waitmessage B_WAIT_TIME_LONG
	jumpifnoally BS_ATTACKER, BattleScript_MoveEnd
	setallytonexttarget BattleScript_MagicCoatOnAlly
	goto BattleScript_MoveEnd
BattleScript_MagicCoatOnAlly::
	trysetmagiccoat BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_PKMNWASSHROUDEDBY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRecycle::
	attackcanceler
	attackstring
	ppreduce
	tryrecycleitem BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_XFOUNDONEY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectBrickBreak::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	removelightscreenreflect
	critcalc
	damagecalc
	adjustdamage
	jumpifbyte CMP_EQUAL, sB_ANIM_TURN, 0, BattleScript_BrickBreakAnim
	bichalfword gMoveResultFlags, MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE
BattleScript_BrickBreakAnim::
	attackanimation
	waitanimation
	jumpifbyte CMP_LESS_THAN, sB_ANIM_TURN, 2, BattleScript_BrickBreakDoHit
	printstring STRINGID_THEWALLSHATTERED
	waitmessage B_WAIT_TIME_LONG
BattleScript_BrickBreakDoHit::
	typecalc
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectYawn::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_VITAL_SPIRIT, BattleScript_PrintBattlerAbilityMadeIneffective
	jumpifability BS_TARGET, ABILITY_INSOMNIA, BattleScript_PrintBattlerAbilityMadeIneffective
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_PrintBattlerAbilityMadeIneffective
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_AbilityProtectsDoesntAffect
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_AbilityProtectsDoesntAffect
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguardprotected BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifeeriemaskprotected BS_TARGET, BattleScript_ItemProtectsDoesntAffect
	jumpifshieldsdown BS_TARGET, BattleScript_AbilityProtectsDoesntAffect
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpifgearmagnet BS_TARGET, BattleScript_ButItFailed
	jumpifsafeguard BattleScript_SafeguardProtected
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifuproarwakes BattleScript_ButItFailed
	setyawn BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNWASMADEDROWSY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_PrintBattlerAbilityMadeIneffective::
	copybyte sBATTLER, gBattlerAbility
BattleScript_PrintAbilityMadeIneffective::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXMADEITINEFFECTIVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectKnockOff::
	setmoveeffect MOVE_EFFECT_KNOCK_OFF
	goto BattleScript_EffectHit

BattleScript_EffectEndeavor::
	attackcanceler
	attackstring
	ppreduce
	setdamagetohealthdifference BattleScript_ButItFailed
	copyword gHpDealt, gBattleMoveDamage
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	typecalc
	jumpifmovehadnoeffect BattleScript_HitFromAtkAnimation
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	copyword gBattleMoveDamage, gHpDealt
	adjustdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectSkillSwap:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	tryswapabilities BattleScript_ButItFailed
	attackanimation
	waitanimation
.if B_ABILITY_POP_UP == TRUE
	call BattleScript_AbilityPopUpTarget
	pause 20
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
.endif
	printstring STRINGID_PKMNSWAPPEDABILITIES
	waitmessage B_WAIT_TIME_LONG
.if B_SKILL_SWAP >= GEN_4
	switchinabilities BS_ATTACKER
	switchinabilities BS_TARGET
.endif
	goto BattleScript_MoveEnd

BattleScript_EffectImprison::
	attackcanceler
	jumpifsubstituteblocks BattleScript_FailedFromAtkString
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	trysetimprison BS_TARGET, BattleScript_ButItFailed, BattleScript_ImprisonBothEffects
	attackanimation
	waitanimation
	printstring STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_ImprisonBothEffects::
	attackanimation
	waitanimation
	printstring STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNMOVEWASDISABLED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRefresh:
	jumpifnoally BS_ATTACKER, BattleScript_EffectRefreshSingleBattle
	attackcanceler
	attackstring
	ppreduce
	curestatuswithmove BS_TARGET, BattleScript_UserRefreshFailed
	tryresetnegativestatstages BS_TARGET
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	setallytonexttarget BattleScript_EffectRefreshAlly
	goto BattleScript_MoveEnd
BattleScript_EffectRefreshAlly:
	curestatuswithmove BS_TARGET, BattleScript_AllyRefreshFailed
	tryresetnegativestatstages BS_TARGET
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	printstring STRINGID_TARGETNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_EffectRefreshSingleBattle::
	attackcanceler
	attackstring
	ppreduce
	curestatuswithmove BS_TARGET, BattleScript_UserRefreshFailed
	tryresetnegativestatstages BS_TARGET
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd
BattleScript_UserRefreshFailed::
	tryresetnegativestatstages BS_TARGET
	attackanimation
	waitanimation
	printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	jumpifnoally BS_ATTACKER, BattleScript_MoveEnd
	setallytonexttarget BattleScript_EffectRefreshAlly
	goto BattleScript_MoveEnd
BattleScript_AllyRefreshFailed::
	tryresetnegativestatstages BS_TARGET
	printstring STRINGID_TARGETNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGrudge:
	attackcanceler
	attackstring
	ppreduce
	setuserstatus3 STATUS3_GRUDGE, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNWANTSGRUDGE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSnatch:
	attackcanceler
	trysetsnatch BattleScript_FailedFromAtkString
	attackstring
	ppreduce
	attackanimation
	waitanimation
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNWAITSFORTARGET
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSecretPower::
	getsecretpowereffect
	goto BattleScript_EffectHit

BattleScript_EffectRecoilHP25:
	setmoveeffect MOVE_EFFECT_RECOIL_HP_25 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	jumpifnotmove MOVE_STRUGGLE, BattleScript_EffectHit
	incrementgamestat GAME_STAT_USED_STRUGGLE
	goto BattleScript_EffectHit

BattleScript_EffectTeeterDance::
	attackcanceler
	attackstring
	ppreduce
	setbyte gBattlerTarget, 0
BattleScript_TeeterDanceLoop::
	movevaluescleanup
	setmoveeffect MOVE_EFFECT_CONFUSION
	jumpifbyteequal gBattlerAttacker, gBattlerTarget, BattleScript_TeeterDanceLoopIncrement
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_TeeterDanceOwnTempoPrevents
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_TeeterDanceOwnTempoPrevents
	jumpiftype BS_TARGET, TYPE_PSYCHIC, BattleScript_TeeterDanceSubstitutePrevents
	jumpifsubstituteblocks BattleScript_TeeterDanceSubstitutePrevents
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_TeeterDanceAlreadyConfused
	jumpifhasnohp BS_TARGET, BattleScript_TeeterDanceLoopIncrement
	accuracycheck BattleScript_TeeterDanceMissed, ACC_CURR_MOVE
	jumpifsafeguard BattleScript_TeeterDanceSafeguardProtected
	attackanimation
	waitanimation
	seteffectprimary
	resultmessage
	waitmessage B_WAIT_TIME_LONG
BattleScript_TeeterDanceDoMoveEndIncrement::
	moveendto MOVEEND_NEXT_TARGET
BattleScript_TeeterDanceLoopIncrement::
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_TeeterDanceLoop
	goto BattleScript_MoveEnd @required to continue Dance Mania Loop
	end

BattleScript_TeeterDanceOwnTempoPrevents::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNPREVENTSCONFUSIONWITH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TeeterDanceDoMoveEndIncrement

BattleScript_TeeterDanceSafeguardProtected::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TeeterDanceDoMoveEndIncrement

BattleScript_TeeterDanceSubstitutePrevents::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_BUTITFAILED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TeeterDanceDoMoveEndIncrement

BattleScript_TeeterDanceAlreadyConfused::
	setalreadystatusedmoveattempt BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNALREADYCONFUSED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TeeterDanceDoMoveEndIncrement

BattleScript_TeeterDanceMissed::
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TeeterDanceDoMoveEndIncrement

BattleScript_EffectMudSport::
BattleScript_EffectWaterSport::
	attackcanceler
	attackstring
	ppreduce
	settypebasedhalvers BattleScript_ButItFailed
	attackanimation
	waitanimation
	printfromtable gSportsUsedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectPoisonFang::
	setmoveeffect MOVE_EFFECT_TOXIC
	goto BattleScript_EffectHit

BattleScript_EffectOverheat::
	jumpifdoublesmovesucceed BS_ATTACKER, BattleScript_NoMoveEffect
	setmoveeffect MOVE_EFFECT_SP_ATK_MINUS_2 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
    call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_DoublesSkipEffect
	setdoublesmovesucceed BS_ATTACKER
	seteffectwithchance
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd
BattleScript_DoublesSkipEffect:
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectHammerArm::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectTickle::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, MIN_STAT_STAGE, BattleScript_TickleDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_DEF, MIN_STAT_STAGE, BattleScript_CantLowerMultipleStats
BattleScript_TickleDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_TickleTryLowerDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_TickleTryLowerDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TickleTryLowerDef::
	playstatchangeanimation BS_TARGET, BIT_DEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_TickleEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_TickleEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TickleEnd::
	goto BattleScript_MoveEnd

BattleScript_CantLowerMultipleStats::
	pause B_WAIT_TIME_SHORT
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	printstring STRINGID_STATSWONTDECREASE2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectCosmicPower::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_CosmicPowerDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_EffectBide1
BattleScript_CosmicPowerDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CosmicPowerTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CosmicPowerTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CosmicPowerTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CosmicPowerEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CosmicPowerEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CosmicPowerEnd::
	jumpifmove MOVE_BIDE, BattleScript_EffectBide2
	goto BattleScript_MoveEnd

BattleScript_EffectSkyUppercut::
	goto BattleScript_EffectHit

BattleScript_EffectBulkUp::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_BulkUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_DEF, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_BulkUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_BulkUpTryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_BulkUpTryDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_BulkUpTryDef::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_BulkUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_BulkUpEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_BulkUpEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectCalmMind::
	attackcanceler
	attackstring
	ppreduce
BattleScript_CalmMindTryToRaiseStats::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CalmMindDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_CalmMindDoMoveAnim::
	attackanimation
	waitanimation
BattleScript_CalmMindStatRaise::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CalmMindTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CalmMindTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CalmMindTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_CalmMindEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CalmMindEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CalmMindEnd::
	goto BattleScript_MoveEnd

BattleScript_CantRaiseMultipleStats::
	pause B_WAIT_TIME_SHORT
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	printstring STRINGID_STATSWONTINCREASE2
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectDragonDance::
	attackcanceler
	attackstring
	ppreduce
BattleScript_EffectDragonDanceFromStatUp::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_DragonDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_DragonDanceDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPEED, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_DragonDanceTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DragonDanceTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DragonDanceTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_DragonDanceEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DragonDanceEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DragonDanceEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectCamouflage::
	attackcanceler
	attackstring
	ppreduce
	settypetoterrain BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_FaintAttacker::
	playfaintcry BS_ATTACKER
	pause B_WAIT_TIME_SHORT
	dofaintanimation BS_ATTACKER
	printstring STRINGID_ATTACKERFAINTED
	cleareffectsonfaint BS_ATTACKER
	tryactivatesoulheart
	tryactivatereceiver BS_ATTACKER
	trytrainerslidefirstdownmsg BS_ATTACKER
	return

BattleScript_FaintTarget::
	tryillusionoff BS_TARGET
	playfaintcry BS_TARGET
	pause B_WAIT_TIME_SHORT
	dofaintanimation BS_TARGET
	printstring STRINGID_TARGETFAINTED
	cleareffectsonfaint BS_TARGET
	tryactivatefellstinger BS_ATTACKER
	tryactivateheartcarve BS_ATTACKER
	tryactivatestarassault BS_ATTACKER
	tryactivateshadowforce BS_ATTACKER
	tryactivatesoulheart
	tryactivatereceiver BS_TARGET
	tryactivatemoxie BS_ATTACKER        @ and chilling neigh, as one ice rider
	tryactivateappetite BS_ATTACKER
	tryactivatebeastboost BS_ATTACKER
	tryactivategrimneigh BS_ATTACKER    @ and as one shadow rider
	tryactivatebattlebond BS_ATTACKER
	trytrainerslidefirstdownmsg BS_TARGET
	return

BattleScript_GiveExp::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_TARGET
	end2

BattleScript_HandleFaintedMon::
	setbyte sSHIFT_SWITCHED, 0
	checkteamslost BattleScript_LinkHandleFaintedMonMultiple
	jumpifbyte CMP_NOT_EQUAL, gBattleOutcome, 0, BattleScript_FaintedMonEnd
	jumpifbattletype BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE, BattleScript_FaintedMonTryChoose
	jumpifword CMP_NO_COMMON_BITS, gHitMarker, HITMARKER_PLAYER_FAINTED, BattleScript_FaintedMonTryChoose
@ Yes/No for sending out a new Pokémon if one is defeated in a wild battle
	printstring STRINGID_USENEXTPKMN
	setbyte gBattleCommunication, 0
	yesnobox
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, 0, BattleScript_FaintedMonTryChoose
@ Player said no, try to run
	jumpifplayerran BattleScript_FaintedMonEnd
	printstring STRINGID_CANTESCAPE2
BattleScript_FaintedMonTryChoose:
	openpartyscreen BS_FAINTED, BattleScript_FaintedMonEnd
	switchhandleorder BS_FAINTED, 2
	jumpifnotbattletype BATTLE_TYPE_TRAINER, BattleScript_FaintedMonSendOutNew
	jumpifbattletype BATTLE_TYPE_LINK, BattleScript_FaintedMonSendOutNew
	jumpifbattletype BATTLE_TYPE_RECORDED_LINK, BattleScript_FaintedMonSendOutNew
	jumpifbattletype BATTLE_TYPE_FRONTIER, BattleScript_FaintedMonSendOutNew
	jumpifbattletype BATTLE_TYPE_DOUBLE, BattleScript_FaintedMonSendOutNew
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_PLAYER_FAINTED, BattleScript_FaintedMonSendOutNew
	jumpifbyte CMP_EQUAL, sBATTLE_STYLE, OPTIONS_BATTLE_STYLE_SET, BattleScript_FaintedMonSendOutNew
	jumpifcantswitch BS_PLAYER1, BattleScript_FaintedMonSendOutNew
	setbyte sILLUSION_NICK_HACK, 1
@ Yes/No for sending out a new Pokémon when the opponent is switching
	printstring STRINGID_ENEMYABOUTTOSWITCHPKMN
	setbyte gBattleCommunication, 0
	yesnobox
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, 1, BattleScript_FaintedMonSendOutNew
@ Player said yes, go to party screen (note optional flag, player may exit the menu instead)
	setatktoplayer0
	openpartyscreen BS_ATTACKER | PARTY_SCREEN_OPTIONAL, BattleScript_FaintedMonSendOutNew
	switchhandleorder BS_ATTACKER, 2
	jumpifbyte CMP_EQUAL, gBattleCommunication, PARTY_SIZE, BattleScript_FaintedMonSendOutNew
@ Switch Pokémon before opponent
	atknameinbuff1
	resetswitchinabilitybits BS_ATTACKER
	hpthresholds2 BS_ATTACKER
	printstring STRINGID_RETURNMON
	switchoutabilities BS_ATTACKER
	waitstate
	returnatktoball
	waitstate
	drawpartystatussummary BS_ATTACKER
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring STRINGID_SWITCHINMON
	hidepartystatussummary BS_ATTACKER
	switchinanim BS_ATTACKER, 0
	waitstate
	setbyte sSHIFT_SWITCHED, 1
BattleScript_FaintedMonSendOutNew:
	drawpartystatussummary BS_FAINTED
	getswitchedmondata BS_FAINTED
	switchindataupdate BS_FAINTED
	hpthresholds BS_FAINTED
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring STRINGID_SWITCHINMON
	hidepartystatussummary BS_FAINTED
	switchinanim BS_FAINTED, FALSE
	waitstate
	resetplayerfainted
	trytrainerslidelastonmsg BS_FAINTED
	jumpifbytenotequal sSHIFT_SWITCHED, sZero, BattleScript_FaintedMonShiftSwitched
BattleScript_FaintedMonSendOutNewEnd:
	switchineffects BS_FAINTED
	jumpifbattletype BATTLE_TYPE_DOUBLE, BattleScript_FaintedMonEnd
	cancelallactions
BattleScript_FaintedMonEnd::
	end2
BattleScript_FaintedMonShiftSwitched:
	copybyte sSAVED_BATTLER, gBattlerTarget
	switchineffects BS_ATTACKER
	resetsentmonsvalue
	copybyte gBattlerTarget, sSAVED_BATTLER
	goto BattleScript_FaintedMonSendOutNewEnd

BattleScript_LinkHandleFaintedMonMultiple::
	openpartyscreen BS_FAINTED_LINK_MULTIPLE_1, BattleScript_LinkHandleFaintedMonMultipleStart
BattleScript_LinkHandleFaintedMonMultipleStart::
	switchhandleorder BS_FAINTED, 0
	openpartyscreen BS_FAINTED_LINK_MULTIPLE_2, BattleScript_LinkHandleFaintedMonMultipleEnd
	switchhandleorder BS_FAINTED, 0
BattleScript_LinkHandleFaintedMonLoop::
	switchhandleorder BS_FAINTED, 3
	drawpartystatussummary BS_FAINTED
	getswitchedmondata BS_FAINTED
	switchindataupdate BS_FAINTED
	hpthresholds BS_FAINTED
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring STRINGID_SWITCHINMON
	hidepartystatussummary BS_FAINTED
	switchinanim BS_FAINTED, FALSE
	waitstate
	switchineffects BS_FAINTED_LINK_MULTIPLE_1
	jumpifbytenotequal gBattlerFainted, gBattlersCount, BattleScript_LinkHandleFaintedMonLoop
BattleScript_LinkHandleFaintedMonMultipleEnd::
	end2

BattleScript_LocalTrainerBattleWon::
	jumpifbattletype BATTLE_TYPE_TWO_OPPONENTS, BattleScript_LocalTwoTrainersDefeated
	printstring STRINGID_PLAYERDEFEATEDTRAINER1
	goto BattleScript_LocalBattleWonLoseTexts
BattleScript_LocalTwoTrainersDefeated::
	printstring STRINGID_TWOENEMIESDEFEATED
BattleScript_LocalBattleWonLoseTexts::
	trainerslidein BS_ATTACKER
	waitstate
	printstring STRINGID_TRAINER1LOSETEXT
	jumpifnotbattletype BATTLE_TYPE_TWO_OPPONENTS, BattleScript_LocalBattleWonReward
	trainerslideout B_POSITION_OPPONENT_LEFT
	waitstate
	trainerslidein BS_FAINTED
	waitstate
	printstring STRINGID_TRAINER2LOSETEXT
BattleScript_LocalBattleWonReward::
	getmoneyreward
	printstring STRINGID_PLAYERGOTMONEY
	waitmessage B_WAIT_TIME_LONG
BattleScript_PayDayMoneyAndPickUpItems::
	givepaydaymoney
	pickup
	end2

BattleScript_LocalBattleLost::
	jumpifbattletype BATTLE_TYPE_INGAME_PARTNER, BattleScript_LocalBattleLostPrintWhiteOut
	jumpifbattletype BATTLE_TYPE_DOME, BattleScript_CheckDomeDrew
	jumpifbattletype BATTLE_TYPE_FRONTIER, BattleScript_LocalBattleLostPrintTrainersWinText
	jumpifbattletype BATTLE_TYPE_TRAINER_HILL, BattleScript_LocalBattleLostPrintTrainersWinText
	jumpifbattletype BATTLE_TYPE_EREADER_TRAINER, BattleScript_LocalBattleLostEnd
	jumpifhalfword CMP_EQUAL, gTrainerBattleOpponent_A, TRAINER_SECRET_BASE, BattleScript_LocalBattleLostEnd
BattleScript_LocalBattleLostPrintWhiteOut::
.if B_WHITEOUT_MONEY >= GEN_4
	jumpifbattletype BATTLE_TYPE_TRAINER, BattleScript_LocalBattleLostEnd
	printstring STRINGID_PLAYERWHITEOUT
	waitmessage B_WAIT_TIME_LONG
	getmoneyreward
	printstring STRINGID_PLAYERWHITEOUT2
	waitmessage B_WAIT_TIME_LONG
	end2
BattleScript_LocalBattleLostEnd::
	printstring STRINGID_PLAYERLOSTTOENEMYTRAINER
	waitmessage B_WAIT_TIME_LONG
	getmoneyreward
	printstring STRINGID_PLAYERPAIDPRIZEMONEY
	waitmessage B_WAIT_TIME_LONG
	end2
.else
	printstring STRINGID_PLAYERWHITEOUT
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PLAYERWHITEOUT2
	waitmessage B_WAIT_TIME_LONG
BattleScript_LocalBattleLostEnd::
	end2
.endif

BattleScript_LocalBattleLostGym::
	printstring STRINGID_PLAYERWHITEOUT
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PLAYERWHITEOUT3
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_CheckDomeDrew::
	jumpifbyte CMP_EQUAL, gBattleOutcome, B_OUTCOME_DREW, BattleScript_LocalBattleLostEnd_
BattleScript_LocalBattleLostPrintTrainersWinText::
	jumpifnotbattletype BATTLE_TYPE_TRAINER, BattleScript_LocalBattleLostPrintWhiteOut
	returnopponentmon1toball BS_ATTACKER
	waitstate
	returnopponentmon2toball BS_ATTACKER
	waitstate
	trainerslidein BS_ATTACKER
	waitstate
	printstring STRINGID_TRAINER1WINTEXT
	jumpifbattletype BATTLE_TYPE_TOWER_LINK_MULTI, BattleScript_LocalBattleLostDoTrainer2WinText
	jumpifnotbattletype BATTLE_TYPE_TWO_OPPONENTS, BattleScript_LocalBattleLostEnd_
BattleScript_LocalBattleLostDoTrainer2WinText::
	trainerslideout B_POSITION_OPPONENT_LEFT
	waitstate
	trainerslidein BS_FAINTED
	waitstate
	printstring STRINGID_TRAINER2WINTEXT
BattleScript_LocalBattleLostEnd_::
	end2

BattleScript_FrontierLinkBattleLost::
	returnopponentmon1toball BS_ATTACKER
	waitstate
	returnopponentmon2toball BS_ATTACKER
	waitstate
	trainerslidein BS_ATTACKER
	waitstate
	printstring STRINGID_TRAINER1WINTEXT
	trainerslideout B_POSITION_OPPONENT_LEFT
	waitstate
	trainerslidein BS_FAINTED
	waitstate
	printstring STRINGID_TRAINER2WINTEXT
	jumpifbattletype BATTLE_TYPE_RECORDED, BattleScript_FrontierLinkBattleLostEnd
	endlinkbattle
BattleScript_FrontierLinkBattleLostEnd::
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_LinkBattleWonOrLost::
	jumpifbattletype BATTLE_TYPE_BATTLE_TOWER, BattleScript_TowerLinkBattleWon
	printstring STRINGID_BATTLEEND
	waitmessage B_WAIT_TIME_LONG
	jumpifbattletype BATTLE_TYPE_RECORDED, BattleScript_LinkBattleWonOrLostWaitEnd
	endlinkbattle
BattleScript_LinkBattleWonOrLostWaitEnd::
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_TowerLinkBattleWon::
	playtrainerdefeatbgm BS_ATTACKER
	printstring STRINGID_BATTLEEND
	waitmessage B_WAIT_TIME_LONG
	trainerslidein BS_ATTACKER
	waitstate
	printstring STRINGID_TRAINER1LOSETEXT
	trainerslideout B_POSITION_OPPONENT_LEFT
	waitstate
	trainerslidein BS_FAINTED
	waitstate
	printstring STRINGID_TRAINER2LOSETEXT
	jumpifbattletype BATTLE_TYPE_RECORDED, BattleScript_TowerLinkBattleWonEnd
	endlinkbattle
BattleScript_TowerLinkBattleWonEnd::
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_FrontierTrainerBattleWon::
	jumpifnotbattletype BATTLE_TYPE_TRAINER, BattleScript_PayDayMoneyAndPickUpItems
	jumpifbattletype BATTLE_TYPE_TWO_OPPONENTS, BattleScript_FrontierTrainerBattleWon_TwoDefeated
	printstring STRINGID_PLAYERDEFEATEDTRAINER1
	goto BattleScript_FrontierTrainerBattleWon_LoseTexts
BattleScript_FrontierTrainerBattleWon_TwoDefeated:
	printstring STRINGID_TWOENEMIESDEFEATED
BattleScript_FrontierTrainerBattleWon_LoseTexts:
	trainerslidein BS_ATTACKER
	waitstate
	printstring STRINGID_TRAINER1LOSETEXT
	jumpifnotbattletype BATTLE_TYPE_TWO_OPPONENTS, BattleScript_TryPickUpItems
	trainerslideout B_POSITION_OPPONENT_LEFT
	waitstate
	trainerslidein BS_FAINTED
	waitstate
	printstring STRINGID_TRAINER2LOSETEXT
BattleScript_TryPickUpItems:
	jumpifnotbattletype BATTLE_TYPE_PYRAMID, BattleScript_FrontierTrainerBattleWon_End
	pickup
BattleScript_FrontierTrainerBattleWon_End:
	end2

BattleScript_SmokeBallEscape::
	playanimation BS_ATTACKER, B_ANIM_SMOKEBALL_ESCAPE
	printstring STRINGID_PKMNFLEDUSINGITS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_RanAwayUsingMonAbility::
	printstring STRINGID_PKMNFLEDUSING
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_GotAwaySafely::
	printstring STRINGID_GOTAWAYSAFELY
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_WildMonFled::
	printstring STRINGID_WILDPKMNFLED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_PrintCantRunFromTrainer::
	printstring STRINGID_NORUNNINGFROMTRAINERS
	end2

BattleScript_PrintFailedToRunString::
	printfromtable gNoEscapeStringIds
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_PrintCantEscapeFromBattle::
	printselectionstringfromtable gNoEscapeStringIds
	endselectionscript

BattleScript_PrintFullBox::
	printselectionstring STRINGID_BOXISFULL
	endselectionscript

BattleScript_ActionSwitch::
	hpthresholds2 BS_ATTACKER
	printstring STRINGID_RETURNMON
	jumpifbattletype BATTLE_TYPE_DOUBLE, BattleScript_PursuitSwitchDmgSetMultihit
	setmultihit 1
	goto BattleScript_PursuitSwitchDmgLoop
BattleScript_PursuitSwitchDmgSetMultihit::
	setmultihit 2
BattleScript_PursuitSwitchDmgLoop::
	jumpifpursuit BattleScript_HandlePursuit
BattleScript_DoSwitchOut::
	decrementmultihit BattleScript_PursuitSwitchDmgLoop
	switchoutabilities BS_ATTACKER
	waitstate
	returnatktoball
	waitstate
	drawpartystatussummary BS_ATTACKER
	switchhandleorder BS_ATTACKER, 1
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring STRINGID_SWITCHINMON
	hidepartystatussummary BS_ATTACKER
	switchinanim BS_ATTACKER, FALSE
	waitstate
	switchineffects BS_ATTACKER
	moveendcase MOVEEND_STATUS_IMMUNITY_ABILITIES
	moveendcase MOVEEND_MIRROR_MOVE
	end2

BattleScript_HandlePursuit::
	swapattackerwithtarget
	trysetdestinybondtohappen
	call BattleScript_PursuitDmgOnSwitchOut
	swapattackerwithtarget
	call BattleScript_DoSwitchOut

BattleScript_PursuitDmgOnSwitchOut::
	pause B_WAIT_TIME_SHORT
	attackstring
	ppreduce
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	moveendfromto MOVEEND_ABILITIES, MOVEEND_CHOICE_MOVE
	jumpiffainted BS_TARGET, FALSE, BattleScript_PursuitDmgOnSwitchOutRet
	setbyte sGIVEEXP_STATE, 0
	getexp BS_TARGET
BattleScript_PursuitDmgOnSwitchOutRet:
	return

BattleScript_Pausex20::
	pause B_WAIT_TIME_SHORT
	return

BattleScript_LevelUpWithEvoSugg::
	fanfare MUS_LEVEL_UP
	printstring STRINGID_PKMNCANEVOLVE
	setbyte sLVLBOX_STATE, 0
	drawlvlupbox
	handlelearnnewmove BattleScript_LearnedNewMove, BattleScript_LearnMoveReturn, TRUE
	goto BattleScript_AskToLearnMove
BattleScript_LevelUp::
	fanfare MUS_LEVEL_UP
	printstring STRINGID_PKMNGREWTOLV
	setbyte sLVLBOX_STATE, 0
	drawlvlupbox
	handlelearnnewmove BattleScript_LearnedNewMove, BattleScript_LearnMoveReturn, TRUE
	goto BattleScript_AskToLearnMove
BattleScript_TryLearnMoveLoop::
	handlelearnnewmove BattleScript_LearnedNewMove, BattleScript_LearnMoveReturn, FALSE
BattleScript_AskToLearnMove::
	buffermovetolearn
	printstring STRINGID_TRYTOLEARNMOVE1
	printstring STRINGID_TRYTOLEARNMOVE2
	printstring STRINGID_TRYTOLEARNMOVE3
	waitstate
	setbyte sLEARNMOVE_STATE, 0
	yesnoboxlearnmove BattleScript_ForgotAndLearnedNewMove
	printstring STRINGID_STOPLEARNINGMOVE
	waitstate
	setbyte sLEARNMOVE_STATE, 0
	yesnoboxstoplearningmove BattleScript_AskToLearnMove
	printstring STRINGID_DIDNOTLEARNMOVE
	goto BattleScript_TryLearnMoveLoop
BattleScript_ForgotAndLearnedNewMove::
	printstring STRINGID_123POOF
	printstring STRINGID_PKMNFORGOTMOVE
	printstring STRINGID_ANDELLIPSIS
BattleScript_LearnedNewMove::
	buffermovetolearn
	fanfare MUS_LEVEL_UP
	printstring STRINGID_PKMNLEARNEDMOVE
	waitmessage B_WAIT_TIME_LONG
	updatechoicemoveonlvlup BS_ATTACKER
	goto BattleScript_TryLearnMoveLoop
BattleScript_LearnMoveReturn::
	return

BattleScript_RainContinuesOrEnds::
	printfromtable gRainContinuesStringIds
	waitmessage B_WAIT_TIME_LONG
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_RAIN_STOPPED, BattleScript_RainContinuesOrEndsEnd
	playanimation BS_ATTACKER, B_ANIM_RAIN_CONTINUES
BattleScript_RainContinuesOrEndsEnd::
	call BattleScript_ActivateWeatherAbilities
	end2

BattleScript_DamagingWeatherContinues::
	printfromtable gSandStormHailSnowContinuesStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation_var BS_ATTACKER, sB_ANIM_ARG1
	setbyte gBattleCommunication, 0
BattleScript_DamagingWeatherLoop::
	copyarraywithindex gBattlerAttacker, gBattlerByTurnOrder, gBattleCommunication, 1
	weatherdamage
	jumpifword CMP_EQUAL, gBattleMoveDamage, 0, BattleScript_DamagingWeatherLoopIncrement
	jumpifword CMP_COMMON_BITS gBattleMoveDamage, 1 << 31, BattleScript_DamagingWeatherHeal
	printfromtable gSandStormHailDmgStringIds
	waitmessage B_WAIT_TIME_LONG
	effectivenesssound
	hitanimation BS_ATTACKER
	goto BattleScript_DamagingWeatherHpChange
BattleScript_DamagingWeatherHeal:
	call BattleScript_AbilityPopUp
	printstring STRINGID_ICEBODYHPGAIN
	waitmessage B_WAIT_TIME_LONG
BattleScript_DamagingWeatherHpChange:
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_GRUDGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	checkteamslost BattleScript_DamagingWeatherLoopIncrement
BattleScript_DamagingWeatherLoopIncrement::
	jumpifbyte CMP_NOT_EQUAL, gBattleOutcome, 0, BattleScript_DamagingWeatherContinuesEnd
	addbyte gBattleCommunication, 1
	jumpifbytenotequal gBattleCommunication, gBattlersCount, BattleScript_DamagingWeatherLoop
BattleScript_DamagingWeatherContinuesEnd::
	bicword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_GRUDGE
	call BattleScript_ActivateWeatherAbilities
	end2

BattleScript_SandStormHailSnowEnds::
	printfromtable gSandStormHailSnowEndStringIds
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	end2

BattleScript_SunlightContinues::
	printstring STRINGID_SUNLIGHTSTRONG
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_SUN_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end2

BattleScript_SunlightFaded::
	printstring STRINGID_SUNLIGHTFADED
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	end2

BattleScript_OverworldWeatherStarts::
	printfromtable gWeatherStartsStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation_var BS_BATTLER_0, sB_ANIM_ARG1
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_OverworldTerrain::
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_BATTLER_0, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	end3

BattleScript_SideStatusWoreOff::
	printstring STRINGID_PKMNSXWOREOFF
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_SideStatusWoreOffReturn::
	printstring STRINGID_PKMNSXWOREOFF
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_LuckyChantEnds::
	printstring STRINGID_LUCKYCHANTENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_TailwindEnds::
	printstring STRINGID_TAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_TrickRoomEnds::
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printstring STRINGID_TRICKROOMENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_WonderRoomEnds::
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printstring STRINGID_WONDERROOMENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_MagicRoomEnds::
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printstring STRINGID_MAGICROOMENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_InverseRoomEnds::
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printstring STRINGID_INVERSEROOMENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_GrassyTerrainEnds::
	call BattleScript_GrassyTerrainHeals_Ret
	goto BattleScript_TerrainEnds

BattleScript_TerrainEnds_Ret::
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	return

BattleScript_TerrainEnds::
	call BattleScript_TerrainEnds_Ret
	end2

BattleScript_MudSportEnds::
	printstring STRINGID_MUDSPORTENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_WaterSportEnds::
	printstring STRINGID_WATERSPORTENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_GravityEnds::
	printstring STRINGID_GRAVITYENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_SafeguardProtected::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_SafeguardEnds::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNSAFEGUARDEXPIRED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_TickedTurnDrain::
	playanimation BS_ATTACKER, B_ANIM_LEECH_SEED_DRAIN, sB_ANIM_ARG1
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	copyword gBattleMoveDamage, gHpDealt
	jumpifability BS_ATTACKER, ABILITY_LIQUID_OOZE, BattleScript_TickedTurnPrintLiquidOoze
	setbyte cMULTISTRING_CHOOSER, B_MSG_LEECH_SEED_DRAIN
	jumpifstatus3 BS_TARGET, STATUS3_HEAL_BLOCK, BattleScript_TickedHealBlock
	manipulatedamage DMG_BIG_ROOT
	goto BattleScript_TickedTurnPrintAndUpdateHp
BattleScript_TickedTurnPrintLiquidOoze::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setbyte cMULTISTRING_CHOOSER, B_MSG_LEECH_SEED_OOZE
BattleScript_TickedTurnPrintAndUpdateHp::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printfromtable gTickedStringIds
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	tryfaintmon BS_TARGET
	end2
BattleScript_TickedHealBlock:
	setword gBattleMoveDamage, 0
	goto BattleScript_TickedTurnPrintAndUpdateHp

BattleScript_LeechSeedTurnDrain::
	playanimation BS_ATTACKER, B_ANIM_LEECH_SEED_DRAIN, sB_ANIM_ARG1
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	copyword gBattleMoveDamage, gHpDealt
	jumpifability BS_ATTACKER, ABILITY_LIQUID_OOZE, BattleScript_LeechSeedTurnPrintLiquidOoze
	setbyte cMULTISTRING_CHOOSER, B_MSG_LEECH_SEED_DRAIN
	jumpifstatus3 BS_TARGET, STATUS3_HEAL_BLOCK, BattleScript_LeechSeedHealBlock
	manipulatedamage DMG_BIG_ROOT
	goto BattleScript_LeechSeedTurnPrintAndUpdateHp
BattleScript_LeechSeedTurnPrintLiquidOoze::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setbyte cMULTISTRING_CHOOSER, B_MSG_LEECH_SEED_OOZE
BattleScript_LeechSeedTurnPrintAndUpdateHp::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printfromtable gLeechSeedStringIds
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	tryfaintmon BS_TARGET
	end2
BattleScript_LeechSeedHealBlock:
	setword gBattleMoveDamage, 0
	goto BattleScript_LeechSeedTurnPrintAndUpdateHp

BattleScript_BideStoringEnergy::
	printstring STRINGID_PKMNSTORINGENERGY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_BideAttack::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	clearstatusfromeffect BS_ATTACKER
	printstring STRINGID_PKMNUNLEASHEDENERGY
	waitmessage B_WAIT_TIME_LONG
	accuracycheck BattleScript_MoveMissed, ACC_CURR_MOVE
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	copyword gBattleMoveDamage, sBIDE_DMG
	adjustdamage
	setbyte sB_ANIM_TURN, 1
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_BideNoEnergyToAttack::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	clearstatusfromeffect BS_ATTACKER
	printstring STRINGID_PKMNUNLEASHEDENERGY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_ButItFailed

BattleScript_RoarSuccessSwitch::
	call BattleScript_RoarSuccessRet
	getswitchedmondata BS_TARGET
	switchindataupdate BS_TARGET
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	switchinanim BS_TARGET, FALSE
	waitstate
	printstring STRINGID_PKMNWASDRAGGEDOUT
	switchineffects BS_TARGET
	jumpifbyte CMP_EQUAL, sSWITCH_CASE, B_SWITCH_RED_CARD, BattleScript_RoarSuccessSwitch_Ret
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	goto BattleScript_MoveEnd
BattleScript_RoarSuccessSwitch_Ret:
	swapattackerwithtarget  @ continuation of RedCardActivates
	restoretarget
	restoreattacker
	restoresavedmove
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	return

BattleScript_RoarSuccessEndBattle::
	call BattleScript_RoarSuccessRet
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	setoutcomeonteleport BS_ATTACKER
	finishaction

BattleScript_RoarSuccessRet:
	jumpifbyte CMP_EQUAL, sSWITCH_CASE, B_SWITCH_HIT, BattleScript_RoarSuccessRet_Ret
	jumpifbyte CMP_EQUAL, sSWITCH_CASE, B_SWITCH_RED_CARD, BattleScript_RoarSuccessRet_Ret
	attackanimation
	waitanimation
BattleScript_RoarSuccessRet_Ret:
	switchoutabilities BS_TARGET
	returntoball BS_TARGET
	waitstate
	return

BattleScript_WhirlwindSuccessSwitch::
	call BattleScript_RoarSuccessRet
	getswitchedmondata BS_TARGET
	switchindataupdate BS_TARGET
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	switchinanim BS_TARGET, FALSE
	waitstate
	printstring STRINGID_PKMNWASDRAGGEDOUT
	switchineffects BS_TARGET
	jumpifbyte CMP_EQUAL, sSWITCH_CASE, B_SWITCH_RED_CARD, BattleScript_WhirlwindSuccessSwitch_Ret
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	removetailwind BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	settailwind BattleScript_MoveEnd
	printstring STRINGID_TAILWINDBLEW
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryTailwindAbilitiesLoop
	goto BattleScript_MoveEnd
BattleScript_WhirlwindSuccessSwitch_Ret::
	swapattackerwithtarget  @ continuation of RedCardActivates
	restoretarget
	restoreattacker
	restoresavedmove
	setbyte sSWITCH_CASE, B_SWITCH_NORMAL
	removetailwind BS_TARGET, BattleScript_WhirlwindRet
	printstring STRINGID_FOETAILWINDENDS
	waitmessage B_WAIT_TIME_LONG
	settailwind BattleScript_WhirlwindRet
	printstring STRINGID_TAILWINDBLEW
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryTailwindAbilitiesLoop
BattleScript_WhirlwindRet::
	return

BattleScript_WeaknessPolicy::
	copybyte sBATTLER, gBattlerTarget
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_WeaknessPolicyAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_WeaknessPolicyEnd
BattleScript_WeaknessPolicyAtk:
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_WeaknessPolicySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WeaknessPolicySpAtk
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_WeaknessPolicySpAtk:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_WeaknessPolicyRemoveItem
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WeaknessPolicyRemoveItem
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_WeaknessPolicyRemoveItem:
	removeitem BS_TARGET
BattleScript_WeaknessPolicyEnd:
	return

BattleScript_Snowball::
	copybyte sBATTLER, gBattlerTarget
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_SnowballSpAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_SnowballEnd
BattleScript_SnowballSpAtk:
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_SPATK | BIT_SPEED, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SnowballSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SnowballSpeed
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_SnowballSpeed:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SnowballRemoveItem
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SnowballRemoveItem
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_SnowballRemoveItem:
	removeitem BS_TARGET
BattleScript_SnowballEnd:
	return

BattleScript_LuminousMoss::
	copybyte sBATTLER, gBattlerTarget
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_LuminousMossSpAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_LuminousMossEnd
BattleScript_LuminousMossSpAtk:
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_SPATK | BIT_SPDEF, STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_LuminousMossSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_LuminousMossSpDef
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_LuminousMossSpDef:
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_LuminousMossRemoveItem
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_LuminousMossRemoveItem
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_LuminousMossRemoveItem:
	removeitem BS_TARGET
BattleScript_LuminousMossEnd:
	return

BattleScript_CellBattery::
	copybyte sBATTLER, gBattlerTarget
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_CellBatteryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CellBatteryEnd
BattleScript_CellBatteryAtk:
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPEED, STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_CellBatterySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CellBatterySpeed
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_CellBatterySpeed:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_CellBatteryRemoveItem
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_CellBatteryRemoveItem
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_CellBatteryRemoveItem:
	removeitem BS_TARGET
BattleScript_CellBatteryEnd:
	return

BattleScript_AbsorbBulb::
	copybyte sBATTLER, gBattlerTarget
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AbsorbBulbAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_DEF, MAX_STAT_STAGE, BattleScript_AbsorbBulbEnd
BattleScript_AbsorbBulbAtk:
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF, STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AbsorbBulbDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AbsorbBulbDef
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_AbsorbBulbDef:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AbsorbBulbRemoveItem
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AbsorbBulbRemoveItem
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
BattleScript_AbsorbBulbRemoveItem:
	removeitem BS_TARGET
BattleScript_AbsorbBulbEnd:
	return

BattleScript_LostMantle::
	copybyte sBATTLER, gBattlerAttacker
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_LostMantleDef
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_LostMantleEnd
BattleScript_LostMantleDef:
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_LostMantleSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_LostMantleSpDef
	printstring STRINGID_USINGITEMSTATOFPKMNFELL
	waitmessage B_WAIT_TIME_LONG
BattleScript_LostMantleSpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, STAT_CHANGE_NEGATIVE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_LostMantleEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_LostMantleEnd
	printstring STRINGID_USINGITEMSTATOFPKMNFELL
	waitmessage B_WAIT_TIME_LONG
BattleScript_LostMantleEnd:
	return

BattleScript_TargetItemStatRaise::
	copybyte sBATTLER, gBattlerTarget
	statbuffchange 0, BattleScript_TargetItemStatRaiseRemoveItemRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_TargetItemStatRaiseRemoveItemRet
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_TargetItemStatRaiseRemoveItemRet:
	return

BattleScript_TargetItemStatDrop::
	copybyte sBATTLER, gBattlerTarget
	statbuffchange 0, BattleScript_TargetItemStatDropRemoveItemRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_TargetItemStatDropRemoveItemRet
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_USINGITEMSTATOFPKMNFELL
	waitmessage B_WAIT_TIME_LONG
BattleScript_TargetItemStatDropRemoveItemRet:
	return

BattleScript_AttackerItemStatRaise::
	copybyte sBATTLER, gBattlerAttacker
	statbuffchange MOVE_EFFECT_AFFECTS_USER, BattleScript_AttackerItemStatRaiseRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_AttackerItemStatRaiseRet
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
BattleScript_AttackerItemStatRaiseRet:
	return

BattleScript_FlipCoinFlipStats::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	invertpositivestatstages BS_TARGET
	printstring STRINGID_FLIPCOINMESSAGE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_MistProtected::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNPROTECTEDBYMIST
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_RageIsBuilding::
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_RageIsBuildingEnd
	printstring STRINGID_PKMNRAGEBUILDING
	waitmessage B_WAIT_TIME_LONG
BattleScript_RageIsBuildingEnd:
	return

BattleScript_MoveUsedIsDisabled::
	printstring STRINGID_PKMNMOVEISDISABLED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SelectingDisabledMove::
	printselectionstring STRINGID_PKMNMOVEISDISABLED
	endselectionscript

BattleScript_DisabledNoMore::
	printstring STRINGID_PKMNMOVEDISABLEDNOMORE
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_SelectingDisabledMoveInPalace::
	printstring STRINGID_PKMNMOVEISDISABLED
BattleScript_SelectingUnusableMoveInPalace::
	moveendto MOVEEND_NEXT_TARGET
	end

BattleScript_EncoredNoMore::
	printstring STRINGID_PKMNENCOREENDED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_DestinyBondTakesLife::
	printstring STRINGID_PKMNTOOKFOE
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	return

BattleScript_DmgHazardsOnAttacker::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	call BattleScript_PrintHurtByDmgHazards
	tryfaintmon BS_ATTACKER
	tryfaintmon_spikes BS_ATTACKER, BattleScript_DmgHazardsOnAttackerFainted
	return

BattleScript_DmgHazardsOnAttackerFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_ATTACKER
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_DmgHazardsOnTarget::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	call BattleScript_PrintHurtByDmgHazards
	tryfaintmon BS_TARGET
	tryfaintmon_spikes BS_TARGET, BattleScript_DmgHazardsOnTargetFainted
	return

BattleScript_DmgHazardsOnTargetFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_TARGET
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_DmgHazardsOnFaintedBattler::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_FAINTED
	datahpupdate BS_FAINTED
	call BattleScript_PrintHurtByDmgHazards
	tryfaintmon BS_FAINTED
	tryfaintmon_spikes BS_FAINTED, BattleScript_DmgHazardsOnFaintedBattlerFainted
	return

BattleScript_DmgHazardsOnFaintedBattlerFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_FAINTED
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_PrintHurtByDmgHazards::
	printfromtable gDmgHazardsStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ToxicSpikesAbsorbed::
	printstring STRINGID_TOXICSPIKESABSORBED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ToxicSpikesPoisoned::
	printstring STRINGID_TOXICSPIKESPOISONED
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_SCRIPTING
	updatestatusicon BS_SCRIPTING
	waitstate
	return

BattleScript_StickyWebOnSwitchIn::
	savetarget
	saveattacker
	copybyte gBattlerTarget, sBATTLER
	setbyte sSTICKY_WEB_STAT_DROP, 1
	printstring STRINGID_STICKYWEBSWITCHIN
	waitmessage B_WAIT_TIME_LONG
	jumpifability BS_TARGET, ABILITY_MIRROR_ARMOR, BattleScript_MirrorArmorReflectStickyWeb
	jumpifmoonmirrored BS_TARGET, BattleScript_MoonMirrorReflectStickyWeb
StickyWebContinue:
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_StickyWebOnSwitchInEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_StickyWebOnSwitchInStatAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_StickyWebOnSwitchInEnd
	pause B_WAIT_TIME_SHORT
	goto BattleScript_StickyWebOnSwitchInPrintStatMsg
BattleScript_StickyWebOnSwitchInStatAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StickyWebOnSwitchInPrintStatMsg:
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StickyWebOnSwitchInEnd:
	restoretarget
	restoreattacker
	setbyte sSTICKY_WEB_STAT_DROP, 0
	return

BattleScript_PerishSongTakesLife::
	printstring STRINGID_PKMNPERISHCOUNTFELL
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	end2

BattleScript_PerishBodyActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSWILLPERISHIN3TURNS
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	return

BattleScript_GulpMissileGorging::
	call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_GULP_MISSILE
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_GulpMissileNoDmgGorging
	jumpifability BS_ATTACKER, ABILITY_SUGAR_COAT, BattleScript_GulpMissileNoDmgGorging
	jumpifterucharmprotected BS_ATTACKER, BattleScript_GulpMissileNoDmgGorging
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	jumpiffainted BS_ATTACKER, TRUE, BattleScript_GulpMissileNoSecondEffectGorging
BattleScript_GulpMissileNoDmgGorging:
	handleformchange BS_TARGET, 0
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE
	waitanimation
	swapattackerwithtarget
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	swapattackerwithtarget
	return
BattleScript_GulpMissileNoSecondEffectGorging:
	handleformchange BS_TARGET, 0
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE
	waitanimation
	return

BattleScript_GulpMissileGulping::
	call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_GULP_MISSILE
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_GulpMissileNoDmgGulping
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	jumpiffainted BS_ATTACKER, TRUE, BattleScript_GulpMissileNoSecondEffectGulping
BattleScript_GulpMissileNoDmgGulping:
	handleformchange BS_TARGET, 0
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE
	waitanimation
	swapattackerwithtarget @ to make gStatDownStringIds down below print the right battler
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_GulpMissileGulpingEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_GulpMissileGulpingTargetDefenseCantGoLower
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	swapattackerwithtarget @ restore the battlers, just in case
	return
BattleScript_GulpMissileNoSecondEffectGulping:
	handleformchange BS_TARGET, 0
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE
	waitanimation
	return
BattleScript_GulpMissileGulpingTargetDefenseCantGoLower:
	printstring STRINGID_STATSWONTDECREASE
	waitmessage B_WAIT_TIME_LONG
BattleScript_GulpMissileGulpingEnd:
	swapattackerwithtarget @ restore the battlers, just in case
	return

BattleScript_SeedSowerActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESGRASSY
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	return

BattleScript_GuardDogActivates::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_ABILITYLETITUSEMOVEGUARDDOG
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_TARGET, B_ANIM_GUARD_DOG
	waitanimation
	copybyte gEffectBattler, gBattlerTarget
	swapattackerwithtarget
	setbyte gBattlerTarget, 0
BattleScript_GuardDogLoop:
	jumpiffainted BS_TARGET, TRUE, BattleScript_GuardDogLoopIncrement
	jumpiftargetally BattleScript_GuardDogLoopIncrement
	setstatchanger STAT_ATK, 1, TRUE
	jumpifbyteequal gBattlerTarget, gEffectBattler, BattleScript_GuardDogLoopIncrement
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_GuardDogLoopIncrement
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_GuardDogTargetSpeedCantGoLower
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_GuardDogLoopIncrement
BattleScript_GuardDogTargetSpeedCantGoLower:
	printstring STRINGID_STATSWONTDECREASE
	waitmessage B_WAIT_TIME_LONG
BattleScript_GuardDogLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_GuardDogLoop
	swapattackerwithtarget
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_SweetVeilActivates::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_ABILITYLETITUSEMOVESWEETVEIL
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_TARGET, B_ANIM_SWEET_VEIL
	waitanimation
	copybyte gEffectBattler, gBattlerTarget
	swapattackerwithtarget
	setbyte gBattlerTarget, 0
BattleScript_SweetVeilLoop:
	jumpiffainted BS_TARGET, TRUE, BattleScript_SweetVeilLoopIncrement
	jumpiftargetally BattleScript_SweetVeilLoopIncrement
	setstatchanger STAT_EVASION, 1, TRUE
	jumpifbyteequal gBattlerTarget, gEffectBattler, BattleScript_SweetVeilLoopIncrement
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_SweetVeilLoopIncrement
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SweetVeilTargetSpeedCantGoLower
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_SweetVeilLoopIncrement
BattleScript_SweetVeilTargetSpeedCantGoLower:
	printstring STRINGID_STATSWONTDECREASE
	waitmessage B_WAIT_TIME_LONG
BattleScript_SweetVeilLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_SweetVeilLoop
	swapattackerwithtarget
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_AngerShellActivates::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	copybyte gBattlerAbility, gEffectBattler
	copybyte gBattlerAttacker, gBattlerTarget
	call BattleScript_AbilityPopUp
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AngerShellTryDef
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_AngerShellTryDef
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_AngerShellTryDef
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_AngerShellTryDef
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_ButItFailed
BattleScript_AngerShellTryDef::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	modifybattlerstatstage BS_TARGET, STAT_DEF, DECREASE, 1, BattleScript_AngerShellTrySpDef, ANIM_ON
BattleScript_AngerShellTrySpDef:
	modifybattlerstatstage BS_TARGET, STAT_SPDEF, DECREASE, 1, BattleScript_AngerShellTryAttack, ANIM_ON
BattleScript_AngerShellTryAttack:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	modifybattlerstatstage BS_TARGET, STAT_ATK, INCREASE, 1, BattleScript_AngerShellTrySpAtk, ANIM_ON
BattleScript_AngerShellTrySpAtk:
	modifybattlerstatstage BS_TARGET, STAT_SPATK, INCREASE, 1, BattleScript_AngerShellTrySpeed, ANIM_ON
BattleScript_AngerShellTrySpeed:
	modifybattlerstatstage BS_TARGET, STAT_SPEED, INCREASE, 1, BattleScript_AngerShellRet, ANIM_ON
BattleScript_AngerShellRet:
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_WindPowerActivates::
	call BattleScript_AbilityPopUp
	setcharge BS_TARGET
	printstring STRINGID_BEINGHITCHARGEDPKMNWITHPOWER
	waitmessage B_WAIT_TIME_LONG
BattleScript_WindPowerActivates_Ret:
	return

BattleScript_KamenScarfActivates::
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_SCARFWASCHARGEDBYBEINGHIT
	waitmessage B_WAIT_TIME_LONG
BattleScript_KamenScarfActivates_Ret:
	return

BattleScript_SilverCrownActivates::
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_CROWNINFESTEDATTACKER
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ToxicDebrisActivates::
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_SHORT
	settoxicspikes BattleScript_ToxicDebrisRet
	printstring STRINGID_POISONSPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
BattleScript_ToxicDebrisRet:
	copybyte sBATTLER, gBattlerTarget
	copybyte gBattlerTarget, gBattlerAttacker
	copybyte gBattlerAttacker, sBATTLER
	return

BattleScript_EarthEaterActivates::
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_LONG
	tryhealquarterhealth BS_TARGET, BattleScript_EarthEaterRet
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_EarthEaterRet:
	return

BattleScript_PerishSongCountGoesDown::
	printstring STRINGID_PKMNPERISHCOUNTFELL
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_AllStatsUp::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_AllStatsUpAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_AllStatsUpAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_AllStatsUpAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_AllStatsUpAtk
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_AllStatsUpRet
BattleScript_AllStatsUpAtk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUpDef::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUpSpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUpSpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUpSpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUpSpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUpSpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUpSpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AllStatsUpRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AllStatsUpRet::
	return

BattleScript_RapidSpinAway::
	rapidspinfree
	return

BattleScript_WrapFree::
	printstring STRINGID_PKMNGOTFREE
	waitmessage B_WAIT_TIME_LONG
	copybyte gBattlerTarget, sBATTLER
	return

BattleScript_LeechSeedFree::
	printstring STRINGID_PKMNSHEDLEECHSEED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_TickedFree::
	printstring STRINGID_PKMNSHEDTICK
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SpikesFree::
	printstring STRINGID_PKMNBLEWAWAYSPIKES
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ToxicSpikesFree::
	printstring STRINGID_PKMNBLEWAWAYTOXICSPIKES
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_StickyWebFree::
	printstring STRINGID_PKMNBLEWAWAYSTICKYWEB
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_StealthRockFree::
	printstring STRINGID_PKMNBLEWAWAYSTEALTHROCK
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SpikesDefog::
	printstring STRINGID_SPIKESDISAPPEAREDFROMTEAM
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ToxicSpikesDefog::
	printstring STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_StickyWebDefog::
	printstring STRINGID_STICKYWEBDISAPPEAREDFROMTEAM
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_StealthRockDefog::
	printstring STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MonTookFutureAttack::
	printstring STRINGID_PKMNTOOKATTACK
	waitmessage B_WAIT_TIME_LONG
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_FUTURE_SIGHT, BattleScript_CheckDoomDesireMiss
	accuracycheck BattleScript_FutureAttackMiss, MOVE_FUTURE_SIGHT
	goto BattleScript_FutureAttackAnimate
BattleScript_CheckDoomDesireMiss::
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_DOOM_DESIRE, BattleScript_CheckDecimationMiss
	accuracycheck BattleScript_FutureAttackMiss, MOVE_DOOM_DESIRE
	goto BattleScript_FutureAttackAnimate
BattleScript_CheckDecimationMiss::
	accuracycheck BattleScript_FutureAttackMiss, MOVE_DECIMATION
BattleScript_FutureAttackAnimate::
	critcalc
	damagecalc
	adjustdamage
	jumpifmovehadnoeffect BattleScript_DoFutureAttackResult
	jumpifmove MOVE_FUTURE_SIGHT, BattleScript_FutureHitAnimFutureSight
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_DOOM_DESIRE, BattleScript_FutureHitAnimDoomDesire
	playanimation BS_ATTACKER, B_ANIM_DECIMATION_HIT
	goto BattleScript_DoFutureAttackHit
BattleScript_FutureHitAnimDoomDesire::
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_DOOM_DESIRE, BattleScript_FutureHitAnimFutureSight
	playanimation BS_ATTACKER, B_ANIM_DOOM_DESIRE_HIT
	goto BattleScript_DoFutureAttackHit
BattleScript_FutureHitAnimFutureSight::
	playanimation BS_ATTACKER, B_ANIM_FUTURE_SIGHT_HIT
BattleScript_DoFutureAttackHit::
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
BattleScript_DoFutureAttackResult:
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	checkteamslost BattleScript_FutureAttackEnd
BattleScript_FutureAttackEnd::
	moveendcase MOVEEND_RAGE
	moveendfromto MOVEEND_ITEM_EFFECTS_ALL, MOVEEND_UPDATE_LAST_MOVES
	setbyte gMoveResultFlags, 0
	end2
BattleScript_FutureAttackMiss::
	pause B_WAIT_TIME_SHORT
	sethword gMoveResultFlags, MOVE_RESULT_FAILED
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	sethword gMoveResultFlags, 0
	end2

BattleScript_NoMovesLeft::
	printselectionstring STRINGID_PKMNHASNOMOVESLEFT
	endselectionscript

BattleScript_SelectingMoveWithNoPP::
	printselectionstring STRINGID_NOPPLEFT
	endselectionscript

BattleScript_NoPPForMove::
	attackstring
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_BUTNOPPLEFT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SelectingTormentedMove::
	printselectionstring STRINGID_PKMNCANTUSEMOVETORMENT
	endselectionscript

BattleScript_MoveUsedIsTormented::
	printstring STRINGID_PKMNCANTUSEMOVETORMENT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SelectingTormentedMoveInPalace::
	printstring STRINGID_PKMNCANTUSEMOVETORMENT
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedMoveTaunt::
	printselectionstring STRINGID_PKMNCANTUSEMOVETAUNT
	endselectionscript

BattleScript_MoveUsedIsTaunted::
	printstring STRINGID_PKMNCANTUSEMOVETAUNT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SelectingNotAllowedMoveTauntInPalace::
	printstring STRINGID_PKMNCANTUSEMOVETAUNT
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedMoveThroatChop::
	printselectionstring STRINGID_PKMNCANTUSEMOVETHROATCHOP
	endselectionscript

BattleScript_MoveUsedIsThroatChopPrevented::
	printstring STRINGID_PKMNCANTUSEMOVETHROATCHOP
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SelectingNotAllowedMoveThroatChopInPalace::
	printstring STRINGID_PKMNCANTUSEMOVETHROATCHOP
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_ThroatChopEndTurn::
	printstring STRINGID_THROATCHOPENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_MagicCoatEndTurn::
	printstring STRINGID_MAGICCOATENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_SlowStartEnds::
	pause 5
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_SLOWSTARTEND
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_StarsGraceStarts::
	pause 5
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_STARSGRACESTART
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_SilenceContinues::
	playanimation BS_BATTLER_0, B_ANIM_SILENCE
	printstring STRINGID_SILENCECONTINUES
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_SilenceActivatesArcane::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_SilenceAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_SilenceAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_SilenceAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_SilenceAtk
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_SilenceRet
BattleScript_SilenceAtk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, MAX_STAT_STAGE, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceDef
BattleScript_SilenceDef::
	setstatchanger STAT_DEF, MAX_STAT_STAGE, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceSpeed
BattleScript_SilenceSpeed::
	setstatchanger STAT_SPEED, MAX_STAT_STAGE, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceSpAtk
BattleScript_SilenceSpAtk::
	setstatchanger STAT_SPATK, MAX_STAT_STAGE, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceSpDef
BattleScript_SilenceSpDef::
	setstatchanger STAT_SPDEF, MAX_STAT_STAGE, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceRet
	printstring STRINGID_PKMNMAXEDSTATS
	waitmessage B_WAIT_TIME_LONG
	end2
BattleScript_SilenceRet::
	printstring STRINGID_SILENCEEND
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_SilenceActivatesNonArcane::
	jumpifnotbattletype BATTLE_TYPE_TRAINER, BattleScript_SilenceContinueWithoutIncrementingGameStat
	incrementgamestat GAME_STAT_SILENCE_ACTIVATED
BattleScript_SilenceContinueWithoutIncrementingGameStat::
	playanimation BS_BATTLER_0, B_ANIM_SILENCE
	jumpifspecies BS_ATTACKER, SPECIES_INFAIRNO, BattleScript_SilenceActivatesArcane
	jumpifspecies BS_ATTACKER, SPECIES_PURGATIVAL, BattleScript_SilenceActivatesArcane
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_SilenceActivatesNonArcaneAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_SilenceActivatesNonArcaneAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_SilenceActivatesNonArcaneAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_SilenceActivatesNonArcaneAtk
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_SilenceRet
BattleScript_SilenceActivatesNonArcaneAtk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceActivatesNonArcaneDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceActivatesNonArcaneDef
BattleScript_SilenceActivatesNonArcaneDef::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceActivatesNonArcaneSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceActivatesNonArcaneSpeed
BattleScript_SilenceActivatesNonArcaneSpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceActivatesNonArcaneSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceActivatesNonArcaneSpAtk
BattleScript_SilenceActivatesNonArcaneSpAtk::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceActivatesNonArcaneSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceActivatesNonArcaneSpDef
BattleScript_SilenceActivatesNonArcaneSpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SilenceRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SilenceRet
	printstring STRINGID_PKMNDOUBLEDSTATS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_SelectingNotAllowedMoveGravity::
	printselectionstring STRINGID_GRAVITYPREVENTSUSAGE
	endselectionscript

BattleScript_SelectingNotAllowedStuffCheeks::
	printselectionstring STRINGID_STUFFCHEEKSCANTSELECT
	endselectionscript

BattleScript_SelectingNotAllowedStuffCheeksInPalace::
	printstring STRINGID_STUFFCHEEKSCANTSELECT
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedBelch::
	printselectionstring STRINGID_BELCHCANTSELECT
	endselectionscript

BattleScript_SelectingNotAllowedBelchInPalace::
	printstring STRINGID_BELCHCANTSELECT
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_MoveUsedGravityPrevents::
	printstring STRINGID_GRAVITYPREVENTSUSAGE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SelectingNotAllowedMoveGravityInPalace::
	printstring STRINGID_GRAVITYPREVENTSUSAGE
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedMoveHealBlock::
	printselectionstring STRINGID_HEALBLOCKPREVENTSUSAGE
	endselectionscript

BattleScript_MoveUsedHealBlockPrevents::
	printstring STRINGID_HEALBLOCKPREVENTSUSAGE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SelectingNotAllowedMoveHealBlockInPalace::
	printstring STRINGID_HEALBLOCKPREVENTSUSAGE
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedCurrentMove::
	printselectionstring STRINGID_CURRENTMOVECANTSELECT
	endselectionscript

BattleScript_SelectingNotAllowedCurrentMoveInPalace::
	printstring STRINGID_CURRENTMOVECANTSELECT
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_WishComesTrue::
	trywish 1, BattleScript_WishButFullHp
	playanimation BS_TARGET, B_ANIM_WISH_HEAL
	printstring STRINGID_PKMNWISHCAMETRUE
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_WishButFullHp::
	printstring STRINGID_PKMNWISHCAMETRUE
	waitmessage B_WAIT_TIME_LONG
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNHPFULL
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_IngrainTurnHeal::
	playanimation BS_ATTACKER, B_ANIM_INGRAIN_HEAL
	printstring STRINGID_PKMNABSORBEDNUTRIENTS
BattleScript_TurnHeal:
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	end2

BattleScript_DaybreakTurnDamage::
	printstring STRINGID_PKMNHURTBY
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	checkteamslost BattleScript_DoTurnDmgEnd
	end2

BattleScript_AquaRingHeal::
	playanimation BS_ATTACKER, B_ANIM_AQUA_RING_HEAL
	printstring STRINGID_AQUARINGHEAL
	goto BattleScript_TurnHeal

BattleScript_HearthwarmHeal::
	playanimation BS_ATTACKER, B_ANIM_HEARTHWARM_HEAL
	printstring STRINGID_HEARTHWARMHEAL
	goto BattleScript_TurnHeal

BattleScript_PrintMonIsRooted::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNANCHOREDITSELF
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_AtkDefDown::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AtkDefDownTryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkDefDownTryDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkDefDownTryDef:
	playstatchangeanimation BS_TARGET, BIT_DEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_AtkDefDownRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkDefDownRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkDefDownRet:
	return

BattleScript_SuperTropKick::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SuperTropKickTryLowerFoeDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SuperTropKickTryLowerFoeDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SuperTropKickTryLowerFoeDef:
	playstatchangeanimation BS_TARGET, BIT_DEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_SuperTropKickTryRaiseUserAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SuperTropKickTryRaiseUserAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SuperTropKickTryRaiseUserAtk:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_SuperTropKickRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SuperTropKickRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SuperTropKickRet:
	return

BattleScript_DefAccDown::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_ACC, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_DEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_DefAccDownTryAcc
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DefAccDownTryAcc
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefAccDownTryAcc::
	playstatchangeanimation BS_TARGET, BIT_ACC, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_DefAccDownRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DefAccDownRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefAccDownRet::
	return

BattleScript_DefSpDefDown::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPDEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_DEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_DefSpDefDownTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DefSpDefDownTrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefSpDefDownTrySpDef::
	playstatchangeanimation BS_TARGET, BIT_SPDEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_DefSpDefDownRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DefSpDefDownRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefSpDefDownRet::
	return

BattleScript_DefSpDefDownUser::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_DefSpDefDownUserTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DefSpDefDownUserTrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefSpDefDownUserTrySpDef::
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_DefSpDefDownUserRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DefSpDefDownUserRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefSpDefDownUserRet::
	return

BattleScript_AtkSpAtkDown::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkSpAtkDownTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkSpAtkDownTrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkSpAtkDownTrySpDef::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkSpAtkDownRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkSpAtkDownRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkSpAtkDownRet::
	return

BattleScript_AtkSpAtkDown2::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS | STAT_CHANGE_BY_TWO
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 2, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkSpAtkDown2TrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkSpAtkDown2TrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkSpAtkDown2TrySpDef::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPATK, 2, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkSpAtkDown2Ret
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkSpAtkDown2Ret
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkSpAtkDown2Ret::
	return

BattleScript_LongNose::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK | BIT_EVASION | BIT_ACC, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_LongNoseTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_LongNoseTrySpAtk
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_LongNoseTrySpAtk::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_LongNoseTryEvasion
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_LongNoseTryEvasion
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_LongNoseTryEvasion::
	playstatchangeanimation BS_TARGET, BIT_EVASION, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_LongNoseTryAccuracy
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_LongNoseTryAccuracy
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_LongNoseTryAccuracy::
	playstatchangeanimation BS_TARGET, BIT_ACC, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_LongNoseRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_LongNoseRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_LongNoseRet::
	return

BattleScript_AtkSpeedDown::
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_AtkSpeedDownRet
	jumpiftargetally BattleScript_AtkSpeedDownRet
	jumpifabsent BS_TARGET, BattleScript_AtkSpeedDownRet
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPEED, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkSpeedDownTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkSpeedDownTrySpDef
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkSpeedDownTrySpDef::
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkSpeedDownRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkSpeedDownRet
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkSpeedDownRet::
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_AtkSpeedDown
	return

BattleScript_DefSpDefUp::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_DefSpDefUpTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DefSpDefUpTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefSpDefUpTrySpDef::
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_DefSpDefUpRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DefSpDefUpRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefSpDefUpRet::
	return

BattleScript_SpdAccUp::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_ACC, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_SpdAccUpTryAcc
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SpdAccUpTryAcc
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpdAccUpTryAcc::
	playstatchangeanimation BS_ATTACKER, BIT_ACC, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_SpdAccUpRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SpdAccUpRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpdAccUpRet::
	return

BattleScript_SpAtkSpDefUp::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_SPDEF, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_ATTACKER, BIT_SPATK, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_SpAtkSpDefUpTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SpAtkSpDefUpTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpAtkSpDefUpTrySpDef::
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_SpAtkSpDefUpRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SpAtkSpDefUpRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpAtkSpDefUpRet::
	return

BattleScript_AtkSpdUp::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPEED, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_MULTIPLE_STATS
	playstatchangeanimation BS_ATTACKER, BIT_ATK, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkSpdUpTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AtkSpdUpTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkSpdUpTrySpeed::
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkSpdUpRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_AtkSpdUpRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkSpdUpRet::
	return

BattleScript_DefDownSpeedUp::
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_DefDownSpeedUpTryDef
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_DefDownSpeedUpRet
BattleScript_DefDownSpeedUpTryDef::
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_NEGATIVE | STAT_CHANGE_CANT_PREVENT
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_DefDownSpeedUpTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DefDownSpeedUpTrySpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefDownSpeedUpTrySpeed:
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, 0
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_DefDownSpeedUpRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DefDownSpeedUpRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefDownSpeedUpRet::
	return

BattleScript_TailSlapEffect::
	setmoveeffect MOVE_EFFECT_RAPIDSPIN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	seteffectprimary
	setmoveeffect MOVE_EFFECT_CLEAR_SMOG
	seteffectsecondary
	return

BattleScript_TormentAfter::
	jumpiffainted BS_TARGET, TRUE, BattleScript_TormentAfterRet
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_TormentAfterRet
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_TormentAfterRet
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_TormentAfterRet
	jumpifsafeguard BattleScript_TormentAfterRet
	settorment BattleScript_TormentAfterRet
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker
BattleScript_TormentAfterRet::
	return

BattleScript_KnockedOff::
	playanimation BS_TARGET, B_ANIM_ITEM_KNOCKOFF
	printstring STRINGID_PKMNKNOCKEDOFF
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveUsedIsImprisoned::
	printstring STRINGID_PKMNCANTUSEMOVESEALED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SelectingImprisonedMove::
	printselectionstring STRINGID_PKMNCANTUSEMOVESEALED
	endselectionscript

BattleScript_SelectingImprisonedMoveInPalace::
	printstring STRINGID_PKMNCANTUSEMOVESEALED
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_GrudgeTakesPp::
	printstring STRINGID_PKMNLOSTPPGRUDGE
	waitmessage B_WAIT_TIME_LONG
	seteffectsecondary
	return

BattleScript_MagicCoatBounce::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0, BattleScript_MagicCoatBounce_Print
	call BattleScript_AbilityPopUp
BattleScript_MagicCoatBounce_Print:
	printfromtable gMagicCoatBounceStringIds
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_ATTACKSTRING_PRINTED | HITMARKER_NO_PPDEDUCT | HITMARKER_ALLOW_NO_PP
	bicword gHitMarker, HITMARKER_NO_ATTACKSTRING
	setmagiccoattarget BS_ATTACKER
	return

BattleScript_MagicCoatBouncePrankster::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	printfromtable gMagicCoatBounceStringIds
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	goto BattleScript_MoveEnd

BattleScript_SnatchedMove::
	attackstring
	ppreduce
	snatchsetbattlers
	playanimation BS_TARGET, B_ANIM_SNATCH_MOVE
	printstring STRINGID_PKMNSNATCHEDMOVE
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_ATTACKSTRING_PRINTED | HITMARKER_NO_PPDEDUCT | HITMARKER_ALLOW_NO_PP
	swapattackerwithtarget
	return

BattleScript_EnduredMsg::
	printstring STRINGID_PKMNENDUREDHIT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SturdiedMsg::
	pause B_WAIT_TIME_SHORTEST
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_ENDUREDSTURDY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_OneHitKOMsg::
	printstring STRINGID_ONEHITKO
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SAtkDown2::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_BY_TWO
	setstatchanger STAT_SPATK, 2, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_SAtkDown2End
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SAtkDown2End
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_SAtkDown2End::
	return

BattleScript_AtkDown::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkDownEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkDownEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkDownEnd::
	return

BattleScript_AtkDown2::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE | STAT_CHANGE_BY_TWO
	setstatchanger STAT_ATK, 2, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkDown2End
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AtkDown2End
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AtkDown2End::
	return

BattleScript_AccDown::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ACC, STAT_CHANGE_CANT_PREVENT | STAT_CHANGE_NEGATIVE
	setstatchanger STAT_ACC, 1, TRUE
	statbuffchange MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_AtkDownEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_AccDownEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_AccDownEnd::
	return

BattleScript_MoveEffectClearSmog::
	printstring STRINGID_RESETSTARGETSSTATLEVELS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_FocusPunchSetUp::
	jumpiffocusenergy BS_ATTACKER, BattleScript_FocusPunchSetUpEnd3
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	playanimation BS_ATTACKER, B_ANIM_FOCUS_PUNCH_SETUP
	printstring STRINGID_PKMNTIGHTENINGFOCUS
	waitmessage B_WAIT_TIME_LONG
BattleScript_FocusPunchSetUpEnd3::
	end3

BattleScript_MegaEvolution::
	printstring STRINGID_EMPTYSTRING3
	trytrainerslidemegaevolutionmsg BS_ATTACKER
	printstring STRINGID_MEGAEVOREACTING
BattleScript_MegaEvolutionAfterString:
	waitmessage B_WAIT_TIME_LONG
	setbyte gIsCriticalHit, 0
	handlemegaevo BS_ATTACKER, 0
	playanimation BS_ATTACKER, B_ANIM_MEGA_EVOLUTION
	waitanimation
	handlemegaevo BS_ATTACKER, 1
	printstring STRINGID_MEGAEVOEVOLVED
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	end3

BattleScript_WishMegaEvolution::
	printstring STRINGID_EMPTYSTRING3
	trytrainerslidemegaevolutionmsg BS_ATTACKER
	printstring STRINGID_FERVENTWISHREACHED
	goto BattleScript_MegaEvolutionAfterString

BattleScript_PrimalReversion::
	call BattleScript_PrimalReversionRet
	end2

BattleScript_PrimalReversionRestoreAttacker::
	call BattleScript_PrimalReversionRet
	copybyte gBattlerAttacker, sSAVED_BATTLER
	end2

BattleScript_PrimalReversionRet::
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	setbyte gIsCriticalHit, 0
	handleprimalreversion BS_ATTACKER, 0
	handleprimalreversion BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_PRIMAL_REVERSION
	waitanimation
	handleprimalreversion BS_ATTACKER, 2
	printstring STRINGID_PKMNREVERTEDTOPRIMAL
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	return

BattleScript_UltraBurst::
	printstring STRINGID_EMPTYSTRING3
	trytrainerslidezmovemsg BS_ATTACKER
	printstring STRINGID_ULTRABURSTREACTING
	waitmessage B_WAIT_TIME_LONG
	setbyte gIsCriticalHit, 0
	handleultraburst BS_ATTACKER, 0
	playanimation BS_ATTACKER, B_ANIM_ULTRA_BURST
	waitanimation
	handleultraburst BS_ATTACKER, 1
	printstring STRINGID_ULTRABURSTCOMPLETED
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	end3

BattleScript_DefenderFormChange::
	pause 5
	copybyte gBattlerAbility, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
BattleScript_DefenderFormChangeNoPopup::
	handleformchange BS_TARGET, 0
	handleformchange BS_TARGET, 1
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE
	waitanimation
	handleformchange BS_TARGET, 2
	return

BattleScript_AttackerFormChange::
	pause 5
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
BattleScript_AttackerFormChangeNoPopup::
	handleformchange BS_ATTACKER, 0
	handleformchange BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_FORM_CHANGE
	waitanimation
	handleformchange BS_ATTACKER, 2
	return

BattleScript_AttackerFormChangeEnd3::
	call BattleScript_AttackerFormChange
	end3

BattleScript_AttackerFormChangeEnd3NoPopup::
	call BattleScript_AttackerFormChangeNoPopup
	end3

BattleScript_AttackerFormChangeMoveEffect::
	pause 5
	copybyte gBattlerAbility, gBattlerAttacker
	handleformchange BS_ATTACKER, 0
	handleformchange BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_FORM_CHANGE
	waitanimation
	handleformchange BS_ATTACKER, 2
	printstring STRINGID_PKMNTRANSFORMED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BallFetch::
	call BattleScript_AbilityPopUp
	printstring STRINGID_FETCHEDPOKEBALL
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_CudChewActivates::
	pause B_WAIT_TIME_SHORTEST
	call BattleScript_AbilityPopUp
	setbyte sBERRY_OVERRIDE, 1 @ override the requirements for eating berries
	consumeberry BS_TARGET, FALSE
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	setbyte sBERRY_OVERRIDE, 0
	end3

BattleScript_TargetFormChangeNoPopup:
	printstring STRINGID_EMPTYSTRING3
	handleformchange BS_SCRIPTING, 0
	handleformchange BS_SCRIPTING, 1
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE
	waitanimation
	handleformchange BS_SCRIPTING, 2
	return

BattleScript_TargetFormChangeDisguise::
	pause 5
	call BattleScript_AbilityPopUpTarget
	handleformchange BS_SCRIPTING, 0
	handleformchange BS_SCRIPTING, 1
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE
	waitanimation
	handleformchange BS_SCRIPTING, 2
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	return

BattleScript_TargetFormChangeWithString::
	pause 5
	call BattleScript_AbilityPopUpTarget
	call BattleScript_TargetFormChangeNoPopup
	printstring STRINGID_PKMNTRANSFORMED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_TargetFormChangeWithStringNoPopup::
	call BattleScript_TargetFormChangeNoPopup
	printstring STRINGID_PKMNTRANSFORMED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BattlerFormChangeWithStringEnd3::
	pause 5
	call BattleScript_AbilityPopUp
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	handleformchange BS_SCRIPTING, 0
	handleformchange BS_SCRIPTING, 1
	playanimation BS_SCRIPTING, B_ANIM_FORM_CHANGE, NULL
	waitanimation
	handleformchange BS_SCRIPTING, 2
	printstring STRINGID_PKMNTRANSFORMED
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_IllusionOff::
	spriteignore0hp TRUE
	playanimation BS_TARGET, B_ANIM_ILLUSION_OFF
	waitanimation
	updatenick BS_TARGET
	waitstate
	spriteignore0hp FALSE
	printstring STRINGID_ILLUSIONWOREOFF
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_CottonDownActivates::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	call BattleScript_AbilityPopUpTarget
	copybyte gEffectBattler, gBattlerTarget
	swapattackerwithtarget
	setbyte gBattlerTarget, 0
BattleScript_CottonDownLoop:
	jumpiffainted BS_TARGET, TRUE, BattleScript_CottonDownLoopIncrement
	setstatchanger STAT_SPEED, 1, TRUE
	jumpifbyteequal gBattlerTarget, gEffectBattler, BattleScript_CottonDownLoopIncrement
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_CottonDownLoopIncrement
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_CottonDownTargetSpeedCantGoLower
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_CottonDownLoopIncrement
BattleScript_CottonDownTargetSpeedCantGoLower:
	printstring STRINGID_STATSWONTDECREASE
	waitmessage B_WAIT_TIME_LONG
BattleScript_CottonDownLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_CottonDownLoop
	swapattackerwithtarget
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_AnticipationActivates::
	pause 5
	call BattleScript_AbilityPopUp
	printstring STRINGID_ANTICIPATIONACTIVATES
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AftermathDmg::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_AFTERMATHDMG
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	return

BattleScript_DampPreventsAftermath::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	pause 40
	copybyte gBattlerAbility, sBATTLER
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSABILITYPREVENTSABILITY
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_MoveUsedIsAsleep::
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_MoveUsedWokeUp::
	bicword gHitMarker, HITMARKER_WAKE_UP_CLEAR
	printfromtable gWokeUpStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	return

BattleScript_MonWokeUpInUproar::
	printstring STRINGID_PKMNWOKEUPINUPROAR
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	end2

BattleScript_PoisonTurnDmg::
	printstring STRINGID_PKMNHURTBYPOISON
	waitmessage B_WAIT_TIME_LONG
BattleScript_DoStatusTurnDmg::
	statusanimation BS_ATTACKER
BattleScript_DoTurnDmg:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	checkteamslost BattleScript_DoTurnDmgEnd
BattleScript_DoTurnDmgEnd:
	end2

BattleScript_PoisonHealActivates::
	printstring STRINGID_POISONHEALHPUP
	waitmessage B_WAIT_TIME_LONG
	recordability BS_ATTACKER
	statusanimation BS_ATTACKER
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	end2

BattleScript_BurnTurnDmg::
	printstring STRINGID_PKMNHURTBYBURN
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoStatusTurnDmg

BattleScript_FrostbiteTurnDmg::
	printstring STRINGID_PKMNHURTBYFROSTBITE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoStatusTurnDmg

BattleScript_InfernalReignTurnDmg::
	printstring STRINGID_PKMNBURNINGUP
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_INFERNAL_REIGN
	goto BattleScript_DoTurnDmg

BattleScript_MoveUsedIsFrozen::
	printstring STRINGID_PKMNISFROZEN
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_UnfrozeTargetWaitMessage::
    waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNWASDEFROSTED
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
    return
    
    
BattleScript_MoveUsedUnfroze::
	printfromtable gGotDefrostedStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	return

BattleScript_MoveUsedUnfrostbite::
	printfromtable gFrostbiteHealedStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	return

BattleScript_DefrostedViaFireMove::
	printstring STRINGID_PKMNWASDEFROSTED
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_FrostbiteHealedViaFireMove::
	printstring STRINGID_PKMNFROSTBITEHEALED
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_MoveUsedIsParalyzed::
	printstring STRINGID_PKMNISPARALYZED
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	cancelmultiturnmoves BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_PowderMoveNoEffect::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_PowderMoveNoEffectPrint
	jumpifability BS_TARGET, ABILITY_OVERCOAT, BattleScript_PowderMoveNoEffectOvercoat
	printstring STRINGID_SAFETYGOGGLESPROTECTED
	goto BattleScript_PowderMoveNoEffectWaitMsg
BattleScript_PowderMoveNoEffectOvercoat:
	call BattleScript_AbilityPopUp
BattleScript_PowderMoveNoEffectPrint:
	printstring STRINGID_ITDOESNTAFFECT
BattleScript_PowderMoveNoEffectWaitMsg:
	waitmessage B_WAIT_TIME_LONG
	cancelmultiturnmoves BS_ATTACKER
	sethword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_MoveUsedFlinched::
	printstring STRINGID_PKMNFLINCHED
	waitmessage B_WAIT_TIME_LONG
	jumpifability BS_ATTACKER, ABILITY_STEADFAST, BattleScript_TryActivateSteadFast
BattleScript_MoveUsedFlinchedEnd:
	goto BattleScript_MoveEnd
BattleScript_TryActivateSteadFast:
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SteadFastFlinchPreventionSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SteadFastFlinchPreventionSpeed
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	setbyte gBattleCommunication STAT_ATK
	stattextbuffer BS_TARGET
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_SHORTEST
BattleScript_SteadFastFlinchPreventionSpeed:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveUsedFlinchedEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveUsedFlinchedEnd
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	setbyte gBattleCommunication STAT_SPEED
	stattextbuffer BS_TARGET
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_SHORTEST
	goto BattleScript_MoveUsedFlinchedEnd

BattleScript_PrintUproarOverTurns::
	printfromtable gUproarOverTurnStringIds
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ThrashConfuses::
	chosenstatus2animation BS_ATTACKER, STATUS2_CONFUSION
	printstring STRINGID_PKMNFATIGUECONFUSION
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_MoveUsedIsConfused::
	printstring STRINGID_PKMNISCONFUSED
	waitmessage B_WAIT_TIME_LONG
	status2animation BS_ATTACKER, STATUS2_CONFUSION
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, FALSE, BattleScript_MoveUsedIsConfusedRet
BattleScript_DoSelfConfusionDmg::
	cancelmultiturnmoves BS_ATTACKER
	adjustdamage
	printstring STRINGID_ITHURTCONFUSION
	waitmessage B_WAIT_TIME_LONG
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd
BattleScript_MoveUsedIsConfusedRet::
	return

BattleScript_MoveUsedPowder::
	bicword gHitMarker, HITMARKER_NO_ATTACKSTRING | HITMARKER_ATTACKSTRING_PRINTED
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	cancelmultiturnmoves BS_ATTACKER
	status2animation BS_ATTACKER, STATUS2_POWDER
	waitanimation
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_POWDEREXPLODES
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_MoveUsedIsConfusedNoMore::
	printstring STRINGID_PKMNHEALEDCONFUSION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PrintPayDayMoneyString::
	printstring STRINGID_PLAYERPICKEDUPMONEY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_WrapTurnDmg::
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_DoTurnDmgEnd
	jumpifability BS_ATTACKER, ABILITY_SUGAR_COAT, BattleScript_DoTurnDmgEnd
	jumpifterucharmprotected BS_ATTACKER, BattleScript_DoTurnDmgEnd
	playanimation BS_ATTACKER, B_ANIM_TURN_TRAP, sB_ANIM_ARG1
	printstring STRINGID_PKMNHURTBY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoTurnDmg

BattleScript_WrapEnds::
	printstring STRINGID_PKMNFREEDFROM
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_MoveUsedIsInLove::
	printstring STRINGID_PKMNINLOVE
	waitmessage B_WAIT_TIME_LONG
	status2animation BS_ATTACKER, STATUS2_INFATUATION
	return

BattleScript_MoveUsedIsInLoveCantAttack::
	printstring STRINGID_PKMNIMMOBILIZEDBYLOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_NightmareTurnDmg::
	printstring STRINGID_PKMNLOCKEDINNIGHTMARE
	waitmessage B_WAIT_TIME_LONG
	status2animation BS_ATTACKER, STATUS2_NIGHTMARE
	goto BattleScript_DoTurnDmg

BattleScript_CurseTurnDmg::
	printstring STRINGID_PKMNAFFLICTEDBYCURSE
	waitmessage B_WAIT_TIME_LONG
	status2animation BS_ATTACKER, STATUS2_CURSED
	goto BattleScript_DoTurnDmg

BattleScript_TargetPoisonHeal::
	printstring STRINGID_PKMNHEALEDPOISON
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_TargetPRLZHeal::
	printstring STRINGID_PKMNHEALEDPARALYSIS
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_TargetWokeUpWaitMessage::
    waitmessage B_WAIT_TIME_LONG
BattleScript_TargetWokeUp::
	printstring STRINGID_TARGETWOKEUP
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_TargetBurnHeal::
	printstring STRINGID_PKMNBURNHEALED
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_TARGET
	return

BattleScript_MoveEffectSleep::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gFellAsleepStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_UpdateEffectStatusIconRet::
	updatestatusicon BS_EFFECT_BATTLER
	waitstate
	return

BattleScript_YawnMakesAsleep::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNFELLASLEEP
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_EFFECT_BATTLER
	waitstate
	jumpifstatus3 BS_EFFECT_BATTLER, STATUS3_SKY_DROPPED, BattleScript_YawnEnd
	makevisible BS_EFFECT_BATTLER
	skydropyawn
BattleScript_YawnEnd:
	end2

BattleScript_EmbargoEndTurn::
	printstring STRINGID_EMBARGOENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_TelekinesisEndTurn::
	printstring STRINGID_TELEKINESISENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_BufferEndTurn::
	printstring STRINGID_BUFFERENDS
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_ToxicOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectToxic
	end2

BattleScript_FlameOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectBurn
	end2

BattleScript_FrostOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectFrostbite
	end2

BattleScript_PoisonOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectPoison
	end2

BattleScript_BloomOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectBlooming
	removeitem BS_ATTACKER
	end3

BattleScript_PanicOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectPanic
	end2

BattleScript_MoveEffectPoison::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotPoisonedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectBurn::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotBurnedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectFrostbite::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotFrostbiteStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectFreeze::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotFrozenStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectParalysis::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotParalyzedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectPanic::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotPanickedStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_EFFECT_BATTLER
	saveattacker
	savetarget
	itemstatchangeeffects BS_EFFECT_BATTLER
	jumpifnoholdeffect BS_EFFECT_BATTLER, HOLD_EFFECT_ADRENALINE_ORB, BattleScript_MoveEffectPanicRet
	jumpifstat BS_EFFECT_BATTLER, CMP_EQUAL, STAT_SPEED, 12, BattleScript_MoveEffectPanicRet
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveEffectPanicRet
	playanimation BS_EFFECT_BATTLER, B_ANIM_HELD_ITEM_EFFECT
	setgraphicalstatchangevalues
	playanimation BS_EFFECT_BATTLER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	copybyte sBATTLER, BS_EFFECT_BATTLER
	setlastuseditem BS_EFFECT_BATTLER
	printstring STRINGID_USINGITEMSTATOFTARGETPKMNROSE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_EFFECT_BATTLER
BattleScript_MoveEffectPanicRet::
	restoreattacker
	restoretarget
	waitstate
	return

BattleScript_MoveEffectBlooming::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gStartedBloomingStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectExposed::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gWasExposedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectUproar::
	printstring STRINGID_PKMNCAUSEDUPROAR
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectToxic::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNBADLYPOISONED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectPayDay::
	printstring STRINGID_COINSSCATTERED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectTicked::
	printstring STRINGID_PKMNTICKED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveEffectWrap::
	printfromtable gWrappedStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectConfusion::
	chosenstatus2animation BS_EFFECT_BATTLER, STATUS2_CONFUSION
	printstring STRINGID_PKMNWASCONFUSED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectRecoilWithStatus::
	argumentstatuseffect
BattleScript_MoveEffectRecoil::
	jumpifmove MOVE_STRUGGLE, BattleScript_DoRecoil
	jumpifability BS_ATTACKER, ABILITY_ROCK_HEAD, BattleScript_RecoilEnd
BattleScript_DoRecoil::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_IGNORE_DISGUISE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHITWITHRECOIL
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
BattleScript_RecoilEnd::
	return

BattleScript_EffectWithChance::
	seteffectwithchance
	return

BattleScript_ItemSteal::
	playanimation BS_TARGET, B_ANIM_ITEM_STEAL
	printstring STRINGID_PKMNSTOLEITEM
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_DrizzleActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNMADEITRAIN
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_RAIN_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_DelugeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNMADEITRAIN2
	waitstate
	playanimation BS_ATTACKER, B_ANIM_RAIN_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_SunriseActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXINTENSIFIEDSUN2
	waitstate
	playanimation BS_ATTACKER, B_ANIM_SUN_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_AbilityRaisesDefenderStat::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	statbuffchange 0, NULL
	setgraphicalstatchangevalues
	playanimation BS_ABILITY_BATTLER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_DEFENDERSSTATROSE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityPopUpTarget:
	copybyte gBattlerAbility, gBattlerTarget
BattleScript_AbilityPopUp:
	.if B_ABILITY_POP_UP == TRUE
	showabilitypopup BS_ABILITY_BATTLER
	pause 40
	.endif
	recordability BS_ABILITY_BATTLER
	sethword sABILITY_OVERWRITE, 0
	return

BattleScript_SpeedBoostActivates::
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SpeedBoostActivatesEnd
	call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNRAISEDSPEED
	waitmessage B_WAIT_TIME_LONG
BattleScript_SpeedBoostActivatesEnd:
	end3

@ Can't compare directly to a value, have to compare to value at pointer
sZero:
.byte 0

BattleScript_MoodyActivates::
	call BattleScript_AbilityPopUp
	jumpifbyteequal sSTATCHANGER, sZero, BattleScript_MoodyLower
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoodyLower
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_ROSE, BattleScript_MoodyLower
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoodyLower:
	jumpifbyteequal sSAVED_STAT_CHANGER, sZero, BattleScript_MoodyEnd
	copybyte sSTATCHANGER, sSAVED_STAT_CHANGER
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoodyEnd
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_FELL, BattleScript_MoodyEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoodyEnd:
	end3

BattleScript_EmergencyExit::
	pause 5
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_LONG
BattleScript_EmergencyExitNoPopUp::
	playanimation BS_TARGET, B_ANIM_SLIDE_OFFSCREEN
	waitanimation
	openpartyscreen BS_TARGET, BattleScript_EmergencyExitEnd
	switchoutabilities BS_TARGET
	waitstate
	switchhandleorder BS_TARGET, 2
	returntoball BS_TARGET
	getswitchedmondata BS_TARGET
	switchindataupdate BS_TARGET
	hpthresholds BS_TARGET
	printstring STRINGID_SWITCHINMON
	switchinanim BS_TARGET, TRUE
	waitstate
	switchineffects BS_TARGET
BattleScript_EmergencyExitEnd:
	end2

BattleScript_EmergencyExitWild::
	pause 5
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_LONG
BattleScript_EmergencyExitWildNoPopUp::
	playanimation BS_TARGET, B_ANIM_SLIDE_OFFSCREEN
	waitanimation
	setoutcomeonteleport BS_TARGET
	finishaction
	end2

BattleScript_TraceActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNTRACED
	waitmessage B_WAIT_TIME_LONG
	settracedability BS_SCRIPTING
	switchinabilities BS_SCRIPTING
	return

BattleScript_TraceActivatesEnd3::
	call BattleScript_TraceActivates
	end3

BattleScript_ReceiverActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_RECEIVERABILITYTAKEOVER
	waitmessage B_WAIT_TIME_LONG
	settracedability BS_ABILITY_BATTLER
	return

BattleScript_AbilityHpHeal:
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXRESTOREDHPALITTLE2
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	return

BattleScript_HydrationActivates::
	call BattleScript_AbilityHpHeal
	printstring STRINGID_PKMNSXCUREDYPROBLEM
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	end3

BattleScript_RainDishActivates::
	call BattleScript_AbilityHpHeal
	end3

BattleScript_AppetiteActivates::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNRESTOREDHPUSINGABILITY
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	return

BattleScript_HeartCarveHealHP::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_CheekPouchActivates::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	copybyte gBattlerAttacker, gBattlerAbility
	call BattleScript_AbilityHpHeal
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_HarvestActivates::
	pause 5
	tryrecycleitem BattleScript_HarvestActivatesEnd
	call BattleScript_AbilityPopUp
	printstring STRINGID_HARVESTBERRY
	waitmessage B_WAIT_TIME_LONG
BattleScript_HarvestActivatesEnd:
	end3

BattleScript_SolarPowerActivates::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	call BattleScript_AbilityPopUp
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_SOLARPOWERHPDROP
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	end3

BattleScript_IceScalesActivatesHail::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ICESCALESGAINS
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_SolarPowerActivatesSun::
	call BattleScript_AbilityPopUp
	printstring STRINGID_USERGAINEDDAYBREAK
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_HealerActivates::
	call BattleScript_AbilityPopUp
	curestatus BS_SCRIPTING
	updatestatusicon BS_SCRIPTING
	printstring STRINGID_HEALERCURE
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_SandstreamActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXWHIPPEDUPSANDSTORM
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SANDSTORM_CONTINUES
	call BattleScript_TryTailwindAbilitiesLoop
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_SandSpitActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_ASANDSTORMKICKEDUP
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SANDSTORM_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	return

BattleScript_ShedSkinActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXCUREDYPROBLEM
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	end3

BattleScript_ActivateWeatherAbilities:
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_ActivateWeatherAbilities_Loop:
	copybyte sBATTLER, gBattlerTarget
	activateweatherchangeabilities BS_TARGET
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_ActivateWeatherAbilities_Loop
	restoretarget
	return

BattleScript_TryStatDropHoldEffects:
	itemstatchangeeffects BS_TARGET
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_ADRENALINE_ORB, BattleScript_TryStatDropHoldEffectsRet
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, 12, BattleScript_TryStatDropHoldEffectsRet
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN | STAT_CHANGE_ALLOW_PTR, BattleScript_TryStatDropHoldEffectsRet
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	copybyte sBATTLER, gBattlerTarget
	setlastuseditem BS_TARGET
	printstring STRINGID_USINGITEMSTATOFPKMNROSE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_TryStatDropHoldEffectsRet:
	return

BattleScript_IntimidateActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_IntimidateLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_IntimidateLoopIncrement
	jumpiftargetally BattleScript_IntimidateLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_IntimidateLoopIncrement
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_IntimidateLoopIncrement
	jumpiftype BS_TARGET, TYPE_DRAGON, BattleScript_IntimidatePreventedByDragon
	jumpifability BS_TARGET, ABILITY_HYPER_CUTTER, BattleScript_IntimidatePrevented
	jumpifability BS_TARGET, ABILITY_SCRAPPY, BattleScript_IntimidatePrevented
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_IntimidatePrevented
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_IntimidatePrevented
	jumpifability BS_TARGET, ABILITY_GUARD_DOG, BattleScript_IntimidateInReverse
BattleScript_IntimidateEffect:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_IntimidateLoopIncrement
	setgraphicalstatchangevalues
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_IntimidateContrary
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_IntimidateWontDecrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNCUTSATTACKWITH
BattleScript_IntimidateEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_TryStatDropHoldEffects
	restoreattacker
	restoretarget
BattleScript_IntimidateLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_IntimidateLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_IntimidatePreventedByDragon:
	copybyte sBATTLER, gBattlerTarget
	printstring STRINGID_PKMNPREVENTSSTATLOSSDRAGON
	goto BattleScript_IntimidateEffect_WaitString

BattleScript_IntimidatePrevented:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	goto BattleScript_IntimidateEffect_WaitString

BattleScript_IntimidateWontDecrease:
	printstring STRINGID_STATSWONTDECREASE
	goto BattleScript_IntimidateEffect_WaitString

BattleScript_IntimidateContrary:
	call BattleScript_AbilityPopUpTarget
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_IntimidateContrary_WontIncrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	goto BattleScript_IntimidateEffect_WaitString
BattleScript_IntimidateContrary_WontIncrease:
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	goto BattleScript_IntimidateEffect_WaitString

BattleScript_IntimidateInReverse:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUpTarget
	pause B_WAIT_TIME_SHORT
	modifybattlerstatstage BS_TARGET, STAT_ATK, INCREASE, 2, BattleScript_IntimidateLoopIncrement, ANIM_ON
	call BattleScript_TryStatDropHoldEffects
	goto BattleScript_IntimidateLoopIncrement

BattleScript_FriskActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_FriskLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_FriskLoopIncrement
	jumpiftargetally BattleScript_FriskLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_FriskLoopIncrement
BattleScript_FriskEffect:
	copybyte sBATTLER, gBattlerAttacker
	setembargo BattleScript_FriskPreventedNoAbility
	printstring STRINGID_PKMNCANTUSEITEMSANYMORE
BattleScript_FriskEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	restoreattacker
	restoretarget
BattleScript_FriskLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_FriskLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_FriskPrevented:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_LONG
BattleScript_FriskPreventedNoAbility:
	printstring STRINGID_BUTITFAILED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_FriskEffect_WaitString

BattleScript_UnnerveActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_UnnerveLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_UnnerveLoopIncrement
	jumpiftargetally BattleScript_UnnerveLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_UnnerveLoopIncrement
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_UnnervePrevented
	jumpifstatus2 BS_TARGET, STATUS2_TORMENT, BattleScript_UnnervePrevented
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_TitanicUnnervePrevented
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_TitanicUnnervePrevented
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilUnnervePrevented
	jumpifsafeguard BattleScript_SafeguardUnnervePrevented
BattleScript_UnnerveEffect:
	copybyte sBATTLER, gBattlerAttacker
	settorment BattleScript_UnnervePreventedNoAbility
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
BattleScript_UnnerveEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_TryDestinyKnotTormentAttacker
	restoreattacker
	restoretarget
BattleScript_UnnerveLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_UnnerveLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_UnnervePrevented:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	pause B_WAIT_TIME_LONG
BattleScript_UnnervePreventedNoAbility:
	printstring STRINGID_BUTITFAILED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_UnnerveEffect_WaitString

BattleScript_AromaVeilUnnervePrevented:
	call BattleScript_AbilityPopUpTarget
	call BattleScript_AromaVeilProtectsRet
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_TitanicUnnervePrevented::
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_ITDOESNTAFFECT
	goto BattleScript_UnnerveEffect_WaitString

BattleScript_SafeguardUnnervePrevented:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage B_WAIT_TIME_LONG
	restoretarget
	end3

BattleScript_HeartstringsActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_HeartstringsLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_HeartstringsLoopIncrement
	jumpiftargetally BattleScript_HeartstringsLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_HeartstringsLoopIncrement
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilHeartstringsPrevented
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_HeartstringsPreventedAbility
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_HeartstringsPreventedAbility
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_HeartstringsPreventedAbility
	jumpifsafeguard BattleScript_SafeguardHeartstringsPrevented
	jumpifswitchinabilitysucceed BS_ATTACKER, BattleScript_HeartstringsLoopIncrement
BattleScript_HeartstringsEffect:
	copybyte sBATTLER, gBattlerAttacker
	tryinfatuating BattleScript_HeartstringsPrevented
	printstring STRINGID_PKMNFELLINLOVE
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateAttacker
	setswitchinabilitysucceed BS_ATTACKER
BattleScript_HeartstringsLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_HeartstringsLoop
BattleScript_HeartstringsEnd::
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_AromaVeilHeartstringsPrevented::
	call BattleScript_AbilityPopUp
	call BattleScript_AromaVeilProtectsRet
	goto BattleScript_HeartstringsEnd

BattleScript_SafeguardHeartstringsPrevented::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HeartstringsEnd

BattleScript_HeartstringsPrevented:
	printstring STRINGID_ABILITYCANTINFATUATE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HeartstringsLoopIncrement

BattleScript_HeartstringsPreventedAbility:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSINFATUATIONWITH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HeartstringsLoopIncrement

BattleScript_GlaringStaggerActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_GlaringStaggerLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_GlaringStaggerLoopIncrement
	jumpiftargetally BattleScript_GlaringStaggerLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_GlaringStaggerLoopIncrement
	jumpifability BS_TARGET, ABILITY_MAGIC_GUARD, BattleScript_GlaringStaggerLoopIncrement
	jumpifability BS_TARGET, ABILITY_SUGAR_COAT, BattleScript_GlaringStaggerLoopIncrement
	jumpifterucharmprotected BS_TARGET, BattleScript_GlaringStaggerLoopIncrement
BattleScript_GlaringStaggerEffect:
	copybyte sBATTLER, gBattlerAttacker
	staggerdamage
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNCUTSHPWITH
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
BattleScript_GlaringStaggerLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_GlaringStaggerLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_ArbiterActivates::
	setbyte gBattlerTarget, 0
BattleScript_ArbiterActivatesLoop:
	jumpifability BS_TARGET, ABILITY_MAGIC_GUARD, BattleScript_ArbiterActivatesIncrement
	jumpifability BS_TARGET, ABILITY_SUGAR_COAT, BattleScript_ArbiterActivatesIncrement
	jumpifterucharmprotected BS_TARGET, BattleScript_ArbiterActivatesIncrement
	jumpifabsent BS_TARGET, BattleScript_ArbiterActivatesIncrement
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_ArbiterActivatesIncrement
BattleScript_ArbiterActivatesDmg::
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_ArbiterActivates_ShowPopUp
BattleScript_ArbiterActivates_DmgAfterPopUp:
	printstring STRINGID_PKMNCUTSHPWITH2
	waitmessage B_WAIT_TIME_LONG
	arbiterdamage
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	jumpifhasnohp BS_TARGET, BattleScript_ArbiterActivates_HidePopUp
BattleScript_ArbiterActivatesIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_ArbiterActivatesLoop
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_ArbiterActivatesEnd
	destroyabilitypopup
	pause 15
BattleScript_ArbiterActivatesEnd:
	end3
BattleScript_ArbiterActivates_ShowPopUp:
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setbyte sFIXED_ABILITY_POPUP, TRUE
	goto BattleScript_ArbiterActivates_DmgAfterPopUp
BattleScript_ArbiterActivates_HidePopUp:
	destroyabilitypopup
	tryfaintmon BS_TARGET
	goto BattleScript_ArbiterActivatesIncrement

BattleScript_WatcherActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_WatcherLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_WatcherLoopIncrement
	jumpiftargetally BattleScript_WatcherLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_WatcherLoopIncrement
BattleScript_WatcherEffect:
	copybyte sBATTLER, gBattlerAttacker
	setalwayshitflag
	printstring STRINGID_WATCHERSALVATION
	waitmessage B_WAIT_TIME_LONG
BattleScript_WatcherEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	restoreattacker
	restoretarget
BattleScript_WatcherLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_WatcherLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_SolarPowerActivatesSunEveryone::
	call BattleScript_AbilityPopUp
	printstring STRINGID_USERGAINEDDAYBREAK
	waitmessage B_WAIT_TIME_LONG
	setbyte gBattlerTarget, 0
BattleScript_SolarPowerActivatesSunEveryoneLoop:
	jumpiftargetally BattleScript_SolarPowerActivatesSunEveryoneIncrement
	jumpifability BS_TARGET, ABILITY_MAGIC_GUARD, BattleScript_SolarPowerActivatesSunEveryoneIncrement
	jumpifability BS_TARGET, ABILITY_SUGAR_COAT, BattleScript_SolarPowerActivatesSunEveryoneIncrement
	jumpifterucharmprotected BS_TARGET, BattleScript_SolarPowerActivatesSunEveryoneIncrement
	jumpifabsent BS_TARGET, BattleScript_SolarPowerActivatesSunEveryoneIncrement
	printstring STRINGID_PKMNCUTSHPWITH2
	waitmessage B_WAIT_TIME_LONG
	solarpowerdamage
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	jumpifhasnohp BS_TARGET, BattleScript_SolarPowerActivatesSunEveryone_TryFaintMon
BattleScript_SolarPowerActivatesSunEveryoneIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_SolarPowerActivatesSunEveryoneLoop
	end3
BattleScript_SolarPowerActivatesSunEveryone_TryFaintMon:
	tryfaintmon BS_TARGET
	goto BattleScript_SolarPowerActivatesSunEveryoneIncrement

BattleScript_SolarPowerActivatesEveryone::
	setbyte gBattlerTarget, 0
BattleScript_SolarPowerActivatesEveryoneLoop:
	jumpiftargetally BattleScript_SolarPowerActivatesEveryoneIncrement
	jumpifability BS_TARGET, ABILITY_MAGIC_GUARD, BattleScript_SolarPowerActivatesEveryoneIncrement
	jumpifability BS_TARGET, ABILITY_SUGAR_COAT, BattleScript_SolarPowerActivatesEveryoneIncrement
	jumpifterucharmprotected BS_TARGET, BattleScript_SolarPowerActivatesEveryoneIncrement
	jumpifabsent BS_TARGET, BattleScript_SolarPowerActivatesEveryoneIncrement
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_SolarPowerActivatesEveryone_ShowPopUp
BattleScript_SolarPowerActivatesEveryone_DmgAfterPopUp:
	printstring STRINGID_PKMNCUTSHPWITH2
	waitmessage B_WAIT_TIME_LONG
	solarpowerdamage
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	jumpifhasnohp BS_TARGET, BattleScript_SolarPowerActivatesEveryone_HidePopUp
BattleScript_SolarPowerActivatesEveryoneIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_SolarPowerActivatesEveryoneLoop
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_SolarPowerActivatesEveryoneEnd
	destroyabilitypopup
	pause 15
BattleScript_SolarPowerActivatesEveryoneEnd:
	end3
BattleScript_SolarPowerActivatesEveryone_ShowPopUp:
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setbyte sFIXED_ABILITY_POPUP, TRUE
	goto BattleScript_SolarPowerActivatesEveryone_DmgAfterPopUp
BattleScript_SolarPowerActivatesEveryone_HidePopUp:
	destroyabilitypopup
	tryfaintmon BS_TARGET
	goto BattleScript_SolarPowerActivatesEveryoneIncrement

BattleScript_DelugeHurts::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_DelugeLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_DelugeLoopIncrement
	jumpiftargetally BattleScript_DelugeLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_DelugeLoopIncrement
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_DelugeLoopIncrement
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_DelugePrevented
BattleScript_DelugeEffect:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_SPEED, 2, TRUE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_DelugeLoopIncrement
	setgraphicalstatchangevalues
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_DelugeContrary
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DelugeWontDecrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNCUTSSPEEDWITH
BattleScript_DelugeEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
BattleScript_DelugeLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_DelugeLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_DelugePrevented::
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	goto BattleScript_DelugeEffect_WaitString

BattleScript_DelugeContrary:
	call BattleScript_AbilityPopUpTarget
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DelugeContrary_WontIncrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	goto BattleScript_DelugeEffect_WaitString
BattleScript_DelugeContrary_WontIncrease:
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	goto BattleScript_DelugeEffect_WaitString

BattleScript_DelugeWontDecrease:
	printstring STRINGID_STATSWONTDECREASE
	goto BattleScript_DelugeEffect_WaitString

BattleScript_DroughtActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXINTENSIFIEDSUN
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SUN_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_MudWaterSportActivates::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_ELECTRICITYANDFIREWEAKENED
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_MUD_WATER_SPORT
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_MudSportActivates::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_ELECTRICITYWEAKENED
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_MUD_SPORT
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_WaterSportActivates::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_FIREWEAKENED
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_WATER_SPORT
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_DesolateLandActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_EXTREMELYHARSHSUNLIGHT
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SUN_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_PrimalWeatherBlocksMove::
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_ATTACKSTRING_PRINTED, BattleScript_MoveEnd @in case of multi-target moves, if move fails once, no point in printing the message twice
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	pause B_WAIT_TIME_SHORT
	ppreduce
	printfromtable gPrimalWeatherBlocksStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_PrimordialSeaActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_HEAVYRAIN
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_RAIN_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_DeltaStreamActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_MYSTERIOUSAIRCURRENT
	waitstate
	playanimation BS_ATTACKER, B_ANIM_STRONG_WINDS
	end3

BattleScript_ProtosynthesisActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_SUNLIGHTACTIVATEDABILITY
	waitmessage B_WAIT_TIME_MED
	printstring STRINGID_STATWASHEIGHTENED
	waitmessage B_WAIT_TIME_MED
	end3

BattleScript_QuarkDriveActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ELECTRICTERRAINACTIVATEDABILITY
	waitmessage B_WAIT_TIME_MED
	printstring STRINGID_STATWASHEIGHTENED
	waitmessage B_WAIT_TIME_MED
	end3

BattleScript_RuinAbilityActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ABILITYWEAKENEDFSURROUNDINGMONSSTAT
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_WhiteSmokeAbilityActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	setmist	
	printstring STRINGID_ABILITYSUMMONEDMIST
	playanimation BS_ATTACKER, B_ANIM_WHITE_SMOKE	
	waitmessage B_WAIT_TIME_SHORT
	end3

BattleScript_RuinWardHurtActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXDAMAGEDITALITTLE
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	end3

BattleScript_RuinWardActivates::
	call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_SAFEGUARD
	waitanimation
	printstring STRINGID_ABILITYCOVEREDVEIL
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_LUCKY_CHANT
	waitanimation
	printstring STRINGID_ABILITYSHIELDEDFROMCRITICALHITS
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_RuinWardSafeguardActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_SAFEGUARD
	waitanimation
	printstring STRINGID_ABILITYCOVEREDVEIL
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_RuinWardLuckyChantActivates::
	call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_LUCKY_CHANT
	waitanimation
	printstring STRINGID_ABILITYSHIELDEDFROMCRITICALHITS
	waitmessage B_WAIT_TIME_SHORT
	end3

BattleScript_EntrancingAbilityActivates::
	call BattleScript_AbilityPopUp		
	printstring STRINGID_ABILITYENTRANCED
	waitmessage B_WAIT_TIME_SHORT
	end3

BattleScript_MagicianAbilityActivates::	
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_MagicianLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_MagicianLoopIncrement
	jumpiftargetally BattleScript_MagicianLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_MagicianLoopIncrement
	jumpifsubstituteblocks BattleScript_MagicianLoopIncrement
	jumpifswitchinabilitysucceed BS_ATTACKER, BattleScript_MagicianLoopIncrement
BattleScript_MagicianEffect:
	copybyte sBATTLER, gBattlerAttacker
	tryswapitemsmagician BattleScript_MagicianPrevented
	playanimation BS_ATTACKER, B_ANIM_SWITCH_ITEMS
	waitanimation
	printstring STRINGID_PKMNSWITCHEDITEMS
	waitmessage B_WAIT_TIME_LONG
	printfromtable gItemSwapStringIds
	setswitchinabilitysucceed BS_ATTACKER
BattleScript_MagicianLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_MagicianLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_MagicianPrevented:
	printstring STRINGID_ABILITYCANTSWAPITEMS
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MagicianLoopIncrement

BattleScript_FallingAbilityActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_ABILITYWEAKENEDFSURROUNDINGMONSSTATS
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_SupremeOverlordActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_ATTACKERGAINEDSTRENGTHFROMTHEFALLEN
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_CostarActivates::
	pause B_WAIT_TIME_SHORT
	savetarget
	copybyte gBattlerTarget, sBATTLER
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNCOPIEDSTATCHANGES
	waitmessage B_WAIT_TIME_LONG
	restoretarget
	end3

BattleScript_HealerActivates2::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_HEALERRESTORATION
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	end3

BattleScript_AttackWeakenedByStrongWinds::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ATTACKWEAKENEDBSTRONGWINDS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MimicryActivates_End3::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_BATTLERTYPECHANGEDTO
	waitmessage B_WAIT_TIME_SHORT
	end3

BattleScript_SnowWarningActivatesHail::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_SNOWWARNINGHAIL
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_HAIL_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_SnowWarningActivatesSnow::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_SNOWWARNINGSNOW
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SNOW_CONTINUES
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_GustyActivatesTailwind::
	call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_TAILWIND
	waitanimation
	printstring STRINGID_TAILWINDBLEW
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryTailwindAbilitiesLoop
	end3

BattleScript_ActivateTerrainEffects:
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_ActivateTerrainSeed:
	copybyte sBATTLER, gBattlerTarget
	doterrainseed BS_TARGET, BattleScript_ActivateTerrainAbility
	removeitem BS_TARGET
BattleScript_ActivateTerrainAbility:
	activateterrainchangeabilities BS_TARGET
	addbyte gBattlerTarget, 0x1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_ActivateTerrainSeed
	restoretarget
	return

BattleScript_ActivateSwitchInAbilities:
	copybyte sBATTLER, gBattlerAttacker
	setbyte gBattlerAttacker, 0
BattleScript_ActivateSwitchInAbilities_Loop:
	switchinabilities BS_ATTACKER
BattleScript_ActivateSwitchInAbilities_Increment:
	addbyte gBattlerAttacker, 1
	jumpifbytenotequal gBattlerAttacker, gBattlersCount, BattleScript_ActivateSwitchInAbilities_Loop
	copybyte gBattlerAttacker, sBATTLER
	return

BattleScript_ActivateTerrainAbilities:
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_ActivateTerrainAbilities_Loop:
	activateterrainchangeabilities BS_ATTACKER
BattleScript_ActivateTerrainAbilities_Increment:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_ActivateTerrainAbilities_Loop
	restoretarget
	return

BattleScript_ElectricSurgeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESELECTRIC
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	end3

BattleScript_MistySurgeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESMISTY
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	end3

BattleScript_GrassySurgeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESGRASSY
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	end3

BattleScript_PsychicSurgeActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_TERRAINBECOMESPSYCHIC
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG
	call BattleScript_ActivateTerrainEffects
	end3

BattleScript_BadDreamsActivates::
	setbyte gBattlerTarget, 0
BattleScript_BadDreamsLoop:
	jumpiftargetally BattleScript_BadDreamsIncrement
	jumpifability BS_TARGET, ABILITY_MAGIC_GUARD, BattleScript_BadDreamsIncrement
	jumpifability BS_TARGET, ABILITY_SUGAR_COAT, BattleScript_BadDreamsIncrement
	jumpifterucharmprotected BS_TARGET, BattleScript_BadDreamsIncrement
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_BadDreams_Dmg
	jumpifstatus BS_TARGET, STATUS1_SLEEP_ANY, BattleScript_BadDreams_Dmg
	goto BattleScript_BadDreamsIncrement
BattleScript_BadDreams_Dmg:
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_BadDreams_ShowPopUp
BattleScript_BadDreams_DmgAfterPopUp:
	printstring STRINGID_BADDREAMSDMG
	waitmessage B_WAIT_TIME_LONG
	dmg_1_8_targethp
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	jumpifhasnohp BS_TARGET, BattleScript_BadDreams_HidePopUp
BattleScript_BadDreamsIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_BadDreamsLoop
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_BadDreamsEnd
	destroyabilitypopup
	pause 15
BattleScript_BadDreamsEnd:
	end3
BattleScript_BadDreams_ShowPopUp:
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setbyte sFIXED_ABILITY_POPUP, TRUE
	goto BattleScript_BadDreams_DmgAfterPopUp
BattleScript_BadDreams_HidePopUp:
	destroyabilitypopup
	tryfaintmon BS_TARGET
	goto BattleScript_BadDreamsIncrement

BattleScript_MiasmaActivates::
	setbyte gBattlerTarget, 0
BattleScript_MiasmaLoop:
	jumpiftargetally BattleScript_MiasmaIncrement
	jumpifability BS_TARGET, ABILITY_MAGIC_GUARD, BattleScript_MiasmaIncrement
	jumpifability BS_TARGET, ABILITY_SUGAR_COAT, BattleScript_MiasmaIncrement
	jumpifterucharmprotected BS_TARGET, BattleScript_MiasmaIncrement
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_Miasma_Dmg
	goto BattleScript_MiasmaIncrement
BattleScript_Miasma_Dmg:
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_Miasma_ShowPopUp
BattleScript_Miasma_DmgAfterPopUp:
	printstring STRINGID_MIASMADMG
	waitmessage B_WAIT_TIME_LONG
	dmg_1_8_targethp
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	jumpifhasnohp BS_TARGET, BattleScript_Miasma_HidePopUp
BattleScript_MiasmaIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_MiasmaLoop
	jumpifbyteequal sFIXED_ABILITY_POPUP, sZero, BattleScript_MiasmaEnd
	destroyabilitypopup
	pause 15
BattleScript_MiasmaEnd:
	end3
BattleScript_Miasma_ShowPopUp:
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setbyte sFIXED_ABILITY_POPUP, TRUE
	goto BattleScript_Miasma_DmgAfterPopUp
BattleScript_Miasma_HidePopUp:
	destroyabilitypopup
	tryfaintmon BS_TARGET
	goto BattleScript_MiasmaIncrement

BattleScript_TookAttack::
	attackstring
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNSXTOOKATTACK
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_ATTACKSTRING_PRINTED
	return

BattleScript_OvertookAttack::
	attackstring
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNOVERTOOKATTACK
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_ATTACKSTRING_PRINTED
	return

BattleScript_SturdyPreventsOHKO::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPROTECTEDBY
	pause B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_DampStopsExplosion::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_PKMNPREVENTSUSAGE
	pause B_WAIT_TIME_LONG
	moveendto MOVEEND_NEXT_TARGET
	moveendcase MOVEEND_CLEAR_BITS
	end

BattleScript_MoveHPDrain_PPLoss::
	ppreduce
BattleScript_MoveHPDrain::
	attackstring
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNRESTOREDHPUSING
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	goto BattleScript_MoveEnd

BattleScript_MoveStatDrain_PPLoss::
	ppreduce
BattleScript_MoveStatDrain::
	attackstring
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_MoveStatDrain_Cont
.if B_ABSORBING_ABILITY_STRING >= GEN_5
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
.else
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
.endif
BattleScript_MoveStatDrain_Cont:
	clearsemiinvulnerablebit
	goto BattleScript_MoveEnd

BattleScript_MoveStatDrain2_PPLoss::
	ppreduce
BattleScript_MoveStatDrain2::
	attackstring
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_MoveStatDrain2Atk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_MoveStatDrain2Atk::
	setstatchanger STAT_ATK, 1, FALSE
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	statbuffchange MOVE_EFFECT_ATK_PLUS_1 | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveStatDrain2TrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveStatDrain2TrySpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoveStatDrain2TrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	statbuffchange MOVE_EFFECT_SP_ATK_PLUS_1 | STAT_CHANGE_ALLOW_PTR, BattleScript_MoveStatDrain2End
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MoveStatDrain2End
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoveStatDrain2End:
	clearsemiinvulnerablebit
	goto BattleScript_MoveEnd

BattleScript_DrySkinHealStatUp_PPLoss::
	ppreduce
BattleScript_DrySkinHealStatUp::
	attackstring
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNRESTOREDHPUSING
	waitmessage B_WAIT_TIME_LONG
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_DrySkinHealStatUp_Cont
.if B_ABSORBING_ABILITY_STRING >= GEN_5
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
.else
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
.endif
BattleScript_DrySkinHealStatUp_Cont:
	clearsemiinvulnerablebit
	goto BattleScript_MoveEnd

BattleScript_MoveStatNegativeDrain_PPLoss::
	ppreduce
BattleScript_MoveStatNegativeDrain::
	attackstring
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_MoveStatNegativeDrain_Cont
.if B_ABSORBING_ABILITY_STRING >= GEN_5
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
.else
	printstring STRINGID_TARGETABILITYSTATLOWER
	waitmessage B_WAIT_TIME_LONG
.endif
BattleScript_MoveStatNegativeDrain_Cont:
	clearsemiinvulnerablebit
	goto BattleScript_MoveEnd

BattleScript_WindPowerCharge_PPLoss::
	ppreduce
BattleScript_WindPowerCharge::
	attackstring
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	setcharge BS_TARGET
	printstring STRINGID_BEINGHITCHARGEDPKMNWITHPOWER
	waitmessage B_WAIT_TIME_LONG
	clearsemiinvulnerablebit
	goto BattleScript_MoveEnd

BattleScript_MonMadeMoveUseless_PPLoss::
	ppreduce
BattleScript_MonMadeMoveUseless::
	attackstring
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXMADEYUSELESS
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	goto BattleScript_MoveEnd

BattleScript_FlashFireBoost_PPLoss::
	ppreduce
BattleScript_FlashFireBoost::
	attackstring
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printfromtable gFlashFireStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_AbilityPreventsPhasingOut::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNANCHORSITSELFWITH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_AbilityNoStatLoss::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ItemNoStatLoss::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_CLEARAMULETWONTLOWERSTATS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ItemNoSpecificStatLoss::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ITEMWONTLOWERCERTAINSTAT
	waitmessage B_WAIT_TIME_LONG
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY
	return

BattleScript_SuperMagnetNoStatLoss::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_SUPERMAGNETNOSTATLOSS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PurifiedNoStatChange::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PURIFIEDNOSTATCHANGE
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_BRNPrevention::
	pause B_WAIT_TIME_SHORT
	printfromtable gBRNPreventionStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_FSBPrevention::
	pause B_WAIT_TIME_SHORT
	printfromtable gFSBPreventionStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BloomingPrevention::
	pause B_WAIT_TIME_SHORT
	printfromtable gBloomingPreventionStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ExposedPrevention::
	pause B_WAIT_TIME_SHORT
	printfromtable gExposedPreventionStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PNCPrevention::
	pause B_WAIT_TIME_SHORT
	printfromtable gPNCPreventionStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PRLZPrevention::
	pause B_WAIT_TIME_SHORT
	printfromtable gPRLZPreventionStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PSNPrevention::
	pause B_WAIT_TIME_SHORT
	printfromtable gPSNPreventionStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ObliviousPreventsAttraction::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSROMANCEWITH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_FlinchPrevention::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXPREVENTSFLINCHING
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SteadFastFlinchPrevention::
	pause B_WAIT_TIME_SHORTEST
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXPREVENTSFLINCHING
	waitmessage B_WAIT_TIME_SHORT
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SteadFastFlinchPrevention_Speed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SteadFastFlinchPrevention_Speed
	call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	setbyte gBattleCommunication STAT_ATK
	stattextbuffer BS_TARGET
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_SHORTEST
BattleScript_SteadFastFlinchPrevention_Speed:
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_SteadFastFlinchPrevention_End
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_SteadFastFlinchPrevention_End
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	setbyte gBattleCommunication STAT_SPEED
	stattextbuffer BS_TARGET
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_SHORTEST	
BattleScript_SteadFastFlinchPrevention_End:
	goto BattleScript_MoveEnd

BattleScript_OwnTempoPrevents::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSCONFUSIONWITH
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SoundproofProtected::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXBLOCKSY
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	goto BattleScript_MoveEnd

BattleScript_IceFaceNullsDamage::
	attackstring
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	call BattleScript_TargetFormChangeWithString
	goto BattleScript_MoveEnd

BattleScript_DazzlingProtected::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_POKEMONCANNOTUSEMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MoveUsedPsychicTerrainPrevents::
	printstring STRINGID_POKEMONCANNOTUSEMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_GrassyTerrainHeals::
	call BattleScript_GrassyTerrainHeals_Ret
	end2

BattleScript_GrassyTerrainHeals_Ret::
	setbyte gBattleCommunication, 0
BattleScript_GrassyTerrainLoop:
	copyarraywithindex gBattlerAttacker, gBattlerByTurnOrder, gBattleCommunication, 1
	checkgrassyterrainheal BS_ATTACKER, BattleScript_GrassyTerrainLoopIncrement
	printstring STRINGID_GRASSYTERRAINHEALS
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
BattleScript_GrassyTerrainLoopIncrement::
	addbyte gBattleCommunication, 1
	jumpifbytenotequal gBattleCommunication, gBattlersCount, BattleScript_GrassyTerrainLoop
	bicword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	jumpifword CMP_COMMON_BITS, gFieldStatuses, STATUS_FIELD_TERRAIN_PERMANENT, BattleScript_GrassyTerrainHealEnd
BattleScript_GrassyTerrainHealEnd:
	return

BattleScript_AbilityNoSpecificStatLoss::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXPREVENTSYLOSS
	waitmessage B_WAIT_TIME_LONG
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY
	end2

BattleScript_StickyHoldActivates::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXMADEYINEFFECTIVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_StickyHoldActivatesMagician::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PREVENTEDFROMWORKING
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ColorChangeActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNCHANGEDTYPEWITH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ReformActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNRESISTEDTYPEWITH
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ProteanActivates::
	pause B_WAIT_TIME_SHORTEST
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_TeraShellDistortingTypeMatchups::
	pause B_WAIT_TIME_SHORTEST
	call BattleScript_AbilityPopUp
	printstring STRINGID_EGGSROYALE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_CursedBodyActivatesDisable::
	call BattleScript_AbilityPopUp
	printstring STRINGID_CURSEDBODYDISABLED
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotDisabledTarget
	return

BattleScript_CursedBodyActivatesTorment::
	call BattleScript_AbilityPopUp
	printstring STRINGID_CURSEDBODYTORMENTED
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentTarget
	return

BattleScript_CursedBodyActivatesCurse::
	call BattleScript_AbilityPopUp
	printstring STRINGID_CURSEDBODYCURSED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_CursedAmuletActivates::
	printstring STRINGID_CURSEDAMULETDISABLED
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotDisabledTarget
	return

BattleScript_MummyActivates::
.if B_ABILITY_POP_UP == TRUE
	call BattleScript_AbilityPopUpTarget
	setbyte sFIXED_ABILITY_POPUP, TRUE
	copybyte gBattlerAbility, gBattlerAttacker
	copyhword sABILITY_OVERWRITE, gLastUsedAbility
	call BattleScript_AbilityPopUpOverwriteThenNormal
.endif
	recordability BS_TARGET
	recordability BS_ATTACKER
	printstring STRINGID_ATTACKERACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MelancholiaActivates::
	call BattleScript_AbilityPopUpTarget
	destroyabilitypopup
	setbyte sFIXED_ABILITY_POPUP, TRUE
	copybyte gBattlerAbility, gBattlerAttacker
	copyhword sABILITY_OVERWRITE, gLastUsedAbility
	setbyte sFIXED_ABILITY_POPUP, TRUE
	showabilitypopup BS_ABILITY_BATTLER
	pause 60
	recordability BS_ABILITY_BATTLER
	destroyabilitypopup
	pause 40
	recordability BS_TARGET
	recordability BS_ATTACKER
	printstring STRINGID_ATTACKERACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityPopUpOverwriteThenNormal:
	setbyte sFIXED_ABILITY_POPUP, TRUE
	showabilitypopup BS_ABILITY_BATTLER
	pause 60
	sethword sABILITY_OVERWRITE, 0
	updateabilitypopup BS_ABILITY_BATTLER
	pause 20
	recordability BS_ABILITY_BATTLER
	destroyabilitypopup
	pause 40
	return

BattleScript_LovesickMummyEffectActivates::
.if B_ABILITY_POP_UP == TRUE
	call BattleScript_AbilityPopUpTarget
	setbyte sFIXED_ABILITY_POPUP, TRUE
	copybyte gBattlerAbility, gBattlerAttacker
	copyhword sABILITY_OVERWRITE, gLastUsedAbility
	call BattleScript_AbilityPopUpOverwriteThenNormal
.endif
	recordability BS_TARGET
	recordability BS_ATTACKER
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_WanderingSpiritActivates::
.if B_ABILITY_POP_UP == TRUE
	setbyte sFIXED_ABILITY_POPUP, TRUE
	sethword sABILITY_OVERWRITE, ABILITY_WANDERING_SPIRIT
	showabilitypopup BS_TARGET
	pause 60
	sethword sABILITY_OVERWRITE, 0
	updateabilitypopup BS_TARGET
	pause 20
	destroyabilitypopup
	pause 40
	copybyte gBattlerAbility, gBattlerAttacker
	setbyte sFIXED_ABILITY_POPUP, TRUE
	copyhword sABILITY_OVERWRITE, gLastUsedAbility
	showabilitypopup BS_ATTACKER
	pause 60
	sethword sABILITY_OVERWRITE, 0
	updateabilitypopup BS_ATTACKER
	pause 20
	destroyabilitypopup
	pause 40
.endif
	printstring STRINGID_SWAPPEDABILITIES
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	switchinabilities BS_TARGET
	return

BattleScript_TargetsStatWasMaxedOut::
	call BattleScript_AbilityPopUp
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, NULL
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETSSTATWASMAXEDOUT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BattlerAbilityStatRaiseOnSwitchIn::
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, NULL
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_BATTLERABILITYRAISEDSTAT
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_WindRiderStatRaiseOnSwitchIn::
	call BattleScript_AbilityPopUp
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_WindRiderActivatesSpAtk
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WindRiderDefAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_WindRiderActivatesSpAtk
	pause B_WAIT_TIME_SHORTEST
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_WindRiderActivatesSpAtk
BattleScript_WindRiderDefAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_BATTLERABILITYRAISEDSTAT
	waitmessage B_WAIT_TIME_LONG
BattleScript_WindRiderActivatesSpAtk:
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_WindRiderActivatesEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WindRiderSpAtkAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_EMPTY, BattleScript_WindRiderActivatesEnd
	pause B_WAIT_TIME_SHORTEST
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_WindRiderActivatesEnd
BattleScript_WindRiderSpAtkAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_BATTLERABILITYRAISEDSTAT
	waitmessage B_WAIT_TIME_LONG
BattleScript_WindRiderActivatesEnd:
	end3

BattleScript_WindPowerChargeOnSwitchIn::
	call BattleScript_AbilityPopUp
	setcharge BS_ATTACKER
	printstring STRINGID_PKMNCHARGINGPOWER
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_ScriptingAbilityStatRaise::
	copybyte gBattlerAbility, sBATTLER
	call BattleScript_AbilityPopUp
	copybyte sSAVED_DMG, gBattlerAttacker
	copybyte gBattlerAttacker, sBATTLER
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, NULL
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_ATTACKERABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
	copybyte gBattlerAttacker, sSAVED_DMG
	return

BattleScript_WeakArmorActivates::
	call BattleScript_AbilityPopUp
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_WeakArmorActivatesSpeed
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_WeakArmorDefAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_WeakArmorActivatesSpeed
	pause B_WAIT_TIME_SHORTEST
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_WeakArmorActivatesSpeed
BattleScript_WeakArmorDefAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETABILITYSTATLOWER
	waitmessage B_WAIT_TIME_LONG
BattleScript_WeakArmorActivatesSpeed:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_WeakArmorActivatesEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WeakArmorSpeedAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_EMPTY, BattleScript_WeakArmorActivatesEnd
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_WeakArmorActivatesEnd
BattleScript_WeakArmorSpeedAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
BattleScript_WeakArmorActivatesEnd:
	return

BattleScript_RaiseStatOnFaintingTarget::
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_RaiseStatOnFaintingTarget_End
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_LASTABILITYRAISEDSTAT
	waitmessage B_WAIT_TIME_LONG
BattleScript_RaiseStatOnFaintingTarget_End:
	return

BattleScript_AttackerAbilityStatRaise::
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_AttackerAbilityStatRaise_End
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_ATTACKERABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
BattleScript_AttackerAbilityStatRaise_End:
	return

BattleScript_FellStingerRaisesStat::
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_FellStingerRaisesAtkEnd
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_ROSE, BattleScript_FellStingerRaisesAtkEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FellStingerRaisesAtkEnd:
	return

BattleScript_ShadowForceSelfPhantom::
	printstring STRINGID_USERGAINSPHANTOM
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AttackerAbilityStatRaiseEnd3::
	call BattleScript_AttackerAbilityStatRaise
	end3

BattleScript_SwitchInAbilityMsg::
	call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_SwitchInAbilityMsgRet::
	call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ActivateAsOne::
	call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	@ show unnerve
	sethword sABILITY_OVERWRITE, ABILITY_UNNERVE
	setbyte cMULTISTRING_CHOOSER, B_MSG_SWITCHIN_UNNERVE
	call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_ImposterActivates::
	call BattleScript_AbilityPopUp
	transformdataexecution
	playmoveanimation BS_ATTACKER, MOVE_TRANSFORM
	waitanimation
	printstring STRINGID_IMPOSTERTRANSFORM
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_FairyLockEndTurn::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_EVASION, STAT_CHANGE_NEGATIVE
	setstatchanger STAT_EVASION, 1, TRUE
	statbuffchange STAT_CHANGE_ALLOW_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_FairyLockEndTurnEnd
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_FairyLockEndTurnEnd:
	end2

BattleScript_HurtAttacker:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHURTSWITH
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	return

BattleScript_HurtDefender:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNHURTSWITHINATTK
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	return

BattleScript_RoughSkinActivates::
	call BattleScript_AbilityPopUp
	call BattleScript_HurtAttacker
	return

BattleScript_IronBarbsActivates::
	call BattleScript_AbilityPopUp
	call BattleScript_HurtDefender
	return

BattleScript_RockyHelmetActivates::
	@ don't play the animation for a fainted mon
	jumpifabsent BS_TARGET, BattleScript_RockyHelmetActivatesDmg
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
BattleScript_RockyHelmetActivatesDmg:
	call BattleScript_HurtAttacker
	return

BattleScript_SpikyShieldEffect::
	jumpifabsent BS_ATTACKER, BattleScript_SpikyShieldRet
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHURTSWITH
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
BattleScript_SpikyShieldRet::
	return

BattleScript_KingsShieldEffect::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	seteffectsecondary
	setmoveeffect 0
	copybyte sBATTLER, gBattlerTarget
	copybyte gBattlerTarget, gBattlerAttacker
	copybyte gBattlerAttacker, sBATTLER
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	return

BattleScript_DefendOrderEffect::
	jumpifabsent BS_ATTACKER, BattleScript_DefendOrderRet
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHURTSWITH
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
BattleScript_DefendOrderRet::
	return

BattleScript_AcidArmorEffect::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	seteffectsecondary
	setmoveeffect 0
	copybyte sBATTLER, gBattlerTarget
	copybyte gBattlerTarget, gBattlerAttacker
	copybyte gBattlerAttacker, sBATTLER
	return

BattleScript_DetectEffect::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	seteffectsecondary
	setmoveeffect MOVE_EFFECT_ACC_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	return

BattleScript_ShellteredEffect::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	seteffectsecondary
	setmoveeffect MOVE_EFFECT_DEF_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	return

BattleScript_BanefulBunkerEffect::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_SAFEGUARD | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	seteffectsecondary
	setmoveeffect 0
	orhalfword gMoveResultFlags, MOVE_RESULT_MISSED
	return

BattleScript_CuteCharmInfatuationActivates::
	call BattleScript_AbilityPopUp
	status2animation BS_ATTACKER, STATUS2_INFATUATION
	printstring STRINGID_PKMNSXINFATUATEDY
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateTarget
	return

BattleScript_CuteCharmInfatuationActivates2::
	call BattleScript_AbilityPopUp
	status2animation BS_TARGET, STATUS2_INFATUATION
	printstring STRINGID_PKMNSXINFATUATEDY2
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateAttacker
	return

BattleScript_CuteCharmAllureActivates::
	call BattleScript_AbilityPopUp
	status2animation BS_ATTACKER, STATUS2_INFATUATION
	printstring STRINGID_PKMNSHEARTFLUTTERSSHALALALA2
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateTarget
	return

BattleScript_CuteCharmAllureActivates2::
	call BattleScript_AbilityPopUp
	status2animation BS_TARGET, STATUS2_INFATUATION
	printstring STRINGID_PKMNSHEARTFLUTTERSSHALALALA
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateAttacker
	return

BattleScript_LovesickActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_LovesickLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_LovesickLoopIncrement
	jumpiftargetally BattleScript_LovesickLoopIncrement
	jumpifabsent BS_ATTACKER, BattleScript_LovesickLoopIncrement
	jumpifability BS_ATTACKER_SIDE, ABILITY_AROMA_VEIL, BattleScript_LovesickLoopIncrement
	swapattackerwithtarget
	jumpifsafeguard BattleScript_LovesickLoopIncrement2
	swapattackerwithtarget
	jumpifswitchinabilitysucceed BS_ATTACKER, BattleScript_LovesickLoopIncrement
BattleScript_LovesickEffect:
	copybyte sBATTLER, gBattlerAttacker
	infatuatewithbattler BS_ATTACKER, BS_TARGET
	status2animation BS_ATTACKER, STATUS2_INFATUATION
	waitanimation
	printstring STRINGID_PKMNSXINFATUATEDY3
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateTarget
	setswitchinabilitysucceed BS_ATTACKER
BattleScript_LovesickLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_LovesickLoop
BattleScript_LovesickEnd::
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3
BattleScript_LovesickLoopIncrement2:
	swapattackerwithtarget
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_LovesickLoop
	goto BattleScript_LovesickEnd

BattleScript_GooeyActivates::
	waitstate
	call BattleScript_AbilityPopUp
	swapattackerwithtarget  @ for defiant, mirror armor
	seteffectsecondary
	return

BattleScript_GooeyActivatesSpeedandDisable::
	waitstate
	call BattleScript_AbilityPopUp
	swapattackerwithtarget  @ for defiant, mirror armor
	seteffectsecondary
	swapattackerwithtarget
	printstring STRINGID_GOOEYDISABLED
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotDisabledAttacker
	return

BattleScript_StrongJawActivates::
	waitstate
	call BattleScript_AbilityPopUp
	seteffectsecondary
	return

BattleScript_AbilityStatusEffect::
	waitstate
	call BattleScript_AbilityPopUp
	seteffectsecondary
	return

BattleScript_ItemSecondaryEffect::
	waitstate
	seteffectsecondary
	return

BattleScript_AbilitySetGlaiveRush::
	waitstate
	setglaiverush2
	return

BattleScript_AbilitySetPurpleHaze::
	call BattleScript_AbilityPopUp
	setpurplehaze BS_ATTACKER
	printstring STRINGID_PURPLEHAZE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilitySetMagmaArmored::
	call BattleScript_AbilityPopUp
	setmagmaarmored BS_TARGET
	printstring STRINGID_MAGMAARMORED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_TransfusionAbilityCopy::
	waitstate
	trycopyability BattleScript_TransfusionAbilityCopyRet
	setbyte sFIXED_ABILITY_POPUP, TRUE
	showabilitypopup BS_ATTACKER
	pause 60
	sethword sABILITY_OVERWRITE, 0
	updateabilitypopup BS_ATTACKER
	pause 20
	destroyabilitypopup
	pause 40
	printstring STRINGID_PKMNCOPIEDFOE
	waitmessage B_WAIT_TIME_LONG
BattleScript_TransfusionAbilityCopyRet::
	return

BattleScript_ItemBloomingEffect::
	printstring STRINGID_PKMNSITEMCAUSEBLOOMING
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ItemTauntEffect::
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_ItemTauntEffectRet
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_ItemTauntEffectRet
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_ItemTauntEffectRet
	jumpifsafeguard BattleScript_ItemTauntEffectRet
	settaunt BattleScript_ItemTauntEffectRet
	printstring STRINGID_PKMNFELLFORTAUNT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTauntAttacker
BattleScript_ItemTauntEffectRet::
	return

BattleScript_ItemHealBlockEffect::
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_ItemHealBlockEffectRet
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_ItemHealBlockEffectRet
	jumpifsafeguard BattleScript_ItemHealBlockEffectRet
	sethealblock BattleScript_ItemHealBlockEffectRet
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotHealBlockAttacker
BattleScript_ItemHealBlockEffectRet::
	return

BattleScript_BattleBondActivatesOnMoveEndAttacker::
	pause 5
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_ATTACKERBECAMEFULLYCHARGED
	handleformchange BS_ATTACKER, 0
	handleformchange BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_FORM_CHANGE
	waitanimation
	handleformchange BS_ATTACKER, 2
	printstring STRINGID_ATTACKERBECAMEASHSPECIES
	return

BattleScript_DancerActivates::
	call BattleScript_AbilityPopUp
	waitmessage B_WAIT_TIME_SHORT
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	orword gHitMarker, HITMARKER_ALLOW_NO_PP
	jumptocalledmove TRUE

BattleScript_StormBrewActivates::
	call BattleScript_AbilityPopUp
	waitmessage B_WAIT_TIME_SHORT
	printstring STRINGID_GAINEDASTACKOFSTORMBREW
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SynchronizeActivates::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	call BattleScript_AbilityPopUpTarget
	copybyte gEffectBattler, gBattlerTarget
	swapattackerwithtarget
	setbyte gBattlerTarget, 0
BattleScript_SynchronizeLoop:
	jumpiffainted BS_TARGET, TRUE, BattleScript_SynchronizeLoopIncrement
	jumpiftargetally BattleScript_SynchronizeLoopIncrement
	seteffectprimary
BattleScript_SynchronizeLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_SynchronizeLoop
	swapattackerwithtarget
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_NoItemSteal::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNSXMADEYINEFFECTIVE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AbilityCuredStatus::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSXCUREDITSYPROBLEM
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	return

BattleScript_BattlerShookOffTaunt::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSHOOKOFFTHETAUNT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BattlerGotOverItsInfatuation::
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNGOTOVERITSINFATUATION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_IgnoresWhileAsleep::
	printstring STRINGID_PKMNIGNORESASLEEP
	waitmessage B_WAIT_TIME_LONG
	moveendto MOVEEND_NEXT_TARGET
	end

BattleScript_IgnoresAndUsesRandomMove::
	printstring STRINGID_PKMNIGNOREDORDERS
	waitmessage B_WAIT_TIME_LONG
	setbyte sMOVE_EFFECT, 0
	jumptocalledmove FALSE

BattleScript_MoveUsedLoafingAround::
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_LOAFING, BattleScript_MoveUsedLoafingAroundMsg
	@ Skip ahead if not the Battle Palace message
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_INCAPABLE_OF_POWER, BattleScript_MoveUsedLoafingAroundMsg
	setbyte gBattleCommunication, 0
	palacetryescapestatus BS_ATTACKER
	setbyte cMULTISTRING_CHOOSER, B_MSG_INCAPABLE_OF_POWER
BattleScript_MoveUsedLoafingAroundMsg::
	printfromtable gInobedientStringIds
	waitmessage B_WAIT_TIME_LONG
	moveendto MOVEEND_NEXT_TARGET
	end
BattleScript_TruantLoafingAround::
	call BattleScript_AbilityPopUp
	goto BattleScript_MoveUsedLoafingAroundMsg

BattleScript_IgnoresAndFallsAsleep::
	printstring STRINGID_PKMNBEGANTONAP
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_SLEEP | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	moveendto MOVEEND_NEXT_TARGET
	end

BattleScript_IgnoresAndHitsItself::
	printstring STRINGID_PKMNWONTOBEY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_DoSelfConfusionDmg

BattleScript_SubstituteFade::
	playanimation BS_TARGET, B_ANIM_SUBSTITUTE_FADE
	printstring STRINGID_PKMNSUBSTITUTEFADED
	return

BattleScript_BerryCurePrlzEnd2::
	call BattleScript_BerryCureParRet
	end2

BattleScript_BerryCureParRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMCUREDPARALYSIS
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCurePsnEnd2::
	call BattleScript_BerryCurePsnRet
	end2

BattleScript_BerryCurePsnRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMCUREDPOISON
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureBrnEnd2::
	call BattleScript_BerryCureBrnRet
	end2

BattleScript_BerryCureBrnRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMHEALEDBURN
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureFrzEnd2::
	call BattleScript_BerryCureFrzRet
	end2

BattleScript_BerryCureFrzRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMDEFROSTEDIT
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureFsbEnd2::
	call BattleScript_BerryCureFrzRet
	end2

BattleScript_BerryCureFsbRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMHEALEDFROSTBITE
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureSlpEnd2::
	call BattleScript_BerryCureSlpRet
	end2

BattleScript_BerryCureSlpRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMWOKEIT
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCurePanicEnd2::
	call BattleScript_BerryCurePanicRet
	end2

BattleScript_BerryCurePanicRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMCALMEDIT
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureBloomEnd2::
	call BattleScript_BerryCureBloomRet
	end2

BattleScript_BerryCureBloomRet::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_WatmelBerryActivate_Ripen
	goto BattleScript_WatmelBerryActivate_Anim
BattleScript_WatmelBerryActivate_Ripen:
	call BattleScript_AbilityPopUp
BattleScript_WatmelBerryActivate_Anim:
	jumpifabsent BS_SCRIPTING, BattleScript_WatmelBerryActivate_Dmg   @ dont play the animation for a fainted target
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
BattleScript_WatmelBerryActivate_Dmg:
	call BattleScript_WatmelHurtAttacker
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_WatmelHurtAttacker:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	printstring STRINGID_WATMELBERRYEXPLODED
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_SCRIPTING
	return

BattleScript_GemActivates::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setlastuseditem BS_ATTACKER
	printstring STRINGID_GEMACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_BerryReduceDmg::
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	setlastuseditem BS_TARGET
	printstring STRINGID_TARGETATEITEM
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
	return

BattleScript_PrintBerryReduceString::
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_BERRYDMGREDUCES
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BerryCureConfusionEnd2::
	call BattleScript_BerryCureConfusionRet
	end2

BattleScript_BerryCureConfusionRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMSNAPPEDOUT
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureChosenStatusEnd2::
	call BattleScript_BerryCureChosenStatusRet
	end2

BattleScript_BerryCureChosenStatusRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printfromtable gBerryEffectStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_FavorScarfCuredStatusEnd2::
	call BattleScript_FavorScarfCuredStatusRet
	end2

BattleScript_FavorScarfCuredStatusRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printfromtable gBerryEffectStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	return

BattleScript_MentalHerbCureRet::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	printfromtable gMentalHerbCureStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	copybyte gBattlerAttacker, sSAVED_BATTLER   @ restore the original attacker just to be safe
	return

BattleScript_MentalHerbCureEnd2::
	call BattleScript_MentalHerbCureRet
	end2

BattleScript_WhiteHerbEnd2::
	call BattleScript_WhiteHerbRet
	end2

BattleScript_WhiteHerbRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDSTATUS
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_AnnounceTeruCharm::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_TERUCHARMACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	end2

BattleScript_ItemHealHP_RemoveItemRet::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_ItemHealHP_RemoveItemRet_AbilityPopUp
	goto BattleScript_ItemHealHP_RemoveItemRet_Anim
BattleScript_ItemHealHP_RemoveItemRet_AbilityPopUp:
	call BattleScript_AbilityPopUp
BattleScript_ItemHealHP_RemoveItemRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_ItemHealHP_RemoveItemEnd2::
	jumpifability BS_ATTACKER, ABILITY_RIPEN, BattleScript_ItemHealHP_RemoveItemEnd2_AbilityPopUp
	goto BattleScript_ItemHealHP_RemoveItemEnd2_Anim
BattleScript_ItemHealHP_RemoveItemEnd2_AbilityPopUp:
	call BattleScript_AbilityPopUp
BattleScript_ItemHealHP_RemoveItemEnd2_Anim:
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	removeitem BS_ATTACKER
	end2

BattleScript_BerryPPHealRet::
	jumpifability BS_ATTACKER, ABILITY_RIPEN, BattleScript_BerryPPHeal_AbilityPopup
	goto BattleScript_BerryPPHeal_Anim
BattleScript_BerryPPHeal_AbilityPopup:
	call BattleScript_AbilityPopUp
BattleScript_BerryPPHeal_Anim:
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDPP
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_BerryPPHealEnd2::
	call BattleScript_BerryPPHealRet
	end2

BattleScript_ItemHealHP_End2::
	call BattleScript_ItemHealHP_Ret
	end2

BattleScript_AbilityHealHP_End2::
	call BattleScript_AbilityHealHP_Ret
	end2

BattleScript_NormaliseBuffs::
	call BattleScript_AbilityPopUp
	tryresetstatstages BS_ATTACKER
	printstring STRINGID_USERSTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_A_Thing_Happened::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_ATHINGHAPPENED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_A_Thing_HappenedFR::
	playanimation BS_ATTACKER, B_ANIM_A_THING
	printstring STRINGID_ATHINGHAPPENEDFR
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_CrypticPlateEntryEffect::
	setgravity BattleScript_CrypticPlateGravityFailed
	jumpifsideaffecting BS_ATTACKER, SIDE_STATUS_SAFEGUARD, BattleScript_CrypticPlateFailed
	setsafeguard
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_GRAVITYINTENSIFIED
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_PKMNCOVEREDBYVEIL
	waitmessage B_WAIT_TIME_LONG
BattleScript_CrypticPlateFailed::
	end3
BattleScript_CrypticPlateGravityFailed::
	jumpifsideaffecting BS_ATTACKER, SIDE_STATUS_SAFEGUARD, BattleScript_CrypticPlateFailed
	setsafeguard
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_PKMNCOVEREDBYVEIL
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_GemstoneEvasion::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_PKMNGEMSTONEMAXEDEVASION
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_GemstoneEvasionDrop::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_PKMNGEMSTONELOSTEVASION
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_AirBaloonMsgIn::
	printstring STRINGID_AIRBALLOONFLOAT
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_AirBaloonMsgPop::
	printstring STRINGID_AIRBALLOONPOP
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
	return

BattleScript_ItemHurtRet::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_IGNORE_DISGUISE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_HURTBYITEM
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	return

BattleScript_ItemHurtEnd2::
	playanimation BS_ATTACKER, B_ANIM_MON_HIT
	waitanimation
	call BattleScript_ItemHurtRet
	end2

BattleScript_StickyBarb::
	playanimation BS_ATTACKER, B_ANIM_MON_HIT
	waitanimation
	printstring STRINGID_STICKYBARBSPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_IGNORE_DISGUISE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_HURTBYITEM
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	end2

BattleScript_StickyBarbJustSpikes::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_STICKYBARBSPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_HeartGiftSurpriseCount::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_STACKOFSURPRISE
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_HeartGiftSurpriseFulfilled::
	playanimation BS_ATTACKER, B_ANIM_MON_HIT
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_IGNORE_DISGUISE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_COULDNTHANDLETHESURPRISE
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	end2

BattleScript_ItemHealHP_Ret::
	printstring STRINGID_PKMNSITEMRESTOREDHPALITTLE
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	return

BattleScript_AbilityHealHP_Ret::
	call BattleScript_AbilityPopUpTarget
	printstring STRINGID_PKMNRESTOREDHPUSING
	waitmessage B_WAIT_TIME_SHORTEST
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	return

BattleScript_SelectingNotAllowedMoveChoiceItem::
	printselectionstring STRINGID_ITEMALLOWSONLYYMOVE
	endselectionscript

BattleScript_SelectingNotAllowedMoveChoiceItemInPalace::
	printstring STRINGID_ITEMALLOWSONLYYMOVE
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedMoveGorillaTactics::
	printselectionstring STRINGID_ABILITYALLOWSONLYMOVE
	endselectionscript

BattleScript_SelectingNotAllowedMoveGorillaTacticsInPalace::
	printstring STRINGID_ABILITYALLOWSONLYMOVE
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedMoveAssaultVest::
	printselectionstring STRINGID_ASSAULTVESTDOESNTALLOW
	endselectionscript

BattleScript_SelectingNotAllowedMoveAssaultVestInPalace::
	printstring STRINGID_ASSAULTVESTDOESNTALLOW
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_SelectingNotAllowedMovePhantom::
	printselectionstring STRINGID_PHANTOMDOESNTALLOW
	endselectionscript

BattleScript_SelectingNotAllowedMoveStronghold::
	printselectionstring STRINGID_STRONGHOLDDOESNTALLOW
	endselectionscript

BattleScript_SelectingNotAllowedPlaceholder::
	printselectionstring STRINGID_NOTDONEYET
	endselectionscript

BattleScript_SelectingNotAllowedPlaceholderInPalace::
	printstring STRINGID_NOTDONEYET
	goto BattleScript_SelectingUnusableMoveInPalace

BattleScript_HangedOnMsg::
	playanimation BS_TARGET, B_ANIM_HANGED_ON
	printstring STRINGID_PKMNHUNGONWITHX
	waitmessage B_WAIT_TIME_LONG
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_FOCUS_SASH, BattleScript_HangedOnMsgRet
	removeitem BS_TARGET
BattleScript_HangedOnMsgRet:
	return

BattleScript_BerryConfuseHealEnd2::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_BerryConfuseHealEnd2_AbilityPopup
	goto BattleScript_BerryConfuseHealEnd2_Anim
BattleScript_BerryConfuseHealEnd2_AbilityPopup:
	call BattleScript_AbilityPopUp
BattleScript_BerryConfuseHealEnd2_Anim:
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	printstring STRINGID_FORXCOMMAYZ
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_CONFUSION | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	removeitem BS_SCRIPTING
	end2

BattleScript_BerryConfuseHealRet::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_BerryConfuseHealRet_AbilityPopup
	goto BattleScript_BerryConfuseHealRet_Anim
BattleScript_BerryConfuseHealRet_AbilityPopup:
	call BattleScript_AbilityPopUp
BattleScript_BerryConfuseHealRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	printstring STRINGID_FORXCOMMAYZ
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_CONFUSION | MOVE_EFFECT_CERTAIN
	seteffectprimary
	removeitem BS_TARGET
	return

BattleScript_BerryStatRaiseEnd2::
	jumpifability BS_ATTACKER, ABILITY_RIPEN, BattleScript_BerryStatRaiseEnd2_AbilityPopup
	goto BattleScript_BerryStatRaiseEnd2_Anim
BattleScript_BerryStatRaiseEnd2_AbilityPopup:
	call BattleScript_AbilityPopUp
BattleScript_BerryStatRaiseEnd2_Anim:
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_BerryStatRaiseEnd2_End
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_ITEM
	call BattleScript_StatUp
	removeitem BS_ATTACKER
BattleScript_BerryStatRaiseEnd2_End::
	end2

BattleScript_BerryStatRaiseRet::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_BerryStatRaiseRet_AbilityPopup
	goto BattleScript_BerryStatRaiseRet_Anim
BattleScript_BerryStatRaiseRet_AbilityPopup:
	call BattleScript_AbilityPopUp
BattleScript_BerryStatRaiseRet_Anim:
	statbuffchange STAT_CHANGE_ALLOW_PTR | MOVE_EFFECT_CERTAIN, BattleScript_BerryStatRaiseRet_End
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_ITEM
	call BattleScript_StatUp
	removeitem BS_SCRIPTING
BattleScript_BerryStatRaiseRet_End:
	return

BattleScript_BerryFocusEnergyRet::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_PKMNUSEDXTOGETPUMPED
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_BerryFocusEnergyEnd2::
	call BattleScript_BerryFocusEnergyRet
	end2

BattleScript_ActionSelectionItemsCantBeUsed::
	printselectionstring STRINGID_ITEMSCANTBEUSEDNOW
	endselectionscript

BattleScript_FlushMessageBox::
	printstring STRINGID_EMPTYSTRING3
	return

BattleScript_PalacePrintFlavorText::
	setbyte gBattleCommunication + 1, 0
BattleScript_PalaceTryBattlerFlavorText::
	palaceflavortext BS_ATTACKER @ BS_ATTACKER here overwritten by gBattleCommunication + 1
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, TRUE, BattleScript_PalaceEndFlavorText
	printfromtable gBattlePalaceFlavorTextTable
	waitmessage B_WAIT_TIME_LONG
BattleScript_PalaceEndFlavorText::
	addbyte gBattleCommunication + 1, 1
	jumpifbytenotequal gBattleCommunication + 1, gBattlersCount, BattleScript_PalaceTryBattlerFlavorText
	setbyte gBattleCommunication, 0
	setbyte gBattleCommunication + 1, 0
	end2

BattleScript_ArenaTurnBeginning::
	waitcry BS_ATTACKER
	volumedown
	playse SE_ARENA_TIMEUP1
	pause 8
	playse SE_ARENA_TIMEUP1
	arenadrawreftextbox
	arenajudgmentstring B_MSG_REF_COMMENCE_BATTLE
	arenawaitmessage B_MSG_REF_COMMENCE_BATTLE
	pause B_WAIT_TIME_LONG
	arenaerasereftextbox
	volumeup
	end2

@ Unused
BattleScript_ArenaNothingDecided::
	playse SE_DING_DONG
	arenadrawreftextbox
	arenajudgmentstring B_MSG_REF_NOTHING_IS_DECIDED
	arenawaitmessage B_MSG_REF_NOTHING_IS_DECIDED
	pause B_WAIT_TIME_LONG
	arenaerasereftextbox
	end2

BattleScript_ArenaDoJudgment::
	makevisible BS_PLAYER1
	waitstate
	makevisible BS_OPPONENT1
	waitstate
	volumedown
	playse SE_ARENA_TIMEUP1
	pause 8
	playse SE_ARENA_TIMEUP1
	pause B_WAIT_TIME_LONG
	arenadrawreftextbox
	arenajudgmentstring B_MSG_REF_THATS_IT
	arenawaitmessage B_MSG_REF_THATS_IT
	pause B_WAIT_TIME_LONG
	setbyte gBattleCommunication, 0  @ Reset state for arenajudgmentwindow
	arenajudgmentwindow
	pause B_WAIT_TIME_LONG
	arenajudgmentwindow
	arenajudgmentstring B_MSG_REF_JUDGE_MIND
	arenawaitmessage B_MSG_REF_JUDGE_MIND
	arenajudgmentwindow
	arenajudgmentstring B_MSG_REF_JUDGE_SKILL
	arenawaitmessage B_MSG_REF_JUDGE_SKILL
	arenajudgmentwindow
	arenajudgmentstring B_MSG_REF_JUDGE_BODY
	arenawaitmessage B_MSG_REF_JUDGE_BODY
	arenajudgmentwindow
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, ARENA_RESULT_PLAYER_LOST, BattleScript_ArenaJudgmentPlayerLoses
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, ARENA_RESULT_TIE, BattleScript_ArenaJudgmentDraw
@ ARENA_RESULT_PLAYER_WON
	arenajudgmentstring B_MSG_REF_PLAYER_WON
	arenawaitmessage B_MSG_REF_PLAYER_WON
	arenajudgmentwindow
	arenaerasereftextbox
	printstring STRINGID_DEFEATEDOPPONENTBYREFEREE
	waitmessage B_WAIT_TIME_LONG
	playfaintcry BS_OPPONENT1
	waitcry BS_ATTACKER
	dofaintanimation BS_OPPONENT1
	cleareffectsonfaint BS_OPPONENT1
	arenaopponentmonlost
	end2

BattleScript_ArenaJudgmentPlayerLoses:
	arenajudgmentstring B_MSG_REF_OPPONENT_WON
	arenawaitmessage B_MSG_REF_OPPONENT_WON
	arenajudgmentwindow
	arenaerasereftextbox
	printstring STRINGID_LOSTTOOPPONENTBYREFEREE
	waitmessage B_WAIT_TIME_LONG
	playfaintcry BS_PLAYER1
	waitcry BS_ATTACKER
	dofaintanimation BS_PLAYER1
	cleareffectsonfaint BS_PLAYER1
	arenaplayermonlost
	end2

BattleScript_ArenaJudgmentDraw:
	arenajudgmentstring B_MSG_REF_DRAW
	arenawaitmessage B_MSG_REF_DRAW
	arenajudgmentwindow
	arenaerasereftextbox
	printstring STRINGID_TIEDOPPONENTBYREFEREE
	waitmessage B_WAIT_TIME_LONG
	playfaintcry BS_PLAYER1
	waitcry BS_ATTACKER
	dofaintanimation BS_PLAYER1
	cleareffectsonfaint BS_PLAYER1
	playfaintcry BS_OPPONENT1
	waitcry BS_ATTACKER
	dofaintanimation BS_OPPONENT1
	cleareffectsonfaint BS_OPPONENT1
	arenabothmonlost
	end2

BattleScript_AskIfWantsToForfeitMatch::
	printselectionstring STRINGID_QUESTIONFORFEITMATCH
	forfeityesnobox BS_ATTACKER
	endselectionscript

BattleScript_PrintPlayerForfeited::
	printstring STRINGID_FORFEITEDMATCH
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_PrintPlayerForfeitedLinkBattle::
	printstring STRINGID_FORFEITEDMATCH
	waitmessage B_WAIT_TIME_LONG
	endlinkbattle
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_TotemFlaredToLife::
	playanimation BS_ATTACKER, B_ANIM_TOTEM_FLARE, NULL
	printstring STRINGID_AURAFLAREDTOLIFE
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ApplyTotemVarBoost
	end2

@ remove the mirror herb, do totem loop
BattleScript_MirrorHerbCopyStatChangeEnd2::
	call BattleScript_MirrorHerbCopyStatChange
	end2

BattleScript_MirrorHerbCopyStatChange::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, NULL
	printstring STRINGID_MIRRORHERBCOPIED
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_MirrorHerbStartCopyStats:
	copyfoesstatincrease BS_SCRIPTING, BattleScript_MirrorHerbStartReturn
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_MirrorHerbStartReturn
	goto BattleScript_MirrorHerbStartCopyStats
BattleScript_MirrorHerbStartReturn:
	return

BattleScript_TotemVar::
	call BattleScript_TotemVar_Ret
	end2

BattleScript_TotemVar_Ret::
	gettotemboost BattleScript_ApplyTotemVarBoost
BattleScript_TotemVarEnd:
	return
BattleScript_ApplyTotemVarBoost:
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_TotemVarEnd
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_TotemVar_Ret  @loop until stats bitfield is empty


BattleScript_AnnounceCloudNine::
	call BattleScript_AbilityPopUp
	printstring STRINGID_CLOUDNINEACTIVATES
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_ActivateWeatherAbilities
	end3

BattleScript_AnnounceAirLock::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_AIRLOCKACTIVATES
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_QuickClawActivation::
	pause B_WAIT_TIME_SHORT
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_CANACTFASTERTHANKSTO
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_QuickDrawActivation::
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_CANACTFASTERTHANKSTO
	waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_CustapBerryActivation::
	pause B_WAIT_TIME_SHORT
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
	printstring STRINGID_CANACTFASTERTHANKSTO
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	end2

BattleScript_MicleBerryActivateEnd2::
	jumpifability BS_ATTACKER, ABILITY_RIPEN, BattleScript_MicleBerryActivateEnd2_Ripen
	goto BattleScript_MicleBerryActivateEnd2_Anim
BattleScript_MicleBerryActivateEnd2_Ripen:
	call BattleScript_AbilityPopUp
BattleScript_MicleBerryActivateEnd2_Anim:
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_MICLEBERRYACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	end2

BattleScript_MicleBerryActivateRet::
	jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_MicleBerryActivateRet_Ripen
	goto BattleScript_MicleBerryActivateRet_Anim
BattleScript_MicleBerryActivateRet_Ripen:
	call BattleScript_AbilityPopUp
BattleScript_MicleBerryActivateRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_MICLEBERRYACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_JabocaRowapBerryActivates::
	jumpifability BS_TARGET, ABILITY_RIPEN, BattleScript_JabocaRowapBerryActivate_Ripen
	goto BattleScript_JabocaRowapBerryActivate_Anim
BattleScript_JabocaRowapBerryActivate_Ripen:
	call BattleScript_AbilityPopUp
BattleScript_JabocaRowapBerryActivate_Anim:
	jumpifabsent BS_TARGET, BattleScript_JabocaRowapBerryActivate_Dmg   @ dont play the animation for a fainted target
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
BattleScript_JabocaRowapBerryActivate_Dmg:
	call BattleScript_HurtAttacker
	removeitem BS_TARGET
	return

BattleScript_CornnBerryActivatesRet::
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	applysaltcure BS_ATTACKER
	printstring STRINGID_TARGETISBEINGSALTCORNED
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
	return

BattleScript_WepearBerryActivatesRet::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	printstring STRINGID_WEPEARHEALBLOCKPKMN
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_SpelonBerryActivatesRet::
	trysetspikes BS_ATTACKER, BattleScript_SpelonBerryEnd
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	printstring STRINGID_SPELONSPIKESSCATTERED
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_SpelonBerryEnd::
	return

BattleScript_BelueBerryActivatesRet::
	cantarshotwork BS_ATTACKER, BattleScript_BelueBerryEnd
	trytarshot BS_ATTACKER, BattleScript_BelueBerryEnd
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	printstring STRINGID_ATTACKERBECAMEWEAKERTOFIRE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_BelueBerryEnd::
	return

BattleScript_PinapBerryActivatesRet::
	jumpifability BS_TARGET, ABILITY_RIPEN, BattleScript_PinapBerryActivate_Ripen
	goto BattleScript_PinapBerryActivate_Anim
BattleScript_PinapBerryActivate_Ripen:
	call BattleScript_AbilityPopUp
BattleScript_PinapBerryActivate_Anim:
	jumpifabsent BS_TARGET, BattleScript_PinapBerryActivate_Dmg   @ dont play the animation for a fainted target
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT
	waitanimation
BattleScript_PinapBerryActivate_Dmg:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_TARGETHURTBYITEM
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	removeitem BS_TARGET
BattleScript_PinapBerryEnd::
	return

BattleScript_RizzBerryActivatesRet::
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	status2animation BS_ATTACKER, STATUS2_INFATUATION
	printstring STRINGID_PKMNSXINFATUATEDYITEMEDITION
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotInfatuateTarget
	removeitem BS_TARGET
BattleScript_RizzBerryEnd::
	return

BattleScript_RabutaBerryActivatesRet::
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	status2animation BS_ATTACKER, STATUS2_CONFUSION
	printstring STRINGID_ATKPKMNCONFUSED
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_RabutaBerryEnd::
	return

BattleScript_BlukBerryActivatesRet::
	blukberryppreduce BattleScript_BlukBerryReturn
	playanimation BS_TARGET, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	printstring STRINGID_ATKPKMNREDUCEDPP
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_BlukBerryReturn::
	return

BattleScript_NanabBerryActivatesRet::
	playanimation BS_ATTACKER, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	printstring STRINGID_NANABMINIMIZE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

@ z moves / effects
BattleScript_ZMoveActivateDamaging::
	printstring STRINGID_EMPTYSTRING3
	trytrainerslidezmovemsg BS_ATTACKER
	printstring STRINGID_ZPOWERSURROUNDS
	playanimation BS_ATTACKER, B_ANIM_ZMOVE_ACTIVATE, NULL
	printstring STRINGID_ZMOVEUNLEASHED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ZMoveActivateStatus::
	printstring STRINGID_EMPTYSTRING3
	trytrainerslidezmovemsg BS_ATTACKER
	savetarget
	printstring STRINGID_ZPOWERSURROUNDS
	playanimation BS_ATTACKER, B_ANIM_ZMOVE_ACTIVATE, NULL
	setzeffect
	restoretarget
	copybyte sSTATCHANGER, sSAVED_STAT_CHANGER
	return

BattleScript_ZEffectPrintString::
	printfromtable gZEffectStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_RecoverHPZMove::
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	printfromtable gZEffectStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_StatUpZMove::
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_StatUpZMoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_StatUpZMoveEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_ZMOVESTATUP
	waitmessage B_WAIT_TIME_LONG
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StatUpZMoveEnd:
	return

BattleScript_HealReplacementZMove::
	playanimation BS_SCRIPTING B_ANIM_WISH_HEAL 0x0
	printfromtable gZEffectStringIds
	waitmessage B_WAIT_TIME_LONG
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	return

BattleScript_EffectExtremeEvoboost::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_ExtremeEvoboostAnim
	goto BattleScript_ButItFailed
BattleScript_ExtremeEvoboostAnim:
	attackanimation
	waitanimation
BattleScript_ExtremeEvoboostAtk::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0x0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostDef::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostSpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostSpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostSpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostSpAtk::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostSpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostSpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_ALLOW_PTR, BattleScript_ExtremeEvoboostEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ExtremeEvoboostEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectHitSetRemoveTerrain:
    call BattleScript_EffectHit_Ret
	jumpifmovehadnoeffect BattleScript_TryFaint
	seteffectwithchance
	setremoveterrain BattleScript_TryFaint
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printfromtable gDemolisherStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryFaint:
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_RemoveTerrain:
	jumpifterrainaffected BS_TARGET, STATUS_FIELD_TERRAIN_ANY, BattleScript_RemoveTerrain_Cont
	goto BattleScript_ButItFailed
BattleScript_RemoveTerrain_Cont:
	critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	removeterrain
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_Pickpocket::
	call BattleScript_AbilityPopUp
	jumpifability BS_ATTACKER, ABILITY_STICKY_HOLD, BattleScript_PickpocketPrevented
	swapattackerwithtarget
	call BattleScript_ItemSteal
	swapattackerwithtarget
	activateitemeffects BS_TARGET
	return

BattleScript_PickpocketPrevented:
	pause B_WAIT_TIME_SHORT
	copybyte gBattlerAbility, gBattlerAttacker
	call BattleScript_AbilityPopUp
	printstring STRINGID_ITEMCANNOTBEREMOVED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_RedCardActivates::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_REDCARDACTIVATE
	waitmessage B_WAIT_TIME_LONG
	swapattackerwithtarget
	jumpifstatus3 BS_EFFECT_BATTLER, STATUS3_ROOTED, BattleScript_RedCardIngrain
	jumpifability BS_EFFECT_BATTLER, ABILITY_SUCTION_CUPS, BattleScript_RedCardSuctionCups
	removeitem BS_SCRIPTING
	setbyte sSWITCH_CASE, B_SWITCH_RED_CARD
	forcerandomswitch BattleScript_RedCardEnd
	@ changes the current battle script. the rest happens in BattleScript_RoarSuccessSwitch_Ret, if switch is successful
BattleScript_RedCardEnd:
	return
BattleScript_RedCardIngrain:
	printstring STRINGID_PKMNANCHOREDITSELF
BattleScript_RedCardIngrainContinue:
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	restoretarget
	return
BattleScript_RedCardSuctionCups:
    printstring STRINGID_PKMNANCHORSITSELFWITH
    goto BattleScript_RedCardIngrainContinue

BattleScript_EjectButtonActivates::
	makevisible BS_ATTACKER
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_EJECTBUTTONACTIVATE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	makeinvisible BS_SCRIPTING
	openpartyscreen BS_SCRIPTING, BattleScript_EjectButtonEnd
	copybyte sSAVED_BATTLER, sBATTLER
	switchoutabilities BS_SCRIPTING
	copybyte sBATTLER, sSAVED_BATTLER
	waitstate
	switchhandleorder BS_SCRIPTING 0x2
	returntoball BS_SCRIPTING
	getswitchedmondata BS_SCRIPTING
	switchindataupdate BS_SCRIPTING
	hpthresholds BS_SCRIPTING
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring 0x3
	switchinanim BS_SCRIPTING 0x1
	waitstate
	switchineffects BS_SCRIPTING
BattleScript_EjectButtonEnd:
	return

BattleScript_EjectPackActivate_Ret::
	goto BattleScript_EjectButtonActivates

BattleScript_EjectPackActivate_End2::
	call BattleScript_EjectPackActivate_Ret
	end2

BattleScript_EjectPackActivates::
	jumpifcantswitch BS_SCRIPTING, BattleScript_EjectButtonEnd
	goto BattleScript_EjectPackActivate_Ret

BattleScript_EjectPackMissesTiming::
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT
	printstring STRINGID_EJECTBUTTONACTIVATE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_DarkTypePreventsPrankster::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	goto BattleScript_MoveEnd

BattleScript_GoodAsGoldActivates::
	attackstring
	ppreduce
	showabilitypopup BS_TARGET
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_MED
	goto BattleScript_MoveEnd

BattleScript_PastelVeilActivates::
	setbyte gBattleCommunication, 0
	setbyte gBattleCommunication + 1, 0
BattleScript_PastelVeil_TryCurePoison:
	jumpifstatus BS_TARGET, STATUS1_POISON | STATUS1_TOXIC_POISON, BattleScript_PastelVeilCurePoison
	goto BattleScript_PastelVeilLoopIncrement
BattleScript_PastelVeilCurePoison:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication + 1, 0x0, BattleScript_PastelVeilCurePoisonNoPopUp
	call BattleScript_AbilityPopUp
	setbyte gBattleCommunication + 1, 1
BattleScript_PastelVeilCurePoisonNoPopUp: @ Only show Pastel Veil pop up once if it cures two mons
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
BattleScript_PastelVeilLoopIncrement:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_PastelVeilEnd
	addbyte gBattleCommunication, 1
	jumpifnoally BS_TARGET, BattleScript_PastelVeilEnd
	setallytonexttarget BattleScript_PastelVeil_TryCurePoison
	goto BattleScript_PastelVeilEnd
BattleScript_PastelVeilEnd:
	end3

BattleScript_WaterVeilActivates::
	setbyte gBattleCommunication, 0
	setbyte gBattleCommunication + 1, 0
BattleScript_WaterVeil_TryCure:
	jumpifstatus BS_TARGET, STATUS1_BURN | STATUS1_FROSTBITE, BattleScript_WaterVeilCure
	goto BattleScript_WaterVeilLoopIncrement
BattleScript_WaterVeilCure:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication + 1, 0x0, BattleScript_WaterVeilCureNoPopUp
	call BattleScript_AbilityPopUp
	setbyte gBattleCommunication + 1, 1
BattleScript_WaterVeilCureNoPopUp: @ Only show Pastel Veil pop up once if it cures two mons
	printfromtable gSwitchInAbilityStringIds
	waitmessage B_WAIT_TIME_LONG
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
BattleScript_WaterVeilLoopIncrement:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_WaterVeilEnd
	addbyte gBattleCommunication, 1
	jumpifnoally BS_TARGET, BattleScript_WaterVeilEnd
	setallytonexttarget BattleScript_WaterVeil_TryCure
	goto BattleScript_WaterVeilEnd
BattleScript_WaterVeilEnd:
	end3

sByteFour:
.byte MAX_BATTLERS_COUNT

BattleScript_NeutralizingGasExits::
	saveattacker
	savetarget
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NEUTRALIZINGGASOVER
	waitmessage B_WAIT_TIME_LONG
	setbyte gBattlerTarget, 0
BattleScript_NeutralizingGasExitsLoop:
	switchinabilities BS_TARGET
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_NeutralizingGasExitsLoop
	restoreattacker
	restoretarget
	return

BattleScript_MagicianActivates::
	call BattleScript_AbilityPopUp
	call BattleScript_ItemSteal
	return

BattleScript_SymbiosisActivates::
	call BattleScript_AbilityPopUp
	printstring STRINGID_SYMBIOSISITEMPASS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_IceScalesActivatesGain::
	waitstate
	call BattleScript_AbilityPopUp
	printstring STRINGID_ICESCALESGAINS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_IceScalesActivatesLoss::
	waitstate
	call BattleScript_AbilityPopUp
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_ICESCALESLOSS
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER
	return

BattleScript_TargetAbilityStatRaiseRet::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	copybyte gBattlerAbility, gEffectBattler
	copybyte gBattlerAttacker, gBattlerTarget
	call BattleScript_AbilityPopUp
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN, BattleScript_TargetAbilityStatRaiseRet_End
	setgraphicalstatchangevalues
	call BattleScript_StatUp
BattleScript_TargetAbilityStatRaiseRet_End:
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_TargetAbilityStatDropRet::
	copybyte sSAVED_BATTLER, gBattlerAttacker
	copybyte gBattlerAbility, gEffectBattler
	copybyte gBattlerAttacker, gBattlerTarget
	call BattleScript_AbilityPopUp
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN, BattleScript_TargetAbilityStatDropRet_End
	setgraphicalstatchangevalues
	call BattleScript_StatDown
BattleScript_TargetAbilityStatDropRet_End:
	copybyte gBattlerAttacker, sSAVED_BATTLER
	return

BattleScript_PokemonCantUseTheMove::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_BUTPOKEMONCANTUSETHEMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_CouldntFullyProtect::
	printstring STRINGID_COULDNTFULLYPROTECT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BerserkGeneRet::
	savetarget
	copybyte gBattlerTarget, sBATTLER
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_BerserkGeneRet_TryConfuse
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_HELD_ITEM_EFFECT, sB_ANIM_ARG1
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_ITEM
	call BattleScript_StatUp
BattleScript_BerserkGeneRet_TryConfuse:
	jumpifability BS_SCRIPTING, ABILITY_OWN_TEMPO, BattleScript_BerserkGeneRet_OwnTempoPrevents
	jumpifability BS_SCRIPTING, ABILITY_TITANIC, BattleScript_BerserkGeneRet_OwnTempoPrevents
	jumpiftype BS_SCRIPTING, TYPE_PSYCHIC, BattleScript_BerserkGeneRet_End
	jumpifsafeguard BattleScript_BerserkGeneRet_SafeguardProtected
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	goto BattleScript_BerserkGeneRet_End
BattleScript_BerserkGeneRet_SafeguardProtected::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_BerserkGeneRet_End
BattleScript_BerserkGeneRet_OwnTempoPrevents:
	pause B_WAIT_TIME_SHORT
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSCONFUSIONWITH
	waitmessage B_WAIT_TIME_LONG
BattleScript_BerserkGeneRet_End:
	restoretarget
	removeitem BS_SCRIPTING
	end3

BattleScript_EffectSnow::
	attackcanceler
	attackstring
	ppreduce
	call BattleScript_CheckPrimalWeather
	setsnow
	goto BattleScript_MoveWeatherChange

BattleScript_IlluminateActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_IlluminateLoop:
	jumpifabsent BS_TARGET, BattleScript_IlluminateLoopIncrement
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_IlluminateLoopIncrement
BattleScript_IlluminateEffect:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_IlluminateLoopIncrement
	setgraphicalstatchangevalues
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_IlluminateContrary
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_IlluminateWontIncrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNINCREASEACCWITH
BattleScript_IlluminateEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
BattleScript_IlluminateLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_IlluminateLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_IlluminateContrary:
	call BattleScript_AbilityPopUpTarget
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_IlluminateContrary_WontDecrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	goto BattleScript_IlluminateEffect_WaitString
BattleScript_IlluminateContrary_WontDecrease:
	printstring STRINGID_TARGETSTATWONTGOLOWER
	goto BattleScript_IlluminateEffect_WaitString

BattleScript_IlluminateWontIncrease:
	printstring STRINGID_STATSWONTINCREASE
	goto BattleScript_IlluminateEffect_WaitString

BattleScript_HardboiledActivates::
	call BattleScript_AbilityPopUp
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HardboiledActivatesSpdef
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HardboiledDefAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_EMPTY, BattleScript_HardboiledActivatesSpdef
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HardboiledActivatesSpdef
BattleScript_HardboiledDefAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETABILITYSTATRAISESHARPLY
	waitmessage B_WAIT_TIME_LONG
BattleScript_HardboiledActivatesSpdef:
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HardboiledActivatesEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HardboiledSpdefAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_EMPTY, BattleScript_HardboiledActivatesEnd
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HardboiledActivatesEnd
BattleScript_HardboiledSpdefAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETABILITYSTATRAISESHARPLY
	waitmessage B_WAIT_TIME_LONG
BattleScript_HardboiledActivatesEnd:
	return

BattleScript_HardboiledActivatesExtra::
	call BattleScript_AbilityPopUp
	setstatchanger STAT_DEF, 3, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HardboiledActivatesSpdefExtra
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HardboiledDefAnimExtra
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_EMPTY, BattleScript_HardboiledActivatesSpdefExtra
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HardboiledActivatesSpdefExtra
BattleScript_HardboiledDefAnimExtra:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETABILITYSTATRAISEDRASTICALLY
	waitmessage B_WAIT_TIME_LONG
BattleScript_HardboiledActivatesSpdefExtra:
	setstatchanger STAT_SPDEF, 3, FALSE
	statbuffchange STAT_CHANGE_ALLOW_PTR, BattleScript_HardboiledActivatesEndExtra
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_HardboiledSpdefAnimExtra
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_EMPTY, BattleScript_HardboiledActivatesEndExtra
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HardboiledActivatesEndExtra
BattleScript_HardboiledSpdefAnimExtra:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETABILITYSTATRAISEDRASTICALLY
	waitmessage B_WAIT_TIME_LONG
BattleScript_HardboiledActivatesEndExtra:
	return

BattleScript_DisturbActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_DisturbLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_DisturbLoopIncrement
	jumpiftargetally BattleScript_DisturbLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_DisturbLoopIncrement
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_DisturbLoopIncrement
	jumpiftype BS_TARGET, TYPE_DRAGON, BattleScript_DisturbPreventedDragon
	jumpifability BS_TARGET, ABILITY_SCRAPPY, BattleScript_DisturbPrevented // SCRAPPY
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_DisturbPrevented
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_DisturbPrevented
	jumpifability BS_TARGET, ABILITY_GUARD_DOG, BattleScript_DisturbInReverse
BattleScript_DisturbEffect:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_DisturbLoopIncrement
	setgraphicalstatchangevalues
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_DisturbContrary
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_DisturbWontDecrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNCUTSSPATTACKWITH
BattleScript_DisturbEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_TryStatDropHoldEffects
	restoreattacker
	restoretarget
BattleScript_DisturbLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_DisturbLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_DisturbPreventedDragon:
	copybyte sBATTLER, gBattlerTarget
	printstring STRINGID_PKMNPREVENTSSTATLOSSDRAGON
	goto BattleScript_DisturbEffect_WaitString

BattleScript_DisturbPrevented:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	goto BattleScript_DisturbEffect_WaitString

BattleScript_DisturbWontDecrease:
	printstring STRINGID_STATSWONTDECREASE
	goto BattleScript_DisturbEffect_WaitString

BattleScript_DisturbContrary:
	call BattleScript_AbilityPopUpTarget
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DisturbContrary_WontIncrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	goto BattleScript_DisturbEffect_WaitString
BattleScript_DisturbContrary_WontIncrease:
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	goto BattleScript_DisturbEffect_WaitString

BattleScript_DisturbInReverse:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUpTarget
	pause B_WAIT_TIME_SHORT
	modifybattlerstatstage BS_TARGET, STAT_ATK, INCREASE, 2, BattleScript_DisturbLoopIncrement, ANIM_ON
	call BattleScript_TryStatDropHoldEffects
	goto BattleScript_DisturbLoopIncrement

BattleScript_MockingActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_MockingLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_MockingLoopIncrement
	jumpiftargetally BattleScript_MockingLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_MockingLoopIncrement
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_MockingLoopIncrement
	jumpifability BS_TARGET, ABILITY_SCRAPPY, BattleScript_MockingPrevented
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_MockingPrevented
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_MockingPrevented
	jumpifability BS_TARGET, ABILITY_GUARD_DOG, BattleScript_MockingInReverse
BattleScript_MockingEffect_Def:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_MockingEffect_SpDef
	setgraphicalstatchangevalues
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_MockingContraryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_MockingWontDecreaseDef
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNCUTSDEFENCEWITH
	waitmessage B_WAIT_TIME_LONG
BattleScript_MockingEffect_SpDef:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_MockingLoopIncrement
	setgraphicalstatchangevalues
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_MockingContrarySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_MockingWontDecreaseSpDef
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNCUTSSPDEFENCEWITH
BattleScript_MockingEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_TryStatDropHoldEffects
	restoreattacker
	restoretarget
BattleScript_MockingLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_MockingLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_MockingPrevented:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	goto BattleScript_MockingEffect_WaitString

BattleScript_MockingWontDecreaseDef:
	printstring STRINGID_STATSWONTDECREASE
	goto BattleScript_MockingEffect_SpDef

BattleScript_MockingWontDecreaseSpDef:
	printstring STRINGID_STATSWONTDECREASE
	goto BattleScript_MockingEffect_WaitString

BattleScript_MockingContraryDef:
	call BattleScript_AbilityPopUpTarget
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MockingContrary_WontIncreaseDef
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	goto BattleScript_MockingEffect_SpDef
BattleScript_MockingContrary_WontIncreaseDef:
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	goto BattleScript_MockingEffect_SpDef

BattleScript_MockingContrarySpDef:
	call BattleScript_AbilityPopUpTarget
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_MockingContrary_WontIncreaseSpDef
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	goto BattleScript_MockingEffect_WaitString
BattleScript_MockingContrary_WontIncreaseSpDef:
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	goto BattleScript_MockingEffect_WaitString

BattleScript_MockingInReverse:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUpTarget
	pause B_WAIT_TIME_SHORT
	modifybattlerstatstage BS_TARGET, STAT_ATK, INCREASE, 2, BattleScript_MockingLoopIncrement, ANIM_ON
	call BattleScript_TryStatDropHoldEffects
	goto BattleScript_MockingLoopIncrement

BattleScript_EvilEyeActivates::
	savetarget
	showabilitypopup BS_ATTACKER
	pause B_WAIT_TIME_LONG
	destroyabilitypopup
	setbyte gBattlerTarget, 0
BattleScript_EvilEyeLoop:
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_EvilEyeLoopIncrement
	jumpiftargetally BattleScript_EvilEyeLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_EvilEyeLoopIncrement
	checkstatboosts 3, BattleScript_EvilEyeParalysisCheck
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_EvilEyeLoopIncrement
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_EvilEyePrevented
BattleScript_EvilEyeEffect:
	copybyte sBATTLER, gBattlerAttacker
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_EvilEyeLoopIncrement
	setgraphicalstatchangevalues
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_EvilEyeContrary
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_EvilEyeWontDecrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNCUTSSPEEDWITH
BattleScript_EvilEyeEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	saveattacker
	savetarget
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_TryStatDropHoldEffects
	restoreattacker
	restoretarget
BattleScript_EvilEyeLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_EvilEyeLoop
	copybyte sBATTLER, gBattlerAttacker
	destroyabilitypopup
	restoretarget
	pause B_WAIT_TIME_MED
	end3

BattleScript_EvilEyePrevented:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	goto BattleScript_EvilEyeEffect_WaitString
BattleScript_EvilEyePreventedNotAbility:
	setbyte gBattleCommunication STAT_ATK
	stattextbuffer BS_TARGET
	printstring STRINGID_STATWASNOTLOWERED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EvilEyeEffect_WaitString

BattleScript_EvilEyeWontDecrease:
	printstring STRINGID_STATSWONTDECREASE
	goto BattleScript_EvilEyeEffect_WaitString

BattleScript_EvilEyeContrary:
	call BattleScript_AbilityPopUpTarget
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EvilEyeContrary_WontIncrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	goto BattleScript_EvilEyeEffect_WaitString
BattleScript_EvilEyeContrary_WontIncrease:
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	goto BattleScript_EvilEyeEffect_WaitString

BattleScript_EvilEyeParalysisCheck:
	jumpifability BS_TARGET, ABILITY_LIMBER, BattleScript_EvilEyeParalysisPrevented
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_EvilEyeParalysisPrevented
	jumpifability BS_TARGET, ABILITY_PURIFYING_SALT, BattleScript_EvilEyeParalysisPrevented
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_EvilEyeParalysisPrevented
	jumpifflowerveil BattleScript_EvilEyeParalysisFlowerVeilPrevented
	jumpifleafguardprotected BS_TARGET, BattleScript_EvilEyeParalysisPrevented
	jumpifeeriemaskprotected BS_TARGET, BattleScript_EvilEyeParalysisPreventedNotAbility
	jumpifshieldsdown BS_TARGET, BattleScript_EvilEyeParalysisPrevented
	jumpifsubstituteblocks BattleScript_EvilEyeParalysisPreventedNotAbility
	jumpifgearmagnet BS_TARGET, BattleScript_EvilEyeParalysisPreventedNotAbility
	jumpifstatus BS_TARGET, STATUS1_PARALYSIS, BattleScript_EvilEyeParalysisPreventedNotAbility
	tryparalyzetype BS_ATTACKER, BS_TARGET, BattleScript_EvilEyeParalysisPreventedNotAbility
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_EvilEyeParalysisPreventedNotAbility
	jumpifsafeguard BattleScript_SafeguardEvilEyePrevented
BattleScript_EvilEyeParalysisEffect:
	copybyte sBATTLER, gBattlerAttacker
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EvilEyeLoopIncrement

BattleScript_SafeguardEvilEyePrevented:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage B_WAIT_TIME_LONG
	restoretarget
	end3

BattleScript_EvilEyeParalysisPrevented:
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_AbilityPopUp
BattleScript_EvilEyeParalysisPreventedNotAbility:
	printstring STRINGID_BUTITFAILED
	waitmessage B_WAIT_TIME_LONG
	copybyte sBATTLER, gBattlerTarget
	goto BattleScript_EvilEyeLoopIncrement

BattleScript_EvilEyeParalysisFlowerVeilPrevented:
	call BattleScript_FlowerVeilProtectsRet
	waitmessage B_WAIT_TIME_LONG
	copybyte sBATTLER, gBattlerTarget
	goto BattleScript_EvilEyeLoopIncrement

BattleScript_PanicTurn::
	printstring STRINGID_PKMNSISPANICKED
    waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	end2

BattleScript_BloomingHpGain::
	printstring STRINGID_PKMNSISBLOOMING
    waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	end2

BattleScript_BloomingHpGainEnd::
	playanimation BS_ATTACKER, B_ANIM_BLOOMING
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER
	waitstate
	clearstatus BS_ATTACKER
	updatestatusicon BS_ATTACKER
	printstring STRINGID_PKMNSISNOLONGERBLOOMING
    waitmessage B_WAIT_TIME_LONG
	end2

BattleScript_BloomingHealBlockEnd::
	printstring STRINGID_PKMNSISBLOOMING
    waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	end2

@ SHUNYONG
BattleScript_ShunyongAbilityActivates::
	call BattleScript_AbilityPopUp
	jumpifbyteequal sSTATCHANGER, sZero, BattleScript_ShunyongLowerLoop
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_ShunyongLowerLoop
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, B_MSG_DEFENDER_STAT_ROSE, BattleScript_ShunyongLowerLoop
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShunyongLowerLoop:
	jumpifbyteequal sSAVED_STAT_CHANGER, sZero, BattleScript_ShunyongEnd
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_ShunyongLowerLoopIncrement
	jumpiftargetally BattleScript_ShunyongLowerLoopIncrement
	jumpifabsent BS_TARGET, BattleScript_ShunyongLowerLoopIncrement
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ShunyongLowerLoopIncrement
BattleScript_ShunyongLowerEffect:
	copybyte sBATTLER, gBattlerAttacker
	copybyte sSTATCHANGER, sSAVED_STAT_CHANGER
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_ALLOW_PTR, BattleScript_ShunyongLowerLoopIncrement
	setgraphicalstatchangevalues
	jumpifability BS_TARGET, ABILITY_CONTRARY, BattleScript_ShunyongLowerContrary
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_ShunyongLowerEffect_WaitString:
	waitmessage B_WAIT_TIME_LONG
	copybyte sBATTLER, gBattlerTarget
	call BattleScript_TryStatDropHoldEffects
BattleScript_ShunyongLowerLoopIncrement:
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_ShunyongLowerLoop
BattleScript_ShunyongLowerEnd:
	copybyte sBATTLER, gBattlerAttacker
	printstring STRINGID_PRESSUREENTERS
	waitmessage B_WAIT_TIME_LONG
	destroyabilitypopup
	pause B_WAIT_TIME_MED
	end3
BattleScript_ShunyongEnd:
	end3

BattleScript_ShunyongLowerContrary:
	call BattleScript_AbilityPopUpTarget
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_ShunyongLowerContrary_WontIncrease
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	goto BattleScript_ShunyongLowerEffect_WaitString
BattleScript_ShunyongLowerContrary_WontIncrease:
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	goto BattleScript_ShunyongLowerEffect_WaitString

BattleScript_ShunyongCantHealInOffensiveForm::
	printstring STRINGID_CANTHEALINOFFENSIVEFORM
	waitmessage B_WAIT_TIME_LONG
	end3


BattleScript_EffectGoldPlains::
    attackcanceler
	attackstring
@	ppreduce
    @ no need to check failure since its only selected when usable
    attackanimation
	waitanimation
    printstring STRINGID_GOLDPLAINS
    waitmessage B_WAIT_TIME_LONG
    setbyte gBattlerTarget, 0
BattleScript_EffectGoldPlains_Loop:
    jumpifabsent BS_TARGET, BattleScript_EffectGoldPlains_NextBattler
    dogoldplains BS_TARGET, BattleScript_EffectGoldPlains_UpdateStatus
    orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectGoldPlains_UpdateStatus:
    updatestatusicon BS_TARGET
    waitstate
BattleScript_EffectGoldPlains_NextBattler:
    addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_EffectGoldPlains_Loop
BattleScript_EffectGoldPlains_End:
    goto BattleScript_MoveEnd

BattleScript_EffectDownfall:
    attackcanceler
    jumpifstatus BS_ATTACKER, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
    attackstring
@   ppreduce
    critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
BattleScript_DownfallTrySpite:
    tryspiteppreduce BattleScript_DownfallTryPanic
BattleScript_DownfallTryPanic:
    jumpifstatus BS_TARGET, STATUS1_PANIC, BattleScript_DownfallTryLowerStats
    setmoveeffect MOVE_EFFECT_PANIC | MOVE_EFFECT_CERTAIN
	seteffectwithchance
BattleScript_DownfallTryLowerStats:
    setmoveeffect MOVE_EFFECT_ALL_STATS_DOWN
    seteffectwithchance
	tryfaintmon BS_TARGET
    goto BattleScript_MoveEnd
    

BattleScript_EffectMtSplendor:
    attackcanceler
    jumpifstatus BS_ATTACKER, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
    attackstring
@   ppreduce
    critcalc
	damagecalc
	adjustdamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
BattleScript_EffectMtSplendor_TryRaiseStats:
    jumpifword CMP_NO_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING | HITMARKER_NO_PPDEDUCT, BattleScript_EffectMtSplendor_End
    setmoveeffect MOVE_EFFECT_ALL_STATS_UP | MOVE_EFFECT_AFFECTS_USER
    seteffectwithchance
BattleScript_EffectMtSplendor_End:
    tryfaintmon BS_TARGET
    goto BattleScript_MoveEnd

BattleScript_ResetNegativeStatStages::
    tryresetnegativestatstages BS_SCRIPTING
    printstring STRINGID_USERNEGATIVESTATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectPowder::
    setpowder BS_TARGET
    printstring STRINGID_COVEREDINPOWDER
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveEffectPPReduce::
    spelltagppreduce BattleScript_MoveEffectPPReduce_End
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage B_WAIT_TIME_LONG
BattleScript_MoveEffectPPReduce_End:
	return

BattleScript_MoveEffectTorment::
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_MoveEffectTorment_Ret
	jumpifability BS_TARGET, ABILITY_TITANIC, BattleScript_MoveEffectTorment_Ret
	jumpifability BS_TARGET, ABILITY_IGNORANT_BLISS, BattleScript_MoveEffectTorment_Ret
	jumpifsafeguard BattleScript_MoveEffectTorment_Ret
	settorment BattleScript_MoveEffectTorment_Ret
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage B_WAIT_TIME_LONG
	call BattleScript_TryDestinyKnotTormentAttacker
BattleScript_MoveEffectTorment_Ret:
	return
