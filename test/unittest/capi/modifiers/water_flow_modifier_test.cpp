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
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
    struct EventsTracker {
        static inline GENERATED_ArkUIWaterFlowEventsReceiver waterFlowEventReceiver {};
        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getWaterFlowEventsReceiver = [] () -> const GENERATED_ArkUIWaterFlowEventsReceiver* {
                return &waterFlowEventReceiver;
            }
        };
    }; // EventsTracker
}

class WaterFlowModifierTest : public ModifierTestBase<GENERATED_ArkUIWaterFlowModifier,
      &GENERATED_ArkUINodeModifiers::getWaterFlowModifier, GENERATED_ARKUI_WATER_FLOW> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: setOnReachStartTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setOnReachStartTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnReachStart, nullptr);
    const int32_t contextId = 123;

    static std::optional<int32_t> checkData;
    auto checkCallback = [](const Ark_Int32 resourceId) { checkData = resourceId; };
    ASSERT_FALSE(checkData.has_value());

    // setup the callback object via C-API
    auto arkCallback = Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    modifier_->setOnReachStart(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onReachStart = eventHub->GetOnReachStart();
    ASSERT_NE(onReachStart, nullptr);
    onReachStart();

    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(checkData.value(), contextId);
}

/*
 * @tc.name: setOnReachEndTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowModifierTest, setOnReachEndTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnReachEnd, nullptr);
    const int32_t contextId = 123;

    static std::optional<int32_t> checkData;
    auto checkCallback = [](const Ark_Int32 resourceId) { checkData = resourceId; };
    ASSERT_FALSE(checkData.has_value());

    // setup the callback object via C-API
    auto arkCallback = Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    modifier_->setOnReachEnd(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onReachEnd = eventHub->GetOnReachEnd();
    onReachEnd();

    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(checkData.value(), contextId);
}


HWTEST_F(WaterFlowModifierTest, setOnScrollIndexTestCachedCountValidValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();

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
    modifier_->setOnScrollIndex(node_, &callBackValue);

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

} // namespace OHOS::Ace::NG
