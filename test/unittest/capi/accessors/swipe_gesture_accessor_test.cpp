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
#include "core/interfaces/native/implementation/swipe_gesture_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t EXPECTED_ID = 111;
struct CheckEvent {
    int32_t resourceId;
};

constexpr int32_t DEFAULT_FINGERS = 1;
constexpr double DEFAULT_SPEED = 100.0;
constexpr auto DEFAULT_DIRECTION = SwipeDirection{};
constexpr bool DEFAULT_IS_LIMIT_FINGER_COUNT = false;

void testFactoryCallback(Ark_VMContext context, const Ark_Int32 resourceId,
    const Callback_SwipeGesture_Void continuation)
{
    auto arkCallback = CallbackHelper(continuation);
    auto factoryPeer = PeerUtils::CreatePeer<SwipeGesturePeer>();
    arkCallback.InvokeSync(factoryPeer);
};
}

using namespace testing;
using namespace testing::ext;

class SwipeGestureAccessorTest
    : public AccessorTestBase<GENERATED_ArkUISwipeGestureAccessor,
        &GENERATED_ArkUIAccessors::getSwipeGestureAccessor, SwipeGesturePeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        int32_t fingersNum = DEFAULT_SLIDE_FINGER;
        double speedNum = DEFAULT_SLIDE_SPEED;
        SwipeDirection slideDirection;
        gesture_ = AceType::MakeRefPtr<SwipeGesture>(fingersNum, slideDirection, speedNum);
        peer_->gesture = gesture_;
    }
    RefPtr<SwipeGesture> gesture_;
};

