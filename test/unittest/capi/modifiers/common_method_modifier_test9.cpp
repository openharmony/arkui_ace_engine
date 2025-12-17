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
#include "core/interfaces/native/implementation/focus_axis_event_accessor.h"
#include "core/interfaces/native/implementation/hover_event_peer.h"
#include "core/interfaces/native/implementation/touch_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "generated/type_helpers.h"
#include "core/components_ng/event/input_event_hub.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "test/unittest/capi/modifiers/generated/test_fixtures.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;
using namespace OHOS::Ace::NG::GeneratedModifier::FocusAxisEventAccessor;

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
    const auto ATTRIBUTE_DESCRIPTION_RESOURCE_ID_TEST = "accDescr";
    const auto ATTRIBUTE_DESCRIPTION_RESOURCE_VALUE_TEST = "description for accessibilityDescription";
    const auto ATTRIBUTE_LEVEL_NAME_TEST = "accessibilityLevel";
    const auto ATTRIBUTE_LEVEL_DEFAULT_VALUE_TEST = "auto";
    const auto ATTRIBUTE_CHECKED_NAME_TEST = "accessibilityChecked";
    const auto ATTRIBUTE_CHECKED_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_SELECTED_NAME_TEST = "accessibilitySelected";
    const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE_TEST = "";

#ifdef SUPPORT_DIGITAL_CROWN
    constexpr int64_t SEC_TO_MICROSEC = 1000000;

    const std::vector<std::tuple<std::string, CrownAction>> testFixtureEnumCrown = {
        { "ARK_CROWN_ACTION_BEGIN", CrownAction::BEGIN },
        { "ARK_CROWN_ACTION_UPDATE", CrownAction::UPDATE },
        { "ARK_CROWN_ACTION_END", CrownAction::END },
        { "ARK_CROWN_ACTION_UNKNOWN", CrownAction::UNKNOWN },
    };
#endif // SUPPORT_DIGITAL_CROWN
} // namespace

namespace Converter {
    template<>
    void AssignArkValue(Ark_Resource& dst, const std::string& src, ConvContext *ctx)
    {
        dst = ArkCreate<Ark_Resource>(src, ResourceType::STRING, ctx);
    }
#ifdef SUPPORT_DIGITAL_CROWN
    template<>
    void AssignCast(std::optional<CrownAction>& dst, const Ark_CrownAction& src)
    {
        switch (src) {
            case ARK_CROWN_ACTION_BEGIN: dst = CrownAction::BEGIN; break;
            case ARK_CROWN_ACTION_UPDATE: dst = CrownAction::UPDATE; break;
            case ARK_CROWN_ACTION_END: dst = CrownAction::END; break;
            default:
                LOGE("Unexpected enum value in Ark_CrownAction: %{public}d", src);
                break;
        }
    }

