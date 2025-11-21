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
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr int32_t EXPECTED_ID = 111;
constexpr double DEFAULT_PINCH_DISTANCE = 5.0;
constexpr double FLT_PRECISION = 0.001;
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
    bool HandleOnActionCancel(GestureEvent& event)
    {
        if (onActionCancelId_) {
            (*onActionCancelId_)(event);
            return true;
        }
        return false;
    }
};

class PinchGestureInterfaceAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIPinchGestureInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getPinchGestureInterfaceAccessor, PinchGestureInterfacePeer> {
public:
    void *CreatePeerInstance() override
    {
        Ark_PinchGestureInterface_Invoke_Literal value{};
        return accessor_->construct(&value);
    }
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        gesture_ = AceType::MakeRefPtr<MockRotationGesture>(DEFAULT_PINCH_FINGER, DEFAULT_PINCH_DISTANCE);
        peer_->gesture = gesture_;
    }
    RefPtr<MockRotationGesture> gesture_;
};

/**
 * @tc.name: CtorTestFingers
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, CtorTestFingers, TestSize.Level1)
{
    const std::vector<std::pair<int32_t, int32_t>> TEST_PLAN = {
        { 1, DEFAULT_PINCH_FINGER },
        { 2, 2 },
        { 3, 3 },
        { 4, 4 },
        { 5, 5 },
        { 6, DEFAULT_PINCH_FINGER },
    };
    const double expectedDistance = 10.0;

    for (auto& value : TEST_PLAN) {
        Ark_PinchGestureInterface_Invoke_Literal params;
        params.fingers = Converter::ArkValue<Opt_Number>(value.first);
        params.distance = Converter::ArkValue<Opt_Number>(expectedDistance);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, expectedDistance, FLT_PRECISION);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN) {
        Ark_PinchGestureInterface_Invoke_Literal params;
        params.fingers = Converter::ArkValue<Opt_Number>(value.first);
        params.distance = Converter::ArkValue<Opt_Number>();
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, DEFAULT_PINCH_DISTANCE, FLT_PRECISION);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, CtorTestInvalid, TestSize.Level1)
{
    auto peer = accessor_->construct(nullptr);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->gesture, nullptr);
    auto result = peer->gesture->GetFingers();
    EXPECT_EQ(result, DEFAULT_PINCH_FINGER);
    auto distance = peer->gesture->GetDistance();
    EXPECT_NEAR(distance, DEFAULT_PINCH_DISTANCE, FLT_PRECISION);
    finalyzer_(peer);
}

/**
 * @tc.name: CtorTestDistance
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, CtorTestDistance, TestSize.Level1)
{
    const std::vector<std::pair<double, double>> TEST_PLAN = {
        { -1.0, DEFAULT_PINCH_DISTANCE },
        { -0.05, DEFAULT_PINCH_DISTANCE },
        { 0.0, 0.0 },
        { 0.05, 0.05 },
        { 1.0, 1.0 },
        { 100.0, 100.0 },
    };
    const double expectedFingers = 4;

    for (auto& value : TEST_PLAN) {
        Ark_PinchGestureInterface_Invoke_Literal params;
        params.fingers = Converter::ArkValue<Opt_Number>(expectedFingers);
        params.distance = Converter::ArkValue<Opt_Number>(value.first);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto result = peer->gesture->GetFingers();
        EXPECT_EQ(result, expectedFingers);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, value.second, FLT_PRECISION);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN) {
        Ark_PinchGestureInterface_Invoke_Literal params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.distance = Converter::ArkValue<Opt_Number>(value.first);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto result = peer->gesture->GetFingers();
        EXPECT_EQ(result, DEFAULT_PINCH_FINGER);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, value.second, FLT_PRECISION);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: OnActionStartTest
 * @tc.desc: setOnActionStart test
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, OnActionStartTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, testCallback, EXPECTED_ID);
    accessor_->onActionUpdate(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleOnActionUpdate(evt));
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}

/**
 * @tc.name: OnActionCancel0Test
 * @tc.desc: setOnActionCancel test
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, OnActionCancel0Test, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(testCallback, EXPECTED_ID);
    accessor_->onActionCancel0(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleOnActionCancel(evt));
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}

/**
 * @tc.name: OnActionCancel1Test
 * @tc.desc: setOnActionCancel test
 * @tc.type: FUNC
 */
HWTEST_F(PinchGestureInterfaceAccessorTest, OnActionCancel1Test, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, testCallback, EXPECTED_ID);
    accessor_->onActionCancel1(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleOnActionCancel(evt));
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
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, testCallback, EXPECTED_ID);
    accessor_->onActionEnd(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleOnActionEnd(evt));
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}
}
