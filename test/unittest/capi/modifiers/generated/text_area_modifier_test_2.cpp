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

#include "text_area_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::TextArea;
/*
 * @tc.name: setMaxFontScaleTestMaxFontScaleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMaxFontScaleTestMaxFontScaleInvalidValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setHeightAdaptivePolicyTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setHeightAdaptivePolicyTestHeightAdaptivePolicyValidValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setHeightAdaptivePolicyTestHeightAdaptivePolicyInvalidValues, TestSize.Level1)
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
 * @tc.name: setMaxLinesTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setMaxLinesTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, DISABLED_setMaxLinesTestMaxLinesValidValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, DISABLED_setMaxLinesTestMaxLinesInvalidValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setWordBreakTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setWordBreakTestWordBreakValidValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setWordBreakTestWordBreakInvalidValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, DISABLED_setLineBreakStrategyTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setDecorationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setDecorationTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setDecorationTestDecorationTypeValidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(TextAreaModifierTest, setDecorationTestDecorationTypeInvalidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(TextAreaModifierTest, DISABLED_setDecorationTestDecorationColorValidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(TextAreaModifierTest, setDecorationTestDecorationColorInvalidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(TextAreaModifierTest, setDecorationTestDecorationStyleValidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(TextAreaModifierTest, setDecorationTestDecorationStyleInvalidValues, TestSize.Level1)
{
    Opt_TextDecorationOptions initValueDecoration;

    // Initial setup
    WriteTo(initValueDecoration).type = std::get<1>(Fixtures::testFixtureEnumTextDecorationTypeValidValues[0]);
    WriteTo(initValueDecoration).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
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
HWTEST_F(TextAreaModifierTest, setLetterSpacingTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, DISABLED_setLetterSpacingTestLetterSpacingValidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

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
 * @tc.name: setLetterSpacingTestLetterSpacingInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setLetterSpacingTestLetterSpacingInvalidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueLetterSpacing;

    // Initial setup
    initValueLetterSpacing = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

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
 * @tc.name: setLineHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setLineHeightTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, DISABLED_setLineHeightTestLineHeightValidValues, TestSize.Level1)
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

/*
 * @tc.name: setLineHeightTestLineHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setLineHeightTestLineHeightInvalidValues, TestSize.Level1)
{
    Opt_Union_F64_String_Resource initValueLineHeight;

    // Initial setup
    initValueLineHeight = ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueLineHeight](
                          const std::string& input, const Opt_Union_F64_String_Resource& value) {
        Opt_Union_F64_String_Resource inputValueLineHeight = initValueLineHeight;

        modifier_->setLineHeight(node_, &inputValueLineHeight);
        inputValueLineHeight = value;
        modifier_->setLineHeight(node_, &inputValueLineHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLineHeight, attribute: lineHeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_String_Resource>());
}

/*
 * @tc.name: setTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) << "Default value for attribute 'type'";
}

/*
 * @tc.name: setTypeTestTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTypeTestTypeValidValues, TestSize.Level1)
{
    Opt_TextAreaType initValueType;

    // Initial setup
    initValueType = ArkValue<Opt_TextAreaType>(std::get<1>(Fixtures::testFixtureEnumTextAreaTypeValidValues[0]));

    auto checkValue = [this, &initValueType](
                          const std::string& input, const std::string& expectedStr, const Opt_TextAreaType& value) {
        Opt_TextAreaType inputValueType = initValueType;

        inputValueType = value;
        modifier_->setType(node_, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setType, attribute: type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextAreaTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextAreaType>(value));
    }
}

/*
 * @tc.name: setTypeTestTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTypeTestTypeInvalidValues, TestSize.Level1)
{
    Opt_TextAreaType initValueType;

    // Initial setup
    initValueType = ArkValue<Opt_TextAreaType>(std::get<1>(Fixtures::testFixtureEnumTextAreaTypeValidValues[0]));

    auto checkValue = [this, &initValueType](const std::string& input, const Opt_TextAreaType& value) {
        Opt_TextAreaType inputValueType = initValueType;

        modifier_->setType(node_, &inputValueType);
        inputValueType = value;
        modifier_->setType(node_, &inputValueType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setType, attribute: type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextAreaTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_TextAreaType>(value));
    }
}

/*
 * @tc.name: setEnableAutoFillTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnableAutoFillTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setEnableAutoFillTestEnableAutoFillValidValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setEnableAutoFillTestEnableAutoFillInvalidValues, TestSize.Level1)
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
 * @tc.name: setContentTypeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setContentTypeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_TYPE_DEFAULT_VALUE) << "Default value for attribute 'contentType'";
}

/*
 * @tc.name: setContentTypeTestContentTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setContentTypeTestContentTypeValidValues, TestSize.Level1)
{
    Opt_ContentType initValueContentType;

    // Initial setup
    initValueContentType =
        ArkValue<Opt_ContentType>(std::get<1>(Fixtures::testFixtureTextInputContentTypeValidValues[0]));

    auto checkValue = [this, &initValueContentType](
                          const std::string& input, const std::string& expectedStr, const Opt_ContentType& value) {
        Opt_ContentType inputValueContentType = initValueContentType;

        inputValueContentType = value;
        modifier_->setContentType(node_, &inputValueContentType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setContentType, attribute: contentType";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputContentTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ContentType>(value));
    }
}

/*
 * @tc.name: setContentTypeTestContentTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setContentTypeTestContentTypeInvalidValues, TestSize.Level1)
{
    Opt_ContentType initValueContentType;

    // Initial setup
    initValueContentType =
        ArkValue<Opt_ContentType>(std::get<1>(Fixtures::testFixtureTextInputContentTypeValidValues[0]));

    auto checkValue = [this, &initValueContentType](const std::string& input, const Opt_ContentType& value) {
        Opt_ContentType inputValueContentType = initValueContentType;

        modifier_->setContentType(node_, &inputValueContentType);
        inputValueContentType = value;
        modifier_->setContentType(node_, &inputValueContentType);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTENT_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CONTENT_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setContentType, attribute: contentType";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputContentTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ContentType>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ContentType>());
}

/*
 * @tc.name: setFontFeatureTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontFeatureTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setFontFeatureTestFontFeatureValidValues, TestSize.Level1)
{
    Opt_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureFontFeatureStrValidValues[0]));

    auto checkValue = [this, &initValueFontFeature](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Opt_String inputValueFontFeature = initValueFontFeature;

        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFeatureStrValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setFontFeatureTestFontFeatureInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setFontFeatureTestFontFeatureInvalidValues, TestSize.Level1)
{
    Opt_String initValueFontFeature;

    // Initial setup
    initValueFontFeature = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureFontFeatureStrValidValues[0]));

    auto checkValue = [this, &initValueFontFeature](const std::string& input, const Opt_String& value) {
        Opt_String inputValueFontFeature = initValueFontFeature;

        modifier_->setFontFeature(node_, &inputValueFontFeature);
        inputValueFontFeature = value;
        modifier_->setFontFeature(node_, &inputValueFontFeature);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FEATURE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FEATURE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontFeature, attribute: fontFeature";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFeatureStrInvalidValues) {
        checkValue(input, ArkValue<Opt_String>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
}

/*
 * @tc.name: setEnablePreviewTextTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnablePreviewTextTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setEnablePreviewTextTestEnablePreviewTextValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnablePreviewText;

    // Initial setup
    initValueEnablePreviewText = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnablePreviewText](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnablePreviewText = initValueEnablePreviewText;

        inputValueEnablePreviewText = value;
        modifier_->setEnablePreviewText(node_, &inputValueEnablePreviewText);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnablePreviewText, attribute: enablePreviewText";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnablePreviewTextTestEnablePreviewTextInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnablePreviewTextTestEnablePreviewTextInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnablePreviewText;

    // Initial setup
    initValueEnablePreviewText = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnablePreviewText](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnablePreviewText = initValueEnablePreviewText;

        modifier_->setEnablePreviewText(node_, &inputValueEnablePreviewText);
        inputValueEnablePreviewText = value;
        modifier_->setEnablePreviewText(node_, &inputValueEnablePreviewText);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_PREVIEW_TEXT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_PREVIEW_TEXT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnablePreviewText, attribute: enablePreviewText";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextAreaModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableHapticFeedback](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, &inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnableHapticFeedbackTestEnableHapticFeedbackInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableHapticFeedback;

    // Initial setup
    initValueEnableHapticFeedback = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableHapticFeedback](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableHapticFeedback = initValueEnableHapticFeedback;

        modifier_->setEnableHapticFeedback(node_, &inputValueEnableHapticFeedback);
        inputValueEnableHapticFeedback = value;
        modifier_->setEnableHapticFeedback(node_, &inputValueEnableHapticFeedback);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableHapticFeedback, attribute: enableHapticFeedback";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setAutoCapitalizationModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setAutoCapitalizationModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_DEFAULT_VALUE) <<
        "Default value for attribute 'autoCapitalizationMode'";
}

/*
 * @tc.name: setAutoCapitalizationModeTestAutoCapitalizationModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setAutoCapitalizationModeTestAutoCapitalizationModeValidValues, TestSize.Level1)
{
    Opt_AutoCapitalizationMode initValueAutoCapitalizationMode;

    // Initial setup
    initValueAutoCapitalizationMode = ArkValue<Opt_AutoCapitalizationMode>(
        std::get<1>(Fixtures::testFixtureEnumAutoCapitalizationModeValidValues[0]));

    auto checkValue = [this, &initValueAutoCapitalizationMode](const std::string& input, const std::string& expectedStr,
                          const Opt_AutoCapitalizationMode& value) {
        Opt_AutoCapitalizationMode inputValueAutoCapitalizationMode = initValueAutoCapitalizationMode;

        inputValueAutoCapitalizationMode = value;
        modifier_->setAutoCapitalizationMode(node_, &inputValueAutoCapitalizationMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAutoCapitalizationMode, attribute: autoCapitalizationMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumAutoCapitalizationModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_AutoCapitalizationMode>(value));
    }
}

/*
 * @tc.name: setAutoCapitalizationModeTestAutoCapitalizationModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    TextAreaModifierTest, DISABLED_setAutoCapitalizationModeTestAutoCapitalizationModeInvalidValues, TestSize.Level1)
{
    Opt_AutoCapitalizationMode initValueAutoCapitalizationMode;

    // Initial setup
    initValueAutoCapitalizationMode = ArkValue<Opt_AutoCapitalizationMode>(
        std::get<1>(Fixtures::testFixtureEnumAutoCapitalizationModeValidValues[0]));

    auto checkValue = [this, &initValueAutoCapitalizationMode](
                          const std::string& input, const Opt_AutoCapitalizationMode& value) {
        Opt_AutoCapitalizationMode inputValueAutoCapitalizationMode = initValueAutoCapitalizationMode;

        modifier_->setAutoCapitalizationMode(node_, &inputValueAutoCapitalizationMode);
        inputValueAutoCapitalizationMode = value;
        modifier_->setAutoCapitalizationMode(node_, &inputValueAutoCapitalizationMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_CAPITALIZATION_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAutoCapitalizationMode, attribute: autoCapitalizationMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumAutoCapitalizationModeInvalidValues) {
        checkValue(input, ArkValue<Opt_AutoCapitalizationMode>(value));
    }
}

/*
 * @tc.name: setHalfLeadingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setHalfLeadingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HALF_LEADING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HALF_LEADING_DEFAULT_VALUE) << "Default value for attribute 'halfLeading'";
}

/*
 * @tc.name: setHalfLeadingTestHalfLeadingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setHalfLeadingTestHalfLeadingValidValues, TestSize.Level1)
{
    Opt_Boolean initValueHalfLeading;

    // Initial setup
    initValueHalfLeading = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueHalfLeading](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueHalfLeading = initValueHalfLeading;

        inputValueHalfLeading = value;
        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HALF_LEADING_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHalfLeading, attribute: halfLeading";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setHalfLeadingTestHalfLeadingInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setHalfLeadingTestHalfLeadingInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueHalfLeading;

    // Initial setup
    initValueHalfLeading = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueHalfLeading](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueHalfLeading = initValueHalfLeading;

        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        inputValueHalfLeading = value;
        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HALF_LEADING_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_HALF_LEADING_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setHalfLeading, attribute: halfLeading";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setEllipsisModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEllipsisModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ELLIPSIS_MODE_DEFAULT_VALUE) << "Default value for attribute 'ellipsisMode'";
}

/*
 * @tc.name: setEllipsisModeTestEllipsisModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEllipsisModeTestEllipsisModeValidValues, TestSize.Level1)
{
    Opt_EllipsisMode initValueEllipsisMode;

    // Initial setup
    initValueEllipsisMode =
        ArkValue<Opt_EllipsisMode>(std::get<1>(Fixtures::testFixtureEnumEllipsisModeValidValues[0]));

    auto checkValue = [this, &initValueEllipsisMode](
                          const std::string& input, const std::string& expectedStr, const Opt_EllipsisMode& value) {
        Opt_EllipsisMode inputValueEllipsisMode = initValueEllipsisMode;

        inputValueEllipsisMode = value;
        modifier_->setEllipsisMode(node_, &inputValueEllipsisMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEllipsisMode, attribute: ellipsisMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumEllipsisModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_EllipsisMode>(value));
    }
}

/*
 * @tc.name: setEllipsisModeTestEllipsisModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEllipsisModeTestEllipsisModeInvalidValues, TestSize.Level1)
{
    Opt_EllipsisMode initValueEllipsisMode;

    // Initial setup
    initValueEllipsisMode =
        ArkValue<Opt_EllipsisMode>(std::get<1>(Fixtures::testFixtureEnumEllipsisModeValidValues[0]));

    auto checkValue = [this, &initValueEllipsisMode](const std::string& input, const Opt_EllipsisMode& value) {
        Opt_EllipsisMode inputValueEllipsisMode = initValueEllipsisMode;

        modifier_->setEllipsisMode(node_, &inputValueEllipsisMode);
        inputValueEllipsisMode = value;
        modifier_->setEllipsisMode(node_, &inputValueEllipsisMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ELLIPSIS_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ELLIPSIS_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEllipsisMode, attribute: ellipsisMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumEllipsisModeInvalidValues) {
        checkValue(input, ArkValue<Opt_EllipsisMode>(value));
    }
}

/*
 * @tc.name: setStopBackPressTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setStopBackPressTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STOP_BACK_PRESS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STOP_BACK_PRESS_DEFAULT_VALUE) << "Default value for attribute 'stopBackPress'";
}

/*
 * @tc.name: setStopBackPressTestStopBackPressValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setStopBackPressTestStopBackPressValidValues, TestSize.Level1)
{
    Opt_Boolean initValueStopBackPress;

    // Initial setup
    initValueStopBackPress = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStopBackPress](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueStopBackPress = initValueStopBackPress;

        inputValueStopBackPress = value;
        modifier_->setStopBackPress(node_, &inputValueStopBackPress);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STOP_BACK_PRESS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStopBackPress, attribute: stopBackPress";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setStopBackPressTestStopBackPressInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setStopBackPressTestStopBackPressInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueStopBackPress;

    // Initial setup
    initValueStopBackPress = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStopBackPress](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueStopBackPress = initValueStopBackPress;

        modifier_->setStopBackPress(node_, &inputValueStopBackPress);
        inputValueStopBackPress = value;
        modifier_->setStopBackPress(node_, &inputValueStopBackPress);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STOP_BACK_PRESS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STOP_BACK_PRESS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStopBackPress, attribute: stopBackPress";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setKeyboardAppearanceTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setKeyboardAppearanceTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE) <<
        "Default value for attribute 'keyboardAppearance'";
}

/*
 * @tc.name: setKeyboardAppearanceTestKeyboardAppearanceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setKeyboardAppearanceTestKeyboardAppearanceValidValues, TestSize.Level1)
{
    Opt_KeyboardAppearance initValueKeyboardAppearance;

    // Initial setup
    initValueKeyboardAppearance =
        ArkValue<Opt_KeyboardAppearance>(std::get<1>(Fixtures::testFixtureEnumKeyboardAppearanceValidValues[0]));

    auto checkValue = [this, &initValueKeyboardAppearance](const std::string& input, const std::string& expectedStr,
                          const Opt_KeyboardAppearance& value) {
        Opt_KeyboardAppearance inputValueKeyboardAppearance = initValueKeyboardAppearance;

        inputValueKeyboardAppearance = value;
        modifier_->setKeyboardAppearance(node_, &inputValueKeyboardAppearance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setKeyboardAppearance, attribute: keyboardAppearance";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumKeyboardAppearanceValidValues) {
        checkValue(input, expected, ArkValue<Opt_KeyboardAppearance>(value));
    }
}

/*
 * @tc.name: setKeyboardAppearanceTestKeyboardAppearanceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setKeyboardAppearanceTestKeyboardAppearanceInvalidValues, TestSize.Level1)
{
    Opt_KeyboardAppearance initValueKeyboardAppearance;

    // Initial setup
    initValueKeyboardAppearance =
        ArkValue<Opt_KeyboardAppearance>(std::get<1>(Fixtures::testFixtureEnumKeyboardAppearanceValidValues[0]));

    auto checkValue = [this, &initValueKeyboardAppearance](
                          const std::string& input, const Opt_KeyboardAppearance& value) {
        Opt_KeyboardAppearance inputValueKeyboardAppearance = initValueKeyboardAppearance;

        modifier_->setKeyboardAppearance(node_, &inputValueKeyboardAppearance);
        inputValueKeyboardAppearance = value;
        modifier_->setKeyboardAppearance(node_, &inputValueKeyboardAppearance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setKeyboardAppearance, attribute: keyboardAppearance";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumKeyboardAppearanceInvalidValues) {
        checkValue(input, ArkValue<Opt_KeyboardAppearance>(value));
    }
}

/*
 * @tc.name: setShowCounterTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestDefaultValues, TestSize.Level1)
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

/*
 * @tc.name: setShowCounterTestShowCounterValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterValueValidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        inputValueValue = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShowCounter, attribute: showCounter.value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setShowCounterTestShowCounterValueInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        inputValueValue = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_VALUE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShowCounter, attribute: showCounter.value";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsThresholdPercentageValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterOptionsThresholdPercentageValidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).thresholdPercentage = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.thresholdPercentage";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPercentageThresholdFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsThresholdPercentageInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterOptionsThresholdPercentageInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        WriteTo(inputValueOptions).thresholdPercentage = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_THRESHOLD_PERCENTAGE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.thresholdPercentage";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPercentageThresholdFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsHighlightBorderValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterOptionsHighlightBorderValidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).highlightBorder = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setShowCounter, attribute: showCounter.options.highlightBorder";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setShowCounterTestShowCounterOptionsHighlightBorderInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setShowCounterTestShowCounterOptionsHighlightBorderInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueValue;
    Opt_InputCounterOptions initValueOptions;

    // Initial setup
    initValueValue = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueOptions).thresholdPercentage =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPercentageThresholdFloorValidValues[0]));
    WriteTo(initValueOptions).highlightBorder =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueValue, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueValue = initValueValue;
        Opt_InputCounterOptions inputValueOptions = initValueOptions;

        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        WriteTo(inputValueOptions).highlightBorder = value;
        modifier_->setShowCounter(node_, &inputValueValue, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultShowCounter = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SHOW_COUNTER_NAME);
        auto resultOptions =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultShowCounter, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultOptions, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_COUNTER_I_OPTIONS_I_HIGHLIGHT_BORDER_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setShowCounter, attribute: showCounter.options.highlightBorder";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}
} // namespace OHOS::Ace::NG
