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

#include "text_input_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::TextInput;
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
    Ark_Boolean initValueShowUnderline;

    // Initial setup
    initValueShowUnderline = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueShowUnderline](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueShowUnderline = initValueShowUnderline;

        inputValueShowUnderline = value;
        modifier_->setShowUnderline(node_, inputValueShowUnderline);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_UNDERLINE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowUnderline, attribute: showUnderline";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
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
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorUnderlineColorTypingValidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
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
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorUnderlineColorNormalValidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
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
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorUnderlineColorErrorValidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
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
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorUnderlineColorDisableValidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_UnderlineColor initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).typing =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).normal =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).error =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_UnderlineColor>(WriteTo(initValueUnderlineColor)).disable =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setSelectionMenuHiddenTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectionMenuHiddenTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTION_MENU_HIDDEN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTION_MENU_HIDDEN_DEFAULT_VALUE) <<
        "Default value for attribute 'selectionMenuHidden'";
}

/*
 * @tc.name: setSelectionMenuHiddenTestSelectionMenuHiddenValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setSelectionMenuHiddenTestSelectionMenuHiddenValidValues, TestSize.Level1)
{
    Ark_Boolean initValueSelectionMenuHidden;

    // Initial setup
    initValueSelectionMenuHidden = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueSelectionMenuHidden](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueSelectionMenuHidden = initValueSelectionMenuHidden;

        inputValueSelectionMenuHidden = value;
        modifier_->setSelectionMenuHidden(node_, inputValueSelectionMenuHidden);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTION_MENU_HIDDEN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectionMenuHidden, attribute: selectionMenuHidden";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_BarState initValueBarState;

    // Initial setup
    initValueBarState = std::get<1>(Fixtures::testFixtureTextInputBarStateValidValues[0]);

    auto checkValue = [this, &initValueBarState](
                          const std::string& input, const std::string& expectedStr, const Ark_BarState& value) {
        Ark_BarState inputValueBarState = initValueBarState;

        inputValueBarState = value;
        modifier_->setBarState(node_, inputValueBarState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setBarState, attribute: barState";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputBarStateValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setBarStateTestBarStateInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setBarStateTestBarStateInvalidValues, TestSize.Level1)
{
    Ark_BarState initValueBarState;

    // Initial setup
    initValueBarState = std::get<1>(Fixtures::testFixtureTextInputBarStateValidValues[0]);

    auto checkValue = [this, &initValueBarState](const std::string& input, const Ark_BarState& value) {
        Ark_BarState inputValueBarState = initValueBarState;

        modifier_->setBarState(node_, inputValueBarState);
        inputValueBarState = value;
        modifier_->setBarState(node_, inputValueBarState);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BAR_STATE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_BAR_STATE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setBarState, attribute: barState";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputBarStateInvalidValues) {
        checkValue(input, value);
    }
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
HWTEST_F(TextInputModifierTest, setMaxLinesTestMaxLinesValidValues, TestSize.Level1)
{
    Ark_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]);

    auto checkValue = [this, &initValueMaxLines](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueMaxLines = initValueMaxLines;

        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPosIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMaxLinesTestMaxLinesInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setMaxLinesTestMaxLinesInvalidValues, TestSize.Level1)
{
    Ark_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]);

    auto checkValue = [this, &initValueMaxLines](const std::string& input, const Ark_Number& value) {
        Ark_Number inputValueMaxLines = initValueMaxLines;

        modifier_->setMaxLines(node_, &inputValueMaxLines);
        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPosIntFloorInvalidValues) {
        checkValue(input, value);
    }
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
    Ark_WordBreak initValueWordBreak;

    // Initial setup
    initValueWordBreak = std::get<1>(Fixtures::testFixtureTextInputBreakWordValidValues[0]);

    auto checkValue = [this, &initValueWordBreak](
                          const std::string& input, const std::string& expectedStr, const Ark_WordBreak& value) {
        Ark_WordBreak inputValueWordBreak = initValueWordBreak;

        inputValueWordBreak = value;
        modifier_->setWordBreak(node_, inputValueWordBreak);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setWordBreak, attribute: wordBreak";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputBreakWordValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setWordBreakTestWordBreakInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setWordBreakTestWordBreakInvalidValues, TestSize.Level1)
{
    Ark_WordBreak initValueWordBreak;

    // Initial setup
    initValueWordBreak = std::get<1>(Fixtures::testFixtureTextInputBreakWordValidValues[0]);

    auto checkValue = [this, &initValueWordBreak](const std::string& input, const Ark_WordBreak& value) {
        Ark_WordBreak inputValueWordBreak = initValueWordBreak;

        modifier_->setWordBreak(node_, inputValueWordBreak);
        inputValueWordBreak = value;
        modifier_->setWordBreak(node_, inputValueWordBreak);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORD_BREAK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORD_BREAK_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setWordBreak, attribute: wordBreak";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputBreakWordInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setLineBreakStrategyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setLineBreakStrategyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LINE_BREAK_STRATEGY_DEFAULT_VALUE) <<
        "Default value for attribute 'lineBreakStrategy'";
}

/*
 * @tc.name: setLineBreakStrategyTestLineBreakStrategyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setLineBreakStrategyTestLineBreakStrategyValidValues, TestSize.Level1)
{
    Ark_LineBreakStrategy initValueLineBreakStrategy;

    // Initial setup
    initValueLineBreakStrategy = std::get<1>(Fixtures::testFixtureTextInputLineBreakStrategyValidValues[0]);

    auto checkValue = [this, &initValueLineBreakStrategy](const std::string& input, const std::string& expectedStr,
                          const Ark_LineBreakStrategy& value) {
        Ark_LineBreakStrategy inputValueLineBreakStrategy = initValueLineBreakStrategy;

        inputValueLineBreakStrategy = value;
        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLineBreakStrategy, attribute: lineBreakStrategy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputLineBreakStrategyValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setLineBreakStrategyTestLineBreakStrategyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setLineBreakStrategyTestLineBreakStrategyInvalidValues, TestSize.Level1)
{
    Ark_LineBreakStrategy initValueLineBreakStrategy;

    // Initial setup
    initValueLineBreakStrategy = std::get<1>(Fixtures::testFixtureTextInputLineBreakStrategyValidValues[0]);

    auto checkValue = [this, &initValueLineBreakStrategy](
                          const std::string& input, const Ark_LineBreakStrategy& value) {
        Ark_LineBreakStrategy inputValueLineBreakStrategy = initValueLineBreakStrategy;

        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategy);
        inputValueLineBreakStrategy = value;
        modifier_->setLineBreakStrategy(node_, inputValueLineBreakStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_BREAK_STRATEGY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLineBreakStrategy, attribute: lineBreakStrategy";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputLineBreakStrategyInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setCancelButton0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCancelButton =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
    std::unique_ptr<JsonValue> resultIcon =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.style'";

    resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.icon.size'";

    resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.icon.color'";

    resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.icon.src'";
}

/*
 * @tc.name: setCancelButton0TestCancelButtonStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestCancelButtonStyleValidValues, TestSize.Level1)
{
    Ark_CancelButtonOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(initValueCancelButton.icon).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueCancelButton.icon).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueCancelButton.icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const std::string& expectedStr,
                          const Opt_CancelButtonStyle& value) {
        Ark_CancelButtonOptions inputValueCancelButton = initValueCancelButton;

        inputValueCancelButton.style = value;
        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCancelButton0, attribute: cancelButton.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputCancelButtonStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_CancelButtonStyle>(value));
    }
}

/*
 * @tc.name: setCancelButton0TestCancelButtonStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestCancelButtonStyleInvalidValues, TestSize.Level1)
{
    Ark_CancelButtonOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(initValueCancelButton.icon).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueCancelButton.icon).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueCancelButton.icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_CancelButtonStyle& value) {
        Ark_CancelButtonOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        inputValueCancelButton.style = value;
        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCancelButton0, attribute: cancelButton.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputCancelButtonStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_CancelButtonStyle>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_CancelButtonStyle>());
}

/*
 * @tc.name: setCancelButton0TestCancelButtonIconSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestCancelButtonIconSizeValidValues, TestSize.Level1)
{
    Ark_CancelButtonOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(initValueCancelButton.icon).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueCancelButton.icon).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueCancelButton.icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_CancelButtonOptions inputValueCancelButton = initValueCancelButton;

        WriteTo(inputValueCancelButton.icon).size = value;
        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCancelButton0, attribute: cancelButton.icon.size";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setCancelButton0TestCancelButtonIconSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestCancelButtonIconSizeInvalidValues, TestSize.Level1)
{
    Ark_CancelButtonOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(initValueCancelButton.icon).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueCancelButton.icon).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueCancelButton.icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_Length& value) {
        Ark_CancelButtonOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        WriteTo(inputValueCancelButton.icon).size = value;
        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCancelButton0, attribute: cancelButton.icon.size";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setCancelButton0TestCancelButtonIconColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestCancelButtonIconColorValidValues, TestSize.Level1)
{
    Ark_CancelButtonOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(initValueCancelButton.icon).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueCancelButton.icon).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueCancelButton.icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Ark_CancelButtonOptions inputValueCancelButton = initValueCancelButton;

        WriteTo(inputValueCancelButton.icon).color = value;
        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCancelButton0, attribute: cancelButton.icon.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setCancelButton0TestCancelButtonIconColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestCancelButtonIconColorInvalidValues, TestSize.Level1)
{
    Ark_CancelButtonOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(initValueCancelButton.icon).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueCancelButton.icon).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueCancelButton.icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_ResourceColor& value) {
        Ark_CancelButtonOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        WriteTo(inputValueCancelButton.icon).color = value;
        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCancelButton0, attribute: cancelButton.icon.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setCancelButton0TestCancelButtonIconSrcValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestCancelButtonIconSrcValidValues, TestSize.Level1)
{
    Ark_CancelButtonOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(initValueCancelButton.icon).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueCancelButton.icon).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueCancelButton.icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceStr& value) {
        Ark_CancelButtonOptions inputValueCancelButton = initValueCancelButton;

        WriteTo(inputValueCancelButton.icon).src = value;
        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCancelButton0, attribute: cancelButton.icon.src";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setCancelButton0TestCancelButtonIconSrcInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton0TestCancelButtonIconSrcInvalidValues, TestSize.Level1)
{
    Ark_CancelButtonOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));
    WriteTo(initValueCancelButton.icon).size =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueCancelButton.icon).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValueCancelButton.icon).src =
        ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_ResourceStr& value) {
        Ark_CancelButtonOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        WriteTo(inputValueCancelButton.icon).src = value;
        modifier_->setCancelButton0(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultIcon =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_ICON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultIcon, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_ICON_I_SRC_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCancelButton0, attribute: cancelButton.icon.src";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceStr>());
}

/*
 * @tc.name: setCancelButton1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCancelButton =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'cancelButton.style'";
}

/*
 * @tc.name: setCancelButton1TestCancelButtonStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setCancelButton1TestCancelButtonStyleValidValues, TestSize.Level1)
{
    Ark_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const std::string& expectedStr,
                          const Opt_CancelButtonStyle& value) {
        Ark_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        inputValueCancelButton.style = value;
        modifier_->setCancelButton1(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCancelButton1, attribute: cancelButton.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputCancelButtonStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_CancelButtonStyle>(value));
    }
}

/*
 * @tc.name: setCancelButton1TestCancelButtonStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCancelButton1TestCancelButtonStyleInvalidValues, TestSize.Level1)
{
    Ark_CancelButtonSymbolOptions initValueCancelButton;

    // Initial setup
    initValueCancelButton.style =
        ArkValue<Opt_CancelButtonStyle>(std::get<1>(Fixtures::testFixtureTextInputCancelButtonStyleValidValues[0]));

    auto checkValue = [this, &initValueCancelButton](const std::string& input, const Opt_CancelButtonStyle& value) {
        Ark_CancelButtonSymbolOptions inputValueCancelButton = initValueCancelButton;

        modifier_->setCancelButton1(node_, &inputValueCancelButton);
        inputValueCancelButton.style = value;
        modifier_->setCancelButton1(node_, &inputValueCancelButton);
        auto jsonValue = GetJsonValue(node_);
        auto resultCancelButton = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CANCEL_BUTTON_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCancelButton, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CANCEL_BUTTON_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCancelButton1, attribute: cancelButton.style";
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
    Ark_Boolean initValueSelectAll;

    // Initial setup
    initValueSelectAll = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueSelectAll](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueSelectAll = initValueSelectAll;

        inputValueSelectAll = value;
        modifier_->setSelectAll(node_, inputValueSelectAll);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECT_ALL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSelectAll, attribute: selectAll";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
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
HWTEST_F(TextInputModifierTest, setMinFontSizeTestMinFontSizeValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMinFontSize = initValueMinFontSize;

        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMinFontSizeTestMinFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMinFontSizeTestMinFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMinFontSize = initValueMinFontSize;

        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MIN_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MIN_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
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
HWTEST_F(TextInputModifierTest, setMaxFontSizeTestMaxFontSizeValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMaxFontSizeTestMaxFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setMaxFontSizeTestMaxFontSizeInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
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
    Ark_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]);

    auto checkValue = [this, &initValueHeightAdaptivePolicy](const std::string& input, const std::string& expectedStr,
                          const Ark_TextHeightAdaptivePolicy& value) {
        Ark_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues, TestSize.Level1)
{
    Ark_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]);

    auto checkValue = [this, &initValueHeightAdaptivePolicy](
                          const std::string& input, const Ark_TextHeightAdaptivePolicy& value) {
        Ark_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_ADAPTIVE_POLICY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyInvalidValues) {
        checkValue(input, value);
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
    Ark_Boolean initValueEnableAutoFill;

    // Initial setup
    initValueEnableAutoFill = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableAutoFill](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableAutoFill = initValueEnableAutoFill;

        inputValueEnableAutoFill = value;
        modifier_->setEnableAutoFill(node_, inputValueEnableAutoFill);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_AUTO_FILL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableAutoFill, attribute: enableAutoFill";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setDecorationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setDecorationTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextInputModifierTest, DISABLED_setDecorationTestDecorationTypeValidValues, TestSize.Level1)
{
    Ark_TextDecorationOptions initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const std::string& expectedStr,
                          const Ark_TextDecorationType& value) {
        Ark_TextDecorationOptions inputValueDecoration = initValueDecoration;

        inputValueDecoration.type = value;
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
HWTEST_F(TextInputModifierTest, DISABLED_setDecorationTestDecorationTypeInvalidValues, TestSize.Level1)
{
    Ark_TextDecorationOptions initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Ark_TextDecorationType& value) {
        Ark_TextDecorationOptions inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        inputValueDecoration.type = value;
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
    Ark_TextDecorationOptions initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Ark_TextDecorationOptions inputValueDecoration = initValueDecoration;

        inputValueDecoration.color = value;
        modifier_->setDecoration(node_, &inputValueDecoration);
        auto jsonValue = GetJsonValue(node_);
        auto resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DECORATION_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DECORATION_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDecoration, attribute: decoration.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
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
HWTEST_F(TextInputModifierTest, DISABLED_setDecorationTestDecorationColorInvalidValues, TestSize.Level1)
{
    Ark_TextDecorationOptions initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_ResourceColor& value) {
        Ark_TextDecorationOptions inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        inputValueDecoration.color = value;
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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
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
HWTEST_F(TextInputModifierTest, DISABLED_setDecorationTestDecorationStyleValidValues, TestSize.Level1)
{
    Ark_TextDecorationOptions initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const std::string& expectedStr,
                          const Opt_TextDecorationStyle& value) {
        Ark_TextDecorationOptions inputValueDecoration = initValueDecoration;

        inputValueDecoration.style = value;
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
HWTEST_F(TextInputModifierTest, DISABLED_setDecorationTestDecorationStyleInvalidValues, TestSize.Level1)
{
    Ark_TextDecorationOptions initValueDecoration;

    // Initial setup
    initValueDecoration.type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    initValueDecoration.color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueDecoration.style =
        ArkValue<Opt_TextDecorationStyle>(std::get<1>(Fixtures::testFixtureEnumTextDecorationStyleValidValues[0]));

    auto checkValue = [this, &initValueDecoration](const std::string& input, const Opt_TextDecorationStyle& value) {
        Ark_TextDecorationOptions inputValueDecoration = initValueDecoration;

        modifier_->setDecoration(node_, &inputValueDecoration);
        inputValueDecoration.style = value;
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
    Ark_Union_Number_String_Resource initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueLetterSpacing](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueLetterSpacing = initValueLetterSpacing;

        inputValueLetterSpacing = value;
        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLetterSpacing, attribute: letterSpacing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setLetterSpacingTestLetterSpacingInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLetterSpacingTestLetterSpacingInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueLetterSpacing](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueLetterSpacing = initValueLetterSpacing;

        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        inputValueLetterSpacing = value;
        modifier_->setLetterSpacing(node_, &inputValueLetterSpacing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LETTER_SPACING_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LETTER_SPACING_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLetterSpacing, attribute: letterSpacing";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
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
    Ark_Union_Number_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueLineHeight = initValueLineHeight;

        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setLineHeightTestLineHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setLineHeightTestLineHeightInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueLineHeight = initValueLineHeight;

        modifier_->setLineHeight(node_, &inputValueLineHeight);
        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setPasswordRulesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordRulesTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_RULES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PASSWORD_RULES_DEFAULT_VALUE) << "Default value for attribute 'passwordRules'";
}

/*
 * @tc.name: setPasswordRulesTestPasswordRulesValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setPasswordRulesTestPasswordRulesValidValues, TestSize.Level1)
{
    Ark_String initValuePasswordRules;

    // Initial setup
    initValuePasswordRules = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValuePasswordRules](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValuePasswordRules = initValuePasswordRules;

        inputValuePasswordRules = value;
        modifier_->setPasswordRules(node_, &inputValuePasswordRules);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PASSWORD_RULES_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPasswordRules, attribute: passwordRules";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFontFeatureTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontFeatureTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE) << "Default value for attribute 'fontFeature'";
}

/*
 * @tc.name: setFontFeatureTestFontFeatureValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setFontFeatureTestFontFeatureValidValues, TestSize.Level1)
{
    Ark_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueFontFeature](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueFontFeature = initValueFontFeature;

        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setShowPasswordTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_PASSWORD_DEFAULT_VALUE) << "Default value for attribute 'showPassword'";
}

/*
 * @tc.name: setShowPasswordTestShowPasswordValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowPasswordTestShowPasswordValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowPassword;

    // Initial setup
    initValueShowPassword = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueShowPassword](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueShowPassword = initValueShowPassword;

        inputValueShowPassword = value;
        modifier_->setShowPassword(node_, inputValueShowPassword);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_PASSWORD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowPassword, attribute: showPassword";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setEnablePreviewTextTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnablePreviewTextTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_PREVIEW_TEXT_DEFAULT_VALUE) <<
        "Default value for attribute 'enablePreviewText'";
}

/*
 * @tc.name: setEnablePreviewTextTestEnablePreviewTextValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnablePreviewTextTestEnablePreviewTextValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnablePreviewText;

    // Initial setup
    initValueEnablePreviewText = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnablePreviewText](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnablePreviewText = initValueEnablePreviewText;

        inputValueEnablePreviewText = value;
        modifier_->setEnablePreviewText(node_, inputValueEnablePreviewText);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnablePreviewText, attribute: enablePreviewText";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE) <<
        "Default value for attribute 'enableHapticFeedback'";
}

/*
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableHapticFeedback](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setShowCounterTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowCounterTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultShowCounter =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_VALUE_DEFAULT_VALUE) <<
        "Default value for attribute 'showCounter.value'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_DEFAULT_VALUE) <<
        "Default value for attribute 'showCounter.options.thresholdPercentage'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_DEFAULT_VALUE) <<
        "Default value for attribute 'showCounter.options.highlightBorder'";
}

} // namespace OHOS::Ace::NG
