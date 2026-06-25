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

#include "animation_test_min.h"

#include "core/animation/animation_pub.h"

using namespace testing;
using namespace testing::ext;

class AnimationPubTest : public AnimationTestBase {};

/**
 * @tc.name: HistogramInfiniteAnimationEvent_AllBranches
 * @tc.desc: Test HistogramInfiniteAnimationEvent covers all AnimationInterface enum values
 * @tc.type: FUNC
 */
HWTEST_F(AnimationPubTest, HistogramInfiniteAnimationEvent_AllBranches, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call HistogramInfiniteAnimationEvent with all valid enum values.
     * @tc.expected: step1. No crash for any branch.
     */
    OHOS::Ace::HistogramInfiniteAnimationEvent(OHOS::Ace::AnimationInterface::ANIMATION);
    OHOS::Ace::HistogramInfiniteAnimationEvent(OHOS::Ace::AnimationInterface::ANIMATE_TO);
    OHOS::Ace::HistogramInfiniteAnimationEvent(OHOS::Ace::AnimationInterface::ANIMATE_TO_IMMEDIATELY);
    OHOS::Ace::HistogramInfiniteAnimationEvent(OHOS::Ace::AnimationInterface::KEYFRAME_ANIMATE_TO);
    /**
     * @tc.steps: step2. Call with UNKNOWN to cover default branch.
     * @tc.expected: step2. No crash, default branch handled.
     */
    OHOS::Ace::HistogramInfiniteAnimationEvent(OHOS::Ace::AnimationInterface::UNKNOWN);
    /**
     * @tc.steps: step3. Call GetAnimationInterfaceName with all valid enum values.
     * @tc.expected: step3. Returns correct name string for each.
     */
    auto nameAnimation = OHOS::Ace::GetAnimationInterfaceName(OHOS::Ace::AnimationInterface::ANIMATION);
    EXPECT_NE(nameAnimation, nullptr);
    EXPECT_STREQ(nameAnimation, "animation");
    auto nameAnimateTo = OHOS::Ace::GetAnimationInterfaceName(OHOS::Ace::AnimationInterface::ANIMATE_TO);
    EXPECT_NE(nameAnimateTo, nullptr);
    EXPECT_STREQ(nameAnimateTo, "animateTo");
    auto nameKeyframe = OHOS::Ace::GetAnimationInterfaceName(
        OHOS::Ace::AnimationInterface::KEYFRAME_ANIMATE_TO);
    EXPECT_NE(nameKeyframe, nullptr);
    EXPECT_STREQ(nameKeyframe, "keyframeAnimateTo");
    /**
     * @tc.steps: step4. Call GetAnimationInterfaceName with out-of-range value.
     * @tc.expected: step4. Returns nullptr.
     */
    auto nameInvalid = OHOS::Ace::GetAnimationInterfaceName(static_cast<OHOS::Ace::AnimationInterface>(-1));
    EXPECT_EQ(nameInvalid, nullptr);
}

/**
 * @tc.name: GetAnimationFinishCount_Basic
 * @tc.desc: Test GetAnimationFinishCount returns incrementing values
 * @tc.type: FUNC
 */
HWTEST_F(AnimationPubTest, GetAnimationFinishCount_Basic, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetAnimationFinishCount twice.
     * @tc.expected: step1. Second call returns value greater than first.
     */
    auto count1 = OHOS::Ace::GetAnimationFinishCount();
    auto count2 = OHOS::Ace::GetAnimationFinishCount();
    EXPECT_GT(count2, count1);
}
