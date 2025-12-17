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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/components/progress/progress_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_STYLE_NAME = "style";
const auto ATTRIBUTE_STYLE_I_FONT_NAME = "font";
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_TOTAL_NAME = "total";
const auto ATTRIBUTE_TOTAL_DEFAULT_VALUE = "100.000000";
const auto ATTRIBUTE_TYPE_NAME = "type";
const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "ProgressStyle.Linear";
const auto ATTRIBUTE_COLOR_NAME = "color";
const auto ATTRIBUTE_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_STROKE_WIDTH_NAME = "strokeWidth";
const auto ATTRIBUTE_STYLE_I_STROKE_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_STYLE_I_STROKE_RADIUS_NAME = "strokeRadius";
const auto ATTRIBUTE_STYLE_I_STROKE_RADIUS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_SHADOW_NAME = "shadow";
const auto ATTRIBUTE_STYLE_I_SHADOW_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_STATUS_NAME = "status";
const auto ATTRIBUTE_STYLE_I_STATUS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_BORDER_COLOR_NAME = "borderColor";
const auto ATTRIBUTE_STYLE_I_BORDER_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_BORDER_WIDTH_NAME = "borderWidth";
const auto ATTRIBUTE_STYLE_I_BORDER_WIDTH_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_FONT_I_SIZE_NAME = "size";
const auto ATTRIBUTE_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_FONT_I_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_FONT_I_FAMILY_NAME = "family";
const auto ATTRIBUTE_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_FONT_I_STYLE_NAME = "style";
const auto ATTRIBUTE_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_STYLE_I_FONT_COLOR_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_SHOW_DEFAULT_PERCENTAGE_NAME = "showDefaultPercentage";
const auto ATTRIBUTE_STYLE_I_SHOW_DEFAULT_PERCENTAGE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_STYLE_I_SCALE_COUNT_NAME = "scaleCount";
const auto ATTRIBUTE_STYLE_I_SCALE_COUNT_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_STYLE_I_SCALE_WIDTH_NAME = "scaleWidth";
const auto ATTRIBUTE_STYLE_I_SCALE_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_NAME = "privacySensitive";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE = "false";
} // namespace

class ProgressModifierTest : public ModifierTestBase<GENERATED_ArkUIProgressModifier,
                                 &GENERATED_ArkUINodeModifiers::getProgressModifier, GENERATED_ARKUI_PROGRESS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ProgressTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setProgressOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setProgressOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'options.value'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TOTAL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TOTAL_DEFAULT_VALUE) << "Default value for attribute 'options.total'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) << "Default value for attribute 'options.type'";
}

