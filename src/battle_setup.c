#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "battle_transition.h"
#include "main.h"
#include "task.h"
#include "safari_zone.h"
#include "script.h"
#include "event_data.h"
#include "metatile_behavior.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "random.h"
#include "starter_choose.h"
#include "script_pokemon_util.h"
#include "palette.h"
#include "window.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "tv.h"
#include "trainer_see.h"
#include "field_message_box.h"
#include "sound.h"
#include "strings.h"
#include "trainer_hill.h"
#include "secret_base.h"
#include "string_util.h"
#include "overworld.h"
#include "field_weather.h"
#include "battle_tower.h"
#include "gym_leader_rematch.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "field_control_avatar.h"
#include "mirage_tower.h"
#include "field_screen_effect.h"
#include "data.h"
#include "constants/battle_frontier.h"
#include "constants/battle_setup.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "constants/map_types.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"
#include "constants/rgb.h"

enum {
    TRANSITION_TYPE_NORMAL,
    TRANSITION_TYPE_CAVE,
    TRANSITION_TYPE_FLASH,
    TRANSITION_TYPE_WATER,
};

enum {
    TRAINER_PARAM_LOAD_VAL_8BIT,
    TRAINER_PARAM_LOAD_VAL_16BIT,
    TRAINER_PARAM_LOAD_VAL_32BIT,
    TRAINER_PARAM_CLEAR_VAL_8BIT,
    TRAINER_PARAM_CLEAR_VAL_16BIT,
    TRAINER_PARAM_CLEAR_VAL_32BIT,
    TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR,
};

struct TrainerBattleParameter
{
    void *varPtr;
    u8 ptrType;
};

// this file's functions
static void DoBattlePikeWildBattle(void);
static void DoSafariBattle(void);
static void DoStandardWildBattle(bool32 isDouble);
static void CB2_EndWildBattle(void);
static void CB2_EndScriptedWildBattle(void);
static void TryUpdateGymLeaderRematchFromWild(void);
static void TryUpdateGymLeaderRematchFromTrainer(void);
static void CB2_GiveStarter(void);
static void CB2_StartFirstBattle(void);
static void CB2_EndFirstBattle(void);
static void CB2_EndTrainerBattle(void);
static bool32 IsPlayerDefeated(u32 battleOutcome);
#if FREE_MATCH_CALL == FALSE
static u16 GetRematchTrainerId(u16 trainerId);
#endif //FREE_MATCH_CALL
static void RegisterTrainerInMatchCall(void);
static void HandleRematchVarsOnBattleEnd(void);
static const u8 *GetIntroSpeechOfApproachingTrainer(void);
static const u8 *GetTrainerCantBattleSpeech(void);

EWRAM_DATA static u16 sTrainerBattleMode = 0;
EWRAM_DATA u16 gTrainerBattleOpponent_A = 0;
EWRAM_DATA u16 gTrainerBattleOpponent_B = 0;
EWRAM_DATA u16 gPartnerTrainerId = 0;
EWRAM_DATA static u16 sTrainerObjectEventLocalId = 0;
EWRAM_DATA static u8 *sTrainerAIntroSpeech = NULL;
EWRAM_DATA static u8 *sTrainerBIntroSpeech = NULL;
EWRAM_DATA static u8 *sTrainerADefeatSpeech = NULL;
EWRAM_DATA static u8 *sTrainerBDefeatSpeech = NULL;
EWRAM_DATA static u8 *sTrainerVictorySpeech = NULL;
EWRAM_DATA static u8 *sTrainerCannotBattleSpeech = NULL;
EWRAM_DATA static u8 *sTrainerBattleEndScript = NULL;
EWRAM_DATA static u8 *sTrainerABattleScriptRetAddr = NULL;
EWRAM_DATA static u8 *sTrainerBBattleScriptRetAddr = NULL;
EWRAM_DATA static bool8 sShouldCheckTrainerBScript = FALSE;
EWRAM_DATA static u8 sNoOfPossibleTrainerRetScripts = 0;

// The first transition is used if the enemy pokemon are lower level than our pokemon.
// Otherwise, the second transition is used.
static const u8 sBattleTransitionTable_Wild[][2] =
{
    [TRANSITION_TYPE_NORMAL] = {B_TRANSITION_SLICE,          B_TRANSITION_WHITE_BARS_FADE},
    [TRANSITION_TYPE_CAVE]   = {B_TRANSITION_CLOCKWISE_WIPE, B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_FLASH]  = {B_TRANSITION_BLUR,           B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_WATER]  = {B_TRANSITION_WAVE,           B_TRANSITION_RIPPLE},
};

static const u8 sBattleTransitionTable_Trainer[][2] =
{
    [TRANSITION_TYPE_NORMAL] = {B_TRANSITION_POKEBALLS_TRAIL, B_TRANSITION_ANGLED_WIPES},
    [TRANSITION_TYPE_CAVE]   = {B_TRANSITION_SHUFFLE,         B_TRANSITION_BIG_POKEBALL},
    [TRANSITION_TYPE_FLASH]  = {B_TRANSITION_BLUR,            B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_WATER]  = {B_TRANSITION_SWIRL,           B_TRANSITION_RIPPLE},
};

// Battle Frontier (excluding Pyramid and Dome, which have their own tables below)
static const u8 sBattleTransitionTable_BattleFrontier[] =
{
    B_TRANSITION_FRONTIER_LOGO_WIGGLE,
    B_TRANSITION_FRONTIER_LOGO_WAVE,
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_CIRCLES_MEET,
    B_TRANSITION_FRONTIER_CIRCLES_CROSS,
    B_TRANSITION_FRONTIER_CIRCLES_ASYMMETRIC_SPIRAL,
    B_TRANSITION_FRONTIER_CIRCLES_SYMMETRIC_SPIRAL,
    B_TRANSITION_FRONTIER_CIRCLES_MEET_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_CROSS_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_ASYMMETRIC_SPIRAL_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_SYMMETRIC_SPIRAL_IN_SEQ
};

static const u8 sBattleTransitionTable_BattlePyramid[] =
{
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_SQUARES_SPIRAL
};

static const u8 sBattleTransitionTable_BattleDome[] =
{
    B_TRANSITION_FRONTIER_LOGO_WIGGLE,
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_SQUARES_SPIRAL
};

static const struct TrainerBattleParameter sOrdinaryBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sContinueScriptBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sDoubleBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sOrdinaryNoIntroBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sContinueScriptDoubleBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sTrainerBOrdinaryBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_B,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerBIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBDefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBBattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sTrainerBContinueScriptBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_B,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerBIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBDefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBBattleScriptRetAddr, TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

// two trainers, each with a defeat speech
static const struct TrainerBattleParameter sTrainerTwoTrainerBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_CLEAR_VAL_16BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&gTrainerBattleOpponent_B,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerBIntroSpeech,         TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBDefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBBattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

#define REMATCH(trainer1, trainer2, trainer3, trainer4, trainer5, map)  \
{                                                                       \
    .trainerIds = {trainer1, trainer2, trainer3, trainer4, trainer5},   \
    .mapGroup = MAP_GROUP(map),                                         \
    .mapNum = MAP_NUM(map),                                             \
}

