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
#include "core/interfaces/native/implementation/pan_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/pan_gesture_options_peer.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace TypeHelper;

namespace {
    int32_t ID = 123;
    constexpr int32_t DEFAULT_FINGERS = 1;
    constexpr Dimension DEFAULT_DISTANCE = 5.0_vp;
    constexpr auto DEFAULT_DIRECTION = PanDirection{};
    struct CheckEvent {
        int32_t resourceId;
    };

    const std::vector<std::pair<Ark_PanDirection, PanDirection>> TEST_PLAN_DIRECTION = {
        { Ark_PanDirection::ARK_PAN_DIRECTION_NONE, {.type = PanDirection::NONE} },
        { Ark_PanDirection::ARK_PAN_DIRECTION_HORIZONTAL, {.type = PanDirection::HORIZONTAL} },
        { Ark_PanDirection::ARK_PAN_DIRECTION_LEFT, {.type = PanDirection::LEFT} },
        { Ark_PanDirection::ARK_PAN_DIRECTION_RIGHT, {.type = PanDirection::RIGHT} },
        { Ark_PanDirection::ARK_PAN_DIRECTION_VERTICAL, {.type = PanDirection::VERTICAL} },
        { Ark_PanDirection::ARK_PAN_DIRECTION_UP, {.type = PanDirection::UP} },
        { Ark_PanDirection::ARK_PAN_DIRECTION_DOWN, {.type = PanDirection::DOWN} },
        { Ark_PanDirection::ARK_PAN_DIRECTION_ALL, {.type = PanDirection::ALL} },
        { static_cast<Ark_PanDirection>(100), {.type = PanDirection::ALL} },
    };

    constexpr double FLT_PRECISION = 0.001;
}

class MockPanGesture : public PanGesture {
public:
    MockPanGesture(int32_t fingers, const PanDirection& direction, double distance)
        : PanGesture(fingers, direction, distance) {}
    ~MockPanGesture() override = default;

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

class PanGestureInterfaceAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIPanGestureInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getPanGestureInterfaceAccessor, PanGestureInterfacePeer> {
public:
    void *CreatePeerInstance() override
    {
        auto value = Converter::ArkUnion<Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions,
            Ark_Empty>(nullptr);
        return accessor_->construct(&value);
    }
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        peer_->gesture =
            AceType::MakeRefPtr<MockPanGesture>(
                DEFAULT_FINGERS, DEFAULT_DIRECTION, DEFAULT_DISTANCE.ConvertToPx());
    }
};

