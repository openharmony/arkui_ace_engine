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

struct RotationEvent {
    int32_t resourceId;
};

static const int RES_ID = 123;

class RotationGestureInterfaceAccessorTest : public AccessorTestBase<GENERATED_ArkUIRotationGestureInterfaceAccessor,
    &GENERATED_ArkUIAccessors::getRotationGestureInterfaceAccessor, RotationGestureInterfacePeer> {
        void SetUp() override
        {
            AccessorTestBase::SetUp();

            int32_t fingersNum = DEFAULT_SLIDE_FINGER;
            double angleNum = 0;
            peer_->gesture = AceType::MakeRefPtr<MockRotationGesture>(fingersNum, angleNum);
        }
    };

/**
 * @tc.name: onActionStartTest
 * @tc.desc: check work of caretPosition method
 * @tc.type: FUNC
 */
HWTEST_F(RotationGestureInterfaceAccessorTest, onActionStartTest, TestSize.Level1)
{
    static std::optional<RotationEvent> rotationEvent = std::nullopt;
    auto onActionStartFunc = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        rotationEvent = {
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
        rotationEvent = {
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
        rotationEvent = {
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
        rotationEvent = {
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
        rotationEvent = {
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