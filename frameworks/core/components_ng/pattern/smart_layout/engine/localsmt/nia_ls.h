/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NIA_LS_H
#define NIA_LS_H
#include <algorithm>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <stack>
#include <sys/types.h>
#include <unistd.h>

#include "../utils/nia_Array.h"
#include "../utils/ration_num.h"

namespace niaOverall {
const int64_t MAX_INT = __int128_t(INT32_MAX);

// ============================================================================
// Solver constants (G.CNS.02)
// ============================================================================
// Default parameter
constexpr double K_DEFAULT_SWT_P = 0.3;

// Direction indexing (forward/backward in tabulist, lastMove, solution arrays)
constexpr int K_DIR_COUNT = 2;

// Equality and clause sizes
constexpr int K_TWO_VAR_EQUALITY = 2;   // merge requires exactly 2 vars
constexpr int K_MIN_RESOLVE_EQUALS = 2; // minimum literals for resolution
constexpr int K_TWO_LITERAL_CLAUSE = 2; // clause with 2 literals

// SMT-LIB parsing indices
constexpr int K_VEC_OP_IDX = 2;               // index of operator in parsed token vector
constexpr int K_VEC_ARG1_IDX = 3;             // index of first argument
constexpr int K_VEC_ARG2_IDX = 4;             // index of second argument
constexpr int K_VEC_COFF_START_IDX = 5;       // start index for coefficient parsing
constexpr int K_VEC_MULTI_TERM_THRESHOLD = 6; // vec with >6 tokens has multi-term expression

// Operation and search parameters
constexpr int K_OP_MULTIPLIER = 3;     // operation count multiplier
constexpr int K_RAND_WALK_ITER = 3;    // random walk iterations
constexpr int K_RAND_WALK_MAX_OPS = 5; // max operations in random walk

// Component fields (width, height, x, y)
constexpr int K_COMPONENT_FIELDS = 4;

// Tabu search parameters
constexpr int K_TABU_BASE_BOOL = 1; // base offset for boolean tabu tenure
constexpr int K_TABU_RAND_BOOL = 3; // random range for boolean tabu
constexpr int K_TABU_BASE_NIA = 3;  // base offset for NIA tabu tenure
constexpr int K_TABU_RAND_NIA = 10; // random range for NIA tabu

// Thresholds and limits
constexpr int K_RES_CLAUSE_MULTIPLIER = 10; // resolution clause size multiplier
constexpr int K_SWAP_SMALL_THRESHOLD = 20;  // threshold for small operation index
constexpr int K_BMS_THRESHOLD = 45;         // bms threshold
constexpr int K_SWAP_MAX_ITER = 50;         // maximum swap iterations

// Probability bases
constexpr int K_WEIGHT_PROB_BASE = 10000; // base for weight probability calculations

// Solution limits
constexpr int64_t K_SOLUTION_LIMIT = 100000000; // solution value limit

// Initialize parameters
constexpr int CUT_OFF = 1200;
constexpr int ADDITIONAL_LEN = 10;
constexpr int SMOO_PROBABILITY = 3;
constexpr int SWT_THRESHOLD = 50;

// VarLit means the var appears in corresponding lit, with the coff coffient
struct VarLit {
    uint64_t varIdx;
    uint64_t litIdx;
    RationNum coff;
    VarLit(uint64_t varIdx, uint64_t litIdx, RationNum coff) : varIdx(varIdx), litIdx(litIdx), coff(coff) {};
};

struct CoffVar {
    int varIdx;
    RationNum coff;
    CoffVar() {};
    CoffVar(int varIdx, RationNum coff) : varIdx(varIdx), coff(coff) {};
};
// if isNiaLit: \sum coff*var<=key
// else:_vars[delta]
struct lit {
    std::vector<CoffVar> coffVars; // sort by var
    std::vector<VarLit> varLits;   // sort by var
    RationNum key;
    int litsIndex;        // litsIndex<0 means it is already false, litsIndex == 0 means it is already true
    RationNum delta;      // the current value of left side
    bool isEqual = false; // true means a-b-k==0, else a-b-k<=0
    bool isNiaLit = false;
    int isTrue; // 1 means the lit is true, -1 otherwise
};

struct variable {
    std::vector<int> clauseIdxs;
    std::vector<bool> boolVarInPosClause; // true means the boolean var is the pos form in corresponding clause
    std::vector<VarLit> varLits;          // sort by lit
    std::vector<uint64_t> literalIdxs;
    std::string varName;
    RationNum lowBound = RationNum(-MAX_INT);
    RationNum upper_bound = RationNum(MAX_INT);
    bool isNia;
    bool isDelete = false;
    int score;      // if it is a bool var, then the score is calculated beforehand
    int upBool = 0; // the bool value of variables deleted(1 true -1 false)
};

struct ComponentPrintInfo {
    struct Bounds {
        double& x;
        double& y;
        double& w;
        double& h;
    };
    struct Offset {
        int x;
        int y;
    };
    Bounds bounds;
    int& v;
    int cIdx;
    Offset offset;

