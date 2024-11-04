/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "core/components_ng/manager/frame_rate/frame_rate_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class FrameRateRangeTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void FrameRateRangeTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void FrameRateRangeTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RateChangedTest
 * @tc.desc: RateChanged Set and Get test.
 * @tc.type: FUNC
 */
HWTEST_F(FrameRateRangeTest, RateChangedTest, TestSize.Level1)
{
    FrameRateManager frameRageManager;
    EXPECT_EQ(false, frameRageManager.IsRateChanged());
    frameRageManager.SetIsRateChanged(true);
    EXPECT_EQ(true, frameRageManager.IsRateChanged());
}

/**
 * @tc.name: NodeRateTest
 * @tc.desc: NodeRateTest Add and Remove and Update test.
 * @tc.type: FUNC
 */
HWTEST_F(FrameRateRangeTest, NodeRateTest, TestSize.Level1)
{
    int32_t nodeId = 1;
    int32_t nodeId2 = 2;
    int32_t rate1 = 60;
    int32_t rate2 = 120;
    FrameRateManager frameRageManager;
    EXPECT_EQ(false, frameRageManager.IsRateChanged());
    frameRageManager.AddNodeRate(nodeId, rate1);
    EXPECT_EQ(true, frameRageManager.IsRateChanged());

    frameRageManager.SetIsRateChanged(false);
    frameRageManager.AddNodeRate(nodeId, rate2);
    EXPECT_EQ(false, frameRageManager.IsRateChanged());

    frameRageManager.SetIsRateChanged(false);
    frameRageManager.UpdateNodeRate(nodeId2, rate2);
    EXPECT_EQ(false, frameRageManager.IsRateChanged());
    frameRageManager.UpdateNodeRate(nodeId, rate2);
    EXPECT_EQ(true, frameRageManager.IsRateChanged());

    frameRageManager.SetIsRateChanged(false);
    frameRageManager.RemoveNodeRate(nodeId2);
    EXPECT_EQ(false, frameRageManager.IsRateChanged());
    frameRageManager.RemoveNodeRate(nodeId);
    EXPECT_EQ(true, frameRageManager.IsRateChanged());
}

/**
 * @tc.name: GetDisplaySyncRate
 * @tc.desc: GetDisplaySyncRate test.
 * @tc.type: FUNC
 */
HWTEST_F(FrameRateRangeTest, GetDisplaySyncRate, TestSize.Level1)
{
    int32_t nodeId = 1;
    int32_t rate = 120;
    int32_t displaySyncRate = 90;
    int32_t animateRate = 60;
    FrameRateManager frameRageManager;
    auto [expectedRate1, expectedRateType1] = frameRageManager.GetExpectedRate();
    EXPECT_EQ(0, expectedRate1);
    EXPECT_EQ(0, expectedRateType1);
    EXPECT_EQ(0, frameRageManager.GetDisplaySyncRate());
    frameRageManager.SetDisplaySyncRate(displaySyncRate);
    EXPECT_EQ(displaySyncRate, frameRageManager.GetDisplaySyncRate());
    EXPECT_EQ(true, frameRageManager.IsRateChanged());

    frameRageManager.SetIsRateChanged(false);
    frameRageManager.SetDisplaySyncRate(displaySyncRate);
    EXPECT_EQ(false, frameRageManager.IsRateChanged());

    frameRageManager.SetIsRateChanged(false);
    frameRageManager.SetAnimateRate(animateRate, false);
    EXPECT_EQ(true, frameRageManager.IsRateChanged());
    frameRageManager.SetIsRateChanged(false);
    frameRageManager.SetAnimateRate(animateRate, false);
    EXPECT_EQ(false, frameRageManager.IsRateChanged());

    frameRageManager.AddNodeRate(nodeId, rate);
    auto [expectedRate2, expectedRateType2] = frameRageManager.GetExpectedRate();
    EXPECT_EQ(rate, expectedRate2);
    EXPECT_EQ(ACE_COMPONENT_FRAME_RATE_TYPE, expectedRateType2);
}
} // namespace OHOS::Ace::NG