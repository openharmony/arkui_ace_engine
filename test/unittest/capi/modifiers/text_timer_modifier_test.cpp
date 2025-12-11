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
#include "generated/type_helpers.h"

#include "core/components_ng/pattern/texttimer/text_timer_event_hub.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"
#include "core/interfaces/native/implementation/text_timer_controller_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_TEXT_SHADOW_NAME = "textShadow";
const auto ATTRIBUTE_IS_COUNT_DOWN_NAME = "isCountDown";
const auto ATTRIBUTE_IS_COUNT_DOWN_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_COUNT_NAME = "count";
const auto ATTRIBUTE_COUNT_DEFAULT_VALUE = "60000.000000";
const auto ATTRIBUTE_CONTROLLER_NAME = "controller";
const auto ATTRIBUTE_CONTROLLER_DEFAULT_VALUE = "";
const auto ATTRIBUTE_FORMAT_NAME = "format";
const auto ATTRIBUTE_FORMAT_DEFAULT_VALUE = "HH:mm:ss.SS";
const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_FONT_STYLE_NAME = "fontStyle";
const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "fontFamily";
const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME = "radius";
const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME = "type";
const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE = "ShadowType.Color";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME = "color";
const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME = "offsetX";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME = "offsetY";
const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME = "fill";
const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE = "false";
} // namespace

class TextTimerModifierTest : public ModifierTestBase<GENERATED_ArkUITextTimerModifier,
    &GENERATED_ArkUINodeModifiers::getTextTimerModifier, GENERATED_ARKUI_TEXT_TIMER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setTextTimerOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextTimerOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_COUNT_DOWN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IS_COUNT_DOWN_DEFAULT_VALUE) << "Default value for attribute 'options.isCountDown'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COUNT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COUNT_DEFAULT_VALUE) << "Default value for attribute 'options.count'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CONTROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CONTROLLER_DEFAULT_VALUE) << "Default value for attribute 'options.controller'";
}

