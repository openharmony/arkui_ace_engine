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

#include "core/interfaces/native/implementation/text_clock_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/text_clock/text_clock_event_hub.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

using namespace Converter;
using namespace TypeHelper;

namespace  {
    const auto ATTRIBUTE_TIME_ZONE_OFFSET_NAME = "timeZoneOffset";
    const auto ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE = "0.000000";
    const auto ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE = "0.000000";
    const auto ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE = "0.000000";
    const auto ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE = "0.000000";
    const auto ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE = "false";

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureShadowRadiusNumberValidValues = {
    { "123", Converter::ArkValue<Ark_Float64>(123.), "123.000000" },
    { "0", Converter::ArkValue<Ark_Float64>(0.), "0.000000" },
    { "1.23", Converter::ArkValue<Ark_Float64>(1.23), "1.230000" },
};

std::vector<std::tuple<std::string, Ark_Float64>> testFixtureShadowRadiusNumberInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Float64>(-1.) },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureShadowOffsetNumberValidValues = {
    { "123", Converter::ArkValue<Ark_Float64>(123.), "123.000000" },
    { "0", Converter::ArkValue<Ark_Float64>(0.), "0.000000" },
    { "1.23", Converter::ArkValue<Ark_Float64>(1.23), "1.230000" },
    { "-1.23", Converter::ArkValue<Ark_Float64>(-1.23), "-1.230000" },
    { "6.54", Converter::ArkValue<Ark_Float64>(6.54), "6.540000" },
    { "-99", Converter::ArkValue<Ark_Float64>(-99.), "-99.000000" },
    { "100", Converter::ArkValue<Ark_Float64>(100.), "100.000000" },
};
} // namespace

class TextClockModifierTest : public ModifierTestBase<GENERATED_ArkUITextClockModifier,
                                &GENERATED_ArkUINodeModifiers::getTextClockModifier, GENERATED_ARKUI_TEXT_CLOCK> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }

    void InitTextShadow(Ark_Union_ShadowOptions_Array_ShadowOptions &options);
};