    ComponentPrintInfo(Bounds& boundsRef, int& vRef, int idx, Offset off = Offset())
        : bounds(boundsRef), v(vRef), cIdx(idx), offset(off)
    {}
};

struct clause {
    std::vector<int>
        literals; // literals[i]=l means the ith literal of the clause if the pos(neg) of the _lits, it can be negative
    std::vector<int> niaLiterals;
    std::vector<int> boolLiterals;
    int weight = 1;
    int satCount;
    int watchLitIdx; // the litIdx of sat literal in the clause
    bool isDelete = false;
};

// used for restore and record info
struct tmpInfo {
    std::vector<variable> _varsInfo;
    std::vector<clause> _clausesInfo;
    std::vector<lit> _litsInfo;
    std::vector<int> faInfo;
    std::vector<RationNum> faCoffInfo;
    std::vector<RationNum> faConstInfo;
    std::vector<RationNum> presetValuesInfo;
    bool currentBuildUnsat = true;
};

class LsSolver {
public:
    // basic information
    bool unsatInPreprocess = false;
    uint64_t numVars;
    uint64_t numLits;
    int numNiaLits;
    int numBoolLits;
    uint64_t numClauses;
    uint64_t numOpt = 0; // the number of vars in all literals, which is the max number of operations
    uint64_t unchangedVar1 = UINT32_MAX;
    uint64_t unchangedVar2 = UINT32_MAX;
    std::string basicComponentName;
    size_t bWidthIdx = 0, bHightIdx = 0;
    std::vector<variable> _vars;
    std::vector<int> niaVarVec;
    std::vector<int> boolVarVec;
    std::vector<lit> _lits;
    std::vector<int> _litMakeBreak; // making a move will make or break the lit itself (1:make, -1:break, 0:no change)
    std::vector<clause> _clauses;
    std::vector<clause> _reconstructStack;
    std::vector<bool> isInUnsatClause;
    std::vector<int> litsInUnsatClause;
    Array* unsatClauses = nullptr;
    Array* satClauseWithFalseLiteral =
        nullptr;                              // clauses with 0<satNum<literalNum, from which swap operation are choosen
    Array* containBoolUnsatClauses = nullptr; // unsat clause with at least one boolean var
    Array* falseLitOccur = nullptr;           // the false lits for choosing critical move
    uint64_t lastOpVar;
    RationNum lastOpValue; // the last value and last var, x +1, at least at next step, x -1 is forbidden
    std::map<std::string, int> feasible2litidx;
    // solution
    std::vector<RationNum> _solution;
    std::vector<RationNum> _bestSolutin;
    int bestFoundCost;
    int bestFoundThisRestart;
    int noImproveCntBool = 0;
    int noImproveCntNia = 0;
    bool isInBoolSearch = false;
    int bestFoundHardCostThisBool;
    int bestFoundHardCostThisNia;
    // control
    uint64_t step;
    uint64_t outerLayerStep;
    const uint64_t maxStep;
    std::vector<uint64_t>
        tabulist; // tabulist[2*var] and [2*var+1] means that var are forbidden to move forward or backward until then
    std::vector<bool> isChosenBoolVar;
    std::vector<uint64_t> lastMove;
    std::vector<uint64_t> operationVarIdxVec;
    std::vector<RationNum> operationChangeValueVec;
    std::vector<int> operationVarIdxBoolVec;
    std::chrono::steady_clock::time_point start;
    double bestCostTime;
    double cutoff;
    std::mt19937 mt;
    const uint64_t additionalLen;
    std::map<std::string, uint64_t> name2var; // map the name of a variable to its index
    std::vector<RationNum> _preValue1; // the 1st pre-set value of a var, if the var is in the form of (a==0 OR a==1)
    std::vector<RationNum> _preValue2;
    bool useSwapFromFromSmallWeight;
    std::vector<bool> varAppear; // true means the var exists in the formula
    std::vector<bool> litAppear; // true means the lit exists in the formula
    Array* litsInCls = nullptr;
    const bool completeLs;
    void AddUnitClause(std::vector<std::vector<int>>& vec, const std::vector<int>& unitLits);
    // data structure for clause weighting
    const uint64_t smoothProbability;
    uint64_t swtThreshold;
    float swtP; // w=w*p+aveW*(1-p)
    uint64_t totalClauseWeight;
    int litInUnsatClauseNum;
    int boolLitInUnsatClauseNum;
    // data structure for equality
    // fa[x]=f means x=(coff*f)+const
    std::vector<int> fa;
    std::vector<RationNum> faCoff;
    std::vector<RationNum> faConst;
    void PrepareCoffVar();

