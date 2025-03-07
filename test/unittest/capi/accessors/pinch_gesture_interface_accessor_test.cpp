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
#include "core/interfaces/native/implementation/pinch_gesture_interface_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr int32_t EXPECTED_ID = 111;
constexpr double DEFAULT_PINCH_DISTANCE = 5.0;
struct CheckEvent {
    int32_t resourceId;
};
}

using namespace testing;
using namespace testing::ext;

class MockRotationGesture : public PinchGesture {
public:
    MockRotationGesture(int32_t fingers, double distance) : PinchGesture(fingers, distance) {}
    ~MockRotationGesture() override = default;

    bool HandleOnActionStart(GestureEvent& event)
    {
        if (onActionStartId_) {
            (*onActionStartId_)(event);
            return true;
        }
        return false;
    }
    bool HandleOnActionUpdate(GestureEvent& event)
    {
        if (onActionUpdateId_) {
            (*onActionUpdateId_)(event);
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
    bool HandleOnActionCancel()
    {
        if (onActionCancelId_) {
            (*onActionCancelId_)();
            return true;
        }
        return false;
    }
};

class PinchGestureInterfaceAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIPinchGestureInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getPinchGestureInterfaceAccessor, PinchGestureInterfacePeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        gesture_ = AceType::MakeRefPtr<MockRotationGesture>(DEFAULT_PINCH_FINGER, DEFAULT_PINCH_DISTANCE);
        peer_->gesture = gesture_;
    }
    RefPtr<MockRotationGesture> gesture_;
};

/**
 * @tc.name: OnActionStartTest
 * @tc.desc: setOnActionStart test
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, OnActionStartTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, testCallback, EXPECTED_ID);
    accessor_->onActionStart(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleOnActionStart(evt));
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}

/**
 * @tc.name: OnActionUpdateTest
 * @tc.desc: setOnActionUpdate test
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, OnActionUpdateTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, testCallback, EXPECTED_ID);
    accessor_->onActionUpdate(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleOnActionUpdate(evt));
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}

/**
 * @tc.name: OnActionCancelTest
 * @tc.desc: setOnActionCancel test
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, OnActionCancelTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(testCallback, EXPECTED_ID);
    accessor_->onActionCancel(peer_, &arkCallback);
    ASSERT_TRUE(gesture_->HandleOnActionCancel());
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}

/**
 * @tc.name: OnActionEndTest
 * @tc.desc: setOnActionEnd test
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, OnActionEndTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, testCallback, EXPECTED_ID);
    accessor_->onActionEnd(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleOnActionEnd(evt));
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}
}