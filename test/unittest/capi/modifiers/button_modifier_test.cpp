/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components/button/button_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
    // attrs
    const auto ATTRIBUTE_LABEL_NAME("label");
    const auto ATTRIBUTE_TYPE_NAME("type");
    const auto ATTRIBUTE_ROLE_NAME("role");
    const auto ATTRIBUTE_STATE_EFFECT_NAME("stateEffect");
    const auto ATTRIBUTE_CONTROL_SIZE_NAME("controlSize");
    const auto ATTRIBUTE_BUTTON_STYLE_NAME("buttonStyle");
    const auto ATTRIBUTE_FONT_COLOR_NAME("fontColor");
    const auto ATTRIBUTE_FONT_SIZE_NAME("fontSize");
    const auto ATTRIBUTE_FONT_WEIGHT_NAME("fontWeight");
    const auto ATTRIBUTE_FONT_STYLE_NAME("fontStyle");
    const auto ATTRIBUTE_FONT_FAMILY_NAME("fontFamily");
    const auto ATTRIBUTE_LABEL_STYLE_NAME = "labelStyle";
    const auto ATTRIBUTE_LABEL_STYLE_OVERFLOW_NAME = "overflow";
    const auto ATTRIBUTE_LABEL_STYLE_MAX_LINES_NAME = "maxLines";
    const auto ATTRIBUTE_LABEL_STYLE_MIN_FONT_SIZE_NAME = "minFontSize";
    const auto ATTRIBUTE_LABEL_STYLE_MAX_FONT_SIZE_NAME = "maxFontSize";
    const auto ATTRIBUTE_LABEL_STYLE_MIN_FONT_SCALE_NAME = "minFontScale";
    const auto ATTRIBUTE_LABEL_STYLE_MAX_FONT_SCALE_NAME = "maxFontScale";
    const auto ATTRIBUTE_LABEL_STYLE_HEIGHT_ADAPTIVE_POLICY_NAME = "heightAdaptivePolicy";
    const auto ATTRIBUTE_LABEL_STYLE_FONT_NAME = "font";
    const auto ATTRIBUTE_LABEL_STYLE_FONT_SIZE_NAME("size");
    const auto ATTRIBUTE_LABEL_STYLE_FONT_WEIGHT_NAME("weight");
    const auto ATTRIBUTE_LABEL_STYLE_FONT_STYLE_NAME("style");
    const auto ATTRIBUTE_LABEL_STYLE_FONT_FAMILY_NAME("family");

    // default values
    const auto ATTRIBUTE_TYPE_DEFAULT_VALUE("ButtonType.Capsule");
    const auto ATTRIBUTE_ROLE_DEFAULT_VALUE("ButtonRole.NORMAL");
    const auto ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE("true");
    const auto ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE("ControlSize.NORMAL");
    const auto ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE("ButtonStyleMode.EMPHASIZED");
    const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE("#FF000000");
    const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE("0.00px");
    const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE("FontWeight.Medium");
    const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE("FontStyle.Normal");
    const auto ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE("0.850000");
    const auto ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE("2147483648.000000");

    // typedefs
    using ButtonTypeTest = std::pair<Ark_ButtonType, std::string>;
    using ButtonRoleTest = std::pair<Ark_ButtonRole, std::string>;
    using ButtonControlSizeTest = std::pair<Ark_ControlSize, std::string>;
    using ButtonStyleModeTest = std::pair<Ark_ButtonStyleMode, std::string>;
    using BoolTest = std::pair<Ark_Boolean, std::string>;
    // test plans
    const std::vector<ButtonTypeTest> BUTTON_TYPE_TEST_PLAN = {
        { ARK_BUTTON_TYPE_NORMAL, "ButtonType.Normal" },
        { ARK_BUTTON_TYPE_CAPSULE, "ButtonType.Capsule" },
        { ARK_BUTTON_TYPE_CIRCLE, "ButtonType.Circle" },
        { ARK_BUTTON_TYPE_ROUNDED_RECTANGLE, "ButtonType.ROUNDED_RECTANGLE" },
        // Invalid values shouldn't change options
        { static_cast<Ark_ButtonType>(-100), "ButtonType.Capsule" },
        { static_cast<Ark_ButtonType>(100), "ButtonType.Capsule" }
    };
    const std::vector<ButtonRoleTest> BUTTON_ROLE_TEST_PLAN = {
        { ARK_BUTTON_ROLE_NORMAL, "ButtonRole.NORMAL" },
        { ARK_BUTTON_ROLE_ERROR, "ButtonRole.ERROR" },
        // Invalid values shouldn't change options
        { static_cast<Ark_ButtonRole>(-100), "ButtonRole.NORMAL" },
        { static_cast<Ark_ButtonRole>(100), "ButtonRole.NORMAL" }
    };
    const std::vector<ButtonControlSizeTest> BUTTON_CONTROL_SIZE_TEST_PLAN = {
        { ARK_CONTROL_SIZE_NORMAL, "ControlSize.NORMAL" },
        { ARK_CONTROL_SIZE_SMALL, "ControlSize.SMALL" },
        // Invalid values shouldn't change options
        { static_cast<Ark_ControlSize>(-100), "ControlSize.NORMAL" },
        { static_cast<Ark_ControlSize>(100), "ControlSize.NORMAL" }
    };
    const std::vector<ButtonStyleModeTest> BUTTON_STYLE_MODE_TEST_PLAN = {
        { ARK_BUTTON_STYLE_MODE_NORMAL, "ButtonStyleMode.NORMAL" },
        { ARK_BUTTON_STYLE_MODE_EMPHASIZED, "ButtonStyleMode.EMPHASIZED" },
        { ARK_BUTTON_STYLE_MODE_TEXTUAL, "ButtonStyleMode.TEXTUAL" },
        // Invalid values shouldn't change options
        { static_cast<Ark_ButtonStyleMode>(-100), "ButtonStyleMode.EMPHASIZED" },
        { static_cast<Ark_ButtonStyleMode>(100), "ButtonStyleMode.EMPHASIZED" }
    };
    const std::vector<BoolTest> BOOL_TEST_PLAN = {
        { false, "false" },
        { true, "true" },
        { 0, "false" },
        { -25, "true" },
        { 0, "false" },
        { 25, "true" },
        { false, "false" }
    };

