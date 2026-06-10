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

#include <gtest/gtest.h>
// NOLINTBEGIN
#define private public
#define protected public
#include "core/components_ng/pattern/smart_layout/engine/localsmt/localsmt.h"
#undef private
#undef protected
// NOLINTEND
using namespace testing;
using namespace testing::ext;
using namespace localsmt;

namespace niaOverall {
bool IsSameCls(const std::vector<int>& cl1, const std::vector<int>& cl2);
void PrintVec(const std::vector<std::vector<int>>& cl);
} // namespace niaOverall

namespace OHOS::Ace::NG {
using namespace niaOverall;

namespace {
constexpr double ZERO_VALUE = 0.0;
constexpr double HALF_VALUE = 0.5;
constexpr double ONE_VALUE = 1.0;
constexpr double TWO_VALUE = 2.0;
constexpr double THREE_VALUE = 3.0;
constexpr double FIVE_VALUE = 5.0;
constexpr double NINE_VALUE = 9.0;
constexpr double TWENTY_VALUE = 20.0;
constexpr double FIFTY_VALUE = 50.0;
constexpr double HUNDRED_VALUE = 100.0;
constexpr double NEGATIVE_ONE_VALUE = -1.0;
constexpr double NEGATIVE_TEN_VALUE = -10.0;
constexpr double POSITIVE_TEN_VALUE = 10.0;
constexpr double LARGE_NEGATIVE_BOUND = -1000.0;
constexpr double LARGE_POSITIVE_BOUND = 1000.0;
constexpr double VALUE_EPSILON = 1e-6;
constexpr double SOLUTION_TOLERANCE = 1e-3;
} // namespace

class SmartLayoutLocalSmtTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SmartLayoutLocalSmtTest000
 * @tc.desc: Level0 sanity test for localsmt basic feasible solve path.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest000, TestSize.Level0)
{
    Engine engine;
    Expr x = engine.Var("x");
    engine.Add(x >= ZERO_VALUE);
    ASSERT_TRUE(engine.Solve());
}

