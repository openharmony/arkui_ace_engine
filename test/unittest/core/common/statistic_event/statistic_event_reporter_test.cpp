/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/common/ace_application_info.h"
#include "core/common/statistic_event_reporter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t MAX_PENDING_EVENT_COUNT = 20;
}
class StatisticEventReporterTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void StatisticEventReporterTest::SetUpTestSuite()
{
}

void StatisticEventReporterTest::TearDownTestSuite()
{
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ConvertToEventName
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ConvertToEventName001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    std::string eventName = reporter->ConvertToEventName(StatisticEventType::FA_APP_START);
    EXPECT_EQ(eventName, "FA_APP_START");
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test SendEvent
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, SendEvent001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    reporter->SendEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 1);
    EXPECT_EQ(reporter->totalEventCount_, 1);
    reporter->SendEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(reporter->statisitcEventMap_[StatisticEventType::FA_APP_START].eventCount, 2);
    EXPECT_EQ(reporter->totalEventCount_, 2);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ReportStatisticEvents
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ReportStatisticEvents001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    std::map<StatisticEventType, StatisticEventInfo> events;
    reporter->ReportStatisticEvents(events);
    EXPECT_EQ(reporter->appInfo_.bundleName, AceApplicationInfo::GetInstance().GetPackageName());
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test TryReportStatisticEvents
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, TryReportStatisticEvents001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    reporter->totalEventCount_ = MAX_PENDING_EVENT_COUNT - 1;
    reporter->TryReportStatisticEvents(nullptr);
    EXPECT_EQ(reporter->totalEventCount_, MAX_PENDING_EVENT_COUNT - 1);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ForceReportStatisticEvents
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ForceReportStatisticEvents001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);
    reporter->SendEvent(StatisticEventType::FA_APP_START);

    reporter->ForceReportStatisticEvents();
    EXPECT_EQ(reporter->totalEventCount_, 0);
}
} // namespace OHOS::Ace
