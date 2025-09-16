/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_ALIGN_ITEMS_NAME = "alignItems";
const auto ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE = "ItemAlign.Start";
} // namespace

class GridRowModifierTest : public ModifierTestBase<GENERATED_ArkUIGridRowModifier,
                                &GENERATED_ArkUINodeModifiers::getGridRowModifier, GENERATED_ARKUI_GRID_ROW> {
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
 * @tc.name: setGridRowOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setGridRowOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setAlignItemsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setAlignItemsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE) << "Default value for attribute 'alignItems'";
}

/*
 * @tc.name: setAlignItemsTestAlignItemsValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setAlignItemsTestAlignItemsValidValues, TestSize.Level1)
{
    Opt_ItemAlign initValueAlignItems;

    // Initial setup
    initValueAlignItems = ArkValue<Opt_ItemAlign>(std::get<1>(Fixtures::testFixtureEnumItemAlignValidValues[0]));

    auto checkValue = [this, &initValueAlignItems](
                          const std::string& input, const std::string& expectedStr, const Opt_ItemAlign& value) {
        Opt_ItemAlign inputValueAlignItems = initValueAlignItems;

        inputValueAlignItems = value;
        modifier_->setAlignItems(node_, &inputValueAlignItems);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAlignItems, attribute: alignItems";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumItemAlignValidValues) {
        checkValue(input, expected, ArkValue<Opt_ItemAlign>(value));
    }
}

/*
 * @tc.name: setAlignItemsTestAlignItemsInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridRowModifierTest, DISABLED_setAlignItemsTestAlignItemsInvalidValues, TestSize.Level1)
{
    Opt_ItemAlign initValueAlignItems;

    // Initial setup
    initValueAlignItems = ArkValue<Opt_ItemAlign>(std::get<1>(Fixtures::testFixtureEnumItemAlignValidValues[0]));

    auto checkValue = [this, &initValueAlignItems](const std::string& input, const Opt_ItemAlign& value) {
        Opt_ItemAlign inputValueAlignItems = initValueAlignItems;

        modifier_->setAlignItems(node_, &inputValueAlignItems);
        inputValueAlignItems = value;
        modifier_->setAlignItems(node_, &inputValueAlignItems);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_ITEMS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_ITEMS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlignItems, attribute: alignItems";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumItemAlignInvalidValues) {
        checkValue(input, ArkValue<Opt_ItemAlign>(value));
    }
}
} // namespace OHOS::Ace::NG
