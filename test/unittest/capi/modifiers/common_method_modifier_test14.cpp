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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/implementation/long_press_gesture_event_peer.h"
#include "core/interfaces/native/implementation/pan_gesture_event_peer.h"
#include "core/interfaces/native/implementation/pinch_gesture_event_peer.h"
#include "core/interfaces/native/implementation/rotation_gesture_event_peer.h"
#include "core/interfaces/native/implementation/swipe_gesture_event_peer.h"
#include "core/interfaces/native/implementation/tap_gesture_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "generated/type_helpers.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "test/unittest/capi/stubs/mock_gestures.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class MockTapGestureModel : public TapGestureModelNG {
public:
    MOCK_METHOD(void, Create, (int32_t, int32_t, double));
};

class MockLongPressGestureModel : public LongPressGestureModelNG {
public:
    MOCK_METHOD(void, Create, (int32_t, bool, int32_t));
};

class MockPanGestureModel : public PanGestureModelNG {
public:
    MOCK_METHOD(void, Create, (int32_t, const PanDirection&, double));
};

class MockPinchGestureModel : public PinchGestureModelNG {
public:
    MOCK_METHOD(void, Create, (int32_t, double));
};

class MockSwipeGestureModel : public SwipeGestureModelNG {
public:
    MOCK_METHOD(void, Create, (int32_t, const SwipeDirection&, double));
};

class MockRotationGestureModel : public RotationGestureModelNG {
public:
    MOCK_METHOD(void, Create, (int32_t, double));
};

class CommonMethodModifierTest14 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: gesture_Tap_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest14, DISABLED_gesture_Tap_Test, TestSize.Level1)
{
    MockTapGestureModel* mockModel = new MockTapGestureModel();
    TapGestureModelNG::SetMock(mockModel);
    EXPECT_CALL(*mockModel, Create(_, _, _)).Times(3);

    TapGestureEventPeer peer;
    auto event = std::make_shared<TapGestureEvent>();
    event->SetFingerList({ FingerInfo() });
    peer.SetEventInfo(event);

    Ark_TapGestureInterface interface = { };
    Ark_GestureType type = Converter::ArkUnion<Ark_GestureType, Ark_TapGestureInterface>(interface);
    Opt_GestureMask mask = { .value = Ark_GestureMask::ARK_GESTURE_MASK_NORMAL };
    modifier_->setGesture(node_, &type, &mask);
    modifier_->setPriorityGesture(node_, &type, &mask);
    modifier_->setParallelGesture(node_, &type, &mask);
    TapGestureModelNG::SetMock(nullptr);
    delete mockModel;
}

