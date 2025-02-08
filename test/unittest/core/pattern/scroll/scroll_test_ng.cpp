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

#include "mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
void ScrollTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SCROLL_BAR);
    auto scrollBarTheme = ScrollBarTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    scrollBarTheme->normalWidth_ = Dimension(NORMAL_WIDTH);
    scrollBarTheme->padding_ = Edge(0.0);
    scrollBarTheme->scrollBarMargin_ = Dimension(0.0);
    scrollBarTheme->touchWidth_ = Dimension(DEFAULT_TOUCH_WIDTH, DimensionUnit::VP);
    scrollBarTheme->activeWidth_ = Dimension(DEFAULT_ACTIVE_WIDTH, DimensionUnit::VP);
    scrollBarTheme->normalWidth_ = Dimension(DEFAULT_NORMAL_WIDTH, DimensionUnit::VP);
    scrollBarTheme->foregroundColor_ = Color::FromString(SCROLL_BAR_COLOR);
    auto scrollableThemeConstants = CreateThemeConstants(THEME_PATTERN_SCROLLABLE);
    auto scrollableTheme = ScrollableTheme::Builder().Build(scrollableThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ScrollableTheme::TypeId())).WillRepeatedly(Return(scrollableTheme));
    MockAnimationManager::Enable(true);
}

void ScrollTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ScrollTestNg::SetUp() {}

void ScrollTestNg::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    positionController_ = nullptr;
    contentChildren_.clear();
    scrollBar_ = nullptr;
    scrollable_ = nullptr;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    MockAnimationManager::GetInstance().Reset();
}

void ScrollTestNg::GetScroll()
{
    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<ScrollPattern>();
    eventHub_ = frameNode_->GetEventHub<ScrollEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ScrollLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ScrollAccessibilityProperty>();
    positionController_ = pattern_->GetScrollPositionController();
}

RefPtr<PaintWrapper> ScrollTestNg::CreateScrollDone(const RefPtr<FrameNode>& frameNode)
{
    CreateDone();
    scrollBar_ = pattern_->GetScrollBar();
    scrollable_ = pattern_->GetScrollableEvent()->GetScrollable();
    return frameNode_->CreatePaintWrapper();
}

ScrollModelNG ScrollTestNg::CreateScroll()
{
    ScrollModelNG model;
    model.Create();
    auto proxy = model.CreateScrollBarProxy();
    model.SetScrollBarProxy(proxy);
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(HEIGHT));
    GetScroll();
    return model;
}

void ScrollTestNg::CreateContent(float mainSize)
{
    auto axis = layoutProperty_->GetAxis();
    if (axis.has_value() && axis.value() == Axis::HORIZONTAL) {
        RowModelNG rowModel;
        rowModel.Create(Dimension(0), nullptr, "");
    } else {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
    }
    SetSize(axis, CalcLength(FILL_LENGTH), CalcLength(mainSize));
}

void ScrollTestNg::CreateContentChild(int32_t childNumber)
{
    contentChildren_.clear();
    for (int32_t index = 0; index < childNumber; index++) {
        TextModelNG textModel;
        textModel.Create(u"text");
        SetSize(layoutProperty_->GetAxis(), CalcLength(FILL_LENGTH), CalcLength(ITEM_MAIN_SIZE));
        contentChildren_.emplace_back(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ScrollTestNg::ScrollBy(double pixelX, double pixelY, bool smooth)
{
    pattern_->ScrollBy(pixelX, pixelY, smooth);
    FlushUITasks();
}
} // namespace OHOS::Ace::NG