const struct RematchTrainer gRematchTable[REMATCH_TABLE_ENTRIES] =
{
    //[REMATCH_ROSE] = REMATCH(TRAINER_P_HASPAROTH, TRAINER_P_SEBASTIAN, TRAINER_P_DUNDEE, TRAINER_P_MOKA, TRAINER_P_WOODS, ROUTE118),
    //[REMATCH_ANDRES] = REMATCH(TRAINER_ANDRES_1, TRAINER_ANDRES_2, TRAINER_ANDRES_3, TRAINER_ANDRES_4, TRAINER_ANDRES_5, ROUTE105),
    //[REMATCH_DUSTY] = REMATCH(TRAINER_P_FAUNA, TRAINER_P_SKEETER, TRAINER_P_JAJA, TRAINER_P_JANE, TRAINER_P_JO_AND_JO, ROUTE111),
    //[REMATCH_LOLA] = REMATCH(TRAINER_P_PANDOU_1, TRAINER_P_RISE, TRAINER_P_YU, TRAINER_P_GEIGER, TRAINER_P_YORK, ROUTE109),
    //[REMATCH_RICKY] = REMATCH(TRAINER_P_RIKA, TRAINER_P_RAY_1, TRAINER_P_PLANCK, TRAINER_P_LEGRI, TRAINER_P_SPITZER, ROUTE109),
    //[REMATCH_LILA_AND_ROY] = REMATCH(TRAINER_P_RAY_6, TRAINER_P_RAY_7, TRAINER_P_TABITHA_3, TRAINER_P_MATT_3, TRAINER_P_COURTNEY_1, ROUTE124),
    //[REMATCH_CRISTIN] = REMATCH(TRAINER_CRISTIN_1, TRAINER_CRISTIN_2, TRAINER_CRISTIN_3, TRAINER_CRISTIN_4, TRAINER_CRISTIN_5, ROUTE121),
    //[REMATCH_BROOKE] = REMATCH(TRAINER_P_JOSUKE, TRAINER_P_JULIO, TRAINER_P_HOMER, TRAINER_P_MARGE, TRAINER_P_SHALA, ROUTE111),
    //[REMATCH_WILTON] = REMATCH(TRAINER_P_S_STEVEN_5, TRAINER_P_RAINE, TRAINER_P_SKYE, TRAINER_P_GUUNTHER, TRAINER_P_AVA, ROUTE111),
    //[REMATCH_VALERIE] = REMATCH(TRAINER_P_INDA, TRAINER_P_LANDON, TRAINER_P_TERRA, TRAINER_P_OZONE_SEAN, TRAINER_P_MARINA, MT_PYRE_6F),
    //[REMATCH_CINDY] = REMATCH(TRAINER_P_OZONE_MATT_1, TRAINER_P_RITA, TRAINER_P_FELIX, TRAINER_P_RAN, TRAINER_P_BIG_HERTZ, ROUTE104),
    //[REMATCH_THALIA] = REMATCH(TRAINER_P_KUMORI, TRAINER_THALIA_2, TRAINER_THALIA_3, TRAINER_THALIA_4, TRAINER_THALIA_5, ABANDONED_SHIP_ROOMS_1F),
    //[REMATCH_JESSICA] = REMATCH(TRAINER_P_GARNET, TRAINER_P_LARS, TRAINER_P_DARCIE, TRAINER_P_WYNTON, TRAINER_P_PANDOU_2, ROUTE121),
    //[REMATCH_WINSTON] = REMATCH(TRAINER_P_RAMI, TRAINER_P_CAROLINA, TRAINER_P_BETTY, TRAINER_P_HAZAKURA, TRAINER_P_MIA, ROUTE104),
    //[REMATCH_STEVE] = REMATCH(TRAINER_P_MAYA, TRAINER_P_PEARL, TRAINER_P_NEKO, TRAINER_P_AYUMU, TRAINER_P_DEACON, ROUTE114),
    //[REMATCH_TONY] = REMATCH(TRAINER_P_REIMU, TRAINER_P_MADDY_AND_CROSS, TRAINER_P_HECTOR, TRAINER_P_PATRASCHE, TRAINER_P_AMIRA, ROUTE107),
    //[REMATCH_NOB] = REMATCH(TRAINER_P_JUONO, TRAINER_P_WALLPRESS, TRAINER_P_TAWNY, TRAINER_P_JAIDEN, TRAINER_P_GRISELDIS, ROUTE115),
    //[REMATCH_KOJI] = REMATCH(TRAINER_P_MATT_2, TRAINER_KOJI_2, TRAINER_KOJI_3, TRAINER_KOJI_4, TRAINER_KOJI_5, ROUTE127),
    //[REMATCH_FERNANDO] = REMATCH(TRAINER_P_MARISA, TRAINER_FERNANDO_2, TRAINER_FERNANDO_3, TRAINER_FERNANDO_4, TRAINER_FERNANDO_5, ROUTE123),
    //[REMATCH_DALTON] = REMATCH(TRAINER_P_GUNNESS, TRAINER_P_JASON, TRAINER_P_LEAH, TRAINER_P_LELE, TRAINER_P_PICKLE_LOU, ROUTE118),
    //[REMATCH_BERNIE] = REMATCH(TRAINER_P_DENALI, TRAINER_P_RAINIER, TRAINER_P_EVEREST, TRAINER_P_LHOTSE, TRAINER_P_GALE, ROUTE114),
    //[REMATCH_ETHAN] = REMATCH(TRAINER_P_NINA, TRAINER_P_GABBY_AND_TY_2, TRAINER_P_GABBY_AND_TY_3, TRAINER_P_GABBY_AND_TY_4, TRAINER_P_GABBY_AND_TY_5, JAGGED_PASS),
    //[REMATCH_JOHN_AND_JAY] = REMATCH(TRAINER_P_SIDNEY, TRAINER_P_LUCY, TRAINER_P_WALLY, TRAINER_P_RAY_3, TRAINER_P_RAY_4, METEOR_FALLS_1F_2R),
    //[REMATCH_JEFFREY] = REMATCH(TRAINER_P_CHLOE, TRAINER_P_FLOWERS, TRAINER_P_JAY_AND_EM, TRAINER_P_ASHE, TRAINER_P_SARA, ROUTE120),
    //[REMATCH_CAMERON] = REMATCH(TRAINER_P_MIRAI, TRAINER_P_KURENAI, TRAINER_P_SAKURAI, TRAINER_P_LARA, TRAINER_P_ERICA, ROUTE123),
    //[REMATCH_JACKI] = REMATCH(TRAINER_P_FRANK, TRAINER_P_WEINER, TRAINER_P_EVELYNN, TRAINER_P_DYNA, TRAINER_P_AUDREY, ROUTE123),
    //[REMATCH_WALTER] = REMATCH(TRAINER_P_AUDREY_II, TRAINER_P_LIBRA, TRAINER_P_BAZE, TRAINER_P_CHINZAO, TRAINER_P_MARIMAR, ROUTE121),
    //[REMATCH_KAREN] = REMATCH(TRAINER_P_IWAN, TRAINER_P_SANDY, TRAINER_P_JAN, TRAINER_P_CATT, TRAINER_P_CELIA, ROUTE116),
    //[REMATCH_JERRY] = REMATCH(TRAINER_P_JELLY, TRAINER_P_IVAN, TRAINER_P_LIBYA, TRAINER_P_CARVILLE, TRAINER_P_BOOM, ROUTE116),
    //[REMATCH_ANNA_AND_MEG] = REMATCH(TRAINER_P_DIMITRI, TRAINER_P_CLIFF_AND_ISSA, TRAINER_P_GERODE, TRAINER_P_MEZRA, TRAINER_P_LANE, ROUTE117),
    //[REMATCH_ISABEL] = REMATCH(TRAINER_P_THAD, TRAINER_P_LEELA, TRAINER_P_ICKLE, TRAINER_P_STAPH, TRAINER_P_HWARANG, ROUTE110),
    //[REMATCH_MIGUEL] = REMATCH(TRAINER_P_HEDON, TRAINER_P_GHIDORAH, TRAINER_P_GOJIRA, TRAINER_P_GAMERA, TRAINER_P_SANTO, ROUTE103),
    //[REMATCH_TIMOTHY] = REMATCH(TRAINER_P_TAKESHI, TRAINER_P_BEAT, TRAINER_P_DOTTY, TRAINER_P_RELI, TRAINER_P_CASTLE, ROUTE115),
    //[REMATCH_SHELBY] = REMATCH(TRAINER_P_CY, TRAINER_P_GERTRUDE, TRAINER_P_TOOTSIE, TRAINER_P_WENDY_AND_GALE, TRAINER_P_KAKU, MT_CHIMNEY),
    //[REMATCH_CALVIN] = REMATCH(TRAINER_P_KURT, TRAINER_P_DILL, TRAINER_P_DELILAH, TRAINER_P_JIYU_AND_SHIROU, TRAINER_P_SAMUEL, ROUTE102),
    //[REMATCH_ELLIOT] = REMATCH(TRAINER_P_ADAM_AND_STEVE, TRAINER_P_HICHAEL, TRAINER_P_PENNY, TRAINER_P_JUNIOR, TRAINER_P_HICHAELSON, ROUTE106),
    //[REMATCH_ISAIAH] = REMATCH(TRAINER_P_ALEXA, TRAINER_P_PASCAL, TRAINER_P_BONZI, TRAINER_P_JELLO, TRAINER_P_LEN, ROUTE128),
    //[REMATCH_MARIA] = REMATCH(TRAINER_P_ANON, TRAINER_P_ROBIN, TRAINER_P_CHARITY, TRAINER_P_SIN, TRAINER_P_BOB, ROUTE117),
    //[REMATCH_ABIGAIL] = REMATCH(TRAINER_P_GARY, TRAINER_P_VENUS, TRAINER_P_FIGLIOSI, TRAINER_P_OLLY, TRAINER_P_POLLY, ROUTE110),
    //[REMATCH_DYLAN] = REMATCH(TRAINER_P_EDWARD, TRAINER_P_YANCY, TRAINER_P_ERNEST, TRAINER_P_LATTY, TRAINER_P_ALICE, ROUTE117),
    //[REMATCH_KATELYN] = REMATCH(TRAINER_P_DAWN, TRAINER_P_PRAG, TRAINER_P_MARK, TRAINER_P_SACRED, TRAINER_P_MANDALORE, ROUTE128),
    //[REMATCH_BENJAMIN] = REMATCH(TRAINER_P_ANA, TRAINER_P_YOKO, TRAINER_P_FLATS, TRAINER_P_PHILLIP, TRAINER_P_NUE, ROUTE110),
    //[REMATCH_PABLO] = REMATCH(TRAINER_P_BIXBY, TRAINER_PABLO_2, TRAINER_PABLO_3, TRAINER_PABLO_4, TRAINER_PABLO_5, ROUTE126),
    //[REMATCH_NICOLAS] = REMATCH(TRAINER_P_BEAST, TRAINER_P_KAISENAT, TRAINER_P_CHAD, TRAINER_P_CHAZ, TRAINER_P_BRODY, METEOR_FALLS_1F_2R),
    //[REMATCH_ROBERT] = REMATCH(TRAINER_P_DICK_AND_JANE, TRAINER_P_BARNABY, TRAINER_P_VALERIE, TRAINER_P_QUEEQUEG, TRAINER_P_JESS, ROUTE120),
    //[REMATCH_LAO] = REMATCH(TRAINER_P_NUNYA, TRAINER_P_ROSE, TRAINER_P_SANDEEP, TRAINER_P_JOAN, TRAINER_P_LUDI, ROUTE113),
    //[REMATCH_CYNDY] = REMATCH(TRAINER_P_MAGNUS, TRAINER_P_JUNEAU, TRAINER_P_ALASKA, TRAINER_P_TAHOE, TRAINER_P_HURON, ROUTE115),
    //[REMATCH_MADELINE] = REMATCH(TRAINER_P_EYRE, TRAINER_P_ALBERT, TRAINER_P_MARCEL, TRAINER_P_NESSIE, TRAINER_P_DAPHNE, ROUTE113),
    //[REMATCH_JENNY] = REMATCH(TRAINER_P_MIMI, TRAINER_P_DAHLIA, TRAINER_P_ROBERTS, TRAINER_P_BUTTERCUP, TRAINER_P_JUNE, ROUTE124),
    //[REMATCH_DIANA] = REMATCH(TRAINER_P_GREY, TRAINER_P_PI_AND_SEES, TRAINER_P_KU_AND_MORI, TRAINER_P_PERSEPHONE, TRAINER_P_XAVIER, JAGGED_PASS),
    //[REMATCH_AMY_AND_LIV] = REMATCH(TRAINER_P_NAFI, TRAINER_P_MADELINE, TRAINER_P_GUSTAVO, TRAINER_P_NEIL, TRAINER_P_BRITNEY, ROUTE103),
    //[REMATCH_ERNEST] = REMATCH(TRAINER_P_LINE, TRAINER_P_FEZZIK, TRAINER_P_JEAN_AND_JACKITT, TRAINER_P_LUNA_AND_STAR, TRAINER_P_LANCE, ROUTE125),
    //[REMATCH_CORY] = REMATCH(TRAINER_CORY_1, TRAINER_CORY_2, TRAINER_CORY_3, TRAINER_CORY_4, TRAINER_CORY_5, ROUTE108),
    //[REMATCH_EDWIN] = REMATCH(TRAINER_P_BASIL, TRAINER_P_CAMBRIA, TRAINER_P_SERLING, TRAINER_P_MARIANA, TRAINER_P_CORAL, ROUTE110),
    //[REMATCH_LYDIA] = REMATCH(TRAINER_P_GOOMBELLA, TRAINER_P_QIU, TRAINER_P_TUTU, TRAINER_P_DUCK, TRAINER_P_VIOLET, ROUTE117),
    //[REMATCH_ISAAC] = REMATCH(TRAINER_P_GUS, TRAINER_P_JEAN_PAUL, TRAINER_P_SIMONE, TRAINER_P_PLATO_AND_ARIS, TRAINER_P_DIOGENES, ROUTE117),
    //[REMATCH_GABRIELLE] = REMATCH(TRAINER_P_GRANGER, TRAINER_GABRIELLE_2, TRAINER_GABRIELLE_3, TRAINER_GABRIELLE_4, TRAINER_GABRIELLE_5, MT_PYRE_3F),
    //[REMATCH_CATHERINE] = REMATCH(TRAINER_P_INU_AND_PERSIA, TRAINER_P_JOSEPHINE, TRAINER_P_LENNY, TRAINER_P_BRIDGET, TRAINER_P_DARWIN, ROUTE119),
    //[REMATCH_JACKSON] = REMATCH(TRAINER_P_ELIZABETH, TRAINER_P_SUZUME, TRAINER_P_MIO, TRAINER_P_LEMMY, TRAINER_P_ICHI, ROUTE119),
    //[REMATCH_HALEY] = REMATCH(TRAINER_P_DANTE, TRAINER_P_ARI, TRAINER_P_SKYLER, TRAINER_P_WALTER, TRAINER_P_KNUCKLES, ROUTE104),
    //[REMATCH_JAMES] = REMATCH(TRAINER_P_GRISELDA, TRAINER_P_MORGANA, TRAINER_P_ZEPHYR, TRAINER_P_ANTHREENY, TRAINER_P_SCHULI, PETALBURG_WOODS),
    //[REMATCH_TRENT] = REMATCH(TRAINER_P_GONZEROS, TRAINER_P_ARTEMIS, TRAINER_P_SEIMAN, TRAINER_P_GARENA, TRAINER_P_GORO, ROUTE112),
    //[REMATCH_SAWYER] = REMATCH(TRAINER_SAWYER_1, TRAINER_SAWYER_2, TRAINER_SAWYER_3, TRAINER_SAWYER_4, TRAINER_SAWYER_5, MT_CHIMNEY),
    //[REMATCH_KIRA_AND_DAN] = REMATCH(TRAINER_P_ANATINA, TRAINER_P_TAIPUS, TRAINER_P_MARCELUS, TRAINER_P_DEVIA, TRAINER_P_PARPONIX, ABANDONED_SHIP_ROOMS2_1F),
    [REMATCH_WALLY_VR] = REMATCH(TRAINER_WALLY_VR_2, TRAINER_WALLY_VR_3, TRAINER_WALLY_VR_4, TRAINER_WALLY_VR_5, TRAINER_WALLY_VR_5, VICTORY_ROAD_1F),
    [REMATCH_ROXANNE] = REMATCH(TRAINER_ROXANNE_1, TRAINER_ROXANNE_2, TRAINER_ROXANNE_3, TRAINER_ROXANNE_4, TRAINER_ROXANNE_5, RUSTBORO_CITY),
    [REMATCH_BRAWLY] = REMATCH(TRAINER_BRAWLY_1, TRAINER_BRAWLY_2, TRAINER_BRAWLY_3, TRAINER_BRAWLY_4, TRAINER_BRAWLY_5, DEWFORD_TOWN),
    [REMATCH_WATTSON] = REMATCH(TRAINER_WATTSON_1, TRAINER_WATTSON_2, TRAINER_WATTSON_3, TRAINER_WATTSON_4, TRAINER_WATTSON_5, MAUVILLE_CITY),
    [REMATCH_FLANNERY] = REMATCH(TRAINER_FLANNERY_1, TRAINER_FLANNERY_2, TRAINER_FLANNERY_3, TRAINER_FLANNERY_4, TRAINER_FLANNERY_5, LAVARIDGE_TOWN),
    [REMATCH_NORMAN] = REMATCH(TRAINER_NORMAN_1, TRAINER_NORMAN_2, TRAINER_NORMAN_3, TRAINER_NORMAN_4, TRAINER_NORMAN_5, PETALBURG_CITY),
    [REMATCH_WINONA] = REMATCH(TRAINER_WINONA_1, TRAINER_WINONA_2, TRAINER_WINONA_3, TRAINER_WINONA_4, TRAINER_WINONA_5, FORTREE_CITY),
    [REMATCH_TATE_AND_LIZA] = REMATCH(TRAINER_TATE_AND_LIZA_1, TRAINER_TATE_AND_LIZA_2, TRAINER_TATE_AND_LIZA_3, TRAINER_TATE_AND_LIZA_4, TRAINER_TATE_AND_LIZA_5, MOSSDEEP_CITY),
    [REMATCH_JUAN] = REMATCH(TRAINER_JUAN_1, TRAINER_JUAN_2, TRAINER_JUAN_3, TRAINER_JUAN_4, TRAINER_JUAN_5, SOOTOPOLIS_CITY),
    [REMATCH_SIDNEY] = REMATCH(TRAINER_DO_NOT_TOUCHIE, TRAINER_DO_NOT_TOUCHIE, TRAINER_DO_NOT_TOUCHIE, TRAINER_DO_NOT_TOUCHIE, TRAINER_DO_NOT_TOUCHIE, EVER_GRANDE_CITY),
    [REMATCH_PHOEBE] = REMATCH(TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, EVER_GRANDE_CITY),
    [REMATCH_GLACIA] = REMATCH(TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, EVER_GRANDE_CITY),
    [REMATCH_DRAKE] = REMATCH(TRAINER_DRAKE, TRAINER_DRAKE, TRAINER_DRAKE, TRAINER_DRAKE, TRAINER_DRAKE, EVER_GRANDE_CITY),
    [REMATCH_WALLACE] = REMATCH(TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, EVER_GRANDE_CITY),
};

