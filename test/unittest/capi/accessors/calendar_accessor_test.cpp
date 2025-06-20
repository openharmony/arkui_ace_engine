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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/calendar_controller_peer.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockCalendarController : public OHOS::Ace::NG::CalendarControllerNg {
public:
    MOCK_METHOD(void, BackToToday, ());
    MOCK_METHOD(void, GoTo, (int32_t, int32_t, int32_t));
};
} // namespace

class CalendarControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUICalendarControllerAccessor,
    &GENERATED_ArkUIAccessors::getCalendarControllerAccessor, CalendarControllerPeer> {
public:
    void SetUp() override
    {
        AccessorTestBase::SetUp();
        mockController_ = Referenced::MakeRefPtr<MockCalendarController>();
        ASSERT_NE(mockController_, nullptr);
        peer_->controller = mockController_;
    }

    void TearDown() override
    {
        AccessorTestBase::TearDown();
        mockController_ = nullptr;
    }

    RefPtr<MockCalendarController> mockController_ = nullptr;
};

/**
 * @tc.name: backToTodayTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarControllerAccessorTest, backToTodayTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->backToToday, nullptr);

    EXPECT_CALL(*mockController_, BackToToday()).Times(3);
    accessor_->backToToday(peer_);
    accessor_->backToToday(peer_);
    accessor_->backToToday(peer_);
}

/**
 * @tc.name: goToTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarControllerAccessorTest, goToTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->goTo, nullptr);
    const std::vector<std::tuple<int32_t, int32_t, int32_t>> testData {
        {2024, 1, 1}, {2024, 12, 31}, {0, 0, 0}
    };
    for (auto [year, month, day] : testData) {
        EXPECT_CALL(*mockController_, GoTo(year, month, day)).Times(1);
        const Ark_CalendarSelectedDate value {
            .year = Converter::ArkValue<Ark_Number>(year),
            .month = Converter::ArkValue<Ark_Number>(month),
            .day = Converter::ArkValue<Ark_Number>(day),
        };
        accessor_->goTo(peer_, &value);
    }
}
} // namespace OHOS::Ace::NG
