#include "global.h"
#include "main.h"
#include "malloc.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_util.h"
#include "battle_ai_main.h"
#include "battle_factory.h"
#include "battle_setup.h"
#include "battle_z_move.h"
#include "data.h"
#include "debug.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "random.h"
#include "recorded_battle.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/battle_move_effects.h"
#include "constants/hold_effects.h"
#include "constants/moves.h"
#include "constants/items.h"

#define AI_ACTION_DONE          (1 << 0)
#define AI_ACTION_FLEE          (1 << 1)
#define AI_ACTION_WATCH         (1 << 2)
#define AI_ACTION_DO_NOT_ATTACK (1 << 3)

static u32 ChooseMoveOrAction_Singles(u32 battlerAi);
static u32 ChooseMoveOrAction_Doubles(u32 battlerAi);
static u32 ChooseMoveOrAction_Shunyong(u32 battlerAi);
static inline void BattleAI_DoAIProcessing(struct AI_ThinkingStruct *aiThink, u32 battler);
static bool32 IsPinchBerryItemEffect(u32 holdEffect);

// ewram
EWRAM_DATA const u8 *gAIScriptPtr = NULL;   // Still used in contests
EWRAM_DATA u8 sBattler_AI = 0;

// const rom data
static s32 AI_CheckBadMove(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_TryToFaint(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_CheckViability(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_SetupFirstTurn(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_Risky(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_PreferStrongestMove(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_PreferBatonPass(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_HPAware(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_Roaming(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_Safari(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_FirstBattle(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_DoubleBattle(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
static s32 AI_JuansTrick(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);

#define MAX_SHUNYONG_MOVES  10
// defense form
static const u16 sShunyongMoves[MAX_SHUNYONG_MOVES] = {
    MOVE_GOLD_PLAINS,
    MOVE_DOWNFALL,
    MOVE_MAGIC_COAT,
    MOVE_STRANGE_STEAM,
    MOVE_BRICK_BREAK,
    MOVE_SLUDGE_WAVE,
    MOVE_WYVERN_WAVE,
    MOVE_EERIE_IMPULSE,
    MOVE_DEMOLISHER,
};

// offense form
static const u16 sShunyongGoldenOffenseMoves[MAX_SHUNYONG_MOVES] = {
    MOVE_GOLD_PLAINS,
    MOVE_MT_SPLENDOR,
    MOVE_SEARING_SHOT,
    MOVE_VITAL_THROW,
    MOVE_FEAR_FACTOR,
    MOVE_OBLIVION_WING,
    MOVE_BLEAKWIND_STORM,
    MOVE_DEMOLISHER,
};

static s32 (*const sBattleAiFuncTable[])(u32, u32, u32, s32) =
{
    [0] = AI_CheckBadMove,           // AI_FLAG_CHECK_BAD_MOVE
    [1] = AI_TryToFaint,             // AI_FLAG_TRY_TO_FAINT
    [2] = AI_CheckViability,         // AI_FLAG_CHECK_VIABILITY
    [3] = AI_SetupFirstTurn,         // AI_FLAG_SETUP_FIRST_TURN
    [4] = AI_Risky,                  // AI_FLAG_RISKY
    [5] = AI_PreferStrongestMove,    // AI_FLAG_PREFER_STRONGEST_MOVE
    [6] = AI_PreferBatonPass,        // AI_FLAG_PREFER_BATON_PASS
    [7] = AI_DoubleBattle,           // AI_FLAG_DOUBLE_BATTLE
    [8] = AI_HPAware,                // AI_FLAG_HP_AWARE
    [9] = NULL,                      // AI_FLAG_WHO
    [10] = NULL,                     // AI_FLAG_WILL_SUICIDE
    [11] = NULL,                     // AI_FLAG_HELP_PARTNER
    [12] = NULL,                     // Unused
    [13] = NULL,                     // Unused
    [14] = NULL,                     // Unused
    [15] = NULL,                     // Unused
    [16] = NULL,                     // Unused
    [17] = NULL,                     // Unused
    [18] = NULL,                     // Unused
    [19] = NULL,                     // Unused
    [20] = NULL,                     // Unused
    [21] = NULL,                     // Unused
    [22] = NULL,                     // Unused
    [23] = NULL,                     // Unused
    [24] = NULL,                     // Unused
    [25] = NULL,                     // Unused
    [26] = NULL,                     // Unused
    [27] = NULL,                     // Unused
    [28] = NULL,                     // Unused
    [29] = AI_Roaming,              // AI_FLAG_ROAMING
    [30] = AI_Safari,               // AI_FLAG_SAFARI
    [31] = AI_FirstBattle,          // AI_FLAG_FIRST_BATTLE
};

// Functions
void BattleAI_SetupItems(void)
{
    s32 i;
    u8 *data = (u8 *)BATTLE_HISTORY;

    for (i = 0; i < sizeof(struct BattleHistory); i++)
        data[i] = 0;

    // Items are allowed to use in ONLY trainer battles.
    if ((gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        && !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_SAFARI | BATTLE_TYPE_BATTLE_TOWER
                               | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_SECRET_BASE | BATTLE_TYPE_FRONTIER
                               | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_RECORDED_LINK)
            )
       )
    {
        for (i = 0; i < MAX_TRAINER_ITEMS; i++)
        {
            if (gTrainers[gTrainerBattleOpponent_A].items[i] != 0)
            {
                BATTLE_HISTORY->trainerItems[BATTLE_HISTORY->itemsNo] = gTrainers[gTrainerBattleOpponent_A].items[i];
                BATTLE_HISTORY->itemsNo++;
            }
        }
    }
}

static u32 GetWildAiFlags(void)
{
    u32 avgLevel = GetMonData(&gEnemyParty[0], MON_DATA_LEVEL);
    u32 flags;

    if (IsDoubleBattle())
        avgLevel = (GetMonData(&gEnemyParty[0], MON_DATA_LEVEL) + GetMonData(&gEnemyParty[1], MON_DATA_LEVEL)) / 2;

    flags |= AI_FLAG_CHECK_BAD_MOVE;
    if (avgLevel >= 20)
        flags |= AI_FLAG_CHECK_VIABILITY;
    if (avgLevel >= 60)
        flags |= AI_FLAG_PREFER_STRONGEST_MOVE;
    if (avgLevel >= 80)
        flags |= AI_FLAG_HP_AWARE;

#if B_VAR_WILD_AI_FLAGS != 0
    if (VarGet(B_VAR_WILD_AI_FLAGS) != 0)
        flags |= VarGet(B_VAR_WILD_AI_FLAGS);
#endif

    return flags;
}

void BattleAI_SetupFlags(void)
{
#if DEBUG_OVERWORLD_MENU == TRUE
    if (gIsDebugBattle)
        AI_THINKING_STRUCT->aiFlags = gDebugAIFlags;
    else
#endif
    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        AI_THINKING_STRUCT->aiFlags = GetAiScriptsInRecordedBattle();
    else if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        AI_THINKING_STRUCT->aiFlags = AI_FLAG_SAFARI;
    else if (gBattleTypeFlags & BATTLE_TYPE_ROAMER)
        AI_THINKING_STRUCT->aiFlags = AI_FLAG_ROAMING;
    else if (gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE)
        AI_THINKING_STRUCT->aiFlags = AI_FLAG_FIRST_BATTLE;
    else if (gBattleTypeFlags & BATTLE_TYPE_FACTORY)
        AI_THINKING_STRUCT->aiFlags = GetAiScriptsInBattleFactory();
    else if (gBattleTypeFlags & (BATTLE_TYPE_FRONTIER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_TRAINER_HILL | BATTLE_TYPE_SECRET_BASE))
        AI_THINKING_STRUCT->aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT;
    else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
        AI_THINKING_STRUCT->aiFlags = gTrainers[gTrainerBattleOpponent_A].aiFlags | gTrainers[gTrainerBattleOpponent_B].aiFlags;
    else
        AI_THINKING_STRUCT->aiFlags = gTrainers[gTrainerBattleOpponent_A].aiFlags;

    // check smart wild AI
    if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_TRAINER)) && IsWildMonSmart())
        AI_THINKING_STRUCT->aiFlags |= GetWildAiFlags();

    if (gBattleTypeFlags & (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS) || gTrainers[gTrainerBattleOpponent_A].doubleBattle)
        AI_THINKING_STRUCT->aiFlags |= AI_FLAG_DOUBLE_BATTLE; // Act smart in doubles and don't attack your partner.
}

// sBattler_AI set in ComputeBattleAiScores
void BattleAI_SetupAIData(u8 defaultScoreMoves, u32 battler)
{
    s32 i, move, dmg;
    u8 moveLimitations;

    // Clear AI data but preserve the flags.
    u32 flags = AI_THINKING_STRUCT->aiFlags;
    memset(AI_THINKING_STRUCT, 0, sizeof(struct AI_ThinkingStruct));
    AI_THINKING_STRUCT->aiFlags = flags;

    // Conditional score reset, unlike Ruby.
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (defaultScoreMoves & 1)
            AI_THINKING_STRUCT->score[i] = 100;
        else
            AI_THINKING_STRUCT->score[i] = 0;

        defaultScoreMoves >>= 1;
    }

    moveLimitations = AI_DATA->moveLimitations[battler];

    // Ignore moves that aren't possible to use.
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (gBitTable[i] & moveLimitations)
            AI_THINKING_STRUCT->score[i] = 0;
    }

    //sBattler_AI = battler;
    gBattlerTarget = SetRandomTarget(sBattler_AI);
    gBattleStruct->aiChosenTarget[sBattler_AI] = gBattlerTarget;
}

u32 BattleAI_ChooseMoveOrAction(void)
{
    u32 ret;
    
    if (IsShunyongBattle())
        ret = ChooseMoveOrAction_Shunyong(sBattler_AI);
    else if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
        ret = ChooseMoveOrAction_Singles(sBattler_AI);
    else
        ret = ChooseMoveOrAction_Doubles(sBattler_AI);

    // Clear protect structures, some flags may be set during AI calcs
    // e.g. pranksterElevated from GetMovePriority
    memset(&gProtectStructs, 0, MAX_BATTLERS_COUNT * sizeof(struct ProtectStruct));
    return ret;
}

// damages/other info computed in GetAIDataAndCalcDmg
u32 ComputeBattleAiScores(u32 battler)
{
    sBattler_AI = battler;
    BattleAI_SetupAIData(0xF, sBattler_AI);
    return BattleAI_ChooseMoveOrAction();
}

static void CopyBattlerDataToAIParty(u32 bPosition, u32 side)
{
    u32 battler = GetBattlerAtPosition(bPosition);
    struct AiPartyMon *aiMon = &AI_PARTY->mons[side][gBattlerPartyIndexes[battler]];
    struct BattlePokemon *bMon = &gBattleMons[battler];

    aiMon->species = bMon->species;
    aiMon->level = bMon->level;
    aiMon->status = bMon->status1;
    aiMon->gender = GetBattlerGender(battler);
    aiMon->isFainted = FALSE;
    aiMon->wasSentInBattle = TRUE;
    aiMon->switchInCount++;
}

void Ai_InitPartyStruct(void)
{
    u32 i;
    bool32 isOmniscient = (AI_THINKING_STRUCT->aiFlags & AI_FLAG_OMNISCIENT);
    struct Pokemon *mon;

    AI_PARTY->count[B_SIDE_PLAYER] = gPlayerPartyCount;
    AI_PARTY->count[B_SIDE_OPPONENT] = gEnemyPartyCount;

    // Save first 2 or 4(in doubles) mons
    CopyBattlerDataToAIParty(B_POSITION_PLAYER_LEFT, B_SIDE_PLAYER);
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        CopyBattlerDataToAIParty(B_POSITION_PLAYER_RIGHT, B_SIDE_PLAYER);

    // If player's partner is AI, save opponent mons
    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
    {
        CopyBattlerDataToAIParty(B_POSITION_OPPONENT_LEFT, B_SIDE_OPPONENT);
        CopyBattlerDataToAIParty(B_POSITION_OPPONENT_RIGHT, B_SIDE_OPPONENT);
    }

    // Find fainted mons
    for (i = 0; i < AI_PARTY->count[B_SIDE_PLAYER]; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_HP) == 0)
            AI_PARTY->mons[B_SIDE_PLAYER][i].isFainted = TRUE;

        if (isOmniscient)
        {
            u32 j;
            mon = &gPlayerParty[i];
            AI_PARTY->mons[B_SIDE_PLAYER][i].item = GetMonData(mon, MON_DATA_HELD_ITEM);
            AI_PARTY->mons[B_SIDE_PLAYER][i].heldEffect = ItemId_GetHoldEffect(AI_PARTY->mons[B_SIDE_PLAYER][i].item);
            AI_PARTY->mons[B_SIDE_PLAYER][i].ability = GetMonAbility(mon);
            for (j = 0; j < MAX_MON_MOVES; j++)
                AI_PARTY->mons[B_SIDE_PLAYER][i].moves[j] = GetMonData(mon, MON_DATA_MOVE1 + j);
        }
    }
}

void Ai_UpdateSwitchInData(u32 battler)
{
    u32 i;
    u32 side = GetBattlerSide(battler);
    struct AiPartyMon *aiMon = &AI_PARTY->mons[side][gBattlerPartyIndexes[battler]];

    // See if the switched-in mon has been already in battle
    if (aiMon->wasSentInBattle)
    {
        if (aiMon->ability)
            BATTLE_HISTORY->abilities[battler] = aiMon->ability;
        if (aiMon->heldEffect)
            BATTLE_HISTORY->itemEffects[battler] = aiMon->heldEffect;
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            if (aiMon->moves[i])
                BATTLE_HISTORY->usedMoves[battler][i] = aiMon->moves[i];
        }
        aiMon->switchInCount++;
        aiMon->status = gBattleMons[battler].status1; // Copy status, because it could've been changed in battle.
    }
    else // If not, copy the newly switched-in mon in battle and clear battle history.
    {
        ClearBattlerMoveHistory(battler);
        ClearBattlerAbilityHistory(battler);
        ClearBattlerItemEffectHistory(battler);
        CopyBattlerDataToAIParty(GetBattlerPosition(battler), side);
    }
}

void Ai_UpdateFaintData(u32 battler)
{
    struct AiPartyMon *aiMon = &AI_PARTY->mons[GetBattlerSide(battler)][gBattlerPartyIndexes[battler]];
    ClearBattlerMoveHistory(battler);
    ClearBattlerAbilityHistory(battler);
    ClearBattlerItemEffectHistory(battler);
    aiMon->isFainted = TRUE;
}

static void SetBattlerAiData(u32 battler, struct AiLogicData *aiData)
{
    u32 ability, holdEffect;

    ability = aiData->abilities[battler] = AI_GetAbility(battler);
    aiData->items[battler] = gBattleMons[battler].item;
    holdEffect = aiData->holdEffects[battler] = AI_GetHoldEffect(battler);
    aiData->holdEffectParams[battler] = GetBattlerHoldEffectParam(battler);
    aiData->predictedMoves[battler] = gLastMoves[battler];
    aiData->hpPercents[battler] = GetHealthPercentage(battler);
    aiData->moveLimitations[battler] = CheckMoveLimitations(battler, 0, MOVE_LIMITATIONS_ALL);
    aiData->speedStats[battler] = GetBattlerTotalSpeedStatArgs(battler, ability, holdEffect);
}

static void SetBattlerAiMovesData(struct AiLogicData *aiData, u32 battlerAtk, u32 battlersCount)
{
    u32 battlerDef, i, weather;
    u16 *moves;

    // Simulate dmg for both ai controlled mons and for player controlled mons.
    SaveBattlerData(battlerAtk);
    moves = GetMovesArray(battlerAtk);
    weather = AI_GetWeather(aiData);
    for (battlerDef = 0; battlerDef < battlersCount; battlerDef++)
    {
        if (battlerAtk == battlerDef)
            continue;

        SaveBattlerData(battlerDef);
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            s32 dmg = 0;
            u8 effectiveness = AI_EFFECTIVENESS_x0;
            u32 move = moves[i];

            if (move != 0
             && move != 0xFFFF
             //&& gBattleMoves[move].power != 0  /* we want to get effectiveness of status moves */
             && !(aiData->moveLimitations[battlerAtk] & gBitTable[i])) {
                dmg = AI_CalcDamage(move, battlerAtk, battlerDef, &effectiveness, TRUE, weather);
            }

            aiData->simulatedDmg[battlerAtk][battlerDef][i] = dmg;
            aiData->effectiveness[battlerAtk][battlerDef][i] = effectiveness;
        }
    }
    SetMoveDamageResult(battlerAtk, moves);
}

void SetAiLogicDataForTurn(struct AiLogicData *aiData)
{
    u32 battlerAtk, battlersCount;

    memset(aiData, 0, sizeof(struct AiLogicData));
    if (!(gBattleTypeFlags & BATTLE_TYPE_HAS_AI) && !IsWildMonSmart())
        return;
    
    if (IsShunyongBattle())
        return;

    // Set delay timer to count how long it takes for AI to choose action/move
    gBattleStruct->aiDelayTimer = gMain.vblankCounter1;

    aiData->weatherHasEffect = WEATHER_HAS_EFFECT;
    // get/assume all battler data and simulate AI damage
    battlersCount = gBattlersCount;
    for (battlerAtk = 0; battlerAtk < battlersCount; battlerAtk++)
    {
        if (!IsBattlerAlive(battlerAtk))
            continue;

        SetBattlerAiData(battlerAtk, aiData);
        SetBattlerAiMovesData(aiData, battlerAtk, battlersCount);
    }
}

static bool32 AI_SwitchMonIfSuitable(u32 battler)
{
    u32 monToSwitchId = GetMostSuitableMonToSwitchInto(battler);
    if (monToSwitchId != PARTY_SIZE)
    {
        AI_DATA->shouldSwitchMon |= gBitTable[battler];
        AI_DATA->monToSwitchId[battler] = monToSwitchId;
        return TRUE;
    }
    return FALSE;
}

static bool32 AI_ShouldSwitchIfBadMoves(u32 battler, bool32 doubleBattle)
{
    u32 i, j;
    // If can switch.
    if (CountUsablePartyMons(battler) > 0
        && !IsBattlerTrapped(battler, TRUE)
        && !(gBattleTypeFlags & (BATTLE_TYPE_ARENA | BATTLE_TYPE_PALACE))
        && AI_THINKING_STRUCT->aiFlags & (AI_FLAG_CHECK_VIABILITY | AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_PREFER_BATON_PASS))
    {
        // Consider switching if all moves are worthless to use.
        if (GetTotalBaseStat(gBattleMons[battler].species) >= 310 // Mon is not weak.
            && gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 2) // Mon has more than 50% of its HP
        {
            s32 cap = AI_THINKING_STRUCT->aiFlags & (AI_FLAG_CHECK_VIABILITY) ? 95 : 93;
            if (doubleBattle)
            {
                for (i = 0; i < MAX_BATTLERS_COUNT; i++)
                {
                    if (i != battler && IsBattlerAlive(i))
                    {
                        for (j = 0; j < MAX_MON_MOVES; j++)
                        {
                            if (gBattleStruct->aiFinalScore[battler][i][j] > cap)
                                break;
                        }
                        if (j != MAX_MON_MOVES)
                            break;
                    }
                }
                if (i == MAX_BATTLERS_COUNT && AI_SwitchMonIfSuitable(battler))
                    return TRUE;
            }
            else
            {
                for (i = 0; i < MAX_MON_MOVES; i++)
                {
                    if (AI_THINKING_STRUCT->score[i] > cap)
                        break;
                }

                if (i == MAX_MON_MOVES && AI_SwitchMonIfSuitable(battler))
                    return TRUE;
            }

        }

        // Consider switching if your mon with truant is bodied by Protect spam.
        // Or is using a double turn semi invulnerable move(such as Fly) and is faster.
        if (GetBattlerAbility(battler) == ABILITY_TRUANT
            && IsTruantMonVulnerable(battler, gBattlerTarget)
            && gDisableStructs[battler].truantCounter
            && gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 2
            && AI_SwitchMonIfSuitable(battler))
        {
            return TRUE;
        }
    }
    return FALSE;
}

static u32 ChooseMoveOrAction_Singles(u32 battlerAi)
{
    u8 currentMoveArray[MAX_MON_MOVES];
    u8 consideredMoveArray[MAX_MON_MOVES];
    u32 numOfBestMoves;
    s32 i, id;
    u32 flags = AI_THINKING_STRUCT->aiFlags;

    AI_DATA->partnerMove = 0;   // no ally
    while (flags != 0)
    {
        if (flags & 1)
        {
            BattleAI_DoAIProcessing(AI_THINKING_STRUCT, battlerAi);
        }
        flags >>= 1;
        AI_THINKING_STRUCT->aiLogicId++;
    }

    for (i = 0; i < MAX_MON_MOVES; i++) {
        gBattleStruct->aiFinalScore[battlerAi][gBattlerTarget][i] = AI_THINKING_STRUCT->score[i];
    }

    // Check special AI actions.
    if (AI_THINKING_STRUCT->aiAction & AI_ACTION_FLEE)
        return AI_CHOICE_FLEE;
    if (AI_THINKING_STRUCT->aiAction & AI_ACTION_WATCH)
        return AI_CHOICE_WATCH;

    // Switch mon if there are no good moves to use.
    if (AI_ShouldSwitchIfBadMoves(battlerAi, FALSE))
        return AI_CHOICE_SWITCH;

    numOfBestMoves = 1;
    currentMoveArray[0] = AI_THINKING_STRUCT->score[0];
    consideredMoveArray[0] = 0;

    for (i = 1; i < MAX_MON_MOVES; i++)
    {
        if (gBattleMons[battlerAi].moves[i] != MOVE_NONE)
        {
            // In ruby, the order of these if statements is reversed.
            if (currentMoveArray[0] == AI_THINKING_STRUCT->score[i])
            {
                currentMoveArray[numOfBestMoves] = AI_THINKING_STRUCT->score[i];
                consideredMoveArray[numOfBestMoves++] = i;
            }
            if (currentMoveArray[0] < AI_THINKING_STRUCT->score[i])
            {
                numOfBestMoves = 1;
                currentMoveArray[0] = AI_THINKING_STRUCT->score[i];
                consideredMoveArray[0] = i;
            }
        }
    }
    return consideredMoveArray[Random() % numOfBestMoves];
}

static u32 ChooseMoveOrAction_Shunyong(u32 battlerAi)
{
    const u16 *moves = (gBattleMons[1].species == SPECIES_SHUNYONG) ? sShunyongMoves : sShunyongGoldenOffenseMoves;
    s32 battlerDef, dmg, i, j, score, bestScore;
    s32 moveidx = 0;
    u32 flags, move, viableMoveCount;
    u8 effectiveness;
    u32 weather;

    u16 *bestMoves;
    u8 *bestTargets;
    
    if (battlerAi == B_POSITION_OPPONENT_RIGHT)
        return 0;
    
    bestMoves = AllocZeroed(sizeof(u16) * 2 * (MAX_SHUNYONG_MOVES+1));
    bestTargets = AllocZeroed(sizeof(u8) * 2 * (MAX_SHUNYONG_MOVES+1));
    
    bestScore = -1;
    
    // get AI assumed info, e.g. abilities
    SetBattlerAiData(battlerAi, AI_DATA);
    SetBattlerAiData(B_POSITION_PLAYER_LEFT, AI_DATA);
    
    // backup battlemons
    SaveBattlerData(battlerAi);
    SetBattlerData(battlerAi);
    
    weather = AI_GetWeather(AI_DATA);

    // loop through moves/targets
    for (battlerDef = 0; battlerDef < MAX_BATTLERS_COUNT; battlerDef++)
    {
        if (GetBattlerSide(battlerDef) == B_SIDE_OPPONENT
                || !IsBattlerAlive(battlerDef))
        {
            continue;
        }
        else
        {
            BattleAI_SetupAIData(0xF, battlerAi);
            gBattlerTarget = battlerDef;
            AI_DATA->partnerMove = MOVE_NONE;
            AI_THINKING_STRUCT->movesetIndex = 0;
            for (moveidx = 0; moveidx < MAX_SHUNYONG_MOVES; moveidx++)
            {
                move = moves[moveidx];
                if (move == 0)
                    continue;
                if (IsMoveUnusable(battlerAi, move, 1, MOVE_LIMITATIONS_ALL))
                    continue;
                
                // backup gBattleMons, set assumed battler data
                SaveBattlerData(battlerDef);
                SetBattlerData(battlerDef);
                // compute dmg, effectiveness
                effectiveness = AI_EFFECTIVENESS_x0;
                dmg = AI_CalcDamage(move, battlerAi, battlerDef, &effectiveness, TRUE, weather);
                
                AI_THINKING_STRUCT->movesetIndex = 0;
                AI_THINKING_STRUCT->moveConsidered = move;
                AI_DATA->simulatedDmg[battlerAi][battlerDef][AI_THINKING_STRUCT->movesetIndex] = dmg;
                AI_DATA->effectiveness[battlerAi][battlerDef][AI_THINKING_STRUCT->movesetIndex] = effectiveness;
        
                // compute score
                score = 100;
                AI_THINKING_STRUCT->aiLogicId = 0;
                flags = AI_THINKING_STRUCT->aiFlags;
                while (flags != 0)
                {
                    if (flags & 1)
                    {
                        //BattleAI_DoAIProcessing(AI_THINKING_STRUCT, battlerAi);
                        if (AI_THINKING_STRUCT->aiLogicId < ARRAY_COUNT(sBattleAiFuncTable)
                              && sBattleAiFuncTable[AI_THINKING_STRUCT->aiLogicId] != NULL) {
                            // Call AI function
                            score = sBattleAiFuncTable[AI_THINKING_STRUCT->aiLogicId](battlerAi, gBattlerTarget, move, score);
                        }
                    }
                    flags >>= 1;
                    AI_THINKING_STRUCT->aiLogicId++;
                } // flags
                
                // restore gBattleMons
                RestoreBattlerData(battlerDef);
                
                if (bestScore == -1)
                {
                    bestMoves[0] = moves[0];
                    bestTargets[0] = 0;
                    viableMoveCount = 1;
                    bestScore = score;
                }
                else
                {
                    if (score > bestScore)
                    {
                        bestMoves[0] = move;
                        bestTargets[0] = battlerDef;
                        bestScore = score;
                        viableMoveCount = 1;
                    }
                    else if (score == bestScore)
                    {
                        bestMoves[viableMoveCount] = move;
                        bestTargets[viableMoveCount] = battlerDef;
                        viableMoveCount++;
                    }
                }
                
                // DebugPrintfLevel(MGBA_LOG_WARN, "attacker %d tgt %d move %d score %d", battlerAi, gBattlerTarget, move, score);
            } // moves loop
        }
    }

    i = Random() % viableMoveCount;
    gBattleMons[battlerAi].moves[0] = bestMoves[i];
    gBattleMons[battlerAi].pp[0] = 1; // can always use (TODO maybe not?)
    gBattleStruct->aiChosenTarget[battlerAi] = bestTargets[i];
    
    // DebugPrintfLevel(MGBA_LOG_WARN, "Shunyong choosing move %d index %d targeting %d", bestMoves[i], i, bestTargets[i]);
    
    Free(bestMoves);
    Free(bestTargets);
    return 0;
}

static u32 ChooseMoveOrAction_Doubles(u32 battlerAi)
{
    s32 i, j;
    u32 flags;
    s32 bestMovePointsForTarget[MAX_BATTLERS_COUNT];
    u8 mostViableTargetsArray[MAX_BATTLERS_COUNT];
    u8 actionOrMoveIndex[MAX_BATTLERS_COUNT];
    s32 mostViableMovesScores[MAX_MON_MOVES];
    u8 mostViableMovesIndices[MAX_MON_MOVES];
    u32 mostViableTargetsNo;
    u32 mostViableMovesNo;
    s32 mostMovePoints;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (i == battlerAi || gBattleMons[i].hp == 0)
        {
            actionOrMoveIndex[i] = 0xFF;
            bestMovePointsForTarget[i] = -1;
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
                BattleAI_SetupAIData(gBattleStruct->palaceFlags >> 4, battlerAi);
            else
                BattleAI_SetupAIData(0xF, battlerAi);

            gBattlerTarget = i;

            AI_DATA->partnerMove = GetAllyChosenMove(i);
            AI_THINKING_STRUCT->aiLogicId = 0;
            AI_THINKING_STRUCT->movesetIndex = 0;
            flags = AI_THINKING_STRUCT->aiFlags;
            while (flags != 0)
            {
                if (flags & 1)
                {
                    BattleAI_DoAIProcessing(AI_THINKING_STRUCT, battlerAi);
                }
                flags >>= 1;
                AI_THINKING_STRUCT->aiLogicId++;
            }

            if (AI_THINKING_STRUCT->aiAction & AI_ACTION_FLEE)
            {
                actionOrMoveIndex[i] = AI_CHOICE_FLEE;
            }
            else if (AI_THINKING_STRUCT->aiAction & AI_ACTION_WATCH)
            {
                actionOrMoveIndex[i] = AI_CHOICE_WATCH;
            }
            else
            {
                mostViableMovesScores[0] = AI_THINKING_STRUCT->score[0];
                mostViableMovesIndices[0] = 0;
                mostViableMovesNo = 1;
                for (j = 1; j < MAX_MON_MOVES; j++)
                {
                    if (gBattleMons[battlerAi].moves[j] != 0)
                    {
                        if (!CanTargetBattler(battlerAi, i, gBattleMons[battlerAi].moves[j]))
                            continue;

                        if (mostViableMovesScores[0] == AI_THINKING_STRUCT->score[j])
                        {
                            mostViableMovesScores[mostViableMovesNo] = AI_THINKING_STRUCT->score[j];
                            mostViableMovesIndices[mostViableMovesNo] = j;
                            mostViableMovesNo++;
                        }
                        if (mostViableMovesScores[0] < AI_THINKING_STRUCT->score[j])
                        {
                            mostViableMovesScores[0] = AI_THINKING_STRUCT->score[j];
                            mostViableMovesIndices[0] = j;
                            mostViableMovesNo = 1;
                        }
                    }
                }
                actionOrMoveIndex[i] = mostViableMovesIndices[Random() % mostViableMovesNo];
                bestMovePointsForTarget[i] = mostViableMovesScores[0];

                // Don't use a move against ally if it has less than 100 points.
                if (i == BATTLE_PARTNER(battlerAi) && bestMovePointsForTarget[i] < 100)
                {
                    bestMovePointsForTarget[i] = -1;
                }
            }

            for (j = 0; j < MAX_MON_MOVES; j++) {
                gBattleStruct->aiFinalScore[battlerAi][gBattlerTarget][j] = AI_THINKING_STRUCT->score[j];
            }
        }
    }

    // Switch mon if all of the moves are bad to use against any of the target.
    if (AI_ShouldSwitchIfBadMoves(battlerAi, TRUE))
        return AI_CHOICE_SWITCH;

    mostMovePoints = bestMovePointsForTarget[0];
    mostViableTargetsArray[0] = 0;
    mostViableTargetsNo = 1;

    for (i = 1; i < MAX_BATTLERS_COUNT; i++)
    {
        if (mostMovePoints == bestMovePointsForTarget[i])
        {
            mostViableTargetsArray[mostViableTargetsNo] = i;
            mostViableTargetsNo++;
        }
        if (mostMovePoints < bestMovePointsForTarget[i])
        {
            mostMovePoints = bestMovePointsForTarget[i];
            mostViableTargetsArray[0] = i;
            mostViableTargetsNo = 1;
        }
    }

    gBattlerTarget = mostViableTargetsArray[Random() % mostViableTargetsNo];
    gBattleStruct->aiChosenTarget[battlerAi] = gBattlerTarget;
    return actionOrMoveIndex[gBattlerTarget];
}

static inline void BattleAI_DoAIProcessing(struct AI_ThinkingStruct *aiThink, u32 battler)
{
    do
    {
        if (gBattleMons[battler].pp[aiThink->movesetIndex] == 0)
            aiThink->moveConsidered = MOVE_NONE;
        else
            aiThink->moveConsidered = gBattleMons[battler].moves[aiThink->movesetIndex];

        if (aiThink->moveConsidered != MOVE_NONE
          && aiThink->score[aiThink->movesetIndex] > 0)
        {
            if (aiThink->aiLogicId < ARRAY_COUNT(sBattleAiFuncTable)
              && sBattleAiFuncTable[aiThink->aiLogicId] != NULL)
            {
                // Call AI function
                aiThink->score[aiThink->movesetIndex] =
                    sBattleAiFuncTable[aiThink->aiLogicId](battler,
                      gBattlerTarget,
                      aiThink->moveConsidered,
                      aiThink->score[aiThink->movesetIndex]);
            }
        }
        else
        {
            aiThink->score[aiThink->movesetIndex] = 0;
        }
        aiThink->movesetIndex++;
    } while (aiThink->movesetIndex < MAX_MON_MOVES && !(aiThink->aiAction & AI_ACTION_DO_NOT_ATTACK));

    aiThink->movesetIndex = 0;
}

// AI Score Functions
// AI_FLAG_CHECK_BAD_MOVE - decreases move scores
static s32 AI_CheckBadMove(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    // move data
    s8 atkPriority = GetMovePriority(battlerAtk, move);
    u32 moveEffect = gBattleMoves[move].effect;
    s32 moveType;
    u32 moveTarget = AI_GetBattlerMoveTargetType(battlerAtk, move);
    u32 accuracy = AI_GetMoveAccuracy(battlerAtk, battlerDef, move);
    struct AiLogicData *aiData = AI_DATA;
    u32 effectiveness = aiData->effectiveness[battlerAtk][battlerDef][AI_THINKING_STRUCT->movesetIndex];
    bool32 isDoubleBattle = IsValidDoubleBattle(battlerAtk);
    u32 i;
    u32 weather;
    u32 predictedMove = aiData->predictedMoves[battlerDef];

    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
        return score;

    SetTypeBeforeUsingMove(move, battlerAtk);
    GET_MOVE_TYPE(move, moveType);

    // check non-user target
    if (!(moveTarget & MOVE_TARGET_USER))
    {
        // handle negative checks on non-user target
        // check powder moves
        if (gBattleMoves[move].powderMove && !IsAffectedByPowder(battlerDef, aiData->abilities[battlerDef], aiData->holdEffects[battlerDef]))
        {
            RETURN_SCORE_MINUS(20);
        }

        if (IS_MOVE_STATUS(move) && predictedMove == MOVE_MIND_READER)
        {
            RETURN_SCORE_MINUS(20);
        }

        // check ground immunities
        if (moveType == TYPE_GROUND
          && !IsBattlerGrounded(battlerDef)
          && ((aiData->abilities[battlerDef] == ABILITY_LEVITATE
          && (AI_DATA->abilities[battlerDef] == ABILITY_GRAVITY_WELL && gFieldStatuses & STATUS_FIELD_GRAVITY)
          && DoesBattlerIgnoreAbilityChecks(aiData->abilities[battlerAtk], move))
          || aiData->holdEffects[battlerDef] == HOLD_EFFECT_AIR_BALLOON
          || (gStatuses3[battlerDef] & (STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS)))
          && move != MOVE_THOUSAND_ARROWS)
        {
            RETURN_SCORE_MINUS(20);
        }

        if ((moveType == TYPE_NORMAL || moveType == TYPE_FIGHTING) && aiData->abilities[battlerDef] == ABILITY_EMPTY)
        {
            RETURN_SCORE_MINUS(20);
        }

        if ((moveType == TYPE_POISON) && aiData->abilities[battlerDef] == ABILITY_IMMUNITY)
        {
            RETURN_SCORE_MINUS(20);
        }

        // check off screen
        if (IsSemiInvulnerable(battlerDef, move) && moveEffect != (EFFECT_SEMI_INVULNERABLE || EFFECT_DIG || EFFECT_DIVE || EFFECT_FLY || EFFECT_SHADOW_FORCE) && AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER)
            RETURN_SCORE_MINUS(20);    // if target off screen and we go first, don't use move

        // check if negates type
        switch (effectiveness)
        {
        case AI_EFFECTIVENESS_x0:
            RETURN_SCORE_MINUS(20);
            break;
        case AI_EFFECTIVENESS_x0_125:
        case AI_EFFECTIVENESS_x0_25:
            RETURN_SCORE_MINUS(10);
            break;
        }

        // target ability checks
        if (!DoesBattlerIgnoreAbilityChecks(aiData->abilities[battlerAtk], move))
        {
            switch (aiData->abilities[battlerDef])
            {
            case ABILITY_SUGAR_COAT:
            case ABILITY_MAGIC_GUARD:
                switch (moveEffect)
                {
                case EFFECT_POISON:
                case EFFECT_WILL_O_WISP:
                case EFFECT_TOXIC:
                case EFFECT_LEECH_SEED:
                case EFFECT_GLACIATE:
                case EFFECT_SCORP_FANG:
                case EFFECT_POISON_POWDER:
                    score -= 5;
                    break;
                case EFFECT_FROST_NOVA:
                    score -= 2;
                    break;
                case EFFECT_SEED_BOMB:
                    if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
                        score -= 5;
                    break;
                case EFFECT_CURSE:
                    if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_GHOST)) // Don't use Curse if you're a ghost type vs a Magic Guard user, they'll take no damage.
                        score -= 5;
                    break;
                }
                break;
            case ABILITY_VOLT_ABSORB:
            case ABILITY_MOTOR_DRIVE:
            case ABILITY_LIGHTNING_ROD:
                if (moveType == TYPE_ELECTRIC)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_MAGNET_PULL:
                if (moveType == TYPE_STEEL)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_WATER_ABSORB:
            case ABILITY_DRY_SKIN:
            case ABILITY_STORM_DRAIN:
                if (moveType == TYPE_WATER)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_EARTH_EATER:
                if (moveType == TYPE_GROUND)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_PINK_MIST:
                if (moveType == TYPE_PSYCHIC && AI_IsTerrainAffected(battlerDef, STATUS_FIELD_MISTY_TERRAIN))
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_EMPTY:
                if (moveType == TYPE_NORMAL || moveType == TYPE_FIGHTING)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_IMMUNITY:
                if (moveType == TYPE_POISON)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_MAGMA_ARMOR:
                if (moveType == TYPE_WATER)
                    RETURN_SCORE_MINUS(6);
                break;
            case ABILITY_TOXIC_BOOST:
                if (moveType == TYPE_POISON)
                    RETURN_SCORE_MINUS(2);
                break;
            case ABILITY_FLARE_BOOST:
                if (moveType == TYPE_FIRE)
                    RETURN_SCORE_MINUS(2);
                break;
            case ABILITY_OVERCOAT:
                if (AI_MoveMakesContact(aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk], move))
                    RETURN_SCORE_PLUS(6);
                break;
            case ABILITY_ALL_GAME:
                if (moveType == TYPE_WATER || moveType == TYPE_GROUND)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_FLASH_FIRE:
                if (moveType == TYPE_FIRE)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_WITCHCRAFT:
                if (moveType == TYPE_FAIRY)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_SOUL_LOCKER:
                if (moveType == TYPE_GHOST)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_WONDER_GUARD:
                if (effectiveness < AI_EFFECTIVENESS_x2)
                    return 0;
                break;
            case ABILITY_SAP_SIPPER:
                if (moveType == TYPE_GRASS)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_JUSTIFIED:
                if (moveType == TYPE_DARK && !IS_MOVE_STATUS(move))
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_RATTLED:
                if (!IS_MOVE_STATUS(move)
                  && (moveType == TYPE_DARK || moveType == TYPE_GHOST || moveType == TYPE_BUG))
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_SOUNDPROOF:
                if (gBattleMoves[move].soundMove)
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_CACOPHONY:
                if (gBattleMoves[move].soundMove)
                    RETURN_SCORE_MINUS(5);
                break;  
            case ABILITY_BULLETPROOF:
                if (gBattleMoves[move].ballisticMove)
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_WIND_POWER:
            case ABILITY_WIND_RIDER:
                if (gBattleMoves[move].windMove)
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_DAZZLING:
            case ABILITY_QUEENLY_MAJESTY:
                if (atkPriority > 0)
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_AROMA_VEIL:
                if (IsAromaVeilProtectedMove(move))
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_SWEET_VEIL:
                if (moveEffect == EFFECT_SLEEP || moveEffect == EFFECT_DARK_VOID || moveEffect == EFFECT_YAWN || moveEffect == EFFECT_SLEEP_POWDER || moveEffect == EFFECT_MAGIC_POWDER)
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_FLOWER_VEIL:
                if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS) && (IsNonVolatileStatusMoveEffect(moveEffect) || IsStatLoweringMoveEffect(moveEffect)))
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_MAGIC_BOUNCE:
                if (gBattleMoves[move].magicCoatAffected)
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_CONTRARY:
                if (IsStatLoweringMoveEffect(moveEffect))
                    RETURN_SCORE_MINUS(20);
                break;
            case ABILITY_CLEAR_BODY:
            case ABILITY_FULL_METAL_BODY:
            case ABILITY_WHITE_SMOKE:
            case ABILITY_TITANIC:
                if (IsStatLoweringMoveEffect(moveEffect))
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_HYPER_CUTTER:
                if ((moveEffect == EFFECT_ATTACK_DOWN ||  moveEffect == EFFECT_ATTACK_DOWN_2)
                  && move != MOVE_PLAY_NICE && move != MOVE_NOBLE_ROAR && move != MOVE_TEARFUL_LOOK && move != MOVE_VENOM_DRENCH)
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_KEEN_EYE:
                if (moveEffect == EFFECT_ACCURACY_DOWN || moveEffect == EFFECT_ACCURACY_DOWN_2)
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_DEFIANT:
            case ABILITY_COMPETITIVE:
                if (IsStatLoweringMoveEffect(moveEffect) && !IS_TARGETING_PARTNER(battlerAtk, battlerDef))
                    RETURN_SCORE_MINUS(8);
                break;
            case ABILITY_COMATOSE:
                if (IsNonVolatileStatusMoveEffect(moveEffect))
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_SHIELDS_DOWN:
                if (IsShieldsDownProtected(battlerAtk) && IsNonVolatileStatusMoveEffect(moveEffect))
                    RETURN_SCORE_MINUS(10);
                break;
            case ABILITY_LEAF_GUARD:
                if ((AI_GetWeather(aiData) & B_WEATHER_SUN)
                  && aiData->holdEffects[battlerDef] != HOLD_EFFECT_UTILITY_UMBRELLA
                  && IsNonVolatileStatusMoveEffect(moveEffect))
                    RETURN_SCORE_MINUS(10);
                break;
            } // def ability checks

            // target partner ability checks & not attacking partner
            if (isDoubleBattle)
            {
                switch (aiData->abilities[BATTLE_PARTNER(battlerDef)])
                {
                case ABILITY_LIGHTNING_ROD:
                    if (moveType == TYPE_ELECTRIC && !IsMoveRedirectionPrevented(move, aiData->abilities[battlerAtk]))
                        RETURN_SCORE_MINUS(20);
                    break;
                case ABILITY_MAGNET_PULL:
                    if (moveType == TYPE_STEEL && !IsMoveRedirectionPrevented(move, aiData->abilities[battlerAtk]))
                        RETURN_SCORE_MINUS(20);
                    break;
                case ABILITY_STORM_DRAIN:
                    if (moveType == TYPE_WATER && !IsMoveRedirectionPrevented(move, aiData->abilities[battlerAtk]))
                        RETURN_SCORE_MINUS(20);
                    break;
                case ABILITY_WITCHCRAFT:
                    if (moveType == TYPE_FAIRY && !IsMoveRedirectionPrevented(move, aiData->abilities[battlerAtk]))
                        RETURN_SCORE_MINUS(20);
                    break;
                case ABILITY_SOUL_LOCKER:
                    if (moveType == TYPE_GHOST && !IsMoveRedirectionPrevented(move, aiData->abilities[battlerAtk]))
                        RETURN_SCORE_MINUS(20);
                    break;
                case ABILITY_MAGIC_BOUNCE:
                    if (gBattleMoves[move].magicCoatAffected && moveTarget & (MOVE_TARGET_BOTH | MOVE_TARGET_FOES_AND_ALLY | MOVE_TARGET_OPPONENTS_FIELD))
                        RETURN_SCORE_MINUS(20);
                    break;
                case ABILITY_SWEET_VEIL:
                    if (moveEffect == EFFECT_SLEEP || moveEffect == EFFECT_DARK_VOID || moveEffect == EFFECT_YAWN || moveEffect == EFFECT_SLEEP_POWDER || moveEffect == EFFECT_MAGIC_POWDER)
                        RETURN_SCORE_MINUS(20);
                    break;
                case ABILITY_FLOWER_VEIL:
                    if ((IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS)) && (IsNonVolatileStatusMoveEffect(moveEffect) || IsStatLoweringMoveEffect(moveEffect)))
                        RETURN_SCORE_MINUS(10);
                    break;
                case ABILITY_AROMA_VEIL:
                    if (IsAromaVeilProtectedMove(move))
                        RETURN_SCORE_MINUS(10);
                    break;
                case ABILITY_DAZZLING:
                case ABILITY_QUEENLY_MAJESTY:
                    if (atkPriority > 0)
                        RETURN_SCORE_MINUS(10);
                    break;
                }
            } // def partner ability checks
        } // ignore def ability check

        // gen7+ dark type mons immune to priority->elevated moves from prankster
        #if B_PRANKSTER_DARK_TYPES >= GEN_7
        if (aiData->abilities[battlerAtk] == ABILITY_PRANKSTER && (IS_BATTLER_OF_TYPE(battlerDef, TYPE_DARK) || IS_BATTLER_OF_TYPE(battlerDef, TYPE_FAIRY)) && IS_MOVE_STATUS(move)
          && !(moveTarget & (MOVE_TARGET_OPPONENTS_FIELD | MOVE_TARGET_USER)))
            RETURN_SCORE_MINUS(10);
        #endif

        // terrain & effect checks
        if (AI_IsTerrainAffected(battlerDef, STATUS_FIELD_ELECTRIC_TERRAIN))
        {
            if (moveEffect == EFFECT_SLEEP || moveEffect == EFFECT_DARK_VOID || moveEffect == EFFECT_YAWN || moveEffect == EFFECT_SLEEP_POWDER || moveEffect == EFFECT_MAGIC_POWDER)
                RETURN_SCORE_MINUS(20);
        }

        if (AI_IsTerrainAffected(battlerAtk, STATUS_FIELD_PSYCHIC_TERRAIN) && atkPriority > 0)
        {
            RETURN_SCORE_MINUS(20);
        }
    } // end check MOVE_TARGET_USER

