/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension WIDTH = 10.0_vp;
constexpr Dimension HEIGHT = 10.0_vp;
const Color COLOR = Color::BLUE;
} // namespace

class CounterPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CounterPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}
void CounterPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}
void CounterPatternTestNg::SetUp() {}
void CounterPatternTestNg::TearDown() {}

/**
 * @tc.name: CounterPatternTest001
 * @tc.desc: Test counter Create function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterPatternTestNg, CounterPatternTest001, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);
    counterModelNG.Create();
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode1, nullptr);
}

/**
 * @tc.name: CounterPatternTest002
 * @tc.desc: Test counter SetOnInc and SetOnDec function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterPatternTestNg, CounterPatternTest002, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto counterEventFunc1 = []() {};
    counterModelNG.SetOnInc(std::move(counterEventFunc1));
    auto counterEventFunc2 = []() {};
    counterModelNG.SetOnDec(std::move(counterEventFunc2));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: CounterPatternTest003
 * @tc.desc: Test counter SetHeight and SetWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterPatternTestNg, CounterPatternTest003, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    counterModelNG.SetWidth(WIDTH);
    counterModelNG.SetHeight(HEIGHT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto selfIdealSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(selfIdealSize->Width()->dimension_, WIDTH);
    EXPECT_EQ(selfIdealSize->Height()->dimension_, HEIGHT);
}

/**
 * @tc.name: CounterPatternTest004
 * @tc.desc: Test counter SetControlWidth, SetStateChange and SetBackgroundColor function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterPatternTestNg, CounterPatternTest004, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    counterModelNG.SetControlWidth(WIDTH);
    counterModelNG.SetStateChange(true);
    counterModelNG.SetBackgroundColor(COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor(), COLOR);
}
} // namespace OHOS::Ace::NG