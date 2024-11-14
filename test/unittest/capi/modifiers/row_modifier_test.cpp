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
    const auto ATTRIBUTE_ALIGN_ITEMS_NAME = "alignItems";
    const auto ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE = "VerticalAlign.Center";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_NAME = "justifyContent";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";
    const auto ATTRIBUTE_IS_REVERSE_NAME = "isReverse";
    const auto ATTRIBUTE_IS_REVERSE_DEFAULT_VALUE = "0";
} // namespace

class RowModifierTest : public ModifierTestBase<GENERATED_ArkUIRowModifier,
    &GENERATED_ArkUINodeModifiers::getRowModifier, GENERATED_ARKUI_ROW> {
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
    Ark_VerticalAlign inputValueAlignItems;

    // Verifying attribute's  values
    inputValueAlignItems = Converter::ArkValue<enum Ark_VerticalAlign>(ARK_VERTICAL_ALIGN_BOTTOM);
    modifier_->setAlignItems(node_, inputValueAlignItems);
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
static std::vector<std::tuple<std::string, enum Ark_FlexAlign, std::string>>
    justifyContentJustifyContentValidValues = {
    {"ARK_FLEX_ALIGN_START", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_START),
        "FlexAlign.Start"},
    {"ARK_FLEX_ALIGN_CENTER", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_CENTER),
        "FlexAlign.Center"},
    {"ARK_FLEX_ALIGN_END", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_END),
        "FlexAlign.End"},
    {"ARK_FLEX_ALIGN_SPACE_BETWEEN", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_SPACE_BETWEEN),
        "FlexAlign.SpaceBetween"},
    {"ARK_FLEX_ALIGN_SPACE_AROUND", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_SPACE_AROUND),
        "FlexAlign.SpaceAround"},
    {"ARK_FLEX_ALIGN_SPACE_EVENLY", Converter::ArkValue<enum Ark_FlexAlign>(ARK_FLEX_ALIGN_SPACE_EVENLY),
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
    Ark_FlexAlign inputValueJustifyContent;

    // Verifying attribute's values
    inputValueJustifyContent = std::get<1>(justifyContentJustifyContentValidValues[0]);
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
 * @tc.name: setIsReverseDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */

HWTEST_F(RowModifierTest, setIsReverseDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    std::cout << jsonValue->ToString() << std::endl;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_REVERSE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IS_REVERSE_DEFAULT_VALUE);
}
#ifdef WRONG_OPT
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
    Ark_Boolean inputValueSelect;
    Ark_Boolean initValueSelect;

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
#endif
} // namespace OHOS::Ace::NG
