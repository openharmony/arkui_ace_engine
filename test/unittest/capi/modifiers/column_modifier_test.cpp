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
    const auto ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE = "HorizontalAlign.Center";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_NAME = "justifyContent";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";

    // Valid values for attribute 'alignItems' of method 'alignItems'
    static const std::vector<std::tuple<std::string,
        Ark_HorizontalAlign,
        std::string>> alignItemsAlignItemsValidValues = {
        {"ARK_HORIZONTAL_ALIGN_START", ARK_HORIZONTAL_ALIGN_START, "HorizontalAlign.Start"},
        {"ARK_HORIZONTAL_ALIGN_CENTER", ARK_HORIZONTAL_ALIGN_CENTER, "HorizontalAlign.Center"},
        {"ARK_HORIZONTAL_ALIGN_END", ARK_HORIZONTAL_ALIGN_END, "HorizontalAlign.End"},
    };

    // Valid values for attribute 'justifyContent' of method 'justifyContent'
    static const std::vector<std::tuple<std::string,
        Ark_FlexAlign,
        std::string>> justifyContentJustifyContentValidValues = {
        {"ARK_FLEX_ALIGN_START", ARK_FLEX_ALIGN_START, "FlexAlign.Start"},
        {"ARK_FLEX_ALIGN_CENTER", ARK_FLEX_ALIGN_CENTER, "FlexAlign.Center"},
        {"ARK_FLEX_ALIGN_END", ARK_FLEX_ALIGN_END, "FlexAlign.End"},
        {"ARK_FLEX_ALIGN_SPACE_BETWEEN", ARK_FLEX_ALIGN_SPACE_BETWEEN, "FlexAlign.SpaceBetween"},
        {"ARK_FLEX_ALIGN_SPACE_AROUND", ARK_FLEX_ALIGN_SPACE_AROUND, "FlexAlign.SpaceAround"},
        {"ARK_FLEX_ALIGN_SPACE_EVENLY", ARK_FLEX_ALIGN_SPACE_EVENLY, "FlexAlign.SpaceEvenly"},
    };
} // namespace

class ColumnModifierTest : public ModifierTestBase<
    GENERATED_ArkUIColumnModifier,
    &GENERATED_ArkUINodeModifiers::getColumnModifier,
    GENERATED_ARKUI_COLUMN
> {
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
HWTEST_F(ColumnModifierTest, setAlignItemsTestDefaultValues, TestSize.Level1)
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
HWTEST_F(ColumnModifierTest, setAlignItemsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_HorizontalAlign inputValueAlignItems;
    Ark_HorizontalAlign initValueAlignItems;

    // Initial setup
    initValueAlignItems = std::get<1>(alignItemsAlignItemsValidValues[0]);


    // Verifying attribute's  values
    inputValueAlignItems = initValueAlignItems;
    for (auto&& value: alignItemsAlignItemsValidValues) {
        inputValueAlignItems = std::get<1>(value);
        auto optInputValueAlignItems = Converter::ArkValue<Opt_HorizontalAlign>(inputValueAlignItems);
        modifier_->setAlignItems(node_, &optInputValueAlignItems);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setJustifyContentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnModifierTest, setJustifyContentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: setJustifyContentTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnModifierTest, setJustifyContentTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_FlexAlign inputValueJustifyContent;
    Ark_FlexAlign initValueJustifyContent;

    // Initial setup
    initValueJustifyContent = std::get<1>(justifyContentJustifyContentValidValues[0]);


    // Verifying attribute's  values
    inputValueJustifyContent = initValueJustifyContent;
    for (auto&& value: justifyContentJustifyContentValidValues) {
        inputValueJustifyContent = std::get<1>(value);
        auto optInputValueJustifyContent = Converter::ArkValue<Opt_FlexAlign>(inputValueJustifyContent);
        modifier_->setJustifyContent(node_, &optInputValueJustifyContent);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JUSTIFY_CONTENT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPointLightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnModifierTest, setPointLightTestDefaultValues, TestSize.Level1)
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

#ifdef WRONG_SDK // PointLight
/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightLightSourcePositionXValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionX = value;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightLightSourcePositionYValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionY = value;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionZValidValues, TestSize.Level1)
{
#ifdef WRONG_GEN
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionZ = value;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightLightSourceIntensity, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const double& expected, const Ark_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).intensity = value;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightLightSourceColorValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).color = value;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightLightSourceColorInvalidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_ResourceColor& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
        WriteTo(inputValuePointLight.lightSource).color = value;
        optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightIlluminatedValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_IlluminatedType& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        inputValuePointLight.illuminated = value;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightIlluminatedInvalidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_IlluminatedType& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;
        inputValuePointLight.illuminated = value;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightBloomValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        inputValuePointLight.bloom = value;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
HWTEST_F(ColumnModifierTest, setPointLightTestPointLightBloomInvalidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

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

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;
        auto optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
        inputValuePointLight.bloom = value;
        optPointLight = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optPointLight);
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
