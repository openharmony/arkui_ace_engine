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

#include "core/interfaces/native/implementation/rotation_gesture_interface_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/gestures/rotation_gesture.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

class MockRotationGesture : public RotationGesture {
    public:
        MockRotationGesture(int32_t fingers, double angle) : RotationGesture(fingers, angle) {}
        ~MockRotationGesture() override = default;

        void HandleOnActionStart(GestureEvent& event)
        {
            (*onActionStartId_)(event);
        }
        void HandleOnActionUpdate(GestureEvent& event)
        {
            (*onActionUpdateId_)(event);
        }
        void HandleOnActionEnd(GestureEvent& event)
        {
            (*onActionEndId_)(event);
        }
        void HandleOnActionCancel(GestureEvent& event)
        {
            (*onActionCancelId_)(event);
        }
    };

namespace {
struct RotationEvent {
    int32_t resourceId;
};

static const int RES_ID = 123;

constexpr int32_t DEFAULT_FINGERS = 2;
constexpr double DEFAULT_ANGLE = 1.0;
constexpr bool DEFAULT_IS_LIMIT_FINGER_COUNT = false;
constexpr double FLT_PRECISION = 0.001;
}
class RotationGestureInterfaceAccessorTest :
    public AccessorTestCtorBase<GENERATED_ArkUIRotationGestureInterfaceAccessor,
    &GENERATED_ArkUIAccessors::getRotationGestureInterfaceAccessor, RotationGestureInterfacePeer> {
public:
    void *CreatePeerInstance() override
    {
        auto value = Converter::ArkValue<Opt_Literal_Number_angle_fingers>();
        return accessor_->construct(&value);
    }
    void SetUp() override
    {
        AccessorTestCtorBase::SetUp();

        int32_t fingersNum = DEFAULT_SLIDE_FINGER;
        double angleNum = 0;
        peer_->gesture = AceType::MakeRefPtr<MockRotationGesture>(fingersNum, angleNum);
    }
};

/**
 * @tc.name: CtorTestFingers
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureInterfaceAccessorTest, CtorTestFingers, TestSize.Level1)
{
    const std::vector<std::pair<int32_t, int32_t>> TEST_PLAN = {
        { -10, DEFAULT_FINGERS },
        { 0, DEFAULT_FINGERS },
        { 1, DEFAULT_FINGERS },
        { 2, 2 },
        { 10, 10 },
        { 11, 11 },
    };
    double someAngle = 50.5;

    for (auto& value : TEST_PLAN) {
        Ark_Literal_Number_angle_fingers params;
        params.fingers = Converter::ArkValue<Opt_Number>(value.first);
        params.angle = Converter::ArkValue<Opt_Number>(someAngle);
        auto optParam = Converter::ArkValue<Opt_Literal_Number_angle_fingers>(params);
        auto peer = accessor_->construct(&optParam);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto angle = peer->gesture->GetAngle();
        EXPECT_NEAR(angle, someAngle, FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN) {
        Ark_Literal_Number_angle_fingers params;
        params.fingers = Converter::ArkValue<Opt_Number>(value.first);
        params.angle = Converter::ArkValue<Opt_Number>();
        auto optParam = Converter::ArkValue<Opt_Literal_Number_angle_fingers>(params);
        auto peer = accessor_->construct(&optParam);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto angle = peer->gesture->GetAngle();
        EXPECT_NEAR(angle, DEFAULT_ANGLE, FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestAngle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureInterfaceAccessorTest, CtorTestAngle, TestSize.Level1)
{
    const std::vector<std::pair<double, double>> TEST_PLAN = {
        { -10.0, DEFAULT_ANGLE },
        { 0.0, DEFAULT_ANGLE },
        { 1.0, 1.0 },
        { 20.0, 20.0 },
    };
    double someFingers = 3;

    for (auto& value : TEST_PLAN) {
        Ark_Literal_Number_angle_fingers params;
        params.fingers = Converter::ArkValue<Opt_Number>(someFingers);
        params.angle = Converter::ArkValue<Opt_Number>(value.first);
        auto optParam = Converter::ArkValue<Opt_Literal_Number_angle_fingers>(params);
        auto peer = accessor_->construct(&optParam);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, someFingers);
        auto angle = peer->gesture->GetAngle();
        EXPECT_NEAR(angle, value.second, FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN) {
        Ark_Literal_Number_angle_fingers params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.angle = Converter::ArkValue<Opt_Number>(value.first);
        auto optParam = Converter::ArkValue<Opt_Literal_Number_angle_fingers>(params);
        auto peer = accessor_->construct(&optParam);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto angle = peer->gesture->GetAngle();
        EXPECT_NEAR(angle, value.second, FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureInterfaceAccessorTest, CtorTestInvalid, TestSize.Level1)
{
    auto peer = accessor_->construct(nullptr);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->gesture, nullptr);
    auto fingers = peer->gesture->GetFingers();
    EXPECT_EQ(fingers, DEFAULT_FINGERS);
    auto angle = peer->gesture->GetAngle();
    EXPECT_NEAR(angle, DEFAULT_ANGLE, FLT_PRECISION);
    auto limitFingerCount = peer->gesture->GetLimitFingerCount();
    EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
    finalyzer_(peer);
}


/**
 * @tc.name: onActionStartTest
 * @tc.desc: check work of caretPosition method
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureInterfaceAccessorTest, onActionStartTest, TestSize.Level1)
{
    static std::optional<RotationEvent> rotationEvent = std::nullopt;
    auto onActionStartFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        rotationEvent = RotationEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, onActionStartFunc, RES_ID);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->onActionStart(peer_, &arkCallback);
    GestureEvent evt;
    (reinterpret_cast<MockRotationGesture*>(Referenced::RawPtr(peer_->gesture)))->HandleOnActionStart(evt);
    ASSERT_TRUE(rotationEvent);
    EXPECT_EQ(rotationEvent->resourceId, RES_ID);
}

 /**
 * @tc.name: onActionUpdateTest
 * @tc.desc: check work of caretPosition method
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureInterfaceAccessorTest, onActionUpdateTest, TestSize.Level1)
{
    static std::optional<RotationEvent> rotationEvent = std::nullopt;
    auto onActionUpdateFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        rotationEvent = RotationEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, onActionUpdateFunc, RES_ID);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->onActionUpdate(peer_, &arkCallback);
    GestureEvent evt;
    (reinterpret_cast<MockRotationGesture*>(Referenced::RawPtr(peer_->gesture)))->HandleOnActionUpdate(evt);
    ASSERT_TRUE(rotationEvent);
    EXPECT_EQ(rotationEvent->resourceId, RES_ID);
}

 /**
 * @tc.name: onActionEndTest
 * @tc.desc: check work of caretPosition method
 * @tc.type: FUNC
 */