    // input transformation
    bool hasUnidentifiedLits = false; // if the literals contains unidentified lits
    void ReadFromFile(const std::string& fileName, const std::vector<std::string>& softCNames = {});
    void SplitString(std::string& inString, std::vector<std::string>& strVec, std::string pattern);
    void BuildLits(std::string& inString);
    void BuildInstanceOriginal(const std::vector<std::string>& unitLits = {});
    void BuildInstanceNewWidth(int bcWidth, int bcHight = 0, int radius = 0);
    void FindBound(bool& modified);
    void PrepareClauseForResolution(const std::vector<std::vector<int>> clauseVec);
    void FindUnitEqualLits(std::vector<int>& unitEqualLitsAll);
    void ConvertInequalToEqual(bool& modified);
    void PrepareFaCoffs();
    void PrepareClsLitIdxForVars();
    void PreprocessOnSize(RationNum bcWidth = RationNum(0), RationNum bcHight = RationNum(0),
        RationNum radius = RationNum(0)); // find out the equalilty among vars, and reset the vars and lits
    void FixValue(RationNum& bcWidth, RationNum& bcHight, RationNum& radius);
    int bcWidthIdx = 0;
    int bcHightIdx = 0;
    int bcXIdx = 0;
    int bcYIdx = 0;
    bool HasSameCoffVars(const lit* l1, const lit* l2);
    void EliminateMultipleInequalities(bool& modified); // a+b<=3 a+b<=2 -->a+b<=2
    bool ResolveMultipleEquals(const std::vector<int>& mLits);
    void UpdateByEquals(bool& modified);
    void ProcessUnitEqualLitsMerge(std::vector<int>& unitEqualLitsAll, bool& findNewMerge, bool& modified);
    std::vector<RationNum> presetValues;
    void DeleteRedundantClauses(std::vector<std::vector<int>>& clauseVec);
    int Find(int varIdx); // return the fa of varIdx
    bool Merge(lit& l);   // l: a*x + b*y +c == 0
    void UpdateBoundByMerge(int varIdx1, int varIdx2, RationNum coff, RationNum constTerm);
    void UpdateLitEqual(int litIdx);
    void UpdateLitPresetVar(int litIdx);
    uint64_t TransferNameToVar(const std::string& name, bool isNia);
    void DetermineLitAppear();                     // determine whether the lit appear in clauses
    void FindMaxVarLit(std::vector<int>& litIdxs); // find the max var and lit index in the formula

    // initialize
    LsSolver();
    explicit LsSolver(int randomSeed, uint64_t maxStep = UINT64_MAX, double cutoff = 1200, bool completeLs = false);
    void MakeSpace();
    void RecordInfoAfterReadFile();
    void RestoreInforBeforeBuildOrigin();
    std::vector<variable> _varsAfterReadFile;
    std::vector<lit> _litsAfterReadFile;
    std::vector<std::vector<int>> originalVec;
    void RecordInfo(tmpInfo& info);
    void RestoreInfo(const tmpInfo& info);
    tmpInfo infoBeforeTrial;
    tmpInfo infoAfterOrigin;
    void MakeLitsSpace(uint64_t newNumLits)
    {
        numLits = newNumLits;
        _lits.resize(numLits + additionalLen);
    };
    void Initialize(const std::map<std::string, double>& varInitial = {});
    void InitializeVariableDatas();
    void InitializeLitDatas();
    void InitializeClauseDatas();
    void UnitProp();
    void Resolution();
    struct ResolveContext {
        std::vector<uint64_t> posClauses;
        std::vector<uint64_t> negClauses;
        int posClauseSize = 0;
        int negClauseSize = 0;
    };

