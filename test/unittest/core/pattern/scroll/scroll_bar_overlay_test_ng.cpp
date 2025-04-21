/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

void ScrollBarOverlayTestNg::SetUp() {}

void ScrollBarOverlayTestNg::TearDown() {}

/**
 * @tc.name: StopAdaptAnimation001
 * @tc.desc: Test StopAdaptAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StopAdaptAnimation001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0, 0);
    ASSERT_NE(motion, nullptr);
    option.SetCurve(motion);
    auto adaptAnimation_ = AnimationUtils::StartAnimation(option, [&]() {});
    ASSERT_NE(adaptAnimation_, nullptr);
    scrollBarOverlayModifier.StopAdaptAnimation();
    EXPECT_EQ(scrollBarOverlayModifier.isAdaptAnimationStop_, true);
}

/**
 * @tc.name: SetMainModeSize001
 * @tc.desc: Test SetMainModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetMainModeSize001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Size size;
    auto barWidth = scrollBarOverlayModifier.barWidth_;
    scrollBarOverlayModifier.barWidth_->Set(size.Width());
    scrollBarOverlayModifier.positionMode_ = PositionMode::BOTTOM;
    scrollBarOverlayModifier.SetMainModeSize(size);
    EXPECT_EQ(scrollBarOverlayModifier.barWidth_, barWidth);
}

/**
 * @tc.name: SetMainModeSize002
 * @tc.desc: Test SetMainModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetMainModeSize002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Size size;
    auto barHeight = scrollBarOverlayModifier.barHeight_;
    scrollBarOverlayModifier.barHeight_->Set(size.Height());
    scrollBarOverlayModifier.positionMode_ = PositionMode::RIGHT;
    scrollBarOverlayModifier.SetMainModeSize(size);
    EXPECT_EQ(scrollBarOverlayModifier.barHeight_, barHeight);
}

/**
 * @tc.name: SetCrossModeSize001
 * @tc.desc: Test SetCrossModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetCrossModeSize001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Size size;
    auto barHeight = scrollBarOverlayModifier.barHeight_;
    scrollBarOverlayModifier.barHeight_->Set(size.Height());
    scrollBarOverlayModifier.positionMode_ = PositionMode::BOTTOM;
    scrollBarOverlayModifier.SetCrossModeSize(size);
    EXPECT_EQ(scrollBarOverlayModifier.barHeight_, barHeight);
}

/**
 * @tc.name: SetCrossModeSize002
 * @tc.desc: Test SetCrossModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetCrossModeSize002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Size size;
    auto barWidth = scrollBarOverlayModifier.barWidth_;
    scrollBarOverlayModifier.barWidth_->Set(size.Width());
    scrollBarOverlayModifier.positionMode_ = PositionMode::RIGHT;
    scrollBarOverlayModifier.SetCrossModeSize(size);
    EXPECT_EQ(scrollBarOverlayModifier.barWidth_, barWidth);
}

/**
 * @tc.name: SetMainModeOffset001
 * @tc.desc: Test SetMainModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetMainModeOffset001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset;
    auto barX = scrollBarOverlayModifier.barX_;
    scrollBarOverlayModifier.barX_->Set(offset.GetX());
    scrollBarOverlayModifier.positionMode_ = PositionMode::BOTTOM;
    scrollBarOverlayModifier.SetMainModeOffset(offset);
    EXPECT_EQ(scrollBarOverlayModifier.barX_, barX);
}

/**
 * @tc.name: SetMainModeOffset002
 * @tc.desc: Test SetMainModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetMainModeOffset002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset;
    auto barY = scrollBarOverlayModifier.barY_;
    scrollBarOverlayModifier.barY_->Set(offset.GetY());
    scrollBarOverlayModifier.positionMode_ = PositionMode::RIGHT;
    scrollBarOverlayModifier.SetMainModeOffset(offset);
    EXPECT_EQ(scrollBarOverlayModifier.barY_, barY);
}

/**
 * @tc.name: SetCrossModeOffset001
 * @tc.desc: Test SetCrossModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetCrossModeOffset001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset;
    auto barY = scrollBarOverlayModifier.barY_;
    scrollBarOverlayModifier.barY_->Set(offset.GetY());
    scrollBarOverlayModifier.positionMode_ = PositionMode::BOTTOM;
    scrollBarOverlayModifier.SetCrossModeOffset(offset);
    EXPECT_EQ(scrollBarOverlayModifier.barY_, barY);
}

/**
 * @tc.name: SetCrossModeOffset002
 * @tc.desc: Test SetCrossModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetCrossModeOffset002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset;
    auto barX = scrollBarOverlayModifier.barX_;
    scrollBarOverlayModifier.barX_->Set(offset.GetX());
    scrollBarOverlayModifier.positionMode_ = PositionMode::RIGHT;
    scrollBarOverlayModifier.SetCrossModeOffset(offset);
    EXPECT_EQ(scrollBarOverlayModifier.barX_, barX);
}

/**
 * @tc.name: StartOpacityAnimation001
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::APPEAR_WITHOUT_ANIMATION;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_EQ(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: StartOpacityAnimation002
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::APPEAR;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_NE(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: StartOpacityAnimation003
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation003, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::DISAPPEAR;
    scrollBarOverlayModifier.isNavDestinationShow_ = false;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_EQ(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: StartOpacityAnimation004
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation004, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::APPEAR;
    scrollBarOverlayModifier.isNavDestinationShow_ = false;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_NE(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: StartOpacityAnimation005
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation005, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::APPEAR;
    scrollBarOverlayModifier.isNavDestinationShow_ = true;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_NE(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG