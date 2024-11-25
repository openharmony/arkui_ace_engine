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
#include "core/components/data_panel/data_panel_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_VALUES_NAME = "values";
    const auto ATTRIBUTE_VALUES_DEFAULT_VALUE = "[]";
    const auto ATTRIBUTE_MAX_NAME = "max";
    const auto ATTRIBUTE_MAX_DEFAULT_VALUE = "100.000000";
    const auto ATTRIBUTE_TYPE_NAME = "type";
    const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "DataPanelType.Circle";
    const auto ATTRIBUTE_CLOSE_EFFECT_NAME = "closeEffect";
    const auto ATTRIBUTE_CLOSE_EFFECT_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_TRACK_BACKGROUND_COLOR_NAME = "trackBackgroundColor";
    const auto ATTRIBUTE_TRACK_BACKGROUND_COLOR_DEFAULT_VALUE = "#08182431";
    const auto ATTRIBUTE_STROKE_WIDTH_NAME = "strokeWidth";
    const auto ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE = "24.00vp";
} // namespace

class DataPanelModifierTest : public ModifierTestBase<GENERATED_ArkUIDataPanelModifier,
    &GENERATED_ArkUINodeModifiers::getDataPanelModifier, GENERATED_ARKUI_DATA_PANEL> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        auto theme = SetupThemeStyle(THEME_PATTERN_DATA_PANEL);
        theme->SetAttr("datapanel_thickness",
            { .value = Dimension::FromString(ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE) });
        theme->SetAttr(PATTERN_BG_COLOR,
            { .value = Color::FromString(ATTRIBUTE_TRACK_BACKGROUND_COLOR_DEFAULT_VALUE) });
        SetupTheme<DataPanelTheme>();
    }
};

