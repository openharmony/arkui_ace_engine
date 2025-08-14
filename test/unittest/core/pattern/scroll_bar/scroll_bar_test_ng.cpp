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

#include "scroll_bar_test_ng.h"

#include "gtest/gtest.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ACTIVE_WIDTH = 8.0f;
constexpr float DEFAULT_NORMAL_WIDTH = 4.0f;
constexpr float DEFAULT_TOUCH_WIDTH = 32.0f;
constexpr float NORMAL_WIDTH = 4.f;
} // namespace

void ScrollBarTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SCROLL_BAR);
    auto scrollBarTheme = ScrollBarTheme::Builder().Build(themeConstants);
    scrollBarTheme->normalWidth_ = Dimension(NORMAL_WIDTH);
    scrollBarTheme->padding_ = Edge(0.0);
    scrollBarTheme->scrollBarMargin_ = Dimension(0.0);
    scrollBarTheme->touchWidth_ = Dimension(DEFAULT_TOUCH_WIDTH, DimensionUnit::VP);
    scrollBarTheme->activeWidth_ = Dimension(DEFAULT_ACTIVE_WIDTH, DimensionUnit::VP);
    scrollBarTheme->normalWidth_ = Dimension(DEFAULT_NORMAL_WIDTH, DimensionUnit::VP);
    auto scrollableThemeConstants = CreateThemeConstants(THEME_PATTERN_SCROLLABLE);
    auto scrollableTheme = ScrollableTheme::Builder().Build(scrollableThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ScrollableTheme::TypeId())).WillRepeatedly(Return(scrollableTheme));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockAnimationManager::Enable(true);
}

void ScrollBarTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ScrollBarTestNg::SetUp() {}

void ScrollBarTestNg::TearDown()
{
    RemoveFromStageNode();
    stackNode_ = nullptr;
    scrollNode_ = nullptr;
    scrollPattern_ = nullptr;
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    MockAnimationManager::GetInstance().Reset();
}

void ScrollBarTestNg::GetScrollBar()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ScrollBarPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ScrollBarLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ScrollBarAccessibilityProperty>();
}

RefPtr<FrameNode> ScrollBarTestNg::CreateMainFrameNode()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    return AceType::DynamicCast<FrameNode>(element);
}

void ScrollBarTestNg::CreateStack(Alignment align)
{
    StackModelNG stackModel;
    stackModel.Create();
    stackModel.SetAlignment(align);
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    stackNode_ = CreateMainFrameNode();
}

void ScrollBarTestNg::CreateScroll(float mainSize, Axis axis)
{
    ScrollModelNG model;
    model.Create();
    auto scrollBarProxy = model.CreateScrollBarProxy();
    model.SetAxis(axis);
    model.SetDisplayMode(static_cast<int>(DisplayMode::OFF));
    model.SetScrollBarProxy(scrollBarProxy);
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    scrollNode_ = CreateMainFrameNode();
    scrollPattern_ = scrollNode_->GetPattern<ScrollPattern>();
    CreateContent(mainSize, axis);
    ViewStackProcessor::GetInstance()->Pop();
}

void ScrollBarTestNg::CreateContent(float mainSize, Axis axis)
{
    ColumnModelNG colModel;
    colModel.Create(Dimension(0), nullptr, "");
    SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(mainSize));
    ViewStackProcessor::GetInstance()->Pop();
}

void ScrollBarTestNg::CreateScrollBar(bool infoflag, bool proxyFlag, Axis axis, DisplayMode displayMode)
{
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(axis);
    if (axis == Axis::NONE) {
        directionValue--;
    }
    scrollBarModel.Create(scrollBarProxy, infoflag, proxyFlag, directionValue, static_cast<int>(displayMode));
    GetScrollBar();
}

void ScrollBarTestNg::CreateScrollBarChild(float mainSize)
{
    Axis axis = layoutProperty_->GetAxisValue();
    ColumnModelNG colModel;
    colModel.Create(Dimension(0), nullptr, "");
    SetSize(axis, CalcLength(SCROLL_BAR_CHILD_WIDTH), CalcLength(mainSize));
    ViewStackProcessor::GetInstance()->Pop();
}

