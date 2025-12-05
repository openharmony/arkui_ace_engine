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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "point_light_test.h"
#include "generated/type_helpers.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::PointLight;
using namespace OHOS::Ace::NG::TypeHelper;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_ALIGN_ITEMS_NAME = "alignItems";
    const auto ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE = "VerticalAlign.Center";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_NAME = "justifyContent";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";
    const auto ATTRIBUTE_IS_REVERSE_NAME = "isReverse";
    const auto ATTRIBUTE_IS_REVERSE_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_POINT_LIGHT_NAME = "pointLight";
    const auto ATTRIBUTE_LIGHT_INTENSITY_NAME = "lightIntensity";
    const auto ATTRIBUTE_LIGHT_INTENSITY_DEFAULT_VALUE = "0";
} // namespace

class RowModifierTest : public ModifierTestBase<GENERATED_ArkUIRowModifier,
    &GENERATED_ArkUINodeModifiers::getRowModifier, GENERATED_ARKUI_ROW> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        for (auto& [id, strid, res] : resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setAlignItemsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setAlignItemsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE);
}

/*
 * @tc.name: setAlignItemsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setAlignItemsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_VerticalAlign inputValueAlignItems;

    // Verifying attribute's  values
    inputValueAlignItems = Converter::ArkValue<Opt_VerticalAlign>(ARK_VERTICAL_ALIGN_BOTTOM);
    modifier_->setAlignItems(node_, &inputValueAlignItems);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
    expectedStr = "VerticalAlign.Bottom";
    EXPECT_EQ(resultStr, expectedStr);
}

/*
 * @tc.name: setJustifyContentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setJustifyContentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE);
}

// Valid values for attribute 'justifyContent' of method 'justifyContent'
static std::vector<std::tuple<std::string, Opt_FlexAlign, std::string>>
    justifyContentJustifyContentValidValues = {
    {"ARK_FLEX_ALIGN_START", Converter::ArkValue<Opt_FlexAlign>(ARK_FLEX_ALIGN_START),
        "FlexAlign.Start"},
    {"ARK_FLEX_ALIGN_CENTER", Converter::ArkValue<Opt_FlexAlign>(ARK_FLEX_ALIGN_CENTER),
        "FlexAlign.Center"},
    {"ARK_FLEX_ALIGN_END", Converter::ArkValue<Opt_FlexAlign>(ARK_FLEX_ALIGN_END),
        "FlexAlign.End"},
    {"ARK_FLEX_ALIGN_SPACE_BETWEEN", Converter::ArkValue<Opt_FlexAlign>(ARK_FLEX_ALIGN_SPACE_BETWEEN),
        "FlexAlign.SpaceBetween"},
    {"ARK_FLEX_ALIGN_SPACE_AROUND", Converter::ArkValue<Opt_FlexAlign>(ARK_FLEX_ALIGN_SPACE_AROUND),
        "FlexAlign.SpaceAround"},
    {"ARK_FLEX_ALIGN_SPACE_EVENLY", Converter::ArkValue<Opt_FlexAlign>(ARK_FLEX_ALIGN_SPACE_EVENLY),
        "FlexAlign.SpaceEvenly"},
};

/*
 * @tc.name: setJustifyContentTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setJustifyContentTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_FlexAlign inputValueJustifyContent;

    // Verifying attribute's values
    inputValueJustifyContent = std::get<1>(justifyContentJustifyContentValidValues[0]);
    for (auto&& value: justifyContentJustifyContentValidValues) {
        inputValueJustifyContent = std::get<1>(value);
        modifier_->setJustifyContent(node_, &inputValueJustifyContent);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JUSTIFY_CONTENT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPointLightDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */

HWTEST_F(RowModifierTest, DISABLED_setPointLightDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    std::string resultStr2;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    resultStr2 = GetAttrValue<std::string>(resultStr, ATTRIBUTE_LIGHT_INTENSITY_NAME);
    EXPECT_EQ(resultStr2, ATTRIBUTE_LIGHT_INTENSITY_DEFAULT_VALUE);
}

