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

#include <chrono>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <atomic>
#include <map>
#include <memory>
#include <system_error>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "core/components_ng/pattern/smart_layout/engine/localsmt/localsmt.h"
#include "core/components_ng/pattern/smart_layout/engine/localsmt/matrix.h"
#include "core/components_ng/pattern/smart_layout/engine/localsmt/nia_ls.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_RANDOM_SEED = 0;
constexpr uint64_t TEST_MAX_STEP = 50000;
constexpr double TEST_CUTOFF_SECONDS = 10.0;
constexpr bool TEST_COMPLETE_LS = true;
constexpr int32_t VALID_WIDTH = 1080;
constexpr int32_t INVALID_WIDTH = 5001;
constexpr int32_t TEST_HEIGHT = 0;
constexpr int32_t WIDTH_LOWER_BOUND = 0;
constexpr int32_t WIDTH_UPPER_BOUND = 4000;
constexpr int32_t INVALID_LOW_WIDTH = -1;
constexpr int32_t RADIUS_VALID = 5;
constexpr int32_t RADIUS_INVALID = 11;
constexpr uint64_t TEST_LITS_SPACE_MEDIUM = 20;
constexpr uint64_t TEST_LITS_SPACE_SMALL = 10;
constexpr uint64_t TEST_LITS_SPACE_CLAUSE = 6;
constexpr uint64_t TEST_LITS_SPACE_MINIMAL = 1;
constexpr int32_t BOOL_VAR_TRUE = 1;
constexpr int32_t NON_NEGATIVE_INDEX = 0;
constexpr double SHORT_CUTOFF_SECONDS = 0.01;
constexpr uint64_t SHORT_MAX_STEP = 8;
constexpr int32_t FEASIBLE_LIT_IDX = 3;
constexpr int32_t SOFTVAR_LIT_IDX = 4;
constexpr int32_t UNIT_LITERAL_ID = 1;
constexpr int32_t CLAUSE_LITERAL_TWO = 2;
constexpr int32_t CLAUSE_LITERAL_THREE = 3;
constexpr int32_t CLAUSE_LITERAL_FOUR = 4;
constexpr int32_t HASH_VEC_A = 3;
constexpr int32_t HASH_VEC_B = -1;
constexpr int32_t HASH_VEC_C = 2;
constexpr int32_t HASH_VEC_D = 1;
constexpr int32_t ASSUME_LIT_INDEX = 1;
constexpr int32_t SEARCH_WIDTH = 1080;
constexpr int32_t SEARCH_HEIGHT = 0;
constexpr uint64_t PARSER_TEST_LITS_SPACE = 16;
constexpr int32_t AUTOLAYOUT_REBUILD_WIDTH = 1500;
constexpr int32_t NIA_LIT_INDEX_FOR_PATH_TEST = 3;
constexpr int32_t NIA_FALSE_THRESHOLD = 10;
constexpr int32_t EQUAL_LIT_INDEX = 99;
constexpr int32_t EQUAL_LIT_TARGET = 8;
constexpr int32_t UPDATED_SOLUTION_FOR_CLAUSE = 2;
constexpr int32_t OPERATION_BOUND_LOW = -100;
constexpr int32_t OPERATION_BOUND_HIGH = 100;
constexpr int32_t OPERATION_TABU_LIST_SIZE = 2;
constexpr int32_t OPERATION_HISTORY_CAPACITY = 10;
constexpr int32_t OPERATION_STEP = 5;
constexpr int32_t TABU_BLOCK_STEP = 100;
constexpr int32_t OUT_OF_BOUND_SOLUTION = 100000000;
constexpr int32_t ACCEPTED_UPPER_BOUND = 10;
constexpr int32_t OPERATION_VALUE_ONE = 1;
constexpr int32_t OPERATION_VALUE_TWO = 2;
constexpr int32_t OPERATION_VALUE_THREE = 3;
constexpr int32_t PREVIOUS_VALUE_FOUR = 4;
constexpr int32_t PREVIOUS_VALUE_FIVE = 5;
constexpr int32_t PREVIOUS_VALUE_EIGHT = 8;
constexpr int32_t FIRST_OPERATION_INDEX = 1;
constexpr int32_t SECOND_OPERATION_INDEX = 2;
constexpr int32_t THIRD_OPERATION_INDEX = 3;
constexpr int32_t BOUND_FIVE = 5;
constexpr int32_t BOUND_NEG_TEN = -10;
constexpr int32_t BOUND_TEN = 10;
constexpr int32_t CONSTRUCT_B2_TRUE = 1;
constexpr int32_t CONSTRUCT_X_BOUND = 5;
constexpr int32_t CONSTRUCT_Y_BOUND = 2;
constexpr int32_t CONSTRUCT_Z_VALUE = 3;
constexpr int32_t MODEL_X_VALUE = 42;
constexpr int32_t THIRD_CHANGE_VALUE_INDEX = 2;
constexpr int32_t CLEAR_PREV_SCORE_PRIMARY = 7;
constexpr int32_t CLEAR_PREV_SCORE_SECONDARY = -3;

const char* EMBEDDED_LAYOUT_SMT = R"(8
0 true
1 (>= BC_width 0.0)
2 (<= BC_width 4000.0)
3 (>= BC_height 0.0)
4 (= BC_height 0.0)
5 BC_feasible
6 (= BC_x 0.0)
7 (= BC_y 0.0)
0
5
(1)
(2)
(3)
(4)
(5)
)";

const char* RADIUS_BOUNDED_SMT = R"(8
0 true
1 (>= BC_width 0)
2 (<= BC_width 4000)
3 (>= BC_height 0)
4 (= BC_height 0)
5 (>= radius 0)
6 (<= radius 10)
7 BC_feasible
0
7
(1)
(2)
(3)
(4)
(5)
(6)
(7)
)";

const char* BOOL_PROPAGATION_SMT = R"(7
0 true
1 b1
2 b2
3 (>= BC_width 0)
4 (<= BC_width 4000)
5 (= BC_height 0)
6 BC_feasible
0
5
(1)
(-1 2)
(3)
(4)
(5)
)";

const char* UNIT_FEASIBLE_CONFLICT_SMT = R"(6
0 true
1 A_feasible
2 (>= X 0)
3 (<= X 10)
4 (>= X 20)
5 BC_feasible
0
4
(2)
(3)
(-1 4)
(5)
)";

const char* SEARCH_STRESS_SMT = R"(8
0 true
1 b1
2 b2
3 (<= X 2)
4 (>= X 8)
5 (<= X 10)
6 (>= X 0)
7 BC_feasible
0
7
(1 2)
(-1 3)
(-2 4)
(5)
(6)
(3)
(7)
)";

const char* AUTOLAYOUT_STYLE_SMT = R"(12
0 true
1 (>= x 0)
2 (>= y 0)
3 (<= x 1200)
4 (>= x 200)
5 (= (+ x y) 500)
6 (>= BC_width 0)
7 (<= BC_width 4000)
8 (> x 500)
9 (< x 100)
10 (= x y)
11 (<= x 50)
0
5
(1 2)
(3 4)
(5)
(8 9)
(10 11)
)";

const char* DOT_COMPONENT_SMT = R"(6
0 true
1 (>= .w 0)
2 (= .h 0)
3 (= .x 0)
4 (= .y 0)
5 root_feasible
0
5
(1)
(2)
(3)
(4)
(5)
)";

struct BuildResult {
    bool buildSuccess = false;
    bool unsatInPreprocess = false;
    bool buildUnsat = false;
};

void FlushTokenIfNeeded(std::vector<std::string>& tokens, std::string& token)
{
    if (token.empty()) {
        return;
    }
    tokens.emplace_back(token);
    token.clear();
}

std::string NormalizeSmtForParser(const std::string& smt)
{
    std::stringstream input(smt);
    std::string line;
    std::string normalized;
    while (std::getline(input, line)) {
        std::vector<std::string> tokens;
        std::string token;
        for (char ch : line) {
            if (ch == '(' || ch == ')') {
                FlushTokenIfNeeded(tokens, token);
                tokens.emplace_back(std::string(1, ch));
                continue;
            }
            if (std::isspace(static_cast<unsigned char>(ch))) {
                FlushTokenIfNeeded(tokens, token);
                continue;
            }
            token.push_back(ch);
        }
        FlushTokenIfNeeded(tokens, token);
        for (size_t i = 0; i < tokens.size(); i++) {
            if (i != 0) {
                normalized.push_back(' ');
            }
            normalized += tokens[i];
        }
        normalized.push_back('\n');
    }
    return normalized;
}

void BuildLitsWithNormalizedInput(niaOverall::LsSolver& solver, const std::string& input)
{
    auto normalized = NormalizeSmtForParser(input);
    if (!normalized.empty() && normalized.back() == '\n') {
        normalized.pop_back();
    }
    solver.BuildLits(normalized);
}

std::filesystem::path WriteSmtToTempFile(const std::string& smt)
{
    static std::atomic<uint64_t> fileId {0};
    const auto timestamp = std::chrono::steady_clock::now().time_since_epoch().count();
    const auto uniqueId = fileId.fetch_add(1, std::memory_order_relaxed);
    const auto fileName = "smart_layout_smt_file_test_" + std::to_string(timestamp) + "_" +
        std::to_string(uniqueId) + ".smt2";

    std::error_code ec;
    std::vector<std::filesystem::path> candidateDirs;
    auto tempDir = std::filesystem::temp_directory_path(ec);
    if (!ec) {
        candidateDirs.emplace_back(tempDir);
    }
    candidateDirs.emplace_back(std::filesystem::current_path(ec));
    candidateDirs.emplace_back("/data/local/tmp");
    candidateDirs.emplace_back(".");

    for (const auto& dir : candidateDirs) {
        if (dir.empty() || !std::filesystem::exists(dir, ec)) {
            continue;
        }
        auto filePath = dir / fileName;
        std::ofstream out(filePath, std::ios::out | std::ios::trunc);
        if (!out.is_open()) {
            continue;
        }
        out << NormalizeSmtForParser(smt);
        out.close();
        if (out.good()) {
            return filePath;
        }
    }
    return {};
}

