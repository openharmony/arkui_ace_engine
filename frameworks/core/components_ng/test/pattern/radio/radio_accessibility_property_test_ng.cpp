/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string VALUE = "radio";
}
class RadioAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
};

void RadioAccessibilityPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void RadioAccessibilityPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: RadioAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable property of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioAccessibilityPropertyTestNg, RadioAccessibilityPropertyTestNg001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    EXPECT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());
}

/**
 * @tc.name: RadioAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsChecked property of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioAccessibilityPropertyTestNg, RadioAccessibilityPropertyTestNg002, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<NG::RadioPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    paintProperty->UpdateRadioCheck(true);
    auto accessibility = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    EXPECT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsChecked());

    paintProperty->UpdateRadioCheck(false);
    EXPECT_FALSE(accessibility->IsChecked());
}

/**
 * @tc.name: RadioAccessibilityPropertyTestNg003
 * @tc.desc: Test the Text property of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioAccessibilityPropertyTestNg, RadioAccessibilityPropertyTestNg003, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto radioEventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    EXPECT_NE(radioEventHub, nullptr);
    radioEventHub->SetValue(VALUE);

    auto accessibility = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    EXPECT_NE(accessibility, nullptr);
    EXPECT_EQ(accessibility->GetText(), VALUE);
}
} // namespace OHOS::Ace::NG
