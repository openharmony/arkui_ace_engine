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
#include "core/interfaces/native/implementation/swipe_gesture_interface_peer.h"
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

class SwipeGestureIntrfaceAccessorTest
    : public AccessorTestBase<GENERATED_ArkUISwipeGestureInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getSwipeGestureInterfaceAccessor, SwipeGestureInterfacePeer> {
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
 * @tc.name: OnActionTest
 * @tc.desc: setOnAction test
 * @tc.type: FUNC
 */
HWTEST_F(SwipeGestureIntrfaceAccessorTest, OnActionTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = {
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