/*
 * @tc.name: gesture_LongPress_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest14, DISABLED_gesture_LongPress_Test, TestSize.Level1)
{
    MockLongPressGestureModel* mockModel = new MockLongPressGestureModel();
    LongPressGestureModelNG::SetMock(mockModel);
    EXPECT_CALL(*mockModel, Create(_, _, _)).Times(3);

    LongPressGestureEventPeer peer;
    auto event = std::make_shared<LongPressGestureEvent>();
    event->SetFingerList({ FingerInfo() });
    peer.SetEventInfo(event);

    Ark_LongPressGestureInterface interface = {  };
    Ark_GestureType type = Converter::ArkUnion<Ark_GestureType, Ark_LongPressGestureInterface>(interface);
    Opt_GestureMask mask = { .value = Ark_GestureMask::ARK_GESTURE_MASK_NORMAL };
    modifier_->setGesture(node_, &type, &mask);
    modifier_->setPriorityGesture(node_, &type, &mask);
    modifier_->setParallelGesture(node_, &type, &mask);
    LongPressGestureModelNG::SetMock(nullptr);
    delete mockModel;
}

/*
 * @tc.name: gesture_Pan_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest14, DISABLED_gesture_Pan_Test, TestSize.Level1)
{
    MockPanGestureModel* mockModel = new MockPanGestureModel();
    PanGestureModelNG::SetMock(mockModel);
    EXPECT_CALL(*mockModel, Create(_, _, _)).Times(3);

    PanGestureEventPeer peer;
    auto event = std::make_shared<PanGestureEvent>();
    event->SetFingerList({ FingerInfo(), FingerInfo() });
    peer.SetEventInfo(event);

    Ark_PanGestureInterface interface = {  };
    Ark_GestureType type = Converter::ArkUnion<Ark_GestureType, Ark_PanGestureInterface>(interface);
    Opt_GestureMask mask = { .value = Ark_GestureMask::ARK_GESTURE_MASK_NORMAL };
    modifier_->setGesture(node_, &type, &mask);
    modifier_->setPriorityGesture(node_, &type, &mask);
    modifier_->setParallelGesture(node_, &type, &mask);
    PanGestureModelNG::SetMock(nullptr);
    delete mockModel;
}

/*
 * @tc.name: gesture_Pinch_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest14, DISABLED_gesture_Pinch_Test, TestSize.Level1)
{
    auto mockModel = new MockPinchGestureModel();
    PinchGestureModelNG::SetMock(mockModel);
    EXPECT_CALL(*mockModel, Create(_, _)).Times(3);

    PinchGestureEventPeer peer;
    auto event = std::make_shared<PinchGestureEvent>();
    event->SetFingerList({ FingerInfo(), FingerInfo() });
    peer.SetEventInfo(event);

    Ark_PinchGestureInterface interface = {  };
    Ark_GestureType type = Converter::ArkUnion<Ark_GestureType, Ark_PinchGestureInterface>(interface);
    Opt_GestureMask mask = { .value = Ark_GestureMask::ARK_GESTURE_MASK_NORMAL };
    modifier_->setGesture(node_, &type, &mask);
    modifier_->setPriorityGesture(node_, &type, &mask);
    modifier_->setParallelGesture(node_, &type, &mask);
    PinchGestureModelNG::SetMock(nullptr);
    delete mockModel;
}

/*
 * @tc.name: gesture_Swipe_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest14, DISABLED_gesture_Swipe_Test, TestSize.Level1)
{
    auto mockModel = new MockSwipeGestureModel();
    SwipeGestureModelNG::SetMock(mockModel);
    EXPECT_CALL(*mockModel, Create(_, _, _)).Times(3);

    SwipeGestureEventPeer peer;
    auto event = std::make_shared<SwipeGestureEvent>();
    event->SetFingerList({ FingerInfo() });
    peer.SetEventInfo(event);

    Ark_SwipeGestureInterface interface = {  };
    Ark_GestureType type = Converter::ArkUnion<Ark_GestureType, Ark_SwipeGestureInterface>(interface);
    Opt_GestureMask mask = { .value = Ark_GestureMask::ARK_GESTURE_MASK_NORMAL };
    modifier_->setGesture(node_, &type, &mask);
    modifier_->setPriorityGesture(node_, &type, &mask);
    modifier_->setParallelGesture(node_, &type, &mask);
    SwipeGestureModelNG::SetMock(nullptr);
    delete mockModel;
}

/*
 * @tc.name: gesture_Rotation_Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest14, DISABLED_gesture_Rotation_Test, TestSize.Level1)
{
    auto mockModel = new MockRotationGestureModel();
    RotationGestureModelNG::SetMock(mockModel);
    EXPECT_CALL(*mockModel, Create(_, _)).Times(3);

    RotationGestureEventPeer peer;
    auto event = std::make_shared<RotationGestureEvent>();
    event->SetFingerList({ FingerInfo(), FingerInfo() });
    event->SetAngle(10);
    peer.SetEventInfo(event);

    Ark_RotationGestureInterface interface = {  };
    Ark_GestureType type = Converter::ArkUnion<Ark_GestureType, Ark_RotationGestureInterface>(interface);
    Opt_GestureMask mask = { .value = Ark_GestureMask::ARK_GESTURE_MASK_NORMAL };
    modifier_->setGesture(node_, &type, &mask);
    modifier_->setPriorityGesture(node_, &type, &mask);
    modifier_->setParallelGesture(node_, &type, &mask);
    RotationGestureModelNG::SetMock(nullptr);
    delete mockModel;
}
}