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
#include "core/interfaces/native/implementation/linear_gradient_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/modifiers/generated/test_fixtures.h"
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
    const auto ATTRIBUTE_VALUE_COLORS_NAME = "valueColors";
    const auto ATTRIBUTE_VALUE_COLORS_COLOR_NAME = "color";
    const auto ATTRIBUTE_VALUE_COLORS_OFFSET_NAME = "offset";
    const auto ATTRIBUTE_TRACK_SHADOW_NAME = "trackShadow";
    const auto ATTRIBUTE_TRACK_SHADOW_COLORS_NAME = "colors";
    const auto ATTRIBUTE_TRACK_SHADOW_OFFSET_X_NAME = "offsetX";
    const auto ATTRIBUTE_TRACK_SHADOW_OFFSET_Y_NAME = "offsetY";
    const auto ATTRIBUTE_TRACK_SHADOW_RADIUS_NAME = "radius";

    constexpr auto VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE = 9;
    constexpr auto VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE = 2;
    constexpr auto VALUE_COLORS_COLOR_THEME_DEFAULT = "#FF000000";
    constexpr auto VALUE_COLORS_OFFSET_0_THEME_DEFAULT = "0.000000";
    constexpr auto VALUE_COLORS_OFFSET_1_THEME_DEFAULT = "1.000000";
    constexpr auto TRACK_SHADOW_OFFSET_X_THEME_DEFAULT = "0.000000";
    constexpr auto TRACK_SHADOW_OFFSET_Y_THEME_DEFAULT = "0.000000";
    constexpr auto TRACK_SHADOW_RADIUS_THEME_DEFAULT = "0.000000";
    const auto RES_VALUE_NAME = NamedResourceId{"test_value", ResourceType::FLOAT};
    const auto RES_VALUE_ID = IntResourceId{1, ResourceType::FLOAT};
    Converter::ConvContext s_ctx;
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

        for (auto&& res : Fixtures::resourceInitTable) {
            AddResource(std::get<0>(res), std::get<2>(res)); // 2 - index of resource
            AddResource(std::get<1>(res), std::get<2>(res)); // 2 - index of resource
        }
        AddResource(RES_VALUE_NAME, 5.0f);
        AddResource(RES_VALUE_ID, 1.0f);
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
const auto numberArray1 = std::array{ 1.0, 2.0, 3.0 };
const auto numberArray2 = std::array{ 4.0, 5.0, 6.0 };

static std::vector<std::tuple<std::string, Array_F64, std::string>> setDataPanelOptionsValuesValidValues = {
    {"[1,2,3]", Converter::ArkValue<Array_F64>(numberArray1, &s_ctx), "[1,2,3]"},
    {"[4,5,6]", Converter::ArkValue<Array_F64>(numberArray2, &s_ctx), "[4,5,6]"},
};

