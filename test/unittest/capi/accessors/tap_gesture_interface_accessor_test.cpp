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
#include "core/interfaces/native/implementation/tap_gesture_interface_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    constexpr int32_t EXPECTED_ID = 100;
    struct CheckEvent {
        int32_t resourceId;
    };
    constexpr int32_t DEFAULT_FINGERS = 1;
    constexpr int32_t DEFAULT_COUNT = 1;
    constexpr double DEFAULT_DISTANCE = std::numeric_limits<double>::infinity();
    constexpr bool DEFAULT_IS_LIMIT_FINGER_COUNT = false;
    constexpr double FLT_PRECISION = 0.00001;
    const std::vector<std::pair<int32_t, int32_t>> TEST_PLAN_FINGERS = {
        { -10, DEFAULT_FINGERS },
        { 0, DEFAULT_FINGERS },
        { 1, 1 },
        { 10, 10 },
        { 11, 11 },
    };

    const std::vector<std::pair<Ark_Number, double>> TEST_PLAN_DISTANCE = {
        { Converter::ArkValue<Ark_Number>(0.0), 0.0 },
        { Converter::ArkValue<Ark_Number>(0.05), 0.05 },
        { Converter::ArkValue<Ark_Number>(1.0), 1.0 },
        { Converter::ArkValue<Ark_Number>(100.0), 100.0 },
    };

    const std::vector<std::pair<int32_t, int32_t>> TEST_PLAN_COUNT = {
        { -10, DEFAULT_COUNT },
        { 0, DEFAULT_COUNT },
        { 1, 1 },
        { 100, 100 },
    };
}

class MockTapGesture : public TapGesture {
public:
    MockTapGesture() : TapGesture(1, 1) {}
    ~MockTapGesture() override = default;

    bool HandleSetOnActionId(GestureEvent& event)
    {
        if (onActionId_) {
            (*onActionId_)(event);
            return true;
        }
        return false;
    }
};

class TapGestureInterfaceAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUITapGestureInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getTapGestureInterfaceAccessor, TapGestureInterfacePeer> {
public:
    void *CreatePeerInstance() override
    {
        Ark_TapGestureParameters value{};
        return accessor_->construct(&value);
    }
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        gesture_ = AceType::MakeRefPtr<MockTapGesture>();
        peer_->gesture = gesture_;
    }
    RefPtr<MockTapGesture> gesture_;
};

