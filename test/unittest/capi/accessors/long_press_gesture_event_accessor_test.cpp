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
#include "core/interfaces/native/implementation/long_press_gesture_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class LongPressGestureEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUILongPressGestureEventAccessor,
        &GENERATED_ArkUIAccessors::getLongPressGestureEventAccessor, LongPressGestureEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        eventInfo_ = std::make_shared<LongPressGestureEvent>();
        peer_->SetEventInfo(eventInfo_);
    }

private:
    std::shared_ptr<LongPressGestureEvent> eventInfo_;
};

/**
 * @tc.name: GetRepeatTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LongPressGestureEventAccessorTest, GetRepeatTest, TestSize.Level1)
{
    for (auto& [input, expected, value] : AccessorTestFixtures::testFixtureBooleanValues) {
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        event->SetRepeat(value);
        Ark_Boolean arkRes = accessor_->getRepeat(peer_);
        EXPECT_EQ(arkRes, expected) <<
            "Input value is: " << input << ", method: GetRepeat";
    }
}

/**
 * @tc.name: SetRepeatTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LongPressGestureEventAccessorTest, SetRepeatTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureBooleanValues) {
        accessor_->setRepeat(peer_, value);
        auto event = peer_->GetEventInfo();
        ASSERT_NE(event, nullptr);
        EXPECT_EQ(event->GetRepeat(), expected) <<
            "Input value is: " << input << ", method: SetRepeat";
    }
}
}