static const u16 sBadgeFlags[NUM_BADGES] =
{
    FLAG_BADGE01_GET, FLAG_BADGE02_GET, FLAG_BADGE03_GET, FLAG_BADGE04_GET,
    FLAG_BADGE05_GET, FLAG_BADGE06_GET, FLAG_BADGE07_GET, FLAG_BADGE08_GET,
};

#define tState data[0]
#define tTransition data[1]

static void Task_BattleStart(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        if (!FldEffPoison_IsActive()) // is poison not active?
        {
            BattleTransition_StartOnField(tTransition);
            ClearMirageTowerPulseBlendEffect();
            tState++; // go to case 1.
        }
        break;
    case 1:
        if (IsBattleTransitionDone() == TRUE)
        {
            CleanupOverworldWindowsAndTilemaps();
            SetMainCallback2(CB2_InitBattle);
            RestartWildEncounterImmunitySteps();
            ClearPoisonStepCounter();
            DestroyTask(taskId);
        }
        break;
    }
}

static void CreateBattleStartTask(u8 transition, u16 song)
{
    u8 taskId = CreateTask(Task_BattleStart, 1);

    gTasks[taskId].tTransition = transition;
    if (!ShouldSkipBattleMusic())
        PlayMapChosenOrBattleBGM(song);
}

static void Task_BattleStart_Debug(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        if (!FldEffPoison_IsActive()) // is poison not active?
        {
            BattleTransition_StartOnField(tTransition);
            ClearMirageTowerPulseBlendEffect();
            tState++; // go to case 1.
        }
        break;
    case 1:
        if (IsBattleTransitionDone() == TRUE)
        {
            CleanupOverworldWindowsAndTilemaps();
            SetMainCallback2(CB2_InitBattle);
            RestartWildEncounterImmunitySteps();
            ClearPoisonStepCounter();
            DestroyTask(taskId);
        }
        break;
    }
}

static void CreateBattleStartTask_Debug(u8 transition, u16 song)
{
    u8 taskId = CreateTask(Task_BattleStart_Debug, 1);

    gTasks[taskId].tTransition = transition;
    PlayMapChosenOrBattleBGM(song);
}