void ScrollBarTestNg::SetScrollContentMainSize(float mainSize)
{
    auto scrollContent = GetChildFrameNode(scrollNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(scrollContent), CalcLength(mainSize));
    scrollNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
}

/**
 * @tc.name: ScrollBarModel001
 * @tc.desc: ScrollBarModelNG Create
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarModel001, TestSize.Level1)
{
    bool proxyFlag = false;
    ScrollBarModelNG scrollBarModel;
    auto proxy = scrollBarModel.GetScrollBarProxy(nullptr);
    scrollBarModel.Create(proxy, true, proxyFlag, 0, 0);
    GetScrollBar();
    CreateDone();
    EXPECT_EQ(pattern_->scrollBarProxy_, nullptr);

    bool infoflag = false;
    scrollBarModel.Create(proxy, infoflag, false, 0, 0);
    GetScrollBar();
    CreateDone();
    EXPECT_FALSE(layoutProperty_->GetAxis().has_value());

    int32_t directionValue = -1;
    scrollBarModel.Create(proxy, true, true, directionValue, 0);
    GetScrollBar();
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetAxisValue(), Axis::VERTICAL);
    directionValue = 100;
    scrollBarModel.Create(proxy, true, true, directionValue, 0);
    GetScrollBar();
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetAxisValue(), Axis::VERTICAL);

    int32_t stateValue = -1;
    scrollBarModel.Create(proxy, true, true, 0, stateValue);
    GetScrollBar();
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetDisplayModeValue(), DisplayMode::AUTO);
    stateValue = 100;
    scrollBarModel.Create(proxy, true, true, 0, stateValue);
    GetScrollBar();
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetDisplayModeValue(), DisplayMode::AUTO);
}

/**
 * @tc.name: ScrollBarModel002
 * @tc.desc: ScrollBarModelNG GetScrollBarProxy
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarModel002, TestSize.Level1)
{
    ScrollBarModelNG scrollBarModel;
    auto proxy = scrollBarModel.GetScrollBarProxy(nullptr);
    EXPECT_NE(proxy, nullptr);
    auto proxy2 = scrollBarModel.GetScrollBarProxy(proxy);
    EXPECT_EQ(proxy, proxy2);
}

/**
 * @tc.name: ScrollBarProxy001
 * @tc.desc: ScrollBarProxy
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarProxy001, TestSize.Level1)
{
    ScrollBarModelNG scrollBarModel;
    auto proxy = scrollBarModel.GetScrollBarProxy(nullptr);
    CHECK_NULL_VOID(proxy);
    auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(proxy);
    CHECK_NULL_VOID(scrollBarProxy);
    ScrollableNodeInfo nodeInfo;
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    ASSERT_NE(scrollBarProxy, nullptr);
    scrollBarProxy->RegisterScrollBar(nullptr);
    scrollBarProxy->RegisterScrollBar(nullptr);
    scrollBarProxy->RegisterNestScrollableNode(nodeInfo);
    ASSERT_EQ(scrollBarProxy->scrollBars_.size(), 1);
    scrollBarProxy->UnRegisterScrollBar(nullptr);
    scrollBarProxy->UnRegisterScrollBar(nullptr);
    ASSERT_EQ(scrollBarProxy->scrollBars_.size(), 0);
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    scrollBarProxy->RegisterScrollBar(nullptr);
    scrollBarProxy->NotifyScrollableNode(0, 1, nullptr);
    scrollBarProxy->NotifyScrollBarNode(0, 1);
    scrollBarProxy->NotifyScrollStart();
    scrollBarProxy->NotifyScrollStop();
    scrollBarProxy->NotifyScrollBar(SCROLL_FROM_NONE);
    scrollBarProxy->StartScrollBarAnimator();
    scrollBarProxy->StopScrollBarAnimator();
    scrollBarProxy->NotifySnapScroll(0, 0, 0, 0);
    scrollBarProxy->CalcPatternOffset(0, 0, 0);
    scrollBarProxy->ScrollPage(true, true);
    scrollBarProxy->SetScrollEnabled(true, nullptr);
}

/**
 * @tc.name: IsNestScroller001
 * @tc.desc: ScrollBarProxy IsNestScroller
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, IsNestScroller001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    pattern_->SetEnableNestedSorll(true);
    ASSERT_EQ(pattern_->scrollBarProxy_->IsNestScroller(), true);
    pattern_->SetEnableNestedSorll(false);
    ASSERT_EQ(pattern_->scrollBarProxy_->IsNestScroller(), false);
}

/**
 * @tc.name: GetScrollableNodeInfo001
 * @tc.desc: ScrollBarProxy GetScrollableNodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetScrollableNodeInfo001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    pattern_->SetEnableNestedSorll(true);
    auto nestScroller = pattern_->scrollBarProxy_->GetScrollableNodeInfo();
    ASSERT_NE(nestScroller.scrollableNode.Upgrade(), nullptr);
}

/**
 * @tc.name: setNestedScroll001
 * @tc.desc: ScrollBarProxy SetNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetNestedScroll001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    CreateScrollBarChild();
    CreateDone();
    pattern_->SetEnableNestedSorll(true);
    auto scrollPnTest = scrollNode_->GetPattern<ScrollablePattern>();
    scrollBarModel.SetNestedScroll(scrollNode_, scrollPnTest);
    ASSERT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: setNestedScroll001
 * @tc.desc: ScrollBarProxy SetNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, UnSetNestedScroll001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    CreateScrollBarChild();
    CreateDone();
    pattern_->SetEnableNestedSorll(true);
    auto scrollPnTest = scrollNode_->GetPattern<ScrollablePattern>();
    scrollBarModel.SetNestedScroll(scrollNode_, scrollPnTest);
    ASSERT_NE(pattern_->GetScrollBarProxy(), nullptr);
    scrollBarModel.UnSetNestedScroll(scrollNode_, scrollPnTest);
    ASSERT_EQ(scrollPnTest->nestScrollBarProxy_.size(), 0);
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Test HandleDragUpdate when child height less than scrollbar height
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, HandleDragUpdate001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    GestureEvent info;
    info.SetMainDelta(10.f);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 10.f);
    auto scrollDelta = pattern_->scrollBarProxy_->CalcPatternOffset(
        scrollPattern_->scrollableDistance_, pattern_->scrollableDistance_, -pattern_->currentOffset_);
    EXPECT_EQ(scrollPattern_->currentOffset_, scrollDelta);

    info.SetMainDelta(10.f);
    auto scrollable = scrollPattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 0.f);
    EXPECT_EQ(scrollPattern_->currentOffset_, 0.f);
}

/**
 * @tc.name: HandleDragUpdate002
 * @tc.desc: Test HandleDragUpdate when child height greater than scrollbar height
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, HandleDragUpdate002, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild(2000.f);
    CreateDone();

    GestureEvent info;
    info.SetMainDelta(10.f);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 0.f);
    EXPECT_EQ(scrollPattern_->currentOffset_, 0.f);

    info.SetMainDelta(-10.f);
    auto scrollable = scrollPattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 0.f);
    EXPECT_EQ(scrollPattern_->currentOffset_, -10.f);
}

/**
 * @tc.name: ValidateOffset001
 * @tc.desc: Test ScrollBarPattern ValidateOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ValidateOffset001, TestSize.Level1)
{
    ScrollBarPattern scrollBarPattern;
    scrollBarPattern.scrollableDistance_ = -2.0f;
    scrollBarPattern.currentOffset_ = 0.0f;
    scrollBarPattern.ValidateOffset();
    EXPECT_EQ(scrollBarPattern.currentOffset_, 0.0f);
}
/**
 * @tc.name: ValidateOffset002
 * @tc.desc: Test ScrollBarPattern ValidateOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ValidateOffset002, TestSize.Level1)
{
    ScrollBarPattern scrollBarPattern;
    scrollBarPattern.scrollableDistance_ = 2.0f;
    scrollBarPattern.currentOffset_ = 3.0f;
    scrollBarPattern.ValidateOffset();
    EXPECT_NE(scrollBarPattern.currentOffset_, 3.0f);
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test ScrollBarPattern UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    scrollBarPattern->scrollableDistance_ = -2.0f;
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    auto result = scrollBarPattern->UpdateCurrentOffset(2.0f, SCROLL_FROM_BAR, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: Test ScrollBarPattern UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    scrollBarPattern->scrollableDistance_ = 2.0f;
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    auto result = scrollBarPattern->UpdateCurrentOffset(2.0f, SCROLL_FROM_BAR, false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: Test ScrollBarPattern UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, UpdateCurrentOffset003, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    scrollBarPattern->scrollableDistance_ = 2.0f;
    scrollBarPattern->currentOffset_ = 2.0f;
    scrollBarPattern->lastOffset_ = 2.0f;
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    auto result = scrollBarPattern->UpdateCurrentOffset(2.0f, SCROLL_FROM_BAR, false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AddScrollBarLayoutInfo001
 * @tc.desc: Test ScrollBarPattern AddScrollBarLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, AddScrollBarLayoutInfo001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    scrollBarPattern->scrollableDistance_ = 2.0f;
    scrollBarPattern->currentOffset_ = 2.0f;
    scrollBarPattern->lastOffset_ = 2.0f;
    RefPtr<ScrollBarProxy> scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    scrollBarPattern->scrollBarProxy_ = scrollBarProxy;
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollBarPattern->outerScrollBarLayoutInfos_.resize(120);
    for (int i = 0; i < 120; ++i) {
        scrollBarPattern->outerScrollBarLayoutInfos_.emplace_back(OuterScrollBarLayoutInfo());
    }
    scrollBarPattern->AddScrollBarLayoutInfo();
    EXPECT_EQ(scrollBarPattern->outerScrollBarLayoutInfos_.back().currentOffset_, 2);
}

/**
 * @tc.name: ProcessFrictionMotionStop001
 * @tc.desc: Test ScrollBarPattern ProcessFrictionMotionStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ProcessFrictionMotionStop001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    RefPtr<ScrollBarProxy> scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    scrollBarPattern->scrollBarProxy_ = scrollBarProxy;
    scrollBarPattern->scrollBarProxy_->scrollSnapTrigger_ = true;
    scrollBarPattern->ProcessFrictionMotionStop();
    EXPECT_FALSE(scrollBarPattern->scrollBarProxy_->scrollSnapTrigger_);
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, DumpAdvanceInfo001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    scrollBarPattern->scrollBar_ = scrollBar;
    scrollBarPattern->scrollBar_->activeRect_ = Rect(2, 6, 5, 10);
    scrollBarPattern->DumpAdvanceInfo(json);
    EXPECT_EQ(json->GetString("activeRect"), "Rect (2.00, 6.00) - [5.00 x 10.00]");
}

/**
 * @tc.name: DumpAdvanceInfo002
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, DumpAdvanceInfo002, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    scrollBarPattern->hasChild_ = true;
    scrollBarPattern->scrollBar_ = scrollBar;
    scrollBarPattern->scrollBar_->activeRect_ = Rect(2, 6, 5, 10);
    scrollBarPattern->DumpAdvanceInfo(json);
    EXPECT_NE(json->GetString("activeRect"), "Rect (2.00, 6.00) - [5.00 x 10.00]");
}

/**
 * @tc.name: DumpAdvanceInfo003
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, DumpAdvanceInfo003, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    OuterScrollBarLayoutInfo layoutInfo;
    layoutInfo.layoutTime_ = 2;
    layoutInfo.currentOffset_ = 3.f;
    layoutInfo.scrollableNodeOffset_ = 5.f;
    scrollBarPattern->outerScrollBarLayoutInfos_.emplace_back(layoutInfo);
    scrollBarPattern->hasChild_ = true;
    scrollBarPattern->DumpAdvanceInfo(json);
    EXPECT_NE(json->GetString("activeRect"), "Rect (2.00, 6.00) - [5.00 x 10.00]");
}

/**
 * @tc.name: DumpAdvanceInfo004
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, DumpAdvanceInfo004, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    OuterScrollBarLayoutInfo layoutInfo;
    layoutInfo.layoutTime_ = 2;
    layoutInfo.currentOffset_ = 3.f;
    layoutInfo.scrollableNodeOffset_ = 5.f;
    scrollBarPattern->outerScrollBarLayoutInfos_.emplace_back(layoutInfo);
    scrollBarPattern->DumpAdvanceInfo(json);
    EXPECT_NE(json->GetString("activeRect"), "Rect (2.00, 6.00) - [5.00 x 10.00]");
}

/**
 * @tc.name: GetDisplayModeDumpInfo001
 * @tc.desc: Test ScrollBarPattern GetDisplayModeDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetDisplayModeDumpInfo001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    scrollBarPattern->displayMode_ = DisplayMode::OFF;
    scrollBarPattern->GetDisplayModeDumpInfo(json);
    EXPECT_EQ(json->GetString("outerScrollBarState"), "OFF");
}

/**
 * @tc.name: GetDisplayModeDumpInfo002
 * @tc.desc: Test ScrollBarPattern GetDisplayModeDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetDisplayModeDumpInfo002, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    scrollBarPattern->GetDisplayModeDumpInfo(json);
    EXPECT_EQ(json->GetString("outerScrollBarState"), "AUTO");
}

/**
 * @tc.name: GetDisplayModeDumpInfo003
 * @tc.desc: Test ScrollBarPattern GetDisplayModeDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetDisplayModeDumpInfo003, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    scrollBarPattern->displayMode_ = DisplayMode::ON;
    scrollBarPattern->GetDisplayModeDumpInfo(json);
    EXPECT_EQ(json->GetString("outerScrollBarState"), "ON");
}

/**
 * @tc.name: GetDisplayModeDumpInfo004
 * @tc.desc: Test ScrollBarPattern GetDisplayModeDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetDisplayModeDumpInfo004, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    int32_t displayMode = 100;
    scrollBarPattern->displayMode_ = static_cast<DisplayMode>(displayMode);
    json->Put("outerScrollBarState", "null");
    scrollBarPattern->GetDisplayModeDumpInfo(json);
    EXPECT_EQ(json->GetString("outerScrollBarState"), "null");
}

/**
 * @tc.name: GetPanDirectionDumpInfo001
 * @tc.desc: Test ScrollBarPattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetPanDirectionDumpInfo001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    scrollBarPattern->panRecognizer_ = panRecognizer;
    scrollBarPattern->panRecognizer_->direction_.type = PanDirection::NONE;
    scrollBarPattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("panDirection"), "NONE");
}

/**
 * @tc.name: GetPanDirectionDumpInfo002
 * @tc.desc: Test ScrollBarPattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetPanDirectionDumpInfo002, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    scrollBarPattern->panRecognizer_ = panRecognizer;
    scrollBarPattern->panRecognizer_->direction_.type = PanDirection::VERTICAL;
    scrollBarPattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("panDirection"), "VERTICAL");
}

/**
 * @tc.name: GetPanDirectionDumpInfo003
 * @tc.desc: Test ScrollBarPattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetPanDirectionDumpInfo003, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    scrollBarPattern->panRecognizer_ = panRecognizer;
    scrollBarPattern->panRecognizer_->direction_.type = PanDirection::HORIZONTAL;
    scrollBarPattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("panDirection"), "HORIZONTAL");
}

/**
 * @tc.name: GetPanDirectionDumpInfo004
 * @tc.desc: Test ScrollBarPattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetPanDirectionDumpInfo004, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    scrollBarPattern->panRecognizer_ = panRecognizer;
    scrollBarPattern->panRecognizer_->direction_.type = PanDirection::ALL;
    scrollBarPattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("panDirection"), "FREE");
}
/**
 * @tc.name: GetPanDirectionDumpInfo005
 * @tc.desc: Test ScrollBarPattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetPanDirectionDumpInfo005, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    json->Put("outerScrollBarState", "null");
    scrollBarPattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("panDirection"), "null");
}

/**
 * @tc.name: GetAxisDumpInfo001
 * @tc.desc: Test ScrollBarPattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetAxisDumpInfo001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    scrollBarPattern->axis_ = Axis::NONE;
    scrollBarPattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "NONE");
}

/**
 * @tc.name: GetAxisDumpInfo002
 * @tc.desc: Test ScrollBarPattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetAxisDumpInfo002, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    scrollBarPattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "VERTICAL");
}

/**
 * @tc.name: GetAxisDumpInfo003
 * @tc.desc: Test ScrollBarPattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetAxisDumpInfo003, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    scrollBarPattern->axis_ = Axis::HORIZONTAL;
    scrollBarPattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "HORIZONTAL");
}

/**
 * @tc.name: GetAxisDumpInfo004
 * @tc.desc: Test ScrollBarPattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetAxisDumpInfo004, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    scrollBarPattern->axis_ = Axis::FREE;
    scrollBarPattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "FREE");
}

/**
 * @tc.name: GetAxisDumpInfo005
 * @tc.desc: Test ScrollBarPattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetAxisDumpInfo005, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    int32_t axis = 100;
    scrollBarPattern->axis_ = static_cast<Axis>(axis);
    json->Put("Axis", "null");
    scrollBarPattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "null");
}

/**
 * @tc.name: ScrollPositionCallback001
 * @tc.desc: Test ScrollBarPattern ScrollPositionCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollPositionCallback001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    scrollBarPattern->ScrollPositionCallback(2.0f, SCROLL_FROM_START, true);
    EXPECT_TRUE(scrollBarPattern->isScrolling_);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test ScrollBarPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ToJsonValue001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 3;
    scrollBarPattern->enableNestedSorll_ = true;
    scrollBarPattern->ToJsonValue(json, filter);
    EXPECT_NE(json->GetString("enableNestedScroll"), "true");
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test ScrollBarPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ToJsonValue002, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 0;
    scrollBarPattern->enableNestedSorll_ = true;
    scrollBarPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("enableNestedScroll"), "true");
}

/**
 * @tc.name: GetPositionMode001
 * @tc.desc: Test ScrollBarPattern GetPositionMode
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetPositionMode001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    frameNode->layoutProperty_ = layoutProperty;
    scrollBarPattern->frameNode_ = frameNode;
    auto result = scrollBarPattern->GetPositionMode();
    EXPECT_EQ(result, PositionMode::LEFT);
}

/**
 * @tc.name: GetPositionMode002
 * @tc.desc: Test ScrollBarPattern GetPositionMode
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetPositionMode002, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::LTR;
    frameNode->layoutProperty_ = layoutProperty;
    scrollBarPattern->frameNode_ = frameNode;
    auto result = scrollBarPattern->GetPositionMode();
    EXPECT_EQ(result, PositionMode::RIGHT);
}

/**
 * @tc.name: GetPositionMode003
 * @tc.desc: Test ScrollBarPattern GetPositionMode
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetPositionMode003, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollBarPattern->frameNode_ = frameNode;
    auto result = scrollBarPattern->GetPositionMode();
    EXPECT_EQ(result, PositionMode::RIGHT);
}

/**
 * @tc.name: UpdateScrollBarRegion001
 * @tc.desc: Test ScrollBarPattern UpdateScrollBarRegion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, UpdateScrollBarRegion001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollBarPattern->frameNode_ = frameNode;
    Size viewPort(4.0F, 2.0F);
    Offset viewOffset(4.0F, 6.0F);
    OffsetF scrollOffset(2.0F, 2.0F);
    SizeF scrollSize(2.0F, 2.0F);
    scrollBarPattern->scrollBarOverlayModifier_ =
        AceType::MakeRefPtr<ScrollBarOverlayModifier>(scrollOffset, scrollSize);
    scrollBarPattern->UpdateScrollBarRegion(2.0f, 2.0f, viewPort, viewOffset, SCROLL_FROM_START);
    EXPECT_NE(scrollBarPattern->scrollBarOverlayModifier_->GetOpacity(), 0);
}

/**
 * @tc.name: SetEnableNestedScroll001
 * @tc.desc: Test SetEnableNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetEnableNestedScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test function SetEnableNestedScroll.
     * @tc.expected: Related functions run ok.
     */
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    pattern_->SetEnableNestedSorll(true);
    scrollBarModel.SetEnableNestedScroll(false);
    EXPECT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: SetEnableNestedScroll002
 * @tc.desc: Test SetEnableNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetEnableNestedScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test function SetEnableNestedScroll.
     * @tc.expected: Related functions run ok.
     */
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    pattern_->SetEnableNestedSorll(true);
    scrollBarModel.SetEnableNestedScroll(true);
    EXPECT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: SetEnableNestedScroll003
 * @tc.desc: Test SetEnableNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetEnableNestedScroll003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test function SetEnableNestedScroll.
     * @tc.expected: Related functions run ok.
     */
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    pattern_->SetEnableNestedSorll(false);
    scrollBarModel.SetEnableNestedScroll(true);
    EXPECT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: SetEnableNestedScroll004
 * @tc.desc: Test SetEnableNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetEnableNestedScroll004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test function SetEnableNestedScroll.
     * @tc.expected: Related functions run ok.
     */
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    pattern_->SetEnableNestedSorll(false);
    scrollBarModel.SetEnableNestedScroll(false);
    EXPECT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: SetEnableNestedScroll005
 * @tc.desc: Test SetEnableNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetEnableNestedScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test function SetEnableNestedScroll.
     * @tc.expected: Related functions run ok.
     */
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    pattern_->SetEnableNestedSorll(true);
    scrollBarModel.SetEnableNestedScroll(frameNode, false);
    EXPECT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: SetEnableNestedScroll006
 * @tc.desc: Test SetEnableNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetEnableNestedScroll006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test function SetEnableNestedScroll.
     * @tc.expected: Related functions run ok.
     */
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    pattern_->SetEnableNestedSorll(true);
    scrollBarModel.SetEnableNestedScroll(frameNode, true);
    EXPECT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: SetEnableNestedScroll007
 * @tc.desc: Test SetEnableNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetEnableNestedScroll007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test function SetEnableNestedScroll.
     * @tc.expected: Related functions run ok.
     */
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    pattern_->SetEnableNestedSorll(false);
    scrollBarModel.SetEnableNestedScroll(frameNode, true);
    EXPECT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: SetEnableNestedScroll008
 * @tc.desc: Test SetEnableNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetEnableNestedScroll008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test function SetEnableNestedScroll.
     * @tc.expected: Related functions run ok.
     */
    CreateStack();
    CreateScroll();
    auto scrollBarProxy = scrollPattern_->GetScrollBarProxy();
    ScrollBarModelNG scrollBarModel;
    int32_t directionValue = static_cast<int>(Axis::VERTICAL);
    scrollBarModel.Create(scrollBarProxy, true, true, directionValue, static_cast<int>(DisplayMode::ON));
    GetScrollBar();
    pattern_->SetEnableNestedSorll(false);
    scrollBarModel.SetEnableNestedScroll(frameNode, false);
    EXPECT_NE(pattern_->GetScrollBarProxy(), nullptr);
}