// the following checks apply to any target (including user)

    // throat chop check
    if (gDisableStructs[battlerAtk].throatChopTimer && gBattleMoves[move].soundMove)
        return 0; // Can't even select move at all
    // heal block check
    if (gStatuses3[battlerAtk] & STATUS3_HEAL_BLOCK && IsHealBlockPreventingMove(battlerAtk, move))
        return 0; // Can't even select heal blocked move

    // primal weather check
    weather = AI_GetWeather(aiData);
    if (weather & B_WEATHER_PRIMAL_ANY)
    {
        switch (move)
        {
            case MOVE_SUNNY_DAY:
            case MOVE_RAIN_DANCE:
            case MOVE_HAIL:
            case MOVE_SANDSTORM:
                RETURN_SCORE_MINUS(30);
        }

        if (!IS_MOVE_STATUS(move))
        {
            if (weather & B_WEATHER_SUN_PRIMAL)
            {
                if (moveType == TYPE_WATER)
                    RETURN_SCORE_MINUS(30);
            }
            else if (weather & B_WEATHER_RAIN_PRIMAL)
            {
                if (moveType == TYPE_FIRE)
                    RETURN_SCORE_MINUS(30);
            }
        }
    }

    // check move effects
    switch (moveEffect)
    {
        case EFFECT_HIT:
        default:
            break;  // check move damage
        case EFFECT_SLEEP:
            if (!AI_CanPutToSleep(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            if (move == MOVE_HYPNOSIS && IS_BATTLER_OF_TYPE(battlerDef, TYPE_PSYCHIC))
                score -= 10;
            if (move == MOVE_LOVELY_KISS && gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)
                score += 2;
            break;
        case EFFECT_DARK_VOID:
            if (!AI_CanPutToSleep(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            if (CountBattlerStatDecreases(battlerAtk, TRUE) < 1)
                score -= 10;
            else
                score += CountBattlerStatDecreases(battlerAtk, TRUE);
            break;
        case EFFECT_SLEEP_POWDER:
            if (!AI_CanPutToSleep(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_EXPLOSION:
            if (!(AI_THINKING_STRUCT->aiFlags & AI_FLAG_WILL_SUICIDE))
                score -= 2;

            if (effectiveness == AI_EFFECTIVENESS_x0)
            {
                score -= 10;
            }
            else if (IsAbilityOnField(ABILITY_DAMP) && !DoesBattlerIgnoreAbilityChecks(aiData->abilities[battlerAtk], move))
            {
                score -= 10;
            }
            else if (CountUsablePartyMons(battlerAtk) == 0)
            {
                if (CountUsablePartyMons(battlerDef) != 0)
                    score -= 10;
                else
                    score--;
            }
            break;
        case EFFECT_DREAM_EATER:
            if (!AI_IsBattlerAsleepOrComatose(battlerDef))
                score -= 30;
            else if (effectiveness == AI_EFFECTIVENESS_x0)
                score -= 10;
            break;
        case EFFECT_SABRE_BREAK:
            if (!(gBattleMons[battlerDef].status1 & STATUS1_FROSTBITE))
                score--;
            break;
    // stat raising effects
        case EFFECT_ATTACK_UP:
        case EFFECT_ATTACK_UP_2:
        case EFFECT_ATTACK_UP_USER_ALLY:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            break;
        case EFFECT_STUFF_CHEEKS:
            if (ItemId_GetPocket(gBattleMons[battlerAtk].item) != POCKET_BERRIES)
                return 0;   // cannot even select
            //fallthrough
        case EFFECT_DEFENSE_UP:
        case EFFECT_DEFENSE_UP_2:
        case EFFECT_DEFENSE_UP_3:
        case EFFECT_DEFENSE_CURL:
        case EFFECT_ACID_ARMOR:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 10;
            break;
        case EFFECT_SPECIAL_ATTACK_UP:
        case EFFECT_SPECIAL_ATTACK_UP_2:
        case EFFECT_SPECIAL_ATTACK_UP_3:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK) || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                score -= 10;
            break;
        case EFFECT_SPECIAL_DEFENSE_UP:
        case EFFECT_SPECIAL_DEFENSE_UP_2:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 10;
            break;
        case EFFECT_ACCURACY_UP:
        case EFFECT_ACCURACY_UP_2:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ACC))
                score -= 10;
            break;
        case EFFECT_EVASION_UP:
        case EFFECT_EVASION_UP_2:
        case EFFECT_MINIMIZE:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_EVASION))
                score -= 10;
            break;
        case EFFECT_GREEN_GUISE:
            if (gBattleMons[battlerAtk].status2 & STATUS2_FOCUS_ENERGY_ANY)
                score -= 2;
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_EVASION))
                score -= 5;
            break;
        case EFFECT_SUN_BASK:
            if (weather & B_WEATHER_SUN)
            {
                if (ShouldBloomSelf(battlerAtk, aiData->abilities[battlerAtk]))
                {
                    score += 2;
                }
                else if (!AI_CanBloom(battlerAtk, battlerDef, move))
                {
                    score -= 2;
                }
            }
        case EFFECT_COSMIC_POWER:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 8;
            break;
        case EFFECT_BULK_UP:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 8;
            break;
        case EFFECT_CALM_MIND:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 8;
            break;
        case EFFECT_DRAGON_DANCE:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                score -= 8;
            break;
        case EFFECT_NO_RETREAT:
            if (gBattleMons[battlerAtk].status2 & STATUS2_ESCAPE_PREVENTION)
                score -= 2;
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 8;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 8;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                score -= 8;
            break;
        case EFFECT_CLANGOROUS_SOUL:
            if (gBattleMons[battlerAtk].hp <= gBattleMons[battlerAtk].maxHP / 3)
                score -= 10;
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK) || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 8;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 8;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                score -= 8;
        case EFFECT_COIL:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ACC))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 8;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 6;
            break;
        case EFFECT_MEDITATE:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 8;
            break;
        case EFFECT_HEAVY_CELL:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 8;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                score -= 6;
            break;
        case EFFECT_SP_ATTACK_ACCURACY_UP:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ACC))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK) || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                score -= 8;
            break;
        case EFFECT_TRAILBLAZE:
            if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            {
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ACC))
                    score -= 10;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                    score -= 8;
            }
            else
            {
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                    score -= 10;
            }
            break;
        case EFFECT_ATTACK_ACCURACY_UP: //hone claws
            if (aiData->abilities[battlerAtk] != ABILITY_CONTRARY)
            {
                if (gBattleMons[battlerAtk].statStages[STAT_ATK] >= MAX_STAT_STAGE
                  && (gBattleMons[battlerAtk].statStages[STAT_ACC] >= MAX_STAT_STAGE || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL)))
                    score -= 10;
                break;
            }
            else
            {
                score -= 10;
            }
            break;
        case EFFECT_CHARGE:
            if (gStatuses3[battlerAtk] & STATUS3_CHARGED_UP)
                score -= 20;
            else if (!HasMoveWithType(battlerAtk, TYPE_ELECTRIC))
                score -= 10;
            #if B_CHARGE_SPDEF_RAISE >= GEN_5
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 5;
            #endif
            break;
        case EFFECT_QUIVER_DANCE:
        case EFFECT_GEOMANCY:
            if (gBattleMons[battlerAtk].statStages[STAT_SPATK] >= MAX_STAT_STAGE || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                score -= 8;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 6;
            break;
        case EFFECT_HUNKER_DOWN:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 10;
            else if (gBattleMons[battlerAtk].statStages[STAT_DEF] >= 9 && gBattleMons[battlerAtk].statStages[STAT_SPDEF] >= 9)
                score -= 20;
            if (!gDisableStructs[battlerAtk].isFirstTurn)
                score -= 2;
            break;
        case EFFECT_VICTORY_DANCE:
            if (gBattleMons[battlerAtk].statStages[STAT_ATK] >= MAX_STAT_STAGE || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                score -= 8;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                score -= 6;
            break;
        case EFFECT_FROST_SHRED:
            if (gBattleMons[battlerAtk].statStages[STAT_SPEED] <= DEFAULT_STAT_STAGE)
                score -= 10;
            break;
        case EFFECT_HAYWIRE:
        case EFFECT_STORED_POWER:
            for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
            {
                if (gBattleMons[battlerAtk].statStages[i] <= DEFAULT_STAT_STAGE)
                    score -= 10;
            }
            break;
        case EFFECT_SHIFT_GEAR:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                score -= 8;
            break;
        case EFFECT_SHELL_SMASH:
            if (aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
            {
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                    score -= 10;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                    score -= 8;
            }
            else
            {
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                    score -= 10;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK) || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                    score -= 8;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                    score -= 6;
            }
            break;
        case EFFECT_PHANTASM:
            if (aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
            {
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                    score -= 10;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                    score -= 8;
            }
            else
            {
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                    score -= 10;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK) || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                    score -= 8;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_EVASION))
                    score -= 6;
            }
            break;
        case EFFECT_TIDY_UP:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPEED))
                score -= 8;
            IncreaseTidyUpScore(battlerAtk, battlerDef, move, &score);
            break;
        case EFFECT_GROWTH:
            if (weather & B_WEATHER_SUN)
            {
                if (ShouldBloomSelf(battlerAtk, aiData->abilities[battlerAtk]))
                {
                    score += 2;
                }
                else if (!AI_CanBloom(battlerAtk, battlerDef, move))
                {
                    score -= 2;
                }
            }
        case EFFECT_ATTACK_SPATK_UP:    // work up
            if ((!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) && !BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK))
             || (!HasDamagingMove(battlerAtk)))
                score -= 10;
            break;
        case EFFECT_ROTOTILLER:
            if (isDoubleBattle)
            {
                if (!(IS_BATTLER_OF_TYPE(battlerAtk, TYPE_GRASS)
                  && AI_IsBattlerGrounded(battlerAtk)
                  && (BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK)))
                  && !(IS_BATTLER_OF_TYPE(BATTLE_PARTNER(battlerAtk), TYPE_GRASS)
                  && AI_IsBattlerGrounded(BATTLE_PARTNER(battlerAtk))
                  && aiData->abilities[BATTLE_PARTNER(battlerAtk)] != ABILITY_CONTRARY
                  && (BattlerStatCanRise(BATTLE_PARTNER(battlerAtk), aiData->abilities[BATTLE_PARTNER(battlerAtk)], STAT_ATK)
                   || BattlerStatCanRise(BATTLE_PARTNER(battlerAtk), aiData->abilities[BATTLE_PARTNER(battlerAtk)], STAT_SPATK))))
                {
                    score -= 10;
                }
            }
            else if (!(IS_BATTLER_OF_TYPE(battlerAtk, TYPE_GRASS)
              && AI_IsBattlerGrounded(battlerAtk)
              && (BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK))))
            {
                score -= 10;
            }
            break;
        case EFFECT_GEAR_UP:
            if (aiData->abilities[battlerAtk] == ABILITY_PLUS || aiData->abilities[battlerAtk] == ABILITY_MINUS)
            {
                // same as growth, work up
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                    score -= 10;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK) || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                    score -= 8;
                break;
            }
            else if (!isDoubleBattle)
            {
                score -= 10;    // no partner and our stats wont rise, so don't use
            }

            if (isDoubleBattle)
            {
                if (aiData->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_PLUS || aiData->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_MINUS)
                {
                    if ((!BattlerStatCanRise(BATTLE_PARTNER(battlerAtk), aiData->abilities[BATTLE_PARTNER(battlerAtk)], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                      && (!BattlerStatCanRise(BATTLE_PARTNER(battlerAtk), aiData->abilities[BATTLE_PARTNER(battlerAtk)], STAT_SPATK) || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL)))
                        score -= 10;
                }
                else if (aiData->abilities[battlerAtk] != ABILITY_PLUS && aiData->abilities[battlerAtk] != ABILITY_MINUS)
                {
                    score -= 10;    // nor our or our partner's ability is plus/minus
                }
            }
            break;
        case EFFECT_ACUPRESSURE:
            if (DoesSubstituteBlockMove(battlerAtk, battlerDef, move) || AreBattlersStatsMaxed(battlerDef))
                score -= 10;
            break;
        case EFFECT_MAGNETIC_FLUX:
            if (aiData->abilities[battlerAtk] == ABILITY_PLUS || aiData->abilities[battlerAtk] == ABILITY_MINUS)
            {
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                    score -= 10;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                    score -= 8;
            }
            else if (!isDoubleBattle)
            {
                score -= 10;    // our stats wont rise from this move
            }

            if (isDoubleBattle)
            {
                if (aiData->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_PLUS || aiData->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_MINUS)
                {
                    if (!BattlerStatCanRise(BATTLE_PARTNER(battlerAtk), aiData->abilities[BATTLE_PARTNER(battlerAtk)], STAT_DEF))
                        score -= 10;
                    else if (!BattlerStatCanRise(BATTLE_PARTNER(battlerAtk), aiData->abilities[BATTLE_PARTNER(battlerAtk)], STAT_SPDEF))
                        score -= 8;
                }
                else if (aiData->abilities[battlerAtk] != ABILITY_PLUS && aiData->abilities[battlerAtk] != ABILITY_MINUS)
                {
                    score -= 10;    // nor our or our partner's ability is plus/minus
                }
            }
            break;
        case EFFECT_SYRUP_BOMB:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                score--;
            else if (aiData->abilities[battlerDef] == ABILITY_SPEED_BOOST)
                score -= 3;
            break;
    // stat lowering effects
        case EFFECT_ATTACK_DOWN:
        case EFFECT_ATTACK_DOWN_2:
        case EFFECT_CHARM:
        case EFFECT_FEATHER_DANCE:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ATK)) //|| !HasMoveWithSplit(battlerDef, SPLIT_PHYSICAL))
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_HYPER_CUTTER)
                score -= 10;
            break;
        case EFFECT_DEFENSE_DOWN:
        case EFFECT_DEFENSE_DOWN_2:
        case EFFECT_DEFENSE_DOWN_HIT_2:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_DEF))
                score -= 10;
            break;
        case EFFECT_SPEED_DOWN:
        case EFFECT_SPEED_DOWN_2:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_SPEED_BOOST)
                score -= 10;
            break;
        case EFFECT_SPECIAL_ATTACK_DOWN:
        case EFFECT_SPECIAL_ATTACK_DOWN_2:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPATK)) //|| !HasMoveWithSplit(battlerDef, SPLIT_SPECIAL))
                score -= 10;
            break;
        case EFFECT_SPECIAL_DEFENSE_DOWN:
        case EFFECT_SPECIAL_DEFENSE_DOWN_2:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPDEF))
                score -= 10;
            break;
        case EFFECT_ACCURACY_DOWN:
        case EFFECT_ACCURACY_DOWN_2:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ACC))
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_KEEN_EYE)
                score -= 8;
            break;
        case EFFECT_EVASION_DOWN:
        case EFFECT_EVASION_DOWN_2:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_EVASION))
                score -= 10;
            break;
        case EFFECT_CHILLY_AIR:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_SPEED_BOOST)
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_EVASION))
                score -= 10;
            break;
        case EFFECT_SPIDER_WEB:
            if (gDisableStructs[battlerDef].spiderweb
              || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_DEF))
                score -= 10;
            else if (gDisableStructs[battlerAtk].isFirstTurn)
                score += 4;
            else if (!gDisableStructs[battlerDef].spiderweb)
                score += 4;
            break;
        case EFFECT_EERIE_IMPULSE:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPATK)) //|| !HasMoveWithSplit(battlerDef, SPLIT_SPECIAL))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPDEF))
                score -= 8;
            break;
        case EFFECT_TICKLE:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ATK))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_DEF))
                score -= 8;
            break;
        case EFFECT_APPLE_ACID:
            if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            {
                if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPDEF))
                    score -= 2;
                else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_DEF))
                    score -= 1;
            }
            else
            {
                if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPDEF))
                    score -= 2;
            }
            break;
        case EFFECT_KINESIS:
            if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
            {
                if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ACC))
                    score -= 10;
                else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPATK))
                    score -= 8;
                else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ATK))
                    score -= 6;
                else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_EVASION))
                    score -= 4;
            }
            else
            {
                if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ACC))
                    score -= 10;
                else if (aiData->abilities[battlerDef] == ABILITY_KEEN_EYE)
                    score -= 8;
            }
            break;
        case EFFECT_ENERVATOR:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ATK))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                score -= 8;
            else if (aiData->abilities[battlerDef] == ABILITY_SPEED_BOOST)
                score -= 7;
            break;
        case EFFECT_COTTON_SPORE:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_SPEED_BOOST)
                score -= 10;
            if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            {
                if (!AI_CanParalyze(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                    score -= 2;
            }
            break;
        case EFFECT_VENOM_DRENCH:
            if (!(gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY))
            {
                score -= 10;
            }
            else
            {
                if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                    score -= 10;
                else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPATK))
                    score -= 8;
                else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ATK))
                    score -= 6;
            }
            break;
        case EFFECT_TEARFUL_LOOK:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPATK))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ATK))
                score -= 8;
            break;
        case EFFECT_CAPTIVATE:
            if (!AreBattlersOfOppositeGender(battlerAtk, battlerDef))
                score -= 10;
            break;
    // other
        case EFFECT_HAZE:
            if (PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
            {
                score -= 10;    // partner already using haze
            }
            else
            {
                for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
                {
                    if (gBattleMons[battlerAtk].statStages[i] > DEFAULT_STAT_STAGE || gBattleMons[BATTLE_PARTNER(battlerAtk)].statStages[i] > DEFAULT_STAT_STAGE)
                        score -= 10;  // Don't want to reset our boosted stats
                }
                for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
                {
                    if (gBattleMons[battlerDef].statStages[i] < DEFAULT_STAT_STAGE || gBattleMons[BATTLE_PARTNER(battlerDef)].statStages[i] < DEFAULT_STAT_STAGE)
                        score -= 10; //Don't want to reset enemy lowered stats
                }
            }
            break;
        //case EFFECT_BIDE:
        //case EFFECT_SUPER_FANG:
        //case EFFECT_RECHARGE:
        case EFFECT_LEVEL_DAMAGE:
        case EFFECT_PSYWAVE:
        //case EFFECT_COUNTER:
        //case EFFECT_FLAIL:
        case EFFECT_RETURN:
        case EFFECT_PRESENT:
        case EFFECT_FRUSTRATION:
        case EFFECT_SONIC_BOOM:
        case EFFECT_DRAGON_RAGE:
        //case EFFECT_MIRROR_COAT:
        case EFFECT_SKULL_BASH:
        case EFFECT_FOCUS_PUNCH:
        case EFFECT_SUPERPOWER:
        //case EFFECT_ENDEAVOR:
        case EFFECT_LOW_KICK:
        case EFFECT_WATERFALL:
        case EFFECT_CUT:
        case EFFECT_ROCK_SMASH:
        case EFFECT_STRENGTH:
        case EFFECT_ROCK_CLIMB:
        case EFFECT_SURF:
        case EFFECT_WHIRLPOOL:
        case EFFECT_HEAVY_CANNON:
        case EFFECT_GIANTS_SPEAR:
            // AI_CBM_HighRiskForDamage
            if (aiData->abilities[battlerDef] == ABILITY_WONDER_GUARD && effectiveness < AI_EFFECTIVENESS_x2)
                score -= 10;
            break;
        case EFFECT_COUNTER:
        case EFFECT_MIRROR_COAT:
            if (IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef]) || gBattleMons[battlerDef].status2 & (STATUS2_INFATUATION | STATUS2_CONFUSION))
                score--;
            if (predictedMove == MOVE_NONE || GetBattleMoveSplit(predictedMove) == SPLIT_STATUS
              || DoesSubstituteBlockMove(battlerAtk, BATTLE_PARTNER(battlerDef), predictedMove))
                score -= 10;
            break;

        case EFFECT_ROAR:
        case EFFECT_DEARLY_DEPART:
        case EFFECT_WHIRLWIND:
        case EFFECT_PSY_SWAP:
            if (CountUsablePartyMons(battlerDef) == 0)
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_SUCTION_CUPS)
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_STALWART)
                score -= 10;
            break;
        case EFFECT_TOXIC_THREAD:
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                score--;    // may still want to just poison
            //fallthrough
        case EFFECT_POISON:
        case EFFECT_POISON_POWDER:
        case EFFECT_TOXIC:
            if (!AI_CanPoison(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_SCORP_FANG:
            if (!AI_CanPoison(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 2;
            break;
        case EFFECT_TERRORIZE:
            if (!AI_CanPanic(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_DEEP_GAZE:
            if (gBattleMons[battlerDef].status1 & STATUS1_ANY)
                score -= 10;
            break;
        case EFFECT_MIND_BREAK:
            if (!(gBattleMons[battlerDef].status1 & STATUS1_PANIC))
                score -= 10;
            else if (!(gBattleMons[battlerDef].status2 & STATUS2_CONFUSION))
                score -= 10;
            break;
        case EFFECT_SILENCE:
            if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_SILENCE
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_LIGHT_SCREEN:
            if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_LIGHTSCREEN
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_REFLECT:
            if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_REFLECT
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_AURORA_VEIL:
            if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_AURORA_VEIL
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove)
              || !(weather & (B_WEATHER_HAIL | B_WEATHER_SNOW)))
                score -= 10;
            break;
        case EFFECT_BABY_BLUES:
            if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_GOOGOO_SCREEN
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_OHKO:
        #if B_SHEER_COLD_IMMUNITY >= GEN_7
            if (move == MOVE_SHEER_COLD && IS_BATTLER_OF_TYPE(battlerDef, TYPE_ICE))
                return 0;
        #endif
            if (!ShouldTryOHKO(battlerAtk, battlerDef, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], move))
                score -= 10;
            break;
        case EFFECT_MIST:
            if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_MIST
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_FOCUS_ENERGY:
            if (gBattleMons[battlerAtk].status2 & STATUS2_FOCUS_ENERGY_ANY)
                score -= 10;
            break;
        case EFFECT_DRAGON_CHEER:
            if (gBattleMons[BATTLE_PARTNER(battlerAtk)].status2 & STATUS2_FOCUS_ENERGY_ANY)
                score -= 10;
            break;
        case EFFECT_CONFUSE:
        case EFFECT_SWAGGER:
        case EFFECT_FLATTER:
        case EFFECT_FLASH:
            if (!AI_CanConfuse(battlerAtk, battlerDef, aiData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_PARALYZE:
            if (!AI_CanParalyze(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_STUN_SPORE:
            if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            {
                if (!AI_CanParalyze(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                    score -= 2;
                break;
            }
            else if (!AI_CanParalyze(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_SUBSTITUTE:
        case EFFECT_SHED_TAIL:
            if (gBattleMons[battlerAtk].status2 & STATUS2_SUBSTITUTE || aiData->abilities[battlerDef] == ABILITY_INFILTRATOR)
                score -= 8;
            else if (aiData->hpPercents[battlerAtk] <= 25)
                score -= 10;
        #if B_SOUND_SUBSTITUTE >= GEN_6
            else if (HasSoundMove(battlerDef))
                score -= 8;
        #endif
            break;
        case EFFECT_LEECH_SEED:
            if (gStatuses3[battlerDef] & STATUS3_LEECHSEED
             || IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS)
             || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_LIQUID_OOZE)
                score -= 3;
            break;
        case EFFECT_SEED_BOMB:
            if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            {
                if (gStatuses3[battlerDef] & STATUS3_LEECHSEED
                 || IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS)
                 || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                    score -= 2;
                else if (aiData->abilities[battlerDef] == ABILITY_LIQUID_OOZE)
                    score -= 2;
            }
            break;
        case EFFECT_MIND_GAP:
            if (!gDisableStructs[battlerAtk].isFirstTurn)
                score -= 10;
        case EFFECT_DISABLE:
        case EFFECT_VOID:
            if (gDisableStructs[battlerDef].disableTimer == 0
            #if B_MENTAL_HERB >= GEN_5
                && aiData->holdEffects[battlerDef] != HOLD_EFFECT_MENTAL_HERB
            #endif
                && !PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
            {
                if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // Attacker should go first
                {
                    if (gLastMoves[battlerDef] == MOVE_NONE || gLastMoves[battlerDef] == 0xFFFF)
                        score -= 10;    // no anticipated move to disable
                }
                else if (predictedMove == MOVE_NONE)
                {
                    score -= 10;
                }
            }
            else
            {
                score -= 10;
            }
            break;
        case EFFECT_ENCORE:
            if (gDisableStructs[battlerDef].encoreTimer == 0
            #if B_MENTAL_HERB >= GEN_5
                && aiData->holdEffects[battlerDef] != HOLD_EFFECT_MENTAL_HERB
            #endif
                && !DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
            {
                if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // Attacker should go first
                {
                    if (gLastMoves[battlerDef] == MOVE_NONE || gLastMoves[battlerDef] == 0xFFFF)
                        score -= 10;    // no anticipated move to encore
                }
                else if (predictedMove == MOVE_NONE)
                {
                    score -= 10;
                }
            }
            else
            {
                score -= 10;
            }
            break;
        case EFFECT_SNORE:
        case EFFECT_SLEEP_TALK:
            if (IsWakeupTurn(battlerAtk) || !AI_IsBattlerAsleepOrComatose(battlerAtk))
                score -= 10;    // if mon will wake up, is not asleep, or is not comatose
            break;
        case EFFECT_MEAN_LOOK:
            if (IsBattlerTrapped(battlerDef, TRUE) || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            if (!gDisableStructs[battlerAtk].isFirstTurn)
                score -= 10;
            break;
        case EFFECT_NIGHTMARE:
            if (!AI_IsBattlerAsleepOrComatose(battlerDef))
            {
                if (!AI_CanPutToSleep(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                    score -= 10;
            }
            else if (AI_IsBattlerAsleepOrComatose(battlerDef))
            {
                if (gBattleMons[battlerDef].status2 & STATUS2_NIGHTMARE)
                    score -= 10;
                else if (DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                    score -= 10;
            }
            break;
        case EFFECT_CURSE:
            if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_GHOST))
            {
                if (gBattleMons[battlerDef].status2 & STATUS2_CURSED
                  || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                    score -= 10;
                else if (aiData->hpPercents[battlerAtk] <= 50)
                    score -= 6;
            }
            else // regular curse
            {
                if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                    score -= 10;
                else if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_DEF))
                    score -= 8;
            }
            break;
        case EFFECT_SPIKES:
            if (gSideTimers[GetBattlerSide(battlerDef)].spikesAmount >= 3)
                score -= 10;
            else if (PartnerMoveIsSameNoTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove)
              && gSideTimers[GetBattlerSide(battlerDef)].spikesAmount == 2)
                score -= 10; // only one mon needs to set up the last layer of Spikes
            else if (aiData->abilities[battlerDef] == ABILITY_TITANIC)
                score -= 10;
            break;
        case EFFECT_STEALTH_ROCK:
            if (gSideTimers[GetBattlerSide(battlerDef)].stealthRockAmount > 0
              || PartnerMoveIsSameNoTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove)) //Only one mon needs to set up Stealth Rocks
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_TITANIC)
                score -= 10;
            break;
        case EFFECT_TOXIC_SPIKES:
            if (gSideTimers[GetBattlerSide(battlerDef)].toxicSpikesAmount >= 2)
                score -= 10;
            else if (PartnerMoveIsSameNoTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove) && gSideTimers[GetBattlerSide(battlerDef)].toxicSpikesAmount == 1)
                score -= 10; // only one mon needs to set up the last layer of Toxic Spikes
            else if (aiData->abilities[battlerDef] == ABILITY_TITANIC)
                score -= 10;
            break;
        case EFFECT_STICKY_WEB:
            if (gSideTimers[GetBattlerSide(battlerDef)].stickyWebAmount)
                score -= 10;
            else if (PartnerMoveIsSameNoTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove) && gSideTimers[GetBattlerSide(battlerDef)].stickyWebAmount)
                score -= 10; // only one mon needs to set up Sticky Web
            else if (aiData->abilities[battlerDef] == ABILITY_TITANIC)
                score -= 10;
            break;
        case EFFECT_FORESIGHT:
            if (gBattleMons[battlerDef].status2 & STATUS2_FORESIGHT)
                score -= 10;
            else if (gBattleMons[battlerDef].statStages[STAT_EVASION] <= 4
              || !(IS_BATTLER_OF_TYPE(battlerDef, TYPE_GHOST))
              || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 9;
            break;
        case EFFECT_PERISH_SONG:
            if (isDoubleBattle)
            {
                if (CountUsablePartyMons(battlerAtk) == 0
                  && aiData->abilities[battlerAtk] != ABILITY_SOUNDPROOF
                  && aiData->abilities[BATTLE_PARTNER(battlerAtk)] != ABILITY_SOUNDPROOF
                  && CountUsablePartyMons(FOE(battlerAtk)) >= 1)
                {
                    score -= 10; //Don't wipe your team if you're going to lose
                }
                else if ((!IsBattlerAlive(FOE(battlerAtk)) || aiData->abilities[FOE(battlerAtk)] == ABILITY_SOUNDPROOF
                  || gStatuses3[FOE(battlerAtk)] & STATUS3_PERISH_SONG)
                  && (!IsBattlerAlive(BATTLE_PARTNER(FOE(battlerAtk))) || aiData->abilities[BATTLE_PARTNER(FOE(battlerAtk))] == ABILITY_SOUNDPROOF
                  || gStatuses3[BATTLE_PARTNER(FOE(battlerAtk))] & STATUS3_PERISH_SONG))
                {
                    score -= 10; //Both enemies are perish songed
                }
                else if (DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                {
                    score -= 10;
                }
            }
            else
            {
                if (CountUsablePartyMons(battlerAtk) == 0 && aiData->abilities[battlerAtk] != ABILITY_SOUNDPROOF
                  && CountUsablePartyMons(battlerDef) >= 1)
                    score -= 10;

                if (gStatuses3[FOE(battlerAtk)] & STATUS3_PERISH_SONG || aiData->abilities[FOE(battlerAtk)] == ABILITY_SOUNDPROOF)
                    score -= 10;
            }
            break;
        case EFFECT_SANDSTORM:
            if (weather & (B_WEATHER_SANDSTORM | B_WEATHER_PRIMAL_ANY)
             || PartnerMoveEffectIsWeather(BATTLE_PARTNER(battlerAtk), aiData->partnerMove))
                score -= 8;
            break;
        case EFFECT_SUNNY_DAY:
        case EFFECT_WARM_WELCOME:
            if (weather & (B_WEATHER_SUN | B_WEATHER_PRIMAL_ANY)
             || PartnerMoveEffectIsWeather(BATTLE_PARTNER(battlerAtk), aiData->partnerMove))
                score -= 8;
            break;
        case EFFECT_RAIN_DANCE:
            if (weather & (B_WEATHER_RAIN | B_WEATHER_PRIMAL_ANY)
             || PartnerMoveEffectIsWeather(BATTLE_PARTNER(battlerAtk), aiData->partnerMove))
                score -= 8;
            break;
        case EFFECT_HAIL:
        case EFFECT_CHILLY_RECEPTION:
            if (weather & (B_WEATHER_HAIL | B_WEATHER_PRIMAL_ANY)
             || PartnerMoveEffectIsWeather(BATTLE_PARTNER(battlerAtk), aiData->partnerMove))
                score -= 8;
            else if (weather & B_WEATHER_SNOW)
                score -= 2; // mainly to prevent looping between hail and snow
            break;
        case EFFECT_SNOWSCAPE:
            if (weather & (B_WEATHER_SNOW | B_WEATHER_PRIMAL_ANY)
             || PartnerMoveEffectIsWeather(BATTLE_PARTNER(battlerAtk), aiData->partnerMove))
                score -= 8;
            else if (weather & B_WEATHER_HAIL)
                score -= 2; // mainly to prevent looping between hail and snow
            break;
        case EFFECT_ATTRACT:
            if (!AI_CanBeInfatuated(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
                score -= 10;
            else
                score += 10;
            break;
        case EFFECT_SAFEGUARD:
            if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_SAFEGUARD
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_MAGNITUDE:
            if (aiData->abilities[battlerDef] == ABILITY_LEVITATE || (AI_DATA->abilities[battlerDef] == ABILITY_GRAVITY_WELL && gFieldStatuses & STATUS_FIELD_GRAVITY))
                score -= 10;
            break;
        case EFFECT_PARTING_SHOT:
        case EFFECT_PARTING_CURRY:
            if (CountUsablePartyMons(battlerAtk) == 0)
                score -= 10;
            break;
        case EFFECT_BATON_PASS:
            if (CountUsablePartyMons(battlerAtk) == 0)
                score -= 10;
            else if (gBattleMons[battlerAtk].status2 & STATUS2_SUBSTITUTE
              || (gStatuses3[battlerAtk] & (STATUS3_ROOTED | STATUS3_AQUA_RING | STATUS3_MAGNET_RISE | STATUS3_POWER_TRICK))
              || AnyStatIsRaised(battlerAtk))
                break;
            else
                score -= 6;
            break;
        case EFFECT_HIT_ESCAPE:
        case EFFECT_U_TURN:
        case EFFECT_FLIP_TURN:
        case EFFECT_SNOWFADE:
        case EFFECT_GLACIAL_SHIFT:
            break;
        case EFFECT_RAPID_SPIN:
        case EFFECT_CINDER_TWIRL:
            if ((gBattleMons[battlerAtk].status2 & STATUS2_WRAPPED) || (gStatuses3[battlerAtk] & STATUS3_LEECHSEED))
                break;  // check damage/accuracy
            //Spin checks
            if (!(gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_HAZARDS_ANY))
                score -= 6;
            break;
        case EFFECT_LEAF_TORNADO:
            if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            {
                if ((gBattleMons[battlerAtk].status2 & STATUS2_WRAPPED) || (gStatuses3[battlerAtk] & STATUS3_LEECHSEED))
                    break;  // check damage/accuracy
                //Spin checks
                if (!(gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_HAZARDS_ANY))
                    score -= 2;
            }
            break;
        case EFFECT_FILLET_AWAY:
            if (aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
                score -= 10;
            if (aiData->hpPercents[battlerAtk] <= 60)
                score -= 10;
            break;
        case EFFECT_BELLY_DRUM:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) || !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
        case EFFECT_IGNITION:
            if (!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK) || !HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                score -= 10;
            if (aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
                score -= 10;
            if (aiData->hpPercents[battlerAtk] <= 60)
                score -= 10;
            break;
        case EFFECT_STALAG_BLAST:
            if (aiData->hpPercents[battlerAtk] <= 50)
                score -= 7;
            break;
        case EFFECT_FUTURE_SIGHT:
            if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_FUTUREATTACK
              || gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_FUTUREATTACK)
                score -= 12;
            else
                score += 5;
            if (aiData->abilities[battlerAtk] == ABILITY_FOREWARN)
                score += 3;
            break;
        case EFFECT_TELEPORT:
            score -= 10;
            break;
        case EFFECT_FAKE_OUT:
        case EFFECT_LOVE_TAP:
        case EFFECT_NOBLE_ROAR:
            if (!gDisableStructs[battlerAtk].isFirstTurn)
                score -= 10;
            break;
        case EFFECT_STOCKPILE:
            if (gDisableStructs[battlerAtk].stockpileCounter >= 3)
                score -= 10;
            break;
        case EFFECT_SPIT_UP:
            if (gDisableStructs[battlerAtk].stockpileCounter < 1)
                score -= 10;
            break;
        case EFFECT_SWALLOW:
            if (gDisableStructs[battlerAtk].stockpileCounter < 1)
            {
                score -= 10;
            }
            else
            {
                if (AtMaxHp(battlerAtk))
                    score -= 10;
                else if (aiData->hpPercents[battlerAtk] >= 80)
                    score -= 5; // do it if nothing better
            }
            break;
        case EFFECT_TORMENT:
        #if B_MENTAL_HERB >= GEN_5
            if (aiData->holdEffects[battlerDef] == HOLD_EFFECT_MENTAL_HERB)
                score -= 6;
        #endif
            break;
        case EFFECT_WILL_O_WISP:
            if (!AI_CanBurn(battlerAtk, battlerDef, aiData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_GLACIATE:
            if (!AI_CanGiveFrostbite(battlerAtk, battlerDef, aiData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_MEMENTO:
            if (CountUsablePartyMons(battlerAtk) == 0 || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            else if (gBattleMons[battlerDef].statStages[STAT_ATK] == MIN_STAT_STAGE && gBattleMons[battlerDef].statStages[STAT_SPATK] == MIN_STAT_STAGE)
                score -= 10;
            break;
        case EFFECT_FOLLOW_ME:
        case EFFECT_HELPING_HAND:
        case EFFECT_INSTRUCT:
            if (!isDoubleBattle
              || !IsBattlerAlive(BATTLE_PARTNER(battlerAtk))
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove)
              || (aiData->partnerMove != MOVE_NONE && IS_MOVE_STATUS(aiData->partnerMove))
              || *(gBattleStruct->monToSwitchIntoId + BATTLE_PARTNER(battlerAtk)) != PARTY_SIZE) //Partner is switching out.
                score -= 10;
            break;
        case EFFECT_TRICK:
        case EFFECT_KNOCK_OFF:
        case EFFECT_PARTY_TRICK:
            if (aiData->abilities[battlerDef] == ABILITY_STICKY_HOLD || IS_BATTLER_OF_TYPE(battlerDef, TYPE_FAIRY))
                score -= 10;
            break;
        case EFFECT_INGRAIN:
            if (gStatuses3[battlerAtk] & STATUS3_ROOTED && (!(AI_CanBloom(battlerAtk, battlerDef, move))))
                score -= 10;
            break;
        case EFFECT_AQUA_RING:
            if (gStatuses3[battlerAtk] & STATUS3_AQUA_RING)
                score -= 10;
            break;
        case EFFECT_HEARTHWARM:
            if (gStatuses4[battlerAtk] & STATUS4_HEARTHWARM)
                score -= 10;
            break;
        case EFFECT_RECYCLE:
            if (GetUsedHeldItem(battlerAtk) == 0 || gBattleMons[battlerAtk].item != 0)
                score -= 10;
            break;
        case EFFECT_REFRESH:
            if (!(gBattleMons[battlerDef].status1 & (STATUS1_PSN_ANY | STATUS1_BURN | STATUS1_PARALYSIS | STATUS1_FROSTBITE)))
                score -= 10;
            break;
        case EFFECT_PSYCHO_SHIFT:
            if (gBattleMons[battlerAtk].status1 & STATUS1_PSN_ANY && !AI_CanPoison(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            else if (gBattleMons[battlerAtk].status1 & STATUS1_BURN && !AI_CanBurn(battlerAtk, battlerDef,
              aiData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            else if (gBattleMons[battlerAtk].status1 & STATUS1_FROSTBITE && !AI_CanGiveFrostbite(battlerAtk, battlerDef,
              aiData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            else if (gBattleMons[battlerAtk].status1 & STATUS1_PARALYSIS && !AI_CanParalyze(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            else if (gBattleMons[battlerAtk].status1 & STATUS1_SLEEP_ANY && !AI_CanPutToSleep(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            else
                score -= 10;    // attacker has no status to transmit
            break;
        case EFFECT_MUD_SPORT:
            if (gFieldStatuses & STATUS_FIELD_MUDSPORT
              || gStatuses4[battlerAtk] & STATUS4_MUD_SPORT
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove)
              || !isDoubleBattle
              || IS_BATTLER_OF_TYPE(battlerAtk, TYPE_GROUND))
                  score -= 10;
            break;
        case EFFECT_WATER_SPORT:
            if (gFieldStatuses & STATUS_FIELD_WATERSPORT
              || gStatuses4[battlerAtk] & STATUS4_WATER_SPORT
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove)
              || !isDoubleBattle 
              || IS_BATTLER_OF_TYPE(battlerAtk, TYPE_WATER))
                score -= 10;
            break;
        case EFFECT_ABSORB:
        case EFFECT_DRAINING_KISS:
        case EFFECT_BLACK_BUFFET:
        case EFFECT_TICK_TACK:
        case EFFECT_SPIRIT_AWAY:
        case EFFECT_SNAPBLOSSOM:
            if (aiData->abilities[battlerDef] == ABILITY_LIQUID_OOZE)
                score -= 6;
            break;
        case EFFECT_STRENGTH_SAP:
            if (aiData->abilities[battlerDef] == ABILITY_CONTRARY)
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ATK))
                score -= 10;
            break;
        case EFFECT_POWER_DRAIN:
            if (aiData->abilities[battlerDef] == ABILITY_CONTRARY)
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPEED))
                score -= 10;
            break;
        case EFFECT_TROP_KICK:
            if (aiData->abilities[battlerDef] == ABILITY_CONTRARY)
                score -= 4;
            break;
        case EFFECT_DRUM_BEATING:
            if (aiData->abilities[battlerDef] == ABILITY_CONTRARY)
                score -= 3;
            if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            {
                if (PartnerMoveEffectIsTerrain(BATTLE_PARTNER(battlerAtk), aiData->partnerMove) || gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
                    score -= 4;
            }
            break;
        case EFFECT_COPYCAT:
        case EFFECT_MIRROR_MOVE:
            return AI_CheckBadMove(battlerAtk, battlerDef, predictedMove, score);
        case EFFECT_FLOWER_SHIELD:
            if (!IS_BATTLER_OF_TYPE(battlerAtk, TYPE_GRASS)
              && !(isDoubleBattle && IS_BATTLER_OF_TYPE(BATTLE_PARTNER(battlerAtk), TYPE_GRASS)))
                score -= 10;
            break;
        case EFFECT_AROMATIC_MIST:
            if (!isDoubleBattle || gBattleMons[BATTLE_PARTNER(battlerAtk)].hp == 0 || !BattlerStatCanRise(BATTLE_PARTNER(battlerAtk), aiData->abilities[BATTLE_PARTNER(battlerAtk)], STAT_SPDEF))
                score -= 10;
            break;
        case EFFECT_BIDE:
            if (!HasDamagingMove(battlerDef)
              || aiData->hpPercents[battlerAtk] < 25 //Close to death
              || gBattleMons[battlerDef].status1 & (STATUS1_SLEEP_ANY | STATUS1_FREEZE)) //No point in biding if can't take damage
                score -= 10;
            break;
        case EFFECT_HIT_SWITCH_TARGET:
        case EFFECT_BERRY_BAD_JOKE:
            if (DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10; // don't scare away pokemon twice
            else if (aiData->hpPercents[battlerDef] < 10 && GetBattlerSecondaryDamage(battlerDef))
                score -= 10;    // don't blow away mon that will faint soon
            else if (gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
                score -= 10;
            break;
        case EFFECT_SPOOK:
            if (DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10; // don't scare away pokemon twice
            else if (gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
                score -= 10;
            else if (aiData->hpPercents[battlerDef] < 50)
                score += 4;
            break;
        case EFFECT_WOOD_HAMMER:
            if (aiData->abilities[battlerAtk] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT) && aiData->abilities[battlerAtk] != ABILITY_ROCK_HEAD)
            {
                u32 recoilDmg = max(1, aiData->simulatedDmg[battlerAtk][battlerDef][AI_THINKING_STRUCT->movesetIndex] / 3);
                if (!ShouldUseRecoilMove(battlerAtk, battlerDef, recoilDmg, AI_THINKING_STRUCT->movesetIndex))
                    score -= 10;
                if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
                {
                    if (DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                        score -= 10; // don't scare away pokemon twice
                    else if (aiData->hpPercents[battlerDef] < 10 && GetBattlerSecondaryDamage(battlerDef))
                        score -= 10;    // don't blow away mon that will faint soon
                    else if (gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
                        score -= 10;
                }
                break;
            }
            break;
        case EFFECT_CONVERSION:
            //Check first move type
            if (IS_BATTLER_OF_TYPE(battlerAtk, gBattleMoves[gBattleMons[battlerAtk].moves[0]].type))
                score -= 10;
            break;
        case EFFECT_REST:
            if (!AI_CanSleep(battlerAtk, aiData->abilities[battlerAtk]))
                score -= 10;
            //fallthrough
        case EFFECT_RESTORE_HP:
        case EFFECT_HEAL_ORDER:
        case EFFECT_SOFTBOILED:
        case EFFECT_ROOST:
        case EFFECT_CRITICAL_REPAIR:
        case EFFECT_SHIELDS_UP:
            if (AtMaxHp(battlerAtk))
                score -= 10;
            else if (aiData->hpPercents[battlerAtk] >= 90)
                score -= 9; //No point in healing, but should at least do it if nothing better
            else
                score += 2;
            break;
        case EFFECT_VIGOR_ROOT:
            if (AtMaxHp(battlerAtk))
                score -= 10;
            else if (aiData->hpPercents[battlerAtk] >= 90)
                score -= 9; //No point in healing, but should at least do it if nothing better
            else
                score += 2;
            break;
        case EFFECT_RESERVOIR:
            if (gStatuses3[battlerAtk] & STATUS4_PUMPED_UP)
            score -= 5;
            if (AtMaxHp(battlerAtk))
                score -= 10;
            else if (aiData->hpPercents[battlerAtk] >= 90)
                score -= 9; //No point in healing, but should at least do it if nothing better
            break;
        case EFFECT_MORNING_SUN:
        case EFFECT_SYNTHESIS:
        case EFFECT_MOONLIGHT:
            if ((AI_GetWeather(aiData) & (B_WEATHER_RAIN | B_WEATHER_SANDSTORM | B_WEATHER_HAIL)))
                score -= 3;
            else if (AtMaxHp(battlerAtk))
                score -= 10;
            else if (aiData->hpPercents[battlerAtk] >= 90)
                score -= 9; //No point in healing, but should at least do it if nothing better
            break;
        case EFFECT_COLD_MEND:
            if ((AI_GetWeather(aiData) & (B_WEATHER_SANDSTORM | B_WEATHER_SUN)))
                score -= 4;
            else if (AtMaxHp(battlerAtk))
                score -= 10;
            else if (aiData->hpPercents[battlerAtk] >= 90)
                score -= 9; //No point in healing, but should at least do it if nothing better
            break;
        case EFFECT_VERGLASTROM:
            if (!(AI_GetWeather(aiData) & (B_WEATHER_HAIL)))
                score -= 3;
            break;
        case EFFECT_SERPENT_SURGE:
            if (aiData->abilities[battlerAtk] == ABILITY_DRIZZLE)
            {
                if ((AI_GetWeather(aiData) & (B_WEATHER_SANDSTORM | B_WEATHER_SUN)))
                    score -= 3;
                break;
            }
            if (aiData->abilities[battlerAtk] == ABILITY_HYDRATION)
            {
                if (aiData->abilities[battlerDef] == ABILITY_LIQUID_OOZE)
                    score -= 5;
                if (AtMaxHp(battlerAtk))
                    score -= 1;
                break;
            }
            if (aiData->abilities[battlerAtk] == ABILITY_REGENERATOR)
            {
                break;
            }
            break;
        case EFFECT_PURIFY:
            if (!(gBattleMons[battlerDef].status1 & STATUS1_ANY))
                score -= 10;
            else if (battlerDef == BATTLE_PARTNER(battlerAtk))
                break; //Always heal your ally
            else if (AtMaxHp(battlerAtk))
                score -= 10;
            else if (aiData->hpPercents[battlerAtk] >= 90)
                score -= 8; //No point in healing, but should at least do it if nothing better
            break;
        case EFFECT_SUPER_FANG:
            if (aiData->hpPercents[battlerDef] < 50)
                score -= 4;
            break;
        case EFFECT_RECOIL_IF_MISS:
            if (aiData->abilities[battlerAtk] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT) && AI_GetMoveAccuracy(battlerAtk, battlerDef, move) < 75)
                score -= 6;
            break;
        case EFFECT_RECOIL_25:
        case EFFECT_FLYING_PRESS:
            if (aiData->abilities[battlerAtk] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT) && aiData->abilities[battlerAtk] != ABILITY_ROCK_HEAD)
            {
                u32 recoilDmg = max(1, aiData->simulatedDmg[battlerAtk][battlerDef][AI_THINKING_STRUCT->movesetIndex] / 4);
                if (!ShouldUseRecoilMove(battlerAtk, battlerDef, recoilDmg, AI_THINKING_STRUCT->movesetIndex))
                    score -= 10;
                break;
            }
            break;
        case EFFECT_RECOIL_33:
        case EFFECT_RECOIL_33_STATUS:
        case EFFECT_RAZING_SUN:
        case EFFECT_WILD_CHARGE:
            if (aiData->abilities[battlerAtk] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT) && aiData->abilities[battlerAtk] != ABILITY_ROCK_HEAD)
            {
                u32 recoilDmg = max(1, aiData->simulatedDmg[battlerAtk][battlerDef][AI_THINKING_STRUCT->movesetIndex] / 3);
                if (!ShouldUseRecoilMove(battlerAtk, battlerDef, recoilDmg, AI_THINKING_STRUCT->movesetIndex))
                    score -= 10;
                break;
            }
            break;
        case EFFECT_RECOIL_50:
        case EFFECT_RECOIL_50_STATUS:
        case EFFECT_RECOIL_50_HAZARD:
        case EFFECT_CRASH_LAND:
            if (aiData->abilities[battlerAtk] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT) && aiData->abilities[battlerAtk] != ABILITY_ROCK_HEAD)
            {
                u32 recoilDmg = max(1, aiData->simulatedDmg[battlerAtk][battlerDef][AI_THINKING_STRUCT->movesetIndex] / 2);
                if (!ShouldUseRecoilMove(battlerAtk, battlerDef, recoilDmg, AI_THINKING_STRUCT->movesetIndex))
                    score -= 10;
                break;
            }
            break;
        case EFFECT_TEETER_DANCE:
            if (((gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)
              || (!DoesBattlerIgnoreAbilityChecks(aiData->abilities[battlerAtk], move) && aiData->abilities[battlerDef] == ABILITY_OWN_TEMPO)
              || (IsBattlerGrounded(battlerDef) && AI_IsTerrainAffected(battlerDef, STATUS_FIELD_MISTY_TERRAIN))
              || (DoesSubstituteBlockMove(battlerAtk, battlerDef, move)))
             && ((gBattleMons[BATTLE_PARTNER(battlerDef)].status2 & STATUS2_CONFUSION)
              || (!DoesBattlerIgnoreAbilityChecks(aiData->abilities[battlerAtk], move) && aiData->abilities[BATTLE_PARTNER(battlerDef)] == ABILITY_OWN_TEMPO)
              || (IsBattlerGrounded(BATTLE_PARTNER(battlerDef)) && AI_IsTerrainAffected(BATTLE_PARTNER(battlerDef), STATUS_FIELD_MISTY_TERRAIN))
              || (DoesSubstituteBlockMove(battlerAtk, BATTLE_PARTNER(battlerDef), move))))
            {
               score -= 10;
            }
            if (!AI_CanConfuse(battlerAtk, battlerDef, aiData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
            {
                score -= 10;
            }
            IncreaseConfusionScore(battlerAtk, battlerDef, move, &score);
            break;
        case EFFECT_TRANSFORM:
            if (gBattleMons[battlerAtk].status2 & STATUS2_TRANSFORMED
              || (gBattleMons[battlerDef].status2 & (STATUS2_TRANSFORMED | STATUS2_SUBSTITUTE))) //Leave out Illusion b/c AI is supposed to be fooled
                score -= 10;
            break;
        case EFFECT_TWO_TURNS_ATTACK:
            if (aiData->holdEffects[battlerAtk] != HOLD_EFFECT_POWER_HERB && CanTargetFaintAi(battlerDef, battlerAtk))
                score -= 6;
            break;
        case EFFECT_RECHARGE:
        case EFFECT_DRAGON_RUIN:
        case EFFECT_FRENZY_PLANT:
        case EFFECT_RECHARGE_REDUCE:
            if (aiData->abilities[battlerDef] == ABILITY_WONDER_GUARD && effectiveness < AI_EFFECTIVENESS_x2)
                score -= 10;
            else if (aiData->abilities[battlerAtk] != ABILITY_TRUANT
              && !CanIndexMoveFaintTarget(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex, 0))
                score -= 2;
            break;
        case EFFECT_AXEL_HEEL:
            if (aiData->abilities[battlerDef] == ABILITY_WONDER_GUARD && effectiveness < AI_EFFECTIVENESS_x2)
                score -= 10;
            else if (aiData->holdEffects[battlerAtk] != HOLD_EFFECT_POWER_HERB && CanTargetFaintAi(battlerDef, battlerAtk))
                score -= 6;
            else if (aiData->abilities[battlerAtk] != ABILITY_TRUANT
              && !CanIndexMoveFaintTarget(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex, 0))
                score -= 2;
            break;
        case EFFECT_SPITE:
        case EFFECT_MIMIC:
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // Attacker should go first
            {
                if (gLastMoves[battlerDef] == MOVE_NONE
                  || gLastMoves[battlerDef] == 0xFFFF)
                    score -= 10;
            }
            else if (predictedMove == MOVE_NONE)
            {
                // TODO predicted move separate from gLastMoves
                score -= 10;
            }
            break;
        case EFFECT_METRONOME:
        case EFFECT_SURPRISE_EGG:
            break;
        case EFFECT_DANCE_MANIA:
            break;
        case EFFECT_ENDEAVOR:
        case EFFECT_PAIN_SPLIT:
            if (gBattleMons[battlerAtk].hp > (gBattleMons[battlerAtk].hp + gBattleMons[battlerDef].hp) / 2)
                score -= 10;
            break;

        case EFFECT_CONVERSION_2:
            //TODO
            break;
        case EFFECT_MIND_READER:
            if (predictedMove != MOVE_NONE)
            {
                if (!IS_MOVE_STATUS(predictedMove) || AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER) // Opponent going first
                    score -= 2;
            }
        case EFFECT_LOCK_ON:
        case EFFECT_ODOR_SLEUTH:
            if (gStatuses3[battlerDef] & STATUS3_ALWAYS_HITS
              || aiData->abilities[battlerAtk] == ABILITY_NO_GUARD
              || aiData->abilities[battlerDef] == ABILITY_NO_GUARD
              || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_LASER_FOCUS:
            if (gStatuses3[battlerAtk] & STATUS3_LASER_FOCUS)
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_SHELL_ARMOR || aiData->abilities[battlerDef] == ABILITY_BATTLE_ARMOR)
                score -= 8;
            break;
        case EFFECT_SKETCH:
            if (gLastMoves[battlerDef] == MOVE_NONE)
                score -= 10;
            break;
        case EFFECT_DESTINY_BOND:
            if (gBattleMons[battlerDef].status2 & STATUS2_DESTINY_BOND)
                score -= 10;
            break;
        case EFFECT_FALSE_SWIPE:
            // TODO
            break;
        case EFFECT_HEAL_BELL:
            if (!AnyPartyMemberStatused(battlerAtk, gBattleMoves[move].soundMove) || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_AROMATHERAPY:
            if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            {
                if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_SAFEGUARD
                  || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                    score -= 10;
            }
            if (!AnyPartyMemberStatused(battlerAtk, gBattleMoves[move].soundMove) || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_HIT_PREVENT_ESCAPE:
            break;
        case EFFECT_ENDURE:
            if (gBattleMons[battlerAtk].hp == 1 || GetBattlerSecondaryDamage(battlerAtk)) //Don't use Endure if you'll die after using it
                score -= 10;
            break;
        case EFFECT_ALLY_SWITCH:
            if (!isDoubleBattle)
                score -= 10;
            break;
        case EFFECT_PROTECT:
            {
                bool32 decreased = FALSE;
                switch (move)
                {
                case MOVE_PROTECT:
                    if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_BUG))
                    {
                        score -= 10;
                        break;
                    }
                case MOVE_QUICK_GUARD:
                case MOVE_WIDE_GUARD:
                case MOVE_CRAFTY_SHIELD:
                    if (!isDoubleBattle)
                    {
                        score -= 10;
                        decreased = TRUE;
                    }
                    break;
                case MOVE_MAT_BLOCK:
                    if (!gDisableStructs[battlerAtk].isFirstTurn)
                    {
                        score -= 10;
                        decreased = TRUE;
                    }
                    break;
                } // move check

                if (decreased)
                    break;
                if (IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef]))
                {
                    score -= 10;
                    break;
                }

                if (move != MOVE_QUICK_GUARD
                  && move != MOVE_WIDE_GUARD
                  && move != MOVE_CRAFTY_SHIELD) //These moves have infinite usage
                {
                    if (GetBattlerSecondaryDamage(battlerAtk) >= gBattleMons[battlerAtk].hp
                      && aiData->abilities[battlerDef] != ABILITY_MOXIE
                      && aiData->abilities[battlerDef] != ABILITY_DISDAIN
                      && aiData->abilities[battlerDef] != ABILITY_APPETITE
                      && aiData->abilities[battlerDef] != ABILITY_BEAST_BOOST)
                    {
                        score -= 10; //Don't protect if you're going to faint after protecting
                    }
                    else if (gDisableStructs[battlerAtk].protectUses == 1 && Random() % 100 < 50)
                    {
                        if (!isDoubleBattle)
                            score -= 6;
                        else
                            score -= 10; //Don't try double protecting in doubles
                    }
                    else if (gDisableStructs[battlerAtk].protectUses >= 2)
                    {
                        score -= 10;
                    }
                }

                /*if (AI_THINKING_STRUCT->aiFlags == AI_SCRIPT_CHECK_BAD_MOVE //Only basic AI
                && IS_DOUBLE_BATTLE) //Make the regular AI know how to use Protect minimally in Doubles
                {
                    u8 shouldProtect = ShouldProtect(battlerAtk, battlerDef, move);
                    if (shouldProtect == USE_PROTECT || shouldProtect == PROTECT_FROM_FOES)
                        IncreaseFoeProtectionViability(&viability, 0xFF, battlerAtk, battlerDef);
                    else if (shouldProtect == PROTECT_FROM_ALLIES)
                        IncreaseAllyProtectionViability(&viability, 0xFF);
                }*/
            }
            break;
        case EFFECT_MIRACLE_EYE:
            if (gStatuses3[battlerDef] & STATUS3_MIRACLE_EYED)
                score -= 10;
            if (CountPositiveStatStages(battlerDef) <= 0)
                score -= 10;
            break;
        case EFFECT_BURN_UP:
            if (!IS_BATTLER_OF_TYPE(battlerAtk, TYPE_FIRE))
                score -= 10;
            break;
        case EFFECT_DOUBLE_SHOCK:
            if (!IS_BATTLER_OF_TYPE(battlerAtk, TYPE_ELECTRIC))
                score -= 10;
            break;
        case EFFECT_DEFOG:
            if (gSideStatuses[GetBattlerSide(battlerDef)]
             & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_GOOGOO_SCREEN | SIDE_STATUS_SAFEGUARD | SIDE_STATUS_MIST)
              || gSideTimers[GetBattlerSide(battlerDef)].auroraVeilTimer != 0
              || gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_HAZARDS_ANY)
            {
                if (PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                {
                    score -= 10; //Only need one hazards removal
                    break;
                }
            }

            if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_HAZARDS_ANY)
            {
                score -= 10; //Don't blow away opposing hazards
                break;
            }

            if (isDoubleBattle)
            {
                if (IsHazardMoveEffect(gBattleMoves[aiData->partnerMove].effect) // partner is going to set up hazards
                  && AI_WhoStrikesFirst(BATTLE_PARTNER(battlerAtk), battlerAtk, aiData->partnerMove) == AI_IS_FASTER) // partner is going to set up before the potential Defog
                {
                    score -= 10;
                    break; // Don't use Defog if partner is going to set up hazards
                }
            }

            // evasion check
            if (gBattleMons[battlerDef].statStages[STAT_EVASION] == MIN_STAT_STAGE
              || ((aiData->abilities[battlerDef] == ABILITY_CONTRARY) && !IS_TARGETING_PARTNER(battlerAtk, battlerDef))) // don't want to raise target stats unless its your partner
                score -= 10;
            break;

        case EFFECT_PSYCH_UP:   // haze stats check
            {
                for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
                {
                    if (gBattleMons[battlerAtk].statStages[i] > DEFAULT_STAT_STAGE || gBattleMons[BATTLE_PARTNER(battlerAtk)].statStages[i] > DEFAULT_STAT_STAGE)
                        score -= 10;  // Don't want to reset our boosted stats
                }
                for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
                {
                    if (gBattleMons[battlerDef].statStages[i] < DEFAULT_STAT_STAGE || gBattleMons[BATTLE_PARTNER(battlerDef)].statStages[i] < DEFAULT_STAT_STAGE)
                        score -= 10; //Don't want to copy enemy lowered stats
                }
            }
            break;
        case EFFECT_SPECTRAL_THIEF:
        case EFFECT_PLUNDER:
            break;
        case EFFECT_SOLAR_BEAM:
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_POWER_HERB
              || ((AI_GetWeather(aiData) & B_WEATHER_SUN) && aiData->holdEffects[battlerAtk] != HOLD_EFFECT_UTILITY_UMBRELLA))
                break;
            if (CanTargetFaintAi(battlerDef, battlerAtk)) //Attacker can be knocked out
                score -= 4;
            break;
        case EFFECT_AIR_CANNON:
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_POWER_HERB
              || (gSideTimers[GetBattlerSide(battlerAtk)].tailwindTimer != 0))
                break;
            if (CanTargetFaintAi(battlerDef, battlerAtk)) //Attacker can be knocked out
                score -= 4;
            break;
        case EFFECT_SEMI_INVULNERABLE:
        case EFFECT_DIG:
        case EFFECT_DIVE:
        case EFFECT_FLY:
        case EFFECT_SHADOW_FORCE:
            if (predictedMove != MOVE_NONE
              && AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER
              && (gBattleMoves[predictedMove].effect == EFFECT_SEMI_INVULNERABLE
                || gBattleMoves[predictedMove].effect == EFFECT_DIG
                || gBattleMoves[predictedMove].effect == EFFECT_DIVE
                || gBattleMoves[predictedMove].effect == EFFECT_FLY
                || gBattleMoves[predictedMove].effect == EFFECT_SHADOW_FORCE))
                score -= 10; // Don't Fly/dig/etc if opponent is going to fly/dig/etc after you

            if (BattlerWillFaintFromWeather(battlerAtk, aiData->abilities[battlerAtk])
              && (move == MOVE_FLY || move == MOVE_BOUNCE))
                score -= 10; // Attacker will faint while in the air
            break;
        case EFFECT_HEALING_WISH:   //healing wish, lunar dance
            if (CountUsablePartyMons(battlerAtk) == 0 || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            else if (IsPartyFullyHealedExceptBattler(battlerAtk))
                score -= 10;
            break;
        case EFFECT_FINAL_GAMBIT:
            if (CountUsablePartyMons(battlerAtk) == 0 || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_NATURE_POWER:
            return AI_CheckBadMove(battlerAtk, battlerDef, GetNaturePowerMove(), score);
        case EFFECT_TAUNT:
            if (gDisableStructs[battlerDef].tauntTimer > 0
              || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_OCTOLOCK:
            if (gDisableStructs[battlerDef].octolock
              || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPDEF))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_DEF))
                score -= 10;
            else if (gDisableStructs[battlerAtk].isFirstTurn)
                score += 4;
            else if (!gDisableStructs[battlerDef].octolock)
                score += 4;
            break;
        case EFFECT_RAGE_POWDER:
            if (gDisableStructs[battlerDef].tauntTimer > 0
              || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            if (!isDoubleBattle
              || !IsBattlerAlive(BATTLE_PARTNER(battlerAtk))
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove)
              || (aiData->partnerMove != MOVE_NONE && IS_MOVE_STATUS(aiData->partnerMove))
              || *(gBattleStruct->monToSwitchIntoId + BATTLE_PARTNER(battlerAtk)) != PARTY_SIZE) //Partner is switching out.
                score -= 10;
            break;
        case EFFECT_BESTOW:
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_NONE
              || !CanBattlerGetOrLoseItem(battlerAtk, gBattleMons[battlerAtk].item))    // AI knows its own item
                score -= 10;
            break;
        case EFFECT_ROLE_PLAY:
            if (aiData->abilities[battlerAtk] == aiData->abilities[battlerDef]
              || aiData->abilities[battlerDef] == ABILITY_NONE
              || IsRolePlayBannedAbilityAtk(aiData->abilities[battlerAtk])
              || IsRolePlayBannedAbility(aiData->abilities[battlerDef]))
                score -= 10;
            else if (IsAbilityOfRating(aiData->abilities[battlerAtk], 5))
                score -= 4;
            break;
        case EFFECT_WISH:
            if (gWishFutureKnock.wishCounter[battlerAtk] != 0)
                score -= 10;
            break;
        case EFFECT_ASSIST:
            if (CountUsablePartyMons(battlerAtk) == 0)
                score -= 10;    // no teammates to assist from
            break;
        case EFFECT_MAGIC_COAT:
            if (!HasMagicCoatAffectedMove(battlerDef))
                score -= 10;
            if (gDisableStructs[battlerAtk].bounceMove)
                score -= 10;
            break;
        case EFFECT_BELCH:
            if (ItemId_GetPocket(GetUsedHeldItem(battlerAtk)) != POCKET_BERRIES)
                score -= 10; // attacker has not consumed a berry
            break;
        case EFFECT_YAWN:
            if (gStatuses3[battlerDef] & STATUS3_YAWN)
                score -= 10;
            else if (!AI_CanPutToSleep(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_SKILL_SWAP:
            if (aiData->abilities[battlerAtk] == ABILITY_NONE || aiData->abilities[battlerDef] == ABILITY_NONE
              || IsSkillSwapBannedAbility(aiData->abilities[battlerAtk]) || IsSkillSwapBannedAbility(aiData->abilities[battlerDef])
              || aiData->holdEffects[battlerDef] == HOLD_EFFECT_ABILITY_SHIELD)
                score -= 10;
            break;
        case EFFECT_WORRY_SEED:
            if (!AI_CanPanic(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            else if (aiData->abilities[battlerDef] == ABILITY_INSOMNIA
              || IsWorrySeedBannedAbility(aiData->abilities[battlerDef])
              || aiData->holdEffects[battlerDef] == HOLD_EFFECT_ABILITY_SHIELD)
                score -= 6;
            break;
        case EFFECT_GASTRO_ACID:
            if (gStatuses3[battlerDef] & STATUS3_GASTRO_ACID
              || IsGastroAcidBannedAbility(aiData->abilities[battlerDef]))
                score -= 10;
            break;
        case EFFECT_ENTRAINMENT:
            if (aiData->abilities[battlerAtk] == ABILITY_NONE
              || IsEntrainmentBannedAbilityAttacker(aiData->abilities[battlerAtk])
              || IsEntrainmentTargetOrSimpleBeamBannedAbility(aiData->abilities[battlerDef])
              || aiData->holdEffects[battlerAtk] == HOLD_EFFECT_ABILITY_SHIELD)
                score -= 10;
            break;
        case EFFECT_CORE_ENFORCER:
            break;
        case EFFECT_SIMPLE_BEAM:
            if (aiData->abilities[battlerDef] == ABILITY_SIMPLE
              || IsEntrainmentTargetOrSimpleBeamBannedAbility(aiData->abilities[battlerDef])
              || aiData->holdEffects[battlerDef] == HOLD_EFFECT_ABILITY_SHIELD)
                score -= 10;
            break;
        case EFFECT_SNATCH:
            if (!HasSnatchAffectedMove(battlerDef)
              || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_POWER_TRICK:
            if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
                score -= 10;
            else if (gBattleMons[battlerAtk].defense >= gBattleMons[battlerAtk].attack && !HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score -= 10;
            break;
        case EFFECT_GUARD_SWAP: // Don't use if attacker's stat stages are higher than opponents
            if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
                score -= 10;
            else if (gBattleMons[battlerAtk].statStages[STAT_DEF] >= gBattleMons[battlerDef].statStages[STAT_DEF]
              && gBattleMons[battlerAtk].statStages[STAT_SPDEF] >= gBattleMons[battlerDef].statStages[STAT_SPDEF])
                score -= 10;
            break;
        case EFFECT_SPEED_SWAP:
            if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
            {
                score -= 10;
            }
            else
            {
                if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM && (gBattleMons[battlerAtk].speed <= gBattleMons[battlerDef].speed))
                    score -= 10;
                else if (gBattleMons[battlerAtk].speed >= gBattleMons[battlerDef].speed)
                    score -= 10;
            }
            break;
        case EFFECT_POWER_SWAP:
            if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
            {
                score -= 10;
            }
            else
            {
                if (gBattleMons[battlerAtk].attack >= gBattleMons[battlerDef].attack && gBattleMons[battlerAtk].spAttack >= gBattleMons[battlerDef].spAttack)
                    score -= 10;
            }
            if ((!BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_ATK) && !BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK))
             || (!HasDamagingMove(battlerAtk)))
                score -= 10;
            if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_SPATK))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ATK))
                score -= 8;
            if (gDisableStructs[battlerAtk].powerSwap)
                score -= 20;
            break;
        case EFFECT_HEART_SWAP:
            if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
            {
                score -= 10;
            }
            else
            {
                u32 atkPositiveStages = CountPositiveStatStages(battlerAtk);
                u32 atkNegativeStages = CountNegativeStatStages(battlerAtk);
                u32 defPositiveStages = CountPositiveStatStages(battlerDef);
                u32 defNegativeStages = CountNegativeStatStages(battlerDef);

                if (atkPositiveStages >= defPositiveStages && atkNegativeStages <= defNegativeStages)
                    score -= 10;
                break;
            }
            break;
        case EFFECT_POWER_SPLIT:
            if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
            {
                score -= 10;
            }
            else
            {
                u32 atkAttack = gBattleMons[battlerAtk].attack;
                u32 defAttack = gBattleMons[battlerDef].attack;
                u32 atkSpAttack = gBattleMons[battlerAtk].spAttack;
                u32 defSpAttack = gBattleMons[battlerDef].spAttack;

                if (atkAttack + atkSpAttack >= defAttack + defSpAttack) // Combined attacker stats are > than combined target stats
                    score -= 10;
                break;
            }
            break;
        case EFFECT_GUARD_SPLIT:
            if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
            {
                score -= 10;
            }
            else
            {
                u32 atkDefense = gBattleMons[battlerAtk].defense;
                u32 defDefense = gBattleMons[battlerDef].defense;
                u32 atkSpDefense = gBattleMons[battlerAtk].spDefense;
                u32 defSpDefense = gBattleMons[battlerDef].spDefense;

                if (atkDefense + atkSpDefense >= defDefense + defSpDefense) //Combined attacker stats are > than combined target stats
                    score -= 10;
                break;
            }
            break;
        case EFFECT_ME_FIRST:
            if (predictedMove != MOVE_NONE)
            {
                if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER)
                    score -= 10;    // Target is predicted to go first, Me First will fail
                else
                    return AI_CheckBadMove(battlerAtk, battlerDef, predictedMove, score);
            }
            else
            {
                score -= 10; //Target is predicted to switch most likely
            }
            break;
        case EFFECT_NATURAL_GIFT:
            if (aiData->abilities[battlerAtk] == ABILITY_KLUTZ
              || gFieldStatuses & STATUS_FIELD_MAGIC_ROOM
              || GetPocketByItemId(gBattleMons[battlerAtk].item) != POCKET_BERRIES)
                score -= 10;
            break;
        case EFFECT_GRASSY_TERRAIN:
            if (PartnerMoveEffectIsTerrain(BATTLE_PARTNER(battlerAtk), aiData->partnerMove) || gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
                score -= 10;
            break;
        case EFFECT_ELECTRIC_TERRAIN:
            if (PartnerMoveEffectIsTerrain(BATTLE_PARTNER(battlerAtk), aiData->partnerMove) || gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
                score -= 10;
            break;
        case EFFECT_PSYCHIC_TERRAIN:
            if (PartnerMoveEffectIsTerrain(BATTLE_PARTNER(battlerAtk), aiData->partnerMove) || gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
                score -= 10;
            break;
        case EFFECT_MISTY_TERRAIN:
            if (PartnerMoveEffectIsTerrain(BATTLE_PARTNER(battlerAtk), aiData->partnerMove) || gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
                score -= 10;
            break;
        case EFFECT_EARTH_SHATTER:
            if (PartnerMoveEffectIsTerrain(BATTLE_PARTNER(battlerAtk), aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_PLEDGE:
            if (isDoubleBattle && gBattleMons[BATTLE_PARTNER(battlerAtk)].hp > 0)
            {
                if (aiData->partnerMove != MOVE_NONE
                  && gBattleMoves[aiData->partnerMove].effect == EFFECT_PLEDGE
                  && move != aiData->partnerMove) // Different pledge moves
                {
                    if (gBattleMons[BATTLE_PARTNER(battlerAtk)].status1 & (STATUS1_SLEEP_ANY | STATUS1_FREEZE))
                    // && gBattleMons[BATTLE_PARTNER(battlerAtk)].status1 != 1) // Will wake up this turn - how would AI know
                        score -= 10; // Don't use combo move if your partner will cause failure
                }
            }
            break;
        case EFFECT_TRICK_ROOM:
            if (PartnerMoveIs(BATTLE_PARTNER(battlerAtk), aiData->partnerMove, MOVE_TRICK_ROOM))
            {
                score -= 10;
            }
            else if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM) // Trick Room Up
            {
                if (GetBattlerSideSpeedAverage(battlerAtk) < GetBattlerSideSpeedAverage(battlerDef)) // Attacker side slower than target side
                    score -= 10; // Keep the Trick Room up
            }
            else
            {
                if (GetBattlerSideSpeedAverage(battlerAtk) >= GetBattlerSideSpeedAverage(battlerDef)) // Attacker side faster than target side
                    score -= 10; // Keep the Trick Room down
            }
            break;
        case EFFECT_MAGIC_ROOM:
            if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM || PartnerMoveIsSameNoTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_WONDER_ROOM:
            if (gFieldStatuses & STATUS_FIELD_WONDER_ROOM || PartnerMoveIsSameNoTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_GRAVITY:
        case EFFECT_GRAVITON_ARM:
            if ((gFieldStatuses & STATUS_FIELD_GRAVITY
              && !IS_BATTLER_OF_TYPE(battlerAtk, TYPE_FLYING)
              && aiData->holdEffects[battlerAtk] != HOLD_EFFECT_AIR_BALLOON) // Should revert Gravity in this case
              || PartnerMoveIsSameNoTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_FLING:
            if (!CanFling(battlerAtk))
            {
                score -= 10;
            }
            else
            {
                /* TODO Fling
                u8 effect = gFlingTable[gBattleMons[battlerAtk].item].effect;
                switch (effect)
                {
                case MOVE_EFFECT_BURN:
                    if (!AI_CanBurn(battlerAtk, battlerDef, BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                        score -= 10;
                    break;
                case MOVE_EFFECT_PARALYSIS:
                    if (!AI_CanParalyze(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                        score -= 10;
                    break;
                case MOVE_EFFECT_POISON:
                    if (!AI_CanPoison(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                        score -= 10;
                    break;
                case MOVE_EFFECT_TOXIC:
                    if (!AI_CanPoison(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                        score -= 10;
                    break;
                case MOVE_EFFECT_FREEZE:
                    if (!CanBeFrozen(battlerDef, TRUE)
                     || MoveBlockedBySubstitute(move, battlerAtk, battlerDef))
                        score -= 10;
                    break;
                }*/
            }
            break;
        case EFFECT_EMBARGO:
            if (aiData->abilities[battlerDef] == ABILITY_KLUTZ
              || gFieldStatuses & STATUS_FIELD_MAGIC_ROOM
              || gDisableStructs[battlerDef].embargoTimer != 0
              || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_POWDER:
            if (!HasMoveWithType(battlerDef, TYPE_FIRE)
              || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            else if (!ShouldLowerStat(battlerDef, aiData->abilities[battlerDef], STAT_ACC))
                score -= 6;
            else if (aiData->abilities[battlerDef] == ABILITY_KEEN_EYE)
                score -= 8;
            break;
        case EFFECT_SILVER_WIND:
            if (!HasMoveWithType(battlerDef, TYPE_FIRE)
              || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score--;
            break;
        case EFFECT_TELEKINESIS:
            if (gStatuses3[battlerDef] & (STATUS3_TELEKINESIS | STATUS3_ROOTED | STATUS3_SMACKED_DOWN)
              || gFieldStatuses & STATUS_FIELD_GRAVITY
              || aiData->holdEffects[battlerDef] == HOLD_EFFECT_IRON_BALL
              || IsTelekinesisBannedSpecies(gBattleMons[battlerDef].species)
              || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_THROAT_CHOP:
            break;
        case EFFECT_PSYCHIC_NOISE:
            if (gDisableStructs[battlerDef].healBlockTimer != 0
              || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 2;
            break;
        case EFFECT_HEAL_BLOCK:
            if (gDisableStructs[battlerDef].healBlockTimer != 0
              || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_SOAK:
            if (PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove)
              || (GetBattlerType(battlerDef, 0) == TYPE_WATER
              && GetBattlerType(battlerDef, 1) == TYPE_WATER
              && GetBattlerType(battlerDef, 2) == TYPE_MYSTERY))
                score -= 10;    // target is already water-only
            break;
        case EFFECT_PURIFICATION:
            if (PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove)
              || (GetBattlerType(battlerDef, 0) == TYPE_NORMAL
              && GetBattlerType(battlerDef, 1) == TYPE_NORMAL
              && GetBattlerType(battlerDef, 2) == TYPE_MYSTERY))
                score -= 10;    // target is already normal-only
            break;
        case EFFECT_MAGIC_POWDER:
            if (PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove)
              || (GetBattlerType(battlerDef, 0) == TYPE_PSYCHIC
              && GetBattlerType(battlerDef, 1) == TYPE_PSYCHIC
              && GetBattlerType(battlerDef, 2) == TYPE_MYSTERY))
                score -= 10;    // target is already water-only
            if (gStatuses3[battlerDef] & STATUS3_YAWN)
                score -= 10;
            else if (!AI_CanPutToSleep(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_THIRD_TYPE:
            switch (move)
            {
            case MOVE_TRICK_OR_TREAT:
                if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GHOST) || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                    score -= 10;
                break;
            case MOVE_FORESTS_CURSE:
                if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS) || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                    score -= 10;
                break;
            }
            break;
        case EFFECT_HEAL_PULSE: // and floral healing
        case EFFECT_FLORAL_HEALING:
            if (!IS_TARGETING_PARTNER(battlerAtk, battlerDef)) // Don't heal enemies
            {
                score -= 10;
                break;
            }
            // fallthrough
        case EFFECT_HIT_ENEMY_HEAL_ALLY:    // pollen puff
        case EFFECT_TRICK_OR_TREAT:
            if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
            {
                if (gStatuses3[battlerDef] & STATUS3_HEAL_BLOCK)
                    return 0;
                if (AtMaxHp(battlerDef))
                    score -= 10;
                else if (gBattleMons[battlerDef].hp > gBattleMons[battlerDef].maxHP / 2)
                    score -= 5;
            }
            break;
        case EFFECT_ELECTRIFY:
        case EFFECT_ION_DELUGE:
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER
              //|| GetMoveTypeSpecial(battlerDef, predictedMove) == TYPE_ELECTRIC // Move will already be electric type
              || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_TOPSY_TURVY:
            if (!IS_TARGETING_PARTNER(battlerAtk, battlerDef))
            {
                u32 targetPositiveStages = CountPositiveStatStages(battlerDef);
                u32 targetNegativeStages = CountNegativeStatStages(battlerDef);

                if (targetPositiveStages == 0 //No good stat changes to make bad
                  || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                    score -= 10;

                else if (targetNegativeStages < targetPositiveStages)
                    score -= 5; //More stages would be made positive than negative
            }
            break;
        case EFFECT_FAIRY_LOCK:
            if (gStatuses4[battlerDef] & STATUS4_FAIRY_LOCK || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_IMPRISON:
            if (gStatuses4[battlerDef] & STATUS4_IMPRISON || DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_DO_NOTHING:
            score -= 10;
            break;
        case EFFECT_QUASH:
            if (!isDoubleBattle
            || AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER
            || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_SUBMISSION:
            if (!isDoubleBattle
            || AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER
            || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score--;
            if (aiData->abilities[battlerAtk] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT) && aiData->abilities[battlerAtk] != ABILITY_ROCK_HEAD)
            {
                u32 recoilDmg = max(1, aiData->simulatedDmg[battlerAtk][battlerDef][AI_THINKING_STRUCT->movesetIndex] / 4);
                if (!ShouldUseRecoilMove(battlerAtk, battlerDef, recoilDmg, AI_THINKING_STRUCT->movesetIndex))
                    score -= 10;
                break;
            }
            break;
        case EFFECT_AFTER_YOU:
            if (!IS_TARGETING_PARTNER(battlerAtk, battlerDef)
              || !isDoubleBattle
              || AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER
              || PartnerMoveIsSameAsAttacker(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_SUCKER_PUNCH:
        case EFFECT_ROADBLOCK:
        case EFFECT_POISON_DART:
            if (predictedMove != MOVE_NONE)
            {
                if (IS_MOVE_STATUS(predictedMove) || AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER) // Opponent going first
                    score -= 10;
            }
            break;
        case EFFECT_SEIZE_CHANCE:
            if (predictedMove != MOVE_NONE)
            {
                if (!IS_MOVE_STATUS(predictedMove) || AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER) // Opponent going first
                    score -= 2;
            }
            break;
        case EFFECT_TAILWIND:
            if (gSideTimers[GetBattlerSide(battlerAtk)].tailwindTimer != 0
              || PartnerMoveIs(BATTLE_PARTNER(battlerAtk), aiData->partnerMove, MOVE_TAILWIND)
              || (gFieldStatuses & STATUS_FIELD_TRICK_ROOM && gFieldTimers.trickRoomTimer > 1)) // Trick Room active and not ending this turn
                score -= 10;
            break;
        case EFFECT_LUCKY_CHANT:
            if (gSideTimers[GetBattlerSide(battlerAtk)].luckyChantTimer != 0
              || PartnerMoveIsSameNoTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
                score -= 10;
            break;
        case EFFECT_MAGNET_RISE:
            if (gFieldStatuses & STATUS_FIELD_GRAVITY
              ||  gDisableStructs[battlerAtk].magnetRiseTimer != 0
              || aiData->holdEffects[battlerAtk] == HOLD_EFFECT_IRON_BALL
              || gStatuses3[battlerAtk] & (STATUS3_ROOTED | STATUS3_MAGNET_RISE | STATUS3_SMACKED_DOWN)
              || !IsBattlerGrounded(battlerAtk))
                score -= 10;
            break;
        case EFFECT_CAMOUFLAGE:
            if (!CanCamouflage(battlerAtk))
                score -= 10;
            break;
        case EFFECT_LAST_RESORT:
            if (!CanUseLastResort(battlerAtk))
                score -= 10;
            break;
        case EFFECT_SYNCHRONOISE:
            //Check holding ring target or is of same type
            if (aiData->holdEffects[battlerDef] == HOLD_EFFECT_RING_TARGET
              || IS_BATTLER_OF_TYPE(battlerDef, GetBattlerType(battlerAtk, 0))
              || IS_BATTLER_OF_TYPE(battlerDef, GetBattlerType(battlerAtk, 1))
              || IS_BATTLER_OF_TYPE(battlerDef, GetBattlerType(battlerAtk, 2)))
                break;
            else
                score -= 10;
            break;
        case EFFECT_REFLECT_TYPE:
            //Check holding ring target or is of same type
            if ((IS_BATTLER_OF_TYPE(battlerDef, GetBattlerType(battlerAtk, 0))
              || IS_BATTLER_OF_TYPE(battlerDef, GetBattlerType(battlerAtk, 1))
              || IS_BATTLER_OF_TYPE(battlerDef, GetBattlerType(battlerAtk, 2)))
              && gStatuses4[battlerAtk] & STATUS4_REFLECTED_TYPE)
                score -= 10;
            else
                score += 10;
            break;
        case EFFECT_ERUPTION:
            if (effectiveness <= AI_EFFECTIVENESS_x0_5)
                score--;
            if (aiData->hpPercents[battlerDef] < 50)
                score--;
            if (aiData->hpPercents[battlerDef] >= 75)
                score++;
            break;
        case EFFECT_LONE_SHARK:
            if (aiData->hpPercents[battlerDef] < 60)
                score--;
            if (aiData->abilities[battlerDef] == ABILITY_WONDER_GUARD && effectiveness < AI_EFFECTIVENESS_x2)
                score -= 10;
            break;
        case EFFECT_VITAL_THROW:
            if (AI_STRIKES_FIRST(battlerAtk, battlerDef, move) && aiData->hpPercents[battlerAtk] < 40)
                score--;    // don't want to move last
            if (DoesPartnerHaveSameMoveEffect(BATTLE_PARTNER(battlerAtk), battlerDef, move, aiData->partnerMove))
                score -= 10; // don't scare away pokemon twice
            else if (aiData->hpPercents[battlerDef] < 10 && GetBattlerSecondaryDamage(battlerDef))
                score -= 10;    // don't blow away mon that will faint soon
            else if (gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
                score -= 10;
            break;
        case EFFECT_ALL_STATS_UP_2_HIT_FOE:
            if (AI_STRIKES_FIRST(battlerAtk, battlerDef, move) && aiData->hpPercents[battlerAtk] < 40)
                score--;    // don't want to move last
            break;
        case EFFECT_FLAIL:
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER // Opponent should go first
              || aiData->hpPercents[battlerAtk] > 50)
                score -= 4;
            break;
        //TODO
        //case EFFECT_PLASMA_FISTS:
            //break;
        //case EFFECT_SHELL_TRAP:
            //break;
        //case EFFECT_BEAK_BLAST:
            //break;
        case EFFECT_SKY_DROP:
            if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_FLYING))
                score -= 10;
            if (BattlerWillFaintFromWeather(battlerAtk, aiData->abilities[battlerAtk])
            ||  DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
            ||  GetBattlerWeight(battlerDef) >= 2000) //200.0 kg
                score -= 10;
            break;
        case EFFECT_REVIVAL_BLESSING:
            if (GetFirstFaintedPartyIndex(battlerAtk) == PARTY_SIZE)
                score -= 10;
            else if (CanAIFaintTarget(battlerAtk, battlerDef, 0))
                score -= 10;
            else if (CanTargetFaintAi(battlerDef, battlerAtk)
             && AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER)
                score -= 10;
            break;
        case EFFECT_JUNGLE_HEALING:
           if (AtMaxHp(battlerAtk)
            && AtMaxHp(BATTLE_PARTNER(battlerAtk))
            && !(gBattleMons[battlerAtk].status1 & STATUS1_ANY)
            && !(gBattleMons[BATTLE_PARTNER(battlerAtk)].status1 & STATUS1_ANY))
                score -= 10;
            break;
        case EFFECT_TAKE_HEART:
            if ((!(gBattleMons[battlerAtk].status1 & STATUS1_ANY)
             || PartnerMoveIs(BATTLE_PARTNER(battlerAtk), aiData->partnerMove, MOVE_JUNGLE_HEALING)
             || PartnerMoveIs(BATTLE_PARTNER(battlerAtk), aiData->partnerMove, MOVE_HEAL_BELL)
             || PartnerMoveIs(BATTLE_PARTNER(battlerAtk), aiData->partnerMove, MOVE_AROMATHERAPY))
             && !BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK)
             && !BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
                score -= 10;
            break;
        case EFFECT_PLACEHOLDER:
            return 0;   // cannot even select
    } // move effect checks

    if (score < 0)
        score = 0;

    return score;
}

static s32 AI_TryToFaint(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    u32 movesetIndex = AI_THINKING_STRUCT->movesetIndex;
    bool32 aiFaster;

    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
        return score;

    if (gBattleMoves[move].power == 0)
        return score;   // can't make anything faint with no power

    aiFaster = AI_STRIKES_FIRST(battlerAtk, battlerDef, move);
    if (CanIndexMoveFaintTarget(battlerAtk, battlerDef, movesetIndex, 0) && gBattleMoves[move].effect != EFFECT_EXPLOSION)
    {
        // this move can faint the target
        if (aiFaster || GetMovePriority(battlerAtk, move) > 0)
            score += 4; // we go first or we're using priority move
        else
            score += 2;
    }
    else
    {
        // this move isn't expected to faint the target
        if (gBattleMoves[move].highCritRatio)
            score += 2; // crit makes it more likely to make them faint

        if (GetMoveDamageResult(battlerAtk, battlerDef, movesetIndex) == MOVE_POWER_OTHER)
            score--;

        switch (AI_DATA->effectiveness[battlerAtk][battlerDef][movesetIndex])
        {
        case AI_EFFECTIVENESS_x8:
            score += 8;
            break;
        case AI_EFFECTIVENESS_x4:
            score += 4;
            break;
        case AI_EFFECTIVENESS_x2:
            if (AI_RandLessThan(176))
                score += 2;
            else
                score++;
            break;
        }
    }

    //AI_TryToFaint_CheckIfDanger
    if (!aiFaster && CanTargetFaintAi(battlerDef, battlerAtk))
    { // AI_TryToFaint_Danger
        if (GetMoveDamageResult(battlerAtk, battlerDef, movesetIndex) != MOVE_POWER_BEST)
            score--;
        else
            score++;
    }

    return score;
}

// double battle logic
static s32 AI_DoubleBattle(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    // move data
    u32 moveType = gBattleMoves[move].type;
    u32 effect = gBattleMoves[move].effect;
    u32 moveTarget = AI_GetBattlerMoveTargetType(battlerAtk, move);
    // ally data
    u32 battlerAtkPartner = BATTLE_PARTNER(battlerAtk);
    struct AiLogicData *aiData = AI_DATA;
    u32 atkPartnerAbility = aiData->abilities[BATTLE_PARTNER(battlerAtk)];
    u32 atkPartnerHoldEffect = aiData->holdEffects[BATTLE_PARTNER(battlerAtk)];
    bool32 partnerProtecting = (gBattleMoves[aiData->partnerMove].effect == EFFECT_PROTECT);
    bool32 attackerHasBadAbility = (GetAbilityRating(aiData->abilities[battlerAtk]) < 0);
    bool32 partnerHasBadAbility = (GetAbilityRating(atkPartnerAbility) < 0);
    u32 predictedMove = aiData->predictedMoves[battlerDef];

    SetTypeBeforeUsingMove(move, battlerAtk);
    GET_MOVE_TYPE(move, moveType);

    // check what effect partner is using
    if (aiData->partnerMove != 0)
    {
        switch (gBattleMoves[aiData->partnerMove].effect)
        {
        case EFFECT_HELPING_HAND:
        case EFFECT_INSTRUCT:
            if (!IS_MOVE_STATUS(predictedMove))
                score += 5;
            break;
        case EFFECT_PERISH_SONG:
            if (!(gBattleMons[battlerDef].status2 & (STATUS2_ESCAPE_PREVENTION | STATUS2_WRAPPED)))
            {
                if (IsTrappingMoveEffect(effect) || predictedMove == MOVE_INGRAIN)
                    score++;
            }
            break;
        case EFFECT_ALWAYS_CRIT:
        case EFFECT_SEIZE_CHANCE:
        case EFFECT_DUNE_SLICER:
            // Ally decided to use Frost Breath on us. we must have Anger Point as our ability
            if (aiData->abilities[battlerAtk] == ABILITY_ANGER_POINT)
            {
                if (AI_WhoStrikesFirst(battlerAtk, battlerAtkPartner, move) == AI_IS_SLOWER)   // Partner moving first
                {
                    // discourage raising our attack since it's about to be maxed out
                    if (IsAttackBoostMoveEffect(effect))
                        score -= 3;
                    // encourage moves hitting multiple opponents
                    if (!IS_MOVE_STATUS(move) && (moveTarget & (MOVE_TARGET_BOTH | MOVE_TARGET_FOES_AND_ALLY)))
                        score += 3;
                }
            }
            break;
        }
    } // check partner move effect

    // consider our move effect relative to partner state
    switch (effect)
    {
    case EFFECT_HELPING_HAND:
    case EFFECT_INSTRUCT:
        if (aiData->partnerMove != 0 && !HasDamagingMove(battlerAtkPartner))
            score -= 5;
        break;
    case EFFECT_PERISH_SONG:
        if (aiData->partnerMove != 0 && HasTrappingMoveEffect(battlerAtkPartner))
            score++;
        break;
    case EFFECT_MAGNET_RISE:
        if (IsBattlerGrounded(battlerAtk)
          && (HasMove(battlerAtkPartner, MOVE_EARTHQUAKE) || HasMove(battlerAtkPartner, MOVE_MAGNITUDE))
          && (AI_GetMoveEffectiveness(MOVE_EARTHQUAKE, battlerAtk, battlerAtkPartner) != AI_EFFECTIVENESS_x0)) // Doesn't resist ground move
        {
            RETURN_SCORE_PLUS(2);   // partner has earthquake or magnitude -> good idea to use magnet rise
        }
        break;
    } // our effect relative to partner

    // consider global move effects
    switch (effect)
    {
    case EFFECT_SANDSTORM:
        if (ShouldSetSandstorm(battlerAtkPartner, atkPartnerAbility, atkPartnerHoldEffect))
        {
            RETURN_SCORE_PLUS(1);   // our partner benefits from sandstorm
        }
        break;
    case EFFECT_RAIN_DANCE:
        if (ShouldSetRain(battlerAtkPartner, atkPartnerAbility, atkPartnerHoldEffect))
        {
            RETURN_SCORE_PLUS(1);   // our partner benefits from rain
        }
        break;
    case EFFECT_SUNNY_DAY:
    case EFFECT_WARM_WELCOME:
        if (ShouldSetSun(battlerAtkPartner, atkPartnerAbility, atkPartnerHoldEffect))
        {
            RETURN_SCORE_PLUS(1);   // our partner benefits from sun
        }
        break;
    case EFFECT_HAIL:
    case EFFECT_CHILLY_RECEPTION:
        if (IsBattlerAlive(battlerAtkPartner)
         && ShouldSetHail(battlerAtkPartner, atkPartnerAbility, atkPartnerHoldEffect))
        {
            RETURN_SCORE_PLUS(2);   // our partner benefits from hail
        }
        break;
    case EFFECT_SNOWSCAPE:
        if (IsBattlerAlive(battlerAtkPartner)
         && ShouldSetSnow(battlerAtkPartner, atkPartnerAbility, atkPartnerHoldEffect))
        {
            RETURN_SCORE_PLUS(2);   // our partner benefits from snow
        }
        break;
    } // global move effect check

    // check specific target
    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
    {
        if (GetMoveDamageResult(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex) == MOVE_POWER_OTHER)
        {
            // partner ability checks
            if (!partnerProtecting && moveTarget != MOVE_TARGET_BOTH && !DoesBattlerIgnoreAbilityChecks(aiData->abilities[battlerAtk], move))
            {
                switch (atkPartnerAbility)
                {
                case ABILITY_VOLT_ABSORB:
                    if (!(AI_THINKING_STRUCT->aiFlags & AI_FLAG_HP_AWARE))
                    {
                        RETURN_SCORE_MINUS(10);
                    }
                    break;  // handled in AI_HPAware
                case ABILITY_MOTOR_DRIVE:
                    if (moveType == TYPE_ELECTRIC && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_SPEED))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_LIGHTNING_ROD:
                    if (moveType == TYPE_ELECTRIC
                      && HasMoveWithSplit(battlerAtkPartner, SPLIT_SPECIAL)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_SPATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_WITCHCRAFT:
                    if (moveType == TYPE_FAIRY
                      && HasMoveWithSplit(battlerAtkPartner, SPLIT_SPECIAL)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_SPATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_SOUL_LOCKER:
                    if (moveType == TYPE_GHOST
                      && HasMoveWithSplit(battlerAtkPartner, SPLIT_SPECIAL)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_SPATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_MAGNET_PULL:
                    if (moveType == TYPE_STEEL
                      && HasMoveWithSplit(battlerAtkPartner, SPLIT_PHYSICAL)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_ATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_WATER_ABSORB:
                case ABILITY_DRY_SKIN:
                    if (!(AI_THINKING_STRUCT->aiFlags & AI_FLAG_HP_AWARE))
                    {
                        RETURN_SCORE_MINUS(10);
                    }
                    break;  // handled in AI_HPAware
                case ABILITY_EARTH_EATER:
                    if (!(AI_THINKING_STRUCT->aiFlags & AI_FLAG_HP_AWARE))
                    {
                        RETURN_SCORE_MINUS(10);
                    }
                    break;  // handled in AI_HPAware
                case ABILITY_PINK_MIST:
                    if (moveType == TYPE_PSYCHIC && AI_IsTerrainAffected(battlerAtkPartner, STATUS_FIELD_MISTY_TERRAIN))
                        RETURN_SCORE_MINUS(10);
                    break;
                case ABILITY_IMMUNITY:
                    if (moveType == TYPE_POISON)
                        RETURN_SCORE_MINUS(10);
                    break;
                case ABILITY_EMPTY:
                    if (moveType == TYPE_NORMAL || moveType == TYPE_FIGHTING)
                        RETURN_SCORE_MINUS(10);
                    break;
                case ABILITY_ALL_GAME:
                    if (moveType == TYPE_WATER || moveType == TYPE_GROUND)
                        RETURN_SCORE_MINUS(10);
                    break;
                case ABILITY_STORM_DRAIN:
                    if (moveType == TYPE_WATER
                      && HasMoveWithSplit(battlerAtkPartner, SPLIT_SPECIAL)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_SPATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_WATER_COMPACTION:
                    if (moveType == TYPE_WATER && GetMoveDamageResult(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex) == MOVE_POWER_WEAK)
                    {
                        RETURN_SCORE_PLUS(1);   // only mon with this ability is weak to water so only make it okay if we do very little damage
                    }
                    RETURN_SCORE_MINUS(10);
                    break;
                case ABILITY_FLASH_FIRE:
                    if (moveType == TYPE_FIRE
                      && HasMoveWithSplit(battlerAtkPartner, SPLIT_PHYSICAL)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_ATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_SAP_SIPPER:
                    if (moveType == TYPE_GRASS
                      && HasMoveWithSplit(battlerAtkPartner, SPLIT_PHYSICAL)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_ATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_JUSTIFIED:
                    if (moveType == TYPE_DARK
                      && !IS_MOVE_STATUS(move)
                      && HasMoveWithSplit(battlerAtkPartner, SPLIT_PHYSICAL)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_ATK)
                      && !CanIndexMoveFaintTarget(battlerAtk, battlerAtkPartner, AI_THINKING_STRUCT->movesetIndex, 1))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_RATTLED:
                    if (!IS_MOVE_STATUS(move)
                      && (moveType == TYPE_DARK || moveType == TYPE_GHOST || moveType == TYPE_BUG)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_SPEED)
                      && !CanIndexMoveFaintTarget(battlerAtk, battlerAtkPartner, AI_THINKING_STRUCT->movesetIndex, 1))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_CONTRARY:
                    if (IsStatLoweringEffect(effect))
                    {
                        RETURN_SCORE_PLUS(2);
                    }
                    break;
                case ABILITY_DEFIANT:
                    if (IsStatLoweringEffect(effect)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_ATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                case ABILITY_COMPETITIVE:
                    if (IsStatLoweringEffect(effect)
                      && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_SPATK))
                    {
                        RETURN_SCORE_PLUS(1);
                    }
                    break;
                }
            } // ability checks
        } // move power check

        // attacker move effects specifically targeting partner
        if (!partnerProtecting)
        {
            switch (effect)
            {
            case EFFECT_PURIFY:
                if (gBattleMons[battlerAtkPartner].status1 & STATUS1_ANY)
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_SWAGGER:
                if (gBattleMons[battlerAtkPartner].statStages[STAT_ATK] < MAX_STAT_STAGE
                 && HasMoveWithSplit(battlerAtkPartner, SPLIT_PHYSICAL)
                 && (!AI_CanBeConfused(battlerAtkPartner, TRUE)
                  || atkPartnerHoldEffect == HOLD_EFFECT_CURE_CONFUSION
                  || atkPartnerHoldEffect == HOLD_EFFECT_CURE_STATUS))
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_FLATTER:
                if (gBattleMons[battlerAtkPartner].statStages[STAT_SPATK] < MAX_STAT_STAGE
                 && HasMoveWithSplit(battlerAtkPartner, SPLIT_SPECIAL)
                 && (!AI_CanBeConfused(battlerAtkPartner, TRUE)
                  || atkPartnerHoldEffect == HOLD_EFFECT_CURE_CONFUSION
                  || atkPartnerHoldEffect == HOLD_EFFECT_CURE_STATUS))
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_BEAT_UP:
                if (atkPartnerAbility == ABILITY_JUSTIFIED
                  && moveType == TYPE_DARK
                  && !IS_MOVE_STATUS(move)
                  && HasMoveWithSplit(battlerAtkPartner, SPLIT_PHYSICAL)
                  && BattlerStatCanRise(battlerAtkPartner, atkPartnerAbility, STAT_ATK)
                  && !CanIndexMoveFaintTarget(battlerAtk, battlerAtkPartner, AI_THINKING_STRUCT->movesetIndex, 0))
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_SKILL_SWAP:
                if (aiData->abilities[battlerAtk] != aiData->abilities[BATTLE_PARTNER(battlerAtk)] && !attackerHasBadAbility)
                {
                    if (aiData->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_TRUANT)
                    {
                        RETURN_SCORE_PLUS(10);
                    }
                    else if (aiData->abilities[battlerAtk] == ABILITY_COMPOUND_EYES
                     && HasMoveWithLowAccuracy(battlerAtkPartner, FOE(battlerAtkPartner), 90, TRUE, atkPartnerAbility, aiData->abilities[FOE(battlerAtkPartner)], atkPartnerHoldEffect, aiData->holdEffects[FOE(battlerAtkPartner)]))
                    {
                        RETURN_SCORE_PLUS(3);
                    }
                }
                break;
            case EFFECT_ROLE_PLAY:
                if (attackerHasBadAbility && !partnerHasBadAbility)
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_WORRY_SEED:
            case EFFECT_GASTRO_ACID:
            case EFFECT_SIMPLE_BEAM:
                if (partnerHasBadAbility)
                {
                    RETURN_SCORE_PLUS(2);
                }
                break;
            case EFFECT_ENTRAINMENT:
                if (partnerHasBadAbility && IsAbilityOfRating(aiData->abilities[battlerAtk], 0))
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_SOAK:
                if (atkPartnerAbility == ABILITY_WONDER_GUARD
                 && (GetBattlerType(battlerAtkPartner, 0) != TYPE_WATER
                 || GetBattlerType(battlerAtkPartner, 1) != TYPE_WATER
                 || GetBattlerType(battlerAtkPartner, 2) != TYPE_WATER))
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_PURIFICATION:
                if (atkPartnerAbility == ABILITY_WONDER_GUARD
                 && (GetBattlerType(battlerAtkPartner, 0) != TYPE_NORMAL
                 || GetBattlerType(battlerAtkPartner, 1) != TYPE_NORMAL
                 || GetBattlerType(battlerAtkPartner, 2) != TYPE_NORMAL))
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_MAGIC_POWDER:
                if (atkPartnerAbility == ABILITY_WONDER_GUARD
                 && (GetBattlerType(battlerAtkPartner, 0) != TYPE_PSYCHIC
                 || GetBattlerType(battlerAtkPartner, 1) != TYPE_PSYCHIC
                 || GetBattlerType(battlerAtkPartner, 2) != TYPE_PSYCHIC))
                {
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_AFTER_YOU:
                if (AI_WhoStrikesFirst(battlerAtkPartner, FOE(battlerAtkPartner), aiData->partnerMove) == AI_IS_SLOWER  // Opponent mon 1 goes before partner
                  || AI_WhoStrikesFirst(battlerAtkPartner, BATTLE_PARTNER(FOE(battlerAtkPartner)), aiData->partnerMove) == AI_IS_SLOWER) // Opponent mon 2 goes before partner
                {
                    if (gBattleMoves[aiData->partnerMove].effect == EFFECT_COUNTER || gBattleMoves[aiData->partnerMove].effect == EFFECT_MIRROR_COAT)
                        break; // These moves need to go last
                    RETURN_SCORE_PLUS(1);
                }
                break;
            case EFFECT_HEAL_PULSE:
            case EFFECT_HIT_ENEMY_HEAL_ALLY:
            case EFFECT_TRICK_OR_TREAT:
            case EFFECT_FLORAL_HEALING:
            case EFFECT_JUNGLE_HEALING:
                if (AI_WhoStrikesFirst(battlerAtk, FOE(battlerAtk), move) == AI_IS_FASTER
                  && AI_WhoStrikesFirst(battlerAtk, BATTLE_PARTNER(FOE(battlerAtk)), move) == AI_IS_FASTER
                  && gBattleMons[battlerAtkPartner].hp < gBattleMons[battlerAtkPartner].maxHP / 2)
                    RETURN_SCORE_PLUS(1);
                break;
            } // attacker move effects
        } // check partner protecting

        score -= 30; // otherwise, don't target partner
    }
    else // checking opponent
    {
        // these checks mostly handled in AI_CheckBadMove and AI_CheckViability
        switch (effect)
        {
        case EFFECT_SKILL_SWAP:
            if (aiData->abilities[battlerAtk] == ABILITY_TRUANT)
                score += 5;
            else if (IsAbilityOfRating(aiData->abilities[battlerAtk], 0) || IsAbilityOfRating(aiData->abilities[battlerDef], 10))
                score += 2; // we want to transfer our bad ability or take their awesome ability
            break;
        case EFFECT_EARTHQUAKE:
        case EFFECT_MAGNITUDE:
            if (!IsBattlerGrounded(battlerAtkPartner)
             || (IsBattlerGrounded(battlerAtkPartner)
               && AI_WhoStrikesFirst(battlerAtk, battlerAtkPartner, move) == AI_IS_SLOWER
               && IsUngroundingEffect(gBattleMoves[aiData->partnerMove].effect)))
                score += 2;
            else if (IS_BATTLER_OF_TYPE(battlerAtkPartner, TYPE_FIRE)
              || IS_BATTLER_OF_TYPE(battlerAtkPartner, TYPE_ELECTRIC)
              || IS_BATTLER_OF_TYPE(battlerAtkPartner, TYPE_POISON)
              || IS_BATTLER_OF_TYPE(battlerAtkPartner, TYPE_ROCK))
                score -= 10;    // partner will be hit by earthquake and is weak to it
            else if (IsBattlerAlive(battlerAtkPartner))
                score -= 3;
            break;
        case EFFECT_KERFUFFLE:
            if (IS_BATTLER_OF_TYPE(battlerAtkPartner, TYPE_FIGHTING)
              || IS_BATTLER_OF_TYPE(battlerAtkPartner, TYPE_DRAGON)
              || IS_BATTLER_OF_TYPE(battlerAtkPartner, TYPE_DARK))
                score -= 10;    // partner will be hit by kerfuffle and is weak to it
            else if (IsBattlerAlive(battlerAtkPartner))
                score -= 3;
            break;
        }

        // lightning rod, flash fire against enemy handled in AI_CheckBadMove
    }

    return score;
}

static bool32 IsPinchBerryItemEffect(u32 holdEffect)
{
    switch (holdEffect)
    {
    case HOLD_EFFECT_ATTACK_UP:
    case HOLD_EFFECT_DEFENSE_UP:
    case HOLD_EFFECT_SPEED_UP:
    case HOLD_EFFECT_SP_ATTACK_UP:
    case HOLD_EFFECT_SP_DEFENSE_UP:
    case HOLD_EFFECT_CRITICAL_UP:
    case HOLD_EFFECT_RANDOM_STAT_UP:
    case HOLD_EFFECT_CUSTAP_BERRY:
    case HOLD_EFFECT_MICLE_BERRY:
        return TRUE;
    }

    return FALSE;
}

static u32 GetAIMostDamagingMoveId(u32 battlerAtk, u32 battlerDef)
{
    u32 i, id = 0;
    u32 mostDmg = 0;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (AI_DATA->simulatedDmg[battlerAtk][battlerDef][i] > mostDmg)
            id = i, mostDmg = AI_DATA->simulatedDmg[battlerAtk][battlerDef][i];
    }
    return id;
}

// AI_FLAG_CHECK_VIABILITY - a weird mix of increasing and decreasing scores
static s32 AI_CheckViability(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    // move data
    u32 moveEffect = gBattleMoves[move].effect;
    struct AiLogicData *aiData = AI_DATA;
    u32 effectiveness = aiData->effectiveness[battlerAtk][battlerDef][AI_THINKING_STRUCT->movesetIndex];
    s8 atkPriority = GetMovePriority(battlerAtk, move);
    u32 predictedMove = aiData->predictedMoves[battlerDef];
    u32 predictedMoveSlot = GetMoveSlot(GetMovesArray(battlerDef), predictedMove);
    bool32 isDoubleBattle = IsValidDoubleBattle(battlerAtk);
    u32 i;
    // We only check for moves that have a 20% chance or more for their secondary effect to happen because moves with a smaller chance are rather worthless. We don't want the AI to use those.
    bool32 sereneGraceBoost = ((aiData->abilities[battlerAtk] == ABILITY_SERENE_GRACE || aiData->abilities[battlerAtk] == ABILITY_RISKTAKER || aiData->abilities[battlerAtk] == ABILITY_SERENE_AURA) && (gBattleMoves[move].secondaryEffectChance >= 20 && gBattleMoves[move].secondaryEffectChance < 100));

    if (gBattleMoves[move].soundMove && aiData->holdEffects[battlerAtk] == HOLD_EFFECT_THROAT_SPRAY)
        score += 8;

    // Targeting partner, check benefits of doing that instead
    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
        return score;

    // check always hits
    if (!IS_MOVE_STATUS(move) && gBattleMoves[move].accuracy == 0)
    {
        // If 2 moves can KO the target in the same number of turns, but one of them always hits and there is a risk the other move could miss, prioritize the always hits move.
        if (gBattleMons[battlerDef].statStages[STAT_EVASION] > 6 || gBattleMons[battlerAtk].statStages[STAT_ACC] < 6)
        {
            u32 mostDmgMoveId = GetAIMostDamagingMoveId(battlerAtk, battlerDef);
            u32 *dmgs = aiData->simulatedDmg[battlerAtk][battlerDef];
            if (GetNoOfHitsToKO(dmgs[mostDmgMoveId], gBattleMons[battlerDef].hp) == GetNoOfHitsToKO(dmgs[AI_THINKING_STRUCT->movesetIndex], gBattleMons[battlerDef].hp))
                score++;
        }
        if (gBattleMons[battlerDef].statStages[STAT_EVASION] >= 10 || gBattleMons[battlerAtk].statStages[STAT_ACC] <= 2)
            score++;
        if (AI_RandLessThan(100) && (gBattleMons[battlerDef].statStages[STAT_EVASION] >= 8 || gBattleMons[battlerAtk].statStages[STAT_ACC] <= 4))
            score++;
    }

    // check high crit
    if (gBattleMoves[move].highCritRatio && effectiveness >= AI_EFFECTIVENESS_x2 && AI_RandLessThan(128))
        score++;

    // check already dead
    if (!IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef])
      && CanTargetFaintAi(battlerAtk, battlerDef)
      && AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER) // Opponent should go first
    {
        if (atkPriority > 0)
            score++;
        else
            score--;
    }

    // check damage
    if (gBattleMoves[move].power != 0 && GetMoveDamageResult(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex) == MOVE_POWER_WEAK)
        score--;

    // check status move preference
    if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_PREFER_STATUS_MOVES && IS_MOVE_STATUS(move) && effectiveness != AI_EFFECTIVENESS_x0)
        score++;

    if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_PASSAWARY)
    {
        i = Random() % 2;

        if (i < 1 && moveEffect == EFFECT_DARK_VOID)
            score += 100;
        else if (i < 2 && moveEffect == EFFECT_WILL_O_WISP)
            score += 100;
    }
    
    // check thawing moves
    if ((gBattleMons[battlerAtk].status1 & (STATUS1_FREEZE | STATUS1_FROSTBITE)) && gBattleMoves[move].thawsUser)
        score += (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) ? 20 : 10;

    // check burn
    if (gBattleMons[battlerAtk].status1 & STATUS1_BURN)
    {
        switch (aiData->abilities[battlerAtk])
        {
        case ABILITY_GUTS:
            break;
        case ABILITY_NATURAL_CURE:
            if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_SMART_SWITCHING
             && HasOnlyMovesWithSplit(battlerAtk, SPLIT_PHYSICAL, TRUE))
                score = 90; // Force switch if all your attacking moves are physical and you have Natural Cure.
            break;
        default:
            if (IS_MOVE_PHYSICAL(move) && gBattleMoves[move].effect != EFFECT_FACADE)
                score -= 2;
            break;
        }
    }

    // check frostbite
    if (gBattleMons[battlerAtk].status1 & STATUS1_FROSTBITE)
    {
        switch (aiData->abilities[battlerAtk])
        {
        case ABILITY_GUTS:
            break;
        case ABILITY_NATURAL_CURE:
            if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_SMART_SWITCHING
             && HasOnlyMovesWithSplit(battlerAtk, SPLIT_SPECIAL, TRUE))
                score = 90; // Force switch if all your attacking moves are special and you have Natural Cure.
            break;
        default:
            if (IS_MOVE_SPECIAL(move) && gBattleMoves[move].effect != EFFECT_FACADE)
                score -= 2;
            break;
        }
    }

    // attacker ability checks
    switch (aiData->abilities[battlerAtk])
    {
    case ABILITY_MOXIE:
    case ABILITY_DISDAIN:
    case ABILITY_APPETITE:
    case ABILITY_BEAST_BOOST:
    case ABILITY_CHILLING_NEIGH:
    case ABILITY_GRIM_NEIGH:
    case ABILITY_AS_ONE_ICE_RIDER:
    case ABILITY_AS_ONE_SHADOW_RIDER:
        if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // Attacker should go first
        {
            if (CanIndexMoveFaintTarget(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex, 0))
                score += 8; // prioritize killing target for stat boost
        }
        break;
    case ABILITY_FROST_JAW:
        if (gBattleMoves[move].bitingMove)
            score += 8;
        break;
    case ABILITY_OWN_TEMPO:
        if (gBattleMoves[move].danceMove)
            score += 8;
        break;
    case ABILITY_PURPLE_HAZE:
        if (gBattleMoves[move].gasMove 
            && (gDisableStructs[battlerAtk].purpleHazeOffense == FALSE
            && gDisableStructs[battlerAtk].purpleHazeDefense == FALSE))
            score += 8;
        break;
    case ABILITY_RAPID_FIRE:
        if (move == MOVE_TRUMP_CARD || move == MOVE_PILGRIMAGE)
            score += 2;
        break;
    case ABILITY_PRODIGY:
    case ABILITY_LOVESICK:
    case ABILITY_PICKPOCKET:
        if (AI_MoveMakesContact(aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk], move))
            score += 8;
        break;
    case ABILITY_AMBUSHER:
        if (IS_MOVE_PHYSICAL(move) && gDisableStructs[battlerAtk].isFirstTurn)
            score += 8;
        break;
    } // ability checks

    // move effect checks
    switch (moveEffect)
    {
    case EFFECT_HIT:
        break;
    case EFFECT_SLEEP:
    case EFFECT_DARK_VOID:
    case EFFECT_YAWN:
    case EFFECT_SLEEP_POWDER:
        if (AI_RandLessThan(128))
            IncreaseSleepScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_ABSORB:
    case EFFECT_TICK_TACK:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_BIG_ROOT)
            score++;
        if (effectiveness <= AI_EFFECTIVENESS_x0_5 && AI_RandLessThan(50))
            score -= 3;
        break;
    case EFFECT_DRAINING_KISS:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_BIG_ROOT)
            score++;
        if (effectiveness <= AI_EFFECTIVENESS_x0_5 && AI_RandLessThan(50))
            score -= 3;
        if (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)
            score += 2;
        break;
    case EFFECT_VENOM_DRAIN:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_BIG_ROOT)
            score++;
        if (effectiveness <= AI_EFFECTIVENESS_x0_5 && AI_RandLessThan(50))
            score -= 3;
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY)
            score += 4;
        break;
    case EFFECT_SNAPBLOSSOM:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_BIG_ROOT)
            score++;
        if (effectiveness <= AI_EFFECTIVENESS_x0_5 && AI_RandLessThan(50))
            score -= 3;
        if (ShouldBloomSelf(battlerAtk, aiData->abilities[battlerAtk]))
            score += 2;
        break;
    case EFFECT_EXPLOSION:
    case EFFECT_MEMENTO:
        if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_WILL_SUICIDE && gBattleMons[battlerDef].statStages[STAT_EVASION] < 7)
        {
            if (aiData->hpPercents[battlerAtk] < 50 && AI_RandLessThan(128))
                score++;
        }
        break;
    case EFFECT_MIRROR_MOVE:
        if (predictedMove != MOVE_NONE)
            return AI_CheckViability(battlerAtk, battlerDef, gLastMoves[battlerDef], score);
        break;
// stat raising effects
    case EFFECT_ATTACK_UP:
    case EFFECT_ATTACK_UP_2:
    case EFFECT_ATTACK_UP_USER_ALLY:
        if (gDisableStructs[battlerAtk].purified)
            score -= 30;
        if (HasMoveEffect(battlerAtk, EFFECT_STORED_POWER))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_HAYWIRE))
            score += 2;
        if (MovesWithSplitUnusable(battlerAtk, battlerDef, SPLIT_PHYSICAL))
        {
            score -= 8;
            break;
        }
        else if (gBattleMons[battlerAtk].statStages[STAT_ATK] < 9)
        {
            if (aiData->hpPercents[battlerAtk] > 90 && AI_RandLessThan(128))
            {
                score += 2;
                break;
            }
        }

        if (!AI_RandLessThan(100))
        {
            score--;
        }
        break;
    case EFFECT_DEFENSE_UP:
    case EFFECT_DEFENSE_UP_2:
    case EFFECT_DEFENSE_UP_3:
    case EFFECT_ACID_ARMOR:
        if (gDisableStructs[battlerAtk].purified)
            score -= 30;
        if (HasMoveEffect(battlerAtk, EFFECT_STORED_POWER))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_HAYWIRE))
            score += 2;
        if (!HasMoveWithSplit(battlerDef, SPLIT_PHYSICAL))
            score -= 2;
        if (aiData->hpPercents[battlerAtk] > 90 && AI_RandLessThan(128))
            score += 2;
        else if (aiData->hpPercents[battlerAtk] > 70 && AI_RandLessThan(200))
            break;
        else if (aiData->hpPercents[battlerAtk] < 40)
            score -= 2;
        break;
    case EFFECT_SPEED_UP:
    case EFFECT_SPEED_UP_2:
    case EFFECT_SPEED_UP_USER_ALLY:
        if (gDisableStructs[battlerAtk].purified)
            score -= 30;
        if (HasMoveEffect(battlerAtk, EFFECT_STORED_POWER))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_HAYWIRE))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_FROST_SHRED) && gBattleMons[battlerAtk].statStages[STAT_SPEED] < 9)
            score += 6;
        else if (HasMoveEffect(battlerAtk, EFFECT_FROST_SHRED))
            score += 2;
        if (!AI_STRIKES_FIRST(battlerAtk, battlerDef, move))
        {
            if (!AI_RandLessThan(70))
                score += 3;
        }
        else
        {
            score -= 3;
        }
        break;
    case EFFECT_SPECIAL_ATTACK_UP:
    case EFFECT_SPECIAL_ATTACK_UP_2:
    case EFFECT_SPECIAL_ATTACK_UP_3:
        if (gDisableStructs[battlerAtk].purified)
            score -= 30;
        if (HasMoveEffect(battlerAtk, EFFECT_STORED_POWER))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_HAYWIRE))
            score += 2;
        if (MovesWithSplitUnusable(battlerAtk, battlerDef, SPLIT_SPECIAL))
        {
            score -= 8;
            break;
        }
        else if (gBattleMons[battlerAtk].statStages[STAT_SPATK] < 9)
        {
            if (aiData->hpPercents[battlerAtk] > 90 && AI_RandLessThan(128))
            {
                score += 2;
                break;
            }
        }

        if (!AI_RandLessThan(100))
        {
            score--;
        }
        break;
    case EFFECT_SPECIAL_DEFENSE_UP:
    case EFFECT_SPECIAL_DEFENSE_UP_2:
        if (gDisableStructs[battlerAtk].purified)
            score -= 30;
        if (HasMoveEffect(battlerAtk, EFFECT_STORED_POWER))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_HAYWIRE))
            score += 2;
        if (!HasMoveWithSplit(battlerDef, SPLIT_SPECIAL))
            score -= 2;
        if (aiData->hpPercents[battlerAtk] > 90 && AI_RandLessThan(128))
            score += 2;
        else if (aiData->hpPercents[battlerAtk] > 70 && AI_RandLessThan(200))
            break;
        else if (aiData->hpPercents[battlerAtk] < 40)
            score -= 2;
        break;
    case EFFECT_ACCURACY_UP:
    case EFFECT_ACCURACY_UP_2:
        if (gDisableStructs[battlerAtk].purified)
            score -= 30;
        if (HasMoveEffect(battlerAtk, EFFECT_STORED_POWER))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_HAYWIRE))
            score += 2;
        if (gBattleMons[battlerAtk].statStages[STAT_ACC] >= 9 && !AI_RandLessThan(50))
            score -= 2;
        else if (aiData->hpPercents[battlerAtk] <= 70)
            score -= 2;
        else
            score++;
        break;
    case EFFECT_GREEN_GUISE:
        if (ShouldBloomSelf(battlerAtk, aiData->abilities[battlerAtk]))
            score += 2;
        if (!AI_CanBloom(battlerAtk, battlerDef, move))
            score -= 1;
        if (aiData->abilities[battlerAtk] == ABILITY_SUPER_LUCK
          || aiData->abilities[battlerAtk] == ABILITY_SNIPER
          || aiData->abilities[battlerAtk] == ABILITY_RISKTAKER
          || aiData->holdEffects[battlerAtk] == HOLD_EFFECT_SCOPE_LENS
          || HasHighCritRatioMove(battlerAtk))
            score += 2;
        if (aiData->abilities[battlerAtk] == ABILITY_INNER_FOCUS)
            score++;
        if (gDisableStructs[battlerAtk].purified)
            score -= 2;
        if (HasMoveEffect(battlerAtk, EFFECT_STORED_POWER))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_HAYWIRE))
            score += 2;
        if (aiData->hpPercents[battlerAtk] > 90 && !AI_RandLessThan(100))
            score += 3;
        if (gBattleMons[battlerAtk].statStages[STAT_EVASION] > 9 && AI_RandLessThan(128))
            score--;
        if ((gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY) && aiData->hpPercents[battlerAtk] >= 50 && !AI_RandLessThan(80))
            score += 3;
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED && !AI_RandLessThan(70))
            score += 3;
        if (gStatuses3[battlerAtk] & STATUS3_ROOTED && AI_RandLessThan(128))
            score += 2;
        if (gBattleMons[battlerDef].status2 & STATUS2_CURSED && !AI_RandLessThan(70))
            score += 3;
        if (aiData->hpPercents[battlerAtk] < 70 || gBattleMons[battlerAtk].statStages[STAT_EVASION] == DEFAULT_STAT_STAGE)
            break;
        else if (aiData->hpPercents[battlerAtk] < 40 || aiData->hpPercents[battlerDef] < 40)
            score -= 1;
        else if (!AI_RandLessThan(70))
            score -= 1;
        break;
    case EFFECT_EVASION_UP:
    case EFFECT_EVASION_UP_2:
        if (gDisableStructs[battlerAtk].purified)
            score -= 30;
        if (HasMoveEffect(battlerAtk, EFFECT_STORED_POWER))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_HAYWIRE))
            score += 2;
        if (aiData->hpPercents[battlerAtk] > 90 && !AI_RandLessThan(100))
            score += 3;
        if (gBattleMons[battlerAtk].statStages[STAT_EVASION] > 9 && AI_RandLessThan(128))
            score--;
        if ((gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY) && aiData->hpPercents[battlerAtk] >= 50 && !AI_RandLessThan(80))
            score += 3;
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED && !AI_RandLessThan(70))
            score += 3;
        if (gStatuses3[battlerAtk] & STATUS3_ROOTED && AI_RandLessThan(128))
            score += 2;
        if (gBattleMons[battlerDef].status2 & STATUS2_CURSED && !AI_RandLessThan(70))
            score += 3;
        if (aiData->hpPercents[battlerAtk] < 70 || gBattleMons[battlerAtk].statStages[STAT_EVASION] == DEFAULT_STAT_STAGE)
            break;
        else if (aiData->hpPercents[battlerAtk] < 40 || aiData->hpPercents[battlerDef] < 40)
            score -= 2;
        else if (!AI_RandLessThan(70))
            score -= 2;
        break;
    case EFFECT_SYRUP_BOMB:
        if (AI_STRIKES_FIRST(battlerAtk, battlerDef, move))
            score--;
        else if (!AI_RandLessThan(70))
            score += 2;
        break;
// stat lowering effects
    case EFFECT_ATTACK_DOWN:
    case EFFECT_ATTACK_DOWN_2:
    case EFFECT_FEATHER_DANCE:
        if (!ShouldLowerAttack(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if (gBattleMons[battlerDef].statStages[STAT_ATK] < DEFAULT_STAT_STAGE)
            score--;
        else if (aiData->hpPercents[battlerAtk] <= 90)
            score--;
        if (gBattleMons[battlerDef].statStages[STAT_ATK] > 3 && !AI_RandLessThan(50))
            score -= 2;
        else if (aiData->hpPercents[battlerDef] < 70)
            score -= 2;
        break;
    case EFFECT_DEFENSE_DOWN:
    case EFFECT_DEFENSE_DOWN_2:
    case EFFECT_DEFENSE_DOWN_HIT_2:
        if (!ShouldLowerDefense(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if ((aiData->hpPercents[battlerAtk] < 70 && !AI_RandLessThan(50)) || (gBattleMons[battlerDef].statStages[STAT_DEF] <= 3 && !AI_RandLessThan(50)))
            score -= 2;
        if (aiData->hpPercents[battlerDef] <= 70)
            score -= 2;
        break;
    case EFFECT_SPEED_DOWN:
    case EFFECT_SPEED_DOWN_2:
        if (AI_STRIKES_FIRST(battlerAtk, battlerDef, move))
            score -= 3;
        else if (!AI_RandLessThan(70))
            score += 2;
        break;
    case EFFECT_SPECIAL_ATTACK_DOWN:
    case EFFECT_SPECIAL_ATTACK_DOWN_2:
        if (!ShouldLowerSpAtk(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if (gBattleMons[battlerDef].statStages[STAT_SPATK] < DEFAULT_STAT_STAGE)
            score--;
        else if (aiData->hpPercents[battlerAtk] <= 90)
            score--;
        if (gBattleMons[battlerDef].statStages[STAT_SPATK] > 3 && !AI_RandLessThan(50))
            score -= 2;
        else if (aiData->hpPercents[battlerDef] < 70)
            score -= 2;
        break;
    case EFFECT_SPECIAL_DEFENSE_DOWN:
    case EFFECT_SPECIAL_DEFENSE_DOWN_2:
        if (!ShouldLowerSpDef(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if ((aiData->hpPercents[battlerAtk] < 70 && !AI_RandLessThan(50))
          || (gBattleMons[battlerDef].statStages[STAT_SPDEF] <= 3 && !AI_RandLessThan(50)))
            score -= 2;
        if (aiData->hpPercents[battlerDef] <= 70)
            score -= 2;
        break;
    case EFFECT_ACCURACY_DOWN:
    case EFFECT_ACCURACY_DOWN_2:
        if (ShouldLowerAccuracy(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if ((aiData->hpPercents[battlerAtk] < 70 || aiData->hpPercents[battlerDef] < 70) && AI_RandLessThan(100))
            score--;
        if (gBattleMons[battlerDef].statStages[STAT_ACC] <= 4 && !AI_RandLessThan(80))
            score -= 2;
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY && !AI_RandLessThan(70))
            score += 2;
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED && !AI_RandLessThan(70))
            score += 2;
        if (gStatuses3[battlerDef] & STATUS3_ROOTED && AI_RandLessThan(128))
            score++;
        if (gBattleMons[battlerDef].status2 & STATUS2_CURSED && !AI_RandLessThan(70))
            score += 2;
        if (aiData->hpPercents[battlerAtk] > 70 || gBattleMons[battlerDef].statStages[STAT_ACC] < DEFAULT_STAT_STAGE)
            break;
        else if (aiData->hpPercents[battlerAtk] < 40 || aiData->hpPercents[battlerDef] < 40 || !AI_RandLessThan(70))
            score -= 2;
        break;
    case EFFECT_EVASION_DOWN:
    case EFFECT_EVASION_DOWN_2:
        if (!ShouldLowerEvasion(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if ((aiData->hpPercents[battlerAtk] < 70 || gBattleMons[battlerDef].statStages[STAT_EVASION] <= 3) && !AI_RandLessThan(50))
            score -= 2;
        if (aiData->hpPercents[battlerDef] <= 70)
            score -= 2;
        if (gBattleMons[battlerAtk].statStages[STAT_ACC] < DEFAULT_STAT_STAGE)
            score++;
        if (gBattleMons[battlerDef].statStages[STAT_EVASION] < 7 || aiData->abilities[battlerAtk] == ABILITY_NO_GUARD)
            score -= 2;
        break;
    case EFFECT_CHILLY_AIR:
        if (AI_STRIKES_FIRST(battlerAtk, battlerDef, move))
            score -= 3;
        if (!ShouldLowerEvasion(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if ((aiData->hpPercents[battlerAtk] < 70 || gBattleMons[battlerDef].statStages[STAT_EVASION] <= 3) && !AI_RandLessThan(50))
            score -= 2;
        if (aiData->hpPercents[battlerDef] <= 70)
            score -= 2;
        if (gBattleMons[battlerAtk].statStages[STAT_ACC] < DEFAULT_STAT_STAGE)
            score++;
        if (gBattleMons[battlerDef].statStages[STAT_EVASION] < 7 || aiData->abilities[battlerAtk] == ABILITY_NO_GUARD)
            score -= 2;
        break;
    case EFFECT_EERIE_IMPULSE:
        if (!ShouldLowerSpAtk(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if (gBattleMons[battlerDef].statStages[STAT_SPATK] < DEFAULT_STAT_STAGE)
            score--;
        else if (aiData->hpPercents[battlerAtk] <= 90)
            score--;
        if (gBattleMons[battlerDef].statStages[STAT_SPATK] > 3 && !AI_RandLessThan(50))
            score -= 2;
        else if (aiData->hpPercents[battlerDef] < 70)
            score -= 2;
        if (!ShouldLowerSpDef(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if ((aiData->hpPercents[battlerAtk] < 70 && !AI_RandLessThan(50))
          || (gBattleMons[battlerDef].statStages[STAT_SPDEF] <= 3 && !AI_RandLessThan(50)))
            score -= 2;
        break;
    case EFFECT_COTTON_SPORE:
        if (AI_STRIKES_FIRST(battlerAtk, battlerDef, move))
            score -= 3;
        else if (!AI_RandLessThan(70))
            score += 2;
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            IncreaseParalyzeScore(battlerAtk, battlerDef, move, &score);
        }
        break;
    case EFFECT_KINESIS:
        if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
        {
            score += 3;
            if (ShouldLowerAccuracy(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
                score -= 2;
            if ((aiData->hpPercents[battlerAtk] < 70 || aiData->hpPercents[battlerDef] < 70) && AI_RandLessThan(100))
                score--;
            if (gBattleMons[battlerDef].statStages[STAT_ACC] <= 4 && !AI_RandLessThan(80))
                score -= 2;
            if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY && !AI_RandLessThan(70))
                score += 2;
            if (gStatuses3[battlerDef] & STATUS3_LEECHSEED && !AI_RandLessThan(70))
                score += 2;
            if (gStatuses3[battlerDef] & STATUS3_ROOTED && AI_RandLessThan(128))
                score += 2;
            if (gBattleMons[battlerDef].status2 & STATUS2_CURSED && !AI_RandLessThan(70))
                score += 2;
            if (!ShouldLowerAttack(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
                score -= 2;
            if (gBattleMons[battlerDef].statStages[STAT_ATK] < DEFAULT_STAT_STAGE)
                score--;
            else if (aiData->hpPercents[battlerAtk] <= 90)
                score--;
            if (gBattleMons[battlerDef].statStages[STAT_ATK] > 3 && !AI_RandLessThan(50))
                score -= 2;
            else if (aiData->hpPercents[battlerDef] < 70)
                score -= 2;
            if (!ShouldLowerEvasion(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
                score--;
            if ((aiData->hpPercents[battlerAtk] < 70 || gBattleMons[battlerDef].statStages[STAT_EVASION] <= 3) && !AI_RandLessThan(50))
                score--;
            if (gBattleMons[battlerAtk].statStages[STAT_ACC] < DEFAULT_STAT_STAGE)
                score += 2;
            if (gBattleMons[battlerDef].statStages[STAT_EVASION] < 7 || aiData->abilities[battlerAtk] == ABILITY_NO_GUARD)
                score--;
            if (aiData->hpPercents[battlerAtk] > 70 || gBattleMons[battlerDef].statStages[STAT_ACC] < DEFAULT_STAT_STAGE)
                break;
            else if (aiData->hpPercents[battlerAtk] < 40 || aiData->hpPercents[battlerDef] < 40 || !AI_RandLessThan(70))
                score -= 2;
        }
        else
        {
            if (ShouldLowerAccuracy(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
                score -= 2;
            if ((aiData->hpPercents[battlerAtk] < 70 || aiData->hpPercents[battlerDef] < 70) && AI_RandLessThan(100))
                score--;
            if (gBattleMons[battlerDef].statStages[STAT_ACC] <= 4 && !AI_RandLessThan(80))
                score -= 2;
            if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY && !AI_RandLessThan(70))
                score += 2;
            if (gStatuses3[battlerDef] & STATUS3_LEECHSEED && !AI_RandLessThan(70))
                score += 2;
            if (gStatuses3[battlerDef] & STATUS3_ROOTED && AI_RandLessThan(128))
                score++;
            if (gBattleMons[battlerDef].status2 & STATUS2_CURSED && !AI_RandLessThan(70))
                score += 2;
            if (aiData->hpPercents[battlerAtk] > 70 || gBattleMons[battlerDef].statStages[STAT_ACC] < DEFAULT_STAT_STAGE)
                break;
            else if (aiData->hpPercents[battlerAtk] < 40 || aiData->hpPercents[battlerDef] < 40 || !AI_RandLessThan(70))
                score -= 2;
        }
        break;
	case EFFECT_BIDE:
        if (aiData->hpPercents[battlerAtk] < 60)
            score -= 2;
        break;
    case EFFECT_DREAM_EATER:
        if (!(gBattleMons[battlerDef].status1 & STATUS1_SLEEP_ANY))
            break;
        score++;    // if target is asleep, dream eater is a pretty good move even without draining
        // fallthrough
    case EFFECT_ACUPRESSURE:
        break;
    case EFFECT_SABRE_BREAK:
        if ((gBattleMons[battlerDef].status1 & STATUS1_FROSTBITE) || (gBattleMons[battlerDef].status1 & STATUS1_FREEZE))
            score += 3;
        score += ShouldTryToFlinch(battlerAtk, battlerDef, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], move);
        break;
    case EFFECT_ATTACK_ACCURACY_UP: // hone claws
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ACC, &score);
        break;
    case EFFECT_GROWTH:
    case EFFECT_ATTACK_SPATK_UP:    // work up
        if (aiData->hpPercents[battlerAtk] <= 40 || aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
            break;

        if (HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        else if (HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        break;
    case EFFECT_VENOM_DRENCH:
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY)
        {
            score += 2;
        }
        break;
    case EFFECT_HAZE:
        if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE)
            score += 4;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_LIGHTSCREEN)
            score++;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_REFLECT)
            score++;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_AURORA_VEIL)
            score += 2;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_GOOGOO_SCREEN)
            score += 2;
        if (AnyStatIsRaised(BATTLE_PARTNER(battlerAtk))
          || PartnerHasSameMoveEffectWithoutTarget(BATTLE_PARTNER(battlerAtk), move, aiData->partnerMove))
            score -= 3;
            break;
        // fallthrough
    case EFFECT_ROAR:
    case EFFECT_DEARLY_DEPART:
    case EFFECT_CLEAR_SMOG:
    case EFFECT_PSY_SWAP:
        if (isDoubleBattle)
            score += CountBattlerStatIncreases(battlerDef, TRUE) + CountBattlerStatIncreases(BATTLE_PARTNER(battlerDef), TRUE);
        else
            score += CountBattlerStatIncreases(battlerDef, TRUE);
        break;
    case EFFECT_WHIRLWIND:
        if (gSideTimers[GetBattlerSide(battlerAtk)].tailwindTimer != 0)
        {
            score += 2;
            if (isDoubleBattle)
                score += min(CountPositiveStatStages(battlerDef) + CountPositiveStatStages(BATTLE_PARTNER(battlerDef)), 7);
            else
                score += min(CountPositiveStatStages(battlerDef), 4);
        }
        else
        {
            if (isDoubleBattle)
                score += min(CountPositiveStatStages(battlerDef) + CountPositiveStatStages(BATTLE_PARTNER(battlerDef)), 7);
            else
                score += min(CountPositiveStatStages(battlerDef), 4);
        }
        break;
    case EFFECT_REDLINE:
            score += (max(0, (CountNegativeStatStages(battlerAtk) - 2)) * 3);
        break;
    case EFFECT_ZAPPER:
            score += max(0, CountNegativeStatStages(battlerDef));
        break;
    case EFFECT_BLACK_BUFFET:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_BIG_ROOT)
            score++;
        if (effectiveness <= AI_EFFECTIVENESS_x0_5 && AI_RandLessThan(50))
            score -= 3;
        // fallthrough
    case EFFECT_MULTI_HIT:
    case EFFECT_TRIPLE_KICK:
    case EFFECT_GRIPPING_NAIL:
        if (AI_MoveMakesContact(aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk], move)
          && aiData->abilities[battlerAtk] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT)
          && aiData->holdEffects[battlerDef] == HOLD_EFFECT_ROCKY_HELMET)
            score -= 2;
        break;
    case EFFECT_BARB_BARRAGE:
        if (AI_MoveMakesContact(aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk], move)
          && aiData->abilities[battlerAtk] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT)
          && aiData->holdEffects[battlerDef] == HOLD_EFFECT_ROCKY_HELMET)
            score -= 2;
        IncreasePoisonScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_CONVERSION:
        if (!IS_BATTLER_OF_TYPE(battlerAtk, gBattleMoves[gBattleMons[battlerAtk].moves[0]].type))
            score++;
        break;
    case EFFECT_FLINCH_HIT:
    case EFFECT_WATERFALL:
        score += ShouldTryToFlinch(battlerAtk, battlerDef, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], move);
        break;
    case EFFECT_SWALLOW:
        if (gDisableStructs[battlerAtk].stockpileCounter < 1)
        {
            break;
        }
        else
        {
            u32 healPercent = 0;
            switch (gDisableStructs[battlerAtk].stockpileCounter)
            {
            case 1:
                healPercent = 45;
                break;
            case 2:
                healPercent = 55;
                break;
            case 3:
                healPercent = 65;
                break;
            default:
                break;
            }

            if (ShouldRecover(battlerAtk, battlerDef, move, healPercent))
                score += 2;
        }
        break;
    case EFFECT_HEAL_ORDER:
        if (ShouldRecover(battlerAtk, battlerDef, move, 66))
            score += 3;
        break;
    case EFFECT_RESTORE_HP:
    case EFFECT_SOFTBOILED:
    case EFFECT_ROOST:
    case EFFECT_MORNING_SUN:
    case EFFECT_SYNTHESIS:
    case EFFECT_MOONLIGHT:
    case EFFECT_COLD_MEND:
        if (ShouldRecover(battlerAtk, battlerDef, move, 50))
            score += 3;
        break;
    case EFFECT_CRITICAL_REPAIR:
        if (ShouldRecover(battlerAtk, battlerDef, move, 25))
            score += 3;
        break;
    case EFFECT_RESERVOIR:
        if (HasDamagingMoveOfType(battlerAtk, TYPE_WATER))
            score += 2;
    case EFFECT_SHIELDS_UP:
        if (ShouldRecover(battlerAtk, battlerDef, move, 35))
            score += 3;
        if (gBattleMons[battlerAtk].status1 & STATUS1_ANY_NEGATIVE)
            score += 2;
        break;
    case EFFECT_TOXIC:
    case EFFECT_POISON:
    case EFFECT_MORTAL_SPIN:
        IncreasePoisonScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_POISON_POWDER:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            score += 2;
        IncreasePoisonScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_TERRORIZE:
        IncreasePanicScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_DEEP_GAZE:
        if (!(gBattleMons[battlerDef].status1 & STATUS1_ANY))
            score += 2;
        break;
    case EFFECT_MIND_BREAK:
        if ((gBattleMons[battlerDef].status1 & STATUS1_PANIC) || (gBattleMons[battlerDef].status2 & STATUS2_CONFUSION))
            score++;
        break;
    case EFFECT_LIGHT_SCREEN:
    case EFFECT_REFLECT:
    case EFFECT_AURORA_VEIL:
    case EFFECT_BABY_BLUES:
        if (ShouldSetScreen(battlerAtk, battlerDef, moveEffect))
        {
            score += 5;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_LIGHT_CLAY)
                score += 2;
            if (aiData->abilities[battlerAtk] == ABILITY_STAR_SCREEN)
                score += 2;
            if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_SCREENER)
                score += 2;
        }
        break;
    case EFFECT_SILENCE:
        if (!(gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_SILENCE))
        {
            score += 4;
        }
        break;
    case EFFECT_REST:
        if (!(AI_CanSleep(battlerAtk, aiData->abilities[battlerAtk])))
        {
            break;
        }
        else if (ShouldRecover(battlerAtk, battlerDef, move, 100))
        {
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_CURE_SLP
              || aiData->holdEffects[battlerAtk] == HOLD_EFFECT_CURE_STATUS
              || HasMoveEffect(EFFECT_SLEEP_TALK, battlerAtk)
              || HasMoveEffect(EFFECT_SNORE, battlerAtk)
              || aiData->abilities[battlerAtk] == ABILITY_SHED_SKIN
              || aiData->abilities[battlerAtk] == ABILITY_EARLY_BIRD
              || (AI_GetWeather(aiData) & B_WEATHER_RAIN && gWishFutureKnock.weatherDuration != 1 && aiData->abilities[battlerAtk] == ABILITY_HYDRATION && aiData->holdEffects[battlerAtk] != HOLD_EFFECT_UTILITY_UMBRELLA))
            {
                score += 2;
            }
            else
            {
                score++;
            }
        }
        break;
    case EFFECT_OHKO:
        if (gStatuses3[battlerAtk] & STATUS3_ALWAYS_HITS)
            score += 5;
        break;
    case EFFECT_TRAP:
    case EFFECT_WHIRLPOOL:
    case EFFECT_SAND_TOMB:
    case EFFECT_SNAP_TRAP:
    case EFFECT_CONSTRICT:
    case EFFECT_BLOCK:
        if (HasMoveEffect(battlerDef, EFFECT_RAPID_SPIN))
            break;
        if (IsBattlerTrapped(battlerDef, TRUE))
            break; // in this case its a bad attacking move
        else if (ShouldTrap(battlerAtk, battlerDef, move))
            score += 5;
        break;
    case EFFECT_MEAN_LOOK:
        if (ShouldTrap(battlerAtk, battlerDef, move))
            score += 2;
        if (ShouldFakeOut(battlerAtk, battlerDef, move))
            score += 4;
        else
            score -= 10;
        break;
    case EFFECT_VERGLASTROM:
        if (HasMoveEffect(battlerDef, EFFECT_RAPID_SPIN))
            break;
        if (IsBattlerTrapped(battlerDef, TRUE))
            break; // in this case its a bad attacking move
        else if (ShouldTrap(battlerAtk, battlerDef, move))
            score += 5;
        if ((AI_GetWeather(aiData) & (B_WEATHER_HAIL)))
            score += 3;
        break;
    case EFFECT_VINE_WHIP:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            if (HasMoveEffect(battlerDef, EFFECT_RAPID_SPIN))
                break;
            if (IsBattlerTrapped(battlerDef, TRUE))
                break; // in this case its a bad attacking move
            else if (ShouldTrap(battlerAtk, battlerDef, move))
                score += 5;
        }
        break;
    case EFFECT_MIST:
    case EFFECT_MIST_BALL:
        if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_SCREENER)
            score += 2;
        break;
    case EFFECT_FOCUS_ENERGY:
        if (aiData->abilities[battlerAtk] == ABILITY_SUPER_LUCK
          || aiData->abilities[battlerAtk] == ABILITY_SNIPER
          || aiData->abilities[battlerAtk] == ABILITY_RISKTAKER
          || aiData->holdEffects[battlerAtk] == HOLD_EFFECT_SCOPE_LENS
          || HasHighCritRatioMove(battlerAtk))
            score += 2;
        if (aiData->abilities[battlerAtk] == ABILITY_INNER_FOCUS)
            score++;
        break;
    case EFFECT_LASER_FOCUS:
        if (aiData->abilities[battlerAtk] == ABILITY_SUPER_LUCK
          || aiData->abilities[battlerAtk] == ABILITY_SNIPER
          || aiData->abilities[battlerAtk] == ABILITY_RISKTAKER
          || aiData->holdEffects[battlerAtk] == HOLD_EFFECT_SCOPE_LENS
          || HasHighCritRatioMove(battlerAtk))
            score += 2;
        break;
    case EFFECT_DRAGON_CHEER:
        if (aiData->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_SUPER_LUCK
          || aiData->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_SNIPER
          || aiData->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_RISKTAKER
          || aiData->holdEffects[BATTLE_PARTNER(battlerAtk)] == HOLD_EFFECT_SCOPE_LENS
          || HasHighCritRatioMove(BATTLE_PARTNER(battlerAtk)))
            score += 2;
        break;
    case EFFECT_CONFUSE_HIT:
    case EFFECT_SIGNAL_BEAM:
    case EFFECT_ROCK_CLIMB:
    case EFFECT_SONIC_BURST:
        if (sereneGraceBoost)
            score++;
        //fallthrough
    case EFFECT_CONFUSE:
    case EFFECT_FLASH:
        IncreaseConfusionScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_PARALYZE:
        IncreaseParalyzeScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_STUN_SPORE:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            score++;
        else
            IncreaseParalyzeScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_LOW_KICK:
    case EFFECT_HEAT_CRASH:
        if (gFieldStatuses & STATUS_FIELD_GRAVITY)
            score += 2;
        break;
    case EFFECT_GRAV_APPLE:
        if (gFieldStatuses & STATUS_FIELD_GRAVITY)
            score += 2;
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            score += ShouldTryToFlinch(battlerAtk, battlerDef, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], move);
        // fall through
    case EFFECT_ATTACK_DOWN_HIT:
    case EFFECT_DEFENSE_DOWN_HIT:
    case EFFECT_SPECIAL_ATTACK_DOWN_HIT:
    case EFFECT_SPECIAL_DEFENSE_DOWN_HIT:
    case EFFECT_ACCURACY_DOWN_HIT:
    case EFFECT_EVASION_DOWN_HIT:
    case EFFECT_MUDDY_WATER:
    case EFFECT_CUT:
    case EFFECT_ROCK_SMASH:
    case EFFECT_ACCURACY_DEFENSE_DOWN_HIT:
    case EFFECT_OCTAZOOKA:
        if (sereneGraceBoost && aiData->abilities[battlerDef] != ABILITY_CONTRARY)
            score += 2;
        break;
    case EFFECT_ALL_STATS_DOWN_HIT:
        if (sereneGraceBoost && aiData->abilities[battlerDef] != ABILITY_CONTRARY)
            score += 2;
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY)
            score += 5;
        break;
    case EFFECT_SPEED_DOWN_HIT:
        if (AI_STRIKES_FIRST(battlerAtk, battlerDef, move))
            score -= 2;
        else if (!AI_RandLessThan(70))
            score++;
        if (ShouldLowerSpeed(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
        {
            if (sereneGraceBoost && aiData->abilities[battlerDef] != ABILITY_CONTRARY)
                score += 5;
            else
                score += 2;
        }
        break;
    case EFFECT_SUBSTITUTE:
        if (gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
            score += 3;
        if (gBattleMons[battlerDef].status1 & (STATUS1_BURN | STATUS1_PSN_ANY | STATUS1_FROSTBITE))
            score++;
        if (HasMoveEffect(battlerDef, EFFECT_SLEEP)
          || HasMoveEffect(battlerDef, EFFECT_DARK_VOID)
          || HasMoveEffect(battlerDef, EFFECT_TOXIC)
          || HasMoveEffect(battlerDef, EFFECT_POISON)
          || HasMoveEffect(battlerDef, EFFECT_PARALYZE)
          || HasMoveEffect(battlerDef, EFFECT_WILL_O_WISP)
          || HasMoveEffect(battlerDef, EFFECT_GLACIATE)
          || HasMoveEffect(battlerDef, EFFECT_CONFUSE)
          || HasMoveEffect(battlerDef, EFFECT_TEETER_DANCE)
          || HasMoveEffect(battlerDef, EFFECT_FLASH)
          || HasMoveEffect(battlerDef, EFFECT_LEECH_SEED)
          || HasMoveEffect(battlerDef, EFFECT_SCORP_FANG)
          || HasMoveEffect(battlerDef, EFFECT_TERRORIZE)
          || HasMoveEffect(battlerDef, EFFECT_SLEEP_POWDER)
          || HasMoveEffect(battlerDef, EFFECT_STUN_SPORE)
          || HasMoveEffect(battlerDef, EFFECT_FROST_NOVA)
          || HasMoveEffect(battlerDef, EFFECT_POISON_POWDER))
            score += 2;
        if (!gBattleMons[battlerDef].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION && aiData->hpPercents[battlerAtk] > 70))
            score++;
        break;
    case EFFECT_SHED_TAIL:
        if (gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
            score += 3;
        if (gBattleMons[battlerDef].status1 & (STATUS1_BURN | STATUS1_PSN_ANY | STATUS1_FROSTBITE))
            score++;
        if (HasMoveEffect(battlerDef, EFFECT_SLEEP)
          || HasMoveEffect(battlerDef, EFFECT_DARK_VOID)
          || HasMoveEffect(battlerDef, EFFECT_TOXIC)
          || HasMoveEffect(battlerDef, EFFECT_POISON)
          || HasMoveEffect(battlerDef, EFFECT_PARALYZE)
          || HasMoveEffect(battlerDef, EFFECT_WILL_O_WISP)
          || HasMoveEffect(battlerDef, EFFECT_GLACIATE)
          || HasMoveEffect(battlerDef, EFFECT_CONFUSE)
          || HasMoveEffect(battlerDef, EFFECT_TEETER_DANCE)
          || HasMoveEffect(battlerDef, EFFECT_FLASH)
          || HasMoveEffect(battlerDef, EFFECT_LEECH_SEED)
          || HasMoveEffect(battlerDef, EFFECT_SCORP_FANG)
          || HasMoveEffect(battlerDef, EFFECT_TERRORIZE)
          || HasMoveEffect(battlerDef, EFFECT_SLEEP_POWDER)
          || HasMoveEffect(battlerDef, EFFECT_STUN_SPORE)
          || HasMoveEffect(battlerDef, EFFECT_FROST_NOVA)
          || HasMoveEffect(battlerDef, EFFECT_POISON_POWDER))
            score += 2;
        if (!gBattleMons[battlerDef].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION && aiData->hpPercents[battlerAtk] > 70))
            score++;
        if (!IsDoubleBattle())
        {
            switch (ShouldPivot(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, AI_THINKING_STRUCT->movesetIndex))
            {
            case 0: // no
                score -= 10;    // technically should go in CheckBadMove, but this is easier/less computationally demanding
                break;
            case 1: // maybe
                break;
            case 2: // yes
                score += 7;
                break;
            }
        }
        else //Double Battle
        {
            if (CountUsablePartyMons(battlerAtk) == 0)
                break; // Can't switch

            //if (switchAbility == ABILITY_INTIMIDATE && PartyHasMoveSplit(battlerDef, SPLIT_PHYSICAL))
                //score += 7;
        }
        break;
    case EFFECT_MIMIC:
        if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER)
        {
            if (gLastMoves[battlerDef] != MOVE_NONE && gLastMoves[battlerDef] != 0xFFFF)
                return AI_CheckViability(battlerAtk, battlerDef, gLastMoves[battlerDef], score);
        }
        break;
    case EFFECT_LEECH_SEED:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            if (HasMoveEffect(battlerDef, EFFECT_RAPID_SPIN))
                score--;
            if (ShouldTrap(battlerAtk, battlerDef, move))
                score += 5;
        }
        if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS)
          || gStatuses3[battlerDef] & STATUS3_LEECHSEED
          || HasMoveEffect(battlerDef, EFFECT_RAPID_SPIN)
          || aiData->abilities[battlerDef] == ABILITY_LIQUID_OOZE
          || aiData->abilities[battlerDef] == (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT))
            break;
        score += 3;
        if (!HasDamagingMove(battlerDef) || IsBattlerTrapped(battlerDef, FALSE))
            score += 2;
        break;
    case EFFECT_SEED_BOMB:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS)
              || gStatuses3[battlerDef] & STATUS3_LEECHSEED
              || HasMoveEffect(battlerDef, EFFECT_RAPID_SPIN)
              || aiData->abilities[battlerDef] == ABILITY_LIQUID_OOZE
              || aiData->abilities[battlerDef] == (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT))
                break;
            score += 3;
            if (!HasDamagingMove(battlerDef) || IsBattlerTrapped(battlerDef, FALSE))
                score += 2;
        }
        break;
    case EFFECT_DO_NOTHING:
        //todo - check z splash, z celebrate, z happy hour (lol)
        break;
    case EFFECT_TELEPORT:
        if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER) || GetBattlerSide(battlerAtk) != B_SIDE_PLAYER)
            break;
        //fallthrough
    case EFFECT_HIT_ESCAPE:
    case EFFECT_U_TURN:
    case EFFECT_FLIP_TURN:
    case EFFECT_PARTING_SHOT:
    case EFFECT_PARTING_CURRY:
        if (!IsDoubleBattle())
        {
            switch (ShouldPivot(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, AI_THINKING_STRUCT->movesetIndex))
            {
            case 0: // no
                score -= 10;    // technically should go in CheckBadMove, but this is easier/less computationally demanding
                break;
            case 1: // maybe
                break;
            case 2: // yes
                score += 7;
                break;
            }
        }
        else //Double Battle
        {
            if (CountUsablePartyMons(battlerAtk) == 0)
                break; // Can't switch

            //if (switchAbility == ABILITY_INTIMIDATE && PartyHasMoveSplit(battlerDef, SPLIT_PHYSICAL))
                //score += 7;
        }
        break;
    case EFFECT_SNOWFADE:
    case EFFECT_GLACIAL_SHIFT:
        if (AI_GetWeather(aiData) & (B_WEATHER_HAIL))
            score += 1;
        if (!IsDoubleBattle())
        {
            switch (ShouldPivot(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, AI_THINKING_STRUCT->movesetIndex))
            {
            case 0: // no
                score -= 10;    // technically should go in CheckBadMove, but this is easier/less computationally demanding
                break;
            case 1: // maybe
                break;
            case 2: // yes
                score += 7;
                break;
            }
        }
        else //Double Battle
        {
            if (CountUsablePartyMons(battlerAtk) == 0)
                break; // Can't switch

            //if (switchAbility == ABILITY_INTIMIDATE && PartyHasMoveSplit(battlerDef, SPLIT_PHYSICAL))
                //score += 7;
        }
        break;
    case EFFECT_SERPENT_SURGE:
        if (aiData->abilities[battlerAtk] == ABILITY_DRIZZLE)
        {
            if ((AI_GetWeather(aiData) & B_WEATHER_RAIN))
                score += 5;
            break;
        }
        if (aiData->abilities[battlerAtk] == ABILITY_HYDRATION)
        {
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_BIG_ROOT)
                score++;
            if (effectiveness <= AI_EFFECTIVENESS_x0_5 && AI_RandLessThan(50))
                score -= 3;
            break;
        }
        if (aiData->abilities[battlerAtk] == ABILITY_REGENERATOR)
        {
            if (!IsDoubleBattle())
            {
                switch (ShouldPivot(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, AI_THINKING_STRUCT->movesetIndex))
                {
                case 0: // no
                    score -= 10;    // technically should go in CheckBadMove, but this is easier/less computationally demanding
                    break;
                case 1: // maybe
                    break;
                case 2: // yes
                    score += 7;
                    break;
                }
            }
            else //Double Battle
            {
                if (CountUsablePartyMons(battlerAtk) == 0)
                    break; // Can't switch

                //if (switchAbility == ABILITY_INTIMIDATE && PartyHasMoveSplit(battlerDef, SPLIT_PHYSICAL))
                    //score += 7;
            }
        }
        break; 
    case EFFECT_CHILLY_RECEPTION:
        if (ShouldSetHail(battlerAtk, aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk]))
        {
            if ((HasMoveEffect(battlerAtk, EFFECT_AURORA_VEIL) || HasMoveEffect(BATTLE_PARTNER(battlerAtk), EFFECT_AURORA_VEIL))
              && ShouldSetScreen(battlerAtk, battlerDef, EFFECT_AURORA_VEIL))
                score += 3;
            if ((HasMoveEffect(battlerAtk, EFFECT_COLD_MEND) || HasMoveEffect(BATTLE_PARTNER(battlerAtk), EFFECT_COLD_MEND)))
                score += 2;

            score++;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_ICY_ROCK)
                score++;
            if (HasMoveEffect(battlerDef, EFFECT_MORNING_SUN)
              || HasMoveEffect(battlerDef, EFFECT_SYNTHESIS)
              || HasMoveEffect(battlerDef, EFFECT_MOONLIGHT))
                score += 2;
        }
        if (!IsDoubleBattle())
        {
            switch (ShouldPivot(battlerAtk, battlerDef, aiData->abilities[battlerDef], move, AI_THINKING_STRUCT->movesetIndex))
            {
            case 0: // no
                score -= 10;    // technically should go in CheckBadMove, but this is easier/less computationally demanding
                break;
            case 1: // maybe
                break;
            case 2: // yes
                score += 7;
                break;
            }
        }
        else //Double Battle
        {
            if (CountUsablePartyMons(battlerAtk) == 0)
                break; // Can't switch
        }
        break;
    case EFFECT_BATON_PASS:
        if (ShouldSwitch(battlerAtk) && (gBattleMons[battlerAtk].status2 & STATUS2_SUBSTITUTE
          || (gStatuses3[battlerAtk] & (STATUS3_ROOTED | STATUS3_AQUA_RING | STATUS3_MAGNET_RISE | STATUS3_POWER_TRICK))
          || AnyStatIsRaised(battlerAtk)))
            score += 5;
        break;
    case EFFECT_DISABLE:
    case EFFECT_MIND_GAP:
        if (gDisableStructs[battlerDef].disableTimer == 0
        #if B_MENTAL_HERB >= GEN_5
            && aiData->holdEffects[battlerDef] != HOLD_EFFECT_MENTAL_HERB    // mental herb
        #endif
        )
        {
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // AI goes first
            {
                if (gLastMoves[battlerDef] != MOVE_NONE
                  && gLastMoves[battlerDef] != 0xFFFF)
                {
                    if (gLastMoves[battlerDef] == predictedMove)
                        score += 3;
                    else if (CanTargetMoveFaintAi(gLastMoves[battlerDef], battlerDef, battlerAtk, 1))
                        score += 2; //Disable move that can kill attacker
                }
            }
            else if (predictedMove != MOVE_NONE && IS_MOVE_STATUS(predictedMove))
            {
                score++; // Disable annoying status moves
            }
        }
        break;
    case EFFECT_VOID:
        if (gDisableStructs[battlerDef].disableTimer == 0
        #if B_MENTAL_HERB >= GEN_5
            && aiData->holdEffects[battlerDef] != HOLD_EFFECT_MENTAL_HERB    // mental herb
        #endif
        )
        {
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // AI goes first
            {
                if (gLastMoves[battlerDef] != MOVE_NONE
                  && gLastMoves[battlerDef] != 0xFFFF)
                {
                    if (gLastMoves[battlerDef] == predictedMove)
                        score += 3;
                    else if (CanTargetMoveFaintAi(gLastMoves[battlerDef], battlerDef, battlerAtk, 1))
                        score += 2; //Disable move that can kill attacker
                }
            }
            else if (predictedMove != MOVE_NONE && IS_MOVE_STATUS(predictedMove))
            {
                score++; // Disable annoying status moves
            }
        }
        if (gBattleMoves[predictedMove].effect == EFFECT_PROTECT)
            score += 3;
        break;
    case EFFECT_ENCORE:
        if (gDisableStructs[battlerDef].encoreTimer == 0
        #if B_MENTAL_HERB >= GEN_5
            && aiData->holdEffects[battlerDef] != HOLD_EFFECT_MENTAL_HERB    // mental herb
        #endif
        )
        {
            if (IsEncoreEncouragedEffect(gBattleMoves[gLastMoves[battlerDef]].effect))
                score += 3;
        }
        break;
    case EFFECT_PAIN_SPLIT:
        {
            u32 newHp = (gBattleMons[battlerAtk].hp + gBattleMons[battlerDef].hp) / 2;
            u32 healthBenchmark = (gBattleMons[battlerAtk].hp * 12) / 10;
            if (newHp > healthBenchmark && ShouldAbsorb(battlerAtk, battlerDef, move, aiData->simulatedDmg[battlerAtk][battlerDef][AI_THINKING_STRUCT->movesetIndex]))
                score += 2;
        }
        break;
    case EFFECT_SLEEP_TALK:
    case EFFECT_SNORE:
        if (!IsWakeupTurn(battlerAtk) && gBattleMons[battlerAtk].status1 & STATUS1_SLEEP_ANY)
            score += 10;
        if (!IsWakeupTurn(battlerAtk) && gBattleMons[battlerAtk].status1 & STATUS1_REST_TURN(1))
            score += 10;
        else if (!IsWakeupTurn(battlerAtk) && gBattleMons[battlerAtk].status1 & STATUS1_REST_TURN(2))
            score += 10;
        else if (!IsWakeupTurn(battlerAtk) && gBattleMons[battlerAtk].status1 & STATUS1_REST_TURN(3))
            score += 10;
        break;
    case EFFECT_LOCK_ON:
    case EFFECT_MIND_READER:
    case EFFECT_ODOR_SLEUTH:
        if (HasMoveEffect(battlerAtk, EFFECT_OHKO))
            score += 3;
        else if (aiData->abilities[battlerAtk] == ABILITY_COMPOUND_EYES && HasMoveWithLowAccuracy(battlerAtk, battlerDef, 80, TRUE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef]))
            score += 3;
        else if (HasMoveWithLowAccuracy(battlerAtk, battlerDef, 85, TRUE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef]))
            score += 3;
        else if (HasMoveWithLowAccuracy(battlerAtk, battlerDef, 90, TRUE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef]))
            score++;
        break;
    case EFFECT_SPEED_UP_HIT:
        if (sereneGraceBoost && aiData->abilities[battlerDef] != ABILITY_CONTRARY && !AI_STRIKES_FIRST(battlerAtk, battlerDef, move))
            score += 3;
        break;
    case EFFECT_DESTINY_BOND:
        if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER && CanTargetFaintAi(battlerDef, battlerAtk))
            score += 3;
        break;
    case EFFECT_SPITE:
        //TODO - predicted move
        break;
    case EFFECT_WISH:
    case EFFECT_HEAL_BELL:
    case EFFECT_AROMATHERAPY:
        if (ShouldUseWishAromatherapy(battlerAtk, battlerDef, move))
            score += 3;
        break;
    case EFFECT_THIEF:
        {
            bool32 canSteal = FALSE;

            #if B_TRAINERS_KNOCK_OFF_ITEMS == TRUE
                canSteal = TRUE;
            #endif
            if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER || GetBattlerSide(battlerAtk) == B_SIDE_PLAYER)
                canSteal = TRUE;

            if (canSteal && aiData->items[battlerAtk] == ITEM_NONE
              && aiData->items[battlerDef] != ITEM_NONE
              && CanBattlerGetOrLoseItem(battlerDef, aiData->items[battlerDef])
              && CanBattlerGetOrLoseItem(battlerAtk, aiData->items[battlerDef])
              && !HasMoveEffect(battlerAtk, EFFECT_ACROBATICS)
              && !HasMoveEffect(battlerAtk, EFFECT_SAVAGE_WING)
              && aiData->abilities[battlerDef] != ABILITY_STICKY_HOLD
              && !IS_BATTLER_OF_TYPE(battlerDef, TYPE_FAIRY))
            {
                switch (aiData->holdEffects[battlerDef])
                {
                case HOLD_EFFECT_NONE:
                    break;
                case HOLD_EFFECT_CHOICE_BAND:
                case HOLD_EFFECT_CHOICE_SCARF:
                case HOLD_EFFECT_CHOICE_SPECS:
                    score += 2;
                    break;
                case HOLD_EFFECT_TOXIC_ORB:
                    if (ShouldPoisonSelf(battlerAtk, aiData->abilities[battlerAtk]))
                        score += 2;
                    break;
                case HOLD_EFFECT_FLAME_ORB:
                    if (ShouldBurnSelf(battlerAtk, aiData->abilities[battlerAtk]))
                        score += 2;
                    break;
                case HOLD_EFFECT_BLACK_SLUDGE:
                    if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_POISON))
                        score += 2;
                    break;
                case HOLD_EFFECT_IRON_BALL:
                    if (HasMoveEffect(battlerAtk, EFFECT_FLING))
                        score += 2;
                    break;
                case HOLD_EFFECT_LAGGING_TAIL:
                case HOLD_EFFECT_STICKY_BARB:
                    break;
                default:
                    score++;
                    break;
                }
            }
            break;
        }
        break;
    case EFFECT_PLUNDER:
        {
            bool32 canSteal = FALSE;

            // Want to copy positive stat changes
            for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
            {
                if (gBattleMons[battlerDef].statStages[i] > gBattleMons[battlerAtk].statStages[i])
                {
                    switch (i)
                    {
                    case STAT_ATK:
                        if (HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                            score++;
                    case STAT_SPATK:
                        if (HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                            score++;
                    case STAT_ACC:
                    case STAT_EVASION:
                    case STAT_SPEED:
                        score++;
                    case STAT_DEF:
                    case STAT_SPDEF:
                        if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_STALL)
                            score++;
                    }
                }
            }

            #if B_TRAINERS_KNOCK_OFF_ITEMS == TRUE
                canSteal = TRUE;
            #endif
            if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER || GetBattlerSide(battlerAtk) == B_SIDE_PLAYER)
                canSteal = TRUE;

            if (canSteal && aiData->items[battlerAtk] == ITEM_NONE
              && aiData->items[battlerDef] != ITEM_NONE
              && CanBattlerGetOrLoseItem(battlerDef, aiData->items[battlerDef])
              && CanBattlerGetOrLoseItem(battlerAtk, aiData->items[battlerDef])
              && !HasMoveEffect(battlerAtk, EFFECT_ACROBATICS)
              && !HasMoveEffect(battlerAtk, EFFECT_SAVAGE_WING)
              && aiData->abilities[battlerDef] != ABILITY_STICKY_HOLD
              && !IS_BATTLER_OF_TYPE(battlerDef, TYPE_FAIRY))
            {
                switch (aiData->holdEffects[battlerDef])
                {
                case HOLD_EFFECT_NONE:
                    break;
                case HOLD_EFFECT_CHOICE_BAND:
                case HOLD_EFFECT_CHOICE_SCARF:
                case HOLD_EFFECT_CHOICE_SPECS:
                    score += 2;
                    break;
                case HOLD_EFFECT_TOXIC_ORB:
                    if (ShouldPoisonSelf(battlerAtk, aiData->abilities[battlerAtk]))
                        score += 2;
                    break;
                case HOLD_EFFECT_FLAME_ORB:
                    if (ShouldBurnSelf(battlerAtk, aiData->abilities[battlerAtk]))
                        score += 2;
                    break;
                case HOLD_EFFECT_BLACK_SLUDGE:
                    if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_POISON))
                        score += 2;
                    break;
                case HOLD_EFFECT_IRON_BALL:
                    if (HasMoveEffect(battlerAtk, EFFECT_FLING))
                        score += 2;
                    break;
                case HOLD_EFFECT_LAGGING_TAIL:
                case HOLD_EFFECT_STICKY_BARB:
                    break;
                default:
                    score++;
                    break;
                }
            }
            break;
        }
        break;
    case EFFECT_NIGHTMARE:
        if (!AI_IsBattlerAsleepOrComatose(battlerDef))
        {
            score++;
            if (AI_RandLessThan(128))
                IncreaseSleepScore(battlerAtk, battlerDef, move, &score);
        }
        else if (AI_IsBattlerAsleepOrComatose(battlerDef))
        {
            if (aiData->abilities[battlerDef] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT)
              && !(gBattleMons[battlerDef].status2 & STATUS2_NIGHTMARE))
            {
                score += 5;
                if (IsBattlerTrapped(battlerDef, TRUE))
                    score += 3;
            }
        }
        break;
    case EFFECT_CURSE:
        if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_GHOST))
        {
            if (IsBattlerTrapped(battlerDef, TRUE))
                score += 3;
            else
                score++;
            break;
        }
        else
        {
            if (aiData->abilities[battlerAtk] == ABILITY_CONTRARY || aiData->abilities[battlerDef] == (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT))
                break;
            else if (gBattleMons[battlerAtk].statStages[STAT_ATK] < 8)
                score += (8 - gBattleMons[battlerAtk].statStages[STAT_ATK]);
            else if (gBattleMons[battlerAtk].statStages[STAT_SPEED] < 3)
                break;
            else if (gBattleMons[battlerAtk].statStages[STAT_DEF] < 8)
                score += (8 - gBattleMons[battlerAtk].statStages[STAT_DEF]);
        }
        break;
    case EFFECT_PROTECT:
        if (predictedMove == 0xFFFF)
            predictedMove = MOVE_NONE;
        if (aiData->abilities[battlerAtk] == ABILITY_STARS_GRACE)
            score++;
        switch (move)
        {
        case MOVE_QUICK_GUARD:
            if (predictedMove != MOVE_NONE && gBattleMoves[predictedMove].priority > 0)
                ProtectChecks(battlerAtk, battlerDef, move, predictedMove, &score);
            break;
        case MOVE_WIDE_GUARD:
            if (predictedMove != MOVE_NONE && AI_GetBattlerMoveTargetType(battlerDef, predictedMove) & (MOVE_TARGET_FOES_AND_ALLY | MOVE_TARGET_BOTH))
            {
                ProtectChecks(battlerAtk, battlerDef, move, predictedMove, &score);
            }
            else if (isDoubleBattle && AI_GetBattlerMoveTargetType(BATTLE_PARTNER(battlerAtk), aiData->partnerMove) & MOVE_TARGET_FOES_AND_ALLY)
            {
                if (aiData->abilities[battlerAtk] != ABILITY_TELEPATHY)
                  ProtectChecks(battlerAtk, battlerDef, move, predictedMove, &score);
            }
            break;
        case MOVE_CRAFTY_SHIELD:
            if (predictedMove != MOVE_NONE && IS_MOVE_STATUS(predictedMove) && !(AI_GetBattlerMoveTargetType(battlerDef, predictedMove) & MOVE_TARGET_USER))
                ProtectChecks(battlerAtk, battlerDef, move, predictedMove, &score);
            break;

        case MOVE_MAT_BLOCK:
            if (gDisableStructs[battlerAtk].isFirstTurn && predictedMove != MOVE_NONE
              && !IS_MOVE_STATUS(predictedMove) && !(AI_GetBattlerMoveTargetType(battlerDef, predictedMove) & MOVE_TARGET_USER))
                ProtectChecks(battlerAtk, battlerDef, move, predictedMove, &score);
            break;
        case MOVE_KINGS_SHIELD:
            if (aiData->abilities[battlerAtk] == ABILITY_STANCE_CHANGE //Special logic for Aegislash
              && gBattleMons[battlerAtk].species == SPECIES_AEGISLASH_BLADE
              && !IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef]))
            {
                score += 3;
                break;
            }
            //fallthrough
        default: // protect
            ProtectChecks(battlerAtk, battlerDef, move, predictedMove, &score);
            break;
        }
        break;
    case EFFECT_ENDURE:
        if (CanTargetFaintAi(battlerDef, battlerAtk))
        {
            if (gBattleMons[battlerAtk].hp > gBattleMons[battlerAtk].maxHP / 4 // Pinch berry couldn't have activated yet
              && IsPinchBerryItemEffect(aiData->holdEffects[battlerAtk]))
            {
                score += 3;
            }
            else if (gBattleMons[battlerAtk].hp > 1) // Only spam endure for Flail/Reversal if you're not at Min Health
            {
                if (HasMoveEffect(battlerAtk, EFFECT_FLAIL) || HasMoveEffect(battlerAtk, EFFECT_ENDEAVOR))
                    score += 3;
            }
        }
        break;

    case EFFECT_SPIKES:
    case EFFECT_HIT_SET_ENTRY_HAZARD:
    case EFFECT_STEALTH_ROCK:
    case EFFECT_STICKY_WEB:
    case EFFECT_TOXIC_SPIKES:
    case EFFECT_RECOIL_50_HAZARD:
        if (aiData->abilities[battlerDef] == ABILITY_MAGIC_BOUNCE || CountUsablePartyMons(battlerDef) == 0)
            break;
        if (gDisableStructs[battlerAtk].isFirstTurn)
            score += 2;
        //TODO - track entire opponent party data to determine hazard effectiveness
        break;
    case EFFECT_NEEDLE_ARM:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            if (aiData->abilities[battlerDef] == ABILITY_MAGIC_BOUNCE || CountUsablePartyMons(battlerDef) == 0)
                break;
            if (gDisableStructs[battlerAtk].isFirstTurn)
                score += 2;
        }
        break;
    case EFFECT_TROP_KICK:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            score += 2;
        }
        if (gBattleMons[battlerDef].status2 & (STATUS2_INFATUATION))
        {
            score += 2;
        }
        break;
    case EFFECT_GRASS_CANNON:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            score += 2;
        if (PartnerMoveEffectIsTerrain(BATTLE_PARTNER(battlerAtk), aiData->partnerMove) || gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
            score += 2;
        break;
    case EFFECT_SPINDA_SWING:
        if (gBattleMons[battlerAtk].status2 & STATUS2_CONFUSION)
        {
            score += 2;
        }
        else if (!(gBattleMons[battlerAtk].status2 & STATUS2_CONFUSION))
        {
            score++;
        }
        break;
    case EFFECT_GUNK_FUNK:
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY)
            score += 4;
        break;
    case EFFECT_CUTIE_CRY:
        if (gBattleMons[battlerDef].status2 & (STATUS2_INFATUATION))
            score += 2;
        break;
    case EFFECT_FORESIGHT:
        if (aiData->abilities[battlerAtk] == ABILITY_SCRAPPY)
            break;
        else if (gBattleMons[battlerDef].statStages[STAT_EVASION] > DEFAULT_STAT_STAGE
         || (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GHOST)
         && (HasMoveWithType(battlerAtk, TYPE_NORMAL)
         || HasMoveWithType(battlerAtk, TYPE_FIGHTING))))
            score += 2;
        break;
    case EFFECT_MIRACLE_EYE:
        if (CountPositiveStatStages(battlerDef) == 1)
                score++;
        else if (CountPositiveStatStages(battlerDef) == 2)
                score += 2;
        else if (CountPositiveStatStages(battlerDef) == 3)
                score += 3;
        else if (CountPositiveStatStages(battlerDef) >= 4)
                score += 4;
        break;
    case EFFECT_PERISH_SONG:
        if (IsBattlerTrapped(battlerDef, TRUE))
            score += 3;
        break;
    case EFFECT_SANDSTORM:
        if (ShouldSetSandstorm(battlerAtk, aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerAtk]))
        {
            score++;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_SMOOTH_ROCK)
                score++;
            if (HasMoveEffect(battlerDef, EFFECT_MORNING_SUN)
              || HasMoveEffect(battlerDef, EFFECT_SYNTHESIS)
              || HasMoveEffect(battlerDef, EFFECT_MOONLIGHT)
              || HasMoveEffect(battlerDef, EFFECT_COLD_MEND)
              || HasMoveEffect(battlerAtk, EFFECT_SAND_TOMB))
                score += 2;
        }
        break;
    case EFFECT_HAIL:
        if (ShouldSetHail(battlerAtk, aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk]))
        {
            if ((HasMoveEffect(battlerAtk, EFFECT_AURORA_VEIL) || HasMoveEffect(BATTLE_PARTNER(battlerAtk), EFFECT_AURORA_VEIL))
              && ShouldSetScreen(battlerAtk, battlerDef, EFFECT_AURORA_VEIL))
                score += 3;
            if ((HasMoveEffect(battlerAtk, EFFECT_COLD_MEND) || HasMoveEffect(BATTLE_PARTNER(battlerAtk), EFFECT_COLD_MEND)))
                score += 2;

            score++;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_ICY_ROCK)
                score++;
            if (HasMoveEffect(battlerDef, EFFECT_MORNING_SUN)
              || HasMoveEffect(battlerDef, EFFECT_SYNTHESIS)
              || HasMoveEffect(battlerDef, EFFECT_MOONLIGHT))
                score += 2;
        }
        break;
    case EFFECT_SNOWSCAPE:
        if (ShouldSetSnow(battlerAtk, aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk]))
        {
            if ((HasMoveEffect(battlerAtk, EFFECT_AURORA_VEIL) || HasMoveEffect(BATTLE_PARTNER(battlerAtk), EFFECT_AURORA_VEIL))
              && ShouldSetScreen(battlerAtk, battlerDef, EFFECT_AURORA_VEIL))
                score += 3;
            if ((HasMoveEffect(battlerAtk, EFFECT_COLD_MEND) || HasMoveEffect(BATTLE_PARTNER(battlerAtk), EFFECT_COLD_MEND)))
                score += 2;

            score++;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_ICY_ROCK)
                score++;
            if (HasMoveEffect(battlerDef, EFFECT_MORNING_SUN)
              || HasMoveEffect(battlerDef, EFFECT_SYNTHESIS)
              || HasMoveEffect(battlerDef, EFFECT_MOONLIGHT))
                score += 2;
        }
        break;
    case EFFECT_RAIN_DANCE:
        if (ShouldSetRain(battlerAtk, aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk]))
        {
            score++;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_DAMP_ROCK)
                score++;
            if (HasMoveEffect(battlerDef, EFFECT_MORNING_SUN)
              || HasMoveEffect(battlerDef, EFFECT_SYNTHESIS)
              || HasMoveEffect(battlerDef, EFFECT_MOONLIGHT)
              || HasMoveEffect(battlerDef, EFFECT_COLD_MEND))
                score += 2;
            if (HasMoveWithType(battlerDef, TYPE_FIRE) || HasMoveWithType(BATTLE_PARTNER(battlerDef), TYPE_FIRE))
                score++;
        }
        break;
    case EFFECT_SUNNY_DAY:
        if (ShouldSetSun(battlerAtk, aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk]))
        {
            score++;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_HEAT_ROCK)
                score++;
            if (HasMoveWithType(battlerDef, TYPE_WATER) || HasMoveWithType(BATTLE_PARTNER(battlerDef), TYPE_WATER))
                score++;
            if (HasMoveEffect(battlerDef, EFFECT_THUNDER) || HasMoveEffect(BATTLE_PARTNER(battlerDef), EFFECT_THUNDER))
                score++;
        }
        break;
    case EFFECT_WARM_WELCOME:
        if (ShouldSetSun(battlerAtk, aiData->abilities[battlerAtk], aiData->holdEffects[battlerAtk]))
        {
            score++;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_HEAT_ROCK)
                score++;
            if (HasMoveWithType(battlerDef, TYPE_WATER) || HasMoveWithType(BATTLE_PARTNER(battlerDef), TYPE_WATER))
                score++;
            if (HasMoveEffect(battlerDef, EFFECT_THUNDER) || HasMoveEffect(BATTLE_PARTNER(battlerDef), EFFECT_THUNDER))
                score++;
        }
        if (ItemId_GetPocket(aiData->items[battlerAtk]) == POCKET_BERRIES)
            score += 3;
        break;
    case EFFECT_SEIZE_CHANCE:
        if (predictedMove != MOVE_NONE)
        {
            if (IS_MOVE_STATUS(predictedMove)) // Opponent going first
                score += 7;
        }
        break;
    case EFFECT_ATTACK_UP_HIT:
        if (sereneGraceBoost)
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        break;
    case EFFECT_SPECIAL_ATTACK_UP_HIT:
        if (sereneGraceBoost)
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        break;
    case EFFECT_FELL_STINGER:
        if (gBattleMons[battlerAtk].statStages[STAT_ATK] < MAX_STAT_STAGE
          && aiData->abilities[battlerAtk] != ABILITY_CONTRARY
          && CanIndexMoveFaintTarget(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex, 0))
        {
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // Attacker goes first
                score += 9;
            else
                score += 3;
        }
        break;
    case EFFECT_BELLY_DRUM:
        if (!CanTargetFaintAi(battlerDef, battlerAtk) && HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL) && aiData->abilities[battlerAtk] != ABILITY_CONTRARY)
            score += (MAX_STAT_STAGE - gBattleMons[battlerAtk].statStages[STAT_ATK]);
        break;
    case EFFECT_IGNITION:
        if (!CanTargetFaintAi(battlerDef, battlerAtk) && HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL) && aiData->abilities[battlerAtk] != ABILITY_CONTRARY)
            score += (MAX_STAT_STAGE - gBattleMons[battlerAtk].statStages[STAT_SPATK]);
        break;
    case EFFECT_STALAG_BLAST:
        if (!CanTargetFaintAi(battlerDef, battlerAtk))
            score += 2;
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER)
                score++;
        break;
    case EFFECT_PSYCH_UP:
    case EFFECT_SPECTRAL_THIEF:
    case EFFECT_HEART_STEAL:
        // Want to copy positive stat changes
        for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
        {
            if (gBattleMons[battlerDef].statStages[i] > gBattleMons[battlerAtk].statStages[i])
            {
                switch (i)
                {
                case STAT_ATK:
                    if (HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                        score++;
                    break;
                case STAT_SPATK:
                    if (HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
                        score++;
                    break;
                case STAT_ACC:
                case STAT_EVASION:
                case STAT_SPEED:
                    score++;
                    break;
                case STAT_DEF:
                case STAT_SPDEF:
                    if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_STALL)
                        score++;
                    break;
                }
            }
        }
        break;
    case EFFECT_SEMI_INVULNERABLE:
    case EFFECT_DIG:
    case EFFECT_DIVE:
    case EFFECT_FLY:
    case EFFECT_SHADOW_FORCE:
        score++;
        if (predictedMove != MOVE_NONE && !isDoubleBattle)
        {
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // Attacker goes first
            {
                if (gBattleMoves[predictedMove].effect == EFFECT_EXPLOSION
                  || gBattleMoves[predictedMove].effect == EFFECT_PROTECT)
                    score += 3;
            }
            else if ((gBattleMoves[predictedMove].effect == EFFECT_SEMI_INVULNERABLE
                || gBattleMoves[predictedMove].effect == EFFECT_DIG
                || gBattleMoves[predictedMove].effect == EFFECT_DIVE
                || gBattleMoves[predictedMove].effect == EFFECT_FLY
                || gBattleMoves[predictedMove].effect == EFFECT_SHADOW_FORCE)
                && !(gStatuses3[battlerDef] & STATUS3_SEMI_INVULNERABLE))
            {
                score += 3;
            }
        }
        break;
    case EFFECT_DEFENSE_CURL:
        if (HasMoveEffect(battlerAtk, EFFECT_ROLLOUT) && !(gBattleMons[battlerAtk].status2 & STATUS2_DEFENSE_CURL))
            score++;
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_DEF, &score);
        break;
    case EFFECT_FAKE_OUT:
    case EFFECT_LOVE_TAP:
    case EFFECT_NOBLE_ROAR:
        if ((move == MOVE_FAKE_OUT) || (move == MOVE_NOBLE_ROAR) || (move == MOVE_COLD_SNAP)) // filter out first impression
        {
            if (ShouldFakeOut(battlerAtk, battlerDef, move))
                score += 4;
            else
                score -= 10;
        }
        if (move == MOVE_LOVE_TAP) // filter out first impression
        {
            if (ShouldLoveTap(battlerAtk, battlerDef, move))
                score += 4;
            else
                score -= 10;
        }
        if (move == MOVE_FIRST_IMPRESSION)
        {
            if (gDisableStructs[battlerAtk].isFirstTurn 
            && AI_DATA->abilities[battlerAtk] != ABILITY_GORILLA_TACTICS
            && AI_DATA->abilities[battlerAtk] != ABILITY_ONE_WAY_TRIP
            && AI_DATA->holdEffects[battlerAtk] != HOLD_EFFECT_CHOICE_BAND
            && AI_DATA->holdEffects[battlerAtk] != HOLD_EFFECT_CHOICE_SCARF
            && AI_DATA->holdEffects[battlerAtk] != HOLD_EFFECT_CHOICE_SPECS
            && DoesSubstituteBlockMove(battlerAtk, battlerDef, move))
                score += 4;
            else
                score -= 10;
        }
        break;
    case EFFECT_STOCKPILE:
        if (aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
            break;
        if (HasMoveEffect(battlerAtk, EFFECT_SWALLOW)
          || HasMoveEffect(battlerAtk, EFFECT_SPIT_UP))
            score += 2;

        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_DEF, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        break;
    case EFFECT_SPIT_UP:
        if (gDisableStructs[battlerAtk].stockpileCounter >= 1)
            score+= gDisableStructs[battlerAtk].stockpileCounter * 2;
        break;
    case EFFECT_FROST_SHRED:
        if (gBattleMons[battlerAtk].statStages[STAT_SPEED] > DEFAULT_STAT_STAGE)
            score+= CountBattlerSpeedIncreases(battlerAtk);
        break;
    case EFFECT_BOLT_BEAK:
        if (gBattleMons[battlerAtk].statStages[STAT_SPEED] > DEFAULT_STAT_STAGE)
            score+= CountBattlerSpeedIncreases(battlerAtk);
        break;
    case EFFECT_AERIAL_ACE:
        if (gBattleMons[battlerAtk].statStages[STAT_SPEED] > DEFAULT_STAT_STAGE)
            score+= CountBattlerAccuracyIncreases(battlerAtk);
        break;
    case EFFECT_HAYWIRE:
    case EFFECT_STORED_POWER:
        for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
        {
            if (gBattleMons[battlerAtk].statStages[i] > DEFAULT_STAT_STAGE)
                score += CountBattlerStatIncreases(battlerAtk, TRUE);
        }
        break;
    case EFFECT_ROLLOUT:
        if (gBattleMons[battlerAtk].status2 & STATUS2_DEFENSE_CURL)
            score += 8;
        break;
    case EFFECT_SWAGGER:
        if (HasMoveEffect(battlerAtk, EFFECT_FOUL_PLAY)
          || HasMoveEffect(battlerAtk, EFFECT_PSYCH_UP)
          || HasMoveEffect(battlerAtk, EFFECT_SPECTRAL_THIEF))
            score++;

        if (aiData->abilities[battlerDef] == ABILITY_CONTRARY)
            score += 2;

        IncreaseConfusionScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_FLATTER:
        if (HasMoveEffect(battlerAtk, EFFECT_PSYCH_UP)
          || HasMoveEffect(battlerAtk, EFFECT_SPECTRAL_THIEF))
            score += 2;

        if (aiData->abilities[battlerDef] == ABILITY_CONTRARY)
            score += 2;

        IncreaseConfusionScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_FURY_CUTTER:
    case EFFECT_RAGE_FIST:
        if (!isDoubleBattle && aiData->holdEffects[battlerAtk] == HOLD_EFFECT_METRONOME)
            score += 3;
        break;
    case EFFECT_ATTRACT:
        if (!isDoubleBattle && BattlerWillFaintFromSecondaryDamage(battlerDef, aiData->abilities[battlerDef])
          && AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER) // Target goes first
            break; // Don't use if the attract won't have a change to activate

        if (gBattleMons[battlerDef].status1 & STATUS1_ANY
          || (gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)
          || IsBattlerTrapped(battlerDef, TRUE))
            score += 2;
        else
            score++;
        break;
    case EFFECT_SAFEGUARD:
        if (!AI_IsTerrainAffected(battlerAtk, STATUS_FIELD_MISTY_TERRAIN) || !IsBattlerGrounded(battlerAtk))
            score++;
        //if (CountUsablePartyMons(battlerDef) != 0)
            //score += 8;
        break;
    case EFFECT_PURSUIT:
        /*TODO
        if (IsPredictedToSwitch(battlerDef, battlerAtk))
            score += 3;
        else if (IsPredictedToUsePursuitableMove(battlerDef, battlerAtk) && !MoveWouldHitFirst(move, battlerAtk, battlerDef)) //Pursuit against fast U-Turn
            score += 3;*/
        break;
    case EFFECT_RAPID_SPIN:
    case EFFECT_CINDER_TWIRL:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);    // Gen 8 increases speed
        //fallthrough
    case EFFECT_DEFOG:
        if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_HAZARDS_ANY && CountUsablePartyMons(battlerAtk) != 0)
        {
            score += 3;
            break;
        }

        switch (move)
        {
        case MOVE_DEFOG:
            if (gSideStatuses[GetBattlerSide(battlerDef)] & (SIDE_STATUS_SCREEN_ANY | SIDE_STATUS_SAFEGUARD | SIDE_STATUS_MIST))
            {
                score += 3;
            }
            else if (!(gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_SPIKES)) //Don't blow away hazards if you set them up
            {
                if (isDoubleBattle)
                {
                    if (IsHazardMoveEffect(gBattleMoves[aiData->partnerMove].effect) // Partner is going to set up hazards
                      && AI_WhoStrikesFirst(battlerAtk, BATTLE_PARTNER(battlerAtk), move) == AI_IS_SLOWER) // Partner going first
                        break; // Don't use Defog if partner is going to set up hazards
                }

                // check defog lowering evasion
                if (ShouldLowerEvasion(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
                {
                    if (gBattleMons[battlerDef].statStages[STAT_EVASION] > 7
                      || HasMoveWithLowAccuracy(battlerAtk, battlerDef, 90, TRUE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef]))
                        score += 2; // encourage lowering evasion if they are evasive or we have a move with low accuracy
                    else
                        score++;
                }
            }
            break;
        case MOVE_RAPID_SPIN:
        case MOVE_MORTAL_SPIN:
        case MOVE_CINDER_TWIRL:
            if (gStatuses3[battlerAtk] & STATUS3_LEECHSEED || gBattleMons[battlerAtk].status2 & STATUS2_WRAPPED)
                score += 3;
            break;
        }
        break;
    case EFFECT_LEAF_TORNADO:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_HAZARDS_ANY && CountUsablePartyMons(battlerAtk) != 0)
            {
                score += 3;
                break;
            }
            if (gStatuses3[battlerAtk] & STATUS3_LEECHSEED || gBattleMons[battlerAtk].status2 & STATUS2_WRAPPED)
                score += 3;
            break;
        }
    case EFFECT_TORMENT:
        break;
    case EFFECT_VEXING_KI:
        if (gBattleMons[battlerDef].status2 & STATUS2_TORMENT)
            IncreasePanicScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_WILL_O_WISP:
        IncreaseBurnScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_GLACIATE:
        IncreaseFrostbiteScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_FROST_NOVA:
        if (!(gBattleMons[battlerDef].status1 & STATUS1_ANY))
            IncreaseFrostbiteScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_FOLLOW_ME:
        if (isDoubleBattle
          && move != MOVE_SPOTLIGHT
          && !IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef])
          && (move != MOVE_RAGE_POWDER || IsAffectedByPowder(battlerDef, aiData->abilities[battlerDef], aiData->holdEffects[battlerDef])) // Rage Powder doesn't affect powder immunities
          && IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
        {
            u32 predictedMoveOnPartner = gLastMoves[BATTLE_PARTNER(battlerAtk)];
            if (predictedMoveOnPartner != MOVE_NONE && !IS_MOVE_STATUS(predictedMoveOnPartner))
                score += 3;
        }
        break;
    case EFFECT_NATURE_POWER:
        return AI_CheckViability(battlerAtk, battlerDef, GetNaturePowerMove(), score);
    case EFFECT_CHARGE:
        if (HasDamagingMoveOfType(battlerAtk, TYPE_ELECTRIC))
            score += 2;
        #if B_CHARGE_SPDEF_RAISE >= GEN_5
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        #endif
        if (AI_IsTerrainAffected(battlerAtk, STATUS_FIELD_ELECTRIC_TERRAIN))
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        break;
    case EFFECT_TAUNT:
        if (IS_MOVE_STATUS(predictedMove))
            score += 3;
        else if (HasMoveWithSplit(battlerDef, SPLIT_STATUS))
            score += 2;
        break;
    case EFFECT_RAGE_POWDER:
        if (IS_MOVE_STATUS(predictedMove))
            score += 3;
        else if (HasMoveWithSplit(battlerDef, SPLIT_STATUS))
            score += 2;

        if (isDoubleBattle
          && move != MOVE_SPOTLIGHT
          && !IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef])
          && (IsAffectedByPowder(battlerDef, aiData->abilities[battlerDef], aiData->holdEffects[battlerDef])) // Rage Powder doesn't affect powder immunities
          && IsBattlerAlive(BATTLE_PARTNER(battlerAtk)))
        {
            u32 predictedMoveOnPartner = gLastMoves[BATTLE_PARTNER(battlerAtk)];
            if (predictedMoveOnPartner != MOVE_NONE && !IS_MOVE_STATUS(predictedMoveOnPartner))
                score += 3;
        }
        break;
    case EFFECT_TRICK:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_FROST_ORB && AI_THINKING_STRUCT->aiFlags & AI_FLAG_SEBASTIANS_TRICK)
            score += 20;
        else if (aiData->holdEffects[battlerAtk] != HOLD_EFFECT_FROST_ORB && AI_THINKING_STRUCT->aiFlags & AI_FLAG_SEBASTIANS_TRICK)
            score -= 20;
        break;
    case EFFECT_BESTOW:
        switch (aiData->holdEffects[battlerAtk])
        {
        case HOLD_EFFECT_CHOICE_SCARF:
            score += 2; // assume its beneficial
            break;
        case HOLD_EFFECT_CHOICE_BAND:
            if (!HasMoveWithSplit(battlerDef, SPLIT_PHYSICAL))
                score += 2;
            break;
        case HOLD_EFFECT_CHOICE_SPECS:
            if (!HasMoveWithSplit(battlerDef, SPLIT_SPECIAL))
                score += 2;
            break;
        case HOLD_EFFECT_TOXIC_ORB:
            if (!ShouldPoisonSelf(battlerAtk, aiData->abilities[battlerAtk]))
                score += 2;
            break;
        case HOLD_EFFECT_FLAME_ORB:
            if (!ShouldBurnSelf(battlerAtk, aiData->abilities[battlerAtk]) && AI_CanBeBurned(battlerAtk, aiData->abilities[battlerDef]))
                score += 2;
            break;
        case HOLD_EFFECT_BLACK_SLUDGE:
            if (!IS_BATTLER_OF_TYPE(battlerDef, TYPE_POISON) && aiData->abilities[battlerDef] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT))
                score += 3;
            break;
        case HOLD_EFFECT_IRON_BALL:
            if (!HasMoveEffect(battlerDef, EFFECT_FLING) || !IsBattlerGrounded(battlerDef))
                score += 2;
            break;
        case HOLD_EFFECT_LAGGING_TAIL:
        case HOLD_EFFECT_STICKY_BARB:
            score += 3;
            break;
        case HOLD_EFFECT_UTILITY_UMBRELLA:
            if (aiData->abilities[battlerAtk] != ABILITY_SOLAR_POWER && aiData->abilities[battlerAtk] != ABILITY_DRY_SKIN)
            {
                switch (aiData->abilities[battlerDef])
                {
                case ABILITY_SWIFT_SWIM:
                    if (AI_GetWeather(aiData) & B_WEATHER_RAIN)
                        score += 3; // Slow 'em down
                    break;
                case ABILITY_CHLOROPHYLL:
                case ABILITY_FLOWER_GIFT:
                    if (AI_GetWeather(aiData) & B_WEATHER_SUN)
                        score += 3; // Slow 'em down
                    break;
                }
            }
            break;
        case HOLD_EFFECT_EJECT_BUTTON:
            //if (!IsRaidBattle() && IsDynamaxed(battlerDef) && gNewBS->dynamaxData.timer[battlerDef] > 1 &&
            if (HasDamagingMove(battlerAtk)
             || (isDoubleBattle && IsBattlerAlive(BATTLE_PARTNER(battlerAtk)) && HasDamagingMove(BATTLE_PARTNER(battlerAtk))))
                score += 2; // Force 'em out next turn
            break;
        default:
            if (move != MOVE_BESTOW && aiData->items[battlerAtk] == ITEM_NONE)
            {
                switch (aiData->holdEffects[battlerDef])
                {
                case HOLD_EFFECT_CHOICE_BAND:
                    break;
                case HOLD_EFFECT_TOXIC_ORB:
                    if (ShouldPoisonSelf(battlerAtk, aiData->abilities[battlerAtk]))
                        score += 2;
                    break;
                case HOLD_EFFECT_FLAME_ORB:
                    if (ShouldBurnSelf(battlerAtk, aiData->abilities[battlerAtk]))
                        score += 2;
                    break;
                case HOLD_EFFECT_BLACK_SLUDGE:
                    if (IS_BATTLER_OF_TYPE(battlerAtk, TYPE_POISON) || aiData->abilities[battlerAtk] == (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT))
                        score += 3;
                    break;
                case HOLD_EFFECT_IRON_BALL:
                    if (HasMoveEffect(battlerAtk, EFFECT_FLING))
                        score += 2;
                    break;
                case HOLD_EFFECT_LAGGING_TAIL:
                case HOLD_EFFECT_STICKY_BARB:
                    break;
                default:
                    score++;    //other hold effects generally universally good
                    break;
                }
            }
        }
        break;
    case EFFECT_ROLE_PLAY:
        if (!IsRolePlayBannedAbilityAtk(aiData->abilities[battlerAtk])
          && !IsRolePlayBannedAbility(aiData->abilities[battlerDef])
          && !IsAbilityOfRating(aiData->abilities[battlerAtk], 5)
          && IsAbilityOfRating(aiData->abilities[battlerDef], 5))
            score += 2;
        break;
    case EFFECT_INGRAIN:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_BIG_ROOT)
            score += 3;
        break;
    case EFFECT_SUPERPOWER:
    case EFFECT_OVERHEAT:
    case EFFECT_MAKE_IT_RAIN:
    case EFFECT_BRUTALIZE:
    case EFFECT_HEAVY_CANNON:
    case EFFECT_GIANTS_SPEAR:
        if (aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
            score += 3;
        break;
    case EFFECT_FLEUR_CANNON:
        if (aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
            score += 3;
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
            score += 2;    
        break;
    case EFFECT_MAGIC_COAT:
        if (IS_MOVE_STATUS(predictedMove) && AI_GetBattlerMoveTargetType(battlerDef, predictedMove) & (MOVE_TARGET_SELECTED | MOVE_TARGET_OPPONENTS_FIELD | MOVE_TARGET_BOTH))
            score += 3;
        break;
    case EFFECT_RECYCLE:
        if (GetUsedHeldItem(battlerAtk) != ITEM_NONE)
            score++;
        if (IsRecycleEncouragedItem(GetUsedHeldItem(battlerAtk)))
            score++;
        if (aiData->abilities[battlerAtk] == ABILITY_RIPEN)
        {
            u32 item = GetUsedHeldItem(battlerAtk);
            u32 toHeal = (ItemId_GetHoldEffectParam(item) == 10) ? 10 : gBattleMons[battlerAtk].maxHP / ItemId_GetHoldEffectParam(item);

            if (IsStatBoostingBerry(item) && aiData->hpPercents[battlerAtk] > 60)
                score++;
            else if (ShouldRestoreHpBerry(battlerAtk, item) && !CanAIFaintTarget(battlerAtk, battlerDef, 0)
              && ((GetWhichBattlerFaster(battlerAtk, battlerDef, TRUE) == 0 && CanTargetFaintAiWithMod(battlerDef, battlerAtk, 0, 0))
               || !CanTargetFaintAiWithMod(battlerDef, battlerAtk, toHeal, 0)))
                score++;    // Recycle healing berry if we can't otherwise faint the target and the target wont kill us after we activate the berry
        }
        break;
    case EFFECT_BRICK_BREAK:
    case EFFECT_PSYCHIC_FANGS:
    if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_REFLECT)
            score++;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_LIGHTSCREEN)
            score++;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_AURORA_VEIL)
            score++;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_GOOGOO_SCREEN)
            score++;
        break;
    case EFFECT_KNOCK_OFF:
    case EFFECT_PARTY_TRICK:
        if (CanKnockOffItem(battlerDef, aiData->items[battlerDef]))
        {
            switch (aiData->holdEffects[battlerDef])
            {
            case HOLD_EFFECT_IRON_BALL:
                if (HasMoveEffect(battlerDef, EFFECT_FLING))
                    score += 4;
                break;
            case HOLD_EFFECT_LAGGING_TAIL:
            case HOLD_EFFECT_STICKY_BARB:
                break;
            default:
                score += 3;
                break;
            }
        }
        break;
    case EFFECT_SKILL_SWAP:
        if (GetAbilityRating(aiData->abilities[battlerDef]) > GetAbilityRating(aiData->abilities[battlerAtk]))
            score++;
        break;
    case EFFECT_GASTRO_ACID:
    case EFFECT_SIMPLE_BEAM:
        if (IsAbilityOfRating(aiData->abilities[battlerDef], 5))
            score += 2;
        break;
    case EFFECT_WORRY_SEED:
        IncreasePanicScore(battlerAtk, battlerDef, move, &score);
        if (IsAbilityOfRating(aiData->abilities[battlerDef], 5))
            score += 2;
        break;
    case EFFECT_ENTRAINMENT:
        if (IsAbilityOfRating(aiData->abilities[battlerDef], 5) || GetAbilityRating(aiData->abilities[battlerAtk]) <= 0)
        {
            if (aiData->abilities[battlerDef] != aiData->abilities[battlerAtk] && !(gStatuses3[battlerDef] & STATUS3_GASTRO_ACID))
                score += 2;
        }
        break;
    case EFFECT_IMPRISON:
        if (predictedMove != MOVE_NONE && HasMove(battlerAtk, predictedMove))
            score += 3;
        else if (gDisableStructs[battlerAtk].isFirstTurn == 0)
            score++;
        break;
    case EFFECT_SUN_BASK:
        if (aiData->hpPercents[battlerAtk] <= 40 || aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
            break;
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_DEF, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        break;
    case EFFECT_REFRESH:
    case EFFECT_MOON_BEAM:
        if (gBattleMons[battlerAtk].status1 & STATUS1_ANY_NEGATIVE)
            score += 2;
        break;
    case EFFECT_FLORESCENCE:
        if (gBattleMons[battlerAtk].status1 & STATUS1_ANY_NEGATIVE)
            score += 2;
        else if (ShouldBloomSelf(battlerAtk, aiData->abilities[battlerAtk]))
            score += 2;
        break;
    case EFFECT_TAKE_HEART:
        if (gBattleMons[battlerAtk].status1 & STATUS1_ANY
         || BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPATK)
         || BattlerStatCanRise(battlerAtk, aiData->abilities[battlerAtk], STAT_SPDEF))
            score += 2;
        break;
    case EFFECT_PSYCHO_SHIFT:
        if (gBattleMons[battlerAtk].status1 & STATUS1_PSN_ANY)
            IncreasePoisonScore(battlerAtk, battlerDef, move, &score);
        else if (gBattleMons[battlerAtk].status1 & STATUS1_BURN)
            IncreaseBurnScore(battlerAtk, battlerDef, move, &score);
        else if (gBattleMons[battlerAtk].status1 & STATUS1_PARALYSIS)
            IncreaseParalyzeScore(battlerAtk, battlerDef, move, &score);
        else if (gBattleMons[battlerAtk].status1 & STATUS1_SLEEP_ANY)
            IncreaseSleepScore(battlerAtk, battlerDef, move, &score);
        else if (gBattleMons[battlerAtk].status1 & STATUS1_FROSTBITE)
            IncreaseFrostbiteScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_GRUDGE:
        break;
    case EFFECT_SNATCH:
        if (predictedMove != MOVE_NONE && gBattleMoves[predictedMove].snatchAffected)
            score += 3; // Steal move
        break;
    case EFFECT_MUD_SPORT:
        if (!HasMoveWithType(battlerAtk, TYPE_ELECTRIC) && HasMoveWithType(battlerDef, TYPE_ELECTRIC))
            score++;
        break;
    case EFFECT_WATER_SPORT:
        if (!HasMoveWithType(battlerAtk, TYPE_FIRE) && (HasMoveWithType(battlerDef, TYPE_FIRE)))
            score++;
        break;
    case EFFECT_TICKLE:
        if (gBattleMons[battlerDef].statStages[STAT_DEF] > 4 && HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL)
          && aiData->abilities[battlerDef] != ABILITY_CONTRARY && ShouldLowerDefense(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
        {
            score += 2;
        }
        else if (ShouldLowerAttack(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
        {
            score += 2;
        }
        break;
    case EFFECT_ENERVATOR:
        if (ShouldLowerSpeed(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
        {
            score += 2;
        }
        else if (ShouldLowerAttack(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
        {
            score += 2;
        }
        break;
    case EFFECT_COSMIC_POWER:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_DEF, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        break;
    case EFFECT_BULK_UP:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_DEF, &score);
        break;
    case EFFECT_MEDITATE:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        if (aiData->abilities[battlerAtk] == ABILITY_INNER_FOCUS)
            score++;
        break;
    case EFFECT_CALM_MIND:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        break;
    case EFFECT_GEOMANCY:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_POWER_HERB)
            score += 3;
        //fallthrough
    case EFFECT_QUIVER_DANCE:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        break;
    case EFFECT_HUNKER_DOWN:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_DEF, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        break;
    case EFFECT_FILLET_AWAY:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        break;
    case EFFECT_VICTORY_DANCE:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_DEF, &score);
        break;
    case EFFECT_SHELL_SMASH:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_RESTORE_STATS)
            score += 1;

        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        break;
    case EFFECT_PHANTASM:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_RESTORE_STATS)
            score += 1;

        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_EVASION, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        break;
    case EFFECT_DRAGON_DANCE:
    case EFFECT_SHIFT_GEAR:
    case EFFECT_TIDY_UP:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        break;
    case EFFECT_VIGOR_ROOT:
        if (ShouldRecover(battlerAtk, battlerDef, move, 100))
            score += 3;
    case EFFECT_CLANGOROUS_SOUL:
    case EFFECT_NO_RETREAT:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_DEF, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPDEF, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        break;
    case EFFECT_TRAILBLAZE:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ACC, &score);
        }
        else
        {
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        }
        break;
    case EFFECT_GUARD_SWAP:
        if (gBattleMons[battlerDef].statStages[STAT_DEF] > gBattleMons[battlerAtk].statStages[STAT_DEF]
          && gBattleMons[battlerDef].statStages[STAT_SPDEF] >= gBattleMons[battlerAtk].statStages[STAT_SPDEF])
            score++;
        else if (gBattleMons[battlerDef].statStages[STAT_SPDEF] > gBattleMons[battlerAtk].statStages[STAT_SPDEF]
          && gBattleMons[battlerDef].statStages[STAT_DEF] >= gBattleMons[battlerAtk].statStages[STAT_DEF])
            score++;
        break;
    case EFFECT_POWER_TRICK:
        if (!(gStatuses3[battlerAtk] & STATUS3_POWER_TRICK))
        {
            if (gBattleMons[battlerAtk].defense > gBattleMons[battlerAtk].attack && HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
                score += 2;
            break;
        }
        break;
    case EFFECT_HEART_SWAP:
        {
            bool32 hasHigherStat = FALSE;
            //Only use if all target stats are >= attacker stats to prevent infinite loop
            for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
            {
                if (gBattleMons[battlerDef].statStages[i] < gBattleMons[battlerAtk].statStages[i])
                    break;
                if (gBattleMons[battlerDef].statStages[i] > gBattleMons[battlerAtk].statStages[i])
                    hasHigherStat = TRUE;
            }
            if (hasHigherStat && i == NUM_BATTLE_STATS)
                score++;
        }
        break;
    case EFFECT_SPEED_SWAP:
        // TODO this is cheating a bit...
        if (gBattleMons[battlerDef].speed > gBattleMons[battlerAtk].speed)
            score += 3;
        break;
    case EFFECT_POWER_SWAP:
        // TODO this is cheating a bit...
        if (gBattleMons[battlerDef].attack > gBattleMons[battlerAtk].attack && gBattleMons[battlerDef].spAttack > gBattleMons[battlerAtk].spAttack)
            score += 3;
        if (aiData->hpPercents[battlerAtk] <= 40 || aiData->abilities[battlerAtk] == ABILITY_CONTRARY)
            break;

        if (HasMoveWithSplit(battlerAtk, SPLIT_PHYSICAL))
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_ATK, &score);
        else if (HasMoveWithSplit(battlerAtk, SPLIT_SPECIAL))
            IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPATK, &score);
        break;
    case EFFECT_GUARD_SPLIT:
        {
            // TODO also kind of cheating...
            u32 newDefense = (gBattleMons[battlerAtk].defense + gBattleMons[battlerDef].defense) / 2;
            u32 newSpDef = (gBattleMons[battlerAtk].spDefense + gBattleMons[battlerDef].spDefense) / 2;

            if ((newDefense > gBattleMons[battlerAtk].defense && newSpDef >= gBattleMons[battlerAtk].spDefense)
              || (newSpDef > gBattleMons[battlerAtk].spDefense && newDefense >= gBattleMons[battlerAtk].defense))
                score++;
        }
        break;
    case EFFECT_POWER_SPLIT:
        {
            u32 newAttack = (gBattleMons[battlerAtk].attack + gBattleMons[battlerDef].attack) / 2;
            u32 newSpAtk = (gBattleMons[battlerAtk].spAttack + gBattleMons[battlerDef].spAttack) / 2;

            if ((newAttack > gBattleMons[battlerAtk].attack && newSpAtk >= gBattleMons[battlerAtk].spAttack)
              || (newSpAtk > gBattleMons[battlerAtk].spAttack && newAttack >= gBattleMons[battlerAtk].attack))
                score++;
        }
        break;
    case EFFECT_BUG_BITE:   // And pluck
        if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE || aiData->abilities[battlerDef] == ABILITY_STICKY_HOLD || IS_BATTLER_OF_TYPE(battlerDef, TYPE_FAIRY))
            break;
        else if (ItemId_GetPocket(aiData->items[battlerDef]) == POCKET_BERRIES)
            score += 3;
        break;
    case EFFECT_INCINERATE:
        if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE || aiData->abilities[battlerDef] == ABILITY_STICKY_HOLD || IS_BATTLER_OF_TYPE(battlerDef, TYPE_FAIRY))
            break;
        else if (ItemId_GetPocket(aiData->items[battlerDef]) == POCKET_BERRIES || aiData->holdEffects[battlerDef] == HOLD_EFFECT_GEMS)
            score += 3;
        break;
    case EFFECT_SMACK_DOWN:
        if (!IsBattlerGrounded(battlerDef))
            score += 3;
        if (gFieldStatuses & STATUS_FIELD_GRAVITY)
            score += 2;
        break;
    case EFFECT_SCORP_FANG:
        if (!IsBattlerGrounded(battlerDef))
            score += 3;
        IncreasePoisonScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_RELIC_SONG:
        if (!(gBattleMons[battlerAtk].status2 & STATUS2_TRANSFORMED)) // Don't try to change form if it's transformed.
        {
            if (gBattleMons[battlerAtk].species == SPECIES_MELOETTA && gBattleMons[battlerDef].defense < gBattleMons[battlerDef].spDefense)
                score += 3; // Change to Pirouette if can do more damage
            else if (gBattleMons[battlerAtk].species == SPECIES_MELOETTA_PIROUETTE && gBattleMons[battlerDef].spDefense < gBattleMons[battlerDef].defense)
                score += 3; // Change to Aria if can do more damage
        }
        break;
    case EFFECT_ELECTRIC_TERRAIN:
    case EFFECT_MISTY_TERRAIN:
        if (gStatuses3[battlerAtk] & STATUS3_YAWN && IsBattlerGrounded(battlerAtk))
            score += 10;
        //fallthrough
    case EFFECT_GRASSY_TERRAIN:
    case EFFECT_PSYCHIC_TERRAIN:
        score += 2;
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_TERRAIN_EXTENDER)
            score += 2;
        break;
    case EFFECT_DRUM_BEATING:
        if (gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING)
        {
            score += 2;
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_TERRAIN_EXTENDER)
                score += 2;
        }
        break;
    case EFFECT_HIT_SET_REMOVE_TERRAIN:
        if (IsShunyongBattle())  // DEMOLISHER:
        {
            if (gFieldStatuses & (STATUS_FIELD_TRICK_ROOM | STATUS_FIELD_TERRAIN_ANY) && (Random() % 100) < 20) // 20% chance to use
                score += 20;
            else
                score -= 2;
        }
        //fallthrough
    case EFFECT_EARTH_SHATTER:
        if (gFieldStatuses & STATUS_FIELD_TERRAIN_ANY)
            score += 4;
        break;
    case EFFECT_SKY_SPLITTER:
        if (AI_GetWeather(aiData) & (B_WEATHER_ANY))
            score += 4;
        break;
    case EFFECT_PLEDGE:
        if (isDoubleBattle)
        {
            if (HasMoveEffect(BATTLE_PARTNER(battlerAtk), EFFECT_PLEDGE))
                score += 3; // Partner might use pledge move
        }
        break;
    case EFFECT_TRICK_ROOM:
        if (!(gFieldStatuses & STATUS_FIELD_TRICK_ROOM) && GetBattlerSideSpeedAverage(battlerAtk) < GetBattlerSideSpeedAverage(battlerDef))
            score += 3;
        else if ((gFieldStatuses & STATUS_FIELD_TRICK_ROOM) && GetBattlerSideSpeedAverage(battlerAtk) >= GetBattlerSideSpeedAverage(battlerDef))
            score += 3;
        break;
    case EFFECT_MAGIC_ROOM:
        score++;
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_NONE && aiData->holdEffects[battlerDef] != HOLD_EFFECT_NONE)
            score++;
        if (isDoubleBattle && aiData->holdEffects[BATTLE_PARTNER(battlerAtk)] == HOLD_EFFECT_NONE && aiData->holdEffects[BATTLE_PARTNER(battlerDef)] != HOLD_EFFECT_NONE)
            score++;
        break;
    case EFFECT_WONDER_ROOM:
        if ((HasMoveWithSplit(battlerDef, SPLIT_PHYSICAL) && gBattleMons[battlerAtk].defense < gBattleMons[battlerAtk].spDefense)
          || (HasMoveWithSplit(battlerDef, SPLIT_SPECIAL) && gBattleMons[battlerAtk].spDefense < gBattleMons[battlerAtk].defense))
            score += 2;
        break;
    case EFFECT_GRAVITY:
        if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
        {
            if (HasMoveEffect(battlerAtk, EFFECT_LOW_KICK)
             || HasMoveEffect(battlerAtk, EFFECT_HEAT_CRASH)
             || HasMoveEffect(battlerAtk, EFFECT_GRAVITON_ARM)
             || HasMoveEffect(battlerAtk, EFFECT_GRAV_APPLE)
             || HasMoveEffect(battlerAtk, EFFECT_SMACK_DOWN))
                score += 2;
            if (HasSleepMoveWithLowAccuracy(battlerAtk, battlerDef)) // Has Gravity for a move like Hypnosis
                IncreaseSleepScore(battlerAtk, battlerDef, move, &score);
            else if (HasMoveWithLowAccuracy(battlerAtk, battlerDef, 90, FALSE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef]))
                score += 2;
            else
                score++;
        }
        break;
    case EFFECT_GRAVITON_ARM:
        if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
        {
            if (HasMoveEffect(battlerAtk, EFFECT_LOW_KICK)
             || HasMoveEffect(battlerAtk, EFFECT_HEAT_CRASH)
             || HasMoveEffect(battlerAtk, EFFECT_GRAVITON_ARM)
             || HasMoveEffect(battlerAtk, EFFECT_GRAV_APPLE)
             || HasMoveEffect(battlerAtk, EFFECT_SMACK_DOWN))
                score += 2;
            if (HasSleepMoveWithLowAccuracy(battlerAtk, battlerDef)) // Has Gravity for a move like Hypnosis
                IncreaseSleepScore(battlerAtk, battlerDef, move, &score);
            else if (HasMoveWithLowAccuracy(battlerAtk, battlerDef, 90, FALSE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef]))
                score += 2;
            else
                score++;
        }
        if (gFieldStatuses & STATUS_FIELD_GRAVITY)
            score += 2;
        break;
    case EFFECT_ION_DELUGE:
        if (isDoubleBattle)
            score++;
        if ((aiData->abilities[battlerAtk] == ABILITY_VOLT_ABSORB
          || aiData->abilities[battlerAtk] == ABILITY_MOTOR_DRIVE
          || aiData->abilities[battlerAtk] == ABILITY_LIGHTNING_ROD)
          || IS_BATTLER_OF_TYPE(battlerAtk, TYPE_GROUND))
            score += 3;
        break;
    case EFFECT_FLING:
        /* TODO
        switch (gFlingTable[aiData->items[battlerAtk]].effect)
        {
        case MOVE_EFFECT_BURN:
            IncreaseBurnScore(battlerAtk, battlerDef, move, &score);
            break;
        case MOVE_EFFECT_FLINCH:
            score += ShouldTryToFlinch(battlerAtk, battlerDef, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], move);
            break;
        case MOVE_EFFECT_PARALYSIS:
            IncreaseParalyzeScore(battlerAtk, battlerDef, move, &score);
            break;
        case MOVE_EFFECT_POISON:
        case MOVE_EFFECT_TOXIC:
            IncreasePoisonScore(battlerAtk, battlerDef, move, &score);
            break;
        case MOVE_EFFECT_FREEZE:
            if (AI_CanFreeze(battlerAtk, battlerDef))
                score += 3;
            break;
        }*/
        if (aiData->items[battlerAtk] == ITEM_LIGHT_BALL && CanFling(battlerAtk))
            IncreaseParalyzeScore(battlerAtk, battlerDef, move, &score);
        if (HasMoveEffect(battlerDef, EFFECT_ACROBATICS) && CanFling(battlerAtk))
            score += 4;
        if (gDisableStructs[battlerAtk].isFirstTurn && CanFling(battlerAtk))
            score += 2;
        break;
    case EFFECT_FEINT:
        if (gBattleMoves[predictedMove].effect == EFFECT_PROTECT)
            score += 4;
        break;
    case EFFECT_HULLBREAKER:
    case EFFECT_HYPER_DRILL:
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_REFLECT)
            score++;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_LIGHTSCREEN)
            score++;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_AURORA_VEIL)
            score++;
        if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_GOOGOO_SCREEN)
            score++;
        if (gBattleMoves[predictedMove].effect == EFFECT_PROTECT)
            score += 3;
        break;
    case EFFECT_EMBARGO:
        if (aiData->holdEffects[battlerDef] != HOLD_EFFECT_NONE)
            score++;
        break;
    case EFFECT_POWDER:
        if (predictedMove != MOVE_NONE && !IS_MOVE_STATUS(predictedMove) && gBattleMoves[predictedMove].type == TYPE_FIRE)
            score += 4;
        if (ShouldLowerAccuracy(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if ((aiData->hpPercents[battlerAtk] < 70 || aiData->hpPercents[battlerDef] < 70) && AI_RandLessThan(100))
            score--;
        if (gBattleMons[battlerDef].statStages[STAT_ACC] <= 4 && !AI_RandLessThan(80))
            score -= 2;
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY && !AI_RandLessThan(70))
            score += 2;
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED && !AI_RandLessThan(70))
            score += 2;
        if (gStatuses3[battlerDef] & STATUS3_ROOTED && AI_RandLessThan(128))
            score++;
        if (gBattleMons[battlerDef].status2 & STATUS2_CURSED && !AI_RandLessThan(70))
            score += 2;
        if (aiData->hpPercents[battlerAtk] > 70 || gBattleMons[battlerDef].statStages[STAT_ACC] < DEFAULT_STAT_STAGE)
            break;
        else if (aiData->hpPercents[battlerAtk] < 40 || aiData->hpPercents[battlerDef] < 40 || !AI_RandLessThan(70))
            score -= 2;
        break;
    case EFFECT_SILVER_WIND:
        if (predictedMove != MOVE_NONE && !IS_MOVE_STATUS(predictedMove) && gBattleMoves[predictedMove].type == TYPE_FIRE)
            score += 3;
        break;
    case EFFECT_TELEKINESIS:
        if (HasMoveWithLowAccuracy(battlerAtk, battlerDef, 90, FALSE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef])
          || !IsBattlerGrounded(battlerDef))
            score++;
        if (ShouldTrap(battlerAtk, battlerDef, move))
            score += 3;
        break;
    case EFFECT_THROAT_CHOP:
        if (predictedMove != MOVE_NONE && gBattleMoves[predictedMove].soundMove && AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER)
            score += 3; // Ai goes first and predicts the target will use a sound move
        else if (HasSoundMove(battlerDef))
            score += 3;
        break;
    case EFFECT_HEAL_BLOCK:
        if (IsBattlerTrapped(battlerDef, TRUE))
            score--;
        else if (ShouldTrap(battlerAtk, battlerDef, move))
            score += 5;
        if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER && predictedMove != MOVE_NONE && IsHealingMoveEffect(gBattleMoves[predictedMove].effect))
            score += 3; // Try to cancel healing move
        else if (HasHealingEffect(battlerDef) || aiData->holdEffects[battlerDef] == HOLD_EFFECT_LEFTOVERS
          || (aiData->holdEffects[battlerDef] == HOLD_EFFECT_BLACK_SLUDGE && IS_BATTLER_OF_TYPE(battlerDef, TYPE_POISON)))
            score += 2;
        break;
    case EFFECT_PSYCHIC_NOISE:
        if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER && predictedMove != MOVE_NONE && IsHealingMoveEffect(gBattleMoves[predictedMove].effect))
            score += 3; // Try to cancel healing move
        else if (HasHealingEffect(battlerDef) || aiData->holdEffects[battlerDef] == HOLD_EFFECT_LEFTOVERS
          || (aiData->holdEffects[battlerDef] == HOLD_EFFECT_BLACK_SLUDGE && IS_BATTLER_OF_TYPE(battlerDef, TYPE_POISON)))
            score += 2;
        break;
    case EFFECT_SOAK:
        if (HasMoveWithType(battlerAtk, TYPE_ELECTRIC) || HasMoveWithType(battlerAtk, TYPE_GRASS) || HasMoveEffect(battlerAtk, EFFECT_FREEZE_DRY))
            score += 2; // Get some super effective moves
        break;
    case EFFECT_SPIRIT_AWAY:
        if ((HasMoveWithType(battlerAtk, TYPE_GHOST) || HasMoveWithType(battlerAtk, TYPE_DARK) || HasMoveEffect(battlerAtk, EFFECT_EXORCISM))
        && (GetBattlerType(battlerDef, 0) != TYPE_GHOST || GetBattlerType(battlerDef, 1) != TYPE_GHOST || GetBattlerType(battlerDef, 2) != TYPE_GHOST))
            score += 2; // Get some super effective moves
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_BIG_ROOT)
            score++;
        if (effectiveness <= AI_EFFECTIVENESS_x0_5 && AI_RandLessThan(50))
            score -= 3;
        break;
    case EFFECT_PURIFICATION:
        if (HasMoveWithType(battlerAtk, TYPE_FIGHTING))
            score += 3; // Get some super effective moves
        break;
    case EFFECT_MAGIC_POWDER:
        if (HasMoveWithType(battlerAtk, TYPE_GHOST) || HasMoveWithType(battlerAtk, TYPE_DARK) || HasMoveWithType(battlerAtk, TYPE_BUG))
            score += 2; // Get some super effective moves
        if (AI_RandLessThan(128))
            IncreaseSleepScore(battlerAtk, battlerDef, move, &score);
        break;
    case EFFECT_THIRD_TYPE:
        if (aiData->abilities[battlerDef] == ABILITY_WONDER_GUARD)
            score += 2; // Give target more weaknesses
        break;
    case EFFECT_ELECTRIFY:
        if (predictedMove != MOVE_NONE
         && (aiData->abilities[battlerAtk] == ABILITY_VOLT_ABSORB
          || aiData->abilities[battlerAtk] == ABILITY_MOTOR_DRIVE
          || aiData->abilities[battlerAtk] == ABILITY_LIGHTNING_ROD))
        {
            score += 3;
        }
        break;
    case EFFECT_TOPSY_TURVY:
        if (CountPositiveStatStages(battlerDef) > CountNegativeStatStages(battlerDef))
            score++;
        break;
    case EFFECT_BURNING_ENVY:
        if (CountBattlerStatIncreases(battlerDef, TRUE) > 2)
            score += 8;
        if (!(AI_CanBeBurned(battlerAtk, aiData->abilities[battlerDef])))
            score -= 6;
        if (gBattleMons[battlerDef].status2 & STATUS2_TORMENT || aiData->holdEffects[battlerDef] == HOLD_EFFECT_MENTAL_HERB)
            score -= 3;
        if (CountBattlerStatIncreases(battlerDef, TRUE) < 3)
            score -= 8;
        break;
    case EFFECT_ALLURING_VOICE:
        if (CountBattlerStatIncreases(battlerDef, TRUE) > 1 && AI_CanBeConfused(battlerDef, TRUE))
            score += 2;
        break;
    case EFFECT_ALL_STATS_UP_HIT:
        if (move == MOVE_OMINOUS_WIND && (gBattleMons[battlerDef].status1 & STATUS1_PANIC))
            score += 3;
        break;
    case EFFECT_FAIRY_LOCK:
        if (!IsBattlerTrapped(battlerDef, TRUE))
        {
            if (ShouldTrap(battlerAtk, battlerDef, move))
                score += 8;
        }
        break;
    case EFFECT_QUASH:
        if (isDoubleBattle
          && AI_WhoStrikesFirst(BATTLE_PARTNER(battlerAtk), battlerDef, aiData->partnerMove) == AI_IS_SLOWER) // Attacker partner wouldn't go before target
            score++;
        break;
    case EFFECT_SUBMISSION:
        if (isDoubleBattle
          && AI_WhoStrikesFirst(BATTLE_PARTNER(battlerAtk), battlerDef, aiData->partnerMove) == AI_IS_SLOWER) // Attacker partner wouldn't go before target
            score++;
        if ((!IS_MOVE_STATUS(predictedMove)))
            score += 2;
        break;
    case EFFECT_TAILWIND:
        if (GetBattlerSideSpeedAverage(battlerAtk) < GetBattlerSideSpeedAverage(battlerDef))
            score += 2;
        if (HasMoveEffect(battlerAtk, EFFECT_MANEUVER)
             || HasMoveEffect(battlerAtk, EFFECT_SHARP_GLIDE)
             || HasMoveEffect(battlerAtk, EFFECT_AIR_CANNON))
                score += 2;
        break;
    case EFFECT_MANEUVER:
            if (gSideTimers[GetBattlerSide(battlerAtk)].tailwindTimer != 0
              || PartnerMoveIs(BATTLE_PARTNER(battlerAtk), aiData->partnerMove, MOVE_TAILWIND))
                score += 3;
            break;
    case EFFECT_LUCKY_CHANT:
        if (!isDoubleBattle)
        {
            score += 3;
        }
        else
        {
            score++;
            if (CountUsablePartyMons(battlerDef) > 0)
                score += 8;
        }
        break;
    case EFFECT_MAGNET_RISE:
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        if (IsBattlerGrounded(battlerAtk) && HasDamagingMoveOfType(battlerDef, TYPE_ELECTRIC)
          && !(AI_GetTypeEffectiveness(MOVE_EARTHQUAKE, battlerDef, battlerAtk) == AI_EFFECTIVENESS_x0)) // Doesn't resist ground move
        {
            if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER) // Attacker goes first
           {
                if (gBattleMoves[predictedMove].type == TYPE_GROUND)
                    score += 3; // Cause the enemy's move to fail
                break;
            }
            else // Opponent Goes First
            {
                if (HasDamagingMoveOfType(battlerDef, TYPE_GROUND))
                    score += 2;
                break;
            }
        }
        break;
    case EFFECT_CAMOUFLAGE:
        if (predictedMove != MOVE_NONE && AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER // Attacker goes first
          && !IS_MOVE_STATUS(move) && AI_GetTypeEffectiveness(predictedMove, battlerDef, battlerAtk) != AI_EFFECTIVENESS_x0)
            score++;
        break;
    case EFFECT_FLAME_BURST:
        if (isDoubleBattle)
        {
            if (IsBattlerAlive(BATTLE_PARTNER(battlerDef))
              && aiData->hpPercents[BATTLE_PARTNER(battlerDef)] < 12
              && aiData->abilities[BATTLE_PARTNER(battlerDef)] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT)
              && !IS_BATTLER_OF_TYPE(BATTLE_PARTNER(battlerDef), TYPE_FIRE))
                score++;
        }
        break;
    case EFFECT_WILD_CHARGE:
        if (isDoubleBattle)
        {
            if (IsBattlerAlive(BATTLE_PARTNER(battlerDef))
              && aiData->hpPercents[BATTLE_PARTNER(battlerDef)] < 12
              && aiData->abilities[BATTLE_PARTNER(battlerDef)] != (ABILITY_MAGIC_GUARD || ABILITY_SUGAR_COAT)
              && !IS_BATTLER_OF_TYPE(BATTLE_PARTNER(battlerDef), TYPE_ELECTRIC))
                score++;
        }
        break;
    case EFFECT_TOXIC_THREAD:
        IncreasePoisonScore(battlerAtk, battlerDef, move, &score);
        IncreaseStatUpScore(battlerAtk, battlerDef, STAT_SPEED, &score);
        break;
    case EFFECT_TWO_TURNS_ATTACK:
    case EFFECT_SKULL_BASH:
    case EFFECT_SOLAR_BEAM:
    case EFFECT_AIR_CANNON:
    case EFFECT_AXEL_HEEL:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_POWER_HERB)
            score += 2;
        break;
    case EFFECT_DRAGON_RUIN:
        if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_POWER_HERB)
            score += 2;
        if (IsShunyongBattle())
        {
            if (AI_DATA->hpPercents[battlerAtk] <= 10)
                score += 40;
        }
        else
        {
            // other logic here
        }
        break;
    case EFFECT_COUNTER:
        if (!IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef]) && predictedMove != MOVE_NONE)
        {
            if (gDisableStructs[battlerDef].tauntTimer != 0)
                score++;    // target must use damaging move
            if (GetMoveDamageResult(battlerDef, battlerAtk, predictedMoveSlot) >= MOVE_POWER_GOOD && GetBattleMoveSplit(predictedMove) == SPLIT_PHYSICAL)
                score += 3;
        }
        break;
    case EFFECT_MIRROR_COAT:
        if (!IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef]) && predictedMove != MOVE_NONE)
        {
            if (gDisableStructs[battlerDef].tauntTimer != 0)
                score++;    // target must use damaging move
            if (GetMoveDamageResult(battlerDef, battlerAtk, predictedMoveSlot) >= MOVE_POWER_GOOD && GetBattleMoveSplit(predictedMove) == SPLIT_SPECIAL)
                score += 3;
        }
        break;
    case EFFECT_FLAIL:
        if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_FASTER)  // Ai goes first
        {
            if (aiData->hpPercents[battlerAtk] < 20)
                score++;
            else if (aiData->hpPercents[battlerAtk] < 8)
                score += 2;
        }
        break;
    case EFFECT_SHORE_UP:
        if ((AI_GetWeather(aiData) & B_WEATHER_SANDSTORM)
          && ShouldRecover(battlerAtk, battlerDef, move, 67))
            score += 3;
        else if (ShouldRecover(battlerAtk, battlerDef, move, 50))
            score += 2;
        break;
    case EFFECT_FACADE:
        if (gBattleMons[battlerAtk].status1 & (STATUS1_POISON | STATUS1_BURN | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON | STATUS1_FROSTBITE))
            score++;
        break;
    case EFFECT_RADIOACID:
        if (gBattleMons[battlerDef].status1 & (STATUS1_POISON | STATUS1_BURN | STATUS1_TOXIC_POISON))
            score++;
        break;
    case EFFECT_HEART_CARVE:
        if (gBattleMons[battlerAtk].status2 & (STATUS2_INFATUATION))
            score += 4;
        break;
    case EFFECT_FOCUS_PUNCH:
        if (!isDoubleBattle && effectiveness > AI_EFFECTIVENESS_x0_5)
        {
            if (IsBattlerIncapacitated(battlerDef, aiData->abilities[battlerDef]))
                score += 2;
            else if (gBattleMons[battlerDef].status2 & (STATUS2_INFATUATION | STATUS2_CONFUSION))
                score++;
        }
        break;
    case EFFECT_SMELLINGSALT:
        if (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS)
            score += 2;
        break;
    case EFFECT_WAKE_UP_SLAP:
        if (gBattleMons[battlerDef].status1 & STATUS1_SLEEP_ANY)
            score += 2;
        break;
    case EFFECT_CHARM:
        if (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)
            score += 3;
        if (!ShouldLowerAttack(battlerAtk, battlerDef, aiData->abilities[battlerDef]))
            score -= 2;
        if (gBattleMons[battlerDef].statStages[STAT_ATK] < DEFAULT_STAT_STAGE)
            score--;
        else if (aiData->hpPercents[battlerAtk] <= 90)
            score--;
        if (gBattleMons[battlerDef].statStages[STAT_ATK] > 3 && !AI_RandLessThan(50))
            score -= 2;
        else if (aiData->hpPercents[battlerDef] < 70)
            score -= 2;
        break;
    case EFFECT_HEART_STAMP:
        if (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)
            score += 3;
        score += ShouldTryToFlinch(battlerAtk, battlerDef, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], move);
        break;
    case EFFECT_REVENGE:
        if (!(gBattleMons[battlerDef].status1 & STATUS1_SLEEP_ANY)
          &&  !(gBattleMons[battlerDef].status2 & (STATUS2_INFATUATION | STATUS2_CONFUSION)))
            score += 2;
        break;
    case EFFECT_ENDEAVOR:
        if (AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER)  // Opponent faster
        {
            if (aiData->hpPercents[battlerAtk] < 40)
                score++;
        }
        else if (aiData->hpPercents[battlerAtk] < 50)
        {
            score++;
        }
        break;
    case EFFECT_REVIVAL_BLESSING:
        if (GetFirstFaintedPartyIndex(battlerAtk) != PARTY_SIZE)
            score += 2;
        break;
    //case EFFECT_EXTREME_EVOBOOST: // TODO
        //break;
    //case EFFECT_SKY_DROP
        //break;
    case EFFECT_JUNGLE_HEALING:
        if (ShouldRecover(battlerAtk, battlerDef, move, 25)
         || ShouldRecover(BATTLE_PARTNER(battlerAtk), battlerDef, move, 25)
         || gBattleMons[battlerAtk].status1 & STATUS1_ANY
         || gBattleMons[BATTLE_PARTNER(battlerAtk)].status1 & STATUS1_ANY)
            score += 3;
        break;
    case EFFECT_SALT_CURE:
        if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_WATER) || IS_BATTLER_OF_TYPE(battlerDef, TYPE_STEEL))
            score += 2;
        break;
    
    // Pisces move effects
    case EFFECT_GOLD_PLAINS:
        if (IsShunyongBattle())
        {
            bool32 use = FALSE;
            s32 shunyongTotalStatStages = 0, playerLeftTotalStatStages = 0, playerRightTotalStatStages = 0;
            for (i = 0; i < NUM_BATTLE_STATS; i++)
            {
                shunyongTotalStatStages += gBattleMons[B_POSITION_OPPONENT_LEFT].statStages[i] - DEFAULT_STAT_STAGE;
                playerLeftTotalStatStages += gBattleMons[B_POSITION_PLAYER_LEFT].statStages[i] - DEFAULT_STAT_STAGE;
                playerRightTotalStatStages += gBattleMons[B_POSITION_PLAYER_RIGHT].statStages[i] - DEFAULT_STAT_STAGE;
            }
            
            // DebugPrintfLevel(MGBA_LOG_WARN, "shunyong hp pct %d", AI_DATA->hpPercents[battlerAtk]);
            
            // use at hp thresholds 75%, 50% and 25%
            if (!(gBattleStruct->shunyongGoldPlainsHpUses & (1 << 0)) && AI_DATA->hpPercents[battlerAtk] <= 75)
            {
                gBattleStruct->shunyongGoldPlainsHpUses |= (1 << 0);
                use = TRUE;
            }
            else if (!(gBattleStruct->shunyongGoldPlainsHpUses & (1 << 1)) && AI_DATA->hpPercents[battlerAtk] <= 50)
            {
                gBattleStruct->shunyongGoldPlainsHpUses |= (1 << 1);
                use = TRUE;
            }
            else if (!(gBattleStruct->shunyongGoldPlainsHpUses & (1 << 2)) && AI_DATA->hpPercents[battlerAtk] <= 25)
            {
                gBattleStruct->shunyongGoldPlainsHpUses |= (1 << 2);
                use = TRUE;
            }
            else if (gBattleResults.shunyongStatusCounter >= 3)
            {
                // use when statused for 3 turns
                gBattleResults.shunyongStatusCounter = 0;
                use = TRUE;
            }
            else if (shunyongTotalStatStages <= -6 || (playerLeftTotalStatStages >= 6 || playerRightTotalStatStages >= 6))   
            {
                // use if significantly buffed target or significantly debuffed self
                use = TRUE;
            }
            
            if (use)
                score += 40;
            else
                score = 0;
        }
        else
        {
            score = 0;
        }
        break;
    case EFFECT_MT_SPLENDOR:
        if (gBattleMons[battlerAtk].species == SPECIES_SHUNYONG_GOLDEN_OFFENSE
                && (Random() % 100) < 5) // 5% chance
        {
            score += 35; // prioritize gold plains if those conditions are met otherwise
            break;
        }
        else
        {
            score -= 20;
        }
        break;
    case EFFECT_DOWNFALL:
        if (gBattleMons[battlerAtk].status1 & STATUS1_ANY)
            score = 0;
        else if (gBattleMons[battlerAtk].species == SPECIES_SHUNYONG && (Random() % 100) < 10) // 10% chance
            score += 35;
        else
            score -= 20;
        break;
    } // move effect checks

    return score;
}

