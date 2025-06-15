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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "ani_test.h"
#include "performanceMonitor.cpp"
#include "frameworks/base/perfmonitor/perf_monitor.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class PerformanceMonitorTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: BeginTest001
 * @tc.desc: Test begin
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, BeginTest001, TestSize.Level1)
{
    ani_env *env = new ani_env;
    ASSERT_NE(env, nullptr);
    ani_string scene("LAUNCHER_APP_LAUNCH_FROM_ICON");
    ani_enum_item startInputType(2);
    ani_string note("APP_START_BEGIN");
    Begin(env, scene, startInputType, note);
    ASSERT_NE(PerfMonitor::GetPerfMonitor(), nullptr);
}

/**
 * @tc.name: EndTest001
 * @tc.desc: Test end
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, EndTest001, TestSize.Level1)
{
    ani_env *env = new ani_env;
    ASSERT_NE(env, nullptr);
    ani_string scene("LAUNCHER_APP_LAUNCH_FROM_ICON");
    ani_enum_item startInputType(2);
    ani_string note("APP_START_BEGIN");
    Begin(env, scene, startInputType, note);
    ASSERT_NE(PerfMonitor::GetPerfMonitor(), nullptr);
    End(env, scene);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mRecords.count(scene), 0);
}

/**
 * @tc.name: RecordInputEventTimeTest001
 * @tc.desc: Test RecordInputEventTime
 * @tc.type: FUNC
 */
HWTEST_F(PerformanceMonitorTest, RecordInputEventTimeTest001, TestSize.Level1)
{
    ani_env *env = new ani_env;
    ASSERT_NE(env, nullptr);
    ani_string scene("LAUNCHER_APP_LAUNCH_FROM_ICON");
    ani_enum_item startInputType(2);
    ani_string note("APP_START_BEGIN");
    ani_enum_item type(0);
    ani_enum_item sourceType(0);
    ani_double time(60);
    Begin(env, scene, startInputType, note);
    ASSERT_NE(PerfMonitor::GetPerfMonitor(), nullptr);
    RecordInputEventTime(env, type, sourceType, time);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mInputTime[LAST_DOWN], 60);
    End(env, scene);
    ASSERT_EQ(PerfMonitor::GetPerfMonitor()->mRecords.count(scene), 0);
}
} // namespace OHOS::Ace
