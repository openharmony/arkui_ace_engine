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
    StatisticEventInfo event = reporter->ConvertToEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(event.subEventName, "FA_APP_START");
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

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ConvertToEvent with all event types
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ConvertToEvent002, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    // Test CALL_SET_CACHE_RANGE
    auto event1 = reporter->ConvertToEvent(StatisticEventType::CALL_SET_CACHE_RANGE);
    EXPECT_EQ(event1.eventName, "List");
    EXPECT_EQ(event1.subEventName, "CALL_SET_CACHE_RANGE");

    // Test SEARCH_ONDIDINSERT
    auto event2 = reporter->ConvertToEvent(StatisticEventType::SEARCH_ONDIDINSERT);
    EXPECT_EQ(event2.eventName, "SEARCH");
    EXPECT_EQ(event2.subEventName, "ONDIDINSERT");

    // Test SEARCH_ONWILLDELETE
    auto event3 = reporter->ConvertToEvent(StatisticEventType::SEARCH_ONWILLDELETE);
    EXPECT_EQ(event3.eventName, "SEARCH");
    EXPECT_EQ(event3.subEventName, "ONWILLDELETE");

    // Test SEARCH_ONDIDDELETE
    auto event4 = reporter->ConvertToEvent(StatisticEventType::SEARCH_ONDIDDELETE);
    EXPECT_EQ(event4.eventName, "SEARCH");
    EXPECT_EQ(event4.subEventName, "ONDIDDELETE");

    // Test CLICK_AI_MENU_PHONE_NUMBER
    auto event5 = reporter->ConvertToEvent(StatisticEventType::CLICK_AI_MENU_PHONE_NUMBER);
    EXPECT_EQ(event5.eventName, "CLICK_AI_MENU");
    EXPECT_EQ(event5.subEventName, "PHONE_NUMBER");

    // Test CLICK_AI_MENU_URL
    auto event6 = reporter->ConvertToEvent(StatisticEventType::CLICK_AI_MENU_URL);
    EXPECT_EQ(event6.eventName, "CLICK_AI_MENU");
    EXPECT_EQ(event6.subEventName, "URL");

    // Test CLICK_AI_MENU_EMAIL
    auto event7 = reporter->ConvertToEvent(StatisticEventType::CLICK_AI_MENU_EMAIL);
    EXPECT_EQ(event7.eventName, "CLICK_AI_MENU");
    EXPECT_EQ(event7.subEventName, "EMAIL");

    // Test CLICK_AI_MENU_ADDRESS
    auto event8 = reporter->ConvertToEvent(StatisticEventType::CLICK_AI_MENU_ADDRESS);
    EXPECT_EQ(event8.eventName, "CLICK_AI_MENU");
    EXPECT_EQ(event8.subEventName, "ADDRESS");

    // Test CLICK_AI_MENU_DATE_TIME
    auto event9 = reporter->ConvertToEvent(StatisticEventType::CLICK_AI_MENU_DATE_TIME);
    EXPECT_EQ(event9.eventName, "CLICK_AI_MENU");
    EXPECT_EQ(event9.subEventName, "DATE_TIME");

    // Test CLICK_AI_MENU_ASK_CELIA
    auto event10 = reporter->ConvertToEvent(StatisticEventType::CLICK_AI_MENU_ASK_CELIA);
    EXPECT_EQ(event10.eventName, "CLICK_AI_MENU");
    EXPECT_EQ(event10.subEventName, "ASK_CELIA");
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ConvertToEvent with invalid event type
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ConvertToEvent003, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    // Test with an invalid event type (larger than the last valid enum value)
    auto event = reporter->ConvertToEvent(static_cast<StatisticEventType>(999));
    EXPECT_EQ(event.eventName, "");
    EXPECT_EQ(event.subEventName, "");
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test SendEvent with existing event
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, SendEvent002, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    // Send event first time
    reporter->SendEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 1);
    EXPECT_EQ(reporter->totalEventCount_, 1);

    // Send same event again - should increment eventCount
    reporter->SendEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 1);
    EXPECT_EQ(reporter->statisitcEventMap_[StatisticEventType::FA_APP_START].eventCount, 2);
    EXPECT_EQ(reporter->totalEventCount_, 2);

    // Send same event third time
    reporter->SendEvent(StatisticEventType::FA_APP_START);
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 1);
    EXPECT_EQ(reporter->statisitcEventMap_[StatisticEventType::FA_APP_START].eventCount, 3);
    EXPECT_EQ(reporter->totalEventCount_, 3);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test SendEvent with multiple different events
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, SendEvent003, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    reporter->SendEvent(StatisticEventType::FA_APP_START);
    reporter->SendEvent(StatisticEventType::CALL_SET_CACHE_RANGE);
    reporter->SendEvent(StatisticEventType::CLICK_AI_MENU_PHONE_NUMBER);

    EXPECT_EQ(reporter->statisitcEventMap_.size(), 3);
    EXPECT_EQ(reporter->totalEventCount_, 3);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test TryReportStatisticEvents with null pipeline
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, TryReportStatisticEvents002, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    reporter->totalEventCount_ = MAX_PENDING_EVENT_COUNT;
    reporter->SendEvent(StatisticEventType::FA_APP_START);

    // Should not crash with null pipeline
    reporter->TryReportStatisticEvents(nullptr);
    EXPECT_EQ(reporter->totalEventCount_, MAX_PENDING_EVENT_COUNT + 1);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test TryReportStatisticEvents with threshold not reached
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, TryReportStatisticEvents003, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    // Set totalEventCount_ below MAX_PENDING_EVENT_COUNT
    reporter->totalEventCount_ = MAX_PENDING_EVENT_COUNT - 1;
    reporter->SendEvent(StatisticEventType::FA_APP_START);

    reporter->TryReportStatisticEvents(nullptr);
    // Event count should remain unchanged
    EXPECT_EQ(reporter->totalEventCount_, MAX_PENDING_EVENT_COUNT);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ForceReportStatisticEvents with empty map
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ForceReportStatisticEvents002, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    // statisitcEventMap_ should be empty initially
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 0);

    // ForceReportStatisticEvents should handle empty map gracefully
    reporter->ForceReportStatisticEvents();
    EXPECT_EQ(reporter->totalEventCount_, 0);
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 0);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test ForceReportStatisticEvents with multiple events
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ForceReportStatisticEvents003, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    reporter->SendEvent(StatisticEventType::FA_APP_START);
    reporter->SendEvent(StatisticEventType::CALL_SET_CACHE_RANGE);
    reporter->SendEvent(StatisticEventType::SEARCH_ONDIDINSERT);

    EXPECT_EQ(reporter->statisitcEventMap_.size(), 3);
    EXPECT_EQ(reporter->totalEventCount_, 3);

    reporter->ForceReportStatisticEvents();
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 0);
    EXPECT_EQ(reporter->totalEventCount_, 0);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test reporter initial state
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, InitialState001, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    // Check initial state
    EXPECT_EQ(reporter->totalEventCount_, 0);
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 0);
}

/**
 * @tc.name: StatisticEventReporterTest
 * @tc.desc: Test multiple calls to ForceReportStatisticEvents
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventReporterTest, ForceReportStatisticEvents004, TestSize.Level1)
{
    auto reporter = std::make_shared<StatisticEventReporter>();
    ASSERT_TRUE(reporter != nullptr);

    reporter->SendEvent(StatisticEventType::FA_APP_START);
    reporter->ForceReportStatisticEvents();
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 0);

    // Call ForceReportStatisticEvents again on empty map
    reporter->ForceReportStatisticEvents();
    EXPECT_EQ(reporter->statisitcEventMap_.size(), 0);
    EXPECT_EQ(reporter->totalEventCount_, 0);
}
} // namespace OHOS::Ace