#undef tState
#undef tTransition

void BattleSetup_StartWildBattle(void)
{
    if (GetSafariZoneFlag())
        DoSafariBattle();
    else
        DoStandardWildBattle(FALSE);
}

void BattleSetup_StartDoubleWildBattle(void)
{
    DoStandardWildBattle(TRUE);
}

void BattleSetup_StartBattlePikeWildBattle(void)
{
    DoBattlePikeWildBattle();
}

static void DoStandardWildBattle(bool32 isDouble)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = 0;
    if (isDouble)
        gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
    if (InBattlePyramid())
    {
        VarSet(VAR_TEMP_E, 0);
        gBattleTypeFlags |= BATTLE_TYPE_PYRAMID;
    }
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void DoStandardWildBattle_Debug(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = 0;
    if (InBattlePyramid())
    {
        VarSet(VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0);
        gBattleTypeFlags |= BATTLE_TYPE_PYRAMID;
    }
    CreateBattleStartTask_Debug(GetWildBattleTransition(), 0);
    //IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    //IncrementGameStat(GAME_STAT_WILD_BATTLES);
    //IncrementDailyWildBattles();
    //TryUpdateGymLeaderRematchFromWild();
}

void BattleSetup_StartRoamerBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_ROAMER;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

static void DoSafariBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndSafariBattle;
    gBattleTypeFlags = BATTLE_TYPE_SAFARI;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
}

static void DoBattlePikeWildBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_PIKE;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

static void DoTrainerBattle(void)
{
    CreateBattleStartTask(GetTrainerBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_TRAINER_BATTLES);
    TryUpdateGymLeaderRematchFromTrainer();
}

static void DoBattlePyramidTrainerHillBattle(void)
{
    if (InBattlePyramid())
        CreateBattleStartTask(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PYRAMID), 0);
    else
        CreateBattleStartTask(GetSpecialBattleTransition(B_TRANSITION_GROUP_TRAINER_HILL), 0);

    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_TRAINER_BATTLES);
    TryUpdateGymLeaderRematchFromTrainer();
}

// Initiates battle where Wally catches Ralts
void StartWallyTutorialBattle(void)
{
    CreateMaleMon(&gEnemyParty[0], SPECIES_RALTS, 5);
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_ReturnToFieldContinueScriptPlayMapMusic;
    gBattleTypeFlags = BATTLE_TYPE_WALLY_TUTORIAL;
    CreateBattleStartTask(B_TRANSITION_SLICE, 0);
}

void BattleSetup_StartScriptedWildBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = 0;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void BattleSetup_StartScriptedDoubleWildBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_DOUBLE;

    switch (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL))
    {
    case SPECIES_SHUNYONG:
    case SPECIES_SHUNYONG_GOLDEN_OFFENSE:
        gBattleTypeFlags |= BATTLE_TYPE_SHUNYONG;
        break;
    default:
        break;
    }
    
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void BattleSetup_StartLatiBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void BattleSetup_StartLegendaryBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY;

    switch (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL))
    {
    default:
    case SPECIES_GROUDON:
        gBattleTypeFlags |= BATTLE_TYPE_GROUDON;
        CreateBattleStartTask(B_TRANSITION_GROUDON, MUS_VS_KYOGRE_GROUDON);
        break;
    case SPECIES_KYOGRE:
        gBattleTypeFlags |= BATTLE_TYPE_KYOGRE;
        CreateBattleStartTask(B_TRANSITION_KYOGRE, MUS_VS_KYOGRE_GROUDON);
        break;
    case SPECIES_RAYQUAZA:
        gBattleTypeFlags |= BATTLE_TYPE_RAYQUAZA;
        CreateBattleStartTask(B_TRANSITION_RAYQUAZA, MUS_VS_RAYQUAZA);
        break;
    case SPECIES_DEOXYS:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_RG_VS_DEOXYS);
        break;
    case SPECIES_LUGIA:
    case SPECIES_HO_OH:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_RG_VS_LEGEND);
        break;
    case SPECIES_MEW:
        CreateBattleStartTask(B_TRANSITION_GRID_SQUARES, MUS_VS_MEW);
        break;
    }

    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void StartGroudonKyogreBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY | BATTLE_TYPE_KYOGRE_GROUDON;

    if (gGameVersion == VERSION_RUBY)
        CreateBattleStartTask(B_TRANSITION_ANGLED_WIPES, MUS_VS_KYOGRE_GROUDON); // GROUDON
    else
        CreateBattleStartTask(B_TRANSITION_RIPPLE, MUS_VS_KYOGRE_GROUDON); // KYOGRE

    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void StartRegiBattle(void)
{
    u8 transitionId;
    u16 species;

    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY;

    species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES);
    switch (species)
    {
    case SPECIES_REGIROCK:
        transitionId = B_TRANSITION_REGIROCK;
        break;
    case SPECIES_REGICE:
        transitionId = B_TRANSITION_REGICE;
        break;
    case SPECIES_REGISTEEL:
        transitionId = B_TRANSITION_REGISTEEL;
        break;
    default:
        transitionId = B_TRANSITION_GRID_SQUARES;
        break;
    }
    CreateBattleStartTask(transitionId, MUS_VS_REGI);

    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

static void CB2_EndWildBattle(void)
{
    CpuFill16(0, (void *)(BG_PLTT), BG_PLTT_SIZE);
    ResetOamRange(0, 128);

    if (IsPlayerDefeated(gBattleOutcome) == TRUE && !InBattlePyramid() && !InBattlePike())
    {
        SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToField);
        gFieldCallback = FieldCB_ReturnToFieldNoScriptCheckMusic;
    }
}

static void CB2_EndScriptedWildBattle(void)
{
    CpuFill16(0, (void *)(BG_PLTT), BG_PLTT_SIZE);
    ResetOamRange(0, 128);

    if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        if (InBattlePyramid())
            SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        else
            SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
}

u8 BattleSetup_GetTerrainId(void)
{
    u16 tileBehavior;
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    tileBehavior = MapGridGetMetatileBehaviorAt(x, y);

    if (MetatileBehavior_IsTallGrass(tileBehavior))
        return BATTLE_TERRAIN_GRASS;
    if (MetatileBehavior_IsLongGrass(tileBehavior))
        return BATTLE_TERRAIN_LONG_GRASS;
    if (MetatileBehavior_IsSandOrDeepSand(tileBehavior))
        return BATTLE_TERRAIN_SAND;
    if (MetatileBehavior_IsChimneyGrass(tileBehavior))
        return BATTLE_TERRAIN_CHIMNEY_ROUTE;

    switch (gMapHeader.mapType)
    {
    case MAP_TYPE_TOWN:
    case MAP_TYPE_CITY:
    case MAP_TYPE_ROUTE:
        break;
    case MAP_TYPE_UNDERGROUND:
        if (MetatileBehavior_IsIndoorEncounter(tileBehavior))
            return BATTLE_TERRAIN_BUILDING;
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return BATTLE_TERRAIN_POND;
        return BATTLE_TERRAIN_CAVE;
    case MAP_TYPE_INDOOR:
    case MAP_TYPE_SECRET_BASE:
        return BATTLE_TERRAIN_BUILDING;
    case MAP_TYPE_UNDERWATER:
        return BATTLE_TERRAIN_UNDERWATER;
    case MAP_TYPE_SNOW_ROUTE:
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return BATTLE_TERRAIN_WATER;
        return BATTLE_TERRAIN_SNOW_ROUTE;
    case MAP_TYPE_BLOSSOM_ROUTE:
        return BATTLE_TERRAIN_BLOSSOM_ROUTE;
    case MAP_TYPE_CHIMNEY_ROUTE:
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return BATTLE_TERRAIN_WATER;
        return BATTLE_TERRAIN_CHIMNEY_ROUTE;
    case MAP_TYPE_GOLD_ROUTE:
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return BATTLE_TERRAIN_WATER;
        return BATTLE_TERRAIN_GOLD_ROUTE;
    case MAP_TYPE_WOODEN_ROUTE:
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return BATTLE_TERRAIN_WATER;
        return BATTLE_TERRAIN_DARK_AREA;
    case MAP_TYPE_SHUNYONG_ARENA:
        return BATTLE_TERRAIN_SHUNYONG;
    case MAP_TYPE_OCEAN_ROUTE:
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return BATTLE_TERRAIN_WATER;
        return BATTLE_TERRAIN_PLAIN;
    }
    if (MetatileBehavior_IsDeepOrOceanWater(tileBehavior))
        return BATTLE_TERRAIN_WATER;
    if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
        return BATTLE_TERRAIN_POND;
    if (MetatileBehavior_IsShallowFlowingWater(tileBehavior))
        return BATTLE_TERRAIN_POND;
    if (MetatileBehavior_IsMountain(tileBehavior))
        return BATTLE_TERRAIN_MOUNTAIN;
    if (MetatileBehavior_IsWooden(tileBehavior))
        return BATTLE_TERRAIN_WOODEN_ROUTE;
    if (MetatileBehavior_IsWhitePath(tileBehavior))
        return BATTLE_TERRAIN_PATH;
    if (MetatileBehavior_IsShunyongTile(tileBehavior))
        return BATTLE_TERRAIN_SHUNYONG;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
    {
        // Is BRIDGE_TYPE_POND_*?
        if (MetatileBehavior_GetBridgeType(tileBehavior) != BRIDGE_TYPE_OCEAN)
            return BATTLE_TERRAIN_POND;

        if (MetatileBehavior_IsBridgeOverWater(tileBehavior) == TRUE)
            return BATTLE_TERRAIN_WATER;
    }
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ROUTE113) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE113))
        return BATTLE_TERRAIN_SAND;
    if (GetSavedWeather() == WEATHER_SANDSTORM)
        return BATTLE_TERRAIN_SAND;

    return BATTLE_TERRAIN_PLAIN;
}

