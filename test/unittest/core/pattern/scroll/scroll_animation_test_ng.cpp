/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "scroll_test_ng.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

class ScrolleAnimationTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: PlaySpringAnimation001
 * @tc.desc: Test PlaySpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleAnimationTestNg, PlaySpringAnimation001, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) {});
    auto smooth = false;
    pattern_->isAnimationStop_ = false;
    pattern_->AnimateTo(ITEM_HEIGHT * TOTAL_LINE_NUMBER, 1.f, Curves::LINEAR, smooth);
    EXPECT_FALSE(pattern_->isAnimationStop_);
}

/**
 * @tc.name: StopAnimation001
 * @tc.desc: Test StopAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleAnimationTestNg, StopAnimation001, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) {});
    std::shared_ptr<AnimationUtils::Animation> animation;
    pattern_->StopAnimation(animation);
    EXPECT_TRUE(pattern_->isAnimationStop_);
}

/**
 * @tc.name: StopAdaptAnimation001
 * @tc.desc: Test StopAdaptAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleAnimationTestNg, StopAdaptAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, start adapt animation
     * @tc.expected: Change modifer's MainModeSize to the initial value
     */
    double x = 1.00;
    double y = 1.25;
    double width = 1.00;
    double height = 2.00;
    Rect rect(x, y, width, height);
    bool needAdaptAnimation = true;
    ScrollBarOverlayModifier modifer;
    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.314f, 0.95f);
    option.SetCurve(motion);
    std::shared_ptr<AnimationUtils::Animation> adaptAnimation_ = AnimationUtils::StartAnimation(option, [&]() {});
    modifer.StartAdaptAnimation(rect, needAdaptAnimation);
    modifer.StopAdaptAnimation();
    EXPECT_NE(adaptAnimation_, nullptr);
}

/**
 * @tc.name: StartHoverAnimation001
 * @tc.desc: Test StartHoverAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleAnimationTestNg, StartHoverAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set hoverAnimationType is GROW
     * @tc.expected: modifer's hoverAnimatingType_ is equal to the hoverType
     */
    ScrollBarOverlayModifier modifer;
    auto hoverType = HoverAnimationType::GROW;
    double x = 1.00;
    double y = 1.25;
    double width = 1.00;
    double height = 2.00;
    Rect rect(x, y, width, height);
    modifer.StartHoverAnimation(rect, HoverAnimationType::GROW);
    EXPECT_EQ(modifer.hoverAnimatingType_, hoverType);
}

/**
 * @tc.name: StartHoverAnimation002
 * @tc.desc: Test StartHoverAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleAnimationTestNg, StartHoverAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set hoverAnimationType is GROW
     * @tc.expected: modifer's hoverAnimatingType_ is equal to the hoverType
     */
    ScrollBarOverlayModifier modifer;
    auto hoverType = HoverAnimationType::SHRINK;
    double x = 1.00;
    double y = 1.25;
    double width = 1.00;
    double height = 2.00;
    Rect rect(x, y, width, height);
    modifer.StartHoverAnimation(rect, HoverAnimationType::SHRINK);
    EXPECT_EQ(modifer.hoverAnimatingType_, hoverType);
}

/**
 * @tc.name: StopHoverAnimation001
 * @tc.desc: Test StopHoverAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleAnimationTestNg, StopHoverAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, start hover animation
     * @tc.expected: modifer's hoverAnimation_ is initialized and stopped
     */
    ScrollBarOverlayModifier modifer;
    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.314f, 0.95f);
    option.SetCurve(motion);
    std::shared_ptr<AnimationUtils::Animation> hoverAnimation_ = AnimationUtils::StartAnimation(option, [&]() {});
    double x = 1.00;
    double y = 1.25;
    double width = 1.00;
    double height = 2.00;
    Rect rect(x, y, width, height);
    modifer.StartHoverAnimation(rect, HoverAnimationType::SHRINK);
    modifer.StopHoverAnimation();
    EXPECT_NE(modifer.hoverAnimation_, nullptr);
}
} // namespace OHOS::Ace::NG
