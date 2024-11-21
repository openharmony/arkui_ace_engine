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
#include "core/interfaces/arkoala/implementation/text_clock_controller_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/text_clock/text_clock_event_hub.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
struct EventsTracker {
    static inline GENERATED_ArkUITextClockEventsReceiver eventsReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl {
        .getTextClockEventsReceiver = []() -> const GENERATED_ArkUITextClockEventsReceiver* {
            return &eventsReceiver;
        }
    };
}; // EventsTracker

    const auto ATTRIBUTE_TIME_ZONE_OFFSET_NAME = "timeZoneOffset";
    const auto ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE = "0.000000";
} // namespace

class TextClockModifierTest : public ModifierTestBase<GENERATED_ArkUITextClockModifier,
                                &GENERATED_ArkUINodeModifiers::getTextClockModifier, GENERATED_ARKUI_TEXT_CLOCK> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextTheme>();

        // setup the test event handler
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};


/*
 * @tc.name: setTextClockOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextClockOptionsTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextClockOptions, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setTextClockOptions(node_, nullptr);
    auto controllerUndef = Converter::ArkValue<Opt_TextClockOptions>();
    modifier_->setTextClockOptions(node_, &controllerUndef);

    bool checkInvokeStart = false;
    bool checkInvokeStop = false;
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto internalController = TextClockModelNG::InitTextController(frameNode);
    ASSERT_NE(internalController, nullptr);
    internalController->OnStart([&checkInvokeStart]() {
        checkInvokeStart = true;
    });
    internalController->OnStop([&checkInvokeStop]() {
        checkInvokeStop = true;
    });
    

    TextClockControllerPeer peer;
    Opt_TextClockController controller = { .tag = ARK_TAG_OBJECT, .value.ptr = &peer };
    ASSERT_NE(controller.value.ptr, nullptr);
    auto timeZoneOffset = Converter::ArkValue<Opt_Number>(0);
    Opt_TextClockOptions realInputValue = {.tag = ARK_TAG_OBJECT,
        .value = {
            .timeZoneOffset = timeZoneOffset,
            .controller = controller}};
    modifier_->setTextClockOptions(node_, &realInputValue);

    ASSERT_NE(peer.controller, nullptr);

    // check initial state of invoke start
    EXPECT_FALSE(checkInvokeStart);
    peer.controller->Start();
    EXPECT_TRUE(checkInvokeStart);

    // check initial state of invoke stop
    EXPECT_FALSE(checkInvokeStop);
    peer.controller->Stop();
    EXPECT_TRUE(checkInvokeStop);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'options.timeZoneOffset'";
}

// Valid values for attribute 'options' of method 'setTextClockOptions'
static std::vector<std::tuple<std::string, Opt_TextClockOptions, std::string>> setTextClockOptionsOptionsValidValues = {
    {
        "12.000000",
        Converter::ArkValue<Opt_TextClockOptions>(
            Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Number>(12)}),
        "12.000000"
    }, {
        "-14.000000",
        Converter::ArkValue<Opt_TextClockOptions>(
            Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Number>(-14)}),
        "-14.000000"
    }, {
        "9.500000", Converter::ArkValue<Opt_TextClockOptions>(
            Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Number>(9.5)}),
        "9.500000"
    }, {
        "-5.750000", Converter::ArkValue<Opt_TextClockOptions>(
            Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Number>(-5.75)}),
        "-5.750000"
    },
};

/*
 * @tc.name: setTextClockOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextClockOptionsTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Opt_TextClockOptions inputValueOptions = {.tag = ARK_TAG_OBJECT, .value = {}};

    // Verifying attribute's  values
    for (auto& [print, input, expectedStr]: setTextClockOptionsOptionsValidValues) {
        inputValueOptions = input;
        modifier_->setTextClockOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << print;
    }
}

// Invalid values for attribute 'options' of method 'setTextClockOptions'
static std::vector<std::tuple<std::string, Opt_TextClockOptions>> setTextClockOptionsOptionsInvalidValues = {
    {"Ark_Empty()", Converter::ArkValue<Opt_TextClockOptions>(Ark_Empty())},
    {"20.000000", Converter::ArkValue<Opt_TextClockOptions>(
        Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Number>(20)})},
    {"-20.000000", Converter::ArkValue<Opt_TextClockOptions>(
        Ark_TextClockOptions{.timeZoneOffset = Converter::ArkValue<Opt_Number>(-20)})},
};

/*
 * @tc.name: setTextClockOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setTextClockOptionsTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Opt_TextClockOptions realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    Ark_TextClockOptions& inputValueOptions = realInputValue.value;
    Ark_TextClockOptions initValueOptions;

    // Verifying attribute's  values
    for (auto&& value: setTextClockOptionsOptionsInvalidValues) {
        inputValueOptions = initValueOptions;
        modifier_->setTextClockOptions(node_, &realInputValue);
        inputValueOptions = std::get<1>(value).value;
        modifier_->setTextClockOptions(node_, &realInputValue);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TIME_ZONE_OFFSET_NAME);
        expectedStr = ATTRIBUTE_TIME_ZONE_OFFSET_DEFAULT_VALUE;
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setOnDateChange
 * @tc.desc: Check the functionality of DatePickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextClockModifierTest, setOnDateChange, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnDateChange, nullptr);
    Callback_Number_Void func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextClockEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        float index;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::eventsReceiver.onDateChange = [](Ark_Int32 nodeId, const Ark_Number index)
    {
        checkEvent = {
            .nodeId = nodeId,
            .index = Converter::Convert<float>(index),
        };
    };

    modifier_->setOnDateChange(node_, &func);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireChangeEvent("55.5");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 55.5);
    eventHub->FireChangeEvent("0.0");
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->index, 0.0);
}

} // namespace OHOS::Ace::NG