/*
 * @tc.name: setTextTimerOptionsTestCountDownValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextTimerOptionsTestCountDownValues, TestSize.Level1)
{
    Ark_Boolean isCountDown;

    // Initial setup
    isCountDown = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    Opt_TextTimerOptions opts = { .value = { .isCountDown = { .value = isCountDown } } };

    auto checkValue = [this, &opts](const std::string& input, const Ark_Boolean& value,
        const std::string& expectedStr) {
        Opt_TextTimerOptions options = opts;
        options.value.isCountDown = { .value = value };
        modifier_->setTextTimerOptions(node_, &options);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_COUNT_DOWN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextTimerOptions, attribute: isCountDown";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextTimerOptionsTestInputCountValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextTimerOptionsTestInputCountValidValues, TestSize.Level1)
{
    Ark_Number inputCount;

    // Initial setup
    inputCount = std::get<1>(Fixtures::testFixtureTimerInputCountValidValues[0]);
    Opt_TextTimerOptions opts = { .value = { .count = { .value = inputCount } } };

    auto checkValue = [this, &opts](const std::string& input, const Ark_Number& value,
        const std::string& expectedStr) {
        Opt_TextTimerOptions options = opts;

        options.value.isCountDown = { .value = Converter::ArkValue<Ark_Boolean>(true) };
        options.value.count = { .value = value };
        modifier_->setTextTimerOptions(node_, &options);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COUNT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextTimerOptions, attribute: count";

        // If isCountDown set to false, input count should have default value
        options.value.isCountDown = { .value = Converter::ArkValue<Ark_Boolean>(false) };
        options.value.count = { .value = value };
        modifier_->setTextTimerOptions(node_, &options);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COUNT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COUNT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextTimerOptions, attribute: count";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTimerInputCountValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setTextTimerOptionsTestInputCountInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextTimerOptionsTestInputCountInvalidValues, TestSize.Level1)
{
    Ark_Number inputCount;

    // Initial setup
    inputCount = std::get<1>(Fixtures::testFixtureTimerInputCountValidValues[0]);
    Opt_TextTimerOptions opts = { .value = { .count = { .value = inputCount } } };

    auto checkValue = [this, &opts](const std::string& input, const Ark_Number& value) {
        Opt_TextTimerOptions options = opts;

        options.value.isCountDown = { .value = Converter::ArkValue<Ark_Boolean>(true) };
        options.value.count = { .value = value };
        modifier_->setTextTimerOptions(node_, &options);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COUNT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COUNT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextTimerOptions, attribute: count";

        // If isCountDown set to false, input count should be default value
        options.value.isCountDown = { .value = Converter::ArkValue<Ark_Boolean>(false) };
        options.value.count = { .value = value };
        modifier_->setTextTimerOptions(node_, &options);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COUNT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COUNT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextTimerOptions, attribute: count";
    };

    for (auto& [input, value] : Fixtures::testFixtureTimerInputCountInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setTextTimerOptionsTestController
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextTimerOptionsTestController, TestSize.Level1)
{
    auto controllerPtr =
        fullAPI_->getAccessors()->getTextTimerControllerAccessor()->construct();
    ASSERT_NE(controllerPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    ASSERT_NE(pattern, nullptr);

    Opt_TextTimerOptions opts = Converter::ArkValue<Opt_TextTimerOptions>(Ark_TextTimerOptions{
        .controller = Converter::ArkValue<Opt_TextTimerController>(controllerPtr),
    });
    modifier_->setTextTimerOptions(node_, &opts);

    RefPtr<TextTimerController> controller = pattern->GetTextTimerController();
    ASSERT_NE(controller, nullptr);

    EXPECT_EQ(controllerPtr->GetController(), controller);

    auto finalizerPtr =
        fullAPI_->getAccessors()->getTextTimerControllerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(TextTimerControllerPeer *)>(finalizerPtr);
    ASSERT_NE(finalyzer, nullptr);
    finalyzer(controllerPtr);
}

/*
 * @tc.name: setFormatTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFormatTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FORMAT_DEFAULT_VALUE) << "Default value for attribute 'format'";
}

/*
 * @tc.name: setFormatTestFormatValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFormatTestFormatValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        auto format = Converter::ArkValue<Opt_String>(value);
        modifier_->setFormat(node_, &format);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextTimerDateFormatValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFormatTestFormatInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFormatTestFormatInvalidValues, TestSize.Level1)
{
    Ark_String initValueFormat;

    // Initial setup
    initValueFormat = std::get<1>(Fixtures::testFixtureTextTimerDateFormatValidValues[0]);

    auto checkValue = [this, &initValueFormat](const std::string& input, const Ark_String& value) {
        Opt_String inputValueFormat = Converter::ArkValue<Opt_String>(initValueFormat);

        modifier_->setFormat(node_, &inputValueFormat);
        inputValueFormat = Converter::ArkValue<Opt_String>(value);
        modifier_->setFormat(node_, &inputValueFormat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FORMAT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value] : Fixtures::testFixtureTextTimerDateFormatInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setFontColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) << "Default value for attribute 'fontColor'";
}

/*
 * @tc.name: setFontColorTestFontColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, DISABLED_setFontColorTestFontColorValidValues, TestSize.Level1)
{
    auto checkValue = [this](
                          const std::string& input, const Ark_ResourceColor& value, const std::string& expectedStr) {
        Opt_ResourceColor inputValueFontColor = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Int32>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontColorTestFontColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontColorTestFontColorInvalidValues, TestSize.Level1)
{
    Opt_ResourceColor initValueFontColor;

    // Initial setup
    initValueFontColor = Converter::ArkValue<Opt_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueFontColor](const std::string& input, const Ark_ResourceColor& value) {
        Opt_ResourceColor inputValueFontColor = initValueFontColor;

        modifier_->setFontColor(node_, &inputValueFontColor);
        inputValueFontColor = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setFontColor(node_, &inputValueFontColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontColor, attribute: fontColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) << "Default value for attribute 'fontSize'";
}

/*
 * @tc.name: setFontSizeTestFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontSizeTestFontSizeValidValues, TestSize.Level1)
{
    auto checkValue = [this](
                          const std::string& input, const Ark_Length& value, const std::string& expectedStr) {
        Opt_Length inputValueFontSize = Converter::ArkValue<Opt_Length>(value);
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Length, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    Opt_Length initValueFontSize;

    // Initial setup
    initValueFontSize = Converter::ArkUnion<Opt_Length, Ark_String>(
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueFontSize](const std::string& input, const Ark_Length& value) {
        Opt_Length inputValueFontSize = initValueFontSize;

        modifier_->setFontSize(node_, &inputValueFontSize);
        inputValueFontSize = Converter::ArkValue<Opt_Length>(value);
        modifier_->setFontSize(node_, &inputValueFontSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontSize, attribute: fontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, Converter::ArkUnion<Ark_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setFontStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE) << "Default value for attribute 'fontStyle'";
}

/*
 * @tc.name: setFontStyleTestFontStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontStyleTestFontStyleValidValues, TestSize.Level1)
{
    auto checkValue = [this](
                          const std::string& input, const Ark_FontStyle& value, const std::string& expectedStr) {
        Opt_FontStyle inputValueFontStyle = Converter::ArkValue<Opt_FontStyle>(value);
        modifier_->setFontStyle(node_, &inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontStyleValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFontStyleTestFontStyleInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontStyleTestFontStyleInvalidValues, TestSize.Level1)
{
    Opt_FontStyle initValueFontStyle;

    // Initial setup
    initValueFontStyle = Converter::ArkValue<Opt_FontStyle>(
        std::get<1>(Fixtures::testFixtureEnumFontStyleValidValues[0]));

    auto checkValue = [this, &initValueFontStyle](const std::string& input, const Ark_FontStyle& value) {
        Opt_FontStyle inputValueFontStyle = initValueFontStyle;

        modifier_->setFontStyle(node_, &inputValueFontStyle);
        inputValueFontStyle = Converter::ArkValue<Opt_FontStyle>(value);
        modifier_->setFontStyle(node_, &inputValueFontStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_STYLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontStyle, attribute: fontStyle";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFontStyleInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setFontWeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontWeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) << "Default value for attribute 'fontWeight'";
}

/*
 * @tc.name: setFontWeightTestFontWeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontWeightTestFontWeightValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input,
                          const Ark_Union_Number_FontWeight_ResourceStr& value, const std::string& expectedStr) {
        Opt_Union_Number_FontWeight_ResourceStr inputValueFontWeight =
            Converter::ArkValue<Opt_Union_Number_FontWeight_ResourceStr>(value);
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFontWeightValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightNumbersValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_ResourceStr, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontWeightStringsValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
            ArkUnion<Ark_ResourceStr, Ark_String>(value)), expected);
    }
}

/*
 * @tc.name: setFontWeightTestFontWeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontWeightTestFontWeightInvalidValues, TestSize.Level1)
{
    Opt_Union_Number_FontWeight_ResourceStr initValueFontWeight;

    // Initial setup
    initValueFontWeight = ArkUnion<Opt_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(
        std::get<1>(Fixtures::testFixtureEnumFontWeightValidValues[0]));

    auto checkValue = [this, &initValueFontWeight](
                          const std::string& input, const Ark_Union_Number_FontWeight_ResourceStr& value) {
        Opt_Union_Number_FontWeight_ResourceStr inputValueFontWeight = initValueFontWeight;

        modifier_->setFontWeight(node_, &inputValueFontWeight);
        inputValueFontWeight = Converter::ArkValue<Opt_Union_Number_FontWeight_ResourceStr>(value);
        modifier_->setFontWeight(node_, &inputValueFontWeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontWeight, attribute: fontWeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontWeightNumbersInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_ResourceStr, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontWeightStringsInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_ResourceStr, Ark_ResourceStr>(
            ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumFontWeightInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_FontWeight_ResourceStr, Ark_FontWeight>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_FontWeight_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setFontFamilyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontFamilyTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) << "Default value for attribute 'fontFamily'";
}

/*
 * @tc.name: setFontFamilyTestFontFamilyValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, DISABLED_setFontFamilyTestFontFamilyValidValues, TestSize.Level1)
{
    auto checkValue = [this](
                          const std::string& input, const Ark_ResourceStr& value, const std::string& expectedStr) {
        Opt_ResourceStr inputValueFontFamily = Converter::ArkValue<Opt_ResourceStr>(value);
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyResourceValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureFontFamilyStringValidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setFontFamilyTestFontFamilyInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setFontFamilyTestFontFamilyInvalidValues, TestSize.Level1)
{
    Opt_ResourceStr initValueFontFamily;

    // Initial setup
    initValueFontFamily =
        ArkUnion<Opt_ResourceStr, Ark_Resource>(std::get<1>(Fixtures::testFixtureFontFamilyResourceValidValues[0]));

    auto checkValue = [this, &initValueFontFamily](const std::string& input, const Ark_ResourceStr& value) {
        Opt_ResourceStr inputValueFontFamily = initValueFontFamily;

        modifier_->setFontFamily(node_, &inputValueFontFamily);
        inputValueFontFamily = Converter::ArkValue<Opt_ResourceStr>(value);
        modifier_->setFontFamily(node_, &inputValueFontFamily);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFontFamily, attribute: fontFamily";
    };

    for (auto& [input, value] : Fixtures::testFixtureFontFamilyResourceInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureFontFamilyStringInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, DISABLED_setTextShadowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTextShadow =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow..radius'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow..type'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow..color'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow..offsetX'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow..offsetY'";

    resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE) <<
        "Default value for attribute 'textShadow..fill'";
}

/*
 * @tc.name: setTextShadowTestTextShadowRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowRadiusValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Ark_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).radius = value;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..radius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowRadiusNumberValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowRadiusResValidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowRadiusInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Ark_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).radius = value;
        optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..radius";
    };

    for (auto& [input, value] : Fixtures::testFixtureShadowRadiusNumberInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureShadowRadiusResInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestTextShadowTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, DISABLED_setTextShadowTestTextShadowTypeValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_ShadowType& value, const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).type = value;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumShadowTypeValidValues) {
        checkValue(input, ArkValue<Opt_ShadowType>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, DISABLED_setTextShadowTestTextShadowTypeInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_ShadowType& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).type = value;
        optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_TYPE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..type";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumShadowTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, DISABLED_setTextShadowTestTextShadowColorValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input,
                          const Opt_Union_Color_String_Resource_ColoringStrategy& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).color = value;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureEnumColoringStrategyValidValues) {
        checkValue(
            input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowColorInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_Union_Color_String_Resource_ColoringStrategy& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).color = value;
        optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureEnumColoringStrategyInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>());
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowOffsetXValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetX = value;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetNumberValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetResValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowOffsetXInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetX = value;
        optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetX";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowOffsetYValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value,
                          const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetY = value;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetNumberValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_Resource, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetResValidValues) {
        checkValue(input, ArkUnion<Opt_Union_Number_Resource, Ark_Resource>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowOffsetYInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Union_Number_Resource& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).offsetY = value;
        optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..offsetY";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_Number_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_Number_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowFillValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowFillValidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).fill = value;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..fill";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, ArkValue<Opt_Boolean>(value), expected);
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowFillInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, setTextShadowTestTextShadowFillInvalidValues, TestSize.Level1)
{
    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).radius = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureEnumShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).color =
        ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetX = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).offsetY = ArkUnion<Opt_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(initValueTextShadow).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueTextShadow](const std::string& input, const Opt_Boolean& value) {
        Ark_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow = initValueTextShadow;
        auto optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        WriteToUnion<Ark_ShadowOptions>(inputValueTextShadow).fill = value;
        optValue = Converter::ArkValue<Opt_Union_ShadowOptions_Array_ShadowOptions>(inputValueTextShadow);
        modifier_->setTextShadow(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultTextShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEXT_SHADOW_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTextShadow, ATTRIBUTE_TEXT_SHADOW_I_FILL_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow..fill";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setOnScrollIndexTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerModifierTest, DISABLED_setOnTimerTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextTimerEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int64_t utc;
        int64_t elapsedTime;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    static constexpr int32_t contextId = 123;
    static bool isCalled = false;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Int64 utc, const Ark_Int64 elapsedTime) {
        isCalled = true;
        checkEvent = {
            .nodeId = resourceId,
            .utc = Converter::Convert<int64_t>(utc),
            .elapsedTime = Converter::Convert<int64_t>(elapsedTime)
        };
    };

    auto arkCallback = Converter::ArkValue<TimerCallback>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_TimerCallback>(arkCallback);
    modifier_->setOnTimer(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);

    // first: 12, last: 10
    isCalled = false;
    eventHub->FireChangeEvent(12, 10);
    ASSERT_TRUE(isCalled);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->utc, 12);
    EXPECT_EQ(checkEvent->elapsedTime, 10);

    // first: 5, last: 25
    isCalled = false;
    eventHub->FireChangeEvent(5, 25);
    ASSERT_TRUE(isCalled);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->utc, 5);
    EXPECT_EQ(checkEvent->elapsedTime, 25);
}
} // namespace OHOS::Ace::NG
