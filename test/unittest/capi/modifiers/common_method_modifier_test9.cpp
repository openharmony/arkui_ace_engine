/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common_method_modifier_test.h"
#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/implementation/accessiblt_hover_event_peer.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/implementation/touch_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "generated/type_helpers.h"
#include "core/components_ng/event/input_event_hub.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_GROUP_NAME_TEST = "accessibilityGroup";
    const auto ATTRIBUTE_GROUP_DEFAULT_VALUE_TEST = "false";
    const auto ATTRIBUTE_TEXT_NAME_TEST = "accessibilityText";
    const auto ATTRIBUTE_TEXT_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_TEXT_HINT_NAME_TEST = "accessibilityTextHint";
    const auto ATTRIBUTE_TEXT_HINT_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_DESCRIPTION_NAME_TEST = "accessibilityDescription";
    const auto ATTRIBUTE_DESCRIPTION_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_LEVEL_NAME_TEST = "accessibilityLevel";
    const auto ATTRIBUTE_LEVEL_DEFAULT_VALUE_TEST = "auto";
    const auto ATTRIBUTE_CHECKED_NAME_TEST = "accessibilityChecked";
    const auto ATTRIBUTE_CHECKED_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_SELECTED_NAME_TEST = "accessibilitySelected";
    const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE_TEST = "";
}

namespace Converter {
    template<>
    void AssignArkValue(Ark_Resource& dst, const std::string& src, ConvContext *ctx)
    {
        dst.type = Converter::ArkValue<Opt_Number>(static_cast<uint32_t>(ResourceType::STRING));
        dst.bundleName = Converter::ArkValue<Ark_String>(src);
        LOGE("this converter is disabled");
    }
}

namespace GeneratedModifier {
    const GENERATED_ArkUIAccessibilityHoverEventAccessor* GetAccessibilityHoverEventAccessor();
    const GENERATED_ArkUITouchEventAccessor* GetTouchEventAccessor();
    const GENERATED_ArkUIHoverEventAccessor* GetHoverEventAccessor();
}

class CommonMethodModifierTest9 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }

    RefPtr<GestureEventHub> GetGestureEventHub()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            if (auto eventHub = fnode->GetEventHub<NG::EventHub>(); eventHub) {
                return eventHub->GetOrCreateGestureEventHub();
            }
        }
        return nullptr;
    }
};