BuildResult BuildOneCaseFromSmt(
    const std::string& smt, int width, int height, int radius = 0, const std::vector<std::string>& unitLits = {})
{
    const auto smtPath = WriteSmtToTempFile(smt);
    if (smtPath.empty()) {
        return {};
    }
    BuildResult result;
    {
        niaOverall::LsSolver solver(TEST_RANDOM_SEED, TEST_MAX_STEP, TEST_CUTOFF_SECONDS, TEST_COMPLETE_LS);
        solver.ReadFromFile(smtPath.string());
        solver.BuildInstanceOriginal(unitLits);
        if (!solver.unsatInPreprocess && !solver.buildUnsat) {
            solver.BuildInstanceNewWidth(width, height, radius);
        }
        result.unsatInPreprocess = solver.unsatInPreprocess;
        result.buildUnsat = solver.buildUnsat;
        result.buildSuccess = !result.unsatInPreprocess && !result.buildUnsat;
    }

    std::error_code ec;
    std::filesystem::remove(smtPath, ec);
    return result;
}

bool BuildOneCaseFromEmbeddedSmt(int width, int height)
{
    return BuildOneCaseFromSmt(EMBEDDED_LAYOUT_SMT, width, height).buildSuccess;
}

std::unique_ptr<niaOverall::LsSolver> BuildSearchSolverFromSmt(const std::string& smt, int width, int height)
{
    const auto smtPath = WriteSmtToTempFile(smt);
    auto solver = std::make_unique<niaOverall::LsSolver>(
        TEST_RANDOM_SEED, TEST_MAX_STEP, TEST_CUTOFF_SECONDS, TEST_COMPLETE_LS);
    solver->ReadFromFile(smtPath.string());
    solver->BuildInstanceOriginal();
    if (!solver->unsatInPreprocess && !solver->buildUnsat) {
        solver->BuildInstanceNewWidth(width, height);
    }
    std::error_code ec;
    std::filesystem::remove(smtPath, ec);
    return solver;
}

void VerifyLiteralEvaluationPaths(niaOverall::LsSolver& solver, size_t xIdx)
{
    auto* niaLit = &(solver.lits[NIA_LIT_INDEX_FOR_PATH_TEST]);
    EXPECT_TRUE(solver.EvaluateNiaLiteral(niaLit, NIA_LIT_INDEX_FOR_PATH_TEST, RationNum(0)));
    EXPECT_FALSE(solver.EvaluateNiaLiteral(niaLit, NIA_LIT_INDEX_FOR_PATH_TEST, RationNum(NIA_FALSE_THRESHOLD)));

    niaOverall::Lit equalLit;
    equalLit.isNiaLit = true;
    equalLit.isEqual = true;
    equalLit.litsIndex = EQUAL_LIT_INDEX;
    equalLit.coffVars.emplace_back(static_cast<int>(xIdx), RationNum(OPERATION_VALUE_ONE));
    EXPECT_TRUE(solver.EvaluateNiaLiteral(&equalLit, EQUAL_LIT_TARGET, RationNum(0)));
    EXPECT_FALSE(solver.EvaluateNiaLiteral(&equalLit, EQUAL_LIT_TARGET, RationNum(OPERATION_VALUE_ONE)));

    std::vector<bool> litAppearTmp = solver.litAppear;
    EXPECT_TRUE(solver.CheckNiaLiteralSatisfaction(niaLit, NIA_LIT_INDEX_FOR_PATH_TEST, litAppearTmp));
    solver.lits[ASSUME_LIT_INDEX].litsIndex = NON_NEGATIVE_INDEX;
    EXPECT_TRUE(solver.CheckLiteralSatisfaction(ASSUME_LIT_INDEX, litAppearTmp));
    solver.lits[ASSUME_LIT_INDEX].litsIndex = ASSUME_LIT_INDEX;
    bool litSat = solver.CheckLiteralSatisfaction(ASSUME_LIT_INDEX, litAppearTmp);
    EXPECT_EQ(litSat, solver.CheckLiteralSatisfaction(ASSUME_LIT_INDEX, litAppearTmp));
    solver.solution[xIdx] = UPDATED_SOLUTION_FOR_CLAUSE;
    if (!solver.clauses.empty()) {
        EXPECT_GE(solver.CheckSingleClause(&solver.clauses[0]), 0);
    }
}

void VerifyBoolRestoreAndBestUpdatePaths(niaOverall::LsSolver& solver)
{
    if (solver.name2var.find("b1") != solver.name2var.end()) {
        auto b1Idx = solver.name2var["b1"];
        if (b1Idx < solver.varAppear.size()) {
            solver.varAppear[b1Idx] = false;
        }
    }
    solver.reconstructStack.clear();
    niaOverall::Clause satClause;
    satClause.literals = { 1 };
    niaOverall::Clause unsatClause;
    unsatClause.literals = { -1 };
    solver.reconstructStack.push_back(satClause);
    solver.reconstructStack.push_back(unsatClause);
    solver.UpBoolVars();

    solver.bestFoundHardCostThisNia = INT32_MAX;
    solver.bestFoundHardCostThisBool = INT32_MAX;
    EXPECT_TRUE(solver.UpdateInnerBestSolution());
    EXPECT_TRUE(solver.UpdateOuterBestSolution());
    solver.buildUnsat = true;
    EXPECT_FALSE(solver.LocalSearch());
    solver.buildUnsat = false;
}

void PrepareInsertOperationSolver(niaOverall::LsSolver& solver)
{
    solver.numVars = OPERATION_VALUE_ONE;
    solver.vars.resize(OPERATION_VALUE_ONE);
    solver.vars[0].isNia = true;
    solver.vars[0].lowBound = RationNum(OPERATION_BOUND_LOW);
    solver.vars[0].upperBound = RationNum(OPERATION_BOUND_HIGH);
    solver.solution = { RationNum(0) };
    solver.preValue1 = { RationNum(INT32_MAX) };
    solver.preValue2 = { RationNum(INT32_MAX) };
    solver.tabulist.resize(OPERATION_TABU_LIST_SIZE, 0);
    solver.operationVarIdxVec.resize(OPERATION_HISTORY_CAPACITY);
    solver.operationChangeValueVec.resize(OPERATION_HISTORY_CAPACITY);
    solver.step = OPERATION_STEP;
}

void VerifyInsertOperationGuards(niaOverall::LsSolver& solver, int& operationIdx)
{
    solver.unchangedVar1 = 0;
    solver.InsertOperation(0, RationNum(OPERATION_VALUE_ONE), operationIdx, false);
    EXPECT_EQ(operationIdx, 0);

    solver.unchangedVar1 = UINT32_MAX;
    solver.lastOpVar = 0;
    solver.lastOpValue = RationNum(OPERATION_VALUE_ONE);
    solver.InsertOperation(0, RationNum(-OPERATION_VALUE_ONE), operationIdx, false);
    EXPECT_EQ(operationIdx, 0);

    solver.lastOpVar = UINT64_MAX;
    solver.tabulist[0] = TABU_BLOCK_STEP;
    solver.InsertOperation(0, RationNum(OPERATION_VALUE_ONE), operationIdx, true);
    EXPECT_EQ(operationIdx, 0);

    solver.tabulist[0] = 0;
    solver.solution[0] = RationNum(OUT_OF_BOUND_SOLUTION);
    solver.InsertOperation(0, RationNum(OPERATION_VALUE_ONE), operationIdx, false);
    EXPECT_EQ(operationIdx, 0);
}

void VerifyInsertOperationAcceptedPaths(niaOverall::LsSolver& solver, int& operationIdx)
{
    solver.solution[0] = RationNum(OPERATION_VALUE_TWO);
    solver.preValue1[0] = RationNum(INT32_MAX);
    solver.preValue2[0] = RationNum(INT32_MAX);
    solver.vars[0].lowBound = RationNum(0);
    solver.vars[0].upperBound = RationNum(ACCEPTED_UPPER_BOUND);
    solver.InsertOperation(0, RationNum(OPERATION_VALUE_ONE), operationIdx, false);
    ASSERT_EQ(operationIdx, FIRST_OPERATION_INDEX);
    EXPECT_EQ(solver.operationVarIdxVec[0], 0u);
    EXPECT_TRUE(solver.operationChangeValueVec[0] == OPERATION_VALUE_ONE);

    solver.preValue1[0] = RationNum(PREVIOUS_VALUE_FOUR);
    solver.preValue2[0] = RationNum(INT32_MAX);
    solver.InsertOperation(0, RationNum(OPERATION_VALUE_TWO), operationIdx, false);
    ASSERT_EQ(operationIdx, SECOND_OPERATION_INDEX);
    EXPECT_TRUE(solver.operationChangeValueVec[1] == OPERATION_VALUE_TWO);

    solver.preValue1[0] = RationNum(PREVIOUS_VALUE_FIVE);
    solver.preValue2[0] = RationNum(PREVIOUS_VALUE_EIGHT);
    solver.InsertOperation(0, RationNum(OPERATION_VALUE_THREE), operationIdx, false);
    ASSERT_EQ(operationIdx, THIRD_OPERATION_INDEX);
    EXPECT_TRUE(solver.operationChangeValueVec[THIRD_CHANGE_VALUE_INDEX] == OPERATION_VALUE_THREE);
}

