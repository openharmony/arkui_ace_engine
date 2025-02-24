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

#include "refresh_test_ng.h"

#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components/refresh/refresh_theme.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float TEXT_HEIGHT = 200.f;
} // namespace

void RefreshTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_REFRESH);
    auto refreshTheme = RefreshTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(refreshTheme));
    auto scrollableThemeConstants = CreateThemeConstants(THEME_PATTERN_SCROLLABLE);
    auto scrollableTheme = ScrollableTheme::Builder().Build(scrollableThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(ScrollableTheme::TypeId())).WillRepeatedly(Return(scrollableTheme));
    MockAnimationManager::Enable(true);
}

void RefreshTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RefreshTestNg::SetUp() {}

void RefreshTestNg::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    MockAnimationManager::GetInstance().Reset();
}

void RefreshTestNg::GetRefresh()
{
    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<RefreshPattern>();
    eventHub_ = frameNode_->GetEventHub<RefreshEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<RefreshLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<RefreshAccessibilityProperty>();
}

RefreshModelNG RefreshTestNg::CreateRefresh()
{
    RefreshModelNG model;
    model.Create();
    GetRefresh();
    return model;
}

void RefreshTestNg::CreateText()
{
    TextModelNG model;
    model.Create(u"text");
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(TEXT_HEIGHT));
    ViewStackProcessor::GetInstance()->Pop();
}

RefPtr<FrameNode> RefreshTestNg::CreateCustomNode()
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(CUSTOM_NODE_WIDTH), CalcLength(CUSTOM_NODE_HEIGHT)));
    return frameNode;
}
} // namespace OHOS::Ace::NG
