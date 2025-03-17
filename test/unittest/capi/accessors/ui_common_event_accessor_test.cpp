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

namespace {
    class MockFrameNode : public FrameNode {
    public:
        MockFrameNode() : FrameNode("TEST", 0, AceType::MakeRefPtr<Pattern>()) {}
    
        MOCK_METHOD(void, MarkDirtyNode, (PropertyChangeFlag));
    };
} // namespace

static const int expectedResId = 123;

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
    const auto frameNode = AceType::MakeRefPtr<MockFrameNode>();
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;
    auto hub = frameNode->GetOrCreateGestureEventHub();

    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onClickFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_ClickEvent event) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_ClickEvent_Void>(nullptr, onClickFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_ClickEvent_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnClick(peer_, &optCallback);

   // auto func = hub->userParallelClickEventActuator_;
   // f();

    /*TestEvent evt;
    (reinterpret_cast<MockRotationGesture*>(Referenced::RawPtr(peer_->gesture)))->HandleOnClick(evt);
    ASSERT_TRUE(rotationEvent);
    EXPECT_EQ(rotationEvent->resourceId, expectedResId);*/
}

/**
 * @tc.name: setOnTouchTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnTouchTest, TestSize.Level1)
{
    const auto frameNode = AceType::MakeRefPtr<MockFrameNode>();
    ASSERT_NE(frameNode, nullptr);
    peer_->node = frameNode;
    auto hub = frameNode->GetOrCreateGestureEventHub();

    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onTouchFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_TouchEvent event) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_TouchEvent_Void>(nullptr, onTouchFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_TouchEvent_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnTouch(peer_, &optCallback);

    TestEvent evt;
    auto func = hub->GetOnTouchIntercept();
    func(&evt);
    ASSERT_TRUE(testEvent);
    EXPECT_EQ(testEvent->resourceId, expectedResId);
}

/**
 * @tc.name: setOnAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnAppearTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onAppearFunc = [](Ark_VMContext context, const Ark_Int32 resourceId) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(nullptr, onAppearFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnAppear(peer_, &optCallback);
}

/**
 * @tc.name: setOnDisappearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnDisappearTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onDisappearFunc = [](Ark_VMContext context, const Ark_Int32 resourceId) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(nullptr, onDisappearFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnDisappear(peer_, &optCallback);
}

/**
 * @tc.name: setOnFocusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnFocusTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onFocusFunc = [](Ark_VMContext context, const Ark_Int32 resourceId) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(nullptr, onFocusFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnFocus(peer_, &optCallback);
}

/**
 * @tc.name: setOnBlurTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnBlurTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onBlurFunc = [](Ark_VMContext context, const Ark_Int32 resourceId) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(nullptr, onBlurFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnBlur(peer_, &optCallback);
}

/**
 * @tc.name: setOnHoverTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnHoverTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onHoverFunc = [](Ark_VMContext context,
                        const Ark_Int32 resourceId,
                        const Ark_Boolean isHover,
                        const Ark_HoverEvent event) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<HoverCallback>(nullptr, onHoverFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_HoverCallback>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnHover(peer_, &optCallback);
}

/**
 * @tc.name: setOnMouseTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnMouseTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onMouseFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_MouseEvent event) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_MouseEvent_Void>(nullptr, onMouseFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_MouseEvent_Void>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->setOnMouse(peer_, &optCallback);
}

/**
 * @tc.name: setOnVisibleAreaApproximateChange
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UICommonEventAccessorTest, setOnVisibleAreaApproximateChangeTest, TestSize.Level1)
{
    static std::optional<TestEvent> testEvent = std::nullopt;

    auto onAreaChangeFunc = [](Ark_VMContext context,
        const Ark_Int32 resourceId,
        const Ark_Boolean isExpanding,
        const Ark_Number currentRatio) {
        testEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<VisibleAreaChangeCallback>(nullptr, onAreaChangeFunc, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_VisibleAreaChangeCallback>(arkCallback);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    Ark_VisibleAreaEventOptions options = {};
    accessor_->setOnVisibleAreaApproximateChange(peer_, &options, &optCallback);
}
} // namespace OHOS::Ace::NG
 