/*
 * @tc.name: setDataPanelOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setDataPanelOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUES_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE);
}

// Valid values for attribute 'values' of method 'setDataPanelOptions'
auto numberArray1 = std::array{ Converter::ArkValue<Ark_Number>(1), Converter::ArkValue<Ark_Number>(2),
    Converter::ArkValue<Ark_Number>(3)
};
Converter::ArkArrayHolder<Array_Number> arrayHolder1(numberArray1);
Array_Number numberArrayResult1 = arrayHolder1.ArkValue();

auto numberArray2 = std::array{ Converter::ArkValue<Ark_Number>(4.0f), Converter::ArkValue<Ark_Number>(5.0f),
    Converter::ArkValue<Ark_Number>(6.0f)
};
Converter::ArkArrayHolder<Array_Number> arrayHolder2(numberArray2);
Array_Number numberArrayResult2 = arrayHolder2.ArkValue();

static std::vector<std::tuple<std::string, Array_Number, std::string>> setDataPanelOptionsValuesValidValues = {
    {"[1,2,3]", numberArrayResult1, "[1,2,3]"},
    {"[4,5,6]", numberArrayResult2, "[4,5,6]"},
};

// Valid values for attribute 'max' of method 'setDataPanelOptions'
static std::vector<std::tuple<std::string, Opt_Number, std::string>> setDataPanelOptionsMaxValidValues = {
    {"1.000000", Converter::ArkValue<Opt_Number>(1), "1.000000"},
    {"2.000000", Converter::ArkValue<Opt_Number>(2.0f), "2.000000"},
};

// Valid values for attribute 'type' of method 'setDataPanelOptions'
// see the converter AssignCast(std::optional<DataPanelType>& dst, const Ark_DataPanelType& src)
static std::vector<std::tuple<std::string, Opt_DataPanelType, std::string>> setDataPanelOptionsTypeValidValues = {
    {"DataPanelType.Circle", Converter::ArkValue<Opt_DataPanelType>(ARK_DATA_PANEL_TYPE_CIRCLE),
        "DataPanelType.Circle"},
    {"DataPanelType.Line", Converter::ArkValue<Opt_DataPanelType>(ARK_DATA_PANEL_TYPE_LINE),
        "DataPanelType.Line"},
};

/*
 * @tc.name: setDataPanelOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setDataPanelOptionsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_DataPanelOptions inputValueOptions;
    Ark_DataPanelOptions initValueOptions;

    // Initial setup
    initValueOptions.values = std::get<1>(setDataPanelOptionsValuesValidValues[0]);
    initValueOptions.max = std::get<1>(setDataPanelOptionsMaxValidValues[0]);
    initValueOptions.type = std::get<1>(setDataPanelOptionsTypeValidValues[0]);

    // Verifying attribute's 'values'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setDataPanelOptionsValuesValidValues) {
        inputValueOptions.values = std::get<1>(value);
        modifier_->setDataPanelOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUES_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'max'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setDataPanelOptionsMaxValidValues) {
        inputValueOptions.max = std::get<1>(value);
        modifier_->setDataPanelOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'type'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setDataPanelOptionsTypeValidValues) {
        inputValueOptions.type = std::get<1>(value);
        modifier_->setDataPanelOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

//Invalid values attribute 'values'
auto numberArray3 = std::array{ Converter::ArkValue<Ark_Number>(-1), Converter::ArkValue<Ark_Number>(-2),
    Converter::ArkValue<Ark_Number>(3), Converter::ArkValue<Ark_Number>(4), Converter::ArkValue<Ark_Number>(5),
    Converter::ArkValue<Ark_Number>(6), Converter::ArkValue<Ark_Number>(7), Converter::ArkValue<Ark_Number>(8),
    Converter::ArkValue<Ark_Number>(9), Converter::ArkValue<Ark_Number>(10),
};
Converter::ArkArrayHolder<Array_Number> arrayHolder3(numberArray3);
Array_Number numberArrayResult3 = arrayHolder3.ArkValue();

static std::vector<std::tuple<std::string, Array_Number, std::string>> setDataPanelOptionsValuesInvalidValues = {
    {"[1,2,3]", numberArrayResult3, "[1,2,3]"},
};

// Invalid values for attribute 'max' of method 'setDataPanelOptions'
static std::vector<std::tuple<std::string, Opt_Number>> setDataPanelOptionsMaxInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Number>(Ark_Empty())},
};

// Invalid values for attribute 'type' of method 'setDataPanelOptions'
static std::vector<std::tuple<std::string, Opt_DataPanelType>> setDataPanelOptionsTypeInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_DataPanelType>(Ark_Empty())},
    {"static_cast<Ark_DataPanelType>(-1)",
        Converter::ArkValue<Opt_DataPanelType>(static_cast<Ark_DataPanelType>(-1))},
};

/*
 * @tc.name: setDataPanelOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setDataPanelOptionsTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_DataPanelOptions inputValueOptions;
    Ark_DataPanelOptions initValueOptions;

    // Initial setup
    initValueOptions.values = std::get<1>(setDataPanelOptionsValuesInvalidValues[0]);
    initValueOptions.max = std::get<1>(setDataPanelOptionsMaxInvalidValues[0]);
    initValueOptions.type = std::get<1>(setDataPanelOptionsTypeInvalidValues[0]);

    // Verifying attribute's 'max'  values
    for (auto&& value: setDataPanelOptionsMaxInvalidValues) {
        inputValueOptions = initValueOptions;
        modifier_->setDataPanelOptions(node_, &inputValueOptions);
        inputValueOptions.max = std::get<1>(value);
        modifier_->setDataPanelOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
        expectedStr = ATTRIBUTE_MAX_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'type'  values
    for (auto&& value: setDataPanelOptionsTypeInvalidValues) {
        inputValueOptions = initValueOptions;
        modifier_->setDataPanelOptions(node_, &inputValueOptions);
        inputValueOptions.type = std::get<1>(value);
        modifier_->setDataPanelOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        expectedStr = ATTRIBUTE_TYPE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setCloseEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setCloseEffectTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CLOSE_EFFECT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CLOSE_EFFECT_DEFAULT_VALUE);
}

// Valid values for attribute 'closeEffect' of method 'closeEffect'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> closeEffectCloseEffectValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setCloseEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setCloseEffectTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueCloseEffect;
    Ark_Boolean initValueCloseEffect;

    // Initial setup
    initValueCloseEffect = std::get<1>(closeEffectCloseEffectValidValues[0]);

    // Verifying attribute's  values
    inputValueCloseEffect = initValueCloseEffect;
    for (auto&& value: closeEffectCloseEffectValidValues) {
        inputValueCloseEffect = std::get<1>(value);
        modifier_->setCloseEffect(node_, inputValueCloseEffect);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CLOSE_EFFECT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setStrokeWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setStrokeWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE);
}

// Valid values for attribute 'strokeWidth' of method 'strokeWidth'
static std::vector<std::tuple<std::string, Ark_Length, std::string>> strokeWidthStrokeWidthValidValues = {
    {"1.00px", Converter::ArkValue<Ark_Length>(1), "1.00px"},
};

/*
 * @tc.name: setStrokeWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setStrokeWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueStrokeWidth;
    Ark_Length initValueStrokeWidth;

    // Initial setup
    initValueStrokeWidth = std::get<1>(strokeWidthStrokeWidthValidValues[0]);

    // Verifying attribute's  values
    inputValueStrokeWidth = initValueStrokeWidth;
    for (auto&& value: strokeWidthStrokeWidthValidValues) {
        inputValueStrokeWidth = std::get<1>(value);
        modifier_->setStrokeWidth(node_, &inputValueStrokeWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static Ark_Length RESOURCE_STROKE = {.type = Ark_Tag::ARK_TAG_RESOURCE, .resource = 123};
static std::vector<std::tuple<std::string, Ark_Length, std::string>> strokeWidthStrokeWidthResourceValues = {
    {"10.00px", RESOURCE_STROKE, "10.00px"},
}; // 10.00px is in mock theme constants
/*
 * @tc.name: setStrokeWidthTestResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setStrokeWidthTestResourceValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueStrokeWidth;
    Ark_Length initValueStrokeWidth;

    // Initial setup
    initValueStrokeWidth = std::get<1>(strokeWidthStrokeWidthResourceValues[0]);

    // Verifying attribute's  values
    inputValueStrokeWidth = initValueStrokeWidth;
    for (auto&& value: strokeWidthStrokeWidthResourceValues) {
        inputValueStrokeWidth = std::get<1>(value);
        modifier_->setStrokeWidth(node_, &inputValueStrokeWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Ark_Length, std::string>> strokeWidthStrokeWidthInvalidValues = {
    {"24.00vp", Converter::ArkValue<Ark_Length>(-1), "24.00vp"},
};

/*
 * @tc.name: setStrokeWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setStrokeWidthTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Length inputValueStrokeWidth;
    Ark_Length initValueStrokeWidth;

    // Initial setup
    initValueStrokeWidth = std::get<1>(strokeWidthStrokeWidthInvalidValues[0]);

    // Verifying attribute's  values
    inputValueStrokeWidth = initValueStrokeWidth;
    for (auto&& value: strokeWidthStrokeWidthInvalidValues) {
        inputValueStrokeWidth = std::get<1>(value);
        modifier_->setStrokeWidth(node_, &inputValueStrokeWidth);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTrackBackgroundColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackBackgroundColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TRACK_BACKGROUND_COLOR_DEFAULT_VALUE);
}

// Valid values for attribute 'trackBackgroundColor' of method 'trackBackgroundColor'
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>>
    trackBackgroundColorValidValues = {
    { "#FF0000FF", Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { "#FF123456", Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Color::TRANSPARENT.ToString(), Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f),
        Color::TRANSPARENT.ToString() },
    { "#11223344", Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { "#FF00FFFF", Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

/*
 * @tc.name: setTrackBackgroundColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackBackgroundColorTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueTrackBackgroundColor;
    Ark_ResourceColor initValueTrackBackgroundColor;

    // Initial setup
    initValueTrackBackgroundColor = std::get<1>(trackBackgroundColorValidValues[0]);

    // Verifying attribute's  values
    inputValueTrackBackgroundColor = initValueTrackBackgroundColor;
    for (auto&& value: trackBackgroundColorValidValues) {
        inputValueTrackBackgroundColor = std::get<1>(value);
        modifier_->setTrackBackgroundColor(node_, &inputValueTrackBackgroundColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Color::RED is mocked by mocked theme constants
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>>
    trackBackgroundColorValidResourceValues = {{ Color::RED.ToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(12345, NodeModifier::ResourceType::COLOR)),
        Color::RED.ToString() },
};

/*
 * @tc.name: setTrackBackgroundColorTestValidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackBackgroundColorTestValidResourceValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueTrackBackgroundColor;
    Ark_ResourceColor initValueTrackBackgroundColor;

    // Initial setup
    initValueTrackBackgroundColor = std::get<1>(trackBackgroundColorValidResourceValues[0]);

    // Verifying attribute's  values
    inputValueTrackBackgroundColor = initValueTrackBackgroundColor;
    for (auto&& value: trackBackgroundColorValidResourceValues) {
        inputValueTrackBackgroundColor = std::get<1>(value);
        modifier_->setTrackBackgroundColor(node_, &inputValueTrackBackgroundColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>>
    trackBackgroundColorInvalidValues = {
    { ATTRIBUTE_TRACK_BACKGROUND_COLOR_DEFAULT_VALUE, Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""),
        ATTRIBUTE_TRACK_BACKGROUND_COLOR_DEFAULT_VALUE },
    { ATTRIBUTE_TRACK_BACKGROUND_COLOR_DEFAULT_VALUE,
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"),
        ATTRIBUTE_TRACK_BACKGROUND_COLOR_DEFAULT_VALUE }
};

/*
 * @tc.name: setTrackBackgroundColorTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackBackgroundColorTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_ResourceColor inputValueTrackBackgroundColor;
    Ark_ResourceColor initValueTrackBackgroundColor;

    // Initial setup
    initValueTrackBackgroundColor = std::get<1>(trackBackgroundColorInvalidValues[0]);

    // Verifying attribute's  values
    inputValueTrackBackgroundColor = initValueTrackBackgroundColor;
    for (auto&& value: trackBackgroundColorInvalidValues) {
        inputValueTrackBackgroundColor = std::get<1>(value);
        modifier_->setTrackBackgroundColor(node_, &inputValueTrackBackgroundColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

} // namespace OHOS::Ace::NG