    template<>
    CrownEventInfo Convert(const Ark_CrownEvent& crownEvent)
    {
        CrownEvent event;
        auto originalTime = Convert<int64_t>(crownEvent.timestamp) / SEC_TO_MICROSEC;
        event.SetTimeStamp(originalTime);
        event.angularVelocity = Convert<float>(crownEvent.angularVelocity);
        event.degree = Convert<float>(crownEvent.degree);
        auto action = OptConvert<CrownAction>(crownEvent.action);
        if (action) {
            event.SetAction(*action);
        }
        CrownEventInfo info(event);
        return info;
    }
#endif // SUPPORT_DIGITAL_CROWN
} // namespace Converter

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

    void SetUp() override
    {
        ModifierTestBase::SetUp();
        auto fnode = reinterpret_cast<FrameNode *>(node_);
        ASSERT_NE(fnode, nullptr);
        render_ = fnode->GetRenderContext();
        ASSERT_NE(render_, nullptr);
        AddResource(ATTRIBUTE_DESCRIPTION_RESOURCE_ID_TEST, ATTRIBUTE_DESCRIPTION_RESOURCE_VALUE_TEST);
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
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityGroupTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityGroupWithValue, nullptr);
    using OneTestStep = std::tuple<Opt_Boolean, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Boolean>(true), "true"},
        {Converter::ArkValue<Opt_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityGroupWithValue(node_, &inputValue);
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
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityTextOfStringTypeTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityTextOfStringType, nullptr);
    using OneTestStep = std::tuple<Opt_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Opt_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityTextOfStringType(node_, &inputValue);
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
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityTextOfResourceTypeTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityTextOfResourceType, nullptr);
    using OneTestStep = std::tuple<Ark_Resource, std::string>;
    std::string inputVal1 {"test string 1"}, inputVal2 {"test string 2"};
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Resource>(inputVal1, nullptr), inputVal1},
        {Converter::ArkValue<Ark_Resource>(inputVal2, nullptr), inputVal2},
    };
    Opt_Resource optInputValue;
    for (auto [inputValue, expectedValue]: testPlan) {
        optInputValue = Converter::ArkValue<Opt_Resource>(inputValue);
        modifier_->setAccessibilityTextOfResourceType(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityTextHintTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityTextHint, nullptr);
    using OneTestStep = std::tuple<Opt_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Opt_String>("test string 2"), "test string 2"},
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
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityDescription0TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityDescriptionOfStringType, nullptr);
    using OneTestStep = std::tuple<Opt_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Opt_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityDescriptionOfStringType(node_, &inputValue);
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
    ASSERT_NE(modifier_->setAccessibilityDescriptionOfResourceType, nullptr);
    auto resName = NamedResourceId(ATTRIBUTE_DESCRIPTION_RESOURCE_ID_TEST, ResourceType::STRING);
    auto src = Converter::ArkValue<Opt_Resource>(CreateResource(resName));

    modifier_->setAccessibilityDescriptionOfResourceType(node_, &src);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_DESCRIPTION_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_DESCRIPTION_RESOURCE_VALUE_TEST);
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
    using OneTestStep = std::tuple<Opt_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Opt_String>("test string 2"), "test string 2"},
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
    using OneTestStep = std::tuple<Opt_Boolean, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Boolean>(true), "true"},
        {Converter::ArkValue<Opt_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityChecked(node_, &inputValue);
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
    using OneTestStep = std::tuple<Opt_Boolean, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Boolean>(true), "true"},
        {Converter::ArkValue<Opt_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilitySelected(node_, &inputValue);
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

    auto onHoverFunc = [](Ark_VMContext, const Ark_Int32 resourceId, const Ark_Boolean isHover,
            const Ark_HoverEvent peer) {
        ASSERT_NE(peer, nullptr);
        auto hoverEventInfo = peer->GetEventInfo();
        ASSERT_NE(hoverEventInfo, nullptr);
        EXPECT_EQ(hoverEventInfo->GetType(), expectedType);
        GeneratedModifier::GetHoverEventAccessor()->destroyPeer(peer);
        checkEvent = {
            .nodeId = resourceId, .isHover = Converter::Convert<bool>(isHover),
            .deviceType = hoverEventInfo->GetSourceDevice()
        };
    };

    auto callbackValue = Converter::ArkValue<Opt_Callback_Boolean_HoverEvent_Void>(
        Converter::ArkValue<Callback_Boolean_HoverEvent_Void>(onHoverFunc, expectedResId));

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
    test(false, SourceType::JOYSTICK);
}

