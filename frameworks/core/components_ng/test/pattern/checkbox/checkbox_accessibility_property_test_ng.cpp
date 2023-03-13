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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "checkbox";
const std::string GROUP_NAME = "checkboxGroup";
const std::string TAG = "CHECKBOX_TAG";
} // namespace

class CheckBoxAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CheckBoxAccessibilityPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}
void CheckBoxAccessibilityPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}
void CheckBoxAccessibilityPropertyTestNg::SetUp() {}
void CheckBoxAccessibilityPropertyTestNg::TearDown() {}

/**
 * @tc.name: CheckBoxAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable property of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxAccessibilityPropertyTestNg, CheckBoxAccessibilityPropertyTestNg001, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxAccessibilityProperty>();
    EXPECT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->IsCheckable());
}

/**
 * @tc.name: CheckBoxAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsChecked property of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxAccessibilityPropertyTestNg, CheckBoxAccessibilityPropertyTestNg002, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    paintProperty->UpdateCheckBoxSelect(true);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxAccessibilityProperty>();
    EXPECT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->IsChecked());

    paintProperty->UpdateCheckBoxSelect(false);
    EXPECT_FALSE(accessibilityProperty->IsChecked());
}

/**
 * @tc.name: CheckBoxAccessibilityPropertyTestNg003
 * @tc.desc: Test the GetText property of CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxAccessibilityPropertyTestNg, CheckBoxAccessibilityPropertyTestNg003, TestSize.Level1)
{
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.Create(NAME, GROUP_NAME, TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<CheckBoxAccessibilityProperty>();
    EXPECT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), NAME);
}
} // namespace OHOS::Ace::NG