static u8 GetBattleTransitionTypeByMap(void)
{
    u16 tileBehavior;
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    tileBehavior = MapGridGetMetatileBehaviorAt(x, y);

    if (GetFlashLevel())
        return TRANSITION_TYPE_FLASH;

    if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
        return TRANSITION_TYPE_WATER;

    switch (gMapHeader.mapType)
    {
    case MAP_TYPE_UNDERGROUND:
        return TRANSITION_TYPE_CAVE;
    case MAP_TYPE_UNDERWATER:
        return TRANSITION_TYPE_WATER;
    default:
        return TRANSITION_TYPE_NORMAL;
    }
}

static u16 GetSumOfPlayerPartyLevel(u8 numMons)
{
    u8 sum = 0;
    int i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u32 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);

        if (species != SPECIES_EGG && species != SPECIES_NONE && GetMonData(&gPlayerParty[i], MON_DATA_HP) != 0)
        {
            sum += GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
            if (--numMons == 0)
                break;
        }
    }
    return sum;
}

static u8 GetSumOfEnemyPartyLevel(u16 opponentId, u8 numMons)
{
    u8 i;
    u8 sum;
    u32 count = numMons;
    const struct TrainerMon *party;

    if (gTrainers[opponentId].partySize < count)
        count = gTrainers[opponentId].partySize;

    sum = 0;

    party = gTrainers[opponentId].party;
    for (i = 0; i < count; i++)
        sum += party[i].lvl;

    return sum;
}

u8 GetWildBattleTransition(void)
{
    u8 transitionType = GetBattleTransitionTypeByMap();
    u8 enemyLevel = GetMonData(&gEnemyParty[0], MON_DATA_LEVEL);
    u8 playerLevel = GetSumOfPlayerPartyLevel(1);

    if (enemyLevel < playerLevel)
    {
        if (InBattlePyramid())
            return B_TRANSITION_BLUR;
        else
            return sBattleTransitionTable_Wild[transitionType][0];
    }
    else
    {
        if (InBattlePyramid())
            return B_TRANSITION_GRID_SQUARES;
        else
            return sBattleTransitionTable_Wild[transitionType][1];
    }
}

u8 GetTrainerBattleTransition(void)
{
    u8 minPartyCount;
    u8 transitionType;
    u8 enemyLevel;
    u8 playerLevel;

    if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
        return B_TRANSITION_CHAMPION;

    if (gTrainers[gTrainerBattleOpponent_A].doubleBattle == TRUE)
        minPartyCount = 2; // double battles always at least have 2 pokemon.
    else
        minPartyCount = 1;

    transitionType = GetBattleTransitionTypeByMap();
    enemyLevel = GetSumOfEnemyPartyLevel(gTrainerBattleOpponent_A, minPartyCount);
    playerLevel = GetSumOfPlayerPartyLevel(minPartyCount);

    if (enemyLevel < playerLevel)
        return sBattleTransitionTable_Trainer[transitionType][0];
    else
        return sBattleTransitionTable_Trainer[transitionType][1];
}

#define RANDOM_TRANSITION(table)(table[Random() % ARRAY_COUNT(table)])
u8 GetSpecialBattleTransition(s32 id)
{
    u16 var;
    u8 enemyLevel = GetMonData(&gEnemyParty[0], MON_DATA_LEVEL);
    u8 playerLevel = GetSumOfPlayerPartyLevel(1);

    if (enemyLevel < playerLevel)
    {
        switch (id)
        {
        case B_TRANSITION_GROUP_TRAINER_HILL:
        case B_TRANSITION_GROUP_SECRET_BASE:
        case B_TRANSITION_GROUP_E_READER:
            return B_TRANSITION_POKEBALLS_TRAIL;
        case B_TRANSITION_GROUP_B_PYRAMID:
            return RANDOM_TRANSITION(sBattleTransitionTable_BattlePyramid);
        case B_TRANSITION_GROUP_B_DOME:
            return RANDOM_TRANSITION(sBattleTransitionTable_BattleDome);
        }

        if (VarGet(VAR_FRONTIER_BATTLE_MODE) != FRONTIER_MODE_LINK_MULTIS)
            return RANDOM_TRANSITION(sBattleTransitionTable_BattleFrontier);
    }
    else
    {
        switch (id)
        {
        case B_TRANSITION_GROUP_TRAINER_HILL:
        case B_TRANSITION_GROUP_SECRET_BASE:
        case B_TRANSITION_GROUP_E_READER:
            return B_TRANSITION_BIG_POKEBALL;
        case B_TRANSITION_GROUP_B_PYRAMID:
            return RANDOM_TRANSITION(sBattleTransitionTable_BattlePyramid);
        case B_TRANSITION_GROUP_B_DOME:
            return RANDOM_TRANSITION(sBattleTransitionTable_BattleDome);
        }

        if (VarGet(VAR_FRONTIER_BATTLE_MODE) != FRONTIER_MODE_LINK_MULTIS)
            return RANDOM_TRANSITION(sBattleTransitionTable_BattleFrontier);
    }

    var = gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum * 2 + 0]
        + gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum * 2 + 1];

    return sBattleTransitionTable_BattleFrontier[var % ARRAY_COUNT(sBattleTransitionTable_BattleFrontier)];
}

void ChooseStarter(void)
{
    SetMainCallback2(CB2_ChooseStarter);
    gMain.savedCallback = CB2_GiveStarter;
}

