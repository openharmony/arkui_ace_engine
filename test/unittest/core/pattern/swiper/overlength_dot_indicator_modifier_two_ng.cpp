/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "swiper_test_ng.h"

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/overlength_dot_indicator_modifier.h"

namespace OHOS::Ace::NG {

class SwiperIndicatorTestTwoNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: NeedUpdateWhenAnimationFinish008
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish008, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 2.0f;
    modifier.currentSelectedIndex_ = 9;
    modifier.targetSelectedIndex_ = 6;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedUpdateWhenAnimationFinish009
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish009, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 0.3f;
    modifier.currentSelectedIndex_ = 3;
    modifier.targetSelectedIndex_ = 6;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedUpdateWhenAnimationFinish010
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish010, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 0.3f;
    modifier.currentSelectedIndex_ = 3;
    modifier.targetSelectedIndex_ = 2;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedUpdateWhenAnimationFinish011
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish011, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 0.7f;
    modifier.currentSelectedIndex_ = 3;
    modifier.targetSelectedIndex_ = 4;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedUpdateWhenAnimationFinish012
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish012, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 0.7f;
    modifier.currentSelectedIndex_ = 4;
    modifier.targetSelectedIndex_ = 3;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedUpdateWhenAnimationFinish013
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish013, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 2.0f;
    modifier.currentSelectedIndex_ = 4;
    modifier.targetSelectedIndex_ = 3;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedUpdateWhenAnimationFinish014
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish014, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 2.0f;
    modifier.currentSelectedIndex_ = 3;
    modifier.targetSelectedIndex_ = 4;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedUpdateWhenAnimationFinish015
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish015, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 0.4f;
    modifier.currentSelectedIndex_ = 4;
    modifier.targetSelectedIndex_ = 3;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NeedUpdateWhenAnimationFinish016
 * @tc.desc: Test OverlengthDotIndicatorModifier NeedUpdateWhenAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, NeedUpdateWhenAnimationFinish016, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.forceStopPageRate_ = 0.4f;
    modifier.currentSelectedIndex_ = 3;
    modifier.targetSelectedIndex_ = 4;
    modifier.maxDisplayCount_ = 6;
    auto result = modifier.NeedUpdateWhenAnimationFinish();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PlayBlackPointsAnimation001
 * @tc.desc: Test OverlengthDotIndicatorModifier PlayBlackPointsAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, PlayBlackPointsAnimation001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.targetSelectedIndex_ = 0;
    modifier.moveDirection_ = OverlongIndicatorMove::MOVE_BACKWARD;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.PlayBlackPointsAnimation(itemHalfSizes);
    EXPECT_EQ(modifier.longPointRightCenterX_, 1);
}

/**
 * @tc.name: PlayBlackPointsAnimation002
 * @tc.desc: Test OverlengthDotIndicatorModifier PlayBlackPointsAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, PlayBlackPointsAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create OverlengthDotIndicatorModifier, check isSelectedColorAnimEnd_ after animation end.
     */
    RefPtr<OverlengthDotIndicatorModifier> modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    modifier->targetSelectedIndex_ = 0;
    modifier->moveDirection_ = OverlongIndicatorMove::MOVE_BACKWARD;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier->PlayBlackPointsAnimation(itemHalfSizes);
    EXPECT_EQ(modifier->isSelectedColorAnimEnd_, true);
}
} // namespace OHOS::Ace::NG