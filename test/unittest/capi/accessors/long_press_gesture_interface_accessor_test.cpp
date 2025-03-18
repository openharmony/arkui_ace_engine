/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/long_press_gesture_interface_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    int32_t ID = 123;
    constexpr bool DEFAULT_REPEAT = false;
    constexpr int32_t DEFAULT_FINGERS = 1;
    constexpr int32_t DEFAULT_DURATION = 500;
    struct CheckEvent {
        int32_t resourceId;
    };
}

class MockLongPressGesture : public LongPressGesture {
public:
    MockLongPressGesture(int32_t fingers, bool repeat, int32_t duration) : LongPressGesture(fingers, repeat, duration)
    {}
    ~MockLongPressGesture() override = default;

    bool HandleOnAction(GestureEvent& event)
    {
        if (onActionId_) {
            (*onActionId_)(event);
            return true;
        }
        return false;
    }

    bool HandleOnActionEnd(GestureEvent& event)
    {
        if (onActionEndId_) {
            (*onActionEndId_)(event);
            return true;
        }
        return false;
    }

    bool HandleOnActionCancel(GestureEvent& event)
    {
        if (onActionCancelId_) {
            (*onActionCancelId_)(event);
            return true;
        }
        return false;
    }
};

class LongPressGestureIntrfaceAccessorTest
    : public AccessorTestBase<GENERATED_ArkUILongPressGestureInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getLongPressGestureInterfaceAccessor, LongPressGestureInterfacePeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        peer_->gesture =
            AceType::MakeRefPtr<MockLongPressGesture>(DEFAULT_FINGERS, DEFAULT_REPEAT, DEFAULT_DURATION);
    }
};

/**
 * @tc.name: OnActionTest
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(LongPressGestureIntrfaceAccessorTest, OnActionTest, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(testCallback, ID);
    accessor_->onAction(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockLongPressGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnAction(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}

/**
 * @tc.name: OnActionEndTest
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(LongPressGestureIntrfaceAccessorTest, OnActionEndTest, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(testCallback, ID);
    accessor_->onActionEnd(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockLongPressGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnActionEnd(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}

/**
 * @tc.name: OnActionCancel0Test
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(LongPressGestureIntrfaceAccessorTest, OnActionCancel0Test, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(testCallback, ID);
    accessor_->onActionCancel0(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockLongPressGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnActionCancel(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}

/**
 * @tc.name: OnActionCancel1Test
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(LongPressGestureIntrfaceAccessorTest, OnActionCancel1Test, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(testCallback, ID);
    accessor_->onActionCancel1(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockLongPressGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnActionCancel(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}
}
