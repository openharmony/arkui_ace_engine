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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components/button/button_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr Color SELECTED_COLOR = Color(0XFFFF0000);
constexpr Color BACKGROUND_COLOR = Color(0XFFFF0000);
const char TOGGLE_ETS_TAG[] = "Toggle";
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;
} // namespace

struct TestProperty {
    std::optional<bool> isOn = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
};

class ToggleButtonPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<FrameNode> CreateToggleButtonFrameNode(const TestProperty& testProperty);
};

void ToggleButtonPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ButtonTheme>()));
}

void ToggleButtonPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> ToggleButtonPatternTestNg::CreateToggleButtonFrameNode(const TestProperty& testProperty)
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
        toggleButtonModelNG.SetBackgroundColor(testProperty.backgroundColor.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: ToggleButtonPatternTest001
 * @tc.desc: Test all the properties of bubble.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButtonPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of bubble.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    testProperty.selectedColor = std::make_optional(SELECTED_COLOR);
    testProperty.backgroundColor = std::make_optional(BACKGROUND_COLOR);

    /**
     * @tc.steps: step2. create list frameNode and get LayoutProperty and paintProperty.
     * @tc.expected: step2. get paintProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    EXPECT_FALSE(frameNode == nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    EXPECT_FALSE(pattern == nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    auto toggleButtonEventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(toggleButtonEventHub);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
    EXPECT_EQ(paintProperty->GetBackgroundColor(), BACKGROUND_COLOR);
}

/**
 * @tc.name: ToggleButtonPatternTest002
 * @tc.desc: test toggleButton pattern OnModifyDone .
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButtonPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    testProperty.selectedColor = std::make_optional(SELECTED_COLOR);
    testProperty.backgroundColor = std::make_optional(BACKGROUND_COLOR);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    EXPECT_FALSE(togglePattern == nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. pattern OnModifyDone and OnClick.
     * @tc.expected: step3. check whether the function is executed successfully.
     */
    togglePattern->isOn_ = false;
    togglePattern->OnModifyDone();
}

/**
 * @tc.name: ToggleButtonPatternTest003
 * @tc.desc: test toggleButton pattern OnModifyDone and onClick.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonPatternTestNg, ToggleButtonPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    EXPECT_FALSE(togglePattern == nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    paintProperty->UpdateSelectedColor(SELECTED_COLOR);
    paintProperty->UpdateBackgroundColor(BACKGROUND_COLOR);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. pattern OnModifyDone and OnClick.
     * @tc.expected: step3. check whether the function is executed successfully.
     */
    togglePattern->OnModifyDone();
    togglePattern->OnClick();
    layoutProperty->UpdateAlignment(ALIGNMENT);
    EXPECT_EQ(ALIGNMENT, layoutProperty->GetPositionProperty()->GetAlignmentValue());

    // update isOn value
    togglePattern->isOn_ = false;
    togglePattern->OnModifyDone();
    paintProperty->UpdateIsOn(false);
    togglePattern->OnClick();
}
} // namespace OHOS::Ace::NG