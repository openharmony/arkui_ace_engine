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
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_ALIGN_ITEMS_NAME = "alignItems";
    const auto ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE = "HorizontalAlign.Center";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_NAME = "justifyContent";
    const auto ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE = "FlexAlign.Start";
} // namespace

class ColumnModifierTest : public ModifierTestBase<
    GENERATED_ArkUIColumnModifier,
    &GENERATED_ArkUINodeModifiers::getColumnModifier,
    GENERATED_ARKUI_COLUMN
> {
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

// Valid values for attribute 'alignItems' of method 'alignItems'
static std::vector<std::tuple<std::string, enum Ark_HorizontalAlign, std::string>> alignItemsAlignItemsValidValues = {
    {"ARK_HORIZONTAL_ALIGN_START", ARK_HORIZONTAL_ALIGN_START, "HorizontalAlign.Start"},
    {"ARK_HORIZONTAL_ALIGN_CENTER", ARK_HORIZONTAL_ALIGN_CENTER, "HorizontalAlign.Center"},
    {"ARK_HORIZONTAL_ALIGN_END", ARK_HORIZONTAL_ALIGN_END, "HorizontalAlign.End"},
};

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
HWTEST_F(ColumnModifierTest, setJustifyContentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JUSTIFY_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_JUSTIFY_CONTENT_DEFAULT_VALUE);
}

// Valid values for attribute 'justifyContent' of method 'justifyContent'
static std::vector<std::tuple<std::string, enum Ark_FlexAlign, std::string>> justifyContentJustifyContentValidValues = {
    {"ARK_FLEX_ALIGN_START", ARK_FLEX_ALIGN_START, "FlexAlign.Start"},
    {"ARK_FLEX_ALIGN_CENTER", ARK_FLEX_ALIGN_CENTER, "FlexAlign.Center"},
    {"ARK_FLEX_ALIGN_END", ARK_FLEX_ALIGN_END, "FlexAlign.End"},
    {"ARK_FLEX_ALIGN_SPACE_BETWEEN", ARK_FLEX_ALIGN_SPACE_BETWEEN, "FlexAlign.SpaceBetween"},
    {"ARK_FLEX_ALIGN_SPACE_AROUND", ARK_FLEX_ALIGN_SPACE_AROUND, "FlexAlign.SpaceAround"},
    {"ARK_FLEX_ALIGN_SPACE_EVENLY", ARK_FLEX_ALIGN_SPACE_EVENLY, "FlexAlign.SpaceEvenly"},
};

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
        modifier_->setJustifyContent(node_, inputValueJustifyContent);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_JUSTIFY_CONTENT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

} // namespace OHOS::Ace::NG