/**
 * @tc.name: CtorTestFingers
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, CtorTestFingers, TestSize.Level1)
{
    const std::vector<std::pair<int32_t, int32_t>> TEST_PLAN = {
        { -10, DEFAULT_FINGERS },
        { 0, DEFAULT_FINGERS },
        { 1, 1 },
        { 10, 10 },
        { 11, DEFAULT_FINGERS },
    };
    const double someDistance = 10.0;

    for (auto& value : TEST_PLAN) {
        Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions params;
        auto& dst = WriteToUnion<Ark_PanGestureInterface_Invoke_Literal>(params);
        dst.fingers = Converter::ArkValue<Opt_Number>(value.first);
        dst.distance = Converter::ArkValue<Opt_Number>(someDistance);
        dst.direction = Converter::ArkValue<Opt_PanDirection>(Ark_PanDirection::ARK_PAN_DIRECTION_HORIZONTAL);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, (Dimension(someDistance, DimensionUnit::VP)).ConvertToPx(), FLT_PRECISION);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, PanDirection::HORIZONTAL);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN) {
        Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions params;
        auto& dst = WriteToUnion<Ark_PanGestureInterface_Invoke_Literal>(params);
        dst.fingers = Converter::ArkValue<Opt_Number>(value.first);
        dst.distance = Converter::ArkValue<Opt_Number>();
        dst.direction = Converter::ArkValue<Opt_PanDirection>();
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, DEFAULT_DISTANCE.ConvertToPx(), FLT_PRECISION);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, DEFAULT_DIRECTION.type);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestGestureOptionsFingers
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, CtorTestGestureOptionsFingers, TestSize.Level1)
{
    const std::vector<std::pair<Ark_Number, int32_t>> TEST_PLAN = {
        { Converter::ArkValue<Ark_Number>(-10), DEFAULT_FINGERS },
        { Converter::ArkValue<Ark_Number>(0), DEFAULT_FINGERS },
        { Converter::ArkValue<Ark_Number>(1), 1 },
        { Converter::ArkValue<Ark_Number>(10), 10 },
        { Converter::ArkValue<Ark_Number>(11), DEFAULT_FINGERS },
    };

    for (auto& value : TEST_PLAN) {
        auto options = PeerUtils::CreatePeer<PanGestureOptionsPeer>();
        options->handler = Referenced::MakeRefPtr<PanGestureOption>();
        fullAPI_->getAccessors()->getPanGestureOptionsAccessor()->setFingers(options, &value.first);
        auto params = Converter::ArkUnion<Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions,
            Ark_PanGestureOptions>(options);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto gestureOptions = peer->gesture->GetGestureOptions();
        ASSERT_NE(gestureOptions, nullptr);
        auto optionsFingers = gestureOptions->GetFingers();
        EXPECT_EQ(optionsFingers, value.second);
        PeerUtils::DestroyPeer(options);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestDistance
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, CtorTestDistance, TestSize.Level1)
{
    const std::vector<std::pair<double, double>> TEST_PLAN = {
        { -1.0, DEFAULT_DISTANCE.ConvertToPx() },
        { -0.05, DEFAULT_DISTANCE.ConvertToPx() },
        { 3.0, (Dimension(3.0, DimensionUnit::VP)).ConvertToPx() },
        { 5.0, (Dimension(5.0, DimensionUnit::VP)).ConvertToPx() },
        { 10.0, (Dimension(10.0, DimensionUnit::VP)).ConvertToPx() },
    };
    const double expectedFingers = 4;

    for (auto& value : TEST_PLAN) {
        Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions params;
        auto& dst = WriteToUnion<Ark_PanGestureInterface_Invoke_Literal>(params);
        dst.fingers = Converter::ArkValue<Opt_Number>(expectedFingers);
        dst.distance = Converter::ArkValue<Opt_Number>(value.first);
        dst.direction = Converter::ArkValue<Opt_PanDirection>(Ark_PanDirection::ARK_PAN_DIRECTION_HORIZONTAL);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto result = peer->gesture->GetFingers();
        EXPECT_EQ(result, expectedFingers);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, value.second, FLT_PRECISION);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, PanDirection::HORIZONTAL);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN) {
        Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions params;
        auto& dst = WriteToUnion<Ark_PanGestureInterface_Invoke_Literal>(params);
        dst.fingers = Converter::ArkValue<Opt_Number>();
        dst.distance = Converter::ArkValue<Opt_Number>(value.first);
        dst.direction = Converter::ArkValue<Opt_PanDirection>();
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto result = peer->gesture->GetFingers();
        EXPECT_EQ(result, DEFAULT_FINGERS);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, value.second, FLT_PRECISION);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, DEFAULT_DIRECTION.type);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestGestureOptionsDistance
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, CtorTestGestureOptionsDistance, TestSize.Level1)
{
    const std::vector<std::pair<Ark_Number, double>> TEST_PLAN = {
        { Converter::ArkValue<Ark_Number>(-1.0), DEFAULT_DISTANCE.ConvertToPx() },
        { Converter::ArkValue<Ark_Number>(-0.05), DEFAULT_DISTANCE.ConvertToPx() },
        { Converter::ArkValue<Ark_Number>(0.0), (Dimension(0.0, DimensionUnit::VP)).ConvertToPx() },
        { Converter::ArkValue<Ark_Number>(0.05), (Dimension(0.05, DimensionUnit::VP)).ConvertToPx() },
        { Converter::ArkValue<Ark_Number>(1.0), (Dimension(1.0, DimensionUnit::VP)).ConvertToPx() },
        { Converter::ArkValue<Ark_Number>(100.0), (Dimension(100.0, DimensionUnit::VP)).ConvertToPx() },
    };

    for (auto& value : TEST_PLAN) {
        auto options = PeerUtils::CreatePeer<PanGestureOptionsPeer>();
        options->handler = Referenced::MakeRefPtr<PanGestureOption>();
        fullAPI_->getAccessors()->getPanGestureOptionsAccessor()->setDistance(options, &value.first);
        auto params = Converter::ArkUnion<Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions,
            Ark_PanGestureOptions>(options);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, 0.0, FLT_PRECISION);
        auto gestureOptions = peer->gesture->GetGestureOptions();
        ASSERT_NE(gestureOptions, nullptr);
        auto optionsDistance = gestureOptions->GetDistance();
        EXPECT_NEAR(optionsDistance, value.second, FLT_PRECISION);
        PeerUtils::DestroyPeer(options);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestDirection
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, CtorTestDirection, TestSize.Level1)
{
    const double expectedFingers = 4;
    const double expectedDistance = 4.0;

    for (auto& value : TEST_PLAN_DIRECTION) {
        Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions params;
        auto& dst = WriteToUnion<Ark_PanGestureInterface_Invoke_Literal>(params);
        dst.fingers = Converter::ArkValue<Opt_Number>(expectedFingers);
        dst.distance = Converter::ArkValue<Opt_Number>(expectedDistance);
        dst.direction = Converter::ArkValue<Opt_PanDirection>(value.first);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto result = peer->gesture->GetFingers();
        EXPECT_EQ(result, expectedFingers);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, (Dimension(expectedDistance, DimensionUnit::VP)).ConvertToPx(), FLT_PRECISION);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, value.second.type);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN_DIRECTION) {
        Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions params;
        auto& dst = WriteToUnion<Ark_PanGestureInterface_Invoke_Literal>(params);
        dst.fingers = Converter::ArkValue<Opt_Number>();
        dst.distance = Converter::ArkValue<Opt_Number>();
        dst.direction = Converter::ArkValue<Opt_PanDirection>(value.first);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto result = peer->gesture->GetFingers();
        EXPECT_EQ(result, DEFAULT_FINGERS);
        auto distance = peer->gesture->GetDistance();
        EXPECT_NEAR(distance, DEFAULT_DISTANCE.ConvertToPx(), FLT_PRECISION);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, value.second.type);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestGestureOptionsDirection
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, CtorTestGestureOptionsDirection, TestSize.Level1)
{
    for (auto& value : TEST_PLAN_DIRECTION) {
        auto options = PeerUtils::CreatePeer<PanGestureOptionsPeer>();
        options->handler = Referenced::MakeRefPtr<PanGestureOption>();
        fullAPI_->getAccessors()->getPanGestureOptionsAccessor()->setDirection(options, value.first);
        auto params = Converter::ArkUnion<Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions,
            Ark_PanGestureOptions>(options);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto direction = peer->gesture->GetDirection();
        EXPECT_EQ(direction.type, PanDirection::ALL);
        auto gestureOptions = peer->gesture->GetGestureOptions();
        ASSERT_NE(gestureOptions, nullptr);
        auto optionsDirection = gestureOptions->GetDirection();
        EXPECT_EQ(optionsDirection.type, value.second.type);
        PeerUtils::DestroyPeer(options);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, CtorTestInvalid, TestSize.Level1)
{
    ASSERT_NE(peer_->gesture, nullptr);
    auto fingers = peer_->gesture->GetFingers();
    EXPECT_EQ(fingers, DEFAULT_FINGERS);
    auto distance = peer_->gesture->GetDistance();
    EXPECT_NEAR(distance, DEFAULT_DISTANCE.ConvertToPx(), FLT_PRECISION);
    auto direction = peer_->gesture->GetDirection();
    EXPECT_EQ(direction.type, DEFAULT_DIRECTION.type);
    auto options = peer_->gesture->GetGestureOptions();
    EXPECT_EQ(options, nullptr);
}

/**
 * @tc.name: OnActionStartTest
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, OnActionStartTest, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(testCallback, ID);
    accessor_->onActionStart(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockPanGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnActionStart(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}

/**
 * @tc.name: OnActionUpdateTest
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, OnActionUpdateTest, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(testCallback, ID);
    accessor_->onActionUpdate(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockPanGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnActionUpdate(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}

/**
 * @tc.name: OnActionEndTest
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, OnActionEndTest, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(testCallback, ID);
    accessor_->onActionEnd(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockPanGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnActionEnd(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}

/**
 * @tc.name: OnActionCancelTest
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, OnActionCancelTest, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(testCallback, ID);
    accessor_->onActionCancel0(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockPanGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnActionCancel(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}

/**
 * @tc.name: OnActionCancel1Test
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(PanGestureInterfaceAccessorTest, OnActionCancel1Test, TestSize.Level1)
{
    ASSERT_TRUE(peer_ && peer_->gesture && accessor_);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        fullAPI_->getAccessors()->getGestureEventAccessor()->destroyPeer(event);
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(testCallback, ID);
    accessor_->onActionCancel1(peer_, &arkCallback);
    GestureEvent evt;
    auto callResult =
        reinterpret_cast<MockPanGesture*>(Referenced::RawPtr(peer_->gesture))->HandleOnActionCancel(evt);
    ASSERT_TRUE(callResult);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, ID);
}
}