// Effects that are encouraged on the first turn of battle
static s32 AI_SetupFirstTurn(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef)
      || gBattleResults.battleTurnCounter != 0)
        return score;

    if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_SMART_SWITCHING
      && AI_WhoStrikesFirst(battlerAtk, battlerDef, move) == AI_IS_SLOWER
      && CanTargetFaintAi(battlerDef, battlerAtk)
      && GetMovePriority(battlerAtk, move) == 0)
    {
        RETURN_SCORE_MINUS(20);    // No point in setting up if you will faint. Should just switch if possible..
    }

    // check effects to prioritize first turn
    switch (gBattleMoves[move].effect)
    {
    case EFFECT_ATTACK_UP:
    case EFFECT_ATTACK_UP_USER_ALLY:
    case EFFECT_DEFENSE_UP:
    case EFFECT_SPEED_UP:
    case EFFECT_SPECIAL_ATTACK_UP:
    case EFFECT_SPECIAL_DEFENSE_UP:
    case EFFECT_ACCURACY_UP:
    case EFFECT_EVASION_UP:
    case EFFECT_ATTACK_DOWN:
    case EFFECT_DEFENSE_DOWN:
    case EFFECT_SPEED_DOWN:
    case EFFECT_SPECIAL_ATTACK_DOWN:
    case EFFECT_SPECIAL_DEFENSE_DOWN:
    case EFFECT_ACCURACY_DOWN:
    case EFFECT_EVASION_DOWN:
    case EFFECT_CONVERSION:
    case EFFECT_LIGHT_SCREEN:
    case EFFECT_FOCUS_ENERGY:
    case EFFECT_CONFUSE:
    case EFFECT_ATTACK_UP_2:
    case EFFECT_DEFENSE_UP_2:
    case EFFECT_DEFENSE_UP_3:
    case EFFECT_SPEED_UP_2:
    case EFFECT_SPECIAL_ATTACK_UP_2:
    case EFFECT_SPECIAL_ATTACK_UP_3:
    case EFFECT_SPECIAL_DEFENSE_UP_2:
    case EFFECT_ACCURACY_UP_2:
    case EFFECT_EVASION_UP_2:
    case EFFECT_GREEN_GUISE:
    case EFFECT_ATTACK_DOWN_2:
    case EFFECT_DEFENSE_DOWN_2:
    case EFFECT_SPEED_DOWN_2:
    case EFFECT_SPECIAL_ATTACK_DOWN_2:
    case EFFECT_SPECIAL_DEFENSE_DOWN_2:
    case EFFECT_ACCURACY_DOWN_2:
    case EFFECT_EVASION_DOWN_2:
    case EFFECT_REFLECT:
    case EFFECT_POISON:
    case EFFECT_PARALYZE:
    case EFFECT_SUBSTITUTE:
    case EFFECT_LEECH_SEED:
    case EFFECT_MINIMIZE:
    case EFFECT_CURSE:
    case EFFECT_SWAGGER:
    case EFFECT_CAMOUFLAGE:
    case EFFECT_YAWN:
    case EFFECT_DEFENSE_CURL:
    case EFFECT_TORMENT:
    case EFFECT_FLATTER:
    case EFFECT_WILL_O_WISP:
    case EFFECT_GLACIATE:
    case EFFECT_INGRAIN:
    case EFFECT_IMPRISON:
    case EFFECT_TEETER_DANCE:
    case EFFECT_TICKLE:
    case EFFECT_COSMIC_POWER:
    case EFFECT_BULK_UP:
    case EFFECT_CALM_MIND:
    case EFFECT_ACUPRESSURE:
    case EFFECT_AUTOTOMIZE:
    case EFFECT_SHIFT_GEAR:
    case EFFECT_VIGOR_ROOT:
    case EFFECT_SHELL_SMASH:
    case EFFECT_GROWTH:
    case EFFECT_SUN_BASK:
    case EFFECT_QUIVER_DANCE:
    case EFFECT_ATTACK_SPATK_UP:
    case EFFECT_POWER_SWAP:
    case EFFECT_ATTACK_ACCURACY_UP:
    case EFFECT_PSYCHIC_TERRAIN:
    case EFFECT_GRASSY_TERRAIN:
    case EFFECT_ELECTRIC_TERRAIN:
    case EFFECT_MISTY_TERRAIN:
    case EFFECT_STEALTH_ROCK:
    case EFFECT_TOXIC_SPIKES:
    case EFFECT_TRICK_ROOM:
    case EFFECT_WONDER_ROOM:
    case EFFECT_MAGIC_ROOM:
    case EFFECT_TAILWIND:
    case EFFECT_DRAGON_DANCE:
    case EFFECT_NO_RETREAT:
    case EFFECT_CLANGOROUS_SOUL:
    case EFFECT_TIDY_UP:
    case EFFECT_STICKY_WEB:
    case EFFECT_RAIN_DANCE:
    case EFFECT_SUNNY_DAY:
    case EFFECT_SANDSTORM:
    case EFFECT_HAIL:
    case EFFECT_SNOWSCAPE:
    case EFFECT_GEOMANCY:
    case EFFECT_VICTORY_DANCE:
    case EFFECT_HIT_SET_ENTRY_HAZARD:
    case EFFECT_CHILLY_AIR:
    case EFFECT_FILLET_AWAY:
    case EFFECT_CHILLY_RECEPTION:
    case EFFECT_DRAGON_CHEER:
    case EFFECT_SPIDER_WEB:
    case EFFECT_EERIE_IMPULSE:
    case EFFECT_FLASH:
    case EFFECT_CHARM:
    case EFFECT_MEDITATE:
    case EFFECT_CINDER_TWIRL:
    case EFFECT_CINDER_DRILL:
    case EFFECT_SILENCE:
    case EFFECT_VEXING_KI:
    case EFFECT_WARM_WELCOME:
    case EFFECT_SCORP_FANG:
    case EFFECT_RECOIL_50_HAZARD:
    case EFFECT_TERRORIZE:
    case EFFECT_DEFENSE_DOWN_HIT_2:
    case EFFECT_TICK_TACK:
    case EFFECT_DEEP_GAZE:
    case EFFECT_ENERVATOR:
    case EFFECT_HEAVY_CELL:
    case EFFECT_COTTON_SPORE:
    case EFFECT_FLORESCENCE:
    case EFFECT_SPIRIT_AWAY:
    case EFFECT_PHANTASM:
    case EFFECT_SNAPBLOSSOM:
    case EFFECT_DANCE_MANIA:
    case EFFECT_SPEED_UP_USER_ALLY:
    case EFFECT_FEATHER_DANCE:
    case EFFECT_STUN_SPORE:
    case EFFECT_FROST_NOVA:
    case EFFECT_SMOG:
    case EFFECT_POISON_POWDER:
    case EFFECT_KINESIS:
    case EFFECT_ACID_ARMOR:
    case EFFECT_MAGIC_POWDER:
    case EFFECT_HUNKER_DOWN:
    case EFFECT_SYRUP_BOMB:
    case EFFECT_POWDER:
    case EFFECT_MIST:
    case EFFECT_WORRY_SEED:
    case EFFECT_LUCKY_CHANT:
    case EFFECT_MAGNET_RISE:
    case EFFECT_OCTOLOCK:
        score += 2;
        break;
    case EFFECT_CORROSIVE_GAS:
        score += 8;
        break;
    default:
        break;
    }

    return score;
}