//////// AccessibilityGroup
/*
 * @tc.name: setAccessibilityGroupTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityGroupTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_GROUP_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_GROUP_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityGroupTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityGroupTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityGroup0, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityGroup0(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_GROUP_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilityText
/*
 * @tc.name: setAccessibilityTextTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityTextTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_TEXT_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_TEXT_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityTextTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityText0TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityText0, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Ark_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityText0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TEXT_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setAccessibilityTextTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityText1TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityText1, nullptr);
    using OneTestStep = std::tuple<Ark_Resource, std::string>;
    std::string inputVal1 {"test string 1"}, inputVal2 {"test string 2"};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Resource>(inputVal1, nullptr), inputVal1},
        {Converter::ArkValue<Ark_Resource>(inputVal2, nullptr), inputVal2},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityText1(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TEXT_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
        // Освобождаем выделенную память
        delete[] inputValue.params.value.array;
    }
}

//////// AccessibilityTextHint
/*
 * @tc.name: setAccessibilityTextHintTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityTextHintTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_TEXT_HINT_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_TEXT_HINT_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityTextHintTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityTextHintTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityTextHint, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Ark_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityTextHint(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TEXT_HINT_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilityDescription
/*
 * @tc.name: setAccessibilityDescriptionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityDescriptionTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_DESCRIPTION_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_DESCRIPTION_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityDescriptionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityDescription0TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityDescription0, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Ark_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityDescription0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_DESCRIPTION_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setAccessibilityDescriptionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityDescription1TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityDescription1, nullptr);
    using OneTestStep = std::tuple<Ark_Resource, std::string>;
    std::string inputVal1 {"test string 1"}, inputVal2 {"test string 2"};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Resource>(inputVal1, nullptr), inputVal1},
        {Converter::ArkValue<Ark_Resource>(inputVal2, nullptr), inputVal2},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityDescription1(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_DESCRIPTION_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilityLevel
/*
 * @tc.name: setAccessibilityLevelTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityLevelTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_LEVEL_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_LEVEL_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityLevelTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityLevelTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityLevel, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Ark_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityLevel(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_LEVEL_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilityChecked
/*
 * @tc.name: setAccessibilityCheckedTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityCheckedTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_CHECKED_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_CHECKED_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityCheckedTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityCheckedTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityChecked, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityChecked(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CHECKED_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilitySelected
/*
 * @tc.name: setAccessibilitySelectedTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilitySelectedTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_SELECTED_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_SELECTED_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilitySelectedTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilitySelectedTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilitySelected, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilitySelected(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_SELECTED_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: SetOnHover
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, SetOnHoverTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    static const std::string expectedType = "onHover";
    static const int expectedResId = 123;

    struct CheckEvent {
        int32_t nodeId;
        bool isHover;
        SourceType deviceType;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onHoverFunc = [](
        Ark_VMContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event
    ) {
        ASSERT_NE(event, nullptr);
        auto peer = event;
        auto hoverEventInfo = peer->GetEventInfo();
        ASSERT_NE(hoverEventInfo, nullptr);
        EXPECT_EQ(hoverEventInfo->GetType(), expectedType);
        GeneratedModifier::GetHoverEventAccessor()->destroyPeer(peer);
        checkEvent = {
            .nodeId = resourceId, .isHover = Converter::Convert<bool>(isHover),
            .deviceType = hoverEventInfo->GetSourceDevice()
        };
    };

    auto callbackValue =
        Converter::ArkValue<Callback_Boolean_HoverEvent_Void>(onHoverFunc, expectedResId);

    auto test = [this, &callbackValue, eventHub, frameNode](bool isHover, SourceType type) {
        checkEvent = std::nullopt;
        modifier_->setOnHover(node_, &callbackValue);
        ASSERT_FALSE(checkEvent.has_value());
        auto inputEventHub = eventHub->GetInputEventHub();
        ASSERT_NE(inputEventHub, nullptr);

        OffsetF offset;
        TouchTestResult result;
        inputEventHub->ProcessMouseTestHit(offset, result);
        for (const auto& resultData : result) {
            auto hoverResult = AceType::DynamicCast<HoverEventTarget>(resultData);
            ASSERT_NE(hoverResult, nullptr);
            MouseEvent me;
            me.sourceType = type;
            hoverResult->HandleHoverEvent(isHover, me);
        }
        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->isHover, isHover);
        EXPECT_EQ(checkEvent->nodeId, expectedResId);
        EXPECT_EQ(checkEvent->deviceType, type);
    };
    test(true, SourceType::MOUSE);
    test(false, SourceType::TOUCH_PAD);
}

/*
 * @tc.name: SetOnAccessibilityHover
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, SetOnAccessibilityHoverTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        bool isHover;
        AccessibilityHoverAction type;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onAccessibilityHoverFunc = [](Ark_VMContext, const Ark_Int32 resourceId,
                          const Ark_Boolean isHover,
                          const Ark_AccessibilityHoverEvent peer) {
        auto info = peer ? peer->GetEventInfo() : nullptr;
        ASSERT_NE(info, nullptr);
        checkEvent = { .nodeId = resourceId, .isHover = isHover, .type = info->GetActionType() };
        GeneratedModifier::GetAccessibilityHoverEventAccessor()->destroyPeer(peer);
    };
    auto callBackValue = Converter::ArkValue<AccessibilityCallback>(onAccessibilityHoverFunc, frameNode->GetId());

    auto test = [this, &callBackValue, eventHub, frameNode](bool isHover) {
        checkEvent = std::nullopt;
        modifier_->setOnAccessibilityHover(node_, &callBackValue);
        ASSERT_FALSE(checkEvent.has_value());
        auto inputEventHub = eventHub->GetInputEventHub();
        ASSERT_NE(inputEventHub, nullptr);

        std::tuple<TouchType, AccessibilityHoverAction> touchHoverType = {
            TouchType::HOVER_MOVE, AccessibilityHoverAction::HOVER_MOVE
        };
        OffsetF offset;
        TouchTestResult result;
        inputEventHub->ProcessMouseTestHit(offset, result);
        for (const auto& resultData : result) {
            auto hoverResult = AceType::DynamicCast<HoverEventTarget>(resultData);
            ASSERT_NE(hoverResult, nullptr);
            TouchEvent me;
            me.SetType(std::get<0>(touchHoverType));
            hoverResult->HandleAccessibilityHoverEvent(isHover, me);
        }
        ASSERT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->isHover, isHover);
        EXPECT_EQ(checkEvent->type, std::get<1>(touchHoverType));
    };
    test(true);
    test(false);
}

/*
 * @tc.name: SetOnMouse
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, SetOnMouseTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onMouseFunc = [](Ark_VMContext, const Ark_Int32 resourceId, const Ark_MouseEvent event) {
        checkEvent = { .nodeId = resourceId };
    };

    auto callBackValue = Converter::ArkValue<Callback_MouseEvent_Void>(onMouseFunc, frameNode->GetId());

    auto test = [this, &callBackValue, eventHub, frameNode]() {
        checkEvent = std::nullopt;
        modifier_->setOnMouse(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());
        auto inputEventHub = eventHub->GetInputEventHub();
        ASSERT_NE(inputEventHub, nullptr);

        OffsetF offset;
        TouchTestResult result;
        inputEventHub->ProcessMouseTestHit(offset, result);
        for (const auto& resultData : result) {
            auto mouseResult = AceType::DynamicCast<MouseEventTarget>(resultData);
            ASSERT_NE(mouseResult, nullptr);
            MouseEvent me;
            mouseResult->HandleMouseEvent(me);
        }
        ASSERT_TRUE(checkEvent.has_value());
    };
    test();
}

/*
 * @tc.name: SetOnTouchIntercept
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, SetOnTouchInterceptTest, TestSize.Level1)
{
    static const int expectedResId = 123;
    static const std::string expectedType = "xxx";
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int resId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onTouchInterceptFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
                                const Ark_TouchEvent parameter,
                                const Callback_HitTestMode_Void continuation) {
        ASSERT_NE(parameter, nullptr);
        auto touchEventInfo = parameter->GetEventInfo();
        EXPECT_EQ(touchEventInfo->GetType(), expectedType);
        GeneratedModifier::GetTouchEventAccessor()->destroyPeer(parameter);
        checkEvent = { .resId = resourceId };
        Ark_HitTestMode retVal = Ark_HitTestMode::ARK_HIT_TEST_MODE_BLOCK;
        CallbackHelper(continuation).Invoke(retVal);
    };

    auto callbackValue =
        Converter::ArkValue<Callback_TouchEvent_HitTestMode>(nullptr, onTouchInterceptFunc, expectedResId);

    checkEvent = std::nullopt;
    modifier_->setOnTouchIntercept(node_, &callbackValue);
    EXPECT_FALSE(checkEvent.has_value());
    auto gestureEventHub = eventHub->GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto fireTouchEvent = gestureEventHub->GetOnTouchIntercept();
    TouchEventInfo info(expectedType);
    auto retValue = fireTouchEvent(info);
    EXPECT_EQ(retValue, NG::HitTestMode::HTMBLOCK);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent.value().resId, expectedResId);
}

/*
 * @tc.name: SetOnTouchTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, SetOnTouchTest, TestSize.Level1)
{
    static const int expectedResId = 123;
    static const std::string expectedType = "xxx";
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int resId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onTouchFunc = [](Ark_VMContext, const Ark_Int32 resourceId, const Ark_TouchEvent parameter) {
        ASSERT_NE(parameter, nullptr);
        auto peer = parameter;
        auto touchEventInfo = peer->GetEventInfo();
        ASSERT_NE(touchEventInfo, nullptr);
        EXPECT_EQ(touchEventInfo->GetType(), expectedType);
        GeneratedModifier::GetTouchEventAccessor()->destroyPeer(peer);
        checkEvent = { .resId = resourceId };
    };

    auto callbackValue =
        Converter::ArkValue<Callback_TouchEvent_Void>(onTouchFunc, expectedResId);

    checkEvent = std::nullopt;
    modifier_->setOnTouch(node_, &callbackValue);
    EXPECT_FALSE(checkEvent.has_value());
    auto gestureEventHub = eventHub->GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto& callback = gestureEventHub->touchEventActuator_->userCallback_;
    ASSERT_NE(callback, nullptr);
    TouchEventInfo info(expectedType);
    auto fire = callback->GetTouchEventCallback();
    ASSERT_NE(fire, nullptr);
    fire(info);
}

/*
 * @tc.name: SetOnAttach
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, SetOnAttachTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onAttachFunc = [](const Ark_Int32 resourceId) {
        checkEvent = { .nodeId = resourceId };
    };

    Callback_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr
        },
        .call = onAttachFunc
    };

    auto test = [this, &callBackValue, eventHub, frameNode]() {
        checkEvent = std::nullopt;
        modifier_->setOnAttach(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());
        eventHub->FireOnAttach();
        ASSERT_TRUE(checkEvent.has_value());
    };
    test();
}

/*
 * @tc.name: SetOnDetach
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, SetOnDetachTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onDetachFunc = [](const Ark_Int32 resourceId) {
        checkEvent = { .nodeId = resourceId };
    };

    Callback_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr
        },
        .call = onDetachFunc
    };

    auto test = [this, &callBackValue, eventHub, frameNode]() {
        checkEvent = std::nullopt;
        modifier_->setOnDetach(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());
        eventHub->FireOnDetach();
        ASSERT_TRUE(checkEvent.has_value());
    };
    test();
}
}