/**
 * @tc.name: SetScrollBarColorTest001
 * @tc.desc: Test SetScrollBarColor and GetBarColor method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetScrollBarColorTest, TestSize.Level1)
{
    ScrollBarModelNG scrollBarModel;
    auto scrollBarProxy = scrollBarModel.GetScrollBarProxy(nullptr);
    scrollBarModel.Create(
        scrollBarProxy, true, true, static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::ON));
    scrollBarModel.SetScrollBarColor(Color::FromString(SCROLLBAR_COLOR_BLUE));
    GetScrollBar();
    CreateScrollBarChild();
    CreateDone();
    auto paintProperty = pattern_->GetPaintProperty<ScrollBarPaintProperty>();
    /**
     * @tc.steps: step1. Set ScrollBarColor to blue
     * @tc.expected: ScrollablePaintProperty ScrollBarColor is updated to blue
     */
    // scrollBarModel.SetScrollBarColor(Color::FromString(SCROLLBAR_COLOR_BLUE));
    EXPECT_EQ(paintProperty->GetScrollBarColor()->GetValue(), Color::FromString(SCROLLBAR_COLOR_BLUE).GetValue());
}

/**
 * @tc.name: SetScrollBarColorTest002
 * @tc.desc: Test SetScrollBarColor
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetScrollBarColorTest002, TestSize.Level1)
{
    ScrollModelNG model;
    model.Create();
    model.SetAxis(Axis::FREE);
    scrollNode_ = CreateMainFrameNode();
    CHECK_NULL_VOID(scrollNode_);
    scrollPattern_ = scrollNode_->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern_);

    model.SetScrollBarColor(Color::BLUE);
    auto scrollBar = scrollPattern_->GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    EXPECT_EQ(scrollBar->GetForegroundColor(), Color::BLUE);
}

/**
 * @tc.name: CreateWithResourceObj
 * @tc.desc: Test CreateWithResourceObj in ScrollBaModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, CreateWithResourceObj001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    ScrollBarModelNG scrollBarModel;
    auto scrollBarProxy = scrollBarModel.GetScrollBarProxy(nullptr);
    scrollBarModel.Create(
        scrollBarProxy, true, true, static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::ON));
    GetScrollBar();

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    scrollBarModel.CreateWithResourceObj(ScrollBarJsResType::SCROLLBAR_COLOR, invalidResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(0, Color::BLUE);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::COLOR), params, "", "", Container::CurrentIdSafely());
    scrollBarModel.CreateWithResourceObj(ScrollBarJsResType::SCROLLBAR_COLOR, resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    auto paintProperty = pattern_->GetPaintProperty<ScrollBarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto color = paintProperty->GetScrollBarColorValue(Color::BLUE);
    EXPECT_EQ(color, Color::BLUE);

    scrollBarModel.CreateWithResourceObj(ScrollBarJsResType::SCROLLBAR_COLOR, resObjWithString);
    pattern_->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: UpdateScrollBarDisplay
 * @tc.desc: Test UpdateScrollBarDisplay
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, UpdateScrollBarDisplay, TestSize.Level1)
{
    ScrollBarModelNG scrollBarModel;
    auto scrollBarProxy = scrollBarModel.GetScrollBarProxy(nullptr);
    scrollBarModel.Create(
        scrollBarProxy, true, true, static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::AUTO));
    GetScrollBar();

    /**
     * @tc.steps: step1. scrollable node is scrolling
     * @tc.expected: don't start disappearAnimation
     */
    pattern_->controlDistance_ = 100.0f;
    pattern_->controlDistanceChanged_ = true;
    pattern_->scrollBarProxy_->SetIsScrollableNodeScrolling(true);
    pattern_->UpdateScrollBarDisplay();
    EXPECT_FALSE(pattern_->controlDistanceChanged_);
    EXPECT_FALSE(pattern_->disappearAnimation_);

    /**
     * @tc.steps: step2. scrollable node isn't scrolling
     * @tc.expected: start disappearAnimation
     */
    pattern_->controlDistanceChanged_ = true;
    pattern_->scrollBarProxy_->SetIsScrollableNodeScrolling(false);
    pattern_->UpdateScrollBarDisplay();
    EXPECT_FALSE(pattern_->controlDistanceChanged_);
    EXPECT_TRUE(pattern_->disappearAnimation_);
}