/**
 * @tc.name: CtorTestFingers
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapGestureInterfaceAccessorTest, CtorTestFingers, TestSize.Level1)
{
    const double distance = 10.0;
    bool isFingerCountLimited = true;
    int32_t count = 5;

    for (auto& value : TEST_PLAN_FINGERS) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>(value.first);
        params.count = Converter::ArkValue<Opt_Number>(count);
        params.distanceThreshold = Converter::ArkValue<Opt_Number>(distance);
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>(isFingerCountLimited);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, count);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_NEAR(distanceThreshold, (Dimension(distance, DimensionUnit::VP)).ConvertToPx(), FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, isFingerCountLimited);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN_FINGERS) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>(value.first);
        params.count = Converter::ArkValue<Opt_Number>();
        params.distanceThreshold = Converter::ArkValue<Opt_Number>();
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>();
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, value.second);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, DEFAULT_COUNT);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_EQ(distanceThreshold, DEFAULT_DISTANCE);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestCount
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapGestureInterfaceAccessorTest, CtorTestCount, TestSize.Level1)
{
    const int32_t fingerCount = 3;
    const double distance = 10.0;
    bool isFingerCountLimited = true;

    for (auto& value : TEST_PLAN_COUNT) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>(fingerCount);
        params.count = Converter::ArkValue<Opt_Number>(value.first);
        params.distanceThreshold = Converter::ArkValue<Opt_Number>(distance);
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>(isFingerCountLimited);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, fingerCount);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, value.second);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_NEAR(distanceThreshold, (Dimension(distance, DimensionUnit::VP)).ConvertToPx(), FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, isFingerCountLimited);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN_COUNT) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.count = Converter::ArkValue<Opt_Number>(value.first);
        params.distanceThreshold = Converter::ArkValue<Opt_Number>();
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>();
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, value.second);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_EQ(distanceThreshold, DEFAULT_DISTANCE);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestDistance
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapGestureInterfaceAccessorTest, CtorTestDistance, TestSize.Level1)
{
    const int32_t fingerCount = 3;
    const int32_t count = 5;
    bool isFingerCountLimited = true;

    for (auto& value : TEST_PLAN_DISTANCE) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>(fingerCount);
        params.count = Converter::ArkValue<Opt_Number>(count);
        params.distanceThreshold = Converter::ArkValue<Opt_Number>(value.first);
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>(isFingerCountLimited);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, fingerCount);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, count);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_NEAR(distanceThreshold, (Dimension(value.second, DimensionUnit::VP)).ConvertToPx(), FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, isFingerCountLimited);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN_DISTANCE) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.count = Converter::ArkValue<Opt_Number>();
        params.distanceThreshold = Converter::ArkValue<Opt_Number>(value.first);
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>();
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, DEFAULT_COUNT);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_NEAR(distanceThreshold, value.second, FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestDistanceInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapGestureInterfaceAccessorTest, CtorTestDistanceInvalid, TestSize.Level1)
{
    const std::vector<std::pair<Ark_Number, double>> TEST_PLAN = {
        { Converter::ArkValue<Ark_Number>(-1.0), DEFAULT_DISTANCE },
        { Converter::ArkValue<Ark_Number>(-0.05), DEFAULT_DISTANCE },
    };
    const int32_t fingerCount = 3;
    const int32_t count = 5;
    bool isFingerCountLimited = true;

    for (auto& value : TEST_PLAN) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>(fingerCount);
        params.count = Converter::ArkValue<Opt_Number>(count);
        params.distanceThreshold = Converter::ArkValue<Opt_Number>(value.first);
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>(isFingerCountLimited);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, fingerCount);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, count);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_EQ(distanceThreshold, value.second);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, isFingerCountLimited);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.count = Converter::ArkValue<Opt_Number>(value.first);
        params.distanceThreshold = Converter::ArkValue<Opt_Number>();
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>();
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, DEFAULT_COUNT);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_EQ(distanceThreshold, value.second);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestFingerCountLimited
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapGestureInterfaceAccessorTest, CtorTestFingerCountLimited, TestSize.Level1)
{
    const std::vector<std::pair<Ark_Boolean, bool>> TEST_PLAN = {
        { Converter::ArkValue<Ark_Boolean>(true), true },
        { Converter::ArkValue<Ark_Boolean>(false), false },
    };
    const int32_t fingerCount = 3;
    const int32_t count = 5;
    const double distance = 10.0;

    for (auto& value : TEST_PLAN) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>(fingerCount);
        params.count = Converter::ArkValue<Opt_Number>(count);
        params.distanceThreshold = Converter::ArkValue<Opt_Number>(distance);
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>(value.first);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, fingerCount);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, count);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_NEAR(distanceThreshold, (Dimension(distance, DimensionUnit::VP)).ConvertToPx(), FLT_PRECISION);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, value.second);
        finalyzer_(peer);
    }

    for (auto& value : TEST_PLAN) {
        Ark_TapGestureParameters params;
        params.fingers = Converter::ArkValue<Opt_Number>();
        params.count = Converter::ArkValue<Opt_Number>();
        params.distanceThreshold = Converter::ArkValue<Opt_Number>();
        params.isFingerCountLimited = Converter::ArkValue<Opt_Boolean>(value.first);
        auto peer = accessor_->construct(&params);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto fingers = peer->gesture->GetFingers();
        EXPECT_EQ(fingers, DEFAULT_FINGERS);
        auto tapCount = peer->gesture->GetTapCount();
        EXPECT_EQ(tapCount, DEFAULT_COUNT);
        auto distanceThreshold = peer->gesture->GetDistanceThreshold();
        EXPECT_EQ(distanceThreshold, DEFAULT_DISTANCE);
        auto limitFingerCount = peer->gesture->GetLimitFingerCount();
        EXPECT_EQ(limitFingerCount, value.second);
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapGestureInterfaceAccessorTest, CtorTestInvalid, TestSize.Level1)
{
    auto peer = accessor_->construct(nullptr);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->gesture, nullptr);
    auto fingers = peer->gesture->GetFingers();
    EXPECT_EQ(fingers, DEFAULT_FINGERS);
    auto tapCount = peer->gesture->GetTapCount();
    EXPECT_EQ(tapCount, DEFAULT_COUNT);
    auto distanceThreshold = peer->gesture->GetDistanceThreshold();
    EXPECT_EQ(distanceThreshold, DEFAULT_DISTANCE);
    auto limitFingerCount = peer->gesture->GetLimitFingerCount();
    EXPECT_EQ(limitFingerCount, DEFAULT_IS_LIMIT_FINGER_COUNT);
    finalyzer_(peer);
}

/**
 * @tc.name: onActionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapGestureInterfaceAccessorTest, onActionTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_GestureEvent_Void>(nullptr, testCallback, EXPECTED_ID);
    accessor_->onAction(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleSetOnActionId(evt));
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}
} // namespace OHOS::Ace::NG
