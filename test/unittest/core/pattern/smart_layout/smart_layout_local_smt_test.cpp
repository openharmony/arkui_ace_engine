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

#include "core/components_ng/pattern/smart_layout/engine/localsmt/localsmt.h"

using namespace testing;
using namespace testing::ext;
using namespace localsmt;

namespace OHOS::Ace::NG {
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

} // namespace OHOS::Ace::NG
