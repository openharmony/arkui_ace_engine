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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "point_light_test.h"
#include "generated/type_helpers.h"
#include <gtest/gtest.h>

#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::PointLight;
using namespace OHOS::Ace::NG::TypeHelper;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME = "constructor";
    const auto ATTRIBUTE_SET_FLEX_DIRECTION_NAME = "direction";
    const auto ATTRIBUTE_SET_FLEX_DIRECTION_DEFAULT_VALUE = "FlexDirection.Row";
    const auto ATTRIBUTE_SET_FLEX_WRAP_NAME = "wrap";
    const auto ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE = "FlexWrap.NoWrap";
    const auto ATTRIBUTE_SET_FLEX_WRAP_VALUE = "FlexWrap.Wrap";
    const auto ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME = "justifyContent";
    const auto ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME = "alignItems";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_DEFAULT_VALUE = "ItemAlign.Start";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME = "alignContent";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";
    const auto ATTRIBUTE_SET_FLEX_SPACE_NAME = "space";
    const auto ATTRIBUTE_SET_FLEX_SPACE_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_SET_FLEX_DIRECTION_VALID_VALUE = "FlexDirection.Column";
    const auto ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_VALID_VALUE = "FlexAlign.Center";
    const auto ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_VALID_VALUE = "ItemAlign.Center";
} // namespace

