/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "generated/test_fixtures.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_TYPE_NAME = "type";
    const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "ToggleType.Switch";
    const auto ATTRIBUTE_IS_ON_NAME = "isOn";
    const auto ATTRIBUTE_IS_ON_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_SELECTED_COLOR_NAME = "selectedColor";
    const auto ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE = "#FF007DFF";
    const auto ATTRIBUTE_SWITCH_POINT_COLOR_NAME = "switchPointColor";
    const auto ATTRIBUTE_SWITCH_POINT_COLOR_DEFAULT_VALUE = "#FFFFFFFF";
    const auto ATTRIBUTE_SWITCH_STYLE_POINT_RADIUS_NAME = "pointRadius";
    // in SDK doc: (Component height (in vp)/2) - (2 vp x Component height (in vp)/20 vp)
    // in ace_engine: (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2) / 2 - 2.0_vp
    const auto ATTRIBUTE_SWITCH_STYLE_POINT_RADIUS_DEFAULT_VALUE = "3.00vp";
    const auto ATTRIBUTE_SWITCH_STYLE_UNSELECTED_COLOR_NAME = "unselectedColor";
    const auto ATTRIBUTE_SWITCH_STYLE_UNSELECTED_COLOR_DEFAULT_VALUE = "#337F7F7F";
    const auto ATTRIBUTE_SWITCH_STYLE_POINT_COLOR_NAME = "switchPointColor";
    const auto ATTRIBUTE_SWITCH_STYLE_POINT_COLOR_DEFAULT_VALUE = "#FFFFFFFF";
    const auto ATTRIBUTE_SWITCH_STYLE_TRACK_BORDER_RADIUS_NAME = "trackBorderRadius";
    // in SDK doc: Component height (in vp)/2
    // in ace_engine: (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2) / 2
    const auto ATTRIBUTE_SWITCH_STYLE_TRACK_BORDER_RADIUS_DEFAULT_VALUE = "5.00vp";
    const auto SWITCH_HEIGHT = 20;
    const auto SWITCH_PADDING = 5;
    const auto SWITCH_RADIUS = 7;
    const auto SELECTED_COLOR_RESOURCE = CreateResource("switch_selected_color", ResourceType::COLOR);
    const auto POINT_COLOR_RESOURCE = CreateResource("switch_point_color", ResourceType::COLOR);
    const auto POINT_RADIUS_RESOURCE = CreateResource("switch_point_radius", ResourceType::FLOAT);
    const auto TRACK_BORDER_RADIUS_RESOURCE = CreateResource("track_border_radius", ResourceType::FLOAT);
} // namespace

class ToggleModifierTest : public ModifierTestBase<GENERATED_ArkUIToggleModifier,
    &GENERATED_ArkUINodeModifiers::getToggleModifier, GENERATED_ARKUI_TOGGLE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);
        MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutor);

        auto theme = SetupThemeStyle(THEME_PATTERN_SWITCH);
        theme->SetAttr("switch_pattern_height",
            { .value = Dimension(SWITCH_HEIGHT, DimensionUnit::VP) });
        theme->SetAttr("switch_hotzone_vertical_padding",
            { .value = Dimension(SWITCH_PADDING, DimensionUnit::VP) });

        AddResource("switch_selected_color", Color::FromString("#FF007DFF"));
        AddResource("switch_point_color", Color::FromString("#FFFFFFFF"));
        AddResource("switch_unselected_color", Color::FromString("#337F7F7F"));
        AddResource("switch_point_radius", Dimension(SWITCH_RADIUS, DimensionUnit::VP));
        AddResource("track_border_radius", Dimension(SWITCH_RADIUS, DimensionUnit::VP));
        SetupTheme<SwitchTheme>();
        SetupTheme<CheckboxTheme>();
    }
};

