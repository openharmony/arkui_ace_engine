/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"
#define protected public
#define private public

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/button/button_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_model_static.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "test/mock/base/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr Color SELECTED_COLOR = Color(0XFFFF0000);
constexpr Color BACKGROUND_COLOR = Color(0XFFFF0000);
const char TOGGLE_ETS_TAG[] = "Toggle";
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;
const double dimensionValue = 1.0;
const double childDimensionValue = 5.0;
constexpr float HOVER_OPACITY = 0.05f;
constexpr int32_t TOUCH_DURATION = 250;
constexpr bool STATE_EFFECT = false;
} // namespace

struct TestProperty {
    std::optional<bool> isOn = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
};

class ToggleButtonStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<FrameNode> CreateToggleButtonFrameNode(const TestProperty& testProperty);
};

void ToggleButtonStaticTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ButtonTheme>()));
}

void ToggleButtonStaticTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> ToggleButtonStaticTestNg::CreateToggleButtonFrameNode(const TestProperty& testProperty)
{
    ToggleButtonModelNG toggleButtonModelNG;
    toggleButtonModelNG.Create(TOGGLE_ETS_TAG);
    if (testProperty.isOn.has_value()) {
        toggleButtonModelNG.SetIsOn(testProperty.isOn.value());
    }
    if (testProperty.selectedColor.has_value()) {
        toggleButtonModelNG.SetSelectedColor(testProperty.selectedColor.value());
    }
    if (testProperty.backgroundColor.has_value()) {
        toggleButtonModelNG.SetBackgroundColor(testProperty.backgroundColor.value(), true);
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: ToggleButtonStaticTestNg001
 * @tc.desc: test toggleButton SetOnChange.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonStaticTestNg, ToggleButtonStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of bubble.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    testProperty.selectedColor = std::make_optional(SELECTED_COLOR);
    testProperty.backgroundColor = std::make_optional(BACKGROUND_COLOR);

    /**
     * @tc.steps: step2. create list frameNode and get paintProperty.
     * @tc.expected: step2. get paintProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSelectedColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> selectedColor = std::nullopt;
    ToggleButtonModelStatic::SetSelectedColor(frameNode, selectedColor);
    EXPECT_EQ(paintProperty->GetSelectedColor(), std::nullopt);
    selectedColor = SELECTED_COLOR;
    ToggleButtonModelStatic::SetSelectedColor(frameNode, selectedColor);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
}
} // namespace OHOS::Ace::NG