/**
 * @tc.name: InstantiateTestFingers
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwipeGestureAccessorTest, InstantiateTestFingers, TestSize.Level1)
{
    const std::vector<std::pair<int32_t, int32_t>> TEST_PLAN = {
        { -10, DEFAULT_FINGERS },
        { 0, DEFAULT_FINGERS },
        { 1, 1 },
        { 10, 10 },
        { 11, 11 },
    };

    auto arkCallback = Converter::ArkValue<Callback_SwipeGesture>(nullptr, testFactoryCallback, EXPECTED_ID);

    for (auto& value : TEST_PLAN) {
        Ark_SwipeGestureHandlerOptions params;
        params.fingers = Converter::ArkValue<Opt_Number>(value.first);
        params.direction = Converter::ArkValue<Opt_SwipeDirection>();
        params.speed = Converter::ArkValue<Opt_Number>();
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>();
        auto optParam = Converter::ArkValue<Opt_SwipeGestureHandlerOptions>(params);
        auto peer = accessor_->$_instantiate(&arkCallback, &optParam);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, DEFAULT_DIRECTION.type);
        auto speed = peer->gesture->GetSpeed();
        EXPECT_FLOAT_EQ(speed, DEFAULT_SPEED);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
    }
}

/**
 * @tc.name: InstantiateTestDirection
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwipeGestureAccessorTest, InstantiateTestDirection, TestSize.Level1)
{
    const std::vector<std::pair<Ark_SwipeDirection, SwipeDirection>> TEST_PLAN = {
        { ARK_SWIPE_DIRECTION_NONE, { .type = SwipeDirection::NONE } },
        { static_cast<Ark_SwipeDirection>(100), { .type = SwipeDirection::ALL } },
        { ARK_SWIPE_DIRECTION_HORIZONTAL, { .type = SwipeDirection::HORIZONTAL } },
        { ARK_SWIPE_DIRECTION_VERTICAL, { .type = SwipeDirection::VERTICAL } },
        { ARK_SWIPE_DIRECTION_ALL, { .type = SwipeDirection::ALL } },
    };

    auto arkCallback = Converter::ArkValue<Callback_SwipeGesture>(nullptr, testFactoryCallback, EXPECTED_ID);

    for (auto& value : TEST_PLAN) {
        Ark_SwipeGestureHandlerOptions params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.direction = Converter::ArkValue<Opt_SwipeDirection>(value.first);
        params.speed = Converter::ArkValue<Opt_Number>();
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>();
        auto optParam = Converter::ArkValue<Opt_SwipeGestureHandlerOptions>(params);
        auto peer = accessor_->$_instantiate(&arkCallback, &optParam);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, value.second.type);
        auto speed = peer->gesture->GetSpeed();
        EXPECT_FLOAT_EQ(speed, DEFAULT_SPEED);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
    }
}

/**
 * @tc.name: InstantiateTestSpeed
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwipeGestureAccessorTest, InstantiateTestSpeed, TestSize.Level1)
{
    const std::vector<std::pair<double, double>> TEST_PLAN = {
        { -10.0, DEFAULT_SPEED },
        { 10.0, 10.0 },
        { 100.0, 100.0 },
        { 200.05, 200.05 },
        { 0.0, DEFAULT_SPEED },
    };

    auto arkCallback = Converter::ArkValue<Callback_SwipeGesture>(nullptr, testFactoryCallback, EXPECTED_ID);

    for (auto& value : TEST_PLAN) {
        Ark_SwipeGestureHandlerOptions params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.direction = Converter::ArkValue<Opt_SwipeDirection>();
        params.speed = Converter::ArkValue<Opt_Number>(value.first);
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>();
        auto optParam = Converter::ArkValue<Opt_SwipeGestureHandlerOptions>(params);
        auto peer = accessor_->$_instantiate(&arkCallback, &optParam);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, DEFAULT_DIRECTION.type);
        auto speed = peer->gesture->GetSpeed();
        EXPECT_FLOAT_EQ(speed, value.second);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
    }
}

/**
 * @tc.name: InstantiateTestFingerCountLimited
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwipeGestureAccessorTest, InstantiateTestFingerCountLimited, TestSize.Level1)
{
    const std::vector<std::pair<bool, bool>> TEST_PLAN = {
        { true, true },
        { false, false },
        { true, true },
    };

    auto arkCallback = Converter::ArkValue<Callback_SwipeGesture>(nullptr, testFactoryCallback, EXPECTED_ID);

    for (auto& value : TEST_PLAN) {
        Ark_SwipeGestureHandlerOptions params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.direction = Converter::ArkValue<Opt_SwipeDirection>();
        params.speed = Converter::ArkValue<Opt_Number>();
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>(value.first);
        auto optParam = Converter::ArkValue<Opt_SwipeGestureHandlerOptions>(params);
        auto peer = accessor_->$_instantiate(&arkCallback, &optParam);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, DEFAULT_DIRECTION.type);
        auto speed = peer->gesture->GetSpeed();
        EXPECT_FLOAT_EQ(speed, DEFAULT_SPEED);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, value.second);
    }
}

/**
 * @tc.name: InstantiateTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwipeGestureAccessorTest, InstantiateTestInvalid, TestSize.Level1)
{
    auto arkCallback = Converter::ArkValue<Callback_SwipeGesture>(nullptr, testFactoryCallback, EXPECTED_ID);
    auto optParam = Converter::ArkValue<Opt_SwipeGestureHandlerOptions>();
    auto peer = accessor_->$_instantiate(&arkCallback, &optParam);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->gesture, nullptr);
    auto fingers = peer->gesture->GetFingers();
    EXPECT_EQ(fingers, DEFAULT_FINGERS);
    auto direction = peer->gesture->GetDirection();
    EXPECT_EQ(direction.type, DEFAULT_DIRECTION.type);
    auto speed = peer->gesture->GetSpeed();
    EXPECT_FLOAT_EQ(speed, DEFAULT_SPEED);
    auto limitFingerCount = peer->gesture->GetLimitFingerCount();
    EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
}

/**
 * @tc.name: OnActionTest
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(SwipeGestureAccessorTest, OnActionTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, testCallback, EXPECTED_ID);
    accessor_->onAction(peer_, &arkCallback);
    auto func = gesture_->GetOnActionId();
    ASSERT_NE(func, nullptr);
    GestureEvent evt;
    (*func)(evt);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}
}
