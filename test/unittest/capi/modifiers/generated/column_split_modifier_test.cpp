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

#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_DIVIDER_NAME = "divider";
const auto ATTRIBUTE_RESIZEABLE_NAME = "resizeable";
const auto ATTRIBUTE_RESIZEABLE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_DIVIDER_I_START_MARGIN_NAME = "startMargin";
const auto ATTRIBUTE_DIVIDER_I_START_MARGIN_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_DIVIDER_I_END_MARGIN_NAME = "endMargin";
const auto ATTRIBUTE_DIVIDER_I_END_MARGIN_DEFAULT_VALUE = "0.00vp";
} // namespace

class ColumnSplitModifierTest
    : public ModifierTestBase<GENERATED_ArkUIColumnSplitModifier, &GENERATED_ArkUINodeModifiers::getColumnSplitModifier,
          GENERATED_ARKUI_COLUMN_SPLIT> {
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
 * @tc.name: setResizeableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setResizeableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RESIZEABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RESIZEABLE_DEFAULT_VALUE) << "Default value for attribute 'resizeable'";
}

/*
 * @tc.name: setResizeableTestResizeableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setResizeableTestResizeableValidValues, TestSize.Level1)
{
    Ark_Boolean initValueResizeable;

    // Initial setup
    initValueResizeable = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueResizeable](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueResizeable = initValueResizeable;

        inputValueResizeable = value;
        modifier_->setResizeable(node_, inputValueResizeable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RESIZEABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setResizeable, attribute: resizeable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDividerTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, DISABLED_setDividerTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultDivider =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDivider, ATTRIBUTE_DIVIDER_I_START_MARGIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_I_START_MARGIN_DEFAULT_VALUE)
        << "Default value for attribute 'divider..startMargin'";

    resultStr = GetAttrValue<std::string>(resultDivider, ATTRIBUTE_DIVIDER_I_END_MARGIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_I_END_MARGIN_DEFAULT_VALUE)
        << "Default value for attribute 'divider..endMargin'";
}

/*
 * @tc.name: setDividerTestDividerStartMarginValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setDividerTestDividerStartMarginValidValues, TestSize.Level1)
{
    Ark_Union_ColumnSplitDividerStyle_Undefined initValueDivider;

    // Initial setup
    WriteToUnion<Ark_ColumnSplitDividerStyle>(initValueDivider).startMargin =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]));
    WriteToUnion<Ark_ColumnSplitDividerStyle>(initValueDivider).endMargin =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]));

    auto checkValue = [this, &initValueDivider](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_Union_ColumnSplitDividerStyle_Undefined inputValueDivider = initValueDivider;

        WriteToUnion<Ark_ColumnSplitDividerStyle>(inputValueDivider).startMargin = value;
        modifier_->setDivider(node_, &inputValueDivider);
        auto jsonValue = GetJsonValue(node_);
        auto resultDivider = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDivider, ATTRIBUTE_DIVIDER_I_START_MARGIN_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDivider, attribute: divider..startMargin";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setDividerTestDividerStartMarginInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setDividerTestDividerStartMarginInvalidValues, TestSize.Level1)
{
    Ark_Union_ColumnSplitDividerStyle_Undefined initValueDivider;

    // Initial setup
    WriteToUnion<Ark_ColumnSplitDividerStyle>(initValueDivider).startMargin =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]));
    WriteToUnion<Ark_ColumnSplitDividerStyle>(initValueDivider).endMargin =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]));

    auto checkValue = [this, &initValueDivider](const std::string& input, const Opt_Length& value) {
        Ark_Union_ColumnSplitDividerStyle_Undefined inputValueDivider = initValueDivider;

        modifier_->setDivider(node_, &inputValueDivider);
        WriteToUnion<Ark_ColumnSplitDividerStyle>(inputValueDivider).startMargin = value;
        modifier_->setDivider(node_, &inputValueDivider);
        auto jsonValue = GetJsonValue(node_);
        auto resultDivider = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDivider, ATTRIBUTE_DIVIDER_I_START_MARGIN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_I_START_MARGIN_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setDivider, attribute: divider..startMargin";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setDividerTestDividerEndMarginValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setDividerTestDividerEndMarginValidValues, TestSize.Level1)
{
    Ark_Union_ColumnSplitDividerStyle_Undefined initValueDivider;

    // Initial setup
    WriteToUnion<Ark_ColumnSplitDividerStyle>(initValueDivider).startMargin =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]));
    WriteToUnion<Ark_ColumnSplitDividerStyle>(initValueDivider).endMargin =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]));

    auto checkValue = [this, &initValueDivider](
                          const std::string& input, const Opt_Length& value, const std::string& expectedStr) {
        Ark_Union_ColumnSplitDividerStyle_Undefined inputValueDivider = initValueDivider;

        WriteToUnion<Ark_ColumnSplitDividerStyle>(inputValueDivider).endMargin = value;
        modifier_->setDivider(node_, &inputValueDivider);
        auto jsonValue = GetJsonValue(node_);
        auto resultDivider = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDivider, ATTRIBUTE_DIVIDER_I_END_MARGIN_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDivider, attribute: divider..endMargin";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthAnyValidValues) {
        checkValue(input, ArkValue<Opt_Length>(value), expected);
    }
}

/*
 * @tc.name: setDividerTestDividerEndMarginInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setDividerTestDividerEndMarginInvalidValues, TestSize.Level1)
{
    Ark_Union_ColumnSplitDividerStyle_Undefined initValueDivider;

    // Initial setup
    WriteToUnion<Ark_ColumnSplitDividerStyle>(initValueDivider).startMargin =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]));
    WriteToUnion<Ark_ColumnSplitDividerStyle>(initValueDivider).endMargin =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthAnyValidValues[0]));

    auto checkValue = [this, &initValueDivider](const std::string& input, const Opt_Length& value) {
        Ark_Union_ColumnSplitDividerStyle_Undefined inputValueDivider = initValueDivider;

        modifier_->setDivider(node_, &inputValueDivider);
        WriteToUnion<Ark_ColumnSplitDividerStyle>(inputValueDivider).endMargin = value;
        modifier_->setDivider(node_, &inputValueDivider);
        auto jsonValue = GetJsonValue(node_);
        auto resultDivider = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultDivider, ATTRIBUTE_DIVIDER_I_END_MARGIN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_I_END_MARGIN_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setDivider, attribute: divider..endMargin";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}
} // namespace OHOS::Ace::NG
