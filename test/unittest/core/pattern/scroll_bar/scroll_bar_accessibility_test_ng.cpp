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
constexpr float CURRENT_DISTANCE = 5.0f;
constexpr float MIN_DISTANCE = 0.0f;
constexpr float SCROLLABLE_DISTANCE = 10.0f;
} // namespace

class ScrollBarAccessibilityTestNg : public ScrollBarTestNg {
public:
};

/**
 * @tc.name: IsScrollable001
 * @tc.desc: Test IsScrollable of scrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityTestNg, IsScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Axis::VERTICAL and has ControlDistance
     * @tc.expected: Scrollable
     */
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(pattern_->GetControlDistance(), 200.f);

    /**
     * @tc.steps: step2. Axis::VERTICAL and has no ControlDistance
     * @tc.expected: UnScrollable
     */
    SetScrollContentMainSize(SCROLL_HEIGHT);
    EXPECT_EQ(pattern_->GetControlDistance(), 0.f);
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());

    /**
     * @tc.steps: step3. Axis::NONE and has ControlDistance
     * @tc.expected: UnScrollable
     */
    SetScrollContentMainSize(CONTENT_MAIN_SIZE);
    EXPECT_EQ(pattern_->GetControlDistance(), 200.f);
    pattern_->axis_ = Axis::NONE;
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: IsScrollable002
 * @tc.desc: Test IsScrollable without child
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityTestNg, IsScrollable002, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    CreateDone();
    FlushUITasks();
    EXPECT_NE(pattern_->scrollBar_, nullptr);
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_->GetOpacity(), UINT8_MAX);

    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: IsScrollable003
 * @tc.desc: Test IsScrollable of scrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityTestNg, IsScrollable003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. child height greater than scrollbar height
     * @tc.expected: Scrollable
     */
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild(2000.f);
    CreateDone();
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: ScrollBarAccessibilityPropertyGetAccessibilityValue001
 * @tc.desc: Test GetAccessibilityValue of scrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityTestNg, ScrollBarAccessibilityPropertyGetAccessibilityValue001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    EXPECT_TRUE(accessibilityProperty_->HasRange());
    AccessibilityValue result = accessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, MIN_DISTANCE);
    EXPECT_EQ(result.max, SCROLL_HEIGHT - SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(result.current, MIN_DISTANCE);

    pattern_->currentOffset_ = CURRENT_DISTANCE;
    pattern_->scrollableDistance_ = SCROLLABLE_DISTANCE;
    result = accessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, MIN_DISTANCE);
    EXPECT_EQ(result.max, SCROLLABLE_DISTANCE);
    EXPECT_EQ(result.current, CURRENT_DISTANCE);
}

/**
 * @tc.name: SetSpecificSupportAction001
 * @tc.desc: Test GetSupportAction of scrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityTestNg, SetSpecificSupportAction001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 640.f);

    /**
     * @tc.steps: step1. Scroll to Top.
     */
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0.f);
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SCROLL_FORWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    pattern_->UpdateCurrentOffset(1.f, SCROLL_FROM_BAR);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 1.f);
    accessibilityProperty_->ResetSupportAction();
    expectedActions = { AceAction::ACTION_SCROLL_FORWARD, AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step3. Scroll to bottom.
     */
    pattern_->UpdateCurrentOffset(SCROLL_HEIGHT - SCROLL_BAR_CHILD_HEIGHT, SCROLL_FROM_BAR);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 640.f);
    accessibilityProperty_->ResetSupportAction();
    expectedActions = { AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: SetSpecificSupportAction002
 * @tc.desc: Test GetSupportAction of scrollBar.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityTestNg, SetSpecificSupportAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UnScrollable
     */
    CreateStack();
    CreateScroll(SCROLL_HEIGHT);
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = {};
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: ScrollBar Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityTestNg, PerformActionTest001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    /**
     * @tc.steps: step1. Axis::VERTICAL
     * @tc.expected: Can scroll
     */
    accessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 50.f);

    accessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step2. Axis::NONE
     * @tc.expected: Can not scroll
     */
    layoutProperty_->UpdateAxis(Axis::NONE);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    accessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    accessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step2. Axis::VERTICAL, but unScrollable
     * @tc.expected: Can not scroll
     */
    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    SetScrollContentMainSize(SCROLL_HEIGHT);
    accessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    accessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: ScrollBar Accessibility PerformAction test ScrollForward and ScrollBackward. UnScrollable scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarAccessibilityTestNg, PerformActionTest002, TestSize.Level1)
{
    CreateStack();
    CreateScroll(SCROLL_HEIGHT);
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    EXPECT_EQ(scrollPattern_->GetScrollableDistance(), 0.f);

    accessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    accessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);
}
} // namespace OHOS::Ace::NG