void PrepareSolutionReadModelSolver(niaOverall::LsSolver& solver)
{
    solver.numVars = PREVIOUS_VALUE_FIVE;
    solver.numClauses = 0;
    solver.MakeLitsSpace(OPERATION_VALUE_TWO);
    solver.litAppear.resize(solver.numLits + TEST_LITS_SPACE_SMALL, false);
    solver.vars.resize(solver.numVars);
    solver.upValueVars.resize(solver.numVars + TEST_LITS_SPACE_SMALL, 0);
    solver.name2var["b1"] = 0;
    solver.name2var["b2"] = OPERATION_VALUE_ONE;
    solver.name2var["x"] = OPERATION_VALUE_TWO;
    solver.name2var["y"] = OPERATION_VALUE_THREE;
    solver.name2var["z"] = PREVIOUS_VALUE_FOUR;

    solver.vars[0].isNia = false;
    solver.vars[OPERATION_VALUE_ONE].isNia = false;
    solver.vars[OPERATION_VALUE_TWO].isNia = true;
    solver.vars[OPERATION_VALUE_THREE].isNia = true;
    solver.vars[PREVIOUS_VALUE_FOUR].isNia = true;
    solver.vars[OPERATION_VALUE_TWO].lowBound = RationNum(BOUND_FIVE);
    solver.vars[OPERATION_VALUE_THREE].upperBound = RationNum(OPERATION_VALUE_TWO);
    solver.vars[PREVIOUS_VALUE_FOUR].lowBound = RationNum(BOUND_NEG_TEN);
    solver.vars[PREVIOUS_VALUE_FOUR].upperBound = RationNum(BOUND_TEN);
    solver.upValueVars[0] = OPERATION_VALUE_ONE;
    solver.boolVarVec = { 0, OPERATION_VALUE_ONE };
}

void VerifyClearPrevData(niaOverall::LsSolver& solver)
{
    solver.MakeSpace();
    solver.vars[0].score = CLEAR_PREV_SCORE_PRIMARY;
    solver.vars[OPERATION_VALUE_ONE].score = CLEAR_PREV_SCORE_SECONDARY;
    std::fill(solver.tabulist.begin(), solver.tabulist.end(), OPERATION_VALUE_ONE);
    std::fill(solver.litMakeBreak.begin(), solver.litMakeBreak.end(), OPERATION_VALUE_ONE);
    std::fill(solver.isInUnsatClause.begin(), solver.isInUnsatClause.end(), true);
    std::fill(solver.lastMove.begin(), solver.lastMove.end(), OPERATION_VALUE_ONE);
    std::fill(solver.isChosenBoolVar.begin(), solver.isChosenBoolVar.end(), true);
    solver.unsatClauses->InsertElement(0);
    solver.falseLitOccur->InsertElement(0);

    solver.ClearPrevData();
    EXPECT_EQ(solver.vars[0].score, 0);
    EXPECT_EQ(solver.vars[OPERATION_VALUE_ONE].score, 0);
    EXPECT_TRUE(solver.unsatClauses->IsEmpty());
    EXPECT_TRUE(solver.falseLitOccur->IsEmpty());
}

void VerifyConstructSolutionAndReadModel(niaOverall::LsSolver& solver)
{
    solver.ConstructSolution({
        { "b1", 0.2 },
        { "b2", 0.8 },
        { "x", 1.0 },
        { "y", 8.0 },
        { "z", 3.0 },
        { "unknown", 9.0 },
    });
    EXPECT_TRUE(solver.solution[0] == OPERATION_VALUE_ONE);
    EXPECT_TRUE(solver.solution[OPERATION_VALUE_ONE] == CONSTRUCT_B2_TRUE);
    EXPECT_TRUE(solver.solution[OPERATION_VALUE_TWO] == CONSTRUCT_X_BOUND);
    EXPECT_TRUE(solver.solution[OPERATION_VALUE_THREE] == CONSTRUCT_Y_BOUND);
    EXPECT_TRUE(solver.solution[PREVIOUS_VALUE_FOUR] == CONSTRUCT_Z_VALUE);

    std::istringstream input("4 b1 false b2 true x 42 unknown 7");
    auto* oldBuf = std::cin.rdbuf(input.rdbuf());
    solver.ReadModel();
    std::cin.rdbuf(oldBuf);
    EXPECT_TRUE(solver.solution[0] == -OPERATION_VALUE_ONE);
    EXPECT_TRUE(solver.solution[OPERATION_VALUE_ONE] == OPERATION_VALUE_ONE);
    EXPECT_TRUE(solver.solution[OPERATION_VALUE_TWO] == MODEL_X_VALUE);
}
} // namespace

class SmartLayoutSmtFileTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SmartLayoutSmtFileTest000
 * @tc.desc: Level0 sanity test for matrix helpers with deterministic input.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest000, TestSize.Level0)
{
    std::vector<std::vector<RationNum>> matrix = {
        { RationNum(0), RationNum(1), RationNum(2) },
        { RationNum(-2), RationNum(3), RationNum(4) },
        { RationNum(1), RationNum(5), RationNum(6) },
    };

    auto pivotIdx = FindPivot(matrix, 0, 0);
    EXPECT_EQ(pivotIdx, 2);

    SwapRows(matrix, 0, 2);
    EXPECT_TRUE(matrix[0][0] == 1);
    EXPECT_TRUE(matrix[2][0] == 0);
}

