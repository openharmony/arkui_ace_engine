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
const auto ATTRIBUTE_RESIZEABLE_NAME = "resizeable";
const auto ATTRIBUTE_RESIZEABLE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_DIVIDER_NAME = "divider";
const auto ATTRIBUTE_DIVIDER_START_MARGIN = "startMargin";
const auto ATTRIBUTE_DIVIDER_START_MARGIN_DEFAULT_VALUE = "";
const auto ATTRIBUTE_DIVIDER_END_MARGIN = "endMargin";
const auto ATTRIBUTE_DIVIDER_END_MARGIN_DEFAULT_VALUE = "";

const auto OPT_LEN_NUM_NEG = Converter::ArkValue<Opt_Dimension>("-1234.00px");
const auto OPT_LEN_NUM_ZERO = Converter::ArkValue<Opt_Dimension>("0.00px");
const auto OPT_LEN_NUM_VALID = Converter::ArkValue<Opt_Dimension>("1234.00px");
const auto OPT_LEN_NUM_MAX = Converter::ArkValue<Opt_Dimension>("2147483648.00px");

constexpr auto EXPECTED_NUM_NEG_PX = "-1234.00px";
constexpr auto EXPECTED_NUM_VILID_PX = "1234.00px";
constexpr auto EXPECTED_NUM_MAX_PX = "2147483648.00px";
constexpr auto EXPECTED_NUM_ZERO_PX = "0.00px";
} // namespace

class ColumnSplitModifierTest : public ModifierTestBase<GENERATED_ArkUIColumnSplitModifier,
    &GENERATED_ArkUINodeModifiers::getColumnSplitModifier, GENERATED_ARKUI_COLUMN_SPLIT> {
    public:
    void checkDividerLengthAttr(std::vector<std::tuple<std::string, Opt_Dimension, std::string>> styleArray,
        std::string attribute)
    {
        std::unique_ptr<JsonValue> jsonValue;
        std::unique_ptr<JsonValue> divJson;
        std::string resultStr;
        Ark_ColumnSplitDividerStyle inputValue;

        for (auto [passed, checkVal, expected]: styleArray) {
            if (attribute == ATTRIBUTE_DIVIDER_START_MARGIN) {
                inputValue.startMargin = checkVal;
            }
            if (attribute == ATTRIBUTE_DIVIDER_END_MARGIN) {
                inputValue.endMargin = checkVal;
            }
            auto divider = Converter::ArkValue<Opt_ColumnSplitDividerStyle>(inputValue);
            modifier_->setDivider(node_, &divider);
            jsonValue = GetJsonValue(node_);
            divJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
            resultStr = GetAttrValue<std::string>(divJson, attribute);
            EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
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
    EXPECT_EQ(resultStr, ATTRIBUTE_RESIZEABLE_DEFAULT_VALUE);
}

// Valid values for attribute 'resizeable' of method 'resizeable'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> resizeableValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setResizeableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setResizeableTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    for (auto [passed, checkVal, expected]: resizeableValidValues) {
        auto checkValue = Converter::ArkValue<Opt_Boolean>(checkVal);
        modifier_->setResizeable(node_, &checkValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RESIZEABLE_NAME);
        EXPECT_EQ(resultStr, expected) << "Passed value is: " << passed;
    }
}

/*
 * @tc.name: setDividerTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setDividerTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> divJson;
    std::string resultStr;
    divJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_DIVIDER_NAME);
    resultStr = GetAttrValue<std::string>(divJson, ATTRIBUTE_DIVIDER_START_MARGIN);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_START_MARGIN_DEFAULT_VALUE);
    resultStr = GetAttrValue<std::string>(divJson, ATTRIBUTE_DIVIDER_END_MARGIN);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIVIDER_END_MARGIN_DEFAULT_VALUE);
}

static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> dividerStartMarginValidValues = {
    {EXPECTED_NUM_NEG_PX, OPT_LEN_NUM_NEG, EXPECTED_NUM_NEG_PX},
    {EXPECTED_NUM_ZERO_PX, OPT_LEN_NUM_ZERO, EXPECTED_NUM_ZERO_PX},
    {EXPECTED_NUM_VILID_PX, OPT_LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
    {EXPECTED_NUM_MAX_PX, OPT_LEN_NUM_MAX, EXPECTED_NUM_MAX_PX},
};

// Valid values for attribute 'endMargin' of method 'setDivider'
static std::vector<std::tuple<std::string, Opt_Dimension, std::string>> dividerEndMarginValidValues = {
    {EXPECTED_NUM_NEG_PX, OPT_LEN_NUM_NEG, EXPECTED_NUM_NEG_PX},
    {EXPECTED_NUM_ZERO_PX, OPT_LEN_NUM_ZERO, EXPECTED_NUM_ZERO_PX},
    {EXPECTED_NUM_VILID_PX, OPT_LEN_NUM_VALID, EXPECTED_NUM_VILID_PX},
    {EXPECTED_NUM_MAX_PX, OPT_LEN_NUM_MAX, EXPECTED_NUM_MAX_PX},
};

/*
 * @tc.name: setDividerTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColumnSplitModifierTest, setDividerTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setResizeable, nullptr);
    checkDividerLengthAttr(dividerStartMarginValidValues, ATTRIBUTE_DIVIDER_START_MARGIN);
    checkDividerLengthAttr(dividerEndMarginValidValues, ATTRIBUTE_DIVIDER_END_MARGIN);
}

} // namespace OHOS::Ace::NG