/*
 * @tc.name: setProgressOptionsTestOptionsValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsValueValidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatNonNegValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPosValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.value = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatNonNegValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsValueInvalidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatNonNegValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPosValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Ark_Number& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.value = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.value";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberFloatNonNegInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsTotalValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsTotalValidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatNonNegValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPosValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.total = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TOTAL_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.total";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatPosValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsTotalInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsTotalInvalidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatNonNegValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPosValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Number& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.total = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TOTAL_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TOTAL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.total";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberFloatPosInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setProgressOptionsTestOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsTypeValidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatNonNegValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPosValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ProgressType& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.type = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureProgressTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ProgressType>(value));
    }
}

/*
 * @tc.name: setProgressOptionsTestOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestOptionsTypeInvalidValues, TestSize.Level1)
{
    Ark_ProgressOptions initValueOptions;

    // Initial setup
    initValueOptions.value = std::get<1>(Fixtures::testFixtureNumberFloatNonNegValidValues[0]);
    initValueOptions.total = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatPosValidValues[0]));
    initValueOptions.type = ArkValue<Opt_ProgressType>(std::get<1>(Fixtures::testFixtureProgressTypeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_ProgressType& value) {
        Ark_ProgressOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.type = value;
        modifier_->setProgressOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setProgressOptions, attribute: options.type";
    };

    for (auto& [input, value] : Fixtures::testFixtureProgressTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ProgressType>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ProgressType>());
}

/*
 * @tc.name: setValueTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setValueTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'value'";
}

/*
 * @tc.name: setValueTestValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setValueTestValueValidValues, TestSize.Level1)
{
    Opt_Number initValueValue;

    // Initial setup
    initValueValue = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatNonNegValidValues[0]));

    auto checkValue = [this, &initValueValue](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Number inputValueValue = initValueValue;

        inputValueValue = value;
        modifier_->setValue(node_, &inputValueValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setValue, attribute: value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberFloatNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setValueTestValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setValueTestValueInvalidValues, TestSize.Level1)
{
    Opt_Number initValueValue;

    // Initial setup
    initValueValue = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberFloatNonNegValidValues[0]));

    auto checkValue = [this, &initValueValue](const std::string& input, const Opt_Number& value) {
        Opt_Number inputValueValue = initValueValue;

        modifier_->setValue(node_, &inputValueValue);
        inputValueValue = value;
        modifier_->setValue(node_, &inputValueValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setValue, attribute: value";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberFloatNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_DEFAULT_VALUE) << "Default value for attribute 'color'";
}

/*
 * @tc.name: setColorTestColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setColorTestColorValidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_LinearGradient initValueColor;

    // Initial setup
    initValueColor = ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueColor](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_ResourceColor_LinearGradient& value) {
        Opt_Union_ResourceColor_LinearGradient inputValueColor = initValueColor;

        inputValueColor = value;
        modifier_->setColor(node_, &inputValueColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setColor, attribute: color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Int32>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Resource>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_String>(value)));
    }
}

/*
 * @tc.name: setColorTestColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setColorTestColorInvalidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_LinearGradient initValueColor;

    // Initial setup
    initValueColor = ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueColor](
                          const std::string& input, const Opt_Union_ResourceColor_LinearGradient& value) {
        Opt_Union_ResourceColor_LinearGradient inputValueColor = initValueColor;

        modifier_->setColor(node_, &inputValueColor);
        inputValueColor = value;
        modifier_->setColor(node_, &inputValueColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setColor, attribute: color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                              ArkUnion<Ark_ResourceColor, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(
                              ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(value)));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_Empty>(nullptr));
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_ResourceColor_LinearGradient>());
}

/*
 * @tc.name: setStyleTestStyleLinearStyleOptionsStrokeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleLinearStyleOptionsStrokeWidthValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_LinearStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_LinearStyleOptions>(WriteTo(initValueStyle)).strokeRadius =
        ArkUnion<Opt_Union_String_F64_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_LinearStyleOptions>(WriteTo(inputValueStyle)).strokeWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STROKE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.LinearStyleOptions.strokeWidth";
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
 * @tc.name: setStyleTestStyleLinearStyleOptionsStrokeWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleLinearStyleOptionsStrokeWidthInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_LinearStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_LinearStyleOptions>(WriteTo(initValueStyle)).strokeRadius =
        ArkUnion<Opt_Union_String_F64_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_LinearStyleOptions>(WriteTo(inputValueStyle)).strokeWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STROKE_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_STROKE_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.LinearStyleOptions.strokeWidth";
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
 * @tc.name: setStyleTestStyleLinearStyleOptionsStrokeRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleLinearStyleOptionsStrokeRadiusInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_LinearStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_LinearStyleOptions>(WriteTo(initValueStyle)).strokeRadius =
        ArkUnion<Opt_Union_String_F64_Resource, Ark_Number>(
            std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Union_String_F64_Resource& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_LinearStyleOptions>(WriteTo(inputValueStyle)).strokeRadius = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STROKE_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_STROKE_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.LinearStyleOptions.strokeRadius";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_F64_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_F64_Resource>());
}

/*
 * @tc.name: setStyleTestStyleRingStyleOptionsStrokeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleRingStyleOptionsStrokeWidthValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).shadow =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).status =
        ArkValue<Opt_ProgressStatus>(std::get<1>(Fixtures::testFixtureEnumProgressStatusValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_RingStyleOptions>(WriteTo(inputValueStyle)).strokeWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STROKE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.RingStyleOptions.strokeWidth";
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
 * @tc.name: setStyleTestStyleRingStyleOptionsStrokeWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleRingStyleOptionsStrokeWidthInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).shadow =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).status =
        ArkValue<Opt_ProgressStatus>(std::get<1>(Fixtures::testFixtureEnumProgressStatusValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_RingStyleOptions>(WriteTo(inputValueStyle)).strokeWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STROKE_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_STROKE_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.RingStyleOptions.strokeWidth";
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
 * @tc.name: setStyleTestStyleRingStyleOptionsShadowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleRingStyleOptionsShadowValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).shadow =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).status =
        ArkValue<Opt_ProgressStatus>(std::get<1>(Fixtures::testFixtureEnumProgressStatusValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_RingStyleOptions>(WriteTo(inputValueStyle)).shadow = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_SHADOW_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.RingStyleOptions.shadow";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleRingStyleOptionsShadowInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleRingStyleOptionsShadowInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).shadow =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).status =
        ArkValue<Opt_ProgressStatus>(std::get<1>(Fixtures::testFixtureEnumProgressStatusValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Boolean& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_RingStyleOptions>(WriteTo(inputValueStyle)).shadow = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_SHADOW_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_SHADOW_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.RingStyleOptions.shadow";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setStyleTestStyleRingStyleOptionsStatusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleRingStyleOptionsStatusValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).shadow =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).status =
        ArkValue<Opt_ProgressStatus>(std::get<1>(Fixtures::testFixtureEnumProgressStatusValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ProgressStatus& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_RingStyleOptions>(WriteTo(inputValueStyle)).status = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STATUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.RingStyleOptions.status";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumProgressStatusValidValues) {
        checkValue(input, expected, ArkValue<Opt_ProgressStatus>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleRingStyleOptionsStatusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleRingStyleOptionsStatusInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).shadow =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
    WriteToUnion<Ark_RingStyleOptions>(WriteTo(initValueStyle)).status =
        ArkValue<Opt_ProgressStatus>(std::get<1>(Fixtures::testFixtureEnumProgressStatusValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_ProgressStatus& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_RingStyleOptions>(WriteTo(inputValueStyle)).status = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STATUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_STATUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.RingStyleOptions.status";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumProgressStatusInvalidValues) {
        checkValue(input, ArkValue<Opt_ProgressStatus>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsBorderColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsBorderColorValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).borderColor = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.borderColor";
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
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsBorderColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsBorderColorInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).borderColor = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_BORDER_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_BORDER_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.borderColor";
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
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsBorderWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsBorderWidthValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).borderWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.borderWidth";
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
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsBorderWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsBorderWidthInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).borderWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_BORDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_BORDER_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.borderWidth";
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
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontSizeValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).font).size = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_STYLE_I_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.font.size";
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
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).font).size = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_STYLE_I_FONT_I_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_FONT_I_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.font.size";
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
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontWeightValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_FontWeight_Number_String& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).font).weight = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_STYLE_I_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.font.weight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const Opt_Union_FontWeight_Number_String& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).font).weight = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_STYLE_I_FONT_I_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_FONT_I_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.font.weight";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_FontWeight_Number_String>());
}

/*
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontFamilyValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).font).family = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_STYLE_I_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.font.family";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource, Ark_String>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Union_String_Resource& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).font).family = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_STYLE_I_FONT_I_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_FONT_I_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.font.family";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource>());
}

/*
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontStyleValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_FontStyle& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).font).style = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_STYLE_I_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.font.style";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, expected, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontStyleInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_FontStyle& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).font).style = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultFont = GetAttrValue<std::unique_ptr<JsonValue>>(resultStyle, ATTRIBUTE_STYLE_I_FONT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultFont, ATTRIBUTE_STYLE_I_FONT_I_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_FONT_I_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.font.style";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, ArkValue<Opt_FontStyle>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontColorValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).fontColor = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.fontColor";
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
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsFontColorInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_ResourceColor& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).fontColor = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.CapsuleStyleOptions.fontColor";
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
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsShowDefaultPercentageValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsShowDefaultPercentageValidValues,
    TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).showDefaultPercentage = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_SHOW_DEFAULT_PERCENTAGE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setStyle, attribute: style.CapsuleStyleOptions.showDefaultPercentage";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleCapsuleStyleOptionsShowDefaultPercentageInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleCapsuleStyleOptionsShowDefaultPercentageInvalidValues,
    TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).borderWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).size =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).weight =
        ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(
            std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).family =
        ArkUnion<Opt_Union_String_Resource, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    WriteTo(WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).font).style =
        ArkValue<Opt_FontStyle>(std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).fontColor =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(initValueStyle)).showDefaultPercentage =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Boolean& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_CapsuleStyleOptions>(WriteTo(inputValueStyle)).showDefaultPercentage = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_SHOW_DEFAULT_PERCENTAGE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_SHOW_DEFAULT_PERCENTAGE_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setStyle, attribute: style.CapsuleStyleOptions.showDefaultPercentage";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setStyleTestStyleProgressStyleOptionsStrokeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleProgressStyleOptionsStrokeWidthValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleCount =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(inputValueStyle)).strokeWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STROKE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.ProgressStyleOptions.strokeWidth";
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
 * @tc.name: setStyleTestStyleProgressStyleOptionsStrokeWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleProgressStyleOptionsStrokeWidthInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleCount =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(inputValueStyle)).strokeWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_STROKE_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_STROKE_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.ProgressStyleOptions.strokeWidth";
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
 * @tc.name: setStyleTestStyleProgressStyleOptionsScaleCountValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setStyleTestStyleProgressStyleOptionsScaleCountValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleCount =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(inputValueStyle)).scaleCount = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_SCALE_COUNT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.ProgressStyleOptions.scaleCount";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberPosIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setStyleTestStyleProgressStyleOptionsScaleCountInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setStyleTestStyleProgressStyleOptionsScaleCountInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleCount =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Number& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(inputValueStyle)).scaleCount = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_SCALE_COUNT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_SCALE_COUNT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.ProgressStyleOptions.scaleCount";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberPosIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Number>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setStyleTestStyleProgressStyleOptionsScaleWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setStyleTestStyleProgressStyleOptionsScaleWidthValidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleCount =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueStyle](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(inputValueStyle)).scaleWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_SCALE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.ProgressStyleOptions.scaleWidth";
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
 * @tc.name: setStyleTestStyleProgressStyleOptionsScaleWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setStyleTestStyleProgressStyleOptionsScaleWidthInvalidValues, TestSize.Level1)
{
    Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions initValueStyle;

    // Initial setup
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).strokeWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleCount =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberPosIntFloorValidValues[0]));
    WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(initValueStyle)).scaleWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueStyle](const std::string& input, const Opt_Length& value) {
        Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions inputValueStyle =
            initValueStyle;

        modifier_->setStyle(node_, &inputValueStyle);
        WriteToUnion<Ark_ProgressStyleOptions>(WriteTo(inputValueStyle)).scaleWidth = value;
        modifier_->setStyle(node_, &inputValueStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultStyle, ATTRIBUTE_STYLE_I_SCALE_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STYLE_I_SCALE_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStyle, attribute: style.ProgressStyleOptions.scaleWidth";
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
 * @tc.name: setPrivacySensitiveTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setPrivacySensitiveTestDefaultValues, TestSize.Level1)
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
HWTEST_F(ProgressModifierTest, DISABLED_setPrivacySensitiveTestPrivacySensitiveValidValues, TestSize.Level1)
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
HWTEST_F(ProgressModifierTest, setPrivacySensitiveTestPrivacySensitiveInvalidValues, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
