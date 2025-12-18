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
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_event_hub.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_REFRESH_OFFSET_NAME = "refreshOffset";
    const auto ATTRIBUTE_REFRESH_OFFSET_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_PULL_TO_REFRESH_NAME = "pullToRefresh";
    const auto ATTRIBUTE_PULL_TO_REFRESH_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_PULL_DOWN_RATIO_RATIO_NAME = "pullDownRatio";
    const auto ATTRIBUTE_PULL_DOWN_RATIO_RATIO_DEFAULT_VALUE = "";
} // namespace

class RefreshModifierTest : public ModifierTestBase<
    GENERATED_ArkUIRefreshModifier,
    &GENERATED_ArkUINodeModifiers::getRefreshModifier,
    GENERATED_ARKUI_REFRESH
> {
};

typedef std::pair<int32_t, Ark_RefreshStatus> StateChangeTest;
const std::vector<StateChangeTest> STATE_CHANGE_EVENT_TEST_PLAN = {
    { 0, ARK_REFRESH_STATUS_INACTIVE },
    { 1, ARK_REFRESH_STATUS_DRAG },
    { 2, ARK_REFRESH_STATUS_OVER_DRAG },
    { 3, ARK_REFRESH_STATUS_REFRESH },
    { 4, ARK_REFRESH_STATUS_DONE },
};

