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
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"

#define private public
#include "base/geometry/dimension.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr Color SELECTED_COLOR = Color(0XFFFF0000);
constexpr Color SWITCH_POINT_COLOR = Color(0XFFFFFF00);
constexpr Color BACKGROUND_COLOR = Color(0XFFFF0000);
constexpr Dimension LENGTH = 0.0_px;
constexpr Dimension TOGGLE_WIDTH = 60.0_px;
constexpr Dimension TOGGLE_HEIGH = 20.0_px;
const std::vector<NG::ToggleType> TOGGLE_TYPE = { ToggleType::CHECKBOX, ToggleType::BUTTON, ToggleType::SWITCH };
} // namespace

class TogglePatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void TogglePatternTestNg::SetUp() {}
void TogglePatternTestNg::TearDown() {}

PaddingPropertyF TogglePatternTestNg::CreatePadding(Dimension length)
{
    PaddingPropertyF padding;
    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return padding;
}

/**
 * @tc.name: TogglePatternTest001
 * @tc.desc: test the process of toggle created with checkbox.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    auto checkBoxFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(checkBoxFrameNode == nullptr);
    EXPECT_EQ(checkBoxFrameNode->GetTag(), V2::CHECKBOX_ETS_TAG);

    /**
     * @tc.steps: step2.get checkBox property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<CheckBoxPattern>(checkBoxFrameNode->GetPattern());
    EXPECT_FALSE(pattern == nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxSelect(), IS_ON);
    EXPECT_EQ(paintProperty->GetCheckBoxSelectedColor(), SELECTED_COLOR);
    ViewStackProcessor::GetInstance()->ClearStack();

    // update different toggle type
    for (size_t i = 0; i < TOGGLE_TYPE.size(); ++i) {
        ToggleModelNG toggleModelNG;
        toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);

        auto isOn = i % 2 == 0 ? true : false;
        toggleModelNG.Create(TOGGLE_TYPE[i], isOn);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_FALSE(frameNode == nullptr);

        auto pattern = frameNode->GetPattern();
        EXPECT_FALSE(pattern == nullptr);
        if (AceType::InstanceOf<CheckBoxPattern>(pattern)) {
            auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
            EXPECT_FALSE(paintProperty == nullptr);
            EXPECT_EQ(paintProperty->GetCheckBoxSelect(), isOn);
        }
        if (AceType::InstanceOf<SwitchPattern>(pattern)) {
            auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
            EXPECT_FALSE(paintProperty == nullptr);
            EXPECT_EQ(paintProperty->GetIsOn(), isOn);
        }
        if (AceType::InstanceOf<ToggleButtonPattern>(pattern)) {
            auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
            EXPECT_FALSE(paintProperty == nullptr);
            EXPECT_EQ(paintProperty->GetIsOn(), isOn);
        }
        ViewStackProcessor::GetInstance()->ClearStack();
    }
}

/**
 * @tc.name: TogglePatternTest002
 * @tc.desc: test the process of toggle created with button.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(buttonFrameNode == nullptr);
    EXPECT_EQ(buttonFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);

    /**
     * @tc.steps: step2.get button property and check whether the property value is correct.
     */
    auto paintProperty = buttonFrameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
}

/**
 * @tc.name: TogglePatternTest003
 * @tc.desc: test the process of toggle created with switch.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    toggleModelNG.SetSwitchPointColor(SWITCH_POINT_COLOR);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(switchFrameNode == nullptr);
    EXPECT_EQ(switchFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    EXPECT_EQ(toggleModelNG.IsToggle(), false);

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_FALSE(pattern == nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
    EXPECT_EQ(paintProperty->GetSwitchPointColor(), SWITCH_POINT_COLOR);
}

/**
 * @tc.name: TogglePatternTest004
 * @tc.desc: test toggle created SetWidth SetHeight SetBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    toggleModelNG.SetWidth(TOGGLE_WIDTH);
    toggleModelNG.SetHeight(TOGGLE_HEIGH);
    toggleModelNG.SetBackgroundColor(BACKGROUND_COLOR);
    auto padding = CreatePadding(LENGTH);
    toggleModelNG.SetPadding(padding);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(buttonFrameNode == nullptr);
    EXPECT_EQ(buttonFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);

    /**
     * @tc.steps: step2.get button property and check whether the property value is correct.
     */
    auto paintProperty = buttonFrameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_FALSE(paintProperty == nullptr);
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
    EXPECT_EQ(paintProperty->GetBackgroundColor(), BACKGROUND_COLOR);
}

/**
 * @tc.name: TogglePatternTest005
 * @tc.desc: Test event function of toggle with checkbox.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto checkBoxFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(checkBoxFrameNode == nullptr);
    EXPECT_EQ(checkBoxFrameNode->GetTag(), V2::CHECKBOX_ETS_TAG);
    auto eventHub = checkBoxFrameNode->GetEventHub<CheckBoxEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->UpdateChangeEvent(false);
    EXPECT_EQ(stateChange, false);

    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(stateChange, true);
}

/**
 * @tc.name: TogglePatternTest006
 * @tc.desc: Test event function of toggle with button.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(buttonFrameNode == nullptr);
    EXPECT_EQ(buttonFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    auto eventHub = buttonFrameNode->GetEventHub<ToggleButtonEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->UpdateChangeEvent(false);
    EXPECT_EQ(stateChange, false);

    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(stateChange, true);
}

/**
 * @tc.name: TogglePatternTest007
 * @tc.desc: Test event function of toggle with switch.
 * @tc.type: FUNC
 */
HWTEST_F(TogglePatternTestNg, TogglePatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    toggleModelNG.SetSelectedColor(SELECTED_COLOR);
    toggleModelNG.SetSwitchPointColor(SWITCH_POINT_COLOR);

    /**
     * @tc.steps: step2. set toggle event.
     * @tc.expected: step2. function is called.
     */
    bool stateChange = true;
    auto onChange = [&stateChange](bool flag) { stateChange = flag; };
    toggleModelNG.OnChange(onChange);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(switchFrameNode == nullptr);
    EXPECT_EQ(switchFrameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    auto eventHub = switchFrameNode->GetEventHub<SwitchEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->UpdateChangeEvent(true);
    EXPECT_EQ(stateChange, true);
}
} // namespace OHOS::Ace::NG