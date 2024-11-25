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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME = "itemConstraintSize";
const auto ATTRIBUTE_NESTED_SCROLL_NAME = "nestedScroll";
const auto ATTRIBUTE_SCROLLER_NAME = "scroller";
const auto ATTRIBUTE_SCROLLER_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SECTIONS_NAME = "sections";
const auto ATTRIBUTE_SECTIONS_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_LAYOUT_MODE_NAME = "layoutMode";
const auto ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_COLUMNS_TEMPLATE_NAME = "columnsTemplate";
const auto ATTRIBUTE_COLUMNS_TEMPLATE_DEFAULT_VALUE = "1fr";
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_NAME = "minWidth";
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_NAME = "maxWidth";
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_HEIGHT_NAME = "minHeight";
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_HEIGHT_NAME = "maxHeight";
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_ROWS_TEMPLATE_NAME = "rowsTemplate";
const auto ATTRIBUTE_ROWS_TEMPLATE_DEFAULT_VALUE = "1fr";
const auto ATTRIBUTE_COLUMNS_GAP_NAME = "columnsGap";
const auto ATTRIBUTE_COLUMNS_GAP_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_ROWS_GAP_NAME = "rowsGap";
const auto ATTRIBUTE_ROWS_GAP_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_LAYOUT_DIRECTION_NAME = "layoutDirection";
const auto ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE = "FlexDirection.Column";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME = "scrollForward";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE = "NestedScrollMode.SELF_ONLY";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME = "scrollBackward";
const auto ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE = "NestedScrollMode.SELF_ONLY";
const auto ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME = "enableScrollInteraction";
const auto ATTRIBUTE_ENABLE_SCROLL_INTERACTION_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FRICTION_NAME = "friction";
const auto ATTRIBUTE_FRICTION_DEFAULT_VALUE = "0.75";
const auto ATTRIBUTE_CACHED_COUNT_NAME = "cachedCount";
const auto ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE = "1";
} // namespace

class WaterFlowModifierTest : public ModifierTestBase<GENERATED_ArkUIWaterFlowModifier,
                                  &GENERATED_ArkUINodeModifiers::getWaterFlowModifier, GENERATED_ARKUI_WATER_FLOW> {
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
 * @tc.name: setWaterFlowOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setWaterFlowOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SCROLLER_DEFAULT_VALUE) << "Default value for attribute 'options.scroller'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SECTIONS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SECTIONS_DEFAULT_VALUE) << "Default value for attribute 'options.sections'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE) << "Default value for attribute 'options.layoutMode'";
}

