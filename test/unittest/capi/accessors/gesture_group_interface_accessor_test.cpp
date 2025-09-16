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
#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/implementation/gesture_group_interface_peer.h"
#include "core/interfaces/native/implementation/long_press_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/tap_gesture_interface_peer.h"
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
}
using namespace testing;
using namespace testing::ext;

class MockGestureGroup : public GestureGroup {
public:
    explicit MockGestureGroup(GestureMode mode) : GestureGroup(mode) {}
    ~MockGestureGroup() override = default;

    bool HandleOnActionCancel(GestureEvent& event)
    {
        if (onActionCancelId_) {
            (*onActionCancelId_)(event);
            return true;
        }
        return false;
    }
};

class GestureGroupInterfaceAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIGestureGroupInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getGestureGroupInterfaceAccessor, GestureGroupInterfacePeer> {
public:
    void *CreatePeerInstance() override
    {
        Ark_GestureMode mode = ARK_GESTURE_MODE_SEQUENCE;
        Array_GestureType gesture{};
        return accessor_->construct(mode, &gesture);
    }
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        gesture_ = AceType::MakeRefPtr<MockGestureGroup>(GestureMode::Sequence);
        peer_->gesture = gesture_;
    }
    RefPtr<MockGestureGroup> gesture_;
};

/**
 * @tc.name: CtorTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupInterfaceAccessorTest, CtorTestInvalid, TestSize.Level1)
{
    auto peer = accessor_->construct(static_cast<Ark_GestureMode>(100), nullptr);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->gesture, nullptr);
    auto mode = peer->gesture->GetMode();
    EXPECT_EQ(mode, GestureMode::Sequence);
    std::vector<RefPtr<Gesture>> gestures = peer->gesture->GetGestures();
    EXPECT_TRUE(gestures.empty());
    finalyzer_(peer);
}

/**
 * @tc.name: CtorTestMode
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupInterfaceAccessorTest, CtorTestMode, TestSize.Level1)
{
    const std::vector<std::pair<Ark_GestureMode, GestureMode>> TEST_PLAN = {
        { Ark_GestureMode::ARK_GESTURE_MODE_EXCLUSIVE, GestureMode::Exclusive },
        { Ark_GestureMode::ARK_GESTURE_MODE_PARALLEL, GestureMode::Parallel },
        { Ark_GestureMode::ARK_GESTURE_MODE_SEQUENCE, GestureMode::Sequence },
    };

    for (auto& value : TEST_PLAN) {
        auto peer = accessor_->construct(value.first, nullptr);
        ASSERT_NE(peer, nullptr);
        ASSERT_NE(peer->gesture, nullptr);
        auto mode = peer->gesture->GetMode();
        EXPECT_EQ(mode, value.second);
        std::vector<RefPtr<Gesture>> gestures = peer->gesture->GetGestures();
        EXPECT_TRUE(gestures.empty());
        finalyzer_(peer);
    }
}

/**
 * @tc.name: CtorTestGestures
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupInterfaceAccessorTest, CtorTestGestures, TestSize.Level1)
{
    Ark_GestureMode someMode = Ark_GestureMode::ARK_GESTURE_MODE_PARALLEL;
    std::vector<Ark_GestureType> vectorData;
    std::vector<GestureTypeName> vectorGestureType;

    auto tapGestureInterfacePeer = fullAPI_->getAccessors()->getTapGestureInterfaceAccessor()->construct(nullptr);
    vectorData.push_back(Converter::ArkUnion<Ark_GestureType, Ark_Gesture>(tapGestureInterfacePeer));
    vectorGestureType.push_back(GestureTypeName::TAP_GESTURE);

    auto longPressGestureInterfacePeer =
        fullAPI_->getAccessors()->getLongPressGestureInterfaceAccessor()->construct(nullptr);
    vectorData.push_back(Converter::ArkUnion<Ark_GestureType, Ark_Gesture>(longPressGestureInterfacePeer));
    vectorGestureType.push_back(GestureTypeName::LONG_PRESS_GESTURE);

    Converter::ArkArrayHolder<Array_GestureType> vectorHolder(vectorData);
    Array_GestureType gestureArray = vectorHolder.ArkValue();

    auto peer = accessor_->construct(someMode, &gestureArray);
    ASSERT_NE(peer, nullptr);
    ASSERT_NE(peer->gesture, nullptr);
    auto mode = peer->gesture->GetMode();
    EXPECT_EQ(mode, GestureMode::Parallel);
    std::vector<RefPtr<Gesture>> gestures = peer->gesture->GetGestures();
    EXPECT_EQ(gestures.size(), vectorData.size());
    EXPECT_EQ(gestures.size(), vectorGestureType.size());
    for (int i = 0; i < vectorGestureType.size(); i++) {
        ASSERT_NE(gestures[i], nullptr);
        auto typeOpt = gestures[i]->GetType();
        ASSERT_TRUE(typeOpt.has_value());
        EXPECT_EQ(typeOpt.value(), vectorGestureType[i]);
    }
    PeerUtils::DestroyPeer(tapGestureInterfacePeer);
    PeerUtils::DestroyPeer(longPressGestureInterfacePeer);
    finalyzer_(peer);
}

/**
 * @tc.name: OnCancelTest
 * @tc.desc: setOnCancel test
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupInterfaceAccessorTest, OnCancelTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(testCallback, EXPECTED_ID);
    accessor_->onCancel(peer_, &arkCallback);
    GestureEvent evt;
    ASSERT_TRUE(gesture_->HandleOnActionCancel(evt));
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}
}
