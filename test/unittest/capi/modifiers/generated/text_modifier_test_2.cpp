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

#include "text_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Text;
/*
 * @tc.name: setWordBreakTestWordBreakValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setWordBreakTestWordBreakValidValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setWordBreakTestWordBreakInvalidValues, TestSize.Level1)
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
 * @tc.name: setLineBreakStrategyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setLineBreakStrategyTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setLineBreakStrategyTestLineBreakStrategyValidValues, TestSize.Level1)
{
    Opt_LineBreakStrategy initValueLineBreakStrategy;

    // Initial setup
    initValueLineBreakStrategy =
        ArkValue<Opt_LineBreakStrategy>(std::get<1>(Fixtures::testFixtureTextInputLineBreakStrategyValidValues[0]));

    auto checkValue = [this, &initValueLineBreakStrategy](const std::string& input, const std::string& expectedStr,
                          const Opt_LineBreakStrategy& value) {
        Opt_LineBreakStrategy inputValueLineBreakStrategy = initValueLineBreakStrategy;

        inputValueLineBreakStrategy = value;
        modifier_->setLineBreakStrategy(node_, &inputValueLineBreakStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLineBreakStrategy, attribute: lineBreakStrategy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextInputLineBreakStrategyValidValues) {
        checkValue(input, expected, ArkValue<Opt_LineBreakStrategy>(value));
    }
}

/*
 * @tc.name: setLineBreakStrategyTestLineBreakStrategyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setLineBreakStrategyTestLineBreakStrategyInvalidValues, TestSize.Level1)
{
    Opt_LineBreakStrategy initValueLineBreakStrategy;

    // Initial setup
    initValueLineBreakStrategy =
        ArkValue<Opt_LineBreakStrategy>(std::get<1>(Fixtures::testFixtureTextInputLineBreakStrategyValidValues[0]));

    auto checkValue = [this, &initValueLineBreakStrategy](
                          const std::string& input, const Opt_LineBreakStrategy& value) {
        Opt_LineBreakStrategy inputValueLineBreakStrategy = initValueLineBreakStrategy;

        modifier_->setLineBreakStrategy(node_, &inputValueLineBreakStrategy);
        inputValueLineBreakStrategy = value;
        modifier_->setLineBreakStrategy(node_, &inputValueLineBreakStrategy);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LINE_BREAK_STRATEGY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LINE_BREAK_STRATEGY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLineBreakStrategy, attribute: lineBreakStrategy";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextInputLineBreakStrategyInvalidValues) {
        checkValue(input, ArkValue<Opt_LineBreakStrategy>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_LineBreakStrategy>());
}

/*
 * @tc.name: setCaretColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setCaretColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE) << "Default value for attribute 'caretColor'";
}

/*
 * @tc.name: setCaretColorTestCaretColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setCaretColorTestCaretColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueCaretColor;

    // Initial setup
    initValueCaretColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueCaretColor = initValueCaretColor;

        inputValueCaretColor = value;
        modifier_->setCaretColor(node_, &inputValueCaretColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCaretColor, attribute: caretColor";
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
 * @tc.name: setCaretColorTestCaretColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setCaretColorTestCaretColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueCaretColor;

    // Initial setup
    initValueCaretColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueCaretColor](const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueCaretColor = initValueCaretColor;

        modifier_->setCaretColor(node_, &inputValueCaretColor);
        inputValueCaretColor = value;
        modifier_->setCaretColor(node_, &inputValueCaretColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CARET_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCaretColor, attribute: caretColor";
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
 * @tc.name: setSelectedBackgroundColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setSelectedBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'selectedBackgroundColor'";
}

/*
 * @tc.name: setSelectedBackgroundColorTestSelectedBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectedBackgroundColorTestSelectedBackgroundColorValidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedBackgroundColor;

    // Initial setup
    initValueSelectedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsAlpha20EnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedBackgroundColor](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedBackgroundColor = initValueSelectedBackgroundColor;

        inputValueSelectedBackgroundColor = value;
        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setSelectedBackgroundColor, attribute: selectedBackgroundColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsAlpha20EnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsAlpha20NumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsAlpha20ResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsAlpha20StrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setSelectedBackgroundColorTestSelectedBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setSelectedBackgroundColorTestSelectedBackgroundColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueSelectedBackgroundColor;

    // Initial setup
    initValueSelectedBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsAlpha20EnumValidValues[0]));

    auto checkValue = [this, &initValueSelectedBackgroundColor](
                          const std::string& input, const Opt_ResourceColor& value) {
        Opt_ResourceColor inputValueSelectedBackgroundColor = initValueSelectedBackgroundColor;

        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        inputValueSelectedBackgroundColor = value;
        modifier_->setSelectedBackgroundColor(node_, &inputValueSelectedBackgroundColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_BACKGROUND_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setSelectedBackgroundColor, attribute: selectedBackgroundColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsAlpha20EnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsAlpha20StrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setEllipsisModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEllipsisModeTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setEllipsisModeTestEllipsisModeValidValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setEllipsisModeTestEllipsisModeInvalidValues, TestSize.Level1)
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
 * @tc.name: setEnableDataDetectorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableDataDetectorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_DATA_DETECTOR_DEFAULT_VALUE) <<
        "Default value for attribute 'enableDataDetector'";
}

/*
 * @tc.name: setEnableDataDetectorTestEnableDataDetectorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableDataDetectorTestEnableDataDetectorValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableDataDetector;

    // Initial setup
    initValueEnableDataDetector = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableDataDetector](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableDataDetector = initValueEnableDataDetector;

        inputValueEnableDataDetector = value;
        modifier_->setEnableDataDetector(node_, &inputValueEnableDataDetector);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableDataDetector, attribute: enableDataDetector";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnableDataDetectorTestEnableDataDetectorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableDataDetectorTestEnableDataDetectorInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableDataDetector;

    // Initial setup
    initValueEnableDataDetector = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableDataDetector](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableDataDetector = initValueEnableDataDetector;

        modifier_->setEnableDataDetector(node_, &inputValueEnableDataDetector);
        inputValueEnableDataDetector = value;
        modifier_->setEnableDataDetector(node_, &inputValueEnableDataDetector);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_DATA_DETECTOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_DATA_DETECTOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableDataDetector, attribute: enableDataDetector";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setDataDetectorConfigTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDataDetectorConfigTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultDataDetectorConfig =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DATA_DETECTOR_CONFIG_NAME);
    std::unique_ptr<JsonValue> resultDecoration = GetAttrValue<std::unique_ptr<JsonValue>>(
        resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_TYPES_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.types'";

    resultStr = GetAttrValue<std::string>(resultDataDetectorConfig, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.decoration.type'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.decoration.color'";

    resultStr = GetAttrValue<std::string>(resultDecoration, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DATA_DETECTOR_CONFIG_I_DECORATION_I_STYLE_DEFAULT_VALUE) <<
        "Default value for attribute 'dataDetectorConfig.decoration.style'";
}

/*
 * @tc.name: setDataDetectorConfigTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setDataDetectorConfigTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setFontFeatureTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontFeatureTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setMarqueeOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMarqueeOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultMarqueeOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_START_DEFAULT_VALUE) <<
        "Default value for attribute 'marqueeOptions.start'";

    resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_STEP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_STEP_DEFAULT_VALUE) <<
        "Default value for attribute 'marqueeOptions.step'";

    resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_LOOP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_LOOP_DEFAULT_VALUE) <<
        "Default value for attribute 'marqueeOptions.loop'";

    resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_FROM_START_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_FROM_START_DEFAULT_VALUE) <<
        "Default value for attribute 'marqueeOptions.fromStart'";

    resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_DELAY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_DELAY_DEFAULT_VALUE) <<
        "Default value for attribute 'marqueeOptions.delay'";

    resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_FADEOUT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_FADEOUT_DEFAULT_VALUE) <<
        "Default value for attribute 'marqueeOptions.fadeout'";

    resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_DEFAULT_VALUE) <<
        "Default value for attribute 'marqueeOptions.marqueeStartPolicy'";
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsStartValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsStartValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).start = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_START_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.start";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsStepValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsStepValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).step = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_STEP_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.step";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextMarqueeStepValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsStepInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsStepInvalidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const Opt_Number& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        WriteTo(inputValueMarqueeOptions).step = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_STEP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_STEP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.step";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextMarqueeStepInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsLoopValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsLoopValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).loop = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_LOOP_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.loop";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextMarqueeLoopValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsLoopInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsLoopInvalidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const Opt_Number& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        WriteTo(inputValueMarqueeOptions).loop = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_LOOP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_LOOP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.loop";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsFromStartValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMarqueeOptionsTestMarqueeOptionsFromStartValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).fromStart = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_FROM_START_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.fromStart";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsFromStartInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMarqueeOptionsTestMarqueeOptionsFromStartInvalidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        WriteTo(inputValueMarqueeOptions).fromStart = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_FROM_START_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_FROM_START_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.fromStart";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsDelayValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsDelayValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).delay = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_DELAY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.delay";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsDelayInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsDelayInvalidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const Opt_Number& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        WriteTo(inputValueMarqueeOptions).delay = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_DELAY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_DELAY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.delay";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsFadeoutValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsFadeoutValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).fadeout = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_FADEOUT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.fadeout";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsFadeoutInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setMarqueeOptionsTestMarqueeOptionsFadeoutInvalidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        WriteTo(inputValueMarqueeOptions).fadeout = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_FADEOUT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_FADEOUT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMarqueeOptions, attribute: marqueeOptions.fadeout";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsMarqueeStartPolicyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMarqueeOptionsTestMarqueeOptionsMarqueeStartPolicyValidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_MarqueeStartPolicy& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        WriteTo(inputValueMarqueeOptions).marqueeStartPolicy = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setMarqueeOptions, attribute: marqueeOptions.marqueeStartPolicy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumMarqueeStartPolicyValidValues) {
        checkValue(input, expected, ArkValue<Opt_MarqueeStartPolicy>(value));
    }
}

/*
 * @tc.name: setMarqueeOptionsTestMarqueeOptionsMarqueeStartPolicyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setMarqueeOptionsTestMarqueeOptionsMarqueeStartPolicyInvalidValues, TestSize.Level1)
{
    Opt_TextMarqueeOptions initValueMarqueeOptions;

    // Initial setup
    WriteTo(initValueMarqueeOptions).start = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    WriteTo(initValueMarqueeOptions).step =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeStepValidValues[0]));
    WriteTo(initValueMarqueeOptions).loop =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureTextMarqueeLoopValidValues[0]));
    WriteTo(initValueMarqueeOptions).fromStart =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).delay =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));
    WriteTo(initValueMarqueeOptions).fadeout =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteTo(initValueMarqueeOptions).marqueeStartPolicy =
        ArkValue<Opt_MarqueeStartPolicy>(std::get<1>(Fixtures::testFixtureEnumMarqueeStartPolicyValidValues[0]));

    auto checkValue = [this, &initValueMarqueeOptions](const std::string& input, const Opt_MarqueeStartPolicy& value) {
        Opt_TextMarqueeOptions inputValueMarqueeOptions = initValueMarqueeOptions;

        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        WriteTo(inputValueMarqueeOptions).marqueeStartPolicy = value;
        modifier_->setMarqueeOptions(node_, &inputValueMarqueeOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultMarqueeOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_MARQUEE_OPTIONS_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultMarqueeOptions, ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MARQUEE_OPTIONS_I_MARQUEE_START_POLICY_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setMarqueeOptions, attribute: marqueeOptions.marqueeStartPolicy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumMarqueeStartPolicyInvalidValues) {
        checkValue(input, ArkValue<Opt_MarqueeStartPolicy>(value));
    }
}

/*
 * @tc.name: setPrivacySensitiveTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setPrivacySensitiveTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE) << "Default value for attribute 'privacySensitive'";
}

/*
 * @tc.name: setPrivacySensitiveTestPrivacySensitiveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setPrivacySensitiveTestPrivacySensitiveValidValues, TestSize.Level1)
{
    Opt_Boolean initValuePrivacySensitive;

    // Initial setup
    initValuePrivacySensitive = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValuePrivacySensitive](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValuePrivacySensitive = initValuePrivacySensitive;

        inputValuePrivacySensitive = value;
        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPrivacySensitive, attribute: privacySensitive";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setPrivacySensitiveTestPrivacySensitiveInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setPrivacySensitiveTestPrivacySensitiveInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValuePrivacySensitive;

    // Initial setup
    initValuePrivacySensitive = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValuePrivacySensitive](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValuePrivacySensitive = initValuePrivacySensitive;

        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        inputValuePrivacySensitive = value;
        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPrivacySensitive, attribute: privacySensitive";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setTextSelectableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextSelectableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_SELECTABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SELECTABLE_DEFAULT_VALUE) << "Default value for attribute 'textSelectable'";
}

/*
 * @tc.name: setTextSelectableTestTextSelectableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextSelectableTestTextSelectableValidValues, TestSize.Level1)
{
    Opt_TextSelectableMode initValueTextSelectable;

    // Initial setup
    initValueTextSelectable =
        ArkValue<Opt_TextSelectableMode>(std::get<1>(Fixtures::testFixtureTextSelectableModeValidValues[0]));

    auto checkValue = [this, &initValueTextSelectable](const std::string& input, const std::string& expectedStr,
                          const Opt_TextSelectableMode& value) {
        Opt_TextSelectableMode inputValueTextSelectable = initValueTextSelectable;

        inputValueTextSelectable = value;
        modifier_->setTextSelectable(node_, &inputValueTextSelectable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_SELECTABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextSelectable, attribute: textSelectable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextSelectableModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_TextSelectableMode>(value));
    }
}

/*
 * @tc.name: setTextSelectableTestTextSelectableInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setTextSelectableTestTextSelectableInvalidValues, TestSize.Level1)
{
    Opt_TextSelectableMode initValueTextSelectable;

    // Initial setup
    initValueTextSelectable =
        ArkValue<Opt_TextSelectableMode>(std::get<1>(Fixtures::testFixtureTextSelectableModeValidValues[0]));

    auto checkValue = [this, &initValueTextSelectable](const std::string& input, const Opt_TextSelectableMode& value) {
        Opt_TextSelectableMode inputValueTextSelectable = initValueTextSelectable;

        modifier_->setTextSelectable(node_, &inputValueTextSelectable);
        inputValueTextSelectable = value;
        modifier_->setTextSelectable(node_, &inputValueTextSelectable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_SELECTABLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SELECTABLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextSelectable, attribute: textSelectable";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextSelectableModeInvalidValues) {
        checkValue(input, ArkValue<Opt_TextSelectableMode>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_TextSelectableMode>());
}

/*
 * @tc.name: setHalfLeadingTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setHalfLeadingTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setEnableHapticFeedbackTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setEnableHapticFeedbackTestDefaultValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackValidValues, TestSize.Level1)
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
HWTEST_F(TextModifierTest, setEnableHapticFeedbackTestEnableHapticFeedbackInvalidValues, TestSize.Level1)
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
 * @tc.name: setFontTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
    std::unique_ptr<JsonValue> resultOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE) << "Default value for attribute 'font.size'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'font.weight'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE) << "Default value for attribute 'font.family'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE) << "Default value for attribute 'font.style'";

    resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'options.enableVariableFontWeight'";
}

/*
 * @tc.name: setFontTestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontTestFontSizeValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueFont).size = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.size";
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
 * @tc.name: setFontTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](const std::string& input, const Opt_Length& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        WriteTo(inputValueFont).size = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.size";
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
 * @tc.name: setFontTestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontTestFontWeightValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](const std::string& input,
                          const std::string& expectedStr, const Opt_Union_FontWeight_Number_String& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueFont).weight = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        WriteTo(inputValueFont).weight = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_Number_String>());
}

/*
 * @tc.name: setFontTestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontTestFontFamilyValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](const std::string& input,
                          const std::string& expectedStr, const Opt_Union_String_Resource& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueFont).family = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontTestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](
                          const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        WriteTo(inputValueFont).family = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.family";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setFontTestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontTestFontStyleValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueFont).style = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFont, attribute: font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontTestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontTestFontStyleInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](const std::string& input, const Opt_FontStyle& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        WriteTo(inputValueFont).style = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setFontTestOptionsEnableVariableFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontTestOptionsEnableVariableFontWeightValidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        WriteTo(inputValueOptions).enableVariableFontWeight = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFont, attribute: options.enableVariableFontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setFontTestOptionsEnableVariableFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setFontTestOptionsEnableVariableFontWeightInvalidValues, TestSize.Level1)
{
    Opt_arkui_component_units_Font initValueFont;
    Opt_FontSettingOptions initValueOptions;

    // Initial setup
    WriteTo(initValueFont).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueFont).weight = ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).family = ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));
    WriteTo(initValueFont).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteTo(initValueOptions).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFont, &initValueOptions](const std::string& input, const Opt_Boolean& value) {
        Opt_arkui_component_units_Font inputValueFont = initValueFont;
        Opt_FontSettingOptions inputValueOptions = initValueOptions;

        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        WriteTo(inputValueOptions).enableVariableFontWeight = value;
        modifier_->setFont(node_, &inputValueFont, &inputValueOptions);
        auto jsonValue = GetJsonValue(node_);
        auto resultOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultOptions, ATTRIBUTE_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OPTIONS_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFont, attribute: options.enableVariableFontWeight";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'fontWeight'";

    resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'font.enableVariableFontWeight'";
}

/*
 * @tc.name: setFontWeightTestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;
    Opt_FontSettingOptions initValueFont;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontWeight, &initValueFont](const std::string& input,
                          const std::string& expectedStr, const Opt_Union_Number_FontWeight_String& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;
        Opt_FontSettingOptions inputValueFont = initValueFont;

        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;
    Opt_FontSettingOptions initValueFont;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontWeight, &initValueFont](
                          const std::string& input, const Opt_Union_Number_FontWeight_String& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;
        Opt_FontSettingOptions inputValueFont = initValueFont;

        modifier_->setFontWeight(node_, &inputValueFontWeight, &inputValueFont);
        inputValueFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_FontWeight_String>());
}

/*
 * @tc.name: setFontWeightTestFontEnableVariableFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestFontEnableVariableFontWeightValidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;
    Opt_FontSettingOptions initValueFont;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontWeight, &initValueFont](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;
        Opt_FontSettingOptions inputValueFont = initValueFont;

        WriteTo(inputValueFont).enableVariableFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: font.enableVariableFontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setFontWeightTestFontEnableVariableFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, setFontWeightTestFontEnableVariableFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_String initValueFontWeight;
    Opt_FontSettingOptions initValueFont;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(initValueFont).enableVariableFontWeight =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFontWeight, &initValueFont](const std::string& input, const Opt_Boolean& value) {
        Opt_Union_Number_FontWeight_String inputValueFontWeight = initValueFontWeight;
        Opt_FontSettingOptions inputValueFont = initValueFont;

        modifier_->setFontWeight(node_, &inputValueFontWeight, &inputValueFont);
        WriteTo(inputValueFont).enableVariableFontWeight = value;
        modifier_->setFontWeight(node_, &inputValueFontWeight, &inputValueFont);
        auto jsonValue = GetJsonValue(node_);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_FONT_I_ENABLE_VARIABLE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_I_ENABLE_VARIABLE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: font.enableVariableFontWeight";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setSelectionTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextModifierTest, DISABLED_setSelectionTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}
} // namespace OHOS::Ace::NG
