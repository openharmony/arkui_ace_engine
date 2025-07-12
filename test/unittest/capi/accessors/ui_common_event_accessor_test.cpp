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

#include "core/interfaces/native/implementation/ui_common_event_peer.h"
#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

static const int RES_ID = 123;

struct TestEvent {
    int32_t resourceId;
};

class UICommonEventAccessorTest : public AccessorTestBase<GENERATED_ArkUIUICommonEventAccessor,
    &GENERATED_ArkUIAccessors::getUICommonEventAccessor, UICommonEventPeer> {
};

/**
 * @tc.name: setOnClickTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnClickTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;
    auto hub = frameNode->GetOrCreateGestureEventHub();
    hub->CheckClickActuator();

    auto onClickFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_ClickEvent event) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_ClickEvent_Void>(nullptr, onClickFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_ClickEvent_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnClick(peer_, &optCallback);

    auto func = hub->GetClickEvent();
    ASSERT_NE(func, nullptr);
    OHOS::Ace::GestureEvent arg {};
    func(arg);
    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, RES_ID);
}

/**
 * @tc.name: setOnTouchTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnTouchTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;

    auto hub = frameNode->GetOrCreateGestureEventHub();

    auto onTouchFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_TouchEvent event) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_TouchEvent_Void>(nullptr, onTouchFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_TouchEvent_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnTouch(peer_, &optCallback);

    const OffsetF off;
    const TouchRestrict touchR;
    TouchTestResult result;
    TouchTestResult fresult;
    int32_t touchId = 0;
    const PointF localPoint;
    const RefPtr<TargetComponent> targetC;
    ResponseLinkResult response;

    hub->ProcessEventTouchTestHit(off, touchR, result, fresult, touchId, localPoint, targetC, response);
    auto target = result.front();
    ASSERT_NE(target, nullptr);
    TouchEvent ev {};
    target->HandleEvent(ev);
}

/**
 * @tc.name: setOnAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, DISABLED_setOnAppearTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;

    auto hub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);

    auto onAppearFunc = [](const Ark_Int32 resourceId) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(onAppearFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnAppear(peer_, &optCallback);
    // EventHub::FireOnAppear() puts the callback into taskSheduler
    hub->FireOnAppear();
    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, RES_ID);
}

/**
 * @tc.name: setOnDisappearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnDisappearTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;

    auto hub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);

    auto onDisappearFunc = [](const Ark_Int32 resourceId) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(onDisappearFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnDisappear(peer_, &optCallback);

    hub->FireOnDisappear();
    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, RES_ID);
}

/**
 * @tc.name: setOnFocusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnFocusTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;
    auto focusHub = frameNode->GetEventHub<EventHub>()->GetOrCreateFocusHub();

    auto onFocusFunc = [](const Ark_Int32 resourceId) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(onFocusFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnFocus(peer_, &optCallback);

    ASSERT_NE(focusHub, nullptr);
    OHOS::Ace::NonPointerEvent evt {};
    focusHub->SetCurrentFocus(false);
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->SetEnabled(true);
    focusHub->SetFocusable(true);
    focusHub->SetShow(true);
    focusHub->RequestFocusImmediately(FocusReason::DEFAULT);
    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, RES_ID);
}

/**
 * @tc.name: setOnBlurTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnBlurTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;
    auto focusHub = frameNode->GetEventHub<EventHub>()->GetOrCreateFocusHub();

    auto onBlurFunc = [](const Ark_Int32 resourceId) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(onBlurFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnBlur(peer_, &optCallback);

    ASSERT_NE(focusHub, nullptr);
    focusHub->SetCurrentFocus(true);
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->LostFocus();
    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, RES_ID);
}

/**
 * @tc.name: setOnHoverTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnHoverTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;

    auto onHoverFunc = [](Ark_VMContext context,
                        const Ark_Int32 resourceId,
                        const Ark_Boolean isHover,
                        const Ark_HoverEvent event) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };

    auto arkCallback = Converter::ArkValue<HoverCallback>(nullptr, onHoverFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_HoverCallback>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnHover(peer_, &optCallback);

    auto inputHub = frameNode->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    const OffsetF& off {};
    TouchTestResult result;
    inputHub->ProcessMouseTestHit(off, result);
    auto target = AceType::DynamicCast<HoverEventTarget>(result.front());
    ASSERT_NE(target, nullptr);
    MouseEvent ev {};
    target->HandleHoverEvent(true, ev);

    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, RES_ID);
}

/**
 * @tc.name: setOnMouseTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnMouseTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;

    auto onMouseFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_MouseEvent event) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_MouseEvent_Void>(nullptr, onMouseFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_MouseEvent_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnMouse(peer_, &optCallback);

    auto inputHub = frameNode->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    const OffsetF& off {};
    TouchTestResult result;
    inputHub->ProcessMouseTestHit(off, result);
    auto target = AceType::DynamicCast<MouseEventTarget>(result.front());
    ASSERT_NE(target, nullptr);
    MouseEvent ev {};
    target->HandleMouseEvent(ev);

    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, RES_ID);
}

/**
 * @tc.name: setOnVisibleAreaApproximateChange
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, DISABLED_setOnVisibleAreaApproximateChangeTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onAreaChangeFunc = [](Ark_VMContext context,
        const Ark_Int32 resourceId,
        const Ark_Boolean isExpanding,
        const Ark_Number currentRatio) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<VisibleAreaChangeCallback>(nullptr, onAreaChangeFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_VisibleAreaChangeCallback>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    Ark_VisibleAreaEventOptions options {};
    accessor_->setOnVisibleAreaApproximateChange(peer_, &options, &optCallback);
}

/**
 * @tc.name: setOnKeyEventTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, DISABLED_setOnKeyEventTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;

    auto focusHub = frameNode->GetEventHub<EventHub>()->GetOrCreateFocusHub();

    auto onKeyEventFunc = [](const Ark_Int32 resourceId, const Ark_KeyEvent event) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_KeyEvent_Void>(onKeyEventFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_KeyEvent_Void>(arkCallback);
    accessor_->setOnKeyEvent(peer_, &optCallback);
}

/**
 * @tc.name: setOnSizeChangeEventTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, DISABLED_setOnSizeChangeEventTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;
    const auto frameNode = AceType::MakeRefPtr<FrameNode>("TEST", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;
    auto hub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);

    auto onSizeChangeFunc = [](const Ark_Int32 resourceId,
                                const Ark_SizeOptions oldValue,
                                const Ark_SizeOptions newValue) {
        testEvent = TestEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<SizeChangeCallback>(onSizeChangeFunc, RES_ID);
    auto optCallback = Converter::ArkValue<Opt_SizeChangeCallback>(arkCallback);
    accessor_->setOnSizeChange(peer_, &optCallback);
    RectF oldRect {};
    RectF newRect {};
    hub->FireOnSizeChanged(oldRect, newRect);
    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, RES_ID);
}

} // namespace OHOS::Ace::NG
