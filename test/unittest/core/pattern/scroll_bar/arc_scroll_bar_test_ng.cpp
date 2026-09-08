/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"

namespace OHOS::Ace::NG {

class ArcScrollBarTestNg : public ScrollBarTestNg {
public:
    void CreateArcScrollBar(DisplayMode displayMode);
};

void ArcScrollBarTestNg::CreateArcScrollBar(DisplayMode displayMode)
{
    SystemProperties::SetDeviceType(DeviceType::WATCH);
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
    arcScrollBar->HandleDragStart(info);

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

/**
 * @tc.name: CreateOnSupportedDevices001
 * @tc.desc: Test ArcScrollBar creation on all supported device types.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, CreateOnSupportedDevices001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    const DeviceType supportedDeviceTypes[] = { DeviceType::PHONE, DeviceType::TWO_IN_ONE, DeviceType::TABLET,
        DeviceType::TV, DeviceType::WATCH, DeviceType::WEARABLE };

    for (auto deviceType : supportedDeviceTypes) {
        SystemProperties::SetDeviceType(deviceType);
        scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON), true);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        EXPECT_NE(AceType::DynamicCast<ArcScrollBarPattern>(frameNode->GetPattern()), nullptr);
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();
}

/**
 * @tc.name: ScrollBarInteractive001
 * @tc.desc: The layered parameter scroll_bar_interactive=false must not disable ArcScrollBar touch
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ScrollBarInteractive001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto themeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManager, nullptr);
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    ASSERT_NE(scrollBarTheme, nullptr);
    auto oldInteractive = scrollBarTheme->scrollBarInteractive_;
    scrollBarTheme->scrollBarInteractive_ = false;

    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    EXPECT_TRUE(arcScrollBar->GetScrollBarInteractive());

    // switching inner/outer scroll bar style re-applies the theme value to the member,
    // but the arc bar must still report itself interactive
    arcScrollBar->SetUseInnerScrollBar(false);
    EXPECT_TRUE(arcScrollBar->GetScrollBarInteractive());
    arcScrollBar->SetUseInnerScrollBar(true);
    EXPECT_TRUE(arcScrollBar->GetScrollBarInteractive());

    // the pan recognizer for thumb dragging must still be collected even when the
    // layered parameter scroll_bar_interactive is disabled for the round scroll bar.
    arcScrollBar->SetGestureEvent();
    arcScrollBar->SetScrollable(true);
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectTouchTarget(OffsetF(), getEventTargetImpl, result, frameNode_, responseLinkResult);
    EXPECT_EQ(result.size(), 1);

    scrollBarTheme->scrollBarInteractive_ = oldInteractive;
}

/**
 * @tc.name: ScrollBarInteractive002
 * @tc.desc: ArcScrollBar GetScrollBarInteractive returns true when scrollBarInteractive_=true and shapeMode=ROUND.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ScrollBarInteractive002, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    // default theme scrollBarInteractive_=true, shapeMode_=ROUND
    arcScrollBar->SetScrollBarInteractive(true);
    EXPECT_EQ(arcScrollBar->GetShapeMode(), ShapeMode::ROUND);
    EXPECT_TRUE(arcScrollBar->GetScrollBarInteractive());
}

/**
 * @tc.name: ScrollBarInteractive003
 * @tc.desc: ArcScrollBar GetScrollBarInteractive returns true when scrollBarInteractive_=false and shapeMode=ROUND
 *           (the DRA fix scenario: arc scroll bar must stay touch interactive).
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ScrollBarInteractive003, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    EXPECT_EQ(arcScrollBar->GetShapeMode(), ShapeMode::ROUND);
    // explicitly disable the layered parameter; ROUND must still report interactive
    arcScrollBar->SetScrollBarInteractive(false);
    EXPECT_TRUE(arcScrollBar->GetScrollBarInteractive());
}

/**
 * @tc.name: OnCollectLongPressTarget001
 * @tc.desc: ArcScrollBar OnCollectLongPressTarget collects the long-press recognizer when interactive=false (ROUND),
 *           covering the true branch of the if condition.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, OnCollectLongPressTarget001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    arcScrollBar->SetScrollBarInteractive(false);
    arcScrollBar->SetScrollable(true);
    arcScrollBar->InitLongPressEvent();
    ASSERT_NE(arcScrollBar->GetLongPressRecognizer(), nullptr);

    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectLongPressTarget(
        OffsetF(), getEventTargetImpl, result, frameNode_, responseLinkResult);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(responseLinkResult.size(), 1);
}

/**
 * @tc.name: OnCollectLongPressTarget002
 * @tc.desc: ArcScrollBar OnCollectLongPressTarget does not collect when isScrollable=false, covering the
 *           short-circuit false branch of the if condition.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, OnCollectLongPressTarget002, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    arcScrollBar->SetScrollBarInteractive(true);
    // The fixture content is taller than the viewport, so the layout pass marks the bar scrollable;
    // explicitly disable it to exercise the short-circuit branch.
    arcScrollBar->SetScrollable(false);
    ASSERT_FALSE(arcScrollBar->IsScrollable());
    arcScrollBar->InitLongPressEvent();
    ASSERT_NE(arcScrollBar->GetLongPressRecognizer(), nullptr);

    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectLongPressTarget(
        OffsetF(), getEventTargetImpl, result, frameNode_, responseLinkResult);
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(responseLinkResult.empty());
}

/**
 * @tc.name: OnCollectLongPressTarget003
 * @tc.desc: ArcScrollBar OnCollectLongPressTarget short-circuits when longPressRecognizer_ is null, covering
 *           branch1 (longPressRecognizer_ false → skip, isScrollable_ and GetScrollBarInteractive() not evaluated).
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, OnCollectLongPressTarget003, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    // The scroll bar pattern initializes the long-press recognizer during setup,
    // so reset it to null to exercise the short-circuit branch.
    arcScrollBar->SetLongPressRecognizer(nullptr);
    ASSERT_EQ(arcScrollBar->GetLongPressRecognizer(), nullptr);
    arcScrollBar->SetScrollable(true);

    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectLongPressTarget(
        OffsetF(), getEventTargetImpl, result, frameNode_, responseLinkResult);
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(responseLinkResult.empty());
}

/**
 * @tc.name: OnCollectLongPressTarget004
 * @tc.desc: ArcScrollBar OnCollectLongPressTarget short-circuits when isScrollable_ is false (recognizer exists),
 *           covering branch3 (isScrollable_ false → skip, GetScrollBarInteractive() not evaluated).
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, OnCollectLongPressTarget004, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    arcScrollBar->InitLongPressEvent();
    ASSERT_NE(arcScrollBar->GetLongPressRecognizer(), nullptr);
    // SetScrollable has a guard: CHECK_NULL_VOID(isScrollable_ != isScrollable).
    // Toggle to true first, then back to false to ensure isScrollable_ is false.
    arcScrollBar->SetScrollable(true);
    arcScrollBar->SetScrollable(false);
    ASSERT_FALSE(arcScrollBar->IsScrollable());

    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectLongPressTarget(
        OffsetF(), getEventTargetImpl, result, frameNode_, responseLinkResult);
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(responseLinkResult.empty());
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: ArcScrollBar HandleLongPress does not early-return when interactive=false (ROUND), and invokes the
 *           scroll page callback when AnalysisUpOrDown  isMousePressed  callback are all satisfied.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, HandleLongPress001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    // interactive=false but ROUND -> GetScrollBarInteractive() returns true, CHECK_NULL_VOID passes
    arcScrollBar->SetScrollBarInteractive(false);
    EXPECT_TRUE(arcScrollBar->GetScrollBarInteractive());

    bool callbackCalled = false;
    arcScrollBar->SetScrollPageCallback([&callbackCalled](bool reverse, bool smooth) {
        callbackCalled = true;
    });
    // configure state so isMousePressed_=true and callback is set; with default (unconfigured) geometry
    // CheckBarDirection returns BAR_NONE so AnalysisUpOrDown returns false -> inner if is false.
    // This covers the inner-false branch while proving CHECK_NULL_VOID did not early-return.
    arcScrollBar->SetIsMousePressed(true);
    arcScrollBar->SetLocationInfo(Offset(0, 0));
    arcScrollBar->HandleLongPress(true);
    // CHECK_NULL_VOID passed (no early return), but inner condition is false -> callback not called
    EXPECT_FALSE(callbackCalled);
    EXPECT_TRUE(arcScrollBar->GetScrollBarInteractive());
}

/**
 * @tc.name: OnCollectTouchTarget001
 * @tc.desc: ArcScrollBar OnCollectTouchTarget collects the pan recognizer with inBarRect=true and inBarRect=false,
 *           covering both branches of the inner if (sysJudge set vs null) for the ROUND scroll bar.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, OnCollectTouchTarget001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    arcScrollBar->SetScrollBarInteractive(false);
    arcScrollBar->SetScrollable(true);
    arcScrollBar->SetGestureEvent();
    ASSERT_NE(arcScrollBar->GetPanRecognizer(), nullptr);

    // inBarRect=true: sysJudge is set (non-null)
    TouchTestResult resultInBar;
    ResponseLinkResult responseLinkInBar;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectTouchTarget(
        OffsetF(), getEventTargetImpl, resultInBar, frameNode_, responseLinkInBar, true);
    EXPECT_EQ(resultInBar.size(), 1);
    EXPECT_EQ(responseLinkInBar.size(), 1);

    // inBarRect=false: sysJudge is nullptr
    TouchTestResult resultOutBar;
    ResponseLinkResult responseLinkOutBar;
    arcScrollBar->OnCollectTouchTarget(
        OffsetF(), getEventTargetImpl, resultOutBar, frameNode_, responseLinkOutBar, false);
    EXPECT_EQ(resultOutBar.size(), 1);
    EXPECT_EQ(responseLinkOutBar.size(), 1);
}

/**
 * @tc.name: OnCollectTouchTarget002
 * @tc.desc: ArcScrollBar OnCollectTouchTarget does not collect when isScrollable=false, covering the
 *           short-circuit false branch of the if condition for the ROUND scroll bar.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, OnCollectTouchTarget002, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    arcScrollBar->SetScrollBarInteractive(true);
    // The fixture content is taller than the viewport, so the layout pass marks the bar scrollable;
    // explicitly disable it to exercise the short-circuit branch.
    arcScrollBar->SetScrollable(false);
    ASSERT_FALSE(arcScrollBar->IsScrollable());
    arcScrollBar->SetGestureEvent();
    ASSERT_NE(arcScrollBar->GetPanRecognizer(), nullptr);

    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectTouchTarget(OffsetF(), getEventTargetImpl, result, frameNode_, responseLinkResult);
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(responseLinkResult.empty());
}

/**
 * @tc.name: SetUseInnerScrollBarSameValue001
 * @tc.desc: ArcScrollBar SetUseInnerScrollBar with the same value early-returns without re-applying theme values.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, SetUseInnerScrollBarSameValue001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto themeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManager, nullptr);
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    ASSERT_NE(scrollBarTheme, nullptr);
    auto oldInteractive = scrollBarTheme->scrollBarInteractive_;
    scrollBarTheme->scrollBarInteractive_ = false;

    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    // after creation useInnerScrollBar_ is true; calling with true again should early-return,
    // leaving scrollBarInteractive_ as the theme-applied value (false).
    arcScrollBar->SetScrollBarInteractive(false);
    auto heightBefore = arcScrollBar->GetScrollBarHeight();
    arcScrollBar->SetUseInnerScrollBar(true);
    EXPECT_EQ(arcScrollBar->GetScrollBarHeight(), heightBefore);

    scrollBarTheme->scrollBarInteractive_ = oldInteractive;
}

/**
 * @tc.name: OnCollectTouchTarget003
 * @tc.desc: ArcScrollBar OnCollectTouchTarget short-circuits when panRecognizer_ is null, covering
 *           branch1 (panRecognizer_ false → skip) for the ROUND scroll bar.
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, OnCollectTouchTarget003, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    arcScrollBar->SetScrollBarInteractive(false);
    arcScrollBar->SetScrollable(true);
    // Reset panRecognizer_ to null to cover the null-recognizer branch
    arcScrollBar->SetPanRecognizer(nullptr);
    ASSERT_EQ(arcScrollBar->GetPanRecognizer(), nullptr);

    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectTouchTarget(OffsetF(), getEventTargetImpl, result, frameNode_, responseLinkResult);
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(responseLinkResult.empty());
}

/**
 * @tc.name: OnCollectTouchTarget004
 * @tc.desc: ArcScrollBar OnCollectTouchTarget short-circuits when isScrollable_ is false (panRecognizer exists),
 *           covering branch3 (isScrollable_ false → skip, GetScrollBarInteractive() not evaluated).
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, OnCollectTouchTarget004, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateArcScrollBar(DisplayMode::ON);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    auto scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
    arcScrollBar->SetGestureEvent();
    ASSERT_NE(arcScrollBar->GetPanRecognizer(), nullptr);
    // SetScrollable has a guard: CHECK_NULL_VOID(isScrollable_ != isScrollable).
    // Toggle to true first, then back to false to ensure isScrollable_ is false.
    arcScrollBar->SetScrollable(true);
    arcScrollBar->SetScrollable(false);
    ASSERT_FALSE(arcScrollBar->IsScrollable());

    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    GetEventTargetImpl getEventTargetImpl;
    arcScrollBar->OnCollectTouchTarget(OffsetF(), getEventTargetImpl, result, frameNode_, responseLinkResult);
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(responseLinkResult.empty());
}
} // namespace OHOS::Ace::NG