/*
 * @tc.name: setIsReverseDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setIsReverseDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_REVERSE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IS_REVERSE_DEFAULT_VALUE);
}
// Valid values for attribute 'isReverse'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> isReverseValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "1"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "0"},
};

/*
 * @tc.name: setIsReverseDefaultValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setIsReverseDefaultValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean inputValueSelect;
    Opt_Boolean initValueSelect;

    // Initial setup
    initValueSelect = std::get<1>(isReverseValidValues[0]);

    // Verifying attribute's  values
    inputValueSelect = initValueSelect;
    for (auto&& value: isReverseValidValues) {
        inputValueSelect = std::get<1>(value);
        modifier_->setReverse(node_, &inputValueSelect);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_REVERSE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

#ifdef WRONG_SDK // PointLight
/*
 * @tc.name: setPointLightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestDefaultValues, TestSize.Level1)
{
    auto jsonValue = GetJsonValue(node_);
    auto resultPointLight =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    std::string resultStr;
    double resultDouble;

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_NAME);
    resultDouble = StringUtils::StringToDouble(resultStr);
    EXPECT_NEAR(resultDouble, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_DEFAULT_VALUE, FLT_EPSILON) <<
        "Default value for attribute 'pointLight.lightSource.intensity'";

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.lightSource'";

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.illuminated'";

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_BLOOM_NAME);
    resultDouble = StringUtils::StringToDouble(resultStr);
    EXPECT_NEAR(resultDouble, ATTRIBUTE_POINT_LIGHT_I_BLOOM_DEFAULT_VALUE, FLT_EPSILON) <<
        "Default value for attribute 'pointLight.bloom'";
    auto resultPointLightPosition =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_NAME);
    EXPECT_EQ(resultPointLightPosition->ToString(), ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.lightSource.position'";
    EXPECT_TRUE(resultPointLightPosition->IsObject()) <<
        "Default value for attribute 'pointLight.lightSource.position'";
    EXPECT_FALSE(resultPointLightPosition->IsNull()) <<
        "Default value for attribute 'pointLight.lightSource.position'";
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightLightSourcePositionXValidValues, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).positionX = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionX";
    };

    for (auto& [input, value, expected] : testFixtureLengthLightPosition) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightLightSourcePositionYValidValues, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).positionY = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionY";
    };

    for (auto& [input, value, expected] : testFixtureLengthLightPosition) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionZValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionZValidValues, TestSize.Level1)
{
#ifdef WRONG_GEN
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).positionZ = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionZ";
    };

    for (auto& [input, value, expected] : testFixtureLengthLightPosition) {
        checkValue(input, expected, value);
    }
#endif
}

/*
 * @tc.name: setPointLightTestPointLightLightSourceIntensity
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightLightSourceIntensity, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](
                          const std::string& input, const double& expected, const Ark_Number& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).intensity = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_NAME);
        auto result = StringUtils::StringToDouble(resultStr);
        EXPECT_NEAR(result, expected, FLT_EPSILON) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.intensity";
    };

    for (auto& [input, value, expected] : testFixtureIntensityValidValues) {
        checkValue(input, expected, value);
    }

    for (auto& [input, value] : testFixtureIntensityInvalidValues) {
        checkValue(input, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_DEFAULT_VALUE, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourceColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightLightSourceColorValidValues, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).color = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.color";
    };

    for (auto& [input, value, expected] : testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourceColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightLightSourceColorInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](const std::string& input, const Opt_ResourceColor& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(WriteTo(inputValuePointLight).lightSource).color = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_DEFAULT_VALUE) <<
            "Default value for attribute 'pointLight.lightSource'";
    };

    for (auto& [input, value] : testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setPointLightTestPointLightIlluminatedValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightIlluminatedValidValues, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_IlluminatedType& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        WriteTo(inputValuePointLight).illuminated = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.illuminated";
    };

    for (auto& [input, value, expected] : testFixtureEnumIlluminatedTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_IlluminatedType>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightIlluminatedInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightIlluminatedInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](const std::string& input, const Opt_IlluminatedType& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;
        WriteTo(inputValuePointLight).illuminated = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.illuminated";
    };

    for (auto& [input, value] : testFixtureEnumIlluminatedTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_IlluminatedType>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightBloomValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightBloomValidValues, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        WriteTo(inputValuePointLight).bloom = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_BLOOM_NAME);
        auto result = StringUtils::StringToDouble(resultStr);
        EXPECT_NEAR(result, ATTRIBUTE_POINT_LIGHT_I_BLOOM_DEFAULT_VALUE, FLT_EPSILON) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.bloom";
    };

    for (auto& [input, value, expected] : testFixtureBloomValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightBloomInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setPointLightTestPointLightBloomInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle optPointLight;
    Ark_PointLightStyle& initValuePointLight = WriteTo(optPointLight);

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(testFixtureLengthLightPosition[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(testFixtureLengthLightPosition[0]);
#ifdef WRONG_GEN
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(testFixtureLengthLightPosition[0]);
#endif
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(testFixtureIntensityValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &optPointLight](const std::string& input, const Opt_Number& value) {
        Opt_PointLightStyle inputValuePointLight = optPointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(inputValuePointLight).bloom = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_BLOOM_NAME);
        auto result = StringUtils::StringToDouble(resultStr);
        EXPECT_NEAR(result, ATTRIBUTE_POINT_LIGHT_I_BLOOM_DEFAULT_VALUE, FLT_EPSILON) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.bloom";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}
#endif // PointLight
} // namespace OHOS::Ace::NG