// Valid values for attribute 'max' of method 'setDataPanelOptions'
static std::vector<std::tuple<std::string, Opt_Float64, std::string>> setDataPanelOptionsMaxValidValues = {
    {"10.000000", Converter::ArkValue<Opt_Float64>(10.0), "10.000000"},
    {"1.000000", Converter::ArkValue<Opt_Float64>(1.0), "1.000000"},
    {"2.000000", Converter::ArkValue<Opt_Float64>(2.0), "2.000000"},
    {"100.000000", Converter::ArkValue<Opt_Float64>(100.0), "100.000000"},
    // Special case, if 'max' is less or equal 0, it set to sum of values. In our case its [1,2,3]
    {"0", Converter::ArkValue<Opt_Float64>(0.), "6.000000"},
    {"-1", Converter::ArkValue<Opt_Float64>(-1.), "6.000000"},
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
    initValueOptions.max = Converter::ArkValue<Opt_Float64>();
    initValueOptions.type = Converter::ArkValue<Opt_DataPanelType>();

    // Verifying attribute's 'values'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setDataPanelOptionsValuesValidValues) {
        inputValueOptions.values = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setDataPanelOptions(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUES_NAME);
        DisposeNode(node);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'max'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setDataPanelOptionsMaxValidValues) {
        inputValueOptions.max = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setDataPanelOptions(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
        DisposeNode(node);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'type'  values
    inputValueOptions = initValueOptions;
    for (auto&& value: setDataPanelOptionsTypeValidValues) {
        inputValueOptions.type = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setDataPanelOptions(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

//Invalid values attribute 'values'
auto numberArray3 = std::array{ -1., -2., 3. };

static std::vector<std::tuple<std::string, Array_F64, std::string>> setDataPanelOptionsValuesInvalidValues = {
    {"[-1,-2,3]", Converter::ArkValue<Array_F64>(numberArray3, &s_ctx), "[0,0,3]"},
};

// Invalid values for attribute 'max' of method 'setDataPanelOptions'
static std::vector<std::tuple<std::string, Opt_Float64>> setDataPanelOptionsMaxInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Float64>(Ark_Empty())},
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
    initValueOptions.values = std::get<1>(setDataPanelOptionsValuesValidValues[0]);
    initValueOptions.max = Converter::ArkValue<Opt_Float64>();
    initValueOptions.type = Converter::ArkValue<Opt_DataPanelType>();

    // Verifying attribute's 'values'  values
    for (auto&& value: setDataPanelOptionsValuesInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.values = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setDataPanelOptions(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUES_NAME);
        DisposeNode(node);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'max'  values
    for (auto&& value: setDataPanelOptionsMaxInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.max = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setDataPanelOptions(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_MAX_DEFAULT_VALUE) << "Passed value is: " << std::get<0>(value);
    }

    // Verifying attribute's 'type'  values
    for (auto&& value: setDataPanelOptionsTypeInvalidValues) {
        inputValueOptions = initValueOptions;
        inputValueOptions.type = std::get<1>(value);
        auto node = CreateNode();
        modifier_->setDataPanelOptions(node, &inputValueOptions);
        jsonValue = GetJsonValue(node);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_TYPE_DEFAULT_VALUE) << "Passed value is: " << std::get<0>(value);
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
        auto optValue = Converter::ArkValue<Opt_Boolean>(inputValueCloseEffect);
        modifier_->setCloseEffect(node_, &optValue);
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
    {"1.00px", Converter::ArkValue<Ark_Length>("1.00px"), "1.00px"},
};

/*
 * @tc.name: setStrokeWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setStrokeWidthTestValidValues, TestSize.Level1)
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
        auto optValue = Converter::ArkValue<Opt_Length>(inputValueStrokeWidth);
        modifier_->setStrokeWidth(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

const int64_t RESOURCE_STROKE_ID = 123;
static Ark_Length RESOURCE_STROKE = Converter::ArkValue<Ark_Length>(RESOURCE_STROKE_ID);
static std::vector<std::tuple<std::string, Ark_Length, std::string>> strokeWidthStrokeWidthResourceValues = {
    {"10.00px", RESOURCE_STROKE, "10.00px"},
}; // 10.00px is in mock theme constants
/*
 * @tc.name: setStrokeWidthTestResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setStrokeWidthTestResourceValues, TestSize.Level1)
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
        auto optValue = Converter::ArkValue<Opt_Length>(inputValueStrokeWidth);
        modifier_->setStrokeWidth(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Ark_Length, std::string>> strokeWidthStrokeWidthInvalidValues = {
    {"-1", Converter::ArkValue<Ark_Length>(-1.), "24.00vp"},
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
        auto optValue = Converter::ArkValue<Opt_Length>(inputValueStrokeWidth);
        modifier_->setStrokeWidth(node_, &optValue);
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
    { "#FF0000FF", Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
    { "#FF123456", Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Color::TRANSPARENT.ToString(), Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f),
        Color::TRANSPARENT.ToString() },
    { "#11223344", Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { "#FF00FFFF", Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

/*
 * @tc.name: setTrackBackgroundColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setTrackBackgroundColorTestValidValues, TestSize.Level1)
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
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(inputValueTrackBackgroundColor);
        modifier_->setTrackBackgroundColor(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Color::RED is mocked by mocked theme constants
static std::vector<std::tuple<std::string, Ark_ResourceColor, std::string>>
    trackBackgroundColorValidResourceValues = {{ Color::RED.ToString(),
        Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(CreateResource(12345, ResourceType::COLOR)),
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
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(inputValueTrackBackgroundColor);
        modifier_->setTrackBackgroundColor(node_, &optValue);
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
        auto optValue = Converter::ArkValue<Opt_ResourceColor>(inputValueTrackBackgroundColor);
        modifier_->setTrackBackgroundColor(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TRACK_BACKGROUND_COLOR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setValueColorsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setValueColorsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE);
    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, VALUE_COLORS_COLOR_THEME_DEFAULT);
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setValueColorsTestStringValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setValueColorsTestStringValidValues, TestSize.Level1)
{
    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();
    auto optValue = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    modifier_->setValueColors(node_, &optValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), Fixtures::testFixtureColorsStrValidValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, std::get<2>(Fixtures::testFixtureColorsStrValidValues.at(i)));
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setValueColorsTestStringInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setValueColorsTestStringInvalidValues, TestSize.Level1)
{
    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();
    auto optValue = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    modifier_->setValueColors(node_, &optValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE);

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, VALUE_COLORS_COLOR_THEME_DEFAULT);
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setValueColorsTestNumberValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setValueColorsTestNumberValidValues, TestSize.Level1)
{
    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();
    auto optValue = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    modifier_->setValueColors(node_, &optValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), Fixtures::testFixtureColorsNumValidValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, std::get<2>(Fixtures::testFixtureColorsNumValidValues.at(i)));
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setValueColorsTestEnumValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setValueColorsTestEnumValidValues, TestSize.Level1)
{
    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();
    auto optValue = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    modifier_->setValueColors(node_, &optValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), Fixtures::testFixtureColorsEnumValidValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, std::get<2>(Fixtures::testFixtureColorsEnumValidValues.at(i)));
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setValueColorsTestEnumInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setValueColorsTestEnumInvalidValues, TestSize.Level1)
{
    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();
    auto optValue = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    modifier_->setValueColors(node_, &optValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE);

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, VALUE_COLORS_COLOR_THEME_DEFAULT);
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setValueColorsTestResourceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setValueColorsTestResourceValidValues, TestSize.Level1)
{
    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();
    auto optValue = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    modifier_->setValueColors(node_, &optValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), Fixtures::testFixtureColorsResValidValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, std::get<2>(Fixtures::testFixtureColorsResValidValues.at(i)));
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

std::vector<std::vector<std::pair<std::optional<Color>, Dimension>>> colorStopValues = {
    std::vector<std::pair<std::optional<Color>, Dimension>>
        {std::make_pair(Color::RED, Dimension(0.5f)), std::make_pair(Color::BLUE, Dimension(9.0f))},
    std::vector<std::pair<std::optional<Color>, Dimension>>
        {std::make_pair(Color::GREEN, Dimension(0.2f)), std::make_pair(Color::BLACK, Dimension(0.8f))}
};

std::vector<std::vector<std::pair<std::optional<Color>, Dimension>>> colorStopValuesInvalid = {
    std::vector<std::pair<std::optional<Color>, Dimension>>
        {std::make_pair(std::nullopt, Dimension(0.5f)), std::make_pair(Color::BLUE, Dimension(9.0f))},
    std::vector<std::pair<std::optional<Color>, Dimension>>
        {std::make_pair(Color::GREEN, Dimension(0.2f)), std::make_pair(Color::BLACK, Dimension(0.8f))}
};

/*
 * @tc.name: setValueColorsTestLinearGradientValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setValueColorsTestLinearGradientValidValues, TestSize.Level1)
{
    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& values : colorStopValues) {
        Ark_LinearGradient gradient = PeerUtils::CreatePeer<LinearGradientPeer>(values);
        auto colorGradientUnion =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);
        colorArray.push_back(colorGradientUnion);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();
    auto optValue = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    modifier_->setValueColors(node_, &optValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), colorStopValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), colorStopValues.at(i).size());
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, (std::get<0>(colorStopValues.at(i).at(j))).value().ToString());
            EXPECT_EQ(offsetCheckValue, std::to_string((std::get<1>(colorStopValues.at(i).at(j))).Value()));
        }
    }
}

/*
 * @tc.name: setValueColorsTestLinearGradientInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setValueColorsTestLinearGradientInvalidValues, TestSize.Level1)
{
    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& values : colorStopValuesInvalid) {
        Ark_LinearGradient gradient = PeerUtils::CreatePeer<LinearGradientPeer>(values);
        auto colorGradientUnion =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);
        colorArray.push_back(colorGradientUnion);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();
    auto optValue = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    modifier_->setValueColors(node_, &optValue);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE);

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, VALUE_COLORS_COLOR_THEME_DEFAULT);
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setTrackShadowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setTrackShadowTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto shadowJsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(shadowJsonArray, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE);

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, VALUE_COLORS_COLOR_THEME_DEFAULT);
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }

    auto radiusCheckValue = GetAttrValue<std::string>(shadowJsonArray, ATTRIBUTE_TRACK_SHADOW_RADIUS_NAME);
    EXPECT_EQ(radiusCheckValue, TRACK_SHADOW_RADIUS_THEME_DEFAULT); // a theme value doesn't meet an sdk value
    auto offsetXCheckValue = GetAttrValue<std::string>(shadowJsonArray, ATTRIBUTE_TRACK_SHADOW_OFFSET_X_NAME);
    EXPECT_EQ(offsetXCheckValue, TRACK_SHADOW_OFFSET_X_THEME_DEFAULT); // a theme value doesn't meet an sdk value
    auto offsetYCheckValue = GetAttrValue<std::string>(shadowJsonArray, ATTRIBUTE_TRACK_SHADOW_OFFSET_Y_NAME);
    EXPECT_EQ(offsetYCheckValue, TRACK_SHADOW_OFFSET_Y_THEME_DEFAULT); // a theme value doesn't meet an sdk value
}

// Valid values for attribute 'radius' of method 'trackShadow'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource, std::string>> trackShadowRadiusValidValues = {
    {"0.05", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(0.05), "0.050000"},
    {"10.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(10.0), "10.000000"},
    {"100.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(100.0), "100.000000"},
    {"5.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(CreateResource(RES_VALUE_NAME)), "5.000000"},
    {"1.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(CreateResource(RES_VALUE_ID)), "1.000000"},
};

// Valid values for attribute 'offsetX' of method 'trackShadow'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource, std::string>> trackShadowOffsetXValidValues = {
    {"0.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(0.0), "0.000000"},
    {"10.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(10.0), "10.000000"},
    {"-0.5", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(-0.5), "-0.500000"},
    {"1.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(CreateResource(RES_VALUE_ID)), "1.000000"},
    {"5.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(CreateResource(RES_VALUE_NAME)), "5.000000"},
};

// Valid values for attribute 'offsetY' of method 'trackShadow'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource, std::string>> trackShadowOffsetYValidValues = {
    {"0.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(0.0), "0.000000"},
    {"-100.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(-100.0), "-100.000000"},
    {"5.5", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(5.5), "5.500000"},
    {"5.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(CreateResource(RES_VALUE_NAME)), "5.000000"},
    {"1.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(CreateResource(RES_VALUE_ID)), "1.000000"},
};

// Invalid values for attribute 'radius' of method 'trackShadow'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource>> trackShadowRadiusInvalidValues = {
    {"Ark_Empty()", Converter::ArkUnion<Opt_Union_F64_Resource>(Ark_Empty())},
    {"nullptr", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr)},
    {"0.0", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(0.0)},
    {"-20.5", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(-20.5)},
};

// Invalid values for attribute 'offsetX' of method 'trackShadow'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource>> trackShadowOffsetXInvalidValues = {
    {"Ark_Empty()", Converter::ArkUnion<Opt_Union_F64_Resource>(Ark_Empty())},
    {"nullptr", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr)},
};

// Invalid values for attribute 'offsetY' of method 'trackShadow'
static std::vector<std::tuple<std::string, Opt_Union_F64_Resource>> trackShadowOffsetYInvalidValues = {
    {"Ark_Empty()", Converter::ArkUnion<Opt_Union_F64_Resource>(Ark_Empty())},
    {"nullptr", Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr)},
};

/*
 * @tc.name: setTrackShadowTestRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestRadiusValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultTrackShadow;
    std::string resultStr;
    std::string expectedStr;

    Ark_DataPanelShadowOptions inputValueTrackShadow;
    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = std::get<1>(trackShadowRadiusValidValues[0]);
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(Ark_Empty());

    inputValueTrackShadow = initValueTrackShadow;
    for (auto&& value: trackShadowRadiusValidValues) {
        inputValueTrackShadow.radius = std::get<1>(value);
        auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(inputValueTrackShadow);
        modifier_->setTrackShadow(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
        resultStr = GetAttrValue<std::string>(resultTrackShadow, ATTRIBUTE_TRACK_SHADOW_RADIUS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTrackShadowTestRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setTrackShadowTestRadiusInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultTrackShadow;
    std::string resultStr;
    std::string expectedStr;

    Ark_DataPanelShadowOptions inputValueTrackShadow;
    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = std::get<1>(trackShadowRadiusValidValues[0]);
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(Ark_Empty());

    inputValueTrackShadow = initValueTrackShadow;
    for (auto&& value: trackShadowRadiusInvalidValues) {
        inputValueTrackShadow.radius = std::get<1>(value);
        auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(inputValueTrackShadow);
        modifier_->setTrackShadow(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
        resultStr = GetAttrValue<std::string>(resultTrackShadow, ATTRIBUTE_TRACK_SHADOW_RADIUS_NAME);
        expectedStr = TRACK_SHADOW_RADIUS_THEME_DEFAULT; // a theme value doesn't meet an sdk value
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTrackShadowTestOffsetXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestOffsetXValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultTrackShadow;
    std::string resultStr;
    std::string expectedStr;

    Ark_DataPanelShadowOptions inputValueTrackShadow;
    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius =  Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = std::get<1>(trackShadowOffsetXValidValues[0]);
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(Ark_Empty());

    inputValueTrackShadow = initValueTrackShadow;
    for (auto&& value: trackShadowOffsetXValidValues) {
        inputValueTrackShadow.offsetX = std::get<1>(value);
        auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(inputValueTrackShadow);
        modifier_->setTrackShadow(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
        resultStr = GetAttrValue<std::string>(resultTrackShadow, ATTRIBUTE_TRACK_SHADOW_OFFSET_X_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTrackShadowTestOffsetXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setTrackShadowTestOffsetXInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultTrackShadow;
    std::string resultStr;
    std::string expectedStr;

    Ark_DataPanelShadowOptions inputValueTrackShadow;
    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius =  Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = std::get<1>(trackShadowOffsetXValidValues[0]);
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(Ark_Empty());

    inputValueTrackShadow = initValueTrackShadow;
    for (auto&& value: trackShadowOffsetXInvalidValues) {
        inputValueTrackShadow.offsetX = std::get<1>(value);
        auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(inputValueTrackShadow);
        modifier_->setTrackShadow(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
        resultStr = GetAttrValue<std::string>(resultTrackShadow, ATTRIBUTE_TRACK_SHADOW_OFFSET_X_NAME);
        expectedStr = TRACK_SHADOW_OFFSET_X_THEME_DEFAULT; // a theme value doesn't meet an sdk value
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTrackShadowTestOffsetYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestOffsetYValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultTrackShadow;
    std::string resultStr;
    std::string expectedStr;

    Ark_DataPanelShadowOptions inputValueTrackShadow;
    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius =  Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = std::get<1>(trackShadowOffsetYValidValues[0]);
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(Ark_Empty());

    inputValueTrackShadow = initValueTrackShadow;
    for (auto&& value: trackShadowOffsetYValidValues) {
        inputValueTrackShadow.offsetY = std::get<1>(value);
        auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(inputValueTrackShadow);
        modifier_->setTrackShadow(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
        resultStr = GetAttrValue<std::string>(resultTrackShadow, ATTRIBUTE_TRACK_SHADOW_OFFSET_Y_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTrackShadowTestOffsetYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setTrackShadowTestOffsetYInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> resultTrackShadow;
    std::string resultStr;
    std::string expectedStr;

    Ark_DataPanelShadowOptions inputValueTrackShadow;
    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius =  Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = std::get<1>(trackShadowOffsetYValidValues[0]);
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(Ark_Empty());

    inputValueTrackShadow = initValueTrackShadow;
    for (auto&& value: trackShadowOffsetYInvalidValues) {
        inputValueTrackShadow.offsetY = std::get<1>(value);
        auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(inputValueTrackShadow);
        modifier_->setTrackShadow(node_, &optValue);
        jsonValue = GetJsonValue(node_);
        resultTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
        resultStr = GetAttrValue<std::string>(resultTrackShadow, ATTRIBUTE_TRACK_SHADOW_OFFSET_Y_NAME);
        expectedStr = TRACK_SHADOW_OFFSET_Y_THEME_DEFAULT; // a theme value doesn't meet an sdk value
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setTrackShadowTestColorStringValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestColorStringValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> jsonTrackShadow;
    std::unique_ptr<JsonValue> jsonArray;
    std::string resultStr;
    std::string expectedStr;

    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsStrValidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();

    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(initValueTrackShadow);
    modifier_->setTrackShadow(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    jsonTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonTrackShadow, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), Fixtures::testFixtureColorsStrValidValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, std::get<2>(Fixtures::testFixtureColorsStrValidValues.at(i)));
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setTrackShadowTestColorStringInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestColorStringInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> jsonTrackShadow;
    std::unique_ptr<JsonValue> jsonArray;
    std::string resultStr;
    std::string expectedStr;

    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsStrInvalidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();

    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(initValueTrackShadow);
    modifier_->setTrackShadow(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    jsonTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonTrackShadow, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE);

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, VALUE_COLORS_COLOR_THEME_DEFAULT);
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setTrackShadowTestColorNumberValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, DISABLED_setTrackShadowTestColorNumberValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> jsonTrackShadow;
    std::unique_ptr<JsonValue> jsonArray;
    std::string resultStr;
    std::string expectedStr;

    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsNumValidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();

    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(initValueTrackShadow);
    modifier_->setTrackShadow(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    jsonTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonTrackShadow, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), Fixtures::testFixtureColorsNumValidValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, std::get<2>(Fixtures::testFixtureColorsNumValidValues.at(i)));
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setTrackShadowTestColorEnumValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestColorEnumValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> jsonTrackShadow;
    std::unique_ptr<JsonValue> jsonArray;
    std::string resultStr;
    std::string expectedStr;

    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsEnumValidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();

    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(initValueTrackShadow);
    modifier_->setTrackShadow(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    jsonTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonTrackShadow, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), Fixtures::testFixtureColorsEnumValidValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, std::get<2>(Fixtures::testFixtureColorsEnumValidValues.at(i)));
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setTrackShadowTestColorEnumInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestColorEnumInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> jsonTrackShadow;
    std::unique_ptr<JsonValue> jsonArray;
    std::string resultStr;
    std::string expectedStr;

    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsEnumInvalidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
            std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();

    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(initValueTrackShadow);
    modifier_->setTrackShadow(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    jsonTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonTrackShadow, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE);

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, VALUE_COLORS_COLOR_THEME_DEFAULT);
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setTrackShadowTestColorResourceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestColorResourceValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> jsonTrackShadow;
    std::unique_ptr<JsonValue> jsonArray;
    std::string resultStr;
    std::string expectedStr;

    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& value : Fixtures::testFixtureColorsResValidValues) {
        auto resourceColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(std::get<1>(value));
        auto color =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(resourceColor);
        colorArray.push_back(color);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();

    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(initValueTrackShadow);
    modifier_->setTrackShadow(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    jsonTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonTrackShadow, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), Fixtures::testFixtureColorsResValidValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, std::get<2>(Fixtures::testFixtureColorsResValidValues.at(i)));
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}

/*
 * @tc.name: setTrackShadowTestColorLinearGradientValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestColorLinearGradientValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> jsonTrackShadow;
    std::unique_ptr<JsonValue> jsonArray;
    std::string resultStr;
    std::string expectedStr;

    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& values : colorStopValues) {
        Ark_LinearGradient gradient = PeerUtils::CreatePeer<LinearGradientPeer>(values);
        auto colorGradientUnion =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);
        colorArray.push_back(colorGradientUnion);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();

    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(initValueTrackShadow);
    modifier_->setTrackShadow(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    jsonTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonTrackShadow, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), colorStopValues.size());

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, (std::get<0>(colorStopValues.at(i).at(j))).value().ToString());
            EXPECT_EQ(offsetCheckValue, std::to_string((std::get<1>(colorStopValues.at(i).at(j))).Value()));
        }
    }
}

/*
 * @tc.name: setTrackShadowTestColorLinearGradientInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelModifierTest, setTrackShadowTestColorLinearGradientInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::unique_ptr<JsonValue> jsonTrackShadow;
    std::unique_ptr<JsonValue> jsonArray;
    std::string resultStr;
    std::string expectedStr;

    auto colorArray = std::vector<Ark_Union_ResourceColor_LinearGradient>{};
    for (auto&& values : colorStopValuesInvalid) {
        Ark_LinearGradient gradient = PeerUtils::CreatePeer<LinearGradientPeer>(values);
        auto colorGradientUnion =
            Converter::ArkUnion<Ark_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);
        colorArray.push_back(colorGradientUnion);
    }

    Converter::ArkArrayHolder<Array_Union_ResourceColor_LinearGradient> colorArrayHolder(colorArray);
    auto arkColorArray = colorArrayHolder.ArkValue();

    Ark_DataPanelShadowOptions initValueTrackShadow;

    // Initial setup
    initValueTrackShadow.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    initValueTrackShadow.colors = Converter::ArkValue<Opt_Array_Union_ResourceColor_LinearGradient>(arkColorArray);
    auto optValue = Converter::ArkValue<Opt_DataPanelShadowOptions>(initValueTrackShadow);
    modifier_->setTrackShadow(node_, &optValue);

    jsonValue = GetJsonValue(node_);
    jsonTrackShadow = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TRACK_SHADOW_NAME);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonTrackShadow, ATTRIBUTE_TRACK_SHADOW_COLORS_NAME);
    ASSERT_EQ(jsonArray->GetArraySize(), VALUE_COLORS_COLOR_THEME_VALUES_ARRAY_SIZE);

    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto gradientItem = jsonArray->GetArrayItem(i);
        ASSERT_EQ(gradientItem->GetArraySize(), VALUE_COLORS_COLOR_THEME_GRADIENTS_ARRAY_SIZE);
        for (int j = 0; j < gradientItem->GetArraySize(); j++) {
            auto colorStopItem = gradientItem->GetArrayItem(j);
            auto colorCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_COLOR_NAME);
            auto offsetCheckValue = GetAttrValue<std::string>(colorStopItem, ATTRIBUTE_VALUE_COLORS_OFFSET_NAME);
            EXPECT_EQ(colorCheckValue, VALUE_COLORS_COLOR_THEME_DEFAULT);
            if (0 == j) {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_0_THEME_DEFAULT);
            } else {
                EXPECT_EQ(offsetCheckValue, VALUE_COLORS_OFFSET_1_THEME_DEFAULT);
            }
        }
    }
}
} // namespace OHOS::Ace::NG
