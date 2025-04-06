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
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"

namespace OHOS::Ace::NG {

class ArcScrollBarTestNg : public ScrollBarTestNg {
public:
    void CreateArcScrollBar(DisplayMode displayMode);
};

void ArcScrollBarTestNg::CreateArcScrollBar(DisplayMode displayMode)
{
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(displayMode), true);
    GetScrollBar();
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: Test ArcScrollBar about HandleDrag, the scrollBar and scroll position will change by drag
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, HandleDrag001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 1), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    float controlDistance = pattern_->GetControlDistance();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(controlDistance, CONTENT_MAIN_SIZE - SCROLL_HEIGHT);
    EXPECT_EQ(scrollableDistance, 0);

    auto scrollBar = pattern_->GetScrollBar();
    EXPECT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    EXPECT_NE(arcScrollBar, nullptr);
    EXPECT_EQ(arcScrollBar->trickStartAngle_, -30.0);
    /**
     * @tc.steps: step1. HandleDragStart, drag on scrollBar
     */
    GestureEvent info;
    arcScrollBar->HandleDragStart(info);

    /**
     * @tc.steps: step2. HandleDragUpdate, drag up
     * @tc.expected: Can not scroll up because at top
     */
    float delta = SCROLL_BAR_CHILD_HEIGHT;
    info.SetMainDelta(-delta);
    arcScrollBar->HandleDragUpdate(info);
    FlushUITasks(stackNode_);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);
    EXPECT_EQ(arcScrollBar->trickStartAngle_, -30.0);

    /**
     * @tc.steps: step3. HandleDragUpdate, drag down
     * @tc.expected: Scroll down
     */
    info.SetMainDelta(delta);
    arcScrollBar->HandleDragUpdate(info);
    FlushUITasks(stackNode_);
    float expectOffset = 200.f;
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), expectOffset);
    EXPECT_GT(arcScrollBar->trickStartAngle_, -30.0);

    /**
     * @tc.steps: step4. HandleDragUpdate, drag up
     * @tc.expected: Scroll up
     */
    info.SetMainDelta(-delta);
    arcScrollBar->HandleDragUpdate(info);
    FlushUITasks(stackNode_);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0);
    EXPECT_EQ(arcScrollBar->trickStartAngle_, -30.0);

    /**
     * @tc.steps: step5. HandleDragEnd, drag end
     */
    arcScrollBar->HandleDragEnd(info);
    FlushUITasks(stackNode_);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0);
    EXPECT_EQ(arcScrollBar->trickStartAngle_, -30.0);
}

/**
 * @tc.name: HandleDrag002
 * @tc.desc: Test ArcScrollBar about HandleDrag and out of boundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, HandleDrag002, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 1), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    float controlDistance = pattern_->GetControlDistance();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(controlDistance, CONTENT_MAIN_SIZE - SCROLL_HEIGHT);
    EXPECT_EQ(scrollableDistance, 0);

    auto scrollBar = pattern_->GetScrollBar();
    EXPECT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    EXPECT_NE(arcScrollBar, nullptr);
    EXPECT_EQ(arcScrollBar->trickStartAngle_, -30.0);

    /**
     * @tc.steps: step1. HandleDragStart, drag on scrollBar
     */
    GestureEvent info;
    scrollPattern_->HandleDragStart(info);

    /**
     * @tc.steps: step3. HandleDragUpdate, drag down
     * @tc.expected: Scroll down
     */
    info.SetMainDelta(1000.f);
    arcScrollBar->HandleDragUpdate(info);
    FlushUITasks(stackNode_);
    EXPECT_GT(arcScrollBar->trickSweepAngle_, 10.0);
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test ArcScrollBar in RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, Layout001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 1), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    float controlDistance = pattern_->GetControlDistance();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(controlDistance, CONTENT_MAIN_SIZE - SCROLL_HEIGHT);
    EXPECT_EQ(scrollableDistance, 0);

    auto scrollBar = pattern_->GetScrollBar();
    EXPECT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    EXPECT_NE(arcScrollBar, nullptr);
    EXPECT_EQ(arcScrollBar->trickStartAngle_, -150.0);
}

/**
 * @tc.name: BarStatus001
 * @tc.desc: Test ArcScrollBar barStatus
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, BarStatus001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::AUTO);
    CreateDone();
    float controlDistance = pattern_->GetControlDistance();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(controlDistance, CONTENT_MAIN_SIZE - SCROLL_HEIGHT);
    EXPECT_EQ(scrollableDistance, 0);

    EXPECT_NE(pattern_->scrollBar_, nullptr);
    pattern_->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(pattern_->scrollBar_, nullptr);
}
} // namespace OHOS::Ace::NG