/**
 * @tc.name: UpdateOverlayModifierTest001
 * @tc.desc: Test UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, UpdateOverlayModifierTest001, TestSize.Level1)
{
    RefPtr<ScrollBarPattern> scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    ASSERT_NE(scrollBarPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_BAR_ETS_TAG, 2, scrollBarPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(
        frameNode->GetRenderContext(), frameNode->geometryNode_, frameNode->paintProperty_);
    ASSERT_NE(paintWrapper, nullptr);
    auto paintMethod = ScrollBarPaintMethod(false);
    ScrollModelNG model;
    model.Create();
    scrollNode_ = CreateMainFrameNode();
    CHECK_NULL_VOID(scrollNode_);
    scrollPattern_ = scrollNode_->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern_);
    auto scrollBar = scrollPattern_->GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(theme);
    paintMethod.UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(scrollBar->GetForegroundColor(), theme->GetForegroundColor());
    model.SetScrollBarColor(Color::BLUE);
    paintMethod.UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(scrollBar->GetForegroundColor(), Color::BLUE);

    auto inputHub = pattern_->GetInputHub();
    auto onHover = inputHub->hoverEventActuator_->inputEvents_.front()->GetOnHoverFunc();
    HoverInfo info;
    onHover(true, info);
    paintMethod.UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    Color color = Color::BLUE;
    EXPECT_EQ(scrollBar->GetForegroundColor(), color.BlendColor(theme->GetForegroundHoverBlendColor()));
    onHover(false, info);
    paintMethod.UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(scrollBar->GetForegroundColor(), Color::BLUE);
    ViewStackProcessor::GetInstance()->Pop();
}
} // namespace OHOS::Ace::NG