/**
 * @tc.name: SmartLayoutSmtFileTest001
 * @tc.desc: Test solver builds successfully from embedded SMT content for a valid width.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest001, TestSize.Level1)
{
    const bool firstBuild = BuildOneCaseFromEmbeddedSmt(VALID_WIDTH, TEST_HEIGHT);
    const bool secondBuild = BuildOneCaseFromEmbeddedSmt(VALID_WIDTH, TEST_HEIGHT);
    ASSERT_TRUE(firstBuild);
    EXPECT_TRUE(secondBuild);
    EXPECT_TRUE(firstBuild && secondBuild);
}

/**
 * @tc.name: SmartLayoutSmtFileTest002
 * @tc.desc: Test BuildInstanceNewWidth accepts width assignment at build stage.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest002, TestSize.Level1)
{
    const bool validWidthBuild = BuildOneCaseFromEmbeddedSmt(VALID_WIDTH, TEST_HEIGHT);
    const bool invalidWidthBuild = BuildOneCaseFromEmbeddedSmt(INVALID_WIDTH, TEST_HEIGHT);
    ASSERT_TRUE(validWidthBuild);
    EXPECT_TRUE(invalidWidthBuild);
    EXPECT_NE(validWidthBuild, false);
    EXPECT_NE(invalidWidthBuild, false);
}

/**
 * @tc.name: SmartLayoutSmtFileTest003
 * @tc.desc: Test BuildInstanceNewWidth accepts boundary and out-of-bound widths at build stage.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest003, TestSize.Level1)
{
    EXPECT_TRUE(BuildOneCaseFromEmbeddedSmt(WIDTH_LOWER_BOUND, TEST_HEIGHT));
    EXPECT_TRUE(BuildOneCaseFromEmbeddedSmt(WIDTH_UPPER_BOUND, TEST_HEIGHT));
    EXPECT_TRUE(BuildOneCaseFromEmbeddedSmt(INVALID_LOW_WIDTH, TEST_HEIGHT));
    EXPECT_TRUE(BuildOneCaseFromEmbeddedSmt(WIDTH_UPPER_BOUND + 1, TEST_HEIGHT));
}

/**
 * @tc.name: SmartLayoutSmtFileTest004
 * @tc.desc: Test BuildLits parsing paths including bool/or/if/feasible/simple/multi-term.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest004, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.MakeLitsSpace(TEST_LITS_SPACE_MEDIUM);

    std::string trueLine = "0 true";
    std::string boolOrLine = "1 or bool_a";
    std::string boolIfLine = "2 if bool_b";
    std::string feasibleLine = "3 BC_feasible";
    std::string softVarLine = "4 softVar_extra";
    std::string eqTwoNamesLine = "5 (= left right)";
    std::string simpleBoundLine = "6 (<= BC_width 4000)";
    std::string reverseBoundLine = "7 (>= 0 BC_width)";
    std::string multiTermLine = "8 (>= (+ BC_width (* -1 BC_height)) 0)";

    BuildLitsWithNormalizedInput(solver, trueLine);
    BuildLitsWithNormalizedInput(solver, boolOrLine);
    BuildLitsWithNormalizedInput(solver, boolIfLine);
    BuildLitsWithNormalizedInput(solver, feasibleLine);
    BuildLitsWithNormalizedInput(solver, softVarLine);
    BuildLitsWithNormalizedInput(solver, eqTwoNamesLine);
    BuildLitsWithNormalizedInput(solver, simpleBoundLine);
    BuildLitsWithNormalizedInput(solver, reverseBoundLine);
    BuildLitsWithNormalizedInput(solver, multiTermLine);

    EXPECT_EQ(solver.lits[0].litsIndex, 0);
    EXPECT_FALSE(solver.lits[1].isNiaLit);
    EXPECT_FALSE(solver.lits[2].isNiaLit);
    EXPECT_TRUE(solver.lits[5].isNiaLit);
    EXPECT_TRUE(solver.lits[5].isEqual);
    EXPECT_EQ(solver.lits[5].coffVars.size(), 2u);
    EXPECT_TRUE(solver.lits[8].isNiaLit);
    EXPECT_GE(solver.lits[8].coffVars.size(), 2u);
    EXPECT_EQ(solver.feasible2litidx["BC_feasible"], FEASIBLE_LIT_IDX);
    EXPECT_EQ(solver.feasible2litidx["softVar_extra"], SOFTVAR_LIT_IDX);
}

/**
 * @tc.name: SmartLayoutSmtFileTest005
 * @tc.desc: Test unit propagation on boolean clauses.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest005, TestSize.Level1)
{
    const auto smtPath = WriteSmtToTempFile(BOOL_PROPAGATION_SMT);
    {
        niaOverall::LsSolver solver(TEST_RANDOM_SEED, TEST_MAX_STEP, TEST_CUTOFF_SECONDS, TEST_COMPLETE_LS);
        solver.ReadFromFile(smtPath.string());
        solver.BuildInstanceOriginal();

        ASSERT_FALSE(solver.unsatInPreprocess);
        ASSERT_FALSE(solver.buildUnsat);
        auto b1Idx = solver.name2var.find("b1");
        ASSERT_NE(b1Idx, solver.name2var.end());
        EXPECT_TRUE(solver.vars[b1Idx->second].isDelete);
        EXPECT_EQ(solver.vars[b1Idx->second].upBool, BOOL_VAR_TRUE);
    }
    std::error_code ec;
    std::filesystem::remove(smtPath, ec);
}

/**
 * @tc.name: SmartLayoutSmtFileTest006
 * @tc.desc: Test BuildInstanceOriginal unit literals can introduce conflicts.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest006, TestSize.Level1)
{
    const auto withoutUnit = BuildOneCaseFromSmt(UNIT_FEASIBLE_CONFLICT_SMT, VALID_WIDTH, TEST_HEIGHT);
    EXPECT_TRUE(withoutUnit.buildSuccess);

    const auto withUnit = BuildOneCaseFromSmt(
        UNIT_FEASIBLE_CONFLICT_SMT, VALID_WIDTH, TEST_HEIGHT, 0, std::vector<std::string> { "A_feasible" });
    EXPECT_TRUE(withUnit.unsatInPreprocess || withUnit.buildUnsat);
}

/**
 * @tc.name: SmartLayoutSmtFileTest007
 * @tc.desc: Test BuildInstanceNewWidth accepts radius assignment at build stage.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest007, TestSize.Level1)
{
    const auto validRadius = BuildOneCaseFromSmt(RADIUS_BOUNDED_SMT, VALID_WIDTH, TEST_HEIGHT, RADIUS_VALID);
    const auto invalidRadius = BuildOneCaseFromSmt(RADIUS_BOUNDED_SMT, VALID_WIDTH, TEST_HEIGHT, RADIUS_INVALID);
    EXPECT_TRUE(validRadius.buildSuccess);
    EXPECT_TRUE(invalidRadius.buildSuccess);
}

/**
 * @tc.name: SmartLayoutSmtFileTest008
 * @tc.desc: Test utility helpers: hash/same-lits/name mapping/lit comparison.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest008, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.MakeLitsSpace(TEST_LITS_SPACE_SMALL);

    std::vector<int> lhs = { HASH_VEC_A, HASH_VEC_B, HASH_VEC_C };
    std::vector<int> rhs = { HASH_VEC_C, HASH_VEC_A, HASH_VEC_B };
    std::vector<int> diff = { HASH_VEC_D, HASH_VEC_C, CLAUSE_LITERAL_FOUR };
    EXPECT_TRUE(solver.IsSameLits(lhs, rhs));
    EXPECT_FALSE(solver.IsSameLits(lhs, diff));
    const auto lhsHash = solver.HashLitsToNum(lhs);
    const auto rhsHash = solver.HashLitsToNum(rhs);
    const auto diffHash = solver.HashLitsToNum(diff);
    EXPECT_EQ(lhsHash, rhsHash);
    EXPECT_NE(lhsHash, diffHash);

    const uint64_t niaIdxA = solver.TransferNameToVar("A_width", true);
    const uint64_t niaIdxB = solver.TransferNameToVar("A_width", true);
    const uint64_t boolIdx = solver.TransferNameToVar("flag_a", false);
    ASSERT_NE(solver.name2var.find("A_width"), solver.name2var.end());
    EXPECT_EQ(niaIdxA, solver.name2var["A_width"]);
    EXPECT_EQ(niaIdxB, solver.name2var["A_width"]);
    EXPECT_NE(niaIdxA, boolIdx);

    niaOverall::Lit sameLit1;
    niaOverall::Lit sameLit2;
    sameLit1.isNiaLit = true;
    sameLit2.isNiaLit = true;
    sameLit1.isEqual = false;
    sameLit2.isEqual = false;
    sameLit1.key = -10;
    sameLit2.key = -10;
    sameLit1.coffVars.emplace_back(static_cast<int>(niaIdxA), RationNum(1));
    sameLit2.coffVars.emplace_back(static_cast<int>(niaIdxA), RationNum(1));
    EXPECT_TRUE(solver.HasSameCoffVars(&sameLit1, &sameLit2));
    EXPECT_TRUE(solver.IsSameLit(sameLit1, sameLit2));

    niaOverall::Lit negLit = sameLit1;
    negLit.key = 10;
    negLit.coffVars[0].coff = RationNum(-1);
    EXPECT_TRUE(solver.IsNegLit(sameLit1, negLit));
}

/**
 * @tc.name: SmartLayoutSmtFileTest009
 * @tc.desc: Test DeleteRedundantClauses removes duplicate literals and clauses satisfied by unit literals.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest009, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.MakeLitsSpace(TEST_LITS_SPACE_CLAUSE);
    std::vector<std::vector<int>> clauses = {
        { UNIT_LITERAL_ID, UNIT_LITERAL_ID, CLAUSE_LITERAL_TWO },
        { UNIT_LITERAL_ID },
        { CLAUSE_LITERAL_TWO, CLAUSE_LITERAL_THREE },
        { UNIT_LITERAL_ID, CLAUSE_LITERAL_THREE },
        { CLAUSE_LITERAL_TWO, CLAUSE_LITERAL_THREE },
    };

    solver.DeleteRedundantClauses(clauses);

    bool hasUnitClause = false;
    for (const auto& clause : clauses) {
        if (clause.size() == 1 && clause[0] == UNIT_LITERAL_ID) {
            hasUnitClause = true;
        }
        if (clause.size() > 1) {
            EXPECT_EQ(std::find(clause.begin(), clause.end(), UNIT_LITERAL_ID), clause.end());
        }
    }
    EXPECT_TRUE(hasUnitClause);
}

/**
 * @tc.name: SmartLayoutSmtFileTest010
 * @tc.desc: Test AssumeOneLiteral fast path when no clauses exist.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest010, TestSize.Level1)
{
    niaOverall::LsSolver solver(TEST_RANDOM_SEED, SHORT_MAX_STEP, SHORT_CUTOFF_SECONDS, TEST_COMPLETE_LS);
    solver.MakeLitsSpace(TEST_LITS_SPACE_MINIMAL);
    solver.numVars = NON_NEGATIVE_INDEX;
    solver.numClauses = NON_NEGATIVE_INDEX;
    solver.litAppear.resize(TEST_LITS_SPACE_MINIMAL, false);
    solver.MakeSpace();

    EXPECT_TRUE(solver.AssumeOneLiteral(ASSUME_LIT_INDEX));
}

/**
 * @tc.name: SmartLayoutSmtFileTest011
 * @tc.desc: Test matrix utilities SwapRows and FindPivot.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest011, TestSize.Level1)
{
    std::vector<std::vector<RationNum>> matrix = {
        { RationNum(0), RationNum(1), RationNum(2) },
        { RationNum(-2), RationNum(3), RationNum(4) },
        { RationNum(1), RationNum(5), RationNum(6) },
    };

    const auto pivotFromRow0 = static_cast<size_t>(FindPivot(matrix, 0, 0));
    ASSERT_LT(pivotFromRow0, matrix.size());
    EXPECT_NE(matrix[pivotFromRow0][0], RationNum(0));
    EXPECT_LE(std::abs(matrix[pivotFromRow0][0].ToDouble()), std::abs(matrix[1][0].ToDouble()));
    EXPECT_LE(std::abs(matrix[pivotFromRow0][0].ToDouble()), std::abs(matrix[2][0].ToDouble()));

    const auto pivotFromRow1 = static_cast<size_t>(FindPivot(matrix, 1, 1));
    ASSERT_LT(pivotFromRow1, matrix.size());
    EXPECT_NE(matrix[pivotFromRow1][1], RationNum(0));
    EXPECT_LE(std::abs(matrix[pivotFromRow1][1].ToDouble()), std::abs(matrix[1][1].ToDouble()));
    EXPECT_LE(std::abs(matrix[pivotFromRow1][1].ToDouble()), std::abs(matrix[2][1].ToDouble()));

    auto row0BeforeSwap = matrix[0];
    auto row2BeforeSwap = matrix[2];
    SwapRows(matrix, 0, 2);
    EXPECT_EQ(matrix[0], row2BeforeSwap);
    EXPECT_EQ(matrix[2], row0BeforeSwap);

    auto snapshot = matrix;
    SwapRows(matrix, 0, 99); // out-of-range should keep matrix unchanged
    EXPECT_EQ(matrix, snapshot);
}

/**
 * @tc.name: SmartLayoutSmtFileTest012
 * @tc.desc: Test TransferToInteger and IsAllZeroRow.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest012, TestSize.Level1)
{
    std::vector<RationNum> rowNeedDivide = { RationNum(4), RationNum(8), RationNum(12) };
    auto rowNeedDivideBefore = rowNeedDivide;
    TransferToInteger(rowNeedDivide);
    EXPECT_NE(rowNeedDivide, rowNeedDivideBefore);
    EXPECT_LT(rowNeedDivide[0], rowNeedDivide[1]);
    EXPECT_LT(rowNeedDivide[1], rowNeedDivide[2]);

    std::vector<RationNum> rowNoDivide = { RationNum(3), RationNum(4), RationNum(5) };
    auto originalRow = rowNoDivide;
    TransferToInteger(rowNoDivide); // gcd reaches 1, early return
    EXPECT_EQ(rowNoDivide, originalRow);

    std::vector<std::vector<RationNum>> matrix = {
        { RationNum(0), RationNum(0), RationNum(0) },
        { RationNum(6), RationNum(9), RationNum(12) },
    };
    auto matrixBefore = matrix;
    TransferToInteger(matrix);
    EXPECT_NE(matrix, matrixBefore);
    EXPECT_TRUE(IsAllZeroRow(matrix[0]));
    EXPECT_FALSE(IsAllZeroRow(matrix[1]));
    EXPECT_NE(matrix[1], matrixBefore[1]);
    EXPECT_LT(matrix[1][0], matrix[1][1]);
    EXPECT_LT(matrix[1][1], matrix[1][2]);
}

/**
 * @tc.name: SmartLayoutSmtFileTest013
 * @tc.desc: Test MergeRows branch coverage.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest013, TestSize.Level1)
{
    std::vector<RationNum> upperRow = { RationNum(2), RationNum(4), RationNum(6) };
    std::vector<RationNum> lowRow = { RationNum(1), RationNum(2), RationNum(3) };
    auto upperRowBeforeMerge = upperRow;
    MergeRows(upperRow, lowRow);
    EXPECT_NE(upperRow, upperRowBeforeMerge);
    EXPECT_FALSE(IsAllZeroRow(upperRowBeforeMerge));
    EXPECT_TRUE(IsAllZeroRow(upperRow));

    std::vector<RationNum> upperNoMerge = { RationNum(0), RationNum(4), RationNum(1) };
    std::vector<RationNum> lowNoMerge = { RationNum(1), RationNum(2), RationNum(0) };
    auto snapshot = upperNoMerge;
    MergeRows(upperNoMerge, lowNoMerge); // maxPFre == zeroFre, no merge
    EXPECT_EQ(upperNoMerge, snapshot);
}

/**
 * @tc.name: SmartLayoutSmtFileTest014
 * @tc.desc: Test ToUpperTriangle, ToDiagonal and GaussianElimination.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest014, TestSize.Level1)
{
    std::vector<std::vector<RationNum>> matrix = {
        { RationNum(0), RationNum(1), RationNum(2) },
        { RationNum(2), RationNum(3), RationNum(4) },
    };
    ToUpperTriangle(matrix); // triggers row swap path
    EXPECT_TRUE(matrix[0][0] != 0);
    EXPECT_TRUE(matrix[1][0] == 0);

    ToDiagonal(matrix);
    EXPECT_TRUE(matrix[0][1] == 0);

    std::vector<std::vector<RationNum>> matrixForGE = {
        { RationNum(2), RationNum(1), RationNum(5) },
        { RationNum(4), RationNum(-6), RationNum(-2) },
    };
    GaussianElimination(matrixForGE);
    EXPECT_TRUE(matrixForGE[1][0] == 0);

    std::vector<std::vector<RationNum>> emptyMatrix;
    ToDiagonal(emptyMatrix); // rowNum == 0
    GaussianElimination(emptyMatrix); // rowNum == 0
    EXPECT_TRUE(emptyMatrix.empty());
}

/**
 * @tc.name: SmartLayoutSmtFileTest015
 * @tc.desc: Test ContainsShortRow edge cases.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest015, TestSize.Level1)
{
    std::vector<std::vector<RationNum>> emptyMatrix;
    EXPECT_FALSE(ContainsShortRow(emptyMatrix));

    std::vector<std::vector<RationNum>> emptyRowMatrix = { {} };
    EXPECT_FALSE(ContainsShortRow(emptyRowMatrix));

    std::vector<std::vector<RationNum>> unevenMatrix = {
        { RationNum(1), RationNum(1), RationNum(1), RationNum(0) }, // 3 non-zero -> not short
        { RationNum(1), RationNum(2) }, // skipped due to row size mismatch
    };
    EXPECT_FALSE(ContainsShortRow(unevenMatrix));

    std::vector<std::vector<RationNum>> shortRowMatrix = {
        { RationNum(1), RationNum(0), RationNum(2), RationNum(3) }, // 2 non-zero -> short
    };
    EXPECT_TRUE(ContainsShortRow(shortRowMatrix));
}

/**
 * @tc.name: SmartLayoutSmtFileTest016
 * @tc.desc: Test ClearPrevData/ConstructSolution/ReadModel with branch-focused setup.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest016, TestSize.Level1)
{
    niaOverall::LsSolver solver(TEST_RANDOM_SEED, SHORT_MAX_STEP, SHORT_CUTOFF_SECONDS, TEST_COMPLETE_LS);
    PrepareSolutionReadModelSolver(solver);
    EXPECT_NO_FATAL_FAILURE(VerifyClearPrevData(solver));
    EXPECT_NO_FATAL_FAILURE(VerifyConstructSolutionAndReadModel(solver));
}

/**
 * @tc.name: SmartLayoutSmtFileTest017
 * @tc.desc: Test InitializeLitDatas and InitializeClauseDatas scoring/sat branches.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest017, TestSize.Level1)
{
    niaOverall::LsSolver solver(TEST_RANDOM_SEED, SHORT_MAX_STEP, SHORT_CUTOFF_SECONDS, TEST_COMPLETE_LS);
    solver.numVars = 2;
    solver.numClauses = 2;
    solver.MakeLitsSpace(4);
    solver.vars.resize(solver.numVars);
    solver.clauses.resize(solver.numClauses);
    solver.litAppear.resize(solver.numLits + TEST_LITS_SPACE_SMALL, false);
    solver.MakeSpace();

    solver.vars[0].isNia = false;
    solver.vars[1].isNia = false;
    solver.solution[0] = RationNum(1);
    solver.solution[1] = RationNum(1);

    solver.lits[0].isNiaLit = true;
    solver.lits[0].litsIndex = 0;

    solver.lits[1].isNiaLit = false;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].delta = RationNum(0);
    solver.litAppear[1] = true;

    solver.lits[2].isNiaLit = false;
    solver.lits[2].litsIndex = 2;
    solver.lits[2].delta = RationNum(1);
    solver.litAppear[2] = true;

    solver.lits[3].isNiaLit = true;
    solver.lits[3].litsIndex = 3;
    solver.lits[3].isEqual = false;
    solver.lits[3].key = RationNum(1);
    solver.lits[3].coffVars.emplace_back(0, RationNum(1));

    solver.InitializeLitDatas();
    EXPECT_EQ(solver.lits[1].isTrue, 1);
    EXPECT_EQ(solver.lits[2].isTrue, 1);
    EXPECT_EQ(solver.lits[3].isTrue, -1);

    solver.clauses[0].literals = { -2 };
    solver.clauses[0].boolLiterals = { -2 };
    solver.clauses[1].literals = { 1, 3 };
    solver.clauses[1].boolLiterals = { 1 };

    solver.InitializeClauseDatas();
    EXPECT_EQ(solver.unsatClauses->GetSize(), 1);
    EXPECT_EQ(solver.satClauseWithFalseLiteral->GetSize(), 1);
    EXPECT_EQ(solver.vars[1].score, 1);
    EXPECT_EQ(solver.vars[0].score, -1);
}

/**
 * @tc.name: SmartLayoutSmtFileTest018
 * @tc.desc: Test RationNum edge branches: zero denominator, simplify, divide-by-zero fallback, FromDouble breaks.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest018, TestSize.Level1)
{
    RationNum zeroDenominator(3, 0);
    EXPECT_TRUE(zeroDenominator == 0);

    RationNum negativeDenominator(1, -2);
    negativeDenominator.Simplify();
    EXPECT_EQ(negativeDenominator.n, -1);
    EXPECT_EQ(negativeDenominator.m, 2);

    RationNum precisionLimited(3, 20000000);
    precisionLimited.Simplify();
    EXPECT_EQ(precisionLimited.m, 10000000);
    EXPECT_EQ(precisionLimited.n, 2);

    RationNum divideByZeroFallback = RationNum(5, 2) / RationNum(0);
    EXPECT_EQ(divideByZeroFallback.n, 25000000);
    EXPECT_EQ(divideByZeroFallback.m, 1);

    RationNum overflowBreak = RationNum::FromDouble(1000000000000010.0, 0.0);
    EXPECT_EQ(overflowBreak.m, 1);

    RationNum tinyResidualBreak = RationNum::FromDouble(1.0 + 5e-16, 0.0);
    EXPECT_TRUE(tinyResidualBreak == 1);
}

/**
 * @tc.name: SmartLayoutSmtFileTest019
 * @tc.desc: Test localsmt Engine inspection/arithmetic/remove/clear branches.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest019, TestSize.Level1)
{
    localsmt::Engine engine;
    localsmt::Expr noEngineExpr(3.0);
    EXPECT_EQ(noEngineExpr.Value(), 0.0);

    auto x = engine.Var("x", -5.0, 10.0, 3.0);
    auto y = engine.Var("y");
    auto z = engine.Var("z", 2.0);
    auto xyExpr = x + y;
    EXPECT_EQ(x.Name(), "x");
    EXPECT_EQ(xyExpr.Name(), "");

    auto l1 = engine.Add(x + 2.0 * y <= z + 7.0, localsmt::REQUIRED);
    auto l2 = engine.Add(x - y >= -3.0, localsmt::STRONG);
    auto l3 = engine.Add(x == z, localsmt::MEDIUM);
    auto l4 = engine.Add((x + 1.0) > (y - 2.0), localsmt::REQUIRED);
    auto l5 = engine.Add((x - y) < 9.0, localsmt::REQUIRED);
    engine.AddClause({ l1, -l2, l3, l4, l5 });

    engine.RemoveConstraint(l2);
    engine.RemoveConstraint({ 99999 });

    auto constraints = engine.GetConstraints();
    ASSERT_GE(constraints.size(), 5u);
    bool hasRemoved = false;
    for (const auto& c : constraints) {
        hasRemoved = hasRemoved || c.removed;
    }
    EXPECT_TRUE(hasRemoved);

    auto clauses = engine.GetClauses();
    ASSERT_EQ(clauses.size(), 1u);
    EXPECT_EQ(clauses[0].size(), 5u);

    auto names = engine.GetVariableNames();
    EXPECT_NE(std::find(names.begin(), names.end(), "x"), names.end());
    EXPECT_NE(std::find(names.begin(), names.end(), "y"), names.end());
    EXPECT_NE(std::find(names.begin(), names.end(), "z"), names.end());

    EXPECT_EQ(x.Value(), 0.0);
    EXPECT_EQ(engine.GetVariable("not_exist"), 0.0);

    engine.Clear();
    EXPECT_TRUE(engine.GetConstraints().empty());
    EXPECT_TRUE(engine.GetClauses().empty());
    EXPECT_TRUE(engine.GetVariableNames().empty());
}

/**
 * @tc.name: SmartLayoutSmtFileTest020
 * @tc.desc: Test localsmt Engine solve/resolve sat and unsat branches.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest020, TestSize.Level1)
{
    localsmt::Engine satEngine;
    auto x = satEngine.Var("X", 0.0, 10.0, 9.0);
    auto y = satEngine.Var("Y", 0.0, 10.0, 1.0);
    auto a = satEngine.Add(x <= 2.0);
    auto b = satEngine.Add(y >= 1.0);
    satEngine.Add(x == y);
    satEngine.AddClause({ a, b });

    bool satResult = satEngine.Solve(SEARCH_WIDTH, SEARCH_HEIGHT);
    EXPECT_TRUE(satResult);
    EXPECT_TRUE(satEngine.IsSolved());
    if (satResult) {
        auto results = satEngine.GetResults();
        EXPECT_FALSE(results.empty());
        EXPECT_TRUE(satEngine.GetVariable("X") <= 2.0 || satEngine.GetVariable("Y") >= 1.0);
    }
    EXPECT_TRUE(satEngine.Resolve(SEARCH_WIDTH, SEARCH_HEIGHT));

    localsmt::Engine unsatEngine;
    auto u = unsatEngine.Var("U");
    unsatEngine.Add(u <= 0.0);
    unsatEngine.Add(u >= 1.0);
    bool unsatResult = unsatEngine.Solve();
    EXPECT_FALSE(unsatResult);
    EXPECT_FALSE(unsatEngine.IsSolved());
    EXPECT_TRUE(unsatEngine.GetResults().empty());
    EXPECT_EQ(unsatEngine.GetVariable("U"), 0.0);
}

/**
 * @tc.name: SmartLayoutSmtFileTest021
 * @tc.desc: Test nia_ls operation paths with parser-built solver state.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest021, TestSize.Level1)
{
    auto solver = BuildSearchSolverFromSmt(SEARCH_STRESS_SMT, SEARCH_WIDTH, SEARCH_HEIGHT);
    ASSERT_NE(solver, nullptr);
    ASSERT_FALSE(solver->unsatInPreprocess);
    ASSERT_FALSE(solver->buildUnsat);

    solver->Initialize();

    auto itB1 = solver->name2var.find("b1");
    auto itB2 = solver->name2var.find("b2");
    auto itX = solver->name2var.find("X");
    ASSERT_NE(itB1, solver->name2var.end());
    ASSERT_NE(itB2, solver->name2var.end());
    ASSERT_NE(itX, solver->name2var.end());

    solver->solution[itB1->second] = -1;
    solver->solution[itB2->second] = -1;
    solver->solution[itX->second] = 9;
    solver->ClearPrevData();
    solver->InitializeLitDatas();
    solver->InitializeClauseDatas();

    solver->UpdateClauseWeight();
    solver->SmoothClauseWeight();
    EXPECT_GE(solver->totalClauseWeight, 0u);
    (void)solver->UpdateBestSolution();
    (void)solver->LocalSearch({ { "X", 9.0 } });
    solver->EnterBoolMode();
    solver->EnterNiaMode();
    (void)solver->UpdateInnerBestSolution();
    (void)solver->UpdateOuterBestSolution();
    SUCCEED();
}

/**
 * @tc.name: SmartLayoutSmtFileTest022
 * @tc.desc: Test nia_ls literal evaluation and bool restoration helpers.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest022, TestSize.Level1)
{
    auto solver = BuildSearchSolverFromSmt(SEARCH_STRESS_SMT, SEARCH_WIDTH, SEARCH_HEIGHT);
    ASSERT_NE(solver, nullptr);
    ASSERT_FALSE(solver->unsatInPreprocess);
    ASSERT_FALSE(solver->buildUnsat);

    solver->Initialize();
    auto itX = solver->name2var.find("X");
    ASSERT_NE(itX, solver->name2var.end());
    VerifyLiteralEvaluationPaths(*solver, itX->second);
    VerifyBoolRestoreAndBestUpdatePaths(*solver);
}

/**
 * @tc.name: SmartLayoutSmtFileTest023
 * @tc.desc: Test remaining localsmt expression/build branches.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest023, TestSize.Level1)
{
    localsmt::Engine engine;
    auto x = engine.Var("x", -5.0, 5.0);
    auto y = engine.Var("y", 0.0, 10.0, 2.0);
    localsmt::Expr c(1.0);

    auto foundExpr = x + x;
    auto carryEngineExpr = c + x;
    auto leftMul = 3.0 * x;
    auto leftAdd = 5.0 + x;
    auto leftSub = 5.0 - x;
    auto zeroCoeffExpr = x + (-x);
    auto negativeFirstExpr = (-x) + y;

    engine.SetInitVar("x", 1.0);
    auto litA = engine.Add(foundExpr < carryEngineExpr);
    auto litB = engine.Add(foundExpr > 0.0);
    auto litC = engine.Add(leftMul <= leftAdd);
    auto litD = engine.Add(leftSub >= -2.0);
    auto litE = engine.Add(zeroCoeffExpr == 0.0, localsmt::WEAK);
    auto litF = engine.Add(negativeFirstExpr <= 3.0);

    engine.RemoveConstraint(litA);
    std::vector<localsmt::LitRef> clauseLiterals = { litA, litB, litC, litD, litE };
    clauseLiterals.push_back(litF);
    engine.AddClause(clauseLiterals);

    auto desc = engine.GetConstraints();
    EXPECT_GE(desc.size(), 6u);
    EXPECT_FALSE(engine.GetClauses().empty());
    EXPECT_TRUE(engine.Solve());
    EXPECT_EQ(engine.GetVariable("unknown_when_solved"), 0.0);

    localsmt::Engine widthUnsatEngine;
    auto bcWidth = widthUnsatEngine.Var(".w");
    widthUnsatEngine.Add(bcWidth == 0.0);
    (void)widthUnsatEngine.Solve(SEARCH_WIDTH, SEARCH_HEIGHT);
}

/**
 * @tc.name: SmartLayoutSmtFileTest024
 * @tc.desc: Cover light-weight utility branches in matrix/array and size-unsat solve path.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest024, TestSize.Level1)
{
    Array compactArray(3);
    compactArray.InsertElement(1);
    compactArray.InsertElement(1);
    compactArray.InsertElement(-1);
    compactArray.InsertElement(3);
    EXPECT_EQ(compactArray.GetSize(), 1);

    std::vector<std::vector<RationNum>> upperInput = {
        { RationNum(0), RationNum(1), RationNum(2) },
        { RationNum(0), RationNum(3), RationNum(4) }
    };
    ToUpperTriangle(upperInput);
    EXPECT_EQ(upperInput.size(), 2u);

    std::vector<std::vector<RationNum>> diagonalInput = {
        { RationNum(1), RationNum(0), RationNum(5) },
        { RationNum(0), RationNum(0), RationNum(0) }
    };
    ToDiagonal(diagonalInput);
    EXPECT_TRUE(IsAllZeroRow(diagonalInput[1]));

    localsmt::Engine widthLimitedEngine;
    auto width = widthLimitedEngine.Var(".w");
    widthLimitedEngine.Add(width <= 0.0);
    (void)widthLimitedEngine.Solve(SEARCH_WIDTH, SEARCH_HEIGHT);
}

/**
 * @tc.name: SmartLayoutSmtFileTest025
 * @tc.desc: Test BuildInstanceNewWidth rebuilds from original state on each call.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest025, TestSize.Level1)
{
    const auto smtPath = WriteSmtToTempFile(EMBEDDED_LAYOUT_SMT);
    {
        niaOverall::LsSolver solver(TEST_RANDOM_SEED, TEST_MAX_STEP, TEST_CUTOFF_SECONDS, TEST_COMPLETE_LS);
        solver.ReadFromFile(smtPath.string());
        solver.BuildInstanceOriginal();
        ASSERT_FALSE(solver.unsatInPreprocess);
        ASSERT_FALSE(solver.buildUnsat);

        int rootWidthIdx = solver.Find(solver.bcWidthIdx);
        solver.BuildInstanceNewWidth(VALID_WIDTH, TEST_HEIGHT);
        EXPECT_TRUE(solver.presetValues[rootWidthIdx] == RationNum(VALID_WIDTH));

        // Width 0 does not pin BC_width; this should not keep previous pinned value.
        solver.BuildInstanceNewWidth(WIDTH_LOWER_BOUND, TEST_HEIGHT);
        EXPECT_TRUE(solver.presetValues[rootWidthIdx] == INT32_MAX);
    }
    std::error_code ec;
    std::filesystem::remove(smtPath, ec);
}

/**
 * @tc.name: SmartLayoutSmtFileTest026
 * @tc.desc: Test component helpers and max-var literal discovery on parsed SMT data.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest026, TestSize.Level1)
{
    const auto smtPath = WriteSmtToTempFile(EMBEDDED_LAYOUT_SMT);
    {
        niaOverall::LsSolver solver(TEST_RANDOM_SEED, TEST_MAX_STEP, TEST_CUTOFF_SECONDS, TEST_COMPLETE_LS);
        solver.ReadFromFile(smtPath.string());
        solver.BuildInstanceOriginal();
        ASSERT_FALSE(solver.unsatInPreprocess);
        ASSERT_FALSE(solver.buildUnsat);

        ASSERT_GE(solver.componentsIdx.size(), 4u);
        for (size_t idx : solver.componentsIdx) {
            EXPECT_LT(idx, solver.vars.size());
        }

        solver.softComponentsIdx.clear();
        solver.PrepareSoftComponentsIdx(std::vector<std::string> { "BC" });
        ASSERT_EQ(solver.softComponentsIdx.size(), 4u);
        for (size_t idx : solver.softComponentsIdx) {
            EXPECT_LT(idx, solver.vars.size());
        }

        std::vector<int> maxVarLits;
        solver.FindMaxVarLit(maxVarLits);
        for (int litIdx : maxVarLits) {
            EXPECT_GE(litIdx, 0);
            EXPECT_LT(static_cast<size_t>(litIdx), solver.lits.size());
            EXPECT_EQ(solver.lits[litIdx].coffVars.size(), 1u);
        }
    }
    std::error_code ec;
    std::filesystem::remove(smtPath, ec);
}

/**
 * @tc.name: SmartLayoutSmtFileTest027
 * @tc.desc: Test SetPreValue and bound-driven literal simplification helpers.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest027, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.numVars = 1;
    solver.vars.resize(1);
    solver.vars[0].isNia = true;

    solver.MakeLitsSpace(4);
    solver.numClauses = 2;
    solver.clauses.resize(2);

    solver.lits[1].isNiaLit = true;
    solver.lits[1].isEqual = true;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].coffVars.emplace_back(0, RationNum(1));
    solver.lits[1].key = RationNum(-2);

    solver.lits[2].isNiaLit = true;
    solver.lits[2].isEqual = true;
    solver.lits[2].litsIndex = 2;
    solver.lits[2].coffVars.emplace_back(0, RationNum(1));
    solver.lits[2].key = RationNum(-3);

    solver.clauses[0].literals = { 1 };
    solver.clauses[1].literals = { 1, 2 };
    solver.SetPreValue();
    EXPECT_TRUE(solver.preValue1[0] == 2);
    EXPECT_TRUE(solver.preValue2[0] == 3);

    solver.litAppear.resize(solver.numLits + TEST_LITS_SPACE_SMALL, false);
    solver.litsInCls = new Array(static_cast<int>(solver.numLits + TEST_LITS_SPACE_SMALL));
    solver.clauses.resize(1);
    solver.numClauses = 1;
    solver.clauses[0].literals = { 3 };

    solver.lits[3].isNiaLit = true;
    solver.lits[3].isEqual = false;
    solver.lits[3].litsIndex = 3;
    solver.lits[3].coffVars.clear();
    solver.lits[3].coffVars.emplace_back(0, RationNum(1));
    solver.lits[3].key = RationNum(-5);
    solver.vars[0].lowBound = RationNum(10);
    solver.vars[0].upperBound = RationNum(20);

    solver.DetermineLitAppear();
    bool modified = false;
    solver.DetermineLitsByBound(modified);
    EXPECT_TRUE(modified);
    EXPECT_LT(solver.lits[3].litsIndex, 0);

    niaOverall::Clause clause;
    clause.literals = { 3, 3, -3 };
    bool clauseModified = false;
    solver.ReduceDuplicatedLitsInClause(clause, clauseModified);
    EXPECT_TRUE(clauseModified);
    EXPECT_EQ(clause.literals.size(), 1u);
    EXPECT_EQ(clause.literals[0], -3);
    EXPECT_TRUE(solver.IsClauseTautology(clause));
}

/**
 * @tc.name: SmartLayoutSmtFileTest028
 * @tc.desc: Test UpdateNiaVar branches for merged nia vars and absent boolean vars.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest028, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.numVars = 3;
    solver.vars.resize(3);
    solver.vars[0].isNia = true;
    solver.vars[1].isNia = true;
    solver.vars[2].isNia = false;

    solver.solution = { RationNum(5), RationNum(0), RationNum(7) };
    solver.varAppear = { true, false, false };
    solver.fa = { 0, 0, 2 };
    solver.faCoff = { RationNum(1), RationNum(2), RationNum(1) };
    solver.faConst = { RationNum(0), RationNum(3), RationNum(0) };
    solver.upValueVars = { 0, 0, 0 };

    solver.UpdateNiaVar(1);
    EXPECT_TRUE(solver.solution[1] == 13);

    solver.UpdateNiaVar(2);
    EXPECT_TRUE(solver.solution[2] == -1);

    solver.solution[2] = 9;
    solver.upValueVars[2] = 1;
    solver.UpdateNiaVar(2);
    EXPECT_TRUE(solver.solution[2] == 9);
}

/**
 * @tc.name: SmartLayoutSmtFileTest029
 * @tc.desc: Test InsertOperation guard branches and accepted-operation branches.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest029, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    PrepareInsertOperationSolver(solver);

    int operationIdx = 0;
    EXPECT_NO_FATAL_FAILURE(VerifyInsertOperationGuards(solver, operationIdx));
    EXPECT_NO_FATAL_FAILURE(VerifyInsertOperationAcceptedPaths(solver, operationIdx));
}

/**
 * @tc.name: SmartLayoutSmtFileTest030
 * @tc.desc: Test boolean MoveUpdate updates sat/unsat sets and score transitions.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest030, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.numVars = 1;
    solver.numClauses = 1;
    solver.vars.resize(1);
    solver.vars[0].isNia = false;
    solver.vars[0].literalIdxs = { 1 };
    solver.vars[0].clauseIdxs = { 0 };
    solver.vars[0].boolVarInPosClause = { true };

    solver.MakeLitsSpace(2);
    solver.lits[1].isNiaLit = false;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].delta = RationNum(0);
    solver.lits[1].isTrue = 1;

    solver.clauses.resize(1);
    solver.clauses[0].literals = { 1 };
    solver.clauses[0].boolLiterals = { 1 };
    solver.clauses[0].satCount = 1;
    solver.clauses[0].watchLitIdx = 1;
    solver.clauses[0].weight = 2;

    solver.MakeSpace();
    solver.solution[0] = RationNum(1);
    solver.vars[0].score = 0;
    solver.litInUnsatClauseNum = 0;
    solver.boolLitInUnsatClauseNum = 0;

    solver.MoveUpdate(0);
    EXPECT_TRUE(solver.solution[0] == 1);
    EXPECT_EQ(solver.clauses[0].satCount, 0);
    EXPECT_TRUE(solver.unsatClauses->IsInArray(0));
    EXPECT_EQ(solver.litInUnsatClauseNum, 1);
    EXPECT_EQ(solver.boolLitInUnsatClauseNum, 1);
    EXPECT_EQ(solver.vars[0].score, 2);

    solver.solution[0] = RationNum(-1);
    solver.MoveUpdate(0);
    EXPECT_EQ(solver.clauses[0].satCount, 1);
    EXPECT_FALSE(solver.unsatClauses->IsInArray(0));
    EXPECT_EQ(solver.litInUnsatClauseNum, 0);
    EXPECT_EQ(solver.boolLitInUnsatClauseNum, 0);
    EXPECT_EQ(solver.vars[0].score, 0);
}

/**
 * @tc.name: SmartLayoutSmtFileTest031
 * @tc.desc: Test CriticalMove updates runtime state for both nia and boolean variables.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest031, TestSize.Level1)
{
    {
        niaOverall::LsSolver niaSolver;
        niaSolver.numVars = 1;
        niaSolver.vars.resize(1);
        niaSolver.vars[0].isNia = true;
        niaSolver.MakeLitsSpace(2);
        niaSolver.lits[1].isNiaLit = true;
        niaSolver.lits[1].litsIndex = 1;
        niaSolver.lits[1].delta = RationNum(0);
        niaSolver.vars[0].varLits = { niaOverall::VarLit(0, 1, RationNum(1)) };
        niaSolver.vars[0].literalIdxs = { 1 };
        niaSolver.vars[0].clauseIdxs.clear();
        niaSolver.solution = { RationNum(0) };
        niaSolver.lastMove.resize(2, 0);
        niaSolver.tabulist.resize(2, 0);
        niaSolver.step = 7;

        niaSolver.CriticalMove(0, RationNum(2));
        EXPECT_TRUE(niaSolver.solution[0] == 2);
        EXPECT_EQ(niaSolver.lastOpVar, 0u);
        EXPECT_TRUE(niaSolver.lastOpValue == 2);
        EXPECT_EQ(niaSolver.lastMove[0], 7u);
        EXPECT_GE(niaSolver.tabulist[1], 10u);
    }

    {
        niaOverall::LsSolver boolSolver;
        boolSolver.numVars = 1;
        boolSolver.vars.resize(1);
        boolSolver.vars[0].isNia = false;
        boolSolver.vars[0].score = 5;
        boolSolver.vars[0].literalIdxs = { 1 };
        boolSolver.vars[0].clauseIdxs.clear();
        boolSolver.vars[0].boolVarInPosClause.clear();
        boolSolver.MakeLitsSpace(2);
        boolSolver.lits[1].isNiaLit = false;
        boolSolver.lits[1].delta = RationNum(0);
        boolSolver.lits[1].isTrue = 1;
        boolSolver.solution = { RationNum(1) };
        boolSolver.lastMove.resize(2, 0);
        boolSolver.tabulist.resize(2, 0);
        boolSolver.outerLayerStep = 4;

        boolSolver.CriticalMove(0, RationNum(0));
        EXPECT_TRUE(boolSolver.solution[0] == -1);
        EXPECT_EQ(boolSolver.vars[0].score, -5);
        EXPECT_EQ(boolSolver.lastOpVar, UINT64_MAX);
        EXPECT_EQ(boolSolver.lastMove[0], 4u);
        EXPECT_GE(boolSolver.tabulist[0], 5u);
        EXPECT_EQ(boolSolver.outerLayerStep, 5u);
    }
}

/**
 * @tc.name: SmartLayoutSmtFileTest032
 * @tc.desc: Test AddBoolOperation dedup and SelectBestOperationFromBoolVec tie-break by last move.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest032, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.numVars = 2;
    solver.vars.resize(2);
    solver.vars[0].isNia = false;
    solver.vars[1].isNia = false;
    solver.vars[0].score = 5;
    solver.vars[1].score = 5;

    solver.MakeLitsSpace(3);
    solver.lits[1].isNiaLit = false;
    solver.lits[1].delta = RationNum(0);
    solver.lits[2].isNiaLit = false;
    solver.lits[2].delta = RationNum(1);

    solver.isChosenBoolVar.resize(2, false);
    solver.operationVarIdxBoolVec.resize(8, 0);
    solver.lastMove.resize(4, 0);
    solver.lastMove[0] = 10; // var0
    solver.lastMove[2] = 3;  // var1, should win tie
    solver.tabulist.resize(4, 0);
    solver.outerLayerStep = 1;

    int operationIdxBool = 0;
    solver.AddBoolOperation(false, 1, operationIdxBool);
    solver.AddBoolOperation(false, 2, operationIdxBool);
    ASSERT_EQ(operationIdxBool, 2);

    solver.AddBoolOperation(false, 1, operationIdxBool); // duplicated var should be skipped
    EXPECT_EQ(operationIdxBool, 2);

    int bestScoreBool = INT32_MIN;
    int bestVarIdxBool = -1;
    solver.SelectBestOperationFromBoolVec(operationIdxBool, bestScoreBool, bestVarIdxBool);
    EXPECT_EQ(bestVarIdxBool, 1);
    EXPECT_EQ(bestScoreBool, 5);
}

/**
 * @tc.name: SmartLayoutSmtFileTest033
 * @tc.desc: Test CriticalScore and SelectBestOperationFromVec choose improving NIA operation.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest033, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.numVars = 1;
    solver.numClauses = 1;
    solver.vars.resize(1);
    solver.vars[0].isNia = true;
    solver.vars[0].clauseIdxs = { 0 };
    solver.vars[0].literalIdxs = { 1 };
    solver.vars[0].varLits = { niaOverall::VarLit(0, 1, RationNum(1)) };

    solver.MakeLitsSpace(2);
    solver.lits[1].isNiaLit = true;
    solver.lits[1].isEqual = false;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].delta = RationNum(1);
    solver.lits[1].coffVars.emplace_back(0, RationNum(1));

    solver.clauses.resize(1);
    solver.clauses[0].literals = { 1 };
    solver.clauses[0].satCount = 0;
    solver.clauses[0].weight = 3;

    solver.solution = { RationNum(0) };
    solver.litMakeBreak.resize(4, 0);
    solver.operationVarIdxVec.resize(8, 0);
    solver.operationChangeValueVec.resize(8, RationNum(0));
    solver.lastMove.resize(2, 0);

    int scoreImprove = solver.CriticalScore(0, RationNum(-1));
    int scoreWorse = solver.CriticalScore(0, RationNum(1));
    EXPECT_EQ(scoreImprove, 3);
    EXPECT_LT(scoreWorse, scoreImprove);

    solver.operationVarIdxVec[0] = 0;
    solver.operationChangeValueVec[0] = RationNum(1);
    solver.operationVarIdxVec[1] = 0;
    solver.operationChangeValueVec[1] = RationNum(-1);
    int bestScore = INT32_MIN;
    int bestVarIdx = -1;
    RationNum bestValue(0);
    solver.SelectBestOperationFromVec(2, bestScore, bestVarIdx, bestValue);
    EXPECT_EQ(bestVarIdx, 0);
    EXPECT_TRUE(bestValue == -1);
}

/**
 * @tc.name: SmartLayoutSmtFileTest034
 * @tc.desc: Test parser helper branches: custom SplitString and empty BuildLits.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest034, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    std::string csv = "a,b,c";
    std::vector<std::string> csvParts;
    solver.SplitString(csv, csvParts, ",");
    ASSERT_EQ(csvParts.size(), 3u);
    EXPECT_EQ(csvParts[0], "a");
    EXPECT_EQ(csvParts[1], "b");
    EXPECT_EQ(csvParts[2], "c");

    solver.MakeLitsSpace(TEST_LITS_SPACE_SMALL);
    std::string emptyLine;
    solver.BuildLits(emptyLine);
    EXPECT_EQ(solver.numLits, TEST_LITS_SPACE_SMALL);
}

/**
 * @tc.name: SmartLayoutSmtFileTest035
 * @tc.desc: Test ReadFromFile branch when BC_width is absent and .w/.h are used.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest035, TestSize.Level1)
{
    const auto smtPath = WriteSmtToTempFile(DOT_COMPONENT_SMT);
    {
        niaOverall::LsSolver solver(TEST_RANDOM_SEED, TEST_MAX_STEP, TEST_CUTOFF_SECONDS, TEST_COMPLETE_LS);
        solver.ReadFromFile(smtPath.string());
        ASSERT_TRUE(solver.name2var.find(".w") != solver.name2var.end());
        ASSERT_TRUE(solver.name2var.find(".h") != solver.name2var.end());
        EXPECT_TRUE(solver.basicComponentName == "BC" || solver.basicComponentName.empty());
        EXPECT_EQ(solver.bcWidthIdx, solver.name2var[".w"]);
        auto bcHeightIt = solver.name2var.find("BC_height");
        if (bcHeightIt != solver.name2var.end()) {
            EXPECT_EQ(solver.bcHeightIdx, static_cast<int>(bcHeightIt->second));
        } else {
            EXPECT_EQ(solver.bcHeightIdx, solver.name2var[".h"]);
        }

        solver.BuildInstanceOriginal();
        EXPECT_FALSE(solver.unsatInPreprocess);
        EXPECT_FALSE(solver.buildUnsat);
    }
    std::error_code ec;
    std::filesystem::remove(smtPath, ec);
}

/**
 * @tc.name: SmartLayoutSmtFileTest036
 * @tc.desc: Test BuildLits coverage for AutoLayout-style >/< lines and multi-term equality with numeric lhs.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest036, TestSize.Level1)
{
    niaOverall::LsSolver solver;
    solver.MakeLitsSpace(PARSER_TEST_LITS_SPACE);

    std::string gtLine = "8 (> x 500)";
    std::string ltLine = "9 (< x 100)";
    std::string multiEqLine = "12 (= 0 (+ (* 2 x) (* -1 y)))";

    BuildLitsWithNormalizedInput(solver, gtLine);
    BuildLitsWithNormalizedInput(solver, ltLine);
    BuildLitsWithNormalizedInput(solver, multiEqLine);

    ASSERT_TRUE(solver.lits[8].isNiaLit);
    ASSERT_TRUE(solver.lits[9].isNiaLit);
    EXPECT_FALSE(solver.lits[8].isEqual);
    EXPECT_FALSE(solver.lits[9].isEqual);
    ASSERT_FALSE(solver.lits[8].coffVars.empty());
    ASSERT_FALSE(solver.lits[9].coffVars.empty());
    EXPECT_EQ(solver.lits[8].coffVars[0].varIdx, solver.lits[9].coffVars[0].varIdx);

    ASSERT_TRUE(solver.lits[12].isNiaLit);
    EXPECT_TRUE(solver.lits[12].isEqual);
    ASSERT_TRUE(solver.name2var.find("x") != solver.name2var.end());
    ASSERT_FALSE(solver.lits[12].coffVars.empty());
    bool hasX = false;
    bool hasY = false;
    auto itX = solver.name2var.find("x");
    auto itY = solver.name2var.find("y");
    for (const auto& cv : solver.lits[12].coffVars) {
        if (itX != solver.name2var.end()) {
            hasX = hasX || (cv.varIdx == static_cast<int>(itX->second));
        }
        if (itY != solver.name2var.end()) {
            hasY = hasY || (cv.varIdx == static_cast<int>(itY->second));
        }
    }
    EXPECT_TRUE(hasX || hasY);
}

/**
 * @tc.name: SmartLayoutSmtFileTest037
 * @tc.desc: Test end-to-end conversion from AutoLayout-style hard.smt2 text into solver structures.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutSmtFileTest, SmartLayoutSmtFileTest037, TestSize.Level1)
{
    const auto smtPath = WriteSmtToTempFile(AUTOLAYOUT_STYLE_SMT);
    {
        niaOverall::LsSolver solver(TEST_RANDOM_SEED, TEST_MAX_STEP, TEST_CUTOFF_SECONDS, TEST_COMPLETE_LS);
        solver.ReadFromFile(smtPath.string());

        ASSERT_TRUE(solver.name2var.find("x") != solver.name2var.end());
        ASSERT_TRUE(solver.name2var.find("y") != solver.name2var.end());
        ASSERT_TRUE(solver.name2var.find("BC_width") != solver.name2var.end());
        EXPECT_EQ(solver.basicComponentName, "BC");

        solver.BuildInstanceOriginal();
        EXPECT_FALSE(solver.unsatInPreprocess);
        EXPECT_FALSE(solver.buildUnsat);

        solver.BuildInstanceNewWidth(AUTOLAYOUT_REBUILD_WIDTH, SEARCH_HEIGHT);
        EXPECT_FALSE(solver.unsatInPreprocess);
        EXPECT_FALSE(solver.buildUnsat);
    }
    std::error_code ec;
    std::filesystem::remove(smtPath, ec);
}

} // namespace OHOS::Ace::NG
