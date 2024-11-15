/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "linear_indicator_test_ng.h"

#include "core/components/button/button_theme.h"

namespace OHOS::Ace::NG {

void LinearIndicatorTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_LINEAR_INDICATOR);
    auto linearIndicatorTheme = LinearIndicatorTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(LinearIndicatorTheme::TypeId())).WillRepeatedly(Return(linearIndicatorTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(AnyNumber());
}

void LinearIndicatorTestNg::SetUp() {}

void LinearIndicatorTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    controller_ = nullptr;
    theme_ = nullptr;
}

void LinearIndicatorTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<LinearIndicatorPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<LinearIndicatorLayoutProperty>();
    controller_ = pattern_->GetController();
    auto pipeline = PipelineBase::GetCurrentContext();
    if (pipeline) {
        theme_ = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    }
}

void LinearIndicatorTestNg::Create(const std::function<void(LinearIndicatorModelNG)>& callback)
{
    LinearIndicatorModelNG model;
    model.Create(5);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}
} // namespace OHOS::Ace::NG