HWTEST_F(RotationGestureInterfaceAccessorTest, onActionEndTest, TestSize.Level1)
{
    static std::optional<RotationEvent> rotationEvent = std::nullopt;
    auto onActionEndFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        rotationEvent = RotationEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, onActionEndFunc, RES_ID);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->onActionEnd(peer_, &arkCallback);
    GestureEvent evt;
    (reinterpret_cast<MockRotationGesture*>(Referenced::RawPtr(peer_->gesture)))->HandleOnActionEnd(evt);
    ASSERT_TRUE(rotationEvent);
    EXPECT_EQ(rotationEvent->resourceId, RES_ID);
}

 /**
 * @tc.name: onActionCancel0Test
 * @tc.desc: check work of caretPosition method
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureInterfaceAccessorTest, onActionCancel0Test, TestSize.Level1)
{
    static std::optional<RotationEvent> rotationEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId) {
        rotationEvent = RotationEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(testCallback, RES_ID);
    accessor_->onActionCancel0(peer_, &arkCallback);
    GestureEvent evt;
    (reinterpret_cast<MockRotationGesture*>(Referenced::RawPtr(peer_->gesture)))->HandleOnActionCancel(evt);
    ASSERT_TRUE(rotationEvent);
    EXPECT_EQ(rotationEvent->resourceId, RES_ID);
}

 /**
 * @tc.name: onActionCancel1Test
 * @tc.desc: check work of caretPosition method
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureInterfaceAccessorTest, onActionCancel1Test, TestSize.Level1)
{
    static std::optional<RotationEvent> rotationEvent = std::nullopt;
    auto onActionCancelFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        rotationEvent = RotationEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, onActionCancelFunc, RES_ID);
    ASSERT_NE(peer_, nullptr);
    ASSERT_NE(accessor_, nullptr);
    accessor_->onActionCancel1(peer_, &arkCallback);
    GestureEvent evt;
    (reinterpret_cast<MockRotationGesture*>(Referenced::RawPtr(peer_->gesture)))->HandleOnActionCancel(evt);
    ASSERT_TRUE(rotationEvent);
    EXPECT_EQ(rotationEvent->resourceId, RES_ID);
}
} // namespace OHOS::Ace::NG