/*
 * @tc.name: setWaterFlowOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setWaterFlowOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setColumnsTemplateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setColumnsTemplateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLUMNS_TEMPLATE_DEFAULT_VALUE) << "Default value for attribute 'columnsTemplate'";
}

/*
 * @tc.name: setColumnsTemplateTestColumnsTemplateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setColumnsTemplateTestColumnsTemplateValidValues, TestSize.Level1)
{
    Ark_String initValueColumnsTemplate;

    // Initial setup
    initValueColumnsTemplate = std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]);

    auto checkValue = [this, &initValueColumnsTemplate](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueColumnsTemplate = initValueColumnsTemplate;

        inputValueColumnsTemplate = value;
        modifier_->setColumnsTemplate(node_, &inputValueColumnsTemplate);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setColumnsTemplate, attribute: columnsTemplate";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setItemConstraintSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setItemConstraintSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultItemConstraintSize =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_DEFAULT_VALUE) <<
        "Default value for attribute 'itemConstraintSize.minWidth'";

    resultStr = GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_DEFAULT_VALUE) <<
        "Default value for attribute 'itemConstraintSize.maxWidth'";

    resultStr = GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_HEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'itemConstraintSize.minHeight'";

    resultStr = GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_HEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'itemConstraintSize.maxHeight'";
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMinWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMinWidthValidValues, TestSize.Level1)
{
    Ark_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    initValueItemConstraintSize.minWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.minHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        inputValueItemConstraintSize.minWidth = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setItemConstraintSize, attribute: itemConstraintSize.minWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMinWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMinWidthInvalidValues, TestSize.Level1)
{
    Ark_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    initValueItemConstraintSize.minWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.minHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](const std::string& input, const Opt_Length& value) {
        Ark_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        inputValueItemConstraintSize.minWidth = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setItemConstraintSize, attribute: itemConstraintSize.minWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMaxWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMaxWidthValidValues, TestSize.Level1)
{
    Ark_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    initValueItemConstraintSize.minWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.minHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        inputValueItemConstraintSize.maxWidth = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setItemConstraintSize, attribute: itemConstraintSize.maxWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMaxWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMaxWidthInvalidValues, TestSize.Level1)
{
    Ark_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    initValueItemConstraintSize.minWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.minHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](const std::string& input, const Opt_Length& value) {
        Ark_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        inputValueItemConstraintSize.maxWidth = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setItemConstraintSize, attribute: itemConstraintSize.maxWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMinHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMinHeightValidValues, TestSize.Level1)
{
    Ark_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    initValueItemConstraintSize.minWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.minHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        inputValueItemConstraintSize.minHeight = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setItemConstraintSize, attribute: itemConstraintSize.minHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMinHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMinHeightInvalidValues, TestSize.Level1)
{
    Ark_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    initValueItemConstraintSize.minWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.minHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](const std::string& input, const Opt_Length& value) {
        Ark_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        inputValueItemConstraintSize.minHeight = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setItemConstraintSize, attribute: itemConstraintSize.minHeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMaxHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMaxHeightValidValues, TestSize.Level1)
{
    Ark_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    initValueItemConstraintSize.minWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.minHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        inputValueItemConstraintSize.maxHeight = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setItemConstraintSize, attribute: itemConstraintSize.maxHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMaxHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMaxHeightInvalidValues, TestSize.Level1)
{
    Ark_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    initValueItemConstraintSize.minWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxWidth =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.minHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    initValueItemConstraintSize.maxHeight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](const std::string& input, const Opt_Length& value) {
        Ark_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        inputValueItemConstraintSize.maxHeight = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input
            << ", method: setItemConstraintSize, attribute: itemConstraintSize.maxHeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setRowsTemplateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setRowsTemplateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_TEMPLATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROWS_TEMPLATE_DEFAULT_VALUE) << "Default value for attribute 'rowsTemplate'";
}

/*
 * @tc.name: setRowsTemplateTestRowsTemplateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setRowsTemplateTestRowsTemplateValidValues, TestSize.Level1)
{
    Ark_String initValueRowsTemplate;

    // Initial setup
    initValueRowsTemplate = std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]);

    auto checkValue = [this, &initValueRowsTemplate](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_String inputValueRowsTemplate = initValueRowsTemplate;

        inputValueRowsTemplate = value;
        modifier_->setRowsTemplate(node_, &inputValueRowsTemplate);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_TEMPLATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRowsTemplate, attribute: rowsTemplate";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setColumnsGapTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setColumnsGapTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLUMNS_GAP_DEFAULT_VALUE) << "Default value for attribute 'columnsGap'";
}

/*
 * @tc.name: setColumnsGapTestColumnsGapValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setColumnsGapTestColumnsGapValidValues, TestSize.Level1)
{
    Ark_Length initValueColumnsGap;

    // Initial setup
    initValueColumnsGap = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueColumnsGap](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueColumnsGap = initValueColumnsGap;

        inputValueColumnsGap = value;
        modifier_->setColumnsGap(node_, &inputValueColumnsGap);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_GAP_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setColumnsGap, attribute: columnsGap";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setColumnsGapTestColumnsGapInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setColumnsGapTestColumnsGapInvalidValues, TestSize.Level1)
{
    Ark_Length initValueColumnsGap;

    // Initial setup
    initValueColumnsGap = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueColumnsGap](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueColumnsGap = initValueColumnsGap;

        modifier_->setColumnsGap(node_, &inputValueColumnsGap);
        inputValueColumnsGap = value;
        modifier_->setColumnsGap(node_, &inputValueColumnsGap);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_GAP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COLUMNS_GAP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setColumnsGap, attribute: columnsGap";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setRowsGapTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setRowsGapTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ROWS_GAP_DEFAULT_VALUE) << "Default value for attribute 'rowsGap'";
}

/*
 * @tc.name: setRowsGapTestRowsGapValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setRowsGapTestRowsGapValidValues, TestSize.Level1)
{
    Ark_Length initValueRowsGap;

    // Initial setup
    initValueRowsGap = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueRowsGap](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueRowsGap = initValueRowsGap;

        inputValueRowsGap = value;
        modifier_->setRowsGap(node_, &inputValueRowsGap);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_GAP_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRowsGap, attribute: rowsGap";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRowsGapTestRowsGapInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setRowsGapTestRowsGapInvalidValues, TestSize.Level1)
{
    Ark_Length initValueRowsGap;

    // Initial setup
    initValueRowsGap = std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);

    auto checkValue = [this, &initValueRowsGap](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueRowsGap = initValueRowsGap;

        modifier_->setRowsGap(node_, &inputValueRowsGap);
        inputValueRowsGap = value;
        modifier_->setRowsGap(node_, &inputValueRowsGap);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_GAP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROWS_GAP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRowsGap, attribute: rowsGap";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setLayoutDirectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setLayoutDirectionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE) << "Default value for attribute 'layoutDirection'";
}

/*
 * @tc.name: setLayoutDirectionTestLayoutDirectionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setLayoutDirectionTestLayoutDirectionValidValues, TestSize.Level1)
{
    Ark_FlexDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection = std::get<1>(Fixtures::testFixtureEnumFlexDirectionValidValues[0]);

    auto checkValue = [this, &initValueLayoutDirection](
                          const std::string& input, const std::string& expectedStr, const Ark_FlexDirection& value) {
        Ark_FlexDirection inputValueLayoutDirection = initValueLayoutDirection;

        inputValueLayoutDirection = value;
        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLayoutDirection, attribute: layoutDirection";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFlexDirectionValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setLayoutDirectionTestLayoutDirectionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setLayoutDirectionTestLayoutDirectionInvalidValues, TestSize.Level1)
{
    Ark_FlexDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection = std::get<1>(Fixtures::testFixtureEnumFlexDirectionValidValues[0]);

    auto checkValue = [this, &initValueLayoutDirection](const std::string& input, const Ark_FlexDirection& value) {
        Ark_FlexDirection inputValueLayoutDirection = initValueLayoutDirection;

        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        inputValueLayoutDirection = value;
        modifier_->setLayoutDirection(node_, inputValueLayoutDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLayoutDirection, attribute: layoutDirection";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFlexDirectionInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setNestedScrollTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultNestedScroll =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.scrollForward'";

    resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE) <<
        "Default value for attribute 'nestedScroll.scrollBackward'";
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollForwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setNestedScrollTestNestedScrollScrollForwardValidValues, TestSize.Level1)
{
    Ark_NestedScrollOptions initValueNestedScroll;

    // Initial setup
    initValueNestedScroll.scrollForward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    initValueNestedScroll.scrollBackward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Ark_NestedScrollMode& value) {
        Ark_NestedScrollOptions inputValueNestedScroll = initValueNestedScroll;

        inputValueNestedScroll.scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll.scrollForward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollForwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setNestedScrollTestNestedScrollScrollForwardInvalidValues, TestSize.Level1)
{
    Ark_NestedScrollOptions initValueNestedScroll;

    // Initial setup
    initValueNestedScroll.scrollForward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    initValueNestedScroll.scrollBackward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Ark_NestedScrollOptions inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        inputValueNestedScroll.scrollForward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_FORWARD_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll.scrollForward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollBackwardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setNestedScrollTestNestedScrollScrollBackwardValidValues, TestSize.Level1)
{
    Ark_NestedScrollOptions initValueNestedScroll;

    // Initial setup
    initValueNestedScroll.scrollForward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    initValueNestedScroll.scrollBackward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](
                          const std::string& input, const std::string& expectedStr, const Ark_NestedScrollMode& value) {
        Ark_NestedScrollOptions inputValueNestedScroll = initValueNestedScroll;

        inputValueNestedScroll.scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll.scrollBackward";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumNestedScrollModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setNestedScrollTestNestedScrollScrollBackwardInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setNestedScrollTestNestedScrollScrollBackwardInvalidValues, TestSize.Level1)
{
    Ark_NestedScrollOptions initValueNestedScroll;

    // Initial setup
    initValueNestedScroll.scrollForward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);
    initValueNestedScroll.scrollBackward = std::get<1>(Fixtures::testFixtureEnumNestedScrollModeValidValues[0]);

    auto checkValue = [this, &initValueNestedScroll](const std::string& input, const Ark_NestedScrollMode& value) {
        Ark_NestedScrollOptions inputValueNestedScroll = initValueNestedScroll;

        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        inputValueNestedScroll.scrollBackward = value;
        modifier_->setNestedScroll(node_, &inputValueNestedScroll);
        auto jsonValue = GetJsonValue(node_);
        auto resultNestedScroll = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NESTED_SCROLL_NAME);
        auto resultStr = GetAttrValue<std::string>(resultNestedScroll, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NESTED_SCROLL_I_SCROLL_BACKWARD_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setNestedScroll, attribute: nestedScroll.scrollBackward";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumNestedScrollModeInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setEnableScrollInteractionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setEnableScrollInteractionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_DEFAULT_VALUE) <<
        "Default value for attribute 'enableScrollInteraction'";
}

/*
 * @tc.name: setEnableScrollInteractionTestEnableScrollInteractionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setEnableScrollInteractionTestEnableScrollInteractionValidValues, TestSize.Level1)
{
    Ark_Boolean initValueEnableScrollInteraction;

    // Initial setup
    initValueEnableScrollInteraction = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableScrollInteraction](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableScrollInteraction = initValueEnableScrollInteraction;

        inputValueEnableScrollInteraction = value;
        modifier_->setEnableScrollInteraction(node_, inputValueEnableScrollInteraction);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setEnableScrollInteraction, attribute: enableScrollInteraction";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setFrictionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setFrictionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FRICTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FRICTION_DEFAULT_VALUE) << "Default value for attribute 'friction'";
}

/*
 * @tc.name: setFrictionTestFrictionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setFrictionTestFrictionValidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueFriction;

    // Initial setup
    initValueFriction = ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFrictionResourceValidValues[0]));

    auto checkValue = [this, &initValueFriction](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_Resource& value) {
        Ark_Union_Number_Resource inputValueFriction = initValueFriction;

        inputValueFriction = value;
        modifier_->setFriction(node_, &inputValueFriction);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FRICTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFriction, attribute: friction";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureFrictionResourceValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
}

/*
 * @tc.name: setFrictionTestFrictionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setFrictionTestFrictionInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueFriction;

    // Initial setup
    initValueFriction = ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(
        std::get<1>(Fixtures::testFixtureFrictionResourceValidValues[0]));

    auto checkValue = [this, &initValueFriction](const std::string& input, const Ark_Union_Number_Resource& value) {
        Ark_Union_Number_Resource inputValueFriction = initValueFriction;

        modifier_->setFriction(node_, &inputValueFriction);
        inputValueFriction = value;
        modifier_->setFriction(node_, &inputValueFriction);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FRICTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FRICTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFriction, attribute: friction";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setCachedCountTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setCachedCountTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE) << "Default value for attribute 'cachedCount'";
}

/*
 * @tc.name: setCachedCountTestCachedCountValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setCachedCountTestCachedCountValidValues, TestSize.Level1)
{
    Ark_Number initValueCachedCount;

    // Initial setup
    initValueCachedCount = std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueCachedCount](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueCachedCount = initValueCachedCount;

        inputValueCachedCount = value;
        modifier_->setCachedCount(node_, &inputValueCachedCount);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCachedCount, attribute: cachedCount";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setCachedCountTestCachedCountInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setCachedCountTestCachedCountInvalidValues, TestSize.Level1)
{
    Ark_Number initValueCachedCount;

    // Initial setup
    initValueCachedCount = std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueCachedCount](const std::string& input, const Ark_Number& value) {
        Ark_Number inputValueCachedCount = initValueCachedCount;

        modifier_->setCachedCount(node_, &inputValueCachedCount);
        inputValueCachedCount = value;
        modifier_->setCachedCount(node_, &inputValueCachedCount);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCachedCount, attribute: cachedCount";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegIntFloorInvalidValues) {
        checkValue(input, value);
    }
}
} // namespace OHOS::Ace::NG
