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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;

const auto CASHED_COUNT_ATTRIBUTE_NAME = "cachedCount";
const auto CASHED_COUNT_ATTRIBUTE_DEFAULT_VALUE = "1"

typedef std::tuple<Ark_Number, std::string> ArkNumberTestStep;
static const std::vector<ArkNumberTestStep> CASHED_COUNT_TEST_PLAN = {
    { ArkValue<Ark_Number>(10), "10"},
    { ArkValue<Ark_Number>(-10), "1"},
    { ArkValue<Ark_Number>(12.5), "12"},
    { ArkValue<Ark_Number>(-5.5), "1"},
    { ArkValue<Ark_Number>(832), "832"},
    { ArkValue<Ark_Number>(1.0f), "1"}
};

namespace Converter {
inline void AssignArkValue(Ark_OnScrollFrameBeginHandlerResult& dst, const ScrollFrameResult& src,
    ConvContext *ctx)
{
    dst.offsetRemain = Converter::ArkValue<Ark_Number>(src.offset);
}
} // Converter

namespace {
    const float TEST_OFFSET = 10.0f;
}

class WaterFlowModifierTest : public ModifierTestBase<GENERATED_ArkUIWaterFlowModifier,
      &GENERATED_ArkUINodeModifiers::getWaterFlowModifier, GENERATED_ARKUI_WATER_FLOW> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

HWTEST_F(WaterFlowModifierTest, DISABLED_setOnScrollIndexTestCachedCountValidValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    ASSERT_NE(eventHub, nullptr);

    // Define a structure to check events
    struct CheckEvent {
        int32_t nodeId;
        int32_t firstIndex;
        int32_t lastIndex;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    // Create an event handler for `onScrollIndex`
    auto onScrollIndex = [](Ark_Int32 nodeId, const Ark_Number first, const Ark_Number last) {
        checkEvent = {
            .nodeId = nodeId,
            .firstIndex = Converter::Convert<int32_t>(first),
            .lastIndex = Converter::Convert<int32_t>(last),
        };
    };

    // Initialize the Callback_Number_Number_Void structure
    Callback_Number_Number_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onScrollIndex
    };

    // Set the callback for scroll index change
    auto optCallback = Converter::ArkValue<Opt_Callback_Number_Number_Void>(callBackValue);
    modifier_->setOnScrollIndex(node_, &optCallback);

    // Check that the event has not been triggered yet
    EXPECT_FALSE(checkEvent.has_value());

    // Trigger the scroll index change event with valid values
    auto onScrollIndx = eventHub->GetOnScrollIndex();
    onScrollIndx(10, 20);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->firstIndex, 10);
    EXPECT_EQ(checkEvent->lastIndex, 20);

    // Reset the state for the next test
    checkEvent.reset();

    // Trigger another scroll index change event with different values
    onScrollIndx(15, 25);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->firstIndex, 15);
    EXPECT_EQ(checkEvent->lastIndex, 25);

    // Reset the state for the next test
    checkEvent.reset();

    // Trigger event with zero values to test edge cases
    onScrollIndx = eventHub->GetOnScrollIndex();
    onScrollIndx(0, 0);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->firstIndex, 0);
    EXPECT_EQ(checkEvent->lastIndex, 0);
}

/*
 * @tc.name: setOnScrollFrameBeginTest
 * @tc.desc: test function of setOnScrollFrameBegin
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setOnScrollFrameBeginTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(modifier_->setOnScrollFrameBegin, nullptr);
    static const Ark_Int32 expectedResId = 123;
    auto onScrollFrameBegin = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_Number offset,
                                  Ark_ScrollState state, const Callback_OnScrollFrameBeginHandlerResult_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<float>(offset), TEST_OFFSET);
        ScrollFrameResult result;
        result.offset = Converter::Convert<Dimension>(offset);
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_OnScrollFrameBeginHandlerResult>(result));
    };
    auto arkFunc = Converter::ArkValue<OnScrollFrameBeginCallback>(nullptr, onScrollFrameBegin, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_OnScrollFrameBeginCallback>(arkFunc);
    modifier_->setOnScrollFrameBegin(node_, &optCallback);

    Dimension dimension(TEST_OFFSET);
    ScrollState state = ScrollState::SCROLL;
    ScrollFrameResult result = eventHub->GetOnScrollFrameBegin()(dimension, state);
    EXPECT_EQ(result.offset.ConvertToPx(), dimension.ConvertToPx());
}

/*
 * @tc.name: setCashedCountTest
 * @tc.desc: test function of SetCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setCashedCountTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(modifier_->setCashedCount, nullptr);
    auto checkval = GetAttrValue<std::string>(node_, CASHED_COUNT_ATTRIBUTE_NAME);
    EXPECT_EQ(checkVal, CASHED_COUNT_ATTRIBUTE_DEFAULT_VALUE);
    for (const auto& [value, expectVal] : CASHED_COUNT_TEST_PLAN) {
        auto optValue = Converter::ArkValue<Opt_Number>(value);
        modifier_->setCashedCount(node_, &optValue);
        checkVal = GetAttrValue<std::string>(node_, CASHED_COUNT_ATTRIBUTE_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}
} // namespace OHOS::Ace::NG
