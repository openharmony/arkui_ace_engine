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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/reverse_converter.h"

// #include "core/interfaces/native/implementation/calendar_controller_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
    struct FocusControllerPeer { };
} // namespace

class FocusControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIFocusControllerAccessor,
    &GENERATED_ArkUIAccessors::requestFocus, FocusControllerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        // mockController_ = Referenced::MakeRefPtr<MockFocusController>();
        // ASSERT_NE(mockController_, nullptr);
        // peer_->controller = mockController_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        // mockController_ = nullptr;
    }

    // RefPtr<MockCalendarController> mockController_ = nullptr;
};

/**
 * @tc.name: backToTodayTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarControllerAccessorTest, backToTodayTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->requestFocus, nullptr);

    // EXPECT_CALL(*mockController_, BackToToday()).Times(3);
    // accessor_->backToToday(peer_);
    // accessor_->backToToday(peer_);
    // accessor_->backToToday(peer_);
}
} // namespace OHOS::Ace::NG
