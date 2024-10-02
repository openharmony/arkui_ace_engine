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
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_POINT_LIGHT_NAME = "pointLight";
    const auto ATTRIBUTE_ALIGN_ITEMS_NAME = "alignItems";
    const auto ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE = "VerticalAlign.Center";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_NAME = "justifyContent";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";
    const auto ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_NAME = "lightSource";
    const auto ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME = "illuminated";
    const auto ATTRIBUTE_POINT_LIGHT_ILLUMINATED_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_POINT_LIGHT_BLOOM_NAME = "bloom";
    const auto ATTRIBUTE_POINT_LIGHT_BLOOM_DEFAULT_VALUE = "";
  //  const auto ATTRIBUTE_REVERSE_NAME = "isReverse";
} // namespace

class RowModifierTest : public ModifierTestBase<GENERATED_ArkUIRowModifier, &GENERATED_ArkUINodeModifiers::getRowModifier, GENERATED_ARKUI_ROW> {
};

// TODO: Process non-options argument in setOptions function

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

// Valid values for attribute 'alignItems' of method 'alignItems'
static std::vector<std::tuple<std::string, enum Ark_VerticalAlign, std::string>> alignItemsAlignItemsValidValues = {
    {"ARK_VERTICAL_ALIGN_TOP", Converter::ArkValue<enum Ark_VerticalAlign>(ARK_VERTICAL_ALIGN_TOP), "VerticalAlign.Center"},
    {"ARK_VERTICAL_ALIGN_CENTER", Converter::ArkValue<enum Ark_VerticalAlign>(ARK_VERTICAL_ALIGN_CENTER), "VerticalAlign.Center"},
    {"ARK_VERTICAL_ALIGN_BOTTOM", Converter::ArkValue<enum Ark_VerticalAlign>(ARK_VERTICAL_ALIGN_BOTTOM), "VerticalAlign.Bottom"},
};

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
    enum Ark_VerticalAlign inputValueAlignItems;
    enum Ark_VerticalAlign initValueAlignItems;

    // Initial setup
    initValueAlignItems = std::get<1>(alignItemsAlignItemsValidValues[0]);


    // Verifying attribute's  values
    inputValueAlignItems = initValueAlignItems;
    for (auto&& value: alignItemsAlignItemsValidValues) {
        inputValueAlignItems = std::get<1>(value);
        modifier_->setAlignItems(node_, inputValueAlignItems);
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
HWTEST_F(RowModifierTest, setJustifyContentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE);
}

// Valid values for attribute 'justifyContent' of method 'justifyContent'
static std::vector<std::tuple<std::string, enum Ark_FlexAlign, std::string>> justifyContentJustifyContentValidValues = {
    {"ARK_FLEX_ALIGN_START", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_START), "FlexAlign.Start"},
    {"ARK_FLEX_ALIGN_CENTER", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_CENTER), "FlexAlign.Center"},
    {"ARK_FLEX_ALIGN_END", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_END), "FlexAlign.End"},
    {"ARK_FLEX_ALIGN_SPACE_BETWEEN", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_SPACE_BETWEEN), "FlexAlign.SpaceBetween"},
    {"ARK_FLEX_ALIGN_SPACE_AROUND", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_SPACE_AROUND), "FlexAlign.SpaceAround"},
    {"ARK_FLEX_ALIGN_SPACE_EVENLY", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_SPACE_EVENLY), "FlexAlign.SpaceEvenly"},
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
    enum Ark_FlexAlign inputValueJustifyContent;
    enum Ark_FlexAlign initValueJustifyContent;

    // Initial setup
    initValueJustifyContent = std::get<1>(justifyContentJustifyContentValidValues[0]);

    // Verifying attribute's  values
    inputValueJustifyContent = initValueJustifyContent;
    for (auto&& value: justifyContentJustifyContentValidValues) {
        inputValueJustifyContent = std::get<1>(value);
        modifier_->setJustifyContent(node_, inputValueJustifyContent);
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
HWTEST_F(RowModifierTest, setPointLightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_LIGHT_SOURCE_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_ILLUMINATED_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_BLOOM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_BLOOM_DEFAULT_VALUE);
}

// Valid values for attribute 'lightSource' of method 'pointLight'
static std::vector<std::tuple<std::string, Opt_LightSource, std::string>> pointLightLightSourceValidValues = {
};

/*
 * @tc.name: setReverveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
/*HWTEST_F(RowModifierTest, setReverveDefaultValues, TestSize.Level1)
{
    bool boolResult;

    // Verifying attribute's other values
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_REVERSE_NAME);
    EXPECT_EQ(boolResult, false);
}*/

/*
 * @tc.name: setReverveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
/*HWTEST_F(RowModifierTest, setReverveValidValues, TestSize.Level1)
{
    bool boolResult;
    Opt_Boolean inputValue;

    // Initial setup
    inputValue = Converter::ArkValue<Opt_Boolean>(std::optional(true));
    modifier_->setReverse(node_, &inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_REVERSE_NAME);
    EXPECT_EQ(boolResult, true);

    // Verifying attribute's other values
    inputValue = Converter::ArkValue<Opt_Boolean>(std::optional(false));
    modifier_->setReverse(node_, &inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_REVERSE_NAME);
    EXPECT_EQ(boolResult, false);
}*/

} // namespace OHOS::Ace::NG
