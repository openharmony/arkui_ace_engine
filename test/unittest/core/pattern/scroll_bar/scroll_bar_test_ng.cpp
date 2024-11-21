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

#include "test/mock/base/mock_task_executor.h"
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ScrollBarTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ScrollBarTestNg::SetUp() {}

void ScrollBarTestNg::TearDown()
{
    stackNode_ = nullptr;
    scrollNode_ = nullptr;
    scrollPattern_ = nullptr;
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
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
    FlushLayoutTask(scrollNode_, true);
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
    auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(proxy);
    ScrollableNodeInfo nodeInfo;
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.size(), 1);
    scrollBarProxy->RegisterScrollBar(nullptr);
    scrollBarProxy->RegisterScrollBar(nullptr);
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 1);
    scrollBarProxy->UnRegisterScrollableNode(nullptr);
    scrollBarProxy->UnRegisterScrollableNode(nullptr);
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.size(), 0);
    scrollBarProxy->UnRegisterScrollBar(nullptr);
    scrollBarProxy->UnRegisterScrollBar(nullptr);
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 0);
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    scrollBarProxy->RegisterScrollBar(nullptr);
    scrollBarProxy->NotifyScrollableNode(0, 1, nullptr);
    scrollBarProxy->NotifyScrollBarNode(0, 1);
    scrollBarProxy->NotifyScrollStart();
    scrollBarProxy->NotifyScrollStop();
    scrollBarProxy->NotifyScrollBar(nullptr);
    scrollBarProxy->StartScrollBarAnimator();
    scrollBarProxy->StopScrollBarAnimator();
    scrollBarProxy->NotifySnapScroll(0, 0, 0, 0);
    scrollBarProxy->CalcPatternOffset(0, 0, 0);
    scrollBarProxy->SetScrollEnabled(true, nullptr);
}
} // namespace OHOS::Ace::NG