using  ArkFontWeightTest = std::pair<Ark_Union_Number_FontWeight_String, std::string>;
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(100)), "100" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(200)), "200" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(300)), "300" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(400)), "400" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(500)), "500" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(600)), "600" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(700)), "700" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(800)), "800" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(900)), "900" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("lighter")), "FontWeight.Lighter" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("normal")), "FontWeight.Normal" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("regular")), "FontWeight.Regular" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("medium")), "FontWeight.Medium" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("bold")), "FontWeight.Bold" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("bolder")), "FontWeight.Bolder" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("100")), "100" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("200")), "200" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("300")), "300" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("400")), "400" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("500")), "500" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("600")), "600" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("700")), "700" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("800")), "800" },
    { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("900")), "900" },
};

// Font.fontWeight apply only FontWeight enum values
using  OptArkFontWeightTest = std::pair<Opt_Union_FontWeight_Number_String, std::string>;
const std::vector<OptArkFontWeightTest> OPT_FONT_WEIGHT_TEST_PLAN = {
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(100)), "100" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(200)), "200" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(300)), "300" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(400)), "400" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(500)), "500" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(600)), "600" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(700)), "700" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(800)), "800" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(900)), "900" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("lighter")), "FontWeight.Lighter" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("normal")), "FontWeight.Normal" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("regular")), "FontWeight.Regular" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("medium")), "FontWeight.Medium" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("bold")), "FontWeight.Bold" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("bolder")), "FontWeight.Bolder" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("100")), "100" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("200")), "200" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("300")), "300" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("400")), "400" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("500")), "500" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("600")), "600" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("700")), "700" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("800")), "800" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("900")), "900" },
};

using OptArkFontStyleTest = std::pair<Opt_FontStyle, std::string>;
const std::vector<OptArkFontStyleTest> OPT_FONT_STYLE_TEST_PLAN = {
    { ArkValue<Opt_FontStyle>(Ark_FontStyle::ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
    { ArkValue<Opt_FontStyle>(Ark_FontStyle::ARK_FONT_STYLE_ITALIC), "FontStyle.Italic" },
};
} // namespace

class ButtonModifierTest : public ModifierTestBase<GENERATED_ArkUIButtonModifier,
    &GENERATED_ArkUINodeModifiers::getButtonModifier, GENERATED_ARKUI_BUTTON> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ButtonTheme>();
    }
};