void TextClockModifierTest::InitTextShadow(Ark_Union_ShadowOptions_Array_ShadowOptions &options)
{
    WriteToUnion<Ark_ShadowOptions>(options).radius = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(
        std::get<1>(testFixtureShadowRadiusNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(options).type =
        ArkValue<Opt_ShadowType>(std::get<1>(Fixtures::testFixtureShadowTypeValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(options).color =
        ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_arkui_component_enums_Color>(
            std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(options).offsetX = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(
        std::get<1>(testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(options).offsetY = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(
        std::get<1>(testFixtureShadowOffsetNumberValidValues[0]));
    WriteToUnion<Ark_ShadowOptions>(options).fill =
        ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));
}

/*
 * @tc.name: setTextClockOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextClockOptionsTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextClockOptions, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setTextClockOptions(node_, nullptr);
    auto controllerUndef = Converter::ArkValue<Opt_TextClockOptions>();
    modifier_->setTextClockOptions(node_, &controllerUndef);

    bool checkInvokeStart = false;
    bool checkInvokeStop = false;
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto internalController = TextClockModelNG::InitTextController(frameNode);
    ASSERT_NE(internalController, nullptr);
    internalController->OnStart([&checkInvokeStart]() {
        checkInvokeStart = true;
    });
    internalController->OnStop([&checkInvokeStop]() {
        checkInvokeStop = true;
    });

    TextClockControllerPeer peer;
    Opt_TextClockOptions realInputValue = Converter::ArkValue<Opt_TextClockOptions>(Ark_TextClockOptions{
        .timeZoneOffset = Converter::ArkValue<Opt_Float64>(0.),
        .controller = Converter::ArkValue<Opt_TextClockController>(&peer),
    });
    modifier_->setTextClockOptions(node_, &realInputValue);

    ASSERT_NE(peer.controller, nullptr);

    // check initial state of invoke start
    EXPECT_FALSE(checkInvokeStart);
    peer.controller->Start();
    EXPECT_TRUE(checkInvokeStart);

    // check initial state of invoke stop
    EXPECT_FALSE(checkInvokeStop);
    peer.controller->Stop();
    EXPECT_TRUE(checkInvokeStop);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'options.timeZoneOffset'";
}

// Valid values for attribute 'options' of method 'setTextClockOptions'
static std::vector<std::tuple<std::string, Opt_TextClockOptions, std::string>> setTextClockOptionsOptionsValidValues = {
    {
        "12.000000",
        Converter::ArkValue<Opt_TextClockOptions>(
            Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Float64>(12.)}),
        "12.000000"
    }, {
        "-14.000000",
        Converter::ArkValue<Opt_TextClockOptions>(
            Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Float64>(-14.)}),
        "-14.000000"
    }, {
        "9.500000", Converter::ArkValue<Opt_TextClockOptions>(
            Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Float64>(9.5)}),
        "9.500000"
    }, {
        "-5.750000", Converter::ArkValue<Opt_TextClockOptions>(
            Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Float64>(-5.75)}),
        "-5.750000"
    },
};

/*
 * @tc.name: setTextClockOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextClockOptionsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Opt_TextClockOptions inputValueOptions = Converter::ArkValue<Opt_TextClockOptions>();

    // Verifying attribute's  values
    for (auto& [print, input, expectedStr]: setTextClockOptionsOptionsValidValues) {
        inputValueOptions = input;
        modifier_->setTextClockOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << print;
    }
}

// Invalid values for attribute 'options' of method 'setTextClockOptions'
static std::vector<std::tuple<std::string, Opt_TextClockOptions>> setTextClockOptionsOptionsInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_TextClockOptions>(Ark_Empty())},
    {"20.000000", Converter::ArkValue<Opt_TextClockOptions>(
        Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Float64>(20.)})},
    {"-20.000000", Converter::ArkValue<Opt_TextClockOptions>(
        Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Float64>(-20.)})},
};

/*
 * @tc.name: setTextClockOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextClockOptionsTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_TextClockOptions realInputValue = Converter::ArkValue<Opt_TextClockOptions>();
    Ark_TextClockOptions& inputValueOptions = realInputValue.value;
    Ark_TextClockOptions initValueOptions;

    // Verifying attribute's  values
    for (auto&& value: setTextClockOptionsOptionsInvalidValues) {
        inputValueOptions = initValueOptions;
        modifier_->setTextClockOptions(node_, &realInputValue);
        inputValueOptions = std::get<1>(value).value;
        modifier_->setTextClockOptions(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
        expectedStr = ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOnDateChange
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setOnDateChange, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDateChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextClockEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int64_t index;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onDateChange = [](Ark_Int32 nodeId, const Ark_Int64 index) {
        checkEvent = {
            .nodeId = nodeId,
            .index = Converter::Convert<int64_t>(index),
        };
    };

    auto callBackValue = Converter::ArkCallback<Opt_Callback_I64_Void>(onDateChange, frameNode->GetId());
    modifier_->setOnDateChange(node_, &callBackValue);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireChangeEvent("55");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 55);
    eventHub->FireChangeEvent("0");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 0);
}

/*
 * @tc.name: setFontSizeTestFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, DISABLED_setFontSizeTestFontSizeInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontSize, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    // Initial setup
    auto initValueFontSize = Converter::ArkValue<Opt_Length>("123vp");

    auto checkValue = [this, frameNode, &initValueFontSize](const std::string& input, const Opt_Length& value) {
        auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
        ASSERT_NE(textClockProperty, nullptr);

        modifier_->setFontSize(node_, &initValueFontSize);
        EXPECT_TRUE(textClockProperty->GetFontSize().has_value());
        modifier_->setFontSize(node_, &value);
        EXPECT_FALSE(textClockProperty->GetFontSize().has_value());
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, Converter::ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setTextShadowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    EXPECT_FALSE(textClockProperty->GetTextShadow().has_value());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsRadiusValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, frameNode, &initValueTextShadow](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_F64_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).radius =
            Converter::ArkValue<Opt_Union_F64_Resource>(value);
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
        ASSERT_NE(textClockProperty, nullptr);
        ASSERT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto radius = resultShadow.GetBlurRadius();
        auto resultStr = std::to_string(radius);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.radius";
    };

    for (auto& [input, value, expected] : testFixtureShadowRadiusNumberValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowRadiusResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsRadiusInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
        const std::string& input, const Ark_Union_F64_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).radius =
            Converter::ArkValue<Opt_Union_F64_Resource>(value);
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto radius = resultShadow.GetBlurRadius();
        auto resultStr = std::to_string(radius);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_RADIUS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.radius";
    };

    for (auto& [input, value] : testFixtureShadowRadiusNumberInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureShadowRadiusResInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_F64_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_F64_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsTypeValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
                          const std::string& input, const std::string& expectedStr, const Opt_ShadowType& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto type = resultShadow.GetShadowType();
        auto resultStr = std::to_string(static_cast<int>(type));
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.type";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureShadowTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ShadowType>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsTypeInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
        const std::string& input, const Opt_ShadowType& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).type = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto type = resultShadow.GetShadowType();
        auto resultStr = std::to_string(static_cast<int>(type));
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.type";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ShadowType>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsColorValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
        const std::string& input, const std::string& expectedStr,
                          const Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto color = resultShadow.GetColor();
        auto resultStr = color.ToString();
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDummyColoringStrategyValidValues) {
        checkValue(
            input, expected, ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsColorInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
                          const std::string& input, const Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).color = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto color = resultShadow.GetColor();
        auto resultStr = color.ToString();
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetXValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
        const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto offsetX = resultShadow.GetOffset().GetX();
        auto resultStr = std::to_string(offsetX);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetX";
    };

    for (auto& [input, value, expected] : testFixtureShadowOffsetNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetXInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
        const std::string& input, const Opt_Union_F64_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetX = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto offsetX = resultShadow.GetOffset().GetX();
        auto resultStr = std::to_string(offsetX);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetX";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetYValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
        const std::string& input, const std::string& expectedStr, const Opt_Union_F64_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto offsetY = resultShadow.GetOffset().GetY();
        auto resultStr = std::to_string(offsetY);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetY";
    };

    for (auto& [input, value, expected] : testFixtureShadowOffsetNumberValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureShadowOffsetResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsOffsetYInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
        const std::string& input, const Opt_Union_F64_Resource& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).offsetY = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto offsetY = resultShadow.GetOffset().GetY();
        auto resultStr = std::to_string(offsetY);
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_OFFSET_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.offsetY";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_Resource>());
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsFillValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsFillValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto isFilled = resultShadow.GetIsFilled();
        auto resultStr = isFilled ? "true" : "false";
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.fill";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setTextShadowTestTextShadowShadowOptionsFillInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextShadowTestTextShadowShadowOptionsFillInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextShadow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textClockProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(textClockProperty, nullptr);

    Ark_Union_ShadowOptions_Array_ShadowOptions initValueTextShadow;

    // Initial setup
    InitTextShadow(initValueTextShadow);

    auto checkValue = [this, textClockProperty, &initValueTextShadow](
        const std::string& input, const Opt_Boolean& value) {
        Opt_Union_ShadowOptions_Array_ShadowOptions inputValueTextShadow;
        WriteTo(inputValueTextShadow) = initValueTextShadow;

        modifier_->setTextShadow(node_, &inputValueTextShadow);
        WriteToUnion<Ark_ShadowOptions>(WriteTo(inputValueTextShadow)).fill = value;
        modifier_->setTextShadow(node_, &inputValueTextShadow);
        EXPECT_TRUE(textClockProperty->GetTextShadow().has_value());
        auto resultTextShadow = textClockProperty->GetTextShadow().value();
        ASSERT_TRUE(resultTextShadow.size() > 0);
        Shadow resultShadow = resultTextShadow[0];
        auto isFilled = resultShadow.GetIsFilled();
        auto resultStr = isFilled ? "true" : "false";
        EXPECT_EQ(resultStr, ATTRIBUTE_TEXT_SHADOW_I_FILL_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setTextShadow, attribute: textShadow.ShadowOptions.fill";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}
} // namespace OHOS::Ace::NG