// Adds score bonus to 'riskier' move effects and high crit moves
static s32 AI_Risky(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
        return score;

    if (gBattleMoves[move].highCritRatio)
        score += 2;

    switch (gBattleMoves[move].effect)
    {
    case EFFECT_SLEEP:
    case EFFECT_DARK_VOID:
    case EFFECT_EXPLOSION:
    case EFFECT_MIRROR_MOVE:
    case EFFECT_OHKO:
    case EFFECT_CONFUSE:
    case EFFECT_METRONOME:
    case EFFECT_PSYWAVE:
    case EFFECT_COUNTER:
    case EFFECT_DESTINY_BOND:
    case EFFECT_SWAGGER:
    case EFFECT_ATTRACT:
    case EFFECT_PRESENT:
    case EFFECT_ALL_STATS_UP_HIT:
    case EFFECT_BELLY_DRUM:
    case EFFECT_FILLET_AWAY:
    case EFFECT_MIRROR_COAT:
    case EFFECT_FOCUS_PUNCH:
    case EFFECT_REVENGE:
    case EFFECT_TEETER_DANCE:
    case EFFECT_FICKLE_BEAM:
    case EFFECT_ALL_STATS_UP_2_HIT:
    case EFFECT_SILVER_WIND:
    case EFFECT_FLASH:
    case EFFECT_MAGNITUDE:
    case EFFECT_FEAR_FACTOR:
    case EFFECT_DRAGON_POKER:
    case EFFECT_LONE_SHARK:
    case EFFECT_ALL_STATS_DOWN_HIT:
    case EFFECT_ALL_STATS_UP_2_HIT_FOE:
    case EFFECT_SLEEP_POWDER:
    case EFFECT_BOUNDARY:
    case EFFECT_IGNITION:
    case EFFECT_GATTLING_PINS:
    case EFFECT_SURPRISE_EGG:
    case EFFECT_CANNONADE:
    case EFFECT_STALAG_BLAST:
    case EFFECT_HIGH_ROLL_HIT:
    case EFFECT_SPINDA_SWING:
    case EFFECT_DRAGON_CLAW:
    case EFFECT_TRI_ATTACK:
    case EFFECT_VITAL_THROW:
    case EFFECT_TRIPLE_KICK:
    case EFFECT_FUTURE_SIGHT:
    case EFFECT_DIRE_CLAW:
        if (Random() & 1)
            score += 2;
        break;
    default:
        break;
    }

    return score;
}

