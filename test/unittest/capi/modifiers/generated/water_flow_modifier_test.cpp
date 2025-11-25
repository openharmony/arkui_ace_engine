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
const auto ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME = "itemConstraintSize";
const auto ATTRIBUTE_LAYOUT_MODE_NAME = "layoutMode";
const auto ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE = "";
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
const auto ATTRIBUTE_CACHED_COUNT_NAME = "cachedCount";
const auto ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE = "1";
const auto ATTRIBUTE_CACHED_COUNT_I_COUNT_NAME = "count";
const auto ATTRIBUTE_CACHED_COUNT_I_COUNT_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_CACHED_COUNT_I_SHOW_NAME = "show";
const auto ATTRIBUTE_CACHED_COUNT_I_SHOW_DEFAULT_VALUE = "!NOT-DEFINED!";
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
HWTEST_F(WaterFlowModifierTest, setWaterFlowOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE) << "Default value for attribute 'options.layoutMode'";
}

/*
 * @tc.name: setWaterFlowOptionsTestOptionsLayoutModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setWaterFlowOptionsTestOptionsLayoutModeValidValues, TestSize.Level1)
{
    Opt_WaterFlowOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).layoutMode =
        ArkValue<Opt_WaterFlowLayoutMode>(std::get<1>(Fixtures::testFixtureEnumWaterFlowLayoutModeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_WaterFlowLayoutMode& value) {
        Opt_WaterFlowOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).layoutMode = value;
        modifier_->setWaterFlowOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setWaterFlowOptions, attribute: options.layoutMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumWaterFlowLayoutModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_WaterFlowLayoutMode>(value));
    }
}

/*
 * @tc.name: setWaterFlowOptionsTestOptionsLayoutModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setWaterFlowOptionsTestOptionsLayoutModeInvalidValues, TestSize.Level1)
{
    Opt_WaterFlowOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).layoutMode =
        ArkValue<Opt_WaterFlowLayoutMode>(std::get<1>(Fixtures::testFixtureEnumWaterFlowLayoutModeValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_WaterFlowLayoutMode& value) {
        Opt_WaterFlowOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).layoutMode = value;
        modifier_->setWaterFlowOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_MODE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setWaterFlowOptions, attribute: options.layoutMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumWaterFlowLayoutModeInvalidValues) {
        checkValue(input, ArkValue<Opt_WaterFlowLayoutMode>(value));
    }
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
    Opt_String initValueColumnsTemplate;

    // Initial setup
    initValueColumnsTemplate = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));

    auto checkValue = [this, &initValueColumnsTemplate](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Opt_String inputValueColumnsTemplate = initValueColumnsTemplate;

        inputValueColumnsTemplate = value;
        modifier_->setColumnsTemplate(node_, &inputValueColumnsTemplate);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setColumnsTemplate, attribute: columnsTemplate";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setColumnsTemplateTestColumnsTemplateInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setColumnsTemplateTestColumnsTemplateInvalidValues, TestSize.Level1)
{
    Opt_String initValueColumnsTemplate;

    // Initial setup
    initValueColumnsTemplate = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));

    auto checkValue = [this, &initValueColumnsTemplate](const std::string& input, const Opt_String& value) {
        Opt_String inputValueColumnsTemplate = initValueColumnsTemplate;

        modifier_->setColumnsTemplate(node_, &inputValueColumnsTemplate);
        inputValueColumnsTemplate = value;
        modifier_->setColumnsTemplate(node_, &inputValueColumnsTemplate);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COLUMNS_TEMPLATE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setColumnsTemplate, attribute: columnsTemplate";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
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
    Opt_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    WriteTo(initValueItemConstraintSize).minWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).minHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        WriteTo(inputValueItemConstraintSize).minWidth = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setItemConstraintSize, attribute: itemConstraintSize.minWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMinWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMinWidthInvalidValues, TestSize.Level1)
{
    Opt_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    WriteTo(initValueItemConstraintSize).minWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).minHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](const std::string& input, const Opt_Length& value) {
        Opt_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        WriteTo(inputValueItemConstraintSize).minWidth = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setItemConstraintSize, attribute: itemConstraintSize.minWidth";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
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
    Opt_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    WriteTo(initValueItemConstraintSize).minWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).minHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        WriteTo(inputValueItemConstraintSize).maxWidth = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setItemConstraintSize, attribute: itemConstraintSize.maxWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMaxWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMaxWidthInvalidValues, TestSize.Level1)
{
    Opt_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    WriteTo(initValueItemConstraintSize).minWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).minHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](const std::string& input, const Opt_Length& value) {
        Opt_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        WriteTo(inputValueItemConstraintSize).maxWidth = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setItemConstraintSize, attribute: itemConstraintSize.maxWidth";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
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
    Opt_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    WriteTo(initValueItemConstraintSize).minWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).minHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        WriteTo(inputValueItemConstraintSize).minHeight = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MIN_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setItemConstraintSize, attribute: itemConstraintSize.minHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMinHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMinHeightInvalidValues, TestSize.Level1)
{
    Opt_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    WriteTo(initValueItemConstraintSize).minWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).minHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](const std::string& input, const Opt_Length& value) {
        Opt_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        WriteTo(inputValueItemConstraintSize).minHeight = value;
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

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
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
    Opt_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    WriteTo(initValueItemConstraintSize).minWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).minHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        WriteTo(inputValueItemConstraintSize).maxHeight = value;
        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultItemConstraintSize =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultItemConstraintSize, ATTRIBUTE_ITEM_CONSTRAINT_SIZE_I_MAX_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                          ", method: setItemConstraintSize, attribute: itemConstraintSize.maxHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setItemConstraintSizeTestItemConstraintSizeMaxHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setItemConstraintSizeTestItemConstraintSizeMaxHeightInvalidValues, TestSize.Level1)
{
    Opt_ConstraintSizeOptions initValueItemConstraintSize;

    // Initial setup
    WriteTo(initValueItemConstraintSize).minWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxWidth =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).minHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));
    WriteTo(initValueItemConstraintSize).maxHeight =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumAnyValidValues[0]));

    auto checkValue = [this, &initValueItemConstraintSize](const std::string& input, const Opt_Length& value) {
        Opt_ConstraintSizeOptions inputValueItemConstraintSize = initValueItemConstraintSize;

        modifier_->setItemConstraintSize(node_, &inputValueItemConstraintSize);
        WriteTo(inputValueItemConstraintSize).maxHeight = value;
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

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
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
    Opt_String initValueRowsTemplate;

    // Initial setup
    initValueRowsTemplate = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));

    auto checkValue = [this, &initValueRowsTemplate](
                          const std::string& input, const std::string& expectedStr, const Opt_String& value) {
        Opt_String inputValueRowsTemplate = initValueRowsTemplate;

        inputValueRowsTemplate = value;
        modifier_->setRowsTemplate(node_, &inputValueRowsTemplate);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_TEMPLATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRowsTemplate, attribute: rowsTemplate";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringNoEmptyValidValues) {
        checkValue(input, expected, ArkValue<Opt_String>(value));
    }
}

/*
 * @tc.name: setRowsTemplateTestRowsTemplateInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setRowsTemplateTestRowsTemplateInvalidValues, TestSize.Level1)
{
    Opt_String initValueRowsTemplate;

    // Initial setup
    initValueRowsTemplate = ArkValue<Opt_String>(std::get<1>(Fixtures::testFixtureStringNoEmptyValidValues[0]));

    auto checkValue = [this, &initValueRowsTemplate](const std::string& input, const Opt_String& value) {
        Opt_String inputValueRowsTemplate = initValueRowsTemplate;

        modifier_->setRowsTemplate(node_, &inputValueRowsTemplate);
        inputValueRowsTemplate = value;
        modifier_->setRowsTemplate(node_, &inputValueRowsTemplate);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_TEMPLATE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROWS_TEMPLATE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRowsTemplate, attribute: rowsTemplate";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_String>());
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
    Opt_Length initValueColumnsGap;

    // Initial setup
    initValueColumnsGap =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueColumnsGap](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueColumnsGap = initValueColumnsGap;

        inputValueColumnsGap = value;
        modifier_->setColumnsGap(node_, &inputValueColumnsGap);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_GAP_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setColumnsGap, attribute: columnsGap";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setColumnsGapTestColumnsGapInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setColumnsGapTestColumnsGapInvalidValues, TestSize.Level1)
{
    Opt_Length initValueColumnsGap;

    // Initial setup
    initValueColumnsGap =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueColumnsGap](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueColumnsGap = initValueColumnsGap;

        modifier_->setColumnsGap(node_, &inputValueColumnsGap);
        inputValueColumnsGap = value;
        modifier_->setColumnsGap(node_, &inputValueColumnsGap);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLUMNS_GAP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COLUMNS_GAP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setColumnsGap, attribute: columnsGap";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
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
    Opt_Length initValueRowsGap;

    // Initial setup
    initValueRowsGap =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueRowsGap](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Opt_Length inputValueRowsGap = initValueRowsGap;

        inputValueRowsGap = value;
        modifier_->setRowsGap(node_, &inputValueRowsGap);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_GAP_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setRowsGap, attribute: rowsGap";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value));
    }
}

/*
 * @tc.name: setRowsGapTestRowsGapInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setRowsGapTestRowsGapInvalidValues, TestSize.Level1)
{
    Opt_Length initValueRowsGap;

    // Initial setup
    initValueRowsGap =
        ArkUnion<Opt_Length, Ark_Float64>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueRowsGap](const std::string& input, const Opt_Length& value) {
        Opt_Length inputValueRowsGap = initValueRowsGap;

        modifier_->setRowsGap(node_, &inputValueRowsGap);
        inputValueRowsGap = value;
        modifier_->setRowsGap(node_, &inputValueRowsGap);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ROWS_GAP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ROWS_GAP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRowsGap, attribute: rowsGap";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_Float64>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
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
    Opt_FlexDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection =
        ArkValue<Opt_FlexDirection>(std::get<1>(Fixtures::testFixtureEnumFlexDirectionValidValues[0]));

    auto checkValue = [this, &initValueLayoutDirection](
                          const std::string& input, const std::string& expectedStr, const Opt_FlexDirection& value) {
        Opt_FlexDirection inputValueLayoutDirection = initValueLayoutDirection;

        inputValueLayoutDirection = value;
        modifier_->setLayoutDirection(node_, &inputValueLayoutDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setLayoutDirection, attribute: layoutDirection";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumFlexDirectionValidValues) {
        checkValue(input, expected, ArkValue<Opt_FlexDirection>(value));
    }
}

/*
 * @tc.name: setLayoutDirectionTestLayoutDirectionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setLayoutDirectionTestLayoutDirectionInvalidValues, TestSize.Level1)
{
    Opt_FlexDirection initValueLayoutDirection;

    // Initial setup
    initValueLayoutDirection =
        ArkValue<Opt_FlexDirection>(std::get<1>(Fixtures::testFixtureEnumFlexDirectionValidValues[0]));

    auto checkValue = [this, &initValueLayoutDirection](const std::string& input, const Opt_FlexDirection& value) {
        Opt_FlexDirection inputValueLayoutDirection = initValueLayoutDirection;

        modifier_->setLayoutDirection(node_, &inputValueLayoutDirection);
        inputValueLayoutDirection = value;
        modifier_->setLayoutDirection(node_, &inputValueLayoutDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setLayoutDirection, attribute: layoutDirection";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumFlexDirectionInvalidValues) {
        checkValue(input, ArkValue<Opt_FlexDirection>(value));
    }
}

/*
 * @tc.name: setCachedCount0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setCachedCount0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE) << "Default value for attribute 'cachedCount'";
}

/*
 * @tc.name: setCachedCount0TestCachedCountValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setCachedCount0TestCachedCountValidValues, TestSize.Level1)
{
    Opt_Int32 initValueCachedCount;

    // Initial setup
    initValueCachedCount = ArkValue<Opt_Int32>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));

    auto checkValue = [this, &initValueCachedCount](
                          const std::string& input, const std::string& expectedStr, const Opt_Int32& value) {
        Opt_Int32 inputValueCachedCount = initValueCachedCount;

        inputValueCachedCount = value;
        modifier_->setCachedCount0(node_, &inputValueCachedCount);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCachedCount0, attribute: cachedCount";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, ArkValue<Opt_Int32>(value));
    }
}

/*
 * @tc.name: setCachedCount0TestCachedCountInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setCachedCount0TestCachedCountInvalidValues, TestSize.Level1)
{
    Opt_Int32 initValueCachedCount;

    // Initial setup
    initValueCachedCount = ArkValue<Opt_Int32>(std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]));

    auto checkValue = [this, &initValueCachedCount](const std::string& input, const Opt_Int32& value) {
        Opt_Int32 inputValueCachedCount = initValueCachedCount;

        modifier_->setCachedCount0(node_, &inputValueCachedCount);
        inputValueCachedCount = value;
        modifier_->setCachedCount0(node_, &inputValueCachedCount);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCachedCount0, attribute: cachedCount";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegIntFloorInvalidValues) {
        checkValue(input, ArkValue<Opt_Int32>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Int32>());
}

/*
 * @tc.name: setCachedCount1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setCachedCount1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCachedCount =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCachedCount, ATTRIBUTE_CACHED_COUNT_I_COUNT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CACHED_COUNT_I_COUNT_DEFAULT_VALUE) <<
        "Default value for attribute 'cachedCount.count'";

    resultStr = GetAttrValue<std::string>(resultCachedCount, ATTRIBUTE_CACHED_COUNT_I_SHOW_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CACHED_COUNT_I_SHOW_DEFAULT_VALUE) <<
        "Default value for attribute 'cachedCount.show'";
}

/*
 * @tc.name: setCachedCount1TestCachedCountCountValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setCachedCount1TestCachedCountCountValidValues, TestSize.Level1)
{
    Opt_Int32 initValueCount;
    Opt_Boolean initValueShow;

    // Initial setup
    initValueCount = ArkValue<Opt_Int32>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueShow = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueCount, &initValueShow](
                          const std::string& input, const std::string& expectedStr, const Opt_Int32& value) {
        Opt_Int32 inputValueCount = initValueCount;
        Opt_Boolean inputValueShow = initValueShow;

        inputValueCount = value;
        modifier_->setCachedCount1(node_, &inputValueCount, &inputValueShow);
        auto jsonValue = GetJsonValue(node_);
        auto resultCachedCount = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCachedCount, ATTRIBUTE_CACHED_COUNT_I_COUNT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCachedCount1, attribute: cachedCount.count";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Int32>(value));
    }
}

/*
 * @tc.name: setCachedCount1TestCachedCountCountInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setCachedCount1TestCachedCountCountInvalidValues, TestSize.Level1)
{
    Opt_Int32 initValueCount;
    Opt_Boolean initValueShow;

    // Initial setup
    initValueCount = ArkValue<Opt_Int32>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueShow = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueCount, &initValueShow](const std::string& input, const Opt_Int32& value) {
        Opt_Int32 inputValueCount = initValueCount;
        Opt_Boolean inputValueShow = initValueShow;

        modifier_->setCachedCount1(node_, &inputValueCount, &inputValueShow);
        inputValueCount = value;
        modifier_->setCachedCount1(node_, &inputValueCount, &inputValueShow);
        auto jsonValue = GetJsonValue(node_);
        auto resultCachedCount = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCachedCount, ATTRIBUTE_CACHED_COUNT_I_COUNT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CACHED_COUNT_I_COUNT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCachedCount1, attribute: cachedCount.count";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Int32>());
}

/*
 * @tc.name: setCachedCount1TestCachedCountShowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setCachedCount1TestCachedCountShowValidValues, TestSize.Level1)
{
    Opt_Int32 initValueCount;
    Opt_Boolean initValueShow;

    // Initial setup
    initValueCount = ArkValue<Opt_Int32>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueShow = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueCount, &initValueShow](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Int32 inputValueCount = initValueCount;
        Opt_Boolean inputValueShow = initValueShow;

        inputValueShow = value;
        modifier_->setCachedCount1(node_, &inputValueCount, &inputValueShow);
        auto jsonValue = GetJsonValue(node_);
        auto resultCachedCount = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCachedCount, ATTRIBUTE_CACHED_COUNT_I_SHOW_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCachedCount1, attribute: cachedCount.show";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setCachedCount1TestCachedCountShowInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, DISABLED_setCachedCount1TestCachedCountShowInvalidValues, TestSize.Level1)
{
    Opt_Int32 initValueCount;
    Opt_Boolean initValueShow;

    // Initial setup
    initValueCount = ArkValue<Opt_Int32>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueShow = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueCount, &initValueShow](const std::string& input, const Opt_Boolean& value) {
        Opt_Int32 inputValueCount = initValueCount;
        Opt_Boolean inputValueShow = initValueShow;

        modifier_->setCachedCount1(node_, &inputValueCount, &inputValueShow);
        inputValueShow = value;
        modifier_->setCachedCount1(node_, &inputValueCount, &inputValueShow);
        auto jsonValue = GetJsonValue(node_);
        auto resultCachedCount = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CACHED_COUNT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCachedCount, ATTRIBUTE_CACHED_COUNT_I_SHOW_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CACHED_COUNT_I_SHOW_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCachedCount1, attribute: cachedCount.show";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}
} // namespace OHOS::Ace::NG
