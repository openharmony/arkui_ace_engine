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

#include "common_statistic_event.h"
#include "statistic_event_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
}
class StatisticEventManagerTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void StatisticEventManagerTest::SetUpTestSuite()
{
}

void StatisticEventManagerTest::TearDownTestSuite()
{
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test AggregateEvent
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, AggregateEvent001, TestSize.Level1)
{
    std::string eventName = "FA_APP_START";
    StatisticEvent event(eventName);
    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);
    StatisticEventInfoParcel newEventInfo(eventName, "FA", 10);
    event.AggregateEvent(newAppInfo, newEventInfo);
    EXPECT_EQ(event.eventCounts_.size(), 1);
    EXPECT_EQ(event.extraInfos_.size(), 1);
    EXPECT_EQ(event.eventCounts_[0], 10);

    event.AggregateEvent(newAppInfo, newEventInfo);
    EXPECT_EQ(event.eventCounts_.size(), 1);
    EXPECT_EQ(event.extraInfos_.size(), 1);
    EXPECT_EQ(event.eventCounts_[0], 20);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test AggregateEvent
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, AggregateEvent002, TestSize.Level1)
{
    std::string eventName = "FA_APP_START";
    StatisticEvent event(eventName);
    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);
    StatisticEventInfoParcel newEventInfo(eventName, "FA", 10);
    event.AggregateEvent(newAppInfo, newEventInfo);
    EXPECT_EQ(event.eventCounts_.size(), 1);
    EXPECT_EQ(event.eventCounts_[0], 10);
    EXPECT_EQ(event.extraInfos_.size(), 1);

    StatisticEventInfoParcel newEventInfo2(eventName, "WEB", 10);
    event.AggregateEvent(newAppInfo, newEventInfo2);
    EXPECT_EQ(event.eventCounts_.size(), 2);
    EXPECT_EQ(event.eventCounts_[1], 10);
    EXPECT_EQ(event.extraInfos_.size(), 2);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test SendStatisticEvents
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, SendStatisticEvents001, TestSize.Level1)
{
    DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.clear();
    
    std::string bundleName = "";
    AppInfoParcel newAppInfo(bundleName);
    std::string eventName = "";
    StatisticEventInfoParcel newEventInfo(eventName, "", 1);
    std::vector<StatisticEventInfoParcel> eventInfos;
    eventInfos.emplace_back(newEventInfo);
    DelayedSingleton<StatisticEventManager>::GetInstance()->SendStatisticEvents(
        newAppInfo, eventInfos);
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), 1);

    DelayedSingleton<StatisticEventManager>::GetInstance()->SendStatisticEvents(
        newAppInfo, eventInfos);
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), 1);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test ReportTimedStatisticEvent
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, ReportTimedStatisticEvent001, TestSize.Level1)
{
    DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.clear();
    DelayedSingleton<StatisticEventManager>::GetInstance()->timedSet_.clear();
    DelayedSingleton<StatisticEventManager>::GetInstance()->defaultReportInterval_ = 101;

    std::string bundleName = "";
    AppInfoParcel newAppInfo(bundleName);
    std::string eventName = "FA_APP_START";
    StatisticEventInfoParcel newEventInfo(eventName, "", 1);
    std::vector<StatisticEventInfoParcel> eventInfos;
    eventInfos.emplace_back(newEventInfo);
    DelayedSingleton<StatisticEventManager>::GetInstance()->SendStatisticEvents(
        newAppInfo, eventInfos);

    DelayedSingleton<StatisticEventManager>::GetInstance()->ReportTimedStatisticEvent(100);
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), 1);

    DelayedSingleton<StatisticEventManager>::GetInstance()->ReportTimedStatisticEvent(101);
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), 0);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test AggregateEvent with max pending count
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, AggregateEvent003, TestSize.Level1)
{
    std::string eventName = "TestEvent";
    StatisticEvent event(eventName);
    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);

    // Add 50 events to reach MAX_PENDING_EVENT_COUNT
    for (int i = 0; i < 50; i++) {
        std::string subEventName = "SubEvent" + std::to_string(i);
        StatisticEventInfoParcel newEventInfo(eventName, subEventName, 1);
        bool isReported = event.AggregateEvent(newAppInfo, newEventInfo);
        if (i < 49) {
            EXPECT_FALSE(isReported);
        } else {
            EXPECT_TRUE(isReported);
        }
    }
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test SendStatisticEvents with invalid event name length
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, SendStatisticEvents002, TestSize.Level1)
{
    DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.clear();

    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);

    // Test event name exceeding max length
    std::string longEventName(101, 'A'); // MAX_EVENT_NAME_LENGTH is 100
    StatisticEventInfoParcel newEventInfo(longEventName, "SubEvent", 1);
    std::vector<StatisticEventInfoParcel> eventInfos;
    eventInfos.emplace_back(newEventInfo);

    size_t initialSize = DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size();
    DelayedSingleton<StatisticEventManager>::GetInstance()->SendStatisticEvents(
        newAppInfo, eventInfos);
    // Event should not be added due to invalid length
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), initialSize);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test SendStatisticEvents with invalid sub event name length
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, SendStatisticEvents003, TestSize.Level1)
{
    DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.clear();

    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);

    // Test sub event name exceeding max length
    std::string longSubEventName(101, 'B'); // MAX_EVENT_NAME_LENGTH is 100
    StatisticEventInfoParcel newEventInfo("ValidEvent", longSubEventName, 1);
    std::vector<StatisticEventInfoParcel> eventInfos;
    eventInfos.emplace_back(newEventInfo);

    size_t initialSize = DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size();
    DelayedSingleton<StatisticEventManager>::GetInstance()->SendStatisticEvents(
        newAppInfo, eventInfos);
    // Event should not be added due to invalid length
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), initialSize);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test SendStatisticEvents with max event map size
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, SendStatisticEvents004, TestSize.Level1)
{
    auto manager = DelayedSingleton<StatisticEventManager>::GetInstance();
    manager->eventMap_.clear();

    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);

    // Fill eventMap to MAX_EVENT_MAP_SIZE
    for (int i = 0; i < 500; i++) {
        std::string eventName = "Event" + std::to_string(i);
        StatisticEventInfoParcel newEventInfo(eventName, "SubEvent", 1);
        std::vector<StatisticEventInfoParcel> eventInfos;
        eventInfos.emplace_back(newEventInfo);
        manager->SendStatisticEvents(newAppInfo, eventInfos);
    }

    EXPECT_EQ(manager->eventMap_.size(), 500);

    // Try to add one more event - should fail
    StatisticEventInfoParcel extraEventInfo("ExtraEvent", "SubEvent", 1);
    std::vector<StatisticEventInfoParcel> extraEventInfos;
    extraEventInfos.emplace_back(extraEventInfo);
    manager->SendStatisticEvents(newAppInfo, extraEventInfos);

    // EventMap should still be 500
    EXPECT_EQ(manager->eventMap_.size(), 500);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test NeedReportEvent with default interval
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, NeedReportEvent001, TestSize.Level1)
{
    DelayedSingleton<StatisticEventManager>::GetInstance()->defaultReportInterval_ = 100;

    std::string eventName = "TestEvent";
    StatisticEvent event(eventName);
    event.SetReportInterval(0); // Default interval

    bool needReport = DelayedSingleton<StatisticEventManager>::GetInstance()->NeedReportEvent(event, 100);
    EXPECT_TRUE(needReport);

    needReport = DelayedSingleton<StatisticEventManager>::GetInstance()->NeedReportEvent(event, 50);
    EXPECT_FALSE(needReport);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test NeedReportEvent with custom interval
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, NeedReportEvent002, TestSize.Level1)
{
    DelayedSingleton<StatisticEventManager>::GetInstance()->defaultReportInterval_ = 100;

    std::string eventName = "TestEvent";
    StatisticEvent event(eventName);
    event.SetReportInterval(200); // Custom interval

    bool needReport = DelayedSingleton<StatisticEventManager>::GetInstance()->NeedReportEvent(event, 200);
    EXPECT_TRUE(needReport);

    needReport = DelayedSingleton<StatisticEventManager>::GetInstance()->NeedReportEvent(event, 100);
    EXPECT_FALSE(needReport);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test InitTimedMap
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, InitTimedMap001, TestSize.Level1)
{
    auto manager = DelayedSingleton<StatisticEventManager>::GetInstance();
    manager->timedSet_.clear();
    manager->defaultReportInterval_ = 12345;

    manager->InitTimedMap();

    EXPECT_EQ(manager->timedSet_.size(), 1);
    EXPECT_NE(manager->timedSet_.find(12345), manager->timedSet_.end());
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test Init with null handler
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, Init001, TestSize.Level1)
{
    auto manager = DelayedSingleton<StatisticEventManager>::GetInstance();
    std::shared_ptr<OHOS::AppExecFwk::EventHandler> nullHandler = nullptr;

    manager->handler_ = nullptr;
    manager->Init(nullHandler);

    // handler_ should remain nullptr
    EXPECT_EQ(manager->handler_, nullptr);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test Init with valid handler
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, Init002, TestSize.Level1)
{
    auto manager = DelayedSingleton<StatisticEventManager>::GetInstance();

    // Create a mock handler
    auto runner = OHOS::AppExecFwk::EventRunner::Create("TestRunner");
    auto handler = std::make_shared<OHOS::AppExecFwk::EventHandler>(runner);

    manager->Init(handler);

    EXPECT_NE(manager->handler_, nullptr);
    EXPECT_EQ(manager->handler_, handler);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test GetEventName and SetReportInterval
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, GetEventNameAndSetReportInterval001, TestSize.Level1)
{
    std::string eventName = "TestEventName";
    StatisticEvent event(eventName);

    EXPECT_EQ(event.GetEventName(), eventName);

    event.SetReportInterval(500);
    EXPECT_EQ(event.GetReportInterval(), 500);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test ReportEvent
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, ReportEvent001, TestSize.Level1)
{
    std::string eventName = "TestReportEvent";
    StatisticEvent event(eventName);
    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);
    StatisticEventInfoParcel newEventInfo(eventName, "SubEvent", 5);

    event.AggregateEvent(newAppInfo, newEventInfo);

    // ReportEvent should not crash
    event.ReportEvent();
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test AggregateEvent with different bundle names
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, AggregateEvent004, TestSize.Level1)
{
    std::string eventName = "TestEvent";
    StatisticEvent event(eventName);

    std::string bundleName1 = "com.example.test1";
    AppInfoParcel newAppInfo1(bundleName1);
    StatisticEventInfoParcel newEventInfo1(eventName, "SubEvent", 10);
    event.AggregateEvent(newAppInfo1, newEventInfo1);

    std::string bundleName2 = "com.example.test2";
    AppInfoParcel newAppInfo2(bundleName2);
    StatisticEventInfoParcel newEventInfo2(eventName, "SubEvent", 20);
    event.AggregateEvent(newAppInfo2, newEventInfo2);

    EXPECT_EQ(event.eventCounts_.size(), 2);
    EXPECT_EQ(event.extraInfos_.size(), 2);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test SendStatisticEvents with multiple events
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, SendStatisticEvents005, TestSize.Level1)
{
    DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.clear();

    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);

    std::vector<StatisticEventInfoParcel> eventInfos;
    for (int i = 0; i < 5; i++) {
        std::string eventName = "Event" + std::to_string(i);
        StatisticEventInfoParcel newEventInfo(eventName, "SubEvent", i + 1);
        eventInfos.emplace_back(newEventInfo);
    }

    DelayedSingleton<StatisticEventManager>::GetInstance()->SendStatisticEvents(
        newAppInfo, eventInfos);

    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), 5);
}

/**
 * @tc.name: StatisticEventManagerTest
 * @tc.desc: Test ReportTimedStatisticEvent with no matching events
 * @tc.type: FUNC
 */
HWTEST_F(StatisticEventManagerTest, ReportTimedStatisticEvent002, TestSize.Level1)
{
    DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.clear();
    DelayedSingleton<StatisticEventManager>::GetInstance()->defaultReportInterval_ = 100;

    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);
    std::string eventName = "TestEvent";
    StatisticEventInfoParcel newEventInfo(eventName, "SubEvent", 1);
    std::vector<StatisticEventInfoParcel> eventInfos;
    eventInfos.emplace_back(newEventInfo);
    DelayedSingleton<StatisticEventManager>::GetInstance()->SendStatisticEvents(
        newAppInfo, eventInfos);

    // Report with different interval - event should not be removed
    DelayedSingleton<StatisticEventManager>::GetInstance()->ReportTimedStatisticEvent(200);
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), 1);
}
} // namespace OHOS::Ace