// Adds score bonus to best powered move
static s32 AI_PreferStrongestMove(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
        return score;

    if (GetMoveDamageResult(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex) == MOVE_POWER_BEST)
        score += 2;

    return score;
}

// Prefers moves that are good for baton pass
static s32 AI_PreferBatonPass(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    u32 i;

    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef)
      || CountUsablePartyMons(battlerAtk) == 0
      || GetMoveDamageResult(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex) != MOVE_POWER_OTHER
      || !HasMoveEffect(battlerAtk, EFFECT_BATON_PASS)
      || IsBattlerTrapped(battlerAtk, TRUE))
        return score;

    if (IsStatRaisingEffect(gBattleMoves[move].effect))
    {
        if (gBattleResults.battleTurnCounter == 0)
            score += 5;
        else if (AI_DATA->hpPercents[battlerAtk] < 60)
            score -= 10;
        else
            score++;
    }

    // other specific checks
    switch (gBattleMoves[move].effect)
    {
    case EFFECT_INGRAIN:
        if (!(gStatuses3[battlerAtk] & STATUS3_ROOTED))
            score += 2;
        else if (!(gBattleMons[battlerAtk].status1 & STATUS1_BLOOMING))
            score += 2;
        else 
            score -= 2;
        break;
    case EFFECT_AQUA_RING:
        if (!(gStatuses3[battlerAtk] & STATUS3_AQUA_RING))
            score += 2;
        break;
    case EFFECT_HEARTHWARM:
        if (!(gStatuses4[battlerAtk] & STATUS4_HEARTHWARM))
            score += 2;
        break;
    case EFFECT_PROTECT:
        if (gLastMoves[battlerAtk] == MOVE_PROTECT || gLastMoves[battlerAtk] == MOVE_DETECT)
            score -= 2;
        else
            score += 2;
        break;
    case EFFECT_BATON_PASS:
        for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
        {
            IncreaseStatUpScore(battlerAtk, battlerDef, i, &score);
        }
        if (gStatuses3[battlerAtk] & (STATUS3_ROOTED | STATUS3_AQUA_RING))
            score += 2;
        if (gStatuses3[battlerAtk] & STATUS3_LEECHSEED)
            score -= 3;
        break;
    default:
        break;
    }

    return score;
}

