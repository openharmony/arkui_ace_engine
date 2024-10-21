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
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
constexpr static int32_t PLATFORM_VERSION_12 = 12;
namespace  {
    const auto ATTRIBUTE_MODE_NAME = "mode";
    const auto ATTRIBUTE_MODE_DEFAULT_VALUE = "NavDestinationMode::STANDARD";
    const auto ATTRIBUTE_HIDE_TITLE_BAR_NAME = "hideTitleBar";
    const auto ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE = "false";

    struct EventsTracker {
        static inline GENERATED_ArkUINavDestinationEventsReceiver eventsReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getNavDestinationEventsReceiver = [] () -> const GENERATED_ArkUINavDestinationEventsReceiver* {
                return &eventsReceiver;
            }
        };
    }; // EventsTracker
} // namespace

class NavDestinationModifierTest : public ModifierTestBase<GENERATED_ArkUINavDestinationModifier,
    &GENERATED_ArkUINodeModifiers::getNavDestinationModifier, GENERATED_ARKUI_NAV_DESTINATION> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(PLATFORM_VERSION_12);
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: setModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MODE_DEFAULT_VALUE);
}

// Valid values for attribute 'mode' of method 'mode'
static std::vector<std::tuple<std::string, enum Ark_NavDestinationMode, std::string>> modeModeValidValues = {
    {"ARK_NAV_DESTINATION_MODE_STANDARD",
     Converter::ArkValue<enum Ark_NavDestinationMode>(ARK_NAV_DESTINATION_MODE_STANDARD),
     "NavDestinationMode::STANDARD"},
    {"ARK_NAV_DESTINATION_MODE_DIALOG",
     Converter::ArkValue<enum Ark_NavDestinationMode>(ARK_NAV_DESTINATION_MODE_DIALOG),
     "NavDestinationMode::DIALOG"},
};

/*
 * @tc.name: setModeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setModeTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_NavDestinationMode inputValueMode;
    Ark_NavDestinationMode initValueMode;

    // Initial setup
    initValueMode = std::get<1>(modeModeValidValues[0]);

    // Verifying attribute's  values
    inputValueMode = initValueMode;
    for (auto&& value: modeModeValidValues) {
        inputValueMode = std::get<1>(value);
        modifier_->setMode(node_, inputValueMode);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MODE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setHideTitleBar0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setHideTitleBar0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE);
}

//Valid values for attribute 'hideTitleBar' of method 'hideTitleBar'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> hideTitleBarHideTitleBarValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setHideTitleBar0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setHideTitleBar0TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueHideTitleBar;
    Ark_Boolean initValueHideTitleBar;
    // Initial setup
    initValueHideTitleBar = std::get<1>(hideTitleBarHideTitleBarValidValues[0]);

    // Verifying attribute's  values
    inputValueHideTitleBar = initValueHideTitleBar;
    for (auto&& value: hideTitleBarHideTitleBarValidValues) {
        inputValueHideTitleBar = std::get<1>(value);
        modifier_->setHideTitleBar0(node_, inputValueHideTitleBar);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOnShownTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnShownTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::NavDestinationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::eventsReceiver.onShown = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
        };
    };
    modifier_->setOnShown(node_, func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnShownEvent("", "");
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnHiddenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnHiddenTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::NavDestinationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::eventsReceiver.onHidden = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
        };
    };
    modifier_->setOnHidden(node_, func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnHiddenEvent("");
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnWillAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnWillAppearTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::NavDestinationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::eventsReceiver.onWillAppear = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
        };
    };
    modifier_->setOnWillAppear(node_, func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnWillAppear();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnWillDisappearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnWillDisappearTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::NavDestinationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::eventsReceiver.onWillDisappear = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
        };
    };
    modifier_->setOnWillDisappear(node_, func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnWillDisAppear();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnWillShowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnWillShowTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::NavDestinationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::eventsReceiver.onWillShow = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
        };
    };
    modifier_->setOnWillShow(node_, func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnWillShow();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnWillHideTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnWillHideTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::NavDestinationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::eventsReceiver.onWillHide = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
        };
    };
    modifier_->setOnWillHide(node_, func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnWillHide();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setOnBackPressedTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnBackPressedTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::NavDestinationEventHub>();

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::eventsReceiver.onBackPressed = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
        };
    };
    modifier_->setOnBackPressed(node_, func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnBackPressedEvent();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}
} // namespace OHOS::Ace::NG