static void CB2_GiveStarter(void)
{
    u16 starterMon;

    *GetVarPointer(VAR_STARTER_MON) = gSpecialVar_Result;
    starterMon = GetStarterPokemon(gSpecialVar_Result);
    ScriptGiveMon(starterMon, 5, ITEM_NONE, 0, 0, 0);
    ResetTasks();
    StopCryAndClearCrySongs();
    BlendPalettes(PALETTES_ALL, 16, 0);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void CB2_StartFirstBattle(void)
{
    UpdatePaletteFade();
    RunTasks();

    if (IsBattleTransitionDone() == TRUE)
    {
        gBattleTypeFlags = BATTLE_TYPE_FIRST_BATTLE;
        gMain.savedCallback = CB2_EndFirstBattle;
        FreeAllWindowBuffers();
        SetMainCallback2(CB2_InitBattle);
        RestartWildEncounterImmunitySteps();
        ClearPoisonStepCounter();
        IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
        IncrementGameStat(GAME_STAT_WILD_BATTLES);
        IncrementDailyWildBattles();
        TryUpdateGymLeaderRematchFromWild();
    }
}

static void CB2_EndFirstBattle(void)
{
    Overworld_ClearSavedMusic();
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void TryUpdateGymLeaderRematchFromWild(void)
{
    if (GetGameStat(GAME_STAT_WILD_BATTLES) % 60 == 0)
        UpdateGymLeaderRematch();
}

static void TryUpdateGymLeaderRematchFromTrainer(void)
{
    if (GetGameStat(GAME_STAT_TRAINER_BATTLES) % 20 == 0)
        UpdateGymLeaderRematch();
}

// why not just use the macros? maybe its because they didnt want to uncast const every time?
static u32 TrainerBattleLoadArg32(const u8 *ptr)
{
    return T1_READ_32(ptr);
}

static u16 TrainerBattleLoadArg16(const u8 *ptr)
{
    return T1_READ_16(ptr);
}

static u8 TrainerBattleLoadArg8(const u8 *ptr)
{
    return T1_READ_8(ptr);
}

static u16 GetTrainerAFlag(void)
{
    return TRAINER_FLAGS_START + gTrainerBattleOpponent_A;
}

static u16 GetTrainerBFlag(void)
{
    return TRAINER_FLAGS_START + gTrainerBattleOpponent_B;
}

static bool32 IsPlayerDefeated(u32 battleOutcome)
{
    switch (battleOutcome)
    {
    case B_OUTCOME_LOST:
    case B_OUTCOME_DREW:
        return TRUE;
    case B_OUTCOME_WON:
    case B_OUTCOME_RAN:
    case B_OUTCOME_PLAYER_TELEPORTED:
    case B_OUTCOME_MON_FLED:
    case B_OUTCOME_CAUGHT:
        return FALSE;
    default:
        return FALSE;
    }
}

void ResetTrainerOpponentIds(void)
{
    gTrainerBattleOpponent_A = 0;
    gTrainerBattleOpponent_B = 0;
}

static void InitTrainerBattleVariables(void)
{
    sTrainerBattleMode = 0;
    if (gApproachingTrainerId == 0)
    {
        sTrainerAIntroSpeech = NULL;
        sTrainerADefeatSpeech = NULL;
        sTrainerABattleScriptRetAddr = NULL;
    }
    else
    {
        sTrainerBIntroSpeech = NULL;
        sTrainerBDefeatSpeech = NULL;
        sTrainerBBattleScriptRetAddr = NULL;
    }
    sTrainerObjectEventLocalId = 0;
    sTrainerVictorySpeech = NULL;
    sTrainerCannotBattleSpeech = NULL;
    sTrainerBattleEndScript = NULL;
}

static inline void SetU8(void *ptr, u8 value)
{
    *(u8 *)(ptr) = value;
}

static inline void SetU16(void *ptr, u16 value)
{
    *(u16 *)(ptr) = value;
}

static inline void SetU32(void *ptr, u32 value)
{
    *(u32 *)(ptr) = value;
}

static inline void SetPtr(const void *ptr, const void *value)
{
    *(const void **)(ptr) = value;
}

static void TrainerBattleLoadArgs(const struct TrainerBattleParameter *specs, const u8 *data)
{
    while (1)
    {
        switch (specs->ptrType)
        {
        case TRAINER_PARAM_LOAD_VAL_8BIT:
            SetU8(specs->varPtr, TrainerBattleLoadArg8(data));
            data += 1;
            break;
        case TRAINER_PARAM_LOAD_VAL_16BIT:
            SetU16(specs->varPtr, TrainerBattleLoadArg16(data));
            data += 2;
            break;
        case TRAINER_PARAM_LOAD_VAL_32BIT:
            SetU32(specs->varPtr, TrainerBattleLoadArg32(data));
            data += 4;
            break;
        case TRAINER_PARAM_CLEAR_VAL_8BIT:
            SetU8(specs->varPtr, 0);
            break;
        case TRAINER_PARAM_CLEAR_VAL_16BIT:
            SetU16(specs->varPtr, 0);
            break;
        case TRAINER_PARAM_CLEAR_VAL_32BIT:
            SetU32(specs->varPtr, 0);
            break;
        case TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR:
            SetPtr(specs->varPtr, data);
            return;
        }
        specs++;
    }
}

void SetMapVarsToTrainer(void)
{
    if (sTrainerObjectEventLocalId != 0)
    {
        gSpecialVar_LastTalked = sTrainerObjectEventLocalId;
        gSelectedObjectEvent = GetObjectEventIdByLocalIdAndMap(sTrainerObjectEventLocalId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    }
}

const u8 *BattleSetup_ConfigureTrainerBattle(const u8 *data)
{
    if (TrainerBattleLoadArg8(data) != TRAINER_BATTLE_SET_TRAINER_B)
        InitTrainerBattleVariables();
    sTrainerBattleMode = TrainerBattleLoadArg8(data);

    switch (sTrainerBattleMode)
    {
    case TRAINER_BATTLE_SINGLE_NO_INTRO_TEXT:
        TrainerBattleLoadArgs(sOrdinaryNoIntroBattleParams, data);
        return EventScript_DoNoIntroTrainerBattle;
    case TRAINER_BATTLE_DOUBLE:
        TrainerBattleLoadArgs(sDoubleBattleParams, data);
        SetMapVarsToTrainer();
        return EventScript_TryDoDoubleTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT:
        if (gApproachingTrainerId == 0)
        {
            TrainerBattleLoadArgs(sContinueScriptBattleParams, data);
            SetMapVarsToTrainer();
        }
        else
        {
            TrainerBattleLoadArgs(sTrainerBContinueScriptBattleParams, data);
        }
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC:
        TrainerBattleLoadArgs(sContinueScriptBattleParams, data);
        SetMapVarsToTrainer();
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE:
    case TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC:
        TrainerBattleLoadArgs(sContinueScriptDoubleBattleParams, data);
        SetMapVarsToTrainer();
        return EventScript_TryDoDoubleTrainerBattle;
#if FREE_MATCH_CALL == FALSE
    case TRAINER_BATTLE_REMATCH_DOUBLE:
        TrainerBattleLoadArgs(sDoubleBattleParams, data);
        SetMapVarsToTrainer();
        gTrainerBattleOpponent_A = GetRematchTrainerId(gTrainerBattleOpponent_A);
        return EventScript_TryDoDoubleRematchBattle;
    case TRAINER_BATTLE_REMATCH:
        TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
        SetMapVarsToTrainer();
        gTrainerBattleOpponent_A = GetRematchTrainerId(gTrainerBattleOpponent_A);
        return EventScript_TryDoRematchBattle;
#endif //FREE_MATCH_CALL
    case TRAINER_BATTLE_PYRAMID:
        if (gApproachingTrainerId == 0)
        {
            TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
            SetMapVarsToTrainer();
            gTrainerBattleOpponent_A = LocalIdToPyramidTrainerId(gSpecialVar_LastTalked);
        }
        else
        {
            TrainerBattleLoadArgs(sTrainerBOrdinaryBattleParams, data);
            gTrainerBattleOpponent_B = LocalIdToPyramidTrainerId(gSpecialVar_LastTalked);
        }
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_SET_TRAINER_A:
        TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
        return sTrainerBattleEndScript;
    case TRAINER_BATTLE_SET_TRAINER_B:
        TrainerBattleLoadArgs(sTrainerBOrdinaryBattleParams, data);
        return sTrainerBattleEndScript;
    case TRAINER_BATTLE_HILL:
        if (gApproachingTrainerId == 0)
        {
            TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
            SetMapVarsToTrainer();
            gTrainerBattleOpponent_A = LocalIdToHillTrainerId(gSpecialVar_LastTalked);
        }
        else
        {
            TrainerBattleLoadArgs(sTrainerBOrdinaryBattleParams, data);
            gTrainerBattleOpponent_B = LocalIdToHillTrainerId(gSpecialVar_LastTalked);
        }
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_TWO_TRAINERS:
        gNoOfApproachingTrainers = 2; // set TWO_OPPONENTS gBattleTypeFlags
        gApproachingTrainerId = 1; // prevent trainer approach
        TrainerBattleLoadArgs(sTrainerTwoTrainerBattleParams, data);
        return EventScript_DoNoIntroTrainerBattle;
    default:
        if (gApproachingTrainerId == 0)
        {
            TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
            SetMapVarsToTrainer();
        }
        else
        {
            TrainerBattleLoadArgs(sTrainerBOrdinaryBattleParams, data);
        }
        return EventScript_TryDoNormalTrainerBattle;
    }
}

void ConfigureAndSetUpOneTrainerBattle(u8 trainerObjEventId, const u8 *trainerScript)
{
    gSelectedObjectEvent = trainerObjEventId;
    gSpecialVar_LastTalked = gObjectEvents[trainerObjEventId].localId;
    BattleSetup_ConfigureTrainerBattle(trainerScript + 1);
    ScriptContext_SetupScript(EventScript_StartTrainerApproach);
    LockPlayerFieldControls();
}

void ConfigureTwoTrainersBattle(u8 trainerObjEventId, const u8 *trainerScript)
{
    gSelectedObjectEvent = trainerObjEventId;
    gSpecialVar_LastTalked = gObjectEvents[trainerObjEventId].localId;
    BattleSetup_ConfigureTrainerBattle(trainerScript + 1);
}

void SetUpTwoTrainersBattle(void)
{
    ScriptContext_SetupScript(EventScript_StartTrainerApproach);
    LockPlayerFieldControls();
}

bool32 GetTrainerFlagFromScriptPointer(const u8 *data)
{
    u32 flag = TrainerBattleLoadArg16(data + 2);
    return FlagGet(TRAINER_FLAGS_START + flag);
}

// Set trainer's movement type so they stop and remain facing that direction
// Note: Only for trainers who are spoken to directly
//       For trainers who spot the player this is handled by PlayerFaceApproachingTrainer
void SetTrainerFacingDirection(void)
{
    struct ObjectEvent *objectEvent = &gObjectEvents[gSelectedObjectEvent];
    SetTrainerMovementType(objectEvent, GetTrainerFacingDirectionMovementType(objectEvent->facingDirection));
}

u8 GetTrainerBattleMode(void)
{
    return sTrainerBattleMode;
}

bool8 GetTrainerFlag(void)
{
    if (InBattlePyramid())
        return GetBattlePyramidTrainerFlag(gSelectedObjectEvent);
    else if (InTrainerHill())
        return GetHillTrainerFlag(gSelectedObjectEvent);
    else
        return FlagGet(GetTrainerAFlag());
}

static void SetBattledTrainersFlags(void)
{
    if (gTrainerBattleOpponent_B != 0)
        FlagSet(GetTrainerBFlag());
    FlagSet(GetTrainerAFlag());
}

static void SetBattledTrainerFlag(void)
{
    FlagSet(GetTrainerAFlag());
}

bool8 HasTrainerBeenFought(u16 trainerId)
{
    return FlagGet(TRAINER_FLAGS_START + trainerId);
}

void SetTrainerFlag(u16 trainerId)
{
    FlagSet(TRAINER_FLAGS_START + trainerId);
}

void ClearTrainerFlag(u16 trainerId)
{
    FlagClear(TRAINER_FLAGS_START + trainerId);
}

void BattleSetup_StartTrainerBattle(void)
{
    if (gNoOfApproachingTrainers == 2)
        gBattleTypeFlags = (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_TRAINER);
    else
        gBattleTypeFlags = (BATTLE_TYPE_TRAINER);

    if (InBattlePyramid())
    {
        VarSet(VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0);
        gBattleTypeFlags |= BATTLE_TYPE_PYRAMID;

        if (gNoOfApproachingTrainers == 2)
        {
            FillFrontierTrainersParties(1);
            ZeroMonData(&gEnemyParty[1]);
            ZeroMonData(&gEnemyParty[2]);
            ZeroMonData(&gEnemyParty[4]);
            ZeroMonData(&gEnemyParty[5]);
        }
        else
        {
            FillFrontierTrainerParty(1);
            ZeroMonData(&gEnemyParty[1]);
            ZeroMonData(&gEnemyParty[2]);
        }

        MarkApproachingPyramidTrainersAsBattled();
    }
    else if (InTrainerHillChallenge())
    {
        gBattleTypeFlags |= BATTLE_TYPE_TRAINER_HILL;

        if (gNoOfApproachingTrainers == 2)
            FillHillTrainersParties();
        else
            FillHillTrainerParty();

        SetHillTrainerFlag();
    }

    sNoOfPossibleTrainerRetScripts = gNoOfApproachingTrainers;
    gNoOfApproachingTrainers = 0;
    sShouldCheckTrainerBScript = FALSE;
    gWhichTrainerToFaceAfterBattle = 0;
    gMain.savedCallback = CB2_EndTrainerBattle;

    if (InBattlePyramid() || InTrainerHillChallenge())
        DoBattlePyramidTrainerHillBattle();
    else
        DoTrainerBattle();

    ScriptContext_Stop();
}

void BattleSetup_StartTrainerBattle_Debug(void)
{
    sNoOfPossibleTrainerRetScripts = gNoOfApproachingTrainers;
    gNoOfApproachingTrainers = 0;
    sShouldCheckTrainerBScript = FALSE;
    gWhichTrainerToFaceAfterBattle = 0;
    gMain.savedCallback = CB2_EndTrainerBattle;

    CreateBattleStartTask_Debug(GetWildBattleTransition(), 0);

    ScriptContext_Stop();
}

static void CB2_EndTrainerBattle(void)
{
    if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
    else if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        if (InBattlePyramid() || InTrainerHillChallenge())
            SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        else
            SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        if (!InBattlePyramid() && !InTrainerHillChallenge())
        {
            RegisterTrainerInMatchCall();
            SetBattledTrainersFlags();
        }
    }
}

static void CB2_EndRematchBattle(void)
{
    if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
    else if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        RegisterTrainerInMatchCall();
        SetBattledTrainersFlags();
        HandleRematchVarsOnBattleEnd();
    }
}

void BattleSetup_StartRematchBattle(void)
{
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    gMain.savedCallback = CB2_EndRematchBattle;
    DoTrainerBattle();
    ScriptContext_Stop();
}

void ShowTrainerIntroSpeech(void)
{
    if (InBattlePyramid())
    {
        if (gNoOfApproachingTrainers == 0 || gNoOfApproachingTrainers == 1)
            CopyPyramidTrainerSpeechBefore(LocalIdToPyramidTrainerId(gSpecialVar_LastTalked));
        else
            CopyPyramidTrainerSpeechBefore(LocalIdToPyramidTrainerId(gObjectEvents[gApproachingTrainers[gApproachingTrainerId].objectEventId].localId));

        ShowFieldMessageFromBuffer();
    }
    else if (InTrainerHillChallenge())
    {
        if (gNoOfApproachingTrainers == 0 || gNoOfApproachingTrainers == 1)
            CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_INTRO, LocalIdToHillTrainerId(gSpecialVar_LastTalked));
        else
            CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_INTRO, LocalIdToHillTrainerId(gObjectEvents[gApproachingTrainers[gApproachingTrainerId].objectEventId].localId));

        ShowFieldMessageFromBuffer();
    }
    else
    {
        ShowFieldMessage(GetIntroSpeechOfApproachingTrainer());
    }
}

