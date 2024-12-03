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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_MODE_NAME = "mode";
    const auto ATTRIBUTE_MODE_DEFAULT_VALUE = "NavDestinationMode::STANDARD";
    const auto ATTRIBUTE_HIDE_TITLE_BAR_NAME = "hideTitleBar";
    const auto ATTRIBUTE_HIDE_TITLE_BAR_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_IS_ANIMATED_TITLE_BAR_NAME = "isAnimatedTitleBar";
    const auto ATTRIBUTE_IS_ANIMATED_TITLE_BAR_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_RECOVERABLE_RECOVERABLE_NAME = "recoverable";
    const auto ATTRIBUTE_RECOVERABLE_RECOVERABLE_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_NAME = "ignoreLayoutSafeAreaTypes";
    const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_DEFAULT_VALUE = "SAFE_AREA_TYPE_NONE";
    const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_NAME = "ignoreLayoutSafeAreaEdges";
    const auto ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_DEFAULT_VALUE = "SAFE_AREA_EDGE_NONE";

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

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_ANIMATED_TITLE_BAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IS_ANIMATED_TITLE_BAR_DEFAULT_VALUE);
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

//Valid values for attribute 'animated' of method 'hideTitleBar'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> animatedHideTitleBarValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setHideTitleBar1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setHideTitleBar1TestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueHideTitleBar;
    Ark_Boolean initValueHideTitleBar;
    Ark_Boolean inputValueAnimated;
    Ark_Boolean initValueAnimated;
    // Initial setup
    initValueHideTitleBar = std::get<1>(hideTitleBarHideTitleBarValidValues[0]);
    initValueAnimated = std::get<1>(animatedHideTitleBarValidValues[0]);

    // Verifying attribute's  values
    inputValueHideTitleBar = initValueHideTitleBar;
    inputValueAnimated = initValueAnimated;
    for (auto&& value: hideTitleBarHideTitleBarValidValues) {
        inputValueHideTitleBar = std::get<1>(value);
        for (auto&& animated: animatedHideTitleBarValidValues) {
            inputValueAnimated = std::get<1>(animated);
            modifier_->setHideTitleBar1(node_, inputValueHideTitleBar, inputValueAnimated);
            jsonValue = GetJsonValue(node_);
            resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HIDE_TITLE_BAR_NAME);
            expectedStr = std::get<2>(value);
            EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
            resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_ANIMATED_TITLE_BAR_NAME);
            expectedStr = std::get<2>(animated);
            EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(animated);
        }
    }
}

/*
 * @tc.name: setOnShownTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setOnShownTest, TestSize.Level1)
{
    Callback_Void func{};
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
    modifier_->setOnShown(node_, &func);
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
    Callback_Void func{};
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
    modifier_->setOnHidden(node_, &func);
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
    Callback_Void func{};
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
    modifier_->setOnWillAppear(node_, &func);
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
    Callback_Void func{};
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
    modifier_->setOnWillDisappear(node_, &func);
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
    Callback_Void func{};
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
    modifier_->setOnWillShow(node_, &func);
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
    Callback_Void func{};
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
    modifier_->setOnWillHide(node_, &func);
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
    Callback_Boolean func{};
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
    modifier_->setOnBackPressed(node_, &func);
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnBackPressedEvent();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setRecoverableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setRecoverableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_RECOVERABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RECOVERABLE_RECOVERABLE_DEFAULT_VALUE);
}

//Valid values for attribute 'recoverableRecoverable' of method 'recoverable'
static std::vector<std::tuple<std::string, Opt_Boolean, std::string>> recoverableRecoverableRecoverableValidValues = {
    {"true", Converter::ArkValue<Opt_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Opt_Boolean>(false), "false"},
};

/*
 * @tc.name: setRecoverableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
#ifdef WRONG_OPT
HWTEST_F(NavDestinationModifierTest, setRecoverableTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    Opt_Boolean initValueRecoverableRecoverable;
    Opt_Boolean& inputValueRecoverableRecoverable = realInputValue;
    // Initial setup
    initValueRecoverableRecoverable = std::get<1>(recoverableRecoverableRecoverableValidValues[0]);

    // Verifying attribute's  values
    inputValueRecoverableRecoverable = initValueRecoverableRecoverable;
    for (auto&& value: recoverableRecoverableRecoverableValidValues) {
        inputValueRecoverableRecoverable = std::get<1>(value);
        modifier_->setRecoverable(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_RECOVERABLE_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'recoverableRecoverable' of method 'recoverable'
static std::vector<std::tuple<std::string, Opt_Boolean>> recoverableRecoverableRecoverableInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_Boolean>(Ark_Empty())},
};

/*
 * @tc.name: setRecoverableTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setRecoverableTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_Boolean realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    Opt_Boolean initValueRecoverableRecoverable;
    Opt_Boolean& inputValueRecoverableRecoverable = realInputValue;
    // Initial setup
    initValueRecoverableRecoverable = std::get<1>(recoverableRecoverableRecoverableValidValues[0]);

    // Verifying attribute's  values
    for (auto&& value: recoverableRecoverableRecoverableInvalidValues) {
        inputValueRecoverableRecoverable = initValueRecoverableRecoverable;
        modifier_->setRecoverable(node_, &realInputValue);
        inputValueRecoverableRecoverable = std::get<1>(value);
        modifier_->setRecoverable(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RECOVERABLE_RECOVERABLE_NAME);
        expectedStr = ATTRIBUTE_RECOVERABLE_RECOVERABLE_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
#endif

/*
 * @tc.name: setIgnoreLayoutSafeAreaTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setIgnoreLayoutSafeAreaTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_DEFAULT_VALUE);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_DEFAULT_VALUE);
}

/*
 * @tc.name: setIgnoreLayoutSafeAreaTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModifierTest, setIgnoreLayoutSafeAreaTestValidValues, TestSize.Level1)
{
    std::string resultStr;
    std::string expectedStr;
    std::unique_ptr<JsonValue> jsonValue;
    Opt_Array_LayoutSafeAreaType realInputValue0 = {.tag = ARK_TAG_OBJECT, .value = {}};
    Opt_Array_LayoutSafeAreaEdge realInputValue1 = {.tag = ARK_TAG_OBJECT, .value = {}};

    Ark_LayoutSafeAreaType typeVal = ARK_LAYOUT_SAFE_AREA_TYPE_SYSTEM;
    Ark_LayoutSafeAreaEdge edgeVal = ARK_LAYOUT_SAFE_AREA_EDGE_TOP;

    Array_LayoutSafeAreaType initValueType = {.array = &typeVal, .length = 1};
    Array_LayoutSafeAreaEdge initValueEdge = {.array = &edgeVal, .length = 1};

    realInputValue0.value = initValueType;
    realInputValue1.value = initValueEdge;

    modifier_->setIgnoreLayoutSafeArea(node_, &realInputValue0, &realInputValue1);
    jsonValue = GetJsonValue(node_);

    expectedStr = "SAFE_AREA_TYPE_SYSTEM";
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_TYPES_NAME);
    EXPECT_EQ(resultStr, expectedStr);

    expectedStr = "SAFE_AREA_EDGE_TOP";
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IGNORE_LAYOUT_SAFE_AREA_EDGES_NAME);
    EXPECT_EQ(resultStr, expectedStr);
}
} // namespace OHOS::Ace::NG