/*
 * @tc.name: SetOnAccessibilityHover
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_SetOnAccessibilityHoverTest, TestSize.Level1)
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
                          const Ark_AccessibilityHoverEvent event) {
        auto info = event ? event->GetEventInfo() : nullptr;
        ASSERT_NE(info, nullptr);
        checkEvent = {
            .nodeId = resourceId,
            .isHover = isHover,
            .type = info->GetActionType()
        };
        GeneratedModifier::GetAccessibilityHoverEventAccessor()->destroyPeer(event);
    };
    auto callBackValue = Converter::ArkValue<Opt_AccessibilityCallback>(
        Converter::ArkValue<AccessibilityCallback>(onAccessibilityHoverFunc, frameNode->GetId()));

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

    auto callBackValue = Converter::ArkValue<Opt_Callback_MouseEvent_Void>(
        Converter::ArkValue<Callback_MouseEvent_Void>(onMouseFunc, frameNode->GetId()));

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
        CallbackHelper(continuation).InvokeSync(retVal);
    };

    auto callbackValue = Converter::ArkValue<Opt_Callback_TouchEvent_HitTestMode>(
        Converter::ArkValue<Callback_TouchEvent_HitTestMode>(nullptr, onTouchInterceptFunc, expectedResId));

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
HWTEST_F(CommonMethodModifierTest9, DISABLED_SetOnTouchTest, TestSize.Level1)
{
#ifdef WRONG_PRIVATE
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

    auto callbackValue = Converter::ArkValue<Opt_Callback_TouchEvent_Void>(
        Converter::ArkValue<Callback_TouchEvent_Void>(onTouchFunc, expectedResId));

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
#endif
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

    auto onAttachSyncFunc = [](Ark_VMContext vmContext, const Ark_Int32 resourceId) {
        checkEvent = { .nodeId = resourceId };
    };

    auto callBackValue = Converter::ArkValue<Opt_VoidCallback>(VoidCallback {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr
        },
        .call = onAttachFunc,
        .callSync = onAttachSyncFunc
    });

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

    auto onDetachSyncFunc = [](Ark_VMContext vmContext, const Ark_Int32 resourceId) {
        checkEvent = { .nodeId = resourceId };
    };

    auto callBackValue = Converter::ArkValue<Opt_VoidCallback>(VoidCallback {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr
        },
        .call = onDetachFunc,
        .callSync = onDetachSyncFunc
    });

    auto test = [this, &callBackValue, eventHub, frameNode]() {
        checkEvent = std::nullopt;
        modifier_->setOnDetach(node_, &callBackValue);
        EXPECT_FALSE(checkEvent.has_value());
        eventHub->FireOnDetach();
        ASSERT_TRUE(checkEvent.has_value());
    };
    test();
}


/*
 * @tc.name: setOnAccessibilityFocusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setOnAccessibilityFocusTest, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setOnAccessibilityFocus);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    struct CheckEvent {
        int32_t nodeId = -1;
        bool isFocus = false;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onAccessibilityFocus = [](const Ark_Int32 resourceId, const Ark_Boolean isFocus) {
        checkEvent = {
            .nodeId = resourceId,
            .isFocus = Convert<bool>(isFocus),
        };
    };

    auto accessibilityFocusCallback = ArkValue<Opt_AccessibilityFocusCallback>(
        ArkValue<AccessibilityFocusCallback>(onAccessibilityFocus, frameNode->GetId()));

    for (auto& [message, value, expect] : Fixtures::testFixtureBooleanValidValues) {
        checkEvent = std::nullopt;
        modifier_->setOnAccessibilityFocus(node_, &accessibilityFocusCallback);
        EXPECT_FALSE(checkEvent);
        accessibilityProperty->OnAccessibilityFocusCallback(value);
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId()) << "Passed id is: " << frameNode->GetId();
        EXPECT_EQ(checkEvent->isFocus, value) << "Passed value is: " << message;
    }
}

/*
 * @tc.name: setOnFocusAxisEventTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setOnFocusAxisEventTest, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setOnFocusAxisEvent);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    FocusAxisEvent event;
    event.absXValue = 1.0f;
    event.absYValue = 2.0f;
    event.absZValue = 3.0f;
    event.absRzValue = 4.0f;
    event.absGasValue = 5.0f;
    event.absBrakeValue = 6.0f;
    event.absHat0XValue = 7.0f;
    event.absHat0YValue = 8.0f;
    FocusAxisEventInfo eventInfo(event);

    struct CheckEvent {
        int32_t nodeId = -1;
        std::map<AxisModel, float> info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onFocusAxisCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_FocusAxisEvent parameter) {
        checkEvent = {
            .nodeId = resourceId,
        };
        if (parameter && parameter->GetEventInfo()) {
            checkEvent->info = getAxisMapFromInfo(*parameter->GetEventInfo());
        }
        PeerUtils::DestroyPeer(parameter);
    };

    auto accessibilityFocusCallback = ArkValue<Opt_Callback_FocusAxisEvent_Void>(
        ArkValue<Callback_FocusAxisEvent_Void>(onFocusAxisCallback, frameNode->GetId()));
    modifier_->setOnFocusAxisEvent(node_, &accessibilityFocusCallback);
    EXPECT_FALSE(checkEvent);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_TRUE(focusHub);
    auto onFocusAxisFromFocus = focusHub->GetOnFocusAxisCallback();
    ASSERT_TRUE(onFocusAxisFromFocus);
    onFocusAxisFromFocus(eventInfo);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId()) << "Passed id is: " << frameNode->GetId();
    EXPECT_EQ(getAxisMapFromInfo(eventInfo), checkEvent->info);
}

#ifdef SUPPORT_DIGITAL_CROWN
MATCHER_P(CompareCrownEventInfo, expected, "Compare CrownEventInfo values")
{
    return arg.GetTimeStamp() == expected.GetTimeStamp()
        && arg.GetAngularVelocity() == expected.GetAngularVelocity()
        && arg.GetDegree() == expected.GetDegree()
        && arg.GetAction() == expected.GetAction()
        && expected.IsStopPropagation();
}
#endif // SUPPORT_DIGITAL_CROWN
/*
 * @tc.name: setOnDigitalCrownTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setOnDigitalCrownTest, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setOnDigitalCrown);
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    struct CheckEvent {
        int32_t nodeId;
        CrownEventInfo eventInfo;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    CrownEvent event;
    event.SetTimeStamp(12345);
    event.angularVelocity = 5.0f;
    event.degree = 10.0f;
    event.isInjected = true;
    for (auto& [message, value] : testFixtureEnumCrown) {
        checkEvent = std::nullopt;
        event.SetAction(value);
        CrownEventInfo info(event);
        auto onCrownEvent = [](const Ark_Int32 resourceId, const Ark_CrownEvent parameter) {
            auto callback = CallbackHelper(parameter.stopPropagation);
            callback.Invoke();
            checkEvent = {
                .nodeId = resourceId,
                .eventInfo = Convert<CrownEventInfo>(parameter),
            };
        };
        auto arkCrownCallback = ArkValue<Callback_CrownEvent_Void>(onCrownEvent, frameNode->GetId());
        auto optCrownCallback = ArkValue<Opt_Callback_CrownEvent_Void>(arkCrownCallback);
        modifier_->setOnDigitalCrown(node_, &optCrownCallback);
        ASSERT_FALSE(checkEvent);
        auto focusHub = frameNode->GetOrCreateFocusHub();
        ASSERT_TRUE(focusHub);
        auto focusCallback = focusHub->GetOnCrownCallback();
        focusCallback(info);
        ASSERT_TRUE(checkEvent);
        EXPECT_EQ(checkEvent->nodeId, frameNode->GetId()) << "Passed id is: " << frameNode->GetId();

        EXPECT_THAT(checkEvent->eventInfo, CompareCrownEventInfo(info));
    }
    checkEvent = std::nullopt;
    auto optCrownCallback = ArkValue<Opt_Callback_CrownEvent_Void>();
    modifier_->setOnDigitalCrown(node_, &optCrownCallback);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_TRUE(focusHub);
    focusHub->ProcessOnCrownEventInternal(event);
    ASSERT_FALSE(checkEvent);
#endif // SUPPORT_DIGITAL_CROWN
}
}