const u8 *BattleSetup_GetScriptAddrAfterBattle(void)
{
    if (sTrainerBattleEndScript != NULL)
        return sTrainerBattleEndScript;
    else
        return EventScript_TestSignpostMsg;
}

const u8 *BattleSetup_GetTrainerPostBattleScript(void)
{
    if (sShouldCheckTrainerBScript)
    {
        sShouldCheckTrainerBScript = FALSE;
        if (sTrainerBBattleScriptRetAddr != NULL)
        {
            gWhichTrainerToFaceAfterBattle = 1;
            return sTrainerBBattleScriptRetAddr;
        }
    }
    else
    {
        if (sTrainerABattleScriptRetAddr != NULL)
        {
            gWhichTrainerToFaceAfterBattle = 0;
            return sTrainerABattleScriptRetAddr;
        }
    }

    return EventScript_TryGetTrainerScript;
}

void ShowTrainerCantBattleSpeech(void)
{
    ShowFieldMessage(GetTrainerCantBattleSpeech());
}

void PlayTrainerEncounterMusic(void)
{
    u16 trainerId;
    u16 music;

    if (gApproachingTrainerId == 0)
        trainerId = gTrainerBattleOpponent_A;
    else
        trainerId = gTrainerBattleOpponent_B;

    if(gTrainers[trainerId].trainerClass == TRAINER_CLASS_TOPAZ_ACOLYTE) {
            PlaySE(SE_PIN); //This sound better than the sound effect I made tbh -Celia
    }
    
    if (sTrainerBattleMode != TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC
        && sTrainerBattleMode != TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC
        && gTrainers[trainerId].trainerClass != TRAINER_CLASS_TOPAZ_ACOLYTE
        && !ShouldSkipTrainerClassMusic(trainerId))
    {
        switch (GetTrainerEncounterMusicId(trainerId))
        {
        case TRAINER_ENCOUNTER_MUSIC_MALE:
            music = MUS_ENCOUNTER_MALE;
            break;
        case TRAINER_ENCOUNTER_MUSIC_FEMALE:
            music = MUS_ENCOUNTER_FEMALE;
            break;
        case TRAINER_ENCOUNTER_MUSIC_GIRL:
            music = MUS_ENCOUNTER_GIRL;
            break;
        case TRAINER_ENCOUNTER_MUSIC_INTENSE:
            music = MUS_ENCOUNTER_INTENSE;
            break;
        case TRAINER_ENCOUNTER_MUSIC_COOL:
            music = MUS_ENCOUNTER_COOL;
            break;
        case TRAINER_ENCOUNTER_MUSIC_AQUA:
            music = MUS_ENCOUNTER_AQUA;
            break;
        case TRAINER_ENCOUNTER_MUSIC_MAGMA:
            music = MUS_ENCOUNTER_MAGMA;
            break;
        case TRAINER_ENCOUNTER_MUSIC_SWIMMER:
            music = MUS_ENCOUNTER_SWIMMER;
            break;
        case TRAINER_ENCOUNTER_MUSIC_TWINS:
            music = MUS_ENCOUNTER_TWINS;
            break;
        case TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR:
            music = MUS_ENCOUNTER_ELITE_FOUR;
            break;
        case TRAINER_ENCOUNTER_MUSIC_HIKER:
            music = MUS_ENCOUNTER_HIKER;
            break;
        case TRAINER_ENCOUNTER_MUSIC_INTERVIEWER:
            music = MUS_ENCOUNTER_INTERVIEWER;
            break;
        case TRAINER_ENCOUNTER_MUSIC_RICH:
            music = MUS_ENCOUNTER_RICH;
            break;
        case TRAINER_ENCOUNTER_MUSIC_EVIL:
            music = MUS_RG_ENCOUNTER_ROCKET;
            break;
        case TRAINER_ENCOUNTER_MUSIC_LASSIE:
            music = MUS_RG_ENCOUNTER_GIRL;
            break;
        case TRAINER_ENCOUNTER_MUSIC_LAD:
            music = MUS_RG_ENCOUNTER_BOY;
            break;
        case TRAINER_ENCOUNTER_MUSIC_BLUE:
            music = MUS_RG_ENCOUNTER_RIVAL;
            break;
        default:
            music = MUS_ENCOUNTER_SUSPICIOUS;
        }
        PlayNewMapMusic(music);
        
    }
}

static const u8 *ReturnEmptyStringIfNull(const u8 *string)
{
    if (string == NULL)
        return gText_EmptyString2;
    else
        return string;
}

static const u8 *GetIntroSpeechOfApproachingTrainer(void)
{
    if (gApproachingTrainerId == 0)
    {
        return ReturnEmptyStringIfNull(sTrainerAIntroSpeech);
    }
    else
    {
        return ReturnEmptyStringIfNull(sTrainerBIntroSpeech);
    }
}

const u8 *GetTrainerALoseText(void)
{
    const u8 *string;

    if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
        string = GetSecretBaseTrainerLoseText();
    else
        string = sTrainerADefeatSpeech;

    StringExpandPlaceholders(gStringVar4, ReturnEmptyStringIfNull(string));
    return gStringVar4;
}

const u8 *GetTrainerBLoseText(void)
{
    StringExpandPlaceholders(gStringVar4, ReturnEmptyStringIfNull(sTrainerBDefeatSpeech));
    return gStringVar4;
}

const u8 *GetTrainerWonSpeech(void)
{
    return ReturnEmptyStringIfNull(sTrainerVictorySpeech);
}

static const u8 *GetTrainerCantBattleSpeech(void)
{
    return ReturnEmptyStringIfNull(sTrainerCannotBattleSpeech);
}

static s32 FirstBattleTrainerIdToRematchTableId(const struct RematchTrainer *table, u16 trainerId)
{
    s32 i;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        if (table[i].trainerIds[0] == trainerId)
            return i;
    }

    return -1;
}

static s32 TrainerIdToRematchTableId(const struct RematchTrainer *table, u16 trainerId)
{
    s32 i, j;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        for (j = 0; j < REMATCHES_COUNT; j++)
        {
            if (table[i].trainerIds[j] == 0) break; // one line required to match -g
            if (table[i].trainerIds[j] == trainerId)
                return i;
        }
    }

    return -1;
}

// Returns TRUE if the given trainer (by their entry in the rematch table) is not allowed to have rematches.
// This applies to the Elite Four and Victory Road Wally (if he's not been defeated yet)
static inline bool32 IsRematchForbidden(s32 rematchTableId)
{
    if (rematchTableId >= REMATCH_ELITE_FOUR_ENTRIES)
        return TRUE;
    else if (rematchTableId == REMATCH_WALLY_VR)
        return !FlagGet(FLAG_DEFEATED_WALLY_VICTORY_ROAD);
    else
        return FALSE;
}