class FlexModifierTest : public ModifierTestBase<GENERATED_ArkUIFlexModifier,
 &GENERATED_ArkUINodeModifiers::getFlexModifier, GENERATED_ARKUI_FLEX> {
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
 * @tc.name: SetFlexOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, SetFlexOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SET_FLEX_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SET_FLEX_SPACE_DEFAULT_VALUE);

    auto fullJson = GetJsonValue(node_);
    auto flexConstructorAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME);

    auto flexDirection = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_DIRECTION_NAME);
    EXPECT_EQ(flexDirection, ATTRIBUTE_SET_FLEX_DIRECTION_DEFAULT_VALUE);

    auto wrapAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_WRAP_NAME);
    EXPECT_EQ(wrapAttr, ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE);

    auto justifyContentAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(justifyContentAttr, ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_DEFAULT_VALUE);

    auto alignItemAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME);
    EXPECT_EQ(alignItemAttr, ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_DEFAULT_VALUE);

    auto alignContent = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME);
    EXPECT_EQ(alignContent, ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: SetFlexOptionsTestNoWrapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, SetFlexOptionsTestNoWrapValues, TestSize.Level1)
{
    std::string strResult;
    Opt_FlexOptions inputValue;
    Ark_FlexOptions flexOptions;
    flexOptions.direction.value = Converter::ArkValue<Ark_FlexDirection>(ARK_FLEX_DIRECTION_COLUMN);
    flexOptions.wrap.value = Converter::ArkValue<Ark_FlexWrap>(ARK_FLEX_WRAP_NO_WRAP);
    flexOptions.justifyContent.value = Converter::ArkValue<Ark_FlexAlign>(ARK_FLEX_ALIGN_CENTER);
    flexOptions.alignItems.value =  Converter::ArkValue<Ark_ItemAlign>(ARK_ITEM_ALIGN_CENTER);
    inputValue = Converter::ArkValue<Opt_FlexOptions>(flexOptions);
    modifier_->setFlexOptions(node_, &inputValue);
    auto fullJson = GetJsonValue(node_);

    auto flexConstructorAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME);

    auto wrapAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_WRAP_NAME);
    EXPECT_EQ(wrapAttr, ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE);

    auto alignItemAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME);
    EXPECT_EQ(alignItemAttr, ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_VALID_VALUE);

    auto justifyContentAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(justifyContentAttr, ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_VALID_VALUE);

    auto flexDirection = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_DIRECTION_NAME);
    EXPECT_EQ(flexDirection, ATTRIBUTE_SET_FLEX_DIRECTION_VALID_VALUE);

    auto alignContent = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME);
    EXPECT_EQ(alignContent, ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: SetFlexOptionsTestEmptyWrapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, SetFlexOptionsTestEmptyWrapValues, TestSize.Level1)
{
    std::string strResult;
    Opt_FlexOptions inputValue;
    Ark_FlexOptions flexOptions;
    flexOptions.direction = Converter::ArkValue<Opt_FlexDirection>(ARK_FLEX_DIRECTION_COLUMN);
    flexOptions.wrap = Converter::ArkValue<Opt_FlexWrap>(Ark_Empty());
    flexOptions.justifyContent = Converter::ArkValue<Opt_FlexAlign>(ARK_FLEX_ALIGN_CENTER);
    flexOptions.alignItems =  Converter::ArkValue<Opt_ItemAlign>(ARK_ITEM_ALIGN_CENTER);
    inputValue = Converter::ArkValue<Opt_FlexOptions>(flexOptions);
    modifier_->setFlexOptions(node_, &inputValue);
    auto fullJson = GetJsonValue(node_);

    auto flexConstructorAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME);

    auto wrapAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_WRAP_NAME);
    EXPECT_EQ(wrapAttr, ATTRIBUTE_SET_FLEX_WRAP_DEFAULT_VALUE);

    auto alignItemAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME);
    EXPECT_EQ(alignItemAttr, ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_VALID_VALUE);

    auto justifyContentAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(justifyContentAttr, ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_VALID_VALUE);

    auto flexDirection = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_DIRECTION_NAME);
    EXPECT_EQ(flexDirection, ATTRIBUTE_SET_FLEX_DIRECTION_VALID_VALUE);

    auto alignContent = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME);
    EXPECT_EQ(alignContent, ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: SetFlexOptionsTestWrapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, SetFlexOptionsTestWrapValues, TestSize.Level1)
{
    std::string strResult;
    Opt_FlexOptions inputValue;
    Ark_FlexOptions flexOptions;
    flexOptions.direction.value = Converter::ArkValue<Ark_FlexDirection>(ARK_FLEX_DIRECTION_COLUMN);
    flexOptions.wrap.value = Converter::ArkValue<Ark_FlexWrap>(ARK_FLEX_WRAP_WRAP);
    flexOptions.justifyContent.value = Converter::ArkValue<Ark_FlexAlign>(ARK_FLEX_ALIGN_CENTER);
    flexOptions.alignItems.value =  Converter::ArkValue<Ark_ItemAlign>(ARK_ITEM_ALIGN_CENTER);

    inputValue = Converter::ArkValue<Opt_FlexOptions>(flexOptions);
    modifier_->setFlexOptions(node_, &inputValue);
    auto fullJson = GetJsonValue(node_);
    auto flexConstructorAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SET_FLEX_CONSTRUCTOR_NAME);

    auto wrapAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_WRAP_NAME);
    EXPECT_EQ(wrapAttr, ATTRIBUTE_SET_FLEX_WRAP_VALUE);

    auto alignItemAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_NAME);
    EXPECT_EQ(alignItemAttr, ATTRIBUTE_SET_FLEX_ALIGN_ITEMS_VALID_VALUE);

    auto justifyContentAttr = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(justifyContentAttr, ATTRIBUTE_SET_FLEX_JUSTIFY_CONTENT_VALID_VALUE);

    auto flexDirection = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_DIRECTION_NAME);
    EXPECT_EQ(flexDirection, ATTRIBUTE_SET_FLEX_DIRECTION_VALID_VALUE);

    auto alignContent = flexConstructorAttrs->GetString(ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_NAME);
    EXPECT_EQ(alignContent, ATTRIBUTE_SET_FLEX_ALIGN_CONTENT_DEFAULT_VALUE);
}

/*
 * @tc.name: setPointLightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FlexModifierTest, setPointLightTestDefaultValues, TestSize.Level1)
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightLightSourcePositionXValidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionX = value;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightLightSourcePositionYValidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionY = value;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
HWTEST_F(FlexModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionZValidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionZ = value;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightLightSourceIntensity, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const double& expected, const Ark_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).intensity = value;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightLightSourceColorValidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).color = value;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightLightSourceColorInvalidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_ResourceColor& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
        WriteTo(inputValuePointLight.lightSource).color = value;
        optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightIlluminatedValidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_IlluminatedType& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        inputValuePointLight.illuminated = value;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightIlluminatedInvalidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_IlluminatedType& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;
        inputValuePointLight.illuminated = value;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightBloomValidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        inputValuePointLight.bloom = value;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
HWTEST_F(FlexModifierTest, setPointLightTestPointLightBloomInvalidValues, TestSize.Level1)
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
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(testFixtureBloomValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;
        auto optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
        inputValuePointLight.bloom = value;
        optValue = Converter::ArkValue<Opt_PointLightStyle>(inputValuePointLight);
        modifier_->setPointLight(node_, &optValue);
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