/*
 * @tc.name: setToggleOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setToggleOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_ON_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IS_ON_DEFAULT_VALUE);
}

// Valid values for attribute 'type' of method 'setToggleOptions'
static std::vector<std::tuple<std::string, Ark_ToggleType, std::string>> setToggleOptionsTypeValidValues = {
    {"ARK_TOGGLE_TYPE_CHECKBOX", Converter::ArkValue<Ark_ToggleType>(ARK_TOGGLE_TYPE_CHECKBOX),
        "ToggleType.Checkbox"},
    {"ARK_TOGGLE_TYPE_SWITCH", Converter::ArkValue<Ark_ToggleType>(ARK_TOGGLE_TYPE_SWITCH),
        "ToggleType.Switch"},
    {"ARK_TOGGLE_TYPE_BUTTON", Converter::ArkValue<Ark_ToggleType>(ARK_TOGGLE_TYPE_BUTTON),
        "ToggleType.Button"},
};

// Valid values for attribute 'isOn' of method 'setToggleOptions'
using IsOnType = Opt_Union_Boolean_Bindable_Boolean;
static std::vector<std::tuple<std::string, IsOnType, std::string>> setToggleOptionsIsOnValidValues = {
    {"false", Converter::ArkUnion<IsOnType, Ark_Boolean>(false), "false"},
    {"true", Converter::ArkUnion<IsOnType, Ark_Boolean>(true), "true"},
};

/*
 * @tc.name: setToggleOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setToggleOptionsTestTypeValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ToggleOptions inputValueOptions;
    Ark_ToggleOptions initValueOptions;

    // Initial setup
    initValueOptions.type = std::get<1>(setToggleOptionsTypeValidValues[0]);
    initValueOptions.isOn = std::get<1>(setToggleOptionsIsOnValidValues[0]);

    // Verifying attribute's 'type'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setToggleOptionsTypeValidValues) {
        inputValueOptions.type = std::get<1>(value);
        modifier_->setToggleOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setToggleOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setToggleOptionsTestIsOnValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ToggleOptions inputValueOptions;
    Ark_ToggleOptions initValueOptions;

    // Initial setup
    initValueOptions.type = std::get<1>(setToggleOptionsTypeValidValues[0]);
    initValueOptions.isOn = std::get<1>(setToggleOptionsIsOnValidValues[0]);

    // Verifying attribute's 'isOn'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setToggleOptionsIsOnValidValues) {
        inputValueOptions.isOn = std::get<1>(value);
        modifier_->setToggleOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_ON_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'type' of method 'setToggleOptions'
static std::vector<std::tuple<std::string, Ark_ToggleType>> setToggleOptionsTypeInvalidValues = {
    {"static_cast<Ark_ToggleType>(-1)", Converter::ArkValue<Ark_ToggleType>(static_cast<Ark_ToggleType>(-1))},
};

// Invalid values for attribute 'isOn' of method 'setToggleOptions'
static std::vector<std::tuple<std::string, IsOnType>> setToggleOptionsIsOnInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<IsOnType>(Ark_Empty())},
};

/*
 * @tc.name: setToggleOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setToggleOptionsTestTypeInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ToggleOptions inputValueOptions;
    Ark_ToggleOptions initValueOptions;

    // Initial setup
    initValueOptions.type = std::get<1>(setToggleOptionsTypeValidValues[0]);
    initValueOptions.isOn = std::get<1>(setToggleOptionsIsOnValidValues[0]);

    // Verifying attribute's 'type'  values
    for (auto&& value: setToggleOptionsTypeInvalidValues) {
        inputValueOptions = initValueOptions;
        modifier_->setToggleOptions(node_, &inputValueOptions);
        inputValueOptions.type = std::get<1>(value);
        modifier_->setToggleOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        expectedStr = ATTRIBUTE_TYPE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setToggleOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setToggleOptionsTestIsOnInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ToggleOptions inputValueOptions;
    Ark_ToggleOptions initValueOptions;

    // Initial setup
    initValueOptions.type = std::get<1>(setToggleOptionsTypeValidValues[0]);
    initValueOptions.isOn = std::get<1>(setToggleOptionsIsOnValidValues[0]);

    // Verifying attribute's 'isOn'  values
    for (auto&& value: setToggleOptionsIsOnInvalidValues) {
        inputValueOptions = initValueOptions;
        modifier_->setToggleOptions(node_, &inputValueOptions);
        inputValueOptions.isOn = std::get<1>(value);
        modifier_->setToggleOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_ON_NAME);
        expectedStr = ATTRIBUTE_IS_ON_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of ToggleModifierTest.setOnChange
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<SwitchEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool isOn;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Boolean_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Boolean value) {
            checkEvent = {
                .nodeId = nodeId,
                .isOn = Converter::Convert<bool>(value)
            };
        }
    };
    auto optCallback = Converter::ArkValue<Opt_Callback_Boolean_Void>(arkCallback);
    modifier_->setOnChange(node_, &optCallback);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->UpdateChangeEvent(true);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->isOn);

    eventHub->UpdateChangeEvent(false);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_FALSE(checkEvent->isOn);
}

/*
 * @tc.name: DISABLED_setContentModifierTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setContentModifierTest, TestSize.Level1)
{
    // CustomObjects is not implemented yet!
}

/*
 * @tc.name: setSelectedColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSelectedColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'selectedColor' of method 'selectedColor'
static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> selectedColorValidValues = {
    { "#FF0000FF", Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
    { "#FF123456", Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Color::TRANSPARENT.ToString(), Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0.5f),
        Color::TRANSPARENT.ToString() },
    { "#11223344", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { "#FF00FFFF", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { "#FF007DFF", Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(SELECTED_COLOR_RESOURCE), "#FF007DFF" }
};

/*
 * @tc.name: setSelectedColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSelectedColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_ResourceColor inputValueSelectedColor;
    Opt_ResourceColor initValueSelectedColor;

    // Initial setup
    initValueSelectedColor = std::get<1>(selectedColorValidValues[0]);

    // Verifying attribute's  values
    inputValueSelectedColor = initValueSelectedColor;
    for (auto&& value: selectedColorValidValues) {
        inputValueSelectedColor = std::get<1>(value);
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>>
    selectedColorInvalidValues = {
    { "", Converter::ArkUnion<Opt_ResourceColor, Ark_String>(""), "#FF007DFF" },
    { "incorrect_color", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("incorrect_color"), "#FF007DFF" }
};

/*
 * @tc.name: setSelectedColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSelectedColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_ResourceColor inputValueSelectedColor;
    Opt_ResourceColor initValueSelectedColor;

    // Initial setup
    initValueSelectedColor = std::get<1>(selectedColorValidValues[0]);

    // Verifying attribute's  values
    inputValueSelectedColor = initValueSelectedColor;
    for (auto&& value: selectedColorInvalidValues) {
        inputValueSelectedColor = std::get<1>(value);
        modifier_->setSelectedColor(node_, &inputValueSelectedColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setSwitchPointColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSwitchPointColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_POINT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SWITCH_POINT_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'switchPointColorColor' of method 'switchPointColor'
static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> switchPointColorValidValues = {
    { "#FF0000FF", Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
    { "#FF123456", Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Color::TRANSPARENT.ToString(), Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0.5f),
        Color::TRANSPARENT.ToString() },
    { "#11223344", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { "#FF00FFFF", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { "#FFFFFFFF", Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(POINT_COLOR_RESOURCE), "#FFFFFFFF" }
};

/*
 * @tc.name: setSwitchPointColorTestValidValues
 * @tc.desc: Test for ToggleType::SWITCH only
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSwitchPointColorTestValidValues, TestSize.Level1)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(GetId(), ToggleType::SWITCH, false);
    Ark_NodeHandle node = reinterpret_cast<Ark_NodeHandle>(AceType::RawPtr(frameNode));

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_ResourceColor inputValueSwitchPointColor;
    Opt_ResourceColor initValueSwitchPointColor;

    // Initial setup
    initValueSwitchPointColor = std::get<1>(switchPointColorValidValues[0]);

    // Verifying attribute's  values
    inputValueSwitchPointColor = initValueSwitchPointColor;
    for (auto&& value: switchPointColorValidValues) {
        inputValueSwitchPointColor = std::get<1>(value);
        modifier_->setSwitchPointColor(node, &inputValueSwitchPointColor);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_POINT_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>>
    switchPointColorInvalidValues = {
    { "", Converter::ArkUnion<Opt_ResourceColor, Ark_String>(""),
        ATTRIBUTE_SWITCH_POINT_COLOR_DEFAULT_VALUE },
    { "incorrect_color",  Converter::ArkUnion<Opt_ResourceColor, Ark_String>("incorrect_color"),
        ATTRIBUTE_SWITCH_POINT_COLOR_DEFAULT_VALUE }
};

/*
 * @tc.name: setSwitchPointColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSwitchPointColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_ResourceColor inputValueSwitchPointColor;
    Opt_ResourceColor initValueSwitchPointColor;

    // Initial setup
    initValueSwitchPointColor = std::get<1>(switchPointColorValidValues[0]);

    // Verifying attribute's  values
    inputValueSwitchPointColor = initValueSwitchPointColor;
    for (auto&& value: switchPointColorInvalidValues) {
        inputValueSwitchPointColor = std::get<1>(value);
        modifier_->setSwitchPointColor(node_, &inputValueSwitchPointColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_POINT_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setSwitchStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSwitchStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> resultSwitchStyle = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSwitchStyle, ATTRIBUTE_SWITCH_STYLE_POINT_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SWITCH_STYLE_POINT_RADIUS_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultSwitchStyle, ATTRIBUTE_SWITCH_STYLE_UNSELECTED_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SWITCH_STYLE_UNSELECTED_COLOR_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultSwitchStyle, ATTRIBUTE_SWITCH_STYLE_POINT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SWITCH_STYLE_POINT_COLOR_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultSwitchStyle, ATTRIBUTE_SWITCH_STYLE_TRACK_BORDER_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SWITCH_STYLE_TRACK_BORDER_RADIUS_DEFAULT_VALUE);
}

// Valid values for attribute 'pointRadius' of method 'switchStyle'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource, std::string>>
    switchStylePointRadiusValidValues = {
    { "55.50vp", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(55.5), "55.50vp" },
    { "7.00vp", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(POINT_RADIUS_RESOURCE), "7.00vp" }
};

/*
 * @tc.name: setSwitchStyleTestPointRadiusValidValues
 * @tc.desc: Test for ToggleType::SWITCH only
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setSwitchStyleTestPointRadiusValidValues, TestSize.Level1)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(GetId(), ToggleType::SWITCH, false);
    Ark_NodeHandle node = reinterpret_cast<Ark_NodeHandle>(AceType::RawPtr(frameNode));

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SwitchStyle inputValueSwitchStyle;
    Ark_SwitchStyle initValueSwitchStyle;

    // Initial setup
    initValueSwitchStyle.pointRadius = std::get<1>(switchStylePointRadiusValidValues[0]);

    // Verifying attribute's 'pointRadius'  values
    inputValueSwitchStyle = initValueSwitchStyle;
    for (auto&& value: switchStylePointRadiusValidValues) {
        inputValueSwitchStyle.pointRadius = std::get<1>(value);
        Opt_SwitchStyle optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node, &optStyle);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_STYLE_POINT_RADIUS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Valid values for attribute 'unselectedColor' of method 'switchStyle'
static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> switchStyleUnselectedColorValidValues = {
    { "#FF0000FF", Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
    { "#FF123456", Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Color::TRANSPARENT.ToString(), Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0.5f),
        Color::TRANSPARENT.ToString() },
    { "#11223344", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { "#FF00FFFF", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { "#FFFFFFFF", Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(POINT_COLOR_RESOURCE), "#FFFFFFFF" }
};

/*
 * @tc.name: setSwitchStyleTestUnselectedColorValidValues
 * @tc.desc: Test for ToggleType::SWITCH only
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSwitchStyleTestUnselectedColorValidValues, TestSize.Level1)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(GetId(), ToggleType::SWITCH, false);
    Ark_NodeHandle node = reinterpret_cast<Ark_NodeHandle>(AceType::RawPtr(frameNode));

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SwitchStyle inputValueSwitchStyle;
    Ark_SwitchStyle initValueSwitchStyle;

    // Initial setup
    initValueSwitchStyle.unselectedColor = std::get<1>(switchStyleUnselectedColorValidValues[0]);

    // Verifying attribute's 'unselectedColor'  values
    inputValueSwitchStyle = initValueSwitchStyle;
    for (auto&& value: switchStyleUnselectedColorValidValues) {
        inputValueSwitchStyle.unselectedColor = std::get<1>(value);
        auto optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node, &optStyle);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_STYLE_UNSELECTED_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Valid values for attribute 'pointColor' of method 'switchStyle'
static std::vector<std::tuple<std::string, Opt_ResourceColor, std::string>> switchStylePointColorValidValues = {
    { "#FF0000FF", Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
    { "#FF123456", Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Color::TRANSPARENT.ToString(), Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0.5f),
        Color::TRANSPARENT.ToString() },
    { "#11223344", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { "#FF00FFFF", Converter::ArkUnion<Opt_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { "#FFFFFFFF", Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(POINT_COLOR_RESOURCE), "#FFFFFFFF" }
};

/*
 * @tc.name: setSwitchStyleTestPointColorValidValues
 * @tc.desc: Test for ToggleType::SWITCH only
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSwitchStyleTestPointColorValidValues, TestSize.Level1)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(GetId(), ToggleType::SWITCH, false);
    Ark_NodeHandle node = reinterpret_cast<Ark_NodeHandle>(AceType::RawPtr(frameNode));

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SwitchStyle inputValueSwitchStyle;
    Ark_SwitchStyle initValueSwitchStyle;

    // Initial setup
    initValueSwitchStyle.pointColor = std::get<1>(switchStylePointColorValidValues[0]);

    // Verifying attribute's 'pointColor'  values
    inputValueSwitchStyle = initValueSwitchStyle;
    for (auto&& value: switchStylePointColorValidValues) {
        inputValueSwitchStyle.pointColor = std::get<1>(value);
        auto optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node, &optStyle);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_STYLE_POINT_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Valid values for attribute 'trackBorderRadius' of method 'switchStyle'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource, std::string>>
    switchStyleTrackBorderRadiusValidValues = {
    { "55.50vp", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(55.5), "55.50vp" },
    { "7.00vp", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(TRACK_BORDER_RADIUS_RESOURCE), "7.00vp" }
};

/*
 * @tc.name: setSwitchStyleTestTrackBorderRadiusValidValues
 * @tc.desc: Test for ToggleType::SWITCH only
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setSwitchStyleTestTrackBorderRadiusValidValues, TestSize.Level1)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(GetId(), ToggleType::SWITCH, false);
    Ark_NodeHandle node = reinterpret_cast<Ark_NodeHandle>(AceType::RawPtr(frameNode));

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SwitchStyle inputValueSwitchStyle;
    Ark_SwitchStyle initValueSwitchStyle;

    // Initial setup
    initValueSwitchStyle.trackBorderRadius = std::get<1>(switchStyleTrackBorderRadiusValidValues[0]);

    // Verifying attribute's 'trackBorderRadius'  values
    inputValueSwitchStyle = initValueSwitchStyle;
    for (auto&& value: switchStyleTrackBorderRadiusValidValues) {
        inputValueSwitchStyle.trackBorderRadius = std::get<1>(value);
        auto optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node, &optStyle);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_STYLE_TRACK_BORDER_RADIUS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'pointRadius' of method 'switchStyle'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource>> switchStylePointRadiusInvalidValues = {
    { "Ark_Empty()", Converter::ArkUnion<Opt_Union_F64_Resource>(Ark_Empty()) },
    { "nullptr", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr) },
};

/*
 * @tc.name: setSwitchStyleTestPointRadiusInvalidValues
 * @tc.desc: Test for ToggleType::SWITCH only
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setSwitchStyleTestPointRadiusInvalidValues, TestSize.Level1)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(GetId(), ToggleType::SWITCH, false);
    Ark_NodeHandle node = reinterpret_cast<Ark_NodeHandle>(AceType::RawPtr(frameNode));

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SwitchStyle inputValueSwitchStyle;
    Ark_SwitchStyle initValueSwitchStyle;

    // Initial setup
    initValueSwitchStyle.pointRadius = std::get<1>(switchStylePointRadiusValidValues[0]);

    // Verifying attribute's 'pointRadius'  values
    for (auto&& value: switchStylePointRadiusInvalidValues) {
        inputValueSwitchStyle = initValueSwitchStyle;
        auto optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node, &optStyle);
        inputValueSwitchStyle.pointRadius = std::get<1>(value);
        optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node, &optStyle);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_STYLE_POINT_RADIUS_NAME);
        expectedStr = ATTRIBUTE_SWITCH_STYLE_POINT_RADIUS_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'unselectedColor' of method 'switchStyle'
static std::vector<std::tuple<std::string, Opt_ResourceColor>> switchStyleUnselectedColorInvalidValues = {
    { "Ark_Empty()", Converter::ArkUnion<Opt_ResourceColor>(Ark_Empty()) },
    { "nullptr", Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr) },
};

/*
 * @tc.name: setSwitchStyleTestUnselectedColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSwitchStyleTestUnselectedColorInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SwitchStyle inputValueSwitchStyle;
    Ark_SwitchStyle initValueSwitchStyle;

    // Initial setup
    initValueSwitchStyle.unselectedColor = std::get<1>(switchStyleUnselectedColorValidValues[0]);

    // Verifying attribute's 'unselectedColor'  values
    for (auto&& value: switchStyleUnselectedColorInvalidValues) {
        inputValueSwitchStyle = initValueSwitchStyle;
        auto optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node_, &optStyle);
        inputValueSwitchStyle.unselectedColor = std::get<1>(value);
        optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node_, &optStyle);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_STYLE_UNSELECTED_COLOR_NAME);
        expectedStr = ATTRIBUTE_SWITCH_STYLE_UNSELECTED_COLOR_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'pointColor' of method 'switchStyle'
static std::vector<std::tuple<std::string, Opt_ResourceColor>> switchStylePointColorInvalidValues = {
    { "Ark_Empty()", Converter::ArkUnion<Opt_ResourceColor>(Ark_Empty()) },
    { "nullptr", Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr) },
};

/*
 * @tc.name: setSwitchStyleTestPointColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, DISABLED_setSwitchStyleTestPointColorInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SwitchStyle inputValueSwitchStyle;
    Ark_SwitchStyle initValueSwitchStyle;

    // Initial setup
    initValueSwitchStyle.pointColor = std::get<1>(switchStylePointColorValidValues[0]);

    // Verifying attribute's 'pointColor'  values
    for (auto&& value: switchStylePointColorInvalidValues) {
        inputValueSwitchStyle = initValueSwitchStyle;
        auto optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node_, &optStyle);
        inputValueSwitchStyle.pointColor = std::get<1>(value);
        optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node_, &optStyle);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_STYLE_POINT_COLOR_NAME);
        expectedStr = ATTRIBUTE_SWITCH_STYLE_POINT_COLOR_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'trackBorderRadius' of method 'switchStyle'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource>> switchStyleTrackBorderRadiusInvalidValues = {
    { "Ark_Empty()", Converter::ArkUnion<Opt_Union_F64_Resource>(Ark_Empty()) },
    { "nullptr", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr) },
};

/*
 * @tc.name: setSwitchStyleTestTrackBorderRadiusInvalidValues
 * @tc.desc: Test for ToggleType::SWITCH only
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setSwitchStyleTestTrackBorderRadiusInvalidValues, TestSize.Level1)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(GetId(), ToggleType::SWITCH, false);
    Ark_NodeHandle node = reinterpret_cast<Ark_NodeHandle>(AceType::RawPtr(frameNode));

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_SwitchStyle inputValueSwitchStyle;
    Ark_SwitchStyle initValueSwitchStyle;

    // Initial setup
    initValueSwitchStyle.trackBorderRadius = std::get<1>(switchStyleTrackBorderRadiusValidValues[0]);

    // Verifying attribute's 'trackBorderRadius'  values
    for (auto&& value: switchStyleTrackBorderRadiusInvalidValues) {
        inputValueSwitchStyle = initValueSwitchStyle;
        auto optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node, &optStyle);
        inputValueSwitchStyle.trackBorderRadius = std::get<1>(value);
        optStyle = Converter::ArkValue<Opt_SwitchStyle>(inputValueSwitchStyle);
        modifier_->setSwitchStyle(node, &optStyle);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SWITCH_STYLE_TRACK_BORDER_RADIUS_NAME);
        expectedStr = ATTRIBUTE_SWITCH_STYLE_TRACK_BORDER_RADIUS_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventIsOnImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ToggleModifierTest, setOnChangeEventIsOnImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<SwitchEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        bool value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Boolean parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::Convert<bool>(parameter)
        };
    };

    Callback_Boolean_Void arkCallback = Converter::ArkValue<Callback_Boolean_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_isOn(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->UpdateChangeEvent(true);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, true);
    eventHub->UpdateChangeEvent(false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
}
#endif

} // namespace OHOS::Ace::NG