/*
 * @tc.name: setButtonOptionsTestDefaultValues
 * @tc.desc: Check default options values
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE);
}

/**
 * @tc.name: SetButtonOptions0Test
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions0
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, SetButtonOptions0Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setButtonOptions0, nullptr);
    modifier_->setButtonOptions0(node_);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto type = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto stateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto controlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto buttonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto role = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);

    EXPECT_EQ(type, ATTRIBUTE_TYPE_DEFAULT_VALUE);
    EXPECT_EQ(stateEffect, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE);
    EXPECT_EQ(controlSize, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(buttonStyle, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE);
    EXPECT_EQ(role, ATTRIBUTE_ROLE_DEFAULT_VALUE);
}
/*
 * @tc.name: SetButtonOptions1TestButtonType
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions1TestButtonType, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto type : BUTTON_TYPE_TEST_PLAN) {
        inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(type.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(checkType, type.second);
    }
}
/*
 * @tc.name: SetButtonOptions1TestStateEffect
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions1TestStateEffect, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto stateEffect : BOOL_TEST_PLAN) {
        inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(stateEffect.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        EXPECT_EQ(checkStateEffect, stateEffect.second);
    }
}
/*
 * @tc.name: SetButtonOptions1TestButtonStyleMode
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions1ButtonTypeTestButtonStyleMode, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto styleMode : BUTTON_STYLE_MODE_TEST_PLAN) {
        inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(styleMode.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        EXPECT_EQ(checkButtonStyle, styleMode.second);
    }
}
/*
 * @tc.name: SetButtonOptions1TestControlSize
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions1TestControlSize, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto controlSize : BUTTON_CONTROL_SIZE_TEST_PLAN) {
        inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(controlSize.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(checkControlSize, controlSize.second);
    }
}
/*
 * @tc.name: SetButtonOptions1TestButtonRole
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions1
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions1TestButtonRole, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    // Test
    modifier_->setButtonOptions1(node_, &inputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto role : BUTTON_ROLE_TEST_PLAN) {
        inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(role.first);
        modifier_->setButtonOptions1(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        EXPECT_EQ(checkRole, role.second);
    }
}

/*
 * @tc.name: SetButtonOptions2TestButtonType
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions2
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions2TestButtonType, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    const std::string stringValue("testString");
    auto labelString = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(stringValue);
    auto optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
    // Test
    modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    auto checkLabel = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    EXPECT_EQ(checkLabel, stringValue);

    jsonValue = GetJsonValue(node_);
    for (auto type : BUTTON_TYPE_TEST_PLAN) {
        inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(type.first);
        optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
        modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(checkType, type.second);
    }
}
/*
 * @tc.name: SetButtonOptions2TestStateEffect
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions2
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions2TestStateEffect, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    const std::string stringValue("testString");
    auto labelString = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(stringValue);
    auto optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
    // Test
    modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    auto checkLabel = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto stateEffect : BOOL_TEST_PLAN) {
        inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(stateEffect.first);
        optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
        modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        EXPECT_EQ(checkStateEffect, stateEffect.second);
    }
}
/*
 * @tc.name: SetButtonOptions2ButtonTypeTestButtonStyleMode
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions2
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions2ButtonTypeTestButtonStyleMode, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    const std::string stringValue("testString");
    auto labelString = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(stringValue);
    auto optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
    // Test
    modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto styleMode : BUTTON_STYLE_MODE_TEST_PLAN) {
        inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(styleMode.first);
        optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
        modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        EXPECT_EQ(checkButtonStyle, styleMode.second);
    }
}
/*
 * @tc.name: SetButtonOptions2TestControlSize
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions2
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions2TestControlSize, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    const std::string stringValue("testString");
    auto labelString = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(stringValue);
    auto optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
    // Test
    modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto controlSize : BUTTON_CONTROL_SIZE_TEST_PLAN) {
        inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(controlSize.first);
        optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
        modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(checkControlSize, controlSize.second);
    }
}
/*
 * @tc.name: SetButtonOptions2TestButtonRole
 * @tc.desc: Check the functionality of ButtonModifier.SetButtonOptions2
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_SetButtonOptions2TestButtonRole, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    // Initial setup
    Ark_ButtonOptions inputValueOptions;
    inputValueOptions.type = Converter::ArkValue<Opt_ButtonType>(ARK_BUTTON_TYPE_CAPSULE);
    inputValueOptions.stateEffect = Converter::ArkValue<Opt_Boolean>(true);
    inputValueOptions.buttonStyle = Converter::ArkValue<Opt_ButtonStyleMode>(ARK_BUTTON_STYLE_MODE_NORMAL);
    inputValueOptions.controlSize = Converter::ArkValue<Opt_ControlSize>(ARK_CONTROL_SIZE_SMALL);
    inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(ARK_BUTTON_ROLE_NORMAL);
    const std::string stringValue("testString");
    auto labelString = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(stringValue);
    auto optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
    // Test
    modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
    // Initial verification
    jsonValue = GetJsonValue(node_);
    auto checkType = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    auto checkStateEffect = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    auto checkButtonStyle = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    auto checkControlSize = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    auto checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(checkType, "ButtonType.Capsule");
    EXPECT_EQ(checkStateEffect, "true");
    EXPECT_EQ(checkButtonStyle, "ButtonStyleMode.NORMAL");
    EXPECT_EQ(checkControlSize, "ControlSize.SMALL");
    EXPECT_EQ(checkRole, "ButtonRole.NORMAL");
    for (auto role : BUTTON_ROLE_TEST_PLAN) {
        inputValueOptions.role = Converter::ArkValue<Opt_ButtonRole>(role.first);
        optInputValueOptions = Converter::ArkValue<Opt_ButtonOptions>(inputValueOptions);
        modifier_->setButtonOptions2(node_, &labelString, &optInputValueOptions);
        jsonValue = GetJsonValue(node_);
        checkRole = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        EXPECT_EQ(checkRole, role.second);
    }
}

/*
 * @tc.name: setTypeTestDefaultValues
 * @tc.desc: Check the functionality of ButtonModifier.setTypeTest
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE);
}

/*
 * @tc.name: setTypeTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setTypeTest
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setTypeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    const std::vector<ButtonTypeTest> testPlan = {
        { ARK_BUTTON_TYPE_NORMAL, "ButtonType.Normal" },
        { ARK_BUTTON_TYPE_CAPSULE, "ButtonType.Capsule" },
        { ARK_BUTTON_TYPE_CIRCLE, "ButtonType.Circle" },
        { ARK_BUTTON_TYPE_ROUNDED_RECTANGLE, "ButtonType.ROUNDED_RECTANGLE" }
    };
    for (const auto &[type, expectValue] : testPlan) {
        auto optType = ArkValue<Opt_ButtonType>(type);
        modifier_->setType(node_, &optType);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setTypeTestInvalidValues
 * @tc.desc: Check the functionality of ButtonModifier.setTypeTest
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setTypeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    const std::vector<ButtonTypeTest> testPlan = {
        { static_cast<Ark_ButtonType>(-100), "ButtonType.Capsule" },
        { static_cast<Ark_ButtonType>(100), "ButtonType.Capsule" }
    };
    for (const auto &[type, expectValue] : testPlan) {
        auto optType = ArkValue<Opt_ButtonType>(type);
        modifier_->setType(node_, &optType);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setStateEffectTestDefaultValues
 * @tc.desc: Check the functionality of ButtonModifier.setStateEffect
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setStateEffectTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATE_EFFECT_DEFAULT_VALUE);
}

/*
 * @tc.name: setStateEffectTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setStateEffect
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setStateEffectTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    for (const auto &[stateEffect, expectValue] : BOOL_TEST_PLAN) {
        auto optStateEffect = Converter::ArkValue<Opt_Boolean>(stateEffect);
        modifier_->setStateEffect(node_, &optStateEffect);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATE_EFFECT_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setButtonStyleTestDefaultValues
 * @tc.desc: Check the functionality of ButtonModifier.setButtonStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BUTTON_STYLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setButtonStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setButtonStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonStyleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    const std::vector<ButtonStyleModeTest> BUTTON_STYLE_MODE_TEST_PLAN = {
        { ARK_BUTTON_STYLE_MODE_NORMAL, "ButtonStyleMode.NORMAL" },
        { ARK_BUTTON_STYLE_MODE_EMPHASIZED, "ButtonStyleMode.EMPHASIZED" },
        { ARK_BUTTON_STYLE_MODE_TEXTUAL, "ButtonStyleMode.TEXTUAL" },
    };

    for (const auto &[styleMode, expectValue] : BUTTON_STYLE_MODE_TEST_PLAN) {
        auto optStyleMode = Converter::ArkValue<Opt_ButtonStyleMode>(styleMode);
        modifier_->setButtonStyle(node_, &optStyleMode);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setButtonStyleTestInvalidValues
 * @tc.desc: Check the functionality of ButtonModifier.setButtonStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setButtonStyleTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    const std::vector<ButtonStyleModeTest> BUTTON_STYLE_MODE_TEST_PLAN = {
        { static_cast<Ark_ButtonStyleMode>(-100), "ButtonStyleMode.EMPHASIZED" },
        { static_cast<Ark_ButtonStyleMode>(100), "ButtonStyleMode.EMPHASIZED" }
    };

    for (const auto &[styleMode, expectValue] : BUTTON_STYLE_MODE_TEST_PLAN) {
        auto optStyleMode = Converter::ArkValue<Opt_ButtonStyleMode>(styleMode);
        modifier_->setButtonStyle(node_, &optStyleMode);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BUTTON_STYLE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setControlSizeTestDefaultValues
 * @tc.desc: Check the functionality of ButtonModifier.setControlSize
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setControlSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROL_SIZE_DEFAULT_VALUE);
}

/*
 * @tc.name: setControlSizeTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setControlSize
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setControlSizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    const std::vector<ButtonControlSizeTest> testPlan = {
        { ARK_CONTROL_SIZE_NORMAL, "ControlSize.NORMAL" },
        { ARK_CONTROL_SIZE_SMALL, "ControlSize.SMALL" },
    };
    for (const auto &[controlSize, expectValue] : testPlan) {
        auto optControlSize = Converter::ArkValue<Opt_ControlSize>(controlSize);
        modifier_->setControlSize(node_, &optControlSize);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setControlSizeTestInvalidValues
 * @tc.desc: Check the functionality of ButtonModifier.setControlSize
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setControlSizeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    const std::vector<ButtonControlSizeTest> testPlan = {
        { static_cast<Ark_ControlSize>(-100), "ControlSize.NORMAL" },
        { static_cast<Ark_ControlSize>(100), "ControlSize.NORMAL" }
    };
    for (const auto &[controlSize, expectValue] : testPlan) {
        auto optControlSize = Converter::ArkValue<Opt_ControlSize>(controlSize);
        modifier_->setControlSize(node_, &optControlSize);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROL_SIZE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setRoleTestDefaultValues
 * @tc.desc: Check the functionality of ButtonModifier.setRole
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setRoleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setRoleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setRole
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setRoleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    const std::vector<ButtonRoleTest> testPlan = {
        { ARK_BUTTON_ROLE_NORMAL, "ButtonRole.NORMAL" },
        { ARK_BUTTON_ROLE_ERROR, "ButtonRole.ERROR" }
    };

    for (const auto &[role, expectValue] : testPlan) {
        auto optRole = Converter::ArkValue<Opt_ButtonRole>(role);
        modifier_->setRole(node_, &optRole);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setRoleTestInvalidValues
 * @tc.desc: Check the functionality of ButtonModifier.setRole
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setRoleTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    const std::vector<ButtonRoleTest> testPlan = {
        { static_cast<Ark_ButtonRole>(-100), "ButtonRole.NORMAL" },
        { static_cast<Ark_ButtonRole>(100), "ButtonRole.NORMAL" }
    };

    for (const auto &[role, expectValue] : testPlan) {
        auto optRole = Converter::ArkValue<Opt_ButtonRole>(role);
        modifier_->setRole(node_, &optRole);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROLE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setFontColorTestValidColorValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestValidColorValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        auto optResColor = Converter::ArkValue<Opt_ResourceColor>(arkResColor);
        modifier_->setFontColor(node_, &optResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontColorTestValidNumberValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestValidNumberValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffffffff), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xff000000), "#FF000000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xff0000ff), "#FF0000FF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffa52a2a), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xff808080), "#FF808080" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xff008000), "#FF008000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffffa500), "#FFFFA500" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffffc0cb), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffff0000), "#FFFF0000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffffff00), "#FFFFFF00" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x00000000), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        auto optResColor = Converter::ArkValue<Opt_ResourceColor>(arkResColor);
        modifier_->setFontColor(node_, &optResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontColorTestValidStringValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestValidStringValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#FFFFFFFF"), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ff000000"), "#FF000000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ff0000ff"), "#FF0000FF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffa52a2a"), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ff808080"), "#FF808080" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ff008000"), "#FF008000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffffa500"), "#FFFFA500" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffffc0cb"), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffff0000"), "#FFFF0000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffffff00"), "#FFFFFF00" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#00000000"), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        auto optResColor = Converter::ArkValue<Opt_ResourceColor>(arkResColor);
        modifier_->setFontColor(node_, &optResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontColorTestInvalidNumberValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestInvalidNumberValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_ResourceColor arkResColor;

    arkResColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xffffffff + 1);
    auto optResColor = Converter::ArkValue<Opt_ResourceColor>(arkResColor);
    modifier_->setFontColor(node_, &optResColor);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, "#00000000");

    arkResColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x00000000 - 1);
    optResColor = Converter::ArkValue<Opt_ResourceColor>(arkResColor);
    modifier_->setFontColor(node_, &optResColor);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, "#FFFFFFFF");
}


/*
 * @tc.name: setFontColorTestInvalidStringValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontColorTestInvalidStringValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("undefined"), ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("GGTTSSPP"), ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        auto optResColor = Converter::ArkValue<Opt_ResourceColor>(arkResColor);
        modifier_->setFontColor(node_, &optResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontSizeTestDefaultValue
 * @tc.desc: Check the functionality of setFontSizeTest
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontSizeTestDefaultValue, TestSize.Level1)
{
    auto jsonValue = GetJsonValue(node_);
    auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(result, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
}

/*
 * @tc.name: setFontSizeTestValidValues
 * @tc.desc: Check the functionality of setFontSizeTest
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontSizeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;

    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Opt_Length>(1.0f),  "1.00vp" },
        { ArkValue<Opt_Length>(2.45f), "2.45vp" },
        { ArkValue<Opt_Length>(5.0_px), "5.00px" },
        { ArkValue<Opt_Length>(22.35_px), "22.35px" },
        { ArkValue<Opt_Length>(7.0_vp), "7.00vp" },
        { ArkValue<Opt_Length>(1.65_vp), "1.65vp" },
        { ArkValue<Opt_Length>(65.0_fp), "65.00fp" },
        { ArkValue<Opt_Length>(4.3_fp), "4.30fp" },
    };

    for (const auto &[optLength, expected]: testPlan) {
        modifier_->setFontSize(node_, &optLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(result, expected);
    }
}

/*
 * @tc.name: setFontSizeTestInvalidValues
 * @tc.desc: Check the functionality of setFontSizeTest
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontSizeTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;

    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Opt_Length>("23.00%"), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
        { ArkValue<Opt_Length>(-0.1f), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
        { ArkValue<Opt_Length>(-5.0_px), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
    };

    for (const auto &[optLength, expected]: testPlan) {
        modifier_->setFontSize(node_, &optLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setFontWeightTestDefaultValue
 * @tc.desc: Check the functionality of setFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontWeightTestDefaultValue, TestSize.Level1)
{
    auto jsonValue = GetJsonValue(node_);
    auto result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(result, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
}

/**
 * @tc.name: setFontWeightTestValidValues
 * @tc.desc: Check the functionality of setFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontWeightTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight, nullptr);
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[weight, expectValue] : FONT_WEIGHT_TEST_PLAN) {
        auto optWeight = Converter::ArkValue<Opt_Union_Number_FontWeight_String>(weight);
        modifier_->setFontWeight(node_, &optWeight);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(result, expectValue);
    }
}

/**
 * @tc.name: setFontWeightTestInvalidValues
 * @tc.desc: Check the functionality of setFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontWeightTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontWeight, nullptr);
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;

    const std::vector<ArkFontWeightTest> testPlan = {
        { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_Number>(ArkValue<Ark_Number>(1000)),
            ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
        { ArkUnion<Ark_Union_Number_FontWeight_String, Ark_String>(ArkValue<Ark_String>("1000")),
            ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
    };
    for (const auto &[weight, expectValue] : testPlan) {
        auto optWeight = Converter::ArkValue<Opt_Union_Number_FontWeight_String>(weight);
        modifier_->setFontWeight(node_, &optWeight);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(result, expectValue);
    }
}

/*
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setFontStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontStyleTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    using ArkFontStyleTest = std::pair<Ark_FontStyle, std::string>;
    const std::vector<ArkFontStyleTest> testPlan = {
        { ARK_FONT_STYLE_NORMAL, "FontStyle.Normal" },
        { ARK_FONT_STYLE_ITALIC, "FontStyle.Italic" },
        { ARK_FONT_STYLE_NORMAL, "FontStyle.Normal" },
    };

    for (const auto &[style, expectValue] : testPlan) {
        auto optStyle = Converter::ArkValue<Opt_FontStyle>(style);
        modifier_->setFontStyle(node_, &optStyle);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setFontStyleTestInvalidValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontStyleTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    using ArkFontStyleTest = std::pair<Ark_FontStyle, std::string>;
    const std::vector<ArkFontStyleTest> testPlan = {
        { static_cast<Ark_FontStyle>(2), ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE },
    };

    for (const auto &[style, expectValue] : testPlan) {
        auto optStyle = Converter::ArkValue<Opt_FontStyle>(style);
        modifier_->setFontStyle(node_, &optStyle);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, expectValue);
    }
}

/*
 * @tc.name: setFontFamilyTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setFontFamily
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setFontFamilyTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    auto inputStringValue = "testFamily";
    auto inputArkStringValue = ArkValue<Ark_String>(inputStringValue);
    auto inputValue = ArkUnion<Ark_Union_String_Resource, Ark_String>(inputArkStringValue);

    auto optInputValue = Converter::ArkValue<Opt_Union_String_Resource>(inputValue);
    modifier_->setFontFamily(node_, &optInputValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, inputStringValue);

    inputStringValue = "testFamily1,testFamily2";
    inputArkStringValue = ArkValue<Ark_String>(inputStringValue);
    inputValue = ArkUnion<Ark_Union_String_Resource, Ark_String>(inputArkStringValue);

    optInputValue = Converter::ArkValue<Opt_Union_String_Resource>(inputValue);
    modifier_->setFontFamily(node_, &optInputValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, inputStringValue);

    inputStringValue = "testFamily1, testFamily2";
    inputArkStringValue = ArkValue<Ark_String>(inputStringValue);
    inputValue = ArkUnion<Ark_Union_String_Resource, Ark_String>(inputArkStringValue);

    optInputValue = Converter::ArkValue<Opt_Union_String_Resource>(inputValue);
    modifier_->setFontFamily(node_, &optInputValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, inputStringValue);
}

/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestOverflow, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;

    // Valid values for attribute 'overflow' of method 'labelStyle'
    static std::vector<std::tuple<std::string, Opt_TextOverflow, std::string>> labelStyleOverflow = {
        {"ARK_TEXT_OVERFLOW_NONE",
            Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_NONE),
            "TextOverflow.None"},
        {"ARK_TEXT_OVERFLOW_CLIP",
            Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_CLIP),
            "TextOverflow.Clip"},
        {"ARK_TEXT_OVERFLOW_ELLIPSIS",
            Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_ELLIPSIS),
            "TextOverflow.Ellipsis"},
        {"ARK_TEXT_OVERFLOW_MARQUEE",
            Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_MARQUEE),
            "TextOverflow.Marquee"},
    };

    // Verifying attribute's 'overflow'  values
    for (auto&& value: labelStyleOverflow) {
        inputValueLabelStyle.overflow = std::get<1>(value);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_OVERFLOW_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestMaxLines, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;

    static std::vector<std::tuple<std::string, Opt_Number, std::string>> labelStyleMaxLines = {
        { "20", Converter::ArkValue<Opt_Number>(20), "20" },
        { "0", Converter::ArkValue<Opt_Number>(0), "1" },
        { "22", Converter::ArkValue<Opt_Number>(22.5f), "22" },
        { "-20", Converter::ArkValue<Opt_Number>(-20), "1" },
        { "0.0f", Converter::ArkValue<Opt_Number>(0.0f), "1" },
        { "-22.5f", Converter::ArkValue<Opt_Number>(-22.5f), "1" }
    };

    for (auto&& value: labelStyleMaxLines) {
        inputValueLabelStyle.maxLines = std::get<1>(value);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_MAX_LINES_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestMinFontSize, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;

    // Valid values for attribute 'minFontSize' of method 'labelStyle'
    static std::vector<std::tuple<std::string, Opt_Union_Number_ResourceStr, std::string>> labelStyleMinFontSize = {
        { "20", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(20), "20.00vp" },
        { "0", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(0), "0.00vp" },
        { "22.5f", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(22.5f), "22.50vp" },
        { "-20", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(-20), "0.00px" },
        { "0.0f", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(0.0f), "0.00vp" },
        { "-22.5f", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(-22.5f), "0.00px" }
    };

    for (auto&& value: labelStyleMinFontSize) {
        inputValueLabelStyle.minFontSize = std::get<1>(value);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_MIN_FONT_SIZE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestMaxFontSize, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;
    static std::vector<std::tuple<std::string, Opt_Union_Number_ResourceStr, std::string>> labelStyleMaxFontSize = {
        { "20", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(20), "20.00vp" },
        { "0", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(0), "0.00vp" },
        { "22.5f", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(22.5f), "22.50vp" },
        { "-20", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(-20), "0.00px" },
        { "0.0f", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(0.0f), "0.00vp" },
        { "-22.5f", Converter::ArkUnion<Opt_Union_Number_ResourceStr, Ark_Number>(-22.5f), "0.00px" }
    };
    for (auto&& value: labelStyleMaxFontSize) {
        inputValueLabelStyle.maxFontSize = std::get<1>(value);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_MAX_FONT_SIZE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestHeightAdaptivePolicy, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;

    using adaptivePolicy = std::tuple<std::string, Opt_TextHeightAdaptivePolicy, std::string>;
    static std::vector<adaptivePolicy> labelStyleHeightAdaptivePolicy = {
        {"ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST",
            Converter::ArkValue<Opt_TextHeightAdaptivePolicy>(ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST),
            "TextHeightAdaptivePolicy.MAX_LINES_FIRST"},
        {"ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST",
            Converter::ArkValue<Opt_TextHeightAdaptivePolicy>(ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST),
            "TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST"},
        {"ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST",
            Converter::ArkValue<Opt_TextHeightAdaptivePolicy>(ARK_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST),
            "TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST"},
    };
    for (auto&& value: labelStyleHeightAdaptivePolicy) {
        inputValueLabelStyle.heightAdaptivePolicy = std::get<1>(value);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        resultStr = GetAttrValue<std::string>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_HEIGHT_ADAPTIVE_POLICY_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestFontWeightValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;
    Ark_Font fontLabel;
    for (auto &[value, expectValue]: OPT_FONT_WEIGHT_TEST_PLAN) {
        fontLabel.weight = value;
        inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
        auto weight = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(weight, expectValue);
    }
}


/*
 * @tc.name: setLabelStyleTestFontWeightInvalidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestFontWeightInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;
    Ark_Font fontLabel;
    const std::vector<OptArkFontWeightTest> testPlan = {
        { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(1000)),
            ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
        { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("1000")),
            ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE },
    };
    for (auto &[value, expectValue]: testPlan) {
        fontLabel.weight = value;
        inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
        auto weight = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(weight, expectValue);
    }
}

/*
 * @tc.name: setLabelStyleTestFontStyleValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestFontStyleValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;
    Ark_Font fontLabel;
    for (auto &[value, expectValue]: OPT_FONT_STYLE_TEST_PLAN) {
        fontLabel.style = value;
        inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
        auto style = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_STYLE_NAME);
        EXPECT_EQ(style, expectValue);
    }
}

/*
 * @tc.name: setLabelStyleTestFontStyleInvalidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestFontStyleInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;
    Ark_Font fontLabel;

    const std::vector<OptArkFontStyleTest> testPlan = {
        { ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(2)), "FontStyle.Normal" },
    };

    for (auto &[value, expectValue]: testPlan) {
        fontLabel.style = value;
        inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
        auto style = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_STYLE_NAME);
        EXPECT_EQ(style, expectValue);
    }
}

/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestFontSizeValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;
    Ark_Font fontLabel;
    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlanValid = {
        { ArkValue<Opt_Length>(1.0f),  "1.00vp" },
        { ArkValue<Opt_Length>(2.45f), "2.45vp" },
        { ArkValue<Opt_Length>(5.0_px), "5.00px" },
        { ArkValue<Opt_Length>(22.35_px), "22.35px" },
        { ArkValue<Opt_Length>(7.0_vp), "7.00vp" },
        { ArkValue<Opt_Length>(1.65_vp), "1.65vp" },
        { ArkValue<Opt_Length>(65.0_fp), "65.00fp" },
        { ArkValue<Opt_Length>(4.3_fp), "4.30fp" },
    };

    for (const auto &[value, expectValue]: testPlanValid) {
        fontLabel.size = value;
        inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
        auto style = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_SIZE_NAME);
        EXPECT_EQ(style, expectValue);
    }
}
/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestFontSizeInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    std::string resultStr;
    std::string expectedStr;
    Ark_LabelStyle inputValueLabelStyle;
    Ark_Font fontLabel;
    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlanInvalid = {
        { ArkValue<Opt_Length>("23.00%"), "0.00px" },
        { ArkValue<Opt_Length>(-0.1f), "0.00px"},
        { ArkValue<Opt_Length>(-5.0_px), "0.00px" },
    };
    for (const auto &[value, expectValue]: testPlanInvalid) {
        fontLabel.size = value;
        inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
        auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
        modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
        jsonValue = GetJsonValue(node_);
        resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
        auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
        auto style = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_SIZE_NAME);
        EXPECT_EQ(style, expectValue);
    }
}
/*
 * @tc.name: setLabelStyleTestValidValues
 * @tc.desc: Check the functionality of ButtonModifier.setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setLabelStyleTestFontFamily, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultLabelStyle;
    Ark_LabelStyle inputValueLabelStyle;
    Ark_Font fontLabel;

    auto inputStringValue = "testFamily";
    auto inputArkStringValue = ArkValue<Ark_String>(inputStringValue);
    auto inputValue = ArkUnion<Opt_Union_String_Resource, Ark_String>(inputArkStringValue);

    fontLabel.family = inputValue;
    inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
    auto optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
    modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
    jsonValue = GetJsonValue(node_);
    resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
    auto font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
    auto family = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_FAMILY_NAME);
    EXPECT_EQ(family, inputStringValue);

    inputStringValue = "testFamily1,testFamily2";
    inputArkStringValue = ArkValue<Ark_String>(inputStringValue);
    inputValue = ArkUnion<Opt_Union_String_Resource, Ark_String>(inputArkStringValue);

    fontLabel.family = inputValue;
    inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
    optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
    modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
    jsonValue = GetJsonValue(node_);
    resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
    font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
    family = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_FAMILY_NAME);
    EXPECT_EQ(family, inputStringValue);

    inputStringValue = "testFamily1, testFamily2";
    inputArkStringValue = ArkValue<Ark_String>(inputStringValue);
    inputValue = ArkUnion<Opt_Union_String_Resource, Ark_String>(inputArkStringValue);

    fontLabel.family = inputValue;
    inputValueLabelStyle.font = ArkValue<Opt_Font>(fontLabel);
    optInputValueLabelStyle = Converter::ArkValue<Opt_LabelStyle>(inputValueLabelStyle);
    modifier_->setLabelStyle(node_, &optInputValueLabelStyle);
    jsonValue = GetJsonValue(node_);
    resultLabelStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_LABEL_STYLE_NAME);
    font = GetAttrValue<std::unique_ptr<JsonValue>>(resultLabelStyle, ATTRIBUTE_LABEL_STYLE_FONT_NAME);
    family = GetAttrValue<std::string>(font, ATTRIBUTE_LABEL_STYLE_FONT_FAMILY_NAME);
    EXPECT_EQ(family, inputStringValue);
}

/*
 * @tc.name: setMinFontScaleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, setMinFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_STYLE_MIN_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'minFontScale'";
}

/*
 * @tc.name: setMinFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setMinFontScaleTestValidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureMinFontScaleNumValidValues = {
        { "0.1", Converter::ArkValue<Ark_Number>(0.1), "0.100000" },
        { "0.89", Converter::ArkValue<Ark_Number>(0.89), "0.890000" },
        { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
    };
    Ark_Union_Number_Resource initValueMinFontScale;
    // Initial setup
    initValueMinFontScale = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(testFixtureMinFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const std::string& expectedStr,
                            const Ark_Union_Number_Resource& value) {
        auto optInputValueMinFontScale = Converter::ArkValue<Opt_Union_Number_Resource>(value);
        modifier_->setMinFontScale(node_, &optInputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_STYLE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMinFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
}

/*
 * @tc.name: setMinFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setMinFontScaleTestInvalidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureMinFontScaleNumInvalidValues = {
        { "-1.01", Converter::ArkValue<Ark_Number>(-1.01), ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE },
        { "2.89", Converter::ArkValue<Ark_Number>(2.89), ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE },
        { "-1", Converter::ArkValue<Ark_Number>(-1), ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE },
    };
    Ark_Union_Number_Resource initValueMinFontScale;
    // Initial setup
    initValueMinFontScale = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(Converter::ArkValue<Ark_Number>(2.1));
        auto checkValue = [this, &initValueMinFontScale](const std::string& input,  const std::string& expectedStr,
                                                         const Ark_Union_Number_Resource& value) {
       
        auto optInputValueMinFontScale = Converter::ArkValue<Opt_Union_Number_Resource>(initValueMinFontScale);
        modifier_->setMinFontScale(node_, &optInputValueMinFontScale);
        optInputValueMinFontScale = Converter::ArkValue<Opt_Union_Number_Resource>(value);
        modifier_->setMinFontScale(node_, &optInputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_STYLE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMinFontScaleNumInvalidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
}

/*
 * @tc.name: setMaxFontScaleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setMaxFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_STYLE_MAX_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'maxFontScale'";
}

/*
 * @tc.name: setMaxFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setMaxFontScaleTestValidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureMaxFontScaleNumValidValues = {
        { "1", Converter::ArkValue<Ark_Number>(1), "1.000000" },
        { "1.5", Converter::ArkValue<Ark_Number>(1.5), "1.500000" },
        { "1.99", Converter::ArkValue<Ark_Number>(1.99), "1.990000" },
    };
    Ark_Union_Number_Resource initValueMaxFontScale;
    // Initial setup
    initValueMaxFontScale = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(testFixtureMaxFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const std::string& expectedStr,
                            const Ark_Union_Number_Resource& value) {
        auto optInputValueMaxFontScale = Converter::ArkValue<Opt_Union_Number_Resource>(initValueMaxFontScale);
        modifier_->setMaxFontScale(node_, &optInputValueMaxFontScale);
        optInputValueMaxFontScale = Converter::ArkValue<Opt_Union_Number_Resource>(value);
        modifier_->setMaxFontScale(node_, &optInputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_STYLE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMaxFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
}

/*
 * @tc.name: setMaxFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ButtonModifierTest, DISABLED_setMaxFontScaleTestInvalidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureMaxFontScaleNumInvalidValues = {
        { "0.1", Converter::ArkValue<Ark_Number>(0.1), "ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE" },
        { "-1.5", Converter::ArkValue<Ark_Number>(-1.5), "ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE" },
        { "-0.99", Converter::ArkValue<Ark_Number>(-0.99), "ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE" },
    };
    Ark_Union_Number_Resource initValueMaxFontScale;
    // Initial setup
    initValueMaxFontScale = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(Converter::ArkValue<Ark_Number>(0.1));
    auto checkValue = [this, &initValueMaxFontScale](const std::string& input,  const std::string& expectedStr,
                                                         const Ark_Union_Number_Resource& value) {
        auto optInputValueMaxFontScale = Converter::ArkValue<Opt_Union_Number_Resource>(initValueMaxFontScale);
        modifier_->setMaxFontScale(node_, &optInputValueMaxFontScale);
        optInputValueMaxFontScale = Converter::ArkValue<Opt_Union_Number_Resource>(value);
        modifier_->setMaxFontScale(node_, &optInputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LABEL_STYLE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMaxFontScaleNumInvalidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
}
} // namespace OHOS::Ace::NG
