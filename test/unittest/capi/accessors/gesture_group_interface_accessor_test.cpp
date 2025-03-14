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
#include "core/interfaces/native/implementation/gesture_group_interface_peer.h"
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

    bool HandleOnActionCancel()
    {
        if (onActionCancelId_) {
            (*onActionCancelId_)();
            return true;
        }
        return false;
    }
};

class GestureGroupInterfaceAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIGestureGroupInterfaceAccessor,
        &GENERATED_ArkUIAccessors::getGestureGroupInterfaceAccessor, GestureGroupInterfacePeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        gesture_ = AceType::MakeRefPtr<MockGestureGroup>(GestureMode::Sequence);
        peer_->gesture = gesture_;
    }
    RefPtr<MockGestureGroup> gesture_;
};

/**
 * @tc.name: OnCancelTest
 * @tc.desc: setOnCancel test
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupInterfaceAccessorTest, OnCancelTest, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
    };
    auto arkCallback = Converter::ArkValue<Callback_Void>(testCallback, EXPECTED_ID);
    accessor_->onCancel(peer_, &arkCallback);
    ASSERT_TRUE(gesture_->HandleOnActionCancel());
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, EXPECTED_ID);
}
}