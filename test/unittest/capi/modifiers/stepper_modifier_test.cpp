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
    const auto ATTRIBUTE_STEPPER_INDEX_NAME = "index";
    const auto ATTRIBUTE_STEPPER_INDEX_DEFAULT_VALUE = "0";
} // namespace

class StepperModifierTest : public ModifierTestBase<GENERATED_ArkUIStepperModifier,
    &GENERATED_ArkUINodeModifiers::getStepperModifier, GENERATED_ARKUI_STEPPER> {
};

/*
 * @tc.name: setStepperOptionsTestIndexDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperModifierTest, setStepperOptionsTestIndexDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEPPER_INDEX_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEPPER_INDEX_DEFAULT_VALUE);
}

static std::vector<std::tuple<std::string, Opt_Number, std::string>> optionsIndexValidValues = {
    {"0", Converter::ArkValue<Opt_Number>(0), "0"},
    {"11.1", Converter::ArkValue<Opt_Number>(11.1), "11"},
    {"77.7", Converter::ArkValue<Opt_Number>(77.7), "77"},
    {"99", Converter::ArkValue<Opt_Number>(99), "99"},
};

/*
 * @tc.name: setStepperOptionsTestIndexValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperModifierTest, setStepperOptionsTestIndexValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Literal_Number_index realInputValue = {.tag = ARK_TAG_OBJECT, .value = {.index = {}}};
    Opt_Number& inputValueStatus = realInputValue.value.index;
    Opt_Number initValueStatus;

    // Initial setup
    initValueStatus = std::get<1>(optionsIndexValidValues[0]);

    // Verifying attribute's values
    inputValueStatus = initValueStatus;
    for (auto&& value: optionsIndexValidValues) {
        inputValueStatus = std::get<1>(value);
        modifier_-> setStepperOptions(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEPPER_INDEX_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

static std::vector<std::tuple<std::string, Opt_Number>> optionsIndexInvalidValues = {
    {"-1", Converter::ArkValue<Opt_Number>(-1)},
    {"", Converter::ArkValue<Opt_Number>()},
};

/*
 * @tc.name: setStepperOptionsTestIndexInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperModifierTest, setStepperOptionsTestIndexInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Literal_Number_index realInputValue = {.tag = ARK_TAG_OBJECT, .value = {.index = {}}};
    Opt_Number& inputValueStatus = realInputValue.value.index;
    Opt_Number initValueStatus;

    // Initial setup
    initValueStatus = std::get<1>(optionsIndexValidValues[0]);

    // Verifying attribute's values
    inputValueStatus = initValueStatus;
    for (auto&& value: optionsIndexInvalidValues) {
        inputValueStatus = std::get<1>(value);
        modifier_-> setStepperOptions(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEPPER_INDEX_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_STEPPER_INDEX_DEFAULT_VALUE) << "Passed value is: " << std::get<0>(value);
    }

    realInputValue = Converter::ArkValue<Opt_Literal_Number_index>();
    modifier_-> setStepperOptions(node_, &realInputValue);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STEPPER_INDEX_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STEPPER_INDEX_DEFAULT_VALUE) << "Passed value is: optional";
}
} // namespace OHOS::Ace::NG
