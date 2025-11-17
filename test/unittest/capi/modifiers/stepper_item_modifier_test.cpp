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
#include "core/components_ng/layout/layout_property.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_PREV_LABEL_NAME = "prevLabel";
    const auto ATTRIBUTE_PREV_LABEL_DEFAULT_VALUE = "Back";
    const auto ATTRIBUTE_NEXT_LABEL_NAME = "nextLabel";
    const auto ATTRIBUTE_NEXT_LABEL_DEFAULT_VALUE = "Next";
    const auto ATTRIBUTE_STATUS_NAME = "status";
    const auto ATTRIBUTE_STATUS_DEFAULT_VALUE = "ItemState.Normal";
} // namespace

class StepperItemModifierTest : public ModifierTestBase<GENERATED_ArkUIStepperItemModifier,
    &GENERATED_ArkUINodeModifiers::getStepperItemModifier, GENERATED_ARKUI_STEPPER_ITEM> {
};


/*
 * @tc.name: setPrevLabelTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperItemModifierTest, DISABLED_setPrevLabelTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PREV_LABEL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PREV_LABEL_DEFAULT_VALUE);
}

// Valid values for attribute 'prevLabel' of method 'prevLabel'
static std::vector<std::tuple<std::string, Opt_String, std::string>> prevLabelPrevLabelValidValues = {
    {"\"\"", Converter::ArkValue<Opt_String>(""), ""},
    {"\"abc\"", Converter::ArkValue<Opt_String>("abc"), "abc"},
};

/*
 * @tc.name: setPrevLabelTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperItemModifierTest, setPrevLabelTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_String inputValuePrevLabel;
    Opt_String initValuePrevLabel;

    // Initial setup
    initValuePrevLabel = std::get<1>(prevLabelPrevLabelValidValues[0]);

    // Verifying attribute's  values
    inputValuePrevLabel = initValuePrevLabel;
    for (auto&& value: prevLabelPrevLabelValidValues) {
        inputValuePrevLabel = std::get<1>(value);
        modifier_->setPrevLabel(node_, &inputValuePrevLabel);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PREV_LABEL_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setNextLabelTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperItemModifierTest, DISABLED_setNextLabelTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NEXT_LABEL_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NEXT_LABEL_DEFAULT_VALUE);
}

// Valid values for attribute 'nextLabel' of method 'nextLabel'
static std::vector<std::tuple<std::string, Opt_String, std::string>> nextLabelNextLabelValidValues = {
    {"\"\"", Converter::ArkValue<Opt_String>(""), ""},
    {"\"abc\"", Converter::ArkValue<Opt_String>("abc"), "abc"},
};

/*
 * @tc.name: setNextLabelTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperItemModifierTest, setNextLabelTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_String inputValueNextLabel;
    Opt_String initValueNextLabel;

    // Initial setup
    initValueNextLabel = std::get<1>(nextLabelNextLabelValidValues[0]);

    // Verifying attribute's  values
    inputValueNextLabel = initValueNextLabel;
    for (auto&& value: nextLabelNextLabelValidValues) {
        inputValueNextLabel = std::get<1>(value);
        modifier_->setNextLabel(node_, &inputValueNextLabel);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NEXT_LABEL_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setStatusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperItemModifierTest, setStatusTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STATUS_DEFAULT_VALUE);
}

static std::vector<std::tuple<std::string, Ark_ItemState, std::string>> statusStatusValidValues = {
    {"ARK_ITEM_STATE_NORMAL", Converter::ArkValue<Ark_ItemState>(ARK_ITEM_STATE_NORMAL), "ItemState.Normal"},
    {"ARK_ITEM_STATE_DISABLED", Converter::ArkValue<Ark_ItemState>(ARK_ITEM_STATE_DISABLED), "ItemState.Disabled"},
    {"ARK_ITEM_STATE_WAITING", Converter::ArkValue<Ark_ItemState>(ARK_ITEM_STATE_WAITING), "ItemState.Waiting"},
    {"ARK_ITEM_STATE_SKIP", Converter::ArkValue<Ark_ItemState>(ARK_ITEM_STATE_SKIP), "ItemState.Skip"},
};

/*
 * @tc.name: setStatusTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperItemModifierTest, setStatusTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_ItemState realInputValue = Converter::ArkValue<Opt_ItemState>(Ark_ItemState{});
    Ark_ItemState& inputValueStatus = realInputValue.value;
    Ark_ItemState initValueStatus;

    // Initial setup
    initValueStatus = std::get<1>(statusStatusValidValues[0]);

    // Verifying attribute's  values
    inputValueStatus = initValueStatus;
    for (auto&& value: statusStatusValidValues) {
        inputValueStatus = std::get<1>(value);
        modifier_->setStatus(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATUS_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'status' of method 'status'
static std::vector<std::tuple<std::string, Ark_ItemState>> statusStatusInvalidValues = {
    {"static_cast<Ark_ItemState>(-1)", Converter::ArkValue<Ark_ItemState>(static_cast<Ark_ItemState>(-1))},
};

/*
 * @tc.name: setStatusTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperItemModifierTest, setStatusTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_ItemState realInputValue = Converter::ArkValue<Opt_ItemState>(Ark_ItemState{});
    Ark_ItemState& inputValueStatus = realInputValue.value;
    Ark_ItemState initValueStatus;

    // Initial setup
    initValueStatus = std::get<1>(statusStatusValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: statusStatusInvalidValues) {
        inputValueStatus = initValueStatus;
        modifier_->setStatus(node_, &realInputValue);
        inputValueStatus = std::get<1>(value);
        modifier_->setStatus(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STATUS_NAME);
        expectedStr = ATTRIBUTE_STATUS_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
} // namespace OHOS::Ace::NG
