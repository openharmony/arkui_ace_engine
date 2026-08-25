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

#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_predictor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

constexpr int64_t MS_TO_NS = 1000000;

} // namespace

class ScrollPlaceholderPredictorTest : public testing::Test {};

/**
 * @tc.name: ScrollPlaceholderPredictorTest/EWMAConvergence
 * @tc.desc: FEAT-005 per-template EWMA converges towards recent samples.
 */
HWTEST_F(ScrollPlaceholderPredictorTest, EWMAConvergence, TestSize.Level1)
{
    ScrollPlaceholderPredictor predictor;
    // Feed a constant 5ms cost: the estimate must converge to 5ms.
    for (int i = 0; i < 50; ++i) {
        predictor.RecordBuildCost("tpl", 5 * MS_TO_NS);
    }
    auto estimate = predictor.EstimateBuildCost("tpl");
    EXPECT_TRUE(estimate.warm);
    EXPECT_NEAR(estimate.estimateNs, 5 * MS_TO_NS, MS_TO_NS);
    EXPECT_GE(estimate.samples, ScrollPlaceholderPredictor::WARMUP_SAMPLES);
}

/**
 * @tc.name: ScrollPlaceholderPredictorTest/ColdStart
 * @tc.desc: Without samples the predictor assumes the documented cold cost.
 */
HWTEST_F(ScrollPlaceholderPredictorTest, ColdStart, TestSize.Level1)
{
    ScrollPlaceholderPredictor predictor;
    auto estimate = predictor.EstimateBuildCost("unknown");
    EXPECT_FALSE(estimate.warm);
    EXPECT_EQ(estimate.estimateNs, ScrollPlaceholderPredictor::DEFAULT_COLD_COST_NS);
}

/**
 * @tc.name: ScrollPlaceholderPredictorTest/PerTemplateIsolation
 * @tc.desc: Templates do not share statistics.
 */
HWTEST_F(ScrollPlaceholderPredictorTest, PerTemplateIsolation, TestSize.Level1)
{
    ScrollPlaceholderPredictor predictor;
    for (int i = 0; i < 10; ++i) {
        predictor.RecordBuildCost("a", 1 * MS_TO_NS);
        predictor.RecordBuildCost("b", 10 * MS_TO_NS);
    }
    auto a = predictor.EstimateBuildCost("a");
    auto b = predictor.EstimateBuildCost("b");
    EXPECT_LT(a.estimateNs, 2 * MS_TO_NS);
    EXPECT_GT(b.estimateNs, 8 * MS_TO_NS);
}

/**
 * @tc.name: ScrollPlaceholderPredictorTest/RecentSampleWeighting
 * @tc.desc: A sudden cost spike must move the estimate (alpha > 0).
 */
HWTEST_F(ScrollPlaceholderPredictorTest, RecentSampleWeighting, TestSize.Level1)
{
    ScrollPlaceholderPredictor predictor;
    for (int i = 0; i < 20; ++i) {
        predictor.RecordBuildCost("tpl", 1 * MS_TO_NS);
    }
    predictor.RecordBuildCost("tpl", 20 * MS_TO_NS);
    auto estimate = predictor.EstimateBuildCost("tpl");
    EXPECT_GT(estimate.estimateNs, 2 * MS_TO_NS);
}

/**
 * @tc.name: ScrollPlaceholderPredictorTest/DecideDefersWhenBudgetShort
 * @tc.desc: Budget decision defers when the estimated cost does not fit.
 */
HWTEST_F(ScrollPlaceholderPredictorTest, DecideDefersWhenBudgetShort, TestSize.Level1)
{
    // Remaining budget cannot absorb a 5ms item.
    EXPECT_EQ(ScrollPlaceholderPredictor::Decide(5 * MS_TO_NS, 2 * MS_TO_NS),
        ScrollPlaceholderDecision::DEFER_WITH_PLACEHOLDER);
    // Nearly exhausted budget always defers.
    EXPECT_EQ(ScrollPlaceholderPredictor::Decide(1, 1000), ScrollPlaceholderDecision::DEFER_WITH_PLACEHOLDER);
    // Negative/zero budget defers.
    EXPECT_EQ(ScrollPlaceholderPredictor::Decide(5 * MS_TO_NS, 0), ScrollPlaceholderDecision::DEFER_WITH_PLACEHOLDER);
}

/**
 * @tc.name: ScrollPlaceholderPredictorTest/DecideSyncWhenBudgetSufficient
 * @tc.desc: Budget decision builds synchronously when the estimate fits.
 */
HWTEST_F(ScrollPlaceholderPredictorTest, DecideSyncWhenBudgetSufficient, TestSize.Level1)
{
    // 8.33ms frame budget with 5ms item: fits after the safety margin.
    EXPECT_EQ(ScrollPlaceholderPredictor::Decide(5 * MS_TO_NS, 8333333), ScrollPlaceholderDecision::SYNC_BUILD);
    // Huge budget, tiny item.
    EXPECT_EQ(ScrollPlaceholderPredictor::Decide(1, 16 * MS_TO_NS), ScrollPlaceholderDecision::SYNC_BUILD);
}

/**
 * @tc.name: ScrollPlaceholderPredictorTest/Reset
 * @tc.desc: Reset clears one template without touching others.
 */
HWTEST_F(ScrollPlaceholderPredictorTest, Reset, TestSize.Level1)
{
    ScrollPlaceholderPredictor predictor;
    for (int i = 0; i < 10; ++i) {
        predictor.RecordBuildCost("a", 1 * MS_TO_NS);
        predictor.RecordBuildCost("b", 1 * MS_TO_NS);
    }
    predictor.Reset("a");
    EXPECT_FALSE(predictor.EstimateBuildCost("a").warm);
    EXPECT_TRUE(predictor.EstimateBuildCost("b").warm);
    predictor.ResetAll();
    EXPECT_FALSE(predictor.EstimateBuildCost("b").warm);
}

} // namespace OHOS::Ace::NG