/*
 * @tc.name: setOnStateChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setOnStateChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnStateChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<Ark_RefreshStatus> expected = std::nullopt;
    auto onStateChange = [](const Ark_Int32 resourceId, Ark_RefreshStatus parameter) {
        expected = parameter;
    };
    Callback_RefreshStatus_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onStateChange
    };
    auto optFunc = Converter::ArkValue<Opt_Callback_RefreshStatus_Void>(func);
    modifier_->setOnStateChange(node_, &optFunc);

    for (const auto& testValue : STATE_CHANGE_EVENT_TEST_PLAN) {
        eventHub->FireOnStateChange(testValue.first);

        EXPECT_TRUE(expected.has_value());
        EXPECT_EQ(expected, testValue.second);
    };
}

/*
 * @tc.name: setOnRefreshingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setOnRefreshingTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnRefreshing, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<bool> expected = std::nullopt;
    auto onRefreshing = [](const Ark_Int32 resourceId) {
        expected = true;
    };
    Callback_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onRefreshing
    };
    auto optFunc = Converter::ArkValue<Opt_Callback_Void>(func);
    modifier_->setOnRefreshing(node_, &optFunc);

    eventHub->FireOnRefreshing();

    EXPECT_TRUE(expected.has_value());
}

/*
 * @tc.name: setRefreshOffsetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setRefreshOffsetTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REFRESH_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_REFRESH_OFFSET_DEFAULT_VALUE);
}

// Valid values for attribute 'refreshOffset' of method 'refreshOffset'
static std::vector<std::tuple<std::string, Ark_Float64, std::string>> refreshOffsetRefreshOffsetValidValues = {
    { "-1", Converter::ArkValue<Ark_Float64>(-1), "-1.00vp" },
    { "0", Converter::ArkValue<Ark_Float64>(0), "0.00vp" },
    { "1", Converter::ArkValue<Ark_Float64>(1), "1.00vp" },
    { "10", Converter::ArkValue<Ark_Float64>(10), "10.00vp" },
    { "50", Converter::ArkValue<Ark_Float64>(50), "50.00vp" },
};

/*
 * @tc.name: setRefreshOffsetTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setRefreshOffsetTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Float64 inputValueRefreshOffset;
    Ark_Float64 initValueRefreshOffset;

    // Initial setup
    initValueRefreshOffset = std::get<1>(refreshOffsetRefreshOffsetValidValues[0]);

    // Verifying attribute's  values
    inputValueRefreshOffset = initValueRefreshOffset;
    for (auto&& value: refreshOffsetRefreshOffsetValidValues) {
        inputValueRefreshOffset = std::get<1>(value);
        auto optInputValueRefreshOffset = Converter::ArkValue<Opt_Float64>(inputValueRefreshOffset);
        modifier_->setRefreshOffset(node_, &optInputValueRefreshOffset);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_REFRESH_OFFSET_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setPullToRefreshTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setPullToRefreshTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PULL_TO_REFRESH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PULL_TO_REFRESH_DEFAULT_VALUE);
}

// Valid values for attribute 'pullToRefresh' of method 'pullToRefresh'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> pullToRefreshPullToRefreshValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setPullToRefreshTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setPullToRefreshTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValuePullToRefresh;
    Ark_Boolean initValuePullToRefresh;

    // Initial setup
    initValuePullToRefresh = std::get<1>(pullToRefreshPullToRefreshValidValues[0]);

    // Verifying attribute's  values
    inputValuePullToRefresh = initValuePullToRefresh;
    for (auto&& value: pullToRefreshPullToRefreshValidValues) {
        inputValuePullToRefresh = std::get<1>(value);
        auto optInputValuePullToRefresh = Converter::ArkValue<Opt_Boolean>(inputValuePullToRefresh);
        modifier_->setPullToRefresh(node_, &optInputValuePullToRefresh);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PULL_TO_REFRESH_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

const std::vector<float> OFFSET_CHANGE_EVENT_TEST_PLAN = { 1.f, 3.f, 10.f, 20.f, 100.f };

/*
 * @tc.name: setOnOffsetChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setOnOffsetChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnOffsetChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<float> expected = std::nullopt;
    auto onOffsetChange = [](const Ark_Int32 resourceId, Ark_Float64 parameter) {
        expected = Converter::Convert<float>(parameter);
    };
    Callback_F64_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onOffsetChange
    };
    auto optFunc = Converter::ArkValue<Opt_arkui_component_common_Callback_F64_Void>(func);
    modifier_->setOnOffsetChange(node_, &optFunc);

    for (const auto& testValue : OFFSET_CHANGE_EVENT_TEST_PLAN) {
        eventHub->FireOnOffsetChange(testValue);

        EXPECT_TRUE(expected.has_value());
        EXPECT_EQ(expected, testValue);
    };
}

/*
 * @tc.name: setPullDownRatioTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setPullDownRatioTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_DEFAULT_VALUE);
}

// Valid values for attribute 'pullDownRatioRatio' of method 'pullDownRatio'
static std::vector<std::tuple<std::string, Opt_Float64, double>> pullDownRatioPullDownRatioRatioValidValues = {
    { "0", Converter::ArkValue<Opt_Float64>(0), 0 },
    { "0.5", Converter::ArkValue<Opt_Float64>(0.5f), 0.5 },
    { "1", Converter::ArkValue<Opt_Float64>(1), 1 },
    { "-20", Converter::ArkValue<Opt_Float64>(-20), 0 },
    { "12.4", Converter::ArkValue<Opt_Float64>(12.4f), 1 },
    { "22.5", Converter::ArkValue<Opt_Float64>(22.5f), 1 },
};

/*
 * @tc.name: setPullDownRatioTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setPullDownRatioTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    double result;
    double expected;
    Opt_Float64 initValuePullDownRatioRatio;
    Opt_Float64 inputValuePullDownRatioRatio;

    // Initial setup
    initValuePullDownRatioRatio = std::get<1>(pullDownRatioPullDownRatioRatioValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: pullDownRatioPullDownRatioRatioValidValues) {
        inputValuePullDownRatioRatio = std::get<1>(value);
        modifier_->setPullDownRatio(node_, &inputValuePullDownRatioRatio);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<double>(jsonValue, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_NAME);
        expected = std::get<2>(value);
        EXPECT_FLOAT_EQ(result, expected);
    }

    // Verifying Ark_Empty value
    inputValuePullDownRatioRatio = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    modifier_->setPullDownRatio(node_, &inputValuePullDownRatioRatio);
    jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PULL_DOWN_RATIO_RATIO_DEFAULT_VALUE);
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventRefreshingImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RefreshModifierTest, setOnChangeEventRefreshingImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        bool value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Boolean parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::Convert<bool>(parameter)
        };
    };

    Callback_Boolean_Void arkCallback = Converter::ArkValue<Callback_Boolean_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_refreshing(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent("true");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, true);
    eventHub->FireChangeEvent("false");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
}
#endif
} // namespace OHOS::Ace::NG