    void DeterminePosAndNegClauses(uint64_t boolVarIdx, ResolveContext& ctx);
    int CountTautology(uint64_t boolVarIdx, const ResolveContext& ctx);
    int CountNegClauseTautology(uint64_t posClauseIdx, uint64_t negClauseIdx, uint64_t boolVarIdx);
    void DeleteClausesOfVar(uint64_t clauseIdx, uint64_t boolVarIdx);
    void ResolveClauses(uint64_t boolVarIdx, ResolveContext& ctx, std::map<__int128_t, int>& clauselitMap,
        std::vector<__int128_t>& clauselit);
    void ResolvePosAndNegClause(uint64_t posClauseIdx, uint64_t negClauseIdx, uint64_t boolVarIdx,
        std::map<__int128_t, int>& clauselitMap, std::vector<__int128_t>& clauselit);
    void AddClauseToData(const clause& newClause, __int128_t clauseLitHash, std::map<__int128_t, int>& clauselitMap,
        std::vector<__int128_t>& clauselit);
    void PushClausesToReconstructStack(uint64_t boolVarIdx, const ResolveContext& ctx);
    std::vector<int> upValueVars;
    void PrepareUpValueVars();
    __int128_t HashLitsToNum(std::vector<int>& lits);
    void ReduceDuplicatedLits(bool& modified); // return true if found duplicated lits
    bool litsBeenModified = true;              // whether these lits have modified since last removing duplicated lits
    void GcdForLit(lit& l);
    void ReduceClause(bool& modified);
    bool IsClauseTautology(const clause& c);
    void ReduceDuplicatedLitsInClause(clause& c, bool& modified);
    RationNum CalculateLitUpBound(const lit& l);
    RationNum CalculateLitLowBound(const lit& l);
    void HandleNonEqualCase(lit& l, const RationNum& litUpBound, const RationNum& litLowBound, bool& modified);
    void HandleEqualCase(lit& l, const RationNum& litUpBound, const RationNum& litLowBound, bool& modified);
    void DetermineLitsByBound(bool& modified);
    void SetPreValue();
    void ReadModel();
    bool IsSameLits(std::vector<int>& lits1, std::vector<int>& lits2); // deterine whether 2 cls are the same
    bool IsSameLit(const lit& l1, const lit& l2);
    bool IsNegLit(const lit& l1, const lit& l2);
    bool buildUnsat = false;

    // random walk
    void UpdateClauseWeight();
    void SmoothClauseWeight();
    void RandomWalk();
    void NoOperationRandomWalk(); // when there is no operation, simply find a lit in a random false clause, pick a
                                  // random var with coff!=0, set it to 0

    // construction
    void ConstructSolution(const std::map<std::string, double>& varInitial = {});
    inline bool IsSignedLitTrue(int lIdx)
    {
        return (lIdx ^ _lits[std::abs(lIdx)].isTrue) >= 0;
    };

