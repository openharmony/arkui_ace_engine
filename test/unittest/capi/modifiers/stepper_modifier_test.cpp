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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/stepper/stepper_event_hub.h"
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

/*
 * @tc.name: setOnFinishTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperModifierTest, setOnFinishTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnFinish, nullptr);
    const int32_t contextId = 123;
    const int32_t indexArg = 0;

    static std::optional<int32_t> checkData;
    void (*checkCallback)(const Ark_Int32 resourceId) =
        [](const Ark_Int32 resourceId) { checkData = resourceId; };
    ASSERT_FALSE(checkData.has_value());

    // setup the callback object via C-API
    Callback_Void arkCallback = Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    modifier_->setOnFinish(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireFinishEvent(indexArg);
    // check the invoking result
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(checkData.value(), contextId);
}

/*
 * @tc.name: setOnSkipTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperModifierTest, setOnSkipTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnSkip, nullptr);
    const int32_t contextId = 123;
    const int32_t indexArg = 0;

    static std::optional<int32_t> checkData;
    void (*checkCallback)(const Ark_Int32 resourceId) =
        [](const Ark_Int32 resourceId) { checkData = resourceId; };
    ASSERT_FALSE(checkData.has_value());

    // setup the callback object via C-API
    Callback_Void arkCallback = Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    modifier_->setOnSkip(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireSkipEvent(indexArg);
    // check the invoking result
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(checkData.value(), contextId);
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperModifierTest, setOnChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnChange, nullptr);
    const int32_t contextId = 123;
    const int32_t firstArg = 0;
    const int32_t secondArg = 1;

    static std::optional<std::tuple<int32_t, int32_t, int32_t>> checkData;
    void (*checkCallback)(const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last) =
        [](const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last) {
            checkData = { resourceId, Converter::Convert<int32_t>(first),
                Converter::Convert<int32_t>(last) };
        };
    ASSERT_FALSE(checkData.has_value());

    // setup the callback object via C-API
    auto arkCallback = Converter::ArkValue<Callback_Number_Number_Void>(checkCallback, contextId);
    modifier_->setOnChange(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(firstArg, secondArg);
    // check the invoking result
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(std::get<0>(checkData.value()), contextId);
    EXPECT_EQ(std::get<1>(checkData.value()), firstArg);
    EXPECT_EQ(std::get<2>(checkData.value()), secondArg);
}

/*
 * @tc.name: setOnNextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperModifierTest, setOnNextTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnNext, nullptr);
    const int32_t contextId = 123;
    const int32_t firstArg = 0;
    const int32_t secondArg = 1;

    static std::optional<std::tuple<int32_t, int32_t, int32_t>> checkData;
    void (*checkCallback)(const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last) =
        [](const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last) {
            checkData = { resourceId, Converter::Convert<int32_t>(first),
                Converter::Convert<int32_t>(last) };
        };
    ASSERT_FALSE(checkData.has_value());

    // setup the callback object via C-API
    auto arkCallback = Converter::ArkValue<Callback_Number_Number_Void>(checkCallback, contextId);
    modifier_->setOnNext(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireNextEvent(firstArg, secondArg);
    // check the invoking result
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(std::get<0>(checkData.value()), contextId);
    EXPECT_EQ(std::get<1>(checkData.value()), firstArg);
    EXPECT_EQ(std::get<2>(checkData.value()), secondArg);
}

/*
 * @tc.name: setOnPreviousTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StepperModifierTest, setOnPreviousTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnPrevious, nullptr);
    const int32_t contextId = 123;
    const int32_t firstArg = 0;
    const int32_t secondArg = 1;

    static std::optional<std::tuple<int32_t, int32_t, int32_t>> checkData;
    void (*checkCallback)(const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last) =
        [](const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last) {
            checkData = { resourceId, Converter::Convert<int32_t>(first),
                Converter::Convert<int32_t>(last) };
        };
    ASSERT_FALSE(checkData.has_value());

    // setup the callback object via C-API
    auto arkCallback = Converter::ArkValue<Callback_Number_Number_Void>(checkCallback, contextId);
    modifier_->setOnPrevious(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FirePreviousEvent(firstArg, secondArg);
    // check the invoking result
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(std::get<0>(checkData.value()), contextId);
    EXPECT_EQ(std::get<1>(checkData.value()), firstArg);
    EXPECT_EQ(std::get<2>(checkData.value()), secondArg);
}
} // namespace OHOS::Ace::NG
