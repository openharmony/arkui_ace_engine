/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "text_input_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::TextInput;
/*
 * @tc.name: setPasswordIconTestPasswordIconOffIconSrcInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordIconTestPasswordIconOffIconSrcInvalidValues, TestSize.Level1)
{
    Opt_PasswordIcon initValuePasswordIcon;

    // Initial setup
    WriteTo(initValuePasswordIcon).onIconSrc =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));
    WriteTo(initValuePasswordIcon).offIconSrc =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));

    auto checkValue = [this, &initValuePasswordIcon](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_PasswordIcon inputValuePasswordIcon = initValuePasswordIcon;

        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        WriteTo(inputValuePasswordIcon).offIconSrc = value;
        modifier_->setPasswordIcon(node_, &inputValuePasswordIcon);
        auto jsonValue = GetJsonValue(node_);
        auto resultPasswordIcon = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_PASSWORD_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPasswordIcon, ATTRIBUTE_PASSWORD_ICON_I_OFF_ICON_SRC_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_ICON_I_OFF_ICON_SRC_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPasswordIcon, attribute: passwordIcon.offIconSrc";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setShowErrorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowErrorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_ERROR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_ERROR_DEFAULT_VALUE) << "Default value for attribute 'showError'";
}

/*
 * @tc.name: setShowErrorTestShowErrorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowErrorTestShowErrorValidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueShowError;

    // Initial setup
    initValueShowError = ArkUnion<Opt_ResourceStr, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureStringEmptyResUndefinedValidValues[0]));

    auto checkValue = [this, &initValueShowError](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueShowError = initValueShowError;

        inputValueShowError = value;
        modifier_->setShowError(node_, &inputValueShowError);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_ERROR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowError, attribute: showError";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringEmptyResUndefinedValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringEmptyUndefinedValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setShowErrorTestShowErrorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowErrorTestShowErrorInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueShowError;

    // Initial setup
    initValueShowError = ArkUnion<Opt_ResourceStr, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureStringEmptyResUndefinedValidValues[0]));

    auto checkValue = [this, &initValueShowError](const std::string& input, const Opt_ResourceStr& value) {
        Opt_ResourceStr inputValueShowError = initValueShowError;

        modifier_->setShowError(node_, &inputValueShowError);
        inputValueShowError = value;
        modifier_->setShowError(node_, &inputValueShowError);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_ERROR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_ERROR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowError, attribute: showError";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}

/*
 * @tc.name: setShowUnderlineTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowUnderlineTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_UNDERLINE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_UNDERLINE_DEFAULT_VALUE) << "Default value for attribute 'showUnderline'";
}

/*
 * @tc.name: setShowUnderlineTestShowUnderlineValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowUnderlineTestShowUnderlineValidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowUnderline;

    // Initial setup
    initValueShowUnderline = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueShowUnderline](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowUnderline = initValueShowUnderline;

        inputValueShowUnderline = value;
        modifier_->setShowUnderline(node_, &inputValueShowUnderline);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_UNDERLINE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowUnderline, attribute: showUnderline";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowUnderlineTestShowUnderlineInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowUnderlineTestShowUnderlineInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueShowUnderline;

    // Initial setup
    initValueShowUnderline = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueShowUnderline](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueShowUnderline = initValueShowUnderline;

        modifier_->setShowUnderline(node_, &inputValueShowUnderline);
        inputValueShowUnderline = value;
        modifier_->setShowUnderline(node_, &inputValueShowUnderline);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_UNDERLINE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_UNDERLINE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowUnderline, attribute: showUnderline";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setUnderlineColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultUnderlineColor =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_TYPING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UNDERLINE_COLOR_I_TYPING_DEFAULT_VALUE) <<
        "Default value for attribute 'underlineColor.UnderlineColor.typing'";

    resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_NORMAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UNDERLINE_COLOR_I_NORMAL_DEFAULT_VALUE) <<
        "Default value for attribute 'underlineColor.UnderlineColor.normal'";

    resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_ERROR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UNDERLINE_COLOR_I_ERROR_DEFAULT_VALUE) <<
        "Default value for attribute 'underlineColor.UnderlineColor.error'";

    resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_DISABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_UNDERLINE_COLOR_I_DISABLE_DEFAULT_VALUE) <<
        "Default value for attribute 'underlineColor.UnderlineColor.disable'";
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorUnderlineColorTypingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setUnderlineColorTestUnderlineColorUnderlineColorTypingValidValues,
    TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueUnderlineColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_Union_ResourceColor_UnderlineColor inputValueUnderlineColor = initValueUnderlineColor;

        WriteToUnion<Ark_UnderlineColor>(WriteTo(inputValueUnderlineColor)).typing = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_TYPING_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUnderlineColor, attribute: underlineColor.UnderlineColor.typing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorUnderlineColorTypingInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorUnderlineColorTypingInvalidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueUnderlineColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_Union_ResourceColor_UnderlineColor inputValueUnderlineColor = initValueUnderlineColor;

        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        WriteToUnion<Ark_UnderlineColor>(WriteTo(inputValueUnderlineColor)).typing = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_TYPING_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_UNDERLINE_COLOR_I_TYPING_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setUnderlineColor, attribute: underlineColor.UnderlineColor.typing";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorUnderlineColorNormalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setUnderlineColorTestUnderlineColorUnderlineColorNormalValidValues,
    TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueUnderlineColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_Union_ResourceColor_UnderlineColor inputValueUnderlineColor = initValueUnderlineColor;

        WriteToUnion<Ark_UnderlineColor>(WriteTo(inputValueUnderlineColor)).normal = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_NORMAL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUnderlineColor, attribute: underlineColor.UnderlineColor.normal";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorUnderlineColorNormalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorUnderlineColorNormalInvalidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueUnderlineColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_Union_ResourceColor_UnderlineColor inputValueUnderlineColor = initValueUnderlineColor;

        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        WriteToUnion<Ark_UnderlineColor>(WriteTo(inputValueUnderlineColor)).normal = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_NORMAL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_UNDERLINE_COLOR_I_NORMAL_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setUnderlineColor, attribute: underlineColor.UnderlineColor.normal";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorUnderlineColorErrorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setUnderlineColorTestUnderlineColorUnderlineColorErrorValidValues,
    TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueUnderlineColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_Union_ResourceColor_UnderlineColor inputValueUnderlineColor = initValueUnderlineColor;

        WriteToUnion<Ark_UnderlineColor>(WriteTo(inputValueUnderlineColor)).error = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_ERROR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUnderlineColor, attribute: underlineColor.UnderlineColor.error";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorUnderlineColorErrorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorUnderlineColorErrorInvalidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueUnderlineColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_Union_ResourceColor_UnderlineColor inputValueUnderlineColor = initValueUnderlineColor;

        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        WriteToUnion<Ark_UnderlineColor>(WriteTo(inputValueUnderlineColor)).error = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_ERROR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_UNDERLINE_COLOR_I_ERROR_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setUnderlineColor, attribute: underlineColor.UnderlineColor.error";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorUnderlineColorDisableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setUnderlineColorTestUnderlineColorUnderlineColorDisableValidValues,
    TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueUnderlineColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_Union_ResourceColor_UnderlineColor inputValueUnderlineColor = initValueUnderlineColor;

        WriteToUnion<Ark_UnderlineColor>(WriteTo(inputValueUnderlineColor)).disable = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_DISABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setUnderlineColor, attribute: underlineColor.UnderlineColor.disable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorUnderlineColorDisableInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorUnderlineColorDisableInvalidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueUnderlineColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_Union_ResourceColor_UnderlineColor inputValueUnderlineColor = initValueUnderlineColor;

        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        WriteToUnion<Ark_UnderlineColor>(WriteTo(inputValueUnderlineColor)).disable = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_DISABLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_UNDERLINE_COLOR_I_DISABLE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setUnderlineColor, attribute: underlineColor.UnderlineColor.disable";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setSelectionMenuHiddenTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setSelectionMenuHiddenTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setBarStateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setBarStateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT_VALUE) << "Default value for attribute 'barState'";
}

/*
 * @tc.name: setBarStateTestBarStateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setBarStateTestBarStateValidValues, TestSize.Level1)
{
    Opt_BarState initValueBarState;

    // Initial setup
    initValueBarState = ArkValue<Opt_BarState>(std::get<1>(Fixtures::testFixtureTextInputBarStateValidValues[0]));

    auto checkValue = [this, &initValueBarState](
                          const std::string& input, const std::string& expectedStr, const Opt_BarState& value) {
        Opt_BarState inputValueBarState = initValueBarState;

        inputValueBarState = value;
        modifier_->setBarState(node_, &inputValueBarState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBarState, attribute: barState";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputBarStateValidValues) {
        checkValue(input, expected, ArkValue<Opt_BarState>(value));
    }
}

/*
 * @tc.name: setBarStateTestBarStateInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setBarStateTestBarStateInvalidValues, TestSize.Level1)
{
    Opt_BarState initValueBarState;

    // Initial setup
    initValueBarState = ArkValue<Opt_BarState>(std::get<1>(Fixtures::testFixtureTextInputBarStateValidValues[0]));

    auto checkValue = [this, &initValueBarState](const std::string& input, const Opt_BarState& value) {
        Opt_BarState inputValueBarState = initValueBarState;

        modifier_->setBarState(node_, &inputValueBarState);
        inputValueBarState = value;
        modifier_->setBarState(node_, &inputValueBarState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBarState, attribute: barState";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputBarStateInvalidValues) {
        checkValue(input, ArkValue<Opt_BarState>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_BarState>());
}

/*
 * @tc.name: setMaxLinesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLinesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE) << "Default value for attribute 'maxLines'";
}

/*
 * @tc.name: setMaxLinesTestMaxLinesValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLinesTestMaxLinesValidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));

    auto checkValue = [this, &initValueMaxLines](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueMaxLines = initValueMaxLines;

        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPosIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMaxLinesTestMaxLinesInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLinesTestMaxLinesInvalidValues, TestSize.Level1)
{
    Opt_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));

    auto checkValue = [this, &initValueMaxLines](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueMaxLines = initValueMaxLines;

        modifier_->setMaxLines(node_, &inputValueMaxLines);
        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPosIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWordBreakTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setWordBreakTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE) << "Default value for attribute 'wordBreak'";
}

/*
 * @tc.name: setWordBreakTestWordBreakValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setWordBreakTestWordBreakValidValues, TestSize.Level1)
{
    Opt_WordBreak initValueWordBreak;

    // Initial setup
    initValueWordBreak = ArkValue<Opt_WordBreak>(std::get<1>(Fixtures::testFixtureTextInputBreakWordValidValues[0]));

    auto checkValue = [this, &initValueWordBreak](
                          const std::string& input, const std::string& expectedStr, const Opt_WordBreak& value) {
        Opt_WordBreak inputValueWordBreak = initValueWordBreak;

        inputValueWordBreak = value;
        modifier_->setWordBreak(node_, &inputValueWordBreak);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setWordBreak, attribute: wordBreak";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputBreakWordValidValues) {
        checkValue(input, expected, ArkValue<Opt_WordBreak>(value));
    }
}

/*
 * @tc.name: setWordBreakTestWordBreakInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setWordBreakTestWordBreakInvalidValues, TestSize.Level1)
{
    Opt_WordBreak initValueWordBreak;

    // Initial setup
    initValueWordBreak = ArkValue<Opt_WordBreak>(std::get<1>(Fixtures::testFixtureTextInputBreakWordValidValues[0]));

    auto checkValue = [this, &initValueWordBreak](const std::string& input, const Opt_WordBreak& value) {
        Opt_WordBreak inputValueWordBreak = initValueWordBreak;

        modifier_->setWordBreak(node_, &inputValueWordBreak);
        inputValueWordBreak = value;
        modifier_->setWordBreak(node_, &inputValueWordBreak);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setWordBreak, attribute: wordBreak";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputBreakWordInvalidValues) {
        checkValue(input, ArkValue<Opt_WordBreak>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_WordBreak>());
}

/*
 * @tc.name: setLineBreakStrategyTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLineBreakStrategyTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setCancelButtonTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButtonTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCancelButton =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
    std::unique_ptr<JsonValue> resultIcon =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.CancelButtonOptions.style'";

    resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.CancelButtonOptions.icon.size'";

    resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.CancelButtonOptions.icon.color'";

    resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.CancelButtonOptions.icon.src'";

    resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.CancelButtonSymbolOptions.style'";
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonOptionsStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    TextInputModifierTest, DISABLED_setCancelButtonTestCancelButtonCancelButtonOptionsStyleValidValues, TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const std::string& expectedStr,
                          const Opt_CancelButtonStyle& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        WriteToUnion<Ark_CancelButtonOptions>(WriteTo(inputValueCancelButton)).style = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonOptions.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputCancelButtonStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_CancelButtonStyle>(value));
    }
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonOptionsStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButtonTestCancelButtonCancelButtonOptionsStyleInvalidValues, TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_CancelButtonStyle& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton(node_, &inputValueCancelButton);
        WriteToUnion<Ark_CancelButtonOptions>(WriteTo(inputValueCancelButton)).style = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonOptions.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputCancelButtonStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_CancelButtonStyle>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_CancelButtonStyle>());
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonOptionsIconSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCancelButtonTestCancelButtonCancelButtonOptionsIconSizeValidValues,
    TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(inputValueCancelButton)).icon).size = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonOptions.icon.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonOptionsIconSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    TextInputModifierTest, setCancelButtonTestCancelButtonCancelButtonOptionsIconSizeInvalidValues, TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_Length& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton(node_, &inputValueCancelButton);
        WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(inputValueCancelButton)).icon).size = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonOptions.icon.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonOptionsIconColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCancelButtonTestCancelButtonCancelButtonOptionsIconColorValidValues,
    TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(inputValueCancelButton)).icon).color = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonOptions.icon.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonOptionsIconColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    TextInputModifierTest, setCancelButtonTestCancelButtonCancelButtonOptionsIconColorInvalidValues, TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_ResourceColor& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton(node_, &inputValueCancelButton);
        WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(inputValueCancelButton)).icon).color = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonOptions.icon.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonOptionsIconSrcValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCancelButtonTestCancelButtonCancelButtonOptionsIconSrcValidValues,
    TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(inputValueCancelButton)).icon).src = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonOptions.icon.src";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonOptionsIconSrcInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButtonTestCancelButtonCancelButtonOptionsIconSrcInvalidValues, TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(initValueCancelButton)).icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_ResourceStr& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton(node_, &inputValueCancelButton);
        WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(inputValueCancelButton)).icon).src = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonOptions.icon.src";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonSymbolOptionsStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCancelButtonTestCancelButtonCancelButtonSymbolOptionsStyleValidValues,
    TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonSymbolOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const std::string& expectedStr,
                          const Opt_CancelButtonStyle& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        WriteToUnion<Ark_CancelButtonSymbolOptions>(WriteTo(inputValueCancelButton)).style = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonSymbolOptions.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputCancelButtonStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_CancelButtonStyle>(value));
    }
}

/*
 * @tc.name: setCancelButtonTestCancelButtonCancelButtonSymbolOptionsStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    TextInputModifierTest, setCancelButtonTestCancelButtonCancelButtonSymbolOptionsStyleInvalidValues, TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    WriteToUnion<Ark_CancelButtonSymbolOptions>(WriteTo(initValueCancelButton)).style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_CancelButtonStyle& value) {
        Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton(node_, &inputValueCancelButton);
        WriteToUnion<Ark_CancelButtonSymbolOptions>(WriteTo(inputValueCancelButton)).style = value;
        modifier_->setCancelButton(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setCancelButton, attribute: cancelButton.CancelButtonSymbolOptions.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputCancelButtonStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_CancelButtonStyle>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_CancelButtonStyle>());
}

/*
 * @tc.name: setSelectAllTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectAllTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_ALL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECT_ALL_DEFAULT_VALUE) << "Default value for attribute 'selectAll'";
}

/*
 * @tc.name: setSelectAllTestSelectAllValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectAllTestSelectAllValidValues, TestSize.Level1)
{
    Opt_Boolean initValueSelectAll;

    // Initial setup
    initValueSelectAll = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueSelectAll](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueSelectAll = initValueSelectAll;

        inputValueSelectAll = value;
        modifier_->setSelectAll(node_, &inputValueSelectAll);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_ALL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectAll, attribute: selectAll";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setSelectAllTestSelectAllInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectAllTestSelectAllInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueSelectAll;

    // Initial setup
    initValueSelectAll = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueSelectAll](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueSelectAll = initValueSelectAll;

        modifier_->setSelectAll(node_, &inputValueSelectAll);
        inputValueSelectAll = value;
        modifier_->setSelectAll(node_, &inputValueSelectAll);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_ALL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECT_ALL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSelectAll, attribute: selectAll";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setMinFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMinFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'minFontSize'";
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMinFontSizeTestMinFontSizeValidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueMinFontSize = initValueMinFontSize;

        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMinFontSizeTestMinFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](
                          const std::string& input, const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueMinFontSize = initValueMinFontSize;

        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_String_Resource>());
}

/*
 * @tc.name: setMaxFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'maxFontSize'";
}

/*
 * @tc.name: setMaxFontSizeTestMaxFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxFontSizeTestMaxFontSizeValidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMaxFontSizeTestMaxFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxFontSizeTestMaxFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](
                          const std::string& input, const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_String_Resource>());
}

/*
 * @tc.name: setMinFontScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMinFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'minFontScale'";
}

/*
 * @tc.name: setMinFontScaleTestMinFontScaleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMinFontScaleTestMinFontScaleValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMinFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueMinFontScale = initValueMinFontScale;

        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMinFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureMinFontScaleResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setMinFontScaleTestMinFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMinFontScaleTestMinFontScaleInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMinFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueMinFontScale = initValueMinFontScale;

        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setMaxFontScaleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'maxFontScale'";
}

/*
 * @tc.name: setMaxFontScaleTestMaxFontScaleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxFontScaleTestMaxFontScaleValidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMaxFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueMaxFontScale = initValueMaxFontScale;

        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMaxFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureMaxFontScaleResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setMaxFontScaleTestMaxFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxFontScaleTestMaxFontScaleInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMaxFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const Opt_Union_Number_Resource& value) {
        Opt_Union_Number_Resource inputValueMaxFontScale = initValueMaxFontScale;

        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SCALE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setHeightAdaptivePolicyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHeightAdaptivePolicyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE) <<
        "Default value for attribute 'heightAdaptivePolicy'";
}

/*
 * @tc.name: setHeightAdaptivePolicyTestHeightAdaptivePolicyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHeightAdaptivePolicyTestHeightAdaptivePolicyValidValues, TestSize.Level1)
{
    Opt_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));

    auto checkValue = [this, &initValueHeightAdaptivePolicy](const std::string& input, const std::string& expectedStr,
                          const Opt_TextHeightAdaptivePolicy& value) {
        Opt_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, &inputValueHeightAdaptivePolicy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextHeightAdaptivePolicy>(value));
    }
}

/*
 * @tc.name: setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues, TestSize.Level1)
{
    Opt_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = ArkValue<Opt_TextHeightAdaptivePolicy>(
        std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]));

    auto checkValue = [this, &initValueHeightAdaptivePolicy](
                          const std::string& input, const Opt_TextHeightAdaptivePolicy& value) {
        Opt_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        modifier_->setHeightAdaptivePolicy(node_, &inputValueHeightAdaptivePolicy);
        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, &inputValueHeightAdaptivePolicy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyInvalidValues) {
        checkValue(input, ArkValue<Opt_TextHeightAdaptivePolicy>(value));
    }
}

/*
 * @tc.name: setEnableAutoFillTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableAutoFillTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_AUTO_FILL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_AUTO_FILL_DEFAULT_VALUE) << "Default value for attribute 'enableAutoFill'";
}

/*
 * @tc.name: setEnableAutoFillTestEnableAutoFillValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableAutoFillTestEnableAutoFillValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableAutoFill;

    // Initial setup
    initValueEnableAutoFill = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableAutoFill](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableAutoFill = initValueEnableAutoFill;

        inputValueEnableAutoFill = value;
        modifier_->setEnableAutoFill(node_, &inputValueEnableAutoFill);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_AUTO_FILL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableAutoFill, attribute: enableAutoFill";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnableAutoFillTestEnableAutoFillInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableAutoFillTestEnableAutoFillInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableAutoFill;

    // Initial setup
    initValueEnableAutoFill = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableAutoFill](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableAutoFill = initValueEnableAutoFill;

        modifier_->setEnableAutoFill(node_, &inputValueEnableAutoFill);
        inputValueEnableAutoFill = value;
        modifier_->setEnableAutoFill(node_, &inputValueEnableAutoFill);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_AUTO_FILL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_AUTO_FILL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableAutoFill, attribute: enableAutoFill";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setDecorationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setDecorationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultDecoration =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE) << "Default value for attribute 'decoration.type'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'decoration.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'decoration.style'";
}

/*
 * @tc.name: setDecorationTestDecorationTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setDecorationTestDecorationTypeValidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const std::string& expectedStr,
                          const Ark_TextDecorationType& value) {
        Opt_TextDecorationOptions inputValueDecoration = initValueDecoration;

        WriteTo(inputValueDecoration).type = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextDecorationTypeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setDecorationTestDecorationTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setDecorationTestDecorationTypeInvalidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Ark_TextDecorationType& value) {
        Opt_TextDecorationOptions inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        WriteTo(inputValueDecoration).type = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextDecorationTypeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDecorationTestDecorationColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setDecorationTestDecorationColorValidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_TextDecorationOptions inputValueDecoration = initValueDecoration;

        WriteTo(inputValueDecoration).color = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setDecorationTestDecorationColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setDecorationTestDecorationColorInvalidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_ResourceColor& value) {
        Opt_TextDecorationOptions inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        WriteTo(inputValueDecoration).color = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setDecorationTestDecorationStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setDecorationTestDecorationStyleValidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const std::string& expectedStr,
                          const Opt_TextDecorationStyle& value) {
        Opt_TextDecorationOptions inputValueDecoration = initValueDecoration;

        WriteTo(inputValueDecoration).style = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextDecorationStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextDecorationStyle>(value));
    }
}

/*
 * @tc.name: setDecorationTestDecorationStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setDecorationTestDecorationStyleInvalidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueDecoration).style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_TextDecorationStyle& value) {
        Opt_TextDecorationOptions inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        WriteTo(inputValueDecoration).style = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DECORATION_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextDecorationStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_TextDecorationStyle>(value));
    }
}

/*
 * @tc.name: setLetterSpacingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLetterSpacingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE) << "Default value for attribute 'letterSpacing'";
}

/*
 * @tc.name: setLetterSpacingTestLetterSpacingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLetterSpacingTestLetterSpacingValidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueLetterSpacing](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueLetterSpacing = initValueLetterSpacing;

        inputValueLetterSpacing = value;
        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLetterSpacing, attribute: letterSpacing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonPercValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setLetterSpacingTestLetterSpacingInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLetterSpacingTestLetterSpacingInvalidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueLetterSpacing](
                          const std::string& input, const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueLetterSpacing = initValueLetterSpacing;

        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        inputValueLetterSpacing = value;
        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLetterSpacing, attribute: letterSpacing";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonPercInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_String_Resource>());
}

/*
 * @tc.name: setLineHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLineHeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE) << "Default value for attribute 'lineHeight'";
}

/*
 * @tc.name: setLineHeightTestLineHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLineHeightTestLineHeightValidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueLineHeight = initValueLineHeight;

        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
}

} // namespace OHOS::Ace::NG