/**
 * @tc.name: SmartLayoutLocalSmtTest001
 * @tc.desc: Test localsmt can solve a basic feasible system.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest001, TestSize.Level1)
{
    Engine engine;
    Expr x = engine.Var("x");
    Expr y = engine.Var("y");
    engine.Add(x + y >= ONE_VALUE);
    engine.Add(x - y >= ZERO_VALUE);

    ASSERT_TRUE(engine.Solve());
}

/**
 * @tc.name: SmartLayoutLocalSmtTest002
 * @tc.desc: Test localsmt satisfies multiple linear constraints.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest002, TestSize.Level1)
{
    Engine engine;
    Expr a = engine.Var("a");
    Expr b = engine.Var("b");
    engine.Add(a + b >= ONE_VALUE);
    engine.Add(a - b >= ZERO_VALUE);
    engine.Add(b >= ZERO_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_GE(a.Value() + b.Value(), ONE_VALUE - VALUE_EPSILON);
    EXPECT_GE(a.Value() - b.Value(), ZERO_VALUE - VALUE_EPSILON);
    EXPECT_GE(b.Value(), ZERO_VALUE - VALUE_EPSILON);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest003
 * @tc.desc: Test localsmt keeps equal variables synchronized.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest003, TestSize.Level1)
{
    Engine engine;
    Expr p = engine.Var("p");
    Expr q = engine.Var("q");
    engine.Add(p == q);
    engine.Add(p >= ZERO_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_NEAR(p.Value(), q.Value(), SOLUTION_TOLERANCE);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest004
 * @tc.desc: Test localsmt reports no solution for conflicting constraints.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest004, TestSize.Level1)
{
    Engine engine;
    Expr m = engine.Var("m", NEGATIVE_TEN_VALUE, POSITIVE_TEN_VALUE);
    Expr n = engine.Var("n", NEGATIVE_TEN_VALUE, POSITIVE_TEN_VALUE);
    engine.Add(m + n >= ZERO_VALUE);
    engine.Add(m + n <= NEGATIVE_ONE_VALUE);

    ASSERT_FALSE(engine.Solve());
}

/**
 * @tc.name: SmartLayoutLocalSmtTest005
 * @tc.desc: Test localsmt respects variable bounds after solving.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest005, TestSize.Level1)
{
    Engine engine;
    Expr z = engine.Var("z", FIVE_VALUE, POSITIVE_TEN_VALUE);
    engine.Add(z >= ZERO_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_GE(z.Value(), FIVE_VALUE - VALUE_EPSILON);
    EXPECT_LE(z.Value(), POSITIVE_TEN_VALUE + VALUE_EPSILON);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest006
 * @tc.desc: Test localsmt solves a three variable equality system.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest006, TestSize.Level1)
{
    Engine engine;
    Expr i = engine.Var("i", ZERO_VALUE, HUNDRED_VALUE);
    Expr j = engine.Var("j", ZERO_VALUE, HUNDRED_VALUE);
    Expr k = engine.Var("k", ZERO_VALUE, HUNDRED_VALUE);
    engine.Add(i + j + k == HUNDRED_VALUE);
    engine.Add(i - j >= ZERO_VALUE);
    engine.Add(j - k >= ZERO_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_NEAR(i.Value() + j.Value() + k.Value(), HUNDRED_VALUE, SOLUTION_TOLERANCE);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest007
 * @tc.desc: Test localsmt handles fractional solutions.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest007, TestSize.Level1)
{
    Engine engine;
    Expr f = engine.Var("f");
    engine.Add(TWO_VALUE * f == ONE_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_NEAR(f.Value(), HALF_VALUE, VALUE_EPSILON);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest008
 * @tc.desc: Test localsmt solves mixed linear constraints with non-negative bounds.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest008, TestSize.Level1)
{
    Engine engine;
    Expr a = engine.Var("a");
    Expr b = engine.Var("b");
    Expr c = engine.Var("c");
    engine.Add(TWO_VALUE * a + THREE_VALUE * b - c >= POSITIVE_TEN_VALUE);
    engine.Add(a + b + c <= TWENTY_VALUE);
    engine.Add(a >= ZERO_VALUE);
    engine.Add(b >= ZERO_VALUE);
    engine.Add(c >= ZERO_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_GE(TWO_VALUE * a.Value() + THREE_VALUE * b.Value() - c.Value(),
        POSITIVE_TEN_VALUE - VALUE_EPSILON);
    EXPECT_LE(a.Value() + b.Value() + c.Value(), TWENTY_VALUE + VALUE_EPSILON);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest009
 * @tc.desc: Test localsmt propagates equality across a variable chain.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest009, TestSize.Level1)
{
    Engine engine;
    Expr x1 = engine.Var("x1");
    Expr x2 = engine.Var("x2");
    Expr x3 = engine.Var("x3");
    engine.Add(x1 == x2);
    engine.Add(x2 == x3);
    engine.Add(x1 >= FIVE_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_NEAR(x1.Value(), x2.Value(), SOLUTION_TOLERANCE);
    EXPECT_NEAR(x2.Value(), x3.Value(), SOLUTION_TOLERANCE);
    EXPECT_GE(x3.Value(), FIVE_VALUE - SOLUTION_TOLERANCE);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest010
 * @tc.desc: Test localsmt supports repeated solve calls on the same engine.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest010, TestSize.Level1)
{
    Engine engine;
    Expr r = engine.Var("r", ZERO_VALUE, HUNDRED_VALUE);
    engine.Add(r >= FIFTY_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_GE(r.Value(), FIFTY_VALUE - SOLUTION_TOLERANCE);
    ASSERT_TRUE(engine.Solve());
    ASSERT_TRUE(engine.Solve());
}

/**
 * @tc.name: SmartLayoutLocalSmtTest011
 * @tc.desc: Test localsmt solves simple bounded inequalities.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest011, TestSize.Level1)
{
    Engine engine;
    Expr l = engine.Var("l", LARGE_NEGATIVE_BOUND, LARGE_POSITIVE_BOUND);
    engine.Add(THREE_VALUE * l <= NINE_VALUE);
    engine.Add(l >= ZERO_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_LE(THREE_VALUE * l.Value(), NINE_VALUE + VALUE_EPSILON);
    EXPECT_GE(l.Value(), ZERO_VALUE - VALUE_EPSILON);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest012
 * @tc.desc: Test localsmt keeps a bounded sum feasible at the lower boundary.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest012, TestSize.Level1)
{
    Engine engine;
    Expr s1 = engine.Var("s1", ZERO_VALUE, FIFTY_VALUE);
    Expr s2 = engine.Var("s2", ZERO_VALUE, FIFTY_VALUE);
    Expr s3 = engine.Var("s3", ZERO_VALUE, FIFTY_VALUE);
    engine.Add(s1 + s2 + s3 <= POSITIVE_TEN_VALUE + TWENTY_VALUE);
    engine.Add(s1 >= POSITIVE_TEN_VALUE);
    engine.Add(s2 >= POSITIVE_TEN_VALUE);
    engine.Add(s3 >= POSITIVE_TEN_VALUE);

    ASSERT_TRUE(engine.Solve());
    EXPECT_LE(s1.Value() + s2.Value() + s3.Value(), POSITIVE_TEN_VALUE + TWENTY_VALUE + VALUE_EPSILON);
    EXPECT_GE(s1.Value(), POSITIVE_TEN_VALUE - VALUE_EPSILON);
    EXPECT_GE(s2.Value(), POSITIVE_TEN_VALUE - VALUE_EPSILON);
    EXPECT_GE(s3.Value(), POSITIVE_TEN_VALUE - VALUE_EPSILON);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_IsSameCls_PrintVec
 * @tc.desc: Test IsSameCls PrintVec.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_IsSameCls_PrintVec, TestSize.Level1)
{
    std::vector<int> a = { 1, 2, 3 };
    std::vector<int> b = { 1, 2 };
    std::vector<int> c = { 1, 2, 4 };
    std::vector<int> d = { 1, 2, 3 };
    std::vector<int> e;
    EXPECT_FALSE(IsSameCls(a, b));
    EXPECT_FALSE(IsSameCls(a, c));
    EXPECT_TRUE(IsSameCls(a, d));
    EXPECT_TRUE(IsSameCls(e, e));
    PrintVec({});
    PrintVec({ { 1, -2, 3 } });
    PrintVec({ { 1, 2 }, { -1, 3 }, { 4, -2, 5 } });
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_RemoveClauseIdxFromVar
 * @tc.desc: Test RemoveClauseIdxFromVar.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_RemoveClauseIdxFromVar, TestSize.Level1)
{
    auto setupSolver = [](LsSolver& solver, const std::vector<int>& clauseIdxs) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.vars[0].clauseIdxs = clauseIdxs;
        solver.vars[0].isNia = false;
        Clause cl;
        cl.literals = { 1 };
        solver.lits[1].isNiaLit = false;
        solver.lits[1].delta = 0;
        solver.lits[1].litsIndex = 1;
        solver.clauses.push_back(cl);
    };
    LsSolver s1;
    setupSolver(s1, { 0, 1, 2 });
    s1.DeleteClausesOfVar(0, 1);
    EXPECT_EQ(s1.vars[0].clauseIdxs.size(), 2);

    LsSolver s2;
    setupSolver(s2, { 1, 2 });
    s2.DeleteClausesOfVar(0, 1);
    EXPECT_EQ(s2.vars[0].clauseIdxs.size(), 2);

    LsSolver s3;
    setupSolver(s3, {});
    s3.DeleteClausesOfVar(0, 1);
    EXPECT_EQ(s3.vars[0].clauseIdxs.size(), 0);

    LsSolver s4;
    setupSolver(s4, { 0 });
    s4.DeleteClausesOfVar(0, 1);
    EXPECT_EQ(s4.vars[0].clauseIdxs.size(), 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_CountNegClauseTautology
 * @tc.desc: Test CountNegClauseTautology.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_CountNegClauseTautology, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
    };
    LsSolver s1;
    setup(s1);
    s1.clauses.push_back(Clause{ { 2, 3 } });
    s1.clauses.push_back(Clause{ { -3, 4 } });
    s1.lits[2].isNiaLit = false;
    s1.lits[2].delta = 0;
    s1.lits[3].isNiaLit = false;
    s1.lits[3].delta = 1;
    s1.lits[4].isNiaLit = false;
    s1.lits[4].delta = 2;
    EXPECT_EQ(s1.CountNegClauseTautology(0, 1, 0), 1);

    LsSolver s2;
    setup(s2);
    s2.clauses.push_back(Clause{ { 2, 3 } });
    s2.clauses.push_back(Clause{ { 4, 5 } });
    s2.lits[2].isNiaLit = false;
    s2.lits[2].delta = 0;
    s2.lits[3].isNiaLit = false;
    s2.lits[3].delta = 1;
    s2.lits[4].isNiaLit = false;
    s2.lits[4].delta = 2;
    s2.lits[5] = s2.lits[4];
    EXPECT_EQ(s2.CountNegClauseTautology(0, 1, 0), 0);

    LsSolver s3;
    setup(s3);
    s3.clauses.push_back(Clause{ { 1, 3 } });
    s3.clauses.push_back(Clause{ { -1, 3 } });
    s3.lits[1].isNiaLit = false;
    s3.lits[1].delta = 0;
    s3.lits[3].isNiaLit = false;
    s3.lits[3].delta = 1;
    EXPECT_EQ(s3.CountNegClauseTautology(0, 1, 0), 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_AddClauseToData
 * @tc.desc: Test AddClauseToData.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_AddClauseToData, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.numClauses = 0;
    };
    LsSolver s1;
    setup(s1);
    s1.lits[1].isNiaLit = false;
    s1.lits[1].delta = 0;
    s1.lits[1].litsIndex = 1;
    s1.vars[0].isNia = false;
    std::unordered_map<uint64_t, int> map1;
    std::vector<uint64_t> lit1;
    s1.AddClauseToData(Clause{ { 1 } }, 42, map1, lit1);
    EXPECT_EQ(s1.numClauses, 1);
    EXPECT_EQ(s1.vars[0].clauseIdxs.size(), 1);

    LsSolver s2;
    setup(s2);
    s2.lits[1].isNiaLit = true;
    s2.lits[1].litsIndex = 1;
    std::unordered_map<uint64_t, int> map2;
    std::vector<uint64_t> lit2;
    s2.AddClauseToData(Clause{ { 1 } }, 99, map2, lit2);
    EXPECT_EQ(s2.numClauses, 1);

    LsSolver s3;
    setup(s3);
    s3.lits[1].isNiaLit = true;
    s3.lits[1].litsIndex = 1;
    s3.lits[2].isNiaLit = false;
    s3.lits[2].delta = 1;
    s3.lits[2].litsIndex = 2;
    s3.vars[1].isNia = false;
    std::unordered_map<uint64_t, int> map3;
    std::vector<uint64_t> lit3;
    s3.AddClauseToData(Clause{ { 1, 2 } }, 77, map3, lit3);
    EXPECT_EQ(s3.numClauses, 1);
    EXPECT_EQ(s3.vars[1].clauseIdxs.size(), 1);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_ResolveClauses
 * @tc.desc: Test ResolveClauses.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_ResolveClauses, TestSize.Level1)
{
    auto setupLits = [](LsSolver& solver, int count) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.numClauses = 0;
        for (int i = 1; i <= count; i++) {
            solver.lits[i].isNiaLit = false;
            solver.lits[i].delta = (i - 1) % 2;
            solver.lits[i].litsIndex = i;
            solver.vars[(i - 1) % 2].isNia = false;
        }
    };
    LsSolver s1;
    setupLits(s1, 3);
    LsSolver::ResolveContext ctx1;
    ctx1.posClauses.resize(10);
    ctx1.negClauses.resize(10);
    ctx1.posClauses[0] = 0;
    ctx1.posClauseSize = 1;
    ctx1.negClauses[0] = 1;
    ctx1.negClauseSize = 1;
    s1.clauses.push_back(Clause{ { 1, 2 } });
    s1.clauses.push_back(Clause{ { -1, 3 } });
    std::unordered_map<uint64_t, int> rmap1;
    std::vector<uint64_t> rlit1;
    s1.ResolveClauses(0, ctx1, rmap1, rlit1);
    EXPECT_GE(s1.numClauses, 1);

    LsSolver s2;
    setupLits(s2, 4);
    LsSolver::ResolveContext ctx2;
    ctx2.posClauses.resize(10);
    ctx2.negClauses.resize(10);
    ctx2.posClauses[0] = 0;
    ctx2.posClauses[1] = 1;
    ctx2.posClauseSize = 2;
    ctx2.negClauses[0] = 2;
    ctx2.negClauses[1] = 3;
    ctx2.negClauseSize = 2;
    for (int i = 0; i < 4; i++) {
        s2.clauses.push_back(Clause{ { 1, 2 } });
    }
    std::unordered_map<uint64_t, int> rmap2;
    std::vector<uint64_t> rlit2;
    s2.ResolveClauses(0, ctx2, rmap2, rlit2);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_PushClausesToReconstructStack
 * @tc.desc: Test PushClausesToReconstructStack.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_PushClausesToReconstructStack, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.lits[1].isNiaLit = false;
        solver.lits[1].delta = 0;
        solver.lits[1].litsIndex = 1;
        solver.lits[2].isNiaLit = false;
        solver.lits[2].delta = 1;
        solver.lits[2].litsIndex = 2;
        solver.vars[0].isNia = false;
        solver.vars[1].isNia = false;
    };
    LsSolver s1;
    setup(s1);
    s1.clauses.push_back(Clause{ { 2, 1 } });
    s1.clauses.push_back(Clause{ { -2, -1 } });
    LsSolver::ResolveContext ctx1;
    ctx1.posClauses.resize(10);
    ctx1.negClauses.resize(10);
    ctx1.posClauses[0] = 0;
    ctx1.posClauseSize = 1;
    ctx1.negClauses[0] = 1;
    ctx1.negClauseSize = 1;
    s1.PushClausesToReconstructStack(0, ctx1);
    EXPECT_EQ(s1.reconstructStack.size(), 2);
    EXPECT_EQ(s1.reconstructStack[0].literals[0], 1);

    LsSolver s2;
    setup(s2);
    s2.clauses.push_back(Clause{ { 2 } });
    LsSolver::ResolveContext ctx2;
    ctx2.posClauses.resize(10);
    ctx2.posClauses[0] = 0;
    ctx2.posClauseSize = 1;
    s2.PushClausesToReconstructStack(0, ctx2);
    EXPECT_EQ(s2.reconstructStack.size(), 1);
    EXPECT_EQ(s2.reconstructStack[0].literals[0], 2);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ReduceDuplicatedLits_NotModified
 * @tc.desc: Test ReduceDuplicatedLits when litsBeenModified is false.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ReduceDuplicatedLits_NotModified, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.litsBeenModified = false;
    bool modified = false;
    solver.ReduceDuplicatedLits(modified);
    EXPECT_FALSE(modified);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ReduceDuplicatedLits_EmptyArray
 * @tc.desc: Test ReduceDuplicatedLits with empty litsInCls array.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ReduceDuplicatedLits_EmptyArray, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.litsBeenModified = true;
    solver.litsInCls = new Array(5);
    solver.litsInCls->arraySize = 0;
    solver.litsInCls->indexInArray.resize(solver.numLits + ADDITIONAL_LEN);
    bool modified = false;
    solver.ReduceDuplicatedLits(modified);
    EXPECT_FALSE(modified);
    delete solver.litsInCls;
    solver.litsInCls = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ReduceDuplicatedLits_NoDupKeys
 * @tc.desc: Test ReduceDuplicatedLits with different keys (no duplicates).
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ReduceDuplicatedLits_NoDupKeys, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.litsBeenModified = true;
    solver.litsInCls = new Array(5);
    solver.litsInCls->arraySize = 2;
    solver.litsInCls->indexInArray.resize(solver.numLits + ADDITIONAL_LEN);
    solver.litsInCls->array[0] = 1;
    solver.litsInCls->array[1] = 2;
    solver.lits[1].isNiaLit = true;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].isEqual = false;
    solver.lits[1].key = 1;
    solver.lits[2].isNiaLit = true;
    solver.lits[2].litsIndex = 2;
    solver.lits[2].isEqual = false;
    solver.lits[2].key = 2;
    bool modified = false;
    solver.ReduceDuplicatedLits(modified);
    EXPECT_FALSE(modified);
    delete solver.litsInCls;
    solver.litsInCls = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ReduceDuplicatedLits_HasDupKeys
 * @tc.desc: Test ReduceDuplicatedLits with duplicate keys triggers modification.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ReduceDuplicatedLits_HasDupKeys, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.litsBeenModified = true;
    solver.litsInCls = new Array(5);
    solver.litsInCls->arraySize = 2;
    solver.litsInCls->indexInArray.resize(solver.numLits + ADDITIONAL_LEN);
    solver.litsInCls->array[0] = 1;
    solver.litsInCls->array[1] = 2;
    solver.lits[1].isNiaLit = true;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].isEqual = false;
    solver.lits[1].key = 1;
    solver.lits[2].isNiaLit = true;
    solver.lits[2].litsIndex = 2;
    solver.lits[2].isEqual = false;
    solver.lits[2].key = 1;
    solver.clauses.push_back(Clause{ { 2 } });
    bool modified = false;
    solver.ReduceDuplicatedLits(modified);
    EXPECT_TRUE(modified);
    delete solver.litsInCls;
    solver.litsInCls = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ReduceDuplicatedLits_BoolLits
 * @tc.desc: Test ReduceDuplicatedLits with boolean (non-NIA) literals.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ReduceDuplicatedLits_BoolLits, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.litsBeenModified = true;
    solver.litsInCls = new Array(5);
    solver.litsInCls->arraySize = 2;
    solver.litsInCls->indexInArray.resize(solver.numLits + ADDITIONAL_LEN);
    solver.litsInCls->array[0] = 1;
    solver.litsInCls->array[1] = 2;
    solver.lits[1].isNiaLit = false;
    solver.lits[1].litsIndex = 1;
    solver.lits[2].isNiaLit = false;
    solver.lits[2].litsIndex = 2;
    bool modified = false;
    solver.ReduceDuplicatedLits(modified);
    EXPECT_FALSE(modified);
    delete solver.litsInCls;
    solver.litsInCls = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ResolvePosAndNegClause_NoNewClause
 * @tc.desc: Test ResolvePosAndNegClause produces no new clause when pos/neg cancel.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ResolvePosAndNegClause_NoNewClause, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numClauses = 0;
    solver.lits[1].isNiaLit = false;
    solver.lits[1].delta = 0;
    solver.lits[1].litsIndex = 1;
    solver.lits[2].isNiaLit = false;
    solver.lits[2].delta = 1;
    solver.lits[2].litsIndex = 2;
    solver.vars[0].isNia = false;
    solver.vars[1].isNia = false;
    solver.clauses.push_back(Clause{ { 1, 2 } });
    solver.clauses.push_back(Clause{ { -1, -2 } });
    uint64_t orig = solver.numClauses;
    std::unordered_map<uint64_t, int> rpmap;
    std::vector<uint64_t> rplit;
    solver.ResolvePosAndNegClause(0, 1, 0, rpmap, rplit);
    EXPECT_EQ(solver.numClauses, orig);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ResolvePosAndNegClause_DuplicateExisting
 * @tc.desc: Test ResolvePosAndNegClause skips resolvent that duplicates existing clause.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ResolvePosAndNegClause_DuplicateExisting, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numClauses = 0;
    solver.lits[1].isNiaLit = false;
    solver.lits[1].delta = 0;
    solver.lits[1].litsIndex = 1;
    solver.lits[2].isNiaLit = false;
    solver.lits[2].delta = 1;
    solver.lits[2].litsIndex = 2;
    solver.vars[0].isNia = false;
    solver.vars[1].isNia = false;
    solver.lits[3] = solver.lits[2];
    solver.lits[3].litsIndex = 3;
    Clause existingCl;
    existingCl.literals = { 2 };
    existingCl.isDelete = false;
    solver.clauses.push_back(existingCl);
    solver.numClauses = 1;
    std::sort(existingCl.literals.begin(), existingCl.literals.end());
    uint64_t hash = solver.HashLitsToNum(existingCl.literals);
    std::unordered_map<uint64_t, int> map;
    map[hash] = 0;
    std::vector<uint64_t> lit;
    lit.push_back(hash);
    solver.clauses.push_back(Clause{ { 1, 2 } });
    solver.clauses.push_back(Clause{ { -1 } });
    uint64_t orig = solver.numClauses;
    solver.ResolvePosAndNegClause(1, 2, 0, map, lit);
    EXPECT_EQ(solver.numClauses, orig);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ResolvePosAndNegClause_GeneratesNewClause
 * @tc.desc: Test ResolvePosAndNegClause generates new resolvent clause.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ResolvePosAndNegClause_GeneratesNewClause, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numClauses = 0;
    solver.lits[1].isNiaLit = false;
    solver.lits[1].delta = 0;
    solver.lits[1].litsIndex = 1;
    solver.lits[2].isNiaLit = false;
    solver.lits[2].delta = 1;
    solver.lits[2].litsIndex = 2;
    solver.vars[0].isNia = false;
    solver.vars[1].isNia = false;
    solver.lits[3] = solver.lits[2];
    solver.lits[3].litsIndex = 3;
    solver.clauses.push_back(Clause{ { 1, 2 } });
    solver.clauses.push_back(Clause{ { -1, 3 } });
    uint64_t orig = solver.numClauses;
    std::unordered_map<uint64_t, int> rpmap;
    std::vector<uint64_t> rplit;
    solver.ResolvePosAndNegClause(0, 1, 0, rpmap, rplit);
    EXPECT_GT(solver.numClauses, orig);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_HandleEqualCase
 * @tc.desc: Test HandleEqualCase.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_HandleEqualCase, TestSize.Level1)
{
    auto makeLit = [](bool isNia, bool isEq, int idx, int64_t key) {
        Lit l;
        l.isNiaLit = isNia;
        l.isEqual = isEq;
        l.litsIndex = idx;
        l.key = RationNum(key);
        l.isTrue = (idx > 0);
        return l;
    };
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);

    Lit l1 = makeLit(true, true, 1, 5);
    bool m1 = false;
    solver.HandleEqualCase(l1, RationNum(10), RationNum(10), m1);
    EXPECT_EQ(l1.litsIndex, -1);
    EXPECT_FALSE(l1.isTrue);
    EXPECT_TRUE(m1);

    Lit l2 = makeLit(true, true, 1, 0);
    bool m2 = false;
    solver.HandleEqualCase(l2, RationNum(0), RationNum(0), m2);
    EXPECT_EQ(l2.litsIndex, 0);
    EXPECT_TRUE(m2);

    Lit l3 = makeLit(true, true, 1, -5);
    bool m3 = false;
    solver.HandleEqualCase(l3, RationNum(-3), RationNum(-10), m3);
    EXPECT_EQ(l3.litsIndex, -1);
    EXPECT_TRUE(m3);

    Lit l4 = makeLit(true, true, 1, 5);
    bool m4 = false;
    solver.HandleEqualCase(l4, RationNum(10), RationNum(3), m4);
    EXPECT_EQ(l4.litsIndex, -1);
    EXPECT_TRUE(m4);

    Lit l5 = makeLit(true, true, 1, 0);
    bool m5 = false;
    solver.HandleEqualCase(l5, RationNum(5), RationNum(-5), m5);
    EXPECT_EQ(l5.litsIndex, 1);
    EXPECT_FALSE(m5);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_RecordClauseLiteralRelations
 * @tc.desc: Test RecordClauseLiteralRelations.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_RecordClauseLiteralRelations, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.litAppear.resize(solver.numLits + ADDITIONAL_LEN, false);
        solver.varAppear.resize(solver.vars.size() + ADDITIONAL_LEN, false);
    };
    LsSolver s1;
    setup(s1);
    s1.lits[1].isNiaLit = false;
    s1.lits[1].delta = 0;
    s1.lits[1].litsIndex = 1;
    s1.vars[0].isNia = false;
    s1.clauses.push_back(Clause{ { 1 } });
    s1.RecordClauseLiteralRelations();
    EXPECT_TRUE(s1.litAppear[1]);
    EXPECT_TRUE(s1.varAppear[0]);
    EXPECT_EQ(s1.vars[0].clauseIdxs.size(), 1);
    EXPECT_EQ(s1.clauses[0].boolLiterals.size(), 1);

    LsSolver s2;
    setup(s2);
    s2.lits[1].isNiaLit = true;
    s2.lits[1].litsIndex = 1;
    s2.lits[1].isEqual = false;
    s2.lits[1].key = 0;
    s2.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    s2.vars[0].isNia = true;
    s2.clauses.push_back(Clause{ { 1 } });
    s2.RecordClauseLiteralRelations();
    EXPECT_TRUE(s2.litAppear[1]);
    EXPECT_TRUE(s2.varAppear[0]);
    EXPECT_EQ(s2.vars[0].clauseIdxs.size(), 1);
    EXPECT_EQ(s2.clauses[0].niaLiterals.size(), 1);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_DeduplicateClauseIdxs
 * @tc.desc: Test DeduplicateClauseIdxs removes duplicate clause indices.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_DeduplicateClauseIdxs, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    Variable var;
    var.clauseIdxs = { 0, 0, 1, 1, 2 };
    solver.vars[0] = var;
    solver.DeduplicateClauseIdxs(solver.vars[0]);
    EXPECT_EQ(solver.vars[0].clauseIdxs.size(), 3);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_CollectUniqueLiteralIdxs
 * @tc.desc: Test CollectUniqueLiteralIdxs deduplicates varLits.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_CollectUniqueLiteralIdxs, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    Variable var;
    var.varLits.push_back(VarLit(0, 1, RationNum(1)));
    var.varLits.push_back(VarLit(0, 1, RationNum(1)));
    var.varLits.push_back(VarLit(0, 2, RationNum(1)));
    solver.vars[0] = var;
    solver.CollectUniqueLiteralIdxs(solver.vars[0]);
    EXPECT_EQ(solver.vars[0].literalIdxs.size(), 2);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ClearPreparedClauseLitVarState
 * @tc.desc: Test ClearPreparedClauseLitVarState resets all state.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ClearPreparedClauseLitVarState, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numClauses = 10;
    solver.litAppear.resize(solver.numLits + ADDITIONAL_LEN, true);
    solver.varAppear.resize(solver.vars.size() + ADDITIONAL_LEN, true);
    solver.boolVarVec = { 0, 1 };
    solver.vars[0].clauseIdxs = { 1, 2 };
    solver.vars[1].clauseIdxs = { 3, 4 };
    solver.ClearPreparedClauseLitVarState();
    for (size_t i = 0; i < solver.litAppear.size(); i++) {
        EXPECT_FALSE(solver.litAppear[i]);
    }
    EXPECT_EQ(solver.vars[0].clauseIdxs.size(), 0);
    EXPECT_EQ(solver.vars[1].clauseIdxs.size(), 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_BuildPreparedVarLitRelations
 * @tc.desc: Test BuildPreparedVarLitRelations links vars and lits.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_BuildPreparedVarLitRelations, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.litAppear.resize(solver.numLits + ADDITIONAL_LEN, false);
    solver.litAppear[1] = true;
    solver.lits[1].isNiaLit = true;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].isEqual = false;
    solver.lits[1].key = 0;
    solver.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    solver.vars[0].isNia = true;
    solver.BuildPreparedVarLitRelations();
    EXPECT_EQ(solver.vars[0].varLits.size(), 1);
    EXPECT_EQ(solver.lits[1].varLits.size(), 1);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_PrepareClsLitIdxForVars
 * @tc.desc: Test PrepareClsLitIdxForVars marks lit and var appear.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_PrepareClsLitIdxForVars, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numClauses = 1;
    solver.litAppear.resize(solver.numLits + ADDITIONAL_LEN, false);
    solver.varAppear.resize(solver.vars.size() + ADDITIONAL_LEN, false);
    solver.lits[1].isNiaLit = false;
    solver.lits[1].delta = 0;
    solver.lits[1].litsIndex = 1;
    solver.vars[0].isNia = false;
    solver.boolVarVec = { 0 };
    solver.clauses.push_back(Clause{ { 1 } });
    solver.PrepareClsLitIdxForVars();
    EXPECT_TRUE(solver.litAppear[1]);
    EXPECT_TRUE(solver.varAppear[0]);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_DetermineLitAppear
 * @tc.desc: Test DetermineLitAppear sets litAppear from litsInCls.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_DetermineLitAppear, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.litAppear.resize(solver.numLits + ADDITIONAL_LEN, false);
    solver.litsInCls = new Array(static_cast<int>(solver.numLits));
    solver.litsInCls->InsertElement(1);
    solver.litsInCls->InsertElement(2);
    solver.clauses.push_back(Clause{ { 1, -2 } });
    solver.DetermineLitAppear();
    EXPECT_TRUE(solver.litAppear[1]);
    EXPECT_TRUE(solver.litAppear[2]);
    EXPECT_FALSE(solver.litAppear[3]);
    delete solver.litsInCls;
    solver.litsInCls = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_DetermineLitAppear_ClauseOnly
 * @tc.desc: Lit only in clauses is tracked via localAppear != 0 second pass.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_DetermineLitAppear_ClauseOnly, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.litAppear.resize(solver.numLits + ADDITIONAL_LEN, 0);
    solver.litsInCls = new Array(static_cast<int>(solver.numLits));
    solver.litsInCls->InsertElement(1);
    solver.clauses.push_back(Clause{ { 1, 3 } });
    solver.DetermineLitAppear();
    EXPECT_TRUE(solver.litAppear[3]);
    EXPECT_TRUE(solver.litsInCls->IsInArray(3));
    delete solver.litsInCls;
    solver.litsInCls = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_PrepareComponents
 * @tc.desc: Test PrepareComponents.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_PrepareComponents, TestSize.Level1)
{
    LsSolver s1;
    s1.numLits = 5;
    s1.lits.resize(s1.numLits + ADDITIONAL_LEN);
    s1.vars.resize(20);
    s1.name2var["comp1_width"] = 0;
    s1.name2var["comp1_height"] = 1;
    s1.name2var["comp1_x"] = 2;
    s1.name2var["comp1_y"] = 3;
    s1.vars[0].varName = "comp1_width";
    s1.vars[0].isNia = true;
    s1.vars[1].varName = "comp1_height";
    s1.vars[1].isNia = true;
    s1.vars[2].varName = "comp1_x";
    s1.vars[2].isNia = true;
    s1.vars[3].varName = "comp1_y";
    s1.vars[3].isNia = true;
    s1.niaVarVec = { 0, 1, 2, 3 };
    s1.basicComponentName = "comp1";
    s1.PrepareComponentsIdx();
    EXPECT_EQ(s1.componentsIdx.size(), 4);
    EXPECT_EQ(s1.componentNames.size(), 1);

    LsSolver s2;
    s2.numLits = 5;
    s2.lits.resize(s2.numLits + ADDITIONAL_LEN);
    s2.vars.resize(20);
    s2.name2var["soft_width"] = 10;
    s2.name2var["soft_height"] = 11;
    s2.name2var["soft_x"] = 12;
    s2.name2var["soft_y"] = 13;
    s2.PrepareSoftComponentsIdx({ "soft" });
    EXPECT_EQ(s2.softComponentsIdx.size(), 4);

    LsSolver s3;
    s3.numLits = 5;
    s3.lits.resize(s3.numLits + ADDITIONAL_LEN);
    s3.vars.resize(3);
    s3.numClauses = 1;
    s3.lits[1].isNiaLit = true;
    s3.lits[1].isEqual = true;
    s3.lits[1].litsIndex = 1;
    s3.lits[1].key = -10;
    s3.lits[1].coffVars.push_back(CoffVar(0, RationNum(2, 1)));
    s3.vars[0].isNia = true;
    s3.clauses.push_back(Clause{ { 1 } });
    s3.SetPreValue();
    EXPECT_NE(s3.preValue1[0].ToDouble(), static_cast<double>(INT32_MAX));
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_ClauseReduction
 * @tc.desc: Test ClauseReduction.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_ClauseReduction, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
    };
    LsSolver s1;
    setup(s1);
    s1.lits[1].litsIndex = 0;
    s1.clauses.push_back(Clause{ { 1, 2 } });
    EXPECT_TRUE(s1.IsClauseTautology(s1.clauses[0]));

    LsSolver s2;
    setup(s2);
    s2.lits[1].litsIndex = 1;
    s2.lits[2].litsIndex = 1;
    s2.clauses.push_back(Clause{ { 1, 2 } });
    EXPECT_FALSE(s2.IsClauseTautology(s2.clauses[0]));

    LsSolver s3;
    setup(s3);
    s3.lits[1].litsIndex = 1;
    s3.lits[2].litsIndex = 1;
    s3.clauses.push_back(Clause{ { 1, 1, 2, 2 } });
    bool m3 = false;
    s3.ReduceDuplicatedLitsInClause(s3.clauses[0], m3);
    EXPECT_EQ(s3.clauses[0].literals.size(), 2);
    EXPECT_TRUE(m3);

    LsSolver s4;
    setup(s4);
    s4.lits[1].litsIndex = 0;
    s4.lits[2].litsIndex = -1;
    s4.clauses.push_back(Clause{ { -1, 2 } });
    bool m4 = false;
    s4.ReduceDuplicatedLitsInClause(s4.clauses[0], m4);
    EXPECT_TRUE(s4.buildUnsat);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_GcdAndBounds
 * @tc.desc: Test GcdAndBounds.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_GcdAndBounds, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);

    Lit l1;
    l1.litsIndex = 1;
    l1.isNiaLit = true;
    l1.coffVars.push_back(CoffVar(0, RationNum(2, 1)));
    l1.coffVars.push_back(CoffVar(1, RationNum(4, 1)));
    l1.key = RationNum(6, 1);
    solver.GcdForLit(l1);
    EXPECT_EQ(l1.coffVars[0].coff.ToInt(), 1);
    EXPECT_EQ(l1.coffVars[1].coff.ToInt(), 2);
    EXPECT_EQ(l1.key.ToInt(), 3);

    Lit l2;
    l2.litsIndex = 1;
    l2.isNiaLit = true;
    l2.coffVars.push_back(CoffVar(0, RationNum(3, 1)));
    l2.key = RationNum(6, 1);
    RationNum origKey = l2.key;
    solver.GcdForLit(l2);
    EXPECT_EQ(l2.key, origKey);

    solver.vars[0].upperBound = RationNum(10);
    solver.vars[0].lowBound = RationNum(0);
    solver.vars[1].upperBound = RationNum(5);
    solver.vars[1].lowBound = RationNum(0);
    Lit l3;
    l3.isNiaLit = true;
    l3.key = RationNum(0);
    l3.coffVars.push_back(CoffVar(0, RationNum(1)));
    l3.coffVars.push_back(CoffVar(1, RationNum(-1)));
    EXPECT_EQ(solver.CalculateLitUpBound(l3).ToInt(), 10);
    EXPECT_EQ(solver.CalculateLitLowBound(l3).ToInt(), -5);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_HandleNonEqualCase
 * @tc.desc: Test HandleNonEqualCase.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_HandleNonEqualCase, TestSize.Level1)
{
    auto makeLit = [](bool isNia, bool isEq, int idx) {
        Lit l;
        l.isNiaLit = isNia;
        l.isEqual = isEq;
        l.litsIndex = idx;
        l.isTrue = (idx > 0);
        return l;
    };
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);

    Lit l1 = makeLit(true, false, 1);
    bool m1 = false;
    solver.HandleNonEqualCase(l1, RationNum(-5), RationNum(5), m1);
    EXPECT_EQ(l1.litsIndex, -1);
    EXPECT_FALSE(l1.isTrue);
    EXPECT_TRUE(m1);

    Lit l2 = makeLit(true, false, 1);
    bool m2 = false;
    solver.HandleNonEqualCase(l2, RationNum(10), RationNum(5), m2);
    EXPECT_EQ(l2.litsIndex, -1);
    EXPECT_TRUE(m2);

    Lit l3 = makeLit(true, false, 1);
    bool m3 = false;
    solver.HandleNonEqualCase(l3, RationNum(0), RationNum(-5), m3);
    EXPECT_EQ(l3.litsIndex, 0);
    EXPECT_TRUE(m3);

    Lit l4 = makeLit(true, false, 1);
    bool m4 = false;
    solver.HandleNonEqualCase(l4, RationNum(10), RationNum(-5), m4);
    EXPECT_EQ(l4.litsIndex, 1);
    EXPECT_FALSE(m4);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_DetermineLitsByBound
 * @tc.desc: Test DetermineLitsByBound.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_DetermineLitsByBound, TestSize.Level1)
{
    auto setup = [](LsSolver& solver, bool isNia, int litsIndex) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.litsInCls = new Array(static_cast<int>(solver.numLits));
        solver.litsInCls->InsertElement(1);
        solver.lits[1].isNiaLit = isNia;
        solver.lits[1].litsIndex = litsIndex;
        solver.lits[1].isEqual = false;
        solver.lits[1].key = RationNum(0);
        solver.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    };
    LsSolver s1;
    setup(s1, true, 1);
    s1.vars[0].upperBound = RationNum(-5);
    s1.vars[0].lowBound = RationNum(-10);
    bool m1 = false;
    s1.DetermineLitsByBound(m1);
    EXPECT_TRUE(m1);
    delete s1.litsInCls;
    s1.litsInCls = nullptr;

    LsSolver s2;
    setup(s2, false, 1);
    bool m2 = false;
    s2.DetermineLitsByBound(m2);
    EXPECT_FALSE(m2);
    delete s2.litsInCls;
    s2.litsInCls = nullptr;

    LsSolver s3;
    setup(s3, true, 0);
    bool m3 = false;
    s3.DetermineLitsByBound(m3);
    EXPECT_FALSE(m3);
    delete s3.litsInCls;
    s3.litsInCls = nullptr;

    LsSolver s4;
    setup(s4, true, -1);
    bool m4 = false;
    s4.DetermineLitsByBound(m4);
    EXPECT_FALSE(m4);
    delete s4.litsInCls;
    s4.litsInCls = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_CompareLit
 * @tc.desc: Test CompareLit.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_CompareLit, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    Lit x, y;
    x.isEqual = false;
    x.isNiaLit = true;
    x.coffVars.push_back(CoffVar(0, RationNum(1)));
    x.key = RationNum(0);
    y.isEqual = true;
    y.isNiaLit = true;
    y.coffVars.push_back(CoffVar(0, RationNum(1)));
    y.key = RationNum(0);
    EXPECT_TRUE(solver.CompareLit(x, y, true));
    const LsSolver& constSolver = solver;
    EXPECT_TRUE(constSolver.CompareLit(x, y, true));

    Lit a, b;
    a.coffVars.push_back(CoffVar(0, RationNum(1)));
    a.key = RationNum(0);
    b.coffVars.push_back(CoffVar(0, RationNum(2)));
    b.key = RationNum(0);
    EXPECT_TRUE(solver.CompareLitByCoffVars(a, b));
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_UpdateLitPresetVar_Equal
 * @tc.desc: Test UpdateLitPresetVar Equal.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_UpdateLitPresetVar_Equal, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.presetValues.resize(3, RationNum(INT32_MAX));
    };
    LsSolver s1;
    setup(s1);
    s1.presetValues[0] = RationNum(0);
    s1.lits[1].isNiaLit = true;
    s1.lits[1].litsIndex = 1;
    s1.lits[1].isEqual = false;
    s1.lits[1].key = RationNum(0);
    s1.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    s1.UpdateLitPresetVar(1);
    EXPECT_EQ(s1.lits[1].coffVars.size(), 0);
    EXPECT_EQ(s1.lits[1].litsIndex, 0);

    LsSolver s2;
    setup(s2);
    s2.lits[1].isNiaLit = true;
    s2.lits[1].litsIndex = 0;
    s2.UpdateLitPresetVar(1);

    LsSolver s3;
    setup(s3);
    s3.fa = { 0, 0, 2 };
    s3.faCoff = { RationNum(1), RationNum(2), RationNum(1) };
    s3.faConst = { RationNum(0), RationNum(3), RationNum(0) };
    s3.lits[1].isNiaLit = true;
    s3.lits[1].litsIndex = 1;
    s3.lits[1].key = RationNum(0);
    s3.lits[1].coffVars.push_back(CoffVar(1, RationNum(1)));
    s3.UpdateLitEqual(1);
    EXPECT_EQ(s3.lits[1].coffVars[0].varIdx, 0);

    LsSolver s4;
    setup(s4);
    s4.lits[1].isNiaLit = true;
    s4.lits[1].litsIndex = -1;
    s4.UpdateLitEqual(1);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_UpdateBoundByMerge
 * @tc.desc: Test UpdateBoundByMerge.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_UpdateBoundByMerge, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.vars[0].upperBound = RationNum(MAX_INT);
        solver.vars[0].lowBound = RationNum(-MAX_INT);
        solver.vars[1].upperBound = RationNum(10);
        solver.vars[1].lowBound = RationNum(0);
    };
    LsSolver s1;
    setup(s1);
    s1.UpdateBoundByMerge(0, 1, RationNum(2), RationNum(1));
    EXPECT_EQ(s1.vars[0].upperBound.ToInt(), 21);
    EXPECT_EQ(s1.vars[0].lowBound.ToInt(), 1);

    LsSolver s2;
    setup(s2);
    s2.UpdateBoundByMerge(0, 1, RationNum(-2), RationNum(1));
    EXPECT_EQ(s2.vars[0].lowBound.ToInt(), -19);
    EXPECT_EQ(s2.vars[0].upperBound.ToInt(), 1);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_Find_Merge
 * @tc.desc: Test Find Merge.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_Find_Merge, TestSize.Level1)
{
    auto setup = [](LsSolver& solver, const std::vector<int>& fa) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.fa = fa;
        solver.faCoff = { RationNum(1), RationNum(1), RationNum(1) };
        solver.faConst = { RationNum(0), RationNum(0), RationNum(0) };
    };
    LsSolver s1;
    setup(s1, { 0, 0, 1 });
    EXPECT_EQ(s1.Find(2), 0);

    LsSolver s2;
    setup(s2, { 0, 1, 2 });
    EXPECT_EQ(s2.Find(1), 1);

    LsSolver s3;
    setup(s3, { 0, 1, 2 });
    s3.vars[0].upperBound = RationNum(MAX_INT);
    s3.vars[0].lowBound = RationNum(-MAX_INT);
    s3.vars[1].upperBound = RationNum(MAX_INT);
    s3.vars[1].lowBound = RationNum(-MAX_INT);
    Lit l3;
    l3.isEqual = true;
    l3.key = RationNum(0);
    l3.coffVars.push_back(CoffVar(0, RationNum(1)));
    l3.coffVars.push_back(CoffVar(1, RationNum(-1)));
    EXPECT_TRUE(s3.Merge(l3));

    LsSolver s4;
    setup(s4, { 0, 0, 2 });
    Lit l4;
    l4.isEqual = true;
    l4.key = RationNum(0);
    l4.coffVars.push_back(CoffVar(0, RationNum(1)));
    l4.coffVars.push_back(CoffVar(1, RationNum(-1)));
    EXPECT_FALSE(s4.Merge(l4));
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_FixValue_FaCoffs_TransferName
 * @tc.desc: Test FixValue FaCoffs TransferName.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_FixValue_FaCoffs_TransferName, TestSize.Level1)
{
    LsSolver s1;
    s1.numLits = 5;
    s1.lits.resize(s1.numLits + ADDITIONAL_LEN);
    s1.vars.resize(3);
    s1.bcWidthIdx = 0;
    s1.bcHeightIdx = 1;
    s1.fa = { 0, 1, 2 };
    s1.faCoff = { RationNum(1), RationNum(1), RationNum(1) };
    s1.faConst = { RationNum(0), RationNum(0), RationNum(0) };
    s1.presetValues.resize(3, RationNum(INT32_MAX));
    s1.vars[0].upperBound = RationNum(MAX_INT);
    s1.vars[0].lowBound = RationNum(-MAX_INT);
    RationNum bw(100), bh(0), r(0);
    s1.FixValue(bw, bh, r);
    EXPECT_EQ(s1.presetValues[0].ToInt(), 100);
    EXPECT_EQ(s1.vars[0].upperBound.ToInt(), 100);
    EXPECT_EQ(s1.vars[0].lowBound.ToInt(), 100);

    LsSolver s2;
    s2.numLits = 5;
    s2.lits.resize(s2.numLits + ADDITIONAL_LEN);
    s2.vars.resize(3);
    s2.vars[0].varName = "x";
    s2.vars[0].isNia = true;
    s2.vars[1].varName = "y";
    s2.vars[1].isNia = true;
    s2.vars[2].varName = "z";
    s2.vars[2].isNia = true;
    s2.PrepareFaCoffs();
    EXPECT_EQ(s2.fa.size(), 3);
    EXPECT_EQ(s2.fa[0], 0);
    EXPECT_EQ(s2.fa[1], 1);
    EXPECT_EQ(s2.fa[2], 2);

    LsSolver s3;
    s3.numLits = 5;
    s3.lits.resize(s3.numLits + ADDITIONAL_LEN);
    uint64_t idx = s3.TransferNameToVar("newVar", true);
    EXPECT_EQ(idx, 0);
    EXPECT_EQ(s3.vars.size(), 1);
    EXPECT_EQ(s3.vars[0].varName, "newVar");
    EXPECT_TRUE(s3.vars[0].isNia);
    uint64_t idx2 = s3.TransferNameToVar("newVar", false);
    EXPECT_EQ(idx2, 0);
    EXPECT_TRUE(s3.vars[0].isNia);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_HashLitsToNum_IsSameLits
 * @tc.desc: Test HashLitsToNum IsSameLits.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_HashLitsToNum_IsSameLits, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    std::vector<int> a = { 1, 2, 3 }, b = { 1, 2, 3 }, c = { 4, 5, 6 }, d = { 3, 1, 2 };
    uint64_t h1 = solver.HashLitsToNum(a), h2 = solver.HashLitsToNum(b), h3 = solver.HashLitsToNum(c);
    EXPECT_EQ(h1, h2);
    EXPECT_NE(h1, h3);
    EXPECT_EQ(solver.HashLitsToNum({}), 0);
    EXPECT_TRUE(solver.IsSameLits(a, d));
    EXPECT_FALSE(solver.IsSameLits(a, c));
    std::vector<int> e = { 1, 2 }, f = { 1, 2, 3 };
    EXPECT_FALSE(solver.IsSameLits(e, f));
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_RecordInfo_RestoreInfo_BuildNewWidth
 * @tc.desc: Test RecordInfo RestoreInfo BuildNewWidth.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest,
    SmartLayoutLocalSmtTest_Coverage_RecordInfo_RestoreInfo_BuildNewWidth,
    TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numClauses = 1;
    solver.clauses.push_back(Clause{ { 1 } });
    TmpInfo info;
    solver.RecordInfo(info);
    EXPECT_EQ(info.clausesInfo.size(), 1);
    EXPECT_EQ(info.litsInfo.size(), solver.numLits + ADDITIONAL_LEN);
    EXPECT_EQ(info.varsInfo.size(), 3);
    solver.clauses.clear();
    solver.numClauses = 0;
    solver.RestoreInfo(info);
    EXPECT_EQ(solver.clauses.size(), 1);
    EXPECT_EQ(solver.numClauses, 1);

    TmpInfo info2;
    solver.RecordInfo(info2);
    solver.infoAfterOrigin = info2;
    solver.litsInCls = new Array(static_cast<int>(solver.numLits));
    solver.PrepareFaCoffs();
    solver.BuildInstanceNewWidth(100, 200, 0);
    delete solver.litsInCls;
    solver.litsInCls = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_FindMaxVarLit_PrepareUpValueVars
 * @tc.desc: Test FindMaxVarLit PrepareUpValueVars.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_FindMaxVarLit_PrepareUpValueVars, TestSize.Level1)
{
    LsSolver s1;
    s1.numLits = 5;
    s1.lits.resize(s1.numLits + ADDITIONAL_LEN);
    s1.vars.resize(3);
    s1.numVars = 3;
    s1.lits[1].isNiaLit = true;
    s1.lits[1].litsIndex = 1;
    s1.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    s1.vars[0].isNia = true;
    s1.litsInCls = new Array(static_cast<int>(s1.numLits));
    s1.litsInCls->InsertElement(1);
    s1.clauses.push_back(Clause{ { 1 } });
    std::vector<int> litIdxs;
    s1.FindMaxVarLit(litIdxs);
    delete s1.litsInCls;
    s1.litsInCls = nullptr;

    LsSolver s2;
    s2.numLits = 5;
    s2.lits.resize(s2.numLits + ADDITIONAL_LEN);
    s2.vars.resize(3);
    s2.numVars = 3;
    s2.vars[0].upBool = 1;
    s2.vars[1].upBool = -1;
    s2.vars[2].upBool = 0;
    s2.PrepareUpValueVars();
    EXPECT_EQ(s2.upValueVars[0], 1);
    EXPECT_EQ(s2.upValueVars[1], -1);
    EXPECT_EQ(s2.upValueVars[2], 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_HasSameCoffVars
 * @tc.desc: Test HasSameCoffVars.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_HasSameCoffVars, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    Lit l1, l2, l3, l4;
    l1.coffVars.push_back(CoffVar(0, RationNum(1)));
    l1.coffVars.push_back(CoffVar(1, RationNum(2)));
    l2.coffVars.push_back(CoffVar(0, RationNum(1)));
    l2.coffVars.push_back(CoffVar(1, RationNum(2)));
    l3.coffVars.push_back(CoffVar(0, RationNum(1)));
    l4.coffVars.push_back(CoffVar(0, RationNum(1)));
    l4.coffVars.push_back(CoffVar(1, RationNum(2)));
    EXPECT_TRUE(solver.HasSameCoffVars(&l1, &l2));
    EXPECT_FALSE(solver.HasSameCoffVars(&l1, &l3));
    EXPECT_FALSE(solver.HasSameCoffVars(&l3, &l4));
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_EliminateMultipleInequalities_InvertLit_DeltaLit
 * @tc.desc: Test EliminateMultipleInequalities InvertLit DeltaLit.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest,
    SmartLayoutLocalSmtTest_Coverage_EliminateMultipleInequalities_InvertLit_DeltaLit,
    TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.lits[1].isNiaLit = true;
    solver.lits[1].isEqual = false;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].key = RationNum(10);
    solver.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    solver.lits[2].isNiaLit = true;
    solver.lits[2].isEqual = false;
    solver.lits[2].litsIndex = 2;
    solver.lits[2].key = RationNum(5);
    solver.lits[2].coffVars.push_back(CoffVar(0, RationNum(1)));
    solver.clauses.push_back(Clause{ { 1 } });
    solver.clauses.push_back(Clause{ { 2 } });
    bool m1 = false;
    solver.EliminateMultipleInequalities(m1);
    EXPECT_TRUE(m1);

    Lit l;
    l.key = RationNum(5);
    l.coffVars.push_back(CoffVar(0, RationNum(2)));
    l.coffVars.push_back(CoffVar(1, RationNum(-3)));
    solver.InvertLit(l);
    EXPECT_EQ(l.key.ToInt(), -4);
    EXPECT_EQ(l.coffVars[0].coff.ToInt(), -2);
    EXPECT_EQ(l.coffVars[1].coff.ToInt(), 3);

    solver.numVars = 3;
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(3);
    solver.solution[1] = RationNum(4);
    Lit l2;
    l2.key = RationNum(1);
    l2.coffVars.push_back(CoffVar(0, RationNum(2)));
    l2.coffVars.push_back(CoffVar(1, RationNum(-1)));
    EXPECT_EQ(solver.DeltaLit(l2).ToInt(), 3);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_UpdateNiaVar
 * @tc.desc: Test UpdateNiaVar.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_UpdateNiaVar, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.numVars = 3;
        solver.varAppear.resize(solver.numVars + ADDITIONAL_LEN, false);
        solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    };
    LsSolver s1;
    setup(s1);
    s1.fa = { 0, 0, 2 };
    s1.faCoff = { RationNum(1), RationNum(2), RationNum(1) };
    s1.faConst = { RationNum(0), RationNum(3), RationNum(0) };
    s1.vars[0].isNia = true;
    s1.vars[1].isNia = true;
    s1.vars[2].isNia = true;
    s1.solution[0] = RationNum(5);
    s1.UpdateNiaVar(1);
    EXPECT_EQ(s1.solution[1].ToInt(), 13);

    LsSolver s2;
    setup(s2);
    s2.upValueVars.resize(s2.numVars + ADDITIONAL_LEN, 0);
    s2.vars[0].isNia = false;
    s2.vars[0].upBool = 0;
    s2.UpdateNiaVar(0);
    EXPECT_EQ(s2.solution[0].ToInt(), -1);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_EvaluateNiaLiteral
 * @tc.desc: Test EvaluateNiaLiteral.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_EvaluateNiaLiteral, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    Lit l1;
    l1.isEqual = false;
    l1.delta = RationNum(-1);
    EXPECT_TRUE(solver.EvaluateNiaLiteral(&l1, 1, l1.delta));
    Lit l2;
    l2.isEqual = false;
    l2.delta = RationNum(1);
    EXPECT_FALSE(solver.EvaluateNiaLiteral(&l2, 1, l2.delta));
    Lit l3;
    l3.isEqual = true;
    l3.delta = RationNum(0);
    EXPECT_TRUE(solver.EvaluateNiaLiteral(&l3, 1, l3.delta));
    Lit l4;
    l4.isEqual = true;
    l4.delta = RationNum(1);
    EXPECT_FALSE(solver.EvaluateNiaLiteral(&l4, 1, l4.delta));
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_CheckLiteralSatisfaction
 * @tc.desc: Test CheckLiteralSatisfaction.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_CheckLiteralSatisfaction, TestSize.Level1)
{
    LsSolver s1;
    s1.numLits = 5;
    s1.lits.resize(s1.numLits + ADDITIONAL_LEN);
    s1.vars.resize(3);
    s1.lits[1].litsIndex = 0;
    std::vector<bool> litAppearTmp1(s1.numLits + ADDITIONAL_LEN, true);
    EXPECT_TRUE(s1.CheckLiteralSatisfaction(1, litAppearTmp1));

    LsSolver s2;
    s2.numLits = 5;
    s2.lits.resize(s2.numLits + ADDITIONAL_LEN);
    s2.vars.resize(3);
    s2.numVars = 3;
    s2.solution.resize(s2.numVars + ADDITIONAL_LEN);
    s2.lits[1].isNiaLit = false;
    s2.lits[1].delta = 0;
    s2.lits[1].litsIndex = 1;
    s2.solution[0] = RationNum(1);
    std::vector<bool> litAppearTmp2(s2.numLits + ADDITIONAL_LEN, true);
    EXPECT_TRUE(s2.CheckLiteralSatisfaction(1, litAppearTmp2));
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_CheckSingleClause
 * @tc.desc: Test CheckSingleClause.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_CheckSingleClause, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.numVars = 3;
        solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    };
    LsSolver s1;
    setup(s1);
    s1.lits[1].isNiaLit = false;
    s1.lits[1].delta = 0;
    s1.lits[1].litsIndex = 1;
    s1.solution[0] = RationNum(1);
    s1.lits[2].isNiaLit = true;
    s1.lits[2].isEqual = false;
    s1.lits[2].delta = RationNum(-1);
    s1.lits[2].litsIndex = 2;
    Clause cl1 = { { 1, 2 } };
    EXPECT_GE(s1.CheckSingleClause(&cl1), 0);

    LsSolver s2;
    setup(s2);
    s2.lits[1].isNiaLit = false;
    s2.lits[1].delta = 0;
    s2.lits[1].litsIndex = 1;
    s2.solution[0] = RationNum(-1);
    Clause cl2 = { { -1 } };
    EXPECT_EQ(s2.CheckSingleClause(&cl2), 1);

    LsSolver s3;
    setup(s3);
    s3.lits[1].isNiaLit = true;
    s3.lits[1].isEqual = true;
    s3.lits[1].delta = RationNum(0);
    s3.lits[1].litsIndex = 1;
    Clause cl3 = { { 1 } };
    EXPECT_EQ(s3.CheckSingleClause(&cl3), 1);

    LsSolver s4;
    setup(s4);
    s4.lits[1].isNiaLit = true;
    s4.lits[1].isEqual = false;
    s4.lits[1].delta = RationNum(-1);
    s4.lits[1].litsIndex = 1;
    Clause cl4 = { { 1 } };
    EXPECT_EQ(s4.CheckSingleClause(&cl4), 1);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_CheckSolution
 * @tc.desc: Test CheckSolution.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_CheckSolution, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numClauses = 1;
    solver.numVars = 3;
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.litAppear.resize(solver.numLits + ADDITIONAL_LEN, false);
    solver.lits[1].isNiaLit = true;
    solver.lits[1].delta = RationNum(0);
    solver.lits[1].isEqual = false;
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    Clause cl;
    cl.literals = { 1 };
    cl.satCount = 1;
    solver.clauses.push_back(cl);
    solver.unsatClauses = new Array(static_cast<int>(solver.numClauses) + ADDITIONAL_LEN);
    solver.CheckSolution();
    delete solver.unsatClauses;
    solver.unsatClauses = nullptr;
    EXPECT_EQ(solver.numLits, 5);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_UpdateBestSolutions
 * @tc.desc: Test UpdateBestSolutions.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_UpdateBestSolutions, TestSize.Level1)
{
    auto setup = [](LsSolver& solver, int bestCost, int unsatSize) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.unsatClauses = new Array(20);
        solver.unsatClauses->arraySize = unsatSize;
        solver.bestFoundThisRestart = bestCost;
        solver.bestFoundCost = bestCost;
        solver.bestFoundHardCostThisNia = bestCost;
        solver.bestFoundHardCostThisBool = bestCost;
    };
    LsSolver s1;
    setup(s1, 10, 3);
    EXPECT_TRUE(s1.UpdateBestSolution());
    EXPECT_TRUE(s1.UpdateInnerBestSolution());
    EXPECT_EQ(s1.bestFoundHardCostThisNia, 3);
    EXPECT_TRUE(s1.UpdateOuterBestSolution());
    EXPECT_EQ(s1.bestFoundHardCostThisBool, 3);
    delete s1.unsatClauses;
    s1.unsatClauses = nullptr;

    LsSolver s2;
    setup(s2, 3, 5);
    EXPECT_FALSE(s2.UpdateInnerBestSolution());
    delete s2.unsatClauses;
    s2.unsatClauses = nullptr;

    LsSolver s3;
    setup(s3, 10, 3);
    EXPECT_TRUE(s3.UpdateBestSolution());
    delete s3.unsatClauses;
    s3.unsatClauses = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_EnterNiaMode_EnterBoolMode
 * @tc.desc: Test EnterNiaMode EnterBoolMode.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_EnterNiaMode_EnterBoolMode, TestSize.Level1)
{
    auto setup = [](LsSolver& solver, bool inBool, int cntNia, int cntBool) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.unsatClauses = new Array(20);
        solver.unsatClauses->arraySize = 5;
        solver.isInBoolSearch = inBool;
        solver.noImproveCntNia = cntNia;
        solver.noImproveCntBool = cntBool;
    };
    LsSolver s1;
    setup(s1, true, 100, 0);
    s1.EnterNiaMode();
    EXPECT_FALSE(s1.isInBoolSearch);
    EXPECT_EQ(s1.noImproveCntNia, 0);
    delete s1.unsatClauses;
    s1.unsatClauses = nullptr;

    LsSolver s2;
    setup(s2, false, 100, 0);
    s2.EnterNiaMode();
    EXPECT_FALSE(s2.isInBoolSearch);
    EXPECT_EQ(s2.noImproveCntNia, 100);
    delete s2.unsatClauses;
    s2.unsatClauses = nullptr;

    LsSolver s3;
    setup(s3, false, 0, 100);
    s3.EnterBoolMode();
    EXPECT_TRUE(s3.isInBoolSearch);
    EXPECT_EQ(s3.noImproveCntBool, 0);
    delete s3.unsatClauses;
    s3.unsatClauses = nullptr;
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_InsertOperation_TabuActive
 * @tc.desc: Test InsertOperation skips when tabulist entry exceeds step.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_InsertOperation_TabuActive, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(0);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    solver.step = 1;
    solver.tabulist[0] = 100;
    int op = 0;
    solver.InsertOperation(0, RationNum(1), op, true);
    EXPECT_EQ(op, 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_InsertOperation_SameLastOp
 * @tc.desc: Test InsertOperation skips when same as last operation.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_InsertOperation_SameLastOp, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(0);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    solver.lastOpVar = 0;
    solver.lastOpValue = RationNum(1);
    int op = 0;
    solver.InsertOperation(0, RationNum(-1), op, false);
    EXPECT_EQ(op, 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_InsertOperation_UnchangedVar
 * @tc.desc: Test InsertOperation skips when var is unchanged.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_InsertOperation_UnchangedVar, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(0);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    solver.unchangedVar1 = 0;
    int op = 0;
    solver.InsertOperation(0, RationNum(1), op, false);
    EXPECT_EQ(op, 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_InsertOperation_ValidInsert
 * @tc.desc: Test InsertOperation inserts valid operation.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_InsertOperation_ValidInsert, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(0);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    int op = 0;
    solver.InsertOperation(0, RationNum(1), op, false);
    EXPECT_EQ(op, 1);
    EXPECT_EQ(solver.operationVarIdxVec[0], 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_InsertOperation_SolutionLimit
 * @tc.desc: Test InsertOperation skips when solution at limit.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_InsertOperation_SolutionLimit, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(K_SOLUTION_LIMIT);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    int op = 0;
    solver.InsertOperation(0, RationNum(1), op, false);
    EXPECT_EQ(op, 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_InsertOperation_SamePreValue
 * @tc.desc: Test InsertOperation inserts when value differs from preValue.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_InsertOperation_SamePreValue, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(0);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    solver.preValue1[0] = RationNum(5);
    int op = 0;
    solver.InsertOperation(0, RationNum(5), op, false);
    EXPECT_EQ(op, 1);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_AddBoolOperation
 * @tc.desc: Test AddBoolOperation.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_AddBoolOperation, TestSize.Level1)
{
    auto setup = [](LsSolver& solver) {
        solver.numLits = 5;
        solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
        solver.vars.resize(3);
        solver.numVars = 3;
        solver.lits[1].delta = 0;
        solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
        solver.isChosenBoolVar.resize(solver.numVars + ADDITIONAL_LEN, false);
        solver.operationVarIdxBoolVec.resize(100);
    };
    LsSolver s1;
    setup(s1);
    s1.outerLayerStep = 1;
    s1.tabulist[0] = 100;
    int op1 = 0;
    s1.AddBoolOperation(true, 1, op1);
    EXPECT_EQ(op1, 0);

    LsSolver s2;
    setup(s2);
    s2.outerLayerStep = 10;
    s2.tabulist[0] = 5;
    int op2 = 0;
    s2.AddBoolOperation(true, 1, op2);
    EXPECT_EQ(op2, 1);

    LsSolver s3;
    setup(s3);
    s3.isChosenBoolVar[0] = true;
    int op3 = 0;
    s3.AddBoolOperation(false, 1, op3);
    EXPECT_EQ(op3, 0);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_ProcessClauseNiaLiterals
 * @tc.desc: Test ProcessClauseNiaLiterals processes a single NIA literal clause.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_ProcessClauseNiaLiterals, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.lits[1].isNiaLit = true;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].isEqual = false;
    solver.lits[1].key = RationNum(0);
    solver.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    solver.lits[1].isTrue = 1;
    solver.lits[1].delta = RationNum(1);
    solver.vars[0].isNia = true;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(0);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    solver.falseLitOccur = new Array(static_cast<int>(solver.numLits) + ADDITIONAL_LEN);
    solver.lastOpVar = UINT64_MAX;
    solver.lastOpValue = RationNum(0);
    solver.step = 1;
    int op = 0;
    Clause cl = { { 1 } };
    solver.ProcessClauseNiaLiterals(&cl, op);
    delete solver.falseLitOccur;
    solver.falseLitOccur = nullptr;
    EXPECT_EQ(solver.numLits, 5);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_AddSwapOperation_FewClauses
 * @tc.desc: Test AddSwapOperation with few sat clauses containing false literal.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_AddSwapOperation_FewClauses, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.lits[1].isNiaLit = true;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].isEqual = false;
    solver.lits[1].key = RationNum(0);
    solver.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    solver.lits[1].isTrue = 1;
    solver.lits[1].delta = RationNum(1);
    solver.vars[0].isNia = true;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(0);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    solver.falseLitOccur = new Array(static_cast<int>(solver.numLits) + ADDITIONAL_LEN);
    solver.lastOpVar = UINT64_MAX;
    solver.lastOpValue = RationNum(0);
    solver.step = 1;
    solver.satClauseWithFalseLiteral = new Array(10);
    solver.satClauseWithFalseLiteral->InsertElement(0);
    solver.clauses.push_back(Clause{ { 1 } });
    int op = 0;
    solver.AddSwapOperation(op);
    delete solver.falseLitOccur;
    solver.falseLitOccur = nullptr;
    delete solver.satClauseWithFalseLiteral;
    solver.satClauseWithFalseLiteral = nullptr;
    EXPECT_EQ(solver.numLits, 5);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_AddSwapOperation_ManyClauses
 * @tc.desc: Test AddSwapOperation with many sat clauses containing false literal.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_AddSwapOperation_ManyClauses, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.lits[1].isNiaLit = true;
    solver.lits[1].litsIndex = 1;
    solver.lits[1].isEqual = false;
    solver.lits[1].key = RationNum(0);
    solver.lits[1].coffVars.push_back(CoffVar(0, RationNum(1)));
    solver.lits[1].isTrue = 1;
    solver.lits[1].delta = RationNum(1);
    solver.vars[0].isNia = true;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(0);
    solver.vars[0].lowBound = RationNum(-MAX_INT);
    solver.vars[0].upperBound = RationNum(MAX_INT);
    solver.preValue1.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.preValue2.resize(solver.numVars + ADDITIONAL_LEN, RationNum(INT32_MAX));
    solver.operationVarIdxVec.resize(100);
    solver.operationChangeValueVec.resize(100);
    solver.falseLitOccur = new Array(static_cast<int>(solver.numLits) + ADDITIONAL_LEN);
    solver.lastOpVar = UINT64_MAX;
    solver.lastOpValue = RationNum(0);
    solver.step = 1;
    solver.satClauseWithFalseLiteral = new Array(100);
    for (int i = 0; i < 30; i++) {
        solver.satClauseWithFalseLiteral->InsertElement(0);
    }
    solver.clauses.push_back(Clause{ { 1 } });
    int op = 0;
    solver.AddSwapOperation(op);
    delete solver.falseLitOccur;
    solver.falseLitOccur = nullptr;
    delete solver.satClauseWithFalseLiteral;
    solver.satClauseWithFalseLiteral = nullptr;
    EXPECT_EQ(solver.numLits, 5);
}

/**
 * @tc.name: SmartLayoutLocalSmtTest_Coverage_PickCriticalMoveBool
 * @tc.desc: Test PickCriticalMoveBool.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutLocalSmtTest, SmartLayoutLocalSmtTest_Coverage_PickCriticalMoveBool, TestSize.Level1)
{
    LsSolver solver;
    solver.numLits = 5;
    solver.lits.resize(solver.numLits + ADDITIONAL_LEN);
    solver.vars.resize(3);
    solver.numVars = 3;
    solver.lits[1].isNiaLit = false;
    solver.lits[1].delta = 0;
    solver.lits[1].litsIndex = 1;
    solver.vars[0].isNia = false;
    solver.vars[0].score = 5;
    solver.tabulist.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.solution.resize(solver.numVars + ADDITIONAL_LEN);
    solver.solution[0] = RationNum(1);
    solver.lastMove.resize(K_DIR_COUNT * solver.numVars + ADDITIONAL_LEN, 0);
    solver.isChosenBoolVar.resize(solver.numVars + ADDITIONAL_LEN, false);
    solver.operationVarIdxBoolVec.resize(100);
    solver.containBoolUnsatClauses = new Array(10);
    solver.containBoolUnsatClauses->InsertElement(0);
    solver.unsatClauses = new Array(10);
    solver.falseLitOccur = new Array(static_cast<int>(solver.numLits) + ADDITIONAL_LEN);
    solver.totalClauseWeight = 1;
    solver.mt.seed(42);
    solver.step = 1;
    solver.outerLayerStep = 1;
    Clause cl;
    cl.literals = { 1 };
    cl.satCount = 0;
    cl.boolLiterals.push_back(1);
    solver.clauses.push_back(cl);
    solver.PickCriticalMoveBool();
    delete solver.containBoolUnsatClauses;
    solver.containBoolUnsatClauses = nullptr;
    delete solver.unsatClauses;
    solver.unsatClauses = nullptr;
    delete solver.falseLitOccur;
    solver.falseLitOccur = nullptr;
    EXPECT_EQ(solver.numLits, 5);
}

} // namespace OHOS::Ace::NG
