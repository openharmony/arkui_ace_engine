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

class ScrolleInnerTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: SetMainModeSize001
 * @tc.desc: Test SetMainModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleInnerTestNg, SetMainModeSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set positionMode_ is BOTTOM
     * @tc.expected: modifer's barWidth_ is equal to the width of size
     */
    ScrollBarOverlayModifier modifer;
    modifer.SetPositionMode(PositionMode::BOTTOM);
    auto width = 1.0;
    auto hight = 1.0;
    modifer.SetMainModeSize(Size(width, hight));
    EXPECT_EQ(modifer.barWidth_, width);
}

/**
 * @tc.name: SetCrossModeSize001
 * @tc.desc: Test SetCrossModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleInnerTestNg, SetCrossModeSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set positionMode_ is BOTTOM
     * @tc.expected: modifer's barHeight_ is equal to the hight of size
     */
    ScrollBarOverlayModifier modifer;
    modifer.SetPositionMode(PositionMode::BOTTOM);
    auto width = 1.0;
    auto hight = 1.0;
    modifer.SetCrossModeSize(Size(width, hight));
    EXPECT_EQ(modifer.barHeight_, hight);
}

/**
 * @tc.name: SetCrossModeSize002
 * @tc.desc: Test SetCrossModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleInnerTestNg, SetCrossModeSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set positionMode_ is not BOTTOM
     * @tc.expected: modifer's barWidth_ is equal to the width of size
     */
    auto width = 1.0;
    auto hight = 1.0;
    ScrollBarOverlayModifier modifer;
    modifer.SetPositionMode(PositionMode::LEFT);
    modifer.SetCrossModeSize(Size(width, hight));
    EXPECT_EQ(modifer.barWidth_, width);
}

/**
 * @tc.name: SetMainModeOffset001
 * @tc.desc: Test SetMainModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleInnerTestNg, SetMainModeOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set positionMode_ is BOTTOM
     * @tc.expected: modifer's barX_ is equal to the width of x
     */
    auto x = 1.f;
    auto y = 2.f;
    ScrollBarOverlayModifier modifer;
    modifer.SetPositionMode(PositionMode::BOTTOM);
    modifer.SetMainModeOffset(Offset(x, y));
    EXPECT_EQ(modifer.barX_, x);
}

/**
 * @tc.name: SetCrossModeOffset001
 * @tc.desc: Test SetCrossModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleInnerTestNg, SetCrossModeOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set positionMode_ is BOTTOM
     * @tc.expected: modifer's barY_ is equal to the y of Offset
     */
    auto x = 1.f;
    auto y = 1.f;
    ScrollBarOverlayModifier modifer;
    modifer.SetPositionMode(PositionMode::BOTTOM);
    modifer.SetCrossModeOffset(Offset(x, y));
    EXPECT_EQ(modifer.barY_, y);
}

/**
 * @tc.name: GetHoverOffset001
 * @tc.desc: Test GetHoverOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleInnerTestNg, GetHoverOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set positionMode_ is RIGHT
     * @tc.expected: modifer's Offset is assigned a correlation value
     */
    auto width = 1.0;
    auto hight = 1.0;
    ScrollBarOverlayModifier modifer;
    modifer.SetPositionMode(PositionMode::RIGHT);
    auto result = modifer.GetHoverOffset(Size(width, hight));
    auto offsetResult = width - modifer.barWidth_->Get();
    EXPECT_EQ(result, Offset(offsetResult, 0.f));
}

/**
 * @tc.name: GetHoverOffset002
 * @tc.desc: Test GetHoverOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleInnerTestNg, GetHoverOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBarOverlayModifier, set positionMode_ is BOTTOM
     * @tc.expected: modifer's Offset is assigned a correlation value
     */
    auto width = 1.0;
    auto hight = 1.0;
    ScrollBarOverlayModifier modifer;
    modifer.SetPositionMode(PositionMode::BOTTOM);
    modifer.GetHoverOffset(Size(width, hight));
    auto result = modifer.GetHoverOffset(Size(width, hight));
    auto offsetResult = hight - modifer.barHeight_->Get();
    EXPECT_EQ(result, Offset(0.f, offsetResult));
}
} // namespace OHOS::Ace::NG
