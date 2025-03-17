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

constexpr int32_t EXPECTED_ID = 100;

struct CheckEvent {
    int32_t resourceId;
};

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
    : public AccessorTestBase<GENERATED_ArkUITapGestureInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getTapGestureInterfaceAccessor, TapGestureInterfacePeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        gesture_ = AceType::MakeRefPtr<MockTapGesture>();
        peer_->gesture = gesture_;
    }
    RefPtr<MockTapGesture> gesture_;
};

/**
 * @tc.name: onActionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TapGestureInterfaceAccessorTest, onActionTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_GestureEvent event) {
        checkEvent = {
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