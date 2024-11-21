/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

#include "scroll_bar_test_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_HEIGHT = 16.f;
} // namespace

class ScrollBarLayoutTestNg : public ScrollBarTestNg {
public:
};

/**
 * @tc.name: ScrollBarLayout001
 * @tc.desc: Test scrollBar layout in HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarLayoutTestNg, ScrollBarLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has scrollBar height, has scrollBar child height
     * @tc.expected: The scrollBar height is scrollBar height
     */
    float scrollBarMainSize = 100.f;
    float scrollBarCrossSize = 300.f;
    CreateStack(Alignment::BOTTOM_CENTER);
    CreateScroll();
    CreateScrollBar(true, true, Axis::HORIZONTAL, DisplayMode::ON);
    SetSize(Axis::HORIZONTAL, CalcLength(scrollBarMainSize), CalcLength(scrollBarCrossSize));
    CreateScrollBarChild();
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 1),
        RectF(90.f, SCROLL_HEIGHT - scrollBarMainSize, scrollBarCrossSize, scrollBarMainSize)));

    /**
     * @tc.steps: step2. Has no scrollBar height, has no scrollBar child height
     * @tc.expected: The scrollBar height is theme height
     */
    CreateStack(Alignment::BOTTOM_CENTER);
    CreateScroll();
    CreateScrollBar(true, true, Axis::HORIZONTAL, DisplayMode::ON);
    ColumnModelNG colModel;
    colModel.Create(Dimension(0), nullptr, "");
    SetSize(Axis::HORIZONTAL, CalcLength(0), CalcLength(0));
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(
        IsEqual(GetChildRect(stackNode_, 1), RectF(0, SCROLL_HEIGHT - DEFAULT_HEIGHT, SCROLL_WIDTH, DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step3. Has no scrollBar height, has scrollBar child height
     * @tc.expected: The scrollBar height is child height
     */
    CreateStack(Alignment::BOTTOM_CENTER);
    CreateScroll();
    CreateScrollBar(true, true, Axis::HORIZONTAL, DisplayMode::ON);
    colModel.Create(Dimension(0), nullptr, "");
    SetSize(Axis::HORIZONTAL, CalcLength(SCROLL_BAR_CHILD_WIDTH), CalcLength(SCROLL_BAR_CHILD_HEIGHT));
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 1),
        RectF(0, SCROLL_HEIGHT - SCROLL_BAR_CHILD_WIDTH, SCROLL_WIDTH, SCROLL_BAR_CHILD_WIDTH)));
}

/**
 * @tc.name: DisplayMode001
 * @tc.desc: Test DisplayMode
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarLayoutTestNg, DisplayMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DisplayMode::ON
     * @tc.expected: Show scrollBar
     */
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    auto scrollBarRenderContext = frameNode_->GetRenderContext();
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 1);

    /**
     * @tc.steps: step2. DisplayMode::ON
     * @tc.expected: Show scrollBar
     */
    layoutProperty_->UpdateDisplayMode(DisplayMode::ON);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 1);

    /**
     * @tc.steps: step3. DisplayMode::AUTO
     * @tc.expected: Hide scrollBar
     */
    layoutProperty_->UpdateDisplayMode(DisplayMode::AUTO);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 0);

    layoutProperty_->UpdateDisplayMode(DisplayMode::AUTO);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 0);

    /**
     * @tc.steps: step4. DisplayMode::OFF
     * @tc.expected: Hide scrollBar
     */
    layoutProperty_->UpdateDisplayMode(DisplayMode::OFF);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 0);

    /**
     * @tc.steps: step5. DisplayMode::ON
     * @tc.expected: Show scrollBar
     */
    layoutProperty_->UpdateDisplayMode(DisplayMode::ON);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 1);
}

/**
 * @tc.name: DisplayMode002
 * @tc.desc: Test DisplayMode
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarLayoutTestNg, DisplayMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UnScrollable and DisplayMode::AUTO
     * @tc.expected: Hide scrollBar
     */
    CreateStack();
    CreateScroll(SCROLL_HEIGHT);
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    CreateScrollBarChild();
    CreateDone();
    auto scrollBarRenderContext = frameNode_->GetRenderContext();
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 0);
}

/**
 * @tc.name: UpdateScrollBarOffset001
 * @tc.desc: Test UpdateScrollBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarLayoutTestNg, UpdateScrollBarOffset001, TestSize.Level1)
{
    const int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), UINT8_MAX);

    /**
     * @tc.steps: step1. Change scroll height and scrollable
     * @tc.expected: Still show scrollBar
     */
    SetScrollContentMainSize(CONTENT_MAIN_SIZE + 100.f);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), UINT8_MAX);

    /**
     * @tc.steps: step2. Change scroll height and unScrollable
     * @tc.expected: Hide scrollBar
     */
    SetScrollContentMainSize(SCROLL_HEIGHT);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), 0);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: SetScrollBar001
 * @tc.desc: Test SetScrollBar in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarLayoutTestNg, SetScrollBar001, TestSize.Level1)
{
    const int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateDone();
    FlushLayoutTask(frameNode_);
    EXPECT_NE(pattern_->scrollBar_, nullptr);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), UINT8_MAX);

    /**
     * @tc.steps: step1. Change to DisplayMode::OFF
     * @tc.expected: Hide scrollBar
     */
    pattern_->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(pattern_->scrollBar_, nullptr);
    pattern_->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(pattern_->scrollBar_, nullptr);

    /**
     * @tc.steps: step2. Change axis
     * @tc.expected: ScrollBar positionMode changed
     */
    layoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(stackNode_);
    pattern_->SetScrollBar(DisplayMode::ON);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->positionMode_, PositionMode::BOTTOM);

    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: SetScrollBar002
 * @tc.desc: Test SetScrollBar in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarLayoutTestNg, SetScrollBar002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Change to DisplayMode::ON
     * @tc.expected: Show scrollBar when scrollable
     */
    const int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    CreateDone();
    FlushLayoutTask(frameNode_);
    EXPECT_NE(pattern_->scrollBar_, nullptr);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), UINT8_MAX);

    pattern_->SetScrollBar(DisplayMode::ON);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), UINT8_MAX);

    /**
     * @tc.steps: step2. Change to DisplayMode::ON
     * @tc.expected: Still Hide scrollBar when unScrollable
     */
    pattern_->SetScrollBar(DisplayMode::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), 0);

    SetScrollContentMainSize(SCROLL_HEIGHT);
    EXPECT_FALSE(pattern_->scrollBar_->IsScrollable());
    pattern_->SetScrollBar(DisplayMode::ON);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), 0);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}
} // namespace OHOS::Ace::NG