    // basic operations
    inline void SatAClause(uint64_t clauseIdx)
    {
        unsatClauses->DeleteElement((int)clauseIdx);
        containBoolUnsatClauses->DeleteElement((int)clauseIdx);
    };
    inline void UnsatAClause(uint64_t clauseIdx)
    {
        unsatClauses->InsertElement((int)clauseIdx);
        if (_clauses[clauseIdx].boolLiterals.size() > 0) {
            containBoolUnsatClauses->InsertElement((int)clauseIdx);
        }
    };
    bool UpdateBestSolution();
    int PickCriticalMove(RationNum& bestValue);
    int PickCriticalMoveBool();
    void CriticalMove(uint64_t varIdx, RationNum changeValue);
    void MoveUpdate(uint64_t varIdx, RationNum changeValue);
    void MoveUpdate(uint64_t varIdx);
    void UpdateSingleLitDelta(uint64_t litIdx, RationNum currLitDeltaNew);
    void UpdateClauseSatCountInVar(uint64_t varIdx);
    void UpdateBooleanVarScoreInClause(int clauseIdx, int clauseSatCountOld, int clauseSatCountNew, int watchLitIdxOld);
    void UpdateClauseSatCountBool(int clauseIdx, int makeBreakInClause);
    void UpdateWatchLitBool(int clauseIdx, int vLitIdx, int clSignIdx, int originSatCount);
    void UpdateBooleanVarScoreInClauseBool(int clauseIdx, int makeBreakInClause, int originSatCount);
    void InvertLit(lit& l);
    RationNum DeltaLit(lit& l);
    void AddCoff(uint64_t varIdxCurr, bool useTabu, int litIdx, int& operationIdx, RationNum coff1);
    double TimeElapsed();
    void ClearPrevData();
    void InsertOperation(uint64_t varIdx, RationNum changeValue, int& operationIdx, bool useTabu);
    void AddBoolOperation(bool useTabu, int litIdx,
        int& operationIdxBool); // given a false lit, add the corresponding var to the operationVecBool
    void AddOperationFromFalseLit(
        bool useTabu, int litIdx, int& operationIdx); // given a false lit(litIdx<0 means it is the neg form)
    void SelectBestOperationFromVec(int operationIdx, int& bestScore, int& bestVarIdx, RationNum& bestValue);
    void SelectBestOperationFromBoolVec(int operationIdxBool, int& bestScoreBool, int& bestVarIdxBool);
    void ProcessClauseNiaLiterals(clause* cl, int& operationIdx);
    void AddSwapOperation(int& operationIdx);
    void EnterNiaMode();
    void EnterBoolMode();
    bool UpdateInnerBestSolution();
    bool UpdateOuterBestSolution();
    // print
    void PrintFormula();
    void PrintLiteral(lit& l);
    void PrintFormulaSmt();
    void PrintLitSmt(int litIdx);
    void PrintMv();
    void PrintFullModel();
    void PrintComponents(int offsetX = 0, int offsetY = 0, std::ostream& out = std::cout);
    void PrintComponent(ComponentPrintInfo& info);
    void PrintMvVars(uint64_t varIdx);
    void PrintEnd();
    void PrintVarSolution(std::string& varName, std::string& varValue);
    bool PrintVarSolution(std::string& varName, RationNum& varValue);
    void RecordSoftVarSolution(std::vector<int>& softCInfo);
    std::vector<size_t> componentsIdx;
    std::vector<std::string> componentNames;
    std::vector<size_t> softComponentsIdx;
    void PrepareComponentsIdx();
    void AddComponent(const std::string& cName);
    void PrepareSoftComponentsIdx(const std::vector<std::string>& softCNames);
    void UpBoolVars();
    bool GetLitsValue(uint64_t litIdx, const std::string& str);
    // calculate score
    void SetLitMakeBreak(const std::vector<VarLit>& varLits, int clIdx, uint64_t& currLitIdx,
        RationNum& currLitDeltaNew, const RationNum& changeValue);
    int CriticalScore(uint64_t varIdx, RationNum changeValue);
    __int128_t CriticalSubscore(uint64_t varIdx, RationNum changeValue);
    // check
    int CheckSingleClause(clause* cp);
    bool CheckSolution();
    // handle 128
    inline __int128_t Abs128(__int128_t n)
    {
        return n >= 0 ? n : -n;
    }
    std::string Print128(__int128 n);
    // local search
    bool AssumeOneLiteral(int litIdx, const std::map<std::string, double>& varInitial = {});
    bool AssumeOneLiteral(const std::map<std::string, double>& varInitial = {});
    bool LocalSearch(const std::map<std::string, double>& varInitial = {});
    // delete
    ~LsSolver();
    // update increment
    bool UpdatePresetValue(uint64_t varIdx, RationNum newPreVal);
    bool UpdateWidthHight(RationNum newPreValWidth, RationNum newPreValHight);

private:
    void ClearPreparedClauseLitVarState();
    void RecordNiaLiteralInClause(int clauseIdx, int litSignIdx, lit& currentLit);
    void RecordBoolLiteralInClause(int clauseIdx, int litSignIdx, lit& currentLit);
    void RecordClauseLiteralRelations();
    void DeduplicateClauseIdxs(variable& currentVar);
    void BuildPreparedVarLitRelations();
    void CollectUniqueLiteralIdxs(variable& currentVar);
};
} // namespace niaOverall

#endif // NIA_LS_H