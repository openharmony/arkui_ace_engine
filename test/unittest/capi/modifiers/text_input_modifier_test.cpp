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

#include "test/unittest/capi/modifiers/generated/text_input_modifier_test.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace Converter;
using namespace TypeHelper;
using namespace TestConst::TextInput;

class TextInputModifierTestNonGenerated : public ModifierTestBase<GENERATED_ArkUITextInputModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextInputModifier, GENERATED_ARKUI_TEXT_INPUT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextFieldTheme>();
        for (auto& [id, strid, res]: Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setUnderlineColorTestUnderlineColorTypingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorTypingValidValues, TestSize.Level1)
{
    Ark_Union_ResourceColor_UnderlineColor_Undefined initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).typing =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).normal =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).error =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).disable =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueUnderlineColor](const std::string& input,
                          const Opt_Union_ResourceColor_Undefined& value, const std::string& expectedStr) {
        Ark_Union_ResourceColor_UnderlineColor_Undefined inputValueUnderlineColor = initValueUnderlineColor;

        WriteToUnion<Ark_UnderlineColor>(inputValueUnderlineColor).typing = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_TYPING_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setUnderlineColor, attribute: underlineColor..typing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Color>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Number>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Resource>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_String>(value)), expected);
    }
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorNormalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorNormalValidValues, TestSize.Level1)
{
    Ark_Union_ResourceColor_UnderlineColor_Undefined initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).typing =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).normal =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).error =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).disable =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueUnderlineColor](const std::string& input,
                          const Opt_Union_ResourceColor_Undefined& value, const std::string& expectedStr) {
        Ark_Union_ResourceColor_UnderlineColor_Undefined inputValueUnderlineColor = initValueUnderlineColor;

        WriteToUnion<Ark_UnderlineColor>(inputValueUnderlineColor).normal = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_NORMAL_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setUnderlineColor, attribute: underlineColor..normal";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Color>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Number>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Resource>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_String>(value)), expected);
    }
}

/*
 * @tc.name: setUnderlineColorTestUnderlineColorErrorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorErrorValidValues, TestSize.Level1)
{
    Ark_Union_ResourceColor_UnderlineColor_Undefined initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).typing =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).normal =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).error =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).disable =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueUnderlineColor](const std::string& input,
                          const Opt_Union_ResourceColor_Undefined& value, const std::string& expectedStr) {
        Ark_Union_ResourceColor_UnderlineColor_Undefined inputValueUnderlineColor = initValueUnderlineColor;

        WriteToUnion<Ark_UnderlineColor>(inputValueUnderlineColor).error = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_ERROR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setUnderlineColor, attribute: underlineColor..error";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Color>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Number>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Resource>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_String>(value)), expected);
    }
}
/*
 * @tc.name: setUnderlineColorTestUnderlineColorDisableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setUnderlineColorTestUnderlineColorDisableValidValues, TestSize.Level1)
{
    Ark_Union_ResourceColor_UnderlineColor_Undefined initValueUnderlineColor;

    // Initial setup
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).typing =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).normal =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).error =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));
    WriteToUnion<Ark_UnderlineColor>(initValueUnderlineColor).disable =
        ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueUnderlineColor](const std::string& input,
                          const Opt_Union_ResourceColor_Undefined& value, const std::string& expectedStr) {
        Ark_Union_ResourceColor_UnderlineColor_Undefined inputValueUnderlineColor = initValueUnderlineColor;

        WriteToUnion<Ark_UnderlineColor>(inputValueUnderlineColor).disable = value;
        modifier_->setUnderlineColor(node_, &inputValueUnderlineColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultUnderlineColor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_UNDERLINE_COLOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultUnderlineColor, ATTRIBUTE_UNDERLINE_COLOR_I_DISABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setUnderlineColor, attribute: underlineColor..disable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Color>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Number>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Resource>(value)), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_Undefined, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_String>(value)), expected);
    }
}

/*
 * @tc.name: setCaretPositionTestCaretPositionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretPositionTestCaretPositionValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input) {
        auto textLength = input.length();
        std::vector<int32_t> invalidPositionValues = {
            -1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), textLength + 1
        };

        Opt_TextInputOptions textInputOptions = {};
        textInputOptions.value.text = ArkUnion<Opt_ResourceStr, Ark_String>(input);
        modifier_->setTextInputOptions(node_, &textInputOptions);
        for (auto index = 0; index <= textLength; index++) {
            auto testValue = Converter::ArkValue<Ark_Number>(index);
            modifier_->setCaretPosition(node_, &testValue);
            auto jsonValue = GetJsonValue(node_);
            auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
            EXPECT_EQ(resultStr, std::to_string(index))
                << "Input value is: " << input << ", method: setCaretPosition, attribute: caretPosition: "
                << index;
        }
        for (auto index = static_cast<int>(textLength); index >= 0; index--) {
            auto testValue = Converter::ArkValue<Ark_Number>(index);
            modifier_->setCaretPosition(node_, &testValue);
            auto jsonValue = GetJsonValue(node_);
            auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
            EXPECT_EQ(resultStr, std::to_string(index))
                << "Input value is: " << input << ", method: setCaretPosition (reverse), attribute: caretPosition: "
                << index;
        }
        for (auto invalidIndex: invalidPositionValues) {
            auto testValue = Converter::ArkValue<Ark_Number>(invalidIndex);
            modifier_->setCaretPosition(node_, &testValue);
            auto jsonValue = GetJsonValue(node_);
            auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
            std::string expectedResult =
                invalidIndex < 0 ? ATTRIBUTE_CARET_POSITION_DEFAULT_VALUE : std::to_string(textLength);
            EXPECT_EQ(resultStr, expectedResult)
                << "Input value is: " << input
                << ", method: setCaretPosition exeed than Text length, attribute: caretPosition: " << invalidIndex;
        }
    };

    for (auto& [input, value, unusedStr] : Fixtures::testFixtureTextInputCaretPositionValidValues) {
        checkValue(input);
    }
}

} // namespace OHOS::Ace::NG
