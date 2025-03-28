#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_arena.h"
#include "battle_pyramid.h"
#include "battle_util.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_setup.h"
#include "battle_z_move.h"
#include "party_menu.h"
#include "pokemon.h"
#include "international_string_util.h"
#include "item.h"
#include "util.h"
#include "battle_scripts.h"
#include "random.h"
#include "text.h"
#include "safari_zone.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "test_runner.h"
#include "trig.h"
#include "window.h"
#include "battle_message.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "event_data.h"
#include "link.h"
#include "malloc.h"
#include "berry.h"
#include "pokedex.h"
#include "mail.h"
#include "field_weather.h"
#include "constants/abilities.h"
#include "constants/battle_anim.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_string_ids.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/weather.h"
#include "constants/pokemon.h"

extern struct Evolution gEvolutionTable[][EVOS_PER_MON];

/*
NOTE: The data and functions in this file up until (but not including) sSoundMovesTable
are actually part of battle_main.c. They needed to be moved to this file in order to
match the ROM; this is also why sSoundMovesTable's declaration is in the middle of
functions instead of at the top of the file with the other declarations.
*/

static bool32 TryRemoveScreens(u32 battler);
static bool32 IsUnnerveAbilityOnOpposingSide(u32 battler);
static u32 GetFlingPowerFromItemId(u32 itemId);
static void SetRandomMultiHitCounter();
static void SetRandomMultiHitCounter3To5();
static u32 GetBattlerItemHoldEffectParam(u32 battler, u32 item);
static uq4_12_t GetInverseTypeMultiplier(uq4_12_t multiplier);
static u32 BufferStatusCondition(u32 battler, bool32 checkStatus2);
NOINLINE static uq4_12_t PercentToUQ4_12(u32 percent);
NOINLINE static uq4_12_t PercentToUQ4_12_Floored(u32 percent);

extern const u8 *const gBattleScriptsForMoveEffects[];
extern const u8 *const gBattlescriptsForRunningByItem[];
extern const u8 *const gBattlescriptsForUsingItem[];
extern const u8 *const gBattlescriptsForSafariActions[];

static const u8 sPkblToEscapeFactor[][3] = {
    {[B_MSG_MON_CURIOUS] = 0,
     [B_MSG_MON_ENTHRALLED] = 0,
     [B_MSG_MON_IGNORED] = 0},
    {[B_MSG_MON_CURIOUS] = 3,
     [B_MSG_MON_ENTHRALLED] = 5,
     [B_MSG_MON_IGNORED] = 0},
    {[B_MSG_MON_CURIOUS] = 2,
     [B_MSG_MON_ENTHRALLED] = 3,
     [B_MSG_MON_IGNORED] = 0},
    {[B_MSG_MON_CURIOUS] = 1,
     [B_MSG_MON_ENTHRALLED] = 2,
     [B_MSG_MON_IGNORED] = 0},
    {[B_MSG_MON_CURIOUS] = 1,
     [B_MSG_MON_ENTHRALLED] = 1,
     [B_MSG_MON_IGNORED] = 0}};
static const u8 sGoNearCounterToCatchFactor[] = {4, 3, 2, 1};
static const u8 sGoNearCounterToEscapeFactor[] = {4, 4, 4, 4};

static const u16 sUnchangeableAbilities[] =
{
    ABILITY_WONDER_GUARD,
    ABILITY_MULTITYPE,
    ABILITY_ILLUSION,
    ABILITY_ZEN_MODE,
    ABILITY_STELLAR_BODY,
    ABILITY_SHIELDS_DOWN,
    ABILITY_HUDDLE_UP,
    ABILITY_DISGUISE,
    ABILITY_BROKEN,
    ABILITY_BATTLE_BOND,
    ABILITY_DORMANT,
    ABILITY_COMATOSE,
    ABILITY_RKS_SYSTEM,
    ABILITY_ICE_FACE,
    ABILITY_NEUTRALIZING_GAS,
    ABILITY_HUNGER_SWITCH,
    ABILITY_EGGS_ROYALE,
    ABILITY_TRACE,
    ABILITY_FORECAST,
    ABILITY_FLOWER_GIFT,
    ABILITY_IMPOSTER,
    ABILITY_RECEIVER,
    ABILITY_POWER_OF_ALCHEMY,
    ABILITY_TRUANT,
    ABILITY_SHUNYONG,
    ABILITY_TITANIC,
    ABILITY_ENDLESS,
    ABILITY_RISING,
    ABILITY_FALLING,
    ABILITY_PRODIGY,
    ABILITY_PUNISHER,
    ABILITY_ARBITER,
    ABILITY_WATCHER,
    ABILITY_REVERSI,
    ABILITY_STARS_GRACE,
    ABILITY_SUGAR_COAT,
    ABILITY_TIME_TURN,
    ABILITY_WHITE_SMOKE,
    ABILITY_PINK_MIST,
    ABILITY_IGNORANT_BLISS,
    ABILITY_MELANCHOLIA,
    ABILITY_MILKY_WAY,
    ABILITY_CINDER_WALTZ,
    ABILITY_RESET,
    ABILITY_PURPLE_HAZE,
    ABILITY_MAGMA_ARMOR,
    ABILITY_LOVESICK,
    ABILITY_VERTIGO,
    ABILITY_MIND_GAMES,
    ABILITY_STORM_BREW,
    ABILITY_FULL_METAL_BODY,
    ABILITY_KLUTZ,
    ABILITY_FIREBRAND,
    ABILITY_PURE_POWER,
    ABILITY_MYSTIC_ONE,
    ABILITY_SUNRISE,
    ABILITY_DELUGE,
    ABILITY_REFORM,
    ABILITY_RUIN_WARD,
    ABILITY_RAPID_FIRE,
};

static u8 CalcBeatUpPower(void)
{
    u8 basePower;
    u16 species;
    struct Pokemon *party = GetBattlerParty(gBattlerAttacker);

    // Party slot is incremented by the battle script for Beat Up after this damage calculation
    species = GetMonData(&party[gBattleStruct->beatUpSlot], MON_DATA_SPECIES);
    basePower = (gSpeciesInfo[species].baseAttack * 2) / 10;

    return basePower;
}

bool32 IsAffectedByFollowMe(u32 battlerAtk, u32 defSide, u32 move)
{
    u32 ability = GetBattlerAbility(battlerAtk);
    if (IsAbilityOnOpposingSide(battlerAtk, ABILITY_ENTRANCING))
    {
        if (gSideTimers[defSide].followmeTimer == 0)
        {
            gSideTimers[defSide].followmeTimer = 1;
        }
        return TRUE;
    }
    if (gSideTimers[defSide].followmeTimer == 0 || gBattleMons[gSideTimers[defSide].followmeTarget].hp == 0 || gBattleMoves[move].effect == EFFECT_SNIPE_SHOT || gBattleMoves[move].effect == EFFECT_PSYSTRIKE || gBattleMoves[move].effect == EFFECT_SKY_DROP || ability == ABILITY_PROPELLER_TAIL || ability == ABILITY_STALWART)
        return FALSE;

    if (gSideTimers[defSide].followmePowder && !IsAffectedByPowder(battlerAtk, ability, GetBattlerHoldEffect(battlerAtk, TRUE)))
        return FALSE;

    return TRUE;
}

bool32 IsAffectedBySpotlight(u32 battlerAtk, u32 defSide, u32 move)
{
    u32 ability = GetBattlerAbility(battlerAtk);

    if (gSideTimers[defSide].spotlightTimer == 0 || gBattleMons[gSideTimers[defSide].spotlightTarget].hp == 0 || gBattleMoves[move].effect == EFFECT_SNIPE_SHOT || gBattleMoves[move].effect == EFFECT_PSYSTRIKE || gBattleMoves[move].effect == EFFECT_SKY_DROP || ability == ABILITY_PROPELLER_TAIL || ability == ABILITY_STALWART)
        return FALSE;
    return TRUE;
}

// Functions
void HandleAction_UseMove(void)
{
    u32 battler, i, side, moveType, var = 4;
    u16 moveTarget;

    DestroyTypeIcon();
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    if (gBattleStruct->absentBattlerFlags & gBitTable[gBattlerAttacker] || !IsBattlerAlive(gBattlerAttacker))
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        return;
    }

    gIsCriticalHit = FALSE;
    gBattleStruct->atkCancellerTracker = 0;
    gMoveResultFlags = 0;
    gMultiHitCounter = 0;
    gBattleScripting.savedDmg = 0;
    gBattleCommunication[MISS_TYPE] = 0;
    gBattleScripting.savedMoveEffect = 0;
    gCurrMovePos = gChosenMovePos = *(gBattleStruct->chosenMovePositions + gBattlerAttacker);

    // choose move
    if (gProtectStructs[gBattlerAttacker].noValidMoves)
    {
        gProtectStructs[gBattlerAttacker].noValidMoves = FALSE;
        gCurrentMove = gChosenMove = MOVE_STRUGGLE;
        gHitMarker |= HITMARKER_NO_PPDEDUCT;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(MOVE_STRUGGLE, NO_TARGET_OVERRIDE);
    }
    else if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS 
        || gBattleMons[gBattlerAttacker].status2 & STATUS2_RECHARGE 
        || gStatuses4[gBattlerAttacker] & STATUS4_RECHARGE_REDUCE
        || gStatuses4[gBattlerAttacker] & STATUS4_RECHARGE_STATS
        || gStatuses4[gBattlerAttacker] & STATUS4_RECHARGE_BURN)
    {
        gCurrentMove = gChosenMove = gLockedMoves[gBattlerAttacker];
    }
    // encore forces you to use the same move
    else if (!gBattleStruct->zmove.active && gDisableStructs[gBattlerAttacker].encoredMove != MOVE_NONE && gDisableStructs[gBattlerAttacker].encoredMove == gBattleMons[gBattlerAttacker].moves[gDisableStructs[gBattlerAttacker].encoredMovePos])
    {
        gCurrentMove = gChosenMove = gDisableStructs[gBattlerAttacker].encoredMove;
        gCurrMovePos = gChosenMovePos = gDisableStructs[gBattlerAttacker].encoredMovePos;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, NO_TARGET_OVERRIDE);
    }
    // check if the encored move wasn't overwritten
    else if (!gBattleStruct->zmove.active && gDisableStructs[gBattlerAttacker].encoredMove != MOVE_NONE && gDisableStructs[gBattlerAttacker].encoredMove != gBattleMons[gBattlerAttacker].moves[gDisableStructs[gBattlerAttacker].encoredMovePos])
    {
        gCurrMovePos = gChosenMovePos = gDisableStructs[gBattlerAttacker].encoredMovePos;
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        gDisableStructs[gBattlerAttacker].encoredMove = MOVE_NONE;
        gDisableStructs[gBattlerAttacker].encoredMovePos = 0;
        gDisableStructs[gBattlerAttacker].encoreTimer = 0;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, NO_TARGET_OVERRIDE);
    }
    else if (gBattleMons[gBattlerAttacker].moves[gCurrMovePos] != gChosenMoveByBattler[gBattlerAttacker])
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, NO_TARGET_OVERRIDE);
    }
    else
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
    }

    // check z move used
    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] != MOVE_NONE && !IS_MOVE_STATUS(gCurrentMove))
    {
        gCurrentMove = gBattleStruct->zmove.toBeUsed[gBattlerAttacker];
    }

    moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove);

    if (gBattleMons[gBattlerAttacker].hp != 0)
    {
        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
            gBattleResults.lastUsedMovePlayer = gCurrentMove;
        else
            gBattleResults.lastUsedMoveOpponent = gCurrentMove;
    }

    // Set dynamic move type.
    SetTypeBeforeUsingMove(gChosenMove, gBattlerAttacker);
    GET_MOVE_TYPE(gChosenMove, moveType);

    // choose target
    side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));
    if (IsAffectedBySpotlight(gBattlerAttacker, side, gCurrentMove) && moveTarget == MOVE_TARGET_SELECTED && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gSideTimers[side].spotlightTarget))
    {
        gBattleStruct->moveTarget[gBattlerAttacker] = gBattlerTarget = gSideTimers[side].spotlightTarget; // follow me moxie fix
    }
    else if (IsAffectedByFollowMe(gBattlerAttacker, side, gCurrentMove) && moveTarget == MOVE_TARGET_SELECTED && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gSideTimers[side].followmeTarget))
    {
        gBattleStruct->moveTarget[gBattlerAttacker] = gBattlerTarget = gSideTimers[side].followmeTarget; // follow me moxie fix
    }
    else if (gProtectStructs[gBattlerAttacker].overtakeRedirectActive == TRUE 
        && moveTarget == MOVE_TARGET_SELECTED
        && gBattleMoves[gCurrentMove].effect != EFFECT_SNIPE_SHOT
        && gBattleMoves[gCurrentMove].effect != EFFECT_PSYSTRIKE
        && gBattleMoves[gCurrentMove].effect != EFFECT_SKY_DROP
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_PROPELLER_TAIL
        && GetBattlerAbility(gBattlerAttacker) != ABILITY_STALWART)
    {
        int battler;
        
        for (battler = 0; battler < MAX_BATTLERS_COUNT; battler++)
        {
            //search linked battler to set target
            if (gProtectStructs[gBattlerAttacker].overtakeRedirectedUser == battler)
            {
                //set target
                gBattlerTarget = battler;
                if (!IsBattlerAlive(battler))
                    gBattlerTarget ^= BIT_FLANK; //change target if opponent is dead
                gBattleStruct->moveTarget[gBattlerAttacker] = gBattlerTarget;
                battler = MAX_BATTLERS_COUNT; //exit loop early
            }
        }
    }
    else if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE) && gSideTimers[side].followmeTimer == 0 && gSideTimers[side].spotlightTimer == 0 && (gBattleMoves[gCurrentMove].power != 0 || (moveTarget != MOVE_TARGET_USER && moveTarget != MOVE_TARGET_ALL_BATTLERS)) && ((GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_LIGHTNING_ROD && moveType == TYPE_ELECTRIC) || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_STORM_DRAIN && moveType == TYPE_WATER) || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_MAGNET_PULL && moveType == TYPE_STEEL) || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_WITCHCRAFT && moveType == TYPE_FAIRY) || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_SOUL_LOCKER && moveType == TYPE_GHOST)))
    {
        side = GetBattlerSide(gBattlerAttacker);
        for (battler = 0; battler < gBattlersCount; battler++)
        {
            if (*(gBattleStruct->moveTarget + gBattlerAttacker) != battler 
            && battler != gBattlerAttacker
            && ((GetBattlerAbility(battler) == ABILITY_LIGHTNING_ROD && moveType == TYPE_ELECTRIC)
            || (GetBattlerAbility(battler) == ABILITY_STORM_DRAIN && moveType == TYPE_WATER) 
            || (GetBattlerAbility(battler) == ABILITY_MAGNET_PULL && moveType == TYPE_STEEL) 
            || (GetBattlerAbility(battler) == ABILITY_WITCHCRAFT && moveType == TYPE_FAIRY) 
            || (GetBattlerAbility(battler) == ABILITY_SOUL_LOCKER && moveType == TYPE_GHOST)) 
            && GetBattlerTurnOrderNum(battler) < var 
            && ((gBattleMoves[gCurrentMove].effect != EFFECT_SNIPE_SHOT)
            || (gBattleMoves[gCurrentMove].effect != EFFECT_PSYSTRIKE))
            && (GetBattlerAbility(gBattlerAttacker) != ABILITY_PROPELLER_TAIL 
            || GetBattlerAbility(gBattlerAttacker) != ABILITY_STALWART))
            {
                var = GetBattlerTurnOrderNum(battler);
            }
        }
        if (var == 4)
        {
            if (moveTarget & MOVE_TARGET_RANDOM)
            {
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                {
                    if (Random() & 1)
                        gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
                    else
                        gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
                }
                else
                {
                    if (Random() & 1)
                        gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
                    else
                        gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
                }
            }
            else if (moveTarget & MOVE_TARGET_FOES_AND_ALLY)
            {
                for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; gBattlerTarget++)
                {
                    if (gBattlerTarget == gBattlerAttacker)
                        continue;
                    if (IsBattlerAlive(gBattlerTarget))
                        break;
                }
            }
            else
            {
                gBattlerTarget = *(gBattleStruct->moveTarget + gBattlerAttacker);
            }

            if (!IsBattlerAlive(gBattlerTarget))
            {
                if (GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
                {
                    gBattlerTarget = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerTarget)));
                }
                else
                {
                    gBattlerTarget = GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerPosition(gBattlerAttacker)));
                    if (!IsBattlerAlive(gBattlerTarget))
                        gBattlerTarget = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerTarget)));
                }
            }
        }
        else
        {
            u16 battlerAbility;
            battler = gBattlerByTurnOrder[var];
            battlerAbility = GetBattlerAbility(battler);

            RecordAbilityBattle(battler, gBattleMons[battler].ability);
            if (battlerAbility == ABILITY_LIGHTNING_ROD && gCurrentMove != MOVE_TEATIME)
                gSpecialStatuses[battler].lightningRodRedirected = TRUE;
            else if (battlerAbility == ABILITY_STORM_DRAIN)
                gSpecialStatuses[battler].stormDrainRedirected = TRUE;
            else if (battlerAbility == ABILITY_MAGNET_PULL)
                gSpecialStatuses[battler].magnetPullRedirected = TRUE;
            else if (battlerAbility == ABILITY_WITCHCRAFT)
                gSpecialStatuses[battler].witchcraftRedirected = TRUE;
            else if (battlerAbility == ABILITY_SOUL_LOCKER)
                gSpecialStatuses[battler].soulLockerRedirected = TRUE;
            gBattlerTarget = battler;
        }
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && moveTarget & MOVE_TARGET_RANDOM)
    {
        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        {
            if (Random() & 1)
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            else
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        }
        else
        {
            if (Random() & 1)
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            else
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        }

        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget] && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
        {
            gBattlerTarget = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerTarget)));
        }
    }
    else if (moveTarget == MOVE_TARGET_ALLY)
    {
        if (IsBattlerAlive(BATTLE_PARTNER(gBattlerAttacker)))
            gBattlerTarget = BATTLE_PARTNER(gBattlerAttacker);
        else
            gBattlerTarget = gBattlerAttacker;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && moveTarget == MOVE_TARGET_FOES_AND_ALLY)
    {
        for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount; gBattlerTarget++)
        {
            if (gBattlerTarget == gBattlerAttacker)
                continue;
            if (IsBattlerAlive(gBattlerTarget))
                break;
        }
    }
    else
    {
        gBattlerTarget = *(gBattleStruct->moveTarget + gBattlerAttacker);
        if (!IsBattlerAlive(gBattlerTarget))
        {
            if (GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
            {
                gBattlerTarget = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerTarget)));
            }
            else
            {
                gBattlerTarget = GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerPosition(gBattlerAttacker)));
                if (!IsBattlerAlive(gBattlerTarget))
                    gBattlerTarget = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gBattlerTarget)));
            }
        }
    }

    if (gBattleTypeFlags & BATTLE_TYPE_PALACE && gProtectStructs[gBattlerAttacker].palaceUnableToUseMove)
    {
        // Battle Palace, select battle script for failure to use move
        if (!IsBattlerAlive(gBattlerAttacker))
        {
            gCurrentActionFuncId = B_ACTION_FINISHED;
            return;
        }
        else if (gPalaceSelectionBattleScripts[gBattlerAttacker] != NULL)
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_INCAPABLE_OF_POWER;
            gBattlescriptCurrInstr = gPalaceSelectionBattleScripts[gBattlerAttacker];
            gPalaceSelectionBattleScripts[gBattlerAttacker] = NULL;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_INCAPABLE_OF_POWER;
            gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
        }
    }

    if ((IsAlly(gBattlerAttacker, gBattlerTarget))
     && (!IsBattlerAlive(gBattlerTarget) || gProtectStructs[BATTLE_PARTNER(gBattlerAttacker)].usedAllySwitch))
    {
        gBattlescriptCurrInstr = BattleScript_FailedFromAtkCanceler;
    }
    else
    {
        gBattlescriptCurrInstr = gBattleScriptsForMoveEffects[gBattleMoves[gCurrentMove].effect];
    }

    if (gBattleTypeFlags & BATTLE_TYPE_ARENA)
        BattleArena_AddMindPoints(gBattlerAttacker);

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        gBattleStruct->hpBefore[i] = gBattleMons[i].hp;
        gSpecialStatuses[i].emergencyExited = FALSE;
    }

    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_Switch(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gActionSelectionCursor[gBattlerAttacker] = 0;
    gMoveSelectionCursor[gBattlerAttacker] = 0;

    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, *(gBattleStruct->battlerPartyIndexes + gBattlerAttacker))

    gBattleScripting.battler = gBattlerAttacker;
    gBattlescriptCurrInstr = BattleScript_ActionSwitch;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;

    if (gBattleResults.playerSwitchesCounter < 255)
        gBattleResults.playerSwitchesCounter++;

    TryBattleFormChange(gBattlerAttacker, FORM_CHANGE_BATTLE_SWITCH);
}

void HandleAction_UseItem(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    ClearFuryCutterDestinyBondGrudge(gBattlerAttacker);

    gLastUsedItem = gBattleResources->bufferB[gBattlerAttacker][1] | (gBattleResources->bufferB[gBattlerAttacker][2] << 8);
    gBattlescriptCurrInstr = gBattlescriptsForUsingItem[ItemId_GetBattleUsage(gLastUsedItem) - 1];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

bool32 TryRunFromBattle(u32 battler)
{
    bool32 effect = FALSE;
    u8 holdEffect;
    u8 pyramidMultiplier;
    u8 speedVar;

    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY_E_READER)
        holdEffect = gEnigmaBerries[battler].holdEffect;
    else
        holdEffect = ItemId_GetHoldEffect(gBattleMons[battler].item);

    gPotentialItemEffectBattler = battler;

    if (holdEffect == HOLD_EFFECT_CAN_ALWAYS_RUN)
    {
        gLastUsedItem = gBattleMons[battler].item;
        gProtectStructs[battler].fleeType = FLEE_ITEM;
        effect++;
    }
#if B_GHOSTS_ESCAPE >= GEN_6
    else if (IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
    {
        effect++;
    }
#endif
    else if (GetBattlerAbility(battler) == ABILITY_RUN_AWAY)
    {
        if (InBattlePyramid())
        {
            gBattleStruct->runTries++;
            pyramidMultiplier = GetPyramidRunMultiplier();
            speedVar = (gBattleMons[battler].speed * pyramidMultiplier) / (gBattleMons[BATTLE_OPPOSITE(battler)].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
            {
                gLastUsedAbility = ABILITY_RUN_AWAY;
                gProtectStructs[battler].fleeType = FLEE_ABILITY;
                effect++;
            }
        }
        else
        {
            gLastUsedAbility = ABILITY_RUN_AWAY;
            gProtectStructs[battler].fleeType = FLEE_ABILITY;
            effect++;
        }
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_FRONTIER | BATTLE_TYPE_TRAINER_HILL) && gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        effect++;
    }
    else
    {
        u8 runningFromBattler = BATTLE_OPPOSITE(battler);
        if (!IsBattlerAlive(runningFromBattler))
            runningFromBattler |= BIT_FLANK;

        if (InBattlePyramid())
        {
            pyramidMultiplier = GetPyramidRunMultiplier();
            speedVar = (gBattleMons[battler].speed * pyramidMultiplier) / (gBattleMons[runningFromBattler].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
                effect++;
        }
        else if (gBattleMons[battler].speed < gBattleMons[runningFromBattler].speed)
        {
            speedVar = (gBattleMons[battler].speed * 128) / (gBattleMons[runningFromBattler].speed) + (gBattleStruct->runTries * 30);
            if (speedVar > (Random() & 0xFF))
                effect++;
        }
        else // same speed or faster
        {
            effect++;
        }

        gBattleStruct->runTries++;
    }

    if (effect != 0)
    {
        gCurrentTurnActionNumber = gBattlersCount;
        gBattleOutcome = B_OUTCOME_RAN;
    }

    return effect;
}

void HandleAction_Run(void)
{
    s32 i;

    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
    {
        gCurrentTurnActionNumber = gBattlersCount;

        for (i = 0; i < gBattlersCount; i++)
        {
            if (GetBattlerSide(i) == B_SIDE_PLAYER)
            {
                if (gChosenActionByBattler[i] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_LOST;
            }
            else
            {
                if (gChosenActionByBattler[i] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_WON;
            }
        }

        gBattleOutcome |= B_OUTCOME_LINK_BATTLE_RAN;
        gSaveBlock2Ptr->frontier.disableRecordBattle = TRUE;
    }
    else
    {
        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        {
            if (!TryRunFromBattle(gBattlerAttacker)) // failed to run away
            {
                ClearFuryCutterDestinyBondGrudge(gBattlerAttacker);
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CANT_ESCAPE_2;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
        }
        else
        {
            if (!CanBattlerEscape(gBattlerAttacker))
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_ATTACKER_CANT_ESCAPE;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
            else
            {
                gCurrentTurnActionNumber = gBattlersCount;
                gBattleOutcome = B_OUTCOME_MON_FLED;
            }
        }
    }
}

void HandleAction_WatchesCarefully(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[0];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_SafariZoneBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gNumSafariBalls--;
    gLastUsedItem = ITEM_SAFARI_BALL;
    gBattlescriptCurrInstr = BattleScript_SafariBallThrow;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_ThrowBall(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gLastUsedItem = gBallToDisplay;
    RemoveBagItem(gLastUsedItem, 1);
    gBattlescriptCurrInstr = BattleScript_BallThrow;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_ThrowPokeblock(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattleCommunication[MULTISTRING_CHOOSER] = gBattleResources->bufferB[gBattlerAttacker][1] - 1;
    gLastUsedItem = gBattleResources->bufferB[gBattlerAttacker][2];

    if (gBattleResults.pokeblockThrows < 255)
        gBattleResults.pokeblockThrows++;
    if (gBattleStruct->safariPkblThrowCounter < 3)
        gBattleStruct->safariPkblThrowCounter++;
    if (gBattleStruct->safariEscapeFactor > 1)
    {
// BUG: safariEscapeFactor can become 0 below. This causes the pokeblock throw glitch.
#ifdef BUGFIX
        if (gBattleStruct->safariEscapeFactor <= sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]])
#else
        if (gBattleStruct->safariEscapeFactor < sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]])
#endif
            gBattleStruct->safariEscapeFactor = 1;
        else
            gBattleStruct->safariEscapeFactor -= sPkblToEscapeFactor[gBattleStruct->safariPkblThrowCounter][gBattleCommunication[MULTISTRING_CHOOSER]];
    }

    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[2];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_GoNear(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;

    gBattleStruct->safariCatchFactor += sGoNearCounterToCatchFactor[gBattleStruct->safariGoNearCounter];
    if (gBattleStruct->safariCatchFactor > 20)
        gBattleStruct->safariCatchFactor = 20;

    gBattleStruct->safariEscapeFactor += sGoNearCounterToEscapeFactor[gBattleStruct->safariGoNearCounter];
    if (gBattleStruct->safariEscapeFactor > 20)
        gBattleStruct->safariEscapeFactor = 20;

    if (gBattleStruct->safariGoNearCounter < 3)
    {
        gBattleStruct->safariGoNearCounter++;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CREPT_CLOSER;
    }
    else
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CANT_GET_CLOSER;
    }
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[1];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

void HandleAction_SafariZoneRun(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    PlaySE(SE_FLEE);
    gCurrentTurnActionNumber = gBattlersCount;
    gBattleOutcome = B_OUTCOME_RAN;
}

void HandleAction_WallyBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;

    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])

    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[3];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
    gActionsByTurnOrder[1] = B_ACTION_FINISHED;
}

void HandleAction_TryFinish(void)
{
    if (!HandleFaintedMonActions())
    {
        gBattleStruct->faintedActionsState = 0;
        gCurrentActionFuncId = B_ACTION_FINISHED;
    }
}

void HandleAction_NothingIsFainted(void)
{
    gCurrentTurnActionNumber++;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    gHitMarker &= ~(HITMARKER_DESTINYBOND | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_ATTACKSTRING_PRINTED | HITMARKER_NO_PPDEDUCT | HITMARKER_IGNORE_SAFEGUARD | HITMARKER_PASSIVE_DAMAGE | HITMARKER_OBEYS | HITMARKER_WAKE_UP_CLEAR | HITMARKER_SYNCHRONIZE_EFFECT | HITMARKER_CHARGING | HITMARKER_NEVER_SET | HITMARKER_SYNCHRONIZE_SKIP);
}

void HandleAction_ActionFinished(void)
{
#if B_RECALC_TURN_AFTER_ACTIONS >= GEN_8
    u32 i, j;
    bool32 afterYouActive = gSpecialStatuses[gBattlerByTurnOrder[gCurrentTurnActionNumber + 1]].afterYou;
#endif
    *(gBattleStruct->monToSwitchIntoId + gBattlerByTurnOrder[gCurrentTurnActionNumber]) = gSelectedMonPartyId = PARTY_SIZE;
    gCurrentTurnActionNumber++;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    SpecialStatusesClear();
    gHitMarker &= ~(HITMARKER_DESTINYBOND | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_ATTACKSTRING_PRINTED | HITMARKER_NO_PPDEDUCT | HITMARKER_IGNORE_SAFEGUARD | HITMARKER_PASSIVE_DAMAGE | HITMARKER_OBEYS | HITMARKER_WAKE_UP_CLEAR | HITMARKER_SYNCHRONIZE_EFFECT | HITMARKER_CHARGING | HITMARKER_NEVER_SET | HITMARKER_IGNORE_DISGUISE | HITMARKER_SYNCHRONIZE_SKIP);

    gCurrentMove = 0;
    gBattleMoveDamage = 0;
    gMoveResultFlags = 0;
    gBattleScripting.animTurn = 0;
    gBattleScripting.animTargetsHit = 0;
    gLastLandedMoves[gBattlerAttacker] = 0;
    gLastHitByType[gBattlerAttacker] = 0;
    gProtectStructs[gBattlerAttacker].extraMoveUsed = 0;
    gBattleStruct->dynamicMoveType = 0;
    gBattleScripting.moveendState = 0;
    gBattleCommunication[3] = 0;
    gBattleCommunication[4] = 0;
    gBattleScripting.multihitMoveEffect = 0;
    gBattleResources->battleScriptsStack->size = 0;

#if B_RECALC_TURN_AFTER_ACTIONS >= GEN_8
    if (!afterYouActive)
    {
        // i starts at `gCurrentTurnActionNumber` because we don't want to recalculate turn order for mon that have already
        // taken action. It's been previously increased, which we want in order to not recalculate the turn of the mon that just finished its action
        for (i = gCurrentTurnActionNumber; i < gBattlersCount - 1; i++)
        {
            for (j = i + 1; j < gBattlersCount; j++)
            {
                u32 battler1 = gBattlerByTurnOrder[i];
                u32 battler2 = gBattlerByTurnOrder[j];

                if (gProtectStructs[battler1].quash || gProtectStructs[battler2].quash || gProtectStructs[battler1].shellTrap || gProtectStructs[battler2].shellTrap)
                    continue;

                // We recalculate order only for action of the same priority. If any action other than switch/move has been taken, they should
                // have been executed before. The only recalculation needed is for moves/switch. Mega evolution is handled in src/battle_main.c/TryChangeOrder
                if ((gActionsByTurnOrder[i] == B_ACTION_USE_MOVE && gActionsByTurnOrder[j] == B_ACTION_USE_MOVE))
                {
                    if (GetWhichBattlerFaster(battler1, battler2, FALSE))
                        SwapTurnOrder(i, j);
                }
                else if ((gActionsByTurnOrder[i] == B_ACTION_SWITCH && gActionsByTurnOrder[j] == B_ACTION_SWITCH))
                {
                    if (GetWhichBattlerFaster(battler1, battler2, TRUE)) // If the actions chosen are switching, we recalc order but ignoring the moves
                        SwapTurnOrder(i, j);
                }
            }
        }
    }
#endif
}

static const u8 sHoldEffectToType[][2] =
    {
        {HOLD_EFFECT_BUG_POWER, TYPE_BUG},
        {HOLD_EFFECT_STEEL_POWER, TYPE_STEEL},
        {HOLD_EFFECT_GROUND_POWER, TYPE_GROUND},
        {HOLD_EFFECT_ROCK_POWER, TYPE_ROCK},
        {HOLD_EFFECT_GRASS_POWER, TYPE_GRASS},
        {HOLD_EFFECT_DARK_POWER, TYPE_DARK},
        {HOLD_EFFECT_FIGHTING_POWER, TYPE_FIGHTING},
        {HOLD_EFFECT_ELECTRIC_POWER, TYPE_ELECTRIC},
        {HOLD_EFFECT_WATER_POWER, TYPE_WATER},
        {HOLD_EFFECT_FLYING_POWER, TYPE_FLYING},
        {HOLD_EFFECT_POISON_POWER, TYPE_POISON},
        {HOLD_EFFECT_ICE_POWER, TYPE_ICE},
        {HOLD_EFFECT_GHOST_POWER, TYPE_GHOST},
        {HOLD_EFFECT_PSYCHIC_POWER, TYPE_PSYCHIC},
        {HOLD_EFFECT_FIRE_POWER, TYPE_FIRE},
        {HOLD_EFFECT_DRAGON_POWER, TYPE_DRAGON},
        {HOLD_EFFECT_NORMAL_POWER, TYPE_NORMAL},
        {HOLD_EFFECT_FAIRY_POWER, TYPE_FAIRY},
};

NOINLINE static uq4_12_t PercentToUQ4_12(u32 percent)
{
    return (4096 * percent + 50) / 100;
}

NOINLINE static uq4_12_t PercentToUQ4_12_Floored(u32 percent)
{
    return (4096 * percent) / 100;
}

#define X UQ_4_12

static const uq4_12_t sTypeEffectivenessTable[NUMBER_OF_MON_TYPES][NUMBER_OF_MON_TYPES] =
    {
        //normal fight   flying  poison  ground  rock    bug     ghost   steel   mystery fire    water   grass   elec    psychic ice     dragon  dark    fairy   relic
        {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(0.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // normal
        {X(2.0), X(1.0), X(0.5), X(0.5), X(1.0), X(2.0), X(0.5), X(0.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(2.0), X(1.0), X(2.0), X(0.5), X(1.0)}, // fight
        {X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(0.5), X(2.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(2.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // flying
        {X(1.0), X(1.0), X(1.0), X(0.5), X(0.5), X(0.5), X(1.0), X(0.5), X(0.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0)}, // poison
        {X(1.0), X(1.0), X(0.0), X(2.0), X(1.0), X(2.0), X(0.5), X(1.0), X(2.0), X(1.0), X(2.0), X(1.0), X(0.5), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // ground
        {X(1.0), X(0.5), X(2.0), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // rock
        {X(1.0), X(0.5), X(0.5), X(0.5), X(1.0), X(1.0), X(1.0), X(0.5), X(0.5), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(2.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0)}, // bug
        {X(0.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(0.5), X(1.0), X(0.5)}, // ghost
        {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(0.5), X(1.0), X(0.5), X(0.5), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(1.0), X(2.0), X(1.0)}, // steel
        {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // mystery
        {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(2.0), X(1.0), X(2.0), X(1.0), X(0.5), X(0.5), X(2.0), X(1.0), X(1.0), X(2.0), X(0.5), X(1.0), X(1.0), X(0.5)}, // fire
        {X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(0.5), X(0.5), X(1.0), X(1.0), X(0.5), X(0.5), X(1.0), X(1.0), X(0.5)}, // water
        {X(1.0), X(1.0), X(1.0), X(0.5), X(2.0), X(2.0), X(0.5), X(1.0), X(1.0), X(1.0), X(0.5), X(2.0), X(0.5), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(2.0)}, // grass
        {X(1.0), X(1.0), X(2.0), X(1.0), X(0.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(0.5), X(0.5), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0)}, // electric
        {X(1.0), X(2.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(0.0), X(1.0), X(2.0)}, // psychic
        {X(1.0), X(1.0), X(2.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(0.5), X(2.0), X(1.0), X(1.0), X(0.5), X(2.0), X(1.0), X(1.0), X(1.0)}, // ice
        {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(0.5), X(1.0)}, // dragon
        {X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(0.5), X(0.5), X(1.0)}, // dark
        {X(1.0), X(2.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(2.0), X(1.0), X(1.0)}, // fairy
        {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(2.0), X(1.0)}, // relic
};

#undef X

// code
u8 GetBattlerForBattleScript(u8 caseId)
{
    u8 ret = 0;
    switch (caseId)
    {
    case BS_TARGET:
        ret = gBattlerTarget;
        break;
    case BS_ATTACKER:
        ret = gBattlerAttacker;
        break;
    case BS_ATTACKER_PARTNER:
        ret = BATTLE_PARTNER(gBattlerAttacker);
        break;
    case BS_EFFECT_BATTLER:
        ret = gEffectBattler;
        break;
    case BS_BATTLER_0:
        ret = 0;
        break;
    case BS_SCRIPTING:
        ret = gBattleScripting.battler;
        break;
    case BS_FAINTED:
        ret = gBattlerFainted;
        break;
    case BS_FAINTED_LINK_MULTIPLE_1:
        ret = gBattlerFainted;
        break;
    case BS_ATTACKER_WITH_PARTNER:
    case BS_FAINTED_LINK_MULTIPLE_2:
    case BS_ATTACKER_SIDE:
    case BS_TARGET_SIDE:
    case BS_PLAYER1:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        break;
    case BS_OPPONENT1:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        break;
    case BS_PLAYER2:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        break;
    case BS_OPPONENT2:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        break;
    case BS_ABILITY_BATTLER:
        ret = gBattlerAbility;
        break;
    }
    return ret;
}

void PressurePPLose(u8 target, u8 attacker, u16 move)
{
    int moveIndex;
    u16 targetAbility = GetBattlerAbility(target);

    if (targetAbility != ABILITY_PRESSURE
    || GetBattlerHoldEffect(target, TRUE) != HOLD_EFFECT_SPECTRAL_IDOL
    || (targetAbility != ABILITY_SHUNYONG && gBattleResults.battleTurnCounter % 2 != 0)
    || gBattleMons[attacker].status1 & STATUS1_PANIC)
        return;

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (gBattleMons[attacker].moves[moveIndex] == move)
            break;
    }

    if (moveIndex == MAX_MON_MOVES)
        return;

    if (gBattleMons[attacker].pp[moveIndex] != 0)
    {
        if (targetAbility == ABILITY_PRESSURE)
            gBattleMons[attacker].pp[moveIndex]--;
            gBattleMons[attacker].pp[moveIndex]--;
        if (GetBattlerHoldEffect(target, TRUE) == HOLD_EFFECT_SPECTRAL_IDOL)
            gBattleMons[attacker].pp[moveIndex]--;
        if (gBattleMons[attacker].status1 & STATUS1_PANIC)
            gBattleMons[attacker].pp[moveIndex]--;
        if (targetAbility != ABILITY_SHUNYONG && gBattleResults.battleTurnCounter % 2 != 0)
            gBattleMons[attacker].pp[moveIndex]--;
    }

    if (MOVE_IS_PERMANENT(attacker, moveIndex))
    {
        BtlController_EmitSetMonData(attacker, BUFFER_A, REQUEST_PPMOVE1_BATTLE + moveIndex, 0, 1, &gBattleMons[attacker].pp[moveIndex]);
        MarkBattlerForControllerExec(attacker);
    }
}

void PressurePPLoseOnUsingImprison(u8 attacker)
{
    int i, j;
    int imprisonPos = MAX_MON_MOVES;
    u8 atkSide = GetBattlerSide(attacker);

    for (i = 0; i < gBattlersCount; i++)
    {
        if (atkSide != GetBattlerSide(i) && (GetBattlerAbility(i) == ABILITY_PRESSURE
                                          || GetBattlerHoldEffect(i, TRUE) == HOLD_EFFECT_SPECTRAL_IDOL
                                          || (gBattleMons[attacker].status1 & STATUS1_PANIC)
                                          || (GetBattlerAbility(i) == ABILITY_SHUNYONG && gBattleResults.battleTurnCounter % 2 != 0)))
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMons[attacker].moves[j] == MOVE_IMPRISON)
                    break;
            }
            if (j != MAX_MON_MOVES)
            {
                imprisonPos = j;
                if (gBattleMons[attacker].pp[j] != 0)
                {
                    if (GetBattlerAbility(i) == ABILITY_PRESSURE)
                    {
                        gBattleMons[attacker].pp[j]--;
                        gBattleMons[attacker].pp[j]--;
                    }
                    if (GetBattlerHoldEffect(i, TRUE) == HOLD_EFFECT_SPECTRAL_IDOL)
                    {
                        gBattleMons[attacker].pp[j]--;
                    }
                    if (gBattleMons[attacker].status1 & STATUS1_PANIC)
                    {
                        gBattleMons[attacker].pp[j]--;
                    }
                    if (GetBattlerAbility(i) == ABILITY_SHUNYONG && gBattleResults.battleTurnCounter % 2 != 0)
                    {
                        gBattleMons[attacker].pp[j]--;
                    }
                }
            }
        }
    }

    if (imprisonPos != MAX_MON_MOVES && MOVE_IS_PERMANENT(attacker, imprisonPos))
    {
        BtlController_EmitSetMonData(attacker, BUFFER_A, REQUEST_PPMOVE1_BATTLE + imprisonPos, 0, 1, &gBattleMons[attacker].pp[imprisonPos]);
        MarkBattlerForControllerExec(attacker);
    }
}

void PressurePPLoseOnUsingPerishSong(u8 attacker)
{
    int i, j;
    int perishSongPos = MAX_MON_MOVES;

    for (i = 0; i < gBattlersCount; i++)
    {
        if ((GetBattlerHoldEffect(i, TRUE) == HOLD_EFFECT_SPECTRAL_IDOL
        || (gBattleMons[attacker].status1 & STATUS1_PANIC)
        || (GetBattlerAbility(i) == ABILITY_PRESSURE)
        || (GetBattlerAbility(i) == ABILITY_SHUNYONG
        && gBattleResults.battleTurnCounter % 2 != 0)) && i != attacker)
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMons[attacker].moves[j] == MOVE_PERISH_SONG)
                    break;
            }
            if (j != MAX_MON_MOVES)
            {
                perishSongPos = j;
                if (gBattleMons[attacker].pp[j] != 0)
                    if (GetBattlerAbility(i) == ABILITY_PRESSURE && i != attacker)
                        gBattleMons[attacker].pp[j]--;
                        gBattleMons[attacker].pp[j]--;
                    if (GetBattlerAbility(i) == ABILITY_SHUNYONG && i != attacker && gBattleResults.battleTurnCounter % 2 != 0)
                        gBattleMons[attacker].pp[j]--;
                    if (GetBattlerHoldEffect(i, TRUE) == HOLD_EFFECT_SPECTRAL_IDOL && i != attacker)
                        gBattleMons[attacker].pp[j]--;
                    if (gBattleMons[attacker].status1 & STATUS1_PANIC)
                        gBattleMons[attacker].pp[j]--;
            }
        }
    }

    if (perishSongPos != MAX_MON_MOVES && MOVE_IS_PERMANENT(attacker, perishSongPos))
    {
        BtlController_EmitSetMonData(attacker, BUFFER_A, REQUEST_PPMOVE1_BATTLE + perishSongPos, 0, 1, &gBattleMons[attacker].pp[perishSongPos]);
        MarkBattlerForControllerExec(attacker);
    }
}

// Unused
static void MarkAllBattlersForControllerExec(void)
{
    int i;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        for (i = 0; i < gBattlersCount; i++)
            gBattleControllerExecFlags |= gBitTable[i] << (32 - MAX_BATTLERS_COUNT);
    }
    else
    {
        for (i = 0; i < gBattlersCount; i++)
            gBattleControllerExecFlags |= gBitTable[i];
    }
}

bool32 IsBattlerMarkedForControllerExec(u32 battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        return (gBattleControllerExecFlags & (gBitTable[battler] << 0x1C)) != 0;
    else
        return (gBattleControllerExecFlags & (gBitTable[battler])) != 0;
}

void MarkBattlerForControllerExec(u32 battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        gBattleControllerExecFlags |= gBitTable[battler] << (32 - MAX_BATTLERS_COUNT);
    else
        gBattleControllerExecFlags |= gBitTable[battler];
}

void MarkBattlerReceivedLinkData(u32 battler)
{
    s32 i;

    for (i = 0; i < GetLinkPlayerCount(); i++)
        gBattleControllerExecFlags |= gBitTable[battler] << (i << 2);

    gBattleControllerExecFlags &= ~((1 << 28) << battler);
}

void CancelMultiTurnMoves(u32 battler)
{
    u8 i;
    gBattleMons[battler].status2 &= ~(STATUS2_MULTIPLETURNS);
    gBattleMons[battler].status2 &= ~(STATUS2_LOCK_CONFUSE);
    gBattleMons[battler].status2 &= ~(STATUS2_UPROAR);
    gBattleMons[battler].status2 &= ~(STATUS2_BIDE);

    // Clear battler's semi-invulnerable bits if they are not held by Sky Drop.
    if (!(gStatuses3[battler] & STATUS3_SKY_DROPPED))
        gStatuses3[battler] &= ~(STATUS3_SEMI_INVULNERABLE);

    // Check to see if this Pokemon was in the middle of using Sky Drop. If so, release the target.
    if (gBattleStruct->skyDropTargets[battler] != 0xFF && !(gStatuses3[battler] & STATUS3_SKY_DROPPED))
    {
        // Get the target's battler id
        u8 otherSkyDropper = gBattleStruct->skyDropTargets[battler];

        // Clears sky_dropped and on_air statuses
        gStatuses3[otherSkyDropper] &= ~(STATUS3_SKY_DROPPED | STATUS3_ON_AIR);

        // Makes both attacker and target's sprites visible
        gSprites[gBattlerSpriteIds[battler]].invisible = FALSE;
        gSprites[gBattlerSpriteIds[otherSkyDropper]].invisible = FALSE;

        // If target was sky dropped in the middle of Outrage/Thrash/Petal Dance,
        // confuse them upon release and display "confused by fatigue" message & animation.
        // Don't do this if this CancelMultiTurnMoves is caused by falling asleep via Yawn.
        if (gBattleMons[otherSkyDropper].status2 & STATUS2_LOCK_CONFUSE && gBattleStruct->turnEffectsTracker != 24)
        {
            gBattleMons[otherSkyDropper].status2 &= ~(STATUS2_LOCK_CONFUSE);

            // If the target can be confused, confuse them.
            // Don't use CanBeConfused, can cause issues in edge cases.
            if (!(GetBattlerAbility(otherSkyDropper) == ABILITY_OWN_TEMPO || gBattleMons[otherSkyDropper].status2 & STATUS2_CONFUSION))
            {
                // Set confused status
                gBattleMons[otherSkyDropper].status2 |= STATUS2_CONFUSION_TURN(((Random()) % 4) + 2);

                // If this CancelMultiTurnMoves is occuring due to attackcanceller
                if (gBattlescriptCurrInstr[0] == 0x0)
                {
                    gBattleStruct->skyDropTargets[battler] = 0xFE;
                }
                // If this CancelMultiTurnMoves is occuring due to VARIOUS_GRAVITY_ON_AIRBORNE_MONS
                // Reapplying STATUS3_SKY_DROPPED allows for avoiding unecessary messages when Gravity is applied to the target.
                else if (gBattlescriptCurrInstr[0] == 0x76 && gBattlescriptCurrInstr[2] == 76)
                {
                    gBattleStruct->skyDropTargets[battler] = 0xFE;
                    gStatuses3[otherSkyDropper] |= STATUS3_SKY_DROPPED;
                }
                // If this CancelMultiTurnMoves is occuring due to cancelmultiturnmoves script
                else if (gBattlescriptCurrInstr[0] == 0x76 && gBattlescriptCurrInstr[2] == 0)
                {
                    gBattlerAttacker = otherSkyDropper;
                    gBattlescriptCurrInstr = BattleScript_ThrashConfuses - 3;
                }
                // If this CancelMultiTurnMoves is occuring due to receiving Sleep/Freeze status
                else if (gBattleScripting.moveEffect <= PRIMARY_STATUS_MOVE_EFFECT)
                {
                    gBattlerAttacker = otherSkyDropper;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_ThrashConfuses - 1;
                }
            }
        }

        // Clear skyDropTargets data, unless this CancelMultiTurnMoves is caused by Yawn, attackcanceler, or VARIOUS_GRAVITY_ON_AIRBORNE_MONS
        if (!(gBattleMons[otherSkyDropper].status2 & STATUS2_LOCK_CONFUSE) && gBattleStruct->skyDropTargets[battler] < 4)
        {
            gBattleStruct->skyDropTargets[battler] = 0xFF;
            gBattleStruct->skyDropTargets[otherSkyDropper] = 0xFF;
        }
    }

    gDisableStructs[battler].rolloutTimer = 0;
    gDisableStructs[battler].furyCutterCounter = 0;
}

bool32 WasUnableToUseMove(u32 battler)
{
    if (gProtectStructs[battler].prlzImmobility || gProtectStructs[battler].usedImprisonedMove || gProtectStructs[battler].loveImmobility || gProtectStructs[battler].usedDisabledMove || gProtectStructs[battler].usedTauntedMove || gProtectStructs[battler].usedGravityPreventedMove || gProtectStructs[battler].usedHealBlockedMove || gProtectStructs[battler].flag2Unknown || gProtectStructs[battler].flinchImmobility || gProtectStructs[battler].confusionSelfDmg || gProtectStructs[battler].powderSelfDmg || gProtectStructs[battler].usedThroatChopPreventedMove)
        return TRUE;
    else
        return FALSE;
}

void PrepareStringBattle(u16 stringId, u32 battler)
{
    u32 targetSide = GetBattlerSide(gBattlerTarget);
    u16 battlerAbility = GetBattlerAbility(battler);
    u16 targetAbility = GetBattlerAbility(gBattlerTarget);
    // Support for Contrary ability.
    // If a move attempted to raise stat - print "won't increase".
    // If a move attempted to lower stat - print "won't decrease".
    if (stringId == STRINGID_STATSWONTDECREASE && !(gBattleScripting.statChanger & STAT_BUFF_NEGATIVE))
        stringId = STRINGID_STATSWONTINCREASE;
    else if (stringId == STRINGID_STATSWONTINCREASE && gBattleScripting.statChanger & STAT_BUFF_NEGATIVE)
        stringId = STRINGID_STATSWONTDECREASE;

    else if (stringId == STRINGID_STATSWONTDECREASE2 && battlerAbility == ABILITY_CONTRARY)
        stringId = STRINGID_STATSWONTINCREASE2;
    else if (stringId == STRINGID_STATSWONTINCREASE2 && battlerAbility == ABILITY_CONTRARY)
        stringId = STRINGID_STATSWONTDECREASE2;

    // Check Defiant and Competitive stat raise whenever a stat is lowered.
    else if ((stringId == STRINGID_DEFENDERSSTATFELL || stringId == STRINGID_PKMNCUTSSPEEDWITH || stringId == STRINGID_PKMNCUTSATTACKWITH || stringId == STRINGID_PKMNCUTSSPATTACKWITH || stringId == STRINGID_PKMNCUTSDEFENCEWITH || stringId == STRINGID_PKMNCUTSSPDEFENCEWITH)
              && ((targetAbility == ABILITY_DEFIANT && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                 || (targetAbility == ABILITY_COMPETITIVE && CompareStat(gBattlerTarget, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN)))
              && ((gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != gBattlerTarget) || gBattleScripting.stickyWebStatDrop == 1)
              && !(gBattleScripting.stickyWebStatDrop == 1 && gSideTimers[targetSide].stickyWebBattlerSide == targetSide)) // Sticky Web must have been set by the foe
    {
        gBattleScripting.stickyWebStatDrop = 0;
        gBattlerAbility = gBattlerTarget;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_AbilityRaisesDefenderStat;
        if (targetAbility == ABILITY_DEFIANT)
            SET_STATCHANGER(STAT_ATK, 2, FALSE);
        else
            SET_STATCHANGER(STAT_SPATK, 2, FALSE);
    }
    else if ((stringId == STRINGID_PKMNCUTSATTACKWITH || stringId == STRINGID_PKMNCUTSSPATTACKWITH || stringId == STRINGID_PKMNCUTSDEFENCEWITH || stringId == STRINGID_PKMNCUTSSPDEFENCEWITH) && targetAbility == ABILITY_RATTLED && CompareStat(gBattlerTarget, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
    {
        gBattlerAbility = gBattlerTarget;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_AbilityRaisesDefenderStat;
        SET_STATCHANGER(STAT_SPEED, 2, FALSE);
    }
    // Signal for the trainer slide-in system.
    if ((stringId == STRINGID_ITDOESNTAFFECT || stringId == STRINGID_PKMNWASNTAFFECTED || stringId == STRINGID_PKMNUNAFFECTED) && GetBattlerSide(gBattlerTarget) == B_SIDE_OPPONENT && gBattleStruct->trainerSlidePlayerMonUnaffectedMsgState != 2)
        gBattleStruct->trainerSlidePlayerMonUnaffectedMsgState = 1;

    BtlController_EmitPrintString(battler, BUFFER_A, stringId);
    MarkBattlerForControllerExec(battler);
}

void ResetSentPokesToOpponentValue(void)
{
    s32 i;
    u32 bits = 0;

    gSentPokesToOpponent[0] = 0;
    gSentPokesToOpponent[1] = 0;

    for (i = 0; i < gBattlersCount; i += 2)
        bits |= gBitTable[gBattlerPartyIndexes[i]];

    for (i = 1; i < gBattlersCount; i += 2)
        gSentPokesToOpponent[(i & BIT_FLANK) >> 1] = bits;
}

void OpponentSwitchInResetSentPokesToOpponentValue(u32 battler)
{
    s32 i = 0;
    u32 bits = 0;

    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
    {
        u8 flank = ((battler & BIT_FLANK) >> 1);
        gSentPokesToOpponent[flank] = 0;

        for (i = 0; i < gBattlersCount; i += 2)
        {
            if (!(gAbsentBattlerFlags & gBitTable[i]))
                bits |= gBitTable[gBattlerPartyIndexes[i]];
        }
        gSentPokesToOpponent[flank] = bits;
    }
}

void UpdateSentPokesToOpponentValue(u32 battler)
{
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
    {
        OpponentSwitchInResetSentPokesToOpponentValue(battler);
    }
    else
    {
        s32 i;
        for (i = 1; i < gBattlersCount; i++)
            gSentPokesToOpponent[(i & BIT_FLANK) >> 1] |= gBitTable[gBattlerPartyIndexes[battler]];
    }
}

void BattleScriptPush(const u8 *bsPtr)
{
    gBattleResources->battleScriptsStack->ptr[gBattleResources->battleScriptsStack->size++] = bsPtr;
}

void BattleScriptPushCursor(void)
{
    gBattleResources->battleScriptsStack->ptr[gBattleResources->battleScriptsStack->size++] = gBattlescriptCurrInstr;
}

void BattleScriptPop(void)
{
    if (gBattleResources->battleScriptsStack->size != 0)
        gBattlescriptCurrInstr = gBattleResources->battleScriptsStack->ptr[--gBattleResources->battleScriptsStack->size];
}

static bool32 IsGravityPreventingMove(u32 move)
{
    if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
        return FALSE;

    if (IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_PSYCHIC))
        return FALSE;

    return gBattleMoves[move].gravityBanned;
}

bool32 IsHealBlockPreventingMove(u32 battler, u32 move)
{
    if (!(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
        return FALSE;

    switch (gBattleMoves[move].effect)
    {
#if B_HEAL_BLOCKING >= GEN_6
    case EFFECT_ABSORB:
    case EFFECT_HEART_CARVE:
    case EFFECT_SPIRIT_AWAY:
    case EFFECT_STRENGTH_SAP:
    case EFFECT_POWER_DRAIN:
    case EFFECT_DREAM_EATER:
#endif
    case EFFECT_MORNING_SUN:
    case EFFECT_SYNTHESIS:
    case EFFECT_COLD_MEND:
    case EFFECT_MOONLIGHT:
    case EFFECT_RESTORE_HP:
    case EFFECT_HEAL_ORDER:
    case EFFECT_BLAZING_SOUL:
    case EFFECT_CRITICAL_REPAIR:
    case EFFECT_REST:
    case EFFECT_ROOST:
    case EFFECT_HEALING_WISH:
    case EFFECT_WISH:
    case EFFECT_HEAL_PULSE:
    case EFFECT_JUNGLE_HEALING:
    case EFFECT_DRAINING_KISS:
    case EFFECT_BLACK_BUFFET:
    case EFFECT_LONE_SHARK:
    case EFFECT_VENOM_DRAIN:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 IsBelchPreventingMove(u32 battler, u32 move)
{
    if (gBattleMoves[move].effect != EFFECT_BELCH)
        return FALSE;

    return !(gBattleStruct->ateBerry[battler & BIT_SIDE] & gBitTable[gBattlerPartyIndexes[battler]]);
}

u32 TrySetCantSelectMoveBattleScript(u32 battler)
{
    u32 limitations = 0;
    u8 moveId = gBattleResources->bufferB[battler][2] & ~(RET_MEGA_EVOLUTION | RET_ULTRA_BURST);
    u32 move = gBattleMons[battler].moves[moveId];
    u32 holdEffect = GetBattlerHoldEffect(battler, TRUE);
    u16 *choicedMove = &gBattleStruct->choicedMove[battler];

    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && gDisableStructs[battler].disabledMove == move && move != MOVE_NONE)
    {
        gBattleScripting.battler = battler;
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingDisabledMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingDisabledMove;
            limitations++;
        }
    }

    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && move == gLastMoves[battler] && move != MOVE_STRUGGLE && (gBattleMons[battler].status2 & STATUS2_TORMENT))
    {
        CancelMultiTurnMoves(battler);
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingTormentedMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingTormentedMove;
            limitations++;
        }
    }

    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && gDisableStructs[battler].tauntTimer != 0 && IS_MOVE_STATUS(move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveTauntInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveTaunt;
            limitations++;
        }
    }

    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && gDisableStructs[battler].throatChopTimer != 0 && gBattleMoves[move].soundMove)
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveThroatChopInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveThroatChop;
            limitations++;
        }
    }

    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && GetImprisonedMovesCount(battler, move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingImprisonedMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingImprisonedMove;
            limitations++;
        }
    }

    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && IsGravityPreventingMove(move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGravityInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGravity;
            limitations++;
        }
    }

    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && IsHealBlockPreventingMove(battler, move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveHealBlockInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveHealBlock;
            limitations++;
        }
    }

    if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && IsBelchPreventingMove(battler, move))
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedBelchInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedBelch;
            limitations++;
        }
    }

    if (move == MOVE_STUFF_CHEEKS && ItemId_GetPocket(gBattleMons[battler].item) != POCKET_BERRIES)
    {
        gCurrentMove = move;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedStuffCheeksInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedStuffCheeks;
            limitations++;
        }
    }

    if (gBattleMoves[move].cantUseTwice && move == gLastResultingMoves[battler])
    {
        gCurrentMove = move;
        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gCurrentMove);
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMove;
            limitations++;
        }
    }

    if (gBattleMoves[move].cantUseTwicePsySwap && move == gLastMoves[battler])
    {
        gCurrentMove = move;
        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gCurrentMove);
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMove;
            limitations++;
        }
    }

    if (gBattleMoves[move].cantUseTwiceBlooming && move == gLastResultingMoves[battler] && gBattleMons[battler].status1 & STATUS1_BLOOMING)
    {
        gCurrentMove = move;
        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gCurrentMove);
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMoveInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedCurrentMove;
            limitations++;
        }
    }

    gPotentialItemEffectBattler = battler;
    if (HOLD_EFFECT_CHOICE(holdEffect) && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
    {
        gCurrentMove = *choicedMove;
        gLastUsedItem = gBattleMons[battler].item;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveChoiceItemInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveChoiceItem;
            limitations++;
        }
    }
    
    if (((holdEffect == HOLD_EFFECT_ASSAULT_VEST) || (holdEffect == HOLD_EFFECT_BATTLE_HELM)) && IS_MOVE_STATUS(move) && move != MOVE_ME_FIRST)
    {
        gCurrentMove = move;
        gLastUsedItem = gBattleMons[battler].item;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveAssaultVestInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveAssaultVest;
            limitations++;
        }
    }

    if (gStatuses4[battler] & STATUS4_PHANTOM && IS_MOVE_STATUS(move) && move != MOVE_ME_FIRST)
    {
        gCurrentMove = move;
        gLastUsedItem = gBattleMons[battler].item;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveAssaultVestInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMovePhantom;
            limitations++;
        }
    }

    if ((GetBattlerAbility(battler) == ABILITY_GORILLA_TACTICS || GetBattlerAbility(battler) == ABILITY_ONE_WAY_TRIP) && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
    {
        gCurrentMove = *choicedMove;
        gLastUsedItem = gBattleMons[battler].item;
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGorillaTacticsInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedMoveGorillaTactics;
            limitations++;
        }
    }

    if (gBattleMons[battler].pp[moveId] == 0)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingMoveWithNoPP;
            limitations++;
        }
    }

    if (gBattleMoves[move].effect == EFFECT_PLACEHOLDER)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
        {
            gPalaceSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedPlaceholderInPalace;
            gProtectStructs[battler].palaceUnableToUseMove = TRUE;
        }
        else
        {
            gSelectionBattleScripts[battler] = BattleScript_SelectingNotAllowedPlaceholder;
            limitations++;
        }
    }

    return limitations;
}

u8 IsMoveUnusable(u32 battler, u16 move, u8 pp, u16 check)
{
    u8 unusableMoves = 0;
    
    u8 holdEffect = GetBattlerHoldEffect(battler, TRUE);
    u16 *choicedMove = &gBattleStruct->choicedMove[battler];
    
    // No move
    if (check & MOVE_LIMITATION_ZEROMOVE && move == MOVE_NONE)
        return TRUE;
    // No PP
    else if (check & MOVE_LIMITATION_PP && pp == 0)
        return TRUE;
    // Placeholder
    else if (check & MOVE_LIMITATION_PLACEHOLDER && gBattleMoves[move].effect == EFFECT_PLACEHOLDER)
        return TRUE;
    // Disable
    else if (check & MOVE_LIMITATION_DISABLED && move == gDisableStructs[battler].disabledMove)
        return TRUE;
    // Torment
    else if (check & MOVE_LIMITATION_TORMENTED && move == gLastMoves[battler] && gBattleMons[battler].status2 & STATUS2_TORMENT)
        return TRUE;
    // Taunt
    else if (check & MOVE_LIMITATION_TAUNT && gDisableStructs[battler].tauntTimer && IS_MOVE_STATUS(move))
        return TRUE;
    // Imprison
    else if (check & MOVE_LIMITATION_IMPRISON && GetImprisonedMovesCount(battler, move))
        return TRUE;
    // Encore
    else if (check & MOVE_LIMITATION_ENCORE && gDisableStructs[battler].encoreTimer && gDisableStructs[battler].encoredMove != move)
        return TRUE;
    // Choice Items
    else if (check & MOVE_LIMITATION_CHOICE_ITEM && HOLD_EFFECT_CHOICE(holdEffect) && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
        return TRUE;
    // Assault Vest
    else if (check & MOVE_LIMITATION_ASSAULT_VEST && ((holdEffect == HOLD_EFFECT_ASSAULT_VEST) || (holdEffect == HOLD_EFFECT_BATTLE_HELM) || (gStatuses4[battler] & STATUS4_PHANTOM)) && IS_MOVE_STATUS(move) && move != MOVE_ME_FIRST)
        return TRUE;
    // Gravity
    else if (check & MOVE_LIMITATION_GRAVITY && IsGravityPreventingMove(move))
        return TRUE;
    // Heal Block
    else if (check & MOVE_LIMITATION_HEAL_BLOCK && IsHealBlockPreventingMove(battler, move))
        return TRUE;
    // Belch
    else if (check & MOVE_LIMITATION_BELCH && IsBelchPreventingMove(battler, move))
        return TRUE;
    // Throat Chop
    else if (check & MOVE_LIMITATION_THROAT_CHOP && gDisableStructs[battler].throatChopTimer && gBattleMoves[move].soundMove)
        return TRUE;
    // Stuff Cheeks
    else if (check & MOVE_LIMITATION_STUFF_CHEEKS && move == MOVE_STUFF_CHEEKS && ItemId_GetPocket(gBattleMons[battler].item) != POCKET_BERRIES)
        return TRUE;
    // Gorilla Tactics
    else if (check & MOVE_LIMITATION_CHOICE_ITEM && GetBattlerAbility(battler) == ABILITY_GORILLA_TACTICS && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
        return TRUE;
    // One Way Trip
    else if (check & MOVE_LIMITATION_CHOICE_ITEM && GetBattlerAbility(battler) == ABILITY_ONE_WAY_TRIP && *choicedMove != MOVE_NONE && *choicedMove != MOVE_UNAVAILABLE && *choicedMove != move)
        return TRUE;
    else if (check & MOVE_LIMITATION_CANT_USE_TWICE && ((gBattleMoves[move].cantUseTwice && move == gLastResultingMoves[battler]) || (gBattleMoves[move].cantUseTwicePsySwap && move == gLastMoves[battler])))
        return TRUE;
    else if (check & MOVE_LIMITATION_BLOOMING && gBattleMoves[move].cantUseTwiceBlooming && move == gLastResultingMoves[battler] && gBattleMons[battler].status1 & STATUS1_BLOOMING)
        return TRUE;
    return 0;
}

u8 CheckMoveLimitations(u32 battler, u8 unusableMoves, u16 check)
{
    u32 i;
    gPotentialItemEffectBattler = battler;
    
    for (i = 0; i < MAX_MON_MOVES; i++) {
        if (IsMoveUnusable(battler, gBattleMons[battler].moves[i], gBattleMons[battler].pp[i], check))
            unusableMoves |= gBitTable[i];
    }
    
    return unusableMoves;
}

#define ALL_MOVES_MASK ((1 << MAX_MON_MOVES) - 1)
bool32 AreAllMovesUnusable(u32 battler)
{
    u8 unusable = CheckMoveLimitations(battler, 0, MOVE_LIMITATIONS_ALL);

    if (unusable == ALL_MOVES_MASK) // All moves are unusable.
    {
        gProtectStructs[battler].noValidMoves = TRUE;
        gSelectionBattleScripts[battler] = BattleScript_NoMovesLeft;
    }
    else
    {
        gProtectStructs[battler].noValidMoves = FALSE;
    }

    return (unusable == ALL_MOVES_MASK);
}

u8 GetImprisonedMovesCount(u32 battler, u16 move)
{
    s32 i;
    u8 imprisonedMoves = 0;
    u32 battlerSide = GetBattlerSide(battler);

    for (i = 0; i < gBattlersCount; i++)
    {
        if (battlerSide != GetBattlerSide(i) && gStatuses3[i] & STATUS3_IMPRISONED_OTHERS)
        {
            s32 j;
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (move == gBattleMons[i].moves[j])
                    break;
            }
            if (j < MAX_MON_MOVES)
                imprisonedMoves++;
        }
    }

    return imprisonedMoves;
}

u32 GetBattlerFriendshipScore(u32 battler)
{
    u8 side = GetBattlerSide(battler);
    struct Pokemon *party = GetSideParty(side);
    u16 species = GetMonData(&party[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

    if (side != B_SIDE_PLAYER)
        return FRIENDSHIP_NONE;
    else if (gSpeciesInfo[species].flags & SPECIES_FLAG_MEGA_EVOLUTION || (gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_FRONTIER | BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK | BATTLE_TYPE_SECRET_BASE)))
        return FRIENDSHIP_NONE;

    return GetMonFriendshipScore(&party[gBattlerPartyIndexes[battler]]);
}

static void TryToRevertMimicry(void)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (GetBattlerAbility(i) == ABILITY_MIMICRY)
            RESTORE_BATTLER_TYPE(i);
    }
}

enum
{
    ENDTURN_ORDER,
    ENDTURN_REFLECT,
    ENDTURN_LIGHT_SCREEN,
    ENDTURN_AURORA_VEIL,
    ENDTURN_GOOGOO_SCREEN,
    ENDTURN_MIST,
    ENDTURN_LUCKY_CHANT,
    ENDTURN_SAFEGUARD,
    ENDTURN_TAILWIND,
    ENDTURN_WISH,
    ENDTURN_RAIN,
    ENDTURN_SANDSTORM,
    ENDTURN_SUN,
    ENDTURN_HAIL,
    ENDTURN_SNOW,
    ENDTURN_GRAVITY,
    ENDTURN_WATER_SPORT,
    ENDTURN_MUD_SPORT,
    ENDTURN_TRICK_ROOM,
    ENDTURN_WONDER_ROOM,
    ENDTURN_MAGIC_ROOM,
    ENDTURN_ELECTRIC_TERRAIN,
    ENDTURN_MISTY_TERRAIN,
    ENDTURN_GRASSY_TERRAIN,
    ENDTURN_PSYCHIC_TERRAIN,
    ENDTURN_ION_DELUGE,
    ENDTURN_RETALIATE,
    ENDTURN_WEATHER_FORM,
    ENDTURN_STATUS_HEAL,
    ENDTURN_SILENCE,
    ENDTURN_HEAL_ORDER,
    ENDTURN_INVERSE_ROOM,
    ENDTURN_FIELD_COUNT,
};

static bool32 EndTurnTerrain(u32 terrainFlag, u32 stringTableId)
{
    if (gFieldStatuses & terrainFlag)
    {
        if (terrainFlag & STATUS_FIELD_GRASSY_TERRAIN)
            BattleScriptExecute(BattleScript_GrassyTerrainHeals);
        if (!(gFieldStatuses & STATUS_FIELD_TERRAIN_PERMANENT) && --gFieldTimers.terrainTimer == 0)
        {
            if (!IsAbilityOnField(ABILITY_ENDLESS))
            {
                gFieldStatuses &= ~terrainFlag;
                gBattleCommunication[MULTISTRING_CHOOSER] = stringTableId;
                if (terrainFlag & STATUS_FIELD_GRASSY_TERRAIN)
                    BattleScriptExecute(BattleScript_GrassyTerrainEnds);
                else
                    BattleScriptExecute(BattleScript_TerrainEnds);
                return TRUE;
            }
            else
            {
                gFieldTimers.terrainTimer = 1;
            }
        }
    }
    return FALSE;
}

u8 DoFieldEndTurnEffects(void)
{
    u8 effect = 0;

    for (gBattlerAttacker = 0; gBattlerAttacker < gBattlersCount && gAbsentBattlerFlags & gBitTable[gBattlerAttacker]; gBattlerAttacker++)
    {
    }
    for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount && gAbsentBattlerFlags & gBitTable[gBattlerTarget]; gBattlerTarget++)
    {
    }

    do
    {
        s32 i;
        u8 side;

        switch (gBattleStruct->turnCountersTracker)
        {
        case ENDTURN_ORDER:
            for (i = 0; i < gBattlersCount - 1; i++)
            {
                s32 j;
                for (j = i + 1; j < gBattlersCount; j++)
                {
                    if (!(gProtectStructs[i].quash && gProtectStructs[j].quash)
                            && GetWhichBattlerFaster(gBattlerByTurnOrder[i], gBattlerByTurnOrder[j], FALSE) == 0)
                        SwapTurnOrder(i, j);
                }
            }

            gBattleStruct->turnCountersTracker++;
            gBattleStruct->turnSideTracker = 0;
            // fall through
        case ENDTURN_REFLECT:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].reflectBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_REFLECT)
                {
                    if (--gSideTimers[side].reflectTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_REFLECT;
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_REFLECT);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (effect == 0)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_LIGHT_SCREEN:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].lightscreenBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_LIGHTSCREEN)
                {
                    if (--gSideTimers[side].lightscreenTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_LIGHTSCREEN;
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        gBattleCommunication[MULTISTRING_CHOOSER] = side;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_LIGHT_SCREEN);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (effect == 0)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_AURORA_VEIL:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].auroraVeilBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_AURORA_VEIL)
                {
                    if (--gSideTimers[side].auroraVeilTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_AURORA_VEIL;
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        gBattleCommunication[MULTISTRING_CHOOSER] = side;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_AURORA_VEIL);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_GOOGOO_SCREEN:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].googooScreenBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_GOOGOO_SCREEN)
                {
                    if (--gSideTimers[side].googooScreenTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_GOOGOO_SCREEN;
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        gBattleCommunication[MULTISTRING_CHOOSER] = side;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_BABY_BLUES);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_SILENCE:
            while (gBattleStruct->turnSideTracker < 15)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].silenceTimerBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_SILENCE)
                {
                    if (--gSideTimers[side].silenceTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_SILENCE;
                        gBattleCommunication[MULTISTRING_CHOOSER] = side;
                        BattleScriptExecute(BattleScript_SilenceActivatesNonArcane);
                    }
                    else
                    {
                        BattleScriptExecute(BattleScript_SilenceContinues);
                    }
                    effect++;
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_HEAL_ORDER:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].healOrderTimerBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_HEAL_ORDER)
                {            
                    if (--gSideTimers[side].healOrderTimer == 0)
                    {
                        if ((!(BATTLER_MAX_HP(gBattlerAttacker)))
                        && gBattleMons[gBattlerAttacker].hp != 0
                        && (!(gStatuses3[gBattlerAttacker] & STATUS3_HEAL_BLOCK)))
                        {
                            BattleScriptExecute(BattleScript_HealOrderActivates);
                            effect++;
                        }
                        gSideStatuses[side] &= ~SIDE_STATUS_HEAL_ORDER;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_MIST:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].mistBattlerId;
                if (gSideTimers[side].mistTimer != 0 && --gSideTimers[side].mistTimer == 0)
                {
                    gSideStatuses[side] &= ~SIDE_STATUS_MIST;
                    BattleScriptExecute(BattleScript_SideStatusWoreOff);
                    gBattleCommunication[MULTISTRING_CHOOSER] = side;
                    PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_MIST);
                    effect++;
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (effect == 0)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_SAFEGUARD:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].safeguardBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_SAFEGUARD)
                {
                    if (--gSideTimers[side].safeguardTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_SAFEGUARD;
                        BattleScriptExecute(BattleScript_SafeguardEnds);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (effect == 0)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_LUCKY_CHANT:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].luckyChantBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_LUCKY_CHANT)
                {
                    if (--gSideTimers[side].luckyChantTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_LUCKY_CHANT;
                        BattleScriptExecute(BattleScript_LuckyChantEnds);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_TAILWIND:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gBattlerAttacker = gSideTimers[side].tailwindBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_TAILWIND)
                {
                    if (--gSideTimers[side].tailwindTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_TAILWIND;
                        BattleScriptExecute(BattleScript_TailwindEnds);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_WISH:
            while (gBattleStruct->turnSideTracker < gBattlersCount)
            {
                u32 battler = gBattlerByTurnOrder[gBattleStruct->turnSideTracker];
                if (gWishFutureKnock.wishCounter[battler] != 0 && --gWishFutureKnock.wishCounter[battler] == 0 && gBattleMons[battler].hp != 0)
                {
                    gBattlerTarget = battler;
                    BattleScriptExecute(BattleScript_WishComesTrue);
                    effect++;
                }
                gBattleStruct->turnSideTracker++;
                if (effect != 0)
                    break;
            }
            if (effect == 0)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_RAIN:
            if (gBattleWeather & B_WEATHER_RAIN)
            {
                if (!(gBattleWeather & B_WEATHER_RAIN_PERMANENT) && !(gBattleWeather & B_WEATHER_RAIN_PRIMAL))
                {
                    if (--gWishFutureKnock.weatherDuration == 0)
                    {
                        if (!IsAbilityOnField(ABILITY_ENDLESS))
                        {
                            gBattleWeather &= ~B_WEATHER_RAIN_TEMPORARY;
                            gBattleWeather &= ~B_WEATHER_RAIN_DOWNPOUR;
                            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_RAIN_STOPPED;
                        }
                        else
                        {
                            gWishFutureKnock.weatherDuration = 1;
                            if (gBattleWeather & B_WEATHER_RAIN_DOWNPOUR)
                                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_DOWNPOUR_CONTINUES;
                            else
                                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_RAIN_CONTINUES;
                        }
                    }
                    else if (gBattleWeather & B_WEATHER_RAIN_DOWNPOUR)
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_DOWNPOUR_CONTINUES;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_RAIN_CONTINUES;
                }
                else if (gBattleWeather & B_WEATHER_RAIN_DOWNPOUR)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_DOWNPOUR_CONTINUES;
                }
                else
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_RAIN_CONTINUES;
                }

                BattleScriptExecute(BattleScript_RainContinuesOrEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_SANDSTORM:
            if (gBattleWeather & B_WEATHER_SANDSTORM)
            {
                if (!(gBattleWeather & B_WEATHER_SANDSTORM_PERMANENT) && --gWishFutureKnock.weatherDuration == 0)
                {
                    if (!IsAbilityOnField(ABILITY_ENDLESS))
                    {
                        gBattleWeather &= ~B_WEATHER_SANDSTORM_TEMPORARY;
                        gBattlescriptCurrInstr = BattleScript_SandStormHailSnowEnds;
                    }
                    else
                    {
                        gWishFutureKnock.weatherDuration = 1;
                        gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                    }
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                }

                gBattleScripting.animArg1 = B_ANIM_SANDSTORM_CONTINUES;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SANDSTORM;
                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_SUN:
            if (gBattleWeather & B_WEATHER_SUN)
            {
                if (!(gBattleWeather & B_WEATHER_SUN_PERMANENT) && !(gBattleWeather & B_WEATHER_SUN_PRIMAL) && --gWishFutureKnock.weatherDuration == 0)
                {
                    if (!IsAbilityOnField(ABILITY_ENDLESS))
                    {
                        gBattleWeather &= ~B_WEATHER_SUN_TEMPORARY;
                        gBattlescriptCurrInstr = BattleScript_SunlightFaded;
                    }
                    else
                    {
                        gWishFutureKnock.weatherDuration = 1;
                        gBattlescriptCurrInstr = BattleScript_SunlightContinues;
                    }
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_SunlightContinues;
                }

                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_HAIL:
            if (gBattleWeather & B_WEATHER_HAIL)
            {
                if (!(gBattleWeather & B_WEATHER_HAIL_PERMANENT) && --gWishFutureKnock.weatherDuration == 0)
                {
                    if (!IsAbilityOnField(ABILITY_ENDLESS))
                    {
                        gBattleWeather &= ~B_WEATHER_HAIL_TEMPORARY;
                        gBattlescriptCurrInstr = BattleScript_SandStormHailSnowEnds;
                    }
                    else
                    {
                        gWishFutureKnock.weatherDuration = 1;
                        gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                    }
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                }

                gBattleScripting.animArg1 = B_ANIM_HAIL_CONTINUES;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_HAIL;
                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_SNOW:
            if (gBattleWeather & B_WEATHER_SNOW)
            {
                if (!(gBattleWeather & B_WEATHER_SNOW_PERMANENT) && --gWishFutureKnock.weatherDuration == 0)
                {
                    if (!IsAbilityOnField(ABILITY_ENDLESS))
                    {
                        gBattleWeather &= ~B_WEATHER_SNOW_TEMPORARY;
                        gBattlescriptCurrInstr = BattleScript_SandStormHailSnowEnds;
                    }
                    else
                    {
                        gWishFutureKnock.weatherDuration = 1;
                        gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                    }
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                }

                gBattleScripting.animArg1 = B_ANIM_SNOW_CONTINUES;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SNOW;
                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_TRICK_ROOM:
            if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM && --gFieldTimers.trickRoomTimer == 0)
            {
                if (!IsAbilityOnField(ABILITY_ENDLESS))
                {
                    gFieldStatuses &= ~STATUS_FIELD_TRICK_ROOM;
                    BattleScriptExecute(BattleScript_TrickRoomEnds);
                    effect++;
                }
                else
                {
                    gFieldTimers.trickRoomTimer = 1;
                }
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_WONDER_ROOM:
            if (gFieldStatuses & STATUS_FIELD_WONDER_ROOM && --gFieldTimers.wonderRoomTimer == 0)
            {

                if (!IsAbilityOnField(ABILITY_ENDLESS))
                {
                    gFieldStatuses &= ~STATUS_FIELD_WONDER_ROOM;
                    BattleScriptExecute(BattleScript_WonderRoomEnds);
                    effect++;
                }
                else
                {
                    gFieldTimers.wonderRoomTimer = 1;
                }
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_MAGIC_ROOM:
            if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM && --gFieldTimers.magicRoomTimer == 0)
            {
                if (!IsAbilityOnField(ABILITY_ENDLESS))
                {
                    gFieldStatuses &= ~STATUS_FIELD_MAGIC_ROOM;
                    BattleScriptExecute(BattleScript_MagicRoomEnds);
                    effect++;
                }
                else
                {
                    gFieldTimers.magicRoomTimer = 1;
                }
            }
            gBattleStruct->turnCountersTracker++;
            break;

        case ENDTURN_INVERSE_ROOM:
            if (gFieldStatuses & STATUS_FIELD_INVERSE_ROOM && --gFieldTimers.inverseRoomTimer == 0)
            {
                if (!IsAbilityOnField(ABILITY_ENDLESS))
                {
                    gFieldStatuses &= ~STATUS_FIELD_INVERSE_ROOM;
                    BattleScriptExecute(BattleScript_InverseRoomEnds);
                    effect++;
                }
                else
                {
                    gFieldTimers.inverseRoomTimer = 1;
                }
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_ELECTRIC_TERRAIN:
            effect = EndTurnTerrain(STATUS_FIELD_ELECTRIC_TERRAIN, B_MSG_TERRAIN_END_ELECTRIC);
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_MISTY_TERRAIN:
            effect = EndTurnTerrain(STATUS_FIELD_MISTY_TERRAIN, B_MSG_TERRAIN_END_MISTY);
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_GRASSY_TERRAIN:
            effect = EndTurnTerrain(STATUS_FIELD_GRASSY_TERRAIN, B_MSG_TERRAIN_END_GRASSY);
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_PSYCHIC_TERRAIN:
            effect = EndTurnTerrain(STATUS_FIELD_PSYCHIC_TERRAIN, B_MSG_TERRAIN_END_PSYCHIC);
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_WATER_SPORT:
#if B_SPORT_TURNS >= GEN_6
            if (gFieldStatuses & STATUS_FIELD_WATERSPORT && --gFieldTimers.waterSportTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_WATERSPORT;
                BattleScriptExecute(BattleScript_WaterSportEnds);
                effect++;
            }
#endif
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_MUD_SPORT:
#if B_SPORT_TURNS >= GEN_6
            if (gFieldStatuses & STATUS_FIELD_MUDSPORT && --gFieldTimers.mudSportTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_MUDSPORT;
                BattleScriptExecute(BattleScript_MudSportEnds);
                effect++;
            }
#endif
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_GRAVITY:
            if (gFieldStatuses & STATUS_FIELD_GRAVITY && --gFieldTimers.gravityTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_GRAVITY;
                BattleScriptExecute(BattleScript_GravityEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_ION_DELUGE:
            gFieldStatuses &= ~STATUS_FIELD_ION_DELUGE;
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_RETALIATE:
            if (gSideTimers[B_SIDE_PLAYER].retaliateTimer > 0)
                gSideTimers[B_SIDE_PLAYER].retaliateTimer--;
            if (gSideTimers[B_SIDE_OPPONENT].retaliateTimer > 0)
                gSideTimers[B_SIDE_OPPONENT].retaliateTimer--;
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_WEATHER_FORM:
            for (i = 0; i < gBattlersCount; i++)
            {
                if (AbilityBattleEffects(ABILITYEFFECT_ON_WEATHER, i, 0, 0, 0))
                {
                    effect++;
                    break;
                }
            }
            if (effect == 0)
                gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_STATUS_HEAL:
            for (gBattlerAttacker = 0; gBattlerAttacker < gBattlersCount; gBattlerAttacker++)
            {
#if B_AFFECTION_MECHANICS == TRUE
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER && GetBattlerFriendshipScore(gBattlerAttacker) >= FRIENDSHIP_150_TO_199 && (Random() % 100 < 20))
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                    BattleScriptExecute(BattleScript_AffectionBasedStatusHeal);
                    break;
                }
#endif
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_FIELD_COUNT:
            effect++;
            break;
        }
    } while (effect == 0);

    return (gBattleMainFunc != BattleTurnPassed);
}

enum
{
    ENDTURN_INGRAIN,
    ENDTURN_AQUA_RING,
    ENDTURN_ABILITIES,
    ENDTURN_ITEMS1,
    ENDTURN_LEECH_SEED,
    ENDTURN_POISON,
    ENDTURN_BAD_POISON,
    ENDTURN_BURN,
    ENDTURN_FROSTBITE,
    ENDTURN_NIGHTMARES,
    ENDTURN_CURSE,
    ENDTURN_WRAP,
    ENDTURN_OCTOLOCK,
    ENDTURN_UPROAR,
    ENDTURN_THRASH,
    ENDTURN_FLINCH,
    ENDTURN_DISABLE,
    ENDTURN_ENCORE,
    ENDTURN_MAGNET_RISE,
    ENDTURN_HEALBLOCK,
    ENDTURN_EMBARGO,
    ENDTURN_LOCK_ON,
    ENDTURN_CHARGE,
    ENDTURN_LASER_FOCUS,
    ENDTURN_TAUNT,
    ENDTURN_YAWN,
    ENDTURN_ITEMS2,
    ENDTURN_ORBS,
    ENDTURN_ROOST,
    ENDTURN_ELECTRIFY,
    ENDTURN_POWDER,
    ENDTURN_THROAT_CHOP,
    ENDTURN_PLASMA_FISTS,
    ENDTURN_CUD_CHEW,
    ENDTURN_SALT_CURE,
    ENDTURN_TICKED,
    ENDTURN_PANIC,
    ENDTURN_BLOOMING,
    ENDTURN_SPIDER_WEB,
    ENDTURN_GLAIVE_RUSH,
    ENDTURN_HEARTHWARM,
    ENDTURN_FAIRY_LOCK,
    ENDTURN_PUMPED_UP,
    ENDTURN_EMERGENCY_EXIT,
    ENDTURN_INFERNAL_REIGN,
    ENDTURN_SYRUP_BOMB,
    ENDTURN_DAYBREAK,
    ENDTURN_MAGIC_COAT,
    ENDTURN_ITEMS3,
    ENDTURN_BATTLER_COUNT
};

// Ingrain, Leech Seed, Strength Sap and Aqua Ring
s32 GetDrainedBigRootHp(u32 battler, s32 hp)
{
    if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_BIG_ROOT)
        hp *= 2;
    if (hp == 0)
        hp = 1;

    return hp * -1;
}

#define MAGIC_GUARD_CHECK                                                \
    if (ability == ABILITY_MAGIC_GUARD || ability == ABILITY_SUGAR_COAT) \
    {                                                                    \
        RecordAbilityBattle(battler, ability);                           \
        gBattleStruct->turnEffectsTracker++;                             \
        break;                                                           \
    }

#define TERU_CHARM_CHECK                                                 \
    if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_TERU_CHARM    \
    && gBattleMons[battler].species == SPECIES_CHIROBERRA)               \
    {                                                                    \
        RecordItemEffectBattle(battler, HOLD_EFFECT_TERU_CHARM);         \
        gBattleStruct->turnEffectsTracker++;                             \
        break;                                                           \
    }

u8 DoBattlerEndTurnEffects(void)
{
    u32 battler, ability, i, effect = 0;

    gHitMarker |= (HITMARKER_GRUDGE | HITMARKER_SKIP_DMG_TRACK);
    while (gBattleStruct->turnEffectsBattlerId < gBattlersCount && gBattleStruct->turnEffectsTracker <= ENDTURN_BATTLER_COUNT)
    {
        battler = gBattlerAttacker = gBattlerByTurnOrder[gBattleStruct->turnEffectsBattlerId];
        if (gAbsentBattlerFlags & gBitTable[battler])
        {
            gBattleStruct->turnEffectsBattlerId++;
            continue;
        }

        ability = GetBattlerAbility(battler);
        switch (gBattleStruct->turnEffectsTracker)
        {
        case ENDTURN_INGRAIN: // ingrain
            if ((gStatuses3[battler] & STATUS3_ROOTED) && !BATTLER_MAX_HP(battler) && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK) && gBattleMons[battler].hp != 0)
            {
                gBattleMoveDamage = GetDrainedBigRootHp(battler, gBattleMons[battler].maxHP / 16);
                BattleScriptExecute(BattleScript_IngrainTurnHeal);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_DAYBREAK:
            if (gDisableStructs[battler].daybreakCounter != 0)
            {
                gBattleMoveDamage = (gBattleMons[battler].maxHP / 10) * gDisableStructs[battler].daybreakCounter;
                PREPARE_STRING_BUFFER(gBattleTextBuff1, STRINGID_DAYBREAK);
                BattleScriptExecute(BattleScript_DaybreakTurnDamage);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_AQUA_RING: // aqua ring
            if ((gStatuses3[battler] & STATUS3_AQUA_RING) && !BATTLER_MAX_HP(battler) && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK) && gBattleMons[battler].hp != 0)
            {
                gBattleMoveDamage = GetDrainedBigRootHp(battler, ((gBattleMons[battler].maxHP - gBattleMons[battler].hp) / 5));
                BattleScriptExecute(BattleScript_AquaRingHeal);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_HEARTHWARM: // aqua ring
            if ((gStatuses4[battler] & STATUS4_HEARTHWARM) && !BATTLER_MAX_HP(battler) && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK) && gBattleMons[battler].hp != 0) 
            {
                gBattleMoveDamage = GetDrainedBigRootHp(battler, gBattleMons[battler].maxHP / 16);
                BattleScriptExecute(BattleScript_HearthwarmHeal);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_ABILITIES: // end turn abilities
            if (AbilityBattleEffects(ABILITYEFFECT_ENDTURN, battler, 0, 0, 0))
                effect++;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_ITEMS1: // item effects
            if (ItemBattleEffects(ITEMEFFECT_NORMAL, battler, FALSE))
                effect++;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_ITEMS2: // item effects again
            if (ItemBattleEffects(ITEMEFFECT_NORMAL, battler, TRUE))
                effect++;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_ITEMS3:  // berry effects
            if (ItemId_GetPocket(gBattleMons[battler].item) == POCKET_BERRIES
             || GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_RESTORE_HP)  // Edge case for Berry Juice
            {
                if (ItemBattleEffects(ITEMEFFECT_NORMAL, battler, FALSE))
                    effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_ORBS:
            if (IsBattlerAlive(battler) && ItemBattleEffects(ITEMEFFECT_ORBS, battler, FALSE))
                effect++;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_LEECH_SEED:  // leech seed
            if ((gStatuses3[battler] & STATUS3_LEECHSEED)
             && IsBattlerAlive(gStatuses3[battler] & STATUS3_LEECHSEED_BATTLER)
             && IsBattlerAlive(battler))
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;

                gBattlerTarget = gStatuses3[battler] & STATUS3_LEECHSEED_BATTLER; // Notice gBattlerTarget is actually the HP receiver.
                gBattlerAttacker = battler;
                gBattleScripting.animArg1 = gBattlerTarget;
                gBattleScripting.animArg2 = gBattlerAttacker;
                gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                gHitMarker |= HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE;
                BattleScriptExecute(BattleScript_LeechSeedTurnDrain);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_POISON: // poison
            if ((gBattleMons[battler].status1 & STATUS1_POISON) && gBattleMons[battler].hp != 0)
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;

                if (ability == ABILITY_POISON_HEAL)
                {
                    if (!BATTLER_MAX_HP(battler) && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
                    {
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                        BattleScriptExecute(BattleScript_PoisonHealActivates);
                        effect++;
                    }
                }
                else
                {
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    BattleScriptExecute(BattleScript_PoisonTurnDmg);
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_BAD_POISON: // toxic poison
            if ((gBattleMons[battler].status1 & STATUS1_TOXIC_POISON) && gBattleMons[battler].hp != 0)
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;

                if (ability == ABILITY_POISON_HEAL)
                {
                    if (!BATTLER_MAX_HP(battler) && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
                    {
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                        BattleScriptExecute(BattleScript_PoisonHealActivates);
                        effect++;
                    }
                }
                else
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 16;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if ((gBattleMons[battler].status1 & STATUS1_TOXIC_COUNTER) != STATUS1_TOXIC_TURN(15)) // not 16 turns
                        gBattleMons[battler].status1 += STATUS1_TOXIC_TURN(1);
                    gBattleMoveDamage *= (gBattleMons[battler].status1 & STATUS1_TOXIC_COUNTER) >> 8;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    BattleScriptExecute(BattleScript_PoisonTurnDmg);
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_BURN: // burn
            if ((gBattleMons[battler].status1 & STATUS1_BURN) && gBattleMons[battler].hp != 0)
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;
            #if B_BURN_DAMAGE >= GEN_7
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 16;
            #else
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
            #endif
                if (ability == ABILITY_HEATPROOF)
                {
                    if (gBattleMoveDamage > (gBattleMoveDamage / 2) + 1) // Record ability if the burn takes less damage than it normally would.
                        RecordAbilityBattle(battler, ABILITY_HEATPROOF);
                    gBattleMoveDamage /= 2;
                }
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                BattleScriptExecute(BattleScript_BurnTurnDmg);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_FROSTBITE: // burn
            if ((gBattleMons[battler].status1 & STATUS1_FROSTBITE) && gBattleMons[battler].hp != 0)
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;
            #if B_BURN_DAMAGE >= GEN_7
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 16;
            #else
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
            #endif
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                BattleScriptExecute(BattleScript_FrostbiteTurnDmg);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_NIGHTMARES: // spooky nightmares
            if ((gBattleMons[battler].status2 & STATUS2_NIGHTMARE) && gBattleMons[battler].hp != 0)
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;
                // R/S does not perform this sleep check, which causes the nightmare effect to
                // persist even after the affected Pokemon has been awakened by Shed Skin.
                if (gBattleMons[battler].status1 & STATUS1_SLEEP_ANY)
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    BattleScriptExecute(BattleScript_NightmareTurnDmg);
                    effect++;
                }
                else
                {
                    gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_CURSE: // curse
            if ((gBattleMons[battler].status2 & STATUS2_CURSED) && gBattleMons[battler].hp != 0)
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;
                gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                BattleScriptExecute(BattleScript_CurseTurnDmg);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_WRAP: // wrap
            if ((gBattleMons[battler].status2 & STATUS2_WRAPPED) && gBattleMons[battler].hp != 0)
            {
                if (--gDisableStructs[battler].wrapTurns != 0) // damaged by wrap
                {
                    MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;

                    gBattleScripting.animArg1 = gBattleStruct->wrappedMove[battler];
                    gBattleScripting.animArg2 = gBattleStruct->wrappedMove[battler] >> 8;
                    PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[battler]);
                    gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
                    if (GetBattlerHoldEffect(gBattleStruct->wrappedBy[battler], TRUE) == HOLD_EFFECT_BINDING_BAND)
                #if B_BINDING_DAMAGE >= GEN_6
                        {
                            gBattleMoveDamage = gBattleMons[battler].maxHP / 6;
                        }
                    else
                        {
                            gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                        }
                #else
                        {
                            gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                        }
                    else
                        {
                            gBattleMoveDamage = gBattleMons[battler].maxHP / 16;
                        }
                #endif

                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                }
                else // broke free
                {
                    gBattleMons[battler].status2 &= ~STATUS2_WRAPPED;
                    PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[battler]);
                    gBattlescriptCurrInstr = BattleScript_WrapEnds;
                }
                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_OCTOLOCK:
            if (gDisableStructs[battler].octolock)
            {
                gBattlerAttacker = gDisableStructs[battler].battlerPreventingEscape;    // needed to track who lowered stats
                gBattlerTarget = battler;
                BattleScriptExecute(BattleScript_OctolockEndTurn);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_SPIDER_WEB:
            if (gDisableStructs[battler].spiderweb)
            {
                gBattlerAttacker = gDisableStructs[battler].battlerPreventingEscape;    // needed to track who lowered stats
                gBattlerTarget = battler;
                BattleScriptExecute(BattleScript_SpiderWebEndTurn);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_UPROAR: // uproar
            if (gBattleMons[battler].status2 & STATUS2_UPROAR)
            {
                for (gBattlerAttacker = 0; gBattlerAttacker < gBattlersCount; gBattlerAttacker++)
                {
                    if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP_ANY) && GetBattlerAbility(gBattlerAttacker) != ABILITY_SOUNDPROOF)
                    {
                        gBattleMons[gBattlerAttacker].status1 &= ~STATUS1_SLEEP_ANY;
                        gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_NIGHTMARE;
                        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                        BattleScriptExecute(BattleScript_MonWokeUpInUproar);
                        BtlController_EmitSetMonData(gBattlerAttacker, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gBattlerAttacker].status1);
                        MarkBattlerForControllerExec(gBattlerAttacker);
                        break;
                    }
                }
                if (gBattlerAttacker != gBattlersCount)
                {
                    effect = 2; // a pokemon was awaken
                    break;
                }
                else
                {
                    gBattlerAttacker = battler;
                    gBattleMons[battler].status2 -= STATUS2_UPROAR_TURN(1); // uproar timer goes down
                    if (WasUnableToUseMove(battler))
                    {
                        CancelMultiTurnMoves(battler);
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_UPROAR_ENDS;
                    }
                    else if (gBattleMons[battler].status2 & STATUS2_UPROAR)
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_UPROAR_CONTINUES;
                        gBattleMons[battler].status2 |= STATUS2_MULTIPLETURNS;
                    }
                    else
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_UPROAR_ENDS;
                        CancelMultiTurnMoves(battler);
                    }
                    BattleScriptExecute(BattleScript_PrintUproarOverTurns);
                    effect = 1;
                }
            }
            if (effect != 2)
                gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_THRASH: // thrash
            // Don't decrement STATUS2_LOCK_CONFUSE if the target is held by Sky Drop
            if (gBattleMons[battler].status2 & STATUS2_LOCK_CONFUSE && !(gStatuses3[battler] & STATUS3_SKY_DROPPED))
            {
                gBattleMons[battler].status2 -= STATUS2_LOCK_CONFUSE_TURN(1);
                if (WasUnableToUseMove(battler))
                    CancelMultiTurnMoves(battler);
                else if (!(gBattleMons[battler].status2 & STATUS2_LOCK_CONFUSE) && (gBattleMons[battler].status2 & STATUS2_MULTIPLETURNS))
                {
                    gBattleMons[battler].status2 &= ~STATUS2_MULTIPLETURNS;
                    if (!(gBattleMons[battler].status2 & STATUS2_CONFUSION))
                    {
                        gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION | MOVE_EFFECT_AFFECTS_USER;
                        SetMoveEffect(TRUE, 0);
                        if (gBattleMons[battler].status2 & STATUS2_CONFUSION)
                            BattleScriptExecute(BattleScript_ThrashConfuses);
                        effect++;
                    }
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_FLINCH: // reset flinch
            if(gDisableStructs[battler].shunyongFlinchTimer > 0)
                gDisableStructs[battler].shunyongFlinchTimer--;
            
            gBattleMons[battler].status2 &= ~STATUS2_FLINCHED;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_DISABLE: // disable
            if (gDisableStructs[battler].disableTimer != 0)
            {
                for (i = 0; i < MAX_MON_MOVES; i++)
                {
                    if (gDisableStructs[battler].disabledMove == gBattleMons[battler].moves[i])
                        break;
                }
                if (i == MAX_MON_MOVES) // pokemon does not have the disabled move anymore
                {
                    gDisableStructs[battler].disabledMove = 0;
                    gDisableStructs[battler].disableTimer = 0;
                }
                else if (--gDisableStructs[battler].disableTimer == 0) // disable ends
                {
                    gDisableStructs[battler].disabledMove = 0;
                    BattleScriptExecute(BattleScript_DisabledNoMore);
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_ENCORE: // encore
            if (gDisableStructs[battler].encoreTimer != 0)
            {
                if (gBattleMons[battler].moves[gDisableStructs[battler].encoredMovePos] != gDisableStructs[battler].encoredMove) // pokemon does not have the encored move anymore
                {
                    gDisableStructs[battler].encoredMove = 0;
                    gDisableStructs[battler].encoreTimer = 0;
                }
                else if (--gDisableStructs[battler].encoreTimer == 0 || gBattleMons[battler].pp[gDisableStructs[battler].encoredMovePos] == 0)
                {
                    gDisableStructs[battler].encoredMove = 0;
                    gDisableStructs[battler].encoreTimer = 0;
                    BattleScriptExecute(BattleScript_EncoredNoMore);
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_LOCK_ON: // lock-on decrement
            if (gStatuses3[battler] & STATUS3_ALWAYS_HITS)
                gStatuses3[battler] -= STATUS3_ALWAYS_HITS_TURN(1);
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_CHARGE: // charge
            if (gDisableStructs[battler].chargeTimer > 0 && --gDisableStructs[battler].chargeTimer == 0)
                gStatuses3[battler] &= ~STATUS3_CHARGED_UP;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_PUMPED_UP: // reservoir
            if (gDisableStructs[battler].pumpTimer > 0 && --gDisableStructs[battler].pumpTimer == 0)
                gStatuses4[battler] &= ~STATUS4_PUMPED_UP;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_TAUNT: // taunt
            if (gDisableStructs[battler].tauntTimer && --gDisableStructs[battler].tauntTimer == 0)
            {
                BattleScriptExecute(BattleScript_BufferEndTurn);
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_TAUNT);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_YAWN: // yawn
            if (gStatuses3[battler] & STATUS3_YAWN)
            {
                u16 battlerAbility = GetBattlerAbility(battler);
                gStatuses3[battler] -= STATUS3_YAWN_TURN(1);
                if (!(gStatuses3[battler] & STATUS3_YAWN) && !(gBattleMons[battler].status1 & STATUS1_ANY) && battlerAbility != ABILITY_VITAL_SPIRIT && battlerAbility != ABILITY_INSOMNIA && !UproarWakeUpCheck(battler) && !IsLeafGuardProtected(battler))
                {
                    CancelMultiTurnMoves(battler);
                    gEffectBattler = battler;
                    if (IsBattlerTerrainAffected(battler, STATUS_FIELD_ELECTRIC_TERRAIN))
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_TERRAINPREVENTS_ELECTRIC;
                        BattleScriptExecute(BattleScript_TerrainPreventsEnd2);
                    }
                    else
                    {
#if B_SLEEP_TURNS >= GEN_5
                        gBattleMons[battler].status1 |= ((Random() % 2) + 2);
#else
                        gBattleMons[battler].status1 |= ((Random() % 2) + 2);
#endif
                        BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                        MarkBattlerForControllerExec(battler);
                        BattleScriptExecute(BattleScript_YawnMakesAsleep);
                    }
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_LASER_FOCUS:
            if (gStatuses3[battler] & STATUS3_LASER_FOCUS)
            {
                if (gDisableStructs[battler].laserFocusTimer == 0 || --gDisableStructs[battler].laserFocusTimer == 0)
                    gStatuses3[battler] &= ~STATUS3_LASER_FOCUS;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_FAIRY_LOCK:
            if (gStatuses4[battler] & STATUS4_FAIRY_LOCK)
            {
                gBattlerAttacker = gDisableStructs[battler].battlerPreventingEscape;    // needed to track who lowered stats
                gBattlerTarget = battler;
                BattleScriptExecute(BattleScript_FairyLockEndTurn);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_EMBARGO:
            if (gStatuses3[battler] & STATUS3_EMBARGO)
            {
                if (gDisableStructs[battler].embargoTimer == 0 || --gDisableStructs[battler].embargoTimer == 0)
                {
                    gStatuses3[battler] &= ~STATUS3_EMBARGO;
                    BattleScriptExecute(BattleScript_EmbargoEndTurn);
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_MAGNET_RISE:
            if (gStatuses3[battler] & STATUS3_MAGNET_RISE)
            {
                if (gDisableStructs[battler].magnetRiseTimer == 0 || --gDisableStructs[battler].magnetRiseTimer == 0)
                {
                    gStatuses3[battler] &= ~STATUS3_MAGNET_RISE;
                    BattleScriptExecute(BattleScript_BufferEndTurn);
                    PREPARE_STRING_BUFFER(gBattleTextBuff1, STRINGID_ELECTROMAGNETISM);
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_HEALBLOCK:
            if (gStatuses3[battler] & STATUS3_HEAL_BLOCK)
            {
                if (gDisableStructs[battler].healBlockTimer == 0 || --gDisableStructs[battler].healBlockTimer == 0)
                {
                    gStatuses3[battler] &= ~STATUS3_HEAL_BLOCK;
                    BattleScriptExecute(BattleScript_BufferEndTurn);
                    PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_HEAL_BLOCK);
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_ROOST: // Return flying type.
            if (gBattleResources->flags->flags[battler] & RESOURCE_FLAG_ROOST)
                gBattleResources->flags->flags[battler] &= ~RESOURCE_FLAG_ROOST;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_ELECTRIFY:
            gStatuses4[battler] &= ~STATUS4_ELECTRIFIED;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_POWDER:
            gBattleMons[battler].status2 &= ~STATUS2_POWDER;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_THROAT_CHOP:
            if (gDisableStructs[battler].throatChopTimer && --gDisableStructs[battler].throatChopTimer == 0)
            {
                BattleScriptExecute(BattleScript_ThroatChopEndTurn);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_MAGIC_COAT:
            if (gDisableStructs[battler].bounceMoveTimer && --gDisableStructs[battler].bounceMoveTimer == 0)
            {
                gDisableStructs[battler].bounceMove = FALSE;
                BattleScriptExecute(BattleScript_MagicCoatEndTurn);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_PLASMA_FISTS:
            gStatuses4[battler] &= ~STATUS4_PLASMA_FISTS;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_CUD_CHEW:
            if (GetBattlerAbility(battler) == ABILITY_CUD_CHEW && !gDisableStructs[battler].cudChew && ItemId_GetPocket(GetUsedHeldItem(battler)) == POCKET_BERRIES)
                gDisableStructs[battler].cudChew = TRUE;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_SALT_CURE:
            if (gStatuses4[battler] & STATUS4_SALT_CURE 
            && gBattleMons[battler].hp != 0)
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;

                gBattlerTarget = battler;
                if (IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_STEEL) || IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_WATER))
                    gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 4;
                else
                    gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 8;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[gBattlerTarget].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_SALT_CURE);
                BattleScriptExecute(BattleScript_SaltCureExtraDamage);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_SYRUP_BOMB:
            if ((gStatuses4[battler] & STATUS4_SYRUP_BOMB) && (IsBattlerAlive(battler)))
            {
                if (gDisableStructs[battler].syrupBombTimer > 0 && --gDisableStructs[battler].syrupBombTimer == 0)
                    gStatuses4[battler] &= ~STATUS4_SYRUP_BOMB;
                gBattlerTarget = battler;
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_SYRUP_BOMB);
                gBattlescriptCurrInstr = BattleScript_SyrupBombEndTurn;
                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_TICKED:
            if ((gStatuses4[battler] & STATUS4_TICKED)
             && IsBattlerAlive(gStatuses4[battler] & STATUS4_TICKED_BATTLER)
             && IsBattlerAlive(battler))
            {
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;

                gBattlerTarget = gStatuses4[battler] & STATUS4_TICKED_BATTLER; // Notice gBattlerTarget is actually the HP receiver.
                gBattlerAttacker = battler;
                gBattleScripting.animArg1 = gBattlerTarget;
                gBattleScripting.animArg2 = gBattlerAttacker;
                if (IS_BATTLER_OF_TYPE(battler, TYPE_GRASS) || IS_BATTLER_OF_TYPE(battler, TYPE_DARK) || IS_BATTLER_OF_TYPE(battler, TYPE_PSYCHIC))
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                else
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                gHitMarker |= HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE;
                BattleScriptExecute(BattleScript_TickedTurnDrain);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_GLAIVE_RUSH:
            gStatuses4[battler] &= ~STATUS4_GLAIVE_RUSH;
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_PANIC:
            if (gBattleMons[battler].status1 & STATUS1_PANIC && IsBattlerAlive(battler))
            {
                BattleScriptExecute(BattleScript_PanicTurn);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_BLOOMING:
            if (gBattleMons[battler].status1 & STATUS1_BLOOMING)
            {
                if (((gBattleMons[battler].status1 & STATUS1_BLOOMING) != STATUS1_BLOOMING_TURN(1))
                && IsBattlerAlive(battler) 
                && (!(gStatuses3[battler] & STATUS3_HEAL_BLOCK)))
                {
                    gBattleMons[battler].status1 -= STATUS1_BLOOMING_TURN(1);
                    gBattleMoveDamage = -1 * gBattleMons[battler].maxHP / 10;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = -1;
                    BattleScriptExecute(BattleScript_BloomingHpGain);
                    effect++;
                }
                else if ((gBattleMons[battler].status1 & STATUS1_BLOOMING) == STATUS1_BLOOMING_TURN(1) 
                && IsBattlerAlive(battler) 
                && (!(gStatuses3[battler] & STATUS3_HEAL_BLOCK)))
                {
                    gBattleMons[battler].status1 -= STATUS1_BLOOMING_TURN(1);
                    gBattleMoveDamage = -1 * gBattleMons[battler].maxHP / 10;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = -1;
                    BattleScriptExecute(BattleScript_BloomingHpGainEnd);
                    effect++;
                }
                else
                {
                    gBattleMons[battler].status1 -= STATUS1_BLOOMING_TURN(1);
                    BattleScriptExecute(BattleScript_BloomingHealBlockEnd);
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_EMERGENCY_EXIT:
            if (gBattleResources->flags->flags[battler] & RESOURCE_FLAG_EMERGENCY_EXIT)
            {
                if (gBattleStruct->redCardActivates)
                {
                    gBattleResources->flags->flags[battler] &= ~RESOURCE_FLAG_EMERGENCY_EXIT;
                    continue;
                }
                else
                {
                    gBattleResources->flags->flags[battler] &= ~RESOURCE_FLAG_EMERGENCY_EXIT;
                    gSpecialStatuses[battler].emergencyExited = TRUE;
                    gBattlerTarget = gBattlerAbility = i;
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER || GetBattlerSide(i) == B_SIDE_PLAYER)
                    {
                        BattleScriptExecute(BattleScript_EmergencyExit);
                    }
                    else
                    {
                        BattleScriptExecute(BattleScript_EmergencyExitWild);
                    }
                    effect++;
                }
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_INFERNAL_REIGN:
            if ((IsAbilityOnField(ABILITY_INFERNAL_REIGN))
            && GetBattlerAbility(battler) != ABILITY_INFERNAL_REIGN
            && gBattleMons[battler].hp != 0 
           )
            {
                uq4_12_t modifier = UQ_4_12(1.0);
                MAGIC_GUARD_CHECK;
                TERU_CHARM_CHECK;

                modifier = uq4_12_multiply(modifier, GetTypeModifier(TYPE_FIRE, gBattleMons[battler].type1));
                if (gBattleMons[battler].type1 != gBattleMons[battler].type2)
                    modifier = uq4_12_multiply(modifier, GetTypeModifier(TYPE_FIRE, gBattleMons[battler].type2));

                if (modifier == UQ_4_12(0.0))
                {
                    break;
                }
                else if (modifier == UQ_4_12(0.25))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 64;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                }
                else if (modifier == UQ_4_12(0.5))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 32;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                }
                else if (modifier == UQ_4_12(1.0))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 16;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                }
                else if (modifier == UQ_4_12(2.0))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                }
                else if (modifier == UQ_4_12(4.0))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                }
                BattleScriptExecute(BattleScript_InfernalReignTurnDmg);
                effect++;
            }
            gBattleStruct->turnEffectsTracker++;
            break;
        case ENDTURN_BATTLER_COUNT:  // done
            gBattleStruct->turnEffectsTracker = 0;
            gBattleStruct->turnEffectsBattlerId++;
            break;
        }

        if (effect != 0)
            return effect;
    }
    gHitMarker &= ~(HITMARKER_GRUDGE | HITMARKER_SKIP_DMG_TRACK);
    return 0;
}

bool32 HandleWishPerishSongOnTurnEnd(void)
{
    u32 battler;

    gHitMarker |= (HITMARKER_GRUDGE | HITMARKER_SKIP_DMG_TRACK);
    switch (gBattleStruct->wishPerishSongState)
    {
    case 0:
        while (gBattleStruct->wishPerishSongBattlerId < gBattlersCount)
        {
            battler = gBattleStruct->wishPerishSongBattlerId;

            gBattleStruct->wishPerishSongBattlerId++;

            if (gWishFutureKnock.futureSightCounter[battler] != 0
             && --gWishFutureKnock.futureSightCounter[battler] == 0
             && !(gAbsentBattlerFlags & gBitTable[battler]))
            {
                struct Pokemon *party;

                if (gWishFutureKnock.futureSightCounter[battler] == 0
                 && gWishFutureKnock.futureSightCounter[BATTLE_PARTNER(battler)] == 0)
                {
                    gSideStatuses[GetBattlerSide(battler)] &= ~SIDE_STATUS_FUTUREATTACK;
                }

                if (!IsBattlerAlive(battler))
                    continue;

                if (gWishFutureKnock.futureSightMove[battler] == MOVE_FUTURE_SIGHT)
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_FUTURE_SIGHT;
                else if (gWishFutureKnock.futureSightMove[battler] == MOVE_DOOM_DESIRE)
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_DOOM_DESIRE;

                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gWishFutureKnock.futureSightMove[battler]);

                gBattlerTarget = battler;
                gBattlerAttacker = gWishFutureKnock.futureSightBattlerIndex[battler];
                gSpecialStatuses[gBattlerTarget].shellBellDmg = IGNORE_SHELL_BELL;
                gCurrentMove = gWishFutureKnock.futureSightMove[battler];

                party = GetSideParty(GetBattlerSide(gBattlerAttacker));
                if (&party[gWishFutureKnock.futureSightPartyIndex[gBattlerTarget]] == &party[gBattlerPartyIndexes[gBattlerAttacker]])
                    SetTypeBeforeUsingMove(gCurrentMove, gBattlerAttacker);

                BattleScriptExecute(BattleScript_MonTookFutureAttack);

                return TRUE;
            }
        }
        gBattleStruct->wishPerishSongState = 1;
        gBattleStruct->wishPerishSongBattlerId = 0;
        // fall through
    case 1:
        while (gBattleStruct->wishPerishSongBattlerId < gBattlersCount)
        {
            battler = gBattlerAttacker = gBattlerByTurnOrder[gBattleStruct->wishPerishSongBattlerId];
            if (gAbsentBattlerFlags & gBitTable[battler])
            {
                gBattleStruct->wishPerishSongBattlerId++;
                continue;
            }
            gBattleStruct->wishPerishSongBattlerId++;
            if (gStatuses3[battler] & STATUS3_PERISH_SONG)
            {
                PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 1, gDisableStructs[battler].perishSongTimer);
                if (gDisableStructs[battler].perishSongTimer == 0)
                {
                    gStatuses3[battler] &= ~STATUS3_PERISH_SONG;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG))
                        gBattleMoveDamage = gBattleMons[battler].hp / 10;
                    else if (FlagGet(FLAG_WILD_NO_CATCHING_FLAG))
                        gBattleMoveDamage = gBattleMons[battler].hp / 10;
                    else
                        gBattleMoveDamage = gBattleMons[battler].hp;
                    gBattleMoveDamage = gBattleMons[battler].hp;
                    gBattlescriptCurrInstr = BattleScript_PerishSongTakesLife;
                }
                else
                {
                    gDisableStructs[battler].perishSongTimer--;
                    gBattlescriptCurrInstr = BattleScript_PerishSongCountGoesDown;
                }
                BattleScriptExecute(gBattlescriptCurrInstr);
                return TRUE;
            }
        }
        gBattleStruct->wishPerishSongState = 2;
        gBattleStruct->wishPerishSongBattlerId = 0;
        // fall through
    case 2:
        if ((gBattleTypeFlags & BATTLE_TYPE_ARENA)
         && gBattleStruct->arenaTurnCounter == 2
         && IsBattlerAlive(B_POSITION_PLAYER_LEFT) && IsBattlerAlive(B_POSITION_OPPONENT_LEFT))
        {
            s32 i;

            for (i = 0; i < 2; i++)
                CancelMultiTurnMoves(i);

            gBattlescriptCurrInstr = BattleScript_ArenaDoJudgment;
            BattleScriptExecute(BattleScript_ArenaDoJudgment);
            gBattleStruct->wishPerishSongState++;
            return TRUE;
        }
        break;
    }

    gHitMarker &= ~(HITMARKER_GRUDGE | HITMARKER_SKIP_DMG_TRACK);

    return FALSE;
}

#define FAINTED_ACTIONS_MAX_CASE 8

bool32 HandleFaintedMonActions(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return FALSE;
    do
    {
        s32 i;
        switch (gBattleStruct->faintedActionsState)
        {
        case 0:
            gBattleStruct->faintedActionsBattlerId = 0;
            gBattleStruct->faintedActionsState++;
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gAbsentBattlerFlags & gBitTable[i] && !HasNoMonsToSwitch(i, PARTY_SIZE, PARTY_SIZE))
                    gAbsentBattlerFlags &= ~(gBitTable[i]);
            }
            // fall through
        case 1:
            do
            {
                gBattlerFainted = gBattlerTarget = gBattleStruct->faintedActionsBattlerId;
                if (gBattleMons[gBattleStruct->faintedActionsBattlerId].hp == 0 && !(gBattleStruct->givenExpMons & gBitTable[gBattlerPartyIndexes[gBattleStruct->faintedActionsBattlerId]]) && !(gAbsentBattlerFlags & gBitTable[gBattleStruct->faintedActionsBattlerId]))
                {
                    BattleScriptExecute(BattleScript_GiveExp);
                    gBattleStruct->faintedActionsState = 2;
                    return TRUE;
                }
            } while (++gBattleStruct->faintedActionsBattlerId != gBattlersCount);
            gBattleStruct->faintedActionsState = 3;
            break;
        case 2:
            OpponentSwitchInResetSentPokesToOpponentValue(gBattlerFainted);
            if (++gBattleStruct->faintedActionsBattlerId == gBattlersCount)
                gBattleStruct->faintedActionsState = 3;
            else
                gBattleStruct->faintedActionsState = 1;
#if B_FAINT_SWITCH_IN >= GEN_4
            // Don't switch mons until all pokemon performed their actions or the battle's over.
            if (gBattleOutcome == 0 && !NoAliveMonsForEitherParty() && gCurrentTurnActionNumber != gBattlersCount)
            {
                gAbsentBattlerFlags |= gBitTable[gBattlerFainted];
                return FALSE;
            }
#endif
            break;
        case 3:
#if B_FAINT_SWITCH_IN >= GEN_4
            // Don't switch mons until all pokemon performed their actions or the battle's over.
            if (gBattleOutcome == 0 && !NoAliveMonsForEitherParty() && gCurrentTurnActionNumber != gBattlersCount)
            {
                return FALSE;
            }
#endif
            gBattleStruct->faintedActionsBattlerId = 0;
            gBattleStruct->faintedActionsState++;
            // fall through
        case 4:
            do
            {
                gBattlerFainted = gBattlerTarget = gBattleStruct->faintedActionsBattlerId;
                if (gBattleMons[gBattleStruct->faintedActionsBattlerId].hp == 0 && !(gAbsentBattlerFlags & gBitTable[gBattleStruct->faintedActionsBattlerId]))
                {
                    BattleScriptExecute(BattleScript_HandleFaintedMon);
                    gBattleStruct->faintedActionsState = 5;
                    return TRUE;
                }
            } while (++gBattleStruct->faintedActionsBattlerId != gBattlersCount);
            gBattleStruct->faintedActionsState = 6;
            break;
        case 5:
            if (++gBattleStruct->faintedActionsBattlerId == gBattlersCount)
                gBattleStruct->faintedActionsState = 6;
            else
                gBattleStruct->faintedActionsState = 4;
            break;
        case 6: // All battlers switch-in abilities happen here to prevent them happening against an empty field.
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gBattleStruct->switchInAbilityPostponed & gBitTable[i])
                {
                    if (DoSwitchInAbilitiesItems(i))
                        return TRUE;
                    gBattleStruct->switchInAbilityPostponed &= ~(gBitTable[i]);
                }
            }
            gBattleStruct->faintedActionsState++;
            break;
        case 7:
            if (ItemBattleEffects(ITEMEFFECT_NORMAL, 0, TRUE))
                return TRUE;
            gBattleStruct->faintedActionsState++;
            break;
        case FAINTED_ACTIONS_MAX_CASE:
            break;
        }
    } while (gBattleStruct->faintedActionsState != FAINTED_ACTIONS_MAX_CASE);
    return FALSE;
}

void TryClearRageAndFuryCutter(void)
{
    s32 i;
    for (i = 0; i < gBattlersCount; i++)
    {
        if ((gBattleMons[i].status2 & STATUS2_RAGE) && gChosenMoveByBattler[i] != MOVE_RAGE)
            gBattleMons[i].status2 &= ~STATUS2_RAGE;
        if (gDisableStructs[i].furyCutterCounter != 0 && gChosenMoveByBattler[i] != MOVE_FURY_CUTTER)
            gDisableStructs[i].furyCutterCounter = 0;
    }
}

static inline bool32 TryFormChangeBeforeMove(void)
{
    bool32 result = TryBattleFormChange(gBattlerAttacker, FORM_CHANGE_BATTLE_BEFORE_MOVE_CATEGORY);
    if (!result)
        return FALSE;

    BattleScriptPushCursor();
    gBattlescriptCurrInstr = BattleScript_AttackerFormChange;
    return TRUE;
}

void SetAtkCancellerForCalledMove(void)
{
    gBattleStruct->atkCancellerTracker = CANCELLER_HEAL_BLOCKED;
    gBattleStruct->isAtkCancelerForCalledMove = TRUE;
}

u8 AtkCanceller_UnableToUseMove(u32 moveType)
{
    u8 effect = 0;
    u32 count = 0;
    u32 i;
    u32 dampBattler = IsAbilityOnField(ABILITY_DAMP);

    do
    {
        switch (gBattleStruct->atkCancellerTracker)
        {
        case CANCELLER_FLAGS: // flags clear
            gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_DESTINY_BOND;
            gStatuses3[gBattlerAttacker] &= ~STATUS3_GRUDGE;
            gStatuses4[gBattlerAttacker] &= ~STATUS4_GLAIVE_RUSH_2;
            gBattleScripting.tripleKickPower = 0;
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_SKY_DROP:
            // If Pokemon is being held in Sky Drop
            if (gStatuses3[gBattlerAttacker] & STATUS3_SKY_DROPPED)
            {
                gBattlescriptCurrInstr = BattleScript_MoveEnd;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_ASLEEP: // check being asleep from rest or sleep
            if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP_ANY)
            {
                if (UproarWakeUpCheck(gBattlerAttacker))
                {
                    gBattleMons[gBattlerAttacker].status1 &= ~STATUS1_SLEEP_ANY;
                    gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_NIGHTMARE;
                    BattleScriptPushCursor();
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_WOKE_UP_UPROAR;
                    gBattlescriptCurrInstr = BattleScript_MoveUsedWokeUp;
                    effect = 2;
                }
                else
                {
                    u8 toSub;
                    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_EARLY_BIRD)
                        toSub = 2;
                    else
                        toSub = 1;
                    
                    if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP) 
                    {
                        if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP) < toSub)
                            gBattleMons[gBattlerAttacker].status1 &= ~STATUS1_SLEEP;
                        else
                            gBattleMons[gBattlerAttacker].status1 -= toSub;
                    }
                    else if (gBattleMons[gBattlerAttacker].status1 & STATUS1_REST) 
                    {
                        if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_REST) < STATUS1_REST_TURN(toSub))
                            gBattleMons[gBattlerAttacker].status1 &= ~STATUS1_REST;
                        else
                            gBattleMons[gBattlerAttacker].status1 -= STATUS1_REST_TURN(toSub);
                    }

                    if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP_ANY)
                    {
                        if (gChosenMove != MOVE_SNORE && gChosenMove != MOVE_SLEEP_TALK)
                        {
                            gBattlescriptCurrInstr = BattleScript_MoveUsedIsAsleep;
                            gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                            effect = 2;
                        }
                    }
                    else
                    {
                        gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_NIGHTMARE;
                        BattleScriptPushCursor();
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_WOKE_UP;
                        gBattlescriptCurrInstr = BattleScript_MoveUsedWokeUp;
                        effect = 2;
                    }
                }
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_FROZEN: // check being frozen
            if (gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE && !(gBattleMoves[gCurrentMove].thawsUser))
            {
                gBattleMons[gBattlerAttacker].status1 -= STATUS1_FREEZE_TURN(1);
                if (gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE)
                {
                    gBattlescriptCurrInstr = BattleScript_MoveUsedIsFrozen;
                    gHitMarker |= HITMARKER_NO_ATTACKSTRING;
                }
                else // unfreeze
                {
                    gBattleMons[gBattlerAttacker].status1 &= ~STATUS1_FREEZE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MoveUsedUnfroze;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_DEFROSTED;
                }
                effect = 2;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_TRUANT: // truant
            if (GetBattlerAbility(gBattlerAttacker) == ABILITY_TRUANT && gDisableStructs[gBattlerAttacker].truantCounter)
            {
                if (!(gBattleMoves[gCurrentMove].lazyMove))
                {
                    CancelMultiTurnMoves(gBattlerAttacker);
                    gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_LOAFING;
                    gBattlerAbility = gBattlerAttacker;
                    gBattlescriptCurrInstr = BattleScript_TruantLoafingAround;
                    gMoveResultFlags |= MOVE_RESULT_MISSED;
                    effect = 1;
                }
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_RECHARGE: // recharge
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_RECHARGE 
            || gStatuses4[gBattlerAttacker] & STATUS4_RECHARGE_REDUCE 
            || gStatuses4[gBattlerAttacker] & STATUS4_RECHARGE_BURN)
            {
                gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_RECHARGE;
                gStatuses4[gBattlerAttacker] &= ~STATUS4_RECHARGE_REDUCE;
                gStatuses4[gBattlerAttacker] &= ~STATUS4_RECHARGE_BURN;
                gDisableStructs[gBattlerAttacker].rechargeTimer = 0;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedMustRecharge;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            else if (gStatuses4[gBattlerAttacker] & STATUS4_RECHARGE_STATS)
            {
                gStatuses4[gBattlerAttacker] &= ~STATUS4_RECHARGE_STATS;
                gDisableStructs[gBattlerAttacker].rechargeTimer = 0;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedMustRechargeStats;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_FLINCH: // flinch
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_FLINCHED)
            {
                gProtectStructs[gBattlerAttacker].flinchImmobility = TRUE;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedFlinched;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_DISABLED: // disabled move
            if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && gDisableStructs[gBattlerAttacker].disabledMove == gCurrentMove && gDisableStructs[gBattlerAttacker].disabledMove != MOVE_NONE)
            {
                gProtectStructs[gBattlerAttacker].usedDisabledMove = TRUE;
                gBattleScripting.battler = gBattlerAttacker;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsDisabled;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_HEAL_BLOCKED:
            if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && gStatuses3[gBattlerAttacker] & STATUS3_HEAL_BLOCK && IsHealBlockPreventingMove(gBattlerAttacker, gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedHealBlockedMove = TRUE;
                gBattleScripting.battler = gBattlerAttacker;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedHealBlockPrevents;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_GRAVITY:
            if (gFieldStatuses & STATUS_FIELD_GRAVITY && IsGravityPreventingMove(gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedGravityPreventedMove = TRUE;
                gBattleScripting.battler = gBattlerAttacker;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedGravityPrevents;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_TAUNTED: // taunt
            if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && gDisableStructs[gBattlerAttacker].tauntTimer && IS_MOVE_STATUS(gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedTauntedMove = TRUE;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsTaunted;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_IMPRISONED: // imprisoned
            if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && GetImprisonedMovesCount(gBattlerAttacker, gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedImprisonedMove = TRUE;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsImprisoned;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_CONFUSED: // confusion
            if (!gBattleStruct->isAtkCancelerForCalledMove 
            && gBattleMons[gBattlerAttacker].status2 & STATUS2_CONFUSION
            && gBattleMoves[gCurrentMove].effect != EFFECT_SPINDA_SWING)
            {
                if (!(gStatuses4[gBattlerAttacker] & STATUS4_INFINITE_CONFUSION))
                    gBattleMons[gBattlerAttacker].status2 -= STATUS2_CONFUSION_TURN(1);
                if (gBattleMons[gBattlerAttacker].status2 & STATUS2_CONFUSION)
                {
                    // confusion dmg
#if B_CONFUSION_SELF_DMG_CHANCE >= GEN_7
                    if (RandomWeighted(RNG_CONFUSION, 2, 1))
#else
                    if (RandomWeighted(RNG_CONFUSION, 1, 1))
#endif
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = TRUE;
                        gBattlerTarget = gBattlerAttacker;
                        gBattleMoveDamage = CalculateMoveDamage(MOVE_NONE, gBattlerAttacker, gBattlerAttacker, TYPE_MYSTERY, 40, FALSE, FALSE, TRUE);
                        gProtectStructs[gBattlerAttacker].confusionSelfDmg = TRUE;
                        gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                    }
                    else
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = FALSE;
                        BattleScriptPushCursor();
                    }
                    gBattlescriptCurrInstr = BattleScript_MoveUsedIsConfused;
                }
                else // snapped out of confusion
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MoveUsedIsConfusedNoMore;
                }
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_PARALYSED: // paralysis
            if (!gBattleStruct->isAtkCancelerForCalledMove && (gBattleMons[gBattlerAttacker].status1 & STATUS1_PARALYSIS) && !RandomPercentage(RNG_PARALYSIS, 75))
            {
                gProtectStructs[gBattlerAttacker].prlzImmobility = TRUE;
                // This is removed in FRLG and Emerald for some reason
                // CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsParalyzed;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_IN_LOVE: // infatuation
            if (!gBattleStruct->isAtkCancelerForCalledMove 
            && gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION
            && gBattleMoves[gCurrentMove].effect != EFFECT_HEART_CARVE)
            {
                gBattleScripting.battler = CountTrailingZeroBits((gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION) >> 0x10);
                if (!RandomPercentage(RNG_INFATUATION, 25))
                {
                    BattleScriptPushCursor();
                }
                else
                {
                    BattleScriptPush(BattleScript_MoveUsedIsInLoveCantAttack);
                    gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                    gProtectStructs[gBattlerAttacker].loveImmobility = TRUE;
                    CancelMultiTurnMoves(gBattlerAttacker);
                }
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsInLove;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_BIDE: // bide
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_BIDE)
            {
                gBattleMons[gBattlerAttacker].status2 -= STATUS2_BIDE_TURN(1);
                if (gBattleMons[gBattlerAttacker].status2 & STATUS2_BIDE)
                {
                    gBattlescriptCurrInstr = BattleScript_BideStoringEnergy;
                }
                else
                {
                    // This is removed in FRLG and Emerald for some reason
                    // gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_MULTIPLETURNS;
                    if (gTakenDmg[gBattlerAttacker])
                    {
                        gCurrentMove = MOVE_BIDE;
                        gBattleScripting.bideDmg = gTakenDmg[gBattlerAttacker] * 2;
                        gBattlerTarget = gTakenDmgByBattler[gBattlerAttacker];
                        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
                            gBattlerTarget = GetMoveTarget(MOVE_BIDE, MOVE_TARGET_SELECTED + 1);
                        gBattlescriptCurrInstr = BattleScript_BideAttack;
                    }
                    else
                    {
                        gBattlescriptCurrInstr = BattleScript_BideNoEnergyToAttack;
                    }
                }
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_THAW: // move thawing
            if (gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE)
            {
                if (!(gBattleMoves[gCurrentMove].effect == EFFECT_BURN_UP && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_FIRE)))
                {
                    gBattleMons[gBattlerAttacker].status1 &= ~STATUS1_FREEZE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MoveUsedUnfroze;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_DEFROSTED_BY_MOVE;
                }
                effect = 2;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_STANCE_CHANGE:
            if (!gBattleStruct->isAtkCancelerForCalledMove && TryFormChangeBeforeMove())
                effect = 1;
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_POWDER_MOVE:
            if ((gBattleMoves[gCurrentMove].powderMove) && (gBattlerAttacker != gBattlerTarget))
            {
#if B_POWDER_GRASS >= GEN_6
                if (!(GetBattlerAbility(gBattlerAttacker) == ABILITY_MYCELIUM_MIGHT) && (IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GRASS) || GetBattlerAbility(gBattlerTarget) == ABILITY_OVERCOAT))
#else
                if ((GetBattlerAbility(gBattlerTarget) == ABILITY_OVERCOAT))
#endif
                {
                    gBattlerAbility = gBattlerTarget;
                    effect = 1;
                }
                else if (!(GetBattlerAbility(gBattlerAttacker) == ABILITY_MYCELIUM_MIGHT) && GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_SAFETY_GOGGLES)
                {
                    RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_SAFETY_GOGGLES);
                    gLastUsedItem = gBattleMons[gBattlerTarget].item;
                    effect = 1;
                }

                if (effect != 0)
                    gBattlescriptCurrInstr = BattleScript_PowderMoveNoEffect;
            }
            if (gProtectStructs[gBattlerAttacker].usesBouncedMove) // Edge case for bouncing a powder move against a grass type pokemon.
                gBattleStruct->atkCancellerTracker = CANCELLER_END;
            else
                gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_POWDER_STATUS:
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_POWDER)
            {
                if (moveType == TYPE_FIRE)
                {
                    gProtectStructs[gBattlerAttacker].powderSelfDmg = TRUE;
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                    if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    gBattlescriptCurrInstr = BattleScript_MoveUsedPowder;
                    effect = 1;
                }
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_THROAT_CHOP:
            if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] == MOVE_NONE && gDisableStructs[gBattlerAttacker].throatChopTimer && gBattleMoves[gCurrentMove].soundMove)
            {
                gProtectStructs[gBattlerAttacker].usedThroatChopPreventedMove = TRUE;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsThroatChopPrevented;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_EXPLODING_DAMP:
            if (dampBattler 
            && (gBattleMoves[gCurrentMove].effect == EFFECT_EXPLOSION
            || (gBattleMoves[gCurrentMove].effect == EFFECT_DOUBLE_SHOCK && (gStatuses4[gBattlerAttacker] & STATUS4_SUPERCHARGED) && (gStatuses4[gBattlerAttacker] & STATUS4_GEARED_UP))
            || (gBattleMoves[gCurrentMove].effect == EFFECT_CANNONADE && gBattleMons[gBattlerAttacker].hp <= (gBattleMons[gBattlerAttacker].maxHP / 4))
            || gBattleMoves[gCurrentMove].effect == EFFECT_MIND_BLOWN
            || gBattleMoves[gCurrentMove].effect == EFFECT_STALAG_BLAST)
            && gCurrentMove != MOVE_FINAL_SHRIEK)
            {
                gBattleScripting.battler = dampBattler - 1;
                gBattlescriptCurrInstr = BattleScript_DampStopsExplosion;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_Z_MOVES:
            if (gBattleStruct->zmove.toBeUsed[gBattlerAttacker] != MOVE_NONE)
            {
                // attacker has a queued z move
                gBattleStruct->zmove.active = TRUE;
                gBattleStruct->zmove.activeSplit = gBattleStruct->zmove.splits[gBattlerAttacker];
                RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_Z_CRYSTAL);
                gBattleStruct->zmove.used[gBattlerAttacker] = TRUE;
                if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE) && IsPartnerMonFromSameTrainer(gBattlerAttacker))
                    gBattleStruct->zmove.used[BATTLE_PARTNER(gBattlerAttacker)] = TRUE; // if 1v1 double, set partner used flag as well

                gBattleScripting.battler = gBattlerAttacker;
                if (gBattleStruct->zmove.activeSplit == SPLIT_STATUS)
                {
                    gBattleStruct->zmove.effect = gBattleMoves[gBattleStruct->zmove.baseMoves[gBattlerAttacker]].zMoveEffect;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ZMoveActivateStatus;
                }
                else
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ZMoveActivateDamaging;
                }
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_MULTIHIT_MOVES:
            if (gBattleMoves[gCurrentMove].effect == EFFECT_MULTI_HIT 
                || gBattleMoves[gCurrentMove].effect == EFFECT_COMET_PUNCH
                || gBattleMoves[gCurrentMove].effect == EFFECT_BARB_BARRAGE
                || gBattleMoves[gCurrentMove].effect == EFFECT_BARRAGE
                || gBattleMoves[gCurrentMove].effect == EFFECT_SPIKE_CANNON
                || gBattleMoves[gCurrentMove].effect == EFFECT_PIN_MISSILE)
            {
                u16 ability = gBattleMons[gBattlerAttacker].ability;

                if (ability == ABILITY_SKILL_LINK)
                {
                    gMultiHitCounter = 5;
                }
                else if (ability == ABILITY_BATTLE_BOND && gCurrentMove == MOVE_WATER_SHURIKEN && gBattleMons[gBattlerAttacker].species == SPECIES_GRENINJA_ASH)
                {
                    gMultiHitCounter = 3;
                }
                else if (gCurrentMove == MOVE_DOUBLE_SLAP && IsBattlerTerrainAffected(gBattlerAttacker, STATUS_FIELD_MISTY_TERRAIN))
                {
                    SetRandomMultiHitCounter3To5();
                }
                else
                {
                    SetRandomMultiHitCounter();
                }

                PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 1, 0)
            }
            else if (gBattleMoves[gCurrentMove].effect == EFFECT_BLACK_BUFFET)
            {
                u16 ability = gBattleMons[gBattlerAttacker].ability;

                if (ability == ABILITY_SKILL_LINK)
                {
                    gMultiHitCounter = 5;
                }
                else
                {
                    SetRandomMultiHitCounter3To5();
                }

                PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 1, 0)
            }
            else if (gCurrentMove == MOVE_AQUASCADE && (gBattleWeather & B_WEATHER_RAIN))
            {
                gMultiHitCounter = 2;
                PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 3, 0)
            }
            else if ((gBattleMoves[gCurrentMove].effect == EFFECT_CANNONADE) && (gBattleMons[gBattlerAttacker].hp > (gBattleMons[gBattlerAttacker].maxHP / 4)))
            {
                gMultiHitCounter = 2;
                PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 3, 0)
            }
            else if (gBattleMoves[gCurrentMove].strikeCount > 1)
            {
                if (gBattleMoves[gCurrentMove].effect == EFFECT_POPULATION_BOMB && GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_LOADED_DICE)
                {
                    gMultiHitCounter = RandomUniform(RNG_LOADED_DICE, 4, 10);
                }
                else if ((gBattleMoves[gCurrentMove].effect == EFFECT_FROST_SHRED) && (gBattleMons[gBattlerAttacker].statStages[STAT_SPEED] > DEFAULT_STAT_STAGE))
                {
                    count += gBattleMons[gBattlerAttacker].statStages[STAT_SPEED] - DEFAULT_STAT_STAGE;
                    gMultiHitCounter = count + gBattleMoves[gCurrentMove].strikeCount;
                    PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 3, 0)
                }
                else if ((gCurrentMove == MOVE_BULLET_PUNCH) && (gBattleMons[gBattlerAttacker].statStages[STAT_SPEED] > DEFAULT_STAT_STAGE))
                {
                    count += gBattleMons[gBattlerAttacker].statStages[STAT_SPEED] - DEFAULT_STAT_STAGE;
                    gMultiHitCounter = count + gBattleMoves[gCurrentMove].strikeCount;
                    PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 3, 0)
                }
                else if (gBattleMoves[gCurrentMove].effect == EFFECT_HAYWIRE)
                {
                    gMultiHitCounter = CountBattlerStatIncreases(gBattlerAttacker, TRUE) + gBattleMoves[gCurrentMove].strikeCount;
                    if (gMultiHitCounter > 10)
                        gMultiHitCounter = 10;
                    PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 3, 0)
                }
                else
                {
                    gMultiHitCounter = gBattleMoves[gCurrentMove].strikeCount;
                    PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 3, 0)
                }
            }
#if B_BEAT_UP >= GEN_5
            else if (gBattleMoves[gCurrentMove].effect == EFFECT_BEAT_UP)
            {
                struct Pokemon *party = GetBattlerParty(gBattlerAttacker);
                int i;

                for (i = 0; i < PARTY_SIZE; i++)
                {
                    if (GetMonData(&party[i], MON_DATA_HP) && GetMonData(&party[i], MON_DATA_SPECIES) != SPECIES_NONE && !GetMonData(&party[i], MON_DATA_IS_EGG) && !GetMonData(&party[i], MON_DATA_STATUS))
                        gMultiHitCounter++;
                }

                gBattleStruct->beatUpSlot = 0;
                PREPARE_BYTE_NUMBER_BUFFER(gBattleScripting.multihitString, 1, 0)
            }
#endif
            else
            {
                gMultiHitCounter = 0;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_END:
            break;
        }

    } while (gBattleStruct->atkCancellerTracker != CANCELLER_END && gBattleStruct->atkCancellerTracker != CANCELLER_END2 && effect == 0);

    if (effect == 2)
    {
        BtlController_EmitSetMonData(gBattlerAttacker, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gBattlerAttacker].status1);
        MarkBattlerForControllerExec(gBattlerAttacker);
    }
    return effect;
}

// After Protean Activation.
u8 AtkCanceller_UnableToUseMove2(void)
{
    u8 effect = 0;

    do
    {
        switch (gBattleStruct->atkCancellerTracker)
        {
        case CANCELLER_END:
            gBattleStruct->atkCancellerTracker++;
        case CANCELLER_PSYCHIC_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN && IsBattlerGrounded(gBattlerTarget) && GetChosenMovePriority(gBattlerAttacker) > 0 && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
            {
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedPsychicTerrainPrevents;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_END2:
            break;
        }

    } while (gBattleStruct->atkCancellerTracker != CANCELLER_END2 && effect == 0);

    return effect;
}

bool32 HasNoMonsToSwitch(u32 battler, u8 partyIdBattlerOn1, u8 partyIdBattlerOn2)
{
    u32 i, side, playerId, flankId;
    struct Pokemon *party;

    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
        return FALSE;

    side = GetBattlerSide(battler);

    if (BATTLE_TWO_VS_ONE_OPPONENT && side == B_SIDE_OPPONENT)
    {
        flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        party = gEnemyParty;
        
        // Edge case: If both opposing Pokemon were knocked out on the same turn,
        // make sure opponent only sents out the final Pokemon once.
        if (battler == playerId
         && (gHitMarker & HITMARKER_FAINTED(flankId))
         && (gHitMarker & HITMARKER_FAINTED(playerId)))
        {
            u8 count = 0;
            for (i = 0; i < PARTY_SIZE; i++)
                if (IsValidForBattle(&party[i]))
                    count++;

            if (count < 2)
                return TRUE;
        }

        if (partyIdBattlerOn1 == PARTY_SIZE)
            partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
        if (partyIdBattlerOn2 == PARTY_SIZE)
            partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i]) && i != partyIdBattlerOn1 && i != partyIdBattlerOn2 && i != *(gBattleStruct->monToSwitchIntoId + flankId) && i != playerId[gBattleStruct->monToSwitchIntoId])
                break;
        }
        return (i == PARTY_SIZE);
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
    {
        party = GetBattlerParty(battler);
        if (side == B_SIDE_OPPONENT && WILD_DOUBLE_BATTLE)
        {
            flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);

            if (partyIdBattlerOn1 == PARTY_SIZE)
                partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
            if (partyIdBattlerOn2 == PARTY_SIZE)
                partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

            for (i = 0; i < PARTY_SIZE; i++)
            {
                if (IsValidForBattle(&party[i]) && i != partyIdBattlerOn1 && i != partyIdBattlerOn2 && i != *(gBattleStruct->monToSwitchIntoId + flankId) && i != playerId[gBattleStruct->monToSwitchIntoId])
                    break;
            }
            return (i == PARTY_SIZE);
        }
        else
        {
            playerId = ((battler & BIT_FLANK) / 2);
            for (i = playerId * MULTI_PARTY_SIZE; i < playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE; i++)
            {
                if (IsValidForBattle(&party[i]))
                    break;
            }
            return (i == playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE);
        }
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
        {
            if (side == B_SIDE_PLAYER)
            {
                party = gPlayerParty;
                flankId = GetBattlerMultiplayerId(battler);
                playerId = GetLinkTrainerFlankId(flankId);
            }
            else
            {
                party = gEnemyParty;
                if (battler == 1)
                    playerId = 0;
                else
                    playerId = 1;
            }
        }
        else
        {
            flankId = GetBattlerMultiplayerId(battler);
            party = GetBattlerParty(battler);
            playerId = GetLinkTrainerFlankId(flankId);
        }

        for (i = playerId * MULTI_PARTY_SIZE; i < playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i]))
                break;
        }
        return (i == playerId * MULTI_PARTY_SIZE + MULTI_PARTY_SIZE);
    }
    else if ((gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) && side == B_SIDE_OPPONENT)
    {
        party = gEnemyParty;

        if (battler == 1)
            playerId = 0;
        else
            playerId = MULTI_PARTY_SIZE;

        for (i = playerId; i < playerId + MULTI_PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i]))
                break;
        }
        return (i == playerId + 3);
    }
    else
    {
        if (side == B_SIDE_OPPONENT)
        {
            flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
            party = gEnemyParty;
        }
        else
        {
            flankId = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            playerId = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
            party = gPlayerParty;
        }

        if (partyIdBattlerOn1 == PARTY_SIZE)
            partyIdBattlerOn1 = gBattlerPartyIndexes[flankId];
        if (partyIdBattlerOn2 == PARTY_SIZE)
            partyIdBattlerOn2 = gBattlerPartyIndexes[playerId];

        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (IsValidForBattle(&party[i]) && i != partyIdBattlerOn1 && i != partyIdBattlerOn2 && i != *(gBattleStruct->monToSwitchIntoId + flankId) && i != playerId[gBattleStruct->monToSwitchIntoId])
                break;
        }
        return (i == PARTY_SIZE);
    }
}

static const u16 sWeatherFlagsInfo[][3] =
    {
        [ENUM_WEATHER_RAIN] = {B_WEATHER_RAIN_TEMPORARY, B_WEATHER_RAIN_PERMANENT, HOLD_EFFECT_DAMP_ROCK},
        [ENUM_WEATHER_RAIN_PRIMAL] = {B_WEATHER_RAIN_PRIMAL, B_WEATHER_RAIN_PRIMAL, HOLD_EFFECT_DAMP_ROCK},
        [ENUM_WEATHER_SUN] = {B_WEATHER_SUN_TEMPORARY, B_WEATHER_SUN_PERMANENT, HOLD_EFFECT_HEAT_ROCK},
        [ENUM_WEATHER_SUN_PRIMAL] = {B_WEATHER_SUN_PRIMAL, B_WEATHER_SUN_PRIMAL, HOLD_EFFECT_HEAT_ROCK},
        [ENUM_WEATHER_SANDSTORM] = {B_WEATHER_SANDSTORM_TEMPORARY, B_WEATHER_SANDSTORM_PERMANENT, HOLD_EFFECT_SMOOTH_ROCK},
        [ENUM_WEATHER_HAIL] = {B_WEATHER_HAIL_TEMPORARY, B_WEATHER_HAIL_PERMANENT, HOLD_EFFECT_ICY_ROCK},
        [ENUM_WEATHER_STRONG_WINDS] = {B_WEATHER_STRONG_WINDS, B_WEATHER_STRONG_WINDS, HOLD_EFFECT_NONE},
        [ENUM_WEATHER_SNOW] = {B_WEATHER_SNOW_TEMPORARY, B_WEATHER_SNOW_PERMANENT, HOLD_EFFECT_ICY_ROCK},
};

static void ShouldChangeFormInWeather(u32 battler)
{
    int i;
    int side = GetBattlerSide(battler);
    struct Pokemon *party = GetSideParty(side);

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES) == SPECIES_EISCUE_NOICE_FACE)
            gBattleStruct->allowedToChangeFormInWeather[i][side] = TRUE;
        else
            gBattleStruct->allowedToChangeFormInWeather[i][side] = FALSE;
    }
}

bool32 TryChangeBattleWeather(u32 battler, u32 weatherEnumId, bool32 viaAbility)
{
    u16 battlerAbility = GetBattlerAbility(battler);
    u16 i;

    if (weatherEnumId != WEATHER_NONE)
    {
        if (IsAbilityOnField(ABILITY_AIR_LOCK))
        {
            return FALSE;
        }
    }

    if (weatherEnumId != WEATHER_NONE)
    {
        if (IsTeruCharmOnField())
        {
            return FALSE;
        }
    }

    if (gBattleWeather & B_WEATHER_PRIMAL_ANY && battlerAbility != ABILITY_DESOLATE_LAND && battlerAbility != ABILITY_PRIMORDIAL_SEA && battlerAbility != ABILITY_DELTA_STREAM)
    {
        return FALSE;
    }

#if B_ABILITY_WEATHER <= GEN_5
    else if (viaAbility && !(gBattleWeather & sWeatherFlagsInfo[weatherEnumId][1]))
    {
        gBattleWeather = (sWeatherFlagsInfo[weatherEnumId][0] | sWeatherFlagsInfo[weatherEnumId][1]);
        ShouldChangeFormInWeather(battler);
        return TRUE;
    }
#endif
    else if (!(gBattleWeather & (sWeatherFlagsInfo[weatherEnumId][0] | sWeatherFlagsInfo[weatherEnumId][1])))
    {
        gBattleWeather = (sWeatherFlagsInfo[weatherEnumId][0]);
        if (GetBattlerHoldEffect(battler, TRUE) == sWeatherFlagsInfo[weatherEnumId][2])
            gWishFutureKnock.weatherDuration = 8;
        else if (gCurrentMove == MOVE_SOLAR_FLARE && GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_SOLAR_SWORD && gBattleWeather & B_WEATHER_SUN && gBattleMons[battler].species == SPECIES_SOLROCK)
            gWishFutureKnock.weatherDuration = 6;
        else
            gWishFutureKnock.weatherDuration = 5;
        ShouldChangeFormInWeather(battler);
        return TRUE;
    }
    return FALSE;
}

static bool32 TryChangeBattleTerrain(u32 battler, u32 statusFlag, u8 *timer)
{
    if (!(gFieldStatuses & statusFlag))
    {
        gFieldStatuses &= ~(STATUS_FIELD_MISTY_TERRAIN | STATUS_FIELD_GRASSY_TERRAIN | STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_PSYCHIC_TERRAIN);
        gFieldStatuses |= statusFlag;

        if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_TERRAIN_EXTENDER || GetBattlerAbility(battler) == ABILITY_MIND_GAMES)
            *timer = 8;
        else
            *timer = 5;

        gBattleScripting.battler = battler;
        return TRUE;
    }

    return FALSE;
}

static void ForewarnChooseMove(u32 battler)
{
    struct Forewarn
    {
        u8 battler;
        u8 power;
        u16 moveId;
    };
    u32 i, j, bestId, count;
    struct Forewarn *data = Alloc(sizeof(struct Forewarn) * MAX_BATTLERS_COUNT * MAX_MON_MOVES);

    // Put all moves
    for (count = 0, i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (IsBattlerAlive(i) && GetBattlerSide(i) != GetBattlerSide(battler))
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMons[i].moves[j] == MOVE_NONE)
                    continue;
                data[count].moveId = gBattleMons[i].moves[j];
                data[count].battler = i;
                switch (gBattleMoves[data[count].moveId].effect)
                {
                case EFFECT_OHKO:
                    data[count].power = 150;
                    break;
                case EFFECT_COUNTER:
                case EFFECT_MIRROR_COAT:
                case EFFECT_METAL_BURST:
                    data[count].power = 120;
                    break;
                default:
                    if (gBattleMoves[data[count].moveId].power == 1)
                        data[count].power = 80;
                    else
                        data[count].power = gBattleMoves[data[count].moveId].power;
                    break;
                }
                count++;
            }
        }
    }

    for (bestId = 0, i = 1; i < count; i++)
    {
        if (data[i].power > data[bestId].power)
            bestId = i;
        else if (data[i].power == data[bestId].power && Random() & 1)
            bestId = i;
    }

    gBattlerTarget = data[bestId].battler;
    PREPARE_MOVE_BUFFER(gBattleTextBuff1, data[bestId].moveId)
    RecordKnownMove(gBattlerTarget, data[bestId].moveId);

    Free(data);
}

bool32 ChangeTypeBasedOnTerrain(u32 battler)
{
    u32 battlerType;

    if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
        battlerType = TYPE_ELECTRIC;
    else if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
        battlerType = TYPE_GRASS;
    else if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
        battlerType = TYPE_FAIRY;
    else if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
        battlerType = TYPE_PSYCHIC;
    else // failsafe
        return FALSE;

    SET_BATTLER_TYPE(battler, battlerType);
    PREPARE_TYPE_BUFFER(gBattleTextBuff1, battlerType);
    return TRUE;
}

// Supreme Overlord adds a x0.1 damage boost for each fainted ally.
static inline uq4_12_t GetSupremeOverlordModifier(u32 battler)
{
    return UQ_4_12(1.0) + (PercentToUQ4_12(gBattleStruct->supremeOverlordCounter[battler] * 10));
}

static inline uq4_12_t GetSharpnessModifier(u32 battler)
{
    return UQ_4_12(1.75) - (PercentToUQ4_12(gBattleStruct->slicingMoveTurns[battler] * 25));
}

static inline uq4_12_t GetOwnTempoModifier(u32 battler)
{
    return UQ_4_12(1.0) + (PercentToUQ4_12(gBattleStruct->dancingMoveTurns[battler] * 20));
}

static inline uq4_12_t GetCleanseTagModifier(u32 battler)
{
    return UQ_4_12(1.0) + (PercentToUQ4_12(CountBattlerStatDecreases(battler, TRUE) * 15));
}

static inline uq4_12_t GetDarkAuraModifier(u32 battler)
{
    return UQ_4_12(1.0) + (PercentToUQ4_12(CountBattlerStatDecreases(battler, TRUE) * 10));
}

static inline bool32 IsMoveDraining(u32 move)
{
    bool32 ret = FALSE;
    switch (gBattleMoves[move].effect)
    {
    case EFFECT_ABSORB:
    case EFFECT_SPIRIT_AWAY:
    case EFFECT_DRAINING_KISS:
    case EFFECT_BLACK_BUFFET:
    case EFFECT_LONE_SHARK:
    case EFFECT_VENOM_DRAIN:
        ret = TRUE;
        break;
    default:
        break;
    }
    return ret;
}

#define ANIM_STAT_HP      0
#define ANIM_STAT_ATK     1
#define ANIM_STAT_DEF     2
#define ANIM_STAT_SPATK   3
#define ANIM_STAT_SPDEF   4
#define ANIM_STAT_SPEED   5
#define ANIM_STAT_ACC     6
#define ANIM_STAT_EVASION 7
static void ChooseStatBoostAnimation(u32 battler)
{
    u32 stat;
    bool32 statBuffMoreThan1 = FALSE;
    u32 static const statsOrder[NUM_BATTLE_STATS] =
    {
        [ANIM_STAT_HP]      = STAT_HP,
        [ANIM_STAT_ATK]     = STAT_ATK,
        [ANIM_STAT_DEF]     = STAT_DEF,
        [ANIM_STAT_SPATK]   = STAT_SPATK,
        [ANIM_STAT_SPDEF]   = STAT_SPDEF,
        [ANIM_STAT_SPEED]   = STAT_SPEED,
        [ANIM_STAT_ACC]     = STAT_ACC,
        [ANIM_STAT_EVASION] = STAT_EVASION,
    };
    gBattleScripting.animArg1 = 0;

    for (stat = 1; stat < NUM_BATTLE_STATS; stat++) // Start loop at 1 to avoid STAT_HP
    {
        if ((gQueuedStatBoosts[battler].stats & (1 << statsOrder[stat])) == 0)
            continue;

        if (!statBuffMoreThan1)
            statBuffMoreThan1 = ((gQueuedStatBoosts[battler].stats & (1 << statsOrder[stat])) > 1);

        if (gBattleScripting.animArg1 != 0) // Already set in a different stat so now boosting multiple stats
            gBattleScripting.animArg1 = (statBuffMoreThan1 ? STAT_ANIM_MULTIPLE_PLUS2 : STAT_ANIM_MULTIPLE_PLUS1);
        else
            gBattleScripting.animArg1 = GET_STAT_BUFF_ID((statsOrder[stat] + 1)) + (statBuffMoreThan1 ? STAT_ANIM_PLUS2 : STAT_ANIM_PLUS1);
    }
}
#undef ANIM_STAT_HP
#undef ANIM_STAT_ATK
#undef ANIM_STAT_DEF
#undef ANIM_STAT_SPATK
#undef ANIM_STAT_SPDEF
#undef ANIM_STAT_SPEED
#undef ANIM_STAT_ACC
#undef ANIM_STAT_EVASION

u32 AbilityBattleEffects(u32 caseID, u32 battler, u32 ability, u32 special, u32 moveArg)
{
    u32 effect = 0;
    u32 speciesAtk, speciesDef;
    u32 moveType, move;
    u32 i, j;

    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return 0;

    if (gBattlerAttacker >= gBattlersCount)
        gBattlerAttacker = battler;

    speciesAtk = gBattleMons[gBattlerAttacker].species;
    speciesDef = gBattleMons[gBattlerTarget].species;

    if (special)
        gLastUsedAbility = special;
    else
        gLastUsedAbility = GetBattlerAbility(battler);

    if (moveArg)
        move = moveArg;
    else
        move = gCurrentMove;

    GET_MOVE_TYPE(move, moveType);

    switch (caseID)
    {
    case ABILITYEFFECT_SWITCH_IN_TERRAIN:
        gBattleScripting.battler = battler;
        if (VarGet(VAR_TERRAIN) & STATUS_FIELD_TERRAIN_ANY)
        {
            u16 terrainFlags = VarGet(VAR_TERRAIN) & STATUS_FIELD_TERRAIN_ANY; // only works for status flag (1 << 15)
            gFieldStatuses = terrainFlags | STATUS_FIELD_TERRAIN_PERMANENT;    // terrain is permanent
            switch (VarGet(VAR_TERRAIN) & STATUS_FIELD_TERRAIN_ANY)
            {
            case STATUS_FIELD_ELECTRIC_TERRAIN:
                gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                break;
            case STATUS_FIELD_MISTY_TERRAIN:
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                break;
            case STATUS_FIELD_GRASSY_TERRAIN:
                gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                break;
            case STATUS_FIELD_PSYCHIC_TERRAIN:
                gBattleCommunication[MULTISTRING_CHOOSER] = 3;
                break;
            }

            BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            effect++;
        }
#if B_THUNDERSTORM_TERRAIN == TRUE
        else if (GetCurrentWeather() == WEATHER_RAIN_THUNDERSTORM && !(gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN))
        {
            // overworld weather started rain, so just do electric terrain anim
            gFieldStatuses = (STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_TERRAIN_PERMANENT);
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
            BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            effect++;
        }
#endif
#if B_FOG_TERRAIN == TRUE
        else if ((GetCurrentWeather() == WEATHER_FOG_HORIZONTAL || GetCurrentWeather() == WEATHER_FOG_DIAGONAL) && !(gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN))
        {
            gFieldStatuses = (STATUS_FIELD_MISTY_TERRAIN | STATUS_FIELD_TERRAIN_PERMANENT);
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
            effect++;
        }
#endif
        break;
    case ABILITYEFFECT_SWITCH_IN_WEATHER:
        gBattleScripting.battler = battler;
        if (!(gBattleTypeFlags & BATTLE_TYPE_RECORDED))
        {
            switch (GetCurrentWeather())
            {
            case WEATHER_RAIN:
            case WEATHER_RAIN_THUNDERSTORM:
            case WEATHER_DOWNPOUR:
                if (!(gBattleWeather & B_WEATHER_RAIN))
                {
                    gBattleWeather = (B_WEATHER_RAIN_TEMPORARY | B_WEATHER_RAIN_PERMANENT);
                    gBattleScripting.animArg1 = B_ANIM_RAIN_CONTINUES;
                    effect++;
                }
                break;
            case WEATHER_SANDSTORM:
                if (!(gBattleWeather & B_WEATHER_SANDSTORM))
                {
                    gBattleWeather = B_WEATHER_SANDSTORM;
                    gBattleScripting.animArg1 = B_ANIM_SANDSTORM_CONTINUES;
                    effect++;
                }
                break;
            case WEATHER_DROUGHT:
                if (!(gBattleWeather & B_WEATHER_SUN))
                {
                    gBattleWeather = (B_WEATHER_SUN_PERMANENT | B_WEATHER_SUN_TEMPORARY);
                    gBattleScripting.animArg1 = B_ANIM_SUN_CONTINUES;
                    effect++;
                }
                break;
            case WEATHER_SNOW:
                if (!(gBattleWeather & (B_WEATHER_HAIL | B_WEATHER_SNOW)))
                {
#if B_OVERWORLD_SNOW >= GEN_9
                    gBattleWeather = B_WEATHER_SNOW;
                    gBattleScripting.animArg1 = B_ANIM_SNOW_CONTINUES;
                    effect++;
#else
                    gBattleWeather = B_WEATHER_HAIL;
                    gBattleScripting.animArg1 = B_ANIM_HAIL_CONTINUES;
                    effect++;
#endif
                }
                break;
            }
        }
        if (effect != 0)
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = GetCurrentWeather();
            BattleScriptPushCursorAndCallback(BattleScript_OverworldWeatherStarts);
        }
        break;
    case ABILITYEFFECT_ON_SWITCHIN: // 0
        gBattleScripting.battler = battler;
        switch (gLastUsedAbility)
        {
        case ABILITY_IMPOSTER:
            if (IsBattlerAlive(BATTLE_OPPOSITE(battler)) && !(gBattleMons[BATTLE_OPPOSITE(battler)].status2 & (STATUS2_TRANSFORMED | STATUS2_SUBSTITUTE)) && !(gBattleMons[battler].status2 & STATUS2_TRANSFORMED) && !(gBattleStruct->illusion[BATTLE_OPPOSITE(battler)].on) && !(gStatuses3[BATTLE_OPPOSITE(battler)] & STATUS3_SEMI_INVULNERABLE))
            {
                gBattlerAttacker = battler;
                gBattlerTarget = BATTLE_OPPOSITE(battler);
                BattleScriptPushCursorAndCallback(BattleScript_ImposterActivates);
                effect++;
            }
            break;
        case ABILITY_MOLD_BREAKER:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_MOLDBREAKER;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_TERAVOLT:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_TERAVOLT;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_TURBOBLAZE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_TURBOBLAZE;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_SLOW_START:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gDisableStructs[battler].slowStartTimer = 2;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_SLOWSTART;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_STARS_GRACE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gDisableStructs[battler].slowStartTimer = 3;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_STARSGRACE;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_UNNERVE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_UNNERVE;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_UnnerveActivates);
                effect++;
            }
            break;
        case ABILITY_FRISK:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_FriskActivates);
                effect++;
            }
            break;
        case ABILITY_HEARTSTRINGS:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_HeartstringsActivates);
                effect++;
            }
            break;
        case ABILITY_AS_ONE_ICE_RIDER:
        case ABILITY_AS_ONE_SHADOW_RIDER:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_ASONE;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_ActivateAsOne);
                effect++;
            }
            break;
        case ABILITY_CURIOUS_MEDICINE:
            if (!gSpecialStatuses[battler].switchInAbilityDone && IsDoubleBattle() && IsBattlerAlive(BATTLE_PARTNER(battler)) && TryResetBattlerStatChanges(BATTLE_PARTNER(battler)))
            {
                u32 i;
                gEffectBattler = BATTLE_PARTNER(battler);
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_CURIOUS_MEDICINE;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_PASTEL_VEIL:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerTarget = battler;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_PASTEL_VEIL;
                BattleScriptPushCursorAndCallback(BattleScript_PastelVeilActivates);
                effect++;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
            }
            break;
        case ABILITY_WATER_VEIL:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerTarget = battler;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_WATER_VEIL;
                BattleScriptPushCursorAndCallback(BattleScript_WaterVeilActivates);
                effect++;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
            }
            break;
        case ABILITY_DOWNLOAD:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                u32 statId, opposingBattler;
                u32 opposingDef = 0, opposingSpDef = 0;

                opposingBattler = BATTLE_OPPOSITE(battler);
                for (i = 0; i < 2; opposingBattler ^= BIT_FLANK, i++)
                {
                    if (IsBattlerAlive(opposingBattler))
                    {
                        opposingDef += gBattleMons[opposingBattler].defense * gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_DEF]][0] / gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_DEF]][1];
                        opposingSpDef += gBattleMons[opposingBattler].spDefense * gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_SPDEF]][0] / gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_SPDEF]][1];
                    }
                }

                if (opposingDef < opposingSpDef)
                    statId = STAT_ATK;
                else
                    statId = STAT_SPATK;

                gSpecialStatuses[battler].switchInAbilityDone = TRUE;

                if (CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    SET_STATCHANGER(statId, 1, FALSE);
                    gBattlerAttacker = battler;
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, statId);
                    BattleScriptPushCursorAndCallback(BattleScript_AttackerAbilityStatRaiseEnd3);
                    effect++;
                }
            }
            break;
        case ABILITY_PRESSURE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_PRESSURE;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_DARK_AURA:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_DARKAURA;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_FAIRY_AURA:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_FAIRYAURA;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_AURA_BREAK:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_AURABREAK;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_COMATOSE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_COMATOSE;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_SCREEN_CLEANER:
            if (!gSpecialStatuses[battler].switchInAbilityDone && TryRemoveScreens(battler))
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_SCREENCLEANER;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_FORECAST:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                i = Random() % 4;
                if (i == 0)
                {
                    goto RAIN;
                }
                else if (i == 1)
                {
                    goto SAND;
                }
                else if (i == 2)
                {
                    goto SUN;
                }
                else if (i == 3)
                {
                    goto HAIL;
                }
            }
            break;
        case ABILITY_DRIZZLE:
            RAIN:
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_RAIN, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_DrizzleActivates);
                effect++;
            }
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT && !gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_BlockedByPrimalWeatherEnd3);
                effect++;
            }
            break;
        case ABILITY_SAND_STREAM:
            SAND:
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_SANDSTORM, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_SandstreamActivates);
                effect++;
            }
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT && !gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_BlockedByPrimalWeatherEnd3);
                effect++;
            }
            break;
        case ABILITY_DROUGHT:
            SUN:
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_SUN, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_DroughtActivates);
                effect++;
            }
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT && !gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_BlockedByPrimalWeatherEnd3);
                effect++;
            }
            break;
        case ABILITY_SNOW_WARNING:
#if B_USE_SNOW == TRUE
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_SNOW, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_SnowWarningActivatesSnow);
                effect++;
            }
#else
            HAIL:
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_HAIL, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_SnowWarningActivatesHail);
                effect++;
            }
#endif
            else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT && !gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_BlockedByPrimalWeatherEnd3);
                effect++;
            }
            break;
        case ABILITY_GUSTY:
            if (!(gSideStatuses[GetBattlerSide(gBattlerAttacker)] & SIDE_STATUS_TAILWIND))
            {
                u8 side = GetBattlerSide(gBattlerAttacker);
                gBattlerAttacker = battler;
                gSideStatuses[side] |= SIDE_STATUS_TAILWIND;
                gSideTimers[side].tailwindBattlerId = gBattlerAttacker;
                gSideTimers[side].tailwindTimer = 4;
                BattleScriptPushCursorAndCallback(BattleScript_GustyActivatesTailwind);
                effect++;
            }
            break;
        case ABILITY_ALL_GAME:
            if (!(gFieldStatuses & STATUS_FIELD_MUDSPORT) && !(gFieldStatuses & STATUS_FIELD_WATERSPORT))
            {
                gFieldStatuses |= STATUS_FIELD_MUDSPORT;
                gFieldTimers.mudSportTimer = 5;
                gFieldStatuses |= STATUS_FIELD_WATERSPORT;
                gFieldTimers.waterSportTimer = 5;
                BattleScriptPushCursorAndCallback(BattleScript_MudWaterSportActivates);
                effect++;
            }
            else if ((!(gFieldStatuses & STATUS_FIELD_MUDSPORT)) && (gFieldStatuses & STATUS_FIELD_WATERSPORT))
            {
                gFieldStatuses |= STATUS_FIELD_MUDSPORT;
                gFieldTimers.mudSportTimer = 5;
                BattleScriptPushCursorAndCallback(BattleScript_MudSportActivates);
                effect++;
            }
            else if ((!(gFieldStatuses & STATUS_FIELD_WATERSPORT)) && (gFieldStatuses & STATUS_FIELD_MUDSPORT))
            {
                gFieldStatuses |= STATUS_FIELD_WATERSPORT;
                gFieldTimers.waterSportTimer = 5;
                BattleScriptPushCursorAndCallback(BattleScript_WaterSportActivates);
                effect++;
            }
            break;
        case ABILITY_ELECTRIC_SURGE:
        case ABILITY_HADRON_ENGINE:
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_ELECTRIC_TERRAIN, &gFieldTimers.terrainTimer))
            {
                BattleScriptPushCursorAndCallback(BattleScript_ElectricSurgeActivates);
                effect++;
            }
            break;
        case ABILITY_GRASSY_SURGE:
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_GRASSY_TERRAIN, &gFieldTimers.terrainTimer))
            {
                BattleScriptPushCursorAndCallback(BattleScript_GrassySurgeActivates);
                effect++;
            }
            break;
        case ABILITY_MISTY_SURGE:
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_MISTY_TERRAIN, &gFieldTimers.terrainTimer))
            {
                BattleScriptPushCursorAndCallback(BattleScript_MistySurgeActivates);
                effect++;
            }
            break;
        case ABILITY_PSYCHIC_SURGE:
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_PSYCHIC_TERRAIN, &gFieldTimers.terrainTimer))
            {
                BattleScriptPushCursorAndCallback(BattleScript_PsychicSurgeActivates);
                effect++;
            }
            break;
        case ABILITY_INTIMIDATE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                SET_STATCHANGER(STAT_ATK, 1, TRUE);
                BattleScriptPushCursorAndCallback(BattleScript_IntimidateActivates);
                effect++;
            }
            break;
        case ABILITY_WATCHER:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gDisableStructs[battler].watcherTimer = 2;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_WATCHER;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }
            break;
        case ABILITY_GLARING_STAGGER:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_GlaringStaggerActivates);
                effect++;
            }
            break;
        case ABILITY_EVIL_EYE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                SET_STATCHANGER(STAT_SPEED, 1, TRUE);
                BattleScriptPushCursorAndCallback(BattleScript_EvilEyeActivates);
                gHitMarker |= (HITMARKER_IGNORE_SAFEGUARD | HITMARKER_SYNCHRONIZE_SKIP);
                effect++;
            }
            break;
        case ABILITY_DISTURB:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                SET_STATCHANGER(STAT_SPATK, 1, TRUE);
                BattleScriptPushCursorAndCallback(BattleScript_DisturbActivates);
                effect++;
            }
            break;
        case ABILITY_MOCKING:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_MockingActivates);
                effect++;
            }
            break;
        case ABILITY_TRACE:
            if (!(gSpecialStatuses[battler].traced))
            {
                gBattleResources->flags->flags[battler] |= RESOURCE_FLAG_TRACED;
                gSpecialStatuses[battler].traced = TRUE;
            }
            break;
        case ABILITY_CLOUD_NINE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_AnnounceCloudNine);
                effect++;
            }
            break;
        case ABILITY_AIR_LOCK:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                TryChangeBattleWeather(battler, WEATHER_NONE, TRUE);
                BattleScriptPushCursorAndCallback(BattleScript_AnnounceAirLock);
                effect++;
            }
            break;
        case ABILITY_HUDDLE_UP:
            if (gBattleMons[battler].level < 25)
                break;
            if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_HP_PERCENT))
            {
                gBattlerAbility = gBattlerAttacker = battler;
                BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3);
                effect++;
            }
            break;
        case ABILITY_ZEN_MODE:
        case ABILITY_SHIELDS_DOWN:
            if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_HP_PERCENT))
            {
                gBattlerAbility = gBattlerAttacker = battler;
                BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3);
                effect++;
            }
            break;
        case ABILITY_ILLUMINATE:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                SET_STATCHANGER(STAT_ACC, 1, FALSE);
                BattleScriptPushCursorAndCallback(BattleScript_IlluminateActivates);
                effect++;
            }
            break;
        case ABILITY_INTREPID_SWORD:
            if (!gSpecialStatuses[battler].switchInAbilityDone && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                SET_STATCHANGER(STAT_ATK, 1, FALSE);
                BattleScriptPushCursorAndCallback(BattleScript_BattlerAbilityStatRaiseOnSwitchIn);
                effect++;
            }
            break;
        case ABILITY_DAUNTLESS_SHIELD:
            if (!gSpecialStatuses[battler].switchInAbilityDone && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                SET_STATCHANGER(STAT_DEF, 1, FALSE);
                BattleScriptPushCursorAndCallback(BattleScript_BattlerAbilityStatRaiseOnSwitchIn);
                effect++;
            }
            break;
        case ABILITY_WIND_RIDER:
            if (!gSpecialStatuses[battler].switchInAbilityDone
             && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN)
             && CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN)
             && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND
             || (gBattleWeather & B_WEATHER_SANDSTORM && WEATHER_HAS_EFFECT)))
            {
                gBattleScripting.savedBattler = gBattlerAttacker;
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_WindRiderStatRaiseOnSwitchIn);
                effect++;
            }
            break;
        case ABILITY_WIND_POWER:
            if (!gSpecialStatuses[battler].switchInAbilityDone
             && (!(gStatuses3[battler] & STATUS3_CHARGED_UP))
             && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND
             || (gBattleWeather & B_WEATHER_SANDSTORM && WEATHER_HAS_EFFECT)))
            {
                gBattleScripting.savedBattler = gBattlerAttacker;
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_WindPowerChargeOnSwitchIn);
                effect++;
            }
            break;
        case ABILITY_DESOLATE_LAND:
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_SUN_PRIMAL, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_DesolateLandActivates);
                effect++;
            }
            break;
        case ABILITY_PRIMORDIAL_SEA:
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_RAIN_PRIMAL, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_PrimordialSeaActivates);
                effect++;
            }
            break;
        case ABILITY_DELTA_STREAM:
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_STRONG_WINDS, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_DeltaStreamActivates);
                effect++;
            }
            break;
        case ABILITY_FALLING:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_FallingAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_TIME_TURN:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                if (!(gFieldStatuses & STATUS_FIELD_TRICK_ROOM))
                {
                    // Enable Trick Room
                    gFieldStatuses |= STATUS_FIELD_TRICK_ROOM;

                    if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_ROOM_EXTENDER)
                    {
                        gFieldTimers.trickRoomTimer = 4;
                    }
                    else
                    {
                        gFieldTimers.trickRoomTimer = 3;
                    }

                    BattleScriptPushCursorAndCallback(BattleScript_TimeTurnActivated);
                    effect++;
                }
                else
                {
                    // Removes Trick Room
                    gFieldTimers.trickRoomTimer = 0;
                    gFieldStatuses &= ~(STATUS_FIELD_TRICK_ROOM);
                    BattleScriptPushCursorAndCallback(BattleScript_TimeTurnDeactivated);
                    effect++;
                }
            }
            break;
        case ABILITY_MIND_GAMES:
            if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
            {
                gFieldStatuses |= STATUS_FIELD_GRAVITY;
                gFieldTimers.gravityTimer = 6;
                BattleScriptPushCursorAndCallback(BattleScript_GravityWellActivates);
                effect++;
            }
            if (TryChangeBattleTerrain(battler, STATUS_FIELD_PSYCHIC_TERRAIN, &gFieldTimers.terrainTimer))
            {
                BattleScriptPushCursorAndCallback(BattleScript_PsychicSurgeActivates);
                effect++;
            }
            break;
        case ABILITY_REVERSI:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                if (!(gFieldStatuses & STATUS_FIELD_INVERSE_ROOM))
                {
                    // Enable Inverse Room
                    gFieldStatuses |= STATUS_FIELD_INVERSE_ROOM;

                    if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_ROOM_EXTENDER)
                    {
                        gFieldTimers.inverseRoomTimer = 8;
                    }
                    else
                    {
                        gFieldTimers.inverseRoomTimer = 5;
                    }

                    BattleScriptPushCursorAndCallback(BattleScript_ReversiActivated);
                    effect++;
                }
                else
                {
                    // Removes Inverse Room
                    gFieldTimers.inverseRoomTimer = 0;
                    gFieldStatuses &= ~(STATUS_FIELD_INVERSE_ROOM);
                    BattleScriptPushCursorAndCallback(BattleScript_ReversiDeactivated);
                    effect++;
                }
            }
            break;
        case ABILITY_WHITE_SMOKE:
            if (!(gSideStatuses[GetBattlerSide(gBattlerAttacker)] & SIDE_STATUS_MIST))
            {
                u8 side = GetBattlerSide(gBattlerAttacker);
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                gSideStatuses[side] |= SIDE_STATUS_MIST;
                gSideTimers[side].mistBattlerId = battler;
                gSideTimers[side].mistTimer = 5;
                BattleScriptPushCursorAndCallback(BattleScript_WhiteSmokeAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_RUIN_WARD:
            if (!(gSideStatuses[GetBattlerSide(gBattlerAttacker)] & SIDE_STATUS_SAFEGUARD))
            {
                u8 side = GetBattlerSide(gBattlerAttacker);
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                gSideStatuses[side] |= SIDE_STATUS_SAFEGUARD;
                gSideTimers[side].safeguardBattlerId = battler;
                gSideTimers[side].safeguardTimer = 5;
                BattleScriptPushCursorAndCallback(BattleScript_RuinWardSafeguardActivates);
                effect++;
            }
            break;
        case ABILITY_GRAVITY_WELL:
            if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
            {
                gBattlerAttacker = battler;
                gFieldStatuses |= STATUS_FIELD_GRAVITY;
                gFieldTimers.gravityTimer = 6;
                BattleScriptPushCursorAndCallback(BattleScript_GravityWellActivates);
                effect++;
            }
            break;
        case ABILITY_ENTRANCING:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                gSideTimers[GetBattlerSide(battler)].followmeTimer = 1;
                gSideTimers[GetBattlerSide(battler)].followmeTarget = gBattlerAttacker;
                BattleScriptPushCursorAndCallback(BattleScript_EntrancingAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_MAGICIAN:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_MagicianAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_VESSEL_OF_RUIN:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPATK);
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_SWORD_OF_RUIN:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_DEF);
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_TABLETS_OF_RUIN:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_ATK);
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_SPIRALYSIS:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPEED);
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_BEADS_OF_RUIN:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPDEF);
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                BattleScriptPushCursorAndCallback(BattleScript_RuinAbilityActivates);
                effect++;
            }
            break;
        case ABILITY_ORICHALCUM_PULSE:
            if (TryChangeBattleWeather(battler, ENUM_WEATHER_SUN, TRUE))
            {
                BattleScriptPushCursorAndCallback(BattleScript_DroughtActivates);
                effect++;
            }
            break;
        case ABILITY_SUPREME_OVERLORD:
            if (!gSpecialStatuses[battler].switchInAbilityDone)
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                gBattleStruct->supremeOverlordCounter[battler] = min(5, gBattleStruct->faintedMonCount[GetBattlerSide(battler)]);
                BattleScriptPushCursorAndCallback(BattleScript_SupremeOverlordActivates);
                effect++;
            }
            break;
        case ABILITY_COSTAR:
            if (!gSpecialStatuses[battler].switchInAbilityDone && IsDoubleBattle() && IsBattlerAlive(BATTLE_PARTNER(battler)) && CountBattlerStatIncreases(BATTLE_PARTNER(battler), FALSE))
            {
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                for (i = 0; i < NUM_BATTLE_STATS; i++)
                    gBattleMons[battler].statStages[i] = gBattleMons[BATTLE_PARTNER(battler)].statStages[i];
                gBattlerTarget = BATTLE_PARTNER(battler);
                BattleScriptPushCursorAndCallback(BattleScript_CostarActivates);
                effect++;
            }
            break;
        case ABILITY_HEALER:
            if (!gSpecialStatuses[battler].switchInAbilityDone && IsDoubleBattle() && gBattleMons[BATTLE_PARTNER(battler)].hp < gBattleMons[BATTLE_PARTNER(battler)].maxHP)
            {
                gBattlerTarget = BATTLE_PARTNER(battler);
                gBattlerAttacker = battler;
                gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                gBattleMoveDamage = (gBattleMons[BATTLE_PARTNER(battler)].maxHP / 3) * -1;
                BattleScriptPushCursorAndCallback(BattleScript_HealerActivates2);
                effect++;
            }
            break;
        }
        break;
    case ABILITYEFFECT_ENDTURN: // 1
        if (gBattleMons[battler].hp != 0)
        {
            gBattlerAttacker = battler;
            switch (gLastUsedAbility)
            {
            case ABILITY_SUNRISE:
                if (gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2)
                {
                    if (TryChangeBattleWeather(battler, ENUM_WEATHER_SUN, TRUE))
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_SunriseActivates);
                        effect++;
                    }
                    else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_BlockedByPrimalWeatherEnd3);
                        effect++;
                    }
                }
                break;
            case ABILITY_DELUGE:
                if (IsBattlerWeatherAffected(battler, B_WEATHER_RAIN))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_DelugeHurts);
                    effect++;
                }
                else if (gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2)
                {
                    if (TryChangeBattleWeather(battler, ENUM_WEATHER_RAIN, TRUE))
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_DelugeActivates);
                        effect++;
                    }
                    else if (gBattleWeather & B_WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_BlockedByPrimalWeatherEnd3);
                        effect++;
                    }
                }
                break;
            case ABILITY_HARVEST:
                if ((IsBattlerWeatherAffected(battler, B_WEATHER_SUN) || Random() % 2 == 0) && gBattleMons[battler].item == ITEM_NONE && gBattleStruct->changedItems[battler] == ITEM_NONE // Will not inherit an item
                    && ItemId_GetPocket(GetUsedHeldItem(battler)) == POCKET_BERRIES)
                {
                    gLastUsedItem = GetUsedHeldItem(battler);
                    BattleScriptPushCursorAndCallback(BattleScript_HarvestActivates);
                    effect++;
                }
                break;
            case ABILITY_VITAL_SPIRIT:
                if ((gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2) && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK) && IsBattlerAlive(battler))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                    BattleScriptPushCursorAndCallback(BattleScript_RainDishActivates);
                    effect++;
                }
                break;
            case ABILITY_LOVESICK:
                if (IsBattlerAlive(battler) && (!(gBattleMons[battler].status2 & STATUS2_INFATUATION)))
                {
                    gBattlerAttacker = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_LovesickActivates);
                    effect++;
                }
                break;
            case ABILITY_RESET:
                if (!BATTLER_MAX_HP(battler) 
                && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK) 
                && IsBattlerAlive(battler))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                    BattleScriptPushCursorAndCallback(BattleScript_RainDishActivates);
                    effect++;
                }
                if (gBattleMons[battler].status1 & STATUS1_ANY)
                {
                    BufferStatusCondition(battler, FALSE);
                    gBattleMons[battler].status1 = 0;
                    gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
                    gBattleScripting.battler = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_ShedSkinActivates);
                    BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                    MarkBattlerForControllerExec(battler);
                    effect++;
                }
                if (CountBattlerStatIncreases(battler, TRUE) > 0 || CountBattlerStatDecreases(battler, TRUE) > 0)
                {
                    BattleScriptPushCursorAndCallback(BattleScript_NormaliseBuffs);
                    effect++;
                }
                break;
            case ABILITY_DRY_SKIN:
                if (IsBattlerWeatherAffected(battler, B_WEATHER_SUN))
                {
                SOLAR_POWER_HP_DROP:
                    BattleScriptPushCursorAndCallback(BattleScript_SolarPowerActivates);
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    effect++;
                }
            // Dry Skin works similarly to Rain Dish in Rain
            case ABILITY_RAIN_DISH:
                if (IsBattlerWeatherAffected(battler, B_WEATHER_RAIN) 
                && !BATTLER_MAX_HP(battler) 
                && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_RainDishActivates);
                    gBattleMoveDamage = gBattleMons[battler].maxHP / (gLastUsedAbility == ABILITY_RAIN_DISH ? 16 : 8);
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                    effect++;
                }
                break;
            case ABILITY_HYDRATION:
                if (IsBattlerWeatherAffected(battler, B_WEATHER_RAIN) 
                && !BATTLER_MAX_HP(battler)
                && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK)
                && (gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE) 
                && (Random() % 3) == 0)
                {
                    BufferStatusCondition(battler, FALSE);
                    gBattleMons[battler].status1 = 0;
                    gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
                    gBattleScripting.battler = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_HydrationActivates);
                    BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                    MarkBattlerForControllerExec(battler);
                    gBattleMoveDamage = gBattleMons[battler].maxHP / (gLastUsedAbility == ABILITY_HYDRATION ? 16 : 8);
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                    effect++;
                }
                else if (IsBattlerWeatherAffected(battler, B_WEATHER_RAIN) 
                && !BATTLER_MAX_HP(battler)
                && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_RainDishActivates);
                    gBattleMoveDamage = gBattleMons[battler].maxHP / (gLastUsedAbility == ABILITY_HYDRATION ? 16 : 8);
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                    effect++;
                }
                else if (IsBattlerWeatherAffected(battler, B_WEATHER_RAIN) 
                && (gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE) 
                && (Random() % 3) == 0)
                {
                    goto ABILITY_HEAL_MON_STATUS;
                }
                break;
            case ABILITY_SHED_SKIN:
                if ((gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE) && (Random() % 2) == 0)
                {
                ABILITY_HEAL_MON_STATUS:
                    BufferStatusCondition(battler, FALSE);
                    gBattleMons[battler].status1 = 0;
                    gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
                    gBattleScripting.battler = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_ShedSkinActivates);
                    BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                    MarkBattlerForControllerExec(battler);
                    effect++;
                }
                break;
            case ABILITY_SPEED_BOOST:
                if (CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN) && gDisableStructs[battler].isFirstTurn != 2)
                {
                    SET_STATCHANGER(STAT_SPEED, 1, FALSE);
                    BattleScriptPushCursorAndCallback(BattleScript_SpeedBoostActivates);
                    gBattleScripting.battler = battler;
                    effect++;
                }
                break;
            case ABILITY_ARBITER:
                BattleScriptPushCursorAndCallback(BattleScript_ArbiterActivates);
                effect++;
                break;
            case ABILITY_WATCHER:
                if (gDisableStructs[battler].watcherTimer
                && --gDisableStructs[battler].watcherTimer == 0)
                {
                    gBattlerAttacker = battler;
                    gDisableStructs[battler].watcherTimer = 2;
                    BattleScriptPushCursorAndCallback(BattleScript_WatcherActivates);
                    effect++;
                }
                break;
            case ABILITY_STARS_GRACE:
                if (gDisableStructs[battler].slowStartTimer
                && --gDisableStructs[battler].slowStartTimer == 0)
                {
                    gBattlerAttacker = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_StarsGraceStarts);
                    effect++;
                }
                break;
            case ABILITY_SLOW_START:
                if (gDisableStructs[battler].slowStartTimer
                && --gDisableStructs[battler].slowStartTimer == 0)
                {
                    gBattlerAttacker = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_SlowStartEnds);
                    effect++;
                }
                break;
            case ABILITY_MOODY:
                if (gDisableStructs[battler].isFirstTurn != 2)
                {
                    u32 validToRaise = 0, validToLower = 0;
#if B_MOODY_ACC_EVASION < GEN_8
                    u32 statsNum = NUM_BATTLE_STATS;
#else
                    u32 statsNum = NUM_STATS;
#endif

                    for (i = STAT_ATK; i < statsNum; i++)
                    {
                        if (CompareStat(battler, i, MIN_STAT_STAGE, CMP_GREATER_THAN))
                            validToLower |= gBitTable[i];
                        if (CompareStat(battler, i, MAX_STAT_STAGE, CMP_LESS_THAN))
                            validToRaise |= gBitTable[i];
                    }

                    if (validToLower != 0 || validToRaise != 0) // Can lower one stat, or can raise one stat
                    {
                        gBattleScripting.statChanger = gBattleScripting.savedStatChanger = 0; // for raising and lowering stat respectively
                        if (validToRaise != 0)                                                // Find stat to raise
                        {
                            do
                            {
                                i = (Random() % statsNum) + STAT_ATK;
                            } while (!(validToRaise & gBitTable[i]));
                            SET_STATCHANGER(i, 2, FALSE);
                            validToLower &= ~(gBitTable[i]); // Can't lower the same stat as raising.
                        }
                        if (validToLower != 0) // Find stat to lower
                        {
                            do
                            {
                                i = (Random() % statsNum) + STAT_ATK;
                            } while (!(validToLower & gBitTable[i]));
                            SET_STATCHANGER2(gBattleScripting.savedStatChanger, i, 1, TRUE);
                        }
                        BattleScriptPushCursorAndCallback(BattleScript_MoodyActivates);
                        effect++;
                    }
                }
                break;
            case ABILITY_SADDENED:
                if (gDisableStructs[battler].isFirstTurn != 2)
                {
                    u32 validToLower = 0;
                    u32 statsNum = NUM_STATS;
                    for (i = STAT_ATK; i < statsNum; i++)
                    {
                        if (CompareStat(battler, i, MIN_STAT_STAGE, CMP_GREATER_THAN))
                            validToLower |= gBitTable[i];
                    }

                    if (validToLower != 0) // Can lower one stat
                    {
                        gBattleScripting.statChanger = gBattleScripting.savedStatChanger = 0; // for raising and lowering stat respectively
                        if (validToLower != 0)                                                // Find stat to lower
                        {
                            do
                            {
                                i = (Random() % statsNum) + STAT_ATK;
                            } while (!(validToLower & gBitTable[i]));
                            SET_STATCHANGER2(gBattleScripting.savedStatChanger, i, 2, TRUE);
                        }
                        BattleScriptPushCursorAndCallback(BattleScript_MoodyActivates);
                        effect++;
                    }
                }
                break;
            case ABILITY_TRUANT:
                if (!(gBattleMoves[gCurrentMove].lazyMove))
                    gDisableStructs[gBattlerAttacker].truantCounter ^= 1;
                break;
            case ABILITY_BAD_DREAMS:
                BattleScriptPushCursorAndCallback(BattleScript_BadDreamsActivates);
                effect++;
                break;
            case ABILITY_MIASMA:
                BattleScriptPushCursorAndCallback(BattleScript_MiasmaActivates);
                effect++;
                break;
            case ABILITY_SOLAR_POWER:
                if (IsBattlerWeatherAffected(battler, B_WEATHER_SUN) 
                && gDisableStructs[battler].daybreakCounter < 3
                && gDisableStructs[battler].daybreakCounter != 0)
                {
                    gDisableStructs[gBattlerAttacker].daybreakCounter++;
                    PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 1, gDisableStructs[gBattlerAttacker].daybreakCounter);
                    BattleScriptPushCursorAndCallback(BattleScript_SolarPowerActivatesSunEveryone);
                    effect++;
                }
                else if (IsBattlerWeatherAffected(battler, B_WEATHER_SUN) && gDisableStructs[battler].daybreakCounter < 3)
                {
                    gDisableStructs[gBattlerAttacker].daybreakCounter++;
                    PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 1, gDisableStructs[gBattlerAttacker].daybreakCounter);
                    BattleScriptPushCursorAndCallback(BattleScript_SolarPowerActivatesSun);
                    effect++;
                }
                else if (IsBattlerWeatherAffected(battler, B_WEATHER_SUN) && gDisableStructs[battler].daybreakCounter != 0)
                {
                    BattleScriptPushCursorAndCallback(BattleScript_SolarPowerActivatesEveryone);
                    effect++;
                }
                break;
            case ABILITY_ICE_SCALES:
                if (IsBattlerWeatherAffected(battler, B_WEATHER_HAIL)
                && (gDisableStructs[gBattlerAttacker].iceScalesCounter < 5))
                {
                    gDisableStructs[gBattlerAttacker].iceScalesCounter++;
                    PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 1, gDisableStructs[gBattlerAttacker].iceScalesCounter);
                    BattleScriptPushCursorAndCallback(BattleScript_IceScalesActivatesHail);
                    effect++;
                }
                break;
            case ABILITY_HEALER:
                gBattleScripting.battler = BATTLE_PARTNER(battler);
                if (IsBattlerAlive(gBattleScripting.battler) && gBattleMons[gBattleScripting.battler].status1 & STATUS1_ANY_NEGATIVE && (Random() % 100) < 30)
                {
                    BattleScriptPushCursorAndCallback(BattleScript_HealerActivates);
                    effect++;
                }
                break;
            case ABILITY_HUDDLE_UP:
                if (gBattleMons[battler].level < 25)
                    break;
                if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_HP_PERCENT))
                {
                    gBattlerAbility = gBattlerAttacker = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3);
                    effect++;
                }
                if ((gBattleMons[battler].level >= 40) && !BATTLER_MAX_HP(battler) && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_RainDishActivates);
                    gBattleMoveDamage = gBattleMons[battler].maxHP / (gLastUsedAbility == ABILITY_HUDDLE_UP ? 16 : 8);
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                    effect++;
                }
                break;
            // Fallthrough
            case ABILITY_ZEN_MODE:
            case ABILITY_SHIELDS_DOWN:
            case ABILITY_DORMANT:
                if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_HP_PERCENT))
                {
                    gBattlerAbility = gBattlerAttacker = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3);
                    effect++;
                }
                break;
            case ABILITY_BALL_FETCH:
                if (gBattleMons[battler].item == ITEM_NONE && gBattleResults.catchAttempts[gLastUsedBall - ITEM_ULTRA_BALL] >= 1 && !gHasFetchedBall)
                {
                    gBattleScripting.battler = battler;
                    BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, 2, &gLastUsedBall);
                    MarkBattlerForControllerExec(battler);
                    gHasFetchedBall = TRUE;
                    gLastUsedItem = gLastUsedBall;
                    BattleScriptPushCursorAndCallback(BattleScript_BallFetch);
                    effect++;
                }
                break;
            case ABILITY_GOLDEN_MEAN:
                if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_TURN_END))
                {
                    gBattlerAbility = gBattlerAttacker = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3NoPopup);
                    effect++;
                }
                break;
            case ABILITY_CUD_CHEW:
                if (ItemId_GetPocket(GetUsedHeldItem(battler)) == POCKET_BERRIES && gDisableStructs[battler].cudChew == TRUE)
                {
                    gLastUsedItem = gBattleStruct->usedHeldItems[battler][GetBattlerSide(battler)];
                    gBattleStruct->usedHeldItems[battler][GetBattlerSide(battler)] = ITEM_NONE;
                    BattleScriptPushCursorAndCallback(BattleScript_CudChewActivates);
                    effect++;
                }
                break;
                
            // shunyong effects
            case ABILITY_SHUNYONG:
                if (gDisableStructs[battler].isFirstTurn != 2)
                {
                    s32 sBattlerTargetPlayerRight = B_POSITION_PLAYER_RIGHT; 
                    u32 validToRaise = 0, validToLowerLeft = 0, validToLowerRight;
                #if B_MOODY_ACC_EVASION < GEN_8
                    u32 statsNum = NUM_BATTLE_STATS;
                #else
                    u32 statsNum = NUM_STATS;
                #endif

                    for (i = STAT_ATK; i < statsNum; i++)
                    {
                        if (CompareStat(gBattlerTarget, i, MIN_STAT_STAGE, CMP_GREATER_THAN))
                            validToLowerLeft |= gBitTable[i];
                        if (CompareStat(sBattlerTargetPlayerRight, i, MIN_STAT_STAGE, CMP_GREATER_THAN))
                            validToLowerRight |= gBitTable[i];
                        if (CompareStat(battler, i, MAX_STAT_STAGE, CMP_LESS_THAN))
                            validToRaise |= gBitTable[i];
                    }

                    if(gBattleMons[battler].species == SPECIES_SHUNYONG)
                        validToRaise = 0; // makes it so shunyongs stats wont increase in offensive form
                    if(gBattleMons[battler].species == SPECIES_SHUNYONG_GOLDEN_OFFENSE)
                    {
                        validToLowerLeft = 0; // makes it so opponents stats wont lower when in defensive form
                        validToLowerRight = 0; // makes it so opponents stats wont lower when in defensive form
                        gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK; //sets so offensive form can't heal
                        gDisableStructs[gBattlerTarget].healBlockTimer = 2; //sets so offensive form can't heal
                        gStatuses3[sBattlerTargetPlayerRight] |= STATUS3_HEAL_BLOCK; //sets so offensive form can't heal
                        gDisableStructs[sBattlerTargetPlayerRight].healBlockTimer = 2; //sets so offensive form can't heal
                        BattleScriptPushCursorAndCallback(BattleScript_ShunyongCantHealInOffensiveForm);
                        effect++;
                    }

                    if (validToLowerLeft != 0 || validToRaise != 0 || validToLowerRight != 0) // Can lower one stat, or can raise one stat
                    {
                        gBattleScripting.statChanger = gBattleScripting.savedStatChanger = 0; // for raising and lowering stat respectively
                        if (validToRaise != 0) // Find stat to raise
                        {
                            do
                            {
                                i = (Random() % statsNum) + STAT_ATK;
                            } while (!(validToRaise & gBitTable[i]));
                            SET_STATCHANGER(i, 2, FALSE);
                            validToLowerLeft &= ~(gBitTable[i]); // Can't lower the same stat as raising.
                        }
                        if (validToLowerLeft != 0) // Find stat to lower
                        {
                            do
                            {
                                i = (Random() % statsNum) + STAT_ATK;
                            } while (!(validToLowerLeft & gBitTable[i]));
                            SET_STATCHANGER2(gBattleScripting.savedStatChanger, i, 1, TRUE);
                        }
                        if (validToLowerRight != 0) // Find stat to lower
                        {
                            do
                            {
                                i = (Random() % statsNum) + STAT_ATK;
                            } while (!(validToLowerRight & gBitTable[i]));
                            SET_STATCHANGER2(gBattleScripting.savedStatChanger, i, 1, TRUE);
                        }
                        BattleScriptPushCursorAndCallback(BattleScript_ShunyongAbilityActivates);
                        effect++;
                    }
                }

                if (TryBattleFormChange(battler, FORM_CHANGE_BATTLE_TURN_END))
                {
                    gBattlerAbility = gBattlerAttacker = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3NoPopup);
                    effect++;
                }
                
                if(gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE)
                    gBattleResults.shunyongStatusCounter++;
                else
                    gBattleResults.shunyongStatusCounter = 0;
                break;
            }
        }
        break;
    case ABILITYEFFECT_MOVES_BLOCK: // 2
    {
        u16 moveTarget = GetBattlerMoveTargetType(battler, move);
        u16 battlerAbility = GetBattlerAbility(battler);
        u16 targetAbility = GetBattlerAbility(gBattlerTarget);

        if ((gLastUsedAbility == ABILITY_SOUNDPROOF && gBattleMoves[move].soundMove && !(moveTarget & MOVE_TARGET_USER)) 
        || (gLastUsedAbility == ABILITY_BULLETPROOF && gBattleMoves[move].ballisticMove) 
        || (gLastUsedAbility == ABILITY_BALL_FETCH && gBattleMoves[move].ballisticMove && GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_WINTAMEL_TEA && gBattleMons[gBattlerTarget].species == SPECIES_POMELONIAN))
        {
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)
                gHitMarker |= HITMARKER_NO_PPDEDUCT;
            gBattlescriptCurrInstr = BattleScript_SoundproofProtected;
            effect = 1;
        }
        else if ((gLastUsedAbility == ABILITY_DAZZLING || gLastUsedAbility == ABILITY_QUEENLY_MAJESTY || gLastUsedAbility == ABILITY_ARMOR_TAIL || IsBattlerAlive(battler ^= BIT_FLANK)) && (battlerAbility == ABILITY_DAZZLING || battlerAbility == ABILITY_QUEENLY_MAJESTY || battlerAbility == ABILITY_ARMOR_TAIL) && GetChosenMovePriority(gBattlerAttacker) > 0 && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(battler))
        {
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)
                gHitMarker |= HITMARKER_NO_PPDEDUCT;
            gBattlescriptCurrInstr = BattleScript_DazzlingProtected;
            effect = 1;
        }
        else if (GetBattlerAbility(gBattlerTarget) == ABILITY_GOOD_AS_GOLD && IS_MOVE_STATUS(gCurrentMove) && !(moveTarget & MOVE_TARGET_USER) && !(moveTarget & MOVE_TARGET_OPPONENTS_FIELD) && !(moveTarget & MOVE_TARGET_ALL_BATTLERS))
        {
            gBattlescriptCurrInstr = BattleScript_GoodAsGoldActivates;
            effect = 1;
        }
        else if (gLastUsedAbility == ABILITY_ICE_FACE && IS_MOVE_PHYSICAL(move) && gBattleMons[gBattlerTarget].species == SPECIES_EISCUE)
        {
            gBattleMons[gBattlerTarget].species = SPECIES_EISCUE_NOICE_FACE;
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)
                gHitMarker |= HITMARKER_NO_PPDEDUCT;
            gBattleScripting.battler = gBattlerTarget; // For STRINGID_PKMNTRANSFORMED
            gBattlescriptCurrInstr = BattleScript_IceFaceNullsDamage;
            effect = 1;
        }
        break;
    }
    case ABILITYEFFECT_ABSORBING: // 3
        if (move != MOVE_NONE)
        {
            u8 statId, statId2;
            u8 statAmount = 1, statAmount2;
            switch (gLastUsedAbility)
            {
            case ABILITY_VOLT_ABSORB:
                if (moveType == TYPE_ELECTRIC)
                    effect = 1;
                break;
            case ABILITY_WATER_ABSORB:
                if (moveType == TYPE_WATER)
                    effect = 1;
                break;
            case ABILITY_DRY_SKIN:
                if (moveType == TYPE_WATER)
                    effect = 4, statId = STAT_SPEED;
                break;
            case ABILITY_WITCHCRAFT:
                if (moveType == TYPE_FAIRY)
                    effect = 2, statId = STAT_SPATK;
                break;
            case ABILITY_MOTOR_DRIVE:
                if (moveType == TYPE_ELECTRIC)
                    effect = 2, statId = STAT_SPEED;
                break;
            case ABILITY_LIGHTNING_ROD:
                if (moveType == TYPE_ELECTRIC)
                    effect = 2, statId = STAT_SPATK;
                break;
            case ABILITY_SOUL_LOCKER:
                if (moveType == TYPE_GHOST)
                    effect = 2, statId = STAT_SPATK;
                break;
            case ABILITY_MAGNET_PULL:
                if (moveType == TYPE_STEEL)
                    effect = 2, statId = STAT_ATK;
                break;
            case ABILITY_STORM_DRAIN:
                if (moveType == TYPE_WATER)
                    effect = 2, statId = STAT_SPATK;
                break;
            case ABILITY_SAP_SIPPER:
                if (moveType == TYPE_GRASS)
                    effect = 2, statId = STAT_ATK;
                break;
            case ABILITY_FLASH_FIRE:
                if (moveType == TYPE_FIRE)
                    effect = 2, statId = STAT_ATK;
                break;
            case ABILITY_WELL_BAKED_BODY:
                if (moveType == TYPE_FIRE)
                    effect = 2, statId = STAT_DEF, statAmount = 2;
                break;
            case ABILITY_WIND_RIDER:
                if (gBattleMoves[gCurrentMove].windMove
                    && !(GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove) & MOVE_TARGET_USER)
                    && !(GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove) & MOVE_TARGET_ALL_BATTLERS))
                    effect = 3;
                break;
            case ABILITY_WIND_POWER:
                if (gBattleMoves[gCurrentMove].windMove 
                    && !(GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove) & MOVE_TARGET_USER)
                    && !(GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove) & MOVE_TARGET_ALL_BATTLERS))
                    effect = 5;
                break;
            case ABILITY_EARTH_EATER:
                if (moveType == TYPE_GROUND)
                    effect = 1;
                break;
            }

            if (effect == 1) // Drain Hp ability.
            {
#if B_HEAL_BLOCKING >= GEN_5
                if (BATTLER_MAX_HP(battler) || gStatuses3[battler] & STATUS3_HEAL_BLOCK)
#else
                if (BATTLER_MAX_HP(battler))
#endif
                {
                    if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                    else
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                }
                else
                {
                    if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                        gBattlescriptCurrInstr = BattleScript_MoveHPDrain;
                    else
                        gBattlescriptCurrInstr = BattleScript_MoveHPDrain_PPLoss;

                    gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                }
            }
            else if (effect == 2) // Boost Stat ability;
            {
                if (!CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                    else
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                }
                else
                {
                    if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                        gBattlescriptCurrInstr = BattleScript_MoveStatDrain;
                    else
                        gBattlescriptCurrInstr = BattleScript_MoveStatDrain_PPLoss;

                    SET_STATCHANGER(statId, statAmount, FALSE);
                }
            }
            else if (effect == 3) // Boost 2 Stat ability;
            {
                if (!CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN) && !CompareStat(battler, statId2, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                    else
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                }
                else
                {
                    if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                        gBattlescriptCurrInstr = BattleScript_MoveStatDrain2;
                    else
                        gBattlescriptCurrInstr = BattleScript_MoveStatDrain2_PPLoss;
                }
            }
            else if (effect == 4) // Dry Skin Heal + Stat Up
            {
                if (!CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN) && (BATTLER_MAX_HP(battler) || gStatuses3[battler] & STATUS3_HEAL_BLOCK))
                {
                    if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                    else
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                }
                else if (CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN) && (BATTLER_MAX_HP(battler) || gStatuses3[battler] & STATUS3_HEAL_BLOCK))
                {
                    if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                        gBattlescriptCurrInstr = BattleScript_MoveStatDrain;
                    else
                        gBattlescriptCurrInstr = BattleScript_MoveStatDrain_PPLoss;

                    SET_STATCHANGER(statId, statAmount, FALSE);
                }
                else if (!CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN) && (!(BATTLER_MAX_HP(battler) || gStatuses3[battler] & STATUS3_HEAL_BLOCK)))
                {
                    if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                        gBattlescriptCurrInstr = BattleScript_MoveHPDrain;
                    else
                        gBattlescriptCurrInstr = BattleScript_MoveHPDrain_PPLoss;

                    gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                }
                else
                {
                    if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                        gBattlescriptCurrInstr = BattleScript_DrySkinHealStatUp;
                    else
                        gBattlescriptCurrInstr = BattleScript_DrySkinHealStatUp_PPLoss;

                    SET_STATCHANGER(statId, statAmount, FALSE);

                    gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                }
            }
            else if (effect == 5) // Wind Power Charge
            {
                if (gStatuses3[battler] & STATUS3_CHARGED_UP)
                {
                    if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                    else
                        gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                }
                else
                {
                    if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                        gBattlescriptCurrInstr = BattleScript_WindPowerCharge;
                    else
                        gBattlescriptCurrInstr = BattleScript_WindPowerCharge_PPLoss;

                    SET_STATCHANGER(statId, statAmount, FALSE);
                }
            }
            if (effect)
                gMultiHitCounter = 0; // Prevent multi-hit moves from hitting more than once after move has been absorbed.
        }
        break;
    case ABILITYEFFECT_MOVE_END: // Think contact abilities.
        switch (gLastUsedAbility)
        {
        case ABILITY_GHOULISH:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK) && !BATTLER_MAX_HP(battler) && gBattlerAttacker != gBattlerTarget)
            {
                gEffectBattler = battler;
                gBattleMoveDamage = (gSpecialStatuses[gBattlerTarget].shellBellDmg / 3);
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                gBattleMoveDamage *= -1;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, GetBattlerAbility(gBattlerTarget));
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityHealHP_Ret;
                effect++;
            }
            break;
        case ABILITY_JUSTIFIED:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && moveType == TYPE_DARK && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_ATK, 1, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_TOXIC_BOOST:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && moveType == TYPE_POISON && CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_FLARE_BOOST:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && moveType == TYPE_FIRE && CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_RATTLED:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && (moveType == TYPE_DARK || moveType == TYPE_BUG || moveType == TYPE_GHOST) && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_SPEED, 2, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_WATER_COMPACTION:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && moveType == TYPE_WATER && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_DEF, 2, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_DRY_SKIN:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && moveType == TYPE_FIRE && CompareStat(battler, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_SPEED, 1, TRUE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatDropRet;
                effect++;
            }
            break;
        case ABILITY_MAGMA_ARMOR:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                && TARGET_TURN_DAMAGED
                && IsBattlerAlive(battler)
                && moveType == TYPE_WATER
                && (!(gDisableStructs[battler].magmaArmored)))
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilitySetMagmaArmored;
                effect++;
            }
            break;
        case ABILITY_STAMINA:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
             && gBattlerAttacker != gBattlerTarget
             && TARGET_TURN_DAMAGED
             && IsBattlerAlive(battler)
             && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_DEF, 1, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_HARDBOILED:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattlerAttacker != gBattlerTarget 
            && TARGET_TURN_DAMAGED && IsBattlerAlive(battler)
            && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN)
            && CompareStat(battler, STAT_SPDEF, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                if (CalcTypeEffectivenessMultiplier(move, moveType, battler, gBattlerTarget, GetBattlerAbility(gBattlerTarget), FALSE) == UQ_4_12(2.0))
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_HardboiledActivates;
                    effect++;
                }
                else if (CalcTypeEffectivenessMultiplier(move, moveType, battler, gBattlerTarget, GetBattlerAbility(gBattlerTarget), FALSE) > UQ_4_12(2.0))
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_HardboiledActivatesExtra;
                    effect++;
                }
            }
            break;
        case ABILITY_BERSERK:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler)
                // Had more than half of hp before, now has less
                && gBattleStruct->hpBefore[battler] >= gBattleMons[battler].maxHP / 2 
                && gBattleMons[battler].hp < gBattleMons[battler].maxHP / 2 
                && (gMultiHitCounter == 0 || gMultiHitCounter == 1) && !(TestSheerForceFlag(gBattlerAttacker, gCurrentMove)) && CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_EMERGENCY_EXIT:
        case ABILITY_WIMP_OUT:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED 
                && IsBattlerAlive(battler)
                && gBattleStruct->hpBefore[battler] > gBattleMons[battler].maxHP / 2
                && gBattleMons[battler].hp < gBattleMons[battler].maxHP / 2
                && (gMultiHitCounter == 0 || gMultiHitCounter == 1) 
                && !(TestSheerForceFlag(gBattlerAttacker, gCurrentMove)) 
                && (CanBattlerSwitch(battler) || !(gBattleTypeFlags & BATTLE_TYPE_TRAINER)) 
                && !(gBattleTypeFlags & BATTLE_TYPE_ARENA) 
                && CountUsablePartyMons(battler) > 0
                && !(gStatuses3[battler] & STATUS3_SKY_DROPPED))
            {
                gBattleResources->flags->flags[battler] |= RESOURCE_FLAG_EMERGENCY_EXIT;
                effect++;
            }
            break;
        case ABILITY_WEAK_ARMOR:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && IS_MOVE_PHYSICAL(gCurrentMove) && (CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN)       // Don't activate if speed cannot be raised
                                                                                                                                                    || CompareStat(battler, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN))) // Don't activate if defense cannot be lowered
            {
                if ((gBattleMoves[gCurrentMove].effect == EFFECT_HIT_ESCAPE 
                    || gBattleMoves[gCurrentMove].effect == EFFECT_FLIP_TURN 
                    || gBattleMoves[gCurrentMove].effect == EFFECT_U_TURN 
                    || gBattleMoves[gCurrentMove].effect == EFFECT_MANEUVER
                    || gBattleMoves[gCurrentMove].effect == EFFECT_GLACIAL_SHIFT 
                    || gBattleMoves[gCurrentMove].effect == EFFECT_SNOWFADE) && CanBattlerSwitch(gBattlerAttacker))
                    gProtectStructs[battler].disableEjectPack = TRUE; // Set flag for target

                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_WeakArmorActivates;
                effect++;
            }
            break;
        case ABILITY_CURSED_BODY:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && TARGET_TURN_DAMAGED 
            && gDisableStructs[gBattlerAttacker].disabledMove == MOVE_NONE 
            && IsBattlerAlive(gBattlerAttacker) 
            && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL) 
            && gBattleMons[gBattlerAttacker].pp[gChosenMovePos] != 0 
            && RandomPercentage(RNG_POISON_POINT, 30))
            {
                gDisableStructs[gBattlerAttacker].disabledMove = gChosenMove;
                gDisableStructs[gBattlerAttacker].disableTimer = 4;
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gChosenMove);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_CursedBodyActivatesDisable;
                effect++;
            }
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && TARGET_TURN_DAMAGED 
            && IsBattlerAlive(gBattlerAttacker) 
            && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL)
            && gBattleMons[gBattlerAttacker].pp[gChosenMovePos] != 0 
            && RandomPercentage(RNG_POISON_POINT, 20))
            {
                gBattleMons[gBattlerAttacker].status2 |= STATUS2_TORMENT;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_CursedBodyActivatesTorment;
                effect++;
            }
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && TARGET_TURN_DAMAGED 
            && IsBattlerAlive(gBattlerAttacker) 
            && gBattleMons[gBattlerAttacker].pp[gChosenMovePos] != 0 
            && RandomPercentage(RNG_POISON_POINT, 10))
            {
                gBattleMons[gBattlerAttacker].status2 |= STATUS2_CURSED;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_CursedBodyActivatesCurse;
                effect++;
            }
            break;
        case ABILITY_LINGERING_AROMA:
        case ABILITY_MUMMY:
        case ABILITY_LOVESICK:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && IsBattlerAlive(gBattlerAttacker) 
            && TARGET_TURN_DAMAGED
            && GetBattlerHoldEffect(gBattlerAttacker, TRUE) != HOLD_EFFECT_PROTECTIVE_PADS
            && IsMoveMakingContact(move, gBattlerAttacker) 
            && gBattleMons[gBattlerAttacker].ability != ABILITY_MUMMY
            && gBattleMons[gBattlerAttacker].ability != ABILITY_LINGERING_AROMA
            && gBattleMons[gBattlerAttacker].ability != ABILITY_LOVESICK
            && gBattleStruct->overwrittenAbilities[gBattlerAttacker] != GetBattlerAbility(gBattlerTarget)
            && (!(IsGastroAcidBannedAbility(gBattleMons[gBattlerAttacker].ability))))
            {
                if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_ABILITY_SHIELD)
                {
                    RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD);
                    break;
                }

                gLastUsedAbility = gBattleMons[gBattlerAttacker].ability;
                gBattleMons[gBattlerAttacker].ability = gBattleStruct->overwrittenAbilities[gBattlerAttacker] = gBattleMons[gBattlerTarget].ability;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_MummyActivates;
                effect++;
                break;
            }
            break;
        case ABILITY_MELANCHOLIA:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && IsBattlerAlive(gBattlerAttacker) 
            && TARGET_TURN_DAMAGED 
            && (!(IS_MOVE_STATUS(gCurrentMove)))
            && gBattleStruct->overwrittenAbilities[gBattlerAttacker] != ABILITY_SADDENED)
            {
                if (IsGastroAcidBannedAbility(gBattleMons[gBattlerAttacker].ability))
                {
                    break;
                }
                else
                {
                    if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_ABILITY_SHIELD)
                    {
                        RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD);
                        break;
                    }

                    gLastUsedAbility = gBattleMons[gBattlerAttacker].ability = gBattleStruct->overwrittenAbilities[gBattlerAttacker] = ABILITY_SADDENED;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MelancholiaActivates;
                    effect++;
                    break;
                }
            }
            break;
        case ABILITY_WANDERING_SPIRIT:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && IsBattlerAlive(gBattlerAttacker) && TARGET_TURN_DAMAGED && IsMoveMakingContact(move, gBattlerAttacker))
            {
                if (IsGastroAcidBannedAbility(gBattleMons[gBattlerAttacker].ability))
                {
                    break;
                }
                else
                {
                    if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_ABILITY_SHIELD)
                    {
                        RecordItemEffectBattle(gBattlerAttacker, HOLD_EFFECT_ABILITY_SHIELD);
                        break;
                    }

                    gLastUsedAbility = gBattleMons[gBattlerAttacker].ability;
                    gBattleMons[gBattlerAttacker].ability = gBattleStruct->overwrittenAbilities[gBattlerAttacker] = gBattleMons[gBattlerTarget].ability;
                    gBattleMons[gBattlerTarget].ability = gBattleStruct->overwrittenAbilities[gBattlerTarget] = gLastUsedAbility;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_WanderingSpiritActivates;
                    effect++;
                    break;
                }
            }
            break;
        case ABILITY_ANGER_POINT:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && TARGET_TURN_DAMAGED
            && IsBattlerAlive(battler)
            && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                if (gIsCriticalHit)
                {
                    SET_STATCHANGER(STAT_ATK, MAX_STAT_STAGE - gBattleMons[battler].statStages[STAT_ATK], FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetsStatWasMaxedOut;
                    effect++;
                }
                else if (CalcTypeEffectivenessMultiplier(move, moveType, battler, gBattlerTarget, GetBattlerAbility(gBattlerTarget), FALSE) >= UQ_4_12(2.0))
                {
                    gEffectBattler = battler;
                    SET_STATCHANGER(STAT_ATK, 2, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                    effect++;
                }
            }
            break;
        case ABILITY_PUNISHER:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && TARGET_TURN_DAMAGED
            && IsBattlerAlive(battler) 
            && TryBattleFormChange(battler, FORM_CHANGE_BATTLE_TURN_END))
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_DefenderFormChange;
                effect++;
            }
            break;
        case ABILITY_COLOR_CHANGE:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && move != MOVE_STRUGGLE 
            && gBattleMoves[move].power != 0 
            && TARGET_TURN_DAMAGED 
            && !IS_BATTLER_OF_TYPE(battler, moveType) 
            && gBattleMons[battler].hp != 0)
            {
                SET_BATTLER_TYPE(battler, moveType);
                PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ColorChangeActivates;
                effect++;
            }
            break;
        case ABILITY_REFORM:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && (!(gMoveResultFlags & MOVE_RESULT_NOT_VERY_EFFECTIVE))
            && move != MOVE_STRUGGLE 
            && gBattleMoves[move].power != 0 
            && TARGET_TURN_DAMAGED 
            && gBattleMons[battler].hp != 0
            && ShouldReform(battler, gCurrentMove))
            {
                PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
                if (gBattleMoves[move].type == TYPE_NORMAL && !gDisableStructs[battler].reformNormal)
                    gDisableStructs[battler].reformNormal = TRUE;
                else if (gBattleMoves[move].type == TYPE_FIGHTING && !gDisableStructs[battler].reformFighting)
                    gDisableStructs[battler].reformFighting = TRUE;
                else if (gBattleMoves[move].type == TYPE_FLYING && !gDisableStructs[battler].reformFlying)
                    gDisableStructs[battler].reformFlying = TRUE;
                else if (gBattleMoves[move].type == TYPE_POISON && !gDisableStructs[battler].reformPoison)
                    gDisableStructs[battler].reformPoison = TRUE;
                else if (gBattleMoves[move].type == TYPE_GROUND && !gDisableStructs[battler].reformGround)
                    gDisableStructs[battler].reformGround = TRUE;
                else if (gBattleMoves[move].type == TYPE_ROCK && !gDisableStructs[battler].reformRock)
                    gDisableStructs[battler].reformRock = TRUE;
                else if (gBattleMoves[move].type == TYPE_BUG && !gDisableStructs[battler].reformBug)
                    gDisableStructs[battler].reformBug = TRUE;
                else if (gBattleMoves[move].type == TYPE_GHOST && !gDisableStructs[battler].reformGhost)
                    gDisableStructs[battler].reformGhost = TRUE;
                else if (gBattleMoves[move].type == TYPE_STEEL && !gDisableStructs[battler].reformSteel)
                    gDisableStructs[battler].reformSteel = TRUE;
                else if (gBattleMoves[move].type == TYPE_FIRE && !gDisableStructs[battler].reformFire)
                    gDisableStructs[battler].reformFire = TRUE;
                else if (gBattleMoves[move].type == TYPE_WATER && !gDisableStructs[battler].reformWater)
                    gDisableStructs[battler].reformWater = TRUE;
                else if (gBattleMoves[move].type == TYPE_GRASS && !gDisableStructs[battler].reformGrass)
                    gDisableStructs[battler].reformGrass = TRUE;
                else if (gBattleMoves[move].type == TYPE_ELECTRIC && !gDisableStructs[battler].reformElectric)
                    gDisableStructs[battler].reformElectric = TRUE;
                else if (gBattleMoves[move].type == TYPE_PSYCHIC && !gDisableStructs[battler].reformPsychic)
                    gDisableStructs[battler].reformPsychic = TRUE;
                else if (gBattleMoves[move].type == TYPE_ICE && !gDisableStructs[battler].reformIce)
                    gDisableStructs[battler].reformIce = TRUE;
                else if (gBattleMoves[move].type == TYPE_DRAGON && !gDisableStructs[battler].reformDragon)
                    gDisableStructs[battler].reformDragon = TRUE;
                else if (gBattleMoves[move].type == TYPE_DARK && !gDisableStructs[battler].reformDark)
                    gDisableStructs[battler].reformDark = TRUE;
                else if (gBattleMoves[move].type == TYPE_FAIRY && !gDisableStructs[battler].reformFairy)
                    gDisableStructs[battler].reformFairy = TRUE;
                else if (gBattleMoves[move].type == TYPE_RELIC && !gDisableStructs[battler].reformRelic)
                    gDisableStructs[battler].reformRelic = TRUE;        
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ReformActivates;
                effect++;
            }
            break;
        case ABILITY_GOOEY:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMons[gBattlerAttacker].hp != 0 
            && (CompareStat(gBattlerAttacker, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN) 
            || GetBattlerAbility(gBattlerAttacker) == ABILITY_MIRROR_ARMOR
            || (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_MOON_MIRROR 
            && gBattleMons[gBattlerAttacker].species == SPECIES_LUNATONE))
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED 
            && IsMoveMakingContact(move, gBattlerAttacker)
            && gDisableStructs[gBattlerAttacker].disabledMove == MOVE_NONE 
            && IsBattlerAlive(gBattlerAttacker) 
            && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL) 
            && gBattleMons[gBattlerAttacker].pp[gChosenMovePos] != 0 )
            {
                SET_STATCHANGER(STAT_SPEED, 1, TRUE);
                gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_1;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                gDisableStructs[gBattlerAttacker].disabledMove = gChosenMove;
                gDisableStructs[gBattlerAttacker].disableTimer = 4;
                PREPARE_MOVE_BUFFER(gBattleTextBuff3, gChosenMove);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_GooeyActivatesSpeedandDisable;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            else if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMons[gBattlerAttacker].hp != 0 
            && (CompareStat(gBattlerAttacker, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN) 
            || GetBattlerAbility(gBattlerAttacker) == ABILITY_MIRROR_ARMOR
            || (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_MOON_MIRROR 
            && gBattleMons[gBattlerAttacker].species == SPECIES_LUNATONE))
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED 
            && IsMoveMakingContact(move, gBattlerAttacker))
            {
                SET_STATCHANGER(STAT_SPEED, 1, TRUE);
                gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_1;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_GooeyActivates;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            else if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && TARGET_TURN_DAMAGED 
            && gDisableStructs[gBattlerAttacker].disabledMove == MOVE_NONE 
            && IsBattlerAlive(gBattlerAttacker) 
            && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL) 
            && gBattleMons[gBattlerAttacker].pp[gChosenMovePos] != 0 
            && IsMoveMakingContact(move, gBattlerAttacker))
            {
                gDisableStructs[gBattlerAttacker].disabledMove = gChosenMove;
                gDisableStructs[gBattlerAttacker].disableTimer = 4;
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gChosenMove);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_CursedBodyActivatesDisable;
                effect++;
            }
            break;
        case ABILITY_TANGLING_HAIR:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMons[gBattlerAttacker].hp != 0 
            && (CompareStat(gBattlerAttacker, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN) 
            || GetBattlerAbility(gBattlerAttacker) == ABILITY_MIRROR_ARMOR
            || (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_MOON_MIRROR 
            && gBattleMons[gBattlerAttacker].species == SPECIES_LUNATONE))
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED 
            && IsMoveMakingContact(move, gBattlerAttacker))
            {
                SET_STATCHANGER(STAT_SPEED, 1, TRUE);
                gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_1;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_GooeyActivates;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_IRON_BARBS:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED && IsMoveMakingContact(move, gBattlerAttacker))
            {
                gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 16;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_RoughSkinActivates;
                effect++;
            }
            break;
        case ABILITY_ROUGH_SKIN:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED && IsMoveMakingContact(move, gBattlerAttacker))
            {
                #if B_ROUGH_SKIN_DMG >= GEN_4
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 8;
                #else
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 8;
                #endif
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_RoughSkinActivates;
                effect++;
            }
            break;
        case ABILITY_OVERCOAT:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerAttacker].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED 
            && (!(IsMoveMakingContact(move, gBattlerAttacker)))
            && (gCurrentMove != MOVE_EARTHQUAKE || gCurrentMove != MOVE_MAGNITUDE || gCurrentMove != MOVE_BULLDOZE))
            {
                gBattleMoveDamage = gSpecialStatuses[gBattlerTarget].shellBellDmg / 2; // 50% Overcoat damage
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_RoughSkinActivates;
                effect++;
            }
            break;
        case ABILITY_AFTERMATH:    
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && !IsBattlerAlive(gBattlerTarget)
            && IsBattlerAlive(gBattlerAttacker)
            && gBattlerAttacker != gBattlerTarget
            && !gProtectStructs[gBattlerTarget].confusionSelfDmg
            && !gProtectStructs[gBattlerTarget].extraMoveUsed)
            {
                u16 extraMove = MOVE_BLOW_UP;  //The Extra Move to be used
                u8 movePower = 0;                 //The Move power, leave at 0 if you want it to be the same as the normal move
                u8 moveEffectPercentChance  = 0;  //The percent chance of the move effect happening
                u8 extraMoveSecondaryEffect = 0;  //Leave at 0 to remove it's secondary effect
                gTempMove = gCurrentMove;
                gCurrentMove = extraMove;
                gMultiHitCounter = 0;
                gProtectStructs[battler].extraMoveUsed = TRUE;
                gProtectStructs[battler].aftermathBlowUp = TRUE;

                //Move Effect
                VarSet(VAR_EXTRA_MOVE_DAMAGE,      movePower);
                VarSet(VAR_TEMP_MOVEEFFECT_CHANCE, moveEffectPercentChance);
                VarSet(VAR_TEMP_MOVEEFFECT,        extraMoveSecondaryEffect);

                if ((battler = IsAbilityOnField(ABILITY_DAMP)))
                {
                    gBattleScripting.battler = battler - 1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_DampPreventsAftermath;
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_DefenderUsedAnExtraMove;
                }
                effect++;
            }
            break;
        case ABILITY_CINDER_WALTZ:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0
            && IsBattlerAlive(gBattlerAttacker) 
            && TARGET_TURN_DAMAGED
            && gBattlerAttacker != gBattlerTarget
            && !gProtectStructs[gBattlerTarget].confusionSelfDmg
            && !(gBattleMons[gBattlerTarget].status1 & STATUS1_SLEEP_ANY)
            && !(gBattleMons[gBattlerTarget].status1 & STATUS1_FREEZE)
            && (gMultiHitCounter == 0 || gMultiHitCounter == 1))
            {
                u16 extraMove = MOVE_CINDER_WALTZ;     //The Extra Move to be used
                u8 movePower = 75;                 //The Move power, leave at 0 if you want it to be the same as the normal move
                u8 moveEffectPercentChance  = 20;  //The percent chance of the move effect happening
                u8 extraMoveSecondaryEffect = MOVE_EFFECT_BURN;  //Leave at 0 to remove it's secondary effect
                gTempMove = gCurrentMove;
                gCurrentMove = extraMove;
                gMultiHitCounter = 0;
                gProtectStructs[battler].extraMoveUsed = TRUE;

                //Move Effect
                VarSet(VAR_EXTRA_MOVE_DAMAGE,      movePower);
                VarSet(VAR_TEMP_MOVEEFFECT_CHANCE, moveEffectPercentChance);
                VarSet(VAR_TEMP_MOVEEFFECT,        extraMoveSecondaryEffect);

                gBattlescriptCurrInstr = BattleScript_DefenderUsedCinderWaltz;
                effect++;
            }
            break;
        case ABILITY_VERTIGO:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0
            && IsBattlerAlive(gBattlerAttacker) 
            && TARGET_TURN_DAMAGED
            && gBattlerAttacker != gBattlerTarget
            && !gProtectStructs[gBattlerTarget].confusionSelfDmg
            && (gBattleMons[gBattlerTarget].status2 & STATUS2_CONFUSION)
            && !(gBattleMons[gBattlerTarget].status1 & STATUS1_SLEEP_ANY)
            && !(gBattleMons[gBattlerTarget].status1 & STATUS1_FREEZE)
            && (gMultiHitCounter == 0 || gMultiHitCounter == 1))
            {
                u16 extraMove = MOVE_STUMBLE;  //The Extra Move to be used
                u8 movePower = 70;                  //The Move power, leave at 0 if you want it to be the same as the normal move
                u8 moveEffectPercentChance  = 100;  //The percent chance of the move effect happening
                u8 extraMoveSecondaryEffect = MOVE_EFFECT_RANDOM_STAT_DROP;  //Leave at 0 to remove it's secondary effect
                gTempMove = gCurrentMove;
                gCurrentMove = extraMove;
                gMultiHitCounter = 0;
                gProtectStructs[battler].extraMoveUsed = TRUE;

                //Move Effect
                VarSet(VAR_EXTRA_MOVE_DAMAGE,      movePower);
                VarSet(VAR_TEMP_MOVEEFFECT_CHANCE, moveEffectPercentChance);
                VarSet(VAR_TEMP_MOVEEFFECT,        extraMoveSecondaryEffect);

                gBattlescriptCurrInstr = BattleScript_DefenderUsedAnExtraMove;
                effect++;
            }
            break;
        case ABILITY_INNARDS_OUT:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
             && !IsBattlerAlive(gBattlerTarget)
             && IsBattlerAlive(gBattlerAttacker))
            {
                gBattleMoveDamage = gSpecialStatuses[gBattlerTarget].shellBellDmg;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AftermathDmg;
                effect++;
            }
            break;
        case ABILITY_EFFECT_SPORE:
            if (!IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GRASS) 
            && GetBattlerAbility(gBattlerAttacker) != ABILITY_OVERCOAT 
            && GetBattlerHoldEffect(gBattlerAttacker, TRUE) != HOLD_EFFECT_SAFETY_GOGGLES
            && !gMoveResultFlags & MOVE_RESULT_NO_EFFECT
            && gBattleMons[gBattlerAttacker].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED
            && (Random() % 3) == 0)
            {
                i = Random() % 4;
                if (i == 0)
                    goto POISON;
                if (i == 1)
                    goto PARALYSIS;
                if (i == 2)
                    goto SLEEP;
                if (i == 3)
                    goto PANIC;
                POISON:
                if (CanBePoisoned(gBattlerTarget, gBattlerAttacker))
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_POISON;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    effect++;
                }
                break;
                PARALYSIS:
                if (CanBeParalyzed(gBattlerAttacker))
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_PARALYSIS;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    effect++;
                }
                break;
                SLEEP:
                if (CanSleep(gBattlerAttacker))
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_SLEEP;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    effect++;
                }
                break;
                PANIC:
                if (CanGetPanicked(gBattlerAttacker))
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_PANIC;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    effect++;
                }
                break;
            }
            break;
        case ABILITY_POISON_POINT:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED 
            && CanBePoisoned(gBattlerTarget, gBattlerAttacker) && IsMoveMakingContact(move, gBattlerAttacker))
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_POISON;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_ICE_SCALES:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED
            && (gDisableStructs[gBattlerTarget].iceScalesCounter != 0))
            {
                s32 iceScalesToDeduct;
                
                gBattleMoveDamage = ((gBattleMons[gBattlerAttacker].maxHP / 20) * gDisableStructs[gBattlerTarget].iceScalesCounter);
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;

                if (gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE)
                {
                    iceScalesToDeduct = 3;
                }
                else
                {
                    iceScalesToDeduct = 2;
                }

                if (gDisableStructs[gBattlerTarget].iceScalesCounter < iceScalesToDeduct)
                {
                    iceScalesToDeduct = gDisableStructs[gBattlerTarget].iceScalesCounter;
                }

                gDisableStructs[gBattlerTarget].iceScalesCounter -= iceScalesToDeduct;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_IceScalesActivatesLoss;
                effect++;
            }
            break;
        case ABILITY_STATIC:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED && CanBeParalyzed(gBattlerAttacker) && IsMoveMakingContact(move, gBattlerAttacker) && RandomWeighted(RNG_STATIC, 2, 1))
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_PARALYSIS;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_DREAD_VEIL:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
             && !IsBattlerAlive(gBattlerTarget)
             && IsBattlerAlive(gBattlerAttacker)
             && CanGetPanicked(gBattlerAttacker))
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_PANIC;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_FLAME_BODY:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && (IsMoveMakingContact(move, gBattlerAttacker)) && TARGET_TURN_DAMAGED && CanBeBurned(gBattlerAttacker) && RandomWeighted(RNG_FLAME_BODY, 2, 1))
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_BURN;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_ICE_BODY:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMons[gBattlerAttacker].hp != 0
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
            && IsMoveMakingContact(move, gBattlerAttacker)
            && TARGET_TURN_DAMAGED
            && CanGetFrostbite(gBattlerAttacker)
            && RandomPercentage(RNG_POISON_POINT, 20))
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_FROSTBITE;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_CUTE_CHARM:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMons[gBattlerAttacker].hp != 0
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
            && TARGET_TURN_DAMAGED
            && !(gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION)
            && AreBattlersOfOppositeGender(gBattlerAttacker, gBattlerTarget)
            && GetBattlerAbility(gBattlerAttacker) != ABILITY_OBLIVIOUS
            && GetBattlerAbility(gBattlerAttacker) != ABILITY_IGNORANT_BLISS
            && IsMoveMakingContact(move, gBattlerAttacker)
            && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL))
            {
                if (gDisableStructs[gBattlerAttacker].allureCounter > 1)
                {
                    gDisableStructs[gBattlerAttacker].allureCounter = 0;
                    gBattleMons[gBattlerAttacker].status2 |= STATUS2_INFATUATED_WITH(gBattlerTarget);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CuteCharmInfatuationActivates;
                    effect++;
                }
                else
                {
                    gDisableStructs[gBattlerAttacker].allureCounter++;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CuteCharmAllureActivates;
                    effect++;
                }
            }
            break;
        case ABILITY_FUDDLE_POINT:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED 
            && CanBeConfused(gBattlerTarget) && IsMoveMakingContact(move, gBattlerAttacker))
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CONFUSION;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_STICKY_HOLD:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerAttacker].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED 
            && gBattleMons[gBattlerTarget].hp != 0 
            && !(gBattleMons[gBattlerAttacker].status2 & STATUS2_ESCAPE_PREVENTION) 
            && IsMoveMakingContact(move, gBattlerAttacker))
            {
                BattleScriptPushCursor();
                gBattleMons[gBattlerAttacker].status2 |= STATUS2_ESCAPE_PREVENTION;
                gDisableStructs[gBattlerTarget].battlerPreventingEscape = gBattlerTarget;
                gBattlescriptCurrInstr = BattleScript_EffectStickyHold;
                effect++;
            }
            break;
        case ABILITY_ILLUSION:
            if (gBattleStruct->illusion[gBattlerTarget].on 
                && !gBattleStruct->illusion[gBattlerTarget].broken 
                && TARGET_TURN_DAMAGED)
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_IllusionOff;
                effect++;
            }
            break;
        case ABILITY_COTTON_DOWN:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED)
            {
                gEffectBattler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_CottonDownActivates;
                effect++;
            }
            break;
        case ABILITY_GUARD_DOG:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 && gBattleMons[gBattlerTarget].hp != 0 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED)
            {
                gEffectBattler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_GuardDogActivates;
                effect++;
            }
            break;
        case ABILITY_SWEET_VEIL:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerAttacker].hp != 0 && gBattleMons[gBattlerTarget].hp != 0 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED)
            {
                gEffectBattler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_SweetVeilActivates;
                effect++;
            }
            break;
        case ABILITY_STEAM_ENGINE:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN) && (moveType == TYPE_FIRE || moveType == TYPE_WATER))
            {
                gEffectBattler = battler;
                SET_STATCHANGER(STAT_SPEED, 6, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_SAND_SPIT:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED 
            && !(gBattleWeather & B_WEATHER_SANDSTORM && WEATHER_HAS_EFFECT))
            {
                if (gBattleWeather & B_WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT)
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BlockedByPrimalWeatherRet;
                    effect++;
                }
                else if (TryChangeBattleWeather(battler, ENUM_WEATHER_SANDSTORM, TRUE))
                {
                    gBattleScripting.battler = battler;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_SandSpitActivates;
                    effect++;
                }
            }
            break;
        case ABILITY_PERISH_BODY:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED && IsBattlerAlive(battler) && (IsMoveMakingContact(move, gBattlerAttacker)) && !(gStatuses3[gBattlerAttacker] & STATUS3_PERISH_SONG))
            {
                if (!(gStatuses3[battler] & STATUS3_PERISH_SONG))
                {
                    gStatuses3[battler] |= STATUS3_PERISH_SONG;
                    gDisableStructs[battler].perishSongTimer = 3;
                }
                gStatuses3[gBattlerAttacker] |= STATUS3_PERISH_SONG;
                gDisableStructs[gBattlerAttacker].perishSongTimer = 3;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_PerishBodyActivates;
                effect++;
            }
            break;
        case ABILITY_GULP_MISSILE:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED && IsBattlerAlive(battler))
            {
                if (gBattleMons[gBattlerTarget].species == SPECIES_CRAMORANT_GORGING)
                {
                    gBattleMons[gBattlerTarget].species = SPECIES_CRAMORANT;
                    if (GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD
                    && GetBattlerAbility(gBattlerAttacker) != ABILITY_SUGAR_COAT
                    && !TestTeruCharm(gBattlerAttacker))
                    {
                        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                            gBattleMoveDamage = 50;
                    }
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_GulpMissileGorging;
                    effect++;
                }
                else if (gBattleMons[gBattlerTarget].species == SPECIES_CRAMORANT_GULPING)
                {
                    gBattleMons[gBattlerTarget].species = SPECIES_CRAMORANT;
                    if (GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD
                    && GetBattlerAbility(gBattlerAttacker) != ABILITY_SUGAR_COAT
                    && !TestTeruCharm(gBattlerAttacker))
                    {
                        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                            gBattleMoveDamage = 50;
                    }
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_GulpMissileGulping;
                    effect++;
                }
            }
            break;
        case ABILITY_SEED_SOWER:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED
            && IsBattlerAlive(gBattlerTarget)
            && TryChangeBattleTerrain(gBattlerTarget, STATUS_FIELD_GRASSY_TERRAIN, &gFieldTimers.terrainTimer))
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_SeedSowerActivates;
                effect++;
            }
            break;
        case ABILITY_THERMAL_EXCHANGE:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && TARGET_TURN_DAMAGED && IsBattlerAlive(gBattlerTarget) && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN) && moveType == TYPE_FIRE)
            {
                gEffectBattler = gBattlerTarget;
                SET_STATCHANGER(STAT_ATK, 1, FALSE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                effect++;
            }
            break;
        case ABILITY_ANGER_SHELL:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && !gProtectStructs[battler].confusionSelfDmg 
            && TARGET_TURN_DAMAGED 
            && IsBattlerAlive(battler) 
            && (gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2) 
            && !(TestSheerForceFlag(battler, gCurrentMove)))
            {
                gEffectBattler = battler;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AngerShellActivates;
                effect++;
            }
            break;
        case ABILITY_ELECTROMORPHOSIS:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && TARGET_TURN_DAMAGED && IsBattlerAlive(gBattlerTarget))
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_WindPowerActivates;
                effect++;
            }
            break;
        case ABILITY_TOXIC_DEBRIS:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && IS_MOVE_PHYSICAL(gCurrentMove) && TARGET_TURN_DAMAGED && (gSideTimers[gBattlerAttacker].toxicSpikesAmount != 2))
            {
                SWAP(gBattlerAttacker, gBattlerTarget, i);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ToxicDebrisActivates;
                effect++;
            }
            break;
        }
        break;
    case ABILITYEFFECT_MOVE_END_ATTACKER: // Same as above, but for attacker
        switch (gLastUsedAbility)
        {
        case ABILITY_POISON_TOUCH:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && CanBePoisoned(gBattlerAttacker, gBattlerTarget) 
            && IsMoveMakingContact(move, gBattlerAttacker) 
            && TARGET_TURN_DAMAGED // Need to actually hit the target
            && (Random() % 3) == 0)
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_INNER_FOCUS:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && TARGET_TURN_DAMAGED
            && gIsCriticalHit
            && !BATTLER_MAX_HP(battler)
            && gDisableStructs[battler].focusEnergy
            && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK)
            && IsBattlerAlive(battler)
            && (gMultiHitCounter == 0 || gMultiHitCounter == 1))
            {
                gBattleMoveDamage = (gBattleMons[battler].maxHP * 15 / 100);
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                gBattleMoveDamage *= -1;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AppetiteActivates;
                effect++;
            }
            break;
        case ABILITY_LOVESICK:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && IsBattlerAlive(gBattlerTarget)
            && TARGET_TURN_DAMAGED
            && GetBattlerHoldEffect(gBattlerAttacker, TRUE) != HOLD_EFFECT_PROTECTIVE_PADS
            && IsMoveMakingContact(move, gBattlerAttacker) 
            && gBattleMons[gBattlerTarget].ability != ABILITY_MUMMY
            && gBattleMons[gBattlerTarget].ability != ABILITY_LINGERING_AROMA
            && gBattleMons[gBattlerTarget].ability != ABILITY_LOVESICK
            && gBattleStruct->overwrittenAbilities[gBattlerTarget] != GetBattlerAbility(gBattlerTarget)
            && (!(IsGastroAcidBannedAbility(gBattleMons[gBattlerTarget].ability))))
            {
                if (GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_ABILITY_SHIELD)
                {
                    RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_ABILITY_SHIELD);
                    break;
                }

                gLastUsedAbility = gBattleMons[gBattlerTarget].ability;
                gBattleMons[gBattlerTarget].ability = gBattleStruct->overwrittenAbilities[gBattlerTarget] = gBattleMons[gBattlerAttacker].ability;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_LovesickMummyEffectActivates;
                effect++;
                break;
            }
            break;
        case ABILITY_ICE_SCALES:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && (gBattleMoves[gCurrentMove].type == TYPE_ICE)
            && TARGET_TURN_DAMAGED
            && (gDisableStructs[gBattlerAttacker].iceScalesCounter < 5))
            {
                gDisableStructs[gBattlerAttacker].iceScalesCounter++;
                PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 1, gDisableStructs[gBattlerAttacker].iceScalesCounter);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_IceScalesActivatesGain;
                effect++;
            }
            break;
        case ABILITY_PURPLE_HAZE:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0 
            && TARGET_TURN_DAMAGED
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
            && gBattleMoves[move].gasMove
            && !gDisableStructs[gBattlerAttacker].purpleHazeOffense
            && !gDisableStructs[gBattlerAttacker].purpleHazeDefense)
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilitySetPurpleHaze;
                effect++;
            }
            break;
        case ABILITY_STORM_BREW:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMoves[move].type == TYPE_ELECTRIC
            && gBattleMons[gBattlerAttacker].hp != 0
            && IsBattlerAlive(gBattlerTarget) 
            && TARGET_TURN_DAMAGED
            && gBattlerTarget != gBattlerAttacker
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
            && !gProtectStructs[gBattlerAttacker].extraMoveUsed
            && !(gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP_ANY)
            && !(gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE)
            && (gMultiHitCounter == 0 || gMultiHitCounter == 1))
            {
                u16 extraMove = MOVE_LIGHTNING;  //The Extra Move to be used
                u8 movePower = 20 * (1 + gDisableStructs[gBattlerAttacker].stormBrewCounter); //The Move power, leave at 0 if you want it to be the same as the normal move
                u8 moveEffectPercentChance  = 0;  //The percent chance of the move effect happening
                u8 extraMoveSecondaryEffect = 0;  //Leave at 0 to remove it's secondary effect
                gTempMove = gCurrentMove;
                gCurrentMove = extraMove;
                gMultiHitCounter = 0;
                gProtectStructs[battler].extraMoveUsed = TRUE;
                gProtectStructs[battler].alreadyUsedStormBrew = TRUE;

                //Move Effect
                VarSet(VAR_EXTRA_MOVE_DAMAGE,      movePower);
                VarSet(VAR_TEMP_MOVEEFFECT_CHANCE, moveEffectPercentChance);
                VarSet(VAR_TEMP_MOVEEFFECT,        extraMoveSecondaryEffect);

                gBattlescriptCurrInstr = BattleScript_AttackerUsedAnExtraMove;
                effect++;
            }
            break;
        case ABILITY_FIREBRAND:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMons[gBattlerTarget].status1 & STATUS1_BURN
            && IsMoveMakingContact(gCurrentMove, gBattlerAttacker)
            && !(gStatuses3[gBattlerAttacker] & STATUS3_HEAL_BLOCK)
            && gBattleMons[gBattlerAttacker].hp != 0
            && IsBattlerAlive(gBattlerTarget) 
            && TARGET_TURN_DAMAGED
            && gBattlerTarget != gBattlerAttacker
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
            && !gProtectStructs[gBattlerAttacker].extraMoveUsed
            && !(gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP_ANY)
            && !(gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE)
            && (gMultiHitCounter == 0 || gMultiHitCounter == 1))
            {
                u16 extraMove = MOVE_FIREBRAND;  //The Extra Move to be used
                u8 movePower = 0;                  //The Move power, leave at 0 if you want it to be the same as the normal move
                u8 moveEffectPercentChance  = 100;  //The percent chance of the move effect happening
                u8 extraMoveSecondaryEffect = 0;  //Leave at 0 to remove it's secondary effect
                gTempMove = gCurrentMove;
                gCurrentMove = extraMove;
                gMultiHitCounter = 0;
                gProtectStructs[battler].extraMoveUsed = TRUE;

                //Move Effect
                VarSet(VAR_EXTRA_MOVE_DAMAGE,      movePower);
                VarSet(VAR_TEMP_MOVEEFFECT_CHANCE, moveEffectPercentChance);
                VarSet(VAR_TEMP_MOVEEFFECT,        extraMoveSecondaryEffect);

                gBattlescriptCurrInstr = BattleScript_AttackerUsedFirebrand;
                effect++;
            }
            break;
        case ABILITY_RISKTAKER:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
            && !(IS_MOVE_STATUS(move))
            && TARGET_TURN_DAMAGED)
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilitySetGlaiveRush;
                effect++;
            }
            break;
        case ABILITY_TRANSFUSION:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && IsMoveDraining(move)
            && TARGET_TURN_DAMAGED)
            {
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_TransfusionAbilityCopy;
                effect++;
            }
            break;
        case ABILITY_DOMINEER:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED
            && CompareStat(gBattlerTarget, STAT_ATK, MIN_STAT_STAGE, CMP_GREATER_THAN)
            && moveType == TYPE_PSYCHIC)
            {
                SET_STATCHANGER(STAT_ATK, 1, TRUE);
                gBattleScripting.moveEffect = MOVE_EFFECT_ATK_MINUS_1;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_StrongJawActivates;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_MADNESS:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && CanBeConfused(gBattlerTarget)
            && TARGET_TURN_DAMAGED // Need to actually hit the target
            && RandomPercentage(RNG_POISON_POINT, 15))
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_TOXIC_CHAIN:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && CanBePoisoned(gBattlerAttacker, gBattlerTarget)
            && TARGET_TURN_DAMAGED // Need to actually hit the target
            && (Random() % 3) == 0)
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_TOXIC;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_FROST_JAW:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMons[gBattlerTarget].hp != 0
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && gBattleMoves[move].bitingMove
            && TARGET_TURN_DAMAGED
            && CanBeFrozenFrostbiteAbilityEdition(gBattlerTarget)
            && (gBattleMons[gBattlerTarget].status1 & STATUS1_PSN_ANY || gBattleMons[gBattlerTarget].status1 & STATUS1_FROSTBITE || gBattleMons[gBattlerTarget].status1 & STATUS1_PARALYSIS))
            {
                if (gBattleMons[gBattlerTarget].status1 & STATUS1_PSN_ANY)
                    gBattleMons[gBattlerTarget].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
                else
                    gBattleMons[gBattlerTarget].status1 &= ~(gBattleMons[gBattlerTarget].status1 & STATUS1_ANY);

                BtlController_EmitSetMonData(gBattlerTarget, 0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gBattlerTarget].status1);
                MarkBattlerForControllerExec(gBattlerTarget);

                gBattleScripting.moveEffect = MOVE_EFFECT_FREEZE;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AbilityStatusEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case ABILITY_CUTE_CHARM:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
            && TARGET_TURN_DAMAGED
            && gBattleMons[gBattlerTarget].hp != 0
            && !(gBattleMons[gBattlerTarget].status2 & STATUS2_INFATUATION)
            && AreBattlersOfOppositeGender(gBattlerAttacker, gBattlerTarget)
            && GetBattlerAbility(gBattlerTarget) != ABILITY_OBLIVIOUS
            && GetBattlerAbility(gBattlerTarget) != ABILITY_IGNORANT_BLISS
            && IsMoveMakingContact(move, gBattlerAttacker)
            && !IsAbilityOnSide(gBattlerTarget, ABILITY_AROMA_VEIL))
            {
                if (gDisableStructs[gBattlerTarget].allureCounter > 1)
                {
                    gDisableStructs[gBattlerTarget].allureCounter = 0;
                    gBattleMons[gBattlerTarget].status2 |= STATUS2_INFATUATED_WITH(gBattlerAttacker);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CuteCharmInfatuationActivates2;
                    effect++;
                }
                else
                {
                    gDisableStructs[gBattlerTarget].allureCounter++;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CuteCharmAllureActivates2;
                    effect++;
                }
            }
            break;
        case ABILITY_IRON_BARBS:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED
            && (IsMoveMakingContact(move, gBattlerAttacker)
            || gBattleMoves[move].piercingMove))
            {
                gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 16;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[gBattlerTarget].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_IronBarbsActivates;
                effect++;
            }
            break;
        case ABILITY_LIQUID_OOZE:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED 
            && gBattleMoves[gCurrentMove].oozeMove)
            {
                gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 5;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[gBattlerTarget].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_IronBarbsActivates;
                effect++;
            }
            break;
        case ABILITY_STENCH:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) && gBattleMons[gBattlerTarget].hp != 0 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg && RandomWeighted(RNG_STENCH, 9, 1) && !IS_MOVE_STATUS(move) && gBattleMoves[gCurrentMove].effect != EFFECT_FLINCH_HIT && gBattleMoves[gCurrentMove].effect != EFFECT_FLINCH_STATUS && gBattleMoves[gCurrentMove].effect != EFFECT_TRIPLE_ARROWS)
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_FLINCH;
                BattleScriptPushCursor();
                SetMoveEffect(FALSE, 0);
                BattleScriptPop();
                effect++;
            }
            break;
        case ABILITY_STRONG_JAW:
            if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
            && gBattleMons[gBattlerTarget].hp != 0 
            && !gProtectStructs[gBattlerAttacker].confusionSelfDmg 
            && TARGET_TURN_DAMAGED
            && gBattleMoves[gCurrentMove].effect != EFFECT_DEFENSE_DOWN_HIT
            && (CompareStat(gBattlerTarget, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN)
            || GetBattlerAbility(gBattlerTarget) == ABILITY_MIRROR_ARMOR
            || (GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_MOON_MIRROR 
            && gBattleMons[gBattlerTarget].species == SPECIES_LUNATONE))
            && !IS_MOVE_STATUS(move)
            && gBattleMoves[move].bitingMove)
            {
                SET_STATCHANGER(STAT_DEF, 1, TRUE);
                gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_1;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_StrongJawActivates;
                effect++;
            }
            break;
        case ABILITY_GULP_MISSILE:
            if (((gCurrentMove == MOVE_SURF && TARGET_TURN_DAMAGED) || gStatuses3[gBattlerAttacker] & STATUS3_UNDERWATER) && TryBattleFormChange(gBattlerAttacker, FORM_CHANGE_BATTLE_HP_PERCENT))
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AttackerFormChange;
                effect++;
            }
            break;
        }
        break;
    case ABILITYEFFECT_MOVE_END_OTHER: // Abilities that activate on *another* battler's moveend: Dancer, Soul-Heart, Receiver, Symbiosis
        switch (GetBattlerAbility(battler))
        {
        case ABILITY_DANCER:
            if (IsBattlerAlive(battler) 
            && (gBattleMoves[gCurrentMove].danceMove) 
            && !gSpecialStatuses[battler].dancerUsedMove 
            && gBattlerAttacker != battler)
            {
                // Set bit and save Dancer mon's original target
                gSpecialStatuses[battler].dancerUsedMove = TRUE;
                gSpecialStatuses[battler].dancerOriginalTarget = *(gBattleStruct->moveTarget + battler) | 0x4;
                gBattleStruct->atkCancellerTracker = 0;
                gBattlerAttacker = gBattlerAbility = battler;
                gCalledMove = gCurrentMove;

                // Set the target to the original target of the mon that first used a Dance move
                gBattlerTarget = gBattleScripting.savedBattler & 0x3;

                // Make sure that the target isn't an ally - if it is, target the original user
                if (GetBattlerSide(gBattlerTarget) == GetBattlerSide(gBattlerAttacker))
                    gBattlerTarget = (gBattleScripting.savedBattler & 0xF0) >> 4;
                gHitMarker &= ~HITMARKER_ATTACKSTRING_PRINTED;
                BattleScriptExecute(BattleScript_DancerActivates);
                effect++;
            }
            break;
        }
        break;
    case ABILITYEFFECT_IMMUNITY: // 5
        for (battler = 0; battler < gBattlersCount; battler++)
        {
            switch (GetBattlerAbility(battler))
            {
            case ABILITY_IMMUNITY:
            case ABILITY_PASTEL_VEIL:
                if (gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON | STATUS1_TOXIC_COUNTER))
                {
                    StringCopy(gBattleTextBuff1, gText_Poison);
                    effect = 1;
                }
                break;
            case ABILITY_OWN_TEMPO:
                if (gBattleMons[battler].status2 & STATUS2_CONFUSION)
                {
                    StringCopy(gBattleTextBuff1, gText_Confusion);
                    effect = 2;
                }
                break;
            case ABILITY_LIMBER:
                if (gBattleMons[battler].status1 & STATUS1_PARALYSIS)
                {
                    StringCopy(gBattleTextBuff1, gText_Paralysis);
                    effect = 1;
                }
                break;
            case ABILITY_INSOMNIA:
            case ABILITY_VITAL_SPIRIT:
                if (gBattleMons[battler].status1 & STATUS1_SLEEP_ANY)
                {
                    gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
                    StringCopy(gBattleTextBuff1, gText_Sleep);
                    effect = 1;
                }
                break;
            case ABILITY_WATER_VEIL:
                if (gBattleMons[battler].status1 & STATUS1_FROSTBITE)
                {
                    StringCopy(gBattleTextBuff1, gText_Ice);
                    effect = 1;
                }
                else if (gBattleMons[battler].status1 & STATUS1_BURN)
                {
                    StringCopy(gBattleTextBuff1, gText_Burn);
                    effect = 1;
                }
                break;
            case ABILITY_WATER_BUBBLE:
                if (gBattleMons[battler].status1 & STATUS1_BURN)
                {
                    StringCopy(gBattleTextBuff1, gText_Burn);
                    effect = 1;
                }
                break;
            case ABILITY_MAGMA_ARMOR:
                if (gBattleMons[battler].status1 & (STATUS1_FREEZE | STATUS1_FROSTBITE))
                {
                    StringCopy(gBattleTextBuff1, gText_Ice);
                    effect = 1;
                }
                break;
            case ABILITY_IGNORANT_BLISS:
                if (gBattleMons[battler].status1 & STATUS1_PANIC)
                {
                    StringCopy(gBattleTextBuff1, gText_Panic);
                    effect = 1;
                }
                else if (gBattleMons[battler].status2 & STATUS2_INFATUATION)
                    effect = 3;
                else if (gDisableStructs[battler].tauntTimer != 0)
                    effect = 4;
                break;
            case ABILITY_OBLIVIOUS:
                if (gBattleMons[battler].status2 & STATUS2_INFATUATION)
                    effect = 3;
                else if (gDisableStructs[battler].tauntTimer != 0)
                    effect = 4;
                break;
            }
            if (effect != 0)
            {
                switch (effect)
                {
                case 1: // status cleared
                    gBattleMons[battler].status1 = 0;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AbilityCuredStatus;
                    break;
                case 2: // get rid of confusion
                    RemoveConfusionStatus(battler);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AbilityCuredStatus;
                    break;
                case 3: // get rid of infatuation
                    gBattleMons[battler].status2 &= ~STATUS2_INFATUATION;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BattlerGotOverItsInfatuation;
                    break;
                case 4: // get rid of taunt
                    gDisableStructs[battler].tauntTimer = 0;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BattlerShookOffTaunt;
                    break;
                }

                gBattleScripting.battler = gBattlerAbility = battler;
                BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                MarkBattlerForControllerExec(battler);
                return effect;
            }
        }
        break;
    case ABILITYEFFECT_SYNCHRONIZE:
        if (gLastUsedAbility == ABILITY_SYNCHRONIZE && (gHitMarker & HITMARKER_SYNCHRONIZE_EFFECT))
        {
            gHitMarker &= ~HITMARKER_SYNCHRONIZE_EFFECT;

            if (!(gBattleMons[gBattlerAttacker].status1 & STATUS1_ANY_NEGATIVE))
            {
                gBattleStruct->synchronizeMoveEffect &= ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                if (gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_POISON;

                gBattleScripting.moveEffect = gBattleStruct->synchronizeMoveEffect;
                gBattleScripting.battler = gBattlerAbility = gBattlerTarget;
                
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, ABILITY_SYNCHRONIZE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_SynchronizeActivates;
                gHitMarker |= (HITMARKER_IGNORE_SAFEGUARD | HITMARKER_SYNCHRONIZE_SKIP);
                effect++;
            }
        }
        break;
    case ABILITYEFFECT_ATK_SYNCHRONIZE: // 8
        if (gLastUsedAbility == ABILITY_SYNCHRONIZE && (gHitMarker & HITMARKER_SYNCHRONIZE_EFFECT))
        {
            gHitMarker &= ~HITMARKER_SYNCHRONIZE_EFFECT;

            if (!(gBattleMons[gBattlerTarget].status1 & STATUS1_ANY_NEGATIVE))
            {
                gBattleStruct->synchronizeMoveEffect &= ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                if (gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_POISON;

                gBattleScripting.moveEffect = gBattleStruct->synchronizeMoveEffect + MOVE_EFFECT_AFFECTS_USER;
                gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
                PREPARE_ABILITY_BUFFER(gBattleTextBuff1, ABILITY_SYNCHRONIZE);
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_SynchronizeActivates;
                gHitMarker |= (HITMARKER_IGNORE_SAFEGUARD | HITMARKER_SYNCHRONIZE_SKIP);
                effect++;
            }
        }
        break;
    case ABILITYEFFECT_TRACE1:
    case ABILITYEFFECT_TRACE2:
        for (i = 0; i < gBattlersCount; i++)
        {
            if (gBattleMons[i].ability == ABILITY_TRACE && (gBattleResources->flags->flags[i] & RESOURCE_FLAG_TRACED))
            {
                u32 chosenTarget;
                u32 side = (BATTLE_OPPOSITE(GetBattlerPosition(i))) & BIT_SIDE; // side of the opposing pokemon
                u32 target1 = GetBattlerAtPosition(side);
                u32 target2 = GetBattlerAtPosition(side + BIT_FLANK);

                if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                {
                    if (!IsGastroAcidBannedAbility(gBattleMons[target1].ability) && gBattleMons[target1].hp != 0 && !IsGastroAcidBannedAbility(gBattleMons[target2].ability) && gBattleMons[target2].hp != 0)
                        chosenTarget = GetBattlerAtPosition(((Random() & 1) * 2) | side), effect++;
                    else if (!IsGastroAcidBannedAbility(gBattleMons[target1].ability) && gBattleMons[target1].hp != 0)
                        chosenTarget = target1, effect++;
                    else if (!IsGastroAcidBannedAbility(gBattleMons[target2].ability) && gBattleMons[target2].hp != 0)
                        chosenTarget = target2, effect++;
                }
                else
                {
                    if (!IsGastroAcidBannedAbility(gBattleMons[target1].ability) && gBattleMons[target1].hp != 0)
                        chosenTarget = target1, effect++;
                }

                if (effect != 0)
                {
                    if (caseID == ABILITYEFFECT_TRACE1)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_TraceActivatesEnd3);
                    }
                    else
                    {
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_TraceActivates;
                    }
                    gBattleResources->flags->flags[i] &= ~RESOURCE_FLAG_TRACED;
                    gBattleStruct->tracedAbility[i] = gLastUsedAbility = gBattleMons[chosenTarget].ability;
                    RecordAbilityBattle(chosenTarget, gLastUsedAbility); // Record the opposing battler has this ability
                    battler = gBattlerAbility = gBattleScripting.battler = i;

                    PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, chosenTarget, gBattlerPartyIndexes[chosenTarget])
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff2, gLastUsedAbility)
                    break;
                }
            }
        }
        break;
    case ABILITYEFFECT_NEUTRALIZINGGAS:
        // Prints message only. separate from ABILITYEFFECT_ON_SWITCHIN bc activates before entry hazards
        for (i = 0; i < gBattlersCount; i++)
        {
            if (gBattleMons[i].ability == ABILITY_NEUTRALIZING_GAS && !(gBattleResources->flags->flags[i] & RESOURCE_FLAG_NEUTRALIZING_GAS))
            {
                gBattleResources->flags->flags[i] |= RESOURCE_FLAG_NEUTRALIZING_GAS;
                gBattlerAbility = i;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_NEUTRALIZING_GAS;
                BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                effect++;
            }

            if (effect != 0)
                break;
        }
        break;
    case ABILITYEFFECT_FIELD_SPORT:
        switch (gLastUsedAbility)
        {
        case ABILITYEFFECT_MUD_SPORT:
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gStatuses4[i] & STATUS4_MUD_SPORT)
                    effect = i + 1;
            }
            break;
        case ABILITYEFFECT_WATER_SPORT:
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gStatuses4[i] & STATUS4_WATER_SPORT)
                    effect = i + 1;
            }
            break;
        default:
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gBattleMons[i].ability == ability)
                {
                    gLastUsedAbility = ability;
                    effect = i + 1;
                }
            }
            break;
        }
        break;
    case ABILITYEFFECT_ON_WEATHER: // For ability effects that activate when the battle weather changes.
        battler = gBattlerAbility = gBattleScripting.battler;
        gLastUsedAbility = GetBattlerAbility(battler);
        switch (gLastUsedAbility)
        {
        case ABILITY_FORECAST:
        case ABILITY_FLOWER_GIFT:
            if ((IsBattlerWeatherAffected(battler, gBattleWeather) || gBattleWeather == B_WEATHER_NONE || !WEATHER_HAS_EFFECT) // Air Lock active
                && TryBattleFormChange(battler, FORM_CHANGE_BATTLE_WEATHER))
            {
                BattleScriptPushCursorAndCallback(BattleScript_BattlerFormChangeWithStringEnd3);
                effect++;
            }
            break;
        case ABILITY_ICE_FACE:
            if (IsBattlerWeatherAffected(battler, B_WEATHER_HAIL | B_WEATHER_SNOW) && gBattleMons[battler].species == SPECIES_EISCUE_NOICE_FACE && !(gBattleMons[battler].status2 & STATUS2_TRANSFORMED) && gBattleStruct->allowedToChangeFormInWeather[gBattlerPartyIndexes[battler]][GetBattlerSide(battler)])
            {
                gBattleStruct->allowedToChangeFormInWeather[gBattlerPartyIndexes[battler]][GetBattlerSide(battler)] = FALSE;
                gBattleMons[battler].species = SPECIES_EISCUE;
                BattleScriptPushCursorAndCallback(BattleScript_BattlerFormChangeWithStringEnd3);
                effect++;
            }
            break;
        case ABILITY_PROTOSYNTHESIS:
            if (!gSpecialStatuses[battler].weatherAbilityDone && IsBattlerWeatherAffected(battler, B_WEATHER_SUN))
            {
                gSpecialStatuses[battler].weatherAbilityDone = TRUE;
                PREPARE_STAT_BUFFER(gBattleTextBuff1, GetHighestStatId(battler));
                BattleScriptPushCursorAndCallback(BattleScript_ProtosynthesisActivates);
                effect++;
            }
            break;
        }
        break;
    case ABILITYEFFECT_ON_TERRAIN: // For ability effects that activate when the field terrain changes.
        gLastUsedAbility = GetBattlerAbility(battler);
        switch (gLastUsedAbility)
        {
        case ABILITY_MIMICRY:
            if (!gSpecialStatuses[battler].terrainAbilityDone && ChangeTypeBasedOnTerrain(battler))
            {
                gSpecialStatuses[battler].terrainAbilityDone = TRUE;
                ChangeTypeBasedOnTerrain(battler);
                gBattlerAbility = gBattleScripting.battler = battler;
                BattleScriptPushCursorAndCallback(BattleScript_MimicryActivates_End3);
                effect++;
            }
            break;
        case ABILITY_QUARK_DRIVE:
            if (!gSpecialStatuses[battler].terrainAbilityDone && IsBattlerTerrainAffected(battler, STATUS_FIELD_ELECTRIC_TERRAIN))
            {
                gSpecialStatuses[battler].terrainAbilityDone = TRUE;
                gBattlerAbility = gBattleScripting.battler = battler;
                PREPARE_STAT_BUFFER(gBattleTextBuff1, GetHighestStatId(battler));
                BattleScriptPushCursorAndCallback(BattleScript_QuarkDriveActivates);
                effect++;
            }
            break;
        }
        break;
    }

    if (effect && gLastUsedAbility != 0xFF)
        RecordAbilityBattle(battler, gLastUsedAbility);
    if (effect && caseID <= ABILITYEFFECT_MOVE_END)
        gBattlerAbility = battler;

    return effect;
}

bool32 TryPrimalReversion(u32 battler)
{
    if (GetBattlerHoldEffect(battler, FALSE) == HOLD_EFFECT_PRIMAL_ORB && GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_PRIMAL_REVERSION) != SPECIES_NONE)
    {
        if (gBattlerAttacker == battler)
        {
            BattleScriptExecute(BattleScript_PrimalReversion);
        }
        else
        {
            // edge case for scenarios like a switch-in after activated eject button
            gBattleScripting.savedBattler = gBattlerAttacker;
            gBattlerAttacker = battler;
            BattleScriptExecute(BattleScript_PrimalReversionRestoreAttacker);
        }
        return TRUE;
    }
    return FALSE;
}

bool32 IsNeutralizingGasOnField(void)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (IsBattlerAlive(i) && gBattleMons[i].ability == ABILITY_NEUTRALIZING_GAS && !(gStatuses3[i] & STATUS3_GASTRO_ACID))
            return TRUE;
    }

    return FALSE;
}

bool32 IsMoldBreakerTypeAbility(u32 battler, u32 ability)
{
    if (gStatuses3[battler] & STATUS3_GASTRO_ACID)
        return FALSE;

    return (ability == ABILITY_MOLD_BREAKER 
        || ability == ABILITY_TERAVOLT
        || ability == ABILITY_TURBOBLAZE
        || ability == ABILITY_IGNORANT_BLISS
        || (ability == ABILITY_MYCELIUM_MIGHT && gBattleMoves[gCurrentMove].powderMove)
        || (ability == ABILITY_AQUA_HEART && gBattleStruct->dynamicMoveType == (TYPE_WATER | F_DYNAMIC_TYPE_2))
        || (ability == ABILITY_DRACO_FORCE && gBattleStruct->dynamicMoveType == (TYPE_DRAGON | F_DYNAMIC_TYPE_2)));
}

bool32 IsIgnorantBliss(u32 battler, u32 ability)
{
    return (ability == ABILITY_IGNORANT_BLISS);
}

static inline bool32 CanBreakThroughAbility(u32 battlerAtk, u32 battlerDef, u32 ability)
{
    return ((IsMoldBreakerTypeAbility(battlerAtk, ability)
         || gBattleMoves[gCurrentMove].ignoresTargetAbility
         || ((gCurrentMove == MOVE_SPORE || gCurrentMove == MOVE_SEED_FLARE)
         && gBattleMons[gBattlerAttacker].status1 & STATUS1_BLOOMING)
         || (gCurrentMove == MOVE_RAZING_SUN && gDisableStructs[gBattlerAttacker].daybreakCounter >= 2))
         && battlerDef != battlerAtk
         && !IsGastroAcidBannedAbility(gBattleMons[battlerDef].ability)
         && gBattlerByTurnOrder[gCurrentTurnActionNumber] == battlerAtk
         && gActionsByTurnOrder[gCurrentTurnActionNumber] == B_ACTION_USE_MOVE
         && gCurrentTurnActionNumber < gBattlersCount);
}

u32 GetBattlerAbility(u32 battler)
{
    bool32 noAbilityShield = GetBattlerHoldEffectIgnoreAbility(battler, TRUE) != HOLD_EFFECT_ABILITY_SHIELD;
    bool32 noIgnorantBliss = (!(IsIgnorantBliss(battler, gBattleMons[battler].ability)));

    if (IsGastroAcidBannedAbility(gBattleMons[battler].ability))
    {
        // Edge case: pokemon under the effect of gastro acid transforms into a pokemon with Comatose (Todo: verify how other unsuppressable abilities behave)
        if (gBattleMons[battler].status2 & STATUS2_TRANSFORMED
            && gStatuses3[battler] & STATUS3_GASTRO_ACID
            && gBattleMons[battler].ability == ABILITY_COMATOSE)
                return ABILITY_NONE;

        if ((noAbilityShield || noIgnorantBliss) && CanBreakThroughAbility(gBattlerAttacker, battler, gBattleMons[gBattlerAttacker].ability))
            return ABILITY_NONE;

        return gBattleMons[battler].ability;
    }

    if (gStatuses3[battler] & STATUS3_GASTRO_ACID)
        return ABILITY_NONE;

    if (gBattleMons[gBattlerTarget].ability == ABILITY_IGNORANT_BLISS || GetBattlerHoldEffectIgnoreAbility(gBattlerTarget, TRUE) == HOLD_EFFECT_ABILITY_SHIELD)
        return ABILITY_NONE;

    if (IsNeutralizingGasOnField()
     && gBattleMons[battler].ability != ABILITY_NEUTRALIZING_GAS
     && (noAbilityShield || noIgnorantBliss))
        return ABILITY_NONE;

    if ((noAbilityShield || noIgnorantBliss) && CanBreakThroughAbility(gBattlerAttacker, battler, gBattleMons[gBattlerAttacker].ability))
        return ABILITY_NONE;

    return gBattleMons[battler].ability;
}

u32 IsAbilityOnSide(u32 battler, u32 ability)
{
    if (IsBattlerAlive(battler) && GetBattlerAbility(battler) == ability)
        return battler + 1;
    else if (IsBattlerAlive(BATTLE_PARTNER(battler)) && GetBattlerAbility(BATTLE_PARTNER(battler)) == ability)
        return BATTLE_PARTNER(battler) + 1;
    else
        return 0;
}

u32 IsAbilityOnOpposingSide(u32 battler, u32 ability)
{
    return IsAbilityOnSide(BATTLE_OPPOSITE(battler), ability);
}

u32 IsAbilityOnField(u32 ability)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (IsBattlerAlive(i) && GetBattlerAbility(i) == ability)
            return i + 1;
    }

    return 0;
}

u32 IsTeruCharmOnField(void)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (IsBattlerAlive(i) && GetBattlerHoldEffect(i, FALSE) == HOLD_EFFECT_TERU_CHARM && gBattleMons[i].species == SPECIES_CHIROBERRA)
            return i + 1;
    }

    return 0;
}

u32 IsAbilityOnFieldExcept(u32 battler, u32 ability)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (i != battler && IsBattlerAlive(i) && GetBattlerAbility(i) == ability)
            return i + 1;
    }

    return 0;
}

u32 IsAbilityPreventingEscape(u32 battler)
{
    u32 id;
    if (IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return 0;
    if ((id = GetBattlerAbility(battler) == ABILITY_LUMBERING))
        return id;
    if ((id = IsAbilityOnOpposingSide(battler, ABILITY_SPIRALYSIS)) && GetBattlerAbility(battler) != ABILITY_SPIRALYSIS && (!(IS_BATTLER_OF_TYPE(battler, TYPE_PSYCHIC))) && IsBattlerGrounded(battler) && IsBattlerTerrainAffected(battler, STATUS_FIELD_PSYCHIC_TERRAIN))
        return id;
    if ((id = IsAbilityOnOpposingSide(battler, ABILITY_SHADOW_TAG)) && GetBattlerAbility(battler) != ABILITY_SHADOW_TAG && (!(IsAbilityOnField(ABILITY_ILLUMINATE))) && (!(IS_BATTLER_OF_TYPE(battler, TYPE_DARK))))
        return id;
    if ((id = IsAbilityOnOpposingSide(battler, ABILITY_ARENA_TRAP)) && IsBattlerGrounded(battler))
        return id;
    if ((id = IsAbilityOnOpposingSide(battler, ABILITY_DELUGE)) && IsBattlerWeatherAffected(battler, B_WEATHER_RAIN))
        return id;
    if ((id = IsAbilityOnOpposingSide(battler, ABILITY_MAGNET_PULL)) && IS_BATTLER_OF_TYPE(battler, TYPE_STEEL))
        return id;

    return 0;
}

bool32 CanBattlerEscape(u32 battler) // no ability check
{
    if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_SHED_SHELL)
        return TRUE;
    else if (IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return TRUE;
    else if (GetBattlerAbility(battler) == ABILITY_RUN_AWAY)
        return TRUE;
    else if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_GLUE_TUBE)
        return FALSE;
    else if (gBattleMons[battler].status2 & (STATUS2_ESCAPE_PREVENTION | STATUS2_WRAPPED))
        return FALSE;
    else if (gStatuses3[battler] & STATUS3_ROOTED)
        return FALSE;
    else if (gSideTimers[GetBattlerSide(battler)].spotlightTimer > 1)
        return FALSE;
    else if (gStatuses4[battler] & STATUS4_FAIRY_LOCK)
        return FALSE;
    else if (gStatuses4[battler] & STATUS4_IMPRISON)
        return FALSE;
    else if (gStatuses3[battler] & STATUS3_SKY_DROPPED)
        return FALSE;
    else
        return TRUE;
}

void BattleScriptExecute(const u8 *BS_ptr)
{
    gBattlescriptCurrInstr = BS_ptr;
    gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size++] = gBattleMainFunc;
    gBattleMainFunc = RunBattleScriptCommands_PopCallbacksStack;
    gCurrentActionFuncId = 0;
}

void BattleScriptPushCursorAndCallback(const u8 *BS_ptr)
{
    BattleScriptPushCursor();
    gBattlescriptCurrInstr = BS_ptr;
    gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size++] = gBattleMainFunc;
    gBattleMainFunc = RunBattleScriptCommands;
}

enum
{
    ITEM_NO_EFFECT,
    ITEM_STATUS_CHANGE,
    ITEM_EFFECT_OTHER,
    ITEM_PP_CHANGE,
    ITEM_HP_CHANGE,
    ITEM_STATS_CHANGE,
    ITEM_HP_STATS_CHANGE,
};

bool32 IsBattlerTerrainAffected(u32 battler, u32 terrainFlag)
{
    if (!(gFieldStatuses & terrainFlag))
        return FALSE;
    else if (gStatuses3[battler] & STATUS3_SEMI_INVULNERABLE)
        return FALSE;

    return IsBattlerGrounded(battler);
}

bool32 CanSleep(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    if (ability == ABILITY_INSOMNIA 
    || ability == ABILITY_VITAL_SPIRIT 
    || ability == ABILITY_COMATOSE
    || ability == ABILITY_TITANIC
    || (IS_BATTLER_OF_TYPE(battler, TYPE_RELIC))
    || gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD 
    || gBattleMons[battler].status1 & STATUS1_ANY 
    || IsAbilityOnSide(battler, ABILITY_SWEET_VEIL)
    || IsAbilityStatusProtected(battler) 
    || (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battler].species == SPECIES_SEEDOT || gBattleMons[battler].species == SPECIES_NUZLEAF || gBattleMons[battler].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND))
    || (gStatuses4[battler] & STATUS4_GEARED_UP && gStatuses3[battler] & STATUS3_MAGNET_RISE)
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(1) 
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(2) 
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(3))
        return FALSE;
    return TRUE;
}

bool32 CanBePoisoned(u32 battlerAttacker, u32 battlerTarget)
{
    u16 ability = GetBattlerAbility(battlerTarget);

    if (!(CanPoisonType(battlerAttacker, battlerTarget)) 
    || gSideStatuses[GetBattlerSide(battlerTarget)] & SIDE_STATUS_SAFEGUARD 
    || gBattleMons[battlerTarget].status1 & STATUS1_ANY 
    || ability == ABILITY_IMMUNITY 
    || ability == ABILITY_COMATOSE 
    || ability == ABILITY_TITANIC
    || IsAbilityOnSide(battlerTarget, ABILITY_PASTEL_VEIL) 
    || IsAbilityStatusProtected(battlerTarget) 
    || (GetBattlerHoldEffect(battlerTarget, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battlerTarget].species == SPECIES_SEEDOT || gBattleMons[battlerTarget].species == SPECIES_NUZLEAF || gBattleMons[battlerTarget].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battlerTarget)] & SIDE_STATUS_TAILWIND))
    || (gStatuses4[battlerTarget] & STATUS4_GEARED_UP && gStatuses3[battlerTarget] & STATUS3_MAGNET_RISE)
    || gBattleMons[battlerTarget].status1 & STATUS1_BLOOMING_TURN(1) 
    || gBattleMons[battlerTarget].status1 & STATUS1_BLOOMING_TURN(2) 
    || gBattleMons[battlerTarget].status1 & STATUS1_BLOOMING_TURN(3))
        return FALSE;
    return TRUE;
}

bool32 CanBeBurned(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    if (IS_BATTLER_OF_TYPE(battler, TYPE_FIRE) 
    || gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD 
    || gBattleMons[battler].status1 & STATUS1_ANY 
    || ability == ABILITY_WATER_BUBBLE 
    || ability == ABILITY_COMATOSE 
    || ability == ABILITY_TITANIC
    || ability == ABILITY_THERMAL_EXCHANGE 
    || IsAbilityOnSide(battler, ABILITY_WATER_VEIL) 
    || IsAbilityStatusProtected(battler) 
    || (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battler].species == SPECIES_SEEDOT || gBattleMons[battler].species == SPECIES_NUZLEAF || gBattleMons[battler].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND))
    || (gStatuses4[battler] & STATUS4_GEARED_UP && gStatuses3[battler] & STATUS3_MAGNET_RISE)
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(1) 
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(2) 
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(3)
    || GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_NEVER_MELT_ICE)
        return FALSE;
    return TRUE;
}

bool32 CanBeParalyzed(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    if (
#if B_PARALYZE_ELECTRIC >= GEN_6
        IS_BATTLER_OF_TYPE(battler, TYPE_ELECTRIC) ||
#endif
        gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD 
        || ability == ABILITY_LIMBER || ability == ABILITY_COMATOSE 
        || ability == ABILITY_TITANIC
        || gBattleMons[battler].status1 & STATUS1_ANY 
        || IsAbilityStatusProtected(battler)
        || (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battler].species == SPECIES_SEEDOT || gBattleMons[battler].species == SPECIES_NUZLEAF || gBattleMons[battler].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND))
        || (gStatuses4[battler] & STATUS4_GEARED_UP && gStatuses3[battler] & STATUS3_MAGNET_RISE)
        || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(1) 
        || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(2) 
        || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(3))
        return FALSE;
    return TRUE;
}

bool32 CanBeFrozen(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    if (IS_BATTLER_OF_TYPE(battler, TYPE_ICE) 
    || IsBattlerWeatherAffected(battler, B_WEATHER_SUN) 
    || gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD 
    || ability == ABILITY_MAGMA_ARMOR
    || ability == ABILITY_COMATOSE 
    || ability == ABILITY_TITANIC
    || gBattleMons[battler].status1 & STATUS1_ANY 
    || IsAbilityStatusProtected(battler) 
    || (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battler].species == SPECIES_SEEDOT || gBattleMons[battler].species == SPECIES_NUZLEAF || gBattleMons[battler].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND))
    || (gStatuses4[battler] & STATUS4_GEARED_UP && gStatuses3[battler] & STATUS3_MAGNET_RISE)
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(1) 
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(2) 
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(3))
        return FALSE;
    return TRUE;
}

bool32 CanBeFrozenFrostbiteAbilityEdition(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    if (IS_BATTLER_OF_TYPE(battler, TYPE_ICE) 
    || IsBattlerWeatherAffected(battler, B_WEATHER_SUN) 
    || gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD 
    || ability == ABILITY_MAGMA_ARMOR
    || ability == ABILITY_COMATOSE 
    || ability == ABILITY_TITANIC
    || IsAbilityStatusProtected(battler) 
    || (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battler].species == SPECIES_SEEDOT || gBattleMons[battler].species == SPECIES_NUZLEAF || gBattleMons[battler].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND))
    || (gStatuses4[battler] & STATUS4_GEARED_UP && gStatuses3[battler] & STATUS3_MAGNET_RISE))
        return FALSE;
    return TRUE;
}

bool32 CanGetFrostbite(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    if (IS_BATTLER_OF_TYPE(battler, TYPE_ICE) 
    || gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD 
    || ability == ABILITY_MAGMA_ARMOR 
    || ability == ABILITY_COMATOSE 
    || ability == ABILITY_TITANIC
    || IsAbilityOnSide(battler, ABILITY_WATER_VEIL) 
    || gBattleMons[battler].status1 & STATUS1_ANY 
    || IsAbilityStatusProtected(battler) 
    || (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battler].species == SPECIES_SEEDOT || gBattleMons[battler].species == SPECIES_NUZLEAF || gBattleMons[battler].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND))
    || (gStatuses4[battler] & STATUS4_GEARED_UP && gStatuses3[battler] & STATUS3_MAGNET_RISE)
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(1) 
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(2) 
    || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(3))
        return FALSE;
    return TRUE;
}

bool32 CanGetPanicked(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    if (IS_BATTLER_OF_TYPE(battler, TYPE_DARK)
      || IS_BATTLER_OF_TYPE(battler, TYPE_GHOST)
      || gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD
      || ability == ABILITY_COMATOSE
      || ability == ABILITY_TITANIC
      || ability == ABILITY_IGNORANT_BLISS
      || ability == ABILITY_OBLIVIOUS
      || ability == ABILITY_UNAWARE
      || gBattleMons[battler].status1 & STATUS1_ANY
      || IsAbilityStatusProtected(battler)
      || (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battler].species == SPECIES_SEEDOT || gBattleMons[battler].species == SPECIES_NUZLEAF || gBattleMons[battler].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND)) 
      || (gStatuses4[battler] & STATUS4_GEARED_UP && gStatuses3[battler] & STATUS3_MAGNET_RISE)
      || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(1) 
      || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(2) 
      || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(3))
        return FALSE;
    return TRUE;
}

bool32 CanStartBlooming(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    // NOT blocked by safeguard or flower veil, etc
    if (IS_BATTLER_OF_TYPE(battler, TYPE_FIRE)
            || ability == ABILITY_COMATOSE
            || ability == ABILITY_TITANIC
            || gBattleMons[battler].status1 & STATUS1_ANY
            || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(1)
            || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(2)
            || gBattleMons[battler].status1 & STATUS1_BLOOMING_TURN(3))
        return FALSE;
    return TRUE;
}

bool32 CanBeExposed(u32 battler)
{
    u16 ability = GetBattlerAbility(battler);
    if (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD
            || ability == ABILITY_COMATOSE
            || ability == ABILITY_TITANIC
            || gBattleMons[battler].status1 & STATUS1_ANY
            || IsAbilityStatusProtected(battler)
            || (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_EERIE_MASK && (gBattleMons[battler].species == SPECIES_SEEDOT || gBattleMons[battler].species == SPECIES_NUZLEAF || gBattleMons[battler].species == SPECIES_SHIFTRY) && (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_TAILWIND))
            || (gStatuses4[battler] & STATUS4_GEARED_UP && gStatuses3[battler] & STATUS3_MAGNET_RISE))
        return FALSE;
    return TRUE;
}

bool32 CanBeConfused(u32 battler)
{
    if (GetBattlerAbility(battler) == ABILITY_OWN_TEMPO || gBattleMons[battler].status2 & STATUS2_CONFUSION || gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_SAFEGUARD || IS_BATTLER_OF_TYPE(battler, TYPE_PSYCHIC))
        return FALSE;
    return TRUE;
}

// second argument is 1/X of current hp compared to max hp
bool32 HasEnoughHpToEatBerry(u32 battler, u32 hpFraction, u32 itemId)
{
    bool32 isBerry = (ItemId_GetPocket(itemId) == POCKET_BERRIES);

    if (gBattleMons[battler].hp == 0)
        return FALSE;
    if (gBattleScripting.overrideBerryRequirements)
        return TRUE;
    // Unnerve prevents consumption of opponents' berries.
    if (isBerry && IsUnnerveAbilityOnOpposingSide(battler))
        return FALSE;
    if (gBattleMons[battler].hp <= gBattleMons[battler].maxHP / hpFraction)
        return TRUE;

    if (hpFraction <= 4 && GetBattlerAbility(battler) == ABILITY_GLUTTONY && isBerry && gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2)
    {
        RecordAbilityBattle(battler, ABILITY_GLUTTONY);
        return TRUE;
    }

    return FALSE;
}

#if B_CONFUSE_BERRIES_HEAL >= GEN_7
#define CONFUSE_BERRY_HP_FRACTION 4
#else
#define CONFUSE_BERRY_HP_FRACTION 2
#endif

static u8 HealConfuseBerry(u32 battler, u32 itemId, u32 flavorId, bool32 end2)
{
    if (HasEnoughHpToEatBerry(battler, CONFUSE_BERRY_HP_FRACTION, itemId)
#if B_HEAL_BLOCKING >= GEN_5
        && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK)
#endif
    )
    {
        PREPARE_FLAVOR_BUFFER(gBattleTextBuff1, flavorId);

        gBattleMoveDamage = gBattleMons[battler].maxHP / GetBattlerItemHoldEffectParam(battler, itemId);
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleMoveDamage *= -1;

        if (GetBattlerAbility(battler) == ABILITY_RIPEN)
        {
            gBattleMoveDamage *= 2;
            gBattlerAbility = battler;
        }
        gBattleScripting.battler = battler;
        if (end2)
        {
            if (GetFlavorRelationByPersonality(gBattleMons[battler].personality, flavorId) < 0)
                BattleScriptExecute(BattleScript_BerryConfuseHealEnd2);
            else
                BattleScriptExecute(BattleScript_ItemHealHP_RemoveItemEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            if (GetFlavorRelationByPersonality(gBattleMons[battler].personality, flavorId) < 0)
                gBattlescriptCurrInstr = BattleScript_BerryConfuseHealRet;
            else
                gBattlescriptCurrInstr = BattleScript_ItemHealHP_RemoveItemRet;
        }

        return ITEM_HP_CHANGE;
    }
    return 0;
}

#undef CONFUSE_BERRY_HP_FRACTION

static u8 StatRaiseBerry(u32 battler, u32 itemId, u32 statId, bool32 end2)
{
    if (CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN) && HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, itemId), itemId))
    {
        BufferStatChange(battler, statId, STRINGID_STATROSE);
        gEffectBattler = battler;
        if (GetBattlerAbility(battler) == ABILITY_RIPEN)
            SET_STATCHANGER(statId, 2, FALSE);
        else
            SET_STATCHANGER(statId, 1, FALSE);

        gBattleScripting.animArg1 = 14 + statId;
        gBattleScripting.animArg2 = 0;

        if (end2)
        {
            BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        }
        return ITEM_STATS_CHANGE;
    }
    return 0;
}

static u8 RandomStatRaiseBerry(u32 battler, u32 itemId, bool32 end2)
{
    s32 i;
    u16 stringId;

    for (i = 0; i < NUM_STATS - 1; i++)
    {
        if (CompareStat(battler, STAT_ATK + i, MAX_STAT_STAGE, CMP_LESS_THAN))
            break;
    }
    if (i != NUM_STATS - 1 && HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, itemId), itemId))
    {
        u16 battlerAbility = GetBattlerAbility(battler);
        do
        {
            i = Random() % (NUM_STATS - 1);
        } while (!CompareStat(battler, STAT_ATK + i, MAX_STAT_STAGE, CMP_LESS_THAN));

        PREPARE_STAT_BUFFER(gBattleTextBuff1, i + 1);
        stringId = (battlerAbility == ABILITY_CONTRARY) ? STRINGID_STATFELL : STRINGID_STATROSE;
        gBattleTextBuff2[0] = B_BUFF_PLACEHOLDER_BEGIN;
        gBattleTextBuff2[1] = B_BUFF_STRING;
        gBattleTextBuff2[2] = STRINGID_STATSHARPLY;
        gBattleTextBuff2[3] = STRINGID_STATSHARPLY >> 8;
        gBattleTextBuff2[4] = B_BUFF_STRING;
        gBattleTextBuff2[5] = stringId;
        gBattleTextBuff2[6] = stringId >> 8;
        gBattleTextBuff2[7] = EOS;
        gEffectBattler = battler;
        if (battlerAbility == ABILITY_RIPEN)
            SET_STATCHANGER(i + 1, 4, FALSE);
        else
            SET_STATCHANGER(i + 1, 2, FALSE);

        gBattleScripting.animArg1 = 0x21 + i + 6;
        gBattleScripting.animArg2 = 0;
        if (end2)
        {
            BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        }

        return ITEM_STATS_CHANGE;
    }
    return 0;
}

static u8 TrySetMicleBerry(u32 battler, u32 itemId, bool32 end2)
{
    if (HasEnoughHpToEatBerry(battler, 4, itemId))
    {
        gProtectStructs[battler].usedMicleBerry = TRUE; // battler's next attack has increased accuracy

        if (end2)
        {
            BattleScriptExecute(BattleScript_MicleBerryActivateEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_MicleBerryActivateRet;
        }
        return ITEM_EFFECT_OTHER;
    }
    return 0;
}

static u8 TrySetEnigmaBerry(u32 battler)
{
    if (IsBattlerAlive(battler) && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove) && ((TARGET_TURN_DAMAGED && gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE) || gBattleScripting.overrideBerryRequirements) && !(gBattleScripting.overrideBerryRequirements && gBattleMons[battler].hp == gBattleMons[battler].maxHP)
#if B_HEAL_BLOCKING >= GEN_5
        && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
#endif
    {
        gBattleScripting.battler = battler;
        gBattleMoveDamage = (gBattleMons[battler].maxHP * 25 / 100) * -1;
        if (GetBattlerAbility(battler) == ABILITY_RIPEN)
            gBattleMoveDamage *= 2;

        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_ItemHealHP_RemoveItemRet;
        return ITEM_HP_CHANGE;
    }
    return 0;
}

static u8 DamagedStatBoostBerryEffect(u32 battler, u8 statId, u8 split)
{
    if (IsBattlerAlive(battler) && CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN) && (gBattleScripting.overrideBerryRequirements || (!DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove) && GetBattleMoveSplit(gCurrentMove) == split && BATTLER_DAMAGED(battler))))
    {
        BufferStatChange(battler, statId, STRINGID_STATROSE);

        gEffectBattler = battler;
        if (GetBattlerAbility(battler) == ABILITY_RIPEN)
            SET_STATCHANGER(statId, 2, FALSE);
        else
            SET_STATCHANGER(statId, 1, FALSE);

        gBattleScripting.battler = battler;
        gBattleScripting.animArg1 = 14 + statId;
        gBattleScripting.animArg2 = 0;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        return ITEM_STATS_CHANGE;
    }
    return 0;
}

static u8 TryEjectPack(u32 battler, bool32 execute)
{
    if (gProtectStructs[battler].statFell
     && !gProtectStructs[battler].disableEjectPack
     && CountUsablePartyMons(battler) > 0
     && !(gCurrentMove == MOVE_PARTING_SHOT && CanBattlerSwitch(gBattlerAttacker))) // Does not activate if attacker used Parting Shot and can switch out
    {
        gProtectStructs[battler].statFell = FALSE;
        gBattleScripting.battler = battler;
        if (execute)
        {
            BattleScriptExecute(BattleScript_EjectPackActivate_End2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_EjectPackActivate_Ret;
        }
        return ITEM_STATS_CHANGE;
    }
    return 0;
}

static u8 DamagedPomegBerryEffect(u32 battler, u32 itemId, bool32 end2)
{
    if (HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, itemId), itemId)
    && CountBattlerStatDecreases(battler, TRUE) > 0)
    {
        if (end2)
        {
            BattleScriptExecute(BattleScript_PomegBerryInvertEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_PomegBerryInvertReturn;
        }
        return ITEM_EFFECT_OTHER;
    }
    return 0;
}

static u8 DamagedHondewBerryEffect(u32 battler, u32 itemId, bool32 end2)
{
    if (HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, itemId), itemId) 
    && (!(gStatuses3[battler] & STATUS3_AQUA_RING)))
    {
        if (end2)
        {
            BattleScriptExecute(BattleScript_HondewBerryActivatesEnd2);
        }
        else
        {
            gStatuses3[battler] |= STATUS3_AQUA_RING;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_HondewBerryActivatesReturn;
        }
        return ITEM_EFFECT_OTHER;
    }
    return 0;
}

static u8 DamagedYellowSodaEffect(u32 battler, u32 itemId, bool32 end2)
{
    if (HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, itemId), itemId) 
    && ((!(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
    || (!(gBattleMons[battler].status2 & STATUS2_FOCUS_ENERGY_ANY))
    || (!(CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_EQUAL)))))
    {
        if (end2)
        {
            BattleScriptExecute(BattleScript_YellowSodaActivatesEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_YellowSodaActivatesReturn;
        }
        return ITEM_EFFECT_OTHER;
    }
    return 0;
}

static u8 DamagedCheeseEffect(u32 battler, u32 itemId, bool32 end2)
{
    if (HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, itemId), itemId) 
    && ((!(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
    || (!(CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_SPDEF, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_ACC, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_EVASION, MAX_STAT_STAGE, CMP_EQUAL)))))
    {
        if (end2)
        {
            BattleScriptExecute(BattleScript_CheeseActivatesEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_CheeseActivatesReturn;
        }
        return ITEM_EFFECT_OTHER;
    }
}

static u8 DamagedFrothyCheeseEffect(u32 battler, u32 itemId, bool32 end2)
{
    if (HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, itemId), itemId) 
    && ((!(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
    || (!(CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_SPDEF, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_ACC, MAX_STAT_STAGE, CMP_EQUAL)))
    || (!(CompareStat(battler, STAT_EVASION, MAX_STAT_STAGE, CMP_EQUAL)))))
    {
        if (end2)
        {
            BattleScriptExecute(BattleScript_FrothyCheeseActivatesEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_FrothyCheeseActivatesReturn;
        }
        return ITEM_EFFECT_OTHER;
    }
}

u8 TryHandleSeed(u32 battler, u32 terrainFlag, u8 statId, u16 itemId, bool32 execute)
{
    if (gFieldStatuses & terrainFlag && CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
    {
        BufferStatChange(battler, statId, STRINGID_STATROSE);
        gLastUsedItem = itemId; // For surge abilities
        gEffectBattler = gBattleScripting.battler = battler;
        SET_STATCHANGER(statId, 1, FALSE);
        gBattleScripting.animArg1 = 14 + statId;
        gBattleScripting.animArg2 = 0;
        if (execute)
        {
            BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        }
        return ITEM_STATS_CHANGE;
    }
    return 0;
}

static u32 ItemRestorePp(u32 battler, u32 itemId, bool32 execute)
{
    struct Pokemon *party = GetBattlerParty(battler);
    struct Pokemon *mon = &party[gBattlerPartyIndexes[battler]];
    u32 i, changedPP = 0;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u32 move = GetMonData(mon, MON_DATA_MOVE1 + i);
        u32 currentPP = GetMonData(mon, MON_DATA_PP1 + i);
        u32 ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES);
        u32 maxPP = CalculatePPWithBonus(move, ppBonuses, i);
        if (move && (currentPP == 0 || (gBattleScripting.overrideBerryRequirements && currentPP != maxPP)))
        {
            u32 ppRestored = GetBattlerItemHoldEffectParam(battler, itemId);

            if (GetBattlerAbility(battler) == ABILITY_RIPEN)
            {
                ppRestored *= 2;
                gBattlerAbility = battler;
            }
            if (currentPP + ppRestored > maxPP)
                changedPP = maxPP;
            else
                changedPP = currentPP + ppRestored;

            PREPARE_MOVE_BUFFER(gBattleTextBuff1, move);

            if (execute)
            {
                BattleScriptExecute(BattleScript_BerryPPHealEnd2);
            }
            else
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_BerryPPHealRet;
            }
            BtlController_EmitSetMonData(battler, BUFFER_A, i + REQUEST_PPMOVE1_BATTLE, 0, 1, &changedPP);
            MarkBattlerForControllerExec(battler);
            if (MOVE_IS_PERMANENT(battler, i))
                gBattleMons[battler].pp[i] = changedPP;
            return ITEM_PP_CHANGE;
        }
    }
    return 0;
}

static u8 ItemHealHp(u32 battler, u32 itemId, bool32 end2, bool32 percentHeal)
{
    u32 pomegHP = (gBattleMons[battler].maxHP + 200);
    if (!(gBattleScripting.overrideBerryRequirements && gBattleMons[battler].hp == gBattleMons[battler].maxHP)
#if B_HEAL_BLOCKING >= GEN_5
        && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK)
#endif
        && HasEnoughHpToEatBerry(battler, 2, itemId))
    {
        if (percentHeal)
            gBattleMoveDamage = (gBattleMons[battler].maxHP * GetBattlerItemHoldEffectParam(battler, itemId) / 100) * -1;
        else
            gBattleMoveDamage = GetBattlerItemHoldEffectParam(battler, itemId) * -1;

        // check ripen
        if (ItemId_GetPocket(itemId) == POCKET_BERRIES && GetBattlerAbility(battler) == ABILITY_RIPEN)
            gBattleMoveDamage *= 2;

        gBattlerAbility = battler; // in SWSH, berry juice shows ability pop up but has no effect. This is mimicked here
        if (end2)
        {
            BattleScriptExecute(BattleScript_ItemHealHP_RemoveItemEnd2);
        }
        else if (itemId == 534)
        {
            BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_MAX_HP_BATTLE, 0, sizeof(gBattleMons[battler].hp), &pomegHP);
            MarkBattlerForControllerExec(battler);
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_ItemHealHP_RemoveItemRet;
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_ItemHealHP_RemoveItemRet;
        }

        if (gBattleResources->flags->flags[battler] & RESOURCE_FLAG_EMERGENCY_EXIT
         && gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 2)
            gBattleResources->flags->flags[battler] &= ~RESOURCE_FLAG_EMERGENCY_EXIT;

        return ITEM_HP_CHANGE;
    }
    return 0;
}

static bool32 UnnerveOn(u32 battler, u32 itemId)
{
    if (ItemId_GetPocket(itemId) == POCKET_BERRIES && IsUnnerveAbilityOnOpposingSide(battler))
        return TRUE;
    return FALSE;
}

static bool32 GetMentalHerbEffect(u32 battler)
{
    bool32 ret = FALSE;

    if (gBattleMons[battler].status2 & STATUS2_INFATUATION 
    || gDisableStructs[battler].tauntTimer != 0
    || gDisableStructs[battler].encoreTimer != 0
    || gDisableStructs[battler].encoreTimer != 0
    || gBattleMons[battler].status2 & STATUS2_TORMENT
    || gStatuses3[battler] & STATUS3_HEAL_BLOCK
    || gDisableStructs[battler].disableTimer != 0
    || gBattleMons[battler].status2 & STATUS2_CONFUSION)
    {
        gBattleMons[battler].status2 &= ~STATUS2_INFATUATION;
        gDisableStructs[battler].tauntTimer = 0;
        gDisableStructs[battler].encoredMove = 0;
        gDisableStructs[battler].encoreTimer = 0;
        gBattleMons[battler].status2 &= ~STATUS2_TORMENT;
        gStatuses3[battler] &= ~STATUS3_HEAL_BLOCK;
        gDisableStructs[battler].disableTimer = 0;
        gDisableStructs[battler].disabledMove = 0;
        gBattleMons[battler].status2 &= ~(STATUS2_CONFUSION);
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_INFATUATION; // STRINGID_TARGETGOTOVERINFATUATION
        ret = TRUE;
    }

    return ret;
}

static u8 TryConsumeMirrorHerb(u32 battler, bool32 execute)
{
    u8 effect = 0;

    if (gProtectStructs[battler].eatMirrorHerb && IsBattlerAlive(battler))
    {
        gLastUsedItem = gBattleMons[battler].item;
        gBattleScripting.battler = battler;
        gProtectStructs[battler].eatMirrorHerb = 0;
        ChooseStatBoostAnimation(battler);
        if (execute)
        {
            BattleScriptExecute(BattleScript_MirrorHerbCopyStatChangeEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_MirrorHerbCopyStatChange;
        }
        effect = ITEM_STATS_CHANGE;
    }
    return effect;
}

static u32 RestoreWhiteHerbStats(u32 battler)
{
    u32 i, effect = 0;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battler].statStages[i] < DEFAULT_STAT_STAGE)
        {
            gBattleMons[battler].statStages[i] = DEFAULT_STAT_STAGE;
            effect = ITEM_STATS_CHANGE;
        }
    }
    if (effect != 0)
    {
        gBattleScripting.battler = battler;
        gPotentialItemEffectBattler = battler;
    }
    return effect;
}

static u8 ItemEffectMoveEnd(u32 battler, u16 holdEffect)
{
    u8 effect = 0;
    u32 i;

    switch (holdEffect)
    {
#if B_HP_BERRIES >= GEN_4
    case HOLD_EFFECT_MICLE_BERRY:
        effect = TrySetMicleBerry(battler, gLastUsedItem, FALSE);
        break;
    case HOLD_EFFECT_RESTORE_HP:
        effect = ItemHealHp(battler, gLastUsedItem, FALSE, FALSE);
        break;
#endif
#if B_BERRIES_INSTANT >= GEN_4
    case HOLD_EFFECT_RESTORE_PCT_HP:
        effect = ItemHealHp(battler, gLastUsedItem, FALSE, TRUE);
        break;
    case HOLD_EFFECT_RESTORE_PP:
        effect = ItemRestorePp(battler, gLastUsedItem, FALSE);
        break;
    case HOLD_EFFECT_CONFUSE_SPICY:
        effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SPICY, FALSE);
        break;
    case HOLD_EFFECT_CONFUSE_DRY:
        effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_DRY, FALSE);
        break;
    case HOLD_EFFECT_CONFUSE_SWEET:
        effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SWEET, FALSE);
        break;
    case HOLD_EFFECT_CONFUSE_BITTER:
        effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_BITTER, FALSE);
        break;
    case HOLD_EFFECT_CONFUSE_SOUR:
        effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SOUR, FALSE);
        break;
    case HOLD_EFFECT_ATTACK_UP:
        effect = StatRaiseBerry(battler, gLastUsedItem, STAT_ATK, FALSE);
        break;
    case HOLD_EFFECT_DEFENSE_UP:
        effect = StatRaiseBerry(battler, gLastUsedItem, STAT_DEF, FALSE);
        break;
    case HOLD_EFFECT_SPEED_UP:
        effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPEED, FALSE);
        break;
    case HOLD_EFFECT_SP_ATTACK_UP:
        effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPATK, FALSE);
        break;
    case HOLD_EFFECT_SP_DEFENSE_UP:
        effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPDEF, FALSE);
        break;
    //OLD ENIGMA BERRY EFFECT
    //case HOLD_EFFECT_ENIGMA_BERRY: // consume and heal if hit by super effective move
        //effect = TrySetEnigmaBerry(battler);
        //break;
    case HOLD_EFFECT_KEE_BERRY: // consume and boost defense if used physical move
        effect = DamagedStatBoostBerryEffect(battler, STAT_DEF, SPLIT_PHYSICAL);
        break;
    case HOLD_EFFECT_MARANGA_BERRY: // consume and boost sp. defense if used special move
        effect = DamagedStatBoostBerryEffect(battler, STAT_SPDEF, SPLIT_SPECIAL);
        break;
    case HOLD_EFFECT_RANDOM_STAT_UP:
        effect = RandomStatRaiseBerry(battler, gLastUsedItem, FALSE);
        break;
    case HOLD_EFFECT_POMEG_BERRY:
        effect = DamagedPomegBerryEffect(battler, gLastUsedItem, FALSE);
        break;
    case HOLD_EFFECT_HONDEW_BERRY:
        effect = DamagedHondewBerryEffect(battler, gLastUsedItem, FALSE);
        break;
    case HOLD_EFFECT_YELLOW_SODA:
        effect = DamagedYellowSodaEffect(battler, gLastUsedItem, FALSE);
        break;
    case HOLD_EFFECT_CHEESE:
        effect = DamagedCheeseEffect(battler, gLastUsedItem, FALSE);
        break;
    case HOLD_EFFECT_FROTHY_CHEESE:
        effect = DamagedFrothyCheeseEffect(battler, gLastUsedItem, FALSE);
        break;
#endif
    case HOLD_EFFECT_CURE_PAR:
        if (gBattleMons[battler].status1 & STATUS1_PARALYSIS && !UnnerveOn(battler, gLastUsedItem))
        {
            gBattleMons[battler].status1 &= ~STATUS1_PARALYSIS;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCureParRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_CURE_PSN:
        if (gBattleMons[battler].status1 & STATUS1_PSN_ANY && !UnnerveOn(battler, gLastUsedItem))
        {
            gBattleMons[battler].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCurePsnRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_CURE_BRN:
        if (gBattleMons[battler].status1 & STATUS1_BURN && !UnnerveOn(battler, gLastUsedItem))
        {
            gBattleMons[battler].status1 &= ~STATUS1_BURN;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCureBrnRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_CURE_FRZ:
        if (gBattleMons[battler].status1 & STATUS1_FREEZE && !UnnerveOn(battler, gLastUsedItem))
        {
            gBattleMons[battler].status1 &= ~STATUS1_FREEZE;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCureFrzRet;
            effect = ITEM_STATUS_CHANGE;
        }
        if (gBattleMons[battler].status1 & STATUS1_FROSTBITE && !UnnerveOn(battler, gLastUsedItem))
        {
            gBattleMons[battler].status1 &= ~STATUS1_FROSTBITE;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCureFsbRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_CURE_SLP:
        if (gBattleMons[battler].status1 & STATUS1_SLEEP_ANY && !UnnerveOn(battler, gLastUsedItem))
        {
            gBattleMons[battler].status1 &= ~STATUS1_SLEEP_ANY;
            gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCureSlpRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_CURE_PANIC:
        if (gBattleMons[battler].status1 & STATUS1_PANIC && !UnnerveOn(battler, gLastUsedItem))
        {
            gBattleMons[battler].status1 &= ~STATUS1_PANIC;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCurePanicRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_WATMEL_BERRY:
        if (gBattleMons[battler].status1 & STATUS1_BLOOMING && !UnnerveOn(battler, gLastUsedItem))
        {
            gBattleMoveDamage = gBattleMons[battler].maxHP / 2;
            if (gBattleMoveDamage == 0)
                gBattleMoveDamage = 1;
            if (GetBattlerAbility(battler) == ABILITY_RIPEN)
                gBattleMoveDamage *= 2;
            if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                gBattleMoveDamage = 50;
            gBattleMons[battler].status1 &= ~STATUS1_BLOOMING;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCureBloomRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_CURE_CONFUSION:
        if (gBattleMons[battler].status2 & STATUS2_CONFUSION && !UnnerveOn(battler, gLastUsedItem))
        {
            RemoveConfusionStatus(battler);
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryCureConfusionRet;
            effect = ITEM_EFFECT_OTHER;
        }
        break;
    case HOLD_EFFECT_MENTAL_HERB:
        if (GetMentalHerbEffect(battler))
        {
            gBattleScripting.savedBattler = gBattlerAttacker;
            gBattlerAttacker = battler;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_MentalHerbCureRet;
            effect = ITEM_EFFECT_OTHER;
        }
        break;
    case HOLD_EFFECT_CURE_STATUS:
        if ((gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE || gBattleMons[battler].status2 & STATUS2_CONFUSION) && !UnnerveOn(battler, gLastUsedItem))
        {
            BufferStatusCondition(battler, TRUE);
            if (gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE)
            {
                gBattleMons[battler].status1 = 0;
            }
            RemoveConfusionStatus(battler);
            BattleScriptPushCursor();
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
            gBattlescriptCurrInstr = BattleScript_BerryCureChosenStatusRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_FAVOR_SCARF:
        if ((gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE || gBattleMons[battler].status2 & STATUS2_CONFUSION) && (Random() % 5) == 0)
        {
            BufferStatusCondition(battler, TRUE);
            if (gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE)
            {
                gBattleMons[battler].status1 = 0;
            }
            RemoveConfusionStatus(battler);
            BattleScriptPushCursor();
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
            gBattlescriptCurrInstr = BattleScript_FavorScarfCuredStatusRet;
            effect = ITEM_STATUS_CHANGE;
        }
        break;
    case HOLD_EFFECT_CRITICAL_UP: // lansat berry
        if (B_BERRIES_INSTANT >= GEN_4 && !(gBattleMons[battler].status2 & STATUS2_FOCUS_ENERGY_ANY) && HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, gLastUsedItem), gLastUsedItem))
        {
            gBattleMons[battler].status2 |= STATUS2_FOCUS_ENERGY;
            gBattleScripting.battler = battler;
            gPotentialItemEffectBattler = battler;
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryFocusEnergyRet;
            effect = ITEM_EFFECT_OTHER;
        }
        break;
    case HOLD_EFFECT_BERSERK_GENE:
        BufferStatChange(battler, STAT_ATK, STRINGID_STATROSE);
        gEffectBattler = battler;
        if (CanBeInfinitelyConfused(gEffectBattler))
        {
            gStatuses4[gEffectBattler] |= STATUS4_INFINITE_CONFUSION;
        }
        SET_STATCHANGER(STAT_ATK, 2, FALSE);

        gBattleScripting.animArg1 = 14 + STAT_ATK;
        gBattleScripting.animArg2 = 0;

        BattleScriptPushCursorAndCallback(BattleScript_BerserkGeneRet);
        effect = ITEM_STATS_CHANGE;
        break;
    case HOLD_EFFECT_MIRROR_HERB:
        effect = TryConsumeMirrorHerb(battler, FALSE);
        break;
    }

    return effect;
}

u8 ItemBattleEffects(u8 caseID, u32 battler, bool32 moveTurn)
{
    int i = 0, moveType;
    u8 effect = ITEM_NO_EFFECT;
    u8 changedPP = 0;
    u32 battlerHoldEffect, atkHoldEffect;
    u8 atkHoldEffectParam;
    u16 atkItem;

    if (caseID != ITEMEFFECT_USE_LAST_ITEM)
    {
        gLastUsedItem = gBattleMons[battler].item;
        battlerHoldEffect = GetBattlerHoldEffect(battler, TRUE);
    }

    atkItem = gBattleMons[gBattlerAttacker].item;
    atkHoldEffect = GetBattlerHoldEffect(gBattlerAttacker, TRUE);
    atkHoldEffectParam = GetBattlerHoldEffectParam(gBattlerAttacker);

    switch (caseID)
    {
    case ITEMEFFECT_ON_SWITCH_IN:
        if (!gSpecialStatuses[battler].switchInItemDone)
        {
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_DOUBLE_PRIZE:
                if (GetBattlerSide(battler) == B_SIDE_PLAYER && !gBattleStruct->moneyMultiplierItem)
                {
                    gBattleStruct->moneyMultiplier *= 2;
                    gBattleStruct->moneyMultiplierItem = 1;
                }
                break;
            case HOLD_EFFECT_TERU_CHARM:
                if (gBattleMons[battler].species == SPECIES_CHIROBERRA)
                {
                    gBattlerAttacker = battler;
                    TryChangeBattleWeather(battler, WEATHER_NONE, TRUE);
                    BattleScriptExecute(BattleScript_AnnounceTeruCharm);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_RESTORE_STATS:
                effect = RestoreWhiteHerbStats(battler);
                if (effect != 0)
                {
                    gBattlerAttacker = battler;
                    BattleScriptExecute(BattleScript_WhiteHerbEnd2);
                }
                break;
#if B_BERRIES_INSTANT >= GEN_4
            case HOLD_EFFECT_CONFUSE_SPICY:
                effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SPICY, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_DRY:
                effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_DRY, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SWEET:
                effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SWEET, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_BITTER:
                effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_BITTER, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SOUR:
                effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SOUR, TRUE);
                break;
            case HOLD_EFFECT_ATTACK_UP:
                effect = StatRaiseBerry(battler, gLastUsedItem, STAT_ATK, TRUE);
                break;
            case HOLD_EFFECT_DEFENSE_UP:
                effect = StatRaiseBerry(battler, gLastUsedItem, STAT_DEF, TRUE);
                break;
            case HOLD_EFFECT_SPEED_UP:
                effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPEED, TRUE);
                break;
            case HOLD_EFFECT_SP_ATTACK_UP:
                effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPATK, TRUE);
                break;
            case HOLD_EFFECT_SP_DEFENSE_UP:
                effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPDEF, TRUE);
                break;
            case HOLD_EFFECT_POMEG_BERRY:
                effect = DamagedPomegBerryEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_HONDEW_BERRY:
                effect = DamagedHondewBerryEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_YELLOW_SODA:
                effect = DamagedYellowSodaEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_CHEESE:
                effect = DamagedCheeseEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_FROTHY_CHEESE:
                effect = DamagedFrothyCheeseEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_CRITICAL_UP:
                if (!(gBattleMons[battler].status2 & STATUS2_FOCUS_ENERGY_ANY) && HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, gLastUsedItem), gLastUsedItem))
                {
                    gBattleMons[battler].status2 |= STATUS2_FOCUS_ENERGY;
                    gBattleScripting.battler = battler;
                    BattleScriptExecute(BattleScript_BerryFocusEnergyEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_RANDOM_STAT_UP:
                effect = RandomStatRaiseBerry(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_CURE_PAR:
                if (gBattleMons[battler].status1 & STATUS1_PARALYSIS && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_PARALYSIS;
                    BattleScriptExecute(BattleScript_BerryCurePrlzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PSN:
                if (gBattleMons[battler].status1 & STATUS1_PSN_ANY && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
                    BattleScriptExecute(BattleScript_BerryCurePsnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_BRN:
                if (gBattleMons[battler].status1 & STATUS1_BURN && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_BURN;
                    BattleScriptExecute(BattleScript_BerryCureBrnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_FRZ:
                if (gBattleMons[battler].status1 & STATUS1_FREEZE && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_FREEZE;
                    BattleScriptExecute(BattleScript_BerryCureFrzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                if (gBattleMons[battler].status1 & STATUS1_FROSTBITE && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_FROSTBITE;
                    BattleScriptExecute(BattleScript_BerryCureFsbEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_SLP:
                if (gBattleMons[battler].status1 & STATUS1_SLEEP_ANY && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_SLEEP_ANY;
                    gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
                    BattleScriptExecute(BattleScript_BerryCureSlpEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PANIC:
                if (gBattleMons[battler].status1 & STATUS1_PANIC && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_PANIC;
                    BattleScriptExecute(BattleScript_BerryCurePanicEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_WATMEL_BERRY:
                if (gBattleMons[battler].status1 & STATUS1_BLOOMING && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 2;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (GetBattlerAbility(battler) == ABILITY_RIPEN)
                        gBattleMoveDamage *= 2;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    gBattleMons[battler].status1 &= ~STATUS1_BLOOMING;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureBloomRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_STATUS:
                if ((gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE || gBattleMons[battler].status2 & STATUS2_CONFUSION) && !UnnerveOn(battler, gLastUsedItem))
                {
                    i = BufferStatusCondition(battler, TRUE);
                    if (i <= 1)
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_NORMALIZED_STATUS;
                    if (gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE)
                    {
                        gBattleMons[battler].status1 = 0;
                    }
                    RemoveConfusionStatus(battler);
                    BattleScriptExecute(BattleScript_BerryCureChosenStatusEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_FAVOR_SCARF:
                if ((gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE || gBattleMons[battler].status2 & STATUS2_CONFUSION) && (Random() % 5) == 0)
                {
                    i = BufferStatusCondition(battler, TRUE);
                    if (i <= 1)
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_NORMALIZED_STATUS;
                    if (gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE)
                    {
                        gBattleMons[battler].status1 = 0;
                    }
                    RemoveConfusionStatus(battler);
                    BattleScriptExecute(BattleScript_FavorScarfCuredStatusEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_RESTORE_HP:
                effect = ItemHealHp(battler, gLastUsedItem, TRUE, FALSE);
                break;
            case HOLD_EFFECT_RESTORE_PCT_HP:
                effect = ItemHealHp(battler, gLastUsedItem, TRUE, TRUE);
                break;
#endif
            case HOLD_EFFECT_AIR_BALLOON:
                effect = ITEM_EFFECT_OTHER;
                gBattleScripting.battler = battler;
                BattleScriptPushCursorAndCallback(BattleScript_AirBaloonMsgIn);
                RecordItemEffectBattle(battler, HOLD_EFFECT_AIR_BALLOON);
                break;
            case HOLD_EFFECT_BLOOM_ORB:
                if (CanStartBlooming(battler))
                {
                    effect = ITEM_STATUS_CHANGE;;
                    gBattleMons[battler].status1 = STATUS1_BLOOMING_TURN(1);
                    BattleScriptPushCursorAndCallback(BattleScript_BloomOrb);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_BLOOM_ORB);
                }
                break;
            case HOLD_EFFECT_GEMSTONE:
                if (gBattleMons[battler].species == SPECIES_HARACE)
                {
                    effect = ITEM_EFFECT_OTHER;
                    gBattleScripting.battler = battler;
                    gDisableStructs[battler].gemstoneEvasionCounter = 3;
                    BattleScriptPushCursorAndCallback(BattleScript_GemstoneEvasion);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_GEMSTONE);
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                }
                break;
            case HOLD_EFFECT_CRYPTIC_PLATE:
                if (gBattleMons[battler].species == SPECIES_UHEFOE)
                {
                    effect = ITEM_EFFECT_OTHER;
                    gBattleScripting.battler = battler;
                    BattleScriptPushCursorAndCallback(BattleScript_CrypticPlateEntryEffect);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_CRYPTIC_PLATE);
                }
                break;
            case HOLD_EFFECT_ROOM_SERVICE:
                if (TryRoomService(battler))
                {
                    BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
                    effect = ITEM_STATS_CHANGE;
                }
                break;
            case HOLD_EFFECT_SEEDS:
                switch (GetBattlerHoldEffectParam(battler))
                {
                case HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN:
                    effect = TryHandleSeed(battler, STATUS_FIELD_ELECTRIC_TERRAIN, STAT_DEF, gLastUsedItem, TRUE);
                    break;
                case HOLD_EFFECT_PARAM_GRASSY_TERRAIN:
                    effect = TryHandleSeed(battler, STATUS_FIELD_GRASSY_TERRAIN, STAT_DEF, gLastUsedItem, TRUE);
                    break;
                case HOLD_EFFECT_PARAM_MISTY_TERRAIN:
                    effect = TryHandleSeed(battler, STATUS_FIELD_MISTY_TERRAIN, STAT_SPDEF, gLastUsedItem, TRUE);
                    break;
                case HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN:
                    effect = TryHandleSeed(battler, STATUS_FIELD_PSYCHIC_TERRAIN, STAT_SPDEF, gLastUsedItem, TRUE);
                    break;
                }
                break;
            case HOLD_EFFECT_EJECT_PACK:
                effect = TryEjectPack(battler, TRUE);
                break;
            case HOLD_EFFECT_BERSERK_GENE:
                BufferStatChange(battler, STAT_ATK, STRINGID_STATROSE);
                gEffectBattler = battler;
                if (CanBeInfinitelyConfused(gEffectBattler))
                {
                    gStatuses4[gEffectBattler] |= STATUS4_INFINITE_CONFUSION;
                }
                SET_STATCHANGER(STAT_ATK, 2, FALSE);

                gBattleScripting.animArg1 = 14 + STAT_ATK;
                gBattleScripting.animArg2 = 0;

                BattleScriptPushCursorAndCallback(BattleScript_BerserkGeneRet);
                effect = ITEM_STATS_CHANGE;
                break;
            case HOLD_EFFECT_MIRROR_HERB:
                effect = TryConsumeMirrorHerb(battler, TRUE);
                break;
            }
            if (effect != 0)
            {
                gSpecialStatuses[battler].switchInItemDone = TRUE;
                gBattlerAttacker = gPotentialItemEffectBattler = gBattleScripting.battler = battler;
                switch (effect)
                {
                case ITEM_STATUS_CHANGE:
                    BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                    MarkBattlerForControllerExec(battler);
                    break;
                }
            }
        }
        break;
    case ITEMEFFECT_NORMAL:
        if (gBattleMons[battler].hp)
        {
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_RESTORE_HP:
                if (!moveTurn)
                    effect = ItemHealHp(battler, gLastUsedItem, TRUE, FALSE);
                break;
            case HOLD_EFFECT_RESTORE_PCT_HP:
                if (!moveTurn)
                    effect = ItemHealHp(battler, gLastUsedItem, TRUE, TRUE);
                break;
            case HOLD_EFFECT_RESTORE_PP:
                if (!moveTurn)
                    effect = ItemRestorePp(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_RESTORE_STATS:
                effect = RestoreWhiteHerbStats(battler);
                if (effect != 0)
                {
                    gBattlerAttacker = battler;
                    BattleScriptExecute(BattleScript_WhiteHerbEnd2);
                }
                break;
            case HOLD_EFFECT_BLACK_SLUDGE:
                if (IS_BATTLER_OF_TYPE(battler, TYPE_POISON))
                {
                    goto LEFTOVERS;
                }
                else if (GetBattlerAbility(battler) != ABILITY_MAGIC_GUARD 
                && !moveTurn 
                && GetBattlerAbility(battler) != ABILITY_SUGAR_COAT)
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    BattleScriptExecute(BattleScript_ItemHurtEnd2);
                    effect = ITEM_HP_CHANGE;
                    RecordItemEffectBattle(battler, battlerHoldEffect);
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                }
                break;
            case HOLD_EFFECT_LEFTOVERS:
            LEFTOVERS:
#if B_HEAL_BLOCKING >= GEN_5
                if (gBattleMons[battler].hp < gBattleMons[battler].maxHP && !moveTurn && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
#else
                if (gBattleMons[battler].hp < gBattleMons[battler].maxHP && !moveTurn)
#endif
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 16;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                    BattleScriptExecute(BattleScript_ItemHealHP_End2);
                    effect = ITEM_HP_CHANGE;
                    RecordItemEffectBattle(battler, battlerHoldEffect);
                }
                break;
            case HOLD_EFFECT_HEART_GIFT:
                if (!moveTurn && gDisableStructs[battler].surpriseCounter < 3)
                {
                    gDisableStructs[battler].surpriseCounter++;
                    BattleScriptExecute(BattleScript_HeartGiftSurpriseCount);
                    effect = ITEM_EFFECT_OTHER;
                    RecordItemEffectBattle(battler, battlerHoldEffect);
                }
                if (!moveTurn && gDisableStructs[battler].surpriseCounter >= 3)
                {
                    gDisableStructs[battler].surpriseCounter = 0;
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 2;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    BattleScriptExecute(BattleScript_HeartGiftSurpriseFulfilled);
                    effect = ITEM_HP_CHANGE;
                    RecordItemEffectBattle(battler, battlerHoldEffect);
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                }
                break;
            case HOLD_EFFECT_GEMSTONE:
                if (!moveTurn 
                && gBattleMons[battler].species == SPECIES_HARACE 
                && gDisableStructs[battler].gemstoneEvasionCounter > 0)
                {
                    gDisableStructs[battler].gemstoneEvasionCounter -= 1;
                    BattleScriptPushCursorAndCallback(BattleScript_GemstoneEvasionDrop);
                    effect = ITEM_STATS_CHANGE;
                    RecordItemEffectBattle(battler, battlerHoldEffect);
                }
                break;
            case HOLD_EFFECT_A_THING:
                if ((gBattleMons[battler].species == SPECIES_CAPYBARA || gBattleMons[battler].species == SPECIES_ABARBINASH) && (Random() % 100) == 0 && !moveTurn)
                {
                    BattleScriptExecute(BattleScript_A_Thing_HappenedFR);
                    effect = ITEM_HP_CHANGE,
                    RecordItemEffectBattle(battler, battlerHoldEffect);
                }
                else if ((gBattleMons[battler].species == SPECIES_CAPYBARA || gBattleMons[battler].species == SPECIES_ABARBINASH) && !moveTurn)
                {
                    BattleScriptExecute(BattleScript_A_Thing_Happened);
                    effect = ITEM_HP_CHANGE,
                    RecordItemEffectBattle(battler, battlerHoldEffect);
                }
                break;
            case HOLD_EFFECT_CONFUSE_SPICY:
                if (!moveTurn)
                    effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SPICY, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_DRY:
                if (!moveTurn)
                    effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_DRY, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SWEET:
                if (!moveTurn)
                    effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SWEET, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_BITTER:
                if (!moveTurn)
                    effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_BITTER, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SOUR:
                if (!moveTurn)
                    effect = HealConfuseBerry(battler, gLastUsedItem, FLAVOR_SOUR, TRUE);
                break;
            case HOLD_EFFECT_ATTACK_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battler, gLastUsedItem, STAT_ATK, TRUE);
                break;
            case HOLD_EFFECT_DEFENSE_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battler, gLastUsedItem, STAT_DEF, TRUE);
                break;
            case HOLD_EFFECT_SPEED_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPEED, TRUE);
                break;
            case HOLD_EFFECT_SP_ATTACK_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPATK, TRUE);
                break;
            case HOLD_EFFECT_SP_DEFENSE_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battler, gLastUsedItem, STAT_SPDEF, TRUE);
                break;
            case HOLD_EFFECT_POMEG_BERRY:
                if (!moveTurn)
                    effect = DamagedPomegBerryEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_HONDEW_BERRY:
                if (!moveTurn)
                    effect = DamagedHondewBerryEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_YELLOW_SODA:
                if (!moveTurn)
                    effect = DamagedYellowSodaEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_CHEESE:
                if (!moveTurn)
                    effect = DamagedCheeseEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_FROTHY_CHEESE:
                if (!moveTurn)
                    effect = DamagedFrothyCheeseEffect(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_CRITICAL_UP:
                if (!moveTurn && !(gBattleMons[battler].status2 & STATUS2_FOCUS_ENERGY_ANY) && HasEnoughHpToEatBerry(battler, GetBattlerItemHoldEffectParam(battler, gLastUsedItem), gLastUsedItem))
                {
                    gBattleMons[battler].status2 |= STATUS2_FOCUS_ENERGY;
                    gBattleScripting.battler = battler;
                    BattleScriptExecute(BattleScript_BerryFocusEnergyEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_RANDOM_STAT_UP:
                if (!moveTurn)
                    effect = RandomStatRaiseBerry(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_CURE_PAR:
                if (gBattleMons[battler].status1 & STATUS1_PARALYSIS && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_PARALYSIS;
                    BattleScriptExecute(BattleScript_BerryCurePrlzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PSN:
                if (gBattleMons[battler].status1 & STATUS1_PSN_ANY && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
                    BattleScriptExecute(BattleScript_BerryCurePsnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_BRN:
                if (gBattleMons[battler].status1 & STATUS1_BURN && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_BURN;
                    BattleScriptExecute(BattleScript_BerryCureBrnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_FRZ:
                if (gBattleMons[battler].status1 & STATUS1_FREEZE && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_FREEZE;
                    BattleScriptExecute(BattleScript_BerryCureFrzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                if (gBattleMons[battler].status1 & STATUS1_FROSTBITE && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_FROSTBITE;
                    BattleScriptExecute(BattleScript_BerryCureFsbEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_SLP:
                if (gBattleMons[battler].status1 & STATUS1_SLEEP_ANY && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_SLEEP_ANY;
                    gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
                    BattleScriptExecute(BattleScript_BerryCureSlpEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PANIC:
                if (gBattleMons[battler].status1 & STATUS1_PANIC && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMons[battler].status1 &= ~STATUS1_PANIC;
                    BattleScriptExecute(BattleScript_BerryCurePanicEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_WATMEL_BERRY:
                if (gBattleMons[battler].status1 & STATUS1_BLOOMING && !UnnerveOn(battler, gLastUsedItem))
                {
                    gBattleMoveDamage = gBattleMons[battler].maxHP / 2;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (GetBattlerAbility(battler) == ABILITY_RIPEN)
                        gBattleMoveDamage *= 2;
                    if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    gBattleMons[battler].status1 = 0;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureBloomRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_CONFUSION:
                if (gBattleMons[battler].status2 & STATUS2_CONFUSION && !UnnerveOn(battler, gLastUsedItem))
                {
                    RemoveConfusionStatus(battler);
                    BattleScriptExecute(BattleScript_BerryCureConfusionEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_CURE_STATUS:
                if ((gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE || gBattleMons[battler].status2 & STATUS2_CONFUSION) && !UnnerveOn(battler, gLastUsedItem))
                {
                    i = BufferStatusCondition(battler, TRUE);
                    if (i <= 1)
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_NORMALIZED_STATUS;
                    if (gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE)
                    {
                        gBattleMons[battler].status1 = 0;
                    }
                    RemoveConfusionStatus(battler);
                    BattleScriptExecute(BattleScript_BerryCureChosenStatusEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_FAVOR_SCARF:
                if ((gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE || gBattleMons[battler].status2 & STATUS2_CONFUSION) && (Random() % 5) == 0)
                {
                    i = BufferStatusCondition(battler, TRUE);
                    if (i <= 1)
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_NORMALIZED_STATUS;
                    if (gBattleMons[battler].status1 & STATUS1_ANY_NEGATIVE)
                    {
                        gBattleMons[battler].status1 = 0;
                    }
                    RemoveConfusionStatus(battler);
                    BattleScriptExecute(BattleScript_FavorScarfCuredStatusEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_MENTAL_HERB:
                if (GetMentalHerbEffect(battler))
                {
                    gBattleScripting.savedBattler = gBattlerAttacker;
                    gBattlerAttacker = battler;
                    BattleScriptExecute(BattleScript_MentalHerbCureEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_MICLE_BERRY:
                if (!moveTurn)
                    effect = TrySetMicleBerry(battler, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_BERSERK_GENE:
                BufferStatChange(battler, STAT_ATK, STRINGID_STATROSE);
                gEffectBattler = battler;
                if (CanBeInfinitelyConfused(gEffectBattler))
                {
                    gStatuses4[gEffectBattler] |= STATUS4_INFINITE_CONFUSION;
                }
                SET_STATCHANGER(STAT_ATK, 2, FALSE);

                gBattleScripting.animArg1 = 14 + STAT_ATK;
                gBattleScripting.animArg2 = 0;

                BattleScriptPushCursorAndCallback(BattleScript_BerserkGeneRet);
                effect = ITEM_STATS_CHANGE;
                break;
            case HOLD_EFFECT_MIRROR_HERB:
                effect = TryConsumeMirrorHerb(battler, TRUE);
                break;
            }

            if (effect != 0)
            {
                gBattlerAttacker = gPotentialItemEffectBattler = gBattleScripting.battler = battler;
                switch (effect)
                {
                case ITEM_STATUS_CHANGE:
                    BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                    MarkBattlerForControllerExec(battler);
                    break;
                }
            }
        }
        break;
    case ITEMEFFECT_USE_LAST_ITEM:
        effect = ItemEffectMoveEnd(battler, ItemId_GetHoldEffect(gLastUsedItem));
        gBattleScripting.overrideBerryRequirements = 2; // to exit VARIOUS_CONSUME_BERRIES
        if (effect)
        {
            gPotentialItemEffectBattler = gBattleScripting.battler = battler;
            if (effect == ITEM_STATUS_CHANGE)
            {
                BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                MarkBattlerForControllerExec(battler);
            }
            break;
        }
        break;
    case ITEMEFFECT_MOVE_END:
        for (battler = 0; battler < gBattlersCount; battler++)
        {
            gLastUsedItem = gBattleMons[battler].item;
            effect = ItemEffectMoveEnd(battler, GetBattlerHoldEffect(battler, TRUE));
            if (effect)
            {
                gPotentialItemEffectBattler = gBattleScripting.battler = battler;
                if (effect == ITEM_STATUS_CHANGE)
                {
                    BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                    MarkBattlerForControllerExec(battler);
                }
                break;
            }
        }
        break;
    case ITEMEFFECT_KINGSROCK:
        // Occur on each hit of a multi-strike move
        switch (atkHoldEffect)
        {
        case HOLD_EFFECT_SHELL_BELL:
            if (gSpecialStatuses[gBattlerAttacker].damagedMons  // Need to have done damage
                && gBattlerAttacker != gBattlerTarget
                && gBattleMons[gBattlerAttacker].hp != gBattleMons[gBattlerAttacker].maxHP
                && IsBattlerAlive(gBattlerAttacker)
                && !(gStatuses3[gBattlerAttacker] & STATUS3_HEAL_BLOCK))
            {
                gLastUsedItem = atkItem;
                gPotentialItemEffectBattler = gBattlerAttacker;
                gBattleScripting.battler = gBattlerAttacker;
                gBattleMoveDamage = (gSpecialStatuses[gBattlerTarget].shellBellDmg / atkHoldEffectParam) * -1;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = -1;
                gSpecialStatuses[gBattlerTarget].shellBellDmg = 0;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemHealHP_Ret;
                effect = ITEM_HP_CHANGE;
            }
            break;
        case HOLD_EFFECT_LONG_NOSE:
        {
            u16 ability = GetBattlerAbility(gBattlerAttacker);
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED 
                && IsBattlerAlive(gBattlerTarget)
                && !NoAliveMonsForEitherParty()
                && (gMultiHitCounter == 1 || gMultiHitCounter == 0)
                && (moveType ==  TYPE_BUG || moveType == TYPE_DARK)
                && (CompareStat(gBattlerTarget, STAT_ATK, MIN_STAT_STAGE, CMP_GREATER_THAN) 
                || CompareStat(gBattlerTarget, STAT_SPATK, MIN_STAT_STAGE, CMP_GREATER_THAN)
                || CompareStat(gBattlerTarget, STAT_ACC, MIN_STAT_STAGE, CMP_GREATER_THAN)
                || CompareStat(gBattlerTarget, STAT_EVASION, MIN_STAT_STAGE, CMP_GREATER_THAN))
                && gBattleMons[gBattlerAttacker].species == SPECIES_MOSKOPO)
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_LONG_NOSE;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                effect++;
            }
        }
        break;
        case HOLD_EFFECT_NANAB_BERRY:
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED 
                && (!(IS_MOVE_STATUS(gCurrentMove)))
                && gBattleMons[gBattlerTarget].hp 
                && (!(gStatuses3[gBattlerTarget] & STATUS3_MINIMIZED)))
            {
                gLastUsedItem = atkItem;
                gStatuses3[gBattlerTarget] |= STATUS3_MINIMIZED;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_NanabBerryActivatesRet;    
                effect++;
            }
            break;
        case HOLD_EFFECT_WEPEAR_BERRY:
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED 
                && (!(IS_MOVE_STATUS(gCurrentMove)))
                && gBattleMons[gBattlerTarget].hp 
                && (!(gStatuses3[gBattlerTarget] & STATUS3_HEAL_BLOCK)))
            {
                gLastUsedItem = atkItem;
                gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK;
                gDisableStructs[gBattlerTarget].healBlockTimer = 5;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_WepearBerryActivatesRet;    
                effect++;
            }
            break;
        case HOLD_EFFECT_FLINCH:
        {
            u16 ability = GetBattlerAbility(gBattlerAttacker);
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED 
                && !gBattleMoves[gCurrentMove].ignoresKingsRock 
                && gBattleMons[gBattlerTarget].hp 
                && RandomPercentage(RNG_HOLD_EFFECT_FLINCH, atkHoldEffectParam) 
                && ability != ABILITY_STENCH)
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_FLINCH;
                BattleScriptPushCursor();
                SetMoveEffect(FALSE, 0);
                BattleScriptPop();
            }
        }
        break;
        case HOLD_EFFECT_RAZOR_FANG:
        {
            u16 ability = GetBattlerAbility(gBattlerAttacker);
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED
                && (gBattleMons[gBattlerAttacker].species == SPECIES_GLIGAR || gBattleMons[gBattlerAttacker].species == SPECIES_GLISCOR)
                && CompareStat(gBattlerTarget, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN)
                && gBattleMons[gBattlerTarget].hp 
                && RandomPercentage(RNG_HOLD_EFFECT_RAZOR_FANG, atkHoldEffectParam))
            {
                SET_STATCHANGER(STAT_DEF, 1, TRUE);
                gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_1;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                effect++;
            }
        }
        break;
        case HOLD_EFFECT_STILETTO:
        {
            u16 ability = GetBattlerAbility(gBattlerAttacker);
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED
                && CompareStat(gBattlerTarget, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN)
                && gBattleMons[gBattlerTarget].hp 
                && RandomPercentage(RNG_HOLD_EFFECT_STILETTO, atkHoldEffectParam)
                && gBattleMoves[gCurrentMove].kickingMove)
            {
                SET_STATCHANGER(STAT_SPEED, 1, TRUE);
                gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_1;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                effect++;
            }
        }
        break;
        case HOLD_EFFECT_CORRODE_MOD:
        {
            u16 ability = GetBattlerAbility(gBattlerAttacker);

            if (IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_RELIC) 
            && gBattleMoves[gCurrentMove].type == TYPE_RELIC
            && gBattleMoveDamage != 0 // Need to have done damage)
            && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && TARGET_TURN_DAMAGED
            && gBattleMons[gBattlerTarget].hp
            && RandomPercentage(RNG_HOLD_EFFECT_RAZOR_FANG, 30))
            {
                if (IS_MOVE_PHYSICAL(gCurrentMove) 
                && CompareStat(gBattlerTarget, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN))
                {
                    SET_STATCHANGER(STAT_DEF, 1, TRUE);
                    gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                    effect++;
                }
                else if (IS_MOVE_SPECIAL(gCurrentMove)
                && CompareStat(gBattlerTarget, STAT_SPDEF, MIN_STAT_STAGE, CMP_GREATER_THAN))
                {
                    SET_STATCHANGER(STAT_SPDEF, 1, TRUE);
                    gBattleScripting.moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                    effect++;
                }
            }
        }
        break;
        case HOLD_EFFECT_BLACK_SALAD:
        {
            u16 ability = GetBattlerAbility(gBattlerAttacker);
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED
                && CanStartBlooming(gBattlerTarget)
                && gBattleMons[gBattlerTarget].hp)
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_BLOOMING;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STATUSED_BY_ITEM;
                effect++;
            }
            else if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED
                && gBattleMons[gBattlerTarget].hp 
                && gBattleMons[gBattlerTarget].status1 & STATUS1_BLOOMING
                && !(gStatuses3[gBattlerTarget] & STATUS3_HEAL_BLOCK))
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemHealBlockEffect;
                effect++;
            }
        }
        break;
        case HOLD_EFFECT_COARSE_SAND:
        {
            u16 ability = GetBattlerAbility(gBattlerAttacker);
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED 
                && gBattleMoves[gCurrentMove].sandMove 
                && gBattleMons[gBattlerTarget].hp 
                && RandomPercentage(RNG_HOLD_EFFECT_COARSE_SAND, atkHoldEffectParam)
                && CompareStat(gBattlerAttacker, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN))
            {
                SET_STATCHANGER(STAT_DEF, 2, TRUE);
                gBattleScripting.moveEffect = MOVE_EFFECT_DEF_MINUS_2;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                effect++;
            }
        }
        break;
        case HOLD_EFFECT_BURNT_BRANCH:
        {
            u16 ability = GetBattlerAbility(gBattlerAttacker);
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                && TARGET_TURN_DAMAGED 
                && !(IS_MOVE_STATUS(gCurrentMove))
                && CanBeBurned(gBattlerTarget)
                && IsBattlerAlive(gBattlerTarget)
                && moveType == TYPE_GRASS
                && RandomPercentage(RNG_HOLD_EFFECT_BLACK_GLASSES, 20))
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STATUSED_BY_ITEM;
                gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                effect++;
            }
        }
        break;
        case HOLD_EFFECT_PESKY_PLUSH:
        {
            if (gBattleMoveDamage != 0 // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED
                && (!(IS_MOVE_STATUS(gCurrentMove)))
                && gBattleMons[gBattlerTarget].hp 
                && moveType == TYPE_BUG)
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemTauntEffect;
                effect++;
            }
        }
        break;
        case HOLD_EFFECT_BLUNDER_POLICY:
            if (gBattleStruct->blunderPolicy && gBattleMons[gBattlerAttacker].hp != 0 && CompareStat(gBattlerAttacker, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gBattleStruct->blunderPolicy = FALSE;
                gLastUsedItem = atkItem;
                gBattleScripting.statChanger = SET_STATCHANGER(STAT_SPEED, 2, FALSE);
                effect = ITEM_STATS_CHANGE;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AttackerItemStatRaise;
            }
            break;
        case HOLD_EFFECT_FAIRY_FEATHER:
            if (gBattleMoveDamage != 0
            && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
            && gBattleMons[gBattlerAttacker].hp != 0
            && TARGET_TURN_DAMAGED
            && CanBeConfused(gBattlerTarget) 
            && !IS_MOVE_STATUS(gCurrentMove)
            && gBattleMoves[gCurrentMove].type == TYPE_FAIRY
            && RandomPercentage(RNG_HOLD_EFFECT_BLACK_GLASSES, 20))
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_STATUSED_BY_ITEM;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemSecondaryEffect;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                effect++;
            }
            break;
        case HOLD_EFFECT_SILVER_POWDER: // 50% chance to leave powder on foe when using bug type move
            if (gBattleMoveDamage != 0 // Need to have done damage
                    && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMoves[gCurrentMove].type == TYPE_BUG
                    && IsBattlerAlive(gBattlerTarget)
                    && TARGET_TURN_DAMAGED
                    && !IS_MOVE_STATUS(gCurrentMove)
                    && !(gBattleMons[gBattlerTarget].status2 & STATUS2_POWDER)
                    && RandomPercentage(RNG_HOLD_EFFECT_SILVER_POWDER, 50)) 
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_MoveEffectPowder;
                effect++;
            }
            break;
        case HOLD_EFFECT_SOFT_SAND: // ground type moves have 30% chance to lower accuracy
            if (gBattleMoveDamage != 0 // Need to have done damage
                    && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMoves[gCurrentMove].type == TYPE_GROUND
                    && IsBattlerAlive(gBattlerTarget)
                    && TARGET_TURN_DAMAGED
                    && !IS_MOVE_STATUS(gCurrentMove)
                    && CompareStat(gBattlerTarget, STAT_ACC, MIN_STAT_STAGE, CMP_GREATER_THAN)
                    && RandomPercentage(RNG_HOLD_EFFECT_SOFT_SAND, 30))
            {
                gEffectBattler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AccDown;
                effect++;
            }
            break;
        case HOLD_EFFECT_SPELL_TAG: // ghost moves reduce target PP by 2
            if (gBattleMoveDamage != 0 // Need to have done damage
                    && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMoves[gCurrentMove].type == TYPE_GHOST
                    && IsBattlerAlive(gBattlerTarget)
                    && !IS_MOVE_STATUS(gCurrentMove)
                    && TARGET_TURN_DAMAGED)
            {
                gEffectBattler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_MoveEffectPPReduce;
                effect++;
            }
            break;
        case HOLD_EFFECT_BLACK_GLASSES:
            if (gBattleMoveDamage != 0 // Need to have done damage
                    && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMoves[gCurrentMove].type == TYPE_DARK
                    && IsBattlerAlive(gBattlerTarget)
                    && !IS_MOVE_STATUS(gCurrentMove)
                    && TARGET_TURN_DAMAGED)
            {
                gEffectBattler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_MoveEffectTorment;
                effect++;
            }
            break;
        }
        break;
    case ITEMEFFECT_LIFEORB_SHELLBELL:
        // Occur after the final hit of a multi-strike move
        switch (atkHoldEffect)
        {
        case HOLD_EFFECT_MIRACLE_SEED:
            if (gSpecialStatuses[gBattlerAttacker].damagedMons  // Need to have done damage
                && gBattlerAttacker != gBattlerTarget
                && gBattleMons[gBattlerAttacker].hp != gBattleMons[gBattlerAttacker].maxHP
                && IsBattlerAlive(gBattlerAttacker)
                && moveType == TYPE_GRASS
                && !(gStatuses3[gBattlerAttacker] & STATUS3_HEAL_BLOCK))
            {
                gLastUsedItem = atkItem;
                gPotentialItemEffectBattler = gBattlerAttacker;
                gBattleScripting.battler = gBattlerAttacker;
                gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 10;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = -1;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemHealHP_Ret;
                effect = ITEM_HP_CHANGE;
            }
            break;
        case HOLD_EFFECT_LIFE_ORB:
            if (IsBattlerAlive(gBattlerAttacker)
                && !(TestSheerForceFlag(gBattlerAttacker, gCurrentMove))
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_SUGAR_COAT
                && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                && !gSpecialStatuses[gBattlerAttacker].preventLifeOrbDamage
                && gSpecialStatuses[gBattlerAttacker].damagedMons)
            {
                gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 10;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                effect = ITEM_HP_CHANGE;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemHurtRet;
                gLastUsedItem = gBattleMons[gBattlerAttacker].item;
            }
            break;
        case HOLD_EFFECT_THROAT_SPRAY:                                                                                                                                                                                                                         // Does NOT need to be a damaging move
            if (gProtectStructs[gBattlerAttacker].targetAffected 
                && gBattleMons[gBattlerAttacker].hp != 0 
                && gBattleMoves[gCurrentMove].soundMove 
                && CompareStat(gBattlerAttacker, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN) 
                && !NoAliveMonsForEitherParty()) // Don't activate if battle will end
            {
                gLastUsedItem = atkItem;
                gBattleScripting.battler = gBattlerAttacker;
                gBattleScripting.statChanger = SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                effect = ITEM_STATS_CHANGE;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AttackerItemStatRaise;
            }
            break;
        case HOLD_EFFECT_FLIP_COIN:                                                                                                                                                                                                                         // Does NOT need to be a damaging move
            if ((!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
                && IsBattlerAlive(gBattlerTarget)
                && TARGET_TURN_DAMAGED
                && !IS_MOVE_STATUS(gCurrentMove)
                && CountBattlerStatIncreases(gBattlerTarget, TRUE) > 0
                && !NoAliveMonsForEitherParty()) // Don't activate if battle will end
            {
                gLastUsedItem = atkItem;
                effect = ITEM_EFFECT_OTHER;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_FlipCoinFlipStats;
            }
            break;
        case HOLD_EFFECT_HARD_STONE:    // if use rock type move, next attack on us does 20% less dmg (this turn only)
            if (IsBattlerAlive(gBattlerAttacker)
            && gBattleMoves[gCurrentMove].type == TYPE_ROCK
            && TARGET_TURN_DAMAGED
            && (!(gProtectStructs[gBattlerAttacker].hardStoneBoost)))
                gProtectStructs[gBattlerAttacker].hardStoneBoost = TRUE;
            break;
        case HOLD_EFFECT_MYSTIC_WATER:  // if using water move, 30% chance to undo negative stat changes
            if (IsBattlerAlive(gBattlerAttacker)
            && gBattleMoves[gCurrentMove].type == TYPE_WATER
            && CountBattlerStatDecreases(gBattlerAttacker, TRUE) > 0
            && TARGET_TURN_DAMAGED
            && RandomPercentage(RNG_HOLD_EFFECT_MYSTIC_WATER, 30)
            && !NoAliveMonsForEitherParty())
            {
                gBattleScripting.battler = gBattlerAttacker;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ResetNegativeStatStages;
                effect++;
            }
            break;
        }
        break;
    case ITEMEFFECT_TARGET:
        if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            GET_MOVE_TYPE(gCurrentMove, moveType);
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_CURSED_AMULET:
                if (TARGET_TURN_DAMAGED
                && IsMoveMakingContact(gCurrentMove, gBattlerAttacker)
                && gDisableStructs[gBattlerAttacker].disabledMove == MOVE_NONE
                && IsBattlerAlive(gBattlerAttacker)
                && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL)
                && gBattleMons[gBattlerAttacker].pp[gChosenMovePos] != 0
                && (Random() % 3) == 0) // Hardcoding the chance here since cant get it working right through holdEffectParam
                {
                    gDisableStructs[gBattlerAttacker].disabledMove = gChosenMove;
                    gDisableStructs[gBattlerAttacker].disableTimer = 4;
                    effect = ITEM_EFFECT_OTHER;
                    PREPARE_MOVE_BUFFER(gBattleTextBuff1, gChosenMove);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CursedAmuletActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff2, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_CURSED_AMULET);
                }
                break;
            case HOLD_EFFECT_AIR_BALLOON:
                if (TARGET_TURN_DAMAGED)
                {
                    effect = ITEM_EFFECT_OTHER;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AirBaloonMsgPop;
                }
                break;
            case HOLD_EFFECT_ROCKY_HELMET:
                if (TARGET_TURN_DAMAGED 
                && IsMoveMakingContact(gCurrentMove, gBattlerAttacker) 
                && IsBattlerAlive(gBattlerAttacker)
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD 
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_SUGAR_COAT)
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 6;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;
                    effect = ITEM_HP_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RockyHelmetActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_ROCKY_HELMET);
                }
                break;
            case HOLD_EFFECT_KAMEN_SCARF:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                && TARGET_TURN_DAMAGED
                && !(gStatuses3[gBattlerTarget] & STATUS3_CHARGED_UP)
                && IsBattlerAlive(gBattlerTarget)
                && !IS_MOVE_STATUS(gCurrentMove)
                && gBattleMons[gBattlerTarget].species == SPECIES_SHOCKORE)
                {
                    effect = ITEM_EFFECT_OTHER;
                    gStatuses3[gBattlerTarget] |= STATUS3_CHARGED_UP;
                    gDisableStructs[gBattlerTarget].chargeTimer = 0;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_KamenScarfActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_KAMEN_SCARF);
                }
                break;
            case HOLD_EFFECT_SILVER_CROWN:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) 
                && TARGET_TURN_DAMAGED 
                && !(gBattleMons[gBattlerAttacker].status2 & STATUS2_WRAPPED)
                && IsBattlerAlive(gBattlerAttacker)
                && !IS_MOVE_STATUS(gCurrentMove)
                && gBattleMons[gBattlerTarget].species == SPECIES_FLAGUE_PRINCE)
                {
                    effect = ITEM_EFFECT_OTHER;

                    gBattleMons[gBattlerAttacker].status2 |= STATUS2_WRAPPED;
                    gDisableStructs[gBattlerAttacker].wrapTurns = (Random() % 2) + 4;

                    gBattleStruct->wrappedMove[gBattlerAttacker] = MOVE_INFESTATION;
                    gBattleStruct->wrappedBy[gBattlerAttacker] = gBattlerTarget;

                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_SilverCrownActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_SILVER_CROWN);
                }
                break;
            case HOLD_EFFECT_WEAKNESS_POLICY:
                if (IsBattlerAlive(battler) && TARGET_TURN_DAMAGED && gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_WeaknessPolicy;
                }
                break;
            case HOLD_EFFECT_LOST_MANTLE:
                if (IsBattlerAlive(battler) 
                && TARGET_TURN_DAMAGED
                && !IS_MOVE_STATUS(gCurrentMove)
                && (Random() % 2) == 0)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_LostMantle;
                }
                break;
            case HOLD_EFFECT_SNOWBALL:
                if (IsBattlerAlive(battler) && TARGET_TURN_DAMAGED && moveType == TYPE_ICE)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_Snowball;
                }
                break;
            case HOLD_EFFECT_LUMINOUS_MOSS:
                if (IsBattlerAlive(battler) && TARGET_TURN_DAMAGED && moveType == TYPE_WATER)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_LuminousMoss;
                }
                break;
            case HOLD_EFFECT_CELL_BATTERY:
                if (IsBattlerAlive(battler) && TARGET_TURN_DAMAGED && moveType == TYPE_ELECTRIC)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CellBattery;
                }
                break;
            case HOLD_EFFECT_ABSORB_BULB:
                if (IsBattlerAlive(battler) && TARGET_TURN_DAMAGED && moveType == TYPE_WATER)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AbsorbBulb;
                }
                break;
            // OLD ENIGMA BERRY EFFECT
            //case HOLD_EFFECT_ENIGMA_BERRY: // consume and heal if hit by super effective move
            //    effect = TrySetEnigmaBerry(battler);
            //    break;
            case HOLD_EFFECT_JABOCA_BERRY: // consume and damage attacker if used physical move
                if (IsBattlerAlive(battler) 
                && TARGET_TURN_DAMAGED 
                && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove) 
                && IS_MOVE_PHYSICAL(gCurrentMove) 
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD 
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_SUGAR_COAT)
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (GetBattlerAbility(battler) == ABILITY_RIPEN)
                        gBattleMoveDamage *= 2;
                    if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;

                    effect = ITEM_HP_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_JabocaRowapBerryActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_ROCKY_HELMET);
                }
                break;
            case HOLD_EFFECT_BLUK_BERRY: // consume and damage attacker if used physical move
                if (IsBattlerAlive(gBattlerAttacker)
                && IsBattlerAlive(battler)
                && TARGET_TURN_DAMAGED
                && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove))
                {
                    effect = ITEM_EFFECT_OTHER;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BlukBerryActivatesRet;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_BLUK_BERRY);
                }
                break;
            case HOLD_EFFECT_BELUE_BERRY:
                if (IsBattlerAlive(gBattlerAttacker)
                && IsBattlerAlive(battler)
                && TARGET_TURN_DAMAGED
                && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)
                && !gDisableStructs[gBattlerAttacker].tarShot)
                {
                    effect = ITEM_EFFECT_OTHER;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BelueBerryActivatesRet;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_BELUE_BERRY);
                }
                break;
            case HOLD_EFFECT_CORNN_BERRY:
                if (IsBattlerAlive(gBattlerAttacker)
                && TARGET_TURN_DAMAGED
                && IsBattlerAlive(battler)
                && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)
                && !gStatuses4[gBattlerAttacker] & STATUS4_SALT_CURE
                && gBattleMons[gBattlerTarget].hp < gBattleMons[gBattlerTarget].maxHP / 4)
                {
                    effect = ITEM_EFFECT_OTHER;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CornnBerryActivatesRet;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_CORNN_BERRY);
                }
                break;
            case HOLD_EFFECT_DURIN_BERRY:
                if (IsBattlerAlive(gBattlerAttacker)
                && TARGET_TURN_DAMAGED
                && IsBattlerAlive(battler)
                && (CompareStat(gBattlerAttacker, STAT_ATK, MIN_STAT_STAGE, CMP_GREATER_THAN)
                || CompareStat(gBattlerAttacker, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN)
                || CompareStat(gBattlerAttacker, STAT_SPATK, MIN_STAT_STAGE, CMP_GREATER_THAN)
                || CompareStat(gBattlerAttacker, STAT_SPDEF, MIN_STAT_STAGE, CMP_GREATER_THAN)
                || CompareStat(gBattlerAttacker, STAT_ACC, MIN_STAT_STAGE, CMP_GREATER_THAN)
                || CompareStat(gBattlerAttacker, STAT_EVASION, MIN_STAT_STAGE, CMP_GREATER_THAN))
                && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)
                && gBattleMons[gBattlerTarget].hp < gBattleMons[gBattlerTarget].maxHP / 2)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_DurinBerryAllStatsDown;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_DURIN_BERRY);
                }
                break;
            case HOLD_EFFECT_RIZZ_BERRY:
                if (IsBattlerAlive(gBattlerAttacker)
                && IsBattlerAlive(gBattlerTarget)
                && TARGET_TURN_DAMAGED
                && gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE
                && (!(DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)))
                && (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION))
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_OBLIVIOUS
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_IGNORANT_BLISS
                && (!(IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL))))
                {
                    effect = ITEM_EFFECT_OTHER;
                    gBattleMons[gBattlerAttacker].status2 |= STATUS2_INFATUATED_WITH(gBattlerTarget);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RizzBerryActivatesRet;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_RIZZ_BERRY);
                }
                break;
            case HOLD_EFFECT_RAZZ_BERRY:
                if (IsBattlerAlive(gBattlerAttacker)
                && IsBattlerAlive(gBattlerTarget)
                && TARGET_TURN_DAMAGED
                && AreBattlersOfOppositeGender(gBattlerAttacker, gBattlerTarget)
                && (!(DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)))
                && (!(gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION))
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_OBLIVIOUS
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_IGNORANT_BLISS
                && (!(IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL))))
                {
                    effect = ITEM_EFFECT_OTHER;
                    gBattleMons[gBattlerAttacker].status2 |= STATUS2_INFATUATED_WITH(gBattlerTarget);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RizzBerryActivatesRet;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_RAZZ_BERRY);
                }
                break;
            case HOLD_EFFECT_RABUTA_BERRY:
                if (IsBattlerAlive(gBattlerAttacker)
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                && TARGET_TURN_DAMAGED
                && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)
                && CanBeConfused(gBattlerAttacker)
                && gBattleMons[gBattlerTarget].hp < gBattleMons[battler].maxHP / 2)
                {
                    effect = ITEM_EFFECT_OTHER;
                    gBattleMons[gBattlerAttacker].status2 |= STATUS2_CONFUSION;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RabutaBerryActivatesRet;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_RABUTA_BERRY);
                }
                break;
            case HOLD_EFFECT_SPELON_BERRY:
                if (IsBattlerAlive(gBattlerAttacker)
                && TARGET_TURN_DAMAGED
                && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)
                && (gSideTimers[GetBattlerSide(gBattlerAttacker)].spikesAmount < 3))
                {
                    effect = ITEM_EFFECT_OTHER;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_SpelonBerryActivatesRet;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_SPELON_BERRY);
                }
                break;
            case HOLD_EFFECT_ROWAP_BERRY: // consume and damage attacker if used special move
                if (IsBattlerAlive(battler) 
                && TARGET_TURN_DAMAGED 
                && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove) 
                && IS_MOVE_SPECIAL(gCurrentMove) 
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD 
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_SUGAR_COAT)
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (GetBattlerAbility(battler) == ABILITY_RIPEN)
                        gBattleMoveDamage *= 2;
                    if (IsSpeciesOneOf(gBattleMons[gBattlerAttacker].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;

                    effect = ITEM_HP_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_JabocaRowapBerryActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_ROCKY_HELMET);
                }
                break;
            case HOLD_EFFECT_PINAP_BERRY:
                if (IsBattlerAlive(battler) 
                && TARGET_TURN_DAMAGED 
                && !DoesSubstituteBlockMove(gBattlerTarget, battler, gCurrentMove)
                && gBattleMons[gBattlerTarget].hp < gBattleMons[battler].maxHP / 4
                && GetBattlerAbility(gBattlerTarget) != ABILITY_MAGIC_GUARD 
                && GetBattlerAbility(gBattlerTarget) != ABILITY_SUGAR_COAT)
                {
                    gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (GetBattlerAbility(gBattlerTarget) == ABILITY_RIPEN)
                        gBattleMoveDamage *= 2;
                    if (IsSpeciesOneOf(gBattleMons[gBattlerTarget].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                        gBattleMoveDamage = 50;

                    effect = ITEM_HP_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_PinapBerryActivatesRet;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battler, HOLD_EFFECT_ROCKY_HELMET);
                }
                break;
            case HOLD_EFFECT_KEE_BERRY: // consume and boost defense if used physical move
                effect = DamagedStatBoostBerryEffect(battler, STAT_DEF, SPLIT_PHYSICAL);
                break;
            case HOLD_EFFECT_MARANGA_BERRY: // consume and boost sp. defense if used special move
                effect = DamagedStatBoostBerryEffect(battler, STAT_SPDEF, SPLIT_SPECIAL);
                break;
            }
        }
        break;
    case ITEMEFFECT_ORBS:
    {
        u16 battlerAbility = GetBattlerAbility(battler);
        switch (battlerHoldEffect)
        {
        case HOLD_EFFECT_TOXIC_ORB:
            if (CanBePoisoned(battler, battler))
            {
                effect = ITEM_STATUS_CHANGE;
                gBattleMons[battler].status1 = STATUS1_TOXIC_POISON;
                BattleScriptExecute(BattleScript_ToxicOrb);
                RecordItemEffectBattle(battler, battlerHoldEffect);
            }
            break;
        case HOLD_EFFECT_FLAME_ORB:
            if (CanBeBurned(battler))
            {
                effect = ITEM_STATUS_CHANGE;
                gBattleMons[battler].status1 = STATUS1_BURN;
                BattleScriptExecute(BattleScript_FlameOrb);
                RecordItemEffectBattle(battler, battlerHoldEffect);
            }
            break;
        case HOLD_EFFECT_FROST_ORB:
            if (CanGetFrostbite(battler))
            {
                effect = ITEM_STATUS_CHANGE;
                gBattleMons[battler].status1 = STATUS1_FROSTBITE;
                BattleScriptExecute(BattleScript_FrostOrb);
                RecordItemEffectBattle(battler, battlerHoldEffect);
            }
            break;
        case HOLD_EFFECT_POISON_ORB:
            if (CanBePoisoned(battler, battler))
            {
                effect = ITEM_STATUS_CHANGE;
                gBattleMons[battler].status1 = STATUS1_POISON;
                BattleScriptExecute(BattleScript_PoisonOrb);
                RecordItemEffectBattle(battler, battlerHoldEffect);
            }
            break;
        case HOLD_EFFECT_PANIC_ORB:
            if (CanGetPanicked(battler))
            {
                effect = ITEM_STATUS_CHANGE;
                gBattleMons[battler].status1 = STATUS1_PANIC;
                BattleScriptExecute(BattleScript_PanicOrb);
                RecordItemEffectBattle(battler, battlerHoldEffect);
            }
            break;
        case HOLD_EFFECT_STICKY_BARB: // Not an orb per se, but similar effect, and needs to NOT activate with pickpocket
            if (gSideTimers[GetBattlerSide(BATTLE_OPPOSITE(battler))].spikesAmount < 3 && battlerAbility != ABILITY_MAGIC_GUARD && battlerAbility != ABILITY_SUGAR_COAT)
            {
                gBattlerTarget = BATTLE_OPPOSITE(battler);
                gSideStatuses[GetBattlerSide(gBattlerTarget)] |= SIDE_STATUS_SPIKES;
                gSideTimers[GetBattlerSide(gBattlerTarget)].spikesAmount++;
                gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                BattleScriptExecute(BattleScript_StickyBarb);
                effect = ITEM_EFFECT_OTHER;
                RecordItemEffectBattle(battler, battlerHoldEffect);
                PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
            }
            else if (gSideTimers[GetBattlerSide(BATTLE_OPPOSITE(battler))].spikesAmount < 3)
            {
                gBattlerTarget = BATTLE_OPPOSITE(battler);
                gSideStatuses[GetBattlerSide(gBattlerTarget)] |= SIDE_STATUS_SPIKES;
                gSideTimers[GetBattlerSide(gBattlerTarget)].spikesAmount++;
                BattleScriptExecute(BattleScript_StickyBarbJustSpikes);
                effect = ITEM_EFFECT_OTHER;
                RecordItemEffectBattle(battler, battlerHoldEffect);
                PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
            }
            else if (battlerAbility != ABILITY_MAGIC_GUARD && battlerAbility != ABILITY_SUGAR_COAT)
            {
                gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                if (IsSpeciesOneOf(gBattleMons[battler].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && gBattleMoveDamage > 50)
                    gBattleMoveDamage = 50;
                BattleScriptExecute(BattleScript_ItemHurtEnd2);
                effect = ITEM_HP_CHANGE;
                RecordItemEffectBattle(battler, battlerHoldEffect);
                PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
            }    
            break;
        }

        if (effect == ITEM_STATUS_CHANGE)
        {
            BtlController_EmitSetMonData(battler, BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
            MarkBattlerForControllerExec(battler);
        }
    }
        break;
    case ITEMEFFECT_STATS_CHANGED:
        switch (battlerHoldEffect)
        {
        case HOLD_EFFECT_RESTORE_STATS:
            effect = RestoreWhiteHerbStats(battler);
            if (effect != 0)
            {
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_WhiteHerbRet;
            }
            break;
        case HOLD_EFFECT_EJECT_PACK:
            effect = TryEjectPack(battler, FALSE);
            break;
        }
        break;
    }

    // Berry was successfully used on a Pokemon.
    if (effect && (gLastUsedItem >= FIRST_BERRY_INDEX && gLastUsedItem <= LAST_BERRY_INDEX))
        gBattleStruct->ateBerry[battler & BIT_SIDE] |= gBitTable[gBattlerPartyIndexes[battler]];

    return effect;
}

void ClearFuryCutterDestinyBondGrudge(u32 battler)
{
    gDisableStructs[battler].furyCutterCounter = 0;
    gBattleMons[battler].status2 &= ~STATUS2_DESTINY_BOND;
    gStatuses3[battler] &= ~STATUS3_GRUDGE;
    gStatuses4[gBattlerAttacker] &= ~STATUS4_GLAIVE_RUSH_2;
}

void HandleAction_RunBattleScript(void) // identical to RunBattleScriptCommands
{
    if (gBattleControllerExecFlags == 0)
        gBattleScriptingCommandsTable[*gBattlescriptCurrInstr]();
}

u32 SetRandomTarget(u32 battler)
{
    u32 target;
    static const u8 targets[2][2] =
        {
            [B_SIDE_PLAYER] = {B_POSITION_OPPONENT_LEFT, B_POSITION_OPPONENT_RIGHT},
            [B_SIDE_OPPONENT] = {B_POSITION_PLAYER_LEFT, B_POSITION_PLAYER_RIGHT},
        };

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        target = GetBattlerAtPosition(targets[GetBattlerSide(battler)][Random() % 2]);
        if (!IsBattlerAlive(target))
            target ^= BIT_FLANK;
    }
    else
    {
        target = GetBattlerAtPosition(targets[GetBattlerSide(battler)][0]);
    }

    return target;
}

u32 GetMoveTarget(u16 move, u8 setTarget)
{
    u8 targetBattler = 0;
    u32 i, moveTarget, side;

    if (setTarget != NO_TARGET_OVERRIDE)
        moveTarget = setTarget - 1;
    else
        moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, move);

    // Special cases
    if (move == MOVE_CURSE && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GHOST))
        moveTarget = MOVE_TARGET_USER;

    switch (moveTarget)
    {
    case MOVE_TARGET_SELECTED:
        side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));
        if (IsAffectedBySpotlight(gBattlerAttacker, side, move))
        {
            targetBattler = gSideTimers[side].spotlightTarget;
        }
        else if (IsAffectedByFollowMe(gBattlerAttacker, side, move))
        {
            targetBattler = gSideTimers[side].followmeTarget;
        }
        else
        {
            targetBattler = SetRandomTarget(gBattlerAttacker);

            //this next if might be redundant, but should never negatively affect outcome
            if (gProtectStructs[gBattlerAttacker].overtakeRedirectActive == TRUE)
            {
                int battler;
                
                for (battler = 0; battler < MAX_BATTLERS_COUNT; battler++)
                {
                    //search linked battler to set target
                    if (gProtectStructs[gBattlerAttacker].overtakeRedirectedUser == battler)
                    {
                        //set target
                        targetBattler = battler;
                        if (!IsBattlerAlive(battler))
                            targetBattler ^= BIT_FLANK; //change target if opponent is dead
                        battler = MAX_BATTLERS_COUNT; //exit loop early
                    }
                }
            }

            if (gBattleMoves[move].type == TYPE_ELECTRIC && IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_LIGHTNING_ROD) && GetBattlerAbility(targetBattler) != ABILITY_LIGHTNING_ROD)
            {
                targetBattler ^= BIT_FLANK;
                RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                gSpecialStatuses[targetBattler].lightningRodRedirected = TRUE;
            }
            else if (gBattleMoves[move].type == TYPE_WATER && IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_STORM_DRAIN) && GetBattlerAbility(targetBattler) != ABILITY_STORM_DRAIN)
            {
                targetBattler ^= BIT_FLANK;
                RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                gSpecialStatuses[targetBattler].stormDrainRedirected = TRUE;
            }
            else if (gBattleMoves[move].type == TYPE_STEEL && IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_MAGNET_PULL) && GetBattlerAbility(targetBattler) != ABILITY_MAGNET_PULL)
            {
                targetBattler ^= BIT_FLANK;
                RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                gSpecialStatuses[targetBattler].magnetPullRedirected = TRUE;
            }
            else if (gBattleMoves[move].type == TYPE_FAIRY && IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_WITCHCRAFT) && GetBattlerAbility(targetBattler) != ABILITY_WITCHCRAFT)
            {
                targetBattler ^= BIT_FLANK;
                RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                gSpecialStatuses[targetBattler].witchcraftRedirected = TRUE;
            }
            else if (gBattleMoves[move].type == TYPE_GHOST && IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_SOUL_LOCKER) && GetBattlerAbility(targetBattler) != ABILITY_SOUL_LOCKER)
            {
                targetBattler ^= BIT_FLANK;
                RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                gSpecialStatuses[targetBattler].soulLockerRedirected = TRUE;
            }
        }
        break;
    case MOVE_TARGET_DEPENDS:
    case MOVE_TARGET_BOTH:
    case MOVE_TARGET_FOES_AND_ALLY:
    case MOVE_TARGET_OPPONENTS_FIELD:
        targetBattler = GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker)));
        if (!IsBattlerAlive(targetBattler))
            targetBattler ^= BIT_FLANK;
        break;
    case MOVE_TARGET_RANDOM:
        side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));
        if (IsAffectedBySpotlight(gBattlerAttacker, side, move))
        {
            targetBattler = gSideTimers[side].spotlightTarget;
        }
        else if (IsAffectedByFollowMe(gBattlerAttacker, side, move))
        {
            targetBattler = gSideTimers[side].followmeTarget;
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && moveTarget & MOVE_TARGET_RANDOM)
            targetBattler = SetRandomTarget(gBattlerAttacker);
        else
            targetBattler = GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker)));
        break;
    case MOVE_TARGET_USER_OR_SELECTED:
    case MOVE_TARGET_USER:
    default:
        targetBattler = gBattlerAttacker;
        break;
    case MOVE_TARGET_ALLY:
        if (IsBattlerAlive(BATTLE_PARTNER(gBattlerAttacker)))
            targetBattler = BATTLE_PARTNER(gBattlerAttacker);
        else
            targetBattler = gBattlerAttacker;
        break;
    }

    gBattleStruct->moveTarget[gBattlerAttacker] = targetBattler;

    return targetBattler;
}

static bool32 IsBattlerModernFatefulEncounter(u32 battler)
{
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
        return TRUE;
    if (GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES, NULL) != SPECIES_DEOXYS && GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES, NULL) != SPECIES_MEW)
        return TRUE;
    return GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_MODERN_FATEFUL_ENCOUNTER, NULL);
}

u8 IsMonDisobedient(void)
{
    s32 rnd;
    s32 calc;
    u8 obedienceLevel = 0;
    u8 levelReferenced;

    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
        return 0;
    if (BattlerHasAi(gBattlerAttacker))
        return 0;

    if (IsBattlerModernFatefulEncounter(gBattlerAttacker)) // only false if illegal Mew or Deoxys
    {
        if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && GetBattlerPosition(gBattlerAttacker) == B_POSITION_PLAYER_RIGHT)
            return 0;
        if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
            return 0;
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            return 0;
#if B_OBEDIENCE_MECHANICS < GEN_8
        if (!IsOtherTrainer(gBattleMons[gBattlerAttacker].otId, gBattleMons[gBattlerAttacker].otName))
            return 0;
#endif
        obedienceLevel = 100;

        if (FlagGet(FLAG_BADGE01_GET)) // Stone Badge
            obedienceLevel = 100;
        if (FlagGet(FLAG_BADGE02_GET)) // Knuckle Badge
            obedienceLevel = 100;
        if (FlagGet(FLAG_BADGE03_GET)) // Dynamo Badge
            obedienceLevel = 100;
        if (FlagGet(FLAG_BADGE04_GET)) // Heat Badge
            obedienceLevel = 100;
        if (FlagGet(FLAG_BADGE05_GET)) // Balance Badge
            obedienceLevel = 100;
        if (FlagGet(FLAG_BADGE06_GET)) // Feather Badge
            obedienceLevel = 100;
        if (FlagGet(FLAG_BADGE07_GET)) // Mind Badge
            obedienceLevel = 100;
    }

#if B_OBEDIENCE_MECHANICS >= GEN_8
    if (!IsOtherTrainer(gBattleMons[gBattlerAttacker].otId, gBattleMons[gBattlerAttacker].otName))
        levelReferenced = gBattleMons[gBattlerAttacker].metLevel;
    else
#endif
        levelReferenced = gBattleMons[gBattlerAttacker].level;

    if (levelReferenced <= obedienceLevel)
        return 0;
    rnd = (Random() & 255);
    calc = (levelReferenced + obedienceLevel) * rnd >> 8;
    if (calc < obedienceLevel)
        return 0;

    // is not obedient
    if (gCurrentMove == MOVE_RAGE)
        gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_RAGE;
    if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP_ANY && (gCurrentMove == MOVE_SNORE || gCurrentMove == MOVE_SLEEP_TALK))
    {
        gBattlescriptCurrInstr = BattleScript_IgnoresWhileAsleep;
        return 1;
    }

    rnd = (Random() & 255);
    calc = (levelReferenced + obedienceLevel) * rnd >> 8;
    if (calc < obedienceLevel)
    {
        calc = CheckMoveLimitations(gBattlerAttacker, gBitTable[gCurrMovePos], MOVE_LIMITATIONS_ALL);
        if (calc == ALL_MOVES_MASK) // all moves cannot be used
        {
            // Randomly select, then print a disobedient string
            // B_MSG_LOAFING, B_MSG_WONT_OBEY, B_MSG_TURNED_AWAY, or B_MSG_PRETEND_NOT_NOTICE
            gBattleCommunication[MULTISTRING_CHOOSER] = MOD(Random(), NUM_LOAF_STRINGS);
            gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
            return 1;
        }
        else // use a random move
        {
            do
            {
                gCurrMovePos = gChosenMovePos = MOD(Random(), MAX_MON_MOVES);
            } while (gBitTable[gCurrMovePos] & calc);

            gCalledMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
            gBattlescriptCurrInstr = BattleScript_IgnoresAndUsesRandomMove;
            gBattlerTarget = GetMoveTarget(gCalledMove, NO_TARGET_OVERRIDE);
            gHitMarker |= HITMARKER_DISOBEDIENT_MOVE;
            return 2;
        }
    }
    else
    {
        obedienceLevel = levelReferenced - obedienceLevel;

        calc = (Random() & 255);
        if (calc < obedienceLevel && CanSleep(gBattlerAttacker))
        {
            // try putting asleep
            int i;
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gBattleMons[i].status2 & STATUS2_UPROAR)
                    break;
            }
            if (i == gBattlersCount)
            {
                gBattlescriptCurrInstr = BattleScript_IgnoresAndFallsAsleep;
                return 1;
            }
        }
        calc -= obedienceLevel;
        if (calc < obedienceLevel)
        {
            gBattleMoveDamage = CalculateMoveDamage(MOVE_NONE, gBattlerAttacker, gBattlerAttacker, TYPE_MYSTERY, 40, FALSE, FALSE, TRUE);
            gBattlerTarget = gBattlerAttacker;
            gBattlescriptCurrInstr = BattleScript_IgnoresAndHitsItself;
            gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
            return 2;
        }
        else
        {
            // Randomly select, then print a disobedient string
            // B_MSG_LOAFING, B_MSG_WONT_OBEY, B_MSG_TURNED_AWAY, or B_MSG_PRETEND_NOT_NOTICE
            gBattleCommunication[MULTISTRING_CHOOSER] = MOD(Random(), NUM_LOAF_STRINGS);
            gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
            return 1;
        }
    }
}

u32 GetBattlerHoldEffect(u32 battler, bool32 checkNegating)
{
    return GetBattlerHoldEffectInternal(battler, checkNegating, TRUE);
}

u32 GetBattlerHoldEffectIgnoreAbility(u32 battler, bool32 checkNegating)
{
    return GetBattlerHoldEffectInternal(battler, checkNegating, FALSE);
}

u32 GetBattlerHoldEffectInternal(u32 battler, bool32 checkNegating, bool32 checkAbility)
{
    if (checkNegating)
    {
        if (gStatuses3[battler] & STATUS3_EMBARGO)
            return HOLD_EFFECT_NONE;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return HOLD_EFFECT_NONE;
        if (checkAbility && GetBattlerAbility(battler) == ABILITY_KLUTZ)
            return HOLD_EFFECT_NONE;
    }

    gPotentialItemEffectBattler = battler;

    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY_E_READER)
        return gEnigmaBerries[battler].holdEffect;
    else
        return ItemId_GetHoldEffect(gBattleMons[battler].item);
}

static u32 GetBattlerItemHoldEffectParam(u32 battler, u32 item)
{
    if (item == ITEM_ENIGMA_BERRY_E_READER)
        return gEnigmaBerries[battler].holdEffectParam;
    else
        return ItemId_GetHoldEffectParam(item);
}

u32 GetBattlerHoldEffectParam(u32 battler)
{
    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY_E_READER)
        return gEnigmaBerries[battler].holdEffectParam;
    else
        return ItemId_GetHoldEffectParam(gBattleMons[battler].item);
}

bool32 IsMoveMakingContact(u32 move, u32 battlerAtk)
{
    u32 atkHoldEffect = GetBattlerHoldEffect(battlerAtk, TRUE);
    u16 atkBaseSpeciesId;

    atkBaseSpeciesId = GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species);

    if (!gBattleMoves[move].makesContact)
    {
        if (gBattleMoves[move].effect == EFFECT_SHELL_SIDE_ARM && gBattleStruct->swapDamageCategory)
            return TRUE;
        else
            return FALSE;
    }
    else if ((atkHoldEffect == HOLD_EFFECT_PUNCHING_GLOVE && gBattleMoves[move].punchingMove) 
    || ((atkBaseSpeciesId == SPECIES_PAWNIARD || atkBaseSpeciesId == SPECIES_BISHARP || atkBaseSpeciesId == SPECIES_KINGAMBIT) && (gBattleMoves[move].slicingMove) && atkHoldEffect == HOLD_EFFECT_LEADERS_CREST)
    || atkHoldEffect == HOLD_EFFECT_PROTECTIVE_PADS
    || GetBattlerAbility(battlerAtk) == ABILITY_LONG_REACH)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

bool32 ShouldReform(u32 battlerDef, u32 move)
{
    if (gBattleMoves[move].type == TYPE_NORMAL && !gDisableStructs[battlerDef].reformNormal)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_FIGHTING && !gDisableStructs[battlerDef].reformFighting)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_FLYING && !gDisableStructs[battlerDef].reformFlying)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_POISON && !gDisableStructs[battlerDef].reformPoison)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_GROUND && !gDisableStructs[battlerDef].reformGround)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_ROCK && !gDisableStructs[battlerDef].reformRock)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_BUG && !gDisableStructs[battlerDef].reformBug)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_GHOST && !gDisableStructs[battlerDef].reformGhost)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_STEEL && !gDisableStructs[battlerDef].reformSteel)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_FIRE && !gDisableStructs[battlerDef].reformFire)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_WATER && !gDisableStructs[battlerDef].reformWater)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_GRASS && !gDisableStructs[battlerDef].reformGrass)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_ELECTRIC && !gDisableStructs[battlerDef].reformElectric)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_PSYCHIC && !gDisableStructs[battlerDef].reformPsychic)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_ICE && !gDisableStructs[battlerDef].reformIce)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_DRAGON && !gDisableStructs[battlerDef].reformDragon)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_DARK && !gDisableStructs[battlerDef].reformDark)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_FAIRY && !gDisableStructs[battlerDef].reformFairy)
        return TRUE;
    if (gBattleMoves[move].type == TYPE_RELIC && !gDisableStructs[battlerDef].reformRelic)
        return TRUE;
    return FALSE;
}

bool32 IsBattlerProtected(u32 battler, u32 move)
{
    // Decorate bypasses protect and detect, but not crafty shield
    if (move == MOVE_DECORATE)
    {
        if (gStatuses4[gBattlerTarget] & STATUS4_CRAFTY_SHIELD)
            return TRUE;
        else if (gProtectStructs[gBattlerTarget].protected)
            return FALSE;
    }

    if (move == MOVE_TEATIME)
    {
        return FALSE;
    }

    // Z-Moves and Max Moves bypass protection
    if (gBattleStruct->zmove.active)
    {
        return FALSE;
    }

    // Protective Pads doesn't stop Unseen Fist from bypassing Protect effects, so IsMoveMakingContact() isn't used here.
    // This means extra logic is needed to handle Shell Side Arm.
    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_UNSEEN_FIST && (gBattleMoves[move].makesContact || (gBattleMoves[move].effect == EFFECT_SHELL_SIDE_ARM && gBattleStruct->swapDamageCategory)))
        return FALSE;
    else if (gBattleMoves[move].ignoresProtect)
        return FALSE;
    else if (IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_BUG) && gProtectStructs[gBattlerTarget].protected)
        return FALSE;
    else if (gBattleMoves[move].effect == EFFECT_FEINT)
        return FALSE;
    else if (gSpecialStatuses[gBattlerTarget].gemBoost == TRUE)
        return FALSE;
    else if (gProtectStructs[gBattlerTarget].protected)
        return TRUE;
    else if (gSideStatuses[GetBattlerSide(gBattlerTarget)] & SIDE_STATUS_WIDE_GUARD && GetBattlerMoveTargetType(gBattlerAttacker, move) & (MOVE_TARGET_BOTH | MOVE_TARGET_FOES_AND_ALLY))
        return TRUE;
    else if (gProtectStructs[gBattlerTarget].banefulBunkered)
        return TRUE;
    else if (gProtectStructs[gBattlerTarget].burningBulwarked)
        return TRUE;
    else if (gProtectStructs[gBattlerTarget].drakenGuarded)
        return TRUE;
    else if ((gProtectStructs[gBattlerTarget].obstructed || gProtectStructs[gBattlerTarget].silkTrapped || gProtectStructs[gBattlerTarget].detectShielded || gProtectStructs[gBattlerTarget].shelltered) && (!(IS_MOVE_STATUS(move))))
        return TRUE;
    else if (gProtectStructs[gBattlerTarget].spikyShielded)
        return TRUE;
    else if (gProtectStructs[gBattlerTarget].kingsShielded && gBattleMoves[move].power != 0)
        return TRUE;
    else if (gSideStatuses[GetBattlerSide(gBattlerTarget)] & SIDE_STATUS_QUICK_GUARD && GetChosenMovePriority(gBattlerAttacker) > 0)
        return TRUE;
    else if (gStatuses4[gBattlerTarget] & STATUS4_CRAFTY_SHIELD && IS_MOVE_STATUS(move))
        return TRUE;
    else if (gSideStatuses[GetBattlerSide(gBattlerTarget)] & SIDE_STATUS_MAT_BLOCK && (IS_MOVE_PHYSICAL(move) || IS_MOVE_SPECIAL(move)))
        return TRUE;
    else
        return FALSE;
}

// Only called directly when calculating damage type effectiveness
static bool32 IsBattlerGrounded2(u32 battler, bool32 considerInverse)
{
    u32 holdEffect = GetBattlerHoldEffect(battler, TRUE);

    if (holdEffect == HOLD_EFFECT_IRON_BALL)
        return TRUE;
    if (gFieldStatuses & STATUS_FIELD_GRAVITY)
        return TRUE;
#if B_ROOTED_GROUNDING >= GEN_4
    if (gStatuses3[battler] & STATUS3_ROOTED)
        return TRUE;
#endif
    if (gStatuses3[battler] & STATUS3_SMACKED_DOWN)
        return TRUE;
    if (gStatuses3[battler] & STATUS3_TELEKINESIS)
        return FALSE;
    if (gStatuses3[battler] & STATUS3_MAGNET_RISE)
        return FALSE;
    if (holdEffect == HOLD_EFFECT_AIR_BALLOON)
        return FALSE;
    if (GetBattlerAbility(battler) == ABILITY_LEVITATE)
        return FALSE;
    if (GetBattlerAbility(battler) == ABILITY_GRAVITY_WELL && gFieldStatuses & STATUS_FIELD_GRAVITY)
        return FALSE;
    if (IS_BATTLER_OF_TYPE(battler, TYPE_FLYING) && (!considerInverse || !FlagGet(B_FLAG_INVERSE_BATTLE) || (!(gFieldStatuses & STATUS_FIELD_INVERSE_ROOM))))
        return FALSE;
    return TRUE;
}

bool32 IsBattlerGrounded(u32 battler)
{
    return IsBattlerGrounded2(battler, FALSE);
}

bool32 IsBattlerAlive(u32 battler)
{
    if (gBattleMons[battler].hp == 0)
        return FALSE;
    else if (battler >= gBattlersCount)
        return FALSE;
    else if (gAbsentBattlerFlags & gBitTable[battler])
        return FALSE;
    else
        return TRUE;
}

u32 GetMoveSlot(u16 *moves, u32 move)
{
    u32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] == move)
            break;
    }
    return i;
}

u32 GetBattlerWeight(u32 battler)
{
    u32 i;
    u32 weight = GetPokedexHeightWeight(SpeciesToNationalPokedexNum(gBattleMons[battler].species), 1);
    u32 ability = GetBattlerAbility(battler);
    u32 holdEffect = GetBattlerHoldEffect(battler, TRUE);

    if (gBattleMons[battler].species == SPECIES_MINIOR_CORE_RED
        || gBattleMons[battler].species == SPECIES_MINIOR_CORE_ORANGE
        || gBattleMons[battler].species == SPECIES_MINIOR_CORE_YELLOW
        || gBattleMons[battler].species == SPECIES_MINIOR_CORE_GREEN
        || gBattleMons[battler].species == SPECIES_MINIOR_CORE_BLUE
        || gBattleMons[battler].species == SPECIES_MINIOR_CORE_INDIGO
        || gBattleMons[battler].species == SPECIES_MINIOR_CORE_VIOLET)
        weight = 3;

    if (gBattleMons[battler].species == SPECIES_DUDUNSPARS_THREE_SEGMENT)
        weight = 474;

    if (gBattleMons[battler].species == SPECIES_DUDUNSPARS_EIGHT_SEGMENT)
        weight = 884;

    if (gBattleMons[battler].species == SPECIES_LOTTABATS_HUDDLED)
        weight = 2800;

    if (gBattleMons[battler].species == SPECIES_BISHOUCHA_WARMONGER)
        weight = 862;

    if (gBattleMons[battler].species == SPECIES_PAPYPUS_FEMALE)
        weight = 1344;

    if (ability == ABILITY_HEAVY_METAL)
        weight *= 2;
    else if (ability == ABILITY_LIGHT_METAL)
        weight /= 2;

    if (holdEffect == HOLD_EFFECT_FLOAT_STONE)
        weight /= 2;

    for (i = 0; i < gDisableStructs[battler].autotomizeCount; i++)
    {
        if (weight > 1000)
        {
            weight -= 1000;
        }
        else if (weight <= 1000)
        {
            weight = 1;
            break;
        }
    }

    if (weight == 0)
        weight = 1;

    return weight;
}

u32 GetBattlerHeight(u32 battler)
{
    u32 i;
    u32 height = GetPokedexHeightWeight(SpeciesToNationalPokedexNum(gBattleMons[battler].species), 0);
    u32 ability = GetBattlerAbility(battler);
    u32 holdEffect = GetBattlerHoldEffect(battler, TRUE);

    if (gBattleMons[battler].species == SPECIES_DUDUNSPARS_THREE_SEGMENT)
        height = 45;

    if (gBattleMons[battler].species == SPECIES_DUDUNSPARS_EIGHT_SEGMENT)
        height = 90;

    if (gBattleMons[battler].species == SPECIES_LOTTABATS_HUDDLED)
        height = 25;

    if (gBattleMons[battler].species == SPECIES_PAPYPUS_FEMALE)
        height = 27;

    if (height == 0)
        height = 1;

    return height;
}

u32 CountBattlerStatIncreases(u32 battler, bool32 countEvasionAcc)
{
    u32 i;
    u32 count = 0;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if ((i == STAT_ACC || i == STAT_EVASION) && !countEvasionAcc)
            continue;
        if (gBattleMons[battler].statStages[i] > DEFAULT_STAT_STAGE) // Stat is increased.
            count += gBattleMons[battler].statStages[i] - DEFAULT_STAT_STAGE;
    }

    return count;
}

u32 CountBattlerSpeedIncreases(u32 battler)
{
    u32 i;
    u32 count = 0;

    if (gBattleMons[battler].statStages[STAT_SPEED] > DEFAULT_STAT_STAGE) // Stat is increased.
        count += gBattleMons[battler].statStages[STAT_SPEED] - DEFAULT_STAT_STAGE;

    return count;
}

u32 CountBattlerAccuracyIncreases(u32 battler)
{
    u32 i;
    u32 count = 0;

    if (gBattleMons[battler].statStages[STAT_ACC] > DEFAULT_STAT_STAGE) // Stat is increased.
        count += gBattleMons[battler].statStages[STAT_ACC] - DEFAULT_STAT_STAGE;

    return count;
}

u32 CountBattlerSpecialAttackIncreases(u32 battler)
{
    u32 i;
    u32 count = 0;

    if (gBattleMons[battler].statStages[STAT_SPATK] > DEFAULT_STAT_STAGE) // Stat is increased.
        count += gBattleMons[battler].statStages[STAT_SPATK] - DEFAULT_STAT_STAGE;

    return count;
}

u32 CountBattlerSpecialDefenseIncreases(u32 battler)
{
    u32 i;
    u32 count = 0;

    if (gBattleMons[battler].statStages[STAT_SPDEF] > DEFAULT_STAT_STAGE) // Stat is increased.
        count += gBattleMons[battler].statStages[STAT_SPDEF] - DEFAULT_STAT_STAGE;

    return count;
}

u32 CountBattlerDefenseIncreases(u32 battler)
{
    u32 i;
    u32 count = 0;

    if (gBattleMons[battler].statStages[STAT_DEF] > DEFAULT_STAT_STAGE) // Stat is increased.
        count += gBattleMons[battler].statStages[STAT_DEF] - DEFAULT_STAT_STAGE;

    return count;
}

static inline uq4_12_t GetStrongholdDefenseModifier(u32 battler)
{
    return UQ_4_12(1.0) - (PercentToUQ4_12(CountBattlerDefenseIncreases(battler) * 10));
}

static inline uq4_12_t GetStrongholdOffenseModifier(u32 battler)
{
    return UQ_4_12(1.0) + (PercentToUQ4_12(CountBattlerDefenseIncreases(battler) * 10));
}

u32 CountBattlerStatDecreases(u32 battler, bool32 countEvasionAcc)
{
    u32 i;
    u32 count = 0;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if ((i == STAT_ACC || i == STAT_EVASION) && !countEvasionAcc)
            continue;
        if (gBattleMons[battler].statStages[i] < DEFAULT_STAT_STAGE) // Stat is decreased.
            count += DEFAULT_STAT_STAGE - gBattleMons[battler].statStages[i];
    }

    return count;
}

u32 CountBattlerSpeedDecreases(u32 battler)
{
    u32 i;
    u32 count = 0;

    if (gBattleMons[battler].statStages[STAT_SPEED] < DEFAULT_STAT_STAGE) // Stat is increased.
        count += DEFAULT_STAT_STAGE - gBattleMons[battler].statStages[STAT_SPEED];

    return count;
}

u32 GetMoveTargetCount(u32 move, u32 battlerAtk, u32 battlerDef)
{
    switch (GetBattlerMoveTargetType(battlerAtk, move))
    {
    case MOVE_TARGET_BOTH:
        return !(gAbsentBattlerFlags & (1u << battlerDef))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerDef)));
    case MOVE_TARGET_FOES_AND_ALLY:
        return !(gAbsentBattlerFlags & (1u << battlerDef))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerDef)))
             + !(gAbsentBattlerFlags & (1u << BATTLE_PARTNER(battlerAtk)));
    case MOVE_TARGET_OPPONENTS_FIELD:
        return 1;
    case MOVE_TARGET_DEPENDS:
    case MOVE_TARGET_SELECTED:
    case MOVE_TARGET_RANDOM:
    case MOVE_TARGET_USER_OR_SELECTED:
        return IsBattlerAlive(battlerDef);
    case MOVE_TARGET_USER:
        return IsBattlerAlive(battlerAtk);
    default:
        return 0;
    }
}

bool32 IsMoveMultipleTargetAndDamages(u32 move, u32 battlerAtk)
{
    if (gBattleMoves[move].power > 0)
    {
        switch (GetBattlerMoveTargetType(battlerAtk, move))
        {
        case MOVE_TARGET_BOTH:
        case MOVE_TARGET_FOES_AND_ALLY:
            return TRUE;
        default:
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

static const u8 sFlailHpScaleToPowerTable[] =
    {
        1, 200,
        4, 150,
        9, 100,
        16, 80,
        32, 40,
        48, 20};

static const u8 sMiseryWailHpScaleToPowerTable[] =
    {
        1, 120,
        4, 100,
        9,  80,
        16, 60,
        32, 40,
        48, 20};

static const u8 sLoneSharkHpScaleToPowerTable[] =
    {
        5, 170,
        10, 165,
        15, 160,
        20, 155,
        25, 150,
        30, 145,
        35, 140,
        40, 135,
        45, 130,
        50, 125,
        55, 120,
        60, 115,
        65, 110,
        70, 105,
        75, 100,
        80, 95,
        85, 90,
        90, 85,
        95, 80,
        100, 75};

// format: min. weight (hectograms), base power
static const u16 sWeightToDamageTable[] =
    {
        100, 20,
        250, 40,
        500, 60,
        1000, 80,
        2000, 100,
        0xFFFF, 0xFFFF};

static const u16 sWeightToDamageTableBlooming[] =
    {
        100, 40,
        250, 60,
        500, 80,
        1000, 100,
        2000, 120,
        0xFFFF, 0xFFFF};

static const u8 sSpeedDiffPowerTable[] = {40, 60, 80, 120, 150};
static const u8 sHeatCrashPowerTable[] = {40, 40, 60, 80, 100, 120};
static const u8 sTrumpCardPowerTable[] = {200, 160, 120, 80, 40};
static const u8 sPilgrimagePowerTable[] = {170, 150, 130, 110, 90};

const struct TypePower gNaturalGiftTable[] =
    {
        [ITEM_TO_BERRY(ITEM_CHERI_BERRY)] = {TYPE_FIRE, 80},
        [ITEM_TO_BERRY(ITEM_CHESTO_BERRY)] = {TYPE_WATER, 80},
        [ITEM_TO_BERRY(ITEM_PECHA_BERRY)] = {TYPE_ELECTRIC, 80},
        [ITEM_TO_BERRY(ITEM_RAWST_BERRY)] = {TYPE_GRASS, 80},
        [ITEM_TO_BERRY(ITEM_ASPEAR_BERRY)] = {TYPE_ICE, 80},
        [ITEM_TO_BERRY(ITEM_LEPPA_BERRY)] = {TYPE_FIGHTING, 80},
        [ITEM_TO_BERRY(ITEM_ORAN_BERRY)] = {TYPE_POISON, 80},
        [ITEM_TO_BERRY(ITEM_PERSIM_BERRY)] = {TYPE_GROUND, 80},
        [ITEM_TO_BERRY(ITEM_LUM_BERRY)] = {TYPE_FLYING, 80},
        [ITEM_TO_BERRY(ITEM_SITRUS_BERRY)] = {TYPE_PSYCHIC, 80},
        [ITEM_TO_BERRY(ITEM_FIGY_BERRY)] = {TYPE_BUG, 80},
        [ITEM_TO_BERRY(ITEM_WIKI_BERRY)] = {TYPE_ROCK, 80},
        [ITEM_TO_BERRY(ITEM_MAGO_BERRY)] = {TYPE_GHOST, 80},
        [ITEM_TO_BERRY(ITEM_AGUAV_BERRY)] = {TYPE_DRAGON, 80},
        [ITEM_TO_BERRY(ITEM_IAPAPA_BERRY)] = {TYPE_DARK, 80},
        [ITEM_TO_BERRY(ITEM_RAZZ_BERRY)] = {TYPE_STEEL, 80},
        [ITEM_TO_BERRY(ITEM_OCCA_BERRY)] = {TYPE_FIRE, 80},
        [ITEM_TO_BERRY(ITEM_PASSHO_BERRY)] = {TYPE_WATER, 80},
        [ITEM_TO_BERRY(ITEM_WACAN_BERRY)] = {TYPE_ELECTRIC, 80},
        [ITEM_TO_BERRY(ITEM_RINDO_BERRY)] = {TYPE_GRASS, 80},
        [ITEM_TO_BERRY(ITEM_YACHE_BERRY)] = {TYPE_ICE, 80},
        [ITEM_TO_BERRY(ITEM_CHOPLE_BERRY)] = {TYPE_FIGHTING, 80},
        [ITEM_TO_BERRY(ITEM_KEBIA_BERRY)] = {TYPE_POISON, 80},
        [ITEM_TO_BERRY(ITEM_SHUCA_BERRY)] = {TYPE_GROUND, 80},
        [ITEM_TO_BERRY(ITEM_COBA_BERRY)] = {TYPE_FLYING, 80},
        [ITEM_TO_BERRY(ITEM_PAYAPA_BERRY)] = {TYPE_PSYCHIC, 80},
        [ITEM_TO_BERRY(ITEM_TANGA_BERRY)] = {TYPE_BUG, 80},
        [ITEM_TO_BERRY(ITEM_CHARTI_BERRY)] = {TYPE_ROCK, 80},
        [ITEM_TO_BERRY(ITEM_KASIB_BERRY)] = {TYPE_GHOST, 80},
        [ITEM_TO_BERRY(ITEM_HABAN_BERRY)] = {TYPE_DRAGON, 80},
        [ITEM_TO_BERRY(ITEM_COLBUR_BERRY)] = {TYPE_DARK, 80},
        [ITEM_TO_BERRY(ITEM_BABIRI_BERRY)] = {TYPE_STEEL, 80},
        [ITEM_TO_BERRY(ITEM_CHILAN_BERRY)] = {TYPE_NORMAL, 80},
        [ITEM_TO_BERRY(ITEM_ROSELI_BERRY)] = {TYPE_FAIRY, 80},
        [ITEM_TO_BERRY(ITEM_BLUK_BERRY)] = {TYPE_FIRE, 90},
        [ITEM_TO_BERRY(ITEM_NANAB_BERRY)] = {TYPE_WATER, 90},
        [ITEM_TO_BERRY(ITEM_WEPEAR_BERRY)] = {TYPE_ELECTRIC, 90},
        [ITEM_TO_BERRY(ITEM_PINAP_BERRY)] = {TYPE_GRASS, 90},
        [ITEM_TO_BERRY(ITEM_POMEG_BERRY)] = {TYPE_ICE, 90},
        [ITEM_TO_BERRY(ITEM_KELPSY_BERRY)] = {TYPE_FIGHTING, 90},
        [ITEM_TO_BERRY(ITEM_QUALOT_BERRY)] = {TYPE_POISON, 90},
        [ITEM_TO_BERRY(ITEM_HONDEW_BERRY)] = {TYPE_GROUND, 90},
        [ITEM_TO_BERRY(ITEM_GREPA_BERRY)] = {TYPE_FLYING, 90},
        [ITEM_TO_BERRY(ITEM_TAMATO_BERRY)] = {TYPE_PSYCHIC, 90},
        [ITEM_TO_BERRY(ITEM_CORNN_BERRY)] = {TYPE_BUG, 90},
        [ITEM_TO_BERRY(ITEM_MAGOST_BERRY)] = {TYPE_ROCK, 90},
        [ITEM_TO_BERRY(ITEM_RABUTA_BERRY)] = {TYPE_GHOST, 90},
        [ITEM_TO_BERRY(ITEM_NOMEL_BERRY)] = {TYPE_DRAGON, 90},
        [ITEM_TO_BERRY(ITEM_SPELON_BERRY)] = {TYPE_DARK, 90},
        [ITEM_TO_BERRY(ITEM_PAMTRE_BERRY)] = {TYPE_STEEL, 90},
        [ITEM_TO_BERRY(ITEM_WATMEL_BERRY)] = {TYPE_FIRE, 100},
        [ITEM_TO_BERRY(ITEM_DURIN_BERRY)] = {TYPE_WATER, 100},
        [ITEM_TO_BERRY(ITEM_BELUE_BERRY)] = {TYPE_ELECTRIC, 100},
        [ITEM_TO_BERRY(ITEM_LIECHI_BERRY)] = {TYPE_GRASS, 100},
        [ITEM_TO_BERRY(ITEM_GANLON_BERRY)] = {TYPE_ICE, 100},
        [ITEM_TO_BERRY(ITEM_SALAC_BERRY)] = {TYPE_FIGHTING, 100},
        [ITEM_TO_BERRY(ITEM_PETAYA_BERRY)] = {TYPE_POISON, 100},
        [ITEM_TO_BERRY(ITEM_APICOT_BERRY)] = {TYPE_GROUND, 100},
        [ITEM_TO_BERRY(ITEM_LANSAT_BERRY)] = {TYPE_FLYING, 100},
        [ITEM_TO_BERRY(ITEM_STARF_BERRY)] = {TYPE_PSYCHIC, 100},
        [ITEM_TO_BERRY(ITEM_ENIGMA_BERRY)] = {TYPE_BUG, 100},
        [ITEM_TO_BERRY(ITEM_MICLE_BERRY)] = {TYPE_ROCK, 100},
        [ITEM_TO_BERRY(ITEM_CUSTAP_BERRY)] = {TYPE_GHOST, 100},
        [ITEM_TO_BERRY(ITEM_JABOCA_BERRY)] = {TYPE_DRAGON, 100},
        [ITEM_TO_BERRY(ITEM_ROWAP_BERRY)] = {TYPE_DARK, 100},
        [ITEM_TO_BERRY(ITEM_KEE_BERRY)] = {TYPE_FAIRY, 100},
        [ITEM_TO_BERRY(ITEM_MARANGA_BERRY)] = {TYPE_DARK, 100},
};

u32 CalcRolloutBasePower(u32 battlerAtk, u32 basePower, u32 rolloutTimer)
{
    u32 i;
    for (i = 1; i < (5 - rolloutTimer); i++)
        basePower *= 2;
    if (gBattleMons[battlerAtk].status2 & STATUS2_DEFENSE_CURL)
        basePower *= 2;
    return basePower;
}

u32 CalcFuryCutterBasePower(u32 basePower, u32 furyCutterCounter)
{
    u32 i;
    for (i = 1; i < furyCutterCounter; i++)
        basePower *= 2;
    return basePower;
}

u32 CalcRageFistPower(u32 basePower, u32 ragefistCounter)
{
    u32 i;
    for (i = 1; i < ragefistCounter; i++)
        basePower += 50;
    return basePower;
}

u32 CalcBariBariBeamPower(u32 basePower, u32 baribaribeamCounter)
{
    u32 i;
    for (i = 1; i < baribaribeamCounter; i++)
        basePower += 30;
    return basePower;
}

static inline u32 CalcMoveBasePower(u32 move, u32 battlerAtk, u32 battlerDef, u32 abilityDef, u32 weather)
{
    u32 i;
    u32 basePower = gBattleMoves[move].power;
    u32 weight, hpFraction, speed;

    if ((gFieldStatuses & STATUS_FIELD_GRAVITY) && (move == MOVE_PSYCHIC))
        basePower = 100;

    if ((move == MOVE_CANNONADE) && (gBattleMons[gBattlerAttacker].hp <= (gBattleMons[gBattlerAttacker].maxHP / 4)))
        basePower = 150;

    if (DoBattlersShareType(gBattlerAttacker, gBattlerTarget) && (move == MOVE_SYNCHRONOISE))
        basePower *= 2;

    if (move == MOVE_COLD_SNAP && weather & B_WEATHER_HAIL)
        basePower *= 2;

    if (gBattleStruct->zmove.active)
        return GetZMovePower(gBattleStruct->zmove.baseMoves[battlerAtk]);

    switch (gBattleMoves[move].effect)
    {
    case EFFECT_PLEDGE:
        // todo
        break;
    case EFFECT_FLING:
        basePower = GetFlingPowerFromItemId(gBattleMons[battlerAtk].item);
        break;
    case EFFECT_ERUPTION:
        basePower = gBattleMons[battlerAtk].hp * basePower / gBattleMons[battlerAtk].maxHP;
        break;
    case EFFECT_FLAIL:
        hpFraction = GetScaledHPFraction(gBattleMons[battlerAtk].hp, gBattleMons[battlerAtk].maxHP, 48);
        for (i = 0; i < sizeof(sFlailHpScaleToPowerTable); i += 2)
        {
            if (hpFraction <= sFlailHpScaleToPowerTable[i])
                break;
        }
        basePower = sFlailHpScaleToPowerTable[i + 1];
        break;
    case EFFECT_MISERY_WAIL:
        hpFraction = GetScaledHPFraction(gBattleMons[battlerAtk].hp, gBattleMons[battlerAtk].maxHP, 48);
        for (i = 0; i < sizeof(sMiseryWailHpScaleToPowerTable); i += 2)
        {
            if (hpFraction <= sMiseryWailHpScaleToPowerTable[i])
                break;
        }
        basePower = sMiseryWailHpScaleToPowerTable[i + 1];
        break;
    case EFFECT_LONE_SHARK:
        hpFraction = GetScaledHPFraction(gBattleMons[battlerAtk].hp, gBattleMons[battlerAtk].maxHP, 100);
        for (i = 0; i < sizeof(sLoneSharkHpScaleToPowerTable); i += 2)
        {
            if (hpFraction <= sLoneSharkHpScaleToPowerTable[i])
                break;
        }
        basePower = sLoneSharkHpScaleToPowerTable[i + 1];
        break;
    case EFFECT_BLACK_BUFFET:
        if (gBattleMons[battlerDef].hp <= (gBattleMons[battlerDef].maxHP / 5))
            basePower = 45;
        else if (gBattleMons[battlerDef].hp <= (gBattleMons[battlerDef].maxHP * 2 / 5))
            basePower = 40;
        else if (gBattleMons[battlerDef].hp <= (gBattleMons[battlerDef].maxHP * 3 / 5))
            basePower = 35;
        else if (gBattleMons[battlerDef].hp <= (gBattleMons[battlerDef].maxHP * 4 / 5))
            basePower = 30;
        else
            basePower = 25;
        break;
    case EFFECT_RETURN:
        if (GetBattlerSide(battlerAtk) == B_SIDE_OPPONENT || GetBattlerHoldEffect(battlerAtk, FALSE) == HOLD_EFFECT_FAVOR_SCARF)
        {
            gBattleMons[battlerAtk].friendship = 255;
        }
        basePower = 10 * (gBattleMons[battlerAtk].friendship) / 25;
        break;
    case EFFECT_FALSE_SWIPE:
        basePower = (gBattleMons[battlerAtk].level) * 1.5;
        basePower = (basePower > 75) ? 75 : basePower;
        break;
    case EFFECT_STRENGTH:
        if (GetBattlerSide(battlerAtk) == B_SIDE_OPPONENT || GetBattlerHoldEffect(battlerAtk, FALSE) == HOLD_EFFECT_FAVOR_SCARF)
        {
            gBattleMons[battlerAtk].friendship = 255;
        }
        basePower = 16 * (gBattleMons[battlerAtk].friendship) / 51;
        break;
    case EFFECT_CUT:
    case EFFECT_ROCK_SMASH:
        if (GetBattlerSide(battlerAtk) == B_SIDE_OPPONENT || GetBattlerHoldEffect(battlerAtk, FALSE) == HOLD_EFFECT_FAVOR_SCARF)
        {
            gBattleMons[battlerAtk].friendship = 255;
        }
        basePower = 13 * (gBattleMons[battlerAtk].friendship) / 51;
        break;
    case EFFECT_WATERFALL:
    case EFFECT_ROCK_CLIMB:
    case EFFECT_SURF:
        if (GetBattlerSide(battlerAtk) == B_SIDE_OPPONENT || GetBattlerHoldEffect(battlerAtk, FALSE) == HOLD_EFFECT_FAVOR_SCARF)
        {
            gBattleMons[battlerAtk].friendship = 255;
        }
        basePower = 6 * (gBattleMons[battlerAtk].friendship) / 17;
        break;
    case EFFECT_DIVE:
    case EFFECT_FLY:
    case EFFECT_WHIRLPOOL:
        if (GetBattlerSide(battlerAtk) == B_SIDE_OPPONENT || GetBattlerHoldEffect(battlerAtk, FALSE) == HOLD_EFFECT_FAVOR_SCARF)
        {
            gBattleMons[battlerAtk].friendship = 255;
        }
        basePower = 8 * (gBattleMons[battlerAtk].friendship) / 17;
        break;
    case EFFECT_FRUSTRATION:
        if (GetBattlerSide(battlerAtk) == B_SIDE_OPPONENT || GetBattlerHoldEffect(battlerAtk, FALSE) == HOLD_EFFECT_FAVOR_SCARF)
        {
            gBattleMons[battlerAtk].friendship = 255;
        }
        if (GetBattlerSide(battlerAtk) == B_SIDE_OPPONENT)
        {
            gBattleMons[battlerAtk].friendship = 0;
        }
        basePower = 10 * (MAX_FRIENDSHIP - gBattleMons[battlerAtk].friendship) / 25;
        break;
    case EFFECT_FURY_CUTTER:
        basePower = CalcFuryCutterBasePower(basePower, gDisableStructs[battlerAtk].furyCutterCounter);
        break;
    case EFFECT_ROLLOUT:
        basePower = CalcRolloutBasePower(battlerAtk, basePower, gDisableStructs[battlerAtk].rolloutTimer);
        break;
    case EFFECT_MAGNITUDE:
        basePower = gBattleStruct->magnitudeBasePower;
        break;
    case EFFECT_FEAR_FACTOR:
        basePower = gBattleStruct->fearFactorBasePower;
        break;
    case EFFECT_HIGH_ROLL_HIT:
        basePower = gBattleStruct->rollingBasePower;
        break;
    case EFFECT_DRAGON_POKER:
        basePower = gBattleStruct->dragonpokerBasePower;
        break;
    case EFFECT_PRESENT:
        basePower = gBattleStruct->presentBasePower;
        break;
    case EFFECT_TRIPLE_KICK:
        if (gMultiHitCounter == 0) // Calc damage with max BP for move consideration
            basePower *= 6;
        else
            basePower *= (4 - gMultiHitCounter);
        break;
    case EFFECT_SPIT_UP:
        basePower = 100 + (40 * (gDisableStructs[battlerAtk].stockpileCounter - 1));
        break;
    case EFFECT_REVENGE:
    case EFFECT_STALAG_BLAST:
        if ((gProtectStructs[battlerAtk].physicalDmg && gProtectStructs[battlerAtk].physicalBattlerId == battlerDef) || (gProtectStructs[battlerAtk].specialDmg && gProtectStructs[battlerAtk].specialBattlerId == battlerDef))
            basePower *= 2;
        break;
    case EFFECT_FICKLE_BEAM:
        if (gBattleStruct->fickleBeamBoosted)
            basePower *= 2;
        break;
    case EFFECT_UPPER_HAND:
    {
        if ((!((GetChosenMovePriority(gBattlerTarget) < 1))
        && (!(gChosenMoveByBattler[gBattlerTarget] == MOVE_NONE))
        && (!GetBattlerTurnOrderNum(gBattlerAttacker) > GetBattlerTurnOrderNum(gBattlerTarget))))
            basePower = 70;
        break;
    }
    case EFFECT_FEINT:
        if (gProtectStructs[gBattlerTarget].protected
            || gSideStatuses[GetBattlerSide(gBattlerTarget)] == SIDE_STATUS_WIDE_GUARD
            || gSideStatuses[GetBattlerSide(gBattlerTarget)] == SIDE_STATUS_QUICK_GUARD
            || gSideStatuses[GetBattlerSide(gBattlerTarget)] == SIDE_STATUS_MAT_BLOCK
            || gProtectStructs[gBattlerTarget].spikyShielded
            || gProtectStructs[gBattlerTarget].kingsShielded
            || gProtectStructs[gBattlerTarget].shelltered
            || gProtectStructs[gBattlerTarget].detectShielded
            || gProtectStructs[gBattlerTarget].banefulBunkered
            || gProtectStructs[gBattlerTarget].obstructed
            || gProtectStructs[gBattlerTarget].silkTrapped
            || gProtectStructs[gBattlerTarget].burningBulwarked
            || gProtectStructs[gBattlerTarget].drakenGuarded)
            basePower *= 2;
    case EFFECT_WEATHER_BALL:
        if (weather & B_WEATHER_ANY)
            basePower *= 2;
        break;
    case EFFECT_PURSUIT:
        if (gActionsByTurnOrder[GetBattlerTurnOrderNum(battlerDef)] == B_ACTION_SWITCH)
            basePower *= 2;
        break;
    case EFFECT_FUTURE_SIGHT:
        if (GetBattlerAbility(battlerAtk) == ABILITY_FOREWARN && gCurrentMove != MOVE_DECIMATION)
            basePower = uq4_12_multiply(basePower, UQ_4_12(1.3));
        break;
    case EFFECT_NATURAL_GIFT:
        basePower = gNaturalGiftTable[ITEM_TO_BERRY(gBattleMons[battlerAtk].item)].power;
        break;
    case EFFECT_WAKE_UP_SLAP:
        if (gBattleMons[battlerDef].status1 & STATUS1_SLEEP_ANY || abilityDef == ABILITY_COMATOSE)
            basePower *= 2;
        break;
    case EFFECT_SMELLINGSALT:
        if (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS)
            basePower *= 2;
        break;
    case EFFECT_DRAINING_KISS:
    case EFFECT_HEART_STEAL:
        if (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)
            basePower *= 2;
        break;
    case EFFECT_WRING_OUT:
        basePower = 120 * gBattleMons[battlerDef].hp / gBattleMons[battlerDef].maxHP;
        break;
    case EFFECT_HEX:
    case EFFECT_INFERNAL_PARADE:
    case EFFECT_BITTER_MALICE:
        if (gBattleMons[battlerDef].status1 & STATUS1_ANY_NEGATIVE || abilityDef == ABILITY_COMATOSE)
            basePower *= 2;
        break;
    case EFFECT_ASSURANCE:
        if (gProtectStructs[battlerDef].physicalDmg != 0 || gProtectStructs[battlerDef].specialDmg != 0 || gProtectStructs[battlerDef].confusionSelfDmg)
            basePower *= 2;
        break;
    case EFFECT_TRUMP_CARD:
        i = GetMoveSlot(gBattleMons[battlerAtk].moves, move);
        if (i != MAX_MON_MOVES)
        {
            if (gBattleMons[battlerAtk].pp[i] >= ARRAY_COUNT(sTrumpCardPowerTable))
                basePower = sTrumpCardPowerTable[ARRAY_COUNT(sTrumpCardPowerTable) - 1];
            else
                basePower = sTrumpCardPowerTable[gBattleMons[battlerAtk].pp[i]];
        }
        break;
    case EFFECT_PILGRIMAGE:
        i = GetMoveSlot(gBattleMons[battlerAtk].moves, move);
        if (i != MAX_MON_MOVES)
        {
            if (gBattleMons[battlerAtk].pp[i] >= ARRAY_COUNT(sPilgrimagePowerTable))
                basePower = sPilgrimagePowerTable[ARRAY_COUNT(sPilgrimagePowerTable) - 1];
            else
                basePower = sPilgrimagePowerTable[gBattleMons[battlerAtk].pp[i]];
        }
        break;
    case EFFECT_ACROBATICS:
        if (gBattleMons[battlerAtk].item == ITEM_NONE
            // Edge case, because removal of items happens after damage calculation.
            || (gSpecialStatuses[battlerAtk].gemBoost && GetBattlerHoldEffect(battlerAtk, FALSE) == HOLD_EFFECT_GEMS))
            basePower *= 2;
        break;
    case EFFECT_SAVAGE_WING:
        if (gBattleMons[battlerAtk].item == ITEM_NONE
            // Edge case, because removal of items happens after damage calculation.
            || (gSpecialStatuses[battlerAtk].gemBoost && GetBattlerHoldEffect(battlerAtk, FALSE) == HOLD_EFFECT_GEMS))
            basePower *= 1.5;
        break;
    case EFFECT_LOW_KICK:
        weight = GetBattlerWeight(battlerDef);
        for (i = 0; sWeightToDamageTable[i] != 0xFFFF; i += 2)
        {
            if (sWeightToDamageTable[i] > weight)
                break;
        }
        for (i = 0; sWeightToDamageTableBlooming[i] != 0xFFFF; i += 2)
        {
            if (sWeightToDamageTableBlooming[i] > weight)
                break;
        }
        if (gCurrentMove == MOVE_GRASS_KNOT && sWeightToDamageTable[i] != 0xFFFF && gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            basePower = sWeightToDamageTableBlooming[i + 1];
        else if (gCurrentMove == MOVE_GRASS_KNOT && gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            basePower = 140;
        else if (sWeightToDamageTable[i] != 0xFFFF)
            basePower = sWeightToDamageTable[i + 1];
        else
            basePower = 120;
        break;
    case EFFECT_HEAT_CRASH:
        weight = GetBattlerWeight(battlerAtk) / GetBattlerWeight(battlerDef);
        if (weight >= ARRAY_COUNT(sHeatCrashPowerTable))
            basePower = sHeatCrashPowerTable[ARRAY_COUNT(sHeatCrashPowerTable) - 1];
        else
            basePower = sHeatCrashPowerTable[weight];
        break;
    case EFFECT_PUNISHMENT:
        basePower = 50 + (CountBattlerStatIncreases(battlerDef, TRUE) * 50);
        break;
    case EFFECT_STORED_POWER:
        basePower += (CountBattlerStatIncreases(battlerAtk, TRUE) * 20);
        break;
    case EFFECT_BOLT_BEAK:
        basePower = 65 + (CountBattlerSpeedIncreases(battlerAtk) * 20);
        break;
    case EFFECT_IRON_TAIL:
        basePower = 120 + (CountBattlerDefenseIncreases(battlerAtk) * 20);
        break;
    case EFFECT_METAL_CLAW:
        basePower = 60 + (CountBattlerDefenseIncreases(battlerAtk) * 10);
        break;
    case EFFECT_AERIAL_ACE:
        basePower = 60 + (CountBattlerAccuracyIncreases(battlerAtk) * 15);
        break;
    case EFFECT_COMET_PUNCH:
        basePower = 25 + ((CountBattlerSpecialAttackIncreases(battlerAtk) + CountBattlerSpecialDefenseIncreases(battlerAtk)) * 3);
        break;
    case EFFECT_PSYCHIC_FANGS:
        basePower = 85 + ((CountBattlerSpecialAttackIncreases(battlerAtk) + CountBattlerSpecialDefenseIncreases(battlerAtk)) * 5);
        break;
    case EFFECT_POWER_GEM:
        basePower = 80 + (CountBattlerSpecialDefenseIncreases(battlerAtk) * 15);
        break;
    case EFFECT_REDLINE:
        basePower += (CountBattlerStatDecreases(battlerAtk, TRUE) * 50);
        break;
    case EFFECT_ZAPPER:
        basePower = 60 + (CountBattlerStatDecreases(battlerDef, TRUE) * 20);
        break;
    case EFFECT_DOUBLE_SHOCK:
        if (gStatuses4[battlerAtk] & STATUS4_GEARED_UP && gStatuses4[battlerAtk] & STATUS4_SUPERCHARGED)
            basePower = 250;
        break;
    case EFFECT_ZAP_CANNON:
        if (gStatuses4[battlerAtk] & STATUS4_SUPERCHARGED)
        {
            if (gStatuses4[battlerAtk] & STATUS4_GEARED_UP)
                basePower = 200;
            else
                basePower = 150;
        }
        break;
    case EFFECT_MAGNET_BOMB:
        if (gStatuses4[battlerAtk] & STATUS4_GEARED_UP)
            basePower = 60 + (CountBattlerStatIncreases(battlerDef, TRUE) * 10);
        break;
    case EFFECT_SHADOW_FORCE:
        if (gStatuses4[battlerAtk] & STATUS4_PHANTOM)
            basePower = 150;
        break;
    case EFFECT_HEAVY_CANNON:
        if (gBattleMons[battlerAtk].statStages[STAT_DEF] > DEFAULT_STAT_STAGE || gBattleMons[battlerAtk].statStages[STAT_SPDEF] > DEFAULT_STAT_STAGE)
            basePower += 30 * ((gBattleMons[battlerAtk].statStages[STAT_DEF] - DEFAULT_STAT_STAGE) + (gBattleMons[battlerAtk].statStages[STAT_SPDEF] - DEFAULT_STAT_STAGE));
            if (basePower < 100)
                basePower = 100;
        break;
    case EFFECT_ELECTRO_BALL:
        speed = GetBattlerTotalSpeedStat(battlerAtk) / GetBattlerTotalSpeedStat(battlerDef);
        if (speed >= ARRAY_COUNT(sSpeedDiffPowerTable))
            speed = ARRAY_COUNT(sSpeedDiffPowerTable) - 1;
        basePower = sSpeedDiffPowerTable[speed];
        break;
    case EFFECT_GYRO_BALL:
        basePower = ((25 * GetBattlerTotalSpeedStat(battlerDef)) / GetBattlerTotalSpeedStat(battlerAtk)) + 1;
        if (basePower > 150)
            basePower = 150;
        break;
    case EFFECT_ECHOED_VOICE:
        if (gBattleStruct->sameMoveTurns[battlerAtk] != 0)
        {
            basePower += (basePower * gBattleStruct->sameMoveTurns[battlerAtk]);
            if (basePower > 200)
                basePower = 200;
        }
        break;
    case EFFECT_BEATBOX:
        if (gBattleStruct->sameMoveTurns[battlerAtk] != 0)
        {
            basePower += (basePower * gBattleStruct->sameMoveTurns[battlerAtk]);
            if (basePower > 100)
                basePower = 100;
        }
        break;
    case EFFECT_FOCUS_PUNCH:
        if (gDisableStructs[battlerAtk].focusEnergy)
            basePower = 110;
        break;
    case EFFECT_PAYBACK:
        if (GetBattlerTurnOrderNum(battlerAtk) > GetBattlerTurnOrderNum(battlerDef)
#if B_PAYBACK_SWITCH_BOOST >= GEN_5
            && (gDisableStructs[battlerDef].isFirstTurn != 2)
#endif
        )
            basePower *= 2;
        break;
    case EFFECT_SEA_JAWS:
        if (GetBattlerTurnOrderNum(battlerAtk) < GetBattlerTurnOrderNum(battlerDef) || gDisableStructs[battlerDef].isFirstTurn == 2)
            basePower *= 2;
        break;
    case EFFECT_ROUND:
        for (i = 0; i < gBattlersCount; i++)
        {
            if (i != battlerAtk && IsBattlerAlive(i) && gLastMoves[i] == MOVE_ROUND)
            {
                basePower *= 2;
                break;
            }
        }
        break;
    case EFFECT_FUSION_COMBO:
        if (gBattleMoves[gLastUsedMove].effect == EFFECT_FUSION_COMBO && move != gLastUsedMove)
            basePower *= 2;
        break;
    case EFFECT_LASH_OUT:
        if (CountBattlerStatDecreases(battlerAtk, TRUE) != 0)
            basePower = uq4_12_multiply(basePower, UQ_4_12(2.0));
        break;
    case EFFECT_EXPLOSION:
        if (move == MOVE_MISTY_EXPLOSION && gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN && IsBattlerGrounded(battlerAtk))
            basePower = uq4_12_multiply(basePower, UQ_4_12(1.5));
        break;
    case EFFECT_DYNAMAX_DOUBLE_DMG:
#ifdef B_DYNAMAX
        if (IsDynamaxed(battlerDef))
            basePower *= 2;
#endif
        break;
    case EFFECT_HIDDEN_POWER:
    {
#if B_HIDDEN_POWER_DMG < GEN_6
        u8 powerBits;

        powerBits = ((gBattleMons[battlerAtk].hpIV & 2) >> 1) | ((gBattleMons[battlerAtk].attackIV & 2) << 0) | ((gBattleMons[battlerAtk].defenseIV & 2) << 1) | ((gBattleMons[battlerAtk].speedIV & 2) << 2) | ((gBattleMons[battlerAtk].spAttackIV & 2) << 3) | ((gBattleMons[battlerAtk].spDefenseIV & 2) << 4);

        basePower = (40 * powerBits) / 63 + 30;
#endif
        break;
    }
    case EFFECT_GRAV_APPLE:
        if (gFieldStatuses & STATUS_FIELD_GRAVITY)
            basePower = uq4_12_multiply(basePower, UQ_4_12(2.0));
        break;
    case EFFECT_GRAVITON_ARM:
        if (gFieldStatuses & STATUS_FIELD_GRAVITY)
            basePower = uq4_12_multiply(basePower, UQ_4_12(2.0));
        break;
    case EFFECT_TERRAIN_PULSE:
        if ((gFieldStatuses & STATUS_FIELD_TERRAIN_ANY) && IsBattlerGrounded(battlerAtk))
            basePower *= 2;
        break;
    case EFFECT_EXPANDING_FORCE:
        if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_PSYCHIC_TERRAIN))
            basePower = uq4_12_multiply(basePower, UQ_4_12(1.5));
        break;
    case EFFECT_RISING_VOLTAGE:
        if (IsBattlerTerrainAffected(battlerDef, STATUS_FIELD_ELECTRIC_TERRAIN))
            basePower *= 2;
        break;
    case EFFECT_RAZOR_SHELL:
        if (MOVE_WITHDRAW == gLastResultingMoves[battlerAtk])
            basePower *= 2;
        break;
    case EFFECT_SHARP_GLIDE:
    case EFFECT_AIR_CUTTER:
        if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_TAILWIND)
            basePower *= 2;
        break;
    case EFFECT_HIT_SET_REMOVE_TERRAIN:
        if (gFieldStatuses & STATUS_FIELD_TERRAIN_ANY || gFieldStatuses & STATUS_FIELD_TRICK_ROOM || gFieldStatuses & STATUS_FIELD_WONDER_ROOM || gFieldStatuses & STATUS_FIELD_MAGIC_ROOM || gFieldStatuses & STATUS_FIELD_INVERSE_ROOM)
            basePower = uq4_12_multiply(basePower, UQ_4_12(1.5));
        break;
    case EFFECT_BEAT_UP:
#if B_BEAT_UP >= GEN_5
        basePower = CalcBeatUpPower();
#endif
        break;
    case EFFECT_PSYBLADE:
        if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_ELECTRIC_TERRAIN))
            basePower = uq4_12_multiply(basePower, UQ_4_12(1.5));
        break;
    case EFFECT_LAST_RESPECTS:
        basePower = 50 + (30 * gBattleStruct->faintedMonCount[GetBattlerSide(battlerAtk)]);
        basePower = (basePower > 200) ? 200 : basePower;
        break;
    case EFFECT_RAGE_FIST:
        basePower = 50 + (30 * gBattleStruct->timesGotHit[GetBattlerSide(battlerAtk)][gBattlerPartyIndexes[battlerAtk]]);
        basePower = (basePower > 200) ? 200 : basePower;
        break;
    case EFFECT_FIERY_WRATH:
        basePower = 80 + (20 * gBattleStruct->timesGotHit[GetBattlerSide(battlerAtk)][gBattlerPartyIndexes[battlerAtk]]);
        basePower = (basePower > 200) ? 200 : basePower;
        break;
    case EFFECT_BARI_BARI_BEAM:
        basePower = 40 + (30 * gBattleStruct->timesGotHit[GetBattlerSide(battlerAtk)][gBattlerPartyIndexes[battlerAtk]]);
        basePower = (basePower > 160) ? 160 : basePower;
        break;
    case EFFECT_DRAGON_CLAW:
        if (gBattleStruct->fickleBeamBoosted)
            basePower = 100;
        break;
    case EFFECT_DRAGON_PULSE:
        if (gBattleMons[battlerAtk].hp == gBattleMons[battlerAtk].maxHP)
            basePower = 100;
        break;
    case EFFECT_GRASSY_GLIDE:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            basePower = 70;
        break;
    }

    // Move-specific base power changes
    switch (move)
    {
    case MOVE_WATER_SHURIKEN:
        if (gBattleMons[battlerAtk].species == SPECIES_GRENINJA_ASH)
            basePower = 20;
        break;
    case MOVE_FIRE_SPIN:
        if (gBattleMons[battlerAtk].species == SPECIES_CHARIZARD)
            basePower = 100;
        break;
    }

    if (basePower == 0)
        basePower = 1;
    return basePower;
}

#define TYPE_POWER_INCREASE_CHECK(typeCheck) {    \
    if (moveType == typeCheck) { \
        holdEffectModifier = uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(20)); \
        modifier = uq4_12_multiply(modifier, holdEffectModifier);   \
    }                                                               \
}

u32 CalcMoveBasePowerAfterModifiers(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType, bool32 updateFlags, u32 atkAbility, u32 defAbility, u32 holdEffectAtk, u32 weather)
{
    u32 i;
    u32 holdEffectParamAtk;
    u32 basePower = CalcMoveBasePower(move, battlerAtk, battlerDef, defAbility, weather);
    uq4_12_t holdEffectModifier;
    uq4_12_t modifier = UQ_4_12(1.0);
    u32 atkSide = GetBattlerSide(battlerAtk);

    // move effect
    switch (gBattleMoves[move].effect)
    {
    case EFFECT_FACADE:
        if (gBattleMons[battlerAtk].status1 & (STATUS1_BURN | STATUS1_PSN_ANY | STATUS1_PARALYSIS | STATUS1_FROSTBITE | STATUS1_PANIC | STATUS1_EXPOSED))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_ZEN_HEADBUTT:
        if (gBattleMons[battlerAtk].status2 & STATUS2_TORMENT || gBattleMons[battlerAtk].status2 & STATUS2_CONFUSION || gDisableStructs[battlerAtk].tauntTimer != 0)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case EFFECT_FROST_NOVA:
        if (gBattleMons[battlerDef].status1 & STATUS1_FROSTBITE)
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_VACUUM_WAVE:
        if (CountBattlerStatIncreases(battlerDef, TRUE) < 1 && CountBattlerStatDecreases(battlerDef, TRUE) < 1)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case EFFECT_KERFUFFLE:
        if (gBattleMons[battlerAtk].status2 & STATUS2_CONFUSION)
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_BRINE:
        if (gBattleMons[battlerDef].hp <= (gBattleMons[battlerDef].maxHP / 2))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_BARI_BARI_BASH:
        if (gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 2))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_EXECUTION:
        if (gBattleMons[battlerDef].hp <= (gBattleMons[battlerDef].maxHP * 3 / 4))
            modifier = uq4_12_multiply(modifier, UQ_4_12(3.0));
        break;
    case EFFECT_BARB_BARRAGE:
    case EFFECT_VENOSHOCK:
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY)
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_RETALIATE:
        if (gSideTimers[atkSide].retaliateTimer == 1)
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_SOLAR_BEAM:
        if (IsBattlerWeatherAffected(battlerAtk, (B_WEATHER_HAIL | B_WEATHER_SANDSTORM | B_WEATHER_RAIN | B_WEATHER_SNOW)))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
        break;
    case EFFECT_DUNE_SLICER:
        if (IsBattlerWeatherAffected(battlerAtk, B_WEATHER_SANDSTORM))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case EFFECT_GLACIAL_SHIFT:
        if (IsBattlerWeatherAffected(battlerAtk, B_WEATHER_HAIL))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case EFFECT_STOMPING_TANTRUM:
        if (gBattleStruct->lastMoveFailed & gBitTable[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case EFFECT_BULLDOZE:
    case MOVE_MAGNITUDE:
    case EFFECT_EARTHQUAKE:
        if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN && !(gStatuses3[battlerDef] & STATUS3_SEMI_INVULNERABLE))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
        break;
    case EFFECT_KNOCK_OFF:
#if B_KNOCK_OFF_DMG >= GEN_6
        if (gBattleMons[battlerDef].item != ITEM_NONE && CanBattlerGetOrLoseItem(battlerDef, gBattleMons[battlerDef].item))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
#endif
        break;
    }

#if B_TERRAIN_TYPE_BOOST >= GEN_8
#define TERRAIN_TYPE_BOOST UQ_4_12(1.3)
#else
#define TERRAIN_TYPE_BOOST UQ_4_12(1.5)
#endif

    // various effects
    if (gProtectStructs[battlerAtk].helpingHand)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (gSpecialStatuses[battlerAtk].gemBoost)
        modifier = uq4_12_multiply(modifier, uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(gSpecialStatuses[battlerAtk].gemParam)));
    if (gStatuses3[battlerAtk] & STATUS3_CHARGED_UP && moveType == TYPE_ELECTRIC)
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
    if (gStatuses4[battlerAtk] & STATUS4_PUMPED_UP && moveType == TYPE_WATER)
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
    if (gStatuses4[battlerAtk] & STATUS4_GEARED_UP && moveType == TYPE_STEEL)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (gStatuses4[battlerAtk] & STATUS4_PHANTOM && gIsCriticalHit)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (gStatuses4[battlerAtk] & STATUS4_SUPERCHARGED && moveType == TYPE_ELECTRIC)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (gStatuses4[battlerDef] & STATUS4_CRAFTY_SHIELD)
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    if (gStatuses3[battlerAtk] & STATUS3_ME_FIRST)
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
    if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_GRASSY_TERRAIN) && moveType == TYPE_GRASS)
        modifier = uq4_12_multiply(modifier, TERRAIN_TYPE_BOOST);
    if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_MISTY_TERRAIN) && moveType == TYPE_FAIRY)
        modifier = uq4_12_multiply(modifier, TERRAIN_TYPE_BOOST);
    if (IsBattlerTerrainAffected(battlerDef, STATUS_FIELD_TERRAIN_ANY) && (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GROUND)))
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.9));
    if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_ELECTRIC_TERRAIN) && moveType == TYPE_ELECTRIC)
        modifier = uq4_12_multiply(modifier, TERRAIN_TYPE_BOOST);
    if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_PSYCHIC_TERRAIN) && moveType == TYPE_PSYCHIC)
        modifier = uq4_12_multiply(modifier, TERRAIN_TYPE_BOOST);
#if B_SPORT_TURNS >= GEN_6
    if ((moveType == TYPE_ELECTRIC && gFieldStatuses & STATUS_FIELD_MUDSPORT) || (moveType == TYPE_FIRE && gFieldStatuses & STATUS_FIELD_WATERSPORT))
#else
    if ((moveType == TYPE_ELECTRIC && AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, 0, ABILITYEFFECT_MUD_SPORT, 0)) || (moveType == TYPE_FIRE && AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, 0, ABILITYEFFECT_WATER_SPORT, 0)))
#endif
#if B_SPORT_DMG_REDUCTION >= GEN_5
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.23));
#else
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
#endif

    // attacker's abilities
    switch (atkAbility)
    {
    case ABILITY_TECHNICIAN:
        if (basePower <= 60)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_FLARE_BOOST:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BURN && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_TOXIC_BOOST:
        if (gBattleMons[battlerAtk].status1 & STATUS1_PSN_ANY && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_RECKLESS:
        if (IS_MOVE_RECOIL(move))
        {
            i = Random() % 3;

            if (i == 0)
            {
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
            }
            else if (i == 1)
            {
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            }
            else if (i == 2)
            {
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.4));
            }
            else
            {
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
            }
        }
        break;
    case ABILITY_IRON_FIST:
        if (gBattleMoves[move].punchingMove)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_SHAMBLES:
        if ((IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_TERRAIN_ANY) || gFieldStatuses & STATUS_FIELD_TRICK_ROOM || gFieldStatuses & STATUS_FIELD_WONDER_ROOM || gFieldStatuses & STATUS_FIELD_MAGIC_ROOM || gFieldStatuses & STATUS_FIELD_INVERSE_ROOM) && (gBattleMoves[move].switchingMove))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_SHEER_FORCE:
        if (gBattleMoves[move].sheerForceBoost)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_SAND_FORCE:
        if ((moveType == TYPE_STEEL || moveType == TYPE_ROCK || moveType == TYPE_GROUND) && weather & B_WEATHER_SANDSTORM)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_RIVALRY:
        if (AreBattlersOfSameGender(battlerAtk, battlerDef))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
        else if (AreBattlersOfOppositeGender(battlerAtk, battlerDef))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
        break;
    case ABILITY_ANALYTIC:
        if (GetBattlerTurnOrderNum(battlerAtk) == gBattlersCount - 1 && move != MOVE_FUTURE_SIGHT && move != MOVE_DOOM_DESIRE)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_TOUGH_CLAWS:
        if (IsMoveMakingContact(move, battlerAtk))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_STALL:
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
        break;
    case ABILITY_STRONG_JAW:
        if (gBattleMoves[move].bitingMove)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_MEGA_LAUNCHER:
        if (gBattleMoves[move].pulseMove)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_WATER_BUBBLE:
        if (moveType == TYPE_WATER)
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_STEELWORKER:
        if (moveType == TYPE_STEEL)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_PINK_MIST:
        if (moveType == TYPE_PSYCHIC && gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_POTENCY:
        if (moveType == TYPE_POISON)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_SEAFARER:
        if (moveType == TYPE_WATER)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_CRUELTY:
        if (moveType == TYPE_DARK)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_BIG_PECKS:
        if (moveType == TYPE_FLYING)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_PIXILATE:
        if (moveType == TYPE_FAIRY && gBattleStruct->ateBoost[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_AQUA_HEART:
        if (moveType == TYPE_WATER && gBattleStruct->ateBoost[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_DRACO_FORCE:
        if (moveType == TYPE_DRAGON && gBattleStruct->ateBoost[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_GALVANIZE:
        if (moveType == TYPE_ELECTRIC && gBattleStruct->ateBoost[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_REFRIGERATE:
        if (moveType == TYPE_ICE && gBattleStruct->ateBoost[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_AERILATE:
        if (moveType == TYPE_FLYING && gBattleStruct->ateBoost[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_NORMALIZE:
        if (moveType == TYPE_NORMAL && gBattleStruct->ateBoost[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_LIQUID_VOICE:
        if (gBattleMoves[move].soundMove && moveType == TYPE_WATER && gBattleStruct->ateBoost[battlerAtk])
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_PUNK_ROCK:
        if (gBattleMoves[move].soundMove)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_STEELY_SPIRIT:
        if (moveType == TYPE_STEEL)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_HIBERNAL:
        if (moveType == TYPE_ICE)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_TRANSISTOR:
        if (moveType == TYPE_ELECTRIC)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_DRAGONS_MAW:
        if (moveType == TYPE_DRAGON)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_GORILLA_TACTICS:
        if (IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_ROCKY_PAYLOAD:
        if (moveType == TYPE_ROCK)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_PROTOSYNTHESIS:
    {
        u8 atkHighestStat = GetHighestStatId(battlerAtk);
        if (weather & B_WEATHER_SUN && ((IS_MOVE_PHYSICAL(move) && atkHighestStat == STAT_ATK) || (IS_MOVE_SPECIAL(move) && atkHighestStat == STAT_SPATK)))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    }
    break;
    case ABILITY_QUARK_DRIVE:
    {
        u8 atkHighestStat = GetHighestStatId(battlerAtk);
        if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN && ((IS_MOVE_PHYSICAL(move) && atkHighestStat == STAT_ATK) || (IS_MOVE_SPECIAL(move) && atkHighestStat == STAT_SPATK)))
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    }
    break;
    case ABILITY_ORICHALCUM_PULSE:
        if (weather & B_WEATHER_SUN)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_HADRON_ENGINE:
        if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_MERCILESS:
        if (gBattleMons[battlerDef].status1 & STATUS1_POISON)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
        break;
    case ABILITY_SHARPNESS:
        if (gBattleMoves[move].slicingMove)
            modifier = uq4_12_multiply(modifier, GetSharpnessModifier(battlerAtk));
        break;
    case ABILITY_STRONGHOLD:
        if (CountBattlerDefenseIncreases(battlerAtk) > 0)
            modifier = uq4_12_multiply(modifier, GetStrongholdOffenseModifier(battlerAtk));
        break;
    case ABILITY_OWN_TEMPO:
        if (gBattleMoves[move].danceMove)
            modifier = uq4_12_multiply(modifier, GetOwnTempoModifier(battlerAtk));
        break;
    case ABILITY_PURPLE_HAZE:
        if (gDisableStructs[battlerAtk].purpleHazeOffense && IS_MOVE_PHYSICAL(gCurrentMove))
            modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_DREAD_VEIL:
        if (gBattleMons[battlerDef].status1 & STATUS1_PANIC)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
        break;
    case ABILITY_RISING:
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
        break;
    case ABILITY_SUPREME_OVERLORD:
        modifier = uq4_12_multiply(modifier, GetSupremeOverlordModifier(battlerAtk));
        break;
    }

    // field abilities
    if (IsAbilityOnField(ABILITY_FAIRY_AURA) && moveType == TYPE_FAIRY)
    {
        if (IsAbilityOnField(ABILITY_AURA_BREAK))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
        else
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.33));
    }

    if (IsAbilityOnField(ABILITY_DAMP) && (moveType == TYPE_FIRE || moveType == TYPE_GROUND || moveType == TYPE_ROCK))
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));

    if (IsAbilityOnOpposingSide(battlerAtk, ABILITY_FALLING) && atkAbility != ABILITY_FALLING)
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));

    if (IsAbilityOnField(ABILITY_VESSEL_OF_RUIN) && atkAbility != ABILITY_VESSEL_OF_RUIN && IS_MOVE_SPECIAL(gCurrentMove))
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));

    if (IsAbilityOnField(ABILITY_TABLETS_OF_RUIN) && atkAbility != ABILITY_TABLETS_OF_RUIN && IS_MOVE_PHYSICAL(gCurrentMove))
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));

    if (IsAbilityOnSide(battlerAtk, ABILITY_VICTORY_STAR))
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));

    if (IsAbilityOnField(ABILITY_DARK_AURA) && defAbility != ABILITY_DARK_AURA)
        modifier = uq4_12_multiply_half_down(modifier, GetDarkAuraModifier(battlerDef));

    if (IsAbilityOnSide(battlerAtk, ABILITY_PLUS)
    && IsAbilityOnSide(battlerAtk, ABILITY_MINUS)
    && (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_ELECTRIC) 
    || IS_BATTLER_OF_TYPE(battlerAtk, TYPE_STEEL)))
    {
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
    }
    else if (IsAbilityOnSide(battlerAtk, ABILITY_PLUS) 
    && (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_ELECTRIC) 
    || IS_BATTLER_OF_TYPE(battlerAtk, TYPE_STEEL)))
    {
        modifier = uq4_12_multiply(modifier, UQ_4_12(1.15));
    }

    if (IsAbilityOnSide(battlerDef, ABILITY_MINUS)
    && IsAbilityOnSide(battlerDef, ABILITY_PLUS)
    && (IS_BATTLER_OF_TYPE(battlerDef, TYPE_ELECTRIC) 
    || IS_BATTLER_OF_TYPE(battlerDef, TYPE_STEEL)))
    {
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
    }
    else if (IsAbilityOnSide(battlerDef, ABILITY_MINUS) 
    && (IS_BATTLER_OF_TYPE(battlerDef, TYPE_ELECTRIC) 
    || IS_BATTLER_OF_TYPE(battlerDef, TYPE_STEEL)))
    {
        modifier = uq4_12_multiply(modifier, UQ_4_12(0.75));
    }

    // attacker partner's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
    {
        switch (GetBattlerAbility(BATTLE_PARTNER(battlerAtk)))
        {
        case ABILITY_BATTERY:
            if (IS_MOVE_SPECIAL(move))
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            break;
        case ABILITY_POWER_SPOT:
            if (IS_MOVE_PHYSICAL(move))
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.3));
            break;
        case ABILITY_STEELY_SPIRIT:
            if (moveType == TYPE_STEEL)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.5));
            break;
        }
    }

    // target's abilities
    switch (defAbility)
    {
    case ABILITY_HEATPROOF:
    case ABILITY_WATER_BUBBLE:
        if (moveType == TYPE_FIRE)
        {
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.5));
            if (updateFlags)
                RecordAbilityBattle(battlerDef, defAbility);
        }
        break;
    case ABILITY_DRY_SKIN:
        if (moveType == TYPE_FIRE)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.25));
        break;
    case ABILITY_PROTOSYNTHESIS:
    {
        u8 defHighestStat = GetHighestStatId(battlerDef);
        if (weather & B_WEATHER_SUN && ((IS_MOVE_PHYSICAL(move) && defHighestStat == STAT_DEF) || (IS_MOVE_SPECIAL(move) && defHighestStat == STAT_SPDEF)))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.7));
    }
    break;
    case ABILITY_QUARK_DRIVE:
    {
        u8 defHighestStat = GetHighestStatId(battlerDef);
        if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN && ((IS_MOVE_PHYSICAL(move) && defHighestStat == STAT_DEF) || (IS_MOVE_SPECIAL(move) && defHighestStat == STAT_SPDEF)))
            modifier = uq4_12_multiply(modifier, UQ_4_12(0.7));
    }
    break;
    }

    holdEffectParamAtk = GetBattlerHoldEffectParam(battlerAtk);
    if (holdEffectParamAtk > 100)
        holdEffectParamAtk = 100;

    holdEffectModifier = uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(holdEffectParamAtk));

    // attacker's hold effect
    switch (holdEffectAtk)
    {
    case HOLD_EFFECT_MUSCLE_BAND:
        if (IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply(modifier, uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12_Floored(holdEffectParamAtk)));
        break;
    case HOLD_EFFECT_WISE_GLASSES:
        if (IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply(modifier, uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12_Floored(holdEffectParamAtk)));
        break;
    case HOLD_EFFECT_LUSTROUS_ORB:
        if (GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_PALKIA && (moveType == TYPE_WATER || moveType == TYPE_DRAGON))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_ADAMANT_ORB:
        if (GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_DIALGA && (moveType == TYPE_STEEL || moveType == TYPE_DRAGON))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_GRISEOUS_ORB:
        if (GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species) == SPECIES_GIRATINA && (moveType == TYPE_GHOST || moveType == TYPE_DRAGON))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_SOUL_DEW:
#if B_SOUL_DEW_BOOST >= GEN_7
        if ((gBattleMons[battlerAtk].species == SPECIES_LATIAS || gBattleMons[battlerAtk].species == SPECIES_LATIOS) && (moveType == TYPE_PSYCHIC || moveType == TYPE_DRAGON))
#else
        if ((gBattleMons[battlerAtk].species == SPECIES_LATIAS || gBattleMons[battlerAtk].species == SPECIES_LATIOS) && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER) && IS_MOVE_SPECIAL(move))
#endif
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_BUG_POWER:
    case HOLD_EFFECT_STEEL_POWER:
    case HOLD_EFFECT_GROUND_POWER:
    case HOLD_EFFECT_ROCK_POWER:
    case HOLD_EFFECT_GRASS_POWER:
    case HOLD_EFFECT_DARK_POWER:
    case HOLD_EFFECT_FIGHTING_POWER:
    case HOLD_EFFECT_ELECTRIC_POWER:
    case HOLD_EFFECT_WATER_POWER:
    case HOLD_EFFECT_FLYING_POWER:
    case HOLD_EFFECT_POISON_POWER:
    case HOLD_EFFECT_ICE_POWER:
    case HOLD_EFFECT_GHOST_POWER:
    case HOLD_EFFECT_PSYCHIC_POWER:
    case HOLD_EFFECT_FIRE_POWER:
    case HOLD_EFFECT_DRAGON_POWER:
    case HOLD_EFFECT_NORMAL_POWER:
    case HOLD_EFFECT_FAIRY_POWER:
        for (i = 0; i < ARRAY_COUNT(sHoldEffectToType); i++)
        {
            if (holdEffectAtk == sHoldEffectToType[i][0])
            {
                if (moveType == sHoldEffectToType[i][1])
                    modifier = uq4_12_multiply(modifier, holdEffectModifier);
                break;
            }
        }
        break;
    case HOLD_EFFECT_SILVER_POWDER:
        TYPE_POWER_INCREASE_CHECK(TYPE_BUG);
        break;
    case HOLD_EFFECT_METAL_COAT:
        TYPE_POWER_INCREASE_CHECK(TYPE_STEEL);
        break;
    case HOLD_EFFECT_SOFT_SAND:
        TYPE_POWER_INCREASE_CHECK(TYPE_GROUND);
        break;
    case HOLD_EFFECT_HARD_STONE:
        TYPE_POWER_INCREASE_CHECK(TYPE_ROCK);
        break;
    case HOLD_EFFECT_MIRACLE_SEED:
        TYPE_POWER_INCREASE_CHECK(TYPE_GRASS);
        break;
    case HOLD_EFFECT_BLACK_GLASSES:
        TYPE_POWER_INCREASE_CHECK(TYPE_DARK);
        break;
    case HOLD_EFFECT_BLACK_BELT:
        TYPE_POWER_INCREASE_CHECK(TYPE_FIGHTING);
        break;
    case HOLD_EFFECT_MAGNET:
        TYPE_POWER_INCREASE_CHECK(TYPE_ELECTRIC);
        break;
    case HOLD_EFFECT_MYSTIC_WATER:
        TYPE_POWER_INCREASE_CHECK(TYPE_WATER);
        break;
    case HOLD_EFFECT_SHARP_BEAK:
        if (moveType == TYPE_FLYING) {
            holdEffectModifier = UQ_4_12(1.0);
            holdEffectModifier += PercentToUQ4_12(20);
            if (IsBattlerGrounded(battlerDef))
                holdEffectModifier += PercentToUQ4_12(10);
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        }
        break;
    case HOLD_EFFECT_POISON_BARB:
        if (moveType == TYPE_POISON)
        {
            holdEffectModifier = uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(20));
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        }
        break;
    case HOLD_EFFECT_NEVER_MELT_ICE:
        TYPE_POWER_INCREASE_CHECK(TYPE_ICE);
        break;
    case HOLD_EFFECT_SPELL_TAG:
        TYPE_POWER_INCREASE_CHECK(TYPE_GHOST);
        break;
    case HOLD_EFFECT_TWISTED_SPOON:
        if (moveType == TYPE_PSYCHIC) {
            holdEffectModifier = uq4_12_add(UQ_4_12(1.0), PercentToUQ4_12(20));
            if (CountNegativeStatStages(battlerAtk) > 0)
                holdEffectModifier += PercentToUQ4_12(30);
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        }
        break;
    case HOLD_EFFECT_CHARCOAL:
        if (moveType == TYPE_FIRE)
        {
            holdEffectModifier = UQ_4_12(1.0);
            holdEffectModifier += PercentToUQ4_12(20);
            if (gBattleMons[battlerDef].status1 & STATUS1_BURN)
                holdEffectModifier += PercentToUQ4_12(20);
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        }
        break;
    case HOLD_EFFECT_DRAGON_FANG:
        TYPE_POWER_INCREASE_CHECK(TYPE_DRAGON);
        break;
    case HOLD_EFFECT_SILK_SCARF:
        // either boosts 20% for normal moves or 10%
        holdEffectModifier = UQ_4_12(1.0);
        if (moveType == TYPE_NORMAL) {
            holdEffectModifier += PercentToUQ4_12(20);
        } else {
            holdEffectModifier += PercentToUQ4_12(10);
        }
        modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_FAIRY_FEATHER:
        TYPE_POWER_INCREASE_CHECK(TYPE_FAIRY);
        break;
    case HOLD_EFFECT_PLATE:
        if (moveType == ItemId_GetSecondaryId(gBattleMons[battlerAtk].item))
            modifier = uq4_12_multiply(modifier, holdEffectModifier);
        break;
    case HOLD_EFFECT_PUNCHING_GLOVE:
        if (gBattleMoves[move].punchingMove)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.1));
        break;
    case HOLD_EFFECT_STILETTO:
        if (gBattleMoves[move].kickingMove)
            modifier = uq4_12_multiply(modifier, UQ_4_12(1.1));
        break;
    }
    return uq4_12_multiply_by_int_half_down(modifier, basePower);

    // Ally hold effect
    if (IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
    {
        switch (GetBattlerHoldEffect(BATTLE_PARTNER(battlerAtk), TRUE))
        {
        case HOLD_EFFECT_FRIEND_RIBBON:
            if (BATTLE_PARTNER(battlerAtk) == SPECIES_COLFIN)
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
                break;        
        case HOLD_EFFECT_MAGNET: // boost ally electric power by 20%
            if (moveType == TYPE_ELECTRIC)
                modifier = uq4_12_multiply(modifier, UQ_4_12(1.2));
            break;
        }
    }
}
#undef TERRAIN_TYPE_BOOST
#undef TYPE_POWER_INCREASE_CHECK

static inline u32 CalcAttackStat(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType, bool32 isCrit, bool32 updateFlags, u32 atkAbility, u32 defAbility, u32 holdEffectAtk)
{
    u8 atkStage;
    u32 atkStat;
    uq4_12_t modifier;
    u16 atkBaseSpeciesId;
    u8 formNum;
    u32 atkSide = GetBattlerSide(battlerAtk);

    atkBaseSpeciesId = GET_BASE_SPECIES_ID(gBattleMons[battlerAtk].species);

    if (gBattleMoves[move].effect == EFFECT_FOUL_PLAY)
    {
        atkStat = gBattleMons[battlerDef].attack;
        atkStage = gBattleMons[battlerDef].statStages[STAT_ATK];
    }
    else if (gBattleMoves[move].effect == EFFECT_MIND_BREAK)
    {
        atkStat = gBattleMons[battlerDef].spAttack;
        atkStage = gBattleMons[battlerDef].statStages[STAT_SPATK];
    }
    else if (gBattleMoves[move].effect == EFFECT_ROADBLOCK)
    {
        atkStat = gBattleMons[battlerDef].speed;
        atkStage = gBattleMons[battlerDef].statStages[STAT_SPEED];
    }
    else if (gBattleMoves[move].effect == EFFECT_BODY_PRESS || gBattleMoves[move].effect == EFFECT_RAZOR_SHELL || gBattleMoves[move].effect == EFFECT_SKULL_BASH || gBattleMoves[move].effect == EFFECT_STALAG_BLAST)
    {
        atkStat = gBattleMons[battlerAtk].defense;
        atkStage = gBattleMons[battlerAtk].statStages[STAT_DEF];
    }
    else if (gBattleMoves[move].effect == EFFECT_WILLPOWER || gBattleMoves[move].effect == EFFECT_STELLAR_FIST)
    {
        atkStat = gBattleMons[battlerAtk].spDefense;
        atkStage = gBattleMons[battlerAtk].statStages[STAT_SPDEF];
    }
    else if (gBattleMoves[move].effect == EFFECT_SONIC_BURST)
    {
        atkStat = gBattleMons[battlerAtk].speed;
        atkStage = gBattleMons[battlerAtk].statStages[STAT_SPEED];
    }
    else
    {
        if (IS_MOVE_PHYSICAL(move))
        {
            atkStat = gBattleMons[battlerAtk].attack;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_ATK];
        }
        else
        {
            atkStat = gBattleMons[battlerAtk].spAttack;
            atkStage = gBattleMons[battlerAtk].statStages[STAT_SPATK];
        }
    }

    // critical hits ignore attack stat's stage drops
    if (isCrit && atkStage < DEFAULT_STAT_STAGE)
        atkStage = DEFAULT_STAT_STAGE;
    // pokemon with unaware ignore attack stat changes while taking damage
    if (defAbility == ABILITY_UNAWARE || defAbility == ABILITY_IGNORANT_BLISS)
        atkStage = DEFAULT_STAT_STAGE;
    if (GetBattlerHoldEffect(battlerDef, TRUE) == HOLD_EFFECT_WINTAMEL_TEA && gBattleMons[battlerDef].species == SPECIES_POMELONIAN)
        atkStage = DEFAULT_STAT_STAGE;
    if (atkStage < DEFAULT_STAT_STAGE && atkAbility == ABILITY_AQUA_HEART && gBattleStruct->dynamicMoveType == (TYPE_WATER | F_DYNAMIC_TYPE_2))
        atkStage = DEFAULT_STAT_STAGE;
    if (atkStage < DEFAULT_STAT_STAGE && gCurrentMove == MOVE_AURA_SPHERE)
        atkStage = DEFAULT_STAT_STAGE;

    atkStat *= gStatStageRatios[atkStage][0];
    atkStat /= gStatStageRatios[atkStage][1];

    // apply attack stat modifiers
    modifier = UQ_4_12(1.0);

    // attacker's abilities
    switch (atkAbility)
    {
    case ABILITY_GOLDEN_MEAN:
        if (gBattleMons[battlerAtk].species == SPECIES_SHUNYONG_GOLDEN_OFFENSE)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        if (gBattleMons[battlerAtk].species == SPECIES_SHUNYONG)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    case ABILITY_DORMANT:
        if (gBattleMons[battlerAtk].species == SPECIES_BISHOUCHA_WARMONGER && IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_PUNISHER:
        if ((gBattleMons[battlerAtk].species == SPECIES_SHISHIMA_PUNISHER || gBattleMons[battlerAtk].species == SPECIES_SHISHIMA_PUNISHER_ALT) && IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(4.0));
        break;
    case ABILITY_HUGE_POWER:
    case ABILITY_PURE_POWER:
        if (IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_SHUNYONG:
        if (gBattleMons[battlerAtk].species == SPECIES_SHUNYONG_GOLDEN_OFFENSE)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    case ABILITY_MYSTIC_ONE:
        if (IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_SLOW_START:
        if (gDisableStructs[battlerAtk].slowStartTimer != 0)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    case ABILITY_STARS_GRACE:
        if (gDisableStructs[battlerAtk].slowStartTimer < 1 && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_WHITE_OUT:
        if (IS_MOVE_SPECIAL(move) && IsBattlerWeatherAffected(battlerAtk, B_WEATHER_HAIL))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_DEFEATIST:
        if (gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 2))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    // Flash Fire now does not do this
    /*
    case ABILITY_FLASH_FIRE:
        if (moveType == TYPE_FIRE && gBattleResources->flags->flags[battlerAtk] & RESOURCE_FLAG_FLASH_FIRE)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    */
    case ABILITY_SWARM:
        if (moveType == TYPE_BUG && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_TORRENT:
        if (moveType == TYPE_WATER && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_BLAZE:
        if (moveType == TYPE_FIRE && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_DRAINAGE:
        if (gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 2) && IsMoveDraining(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_POWER_SPIKE:
        if (gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 2) && gBattleMoves[move].piercingMove)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.75));
        break;
    case ABILITY_OVERGROW:
        if (moveType == TYPE_GRASS && gBattleMons[battlerAtk].hp <= (gBattleMons[battlerAtk].maxHP / 3))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_FLOWER_GIFT:
        if (gBattleMons[battlerAtk].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(battlerAtk, B_WEATHER_SUN) && IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_HUSTLE:
        if (IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_STAKEOUT:
        if (gDisableStructs[battlerDef].isFirstTurn == 2) // just switched in
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_GUTS:
        if (gBattleMons[battlerAtk].status1 & STATUS1_ANY_NEGATIVE && IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    }

    // target's abilities
    switch (defAbility)
    {
    case ABILITY_THICK_FAT:
        if (moveType == TYPE_FIRE || moveType == TYPE_ICE)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
            if (updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_THICK_FAT);
        }
        break;
    }

    // ally's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
    {
        switch (GetBattlerAbility(BATTLE_PARTNER(battlerAtk)))
        {
        case ABILITY_FLOWER_GIFT:
            if (gBattleMons[BATTLE_PARTNER(battlerAtk)].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(BATTLE_PARTNER(battlerAtk), B_WEATHER_SUN) && IS_MOVE_PHYSICAL(move))
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            break;
        }
    }

    // attacker's hold effect
    switch (holdEffectAtk)
    {
    case HOLD_EFFECT_THICK_CLUB:
        if ((atkBaseSpeciesId == SPECIES_CUBONE || atkBaseSpeciesId == SPECIES_MAROWAK) && IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_TRIUMPH_STAR:
        if (atkBaseSpeciesId == SPECIES_LEDIAN && gSideStatuses[atkSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_GOOGOO_SCREEN))
        {
            if (IS_MOVE_PHYSICAL(move))
            {
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
            }
            if (gBattleMoves[move].punchingMove)
            {
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            }
        }
        break;
    case HOLD_EFFECT_VIBRANT_SCALE:
        if (gBattleMons[battlerAtk].species == SPECIES_BIVAGUE && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_FAVOR_SCARF:
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.1));
        break;
    case HOLD_EFFECT_SALTY_TEAR:
        if (gBattleMons[battlerAtk].species == SPECIES_SADSOD)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    case HOLD_EFFECT_FAIRY_RING:
        if (gBattleMoves[move].type == TYPE_FAIRY && gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_BLACK_SALAD:
        if (gBattleMons[battlerDef].status1 & STATUS1_BLOOMING)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_OBJECT_D_ARC:
        if (gBattleMons[battlerAtk].species == SPECIES_NYARLY 
        && (gBattleMoves[move].type == TYPE_GHOST || gBattleMoves[move].type == TYPE_PSYCHIC || gBattleMoves[move].type == TYPE_DARK))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_ZIG_SASH:
        if (gBattleMons[battlerAtk].species == SPECIES_ZIGZAGOON && IS_MOVE_PHYSICAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        if (gBattleMons[battlerAtk].species == SPECIES_ZIGZAGOON && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(3.0));
        break;
    case HOLD_EFFECT_DOUGH_STICK:
        if ((atkBaseSpeciesId == SPECIES_KODOUGH || atkBaseSpeciesId == SPECIES_KODOUGH_BLUNT) && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.5));
        break;
    case HOLD_EFFECT_DEEP_SEA_TOOTH:
        if (gBattleMons[battlerAtk].species == SPECIES_CLAMPERL && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_KAMEN_SCARF:
        if (gBattleMons[battlerAtk].species == SPECIES_SHOCKORE && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_GEMSTONE:
        if (gBattleMons[battlerAtk].species == SPECIES_HARACE && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_CRYPTIC_PLATE:
        if (gBattleMons[battlerAtk].species == SPECIES_UHEFOE && IS_MOVE_SPECIAL(move))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_LIGHT_BALL:
        if (atkBaseSpeciesId == SPECIES_PIKACHU)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_WINTAMEL_TEA:
        if (atkBaseSpeciesId == SPECIES_POMELONIAN)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.5));
        break;
    case HOLD_EFFECT_CLEANSE_TAG:
        if ((CountBattlerStatDecreases(battlerDef, TRUE)) > 0)
            modifier = uq4_12_multiply_half_down(modifier, GetCleanseTagModifier(battlerDef));
        break;
    case HOLD_EFFECT_CHOICE_BAND:
        if (IS_MOVE_PHYSICAL(move) && atkAbility != ABILITY_ONE_WAY_TRIP)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_CHOICE_SPECS:
        if (IS_MOVE_SPECIAL(move) && atkAbility != ABILITY_ONE_WAY_TRIP)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_LEADERS_CREST:
        if ((atkBaseSpeciesId == SPECIES_PAWNIARD || atkBaseSpeciesId == SPECIES_BISHARP || atkBaseSpeciesId == SPECIES_KINGAMBIT) && (gBattleMoves[move].slicingMove))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.1));
        break;
    case HOLD_EFFECT_RAZOR_FANG:
        if ((atkBaseSpeciesId == SPECIES_GLIGAR || atkBaseSpeciesId == SPECIES_GLISCOR) && (gBattleMoves[move].bitingMove))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.1));
        break;
    }

    // The offensive stats of a Player's Pok?mon are boosted by x1.1 (+10%) if they have the 1st badge and 7th badges.
    // Having the 1st badge boosts physical attack while having the 7th badge boosts special attack.
    if (ShouldGetStatBadgeBoost(FLAG_BADGE01_GET, battlerAtk) && IS_MOVE_PHYSICAL(move))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.1));
    if (ShouldGetStatBadgeBoost(FLAG_BADGE07_GET, battlerAtk) && IS_MOVE_SPECIAL(move))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.1));

    return uq4_12_multiply_by_int_half_down(modifier, atkStat);
}

static bool32 CanEvolve(u32 species)
{
    u32 i;

    for (i = 0; i < EVOS_PER_MON; i++)
    {
        if (gEvolutionTable[species][i].method)
            return TRUE;
    }
    return FALSE;
}

static inline u32 CalcDefenseStat(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType, bool32 isCrit, bool32 updateFlags, u32 atkAbility, u32 defAbility, u32 holdEffectDef, u32 weather)
{
    bool32 usesDefStat;
    u8 defStage;
    u32 defStat, def, spDef;
    uq4_12_t modifier;
    u16 defBaseSpeciesId;

    defBaseSpeciesId = GET_BASE_SPECIES_ID(gBattleMons[battlerDef].species);

    def = gBattleMons[battlerDef].defense;
    spDef = gBattleMons[battlerDef].spDefense;

    if (gBattleMoves[move].effect == EFFECT_STRENGTH) // uses attack stat
    {
        defStat = gBattleMons[battlerDef].attack;
        defStage = gBattleMons[battlerDef].statStages[STAT_ATK];
        usesDefStat = FALSE;
    }
    else if (gBattleMoves[move].effect == EFFECT_PSYSHOCK || IS_MOVE_PHYSICAL(move)) // uses defense stat instead of sp.def
    {
        defStat = def;
        defStage = gBattleMons[battlerDef].statStages[STAT_DEF];
        usesDefStat = TRUE;
    }
    else if (gBattleMoves[move].effect == EFFECT_SOUL_CUTTER || (gBattleMoves[move].effect == EFFECT_PSYCHO_CUT && IsBattlerTerrainAffected(gBattlerAttacker, STATUS_FIELD_PSYCHIC_TERRAIN)) || IS_MOVE_SPECIAL(move)) // uses sp.def stat instead of defense
    {
        defStat = spDef;
        defStage = gBattleMons[battlerDef].statStages[STAT_SPDEF];
        usesDefStat = FALSE;
    }

    // Self-destruct / Explosion cut defense by 1/4
    if (gCurrentMove == MOVE_EXPLOSION || gCurrentMove == MOVE_SELF_DESTRUCT || gCurrentMove == MOVE_BLOW_UP
        || (gCurrentMove == MOVE_DOUBLE_SHOCK && (gStatuses4[gBattlerAttacker] & STATUS4_SUPERCHARGED) && (gStatuses4[gBattlerAttacker] & STATUS4_GEARED_UP)))
    {
        defStat *= 0.75;
    }

    if ((gCurrentMove == MOVE_CANNONADE) && (gBattleMons[gBattlerAttacker].hp <= (gBattleMons[gBattlerAttacker].maxHP / 4)))
    {
        defStat = spDef;
        defStage = gBattleMons[battlerDef].statStages[STAT_SPDEF];
        defStat *= 0.75;
    }

    if (gCurrentMove == MOVE_FINAL_SHRIEK || gCurrentMove == MOVE_JUMP_N_POP)
    {
        defStat = spDef;
        defStage = gBattleMons[battlerDef].statStages[STAT_SPDEF];
        defStat *= 0.75;
    }

    // freeze status cuts defense in half
    if (gBattleMons[battlerDef].status1 & STATUS1_FREEZE)
    {
        defStat /= 2;
    }

    if (gBattleMons[battlerDef].status1 & STATUS1_FREEZE)
    {
        defStat = spDef;
        defStage = gBattleMons[battlerDef].statStages[STAT_SPDEF];
        defStat *= 3;
    }

    if (gBattleMoves[gCurrentMove].effect == EFFECT_FUTURE_SIGHT && gCurrentMove != MOVE_DECIMATION)
    {
        defStat = spDef;
        defStat /= 2;
    }

    // critical hits ignore positive stat changes
    if (isCrit && defStage > DEFAULT_STAT_STAGE)
        defStage = DEFAULT_STAT_STAGE;
    // pokemon with unaware ignore defense stat changes while dealing damage
    if (atkAbility == ABILITY_UNAWARE || atkAbility == ABILITY_IGNORANT_BLISS)
        defStage = DEFAULT_STAT_STAGE;
    if (GetBattlerHoldEffect(battlerAtk, TRUE) == HOLD_EFFECT_WINTAMEL_TEA && gBattleMons[battlerAtk].species == SPECIES_POMELONIAN)
        defStage = DEFAULT_STAT_STAGE;
    //draco force make normal moves ignore stat changes
    if (defStage > DEFAULT_STAT_STAGE && atkAbility == ABILITY_DRACO_FORCE && gBattleStruct->dynamicMoveType == (TYPE_DRAGON | F_DYNAMIC_TYPE_2))
        defStage = DEFAULT_STAT_STAGE;
    // certain moves also ignore stat changes
    if (gCurrentMove == MOVE_RAZING_SUN && gDisableStructs[battlerAtk].daybreakCounter > 0)
        defStage = DEFAULT_STAT_STAGE;
    if (gBattleMoves[move].ignoresTargetDefenseEvasionStages)
        defStage = DEFAULT_STAT_STAGE;
    if (gCurrentMove == MOVE_BULLET_SEED && gBattleMons[gBattlerAttacker].status1 & STATUS1_BLOOMING)
        defStage = DEFAULT_STAT_STAGE;
    if (defStage > DEFAULT_STAT_STAGE && gCurrentMove == MOVE_AURA_SPHERE)
        defStage = DEFAULT_STAT_STAGE;

    defStat *= gStatStageRatios[defStage][0];
    defStat /= gStatStageRatios[defStage][1];

    // apply defense stat modifiers
    modifier = UQ_4_12(1.0);

    // target's abilities
    switch (defAbility)
    {
    case ABILITY_MARVEL_SCALE:
        if (gBattleMons[battlerDef].status1 & STATUS1_ANY_NEGATIVE && usesDefStat)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            if (updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_MARVEL_SCALE);
        }
        break;
    case ABILITY_WATER_VEIL:
        if (IsBattlerWeatherAffected(battlerDef, B_WEATHER_RAIN) && !usesDefStat)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            if (updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_WATER_VEIL);
        }
        break;
    case ABILITY_EXTREMO:
        if (gBattleMons[battlerDef].status1 & STATUS1_ANY_NEGATIVE)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            if (updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_EXTREMO);
        }
        break;
    case ABILITY_FUR_COAT:
        if (usesDefStat)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
            if (updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_FUR_COAT);
        }
        break;
    case ABILITY_GRASS_PELT:
        if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN && usesDefStat)
        {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.3));
            if (updateFlags)
                RecordAbilityBattle(battlerDef, ABILITY_GRASS_PELT);
        }
        break;
    case ABILITY_FLOWER_GIFT:
        if (IsBattlerWeatherAffected(battlerDef, B_WEATHER_SUN) && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case ABILITY_SHUNYONG:
        if (gBattleMons[battlerDef].species == SPECIES_SHUNYONG)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    case ABILITY_PURIFYING_SALT:
        if (gBattleMoves[move].type == TYPE_GHOST)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case ABILITY_GOLDEN_MEAN:
        if (gBattleMons[battlerDef].species == SPECIES_SHUNYONG_GOLDEN_OFFENSE)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        if (gBattleMons[battlerDef].species == SPECIES_SHUNYONG)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    }

    // ally's abilities
    if (IsBattlerAlive(BATTLE_PARTNER(battlerDef)))
    {
        switch (GetBattlerAbility(BATTLE_PARTNER(battlerDef)))
        {
        case ABILITY_FLOWER_GIFT:
            if (gBattleMons[BATTLE_PARTNER(battlerDef)].species == SPECIES_CHERRIM_SUNSHINE && IsBattlerWeatherAffected(BATTLE_PARTNER(battlerDef), B_WEATHER_SUN) && !usesDefStat)
                modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
            break;
        }
    }

    // field abilities
    if (IsAbilityOnField(ABILITY_SWORD_OF_RUIN) && defAbility != ABILITY_SWORD_OF_RUIN && usesDefStat)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    if (IsAbilityOnField(ABILITY_BEADS_OF_RUIN) && defAbility != ABILITY_BEADS_OF_RUIN && !usesDefStat)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));

    // target's hold effects
    switch (holdEffectDef)
    {
    case HOLD_EFFECT_DEEP_SEA_SCALE:
        if (gBattleMons[battlerDef].species == SPECIES_CLAMPERL && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_SHELL_POLISH:
        if (gBattleMons[battlerDef].species == SPECIES_SNELFREND)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.5));
        break;
    case HOLD_EFFECT_TERU_CHARM:
        if (gBattleMons[battlerDef].species == SPECIES_CHIROBERRA)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.3));
        break;
    case HOLD_EFFECT_WINTAMEL_TEA:
        if (gBattleMons[battlerDef].species == SPECIES_POMELONIAN)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.5));
        break;
    case HOLD_EFFECT_SALTY_TEAR:
        if (gBattleMons[battlerDef].species == SPECIES_SADSOD)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.5));
        break;
    case HOLD_EFFECT_FRIEND_RIBBON:
        if (gBattleMons[battlerDef].species == SPECIES_COLFIN && usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_FAVOR_SCARF:
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.1));
        break;
    case HOLD_EFFECT_DOUGH_STICK:
        if (defBaseSpeciesId == SPECIES_KODOUGH || defBaseSpeciesId == SPECIES_KODOUGH_BLUNT)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.5));
        break;
    case HOLD_EFFECT_METAL_POWDER:
        if (gBattleMons[battlerDef].species == SPECIES_DITTO && usesDefStat && !(gBattleMons[battlerDef].status2 & STATUS2_TRANSFORMED))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(2.0));
        break;
    case HOLD_EFFECT_EVIOLITE:
        if (CanEvolve(gBattleMons[battlerDef].species))
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_ASSAULT_VEST:
        if (!usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
    case HOLD_EFFECT_SPECTRAL_IDOL:
        if (gBattleMons[battlerAtk].status1 & STATUS1_PANIC)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.15));
        break;
    case HOLD_EFFECT_BATTLE_HELM:
        if (usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
#if B_SOUL_DEW_BOOST <= GEN_6
    case HOLD_EFFECT_SOUL_DEW:
        if ((gBattleMons[battlerDef].species == SPECIES_LATIAS || gBattleMons[battlerDef].species == SPECIES_LATIOS) && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER) && !usesDefStat)
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
        break;
#endif
    case HOLD_EFFECT_RING_TARGET:
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(0.75));
        break;
    case HOLD_EFFECT_HARD_STONE:
        if (gProtectStructs[battlerDef].hardStoneBoost) {
            modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.2));
        }
        break;
    }

    // sandstorm sp.def boost for rock types
    if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_ROCK) && weather & B_WEATHER_SANDSTORM && !usesDefStat && holdEffectDef != HOLD_EFFECT_UTILITY_UMBRELLA)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));
    // snow def boost for ice types
    if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_ICE) && weather & B_WEATHER_HAIL && usesDefStat && holdEffectDef != HOLD_EFFECT_UTILITY_UMBRELLA)
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.5));

    // The defensive stats of a Player's Pok?mon are boosted by x1.1 (+10%) if they have the 5th badge and 7th badges.
    // Having the 5th badge boosts physical defense while having the 7th badge boosts special defense.
    if (ShouldGetStatBadgeBoost(FLAG_BADGE05_GET, battlerDef) && IS_MOVE_PHYSICAL(move))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.1));
    if (ShouldGetStatBadgeBoost(FLAG_BADGE07_GET, battlerDef) && IS_MOVE_SPECIAL(move))
        modifier = uq4_12_multiply_half_down(modifier, UQ_4_12(1.1));

    return uq4_12_multiply_by_int_half_down(modifier, defStat);
}

// base damage formula before adding any modifiers
static inline s32 CalculateBaseDamage(u32 power, u32 userFinalAttack, u32 level, u32 targetFinalDefense)
{
    return power * userFinalAttack * (2 * level / 5 + 2) / targetFinalDefense / 50 + 2;
}

#if B_MULTIPLE_TARGETS_DMG >= GEN_4
#define V_MULTIPLE_TARGETS_DMG UQ_4_12(0.75)
#else
#define V_MULTIPLE_TARGETS_DMG UQ_4_12(0.5)
#endif

#if B_CRIT_MULTIPLIER >= GEN_6
#define V_CRIT_MULTIPLIER UQ_4_12(1.5)
#else
#define V_CRIT_MULTIPLIER UQ_4_12(2.0)
#endif

#if B_BURN_FACADE_DMG >= GEN_6
#define FACADE_PREVENTS_BURN_MALUS(move) (gBattleMoves[move].effect == EFFECT_FACADE)
#else
#define FACADE_PREVENTS_BURN_MALUS(move) (FALSE)
#endif

#if B_PARENTAL_BOND_DMG < GEN_7
#define V_PARENTAL_BOND_DMG UQ_4_12(0.5)
#else
#define V_PARENTAL_BOND_DMG UQ_4_12(0.25)
#endif

static inline uq4_12_t GetTargetDamageModifier(u32 move, u32 battlerAtk, u32 battlerDef)
{
    u32 holdEffectDef = GetBattlerHoldEffect(battlerDef, TRUE);

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && GetMoveTargetCount(move, battlerAtk, battlerDef) >= 2)
    {
        if (holdEffectDef == HOLD_EFFECT_WIDE_ARMOR
        && GetBattlerAbility(battlerDef) == ABILITY_TELEPATHY
        && IsMoveMultipleTargetAndDamages(move, battlerAtk))
        {
            return UQ_4_12(0.25);
        }
        else if ((GetBattlerAbility(battlerDef) == ABILITY_TELEPATHY
        || holdEffectDef == HOLD_EFFECT_WIDE_ARMOR)
        && IsMoveMultipleTargetAndDamages(move, battlerAtk))
        {
            return UQ_4_12(0.5);
        }
        else
        {
            return V_MULTIPLE_TARGETS_DMG;
        }
    }
    else
    {
        return UQ_4_12(1.0);
    }
}

static inline uq4_12_t GetParentalBondModifier(u32 battlerAtk)
{
    if (gSpecialStatuses[battlerAtk].parentalBondState != PARENTAL_BOND_2ND_HIT || GetBattlerAbility(battlerAtk) == ABILITY_RAPID_FIRE)
        return UQ_4_12(1.0);
    return V_PARENTAL_BOND_DMG;
}

static inline uq4_12_t GetSameTypeAttackBonusModifier(u32 battlerAtk, u32 moveType, u32 move, u32 abilityAtk)
{
    if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_NORMAL) && moveType == TYPE_NORMAL)
        return (abilityAtk == ABILITY_ADAPTABILITY) ? UQ_4_12(2.0) : UQ_4_12(1.5);
    else if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_NORMAL) && moveType != TYPE_NORMAL && (gFieldStatuses & STATUS_FIELD_WONDER_ROOM))
        return (abilityAtk == ABILITY_ADAPTABILITY) ? UQ_4_12(2.0) : UQ_4_12(1.5);
    else if (IS_BATTLER_OF_TYPE(battlerAtk, moveType) && gFieldStatuses & STATUS_FIELD_WONDER_ROOM)
        return UQ_4_12(1.0);
    else if (!IS_BATTLER_OF_TYPE(battlerAtk, moveType) && gFieldStatuses & STATUS_FIELD_WONDER_ROOM)
        return (abilityAtk == ABILITY_ADAPTABILITY) ? UQ_4_12(1.5) : UQ_4_12(1.25);
    else if (!IS_BATTLER_OF_TYPE(battlerAtk, moveType) || move == MOVE_STRUGGLE || move == MOVE_NONE)
        return UQ_4_12(1.0);
    return (abilityAtk == ABILITY_ADAPTABILITY) ? UQ_4_12(1.5) : UQ_4_12(1.25);
}

// Utility Umbrella holders take normal damage from what would be rain- and sun-weakened attacks.
static uq4_12_t GetWeatherDamageModifier(u32 battlerAtk, u32 move, u32 moveType, u32 holdEffectAtk, u32 holdEffectDef, u32 weather)
{
    if (weather == B_WEATHER_NONE)
        return UQ_4_12(1.0);
    if (gBattleMoves[move].effect == EFFECT_HYDRO_STEAM && (weather & B_WEATHER_SUN))
        return UQ_4_12(1.5);
    if (holdEffectDef == HOLD_EFFECT_UTILITY_UMBRELLA && ((weather & B_WEATHER_SUN) || (weather & B_WEATHER_SUN_PRIMAL)) && (moveType == TYPE_FIRE))
        return UQ_4_12(0.5);
    if (holdEffectDef == HOLD_EFFECT_UTILITY_UMBRELLA && ((weather & B_WEATHER_RAIN) || (weather & B_WEATHER_RAIN_PRIMAL)) && (moveType == TYPE_WATER))
        return UQ_4_12(0.5);
    if (holdEffectDef == HOLD_EFFECT_UTILITY_UMBRELLA && (weather & B_WEATHER_HAIL) && (moveType == TYPE_ICE))
        return UQ_4_12(0.5);
    if (holdEffectDef == HOLD_EFFECT_UTILITY_UMBRELLA && (weather & B_WEATHER_SANDSTORM) && (moveType == TYPE_ROCK))
        return UQ_4_12(0.5);
    if (holdEffectAtk == HOLD_EFFECT_UTILITY_UMBRELLA)
        return UQ_4_12(1.0);

    if (weather & B_WEATHER_RAIN)
    {
        if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_WATER) && moveType == TYPE_WATER)
            return UQ_4_12(1.35);
        else if (moveType == TYPE_WATER)
            return UQ_4_12(1.2);
        else if (moveType == TYPE_FIRE)
            return UQ_4_12(0.5);
    }
    if (weather & B_WEATHER_SUN)
    {
        if (moveType == TYPE_GRASS && GetBattlerAbility(battlerAtk) == ABILITY_CHLOROPHYLL)
            return UQ_4_12(1.5);
        else if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_FIRE) && moveType == TYPE_FIRE)
            return UQ_4_12(1.35);
        else if (moveType == TYPE_FIRE)
            return UQ_4_12(1.2);
        else if (moveType == TYPE_WATER)
            return UQ_4_12(0.5);
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetBurnOrFrostBiteOrPanicModifier(u32 battlerAtk, u32 move, u32 abilityAtk)
{
    if (gBattleMons[battlerAtk].status1 & STATUS1_BURN && IS_MOVE_PHYSICAL(move) && !FACADE_PREVENTS_BURN_MALUS(move) && abilityAtk != ABILITY_GUTS)
        return UQ_4_12(0.5);
    if (gBattleMons[battlerAtk].status1 & STATUS1_FROSTBITE && IS_MOVE_SPECIAL(move) && !FACADE_PREVENTS_BURN_MALUS(move) && abilityAtk != ABILITY_GUTS)
        return UQ_4_12(0.5);
    if (gBattleMons[battlerAtk].status1 & STATUS1_PANIC
        && abilityAtk != ABILITY_GUTS
        && !FACADE_PREVENTS_BURN_MALUS(move))
        return UQ_4_12(0.8);
    if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING 
        && (move == MOVE_MEGA_DRAIN))
        return UQ_4_12(2.0);
    if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING
        && (move == MOVE_RAZOR_LEAF
        || move == MOVE_ABSORB))
        return UQ_4_12(1.5);
    if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING
        && (move == MOVE_SOLAR_BEAM
        || move == MOVE_SOLAR_BLADE
        || move == MOVE_CHLOROBLAST))
        return UQ_4_12(1.2);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetCriticalModifier(bool32 isCrit, u32 battlerAtk)
{
    if (isCrit)
    {
        if (GetBattlerAbility(battlerAtk) == ABILITY_PRODIGY)
            return UQ_4_12(2.0);
        else
            return UQ_4_12(1.5);
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetGlaiveRushModifier(u32 battlerDef)
{
    if (gStatuses4[battlerDef] & STATUS4_GLAIVE_RUSH)
        return UQ_4_12(2.0);
    if (gStatuses4[battlerDef] & STATUS4_GLAIVE_RUSH_2)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetRechargeReduceModifier(u32 battlerDef)
{
    if (gStatuses4[battlerDef] & STATUS4_RECHARGE_REDUCE)
        return UQ_4_12(0.5);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetLuckyChantModifier(u32 abilityAtk, u32 battlerAtk, u32 battlerDef, uq4_12_t typeEffectivenessModifier)
{
    if ((gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_LUCKY_CHANT) 
    && (typeEffectivenessModifier >= UQ_4_12(2.0))
    && (abilityAtk != ABILITY_INFILTRATOR)
    && !(IS_BATTLER_OF_TYPE(battlerAtk, TYPE_BUG)))
        return UQ_4_12(0.7);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetTargetStatusDamageModifier(u32 battlerDef)
{
    if (gBattleMons[battlerDef].status1 & STATUS1_EXPOSED)
        return UQ_4_12(1.5);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetZMoveAgainstProtectionModifier(u32 battlerDef)
{
    if (gBattleStruct->zmove.active && IS_BATTLER_PROTECTED(battlerDef))
        return UQ_4_12(0.25);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetMinimizeModifier(u32 move, u32 battlerDef)
{
    if (gBattleMoves[move].minimizeDoubleDamage && gStatuses3[battlerDef] & STATUS3_MINIMIZED)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetUndergroundModifier(u32 move, u32 battlerDef)
{
    if (gBattleMoves[move].damagesUnderground && gStatuses3[battlerDef] & STATUS3_UNDERGROUND)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDiveModifier(u32 move, u32 battlerDef)
{
    if (gBattleMoves[move].damagesUnderwater && gStatuses3[battlerDef] & STATUS3_UNDERWATER)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetFrenzyAttackerModifier(u32 battlerAtk, bool32 isCrit)
{
    if (isCrit)
    {
        if (gDisableStructs[battlerAtk].frenzyCounter > 2)
            return UQ_4_12(1.9);
        else if (gDisableStructs[battlerAtk].frenzyCounter > 1)
            return UQ_4_12(1.6);
        else if (gDisableStructs[battlerAtk].frenzyCounter > 0)
            return UQ_4_12(1.3);
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetFocusEnergyAttackModifier(u32 battlerAtk, bool32 isCrit)
{
    if (isCrit && gDisableStructs[battlerAtk].focusEnergy)
        return UQ_4_12(1.2);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetFrenzyDefenderModifier(u32 battlerDef)
{
    if (gDisableStructs[battlerDef].frenzyCounter > 2)
        return UQ_4_12(1.6);
    else if (gDisableStructs[battlerDef].frenzyCounter > 1)
        return UQ_4_12(1.4);
    else if (gDisableStructs[battlerDef].frenzyCounter > 0)
        return UQ_4_12(1.2);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetExhaustionAttackerModifier(u32 battlerAtk)
{
    if (gDisableStructs[battlerAtk].exhaustionCounter > 2)
        return UQ_4_12(0.25);
    else if (gDisableStructs[battlerAtk].exhaustionCounter > 1)
        return UQ_4_12(0.5);
    else if (gDisableStructs[battlerAtk].exhaustionCounter > 0)
        return UQ_4_12(0.75);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDaybreakAttackerModifier(u32 battlerAtk)
{
    if (gDisableStructs[battlerAtk].daybreakCounter > 2)
        return UQ_4_12(1.45);
    else if (gDisableStructs[battlerAtk].daybreakCounter > 1)
        return UQ_4_12(1.3);
    else if (gDisableStructs[battlerAtk].daybreakCounter > 0)
        return UQ_4_12(1.15);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDaybreakDefenderModifier(u32 battlerDef)
{
    if (gDisableStructs[battlerDef].daybreakCounter > 2)
        return UQ_4_12(0.25);
    else if (gDisableStructs[battlerDef].daybreakCounter > 1)
        return UQ_4_12(0.5);
    else if (gDisableStructs[battlerDef].daybreakCounter > 0)
        return UQ_4_12(0.75);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetInfatuationDefenderModifier(u32 battlerDef)
{
    if (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION && gBattleMons[battlerDef].species != SPECIES_YANDEMIC && gBattleMons[battlerDef].ability != ABILITY_LOVESICK)
        return UQ_4_12(1.25);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetInfatuationAttackerModifier(u32 battlerAtk)
{
    if (gBattleMons[battlerAtk].status2 & STATUS2_INFATUATION && gBattleMons[battlerAtk].species != SPECIES_YANDEMIC && gBattleMons[battlerAtk].ability != ABILITY_LOVESICK)
        return UQ_4_12(0.75);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAirborneModifier(u32 move, u32 battlerDef)
{
    if (gBattleMoves[move].damagesAirborneDoubleDamage && gStatuses3[battlerDef] & STATUS3_ON_AIR)
        return UQ_4_12(2.0);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetScreensModifier(u32 move, u32 battlerAtk, u32 battlerDef, bool32 isCrit, u32 abilityAtk)
{
    u32 sideStatus = gSideStatuses[GetBattlerSide(battlerDef)];
    u32 sideStatusAtk = gSideStatuses[GetBattlerSide(battlerAtk)];
    bool32 lightScreen = (sideStatus & SIDE_STATUS_LIGHTSCREEN) && IS_MOVE_SPECIAL(move);
    bool32 reflect = (sideStatus & SIDE_STATUS_REFLECT) && IS_MOVE_PHYSICAL(move);
    bool32 auroraVeil = sideStatus & SIDE_STATUS_AURORA_VEIL;
    bool32 googooScreenDef = sideStatus & SIDE_STATUS_GOOGOO_SCREEN;
    bool32 googooScreenAtk = sideStatusAtk & SIDE_STATUS_GOOGOO_SCREEN;

    if (googooScreenAtk)
        return UQ_4_12(1.3);
    if (isCrit || abilityAtk == ABILITY_INFILTRATOR || IS_BATTLER_OF_TYPE(battlerAtk, TYPE_BUG) || gProtectStructs[battlerAtk].confusionSelfDmg)
        return UQ_4_12(1.0);
    if (googooScreenDef)
        return (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) ? UQ_4_12(0.7) : UQ_4_12(0.7);
    if (reflect || lightScreen || auroraVeil)
        return (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) ? UQ_4_12(0.667) : UQ_4_12(0.5);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetCollisionCourseElectroDriftModifier(u32 move, uq4_12_t typeEffectivenessModifier)
{
    if ((gBattleMoves[move].effect == EFFECT_COLLISION_COURSE) && typeEffectivenessModifier >= UQ_4_12(2.0))
        return UQ_4_12(1.3333);
    if ((gBattleMoves[move].effect == EFFECT_GIANTS_SPEAR) && typeEffectivenessModifier >= UQ_4_12(2.0))
        return UQ_4_12(1.3333);
    if ((gCurrentMove == MOVE_RAILGUN) && typeEffectivenessModifier >= UQ_4_12(2.0))
        return UQ_4_12(1.3333);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetPoisonTailModifier(u32 move, bool32 isCrit)
{
    if (gBattleMoves[move].effect == EFFECT_POISON_TAIL && isCrit)
        return UQ_4_12(1.5);
    return UQ_4_12(1.0);
}
static inline uq4_12_t GetBenthicWhipModifier(u32 move, uq4_12_t typeEffectivenessModifier)
{
    if (gCurrentMove == MOVE_BENTHIC_WHIP && (typeEffectivenessModifier < UQ_4_12(1.0)))
        return UQ_4_12(2.5);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetFightingTypeModifier(u32 battlerAtk, u32 move, uq4_12_t typeEffectivenessModifier)
{
    if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_FIGHTING) && typeEffectivenessModifier > UQ_4_12(3.0))
        return UQ_4_12(1.3);
    else if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_FIGHTING) && typeEffectivenessModifier > UQ_4_12(2.0))
        return UQ_4_12(1.2);
    else if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_FIGHTING) && typeEffectivenessModifier > UQ_4_12(1.0))
        return UQ_4_12(1.1);
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAttackerAbilitiesModifier(u32 battlerAtk, uq4_12_t typeEffectivenessModifier, bool32 isCrit, u32 abilityAtk)
{
    switch (abilityAtk)
    {
    case ABILITY_NEUROFORCE:
        if (typeEffectivenessModifier >= UQ_4_12(2.0))
            return UQ_4_12(1.25);
        break;
    case ABILITY_SNIPER:
        if (isCrit)
            return UQ_4_12(1.5);
        break;
    case ABILITY_TINTED_LENS:
        if (typeEffectivenessModifier <= UQ_4_12(0.5))
            return UQ_4_12(2.0);
        break;
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDefenderAbilitiesModifier(u32 move, u32 moveType, u32 battlerAtk, u32 battlerDef, uq4_12_t typeEffectivenessModifier, u32 abilityDef)
{
    switch (abilityDef)
    {
    case ABILITY_MULTISCALE:
    case ABILITY_SUGAR_COAT:
    case ABILITY_SHADOW_SHIELD:
        if (BATTLER_MAX_HP(battlerDef))
            return UQ_4_12(0.5);
        break;
    case ABILITY_BATTLE_ARMOR:
        if (typeEffectivenessModifier <= UQ_4_12(1.0))
            return UQ_4_12(0.75);
        break;
    case ABILITY_FILTER:
    case ABILITY_SOLID_ROCK:
    case ABILITY_PRISM_ARMOR:
        if (typeEffectivenessModifier >= UQ_4_12(2.0))
            return UQ_4_12(0.75);
        break;
    case ABILITY_STRONGHOLD:
        if (CountBattlerDefenseIncreases(battlerDef) > 0)
            return GetStrongholdDefenseModifier(battlerDef);
        break;
    case ABILITY_ICE_SCALES:
        if (gDisableStructs[battlerDef].iceScalesCounter > 4)
            return UQ_4_12(0.5);
        else if (gDisableStructs[battlerDef].iceScalesCounter > 3)
            return UQ_4_12(0.6);
        else if (gDisableStructs[battlerDef].iceScalesCounter > 2)
            return UQ_4_12(0.7);
        else if (gDisableStructs[battlerDef].iceScalesCounter > 1)
            return UQ_4_12(0.8);
        else if (gDisableStructs[battlerDef].iceScalesCounter > 0)
            return UQ_4_12(0.9);
        break;
    case ABILITY_FLUFFY:
        if (!IsMoveMakingContact(move, battlerAtk) && moveType == TYPE_FIRE)
            return UQ_4_12(2.0);
        if (IsMoveMakingContact(move, battlerAtk) && moveType != TYPE_FIRE)
            return UQ_4_12(0.5);
        break;
    case ABILITY_BULLETPROOF:
        if (!(IsMoveMakingContact(move, battlerAtk)))
            return UQ_4_12(0.8);
        break;
    case ABILITY_MAGMA_ARMOR:
        if ((!(gDisableStructs[battlerDef].magmaArmored)) && moveType == TYPE_WATER)
            return UQ_4_12(0.1);
        else if (gDisableStructs[battlerDef].magmaArmored)
            return UQ_4_12(2 / 3);
        break;
    case ABILITY_PURPLE_HAZE:
        if (gDisableStructs[battlerDef].purpleHazeDefense)
            return UQ_4_12(0.5);
        break;
    case ABILITY_CACOPHONY:
    case ABILITY_PUNK_ROCK:
        if (gBattleMoves[move].soundMove)
            return UQ_4_12(0.5);
        break;
    case ABILITY_HIBERNAL:
        if (moveType == TYPE_ICE)
            return UQ_4_12(0.5);
        break;
    case ABILITY_STALL:
        return UQ_4_12(0.75);
        break;
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDefenderPartnerAbilitiesModifier(u32 battlerPartnerDef, u32 moveType)
{
    u32 battlerDef = BATTLE_PARTNER(battlerPartnerDef);
    if (!IsBattlerAlive(battlerPartnerDef))
        return UQ_4_12(1.0);

    switch (GetBattlerAbility(battlerPartnerDef))
    {
    case ABILITY_FRIEND_GUARD:
        return UQ_4_12(0.75);
        break;
    case ABILITY_CACOPHONY:
        if (gBattleMoves[gCurrentMove].soundMove)
            return UQ_4_12(0.5);
        break;
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetAttackerItemsModifier(u32 battlerAtk, uq4_12_t typeEffectivenessModifier, u32 holdEffectAtk)
{
    u32 metronomeTurns;
    uq4_12_t metronomeBoostBase;
    switch (holdEffectAtk)
    {
    case HOLD_EFFECT_METRONOME:
        metronomeBoostBase = PercentToUQ4_12(GetBattlerHoldEffectParam(battlerAtk));
        metronomeTurns = min(gBattleStruct->sameMoveTurns[battlerAtk], 5);
        return uq4_12_add(UQ_4_12(1.0), metronomeBoostBase * metronomeTurns);
        break;
    case HOLD_EFFECT_ODD_STONE:
        metronomeBoostBase = PercentToUQ4_12(GetBattlerHoldEffectParam(battlerAtk));
        metronomeTurns = min(gBattleStruct->sameMoveTurns[battlerAtk], 5);
        if (gBattleMoves[gCurrentMove].soundMove)
            return uq4_12_add(UQ_4_12(1.0), metronomeBoostBase * metronomeTurns);
        break;
    case HOLD_EFFECT_EXPERT_BELT:
        if (typeEffectivenessModifier >= UQ_4_12(2.0))
            return UQ_4_12(1.3);
        break;
    case HOLD_EFFECT_DISTILL_MOD:
        if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_RELIC) && typeEffectivenessModifier >= UQ_4_12(2.0))
            return UQ_4_12(1.5);
        if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_RELIC) && typeEffectivenessModifier <= UQ_4_12(0.5))
            return UQ_4_12(0.75);
        break;
    case HOLD_EFFECT_LIFE_ORB:
        return UQ_4_12_FLOORED(1.3);
        break;
    case HOLD_EFFECT_BLACK_BELT:
        { // +20% if super effective fighting move
            u8 moveType;
            GET_MOVE_TYPE(gCurrentMove, moveType);
            if (moveType == TYPE_FIGHTING && typeEffectivenessModifier >= UQ_4_12(2.0))
                return UQ_4_12(1.2);
        }
        break;
    case HOLD_EFFECT_DRAGON_FANG:
        { // +40% if not very effective dragon move
            u8 moveType;
            GET_MOVE_TYPE(gCurrentMove, moveType);
            if (moveType == TYPE_DRAGON && typeEffectivenessModifier < UQ_4_12(1.0))
                return UQ_4_12(1.4);
        }
        break;
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDefenderItemsModifier(u32 move, u32 moveType, u32 battlerDef, uq4_12_t typeEffectivenessModifier, bool32 updateFlags, u32 abilityDef, u32 holdEffectDef)
{
    u32 holdEffectDefParam = GetBattlerHoldEffectParam(battlerDef);
    u32 itemDef = gBattleMons[battlerDef].item;
    u32 basePower = gBattleMoves[move].power;

    switch (holdEffectDef)
    {
    case HOLD_EFFECT_RESIST_BERRY:
        if (UnnerveOn(battlerDef, itemDef))
            return UQ_4_12(1.0);
        if (moveType == holdEffectDefParam && (moveType == TYPE_NORMAL || typeEffectivenessModifier >= UQ_4_12(2.0)))
        {
            if (updateFlags)
                gSpecialStatuses[battlerDef].berryReduced = TRUE;
            return (abilityDef == ABILITY_RIPEN) ? UQ_4_12(0.25) : UQ_4_12(0.5);
        }
        break;
    case HOLD_EFFECT_MAGOST_BERRY:
        if (UnnerveOn(battlerDef, itemDef))
            return UQ_4_12(1.0);
        if (itemDef == ITEM_MAGOST_BERRY)
        {
            if (updateFlags)
                gSpecialStatuses[battlerDef].berryReduced = TRUE;
            return (abilityDef == ABILITY_RIPEN) ? UQ_4_12(0.5) : UQ_4_12(0.75);
        }
        break;
    case HOLD_EFFECT_ENIGMA_BERRY:
        if (UnnerveOn(battlerDef, itemDef))
            return UQ_4_12(1.0);
        if (itemDef == ITEM_ENIGMA_BERRY)
        {
            if (updateFlags)
                gSpecialStatuses[battlerDef].berryReduced = TRUE;
            return (abilityDef == ABILITY_RIPEN) ? UQ_4_12(0.15) : UQ_4_12(0.25);
        }
        break;
    case HOLD_EFFECT_DILATANT_MOD:
        if ((basePower >= 90) && IS_BATTLER_OF_TYPE(battlerDef, TYPE_RELIC))
            return UQ_4_12(0.75);
        break;
    case HOLD_EFFECT_KAMEN_SCARF:
        if (gBattleMons[battlerDef].species == SPECIES_SHOCKORE && typeEffectivenessModifier >= UQ_4_12(2.0))
            return UQ_4_12(0.5);
    }
    return UQ_4_12(1.0);
}

static inline uq4_12_t GetDefenderPartnerItemsModifier(u32 battlerPartnerDef)
{
    if (!IsBattlerAlive(battlerPartnerDef))
        return UQ_4_12(1.0);

    switch (GetBattlerHoldEffect(battlerPartnerDef, TRUE))
    {
    case HOLD_EFFECT_SHELL_POLISH:
        if (battlerPartnerDef == SPECIES_SNELFREND)
        {
            return UQ_4_12(0.75);
        }
        break;
    case HOLD_EFFECT_FAMILY_MOSS:
        if (battlerPartnerDef == SPECIES_PAPYPUS || battlerPartnerDef == SPECIES_PAPYPUS_FEMALE)
        {
            return UQ_4_12(0.75);
        }
        break;
    }
    return UQ_4_12(1.0);
}

#define DAMAGE_MULTIPLY_MODIFIER(modifier)                                  \
    do                                                                      \
    {                                                                       \
        finalModifier = uq4_12_multiply_half_down(modifier, finalModifier); \
    } while (0)

// Calculates the "other" modifier which accounts for held items, abilities,
// or very specific interactions of moves that are not handled in the basic
// damage calculation. It is implemented as described by bulbapedia:
// https://bulbapedia.bulbagarden.net/wiki/Damage#Generation_V_onward
// Please Note: Fixed Point Multiplication is not associative.
// The order of operations is relevant.
static inline uq4_12_t GetOtherModifiers(u32 move, u32 moveType, u32 battlerAtk, u32 battlerDef, bool32 isCrit, uq4_12_t typeEffectivenessModifier, bool32 updateFlags,
                                         u32 abilityAtk, u32 abilityDef, u32 holdEffectAtk, u32 holdEffectDef)
{
    uq4_12_t finalModifier = UQ_4_12(1.0);
    u32 battlerDefPartner = BATTLE_PARTNER(battlerDef);
    u32 unmodifiedAttackerSpeed = gBattleMons[battlerAtk].speed;
    u32 unmodifiedDefenderSpeed = gBattleMons[battlerDef].speed;
    // TODO: Behemoth Blade, Behemoth Bash, Dynamax Cannon (Dynamax)
    DAMAGE_MULTIPLY_MODIFIER(GetMinimizeModifier(move, battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetUndergroundModifier(move, battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetDiveModifier(move, battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetInfatuationDefenderModifier(battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetInfatuationAttackerModifier(battlerAtk));
    DAMAGE_MULTIPLY_MODIFIER(GetExhaustionAttackerModifier(battlerAtk));
    DAMAGE_MULTIPLY_MODIFIER(GetFrenzyDefenderModifier(battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetFrenzyAttackerModifier(battlerAtk, isCrit));
    DAMAGE_MULTIPLY_MODIFIER(GetFocusEnergyAttackModifier(battlerAtk, isCrit));
    DAMAGE_MULTIPLY_MODIFIER(GetDaybreakDefenderModifier(battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetDaybreakAttackerModifier(battlerAtk));
    DAMAGE_MULTIPLY_MODIFIER(GetAirborneModifier(move, battlerDef));
    DAMAGE_MULTIPLY_MODIFIER(GetScreensModifier(move, battlerAtk, battlerDef, isCrit, abilityAtk));
    DAMAGE_MULTIPLY_MODIFIER(GetCollisionCourseElectroDriftModifier(move, typeEffectivenessModifier));
    DAMAGE_MULTIPLY_MODIFIER(GetPoisonTailModifier(move, isCrit));
    DAMAGE_MULTIPLY_MODIFIER(GetBenthicWhipModifier(move, typeEffectivenessModifier));
    DAMAGE_MULTIPLY_MODIFIER(GetFightingTypeModifier(battlerAtk, move, typeEffectivenessModifier));

    if (unmodifiedAttackerSpeed >= unmodifiedDefenderSpeed)
    {
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerAbilitiesModifier(battlerAtk, typeEffectivenessModifier, isCrit, abilityAtk));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderAbilitiesModifier(move, moveType, battlerAtk, battlerDef, typeEffectivenessModifier, abilityDef));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderPartnerAbilitiesModifier(battlerDefPartner, moveType));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderPartnerItemsModifier(battlerDefPartner));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerItemsModifier(battlerAtk, typeEffectivenessModifier, holdEffectAtk));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderItemsModifier(move, moveType, battlerDef, typeEffectivenessModifier, updateFlags, abilityDef, holdEffectDef));
    }
    else
    {
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderAbilitiesModifier(move, moveType, battlerAtk, battlerDef, typeEffectivenessModifier, abilityDef));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderPartnerAbilitiesModifier(battlerDefPartner, moveType));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderPartnerItemsModifier(battlerDefPartner));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerAbilitiesModifier(battlerAtk, typeEffectivenessModifier, isCrit, abilityAtk));
        DAMAGE_MULTIPLY_MODIFIER(GetDefenderItemsModifier(move, moveType, battlerDef, typeEffectivenessModifier, updateFlags, abilityDef, holdEffectDef));
        DAMAGE_MULTIPLY_MODIFIER(GetAttackerItemsModifier(battlerAtk, typeEffectivenessModifier, holdEffectAtk));
    }
    return finalModifier;
}

#undef DAMAGE_ACCUMULATE_MULTIPLIER

#define DAMAGE_APPLY_MODIFIER(modifier)                        \
    do                                                         \
    {                                                          \
        dmg = uq4_12_multiply_by_int_half_down(modifier, dmg); \
    } while (0)

static inline s32 DoMoveDamageCalcVars(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType, s32 fixedBasePower,
                                       bool32 isCrit, bool32 randomFactor, bool32 updateFlags, uq4_12_t typeEffectivenessModifier, u32 weather,
                                       u32 holdEffectAtk, u32 holdEffectDef, u32 abilityAtk, u32 abilityDef)
{
    s32 dmg;
    u32 userFinalAttack;
    u32 targetFinalDefense;
    u32 defCompare = gBattleMons[battlerAtk].attack - gBattleMons[battlerDef].defense;
    u32 atkCompare = gBattleMons[battlerAtk].attack - gBattleMons[battlerDef].attack;
    u32 uniqueDamage;
    u32 defAbility = GetBattlerAbility(battlerDef);

    if (fixedBasePower)
        gBattleMovePower = fixedBasePower;
    else
        gBattleMovePower = CalcMoveBasePowerAfterModifiers(move, battlerAtk, battlerDef, moveType, updateFlags, abilityAtk, abilityDef, holdEffectAtk, weather);

    userFinalAttack = CalcAttackStat(move, battlerAtk, battlerDef, moveType, isCrit, updateFlags, abilityAtk, abilityDef, holdEffectAtk);
    targetFinalDefense = CalcDefenseStat(move, battlerAtk, battlerDef, moveType, isCrit, updateFlags, abilityAtk, abilityDef, holdEffectDef, weather);

    dmg = CalculateBaseDamage(gBattleMovePower, userFinalAttack, gBattleMons[battlerAtk].level, targetFinalDefense);
    DAMAGE_APPLY_MODIFIER(GetTargetDamageModifier(move, battlerAtk, battlerDef));
    DAMAGE_APPLY_MODIFIER(GetParentalBondModifier(battlerAtk));
    DAMAGE_APPLY_MODIFIER(GetWeatherDamageModifier(battlerAtk, move, moveType, holdEffectAtk, holdEffectDef, weather));
    DAMAGE_APPLY_MODIFIER(GetCriticalModifier(isCrit, battlerAtk));
    DAMAGE_APPLY_MODIFIER(GetGlaiveRushModifier(battlerDef));
    DAMAGE_APPLY_MODIFIER(GetRechargeReduceModifier(battlerDef));
    DAMAGE_APPLY_MODIFIER(GetLuckyChantModifier(abilityAtk, battlerAtk, battlerDef, typeEffectivenessModifier));
    DAMAGE_APPLY_MODIFIER(GetTargetStatusDamageModifier(battlerDef));

    if (randomFactor)
    {
        dmg *= 100 - RandomUniform(RNG_DAMAGE_MODIFIER, 0, 15);
        dmg /= 100;
    }

    DAMAGE_APPLY_MODIFIER(GetSameTypeAttackBonusModifier(battlerAtk, moveType, move, abilityAtk));
    DAMAGE_APPLY_MODIFIER(typeEffectivenessModifier);
    DAMAGE_APPLY_MODIFIER(GetBurnOrFrostBiteOrPanicModifier(battlerAtk, move, abilityAtk));
    DAMAGE_APPLY_MODIFIER(GetZMoveAgainstProtectionModifier(battlerDef));
    DAMAGE_APPLY_MODIFIER(GetOtherModifiers(move, moveType, battlerAtk, battlerDef, isCrit, typeEffectivenessModifier, updateFlags, abilityAtk, abilityDef, holdEffectAtk, holdEffectDef));

    if (holdEffectAtk == HOLD_EFFECT_TRADING_CARD)
    {
        if (gBattleMoves[move].piercingMove)
        {
            if (defCompare > 80)
                defCompare = 80;
            if (IsSpeciesOneOf(gBattleMons[battlerDef].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && defCompare > 50)
                defCompare = 50;
            dmg = dmg + defCompare;
        }
        else
        {
            if (atkCompare > 80)
                atkCompare = 80;
            if (IsSpeciesOneOf(gBattleMons[battlerDef].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && atkCompare > 50)
                atkCompare = 50;
            dmg = dmg + defCompare;
        }
    }

    if ((holdEffectAtk == HOLD_EFFECT_POISON_BARB 
    && gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY
    && gBattleMoves[move].type == TYPE_POISON)
    || (holdEffectAtk == HOLD_EFFECT_CHUPACABRA 
    && CalcMoveBasePower(move, battlerAtk, battlerDef, defAbility, weather) <= 70 
    && (gMultiHitCounter == 1 || gMultiHitCounter == 0)
    && GetBattlerAbility(battlerAtk) != ABILITY_TECHNICIAN)
    || move == MOVE_SPIRIT_DANCE)
    {
        uniqueDamage = gBattleMons[battlerDef].maxHP * 15 / 100;
        if (IsSpeciesOneOf(gBattleMons[battlerDef].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && uniqueDamage > 50)
            uniqueDamage = 50;
        dmg = dmg + uniqueDamage;
    }
    else if (move == MOVE_LICK)
    {
        uniqueDamage = gBattleMons[battlerDef].maxHP / 10;
        uniqueDamage *= CountBattlerStatDecreases(battlerDef, TRUE) + 1;
        if (CountBattlerStatDecreases(battlerDef, TRUE) >= 10)
            uniqueDamage = gBattleMons[battlerDef].maxHP;
        if (IsSpeciesOneOf(gBattleMons[battlerDef].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && uniqueDamage > 50)
            uniqueDamage = 50;
        dmg = dmg + uniqueDamage;
    }
    else if (move == MOVE_MALIGNANT_CHAIN)
    {
        uniqueDamage = gBattleMons[battlerDef].maxHP * 3 / 10;
        if (IsSpeciesOneOf(gBattleMons[battlerDef].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && uniqueDamage > 50)
            uniqueDamage = 50;
        dmg = dmg + uniqueDamage;
    }
    else if (move == MOVE_NEEDLE_ARM
    || (move == MOVE_SHADOW_CLAW && gIsCriticalHit)
    || (move == MOVE_ASTONISH && gBattleMons[battlerDef].status1 & STATUS1_PANIC)
    || move == MOVE_SOUL_CUTTER
    || (move == MOVE_ZING_ZAP && gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN))
    {
        uniqueDamage = gBattleMons[battlerDef].maxHP / 5;
        if (IsSpeciesOneOf(gBattleMons[battlerDef].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && uniqueDamage > 50)
            uniqueDamage = 50;
        dmg = dmg + uniqueDamage;
    }
    else if (move == MOVE_POISON_DART && gBattleMons[battlerDef].status1 & STATUS1_POISON)
    {
        uniqueDamage = gBattleMons[battlerDef].maxHP / 4;
        if (IsSpeciesOneOf(gBattleMons[battlerDef].species, gMegaBosses) && (gBattleTypeFlags & BATTLE_TYPE_SHUNYONG) && uniqueDamage > 50)
            uniqueDamage = 50;
        dmg = dmg + uniqueDamage;
    }

    if (dmg == 0)
        dmg = 1;
    return dmg;
}

static inline s32 DoMoveDamageCalc(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType, s32 fixedBasePower,
                                   bool32 isCrit, bool32 randomFactor, bool32 updateFlags, uq4_12_t typeEffectivenessModifier, u32 weather)
{
    u32 holdEffectAtk, holdEffectDef, abilityAtk, abilityDef;

    if (typeEffectivenessModifier == UQ_4_12(0.0))
        return 0;

    holdEffectAtk = GetBattlerHoldEffect(battlerAtk, TRUE);
    holdEffectDef = GetBattlerHoldEffect(battlerDef, TRUE);
    abilityAtk = GetBattlerAbility(battlerAtk);
    abilityDef = GetBattlerAbility(battlerDef);

    return DoMoveDamageCalcVars(move, battlerAtk, battlerDef, moveType, fixedBasePower, isCrit, randomFactor,
                                updateFlags, typeEffectivenessModifier, weather, holdEffectAtk, holdEffectDef, abilityAtk, abilityDef);
}

static inline s32 DoFutureSightAttackDamageCalcVars(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType,
                            bool32 isCrit, bool32 randomFactor, bool32 updateFlags, uq4_12_t typeEffectivenessModifier, u32 weather,
                            u32 holdEffectDef, u32 abilityDef)
{
    s32 dmg;
    u32 userFinalAttack;
    u32 targetFinalDefense;
    struct Pokemon *party = GetSideParty(GetBattlerSide(battlerAtk));
    struct Pokemon *partyMon = &party[gWishFutureKnock.futureSightPartyIndex[battlerDef]];
    u32 partyMonLevel = GetMonData(partyMon, MON_DATA_LEVEL, NULL);
    u32 partyMonSpecies = GetMonData(partyMon, MON_DATA_SPECIES, NULL);
    gBattleMovePower = gBattleMoves[move].power;
    if (IS_MOVE_PHYSICAL(move))
        userFinalAttack = GetMonData(partyMon, MON_DATA_ATK, NULL);
    else
        userFinalAttack = GetMonData(partyMon, MON_DATA_SPATK, NULL);
    targetFinalDefense = CalcDefenseStat(move, battlerAtk, battlerDef, moveType, isCrit, updateFlags, ABILITY_NONE, abilityDef, holdEffectDef, weather);
    dmg = CalculateBaseDamage(gBattleMovePower, userFinalAttack, partyMonLevel, targetFinalDefense);
    DAMAGE_APPLY_MODIFIER(GetCriticalModifier(isCrit, battlerAtk));
    if (randomFactor)
    {
        dmg *= 100 - RandomUniform(RNG_DAMAGE_MODIFIER, 0, 15);
        dmg /= 100;
    }
    // Same type attack bonus
    if (gSpeciesInfo[partyMonSpecies].types[0] == moveType || gSpeciesInfo[partyMonSpecies].types[1] == moveType)
        DAMAGE_APPLY_MODIFIER(UQ_4_12(1.25));
    else
        DAMAGE_APPLY_MODIFIER(UQ_4_12(1.0));
    DAMAGE_APPLY_MODIFIER(typeEffectivenessModifier);
    if (dmg == 0)
        dmg = 1;
    gSpecialStatuses[battlerAtk].preventLifeOrbDamage = TRUE;
    return dmg;
}
static inline s32 DoFutureSightAttackDamageCalc(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType,
                            bool32 isCrit, bool32 randomFactor, bool32 updateFlags, uq4_12_t typeEffectivenessModifier, u32 weather)
{
    u32 holdEffectDef, abilityDef;
    if (typeEffectivenessModifier == UQ_4_12(0.0))
        return 0;
    holdEffectDef = GetBattlerHoldEffect(battlerDef, TRUE);
    abilityDef = GetBattlerAbility(battlerDef);
    return DoFutureSightAttackDamageCalcVars(move, battlerAtk, battlerDef, moveType, isCrit, randomFactor,
                            updateFlags, typeEffectivenessModifier, weather, holdEffectDef, abilityDef);
}

#undef DAMAGE_APPLY_MODIFIER

static u32 GetWeather(void)
{
    if (gBattleWeather == B_WEATHER_NONE || !WEATHER_HAS_EFFECT)
        return B_WEATHER_NONE;
    else
        return gBattleWeather;
}

s32 CalculateMoveDamage(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType, s32 fixedBasePower, bool32 isCrit, bool32 randomFactor, bool32 updateFlags)
{
    struct Pokemon *party = GetSideParty(GetBattlerSide(gBattlerAttacker));

    if (gBattleMoves[move].effect == EFFECT_FUTURE_SIGHT
     && (&party[gWishFutureKnock.futureSightPartyIndex[battlerDef]] != &party[gBattlerPartyIndexes[battlerAtk]]) )
    {
        return DoFutureSightAttackDamageCalc(move, battlerAtk, battlerDef, moveType, isCrit, randomFactor,
                                updateFlags, CalcTypeEffectivenessMultiplier(move, moveType, battlerAtk, battlerDef, GetBattlerAbility(battlerDef), updateFlags),
                                GetWeather());
    }
    else
    {
        return DoMoveDamageCalc(move, battlerAtk, battlerDef, moveType, fixedBasePower, isCrit, randomFactor,
                            updateFlags, CalcTypeEffectivenessMultiplier(move, moveType, battlerAtk, battlerDef, GetBattlerAbility(battlerDef), updateFlags),
                            GetWeather());
    }
}

// for AI so that typeEffectivenessModifier, weather, abilities and holdEffects are calculated only once
s32 CalculateMoveDamageVars(u32 move, u32 battlerAtk, u32 battlerDef, u32 moveType, s32 fixedBasePower, uq4_12_t typeEffectivenessModifier,
                            u32 weather, bool32 isCrit, u32 holdEffectAtk, u32 holdEffectDef, u32 abilityAtk, u32 abilityDef)
{
    return DoMoveDamageCalcVars(move, battlerAtk, battlerDef, moveType, fixedBasePower, isCrit, FALSE, FALSE,
                                typeEffectivenessModifier, weather, holdEffectAtk, holdEffectDef, abilityAtk, abilityDef);
}

static inline void MulByTypeEffectiveness(uq4_12_t *modifier, u32 move, u32 moveType, u32 battlerDef, u32 defType, u32 battlerAtk, bool32 recordAbilities, uq4_12_t typeEffectivenessModifier)
{
    uq4_12_t mod = GetTypeModifier(moveType, defType);

    if (mod == UQ_4_12(0.0) && GetBattlerHoldEffect(battlerDef, TRUE) == HOLD_EFFECT_RING_TARGET)
    {
        mod = UQ_4_12(1.0);
        if (recordAbilities)
            RecordItemEffectBattle(battlerDef, HOLD_EFFECT_RING_TARGET);
    }
    else if ((typeEffectivenessModifier >= UQ_4_12(2.0)) && GetBattlerHoldEffect(battlerDef, TRUE) == HOLD_EFFECT_KEYCHAIN && gBattleMons[battlerDef].species == SPECIES_SPITFAX)
    {
        mod = UQ_4_12(0.0);
        if (recordAbilities)
            RecordItemEffectBattle(battlerDef, HOLD_EFFECT_KEYCHAIN);
    }
    else if (GetBattlerHoldEffect(battlerDef, TRUE) == HOLD_EFFECT_FOCUS_BAND && (Random() % 5) == 0)
    {
        mod = UQ_4_12(0.5);
        if (recordAbilities)
            RecordItemEffectBattle(battlerDef, HOLD_EFFECT_FOCUS_BAND);
    }
    else if ((moveType == TYPE_FIGHTING || moveType == TYPE_NORMAL) && defType == TYPE_GHOST && gBattleMons[battlerDef].status2 & STATUS2_FORESIGHT && mod == UQ_4_12(0.0))
    {
        mod = UQ_4_12(1.0);
    }
    else if ((moveType == TYPE_FIGHTING || moveType == TYPE_NORMAL) && defType == TYPE_GHOST && GetBattlerAbility(battlerAtk) == ABILITY_SCRAPPY && mod == UQ_4_12(0.0))
    {
        mod = UQ_4_12(1.0);
        if (recordAbilities)
            RecordAbilityBattle(battlerAtk, ABILITY_SCRAPPY);
    }
    else if ((moveType == TYPE_PSYCHIC) && defType == TYPE_DARK && GetBattlerAbility(battlerAtk) == ABILITY_DOMINEER && mod == UQ_4_12(0.0))
    {
        mod = UQ_4_12(1.0);
        if (recordAbilities)
            RecordAbilityBattle(battlerAtk, ABILITY_DOMINEER);
    }
    else if (defType == TYPE_ICE && GetBattlerAbility(battlerDef) == ABILITY_PERMAFROST && mod >= UQ_4_12(1.0) && IsBattlerWeatherAffected(battlerDef, B_WEATHER_HAIL))
    {
        mod = UQ_4_12(1.0);
        if (recordAbilities)
            RecordAbilityBattle(battlerDef, ABILITY_PERMAFROST);
    }
    else if (GetBattlerAbility(battlerDef) == ABILITY_REFORM 
    && ((moveType == TYPE_NORMAL && gDisableStructs[battlerDef].reformNormal)
    || (moveType == TYPE_FIGHTING && gDisableStructs[battlerDef].reformFighting)
    || (moveType == TYPE_FLYING && gDisableStructs[battlerDef].reformFlying)
    || (moveType == TYPE_POISON && gDisableStructs[battlerDef].reformPoison)
    || (moveType == TYPE_GROUND && gDisableStructs[battlerDef].reformGround)
    || (moveType == TYPE_ROCK && gDisableStructs[battlerDef].reformRock)
    || (moveType == TYPE_BUG && gDisableStructs[battlerDef].reformBug)
    || (moveType == TYPE_GHOST && gDisableStructs[battlerDef].reformGhost)
    || (moveType == TYPE_STEEL && gDisableStructs[battlerDef].reformSteel)
    || (moveType == TYPE_FIRE && gDisableStructs[battlerDef].reformFire)
    || (moveType == TYPE_WATER && gDisableStructs[battlerDef].reformWater)
    || (moveType == TYPE_GRASS && gDisableStructs[battlerDef].reformGrass)
    || (moveType == TYPE_ELECTRIC && gDisableStructs[battlerDef].reformElectric)
    || (moveType == TYPE_PSYCHIC && gDisableStructs[battlerDef].reformPsychic)
    || (moveType == TYPE_ICE && gDisableStructs[battlerDef].reformIce)
    || (moveType == TYPE_DRAGON && gDisableStructs[battlerDef].reformDragon)
    || (moveType == TYPE_DARK && gDisableStructs[battlerDef].reformDark)
    || (moveType == TYPE_FAIRY && gDisableStructs[battlerDef].reformFairy)
    || (moveType == TYPE_RELIC && gDisableStructs[battlerDef].reformRelic)))
    {
        mod = UQ_4_12(0.5);
        if (recordAbilities)
            RecordAbilityBattle(battlerDef, ABILITY_REFORM);
    }
    
    if ((moveType == defType) && gStatuses4[battlerDef] & STATUS4_REFLECTED_TYPE)
        mod = UQ_4_12(0.0);
    if (moveType == TYPE_PSYCHIC && defType == TYPE_DARK && gStatuses3[battlerDef] & STATUS3_MIRACLE_EYED && mod == UQ_4_12(0.0))
        mod = UQ_4_12(1.0);
    if (gBattleMoves[move].effect == EFFECT_FREEZE_DRY && defType == TYPE_WATER)
        mod = UQ_4_12(2.0);
    if (!IsBattlerGrounded(battlerDef) && (gBattleMoves[move].ignoreTypeIfFlyingAndUngrounded) && (defType == TYPE_FLYING))
        mod = UQ_4_12(1.0);
    if (gBattleMoves[move].effect == EFFECT_PLASMA_CUTTER && defType == TYPE_GROUND)
        mod = UQ_4_12(1.0);
    if (gCurrentMove == MOVE_BREAK_LANCE && mod > UQ_4_12(0.0) && mod <= UQ_4_12(0.5))
        mod = UQ_4_12(1.0);
    if (gBattleMoves[move].effect == EFFECT_BEATBOX && defType == TYPE_GHOST)
        mod = UQ_4_12(1.0);
    if (gBattleMoves[move].effect == EFFECT_SOLAR_FLARE && defType == TYPE_DARK)
        mod = UQ_4_12(2.0);
    if (gCurrentMove == MOVE_HEAT_SINK && defType == TYPE_FIRE)
        mod = UQ_4_12(2.0);
    if (gCurrentMove == MOVE_EVAPORATE && defType == TYPE_WATER)
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_EXORCISM && defType == TYPE_GHOST)
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_MUDDY_WATER && (defType == TYPE_WATER || defType == TYPE_POISON))
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_EARTH_SHATTER && (defType == TYPE_ROCK || defType == TYPE_STEEL || defType == TYPE_GROUND))
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_IGNA_STRIKE && (defType == TYPE_FIRE || defType == TYPE_ROCK))
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_DECAY_BEAM && (defType == TYPE_BUG || defType == TYPE_GRASS))
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_CINDER_DRILL && (defType == TYPE_BUG || defType == TYPE_GRASS || defType == TYPE_STEEL || defType == TYPE_ICE))
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_SNUFF_OUT && defType == TYPE_FIRE)
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_FALSE_SWIPE)
        mod = UQ_4_12(1.0);
    if (gCurrentMove == MOVE_CHROMA_BEAM)
        mod *= 2;
    if (gCurrentMove == MOVE_MASS_DESTRUCTION && (defType == TYPE_NORMAL || defType == TYPE_FIGHTING))
        mod = UQ_4_12(2.0);
    if (gCurrentMove == MOVE_PURGE_RAY && (defType == TYPE_DARK || defType == TYPE_POISON))
        mod = UQ_4_12(2.0);
    if (gCurrentMove == MOVE_DIFFUSE_WAVE && (defType == TYPE_FIRE || defType == TYPE_ELECTRIC))
        mod = UQ_4_12(2.0);
    if (gBattleMoves[move].effect == EFFECT_SKY_SPLITTER && defType == TYPE_FLYING)
        mod = UQ_4_12(2.0);
    if (gCurrentMove == MOVE_VAPORIZE && (defType == TYPE_ICE || defType == TYPE_WATER))
        mod = UQ_4_12(2.0);
    if (moveType == TYPE_GROUND && defType == TYPE_FLYING && IsBattlerGrounded(battlerDef) && mod == UQ_4_12(0.0))
        mod = UQ_4_12(1.0);
    if (moveType == TYPE_POISON && (defType == TYPE_POISON || defType == TYPE_STEEL) && GetBattlerAbility(battlerAtk) == ABILITY_CORROSION)
        mod = UQ_4_12(2.0);
    if (gCurrentMove == MOVE_SCORP_FANG && (defType == TYPE_POISON || defType == TYPE_STEEL))
        mod = UQ_4_12(1.0);

    // B_WEATHER_STRONG_WINDS weakens Super Effective moves against Flying-type Pok?mon
    if (gBattleWeather & B_WEATHER_STRONG_WINDS && WEATHER_HAS_EFFECT)
    {
        if (defType == TYPE_FLYING && mod >= UQ_4_12(2.0))
            mod = UQ_4_12(1.0);
    }

    if (gBattleStruct->distortedTypeMatchups & gBitTable[battlerDef] || (gBattleStruct->aiCalcInProgress && ShouldTeraShellDistortTypeMatchups(move, battlerDef)))
    {
        mod = UQ_4_12(0.5);
        if (recordAbilities)
            RecordAbilityBattle(battlerDef, GetBattlerAbility(battlerDef));
    }

    *modifier = uq4_12_multiply(*modifier, mod);

    if (*modifier == UQ_4_12(4.0))
    {
        *modifier = UQ_4_12(3.0);
    }

    if (*modifier > UQ_4_12(4.0))
    {
        *modifier = UQ_4_12(4.0);
    }
}

static inline void TryNoticeIllusionInTypeEffectiveness(u32 move, u32 moveType, u32 battlerAtk, u32 battlerDef, uq4_12_t resultingModifier, u32 illusionSpecies)
{
    // Check if the type effectiveness would've been different if the pokemon really had the types as the disguise.
    uq4_12_t presumedModifier = UQ_4_12(1.0);
    MulByTypeEffectiveness(&presumedModifier, move, moveType, battlerDef, gSpeciesInfo[illusionSpecies].types[0], battlerAtk, FALSE, FALSE);
    if (gSpeciesInfo[illusionSpecies].types[1] != gSpeciesInfo[illusionSpecies].types[0])
        MulByTypeEffectiveness(&presumedModifier, move, moveType, battlerDef, gSpeciesInfo[illusionSpecies].types[1], battlerAtk, FALSE, FALSE);

    if (presumedModifier != resultingModifier)
        RecordAbilityBattle(battlerDef, ABILITY_ILLUSION);
}

static void UpdateMoveResultFlags(uq4_12_t modifier)
{
    if (modifier == UQ_4_12(0.0))
    {
        gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE);
    }
    else if (modifier == UQ_4_12(1.0))
    {
        gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    else if (modifier > UQ_4_12(1.0))
    {
        gMoveResultFlags |= MOVE_RESULT_SUPER_EFFECTIVE;
        gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    else // if (modifier < UQ_4_12(1.0))
    {
        gMoveResultFlags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
        gMoveResultFlags &= ~(MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
}

static inline uq4_12_t CalcTypeEffectivenessMultiplierInternal(u32 move, u32 moveType, u32 battlerAtk, u32 battlerDef, bool32 recordAbilities, uq4_12_t modifier, u32 defAbility)
{
    u32 illusionSpecies;

    MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, GetBattlerType(battlerDef, 0), battlerAtk, recordAbilities, FALSE);
    if (GetBattlerType(battlerDef, 1) != GetBattlerType(battlerDef, 0))
        MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, GetBattlerType(battlerDef, 1), battlerAtk, recordAbilities, FALSE);
    if (GetBattlerType(battlerDef, 2) != TYPE_MYSTERY && GetBattlerType(battlerDef, 2) != GetBattlerType(battlerDef, 1) && GetBattlerType(battlerDef, 2) != GetBattlerType(battlerDef, 0))
        MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, GetBattlerType(battlerDef, 2), battlerAtk, recordAbilities, FALSE);
    if (moveType == TYPE_FIRE && gDisableStructs[battlerDef].tarShot)
        modifier = uq4_12_multiply(modifier, UQ_4_12(2.0));

    if (recordAbilities && (illusionSpecies = GetIllusionMonSpecies(battlerDef)))
        TryNoticeIllusionInTypeEffectiveness(move, moveType, battlerAtk, battlerDef, modifier, illusionSpecies);

    if (gBattleMoves[move].split == SPLIT_STATUS && move != MOVE_THUNDER_WAVE)
    {
        modifier = UQ_4_12(1.0);
#if B_GLARE_GHOST <= GEN_3
        if (move == MOVE_GLARE && IS_BATTLER_OF_TYPE(battlerDef, TYPE_GHOST))
        {
            modifier = UQ_4_12(0.0);
        }
#endif
    }
    else if (moveType == TYPE_GROUND && defAbility == ABILITY_GRAVITY_WELL && gFieldStatuses & STATUS_FIELD_GRAVITY && !(gBattleMoves[move].ignoreTypeIfFlyingAndUngrounded))
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities && defAbility == ABILITY_GRAVITY_WELL)
        {
            gLastUsedAbility = ABILITY_GRAVITY_WELL;
            gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastLandedMoves[battlerDef] = 0;
            gBattleCommunication[MISS_TYPE] = B_MSG_GROUND_MISS;
            RecordAbilityBattle(battlerDef, ABILITY_GRAVITY_WELL);
        }
    }
    else if (moveType == TYPE_GROUND && !IsBattlerGrounded2(battlerDef, TRUE) && !(gBattleMoves[move].ignoreTypeIfFlyingAndUngrounded))
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities && defAbility == ABILITY_LEVITATE)
        {
            gLastUsedAbility = ABILITY_LEVITATE;
            gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastLandedMoves[battlerDef] = 0;
            gBattleCommunication[MISS_TYPE] = B_MSG_GROUND_MISS;
            RecordAbilityBattle(battlerDef, ABILITY_LEVITATE);
        }
    }
#if B_SHEER_COLD_IMMUNITY >= GEN_7
    else if (move == MOVE_SHEER_COLD && IS_BATTLER_OF_TYPE(battlerDef, TYPE_ICE))
    {
        modifier = UQ_4_12(0.0);
    }
#endif
    // Immunity
    if (gBattleMoves[move].type == TYPE_POISON && defAbility == ABILITY_IMMUNITY)
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities && defAbility == ABILITY_IMMUNITY)
        {
            gLastUsedAbility = ABILITY_IMMUNITY;
            gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastLandedMoves[battlerDef] = 0;
            PREPARE_TYPE_BUFFER(gBattleTextBuff1, gBattleMoves[move].type);
            gBattleCommunication[MISS_TYPE] = B_MSG_SPECIAL_MISS;
            RecordAbilityBattle(battlerDef, ABILITY_IMMUNITY);
        }
    }
    
    // All Game
    if ((gBattleMoves[move].type == TYPE_GROUND || gBattleMoves[move].type == TYPE_WATER) && defAbility == ABILITY_ALL_GAME)
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities && defAbility == ABILITY_ALL_GAME)
        {
            gLastUsedAbility = ABILITY_ALL_GAME;
            gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastLandedMoves[battlerDef] = 0;
            PREPARE_TYPE_BUFFER(gBattleTextBuff1, gBattleMoves[move].type);
            gBattleCommunication[MISS_TYPE] = B_MSG_SPECIAL_MISS;
            RecordAbilityBattle(battlerDef, ABILITY_ALL_GAME);
        }
    }

    // Empty
    if ((gBattleMoves[move].type == TYPE_NORMAL || gBattleMoves[move].type == TYPE_FIGHTING) && GetBattlerAbility(battlerAtk) != ABILITY_SCRAPPY && defAbility == ABILITY_EMPTY)
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities && defAbility == ABILITY_EMPTY)
        {
            gLastUsedAbility = ABILITY_EMPTY;
            gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastLandedMoves[battlerDef] = 0;
            gBattleCommunication[MISS_TYPE] = B_MSG_IS_EMPTY;
            RecordAbilityBattle(battlerDef, ABILITY_EMPTY);
        }
    }

    // Pink Mist
    if (gBattleMoves[move].type == TYPE_PSYCHIC 
        && defAbility == ABILITY_PINK_MIST 
        && gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities && defAbility == ABILITY_PINK_MIST)
        {
            gLastUsedAbility = ABILITY_PINK_MIST;
            gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastLandedMoves[battlerDef] = 0;
            PREPARE_TYPE_BUFFER(gBattleTextBuff1, gBattleMoves[move].type);
            gBattleCommunication[MISS_TYPE] = B_MSG_SPECIAL_MISS;
            RecordAbilityBattle(battlerDef, ABILITY_PINK_MIST);
        }
    }

    if (((defAbility == ABILITY_WONDER_GUARD && modifier <= UQ_4_12(1.0)) || (defAbility == ABILITY_TELEPATHY && battlerDef == BATTLE_PARTNER(battlerAtk))) && gBattleMoves[move].power)
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities)
        {
            gLastUsedAbility = gBattleMons[battlerDef].ability;
            gMoveResultFlags |= MOVE_RESULT_MISSED;
            gLastLandedMoves[battlerDef] = 0;
            gBattleCommunication[MISS_TYPE] = B_MSG_AVOIDED_DMG;
            RecordAbilityBattle(battlerDef, gBattleMons[battlerDef].ability);
        }
    }

    // Signal for the trainer slide-in system.
    if (GetBattlerSide(battlerDef) != B_SIDE_PLAYER && modifier && gBattleStruct->trainerSlideFirstSTABMoveMsgState != 2)
        gBattleStruct->trainerSlideFirstSTABMoveMsgState = 1;

    return modifier;
}

uq4_12_t CalcTypeEffectivenessMultiplier(u32 move, u32 moveType, u32 battlerAtk, u32 battlerDef, u32 defAbility, bool32 recordAbilities)
{
    uq4_12_t modifier = UQ_4_12(1.0);

    if (move != MOVE_STRUGGLE && moveType != TYPE_MYSTERY)
    {
        modifier = CalcTypeEffectivenessMultiplierInternal(move, moveType, battlerAtk, battlerDef, recordAbilities, modifier, defAbility);
        if (gBattleMoves[move].effect == EFFECT_TWO_TYPED_MOVE)
            modifier = CalcTypeEffectivenessMultiplierInternal(move, gBattleMoves[move].argument, battlerAtk, battlerDef, recordAbilities, modifier, defAbility);
        if (gBattleMoves[move].effect == EFFECT_FLYING_PRESS)
            modifier = CalcTypeEffectivenessMultiplierInternal(move, TYPE_FLYING, battlerAtk, battlerDef, recordAbilities, modifier, defAbility);
        if (gBattleMoves[move].effect == EFFECT_WICKED_WINDS)
            modifier = CalcTypeEffectivenessMultiplierInternal(move, TYPE_FLYING, battlerAtk, battlerDef, recordAbilities, modifier, defAbility);
        if (gBattleMoves[move].effect == EFFECT_CRASH_LAND)
            modifier = CalcTypeEffectivenessMultiplierInternal(move, TYPE_GROUND, battlerAtk, battlerDef, recordAbilities, modifier, defAbility);
    }

    if (recordAbilities)
        UpdateMoveResultFlags(modifier);
    return modifier;
}

uq4_12_t CalcPartyMonTypeEffectivenessMultiplier(u16 move, u16 speciesDef, u16 abilityDef)
{
    uq4_12_t modifier = UQ_4_12(1.0);
    u8 moveType = gBattleMoves[move].type;

    if (move != MOVE_STRUGGLE && moveType != TYPE_MYSTERY)
    {
        MulByTypeEffectiveness(&modifier, move, moveType, 0, gSpeciesInfo[speciesDef].types[0], 0, FALSE, FALSE);
        if (gSpeciesInfo[speciesDef].types[1] != gSpeciesInfo[speciesDef].types[0])
            MulByTypeEffectiveness(&modifier, move, moveType, 0, gSpeciesInfo[speciesDef].types[1], 0, FALSE, FALSE);

        if (moveType == TYPE_GROUND && abilityDef == ABILITY_LEVITATE && !(gFieldStatuses & STATUS_FIELD_GRAVITY))
            modifier = UQ_4_12(0.0);
        if (moveType == TYPE_POISON && abilityDef == ABILITY_IMMUNITY)
            modifier = UQ_4_12(0.0);
        if (moveType == TYPE_NORMAL && abilityDef == ABILITY_EMPTY)
            modifier = UQ_4_12(0.0);
        if (moveType == TYPE_FIGHTING && abilityDef == ABILITY_EMPTY)
            modifier = UQ_4_12(0.0);
        if (moveType == TYPE_GROUND && abilityDef == ABILITY_GRAVITY_WELL && gFieldStatuses & STATUS_FIELD_GRAVITY)
            modifier = UQ_4_12(0.0);
        if (abilityDef == ABILITY_WONDER_GUARD && modifier <= UQ_4_12(1.0) && gBattleMoves[move].power)
            modifier = UQ_4_12(0.0);
    }

    UpdateMoveResultFlags(modifier);
    return modifier;
}

static uq4_12_t GetInverseTypeMultiplier(uq4_12_t multiplier)
{
    switch (multiplier)
    {
    case UQ_4_12(0.0):
    case UQ_4_12(0.5):
        return UQ_4_12(2.0);
    case UQ_4_12(2.0):
        return UQ_4_12(0.5);
    case UQ_4_12(1.0):
    default:
        return UQ_4_12(1.0);
    }
}

uq4_12_t GetTypeModifier(u32 atkType, u32 defType)
{
#if B_FLAG_INVERSE_BATTLE != 0
    if (FlagGet(B_FLAG_INVERSE_BATTLE))
        return GetInverseTypeMultiplier(sTypeEffectivenessTable[atkType][defType]);
#endif
    if (gFieldStatuses & STATUS_FIELD_INVERSE_ROOM)
        return GetInverseTypeMultiplier(sTypeEffectivenessTable[atkType][defType]);
    return sTypeEffectivenessTable[atkType][defType];
}

s32 GetStealthHazardDamageByTypesAndHP(u8 hazardType, u8 type1, u8 type2, u32 maxHp)
{
    s32 dmg = 0;
    uq4_12_t modifier = UQ_4_12(1.0);

    modifier = uq4_12_multiply(modifier, GetTypeModifier(hazardType, type1));
    if (type2 != type1)
        modifier = uq4_12_multiply(modifier, GetTypeModifier(hazardType, type2));

    switch (modifier)
    {
    case UQ_4_12(0.0):
        dmg = 0;
        break;
    case UQ_4_12(0.25):
        dmg = maxHp / 32;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(0.5):
        dmg = maxHp / 16;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(1.0):
        dmg = maxHp / 8;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(2.0):
        dmg = maxHp / 4;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(3.0):
        dmg = maxHp / 3;
        if (dmg == 0)
            dmg = 1;
        break;
    case UQ_4_12(4.0):
        dmg = maxHp / 2;
        if (dmg == 0)
            dmg = 1;
        break;
    }

    return dmg;
}

s32 GetStealthHazardDamage(u8 hazardType, u32 battler)
{
    u8 type1 = gBattleMons[battler].type1;
    u8 type2 = gBattleMons[battler].type2;
    u32 maxHp = gBattleMons[battler].maxHP;

    return GetStealthHazardDamageByTypesAndHP(hazardType, type1, type2, maxHp);
}

bool32 IsPartnerMonFromSameTrainer(u32 battler)
{
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT && gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
        return FALSE;
    else if (GetBattlerSide(battler) == B_SIDE_PLAYER && gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
        return FALSE;
    else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        return FALSE;
    else
        return TRUE;
}

bool32 DoesSpeciesUseHoldItemToChangeForm(u16 species, u16 heldItemId)
{
    u32 i;
    const struct FormChange *formChanges = gFormChangeTablePointers[species];

    for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        switch (formChanges[i].method)
        {
        case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM:
        case FORM_CHANGE_BATTLE_PRIMAL_REVERSION:
        case FORM_CHANGE_BATTLE_ULTRA_BURST:
        case FORM_CHANGE_ITEM_HOLD:
        case FORM_CHANGE_BEGIN_BATTLE:
            if (formChanges[i].param1 == heldItemId)
                return TRUE;
            break;
        }
    }
    return FALSE;
}

bool32 CanMegaEvolve(u32 battler)
{
    u32 itemId, holdEffect, species;
    struct Pokemon *mon;
    u32 battlerPosition = GetBattlerPosition(battler);
    u8 partnerPosition = GetBattlerPosition(BATTLE_PARTNER(battler));
    struct MegaEvolutionData *mega = &(((struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]))->mega);

    // Check if Player has a Mega Ring
    if ((GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT)) && !CheckBagHasItem(ITEM_MEGA_RING, 1))
        return FALSE;

    // Check if trainer already mega evolved a pokemon.
    if (mega->alreadyEvolved[battlerPosition])
        return FALSE;

    // Cannot use z move and mega evolve on same turn
    if (gBattleStruct->zmove.toBeUsed[battler])
        return FALSE;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && IsPartnerMonFromSameTrainer(battler) && (mega->alreadyEvolved[partnerPosition] || (mega->toEvolve & gBitTable[BATTLE_PARTNER(battler)])))
        return FALSE;

    // Check if mon is currently held by Sky Drop
    if (gStatuses3[battler] & STATUS3_SKY_DROPPED)
        return FALSE;

    // Gets mon data.
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
        mon = &gEnemyParty[gBattlerPartyIndexes[battler]];
    else
        mon = &gPlayerParty[gBattlerPartyIndexes[battler]];

    species = GetMonData(mon, MON_DATA_SPECIES);
    itemId = GetMonData(mon, MON_DATA_HELD_ITEM);

    if (itemId == ITEM_ENIGMA_BERRY_E_READER)
        holdEffect = gEnigmaBerries[battler].holdEffect;
    else
        holdEffect = ItemId_GetHoldEffect(itemId);

    // Check if there is an entry in the evolution table for regular Mega Evolution.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM) != SPECIES_NONE)
    {
        // Can Mega Evolve via Mega Stone.
        if (holdEffect == HOLD_EFFECT_MEGA_STONE)
            return TRUE;
    }

    // Check if there is an entry in the evolution table for Wish Mega Evolution.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE) != SPECIES_NONE)
    {
        // Can't Wish Mega Evolve if holding a Z Crystal.
        if (holdEffect != HOLD_EFFECT_Z_CRYSTAL)
            return TRUE;
    }

    // No checks passed, the mon CAN'T mega evolve.
    return FALSE;
}

bool32 CanUltraBurst(u32 battler)
{
    u32 itemId, holdEffect, species;
    struct Pokemon *mon;
    u32 battlerPosition = GetBattlerPosition(battler);
    u8 partnerPosition = GetBattlerPosition(BATTLE_PARTNER(battler));

    // Check if Player has a Z Ring
    if ((GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT)) && !CheckBagHasItem(ITEM_Z_POWER_RING, 1))
        return FALSE;

    // Check if trainer already ultra bursted a pokemon.
    if (gBattleStruct->burst.alreadyBursted[battlerPosition])
        return FALSE;

    // Cannot use z move and ultra burst on same turn
    if (gBattleStruct->zmove.toBeUsed[battler])
        return FALSE;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && IsPartnerMonFromSameTrainer(battler) && (gBattleStruct->burst.alreadyBursted[partnerPosition] || (gBattleStruct->burst.toBurst & gBitTable[BATTLE_PARTNER(battler)])))
        return FALSE;

    // Check if mon is currently held by Sky Drop
    if (gStatuses3[battler] & STATUS3_SKY_DROPPED)
        return FALSE;

    // Gets mon data.
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
        mon = &gEnemyParty[gBattlerPartyIndexes[battler]];
    else
        mon = &gPlayerParty[gBattlerPartyIndexes[battler]];

    species = GetMonData(mon, MON_DATA_SPECIES);
    itemId = GetMonData(mon, MON_DATA_HELD_ITEM);

    // Check if there is an entry in the evolution table for Ultra Burst.
    if (GetBattleFormChangeTargetSpecies(battler, FORM_CHANGE_BATTLE_ULTRA_BURST) != SPECIES_NONE)
    {
        if (itemId == ITEM_ENIGMA_BERRY_E_READER)
            holdEffect = gEnigmaBerries[battler].holdEffect;
        else
            holdEffect = ItemId_GetHoldEffect(itemId);

        // Can Ultra Burst via Z Crystal.
        if (holdEffect == HOLD_EFFECT_Z_CRYSTAL)
            return TRUE;
    }

    // No checks passed, the mon CAN'T ultra burst.
    return FALSE;
}

bool32 IsBattlerMegaEvolved(u32 battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Mega Evolution.
    if (gBattleMons[battler].status2 & STATUS2_TRANSFORMED)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].flags & SPECIES_FLAG_MEGA_EVOLUTION);
}

bool32 IsBattlerPrimalReverted(u32 battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Primal Revesion.
    if (gBattleMons[battler].status2 & STATUS2_TRANSFORMED)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].flags & SPECIES_FLAG_PRIMAL_REVERSION);
}

bool32 IsBattlerUltraBursted(u32 battler)
{
    // While Transform does copy stats and visuals, it shouldn't be counted as true Ultra Burst.
    if (gBattleMons[battler].status2 & STATUS2_TRANSFORMED)
        return FALSE;
    return (gSpeciesInfo[gBattleMons[battler].species].flags & SPECIES_FLAG_ULTRA_BURST);
}

// Returns SPECIES_NONE if no form change is possible
u16 GetBattleFormChangeTargetSpecies(u32 battler, u16 method)
{
    u32 i, j;
    u16 targetSpecies = SPECIES_NONE;
    u16 species = gBattleMons[battler].species;
    const struct FormChange *formChanges = gFormChangeTablePointers[species];
    u16 heldItem;
    u32 ability;

    if (formChanges != NULL)
    {
        heldItem = gBattleMons[battler].item;
        ability = GetBattlerAbility(battler);

        for (i = 0; formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
        {
            if (method == formChanges[i].method && species != formChanges[i].targetSpecies)
            {
                switch (method)
                {
                case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM:
                case FORM_CHANGE_BATTLE_PRIMAL_REVERSION:
                case FORM_CHANGE_BATTLE_ULTRA_BURST:
                    if (heldItem == formChanges[i].param1)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE:
                    if (gBattleMons[battler].moves[0] == formChanges[i].param1 || gBattleMons[battler].moves[1] == formChanges[i].param1 || gBattleMons[battler].moves[2] == formChanges[i].param1 || gBattleMons[battler].moves[3] == formChanges[i].param1)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_BATTLE_SWITCH:
                    targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_BATTLE_HP_PERCENT:
                    if (formChanges[i].param1 == GetBattlerAbility(battler))
                    {
                        // We multiply by 100 to make sure that integer division doesn't mess with the health check.
                        u32 hpCheck = gBattleMons[battler].hp * 100 * 100 / gBattleMons[battler].maxHP;
                        switch (formChanges[i].param2)
                        {
                        case HP_HIGHER_THAN:
                            if (hpCheck > formChanges[i].param3 * 100)
                                targetSpecies = formChanges[i].targetSpecies;
                            break;
                        case HP_LOWER_EQ_THAN:
                            if (hpCheck <= formChanges[i].param3 * 100)
                                targetSpecies = formChanges[i].targetSpecies;
                            break;
                        }
                    }
                    break;
                case FORM_CHANGE_BATTLE_WEATHER:
                    // Check if there is a required ability and if the battler's ability does not match it
                    // or is suppressed. If so, revert to the no weather form.
                    if (formChanges[i].param2
                        && GetBattlerAbility(battler) != formChanges[i].param2
                        && formChanges[i].param1 == B_WEATHER_NONE)
                    {
                        targetSpecies = formChanges[i].targetSpecies;
                    }
                    // We need to revert the weather form if the field is under Air Lock, too.
                    else if (!WEATHER_HAS_EFFECT && formChanges[i].param1 == B_WEATHER_NONE)
                    {
                        targetSpecies = formChanges[i].targetSpecies;
                    }
                    // Otherwise, just check for a match between the weather and the form change table.
                    else if (gBattleWeather & formChanges[i].param1
                        || (gBattleWeather == B_WEATHER_NONE && formChanges[i].param1 == B_WEATHER_NONE))
                    {
                        targetSpecies = formChanges[i].targetSpecies;
                    }
                    break;
                case FORM_CHANGE_BATTLE_TURN_END:
                    if (formChanges[i].param1 == GetBattlerAbility(battler))
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_BATTLE_BEFORE_MOVE_CATEGORY:
                    if (formChanges[i].param1 == gBattleMoves[gCurrentMove].split
                        && (formChanges[i].param2 == ABILITY_NONE || formChanges[i].param2 == GetBattlerAbility(battler)))
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                }
            }
        }
    }

    return targetSpecies;
}

bool32 CanBattlerFormChange(u32 battler, u16 method)
{
    // Can't change form if transformed.
    if (gBattleMons[battler].status2 & STATUS2_TRANSFORMED && B_TRANSFORM_FORM_CHANGES >= GEN_5)
        return FALSE;
    // Mega Evolved and Ultra Bursted Pok?mon should always revert to normal upon fainting or ending the battle.
    if ((IsBattlerMegaEvolved(battler) || IsBattlerUltraBursted(battler)) && (method == FORM_CHANGE_FAINT || method == FORM_CHANGE_END_BATTLE))
        return TRUE;
    else if (IsBattlerPrimalReverted(battler) && (method == FORM_CHANGE_END_BATTLE))
        return TRUE;
    return DoesSpeciesHaveFormChangeMethod(gBattleMons[battler].species, method);
}

bool32 TryBattleFormChange(u32 battler, u16 method)
{
    u8 monId = gBattlerPartyIndexes[battler];
    u8 side = GetBattlerSide(battler);
    struct Pokemon *party = GetBattlerParty(battler);
    u16 targetSpecies;

    if (!CanBattlerFormChange(battler, method))
        return FALSE;

    targetSpecies = GetBattleFormChangeTargetSpecies(battler, method);
    if (targetSpecies == SPECIES_NONE)
        targetSpecies = GetFormChangeTargetSpecies(&party[monId], method, 0);
    if (targetSpecies != SPECIES_NONE)
    {
        // Saves the original species on the first form change for the player.
        if (gBattleStruct->changedSpecies[side][monId] == SPECIES_NONE)
            gBattleStruct->changedSpecies[side][monId] = gBattleMons[battler].species;

        TryToSetBattleFormChangeMoves(&party[monId], method);
        SetMonData(&party[monId], MON_DATA_SPECIES, &targetSpecies);
        gBattleMons[battler].species = targetSpecies;
        RecalcBattlerStats(battler, &party[monId]);
        return TRUE;
    }
    else if (gBattleStruct->changedSpecies[side][monId] != SPECIES_NONE)
    {
        bool32 restoreSpecies = FALSE;

        // Mega Evolved and Ultra Bursted Pokémon should always revert to normal upon fainting or ending the battle, so no need to add it to the form change tables.
        if ((IsBattlerMegaEvolved(battler) || IsBattlerUltraBursted(battler)) && (method == FORM_CHANGE_FAINT || method == FORM_CHANGE_END_BATTLE))
            restoreSpecies = TRUE;

        // Unlike Megas, Primal Reversion isn't canceled on fainting.
        else if (IsBattlerPrimalReverted(battler) && (method == FORM_CHANGE_END_BATTLE))
            restoreSpecies = TRUE;

        if (restoreSpecies)
        {
            u32 abilityForm = gBattleMons[battler].ability;
            // Reverts the original species
            TryToSetBattleFormChangeMoves(&party[monId], method);
            SetMonData(&party[monId], MON_DATA_SPECIES, &gBattleStruct->changedSpecies[side][monId]);
            RecalcBattlerStats(battler, &party[monId]);
            // Battler data is not updated with regular form's ability, not doing so could cause wrong ability activation.
            if (method == FORM_CHANGE_FAINT)
                gBattleMons[battler].ability = abilityForm;
            return TRUE;
        }
    }

    return FALSE;
}

bool32 DoBattlersShareType(u32 battler1, u32 battler2)
{
    s32 i;
    u8 types1[3] = {GetBattlerType(battler1, 0), GetBattlerType(battler1, 1), GetBattlerType(battler1, 2)};
    u8 types2[3] = {GetBattlerType(battler2, 0), GetBattlerType(battler2, 1), GetBattlerType(battler2, 2)};

    if (types1[2] == TYPE_MYSTERY)
        types1[2] = types1[0];
    if (types2[2] == TYPE_MYSTERY)
        types2[2] = types2[0];

    for (i = 0; i < 3; i++)
    {
        if (types1[i] == types2[0] || types1[i] == types2[1] || types1[i] == types2[2])
            return TRUE;
    }

    return FALSE;
}

bool32 CanBattlerGetOrLoseItem(u32 battler, u16 itemId)
{
    u16 species = gBattleMons[battler].species;
    u16 holdEffect = ItemId_GetHoldEffect(itemId);

    // Mail can be stolen now
    if (itemId == ITEM_ENIGMA_BERRY_E_READER)
        return FALSE;
    else if (DoesSpeciesUseHoldItemToChangeForm(species, itemId))
        return FALSE;
    else if (holdEffect == HOLD_EFFECT_Z_CRYSTAL)
        return FALSE;
    else
        return TRUE;
}

struct Pokemon *GetIllusionMonPtr(u32 battler)
{
    if (gBattleStruct->illusion[battler].broken)
        return NULL;
    if (!gBattleStruct->illusion[battler].set)
    {
        if (GetBattlerSide(battler) == B_SIDE_PLAYER)
            SetIllusionMon(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
        else
            SetIllusionMon(&gEnemyParty[gBattlerPartyIndexes[battler]], battler);
    }
    if (!gBattleStruct->illusion[battler].on)
        return NULL;

    return gBattleStruct->illusion[battler].mon;
}

void ClearIllusionMon(u32 battler)
{
    memset(&gBattleStruct->illusion[battler], 0, sizeof(gBattleStruct->illusion[battler]));
}

u32 GetIllusionMonSpecies(u32 battler)
{
    struct Pokemon *illusionMon = GetIllusionMonPtr(battler);
    if (illusionMon != NULL)
        return GetMonData(illusionMon, MON_DATA_SPECIES);
    return SPECIES_NONE;
}

bool32 SetIllusionMon(struct Pokemon *mon, u32 battler)
{
    struct Pokemon *party, *partnerMon;
    s32 i, id;
    u8 side, partyCount;

    gBattleStruct->illusion[battler].set = 1;
    if (GetMonAbility(mon) != ABILITY_ILLUSION)
        return FALSE;

    party = GetBattlerParty(battler);
    side = GetBattlerSide(battler);
    partyCount = side == B_SIDE_PLAYER ? gPlayerPartyCount : gEnemyPartyCount;

    // If this pokemon is last in the party, ignore Illusion.
    if (&party[partyCount - 1] == mon)
        return FALSE;

    if (IsBattlerAlive(BATTLE_PARTNER(battler)))
        partnerMon = &party[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]];
    else
        partnerMon = mon;

    // Find last alive non-egg pokemon.
    for (i = PARTY_SIZE - 1; i >= 0; i--)
    {
        id = i;
        if (GetMonData(&party[id], MON_DATA_SANITY_HAS_SPECIES) && GetMonData(&party[id], MON_DATA_HP) && !GetMonData(&party[id], MON_DATA_IS_EGG) && &party[id] != mon && &party[id] != partnerMon)
        {
            gBattleStruct->illusion[battler].on = 1;
            gBattleStruct->illusion[battler].broken = 0;
            gBattleStruct->illusion[battler].partyId = id;
            gBattleStruct->illusion[battler].mon = &party[id];
            return TRUE;
        }
    }

    return FALSE;
}

bool32 ShouldGetStatBadgeBoost(u16 badgeFlag, u32 battler)
{
#if B_BADGE_BOOST == GEN_3
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_RECORDED_LINK | BATTLE_TYPE_FRONTIER))
        return FALSE;
    else if (GetBattlerSide(battler) != B_SIDE_PLAYER)
        return FALSE;
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
        return FALSE;
    else if (FlagGet(badgeFlag))
        return TRUE;
#endif
    return FALSE;
}

u8 GetBattleMoveSplit(u32 moveId)
{
    if (gBattleStruct != NULL && gBattleStruct->zmove.active && !IS_MOVE_STATUS(moveId))
        return gBattleStruct->zmove.activeSplit;
    if (gBattleStruct != NULL && gBattleStruct->swapDamageCategory) // Photon Geyser, Shell Side Arm, Light That Burns the Sky
        return SPLIT_PHYSICAL;
    if (gProtectStructs != NULL && gProtectStructs[gBattlerAttacker].confusionSelfDmg && (gBattleMons[gBattlerAttacker].attack > gBattleMons[gBattlerAttacker].spAttack))
        return SPLIT_PHYSICAL;
    if (gProtectStructs != NULL && gProtectStructs[gBattlerAttacker].confusionSelfDmg && (gBattleMons[gBattlerAttacker].attack < gBattleMons[gBattlerAttacker].spAttack))
        return SPLIT_SPECIAL;

#if B_PHYSICAL_SPECIAL_SPLIT >= GEN_4
    return gBattleMoves[moveId].split;
#else
    if (IS_MOVE_STATUS(moveId))
        return SPLIT_STATUS;
    else if (gBattleMoves[moveId].type < TYPE_MYSTERY)
        return SPLIT_PHYSICAL;
    else
        return SPLIT_SPECIAL;
#endif
}

static bool32 TryRemoveScreens(u32 battler)
{
    bool32 removed = FALSE;
    u32 battlerSide = GetBattlerSide(battler);
    u8 enemySide = GetBattlerSide(BATTLE_OPPOSITE(battler));

    // try to remove from battler's side
    if (gSideStatuses[battlerSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_GOOGOO_SCREEN))
    {
        gSideStatuses[battlerSide] &= ~(SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_GOOGOO_SCREEN);
        gSideTimers[battlerSide].reflectTimer = 0;
        gSideTimers[battlerSide].lightscreenTimer = 0;
        gSideTimers[battlerSide].auroraVeilTimer = 0;
        gSideTimers[battlerSide].googooScreenTimer = 0;
        removed = TRUE;
    }

    // try to remove from battler opponent's side
    if (gSideStatuses[enemySide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_GOOGOO_SCREEN))
    {
        gSideStatuses[enemySide] &= ~(SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_GOOGOO_SCREEN);
        gSideTimers[enemySide].reflectTimer = 0;
        gSideTimers[enemySide].lightscreenTimer = 0;
        gSideTimers[enemySide].auroraVeilTimer = 0;
        gSideTimers[enemySide].googooScreenTimer = 0;
        removed = TRUE;
    }

    return removed;
}

static bool32 IsUnnerveAbilityOnOpposingSide(u32 battler)
{
    if (IsAbilityOnOpposingSide(battler, ABILITY_UNNERVE) || IsAbilityOnOpposingSide(battler, ABILITY_AS_ONE_ICE_RIDER) || IsAbilityOnOpposingSide(battler, ABILITY_AS_ONE_SHADOW_RIDER))
        return TRUE;
    return FALSE;
}

// Photon geyser & light that burns the sky
u8 GetSplitBasedOnStats(u32 battler)
{
    u32 attack = gBattleMons[battler].attack;
    u32 spAttack = gBattleMons[battler].spAttack;

    attack *= gStatStageRatios[gBattleMons[battler].statStages[STAT_ATK]][0];
    attack /= gStatStageRatios[gBattleMons[battler].statStages[STAT_ATK]][1];

    spAttack *= gStatStageRatios[gBattleMons[battler].statStages[STAT_SPATK]][0];
    spAttack /= gStatStageRatios[gBattleMons[battler].statStages[STAT_SPATK]][1];

    if (spAttack >= attack)
        return SPLIT_SPECIAL;
    else
        return SPLIT_PHYSICAL;
}

static u32 GetFlingPowerFromItemId(u32 itemId)
{
    if (itemId >= ITEM_TM01 && itemId <= ITEM_HM08)
    {
        u32 power = gBattleMoves[ItemIdToBattleMoveId(itemId)].power;
        if (power > 1)
            return power;
        return 10; // Status moves and moves with variable power always return 10 power.
    }
    else
        return ItemId_GetFlingPower(itemId);
}

bool32 CanFling(u32 battler)
{
    u16 item = gBattleMons[battler].item;

    if (item == ITEM_NONE
#if B_KLUTZ_FLING_INTERACTION >= GEN_5
        || GetBattlerAbility(battler) == ABILITY_KLUTZ
#endif
        || gFieldStatuses & STATUS_FIELD_MAGIC_ROOM || gDisableStructs[battler].embargoTimer != 0 || GetFlingPowerFromItemId(item) == 0 || !CanBattlerGetOrLoseItem(battler, item))
        return FALSE;

    return TRUE;
}

// Ability checks
bool32 IsRolePlayBannedAbilityAtk(u16 ability)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sUnchangeableAbilities); i++)
    {
        if (ability == sUnchangeableAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsRolePlayBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sUnchangeableAbilities); i++)
    {
        if (ability == sUnchangeableAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsSkillSwapBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sUnchangeableAbilities); i++)
    {
        if (ability == sUnchangeableAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsWorrySeedBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sUnchangeableAbilities); i++)
    {
        if (ability == sUnchangeableAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsGastroAcidBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sUnchangeableAbilities); i++)
    {
        if (ability == sUnchangeableAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsEntrainmentBannedAbilityAttacker(u16 ability)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sUnchangeableAbilities); i++)
    {
        if (ability == sUnchangeableAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsEntrainmentTargetOrSimpleBeamBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sUnchangeableAbilities); i++)
    {
        if (ability == sUnchangeableAbilities[i])
            return TRUE;
    }
    return FALSE;
}

// Sort an array of battlers by speed
// Useful for effects like pickpocket, eject button, red card, dancer
void SortBattlersBySpeed(u8 *battlers, bool32 slowToFast)
{
    int i, j, currSpeed, currBattler;
    u16 speeds[MAX_BATTLERS_COUNT] = {0};

    for (i = 0; i < gBattlersCount; i++)
        speeds[i] = GetBattlerTotalSpeedStat(battlers[i]);

    for (i = 1; i < gBattlersCount; i++)
    {
        currBattler = battlers[i];
        currSpeed = speeds[i];
        j = i - 1;

        if (slowToFast)
        {
            while (j >= 0 && speeds[j] > currSpeed)
            {
                battlers[j + 1] = battlers[j];
                speeds[j + 1] = speeds[j];
                j = j - 1;
            }
        }
        else
        {
            while (j >= 0 && speeds[j] < currSpeed)
            {
                battlers[j + 1] = battlers[j];
                speeds[j + 1] = speeds[j];
                j = j - 1;
            }
        }

        battlers[j + 1] = currBattler;
        speeds[j + 1] = currSpeed;
    }
}

void TryRestoreHeldItems(void)
{
    u32 i;
    
    for (i = 0; i < PARTY_SIZE; i++)
    {
        // Check if held items should be restored after battle based on generation
        if (B_RESTORE_HELD_BATTLE_ITEMS >= GEN_9 || gBattleStruct->itemLost[B_SIDE_PLAYER][i].stolen || gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            u16 lostItem = gBattleStruct->itemLost[B_SIDE_PLAYER][i].originalItem;

            // Check if the lost item should be restored
            if (lostItem != ITEM_NONE || gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &lostItem);
        }
    }
}

bool32 CanStealItem(u32 battlerStealing, u32 battlerItem, u16 item)
{
    u8 stealerSide = GetBattlerSide(battlerStealing);

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
        return FALSE;

    // Check if the battler trying to steal should be able to
    if (stealerSide == B_SIDE_OPPONENT
        && !(gBattleTypeFlags &
            (BATTLE_TYPE_EREADER_TRAINER 
             | BATTLE_TYPE_FRONTIER 
             | BATTLE_TYPE_LINK 
             | BATTLE_TYPE_RECORDED_LINK 
             | BATTLE_TYPE_SECRET_BASE
             | (B_TRAINERS_KNOCK_OFF_ITEMS == TRUE ? BATTLE_TYPE_TRAINER : 0)
            )))
    {
        return FALSE;
    }
    else if (!(gBattleTypeFlags &
        (BATTLE_TYPE_EREADER_TRAINER 
         | BATTLE_TYPE_FRONTIER 
         | BATTLE_TYPE_LINK 
         | BATTLE_TYPE_RECORDED_LINK 
         | BATTLE_TYPE_SECRET_BASE))
        && (gWishFutureKnock.knockedOffMons[stealerSide] & gBitTable[gBattlerPartyIndexes[battlerStealing]]))
    {
        return FALSE;
    }

    if (!CanBattlerGetOrLoseItem(battlerItem, item)         // Battler with item cannot have it stolen
        || !CanBattlerGetOrLoseItem(battlerStealing, item)) // Stealer cannot take the item
    {
        return FALSE;
    }
        
    return TRUE;
}

void TrySaveExchangedItem(u32 battler, u16 stolenItem)
{
    // Because BtlController_EmitSetMonData does SetMonData, we need to save the stolen item only if it matches the battler's original
    // So, if the player steals an item during battle and has it stolen from it, it will not end the battle with it (naturally)
#if B_TRAINERS_KNOCK_OFF_ITEMS == TRUE
    // If regular trainer battle and mon's original item matches what is being stolen, save it to be restored at end of battle
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER
      && !(gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
      && GetBattlerSide(battler) == B_SIDE_PLAYER
      && stolenItem == gBattleStruct->itemLost[B_SIDE_PLAYER][gBattlerPartyIndexes[battler]].originalItem)
        gBattleStruct->itemLost[B_SIDE_PLAYER][gBattlerPartyIndexes[battler]].stolen = TRUE;
#endif
}

bool32 IsBattlerAffectedByHazards(u32 battler, bool32 toxicSpikes)
{
    bool32 ret = TRUE;
    u32 holdEffect = GetBattlerHoldEffect(battler, TRUE);
    u32 ability = GetBattlerAbility(battler);

    if (IS_BATTLER_OF_TYPE(battler, TYPE_STEEL))
    {
        ret = FALSE;
    }
    else if (ability == ABILITY_SHIELD_DUST || ability == ABILITY_TITANIC || ability == ABILITY_IGNORANT_BLISS || ability == ABILITY_STURDY || (gBattleWeather & B_WEATHER_HAIL && ability == ABILITY_SNOW_CLOAK))
    {
        ret = FALSE;
        RecordAbilityBattle(battler, ability);
    }
    else if (toxicSpikes && holdEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS && !IS_BATTLER_OF_TYPE(battler, TYPE_POISON))
    {
        ret = FALSE;
        RecordItemEffectBattle(battler, holdEffect);
    }
    else if (holdEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS)
    {
        ret = FALSE;
        RecordItemEffectBattle(battler, holdEffect);
    }
    return ret;
}

bool32 TestSheerForceFlag(u32 battler, u16 move)
{
    if (GetBattlerAbility(battler) == ABILITY_SHEER_FORCE && gBattleMoves[move].sheerForceBoost)
        return TRUE;
    else
        return FALSE;
}

bool32 TestTeruCharm(u32 battler)
{
    if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_TERU_CHARM && gBattleMons[battler].species == SPECIES_CHIROBERRA)
        return TRUE;
    else
        return FALSE;
}

// This function is the body of "jumpifstat", but can be used dynamically in a function
bool32 CompareStat(u32 battler, u8 statId, u8 cmpTo, u8 cmpKind)
{
    bool32 ret = FALSE;
    u8 statValue = gBattleMons[battler].statStages[statId];

    // Because this command is used as a way of checking if a stat can be lowered/raised,
    // we need to do some modification at run-time.
    if (GetBattlerAbility(battler) == ABILITY_CONTRARY)
    {
        if (cmpKind == CMP_GREATER_THAN)
            cmpKind = CMP_LESS_THAN;
        else if (cmpKind == CMP_LESS_THAN)
            cmpKind = CMP_GREATER_THAN;

        if (cmpTo == MIN_STAT_STAGE)
            cmpTo = MAX_STAT_STAGE;
        else if (cmpTo == MAX_STAT_STAGE)
            cmpTo = MIN_STAT_STAGE;
    }

    switch (cmpKind)
    {
    case CMP_EQUAL:
        if (statValue == cmpTo)
            ret = TRUE;
        break;
    case CMP_NOT_EQUAL:
        if (statValue != cmpTo)
            ret = TRUE;
        break;
    case CMP_GREATER_THAN:
        if (statValue > cmpTo)
            ret = TRUE;
        break;
    case CMP_LESS_THAN:
        if (statValue < cmpTo)
            ret = TRUE;
        break;
    case CMP_COMMON_BITS:
        if (statValue & cmpTo)
            ret = TRUE;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(statValue & cmpTo))
            ret = TRUE;
        break;
    }

    return ret;
}

void BufferStatChange(u32 battler, u8 statId, u8 stringId)
{
    bool32 hasContrary = (GetBattlerAbility(battler) == ABILITY_CONTRARY);

    PREPARE_STAT_BUFFER(gBattleTextBuff1, statId);
    if (stringId == STRINGID_STATFELL)
    {
        if (hasContrary)
            PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATROSE)
        else
            PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATFELL)
    }
    else if (stringId == STRINGID_STATROSE)
    {
        if (hasContrary)
            PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATFELL)
        else
            PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATROSE)
    }
    else
    {
        PREPARE_STRING_BUFFER(gBattleTextBuff2, stringId)
    }
}

bool32 TryRoomService(u32 battler)
{
    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM && CompareStat(battler, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN))
    {
        BufferStatChange(battler, STAT_SPEED, STRINGID_STATFELL);
        gEffectBattler = gBattleScripting.battler = battler;
        SET_STATCHANGER(STAT_SPEED, 1, TRUE);
        gBattleScripting.animArg1 = 14 + STAT_SPEED;
        gBattleScripting.animArg2 = 0;
        gLastUsedItem = gBattleMons[battler].item;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool32 BlocksPrankster(u16 move, u32 battlerPrankster, u32 battlerDef, bool32 checkTarget)
{
#if B_PRANKSTER_DARK_TYPES >= GEN_7
    if (!gProtectStructs[battlerPrankster].pranksterElevated)
        return FALSE;
    if (GetBattlerSide(battlerPrankster) == GetBattlerSide(battlerDef))
        return FALSE;
    if (checkTarget && (GetBattlerMoveTargetType(battlerPrankster, move) & (MOVE_TARGET_OPPONENTS_FIELD | MOVE_TARGET_DEPENDS)))
        return FALSE;
    if (!IS_BATTLER_OF_TYPE(battlerDef, TYPE_DARK))
        return FALSE;
    if (gStatuses3[battlerDef] & STATUS3_SEMI_INVULNERABLE)
        return FALSE;

    return TRUE;
#endif
    return FALSE;
}

u16 GetUsedHeldItem(u32 battler)
{
    return gBattleStruct->usedHeldItems[gBattlerPartyIndexes[battler]][GetBattlerSide(battler)];
}

bool32 IsBattlerWeatherAffected(u32 battler, u32 weatherFlags)
{
    if (gBattleWeather & weatherFlags && WEATHER_HAS_EFFECT)
    {
        return TRUE;
    }
    return FALSE;
}

// Gets move target before redirection effects etc. are applied
// Possible return values are defined in battle.h following MOVE_TARGET_SELECTED
u32 GetBattlerMoveTargetType(u32 battler, u32 move)
{
    u32 target;

    if (gBattleMoves[move].effect == EFFECT_EXPANDING_FORCE && IsBattlerTerrainAffected(battler, STATUS_FIELD_PSYCHIC_TERRAIN))
        return MOVE_TARGET_BOTH;
    else if (gBattleMoves[move].effect == EFFECT_JUNGLE_RAGE && gDisableStructs[battler].frenzyCounter > 2)
        return MOVE_TARGET_BOTH;
    else if (gCurrentMove == MOVE_LEAF_STORM && (gBattleMons[battler].status1 & STATUS1_BLOOMING))
        return MOVE_TARGET_BOTH;
    else if (gCurrentMove == MOVE_DOUBLE_SHOCK && gStatuses4[battler] & STATUS4_SUPERCHARGED && gStatuses4[battler] & STATUS4_GEARED_UP)
        return MOVE_TARGET_FOES_AND_ALLY;
    else if ((gBattleMoves[gCurrentMove].effect == EFFECT_CANNONADE) && (gBattleMons[battler].hp <= (gBattleMons[battler].maxHP / 4)))
        return MOVE_TARGET_FOES_AND_ALLY;
    else
        return gBattleMoves[move].target;
}

bool32 CanTargetBattler(u32 battlerAtk, u32 battlerDef, u16 move)
{
    if ((gBattleMoves[move].effect == EFFECT_HIT_ENEMY_HEAL_ALLY || gBattleMoves[move].effect == EFFECT_TRICK_OR_TREAT) && GetBattlerSide(battlerAtk) == GetBattlerSide(battlerDef) && gStatuses3[battlerAtk] & STATUS3_HEAL_BLOCK)
        return FALSE; // Pok?mon affected by Heal Block cannot target allies with Pollen Puff
    return TRUE;
}

static void SetRandomMultiHitCounter()
{
    if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_LOADED_DICE)
    {
        if (gStatuses4[gBattlerAttacker] & STATUS4_DOUBLE_TEAM)
        {
            gMultiHitCounter = RandomUniform(RNG_LOADED_DICE, 5, 6);
        }
        else
        {
            gMultiHitCounter = RandomUniform(RNG_LOADED_DICE, 4, 5);
        }
    }
    else
    {
        if (gStatuses4[gBattlerAttacker] & STATUS4_DOUBLE_TEAM)
        {
            gMultiHitCounter = RandomWeighted(RNG_HITS, 0, 0, 0, 7, 7, 3, 3);
        }
        else
        {
            gMultiHitCounter = RandomWeighted(RNG_HITS, 0, 0, 7, 7, 3, 3);
        }
    }
}

static void SetRandomMultiHitCounter3To5()
{
    if (GetBattlerHoldEffect(gBattlerAttacker, TRUE) == HOLD_EFFECT_LOADED_DICE)
    {
        if (gStatuses4[gBattlerAttacker] & STATUS4_DOUBLE_TEAM)
        {
            gMultiHitCounter = RandomUniform(RNG_LOADED_DICE, 5, 6);
        }
        else
        {
            gMultiHitCounter = RandomUniform(RNG_LOADED_DICE, 4, 5);
        }
    }
    else
    {
        if (gStatuses4[gBattlerAttacker] & STATUS4_DOUBLE_TEAM)
        {
            gMultiHitCounter = RandomWeighted(RNG_HITS, 0, 0, 0, 0, 7, 2, 1);
        }
        else
        {
            gMultiHitCounter = RandomWeighted(RNG_HITS, 0, 0, 0, 7, 2, 1);
        }
    }
}

void CopyMonLevelAndBaseStatsToBattleMon(u32 battler, struct Pokemon *mon)
{
    gBattleMons[battler].level = GetMonData(mon, MON_DATA_LEVEL);
    gBattleMons[battler].hp = GetMonData(mon, MON_DATA_HP);
    gBattleMons[battler].maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    gBattleMons[battler].attack = GetMonData(mon, MON_DATA_ATK);
    gBattleMons[battler].defense = GetMonData(mon, MON_DATA_DEF);
    gBattleMons[battler].speed = GetMonData(mon, MON_DATA_SPEED);
    gBattleMons[battler].spAttack = GetMonData(mon, MON_DATA_SPATK);
    gBattleMons[battler].spDefense = GetMonData(mon, MON_DATA_SPDEF);
}

void CopyMonAbilityAndTypesToBattleMon(u32 battler, struct Pokemon *mon)
{
    gBattleMons[battler].ability = GetMonAbility(mon);
    gBattleMons[battler].type1 = gSpeciesInfo[gBattleMons[battler].species].types[0];
    gBattleMons[battler].type2 = gSpeciesInfo[gBattleMons[battler].species].types[1];
    gBattleMons[battler].type3 = TYPE_MYSTERY;
}

void RecalcBattlerStats(u32 battler, struct Pokemon *mon)
{
    CalculateMonStats(mon);
    CopyMonLevelAndBaseStatsToBattleMon(battler, mon);
    CopyMonAbilityAndTypesToBattleMon(battler, mon);
}

void RemoveConfusionStatus(u32 battler)
{
    gBattleMons[battler].status2 &= ~STATUS2_CONFUSION;
    gStatuses4[battler] &= ~STATUS4_INFINITE_CONFUSION;
}

bool32 CanBeInfinitelyConfused(u32 battler)
{
    return TRUE;
}

u8 GetBattlerGender(u32 battler)
{
    return GetGenderFromSpeciesAndPersonality(gBattleMons[battler].species,
                                              gBattleMons[battler].personality);
}

bool32 AreBattlersOfOppositeGender(u32 battler1, u32 battler2)
{
    u8 gender1 = GetBattlerGender(battler1);
    u8 gender2 = GetBattlerGender(battler2);

    return (gender1 != MON_GENDERLESS && gender2 != MON_GENDERLESS && gender1 != gender2);
}

bool32 AreBattlersOfSameGender(u32 battler1, u32 battler2)
{
    u8 gender1 = GetBattlerGender(battler1);
    u8 gender2 = GetBattlerGender(battler2);

    return (gender1 != MON_GENDERLESS && gender2 != MON_GENDERLESS && gender1 == gender2);
}

u32 CalcSecondaryEffectChance(u32 battler, u8 secondaryEffectChance)
{
    if (gBattleMoves[gCurrentMove].effect == EFFECT_FEAR_FACTOR)
    {
        if (gBattleStruct->fearFactorBasePower == 10)
            secondaryEffectChance = 15;
        else if (gBattleStruct->fearFactorBasePower == 25)
            secondaryEffectChance = 20;
        else if (gBattleStruct->fearFactorBasePower == 40)
            secondaryEffectChance = 25;
        else if (gBattleStruct->fearFactorBasePower == 55)
            secondaryEffectChance = 30;
        else if (gBattleStruct->fearFactorBasePower == 70)
            secondaryEffectChance = 35;
        else if (gBattleStruct->fearFactorBasePower == 85)
            secondaryEffectChance = 40;
        else if (gBattleStruct->fearFactorBasePower == 100)
            secondaryEffectChance = 45;
        else
            secondaryEffectChance = 50;
    }
    if (gCurrentMove == MOVE_ASTRAL_BARRAGE && gBattleStruct->faintedMonCount[GetBattlerSide(battler)] != 0)
        secondaryEffectChance = 20 + (10 * gBattleStruct->faintedMonCount[GetBattlerSide(battler)]);
    else if (gCurrentMove == MOVE_METEOR_MASH && gFieldStatuses & STATUS_FIELD_GRAVITY)
        secondaryEffectChance = 100;
    else if ((CanUseLastResort(battler) && gCurrentMove == MOVE_ANCIENT_POWER) || (gBattleMons[gBattlerTarget].status1 & STATUS1_PANIC && gCurrentMove == MOVE_OMINOUS_WIND))
        secondaryEffectChance *= 3;
    else if (gBattleMoves[gCurrentMove].effect == EFFECT_ATTACK_ORDER && gBattleStruct->sameMoveTurns[gBattlerAttacker] != 0)
        secondaryEffectChance = 30 + (10 * gBattleStruct->sameMoveTurns[gBattlerAttacker]);
    else if (CountBattlerSpeedDecreases(gBattlerTarget) > 0 && gCurrentMove == MOVE_FREEZING_GLARE)
        secondaryEffectChance *= CountBattlerSpeedDecreases(gBattlerTarget) + 1;
    else if (gSideStatuses[GetBattlerSide(gBattlerTarget)] & SIDE_STATUS_TAILWIND && gCurrentMove == MOVE_WICKED_WINDS)
        secondaryEffectChance = 100;
    else if (CountBattlerStatDecreases(gBattlerTarget, TRUE) > 0 && gCurrentMove == MOVE_LICK)
        secondaryEffectChance *= CountBattlerStatDecreases(gBattlerTarget, TRUE) + 1;
    else if (CountBattlerDefenseIncreases(gBattlerAttacker) > 0 && gCurrentMove == MOVE_METAL_CLAW)
        secondaryEffectChance *= CountBattlerDefenseIncreases(gBattlerAttacker) + 1;
    else if (CountBattlerSpecialAttackIncreases(gBattlerAttacker) > 0 && CountBattlerSpecialDefenseIncreases(gBattlerAttacker) > 0 && gCurrentMove == MOVE_PSYBEAM)
        secondaryEffectChance *= CountBattlerSpecialAttackIncreases(gBattlerAttacker) + CountBattlerSpecialDefenseIncreases(gBattlerAttacker) + 1;
    else if (GetBattlerAbility(battler) == ABILITY_SERENE_GRACE 
    || GetBattlerAbility(battler) == ABILITY_RISKTAKER
    || IsAbilityOnSide(battler, ABILITY_SERENE_AURA) 
    || (GetBattlerAbility(battler) == ABILITY_FROST_JAW && gBattleMoves[gCurrentMove].bitingMove)
    || (GetBattlerAbility(battler) == ABILITY_FIREBRAND && 
    (gBattleMoves[gCurrentMove].effect == EFFECT_BURN_HIT 
    || gBattleMoves[gCurrentMove].effect == EFFECT_BURNING_ENVY
    || gBattleMoves[gCurrentMove].effect == EFFECT_INFERNAL_PARADE
    || gBattleMoves[gCurrentMove].effect == EFFECT_BLAZING_SOUL)))
        secondaryEffectChance *= 2;
    else if (IsBattlerTerrainAffected(battler, STATUS_FIELD_MISTY_TERRAIN)
    && gBattleMoves[gCurrentMove].effect != EFFECT_FLINCH_HIT
    && gBattleMoves[gCurrentMove].effect != EFFECT_FLINCH_STATUS 
    && gBattleMoves[gCurrentMove].effect != EFFECT_TRIPLE_ARROWS)
        secondaryEffectChance *= 1.5;

    if (GetBattlerAbility(battler) == ABILITY_SHUNYONG && (gBattleMons[battler].hp <= (gBattleMons[battler].maxHP / 2)))
        secondaryEffectChance *= 2;

    if (GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_METAL_COAT
        && !(gBattleScripting.moveEffect & MOVE_EFFECT_AFFECTS_USER))
    secondaryEffectChance /= 2;

    return secondaryEffectChance;
}

bool32 IsAlly(u32 battlerAtk, u32 battlerDef)
{
    return (GetBattlerSide(battlerAtk) == GetBattlerSide(battlerDef));
}

bool32 IsGen6ExpShareEnabled(void)
{
#if I_EXP_SHARE_FLAG <= TEMP_FLAGS_END
    return FALSE;
#else
    return FlagGet(I_EXP_SHARE_FLAG);
#endif
}

u8 GetBattlerType(u32 battler, u8 typeIndex)
{
    u16 types[3] = {0};
    types[0] = gBattleMons[battler].type1;
    types[1] = gBattleMons[battler].type2;
    types[2] = gBattleMons[battler].type3;

    // Handle Roost's Flying-type suppression
    if (typeIndex == 0 || typeIndex == 1)
    {
        if (gBattleResources->flags->flags[battler] & RESOURCE_FLAG_ROOST)
        {
            if (types[0] == TYPE_FLYING && types[1] == TYPE_FLYING)
#if B_ROOST_PURE_FLYING >= GEN_5
                return TYPE_NORMAL;
#else
                return TYPE_MYSTERY;
#endif
            else
                return types[typeIndex] == TYPE_FLYING ? TYPE_MYSTERY : types[typeIndex];
        }
    }

    return types[typeIndex];
}

static u32 BufferStatusCondition(u32 battler, bool32 checkStatus2)
{
    u32 ret = 0;

    if (gBattleMons[battler].status1 & STATUS1_PSN_ANY)
    {
        StringCopy(gBattleTextBuff1, gText_Poison);
        ret++;
    }
    if (gBattleMons[battler].status1 & STATUS1_SLEEP_ANY)
    {
        gBattleMons[battler].status2 &= ~STATUS2_NIGHTMARE;
        StringCopy(gBattleTextBuff1, gText_Sleep);
        ret++;
    }
    if (gBattleMons[battler].status1 & STATUS1_PARALYSIS)
    {
        StringCopy(gBattleTextBuff1, gText_Paralysis);
        ret++;
    }
    if (gBattleMons[battler].status1 & STATUS1_BURN)
    {
        StringCopy(gBattleTextBuff1, gText_Burn);
        ret++;
    }
    if (gBattleMons[battler].status1 & STATUS1_FREEZE || gBattleMons[battler].status1 & STATUS1_FROSTBITE)
    {
        StringCopy(gBattleTextBuff1, gText_Ice);
        ret++;
    }
    if (gBattleMons[battler].status1 & STATUS1_PANIC)
    {
        StringCopy(gBattleTextBuff1, gText_Panic);
        ret++;
    }
    if (gBattleMons[battler].status1 & STATUS1_EXPOSED)
    {
        StringCopy(gBattleTextBuff1, gText_Exposed);
        ret++;
    }
    if (gBattleMons[battler].status1 & STATUS1_REST)
    {
        StringCopy(gBattleTextBuff1, gText_RestStatus);
        ret++;
    }
    
    if (checkStatus2) 
    {
        if (gBattleMons[battler].status2 & STATUS2_CONFUSION)
        {
            StringCopy(gBattleTextBuff1, gText_Confusion);
            ret++;
        }
    }

    return ret;
}
