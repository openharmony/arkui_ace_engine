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
    StatisticEvent event;
    std::string bundleName = "com.example.test";
    AppInfoParcel newAppInfo(bundleName);
    std::string eventName = "";
    StatisticEventInfoParcel newEventInfo(eventName, 1);
    DelayedSingleton<StatisticEventManager>::GetInstance()->AggregateEvent(
        event, newAppInfo, newEventInfo);
    EXPECT_EQ(event.bundleNames.size(), 1);

    DelayedSingleton<StatisticEventManager>::GetInstance()->AggregateEvent(
        event, newAppInfo, newEventInfo);
    EXPECT_EQ(event.bundleNames.size(), 1);
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
    StatisticEventInfoParcel newEventInfo(eventName, 1);
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
    DelayedSingleton<StatisticEventManager>::GetInstance()->timedMap_.clear();
    DelayedSingleton<StatisticEventManager>::GetInstance()->timedMap_[1] = { "FA_APP_START" };
    DelayedSingleton<StatisticEventManager>::GetInstance()->InitReporter();
    
    std::string bundleName = "";
    AppInfoParcel newAppInfo(bundleName);
    std::string eventName = "FA_APP_START";
    StatisticEventInfoParcel newEventInfo(eventName, 1);
    std::vector<StatisticEventInfoParcel> eventInfos;
    eventInfos.emplace_back(newEventInfo);
    DelayedSingleton<StatisticEventManager>::GetInstance()->SendStatisticEvents(
        newAppInfo, eventInfos);

    DelayedSingleton<StatisticEventManager>::GetInstance()->ReportTimedStatisticEvent(0);
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), 1);

    DelayedSingleton<StatisticEventManager>::GetInstance()->ReportTimedStatisticEvent(1);
    EXPECT_EQ(DelayedSingleton<StatisticEventManager>::GetInstance()->eventMap_.size(), 0);
}
} // namespace OHOS::Ace
