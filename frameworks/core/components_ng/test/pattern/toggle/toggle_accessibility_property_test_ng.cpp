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

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

#define private public
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#undef private

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class ToggleAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ToggleAccessibilityPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void ToggleAccessibilityPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: ToggleAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable and IsChecked properties of ToggleButton.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleAccessibilityPropertyTestNg, ToggleAccessibilityPropertyTestNg001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::BUTTON, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibility = frameNode->GetAccessibilityProperty<ToggleButtonAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());
    EXPECT_TRUE(accessibility->IsChecked());

    auto paintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(false);
    EXPECT_FALSE(accessibility->IsChecked());
}

/**
 * @tc.name: ToggleAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsCheckable and IsChecked properties of Switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleAccessibilityPropertyTestNg, ToggleAccessibilityPropertyTestNg002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibility = frameNode->GetAccessibilityProperty<SwitchAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());

    auto pattern = AceType::DynamicCast<SwitchPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    pattern->isOn_ = false;
    EXPECT_FALSE(accessibility->IsChecked());

    pattern->isOn_ = true;
    EXPECT_TRUE(accessibility->IsChecked());
}
} // namespace OHOS::Ace::NG