static void SetRematchIdForTrainer(const struct RematchTrainer *table, u32 tableId)
{
#if FREE_MATCH_CALL == FALSE
    s32 i;

    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        u16 trainerId = table[tableId].trainerIds[i];
        if (trainerId == 0)
            break;
        if (!HasTrainerBeenFought(trainerId))
            break;
    }

    gSaveBlock1Ptr->trainerRematches[tableId] = i;
#endif //FREE_MATCH_CALL
}


#if FREE_MATCH_CALL == FALSE
static bool32 UpdateRandomTrainerRematches(const struct RematchTrainer *table, u16 mapGroup, u16 mapNum)
{
    s32 i;
    bool32 ret = FALSE;

    for (i = 0; i <= REMATCH_SPECIAL_TRAINER_START; i++)
    {
        if (table[i].mapGroup == mapGroup && table[i].mapNum == mapNum && !IsRematchForbidden(i))
        {
            if (gSaveBlock1Ptr->trainerRematches[i] != 0)
            {
                // Trainer already wants a rematch. Don't bother updating it.
                ret = TRUE;
            }
            else if (FlagGet(FLAG_MATCH_CALL_REGISTERED + i)
             && (Random() % 100) <= 30)  // 31% chance of getting a rematch.
            {
                SetRematchIdForTrainer(table, i);
                ret = TRUE;
            }
        }
    }

    return ret;
}
#endif //FREE_MATCH_CALL

void UpdateRematchIfDefeated(s32 rematchTableId)
{
    if (HasTrainerBeenFought(gRematchTable[rematchTableId].trainerIds[0]) == TRUE)
        SetRematchIdForTrainer(gRematchTable, rematchTableId);
}

static bool32 DoesSomeoneWantRematchIn_(const struct RematchTrainer *table, u16 mapGroup, u16 mapNum)
{
#if FREE_MATCH_CALL == FALSE
    s32 i;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        if (table[i].mapGroup == mapGroup && table[i].mapNum == mapNum && gSaveBlock1Ptr->trainerRematches[i] != 0)
            return TRUE;
    }
#endif //FREE_MATCH_CALL

    return FALSE;
}

static bool32 IsRematchTrainerIn_(const struct RematchTrainer *table, u16 mapGroup, u16 mapNum)
{
    s32 i;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        if (table[i].mapGroup == mapGroup && table[i].mapNum == mapNum)
            return TRUE;
    }

    return FALSE;
}

static bool8 IsFirstTrainerIdReadyForRematch(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    s32 tableId = FirstBattleTrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId == -1)
        return FALSE;
    if (tableId >= MAX_REMATCH_ENTRIES)
        return FALSE;
#if FREE_MATCH_CALL == FALSE
    if (gSaveBlock1Ptr->trainerRematches[tableId] == 0)
        return FALSE;
#endif //FREE_MATCH_CALL

    return TRUE;
}

static bool8 IsTrainerReadyForRematch_(const struct RematchTrainer *table, u16 trainerId)
{
    s32 tableId = TrainerIdToRematchTableId(table, trainerId);

    if (tableId == -1)
        return FALSE;
    if (tableId >= MAX_REMATCH_ENTRIES)
        return FALSE;
#if FREE_MATCH_CALL == FALSE
    if (gSaveBlock1Ptr->trainerRematches[tableId] == 0)
        return FALSE;
#endif //FREE_MATCH_CALL

    return TRUE;
}

static u16 GetRematchTrainerIdFromTable(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    const struct RematchTrainer *trainerEntry;
    s32 i;
    s32 tableId = FirstBattleTrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId == -1)
        return FALSE;

    trainerEntry = &table[tableId];
    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        if (trainerEntry->trainerIds[i] == 0) // previous entry was this trainer's last one
            return trainerEntry->trainerIds[i - 1];
        if (!HasTrainerBeenFought(trainerEntry->trainerIds[i]))
            return trainerEntry->trainerIds[i];
    }

    return trainerEntry->trainerIds[REMATCHES_COUNT - 1]; // already beaten at max stage
}

static u16 GetLastBeatenRematchTrainerIdFromTable(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    const struct RematchTrainer *trainerEntry;
    s32 i;
    s32 tableId = FirstBattleTrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId == -1)
        return FALSE;

    trainerEntry = &table[tableId];
    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        if (trainerEntry->trainerIds[i] == 0) // previous entry was this trainer's last one
            return trainerEntry->trainerIds[i - 1];
        if (!HasTrainerBeenFought(trainerEntry->trainerIds[i]))
            return trainerEntry->trainerIds[i - 1];
    }

    return trainerEntry->trainerIds[REMATCHES_COUNT - 1]; // already beaten at max stage
}

static void ClearTrainerWantRematchState(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
#if FREE_MATCH_CALL == FALSE
    s32 tableId = TrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId != -1)
        gSaveBlock1Ptr->trainerRematches[tableId] = 0;
#endif //FREE_MATCH_CALL
}

static u32 GetTrainerMatchCallFlag(u32 trainerId)
{
    s32 i;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        if (gRematchTable[i].trainerIds[0] == trainerId)
            return FLAG_MATCH_CALL_REGISTERED + i;
    }

    return 0xFFFF;
}

static void RegisterTrainerInMatchCall(void)
{
    if (FlagGet(FLAG_HAS_MATCH_CALL))
    {
        u32 matchCallFlagId = GetTrainerMatchCallFlag(gTrainerBattleOpponent_A);
        if (matchCallFlagId != 0xFFFF)
            FlagSet(matchCallFlagId);
    }
}

static bool8 WasSecondRematchWon(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    s32 tableId = FirstBattleTrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId == -1)
        return FALSE;
    if (!HasTrainerBeenFought(table[tableId].trainerIds[1]))
        return FALSE;

    return TRUE;
}

#if FREE_MATCH_CALL == FALSE
static bool32 HasAtLeastFiveBadges(void)
{
    s32 i, count;

    for (count = 0, i = 0; i < ARRAY_COUNT(sBadgeFlags); i++)
    {
        if (FlagGet(sBadgeFlags[i]) == TRUE)
        {
            if (++count >= 5)
                return TRUE;
        }
    }

    return FALSE;
}
#endif //FREE_MATCH_CALL

#define STEP_COUNTER_MAX 255

void IncrementRematchStepCounter(void)
{
#if FREE_MATCH_CALL == FALSE
    if (HasAtLeastFiveBadges())
    {
        if (gSaveBlock1Ptr->trainerRematchStepCounter >= STEP_COUNTER_MAX)
            gSaveBlock1Ptr->trainerRematchStepCounter = STEP_COUNTER_MAX;
        else
            gSaveBlock1Ptr->trainerRematchStepCounter++;
    }
#endif //FREE_MATCH_CALL
}

#if FREE_MATCH_CALL == FALSE
static bool32 IsRematchStepCounterMaxed(void)
{
    if (HasAtLeastFiveBadges() && gSaveBlock1Ptr->trainerRematchStepCounter >= STEP_COUNTER_MAX)
        return TRUE;
    else
        return FALSE;
}

void TryUpdateRandomTrainerRematches(u16 mapGroup, u16 mapNum)
{
    if (IsRematchStepCounterMaxed() && UpdateRandomTrainerRematches(gRematchTable, mapGroup, mapNum) == TRUE)
        gSaveBlock1Ptr->trainerRematchStepCounter = 0;
}
#endif //FREE_MATCH_CALL

bool32 DoesSomeoneWantRematchIn(u16 mapGroup, u16 mapNum)
{
    return DoesSomeoneWantRematchIn_(gRematchTable, mapGroup, mapNum);
}

bool32 IsRematchTrainerIn(u16 mapGroup, u16 mapNum)
{
    return IsRematchTrainerIn_(gRematchTable, mapGroup, mapNum);
}

#if FREE_MATCH_CALL == FALSE
static u16 GetRematchTrainerId(u16 trainerId)
{
    return GetRematchTrainerIdFromTable(gRematchTable, trainerId);
}
#endif //FREE_MATCH_CALL

u16 GetLastBeatenRematchTrainerId(u16 trainerId)
{
    return GetLastBeatenRematchTrainerIdFromTable(gRematchTable, trainerId);
}

bool8 ShouldTryRematchBattle(void)
{
    if (IsFirstTrainerIdReadyForRematch(gRematchTable, gTrainerBattleOpponent_A))
        return TRUE;

    return WasSecondRematchWon(gRematchTable, gTrainerBattleOpponent_A);
}

bool8 IsTrainerReadyForRematch(void)
{
    return IsTrainerReadyForRematch_(gRematchTable, gTrainerBattleOpponent_A);
}

static void HandleRematchVarsOnBattleEnd(void)
{
    ClearTrainerWantRematchState(gRematchTable, gTrainerBattleOpponent_A);
    SetBattledTrainersFlags();
}

void ShouldTryGetTrainerScript(void)
{
    if (sNoOfPossibleTrainerRetScripts > 1)
    {
        sNoOfPossibleTrainerRetScripts = 0;
        sShouldCheckTrainerBScript = TRUE;
        gSpecialVar_Result = TRUE;
    }
    else
    {
        sShouldCheckTrainerBScript = FALSE;
        gSpecialVar_Result = FALSE;
    }
}

u16 CountBattledRematchTeams(u16 trainerId)
{
    s32 i;

    if (HasTrainerBeenFought(gRematchTable[trainerId].trainerIds[0]) != TRUE)
        return 0;

    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        if (gRematchTable[trainerId].trainerIds[i] == 0)
            break;
        if (!HasTrainerBeenFought(gRematchTable[trainerId].trainerIds[i]))
            break;
    }

    return i;
}