static s32 AI_HPAware(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    u32 effect = gBattleMoves[move].effect;
    u32 moveType = gBattleMoves[move].type;

    SetTypeBeforeUsingMove(move, battlerAtk);
    GET_MOVE_TYPE(move, moveType);

    if (IS_TARGETING_PARTNER(battlerAtk, battlerDef))
    {
        if ((effect == EFFECT_HEAL_PULSE || effect == EFFECT_HIT_ENEMY_HEAL_ALLY || effect == EFFECT_TRICK_OR_TREAT || effect == EFFECT_FLORAL_HEALING)
         || (moveType == TYPE_ELECTRIC && AI_DATA->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_VOLT_ABSORB)
         || (moveType == TYPE_GROUND && AI_DATA->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_EARTH_EATER)
         || (moveType == TYPE_WATER && (AI_DATA->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_DRY_SKIN || AI_DATA->abilities[BATTLE_PARTNER(battlerAtk)] == ABILITY_WATER_ABSORB)))
        {
            if (gStatuses3[battlerDef] & STATUS3_HEAL_BLOCK)
                return 0;

            if (CanTargetFaintAi(FOE(battlerAtk), BATTLE_PARTNER(battlerAtk))
              || (CanTargetFaintAi(BATTLE_PARTNER(FOE(battlerAtk)), BATTLE_PARTNER(battlerAtk))))
                score--;

            if (AI_DATA->hpPercents[battlerDef] <= 50)
                score++;
        }
    }
    else
    {
        // Consider AI HP
        if (AI_DATA->hpPercents[battlerAtk] > 70)
        {
            // high hp
            switch (effect)
            {
            case EFFECT_EXPLOSION:
            case EFFECT_RESTORE_HP:
            case EFFECT_HEAL_ORDER:
            case EFFECT_REST:
            case EFFECT_DESTINY_BOND:
            case EFFECT_FLAIL:
            case EFFECT_ENDURE:
            case EFFECT_MORNING_SUN:
            case EFFECT_SYNTHESIS:
            case EFFECT_MOONLIGHT:
            case EFFECT_SHORE_UP:
            case EFFECT_SOFTBOILED:
            case EFFECT_ROOST:
            case EFFECT_MEMENTO:
            case EFFECT_GRUDGE:
            case EFFECT_COLD_MEND:
            case EFFECT_DECAY_BEAM:
            case EFFECT_CRITICAL_REPAIR:
                score -= 4;
                break;
            case EFFECT_SPIRIT_AWAY:
                score += 1;
                break;
            case EFFECT_RESERVOIR:
                score--;
                break;
            default:
                break;
            }
        }
        else if (AI_DATA->hpPercents[battlerAtk] > 50)
        {
            switch (effect)
            {
                case EFFECT_TICK_TACK:
                case EFFECT_SPIRIT_AWAY:
                    score += 2;
                    break;

                default:
                    break;
            }
        }
        else if (AI_DATA->hpPercents[battlerAtk] > 30)
        {
            // med hp
            if (IsStatRaisingEffect(effect) || IsStatLoweringEffect(effect))
                score -= 2;

            switch (effect)
            {
            case EFFECT_EXPLOSION:
            case EFFECT_BIDE:
            case EFFECT_CONVERSION:
            case EFFECT_LIGHT_SCREEN:
            case EFFECT_MIST:
            case EFFECT_FOCUS_ENERGY:
            case EFFECT_CONVERSION_2:
            case EFFECT_SAFEGUARD:
            case EFFECT_BELLY_DRUM:
            case EFFECT_FILLET_AWAY:
            case EFFECT_DRAGON_CHEER:
            case EFFECT_SILENCE:
            case EFFECT_IGNITION:
            case EFFECT_STALAG_BLAST:
                score -= 4;
                break;
            case EFFECT_LONE_SHARK:
            case EFFECT_GREEN_GUISE:
                score -= 1;
                break;
            default:
                break;
            }
        }
        else
        {
            // low hp
            if (IsStatRaisingEffect(effect) || IsStatLoweringEffect(effect))
                score -= 2;

            // check other discouraged low hp effects
            switch (effect)
            {
            case EFFECT_BIDE:
            case EFFECT_CONVERSION:
            case EFFECT_REFLECT:
            case EFFECT_LIGHT_SCREEN:
            case EFFECT_AURORA_VEIL:
            case EFFECT_BABY_BLUES:
            case EFFECT_MIST:
            case EFFECT_FOCUS_ENERGY:
            case EFFECT_RAGE:
            case EFFECT_CONVERSION_2:
            case EFFECT_LOCK_ON:
            case EFFECT_SAFEGUARD:
            case EFFECT_BELLY_DRUM:
            case EFFECT_FILLET_AWAY:
            case EFFECT_PSYCH_UP:
            case EFFECT_MIRROR_COAT:
            case EFFECT_SOLAR_BEAM:
            case EFFECT_TWO_TURNS_ATTACK:
            case EFFECT_ERUPTION:
            case EFFECT_TICKLE:
            case EFFECT_SUNNY_DAY:
            case EFFECT_SANDSTORM:
            case EFFECT_HAIL:
            case EFFECT_SNOWSCAPE:
            case EFFECT_RAIN_DANCE:
            case EFFECT_CHILLY_RECEPTION:
            case EFFECT_DRAGON_CHEER:
            case EFFECT_SILENCE:
            case EFFECT_WARM_WELCOME:
            case EFFECT_RECOIL_50_HAZARD:
            case EFFECT_GIANTS_SPEAR:
            case EFFECT_ENERVATOR:
            case EFFECT_IGNITION:
            case EFFECT_AIR_CANNON:
            case EFFECT_MIND_READER:
            case EFFECT_STALAG_BLAST:
                score -= 6;
                break;
            case EFFECT_GREEN_GUISE:
            case EFFECT_LONE_SHARK:
                score -= 3;
                break;
            case EFFECT_SPIRIT_AWAY:
                score += 3;
                break;
            default:
                break;
            }
        }
    }

    // consider target HP
    if (CanIndexMoveFaintTarget(battlerAtk, battlerDef, AI_THINKING_STRUCT->movesetIndex, 0))
    {
        score += 2;
    }
    else
    {
        if (AI_DATA->hpPercents[battlerDef] > 70)
        {
            // high HP
            switch (effect)
            {
            case EFFECT_ALL_STATS_UP_2_HIT_FOE:
                score -= 2;
                break;
            case EFFECT_TICK_TACK:
                score += 3;
                break;
            default:
                break;
            }
        }
        else if (AI_DATA->hpPercents[battlerDef] > 30)
        {
            // med HP - check discouraged effects
            switch (effect)
            {
            case EFFECT_ATTACK_UP:
            case EFFECT_MAGNET_RISE:
            case EFFECT_ATTACK_UP_USER_ALLY:
            case EFFECT_DEFENSE_UP:
            case EFFECT_SPEED_UP:
            case EFFECT_SPECIAL_ATTACK_UP:
            case EFFECT_SPECIAL_DEFENSE_UP:
            case EFFECT_ACCURACY_UP:
            case EFFECT_EVASION_UP:
            case EFFECT_ATTACK_DOWN:
            case EFFECT_DEFENSE_DOWN:
            case EFFECT_SPEED_DOWN:
            case EFFECT_SPECIAL_ATTACK_DOWN:
            case EFFECT_SPECIAL_DEFENSE_DOWN:
            case EFFECT_ACCURACY_DOWN:
            case EFFECT_EVASION_DOWN:
            case EFFECT_MIST:
            case EFFECT_FOCUS_ENERGY:
            case EFFECT_ATTACK_UP_2:
            case EFFECT_DEFENSE_UP_2:
            case EFFECT_SPEED_UP_2:
            case EFFECT_SPECIAL_ATTACK_UP_2:
            case EFFECT_SPECIAL_DEFENSE_UP_2:
            case EFFECT_ACCURACY_UP_2:
            case EFFECT_EVASION_UP_2:
            case EFFECT_ATTACK_DOWN_2:
            case EFFECT_DEFENSE_DOWN_2:
            case EFFECT_SPEED_DOWN_2:
            case EFFECT_SPECIAL_ATTACK_DOWN_2:
            case EFFECT_SPECIAL_DEFENSE_DOWN_2:
            case EFFECT_ACCURACY_DOWN_2:
            case EFFECT_EVASION_DOWN_2:
            case EFFECT_POISON:
            case EFFECT_PAIN_SPLIT:
            case EFFECT_PERISH_SONG:
            case EFFECT_SAFEGUARD:
            case EFFECT_TICKLE:
            case EFFECT_COSMIC_POWER:
            case EFFECT_BULK_UP:
            case EFFECT_CALM_MIND:
            case EFFECT_DRAGON_DANCE:
            case EFFECT_NO_RETREAT:
            case EFFECT_CLANGOROUS_SOUL:        
            case EFFECT_TIDY_UP:
            case EFFECT_DEFENSE_UP_3:
            case EFFECT_SPECIAL_ATTACK_UP_3:
            case EFFECT_CHILLY_AIR:
            case EFFECT_DRAGON_CHEER:
            case EFFECT_SPIDER_WEB:
            case EFFECT_OCTOLOCK:
            case EFFECT_EERIE_IMPULSE:
            case EFFECT_CHARM:
            case EFFECT_MEDITATE:
            case EFFECT_TERRORIZE:
            case EFFECT_ENERVATOR:
            case EFFECT_TRAILBLAZE:
            case EFFECT_COTTON_SPORE:
            case EFFECT_SPEED_UP_USER_ALLY:
            case EFFECT_FEATHER_DANCE:
            case EFFECT_POISON_POWDER:
            case EFFECT_ACID_ARMOR:
            case EFFECT_POWDER:
                score -= 2;
                break;
            case EFFECT_GREEN_GUISE:
                score -= 1;
                break;
            default:
                break;
            }
        }
        else
        {
            // low HP
            if (IS_MOVE_STATUS(move))
                score -= 2; // don't use status moves if target is at low health
        }
    }

    return score;
}

static void AI_Flee(void)
{
    AI_THINKING_STRUCT->aiAction |= (AI_ACTION_DONE | AI_ACTION_FLEE | AI_ACTION_DO_NOT_ATTACK);
}

static void AI_Watch(void)
{
    AI_THINKING_STRUCT->aiAction |= (AI_ACTION_DONE | AI_ACTION_WATCH | AI_ACTION_DO_NOT_ATTACK);
}

// Roaming pokemon logic
static s32 AI_Roaming(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    if (IsBattlerTrapped(battlerAtk, FALSE))
        return score;

    AI_Flee();
    return score;
}

// Safari pokemon logic
static s32 AI_Safari(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    u32 safariFleeRate = gBattleStruct->safariEscapeFactor * 5; // Safari flee rate, from 0-20.

    if ((Random() % 100) < safariFleeRate)
        AI_Flee();
    else
        AI_Watch();

    return score;
}

// First battle logic
static s32 AI_FirstBattle(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    if (AI_DATA->hpPercents[battlerDef] <= 20)
        AI_Flee();

    return score;
}
