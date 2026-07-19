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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_scroll_controller.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorFreeScrollTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
};

void RichEditorFreeScrollTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(
        AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorFreeScrollTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

/**
 * @tc.name: HandleFreeScroll001
 * @tc.desc: Test HandleFreeScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleFreeScroll001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(richEditorTheme));

    // needUpdateOffset=true, barDisplayMode_=ON, IsAttachedModifier true → UpdateScrollBarOffset
    pattern->barDisplayMode_ = DisplayMode::ON;
    controller->isScrollBarModifierPropertyAttached_ = true;
    pattern->HandleFreeScroll(true);
    ASSERT_TRUE(controller->IsFreeScrollEnabled());
    ASSERT_NE(controller->scrollBar_, nullptr);
    ASSERT_EQ(controller->scrollBar_->GetDisplayMode(), DisplayMode::ON);
    ASSERT_NE(pattern->hostOverlayMod_, nullptr);

    // needUpdateOffset=true, barDisplayMode_ nullopt → AUTO, IsAttachedModifier false → RemoveOverlayModifier
    auto oldCtrl = controller->freeScrollController_;
    controller->isScrollBarModifierPropertyAttached_ = false;
    pattern->overlayMod_ = nullptr;
    pattern->barDisplayMode_.reset();
    pattern->HandleFreeScroll(true);
    ASSERT_NE(controller->freeScrollController_, oldCtrl);
    ASSERT_EQ(controller->scrollBar_->GetDisplayMode(), DisplayMode::AUTO);
    ASSERT_EQ(pattern->hostOverlayMod_, nullptr);

    // needUpdateOffset=false → no recreate, early return
    oldCtrl = controller->freeScrollController_;
    pattern->HandleFreeScroll(false);
    ASSERT_EQ(controller->freeScrollController_, oldCtrl);
}

/**
 * @tc.name: InitFreeScrollController001
 * @tc.desc: Test InitFreeScrollController
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, InitFreeScrollController001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);

    // Branch: freeScrollController_ null → create new controller
    ASSERT_FALSE(controller->IsFreeScrollEnabled());
    controller->InitFreeScrollController();
    ASSERT_TRUE(controller->IsFreeScrollEnabled());

    // Branch: freeScrollController_ exists + forceRecreate=false → early return
    auto oldFreeCtrl = controller->freeScrollController_;
    controller->InitFreeScrollController(false);
    ASSERT_EQ(controller->freeScrollController_, oldFreeCtrl);

    // Branch: freeScrollController_ exists + forceRecreate=true → reset then recreate
    controller->InitFreeScrollController(true);
    ASSERT_NE(controller->freeScrollController_, oldFreeCtrl);
}

/**
 * @tc.name: SetScrollBar001
 * @tc.desc: Test SetScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, SetScrollBar001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);

    // Branch: displayMode==OFF + scrollBar_ null → isScrollBarModifierPropertyAttached_ reset
    controller->SetScrollBar(DisplayMode::OFF);
    ASSERT_EQ(controller->scrollBar_, nullptr);
    ASSERT_FALSE(controller->isScrollBarModifierPropertyAttached_);

    // Branch: displayMode!=OFF + scrollBar_ null + oldMode!=displayMode → create and set mode
    controller->SetScrollBar(DisplayMode::AUTO);
    ASSERT_NE(controller->scrollBar_, nullptr);
    ASSERT_EQ(controller->scrollBar_->GetDisplayMode(), DisplayMode::AUTO);

    // Branch: displayMode!=OFF + scrollBar_ exists + oldMode==displayMode → skip inner block
    controller->SetScrollBar(DisplayMode::AUTO);
    ASSERT_EQ(controller->scrollBar_->GetDisplayMode(), DisplayMode::AUTO);

    // Branch: isSingleLineMode_ true → vertical scrollable disabled
    pattern->isSingleLineMode_ = true;
    controller->SetScrollBar(DisplayMode::ON);
    ASSERT_FALSE(controller->scrollBar_->IsVerticalScrollable());
    pattern->isSingleLineMode_ = false;

    // Branch: displayMode==OFF + scrollBar_ exists → reset scrollBar_
    controller->SetScrollBar(DisplayMode::OFF);
    ASSERT_FALSE(controller->scrollBar_);

    // Branch: isRTL → PositionMode LEFT; isLTR → PositionMode RIGHT
    controller->SetScrollBar(DisplayMode::AUTO);
    auto layoutProperty = pattern->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    controller->SetScrollBar(DisplayMode::ON);
    ASSERT_NE(controller->scrollBar_->GetVerticalBar(), nullptr);
    ASSERT_EQ(controller->scrollBar_->GetVerticalBar()->GetPositionMode(), PositionMode::LEFT);
    layoutProperty->layoutDirection_ = TextDirection::LTR;
    controller->SetScrollBar(DisplayMode::AUTO);
    ASSERT_EQ(controller->scrollBar_->GetVerticalBar()->GetPositionMode(), PositionMode::RIGHT);
}

/**
 * @tc.name: MoveTextRectWithAxis001
 * @tc.desc: Test MoveTextRectWithAxis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, MoveTextRectWithAxis001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::ON);

    // Branch: isSingleLineMode_ + Axis::VERTICAL → IsScrollDirectionValid false → return 0.0f
    pattern->isSingleLineMode_ = true;
    ASSERT_EQ(controller->MoveTextRectWithAxis(10.0f, Axis::VERTICAL), 0.0f);

    // Branch: isSingleLineMode_ + Axis::HORIZONTAL → valid direction, MoveTextRectHorizontal
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(-5.0f, 0.0f, 120.0f, 50.0f);
    auto hOffset = controller->MoveTextRectWithAxis(5.0f, Axis::HORIZONTAL);
    ASSERT_EQ(hOffset, 5.0f);
    ASSERT_EQ(controller->textRect_.GetX(), 0.0f);

    // Branch: !isSingleLineMode_ + Axis::VERTICAL → valid direction, MoveTextRectVertical
    pattern->isSingleLineMode_ = false;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, -3.0f, 100.0f, 80.0f);
    auto vOffset = controller->MoveTextRectWithAxis(3.0f, Axis::VERTICAL);
    ASSERT_EQ(vOffset, 3.0f);
    ASSERT_EQ(controller->textRect_.GetY(), 0.0f);
}

/**
 * @tc.name: HandleScrollCallback001
 * @tc.desc: Test HandleScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleScrollCallback001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();

    // Branch: HandleScrollCallback - invalid direction (isVertical + isSingleLineMode) → early return
    pattern->isSingleLineMode_ = true;
    controller->scrollingAxis_ = Axis::VERTICAL;
    controller->HandleScrollCallback(10.0f, SCROLL_FROM_START, true);
    ASSERT_EQ(controller->scrollingAxis_, Axis::VERTICAL);

    // Branch: HandleScrollCallback - valid direction + source=SCROLL_FROM_START → scrollingAxis_ set
    pattern->isSingleLineMode_ = false;
    controller->HandleScrollCallback(10.0f, SCROLL_FROM_START, false);
    ASSERT_EQ(controller->scrollingAxis_, Axis::HORIZONTAL);

    // Branch: HandleScrollCallback - valid direction + source!=SCROLL_FROM_START + !IsReachAvoidBoundary
    controller->HandleScrollCallback(0.0f, SCROLL_FROM_NONE, true);
    ASSERT_EQ(controller->scrollingAxis_, Axis::HORIZONTAL);

    // Branch: HandleScrollCallback - valid direction + source!=SCROLL_FROM_START + IsReachAvoidBoundary → stop
    pattern->contentRect_ = RectF(0.0f, 0.0f, 300.0f, 300.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 300.0f, 300.0f);
    controller->HandleScrollCallback(5.0f, SCROLL_FROM_NONE, true);
    ASSERT_EQ(controller->scrollingAxis_, Axis::HORIZONTAL);

    // Branch: HandleScrollCallback - valid direction + source=SCROLL_FROM_JUMP + offset!=0 + !IsReachAvoidBoundary
    controller->SetScrollBar(DisplayMode::AUTO);
    controller->scrollBar_->SetVerticalScrollable(true);
    MockContainer::SetUp(MockPipelineContext::pipeline_);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::pipeline_->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, -3.0f, 100.0f, 80.0f);
    ASSERT_NE(controller->scrollBar_, nullptr);
    auto vBar = controller->scrollBar_->GetVerticalBar();
    ASSERT_NE(vBar, nullptr);
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->HandleScrollCallback(3.0f, SCROLL_FROM_JUMP, true);
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::DISAPPEAR);
    ASSERT_EQ(controller->textRect_.GetY(), 0.0f);
}

/**
 * @tc.name: UpdateScrollBarOffsetWithAxis001
 * @tc.desc: Test UpdateScrollBarOffsetWithAxis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, UpdateScrollBarOffsetWithAxis001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::ON);

    // Branch: isSingleLineMode_ + Axis::VERTICAL → IsScrollDirectionValid false → early return
    pattern->isSingleLineMode_ = true;
    controller->UpdateScrollBarOffsetWithAxis(Axis::VERTICAL);
    ASSERT_FALSE(controller->scrollBar_->IsVerticalScrollable());
    pattern->isSingleLineMode_ = false;

    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, -5.0f, 120.0f, 60.0f);
    pattern->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);

    // Branch: Axis::NONE → early return
    controller->UpdateScrollBarOffsetWithAxis(Axis::NONE);
    ASSERT_FALSE(controller->scrollBar_->IsVerticalScrollable());

    // Branch: Axis::VERTICAL + hasText=false → SetVerticalScrollable(false)
    controller->UpdateScrollBarOffsetWithAxis(Axis::VERTICAL, false);
    ASSERT_FALSE(controller->scrollBar_->IsVerticalScrollable());

    // Branch: Axis::HORIZONTAL + hasText=false → SetHorizontalScrollable(false)
    controller->UpdateScrollBarOffsetWithAxis(Axis::HORIZONTAL, false);
    ASSERT_FALSE(controller->scrollBar_->IsHorizontalScrollable());

    AddSpan(TEST_STR);

    // Branch: Axis::VERTICAL + hasText=true + needAnimation=false → SetVerticalScrollable(true)
    controller->UpdateScrollBarOffsetWithAxis(Axis::VERTICAL, false);
    ASSERT_TRUE(controller->scrollBar_->IsVerticalScrollable());

    // Branch: Axis::HORIZONTAL + hasText=true + needAnimation=true → SetHorizontalScrollable(true)
    controller->UpdateScrollBarOffsetWithAxis(Axis::HORIZONTAL, true);
    ASSERT_TRUE(controller->scrollBar_->IsHorizontalScrollable());
}

/**
 * @tc.name: ScheduleDisappearDelayTask001
 * @tc.desc: Test ScheduleDisappearDelayTask
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, ScheduleDisappearDelayTask001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::AUTO);
    controller->scrollBar_->SetVerticalScrollable(true);
    controller->scrollBar_->SetHorizontalScrollable(true);
    MockContainer::SetUp(MockPipelineContext::pipeline_);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::pipeline_->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
    auto vBar = controller->scrollBar_->GetVerticalBar();
    auto hBar = controller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(vBar, nullptr);
    ASSERT_NE(hBar, nullptr);

    // scrollingAxis_ == NONE → schedule both vertical and horizontal disappear tasks
    controller->scrollingAxis_ = Axis::NONE;
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    hBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->ScheduleDisappearDelayTask();
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::DISAPPEAR);
    ASSERT_EQ(hBar->GetOpacityAnimationType(), OpacityAnimationType::DISAPPEAR);

    // scrollingAxis_ == VERTICAL → only schedule vertical disappear task
    controller->scrollingAxis_ = Axis::VERTICAL;
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    hBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->ScheduleDisappearDelayTask();
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::DISAPPEAR);
    ASSERT_EQ(hBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);

    // single-line mode + Axis::VERTICAL → direction invalid → no task scheduled
    pattern->isSingleLineMode_ = true;
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->ScheduleDisappearDelayTask(Axis::VERTICAL);
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);

    // single-line mode + Axis::HORIZONTAL → direction valid → schedule horizontal task
    hBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->ScheduleDisappearDelayTask(Axis::HORIZONTAL);
    ASSERT_EQ(hBar->GetOpacityAnimationType(), OpacityAnimationType::DISAPPEAR);
    pattern->isSingleLineMode_ = false;
}

/**
 * @tc.name: PlayScrollBarAppearAnimation001
 * @tc.desc: Test PlayScrollBarAppearAnimation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, PlayScrollBarAppearAnimation001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::AUTO);
    controller->scrollBar_->SetVerticalScrollable(true);
    controller->scrollBar_->SetHorizontalScrollable(true);
    auto vBar = controller->scrollBar_->GetVerticalBar();
    auto hBar = controller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(vBar, nullptr);
    ASSERT_NE(hBar, nullptr);

    // axis == Axis::VERTICAL → play vertical bar appear animation
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->PlayScrollBarAppearAnimation(Axis::VERTICAL);
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);

    // axis != Axis::VERTICAL → play horizontal bar appear animation
    hBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->PlayScrollBarAppearAnimation(Axis::HORIZONTAL);
    ASSERT_EQ(hBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
}

/**
 * @tc.name: UpdateScrollBarColor001
 * @tc.desc: Test UpdateScrollBarColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, UpdateScrollBarColor001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto scrollbarTheme = AceType::MakeRefPtr<ScrollBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollbarTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(scrollbarTheme));
    auto themeFg = scrollbarTheme->GetForegroundColor();
    auto themeBg = scrollbarTheme->GetBackgroundColor();
    controller->SetScrollBar(DisplayMode::AUTO);
    auto vBar = controller->scrollBar_->GetVerticalBar();
    auto hBar = controller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(vBar, nullptr);
    ASSERT_NE(hBar, nullptr);

    // color has value, foreground uses given color and background uses theme background color
    auto customColor = Color::RED;
    controller->UpdateScrollBarColor(customColor);
    ASSERT_EQ(vBar->GetForegroundColor(), customColor);
    ASSERT_EQ(hBar->GetForegroundColor(), customColor);
    ASSERT_EQ(vBar->GetBackgroundColor(), themeBg);
    ASSERT_EQ(hBar->GetBackgroundColor(), themeBg);

    // color is nullopt, foreground falls back to theme foreground color
    controller->UpdateScrollBarColor(std::nullopt);
    ASSERT_EQ(vBar->GetForegroundColor(), themeFg);
    ASSERT_EQ(hBar->GetForegroundColor(), themeFg);
}

/**
 * @tc.name: IsMouseOverScrollBar001
 * @tc.desc: Test IsMouseOverScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, IsMouseOverScrollBar001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::ON);
    controller->scrollBar_->SetVerticalScrollable(true);
    controller->scrollBar_->SetHorizontalScrollable(true);
    auto vBar = controller->scrollBar_->GetVerticalBar();
    auto hBar = controller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(vBar, nullptr);
    ASSERT_NE(hBar, nullptr);
    pattern->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    vBar->barRect_ = Rect(0.0, 0.0, 100.0, 100.0);
    hBar->barRect_ = Rect(0.0, 0.0, 100.0, 100.0);
    MouseInfo info;
    // verticalBar is pressed
    vBar->SetPressed(true);
    info.SetLocalLocation(Offset(0.0, 0.0));
    ASSERT_TRUE(controller->IsMouseOverScrollBar(info));
    // verticalBar is hovered
    vBar->SetPressed(false);
    vBar->SetHover(true);
    ASSERT_TRUE(controller->IsMouseOverScrollBar(info));
    // point is in vertical scroll bar rect
    vBar->SetHover(false);
    info.SetLocalLocation(Offset(95.0, 50.0));
    ASSERT_TRUE(controller->IsMouseOverScrollBar(info));
    // horizontalBar is pressed
    info.SetLocalLocation(Offset(0.0, 0.0));
    hBar->SetPressed(true);
    ASSERT_TRUE(controller->IsMouseOverScrollBar(info));
    // horizontalBar is hovered
    hBar->SetPressed(false);
    hBar->SetHover(true);
    ASSERT_TRUE(controller->IsMouseOverScrollBar(info));
    // point is in horizontal scroll bar rect
    hBar->SetHover(false);
    info.SetLocalLocation(Offset(50.0, 95.0));
    ASSERT_TRUE(controller->IsMouseOverScrollBar(info));
    // no bar is pressed, hovered, or contains the point
    info.SetLocalLocation(Offset(0.0, 0.0));
    ASSERT_FALSE(controller->IsMouseOverScrollBar(info));
}

/**
 * @tc.name: IsPointInScrollBarRect001
 * @tc.desc: Test IsPointInScrollBarRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, IsPointInScrollBarRect001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->SetScrollBar(DisplayMode::ON);
    controller->scrollBar_->SetVerticalScrollable(true);
    controller->scrollBar_->SetHorizontalScrollable(true);
    auto vBar = controller->scrollBar_->GetVerticalBar();
    auto hBar = controller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(vBar, nullptr);
    ASSERT_NE(hBar, nullptr);
    pattern->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    vBar->barRect_ = Rect(0.0, 0.0, 100.0, 100.0);
    hBar->barRect_ = Rect(0.0, 0.0, 100.0, 100.0);

    // shapeMode is ROUND instead of RECT → return false
    vBar->SetShapeMode(ShapeMode::ROUND);
    ASSERT_FALSE(controller->IsPointInScrollBarRect(Point(95, 50), true));
    vBar->SetShapeMode(ShapeMode::RECT);

    // vertical bar not scrollable → return false
    controller->scrollBar_->SetVerticalScrollable(false);
    ASSERT_FALSE(controller->IsPointInScrollBarRect(Point(95, 50), true));
    controller->scrollBar_->SetVerticalScrollable(true);

    // isVertical true, point in region → return true
    ASSERT_TRUE(controller->IsPointInScrollBarRect(Point(95, 50), true));

    // isVertical true, point not in region → return false
    ASSERT_FALSE(controller->IsPointInScrollBarRect(Point(0, 0), true));

    // isVertical false, point in region → return true
    ASSERT_TRUE(controller->IsPointInScrollBarRect(Point(50, 95), false));

    // isVertical false, point not in region → return false
    ASSERT_FALSE(controller->IsPointInScrollBarRect(Point(0, 0), false));
}

/**
 * @tc.name: CheckScrollEnabled001
 * @tc.desc: Test CheckScrollEnabled
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, CheckScrollEnabled001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::ON);
    ASSERT_NE(controller->freeScrollController_, nullptr);
    ASSERT_NE(controller->scrollBar_->scrollableEvent_, nullptr);

    // no text content and no overflow → enabled false
    pattern->isSingleLineMode_ = false;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    controller->CheckScrollEnabled();
    ASSERT_FALSE(controller->freeScrollController_->enabled_);
    ASSERT_FALSE(controller->scrollBar_->scrollableEvent_->GetEnabled());

    // text present and vertical overflow → enabled true
    AddSpan(TEST_STR);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 100.0f, 200.0f);
    controller->CheckScrollEnabled();
    ASSERT_TRUE(controller->freeScrollController_->enabled_);
    ASSERT_TRUE(controller->scrollBar_->scrollableEvent_->GetEnabled());

    // single-line mode suppresses vertical scroll, horizontal overflow → enabled true
    pattern->isSingleLineMode_ = true;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 50.0f, 100.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 200.0f, 100.0f);
    controller->CheckScrollEnabled();
    ASSERT_TRUE(controller->freeScrollController_->enabled_);
    ASSERT_TRUE(controller->scrollBar_->scrollableEvent_->GetEnabled());

    // text present but no overflow → enabled false
    pattern->isSingleLineMode_ = false;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 300.0f, 300.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 300.0f, 300.0f);
    controller->CheckScrollEnabled();
    ASSERT_FALSE(controller->freeScrollController_->enabled_);
    ASSERT_FALSE(controller->scrollBar_->scrollableEvent_->GetEnabled());
}

/**
 * @tc.name: UpdateScrollBarOffset001
 * @tc.desc: test UpdateScrollBarOffset and UpdateScrollBarOffsetWithAxis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, UpdateScrollBarOffset001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->InitFreeScrollController();
    scrollController->SetScrollBar(DisplayMode::ON);
    ASSERT_NE(scrollController->scrollBar_, nullptr);
    auto verticalBar = scrollController->scrollBar_->GetVerticalBar();
    auto horizontalBar = scrollController->scrollBar_->GetHorizontalBar();
    ASSERT_NE(verticalBar, nullptr);
    ASSERT_NE(horizontalBar, nullptr);
    verticalBar->SetScrollable(true);
    horizontalBar->SetScrollable(true);
    verticalBar->SetDisplayMode(DisplayMode::AUTO);
    horizontalBar->SetDisplayMode(DisplayMode::AUTO);
    scrollController->frameRect_ = RectF(0.0f, 0.0f, 200.0f, 200.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->textRect_ = RectF(0.0f, 0.0f, 150.0f, 150.0f);
    // scrollingAxis_=NONE, both VERTICAL and HORIZONTAL calls have needAnimation=true, no text so hasText=false
    scrollController->UpdateScrollBarOffset();
    EXPECT_FALSE(verticalBar->IsScrollable());
    EXPECT_FALSE(horizontalBar->IsScrollable());
    EXPECT_EQ(verticalBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    EXPECT_EQ(horizontalBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    // add text, set scrollingAxis_=VERTICAL so HORIZONTAL call has needAnimation=false
    AddSpan(INIT_VALUE_1);
    verticalBar->SetScrollable(true);
    horizontalBar->SetScrollable(true);
    verticalBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    horizontalBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    scrollController->scrollingAxis_ = Axis::VERTICAL;
    scrollController->UpdateScrollBarOffset();
    EXPECT_TRUE(verticalBar->IsScrollable());
    EXPECT_TRUE(horizontalBar->IsScrollable());
    EXPECT_EQ(verticalBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    EXPECT_EQ(horizontalBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
}

/**
 * @tc.name: SetMinHeight001
 * @tc.desc: Test SetMinHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, SetMinHeight001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->SetScrollBar(DisplayMode::ON);
    ASSERT_NE(controller->scrollBar_, nullptr);

    Dimension testHeight(50.0, DimensionUnit::VP);
    // horizontalBar is nullptr, verticalBar exists, SetMinHeight sets vertical bar min height
    auto savedHorizontalBar = controller->scrollBar_->horizontalBar_;
    controller->scrollBar_->horizontalBar_ = nullptr;
    controller->SetMinHeight(testHeight);
    auto verticalBar = controller->scrollBar_->GetVerticalBar();
    ASSERT_NE(verticalBar, nullptr);
    ASSERT_EQ(verticalBar->GetMinHeight().Value(), testHeight.Value());

    // verticalBar is nullptr, horizontalBar exists, SetMinHeight sets horizontal bar min height
    controller->scrollBar_->horizontalBar_ = savedHorizontalBar;
    controller->scrollBar_->verticalBar_ = nullptr;
    controller->SetMinHeight(testHeight);
    auto horizontalBar = controller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(horizontalBar, nullptr);
    ASSERT_EQ(horizontalBar->GetMinHeight().Value(), testHeight.Value());
}

/**
 * @tc.name: AttachModifier001
 * @tc.desc: Test AttachModifier
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, AttachModifier001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->SetScrollBar(DisplayMode::ON);
    ASSERT_NE(controller->scrollBar_, nullptr);
    auto verticalModifier = controller->scrollBar_->GetVerticalModifier();
    auto horizontalModifier = controller->scrollBar_->GetHorizontalModifier();
    ASSERT_NE(verticalModifier, nullptr);
    ASSERT_NE(horizontalModifier, nullptr);
    auto modifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
    ASSERT_NE(modifier, nullptr);
    auto expectedCount = verticalModifier->GetAttachedProperties().size() +
        horizontalModifier->GetAttachedProperties().size();
    auto propsBefore = modifier->GetAttachedProperties().size();

    // isScrollBarModifierPropertyAttached_ is false → attach all properties and set flag to true
    controller->AttachModifier(modifier);
    ASSERT_TRUE(controller->isScrollBarModifierPropertyAttached_);
    ASSERT_EQ(modifier->GetAttachedProperties().size(), propsBefore + expectedCount);

    // isScrollBarModifierPropertyAttached_ already true → early return, no additional properties attached
    controller->AttachModifier(modifier);
    ASSERT_EQ(modifier->GetAttachedProperties().size(), propsBefore + expectedCount);
}

/**
 * @tc.name: HandleEndScrollCallback001
 * @tc.desc: Test HandleEndScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleEndScrollCallback001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::AUTO);
    controller->scrollBar_->SetVerticalScrollable(true);
    controller->scrollBar_->SetHorizontalScrollable(true);
    MockContainer::SetUp(MockPipelineContext::pipeline_);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::pipeline_->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
    auto vBar = controller->scrollBar_->GetVerticalBar();
    auto hBar = controller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(vBar, nullptr);
    ASSERT_NE(hBar, nullptr);

    // isVertical true + isSingleLineMode true → direction invalid → early return, scrollingAxis_ reset
    pattern->isSingleLineMode_ = true;
    controller->scrollingAxis_ = Axis::VERTICAL;
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->HandleEndScrollCallback(true);
    ASSERT_EQ(controller->scrollingAxis_, Axis::NONE);
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);

    // isVertical true + isSingleLineMode false → valid → schedule vertical disappear task
    pattern->isSingleLineMode_ = false;
    controller->scrollingAxis_ = Axis::VERTICAL;
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->HandleEndScrollCallback(true);
    ASSERT_EQ(controller->scrollingAxis_, Axis::NONE);
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::DISAPPEAR);

    // isVertical false → valid → schedule horizontal disappear task
    controller->scrollingAxis_ = Axis::HORIZONTAL;
    hBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->HandleEndScrollCallback(false);
    ASSERT_EQ(controller->scrollingAxis_, Axis::NONE);
    ASSERT_EQ(hBar->GetOpacityAnimationType(), OpacityAnimationType::DISAPPEAR);
}

/**
 * @tc.name: MoveHandleOnScrollWithAxis001
 * @tc.desc: Test MoveHandleOnScrollWithAxis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, MoveHandleOnScrollWithAxis001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    auto& textSelector = controller->textSelector_;
    OffsetF zero{ 0.0f, 0.0f };
    textSelector.firstHandle.SetOffset(zero);
    textSelector.secondHandle.SetOffset(zero);
    // offset near zero → early return, handles unchanged
    controller->MoveHandleOnScrollWithAxis(0.0f, Axis::VERTICAL);
    ASSERT_EQ(textSelector.firstHandle.GetOffset(), zero);
    // SelectOverlayIsOn false + non-zero offset → early return
    controller->MoveHandleOnScrollWithAxis(1.0f, Axis::VERTICAL);
    ASSERT_EQ(textSelector.secondHandle.GetOffset(), zero);
    // set up selection overlay to make SelectOverlayIsOn true
    AddSpan(INIT_VALUE_1);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    pattern->textSelector_.Update(0, 2);
    pattern->CalculateHandleOffsetAndShowOverlay();
    pattern->ShowSelectOverlay(
        pattern->textSelector_.firstHandle, pattern->textSelector_.secondHandle, false);
    ASSERT_TRUE(pattern->SelectOverlayIsOn());
    // non-zero offset + VERTICAL → move both handles on Y axis
    textSelector.firstHandle.SetOffset(zero);
    textSelector.secondHandle.SetOffset(zero);
    controller->MoveHandleOnScrollWithAxis(1.0f, Axis::VERTICAL);
    ASSERT_EQ(textSelector.firstHandle.GetOffset(), OffsetF(0.0f, 1.0f));
    ASSERT_EQ(textSelector.secondHandle.GetOffset(), OffsetF(0.0f, 1.0f));
    // non-zero offset + HORIZONTAL → move both handles on X axis
    textSelector.firstHandle.SetOffset(zero);
    textSelector.secondHandle.SetOffset(zero);
    controller->MoveHandleOnScrollWithAxis(1.0f, Axis::HORIZONTAL);
    ASSERT_EQ(textSelector.firstHandle.GetOffset(), OffsetF(1.0f, 0.0f));
    ASSERT_EQ(textSelector.secondHandle.GetOffset(), OffsetF(1.0f, 0.0f));
    // overload2: isFirst true → only firstHandle moves
    textSelector.firstHandle.SetOffset(zero);
    textSelector.secondHandle.SetOffset(zero);
    controller->MoveHandleOnScrollWithAxis(1.0f, true, Axis::VERTICAL);
    ASSERT_EQ(textSelector.firstHandle.GetOffset(), OffsetF(0.0f, 1.0f));
    ASSERT_EQ(textSelector.secondHandle.GetOffset(), zero);
    // overload2: isFirst false → only secondHandle moves
    textSelector.firstHandle.SetOffset(zero);
    textSelector.secondHandle.SetOffset(zero);
    controller->MoveHandleOnScrollWithAxis(1.0f, false, Axis::VERTICAL);
    ASSERT_EQ(textSelector.firstHandle.GetOffset(), zero);
    ASSERT_EQ(textSelector.secondHandle.GetOffset(), OffsetF(0.0f, 1.0f));
}

/**
 * @tc.name: MoveCaretToContentRect001
 * @tc.desc: Test MoveCaretToContentRect and MoveCaretToContentRectWithAxis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, MoveCaretToContentRect001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::AUTO);
    controller->scrollBar_->SetVerticalScrollable(true);
    controller->scrollBar_->SetHorizontalScrollable(true);
    auto vBar = controller->scrollBar_->GetVerticalBar();
    auto hBar = controller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(vBar, nullptr);
    ASSERT_NE(hBar, nullptr);

    // isShowPlaceholder_ is true, MoveCaretToContentRect returns early
    pattern->isShowPlaceholder_ = true;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 100.0f, 200.0f);
    controller->MoveCaretToContentRect(RectF(0.0f, 150.0f, 2.0f, 20.0f));
    ASSERT_EQ(controller->textRect_.GetY(), 0.0f);

    // no overflow on either axis, NeedScroll false, both axis calls return early
    pattern->isShowPlaceholder_ = false;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    controller->MoveCaretToContentRect(RectF(0.0f, 50.0f, 2.0f, 20.0f));
    ASSERT_EQ(controller->textRect_.GetY(), 0.0f);
    ASSERT_EQ(controller->textRect_.GetX(), 0.0f);

    // vertical overflow and caret below content bottom, NeedScroll true, vertical scroll moves textRect up
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 100.0f, 200.0f);
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->MoveCaretToContentRect(RectF(0.0f, 80.0f, 2.0f, 20.0f));
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    ASSERT_EQ(controller->textRect_.GetY(), -66.0f);

    // horizontal overflow and caret to the right of content, NeedScroll true, horizontal scroll moves textRect left
    pattern->contentRect_ = RectF(0.0f, 0.0f, 50.0f, 100.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 200.0f, 100.0f);
    hBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->MoveCaretToContentRect(RectF(60.0f, 0.0f, 2.0f, 20.0f));
    ASSERT_EQ(hBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    ASSERT_EQ(controller->textRect_.GetX(), -12.0f);

    // IsFreeScrollEnabled is true, OffsetF overload delegates to MoveCaretToContentRect(RectF)
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 100.0f, 200.0f);
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->scrollBar_->SetVerticalScrollable(true);
    controller->MoveCaretToContentRect(OffsetF(0.0f, 80.0f), 20.0f);
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    ASSERT_EQ(controller->textRect_.GetY(), -66.0f);
}

/**
 * @tc.name: HandleAutoScrollNearBoundary001
 * @tc.desc: Test HandleAutoScrollNearBoundary covering all branches: inside safe area, both hot areas,
 *           only horizontal hot area, and only vertical hot area
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleAutoScrollNearBoundary001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    // contentRect_ = (0,0,100,100), edgeThreshold=15px, safeAreaRect=(15,15,70,70)
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->richTextRect_ = RectF(-10.0f, -10.0f, 200.0f, 200.0f);
    pattern->isSingleLineMode_ = false;
    controller->prevAutoScrollOffset_ = OffsetF(0.0f, 0.0f);
    MockContainer::SetUp(MockPipelineContext::pipeline_);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::pipeline_->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());

    // point (50,50) is inside safeAreaRect, StopAutoScroll is called
    controller->isAutoScrollRunning_ = true;
    AutoScrollParam param;
    param.autoScrollEvent = AutoScrollEvent::NONE;
    controller->HandleAutoScrollNearBoundary(param, OffsetF(50.0f, 50.0f));
    ASSERT_FALSE(controller->isAutoScrollRunning_);

    // both hot areas active, HandleCornerScrolling dispatches to HandleInVerticalHotArea
    param.isFirstRun_ = true;
    controller->HandleAutoScrollNearBoundary(param, OffsetF(5.0f, 5.0f));
    ASSERT_EQ(controller->currentScrollParam_.axis, Axis::VERTICAL);
    ASSERT_EQ(controller->currentScrollParam_.offset, 10.0f);

    // only horizontal hot area active, HandleInHorizontalHotArea sets axis and offset
    controller->HandleAutoScrollNearBoundary(param, OffsetF(5.0f, 50.0f));
    ASSERT_EQ(controller->currentScrollParam_.axis, Axis::HORIZONTAL);
    ASSERT_EQ(controller->currentScrollParam_.offset, 10.0f);

    // only vertical hot area active, HandleInVerticalHotArea sets axis and offset
    controller->HandleAutoScrollNearBoundary(param, OffsetF(50.0f, 5.0f));
    ASSERT_EQ(controller->currentScrollParam_.axis, Axis::VERTICAL);
    ASSERT_EQ(controller->currentScrollParam_.offset, 10.0f);
}

/**
 * @tc.name: HandleInHorizontalHotArea001
 * @tc.desc: Test HandleInHorizontalHotArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleInHorizontalHotArea001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    // safeAreaRect Left()=15, Right()=85; frameRect_ width=100
    controller->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    RectF safeAreaRect(15.0f, 15.0f, 70.0f, 70.0f);
    AutoScrollParam param;

    // point to the right of safeAreaRect and not dragging
    param.autoScrollEvent = AutoScrollEvent::NONE;
    controller->HandleInHorizontalHotArea(param, safeAreaRect, PointF(95.0f, 50.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_EQ(param.offset, -10.0f);

    // point to the right of safeAreaRect and dragging
    param.autoScrollEvent = AutoScrollEvent::DRAG;
    controller->HandleInHorizontalHotArea(param, safeAreaRect, PointF(95.0f, 50.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_TRUE(param.offset < 0.0f);

    // point to the left of safeAreaRect and not dragging
    param.autoScrollEvent = AutoScrollEvent::NONE;
    controller->HandleInHorizontalHotArea(param, safeAreaRect, PointF(5.0f, 50.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_EQ(param.offset, 10.0f);

    // point to the left of safeAreaRect and dragging
    param.autoScrollEvent = AutoScrollEvent::DRAG;
    controller->HandleInHorizontalHotArea(param, safeAreaRect, PointF(5.0f, 50.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_TRUE(param.offset > 0.0f);

    // point inside safeAreaRect horizontally
    param.offset = 0.0f;
    controller->HandleInHorizontalHotArea(param, safeAreaRect, PointF(50.0f, 50.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_EQ(param.offset, 0.0f);
}

/**
 * @tc.name: HandleInVerticalHotArea001
 * @tc.desc: Test HandleInVerticalHotArea
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleInVerticalHotArea001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    // safeAreaRect Top()=15, Bottom()=85; frameRect_ height=100
    controller->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    RectF safeAreaRect(15.0f, 15.0f, 70.0f, 70.0f);
    AutoScrollParam param;

    // point below safeAreaRect and not dragging
    param.autoScrollEvent = AutoScrollEvent::NONE;
    controller->HandleInVerticalHotArea(param, safeAreaRect, PointF(50.0f, 95.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_EQ(param.offset, -10.0f);

    // point below safeAreaRect and dragging
    param.autoScrollEvent = AutoScrollEvent::DRAG;
    controller->HandleInVerticalHotArea(param, safeAreaRect, PointF(50.0f, 95.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_TRUE(param.offset < 0.0f);

    // point above safeAreaRect and not dragging
    param.autoScrollEvent = AutoScrollEvent::NONE;
    controller->HandleInVerticalHotArea(param, safeAreaRect, PointF(50.0f, 5.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_EQ(param.offset, 10.0f);

    // point above safeAreaRect and dragging
    param.autoScrollEvent = AutoScrollEvent::DRAG;
    controller->HandleInVerticalHotArea(param, safeAreaRect, PointF(50.0f, 5.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_TRUE(param.offset > 0.0f);

    // point inside safeAreaRect vertically
    param.offset = 0.0f;
    controller->HandleInVerticalHotArea(param, safeAreaRect, PointF(50.0f, 50.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_EQ(param.offset, 0.0f);
}

/**
 * @tc.name: HandleCornerScrolling001
 * @tc.desc: Test HandleCornerScrolling for top-right and top-left corners
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleCornerScrolling001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    RectF safeAreaRect(15.0f, 15.0f, 70.0f, 70.0f);
    AutoScrollParam param;
    param.autoScrollEvent = AutoScrollEvent::NONE;

    // top-right corner, angle 315° in HORIZONTAL range, point right of right edge
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(92.0f, 8.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_EQ(param.offset, -7.0f);

    // top-right corner, angle ~283° in VERTICAL range, point above top edge
    param.axis = Axis::NONE;
    param.offset = 0.0f;
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(88.0f, 2.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_EQ(param.offset, 13.0f);

    // top-left corner, angle ~208° in HORIZONTAL range, point left of left edge
    param.axis = Axis::NONE;
    param.offset = 0.0f;
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(2.0f, 8.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_EQ(param.offset, 13.0f);

    // top-left corner, angle ~242° in VERTICAL range, point above top edge
    param.axis = Axis::NONE;
    param.offset = 0.0f;
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(8.0f, 2.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_EQ(param.offset, 13.0f);
}

/**
 * @tc.name: HandleCornerScrolling002
 * @tc.desc: Test HandleCornerScrolling for bottom-left, bottom-right corners and no match
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleCornerScrolling002, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    RectF safeAreaRect(15.0f, 15.0f, 70.0f, 70.0f);
    AutoScrollParam param;
    param.autoScrollEvent = AutoScrollEvent::NONE;

    // bottom-left corner, angle ~118° in VERTICAL range, point below bottom edge
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(8.0f, 98.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_EQ(param.offset, -13.0f);

    // bottom-left corner, angle ~152° in HORIZONTAL range, point left of left edge
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(2.0f, 92.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_EQ(param.offset, 13.0f);

    // bottom-right corner, angle ~28° in HORIZONTAL range, point right of right edge
    param.axis = Axis::NONE;
    param.offset = 0.0f;
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(98.0f, 92.0f));
    ASSERT_EQ(param.axis, Axis::HORIZONTAL);
    ASSERT_EQ(param.offset, -13.0f);

    // bottom-right corner, angle ~66° in VERTICAL range, point below bottom edge
    param.axis = Axis::NONE;
    param.offset = 0.0f;
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(89.0f, 94.0f));
    ASSERT_EQ(param.axis, Axis::VERTICAL);
    ASSERT_EQ(param.offset, -9.0f);

    // point inside safe area, no corner range matches, fall through, axis unchanged
    param.axis = Axis::NONE;
    param.offset = 0.0f;
    controller->HandleCornerScrolling(param, safeAreaRect, PointF(50.0f, 50.0f));
    ASSERT_EQ(param.axis, Axis::NONE);
    ASSERT_EQ(param.offset, 0.0f);
}

/**
 * @tc.name: ProcessAutoScroll001
 * @tc.desc: Test ProcessAutoScroll - showScrollbar, NONE, CARET, DRAG, newOffset==0/!=0
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, ProcessAutoScroll001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::AUTO);
    controller->scrollBar_->SetVerticalScrollable(true);
    auto vBar = controller->scrollBar_->GetVerticalBar();
    ASSERT_NE(vBar, nullptr);
    pattern->isSingleLineMode_ = false;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, -10.0f, 100.0f, 80.0f);
    MockContainer::SetUp(MockPipelineContext::pipeline_);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>(true);
    MockPipelineContext::pipeline_->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(true));

    // showScrollbar=true + CARET + offset!=0 → animation played + ScheduleAutoScroll
    auto& param = controller->currentScrollParam_;
    param.showScrollbar = true;
    param.autoScrollEvent = AutoScrollEvent::CARET;
    param.axis = Axis::VERTICAL;
    param.offset = 3.0f;
    param.isFirstRun_ = true;
    vBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    controller->ProcessAutoScroll();
    ASSERT_EQ(vBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    ASSERT_TRUE(controller->isAutoScrollRunning_);

    // event=NONE → early return, no ScheduleAutoScroll
    controller->StopAutoScroll();
    param.autoScrollEvent = AutoScrollEvent::NONE;
    param.showScrollbar = false;
    controller->ProcessAutoScroll();
    ASSERT_FALSE(controller->isAutoScrollRunning_);

    // CARET + offset=0 → no ScheduleAutoScroll
    param.autoScrollEvent = AutoScrollEvent::CARET;
    param.offset = 0.0f;
    controller->ProcessAutoScroll();
    ASSERT_FALSE(controller->isAutoScrollRunning_);

    // DRAG + offset!=0 → ScheduleAutoScroll
    pattern->richTextRect_ = RectF(0.0f, -10.0f, 100.0f, 80.0f);
    param.autoScrollEvent = AutoScrollEvent::DRAG;
    param.offset = 3.0f;
    param.isFirstRun_ = true;
    controller->ProcessAutoScroll();
    ASSERT_TRUE(controller->isAutoScrollRunning_);
}

/**
 * @tc.name: ProcessAutoScroll002
 * @tc.desc: Test ProcessAutoScroll - HANDLE, MOUSE with empty/non-empty text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, ProcessAutoScroll002, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::ON);
    pattern->isSingleLineMode_ = false;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, -10.0f, 100.0f, 80.0f);
    MockContainer::SetUp(MockPipelineContext::pipeline_);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>(true);
    MockPipelineContext::pipeline_->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(true));

    // HANDLE + offset!=0 → MoveHandle+OnHandleMove called, ScheduleAutoScroll
    auto& param = controller->currentScrollParam_;
    param.autoScrollEvent = AutoScrollEvent::HANDLE;
    param.axis = Axis::VERTICAL;
    param.offset = 3.0f;
    param.isFirstRun_ = true;
    controller->ProcessAutoScroll();
    ASSERT_TRUE(controller->isAutoScrollRunning_);

    // MOUSE + textLength==0 → extend=0, caretPosition clamped to 0
    controller->StopAutoScroll();
    pattern->isSingleLineMode_ = true;
    param.autoScrollEvent = AutoScrollEvent::MOUSE;
    param.offset = 0.0f;
    param.isFirstRun_ = true;
    pattern->textSelector_.Update(0, 5);
    pattern->caretPosition_ = 5;
    controller->ProcessAutoScroll();
    ASSERT_EQ(pattern->GetCaretPosition(), 0);
    ASSERT_EQ(pattern->textSelector_.destinationOffset, 0);

    // MOUSE + textLength!=0 → extend=GetIndex, caretPosition set
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->rangeStart = 0;
    spanItem->position = 4;
    spanItem->content = u"test";
    pattern->spans_.push_back(spanItem);
    pattern->isSingleLineMode_ = false;
    pattern->textSelector_.baseOffset = 3;
    pattern->caretPosition_ = 0;
    controller->ProcessAutoScroll();
    ASSERT_EQ(pattern->GetCaretPosition(), 3);
}

/**
 * @tc.name: UpdateHorizontalScrollState001
 * @tc.desc: Test UpdateHorizontalScrollState
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, UpdateHorizontalScrollState001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);

    // free scroll not enabled → return false
    ASSERT_FALSE(controller->UpdateHorizontalScrollState());

    // free scroll enabled, text width exceeds content width, need scroll → return false
    controller->InitFreeScrollController();
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 120.0f, 50.0f);
    ASSERT_FALSE(controller->UpdateHorizontalScrollState());

    // no horizontal overflow, textRect X not less than contentRect X → return false
    pattern->contentRect_ = RectF(10.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(15.0f, 0.0f, 80.0f, 50.0f);
    ASSERT_FALSE(controller->UpdateHorizontalScrollState());

    // no horizontal overflow, textRect X less than contentRect X → align left and return true
    pattern->contentRect_ = RectF(10.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(5.0f, 0.0f, 80.0f, 50.0f);
    ASSERT_TRUE(controller->UpdateHorizontalScrollState());
    ASSERT_EQ(controller->textRect_.GetX(), 10.0f);
}

} // namespace OHOS::Ace::NG
